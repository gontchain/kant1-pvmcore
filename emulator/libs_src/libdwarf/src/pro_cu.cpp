//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//               Реализационный модуль pro_cu.cpp                       //
//                                                                      //
//  Файл реализации функций класса Dwarf_P_CU                           //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:33p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------
//
// class Dwarf_P_CU
//
//-------------------------------------------------------------------

#include <string.h>

#include "libelf.h"
#include "dwarferr.h"
#include "dwarftyp.h"
#include "dwarf.h"
#include "libdwarf.h"
#include "dwarfint.h"

#include "pro_line.h"
#include "pro_aran.h"
#include "pro_pubn.h"

Dwarf_P_CU::Dwarf_P_CU(Dwarf_P_Debug *dbg) throw() : dpc_file_entries(NULL),
    dpc_last_file_entry(NULL),	dpc_n_file_entries(0),dpc_inc_dirs(NULL),
    dpc_last_inc_dir(NULL),dpc_n_inc_dirs(0),dpc_lines(NULL),dpc_last_line(NULL),
    dpc_debug(dbg),next(NULL),dpc_root(NULL),dpc_line_offset(0),dpc_arange(NULL),
    dpc_last_arange(NULL),dpc_arange_count(0),dpc_info_offset(0),
    dpc_pubname(NULL),dpc_pubname_count(0),dpc_last_pubname(NULL)
{
	DEBUG("make cu\n")
}

Dwarf_P_CU::~Dwarf_P_CU() throw(Dwarf_Error)
{
    DEBUG("delete cu\n")
        // delete something else
    if (dpc_pubname) delete dpc_pubname;
    if (dpc_arange) delete dpc_arange;

    if (dpc_root) delete dpc_root;
    if (dpc_file_entries) {
        Dwarf_P_F_Entry *ptr;
        while (dpc_file_entries != NULL) {
            ptr = dpc_file_entries->next;
            delete dpc_file_entries;
            dpc_file_entries = ptr;
        }
    }
    if (dpc_inc_dirs) {
        Dwarf_P_Inc_Dir *ptr;
        while (dpc_inc_dirs != NULL) {
            ptr = dpc_inc_dirs->next;
            delete dpc_inc_dirs;
            dpc_inc_dirs = ptr;
        }
    }
    if (dpc_lines) {
        Dwarf_P_Line *ptr;
        while (dpc_lines != NULL) {
            ptr = dpc_lines->next;
            delete dpc_lines;
            dpc_lines = ptr;
        }
    }
}

//-----------------------------------------------------------
//-----------------------------------------------------------

Dwarf_P_Die *Dwarf_P_CU::make_root() throw(Dwarf_Error)
{
	if (dpc_root != NULL)
		throw Dwarf_Error_Pro_CU("the root DIE already exist");

	dpc_root = new Dwarf_P_Die(this,NULL,DW_TAG_compile_unit);

   return dpc_root;
}

//-----------------------------------------------------------
// внутренняя функция для создания элементов таблицы строк
//-----------------------------------------------------------

void Dwarf_P_CU::int_add_line_entry(
							Dwarf_Unsigned file_index,
							Dwarf_Addr code_address,
							Dwarf_Unsigned symidx,
							Dwarf_Unsigned line_no,
							Dwarf_Signed col_no,
							Dwarf_Bool is_stmt_begin,
							Dwarf_Bool is_bb_begin,
							Dwarf_Small opc
							) throw(Dwarf_Error)
{
    if (dpc_lines == NULL) {
        dpc_lines = new Dwarf_P_Line;
        dpc_last_line = dpc_lines;
    } else {

            // Добавлено 25.01.00 ЧАЛ
            // Если не меняется адрес, то обновляем последнюю строку.
        if ( dpc_last_line->dpl_address == code_address 
                && dpc_last_line->dpl_file == file_index
                && dpc_last_line->dpl_is_stmt == is_stmt_begin 
                && dpc_last_line->dpl_basic_block == is_bb_begin 
                && opc == 0 ) {

            dpc_last_line->dpl_line = line_no;
            return;
        }

            // Иначе добавляем новую строку.
        dpc_last_line->next = new Dwarf_P_Line;
        dpc_last_line = dpc_last_line->next;
    }

    dpc_last_line->dpl_address = code_address;
    dpc_last_line->dpl_file = file_index;
    dpc_last_line->dpl_line = line_no;
    dpc_last_line->dpl_column = col_no;
    dpc_last_line->dpl_is_stmt = Dwarf_Ubyte(is_stmt_begin);
    dpc_last_line->dpl_basic_block = Dwarf_Ubyte(is_bb_begin);
    dpc_last_line->dpl_opc = opc;
    dpc_last_line->dpl_r_symidx = symidx;
}


void Dwarf_P_CU::add_line_entry(
					Dwarf_Unsigned file_index,
					Dwarf_Addr code_address,
					Dwarf_Unsigned line_no,
					Dwarf_Signed col_no,
					Dwarf_Bool is_stmt_begin,
					Dwarf_Bool is_bb_begin
					) throw (Dwarf_Error)
{
	int_add_line_entry(file_index,code_address,0,line_no,col_no,
		is_stmt_begin,is_bb_begin,0);
}

void Dwarf_P_CU::lne_set_address(Dwarf_Addr offset, Dwarf_Unsigned symidx)
	throw (Dwarf_Error)
{
	Dwarf_Small opc = DW_LNE_set_address;

	int_add_line_entry(0,offset,symidx,0,0,0,0,opc);

}

void Dwarf_P_CU::lne_end_sequence(Dwarf_Addr end_address) throw (Dwarf_Error)
{
	Dwarf_Ubyte opc = DW_LNE_end_sequence;
	int_add_line_entry(0,end_address,0,0,0,0,0,opc);
}

Dwarf_Unsigned Dwarf_P_CU::add_directory_decl(char *name) throw (Dwarf_Error)
{

	if (dpc_inc_dirs == NULL) {
		dpc_inc_dirs = new Dwarf_P_Inc_Dir;

		dpc_last_inc_dir = dpc_inc_dirs;
		dpc_n_inc_dirs = 1;
	}
	else {
		dpc_last_inc_dir->next = new Dwarf_P_Inc_Dir;

		dpc_last_inc_dir = dpc_last_inc_dir->next;
		dpc_n_inc_dirs++;
	}

	dpc_last_inc_dir->dpid_name = new char[strlen(name) + 1];

	strcpy(dpc_last_inc_dir->dpid_name, name);
	dpc_last_inc_dir->next = NULL;

	return dpc_n_inc_dirs;

}

Dwarf_Unsigned Dwarf_P_CU::add_file_decl(
						char *name,
						Dwarf_Unsigned dir_idx,
						Dwarf_Unsigned time_mod,
						Dwarf_Unsigned length
						) throw (Dwarf_Error)
{
	Dwarf_P_F_Entry *cur;
	char *ptr;

	int nbytes_idx, nbytes_time, nbytes_len;
	char buffidx[ENCODE_SPACE_NEEDED];
	char bufftime[ENCODE_SPACE_NEEDED];
	char bufflen[ENCODE_SPACE_NEEDED];

	if (dpc_file_entries == NULL) {
		 dpc_file_entries = new Dwarf_P_F_Entry;

		 cur = dpc_file_entries;
		 dpc_last_file_entry = cur;
		 dpc_n_file_entries = 1;
	}
	else {
		 cur = dpc_last_file_entry;
		 cur->next = new Dwarf_P_F_Entry;

		 cur = cur->next;
		 dpc_last_file_entry = cur;
		 dpc_n_file_entries++;
	}
	cur->dpfe_name = new char [strlen(name)+1];
	strcpy((char *) cur->dpfe_name, name);

	Dwarf::encode_leb128_nm(dir_idx, &nbytes_idx,buffidx,sizeof(buffidx));
	Dwarf::encode_leb128_nm(time_mod, &nbytes_time, bufftime,sizeof(bufftime));
	Dwarf::encode_leb128_nm(length, &nbytes_len,bufflen,sizeof(bufflen));

    cur->dpfe_args = new char[nbytes_idx+nbytes_time+nbytes_len];

    ptr = cur->dpfe_args;
    memcpy((void *)ptr,buffidx,nbytes_idx);
    ptr += nbytes_idx;
    memcpy((void *)ptr,bufftime,nbytes_time);
    ptr += nbytes_time;
    memcpy((void *)ptr,bufflen, nbytes_len);
    ptr += nbytes_len;
    cur->dpfe_nbytes = nbytes_idx+nbytes_time+nbytes_len;
    cur->next = NULL;
    USED(ptr);

	return dpc_n_file_entries;

}

	// функции работы с макрокомандами

void Dwarf_P_CU::def_macro(Dwarf_Unsigned lineno,char *name,char *value)
{
}

void Dwarf_P_CU::undef_macro(Dwarf_Unsigned lineno,char *name)
{
}

void Dwarf_P_CU::start_macro_file(Dwarf_Unsigned lineno, Dwarf_Unsigned file_index)
{
}

void Dwarf_P_CU::end_macro_file()
{
}

	// функции работы с диапазонами адресов

// Функция добавляет адресный диапазон к списку
// адресных диапазонов данной CU.

void Dwarf_P_CU::add_arange(
						Dwarf_Addr begin_address,
						Dwarf_Unsigned length,
						Dwarf_Signed symbol_index) throw(Dwarf_Error)
{
	Dwarf_P_Arange	*arange;

	arange = new Dwarf_P_Arange(begin_address,length,symbol_index);

	if (dpc_arange == NULL)
	  dpc_arange = dpc_last_arange = arange;
	else {
	  dpc_last_arange->next = arange;
	  dpc_last_arange = arange;
	}
	dpc_arange_count++;
}


//-------------------------------------------------------------------
//
// end of functions of class Dwarf_P_CU
//
//-------------------------------------------------------------------



//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Конец реализационного файла pro_cu.cpp                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
