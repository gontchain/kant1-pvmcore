//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//                 Реализационный модуль dw_cu.cpp                      //
//                                                                      //
//  Файл реализации функций класса Dwarf_Cu                             //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:33p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <assert.h>

#include "libelf.h"
#include "dwarferr.h"
#include "dwarftyp.h"
#include "dwarf.h"
#include "libdwarf.h"
#include "dwarfint.h"

//-------------------------------------------------------------------
//
// class Dwarf_CU
//
//-------------------------------------------------------------------

Dwarf_CU::Dwarf_CU(Dwarf_Off offset,Dwarf_Debug *dbg) throw(Dwarf_Error) :
    dc_debug(dbg),dc_length(0),dc_version_stamp(0),dc_abbrev_offset(0),
    dc_address_size(0),next(0),dc_abbrev_table(0),
    dc_first_die(0),dc_files(0),dc_lines(0),dc_is_line_info_read(False),
    dc_dirs(0),dc_comp_dir(0),dc_macro_tab(0)
{
    Dwarf_Unsigned 	length;
    Dwarf_Half      version_stamp;
    Dwarf_Unsigned  abbrev_offset;
    Dwarf_Small     address_size;
    Dwarf_Byte_Ptr 	cu_ptr;

    dc_debug_info_offset = offset;

    cu_ptr = (Dwarf_Byte_Ptr)(dbg->dd_debug_info + offset);

    dbg->read(&length, cu_ptr);
    cu_ptr += dbg->dd_lsize;

    dbg->read_2(&version_stamp,cu_ptr);
    cu_ptr += sizeof(Dwarf_Half);

    dbg->read(&abbrev_offset, cu_ptr);
    cu_ptr += dbg->dd_lsize;

    address_size = *(Dwarf_Small *)cu_ptr;
    cu_ptr++;

    if ((length < CU_VERSION_STAMP_SIZE + dbg->dd_lsize + CU_ADDRESS_SIZE_SIZE) 
            || (offset + length + dbg->dd_lsize >dbg-> dd_debug_info_size))
        throw Dwarf_Error_CU(Dwarf::DWARFERR,
                "bad length of compilation unit ");

    if (address_size != dbg->dd_lsize)
        throw Dwarf_Error_CU(Dwarf::DWARFERR,
                    "CU header address size not match Elf class");

    if (version_stamp != CURRENT_VERSION_STAMP)
        throw Dwarf_Error_CU(Dwarf::DWARFERR,"incorrect version stamp");

    if (abbrev_offset >= dbg->dd_debug_abbrev_size)
        throw Dwarf_Error_CU(Dwarf::DWARFERR,
                "bad offset in section .debug_abbrev");

    dc_length = length;
    dc_version_stamp = version_stamp;
    dc_abbrev_offset = abbrev_offset;
    dc_address_size = address_size;

    dc_abbrev_table = new Dwarf_Abbrev_Tab(ABBREV_HASH_TABLE_SIZE);

    while(1) {
        Dwarf_Abbrev *ptr = new Dwarf_Abbrev(abbrev_offset,dc_debug);
        if (ptr->code() == 0) {
            delete ptr;
            break;
        }
        dc_abbrev_table->insert(ptr);
	}
}

Dwarf_CU::~Dwarf_CU() throw(Dwarf_Error)
{
	if (dc_macro_tab) delete dc_macro_tab;      // удаляем таблицу макросов
	if (dc_abbrev_table) delete dc_abbrev_table;    // удаляем аббревиатуры
    if (dc_files) delete dc_files;              // удаляем таблицу имен файлов
    if (dc_dirs) delete dc_dirs;                // удаляем таблицу каталогов
    if (dc_lines) delete dc_lines;              // удаляем таблицу строк

    if (dc_first_die) delete dc_first_die;      // уничтожаем дерево DIE
}

//-------------------------------------------------------------------

Dwarf_Die *Dwarf_CU::get_first_die() throw(Dwarf_Error,Dwarf_No_Entry)
{
	if (dc_first_die) return dc_first_die;

	Dwarf_Unsigned info_offset = dc_debug_info_offset + 2 * dc_debug->dd_lsize
                                                      + sizeof(Dwarf_Half)
                                                      + 1;

	Dwarf_Unsigned end_info_offset = info_offset + dc_length 
                                                 + dc_debug->dd_lsize;

		// read all DIE tree
	try {
		if (*(info_offset + dc_debug->dd_debug_info) == 0)
			throw Dwarf_No_Entry();

		dc_first_die = new Dwarf_Die(info_offset,end_info_offset,this,NULL);

		if (dc_first_die->tag() != DW_TAG_compile_unit)
			throw Dwarf_Error_Die(Dwarf::DWARFERR,
                    "first DIE in CU not DW_TAG_compile_unit");

		dc_first_die->read_subtree(info_offset,True);	// read all tree
		return dc_first_die;
	}
	catch(Dwarf_Error) {
		if (dc_first_die) delete dc_first_die;
        dc_first_die = 0;
		throw;
	}
}

	// выдает DIE по смещению относительно начала CU
    // Функция переделана на итеративный поиск 16.10.97 Ч.А.
    // т.к. для больших файлов рекурсивный поиск дает переполнение стека
Dwarf_Die *Dwarf_CU::off_cu_die(Dwarf_Off offset) throw(Dwarf_No_Entry,Dwarf_Error)
{
        // добавляем смещение самой CU, т.к. функция findoff ищет
        // по полному смещению (в секции .debug_info).
    Dwarf_Off search_offset = offset + dc_debug_info_offset;

    Dwarf_Die * CurrDie = get_first_die();

    while( CurrDie ) {
            // если смещение совпадает, то возвращаем найденный DIE
        if ( CurrDie->dieoffset() == search_offset )
            return CurrDie;

            // проверка сохранения инварианта
        //assert( CurrDie->dieoffset() <= search_offset );
        if ( CurrDie->dieoffset() > search_offset ) {
			throw Dwarf_Error_Die(Dwarf::DWARFERR, "invalid offset in DIE reference");
        }


            // если есть брат и его смещение меньше искомого, то переходим к нему
        if ( CurrDie->sibling() != NULL
                    && CurrDie->sibling()->dieoffset() <= search_offset ) {
            CurrDie = CurrDie->sibling();
            continue;
        }

            // нужный нам DIE находится среди сыновей текущего DIE
            // переходим к сыну
        if ( CurrDie->child() != NULL ) {
            CurrDie = CurrDie->child();
            continue;
        }

            // нет DIE с нужным нам смещением
        throw Dwarf_No_Entry();
    }

        // нет DIE с нужным нам смещением
    throw Dwarf_No_Entry();
    return 0;
	//return get_first_die()->findoff(offset + dc_debug_info_offset);
}


//-------------------------------------------------------------------
//
// внутренняя функция читает информацию о строках и заполняет
// таблицы информации о строках(dc_lines), таблицу имен каталогов(dc_dirs)
// а также таблицу имен файлов исходных текстов
//
//-------------------------------------------------------------------

void Dwarf_CU::read_line_info() throw(Dwarf_Error,Dwarf_No_Entry)
{
		// This pointer is used to scan the portion of
		// the .debug_line section for the current cu.
	Dwarf_Small *line_ptr;

		// This points to the last byte of the
		// .debug_line portion for the current cu.
	Dwarf_Small *line_ptr_end;

		// This points to the end of the statement program prologue
		// for the current cu, and serves to check that the prologue
		// was correctly decoded.
	Dwarf_Small *check_line_ptr;

		// Pointer to a DW_AT_stmt_list attribute
		// in case it exists in the die.
	Dwarf_Attribute *stmt_list_attr;

		// Pointer to DW_AT_comp_dir attribute in die.
	Dwarf_Attribute *comp_dir_attr;

		// Pointer to name of compilation directory.
	Dwarf_Small *comp_dir = NULL;
	USED(comp_dir);

		// Offset into .debug_line specified by a
		// DW_AT_stmt_list attribute.
	Dwarf_Unsigned line_offset;

		// These are the fields of the statement program header.
	Dwarf_Unsigned  total_length;
	Dwarf_Half      version;
	Dwarf_Unsigned  prologue_length;
	Dwarf_Small     minimum_instruction_length;
	Dwarf_Small     default_is_stmt;
	Dwarf_Sbyte     line_base;
	Dwarf_Small     line_range;
	Dwarf_Small     opcode_base;

		// The full UCHAR_MAX number of standard opcode
		// lengths is used for the opcode_length table because
		// that is the only totally safe limit for static
		// allocation to avoid malloc-ing the exact size needed.
	Dwarf_Small     	opcode_length[UCHAR_MAX];
	Dwarf_Filename  *   file_entries;

		// These are the state machine state variables.
	Dwarf_Addr	address;
	Dwarf_Word  file;
	Dwarf_Word  line;
	Dwarf_Word  column;
	Dwarf_Bool  is_stmt;
	Dwarf_Bool  basic_block;
	Dwarf_Bool  end_sequence;

		// These pointers are used to build the list of files names
		// by this cu.  cur_file_entry points to the file name being
		// added, and prev_file_entry to the previous one.
	Dwarf_Filename *cur_file_entry;
	Dwarf_Filename *prev_file_entry;

	Dwarf_Sword i, file_entry_count, include_directories_count;

		// This is the current opcode read
		// from the statement program.
	Dwarf_Small opcode;

		// This is a pointer to the current
		// line being added to the line matrix.
	Dwarf_Line 	*curr_line;

		// These variables are used to decode leb128 numbers.
		// Leb128_num holds the decoded number, and leb128_length
		// is its length in bytes.
	Dwarf_Word 	leb128_num;
	Dwarf_Word  leb128_length;
	Dwarf_Sword advance_line;

		// This is the operand of the latest fixed_advance_pc
		// extended opcode.
	Dwarf_Half 	fixed_advance_pc;

		// Counts the number of lines in
		// the line matrix.
	Dwarf_Word 	line_count = 0;

		// This is the length of an extended opcode instr.
	Dwarf_Word  instr_length;
	Dwarf_Small ext_opcode;

		// Used to chain together pointers to line table entries
		// that are later used to create a block of Dwarf_Line entries.
	Dwarf_Line 	*chain_line;
	Dwarf_Line 	*head_chain = NULL;
	Dwarf_Line	*curr_chain = NULL;

        // Указатель на таблицу элементов типа Dwarf_Line
	Dwarf_Line_Tab *block_line;

		// Объект Dwarf_Debug к которому относится данная CU
	Dwarf_Debug *dbg = dc_debug;

	// ---------- НАЧАЛО КОДА -----------

	dbg = dc_debug;
	if (dbg->dd_debug_line == NULL)
		throw Dwarf_No_Entry();

	stmt_list_attr = get_first_die()->attr(DW_AT_stmt_list);

	line_offset = stmt_list_attr->form_udata();

	if (line_offset >= dbg->dd_debug_line_size)
		throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
			"offset of lines for current CU outside .debug_line");

	line_ptr = dbg->dd_debug_line + line_offset;

		// If die has DW_AT_comp_dir attribute, get the
		// string that names the compilation directory.

	try {
		comp_dir_attr = get_first_die()->attr(DW_AT_comp_dir);

		char *cdir;

		cdir = comp_dir_attr->form_string();
		comp_dir = (Dwarf_Small *)cdir;
	}
    catch (Dwarf_No_Entry) {
       	comp_dir = NULL;
	}

		// Following is a straightforward decoding of the
		// statement program prologue information.
	dbg->read(&total_length, line_ptr);
	line_ptr += dbg->dd_lsize;
	line_ptr_end = line_ptr + total_length;

	if (line_ptr_end > dbg->dd_debug_line + dbg->dd_debug_line_size)
		throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,"length of .debug_line segment bad");

	dbg->read_2(&version, line_ptr);
	line_ptr += sizeof(Dwarf_Half);
	if (version != CURRENT_VERSION_STAMP)
		throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,"incorrect version stamp");

	dbg->read(&prologue_length, line_ptr);
	line_ptr += dbg->dd_lsize;
	check_line_ptr = line_ptr;

	minimum_instruction_length = *(Dwarf_Small *)line_ptr;
	line_ptr = line_ptr + sizeof(Dwarf_Small);

	default_is_stmt = *(Dwarf_Small *)line_ptr;
	line_ptr = line_ptr + sizeof(Dwarf_Small);

	line_base = *(Dwarf_Sbyte *)line_ptr;
	line_ptr = line_ptr + sizeof(Dwarf_Sbyte);

	line_range = *(Dwarf_Small *)line_ptr;
	line_ptr = line_ptr + sizeof(Dwarf_Small);

	opcode_base = *(Dwarf_Small *)line_ptr;
	line_ptr = line_ptr + sizeof(Dwarf_Small);

	for (i = 1; i < opcode_base; i++) {
		opcode_length[i] = *(Dwarf_Small *)line_ptr;
		line_ptr = line_ptr + sizeof(Dwarf_Small);
	}

	// cur_file_entry, file_entries, prev_file_entry are used for build list
	// of directories names

    Dwarf_Dirname *dir_entries = NULL;
    Dwarf_Dirname *cur_dir_entry;
    Dwarf_Dirname *prev_dir_entry = NULL;

	include_directories_count = 0;
	while ((*(char *)line_ptr) != '\0') {
		cur_dir_entry = new Dwarf_Dirname(line_ptr);
		if (dir_entries == NULL) {
			dir_entries = cur_dir_entry;
			prev_dir_entry = cur_dir_entry;
		}
		else {
			prev_dir_entry->next = cur_dir_entry;
			prev_dir_entry = cur_dir_entry;
		}

		line_ptr = line_ptr + strlen((char *)line_ptr) + 1;
		include_directories_count++;
	}
	line_ptr++;

	dc_dirs = new Dwarf_Dirs_Tab(include_directories_count);
	dc_dirs->convert_list(dir_entries);

    	// теперь все имена включенных каталогов в таблице dc_dirs

    	// строим таблицу имен файлов исходного текста

	file_entry_count = 0;
	file_entries = prev_file_entry = NULL;
	while (*(char *)line_ptr != '\0') {

		cur_file_entry = new Dwarf_Filename(line_ptr);

		cur_file_entry->df_name = (char *)line_ptr;
		line_ptr = line_ptr + strlen((char *)line_ptr) + 1;

		cur_file_entry->df_dir_index =
			Dwarf::decode_u_leb128(line_ptr,leb128_length);
		line_ptr = line_ptr + leb128_length;

		cur_file_entry->df_time_last_mod =
			Dwarf::decode_u_leb128(line_ptr,leb128_length);
		line_ptr = line_ptr + leb128_length;

		cur_file_entry->df_file_length =
			Dwarf::decode_u_leb128(line_ptr,leb128_length);
		line_ptr = line_ptr + leb128_length;

		if (file_entries == NULL)
			file_entries = cur_file_entry;
		else
			prev_file_entry->next = cur_file_entry;

		prev_file_entry = cur_file_entry;

		file_entry_count++;
	}

    // теперь все имена файлов в списке, но таблицу построить еще не можем,
    // т.к. новые имена файлов могут встретиться в самой программе.
    // таблица будет построена после разбора программы машины состояний

	line_ptr++;

	if (line_ptr != check_line_ptr + prologue_length)
   	throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,"length of .debug_line segment bad"); 

		// Initialize the state machine.
	address = 0;
	file = 1;
	line = 1;
	column = 0;
	is_stmt = default_is_stmt;
	basic_block = False;
	end_sequence = False;

		// Start of statement program.
	while (line_ptr < line_ptr_end) {

		opcode = *(Dwarf_Small *)line_ptr;
		line_ptr++;
		switch (opcode) {

		// These are special opcodes between opcode_base
		// and UCHAR_MAX.

			default : {

				opcode = (Dwarf_Small)(opcode - opcode_base);
                Dwarf_Addr addr_adv = minimum_instruction_length * (opcode / line_range);
                Dwarf_Word line_adv = line_base + opcode % line_range;

                    // Если одному адресу соответствуют несколько строк текста,
                    // то берем последнюю.
                    // Внесено ЧАЛ 20.01.2000.
                if ( addr_adv == 0 ) {
                    line += line_adv;
                    break;
                }

				address = address + addr_adv;
				line = line + line_adv;

				curr_line = new Dwarf_Line();

				curr_line->dl_address = address;
				curr_line->dl_file = file;
				curr_line->dl_line = line;
				curr_line->dl_column = Dwarf_Half(column);
				curr_line->dl_is_stmt = Dwarf_Small(is_stmt);
				curr_line->dl_basic_block = Dwarf_Small(basic_block);
				curr_line->dl_end_sequence = Dwarf_Small(end_sequence);
				curr_line->dl_cu = this;
				line_count++;

				chain_line = curr_line;

				if (head_chain == NULL)
					head_chain = curr_chain = chain_line;
				else {
					curr_chain->next = chain_line;
					curr_chain = chain_line;
				}

				basic_block = False;
				break;
			}

			case DW_LNS_copy : {
				if (opcode_length[DW_LNS_copy] != 0)
					throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
						"number of operands to line instruction bad");

				curr_line = new Dwarf_Line();

				curr_line->dl_address = address;
				curr_line->dl_file = file;
				curr_line->dl_line = line;
				curr_line->dl_column = Dwarf_Half(column);
				curr_line->dl_is_stmt = Dwarf_Small(is_stmt);
				curr_line->dl_basic_block = Dwarf_Small(basic_block);
				curr_line->dl_end_sequence = Dwarf_Small(end_sequence);
				curr_line->dl_cu = this;
				line_count++;

				chain_line = curr_line;

				if (head_chain == NULL)
					head_chain = curr_chain = chain_line;
				else {
					curr_chain->next = chain_line;
					curr_chain = chain_line;
				}

				basic_block = False;
				break;
			}

			case DW_LNS_advance_pc : {
				if (opcode_length[DW_LNS_advance_pc] != 1)
					throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
						"number of operands to line instruction bad");

				leb128_num = Dwarf::decode_leb128_uword(line_ptr);
				address = address + minimum_instruction_length * leb128_num;
				break;
			}

			case DW_LNS_advance_line : {
				if (opcode_length[DW_LNS_advance_line] != 1)
					throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
						"number of operands to line instruction bad");

				advance_line = Dwarf::decode_leb128_sword(line_ptr);
				line = line + advance_line;
				break;
			}

			case DW_LNS_set_file : {
				if (opcode_length[DW_LNS_set_file] != 1)
					throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
						"number of operands to line instruction bad");

				file = Dwarf::decode_leb128_uword(line_ptr);
				break;
			}

			case DW_LNS_set_column : {
				if (opcode_length[DW_LNS_set_column] != 1)
					throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
						"number of operands to line instruction bad");

				column = Dwarf::decode_leb128_uword(line_ptr);
				break;
			}

			case DW_LNS_negate_stmt : {
				if (opcode_length[DW_LNS_negate_stmt] != 0)
					throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
						"number of operands to line instruction bad");

				is_stmt = !is_stmt;
				break;
			}

			case DW_LNS_set_basic_block : {
				if (opcode_length[DW_LNS_set_basic_block] != 0)
					throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
						"number of operands to line instruction bad");

				basic_block = True;
				break;
			}

			case DW_LNS_const_add_pc : {
				opcode = Dwarf_Small(UCHAR_MAX - opcode_base);
				address = address + minimum_instruction_length *
					(opcode / line_range);

				break;
			}

			case DW_LNS_fixed_advance_pc : {
				if (opcode_length[DW_LNS_fixed_advance_pc] != 1)
					throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
						"number of operands to line instruction bad");

				dbg->read_2(&fixed_advance_pc, line_ptr);
				line_ptr += sizeof(Dwarf_Half);
				address = address + fixed_advance_pc;
				break;
			}

			case DW_EXTENDED_OPCODE : {
				instr_length = Dwarf::decode_leb128_uword(line_ptr);
				ext_opcode = *(Dwarf_Small *)line_ptr;
				line_ptr++;
				switch (ext_opcode) {
					case DW_LNE_end_sequence : {
						end_sequence = True;

						curr_line = new Dwarf_Line();

						curr_line->dl_address = address;
						curr_line->dl_file = file;
						curr_line->dl_line = line;
						curr_line->dl_column = Dwarf_Half(column);
						curr_line->dl_is_stmt = False;
						curr_line->dl_basic_block = Dwarf_Small(basic_block);
						curr_line->dl_end_sequence = Dwarf_Small(end_sequence);
						curr_line->dl_cu  = this;
						line_count++;

						chain_line = curr_line;

						if (head_chain == NULL)
							head_chain = curr_chain = chain_line;
						else {
							curr_chain->next = chain_line;
							curr_chain = chain_line;
						}

						address = 0;
						file = 1;
						line = 1;
						column = 0;
						is_stmt = default_is_stmt;
						basic_block = False;
						end_sequence = False;

						break;
					}
					case DW_LNE_set_address : {
						if (instr_length - 1 != dbg->dd_lsize)
							throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
								"error in DW_LNE_set_address instruction");

						dbg->read(&address, line_ptr);
						line_ptr += dbg->dd_lsize;

						break;
					}
					case DW_LNE_define_file : {

						cur_file_entry = new Dwarf_Filename(line_ptr);
						line_ptr = line_ptr + strlen((char *)line_ptr) + 1;

						cur_file_entry->df_dir_index =
							Dwarf::decode_u_leb128(line_ptr,leb128_length);
						line_ptr = line_ptr + leb128_length;

						cur_file_entry->df_time_last_mod =
							Dwarf::decode_u_leb128(line_ptr,leb128_length);
						line_ptr = line_ptr + leb128_length;

						cur_file_entry->df_file_length =
							Dwarf::decode_u_leb128(line_ptr,leb128_length);
						line_ptr = line_ptr + leb128_length;

						if (file_entries == NULL)
							file_entries = cur_file_entry;
						else
							prev_file_entry->next = cur_file_entry;
						prev_file_entry = cur_file_entry;

						file_entry_count++;

						break;
					}

					default :
						throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
							"error in DW_EXTENDED_OPCODE instruction");
				}
			}
		}
	}

	block_line = new  Dwarf_Line_Tab(line_count);
	block_line->convert_list(head_chain);

    	// теперь имена файлов заносим в таблице dc_files
	dc_files = new Dwarf_Filename_Tab(file_entry_count, this);
	dc_files->convert_list(file_entries);

        // теперь все готово выставляем переменные
	dc_comp_dir = comp_dir;
    dc_lines = block_line;
    dc_is_line_info_read = True;

}

//-------------------------------------------------------------------

void Dwarf_CU::read_macro(void) throw(Dwarf_Error,Dwarf_No_Entry)
{
	delete new Dwarf_Macro_Tab(0);
	throw Dwarf_No_Entry();
//	throw Dwarf_Error_Internal(Dwarf::DWARFERR,"not yet realised");
}


//-------------------------------------------------------------------

Dwarf_Line_Tab	*Dwarf_CU::get_lineinfo() throw(Dwarf_Error,Dwarf_No_Entry)
{
	if (dc_is_line_info_read)
		return dc_lines;

	read_line_info();

	return dc_lines;
}

//-------------------------------------------------------------------
// выдает каталог в котором проходила компиляция
//-------------------------------------------------------------------
const Dwarf_Small * Dwarf_CU::comp_dir() throw(Dwarf_Error)
{ 
	if (dc_is_line_info_read)
        return dc_comp_dir; 

	read_line_info();

    return dc_comp_dir; 
}

//-------------------------------------------------------------------

Dwarf_Filename_Tab *Dwarf_CU::srcfiles() throw(Dwarf_Error)
{
	if (dc_is_line_info_read)
		return dc_files;

	read_line_info();

	return dc_files;
}

//-------------------------------------------------------------------

Dwarf_Dirs_Tab *Dwarf_CU::srcdirs() throw(Dwarf_Error)
{
	if (dc_is_line_info_read)
		return dc_dirs;

	read_line_info();

	return dc_dirs;
}

//-------------------------------------------------------------------

Dwarf_Macro_Tab *Dwarf_CU::get_macroinfo() throw(Dwarf_Error,Dwarf_No_Entry)
{
	if (dc_macro_tab == NULL)
		read_macro();

	return dc_macro_tab;
}
