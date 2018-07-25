//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//               Реализационный модуль pro_die.cpp                      //
//                                                                      //
//  Файл реализации функций класса Dwarf_P_Die                          //
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
// class Dwarf_P_Die
//
//-------------------------------------------------------------------

#include <string.h>

#include "libelf.h"
#include "dwarferr.h"
#include "dwarftyp.h"
#include "dwarf.h"
#include "libdwarf.h"
#include "dwarfint.h"

#include "pro_attr.h"
#include "pro_pubn.h"

Dwarf_P_Die::Dwarf_P_Die(Dwarf_P_CU *cu,Dwarf_P_Die *parent,Dwarf_Tag tag)
	throw() : dpd_offset(0),dpd_abbrev(NULL),dpd_abbrev_nbytes(0),dpd_tag(tag),
	dpd_parent(parent),dpd_child(NULL),dpd_right(NULL),dpd_attrs(NULL),
	dpd_last_attr(NULL),dpd_n_attr(0),dpd_cu(cu)
{
	DEBUG("make die\n")
}

Dwarf_P_Die::~Dwarf_P_Die() throw(Dwarf_Error)
{
	DEBUG("delete die\n")
	if (dpd_attrs != NULL) {
		Dwarf_P_Attribute *ptr;
		while(dpd_attrs != NULL) {
			ptr = dpd_attrs->next;
			delete dpd_attrs;
			dpd_attrs = ptr;
		}
	}
	if (dpd_child != NULL) delete dpd_child;
	if (dpd_right != NULL) delete dpd_right;

	if (dpd_abbrev != NULL) delete[] dpd_abbrev;
}

	// функции создания новых DIE

Dwarf_P_Die *Dwarf_P_Die::new_child(Dwarf_Tag new_tag) throw(Dwarf_Error)
{
	if (dpd_child == NULL)
		return (dpd_child = new Dwarf_P_Die(dpd_cu,this,new_tag));

	Dwarf_P_Die *ptr = dpd_child;

	while(ptr->dpd_right != NULL) ptr = ptr->dpd_right;

	return (ptr->dpd_right = new Dwarf_P_Die(dpd_cu,this,new_tag));
}

Dwarf_P_Die *Dwarf_P_Die::new_sibling(Dwarf_Tag new_tag) throw(Dwarf_Error)
{
	if (dpd_right == NULL)
		return (dpd_right = new Dwarf_P_Die(dpd_cu,dpd_parent,new_tag));

	Dwarf_P_Die *ptr = new Dwarf_P_Die(dpd_cu,dpd_parent,new_tag);

	ptr->dpd_right = dpd_right;
	dpd_right = ptr;
	return ptr;

//	while(ptr->dpd_right != NULL) ptr = ptr->dpd_right;

//	return (ptr->dpd_right = new Dwarf_P_Die(dpd_cu,dpd_parent,new_tag));
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

Dwarf_P_Die *Dwarf_P_Die::next() const
{
	if (dpd_child) return dpd_child;    // если есть сын вырнуть сына
	if (dpd_right) return dpd_right;    // если есть брат вырнуть брата

	const Dwarf_P_Die *ptr = this;

	do {
		ptr = ptr->parent();
		if (ptr == NULL) return NULL;	// мы в корне дерева

	} while (ptr->sibling() == NULL);

	return ptr->sibling();
}

// функции добавления атрибута к DIE
// вставляет в список упорядоченный по возрастанию кода атрибута

void Dwarf_P_Die::add_at_to_die(Dwarf_P_Attribute *attrib) throw(Dwarf_Error)
{
	Dwarf_P_Attribute *cur_attr;
	Dwarf_P_Attribute *prev_attr;

	if (dpd_attrs == NULL) {
		dpd_attrs = attrib;
		dpd_last_attr = attrib;
		dpd_n_attr = 1;
		return;
	}

	cur_attr = dpd_attrs;

	if (cur_attr->attr() == attrib->attr())
		throw Dwarf_Error_Pro_Attribute("Duplicate attribute in DIE");

	if (cur_attr->attr() > attrib->attr()) {
		// втавить первым элементом

		attrib->next = dpd_attrs;
		dpd_attrs = attrib;
      dpd_n_attr += 1;
		return;
	}

	prev_attr = cur_attr;
	cur_attr = cur_attr->next;

	while(cur_attr != NULL) {
		if (cur_attr->attr() == attrib->attr())
			throw Dwarf_Error_Pro_Attribute("Duplicate attribute in DIE");
		if (cur_attr->attr() > attrib->attr()) {
			// вставить перед текущим

			attrib->next = cur_attr;
			prev_attr->next = attrib;
			dpd_n_attr += 1;
			return;
		}
		prev_attr = cur_attr;
		cur_attr = cur_attr->next;
	}
	// вставить в конец списка

	prev_attr->next = attrib;
	attrib->next = NULL;
   dpd_n_attr += 1;
}

	// функции добавления различных атрибутов к DIE

void Dwarf_P_Die::add_AT_location_expr(Dwarf_Half attr,Dwarf_P_Expr *loc_expr)
	throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_Location(get_debug(),attr,loc_expr);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_name(char *name) throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_String(get_debug(),DW_AT_name,name);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_comp_dir(char *directory) throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_String(get_debug(),DW_AT_comp_dir,directory);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_producer(char *producer) throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_String(get_debug(),DW_AT_producer,producer);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_const_value_signedint(Dwarf_Signed signed_value)
	throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_Sdata(get_debug(),DW_AT_const_value,signed_value);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_const_value_unsignedint(Dwarf_Unsigned unsigned_value)
	throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_Udata(get_debug(),DW_AT_const_value,unsigned_value);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_const_value_string(char *string) throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_String(get_debug(),DW_AT_const_value,string);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_targ_address(Dwarf_Half attr, Dwarf_Unsigned pc_value,
				Dwarf_Signed sym_index) throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_Addr(get_debug(),attr,pc_value,sym_index);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_targ_address_delayed(Dwarf_Half attr,
	Dwarf_Unsigned addr_index) throw(Dwarf_Error)
{
    Dwarf_P_Attribute *new_attr;
    new_attr = new Dwarf_P_A_Addr_Delayed(get_debug(),attr,addr_index);
    add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_unsigned_const(Dwarf_Half attr,Dwarf_Unsigned value)
	throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_Udata(get_debug(),attr,value);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_signed_const(Dwarf_Half attr,Dwarf_Signed value)
	throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_Sdata(get_debug(),attr,value);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_reference(Dwarf_Half attr,Dwarf_P_Die *otherdie)
	throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_Ref(get_debug(),dpd_cu,attr,otherdie);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_reference_delayed(Dwarf_Half attr,
		Dwarf_Unsigned die_index) throw(Dwarf_Error)
{
    Dwarf_P_Attribute *new_attr;
    new_attr = new Dwarf_P_A_Ref_Delayed(get_debug(),dpd_cu,attr,die_index);
    add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_flag(Dwarf_Half attr,Dwarf_Small flag)
	throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_Flag(get_debug(),attr,flag);
	add_at_to_die(new_attr);

}

void Dwarf_P_Die::add_AT_string(Dwarf_Half attr,char *string) throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_String(get_debug(),attr,string);
	add_at_to_die(new_attr);
}

void Dwarf_P_Die::add_AT_macro_info(Dwarf_Unsigned offset) throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_Offset(get_debug(),DW_AT_macro_info,offset,0);
	add_at_to_die(new_attr);

}

void Dwarf_P_Die::add_AT_stmt_list() throw(Dwarf_Error)
{

	Dwarf_P_Attribute *new_attr;

	new_attr = new Dwarf_P_A_Offset(get_debug(),DW_AT_stmt_list,
		dpd_cu->dpc_line_offset,0);

	add_at_to_die(new_attr);

}

void Dwarf_P_Die::add_AT_block(Dwarf_Half attr,Dwarf_Block block)
	throw(Dwarf_Error)
{
	Dwarf_P_Attribute *new_attr;
	new_attr = new Dwarf_P_A_Block(get_debug(), attr, block);
	add_at_to_die(new_attr);
}


	// функции работы с глобальными именами

void Dwarf_P_Die::add_pubname(char *pubname_name) throw(Dwarf_Error)
{
   Dwarf_P_Pubname *pubname;
   char *name;

   name = new char[ strlen(pubname_name) + 1 ];
   strcpy(name, pubname_name);
   pubname = new Dwarf_P_Pubname(this,name);
#if _DWARF_DIAGNOSTIC
    DEBUG("make new pubname")
#endif  // _DWARF_DIAGNOSTIC

   if (dpd_cu->dpc_pubname == NULL) {
       dpd_cu->dpc_pubname = pubname;
       dpd_cu->dpc_last_pubname = pubname;
   }
   else {
       dpd_cu->dpc_last_pubname->next = pubname;
       dpd_cu->dpc_last_pubname = pubname;
   }
   dpd_cu->dpc_pubname_count++;
}
