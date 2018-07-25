//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Ѕазовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Ѕиблиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//                 –еализационный модуль dw_die.cpp                     //
//                                                                      //
//  ‘айл реализации функций класса Dwarf_Die                            //
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
// class Dwarf_Die
//
//-------------------------------------------------------------------

Dwarf_Die::Dwarf_Die(
    Dwarf_Unsigned& offset,
    Dwarf_Unsigned end_offset,
    Dwarf_CU *cu,
    Dwarf_Die *parent) 
        throw(Dwarf_Error) 

        : dd_die_offset(offset),
        dd_cu(cu),
		dd_abbrev(NULL),
        dd_child_list(NULL),
        dd_next_sibling(NULL),
		dd_parent(parent),
        dd_die_end_offset(end_offset),
        dd_attr_list(NULL)
{
	Dwarf_Debug	*debug = cu->dc_debug;
	Dwarf_Small	*die_info_ptr = debug->dd_debug_info + offset;
	Dwarf_Attribute *head_ptr = 0;
	Dwarf_Attribute *tail_ptr = 0;

	Dwarf_Word code = Dwarf::decode_leb128_uword(die_info_ptr);

	if (code == 0)
		throw Dwarf_Error_Internal(Dwarf::DWARFERR,
			"zero DIE code in constructor Dwarf_Die::Dwarf_Die");

	dd_abbrev = cu->dc_abbrev_table->find_at_code(code);

	try {
		for(Dwarf_Unsigned i = 0;i < dd_abbrev->attr_count();i++) {

			Dwarf_Abbrev_Attribute *abbrev_attr_ptr = 
                    dd_abbrev->get_abbrev_entry(i);


			Dwarf_Attribute *cur_ptr = 
                new Dwarf_Attribute(abbrev_attr_ptr,die_info_ptr,this);

			if (head_ptr == NULL) {
				head_ptr = cur_ptr;
				tail_ptr = cur_ptr;
				}
			else {
				tail_ptr->next = cur_ptr;
				tail_ptr = cur_ptr;
			}
		}
	}
	catch (Dwarf_Error) {
		if (head_ptr) delete head_ptr;
		throw;
	}
    dd_attr_list = head_ptr;
	offset = die_info_ptr - debug->dd_debug_info;
}

//-------------------------------------------------------------------

Dwarf_Die::~Dwarf_Die() throw(Dwarf_Error)
{
    if (dd_next_sibling) delete dd_next_sibling;
    if (dd_child_list) delete dd_child_list;
    if (dd_attr_list) delete dd_attr_list;
}

//-------------------------------------------------------------------
// internal private routine for loading subtree with parent of this die
//	as root
//-------------------------------------------------------------------

void Dwarf_Die::read_subtree(Dwarf_Off& offset,Dwarf_Bool is_root)
	throw(Dwarf_Error)
{
	Dwarf_Die *die_ptr = 0;
	USED(die_ptr);

	if (dd_child_list != NULL || dd_next_sibling != NULL)
		throw Dwarf_Error_Internal(Dwarf::DWARFERR,
			"not null references in Dwarf_Die::read_subtree");

	if (dd_abbrev->has_child()) {	// если есть дети, то читаем детей

		if (*(dd_cu->dc_debug->dd_debug_info+offset) != 0) {
                // если сын не нулевой
			die_ptr = new Dwarf_Die(offset,dd_die_end_offset,dd_cu,this);
			dd_child_list = die_ptr;
			die_ptr->read_subtree(offset,False);	// read all child subtree
		}
		else { 
                // если сын нулевой
            dd_child_list = NULL;
            offset += 1;            // пропускаем нулевой байт
        }
	}

	if (*(dd_cu->dc_debug->dd_debug_info+offset) != 0) {
            // если есть брат справа

		if (is_root)	// у DW_TAG_compile_unit не может быть братьев
			throw Dwarf_Error_Die(Dwarf::DWARFERR,
				"DW_TAG_compile_unit DIE can't have siblings");

			// читаем первого брата справа
		die_ptr = new Dwarf_Die(offset,dd_die_end_offset,dd_cu,dd_parent);

		dd_next_sibling = die_ptr;

            // читаем последующих братьев
		dd_next_sibling->read_subtree(offset,False);
	}
    else {
            // если нет братьев
        offset += 1;                // пропускаем нулевой байт
    }
}

//-------------------------------------------------------------------
// внутренн€€ функци€ ищет DIE по смещению в CU
//-------------------------------------------------------------------

Dwarf_Die *Dwarf_Die::findoff(Dwarf_Off offset) throw(Dwarf_Error,Dwarf_No_Entry)
{
	if (dd_die_offset == offset) return this;

	if (dd_next_sibling != NULL)
		if (offset >= dd_next_sibling->dd_die_offset)
			return dd_next_sibling->findoff(offset);

	if (dd_child_list != NULL) return dd_child_list->findoff(offset);

	throw Dwarf_No_Entry();
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return 0;
#endif
}

//-------------------------------------------------------------------

Dwarf_Die *Dwarf_Die::next() const
{
	if (dd_child_list) return dd_child_list;	// если есть сын вырнуть сына
	if (dd_next_sibling) return dd_next_sibling;// если есть брат вырнуть брата

	const Dwarf_Die *ptr = this;

	do {
		ptr = ptr->parent();
		if (ptr == NULL) return NULL;	// мы в корне дерева

	} while (ptr->sibling() == NULL);

	return ptr->sibling();
}

//-------------------------------------------------------------------

Dwarf_Half Dwarf_Die::tag() const throw(Dwarf_Error)
{
	if (dd_abbrev == NULL)
		throw Dwarf_Error_Internal(Dwarf::DWARFERR,"internal - null abbreviation in die");
	return dd_abbrev->tag();
}

//-------------------------------------------------------------------

Dwarf_Off Dwarf_Die::die_cu_offset() const throw(Dwarf_Error)
{
	if (dd_cu == NULL)
		throw(Dwarf_Error_Internal("Dwarf error - ",
			"internal - null cu context in die"));
	return (dd_die_offset - dd_cu->dc_debug_info_offset);
}

//-------------------------------------------------------------------

Dwarf_Bool Dwarf_Die::has_child() const throw(Dwarf_Error)
{
	if (dd_abbrev == NULL)
		throw Dwarf_Error_Internal(Dwarf::DWARFERR,"internal - null abbreviation in die");
	return dd_abbrev->has_child();
}


//-------------------------------------------------------------------

char *Dwarf_Die::name() throw(Dwarf_Error,Dwarf_No_Entry)
{
	Dwarf_Attribute *ptr = attr(DW_AT_name);
	if (ptr == NULL) throw Dwarf_No_Entry();

	return ptr->form_string();
}

//-------------------------------------------------------------------

Dwarf_Bool Dwarf_Die::hasattr(Dwarf_Half attr) throw()
{
	Dwarf_Attribute *ptr = dd_attr_list;

	while(ptr) {
		if (ptr->attr() == attr) return True;
		ptr = ptr->next;
	}
	return False;
}

//-------------------------------------------------------------------

Dwarf_Attribute *Dwarf_Die::attr(Dwarf_Half attr) throw(Dwarf_No_Entry)
{
	Dwarf_Attribute *ptr = dd_attr_list;

	while(ptr) {
		if (ptr->attr() == attr) return ptr;
		ptr = ptr->next;
	}
	throw Dwarf_No_Entry();
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return 0;
#endif
}

//-------------------------------------------------------------------

Dwarf_Attribute *Dwarf_Die::nextattr(Dwarf_Attribute *attr) throw(Dwarf_Error)
{
	if (attr == NULL) return dd_attr_list;
	if (attr->da_die != this)
		throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,"attribute is not owned by DIE");

	return attr->next;
}

//-------------------------------------------------------------------

Dwarf_Addr Dwarf_Die::lowpc() throw(Dwarf_Error,Dwarf_No_Entry)
{
	Dwarf_Attribute *ptr = attr(DW_AT_low_pc);
	if (ptr == NULL) throw Dwarf_No_Entry();
	if (ptr->form() != DW_FORM_addr)
		throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,"bad formed DIE");

	return ptr->form_addr();
}

//-------------------------------------------------------------------

Dwarf_Addr Dwarf_Die::highpc() throw(Dwarf_Error,Dwarf_No_Entry)
{
	Dwarf_Attribute *ptr = attr(DW_AT_high_pc);
	if (ptr == NULL) throw Dwarf_No_Entry();
	if (ptr->form() != DW_FORM_addr)
		throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,"bad formed DIE");

	return ptr->form_addr();
}

//-------------------------------------------------------------------

Dwarf_Unsigned	Dwarf_Die::bytesize() throw(Dwarf_Error,Dwarf_No_Entry)
{
	Dwarf_Attribute *ptr = attr(DW_AT_byte_size);
	if (ptr == NULL) throw Dwarf_No_Entry();

	return ptr->form_udata();
}

//-------------------------------------------------------------------

Dwarf_Unsigned	Dwarf_Die::bitsize() throw(Dwarf_Error,Dwarf_No_Entry)
{
	Dwarf_Attribute *ptr = attr(DW_AT_bit_size);
	if (ptr == NULL) throw Dwarf_No_Entry();

	return ptr->form_udata();
}

//-------------------------------------------------------------------

Dwarf_Unsigned	Dwarf_Die::bitoffset() throw(Dwarf_Error,Dwarf_No_Entry)
{
	Dwarf_Attribute *ptr = attr(DW_AT_bit_offset);
	if (ptr == NULL) throw Dwarf_No_Entry();

	return ptr->form_udata();
}

//-------------------------------------------------------------------

Dwarf_Unsigned	Dwarf_Die::srclang() throw(Dwarf_Error,Dwarf_No_Entry)
{
	Dwarf_Attribute *ptr = attr(DW_AT_language);
	if (ptr == NULL) throw Dwarf_No_Entry();

	return ptr->form_udata();
}

//-------------------------------------------------------------------

Dwarf_Unsigned	Dwarf_Die::arrayorder() throw(Dwarf_Error,Dwarf_No_Entry)
{
	Dwarf_Attribute *ptr = attr(DW_AT_ordering);
	if (ptr == NULL) throw Dwarf_No_Entry();

	return ptr->form_udata();
}
