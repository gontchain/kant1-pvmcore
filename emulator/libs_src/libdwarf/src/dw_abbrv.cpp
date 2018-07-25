//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//                 Реализационный модуль dw_abbrv.cpp                   //
//                                                                      //
//  Файл реализации функций классов Dwarf_Abbrev и Dwarf_Abbrev_Tab     //
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

//-------------------------------------------------------------------
//
// functions of class Dwarf_Abbrev
//
//-------------------------------------------------------------------

Dwarf_Abbrev::Dwarf_Abbrev(Dwarf_Off& offset,Dwarf_Debug *debug)
	throw(Dwarf_Error) :
	da_count(0),da_code(0),da_tag(0),da_has_child(DW_CHILDREN_no),table(NULL),
	da_attr_table(NULL),next(0)
{
	Dwarf_Small		*abbrev_ptr;
    Dwarf_Small     *abbrev_begin;
	Dwarf_Small		*abbrev_section_end;
	Dwarf_Half		attr;
	Dwarf_Half		attr_form;
	Dwarf_Unsigned	attr_count = 0;

   USED(attr_count);

	if (offset >= debug->dd_debug_abbrev_size)
		throw Dwarf_Error_Abbrev(Dwarf::DWARFERR,"internal error in decoding abbreviation");

	attr_count = 0;

	abbrev_ptr = debug->dd_debug_abbrev + offset;
	abbrev_section_end = debug->dd_debug_abbrev + debug->dd_debug_abbrev_size;

	da_code = Dwarf::decode_leb128_uword(abbrev_ptr);

	if (da_code == 0)
		 return;

	da_tag = Dwarf_Half(Dwarf::decode_leb128_uword(abbrev_ptr));
	da_has_child = *(abbrev_ptr++);

    abbrev_begin = abbrev_ptr;
	do {
		attr = Dwarf_Half(Dwarf::decode_leb128_uword(abbrev_ptr));
		attr_form = Dwarf_Half(Dwarf::decode_leb128_uword(abbrev_ptr));

		if ( attr != 0) (attr_count)++;

	} while (abbrev_ptr < abbrev_section_end && (attr != 0 || attr_form != 0));

	if (abbrev_ptr > abbrev_section_end)
		throw Dwarf_Error_Abbrev(Dwarf::DWARFERR,"error in decoding abbreviation");

	da_attr_table = new Dwarf_Abbrev_Attribute[attr_count];

	da_count = attr_count;
	offset = abbrev_ptr - debug->dd_debug_abbrev;

    abbrev_ptr = abbrev_begin;          // снова разбираем абревиатуру,
                                        // на этот раз занося в таблицу

	for(Dwarf_Unsigned i = 0;i < attr_count;i++) {
		da_attr_table[i].daa_num = Dwarf_Half(Dwarf::decode_leb128_uword(abbrev_ptr));
		da_attr_table[i].daa_form = Dwarf_Half(Dwarf::decode_leb128_uword(abbrev_ptr));
	}
}

//-------------------------------------------------------------------

Dwarf_Abbrev_Attribute *Dwarf_Abbrev::get_abbrev_entry(Dwarf_Unsigned index) 
    const throw(Dwarf_Error)
{
	if (index >= da_count)
		throw Dwarf_Error_Abbrev(Dwarf::DWARFERR,
			"invalid index in decoding abbreviation");
	return (da_attr_table+index);
}

//-------------------------------------------------------------------
//
// class Dwarf_Abbrev_Tab
//
//-------------------------------------------------------------------

Dwarf_Abbrev_Tab::Dwarf_Abbrev_Tab(Dwarf_Unsigned size) throw(Dwarf_Error) :
	dat_hash_size(size),dat_elem_count(0)
{
	table = new Dwarf_Abbrev *[size];
	for (Dwarf_Unsigned i= 0;i < dat_hash_size;i++)
   	table[i] = NULL;
}

Dwarf_Abbrev_Tab::~Dwarf_Abbrev_Tab() throw(Dwarf_Error)
{
	if (table) {
		for (Dwarf_Unsigned i = 0;i < dat_hash_size;i++) {
			Dwarf_Abbrev *ptr = table[i];
			Dwarf_Abbrev *ptr_delete;
			while(ptr != NULL) {
				ptr_delete = ptr;
				ptr = ptr->next;
				delete ptr_delete;
			}
		}
		delete[] table;
	}
}

void Dwarf_Abbrev_Tab::insert(Dwarf_Abbrev *elem) throw(Dwarf_Error)
{
	Dwarf_Word hash_num = elem->code() % dat_hash_size;

	Dwarf_Abbrev *ptr = table[hash_num];

	while(ptr != NULL) {
		if (ptr->code() == elem->code())
			throw Dwarf_Error_Internal(Dwarf::DWARFERR,
                                "duplicate abbreviations in table");
		ptr = ptr->next;
	}

	elem->next = table[hash_num];
	table[hash_num] = elem;
}

Dwarf_Abbrev *Dwarf_Abbrev_Tab::find_at_code(Dwarf_Unsigned code) 
    throw(Dwarf_Error)
{
	Dwarf_Word hash_num = code % dat_hash_size;

	Dwarf_Abbrev *ptr = table[hash_num];

	while(ptr != NULL) {
		if (ptr->code() == code)
			return ptr;
		ptr = ptr->next;
	}
	throw Dwarf_Error_Abbrev(Dwarf::DWARFERR,"no abbreviation for code in DIE found");
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return 0;
#endif
}
