//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//                 Реализационный модуль libdwarf.cpp                   //
//                                                                      //
//  Файл реализации различных мелких функций библиотеки                 //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:33p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "libelf.h"
#include "dwarferr.h"
#include "dwarftyp.h"
#include "dwarf.h"
#include "libdwarf.h"
#include "dwarfint.h"

//
// intializing of global variables
//

Dwarf_Signed Dwarf::elf_sects[NUM_DEBUG_SECTIONS];
Dwarf_Signed Dwarf::sect_name_idx[NUM_DEBUG_SECTIONS];
Dwarf_Signed Dwarf::reloc_sects[NUM_DEBUG_SECTIONS];

char *Dwarf::sectnames[] = {
		  ".debug_info",
		  ".debug_line",
		  ".debug_abbrev",
		  ".debug_frame",
		  ".debug_aranges",
		  ".debug_pubnames",
		  ".debug_str",
		  ".debug_macinfo"
};

Dwarf_Ubyte Dwarf::std_opcode_len[] =
			  { 0,    // DW_LNS_copy
				 1,    // DW_LNS_advance_pc
				 1,    // DW_LNS_advance_line
				 1,    // DW_LNS_set_file
				 1,    // DW_LNS_set_column
				 0,    // DW_LNS_negate_stmt
				 0,    // DW_LNS_set_basic_block
				 0,    // DW_LNS_const_add_pc
				 1,    // DW_LNS_fixed_advance_pc
			  };

// The augmentation string.
const char *Dwarf::DW_DEBUG_FRAME_AUGMENTER_STRING = "nc v1";
const char *Dwarf::DW_EMPTY_STRING = "";

const char *Dwarf::DWARFERR = "Dwarf error - ";
const char *Dwarf::DWARF_PRO_ERR = "Dwarf producer error - ";

//-------------------------------------------------------------------
//
// class Dwarf_Loc
//
//-------------------------------------------------------------------

Dwarf_Loc::Dwarf_Loc(Dwarf_Small atom,Dwarf_Unsigned number,Dwarf_Unsigned number2,
			Dwarf_Unsigned offset) : dl_atom(atom),dl_number(number),
			dl_number2(number2),dl_offset(offset),next(NULL),table(NULL)
{
}

//-------------------------------------------------------------------
//
// class Dwarf_Locdesc
//
//-------------------------------------------------------------------

Dwarf_Locdesc::Dwarf_Locdesc(Dwarf_Unsigned count) :
	Dwarf_Tab<Dwarf_Loc,Dwarf_Locdesc>(count), next(NULL), table(NULL)
{
}

//-------------------------------------------------------------------
//
// class Dwarf_Line_Tab
//
//-------------------------------------------------------------------

    // выдает первую строку с наименьшим расстоянием до pc
Dwarf_Line * Dwarf_Line_Tab::pcline(
        Dwarf_Addr pc , 
        Dwarf_Line_Tab::Slide slide) 
            throw (Dwarf_No_Entry)
{
    // Scans the line matrix for the current cu
    // to which a pointer exists in dbg.

    Dwarf_Line  *line;
    Dwarf_Line  *prev_line;

    //  These flags are for efficiency reasons.
    //  Check_line is True initially, but set False when the address
    //  of the current line is greater than pc.  It is set True only
    //  when the address of the current line falls below pc.  This
    //  assumes that addresses within the same segment increase, and
    //  we are only interested in the switch from a less than pc
    //  address to a greater than.
    //  First_line is set True initially, but set False after the first
    //  line is scanned.  This is to prevent looking at the address of
    //  previous line when slide is DW_DLS_BACKWARD, and the first line
    //  is being scanned.

    Dwarf_Bool  check_line;
    Dwarf_Bool  first_line;


    //  Diff tracks the smallest difference a line address
    //  and the input pc value.

    Dwarf_Unsigned    diff;
    Dwarf_Unsigned    i;


    // For the slide = DW_DLS_BACKWARD case, pc_less is the value
    // of the address of the line immediately preceding the first
    // line that has value greater than pc.
    // For the slide = DW_DLS_FORWARD case, pc_more is the values
    // of address for the first line that is greater than pc.
    // Diff is the difference between either of the these values
    // and pc.

    Dwarf_Addr  pc_less;
    Dwarf_Addr  pc_more;


        // указывает на строку с наименьшим на данный момент 
        // отстоянием от pc
        
    Dwarf_Line  *pc_line = NULL;


    check_line = True;
    first_line = True;
    diff = MAX_LINE_DIFF;

    for (i = 0; i < count(); i++) {
        line = (*this)[i];
        prev_line = first_line ? NULL : (*this)[ i - 1 ];

        if (line->addr() == pc) {       // нашли строку начинающуюся
                                        // точно с данного адреса

                // если это команда end_sequence, то ищем дальше
            if ( !line->is_endsequence() )
                return line;                                         
        }
        else {
            
                // проверяем переход с адреса меньшего pc 
                // на больший
            
            if (check_line && line->addr() > pc &&
                (first_line ? 0 : prev_line->addr()) < pc) {
        

                if (slide == DW_DLS_BACKWARD && !first_line) {
                    pc_less = prev_line->addr();
                    if (pc - pc_less <= diff) {
                        pc_line = prev_line;    // запомнили строку
                        diff = pc - pc_less;    // запомнили разницу адресов
                    }
                    check_line = False;
                }
                else if (slide == DW_DLS_FORWARD) {
                    pc_more = line->addr();
                    if (pc_more - pc <= diff) {
                        pc_line = line;
                        diff = pc_more - pc;
                    }
                    check_line = False;
                }
            }
            else {
                    // проверяем адреса только когда они становятся 
                    // меньше pc
                if (line->addr() < pc)
                    check_line = True;
            }
        }

        first_line = False;
    }

    if (pc_line == NULL) throw Dwarf_No_Entry();
    return pc_line;    
}

//-------------------------------------------------------------------
//
// end of functions of class Dwarf_Line_Tab
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// class Dwarf_Global_Tab
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// end of functions of class Dwarf_Global_Tab
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// class Dwarf_Arange_Tab
//
//-------------------------------------------------------------------

Dwarf_Arange *Dwarf_Arange_Tab::get_arange(Dwarf_Addr address)
	throw(Dwarf_Error,Dwarf_No_Entry)
{
	Dwarf_Arange *cur_arange;

	for (Dwarf_Unsigned i = 0;i < count();i++) {
		cur_arange = table[i];
		if (address >= cur_arange->address() && 
                address < cur_arange->address() + cur_arange->length())
			return cur_arange;
	}
	throw Dwarf_No_Entry();
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return 0;
#endif
}

//-------------------------------------------------------------------
//
// end of functions of class Dwarf_Arenge_Tab
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// class Dwarf_Macro_Tab
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// end of functions of class Dwarf_Macro_Tab
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// class Dwarf_Line
// функции класса Dwarf_Line
//
//-------------------------------------------------------------------

char *Dwarf_Line::srcfile() throw(Dwarf_Error)
{
    Dwarf_Filename  *file_entry;

	if (dl_cu == NULL)
		throw Dwarf_Error_Internal(Dwarf::DWARFERR,
			"null cu pointer in Dwarf_Line::srcfile");

	if (dl_file > table->count())
		throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
			"bad file number in .debug_line");

        // обращаемся по индексу dl_file-1 , т.к. в DWARF файлы нумеруются 
        // с единицы, а у нас в таблице с нуля.
	file_entry = (*dl_cu->dc_files)[dl_file - 1];

    return file_entry->fullname();
}

//-------------------------------------------------------------------
//
// выдает короткое имя файла для данной строки
//
//-------------------------------------------------------------------

Dwarf_Filename * Dwarf_Line::file() throw(Dwarf_Error)
{
    Dwarf_Filename  *file_entry;

	if (dl_cu == NULL)
		throw Dwarf_Error_Internal(Dwarf::DWARFERR,
			"null cu pointer in Dwarf_Line::srcfile");

	if (dl_file > table->count())
		throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
			"bad file number in .debug_line");

        // обращаемся по индексу dl_file-1 , т.к. в DWARF файлы нумеруются 
        // с единицы, а у нас в таблице с нуля.
	file_entry = (*dl_cu->dc_files)[dl_file - 1];

    return file_entry;
}


//-------------------------------------------------------------------
//
// end of functions of class Dwarf_Line
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// class Dwarf_Filename
//
//-------------------------------------------------------------------

//--------------------------------------------------------------
// выдает полное имя файла с индексом index.
// символьную строку надо уничтожить после использования.
//--------------------------------------------------------------

char * Dwarf_Filename::fullname()
    throw(Dwarf_Error)
{
    Dwarf_Filename  *file_entry;
    char            *include_directory;
    Dwarf_CU * cu = table->get_cu();

	if (cu == NULL)
		throw Dwarf_Error_Internal(Dwarf::DWARFERR,
			"null cu pointer in Dwarf_Filename::fullname");

        // обращаемся по индексу dl_file-1 , т.к. в DWARF файлы нумеруются 
        // с единицы, а у нас в таблице с нуля.
	file_entry = this;

	if (file_entry->name() == NULL)
		throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
			"no file name specified in .debug_line");

    if (Dwarf::has_full_path(file_entry->name())) {
	    char *name = new char [strlen(file_entry->name()) + 1];
    	strcpy(name,file_entry->name());
		return name;
    }

	if (file_entry->dir_index() == 0) {

		if (cu->comp_dir() == NULL)
			throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
				"no compilation directory for compilation-unit");

		return Dwarf::make_full_name((char *)(cu->comp_dir()),
			(char *)file_entry->name());
	}

	if (file_entry->dir_index() > cu->srcdirs()->count())
		throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
			"error in included directory for this line");

        // индекс 0 означает каталог в которой проходила компиляция
        // поэтому в DWARF индексы каталогов начинаются с 1.
        // у нас индексы в таблице начинаются с 0, поэтому вычитаем 1.
	include_directory = (*cu->srcdirs())[file_entry->dir_index() - 1]->name();

	if (Dwarf::has_full_path(include_directory))
		return Dwarf::make_full_name(include_directory,file_entry->name());
	else {
		if (cu->comp_dir() == NULL)
			throw Dwarf_Error_CU_Line(Dwarf::DWARFERR,
				"no compilation directory for compilation-unit");

		return Dwarf::make_full_name((char *)cu->comp_dir(),
					    		include_directory,file_entry->name());
    }
}

//-------------------------------------------------------------------
//
// end of functions of class Dwarf_Filename
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// class Dwarf_Global
//
//-------------------------------------------------------------------

Dwarf_Die *Dwarf_Global::get_die() const throw (Dwarf_Error)
{
	try {
		return table->dgt_debug->offcu(dg_info_offset)->off_cu_die(dg_cu_offset);
	}
	catch (Dwarf_No_Entry) {
		throw Dwarf_Error_Global(Dwarf::DWARFERR,
			"invalid offset to DIE in section .debug_global");
	}
}

//-------------------------------------------------------------------
//
// end of functions of class Dwarf_Global
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// class Dwarf_Arange
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// end of functions of class Dwarf_Arange
//
//-------------------------------------------------------------------

//===================================================================//
//===================================================================//
//                                                                   //
//                                                                   //
// Dwarf Producer Interface realisation                              //
//                                                                   //
//                                                                   //
//===================================================================//
//===================================================================//

//-------------------------------------------------------------------
// functions for class Dwarf
//-------------------------------------------------------------------

Dwarf_Unsigned Dwarf::decode_u_leb128 (Dwarf_Small *leb128, Dwarf_Unsigned& leb128_length)
{
	Dwarf_Small  	byte;
	Dwarf_Word		word_number;
	Dwarf_Unsigned number;
	Dwarf_Sword  	shift;
	Dwarf_Sword		byte_length;

	if ((*leb128 & 0x80) == 0) {
		leb128_length = 1;
		return(*leb128);
	}
	else if ((*(leb128 + 1) & 0x80) == 0) {
		leb128_length = 2;

		word_number = *leb128 & 0x7f;
		word_number |= (*(leb128 + 1) & 0x7f) << 7;
		return(word_number);
	}
	else if ((*(leb128 + 2) & 0x80) == 0) {
		leb128_length = 3;

		word_number = *leb128 & 0x7f;
		word_number |= (*(leb128 + 1) & 0x7f) << 7;
		word_number |= (*(leb128 + 2) & 0x7f) << 14;
		return(word_number);
	}
	else if ((*(leb128 + 3) & 0x80) == 0) {
		leb128_length = 4;

		word_number = *leb128 & 0x7f;
		word_number |= (*(leb128 + 1) & 0x7f) << 7;
		word_number |= (*(leb128 + 2) & 0x7f) << 14;
		word_number |= (*(leb128 + 3) & 0x7f) << 21;
		return(word_number);
	}

	number = 0;
	shift = 0;
	byte_length = 1;
	byte = *(leb128);
	while (True) {
		number |= (byte & 0x7f) << shift;
		shift += 7;

		if ((byte & 0x80) == 0) {
			 leb128_length = byte_length;
			 return(number);
		}

		byte_length++;
		byte = *(++leb128);
	}
}


//-------------------------------------------------------------------
//	 decode SLEB
//-------------------------------------------------------------------


Dwarf_Signed Dwarf::decode_s_leb128 (Dwarf_Small *leb128,Dwarf_Unsigned& leb128_length )
{
	Dwarf_Small    byte = *leb128;
	Dwarf_Sword		word_number = 0;
	Dwarf_Signed   number;
	Dwarf_Bool	  	sign = 0;
	Dwarf_Bool		ndone = True;
	Dwarf_Sword  	shift = 0;
	Dwarf_Sword		byte_length = 0;

	while (byte_length++ < 4) {
		sign = byte & 0x40;
		word_number |= (byte & 0x7f) << shift;
		shift += 7;

		if ((byte & 0x80) == 0) {
			 ndone = False;
			 break;
		}
		byte = *(++leb128);
	}

	number = word_number;
	while (ndone) {
		sign = byte & 0x40;
		number |= (byte & 0x7f) << shift;
		shift += 7;

		if ((byte & 0x80) == 0) {
			break;
		}

		 /*
		Increment after byte has been placed in
			  number on account of the increment already
			  done when the first loop terminates.  That
			  is the fourth byte is picked up and byte_length
			  updated in the first loop.  So increment not
			  needed in this loop if break is taken.
		 */
		byte_length++;
		byte = *(++leb128);
	}

	if ((shift < sizeof(Dwarf_Signed)*8) && sign)
		number |= - (1 << shift);

	leb128_length = byte_length;
	return(number);
}

//-------------------------------------------------------------------
// return 1 if string ends before 'endptr' else
// return 0 meaning string is not properly terminated.
// Presumption is the 'endptr' pts to end of some dwarf section data.
//-------------------------------------------------------------------

int Dwarf::string_valid(void *startptr, void *endptr)
{

	char *start = (char *)startptr;
	char *end = (char *)endptr;

	while(start < end) {
		if (*start == 0) {
			return 1; /* OK! */
		}
		++start;
		++end;
	}
	return 0; /* FAIL! bad string! */
}

//-------------------------------------------------------------
//	Кодирует val способом leb128. Кодирует как число без знака
//-------------------------------------------------------------

// В случае ошибки порождает исключение Dwarf_Error_Pro_Encode.
// место куда записывается число резервируется вызывающей программой
// длина буфера - параметр slen.
// число байтов в закодированном числе возвращается через параметр nbytes

void Dwarf::encode_leb128_nm(Dwarf_Unsigned val,int *nbytes,char *space,int splen)
		throw (Dwarf_Error)
{
	char *a;
	char *end = space + splen;

	a = space;
	do {
		unsigned char uc;
		if(a >= end)
			throw Dwarf_Error_Pro_Encode("buffer overflow in encoding leb128 number");

		uc = (unsigned char)((unsigned char)(val) & DATA_MASK);
		val >>= DIGIT_WIDTH;
		if (val != 0)
			uc |= MORE_BYTES;
		*a = uc;
		a++;
	}	while (val);
	*nbytes = a - space;
	return;
}

//-------------------------------------------------------------
//	Кодирует val способом leb128. Кодирует как число со знаком
//-------------------------------------------------------------

// В случае ошибки порождает исключение Dwarf_Error_Pro_Encode.
// место куда записывается число резервируется вызывающей программой
// длина буфера - параметр slen.
// число байтов в закодированном числе возвращается через параметр nbytes

void Dwarf::encode_signed_leb128_nm(Dwarf_Signed value, int *nbytes, char *space, int splen)
		throw (Dwarf_Error)
{
	char  *str;
	Dwarf_Signed sign = - (value < 0);
	int more = 1;
	char *end = space + splen;

	str = space;

	do {
		unsigned char byte = (unsigned char)((unsigned char)(value) & DATA_MASK);
		value >>= DIGIT_WIDTH;

		if(str >= end)
			throw Dwarf_Error_Pro_Encode("error encoding leb128 number");

		//
		// Remaining chunks would just contain the sign bit, and this chunk
		// has already captured at least one sign bit.

		if (value == sign && ((byte & SIGN_BIT) == (sign & SIGN_BIT)))
			more = 0;
		else
			byte |= MORE_BYTES;
		*str = byte;
		str++;
	 } while (more);
	*nbytes = str - space;
	return;
}

//------------------------------------------------------------
// Given address advance and line advance, it gives
// either special opcode, or a number < 0
//------------------------------------------------------------

Dwarf_Signed Dwarf::get_opc(Dwarf_Unsigned addr_adv,Dwarf_Signed line_adv)
{
	Dwarf_Signed opc ;

	addr_adv = addr_adv/MIN_INST_LENGTH;
	if (line_adv == 0 && addr_adv == 0)
		return OPC_INCS_ZERO;
	if (line_adv >= LINE_BASE && line_adv < LINE_BASE + LINE_RANGE) {
		opc = (line_adv - LINE_BASE) + (addr_adv*LINE_RANGE) + OPCODE_BASE;
		if (opc > 255) return OPC_OUT_OF_RANGE;
		return opc;
	}
	else
		return LINE_OUT_OF_RANGE;
}

//------------------------------------------------------------
//------------------------------------------------------------

Dwarf_Unsigned Dwarf::decode_leb128_uword(Dwarf_Small *&ptr) throw(Dwarf_Error)
{
	Dwarf_Small		byte;
	Dwarf_Unsigned	value;

	value = (byte = *(ptr++)) & 0x7f;
	if ((byte & 0x80) != 0) {
		 value |= ((byte = *(ptr++)) & 0x7f) << 7;
		 if ((byte & 0x80) != 0) {
			  value |= ((byte = *(ptr++)) & 0x7f) << 14;
			  if ((byte & 0x80) != 0) {
					value |= ((byte = *(ptr++)) & 0x7f) << 21;
					if ((byte & 0x80) != 0) {
    					value |= ((byte = *(ptr++)) & 0x0f) << 28;
                        if ((byte & 0x80) != 0) 
						    throw Dwarf_Error("Dwarf error - ",
                                                "leb128 too long");
						// value = UINT_MAX;
					}
			  }
		 }
	}
	return value;
}

//------------------------------------------------------------
//------------------------------------------------------------

Dwarf_Signed Dwarf::decode_leb128_sword(Dwarf_Small *&ptr) throw(Dwarf_Error)
{
	Dwarf_Small		byte;
	Dwarf_Signed	value;

	value = (byte = *(ptr++)) & 0x7f;
	if ((byte & 0x80) == 0) {
		 if ((byte & 0x40) != 0)
			  value |= 0xffffff80L;
	}
	else {
		 value |= ((byte = *(ptr++)) & 0x7f) << 7;
		 if ((byte & 0x80) == 0) {
			  if ((byte & 0x40) != 0)
					value |= 0xffffc000L;
		 }
		 else {
			  value |= ((byte = *(ptr++)) & 0x7f) << 14;
			  if ((byte & 0x80) == 0) {
					if ((byte & 0x40) != 0)
						 value |= 0xffe00000L;
			  }
			  else {
					value |= ((byte = *(ptr++)) & 0x7f) << 21;
					if ((byte & 0x80) == 0) {
						 if ((byte & 0x40) != 0)
							  value |= 0xf0000000L;
					}
					else
						throw(Dwarf_Error("Dwarf error - ","leb128 too long"));
						// value = INT_MAX;
			  }
		 }
	}
	return value;
}

//------------------------------------------------------------
//------------------------------------------------------------

void Dwarf::skip_leb128_word(Dwarf_Small *ptr) throw(Dwarf_Error)
{
	if ((*(ptr++) & 0x80) != 0) {
		if ((*(ptr++) & 0x80) != 0) {
			if ((*(ptr++) & 0x80) != 0) {
				if ((*(ptr++) & 0x80) != 0) {
					throw(Dwarf_Error("Dwarf error - ","leb128 too long"));
				}
			}
		}
	}
}
