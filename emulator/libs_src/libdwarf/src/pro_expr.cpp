//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//               Реализационный модуль pro_expr.cpp                     //
//                                                                      //
//  Файл реализации функций класса Dwarf_P_Expr                         //
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
// class Dwarf_P_Expr
//
//-------------------------------------------------------------------

#include <string.h>

#include "libelf.h"
#include "dwarferr.h"
#include "dwarftyp.h"
#include "dwarf.h"
#include "libdwarf.h"
#include "dwarfint.h"


Dwarf_P_Expr::Dwarf_P_Expr(Dwarf_P_Debug *dbg) throw (Dwarf_Error) : dpe_dbg(dbg),
	dpe_reloc_offset(0),dpe_reloc_sym_index(SHN_UNDEF),dpe_next_byte_offset(0)
{
	if (dbg == NULL) 
        throw Dwarf_Error_Pro_Expr("null Dwarf_P_Debug argument");

	dpe_byte_stream = new Dwarf_Small[MAXIMUM_LOC_EXPR_LENGTH];

	for (Dwarf_Unsigned i = 0;i < MAXIMUM_LOC_EXPR_LENGTH;i++)
		dpe_byte_stream[i] = 0;
}

Dwarf_P_Expr::~Dwarf_P_Expr() throw()
{
	if (dpe_byte_stream) delete[] dpe_byte_stream;
}

Dwarf_Unsigned Dwarf_P_Expr::add_expr_gen(Dwarf_Small opcode,Dwarf_Unsigned val1,
		Dwarf_Unsigned val2) throw (Dwarf_Error)
{
	char encode_buffer[2*ENCODE_SPACE_NEEDED];
		// 2* since used	to concatenate 2 leb's below

	char encode_buffer2[ENCODE_SPACE_NEEDED];
	USED(encode_buffer2);
//	int  res;

		 // Give the buffer where the operands are first
		 // going to be assembled the largest alignment.
	Dwarf_Unsigned      operand_buffer[10];

		 /*  Size of the byte stream buffer that needs
			  to be memcpy-ed.
		 */
	int                 operand_size;

		 /*  Points to the byte stream for the first operand,
			  and finally to the buffer that is memcp-ed into
			  the Dwarf_P_Expr_s struct.
		 */
	Dwarf_Small         *operand;

		 /*  Points to the initial byte stream for a second
			  operand.  This is appended to the byte stream for
			  the first operand pointed to by operand, so that
			  the final memcpy deals with only one buffer.
		 */
//	Dwarf_Small         *operand2;

		 /* Size of the byte stream for second operand. */
	int                 operand2_size;

		 /* Points to next byte to be written in Dwarf_P_Expr_s struct. */
	Dwarf_Small         *next_byte_ptr;

		 /* Offset past the last byte written into Dwarf_P_Expr_s. */
	int                 next_byte_offset;
	Dwarf_Half tmp_val;

	/* ***** BEGIN CODE ***** */

	operand = NULL;
	operand_size = 0;

	switch (opcode) {
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
			Dwarf::encode_signed_leb128_nm(val1,&operand_size,encode_buffer,
				sizeof(encode_buffer));
			operand = (Dwarf_Small *)encode_buffer;
			break;

		case DW_OP_regx :
			Dwarf::encode_leb128_nm(val1, &operand_size,encode_buffer,
				sizeof(encode_buffer));
			operand = (Dwarf_Small *)encode_buffer;
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
			 break;

		case DW_OP_addr :
      	throw Dwarf_Error_Pro_Expr("use special function to add DW_OP_addr");

		case DW_OP_const1u :
		case DW_OP_const1s :
			operand = (Dwarf_Small *)&operand_buffer[0];
			*operand = (char)val1;
			operand_size = 1;
			break;

		case DW_OP_const2u :
		case DW_OP_const2s :
			operand = (Dwarf_Small *)&operand_buffer[0];
//			*(Dwarf_Half *)operand = *(Dwarf_Half *)((char *)&val1 + sizeof(val1) - 2);
			tmp_val = Dwarf_Half(val1);
			dpe_dbg->write_2(&tmp_val,(char *)operand);
			operand_size = 2;
			break;

		case DW_OP_const4u :
		case DW_OP_const4s :
			operand = (Dwarf_Small *)&operand_buffer[0];
//			*(Dwarf_Word *)operand = *(Dwarf_Word *)((char *)&val1 + sizeof(val1) - 4);
			dpe_dbg->write_4(&val1,(char *)operand);
			operand_size = 4;
			break;

		case DW_OP_const8u :
		case DW_OP_const8s :
			throw Dwarf_Error_Internal("64 bits constants in loc expr not yet realised");
//			operand = (Dwarf_Small *)&operand_buffer[0];
//			*(Dwarf_Unsigned *)operand = val1;
//			operand_size = 8;
//			break;

		case DW_OP_constu :
			Dwarf::encode_leb128_nm(val1,&operand_size,encode_buffer,
				sizeof(encode_buffer));
			operand = (Dwarf_Small *)encode_buffer;
			break;

		case DW_OP_consts :
			Dwarf::encode_signed_leb128_nm(val1,
							 &operand_size,
							 encode_buffer, sizeof(encode_buffer));
			operand = (Dwarf_Small *)encode_buffer;
			break;

		case DW_OP_fbreg :
			Dwarf::encode_signed_leb128_nm(val1,
							 &operand_size,
							 encode_buffer, sizeof(encode_buffer));
			operand = (Dwarf_Small *)encode_buffer;
			break;

		case DW_OP_bregx :
			Dwarf::encode_leb128_nm(val1, &operand_size,
							 encode_buffer, sizeof(encode_buffer));
			operand = (Dwarf_Small *)encode_buffer;
				  /* put this one directly into 'operand' at tail of
					  prev value
				  */
			Dwarf::encode_signed_leb128_nm(val2, &operand2_size,
							 ((char *)operand)+operand_size, sizeof(encode_buffer2));
			operand_size += operand2_size;

		case DW_OP_dup :
		case DW_OP_drop :
			break;

		case DW_OP_pick :
			operand = (Dwarf_Small *)&operand_buffer[0];
			*operand = *((char *)&val1 + sizeof(val1) - 1);
			operand_size = 1;
			break;

		case DW_OP_over :
		case DW_OP_swap :
		case DW_OP_rot :
		case DW_OP_deref :
		case DW_OP_xderef :
			break;

		case DW_OP_deref_size :
		case DW_OP_xderef_size :
			operand = (Dwarf_Small *)&operand_buffer[0];
			*operand = *((char *)&val1 + sizeof(val1) - 1);
			operand_size = 1;
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
			Dwarf::encode_leb128_nm(val1, &operand_size,
							 encode_buffer, sizeof(encode_buffer));
			operand = (Dwarf_Small *)encode_buffer;
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
			// FIX: unhandled! OP_bra, OP_skip!
			throw Dwarf_Error_Internal(Dwarf::DWARF_PRO_ERR,
				"branches in location expression in producer not yet realised");

		case DW_OP_piece :
			Dwarf::encode_leb128_nm(val1, &operand_size, encode_buffer,
				sizeof(encode_buffer));
			operand = (Dwarf_Small *)encode_buffer;
			break;

		case DW_OP_nop :
			break;

		default :
			throw Dwarf_Error_Pro_Expr("invalid opcode in location expression");
	}

	next_byte_offset = dpe_next_byte_offset + operand_size + 1;

	if (next_byte_offset > MAXIMUM_LOC_EXPR_LENGTH)
		throw Dwarf_Error_Pro_Expr("location expression too long");

	next_byte_ptr = &(dpe_byte_stream[0]) + dpe_next_byte_offset;

	*next_byte_ptr = opcode;
	next_byte_ptr++;
	memcpy(next_byte_ptr, operand, operand_size);

	dpe_next_byte_offset = next_byte_offset;
	return(next_byte_offset);

}

Dwarf_Unsigned Dwarf_P_Expr::add_expr_addr(
		Dwarf_Addr address,
		Dwarf_Signed sym_index
		) throw(Dwarf_Error)
{
	Dwarf_P_Debug	*dbg = dpe_dbg;;
	Dwarf_Small		*next_byte_ptr;
	Dwarf_Unsigned	next_byte_offset;

	next_byte_offset = dpe_next_byte_offset + dbg->addr_size() + 1;

	if (next_byte_offset > MAXIMUM_LOC_EXPR_LENGTH)
		throw Dwarf_Error_Pro_Expr("location expression too long");

	next_byte_ptr = &(dpe_byte_stream[0]) + dpe_next_byte_offset;

	*next_byte_ptr = DW_OP_addr;
	next_byte_ptr++;
	dbg->write_4(&address,(char *)next_byte_ptr);

	if (dpe_reloc_offset != 0)
		throw Dwarf_Error_Pro_Expr("multiple relocation in one expression");

	dpe_reloc_sym_index = sym_index;
	dpe_reloc_offset = dpe_next_byte_offset + 1;

	dpe_next_byte_offset = next_byte_offset;

   return dpe_next_byte_offset;
}


Dwarf_Unsigned	Dwarf_P_Expr::current_offset() const
{
	return dpe_next_byte_offset;
}

Dwarf_Ptr Dwarf_P_Expr::get_bytes() const
{
	return((Dwarf_Ptr)&(dpe_byte_stream[0]));
}

Dwarf_Unsigned Dwarf_P_Expr::get_length() const
{
	return dpe_next_byte_offset;
}
