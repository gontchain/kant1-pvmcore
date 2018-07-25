//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//                 Реализационный модуль dw_attr.cpp                    //
//                                                                      //
//  Файл реализации функций класса Dwarf_Attribute                      //
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
// class Dwarf_Attribute
//
//-------------------------------------------------------------------
Dwarf_Attribute::Dwarf_Attribute(Dwarf_Abbrev_Attribute *abbrev_ptr,
	Dwarf_Small *& info_ptr,Dwarf_Die *die) throw(Dwarf_Error) : da_abbrev(abbrev_ptr),
		da_length(0),da_data(info_ptr),da_die(die),next(NULL)
{
	da_length = get_size(die->dd_cu->dc_debug,da_abbrev->form(),da_data);
    info_ptr += da_length;
}

//-------------------------------------------------------------------
//	Given a form, and a pointer to the bytes encoding
//	a value of that form, val_ptr, this function returns
//	the length, in bytes, of a value of that form.
// When using this function, check for a return of 0
// a recursive DW_FORM_INDIRECT value.
//-------------------------------------------------------------------

Dwarf_Unsigned Dwarf_Attribute::get_size(Dwarf_Debug *dbg,Dwarf_Unsigned form,Dwarf_Small *val_ptr)
{
	Dwarf_Unsigned      length;
	Dwarf_Word          leb128_length;
	Dwarf_Unsigned      form_indirect;
	Dwarf_Unsigned      ret_value;

	switch (form) {

		default :                       /* Handles form = 0. */
			return(form);

		case DW_FORM_addr:
		case DW_FORM_ref_addr:
			return(dbg->dd_lsize);

		case DW_FORM_block1:
			return(*(Dwarf_Small *)val_ptr + 1);

		case DW_FORM_block2:
			Dwarf_Half half_ret;
			dbg->read_2(&half_ret, val_ptr);
         ret_value = half_ret;
			return(ret_value + sizeof(Dwarf_Half));

		case DW_FORM_block4:
			dbg->read(&ret_value, val_ptr);
			return(ret_value + sizeof(Dwarf_Word));


		case DW_FORM_data1:
			return(1);

		case DW_FORM_data2:
			return(2);

		case DW_FORM_data4:
			return(4);

		case DW_FORM_data8:
			throw Dwarf_Error_Internal(Dwarf::DWARFERR,
				"operations with 64 bits integers not yet realised");
//			return(8);

		case DW_FORM_string:
			return(strlen((char *)val_ptr) + 1);

		case DW_FORM_block:
			length = Dwarf::decode_u_leb128(val_ptr,leb128_length);
			return(length + leb128_length);

		case DW_FORM_flag:
			return(1);

		case DW_FORM_indirect:
			form_indirect = Dwarf::decode_u_leb128(val_ptr,leb128_length);
			if (form_indirect == DW_FORM_indirect)
				throw Dwarf_Error_Internal(Dwarf::DWARFERR,
					"Recursive indirect form attribute not supported");
			return(leb128_length + get_size(dbg, form_indirect,
				val_ptr+leb128_length));

		case DW_FORM_ref1:
			return(1);

		case DW_FORM_ref2:
			return(2);

		case DW_FORM_ref4:
			return(4);

		case DW_FORM_ref8:
			throw Dwarf_Error_Internal(Dwarf::DWARFERR,
				"operations with 64 bits integers not yet realised");
//			return(8);

		case DW_FORM_sdata:
			Dwarf::decode_s_leb128(val_ptr,leb128_length);
			return(leb128_length);

		case DW_FORM_strp:
			return(dbg->dd_lsize);

		case DW_FORM_udata:
			Dwarf::decode_u_leb128(val_ptr,leb128_length);
			return(leb128_length);
	 }
}

//-------------------------------------------------------------------

Dwarf_Half Dwarf_Attribute::attr() const
{
	return da_abbrev->attr_num();
}

//-------------------------------------------------------------------

Dwarf_Bool Dwarf_Attribute::hasform(Dwarf_Half form) const
{
	return Dwarf_Bool(da_abbrev->form() == form);
}

//-------------------------------------------------------------------

Dwarf_Half Dwarf_Attribute::form() const
{
	return da_abbrev->form();
}

//-------------------------------------------------------------------

Dwarf_CU *Dwarf_Attribute::check() throw(Dwarf_Error)
{
	Dwarf_CU			*cu_context;
	Dwarf_Debug    *dbg;

	if (da_die == NULL)
		throw Dwarf_Error_Internal(Dwarf::DWARFERR,
			"null die pointer in function Dwarf_Attribute::form_block");

	cu_context = da_die->dd_cu;

	if (cu_context == NULL)
		throw Dwarf_Error_Internal(Dwarf::DWARFERR,
			"null CU pointer in function Dwarf_Attribute::form_block");

	dbg = cu_context->dc_debug;

	if (dbg == NULL)
		throw Dwarf_Error_Internal(Dwarf::DWARFERR,
			"null debug pointer in function Dwarf_Attribute::form_block");

	return cu_context;
}

//-------------------------------------------------------------------

Dwarf_Off Dwarf_Attribute::form_ref_off() throw(Dwarf_Error)
{
	Dwarf_CU 	*cu_context = check();
	Dwarf_Debug *dbg = cu_context->dc_debug;

	Dwarf_Off offset;
	Dwarf_Unsigned length;

	switch (form()) {

		case DW_FORM_ref1 :
			offset = *(Dwarf_Small *)da_data;
			break;

		case DW_FORM_ref2 :
			Dwarf_Half half_o;
			dbg->read_2(&half_o,da_data);
         offset = half_o;
			break;

		case DW_FORM_ref4 :
			dbg->read(&offset,da_data);
			break;

		case DW_FORM_ref8 :
			throw Dwarf_Error_Internal(Dwarf::DWARFERR,"64 bits references not yet realised");
//			dbg->read_8(&offset,da_data);
//			break;

		case DW_FORM_ref_udata :

			offset = Dwarf::decode_u_leb128(da_data,length);
			break;

		default :
			throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
				"attribute form don't indicate reference");
	}

		 // Check that offset is within current cu portion of .debug_info.
	if (offset >= cu_context->dc_length + dbg->dd_lsize)
		throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
			"offset reference attribute outside current CU");

	return (offset);
}

//-------------------------------------------------------------------

Dwarf_Die *Dwarf_Attribute::form_ref() throw(Dwarf_Error)
{
	Dwarf_CU 	*cu_context = check();
	Dwarf_Debug *dbg = cu_context->dc_debug;

	Dwarf_Off offset = form_ref_off();
	return dbg->offdie(offset + cu_context->dc_debug_info_offset);
}


//-------------------------------------------------------------------

Dwarf_Addr Dwarf_Attribute::form_addr() throw(Dwarf_Error)
{
	Dwarf_CU 	*cu_context = check();
	Dwarf_Debug *dbg = cu_context->dc_debug;

	Dwarf_Addr	ret_addr;

	if (form() == DW_FORM_addr || form() == DW_FORM_ref_addr) {
		dbg->read(&ret_addr,da_data);
		 return ret_addr;
	}

	throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
		"attribute form don't indicate address");
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return (~Dwarf_Word(0));
#endif
}

//-------------------------------------------------------------------

Dwarf_Bool Dwarf_Attribute::form_flag() throw(Dwarf_Error)
{
	(void)check();

	if (form() == DW_FORM_flag)
		 return Dwarf_Bool((*da_data) != 0);

	throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
		"attribute form don't indicate flag");
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return False;
#endif
}

//-------------------------------------------------------------------

Dwarf_Unsigned Dwarf_Attribute::form_udata() throw(Dwarf_Error)
{
	Dwarf_Unsigned	ret_value;
	Dwarf_CU			*cu_context;
	Dwarf_Debug    *dbg;
	Dwarf_Unsigned	length;

	cu_context = check();
	dbg = cu_context->dc_debug;

	switch (form()) {

		case DW_FORM_data1 :
			return Dwarf_Unsigned((*da_data));

		case DW_FORM_data2 : {
			Dwarf_Half half_ret;
			dbg->read_2(&half_ret, da_data);
         ret_value = half_ret;
			return ret_value;
		}

		case DW_FORM_data4 : {
			dbg->read(&ret_value, da_data);
			return ret_value;
		}

		case DW_FORM_data8 : {
			throw Dwarf_Error_Internal(Dwarf::DWARFERR,"64 bits constants not yet realised");
//			dbg->read_8(&ret_value, da_data);
//			return ret_value;
		}
		case DW_FORM_udata :
			return Dwarf::decode_u_leb128(da_data,length);

		default :
			break;
	}
	throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
		"attribute form don't indicate unsigned data");
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return Dwarf_Unsigned(-1);
#endif
}

//-------------------------------------------------------------------

Dwarf_Signed Dwarf_Attribute::form_sdata() throw(Dwarf_Error)
{
	Dwarf_Signed	ret_value;
	Dwarf_CU			*cu_context;
	Dwarf_Debug    *dbg;
	Dwarf_Unsigned	length;

	cu_context = check();
	dbg = cu_context->dc_debug;

	switch (form()) {

		case DW_FORM_data1 :
			return Dwarf_Signed((*(Dwarf_Sbyte *)da_data));

		case DW_FORM_data2 : {
			Dwarf_Half ret_half;
			dbg->read_2(&ret_half, da_data);
			return Dwarf_Shalf(ret_half);
		}

		case DW_FORM_data4 : {
			dbg->read((Dwarf_Unsigned *)&ret_value, da_data);
			return ret_value;
		}

		case DW_FORM_data8 : {
			throw Dwarf_Error_Internal(Dwarf::DWARFERR,"64 bits constants not yet realised");
//			dbg->read_8(&ret_value, da_data);
//			return ret_value;
		}
		case DW_FORM_sdata :
			return Dwarf::decode_s_leb128(da_data,length);

		default :
			break;
	}
	throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
		"attribute form don't indicate signed data");
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return Dwarf_Signed(-1);
#endif
}

//-------------------------------------------------------------------
// form block from value of attribute
//-------------------------------------------------------------------

Dwarf_Block	*Dwarf_Attribute::form_block() throw(Dwarf_Error)
{
	Dwarf_CU			*cu_context;
	Dwarf_Debug    *dbg;
	Dwarf_Unsigned	length;
	Dwarf_Small		*data = NULL;
//	Dwarf_Word		leb128_length;
	Dwarf_Block		*ret_block;

	cu_context = check();
	dbg = cu_context->dc_debug;

	switch (form()) {

		case DW_FORM_block1 :
			length = *(Dwarf_Small *)da_data;
			data = da_data + sizeof(Dwarf_Small);
			break;

		case DW_FORM_block2 :
			Dwarf_Half half_len;
			dbg->read_2(&half_len,da_data);
         length = half_len;
			data = da_data + sizeof(Dwarf_Half);
			break;

		case DW_FORM_block4 :
			dbg->read(&length,da_data);
			data = da_data + sizeof(Dwarf_Word);
			break;

		case DW_FORM_block :
			throw Dwarf_Error_Internal(Dwarf::DWARFERR,"64 bits blocks not yet realised");
//			length = Dwarf::decode_u_leb128(da_data,leb128_length);
//			data = da_data + leb128_length;
//			break;

		default :
			throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
				"attribute form don't indicate block");
//			break;
	}

		// Check that block lies within current cu in .debug_info.
	if (da_data + length >= dbg->dd_debug_info + cu_context->dc_debug_info_offset
		+ cu_context->dc_length + dbg->dd_lsize)
			throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
				"size of block in attribute value bad");

	ret_block = new Dwarf_Block;

	ret_block->db_len = length;
	ret_block->db_data = (Dwarf_Ptr)data;

	return ret_block;
}

//-------------------------------------------------------------------
// form string from value af attribute
//-------------------------------------------------------------------

char *Dwarf_Attribute::form_string() throw(Dwarf_Error)
{
	Dwarf_CU *cu_context = check();
	Dwarf_Debug *dbg = cu_context->dc_debug;
	Dwarf_Unsigned offset;

	if (form() == DW_FORM_string) {

		Dwarf_Small *begin = da_data;
		Dwarf_Small *end = dbg->dd_debug_info + cu_context->dc_debug_info_offset +
			cu_context->dc_length + dbg->dd_lsize;

		// Check that string lies within current cu in .debug_info.

		if (0==Dwarf::string_valid(begin,end))
			throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,"size of block in attribute value bad");

		return (char *)(begin);
	}

	if (form() == DW_FORM_strp) {
		dbg->read(&offset,da_data);

		if (dbg->dd_debug_str == NULL)
			throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,"no data in .debug_str section");

		if (offset > dbg->dd_debug_str_size)
			throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,"offset into .debug_str past its end");


		return (char *)(dbg->dd_debug_str + offset);
	}

	throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,"attribute form don't indicate on string");
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return 0;
#endif
}

//-------------------------------------------------------------------
//
// internal function for parsing location expression
//
//-------------------------------------------------------------------

Dwarf_Locdesc *Dwarf_Attribute::get_locdesc(Dwarf_Small *ptr,Dwarf_Unsigned len,
	Dwarf_Debug *dbg) throw(Dwarf_Error)
{
		// Size of the block containing
		// the location expression.

	Dwarf_Unsigned      loc_len;

		// Sweeps the block containing
		// the location expression.

	Dwarf_Small         *loc_ptr;

		// Current location operator.
	Dwarf_Small         atom;

		// Offset of current operator from start of block.
	Dwarf_Unsigned      offset;

		// Operands of current location operator.
	Dwarf_Unsigned      operand1, operand2;

		// Used to chain the Dwarf_Loc objects.
	Dwarf_Loc	*curr_loc;
	Dwarf_Loc	*prev_loc = NULL;
	Dwarf_Loc	*head_loc = NULL;

		// Count of the number of location operators.
	Dwarf_Unsigned      op_count;

		// Dwarf_Locdesc pointer to be returned.
	Dwarf_Locdesc       *locdesc;

	Dwarf_Word          leb128_length;
//	Dwarf_Unsigned      i;

		// ----- BEGIN CODE -----

	loc_len = len;
	loc_ptr = ptr;

	offset = 0; op_count = 0;
	while (offset < loc_len) {

		operand1 = 0;
		operand2 = 0;
		op_count++;
		atom = *(Dwarf_Small *)loc_ptr;
		loc_ptr ++;
		offset++;

		curr_loc = new Dwarf_Loc(atom,0,0,offset);

		switch (atom) {

			case DW_OP_reg0 :
			case DW_OP_reg1 :
			case DW_OP_reg2 :
			case DW_OP_reg3 :
			case DW_OP_reg4 :
			case DW_OP_reg5 :
			case DW_OP_reg6 :
			case DW_OP_reg7 :
			case DW_OP_reg8 :
			case DW_OP_reg9 :
			case DW_OP_reg10 :
			case DW_OP_reg11 :
			case DW_OP_reg12 :
			case DW_OP_reg13 :
			case DW_OP_reg14 :
			case DW_OP_reg15 :
			case DW_OP_reg16 :
			case DW_OP_reg17 :
			case DW_OP_reg18 :
			case DW_OP_reg19 :
			case DW_OP_reg20 :
			case DW_OP_reg21 :
			case DW_OP_reg22 :
			case DW_OP_reg23 :
			case DW_OP_reg24 :
			case DW_OP_reg25 :
			case DW_OP_reg26 :
			case DW_OP_reg27 :
			case DW_OP_reg28 :
			case DW_OP_reg29 :
			case DW_OP_reg30 :
			case DW_OP_reg31 :
									 break;
			case DW_OP_regx :
				operand1 = Dwarf::decode_u_leb128(loc_ptr,leb128_length);
				loc_ptr = loc_ptr + leb128_length;
				offset = offset + leb128_length;
				break;

			case DW_OP_lit0 :
			case DW_OP_lit1 :
			case DW_OP_lit2 :
			case DW_OP_lit3 :
			case DW_OP_lit4 :
			case DW_OP_lit5 :
			case DW_OP_lit6 :
			case DW_OP_lit7 :
			case DW_OP_lit8 :
			case DW_OP_lit9 :
			case DW_OP_lit10 :
			case DW_OP_lit11 :
			case DW_OP_lit12 :
			case DW_OP_lit13 :
			case DW_OP_lit14 :
			case DW_OP_lit15 :
			case DW_OP_lit16 :
			case DW_OP_lit17 :
			case DW_OP_lit18 :
			case DW_OP_lit19 :
			case DW_OP_lit20 :
			case DW_OP_lit21 :
			case DW_OP_lit22 :
			case DW_OP_lit23 :
			case DW_OP_lit24 :
			case DW_OP_lit25 :
			case DW_OP_lit26 :
			case DW_OP_lit27 :
			case DW_OP_lit28 :
			case DW_OP_lit29 :
			case DW_OP_lit30 :
			case DW_OP_lit31 :
				operand1 = atom - DW_OP_lit0;
				break;

			case DW_OP_addr :
				dbg->read(&operand1,loc_ptr);
				loc_ptr += dbg->dd_lsize;
				offset += dbg->dd_lsize;
				break;

			case DW_OP_const1u :
				operand1 = *(Dwarf_Small *)loc_ptr;
				loc_ptr = loc_ptr + 1;
				offset = offset + 1;
				break;

			case DW_OP_const1s :
				operand1 = *(Dwarf_Sbyte *)loc_ptr;
				loc_ptr = loc_ptr + 1;
				offset = offset + 1;
				break;

			case DW_OP_const2u :
				Dwarf_Half half_op1;
				dbg->read_2(&half_op1,loc_ptr);
            operand1 = half_op1;
				loc_ptr = loc_ptr + 2;
				offset = offset + 2;
				break;

			case DW_OP_const2s :
				dbg->read(&operand1,loc_ptr);
				loc_ptr = loc_ptr + 2;
				offset = offset + 2;
				break;

			case DW_OP_const4u :
				dbg->read(&operand1,loc_ptr);
				loc_ptr = loc_ptr + 4;
				offset = offset + 4;
				break;

			case DW_OP_const4s :
				dbg->read(&operand1,loc_ptr);
				loc_ptr = loc_ptr + 4;
				offset = offset + 4;
				break;

			case DW_OP_const8u :
				throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
					"64 bits constants in location expression yet not supported");
//				operand1 = dbg->read(loc_ptr);
//				loc_ptr = loc_ptr + 8;
//				offset = offset + 8;
//				break;

			case DW_OP_const8s :
				throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
					"64 bits constants in location expression yet not supported");
//				operand1 = dbg->read(loc_ptr);
//				loc_ptr = loc_ptr + 8;
//				offset = offset + 8;
//				break;

			case DW_OP_constu :
				operand1 = Dwarf::decode_u_leb128(loc_ptr,leb128_length);
				loc_ptr = loc_ptr + leb128_length;
				offset = offset + leb128_length;
				break;

			case DW_OP_consts :
				operand1 = Dwarf::decode_s_leb128(loc_ptr,leb128_length);
				loc_ptr = loc_ptr + leb128_length;
				offset = offset + leb128_length;
				break;

			case DW_OP_fbreg :
				operand1 = Dwarf::decode_s_leb128(loc_ptr,leb128_length);
				loc_ptr = loc_ptr + leb128_length;
				offset = offset + leb128_length;
				break;

			case DW_OP_breg0 :
			case DW_OP_breg1 :
			case DW_OP_breg2 :
			case DW_OP_breg3 :
			case DW_OP_breg4 :
			case DW_OP_breg5 :
			case DW_OP_breg6 :
			case DW_OP_breg7 :
			case DW_OP_breg8 :
			case DW_OP_breg9 :
			case DW_OP_breg10 :
			case DW_OP_breg11 :
			case DW_OP_breg12 :
			case DW_OP_breg13 :
			case DW_OP_breg14 :
			case DW_OP_breg15 :
			case DW_OP_breg16 :
			case DW_OP_breg17 :
			case DW_OP_breg18 :
			case DW_OP_breg19 :
			case DW_OP_breg20 :
			case DW_OP_breg21 :
			case DW_OP_breg22 :
			case DW_OP_breg23 :
			case DW_OP_breg24 :
			case DW_OP_breg25 :
			case DW_OP_breg26 :
			case DW_OP_breg27 :
			case DW_OP_breg28 :
			case DW_OP_breg29 :
			case DW_OP_breg30 :
			case DW_OP_breg31 :
				operand1 = Dwarf::decode_s_leb128(loc_ptr,leb128_length);
				loc_ptr = loc_ptr + leb128_length;
				offset = offset + leb128_length;
				break;

			case DW_OP_bregx :
				operand1 = Dwarf::decode_s_leb128(loc_ptr,leb128_length);
				loc_ptr = loc_ptr + leb128_length;
				offset = offset + leb128_length;

				operand2 = Dwarf::decode_u_leb128(loc_ptr,leb128_length);
				loc_ptr = loc_ptr + leb128_length;
				offset = offset + leb128_length;
				break;

			case DW_OP_dup :
			case DW_OP_drop :
				break;

			case DW_OP_pick :
				operand1 = *(Dwarf_Small *)loc_ptr;
				loc_ptr = loc_ptr + 1;
				offset = offset + 1;
				break;

			case DW_OP_over :
			case DW_OP_swap :
			case DW_OP_rot :
			case DW_OP_deref :
				break;

			case DW_OP_deref_size :
				operand1 = *(Dwarf_Small *)loc_ptr;
				loc_ptr = loc_ptr + 1;
				offset = offset + 1;
				break;

			case DW_OP_xderef :
				break;

			case DW_OP_xderef_size :
				operand1 = *(Dwarf_Small *)loc_ptr;
				loc_ptr = loc_ptr + 1;
				offset = offset + 1;
				break;

			case DW_OP_abs :
			case DW_OP_and :
			case DW_OP_div :
			case DW_OP_minus :
			case DW_OP_mod :
			case DW_OP_mul :
			case DW_OP_neg :
			case DW_OP_not :
			case DW_OP_or :
			case DW_OP_plus :
				break;

			case DW_OP_plus_uconst :
				operand1 = Dwarf::decode_u_leb128(loc_ptr,leb128_length);
				loc_ptr = loc_ptr + leb128_length;
				offset = offset + leb128_length;
				break;

			case DW_OP_shl :
			case DW_OP_shr :
			case DW_OP_shra :
			case DW_OP_xor :
				break;

			case DW_OP_le :
			case DW_OP_ge :
			case DW_OP_eq :
			case DW_OP_lt :
			case DW_OP_gt :
			case DW_OP_ne :
				break;

			case DW_OP_skip :
			case DW_OP_bra :
				dbg->read_2(&half_op1,loc_ptr);
				operand1 = half_op1;
				loc_ptr = loc_ptr + 2;
				offset = offset + 2;
				break;

			case DW_OP_piece :
				operand1 = Dwarf::decode_u_leb128(loc_ptr,leb128_length);
				loc_ptr = loc_ptr + leb128_length;
				offset = offset + leb128_length;
				break;

			case DW_OP_nop :
				break;

			default :
				throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
					"bad operator read for location expression");
		}


		curr_loc->dl_number = operand1;
		curr_loc->dl_number2 = operand2;

		if (head_loc == NULL)
			 head_loc = prev_loc = curr_loc;
		else {
			 prev_loc->next = curr_loc;
			 prev_loc = curr_loc;
		}
	}

	locdesc = new Dwarf_Locdesc(op_count);

	locdesc->convert_list(head_loc);

	return locdesc;
}

//-------------------------------------------------------------------

Dwarf_Locdesc_Tab *Dwarf_Attribute::form_loc() throw(Dwarf_Error)
{
    Dwarf_CU *cu_context = check();
    Dwarf_Debug *dbg = cu_context->dc_debug;

        // Pointer to Dwarf_Block that describes
        // the location expression.

    Dwarf_Block	*loc_block;

        // A pointer to the current Dwarf_Locdesc read.
    Dwarf_Locdesc *locdesc;

        // a pointer to table of location descriptors
    Dwarf_Locdesc_Tab	*tab;

        // offset in .debug_loc section
    Dwarf_Unsigned offset;

        // ----- BEGIN CODE -----

    if (form() == DW_FORM_block || form() == DW_FORM_block1 ||
            form() == DW_FORM_block2 || form() == DW_FORM_block4) {

        // if location expression in block

        loc_block = form_block();

            // Don't know what to do for 0 length location expressions.
        if (loc_block->db_len != 0) {
            locdesc = get_locdesc(
                                (Dwarf_Small *)loc_block->db_data,
                                loc_block->db_len,
                                dbg);

            locdesc->dl_lopc = 0;
            locdesc->dl_hipc = Dwarf_Unsigned(~0L);

            tab = new Dwarf_Locdesc_Tab(1);
            tab->convert_list(locdesc);

            delete loc_block;
            return tab;
        }

        delete loc_block;
    }
    else {
        // if location list as constant
        Dwarf_Addr lopc;
        Dwarf_Addr hipc;
        Dwarf_Unsigned loc_count = 0;
        Dwarf_Half len;

        Dwarf_Locdesc *head_locdesc = NULL;
        Dwarf_Locdesc *cur_locdesc = NULL;
        Dwarf_Locdesc *new_locdesc = NULL;
        USED(new_locdesc);

        offset = form_udata();
        Dwarf_Small *loc_ptr;

        if (dbg->dd_debug_loc == NULL)
            throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
                                                "null .debug_loc section");

        if (offset > dbg->dd_debug_loc_size)
            throw Dwarf_Error_Die_Attribute(Dwarf::DWARFERR,
                "invalid offset in section .debug_loc");

        loc_ptr = dbg->dd_debug_loc + offset;

        while(1) {
            dbg->read(&lopc,loc_ptr);
            dbg->read(&hipc,loc_ptr);

            if (lopc == 0 && hipc == 0) break;

            dbg->read_2(&len,loc_ptr);
            if (len != 0) {
                new_locdesc = get_locdesc(loc_ptr,len,dbg);

                new_locdesc->dl_lopc = lopc;
                new_locdesc->dl_hipc = hipc;

                loc_ptr += len;

                if (head_locdesc == NULL) {
                    head_locdesc = new_locdesc;
                    cur_locdesc = new_locdesc;
                }
				else {
                    cur_locdesc->next = new_locdesc;
                    cur_locdesc = new_locdesc;
                }

                loc_count++;
            }
        }

        tab = new Dwarf_Locdesc_Tab(loc_count);
        tab->convert_list(head_locdesc);
        return tab;
    }
    return NULL;
}
