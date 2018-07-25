//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//               Реализационный модуль pro_aran.cpp                     //
//                                                                      //
//  Файл реализации функций класса Dwarf_P_Attribute и производных      //
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

#include "pro_attr.h"

//-------------------------------------------------------------------//
// Dwarf_P_Attribute implementation
//-------------------------------------------------------------------//
Dwarf_P_Attribute::Dwarf_P_Attribute(Dwarf_P_Debug *dbg,Dwarf_Half attr,Dwarf_Half form)
	throw () : dpa_attribute(attr),dpa_attribute_form(form),
	dpa_data(NULL),dpa_nbytes(0),dpa_rel_symidx(SHN_UNDEF),
	dpa_rel_type(R_NC_NONE),dpa_rel_offset(0),next(NULL),dpa_dbg(dbg)
{
	DEBUG("make attr\n")
}

Dwarf_P_Attribute::~Dwarf_P_Attribute() throw(Dwarf_Error)
{
	DEBUG("delete attribute\n")
	if (dpa_data) delete[] dpa_data;
}

//-------------------------------------------------------------------//
// Dwarf_P_A_String implementation
//-------------------------------------------------------------------//

Dwarf_P_A_String::Dwarf_P_A_String(Dwarf_P_Debug *dbg,Dwarf_Half attr,char *string)
	throw (Dwarf_Error) : Dwarf_P_Attribute(dbg,attr,DW_FORM_string)
{
	dpa_data = new char[strlen(string) + 1];
	dpa_nbytes = strlen(string) + 1;
	strcpy(dpa_data,string);
}

char *Dwarf_P_A_String::get_data() 
{
	return dpa_data;
}

Dwarf_Unsigned Dwarf_P_A_String::get_len() 
{
	return dpa_nbytes;
}

//-------------------------------------------------------------------//
// Dwarf_P_A_Sdata implementation
//-------------------------------------------------------------------//
Dwarf_P_A_Sdata::Dwarf_P_A_Sdata(Dwarf_P_Debug *dbg,Dwarf_Half attr, Dwarf_Signed signed_value)
	throw (Dwarf_Error) : Dwarf_P_Attribute(dbg,attr,DW_FORM_sdata)
{
	int	leb_size;
	char 	encode_buffer[ENCODE_SPACE_NEEDED];

	Dwarf::encode_signed_leb128_nm(signed_value, &leb_size,
			encode_buffer,sizeof(encode_buffer));

	dpa_data = new char[leb_size];

	memcpy(dpa_data,encode_buffer,leb_size);
	dpa_nbytes = leb_size;

}

char *Dwarf_P_A_Sdata::get_data() 
{
	return dpa_data;
}

Dwarf_Unsigned Dwarf_P_A_Sdata::get_len() 
{
	return dpa_nbytes;
}

//-------------------------------------------------------------------//
// Dwarf_P_A_Udata implementation
//-------------------------------------------------------------------//

Dwarf_P_A_Udata::Dwarf_P_A_Udata(Dwarf_P_Debug *dbg,Dwarf_Half attr, Dwarf_Unsigned unsigned_value)
	throw (Dwarf_Error) : Dwarf_P_Attribute(dbg,attr,DW_FORM_udata)
{
    int	    leb_size;
    char    encode_buffer[ENCODE_SPACE_NEEDED];

	Dwarf::encode_leb128_nm(unsigned_value, &leb_size,
			encode_buffer,sizeof(encode_buffer));

	dpa_data = new char[leb_size];

	memcpy(dpa_data,encode_buffer,leb_size);
	dpa_nbytes = leb_size;

}

char *Dwarf_P_A_Udata::get_data() 
{
	return dpa_data;
}

Dwarf_Unsigned Dwarf_P_A_Udata::get_len() 
{
	return dpa_nbytes;
}

//-------------------------------------------------------------------//
// Dwarf_P_A_Flag implementation
//-------------------------------------------------------------------//

Dwarf_P_A_Flag::Dwarf_P_A_Flag(Dwarf_P_Debug *dbg,Dwarf_Half attr, Dwarf_Small flag)
	throw (Dwarf_Error) : Dwarf_P_Attribute(dbg,attr,DW_FORM_flag)
{
	switch (attr) {
		case DW_AT_is_optional :
		case DW_AT_artificial :
		case DW_AT_declaration :
		case DW_AT_external :
		case DW_AT_prototyped :
		case DW_AT_variable_parameter :
			break;

		default :
			throw Dwarf_Error_Pro_Attribute("this attribute can't have form flag");
	}

	dpa_data = new char[1];
	dpa_nbytes = 1;
	*dpa_data = char(flag);
}

char *Dwarf_P_A_Flag::get_data() 
{
	return dpa_data;
}

Dwarf_Unsigned Dwarf_P_A_Flag::get_len() 
{
	return dpa_nbytes;
}

//-------------------------------------------------------------------//
// Dwarf_P_A_Addr implementation
//-------------------------------------------------------------------//

Dwarf_P_A_Addr::Dwarf_P_A_Addr(
        Dwarf_P_Debug *dbg,
        Dwarf_Half attr, 
        Dwarf_Addr addr,
	    Dwarf_Signed sym_idx)
	throw (Dwarf_Error) : Dwarf_P_Attribute(dbg,attr,DW_FORM_addr)
{
	switch (attr) {
		case DW_AT_low_pc :
		case DW_AT_high_pc :
			break;

		default :
			throw Dwarf_Error_Pro_Attribute(
                "this attribute can't have form address");
	}

	dpa_nbytes = dpa_dbg->addr_size();
	dpa_data = new char[dpa_nbytes];
	dpa_rel_symidx = sym_idx;
	if (sym_idx != R_NC_NONE)
		dpa_rel_type = R_NC_ADDR;
	else
		dpa_rel_type = R_NC_NONE;

	dpa_dbg->write_4(&addr,dpa_data);
}

char *Dwarf_P_A_Addr::get_data() 
{
	return dpa_data;
}

Dwarf_Unsigned Dwarf_P_A_Addr::get_len() 
{
	return dpa_nbytes;
}

//-------------------------------------------------------------------//
// Dwarf_P_A_Addr_Delayed implementation
//-------------------------------------------------------------------//

Dwarf_P_A_Addr_Delayed::Dwarf_P_A_Addr_Delayed(
        Dwarf_P_Debug *dbg,
        Dwarf_Half attr, 
        Dwarf_Unsigned addr_index)
	throw (Dwarf_Error) : Dwarf_P_Attribute(dbg,attr,DW_FORM_addr)
{
	switch (attr) {
		case DW_AT_low_pc :
		case DW_AT_high_pc :
			break;

		default :
			throw Dwarf_Error_Pro_Attribute(
                "this attribute can't have form address");
	}

	dpa_nbytes = dpa_dbg->addr_size();
    dpa_addr_index = addr_index;

        // будут вычислены после
    dpa_data = NULL;
    dpa_rel_symidx = 0;
}

void Dwarf_P_A_Addr_Delayed::CalculateAddress() throw(Dwarf_Error)
{
    if ( dpa_dbg->dpd_func_addr == NULL )
        throw Dwarf_Error_Pro_Attribute_Delayed_Addr(
                    dpa_addr_index, 
                    "Can't calculate delayed address");

    Dwarf_Addr addr = 0;
    Dwarf_Signed symbol_index = 0;
    if ((*dpa_dbg->dpd_func_addr)(dpa_addr_index, &addr, &symbol_index))
        throw Dwarf_Error_Pro_Attribute_Delayed_Addr(
                    dpa_addr_index, 
                    "Can't calculate delayed address");

	dpa_data = new char[dpa_nbytes];
	dpa_rel_symidx = symbol_index;
	if (dpa_rel_symidx != R_NC_NONE)
		dpa_rel_type = R_NC_ADDR;
	else
		dpa_rel_type = R_NC_NONE;

	dpa_dbg->write_4(&addr,dpa_data);
}

char *Dwarf_P_A_Addr_Delayed::get_data() 
{
    if (dpa_data == NULL)
        CalculateAddress();

	return dpa_data;
}

Dwarf_Unsigned Dwarf_P_A_Addr_Delayed::get_len() 
{
    if (dpa_data == NULL)
        CalculateAddress();

	return dpa_nbytes;
}

//-------------------------------------------------------------------//
// Dwarf_P_A_Ref implementation
//-------------------------------------------------------------------//

Dwarf_P_A_Ref::Dwarf_P_A_Ref(
        Dwarf_P_Debug *dbg,
        Dwarf_P_CU *cu,
        Dwarf_Half attr,
        Dwarf_P_Die *ref)
	throw (Dwarf_Error) : Dwarf_P_Attribute(dbg,attr,DW_FORM_ref4)
{
	if (ref == NULL)
		throw Dwarf_Error_Pro_Attribute("null reference specified");

	if (ref->get_cu() != cu)
   	throw Dwarf_Error_Pro_Attribute("reference to DIE in different CU");

	switch (attr) {
		case DW_AT_specification :
		case DW_AT_discr :
		case DW_AT_common_reference :
		case DW_AT_import :
		case DW_AT_containing_type :
		case DW_AT_default_value:
		case DW_AT_abstract_origin :
		case DW_AT_friend :
		case DW_AT_priority :
		case DW_AT_type :
		case DW_AT_lower_bound :
		case DW_AT_upper_bound :
		case DW_AT_count :
		case DW_AT_sibling:
			break;

		default :
			throw Dwarf_Error_Pro_Attribute(
                "this attribute can't have form reference");
	}

	dpa_nbytes = 0;
	dpa_data = NULL;

	dpa_ref_die = ref;

	dpa_rel_type = R_NC_NONE;
}

char *Dwarf_P_A_Ref::get_data()
{
	if (dpa_ref_die == NULL)
		throw Dwarf_Error_Pro_Attribute("cannot calculate reference to DIE");

    CalculateValues();

	return dpa_data;
}

Dwarf_Unsigned Dwarf_P_A_Ref::get_len()
{
	if (dpa_ref_die == NULL)
		throw Dwarf_Error_Pro_Attribute(
                "cannot calculate null reference to DIE");

    CalculateValues();

	return dpa_nbytes;
}

Dwarf_Half Dwarf_P_A_Ref::form()
{ 
	if (dpa_ref_die == NULL)
		throw Dwarf_Error_Pro_Attribute(
                "cannot calculate null reference to DIE");

    CalculateValues();

	return dpa_attribute_form;
}


    // внутреняя функция вычисляет все внутрение переменные объекта
void Dwarf_P_A_Ref::CalculateValues() throw(Dwarf_Error)
{
	Dwarf_Off off = dpa_ref_die->dpd_offset;
	Dwarf_Half dh;
	Dwarf_Word dw;

    if ( dpa_data ) {
        delete[] dpa_data; 
        dpa_data = 0;
    }

	if (off != 0 && off <= UCHAR_MAX) {
		 dpa_attribute_form = DW_FORM_ref1;
		 dpa_data = new char[1];
		 *dpa_data = char(off);
		 dpa_nbytes = 1;
	}
	else if (off != 0 && off <= USHRT_MAX) {
		 dpa_attribute_form = DW_FORM_ref2;
		 dpa_data = new char[2];
		 dh = Dwarf_Half(off);
		 dpa_dbg->write_2(&dh,dpa_data);
		 dpa_nbytes = 2;
	}
	else {
		 dpa_attribute_form = DW_FORM_ref4;
		 dpa_data = new char[4];
		 dw = off;
		 dpa_dbg->write_4(&dw,dpa_data);
		 dpa_nbytes = 4;
	}
}

//------------------------------------------------------------------//
// Dwarf_P_A_Ref_Delayed implementation                             //
// реализует ссылку на другую DIE с отложенным вычислением          //
//------------------------------------------------------------------//

Dwarf_P_A_Ref_Delayed::Dwarf_P_A_Ref_Delayed(
        Dwarf_P_Debug *dbg,
        Dwarf_P_CU *cu,
        Dwarf_Half attr,
        Dwarf_Unsigned die_index)
	throw (Dwarf_Error) : Dwarf_P_Attribute(dbg,attr,DW_FORM_ref4)
{

	switch (attr) {
		case DW_AT_specification :
		case DW_AT_discr :
		case DW_AT_common_reference :
		case DW_AT_import :
		case DW_AT_containing_type :
		case DW_AT_default_value:
		case DW_AT_abstract_origin :
		case DW_AT_friend :
		case DW_AT_priority :
		case DW_AT_type :
		case DW_AT_lower_bound :
		case DW_AT_upper_bound :
		case DW_AT_count :
		case DW_AT_sibling:
			break;

		default :
			throw Dwarf_Error_Pro_Attribute(
                "this attribute can't have form reference");
	}

    dpa_die_index = die_index;
	dpa_nbytes = 0;
    dpa_data = NULL;
    dpa_ref_die = NULL;
    dpa_rel_type = R_NC_NONE;
    dpa_cu = cu;
}

void Dwarf_P_A_Ref_Delayed::CalculateReference() throw(Dwarf_Error)
{
    if ( dpa_dbg->dpd_func_ref == NULL )
        throw Dwarf_Error_Pro_Attribute_Delayed_Ref(
                    dpa_die_index,
                    "Can't calculate delayed reference" );

    Dwarf_P_Die * ref = NULL;
    if ( (*dpa_dbg->dpd_func_ref)(dpa_die_index, &ref) )
        throw Dwarf_Error_Pro_Attribute_Delayed_Ref(
                    dpa_die_index,
                    "Can't calculate delayed reference");

	if (ref == NULL)
		throw Dwarf_Error_Pro_Attribute("null reference specified");

	if (ref->get_cu() != dpa_cu)
       	throw Dwarf_Error_Pro_Attribute("reference to DIE in different CU");

    dpa_ref_die = ref;

    dpa_rel_type = R_NC_NONE;
}

    // внутреняя функция вычисляет все внутрение переменные объекта
void Dwarf_P_A_Ref_Delayed::CalculateValues() throw(Dwarf_Error)
{
	Dwarf_Off off = dpa_ref_die->dpd_offset;
	Dwarf_Word dw;

        // Так как мы можем не знать значения смещения в тот момент когда вычисляем
        // размер и форму, то используем всегда максимальную форму.
    dpa_attribute_form = DW_FORM_ref4;
    if ( dpa_data == 0 ) {
        dpa_data = new char[4];
    }
    dw = off;
    dpa_dbg->write_4(&dw,dpa_data);
    dpa_nbytes = 4;
}

char *Dwarf_P_A_Ref_Delayed::get_data()
{
        // Всегда перевычисляем значение этого атрибута, т.к. при сложных ссылках
        // необходима только последняя информация из dpa_ref_die.
        
	if (dpa_ref_die == NULL)
        CalculateReference();
    // else;

    CalculateValues();

    if ( *((Dwarf_Word*)dpa_data) == 0 ) {
        throw Dwarf_Error_Pro_Attribute_Delayed_Ref(
                    dpa_die_index,
                    "delayed reference get zero");
    }
	return dpa_data;
}

Dwarf_Unsigned Dwarf_P_A_Ref_Delayed::get_len()
{
	if (dpa_ref_die == NULL)
        CalculateReference();
    // else ;

    CalculateValues();

	return dpa_nbytes;
}

Dwarf_Half Dwarf_P_A_Ref_Delayed::form()
{ 
	if (dpa_ref_die == NULL)
        CalculateReference();
    // else;

    CalculateValues();

	return dpa_attribute_form;
}

//-------------------------------------------------------------------//
// Dwarf_P_A_Location implementation
//-------------------------------------------------------------------//

Dwarf_P_A_Location::Dwarf_P_A_Location(Dwarf_P_Debug *dbg,Dwarf_Half attr,
	Dwarf_P_Expr *loc_expr)	throw (Dwarf_Error) :
		Dwarf_P_Attribute(dbg,attr,DW_FORM_block)
{
	Dwarf_Half      attr_form;
	int             len_size;
	Dwarf_Unsigned	block_size;
	char            *block_dest_ptr;

//	char encode_buffer[ENCODE_SPACE_NEEDED];
//	char                *len_str;

	if (loc_expr == NULL)
		throw Dwarf_Error_Pro_Attribute("null expression in attribute");

	if (loc_expr->get_debug() != dbg)
		throw Dwarf_Error_Pro_Attribute(
			"location expression belong to other Dwarf_P_Debug");

	block_size = loc_expr->get_length();

	switch (attr) {
		case DW_AT_location :
		case DW_AT_string_length :
		case DW_AT_const_value :
		case DW_AT_use_location :
		case DW_AT_return_addr :
		case DW_AT_data_member_location :
		case DW_AT_frame_base :
		case DW_AT_static_link :
		case DW_AT_vtable_elem_location :
			break;

		default :
			throw Dwarf_Error_Pro_Attribute(
				"this attribute can't have form location expression");
	}

		// Compute the number of bytes
		//	needed to hold constant.

	if (block_size <= UCHAR_MAX) {
		 attr_form = DW_FORM_block1;
		 len_size = 1;
	}
	else if (block_size <= USHRT_MAX) {
		 attr_form = DW_FORM_block2;
		 len_size = 2;
	}
	else {
		 attr_form = DW_FORM_block4;
		 len_size = 4;
	}
/*	 не нужно, т.к. обязательно влезет в 4 байта
	else {
		 attr_form = DW_FORM_block;
		 res = _dwarf_pro_encode_leb128_nm(block_size, &len_size,
					encode_buffer,sizeof(encode_buffer));
		 if (res !=  DW_DLV_OK) {
			  _dwarf_p_error(dbg, error, DW_DLE_ALLOC_FAIL);
			  return((Dwarf_P_Attribute)DW_DLV_BADADDR);
		 }
		 len_str = (char *)encode_buffer;
	}
*/
	dpa_attribute_form = attr_form;
	dpa_nbytes = len_size + block_size;
	dpa_data = new char[dpa_nbytes];

	if (loc_expr->dpe_reloc_sym_index != SHN_UNDEF)
		dpa_rel_type = R_NC_ADDR;
	else
		dpa_rel_type = R_NC_NONE;

	dpa_rel_symidx = loc_expr->dpe_reloc_sym_index;
	dpa_rel_offset = loc_expr->dpe_reloc_offset + len_size;

	block_dest_ptr = dpa_data;

	if (len_size == 1) {
		*block_dest_ptr = char(block_size);
		block_dest_ptr += 1;
	} else if (len_size == 2) {
		Dwarf_Half len = Dwarf_Half(block_size);
		dpa_dbg->write_2(&len,block_dest_ptr);
		block_dest_ptr += 2 ;
	} else { // if (len_size == 4)
		dbg->write_4(&block_size,block_dest_ptr);
		block_dest_ptr += 4 ;
	}
	memcpy(block_dest_ptr, &(loc_expr->dpe_byte_stream[0]), block_size);
}

char *Dwarf_P_A_Location::get_data() 
{
	return dpa_data;
}

Dwarf_Unsigned Dwarf_P_A_Location::get_len() 
{
	return dpa_nbytes;
}


//-------------------------------------------------------------------//
// Dwarf_P_A_Offset implementation
//-------------------------------------------------------------------//

Dwarf_P_A_Offset::Dwarf_P_A_Offset(Dwarf_P_Debug *dbg,Dwarf_Half attr,
	Dwarf_Off offset,Dwarf_Signed sym_idx) throw (Dwarf_Error) :
		Dwarf_P_Attribute(dbg,attr,DW_FORM_data4)
{
	dpa_rel_type = R_NC_BYTEPTR;
	dpa_rel_symidx = sym_idx;

	dpa_nbytes = dpa_dbg->off_size();
	dpa_data = new char[dpa_nbytes];
	dpa_dbg->write_4(&offset,dpa_data);
}

char *Dwarf_P_A_Offset::get_data()
{
	return dpa_data;
}

Dwarf_Unsigned Dwarf_P_A_Offset::get_len()
{
	return dpa_nbytes;
}



//------------------------------------------------------------------//
// Dwarf_P_A_Block реализация                                       //
//------------------------------------------------------------------//

Dwarf_P_A_Block::Dwarf_P_A_Block(Dwarf_P_Debug *dbg,Dwarf_Half attr, Dwarf_Block block)
	throw (Dwarf_Error) : Dwarf_P_Attribute(dbg,attr,DW_FORM_block)
{
    Dwarf_Half      attr_form;
    int             len_size;
    Dwarf_Unsigned	block_size;
    char            *block_dest_ptr;

    block_size = block.db_len;
        // Вычисляю число байт необходимых 
        // для хранения данных блока

	if (block_size <= UCHAR_MAX) {
		 attr_form = DW_FORM_block1;
		 len_size = 1;
	}
	else if (block_size <= USHRT_MAX) {
		 attr_form = DW_FORM_block2;
		 len_size = 2;
	}
	else {
		 attr_form = DW_FORM_block4;
		 len_size = 4;
	}
/*	не нужно, т.к. обязательно влезет в 4 байта
    если будет 8 байтовый Dwarf_Unsigned, то понадобится

    else {
        attr_form = DW_FORM_block;
    	Dwarf::encode_leb128_nm(block_size, &len_size,
            encode_buffer,sizeof(encode_buffer));
        len_str = (char *)encode_buffer;
    }
*/
	dpa_attribute_form = attr_form;
	dpa_nbytes = len_size + block_size;
	dpa_data = new char[dpa_nbytes];

	block_dest_ptr = dpa_data;

	if (len_size == 1) {
		*block_dest_ptr = char(block_size);
		block_dest_ptr += 1;
	} else if (len_size == 2) {
		Dwarf_Half len = Dwarf_Half(block_size);
		dpa_dbg->write_2(&len,block_dest_ptr);
		block_dest_ptr += 2 ;
	} else if (len_size == 4 ) {
		dbg->write_4(&block_size,block_dest_ptr);
		block_dest_ptr += 4 ;
	}
//   пока отключено
//    else {
//    	memcpy(dpa_data,encode_buffer,leb_size);
//        block_dest_ptr += len_size;
//    }

	memcpy(block_dest_ptr, block.db_data, block_size);
}

char *Dwarf_P_A_Block::get_data() 
{
	return dpa_data;
}

Dwarf_Unsigned Dwarf_P_A_Block::get_len() 
{
	return dpa_nbytes;
}



/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//              Конец реализационного модуля pro_attr.cpp                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
