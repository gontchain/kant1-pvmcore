//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//               Реализационный модуль pro_fram.cpp                     //
//                                                                      //
//  Файл реализации функций классов Dwarf_P_Fde и Dwarf_P_Cie           //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:33p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------
//
// class Dwarf_P_Fde & Dwarf_P_Cie implementation
//
//---------------------------------------------------------

#include <string.h>

#include "libelf.h"
#include "dwarferr.h"
#include "dwarftyp.h"
#include "dwarf.h"
#include "libdwarf.h"
#include "dwarfint.h"

#include "pro_fram.h"

//-------------------------------------------------------------------
//
// class Dwarf_P_Fde implementation
//
//-------------------------------------------------------------------

Dwarf_P_Fde::Dwarf_P_Fde(
        Dwarf_P_Debug *dbg,
        Dwarf_P_Cie *cie,
        Dwarf_Addr init_loc,
	    Dwarf_Unsigned sym_idx,
        Dwarf_Addr code_len) throw() : 
    dpf_inst(NULL),
	dpf_n_inst(0),
    dpf_n_bytes(0),
    dpf_last_inst(NULL),
    next(NULL),
    dpf_cie(cie),
	dpf_debug(dbg),
    dpf_initloc(init_loc),
    dpf_r_symidx(sym_idx),
    dpf_addr_range(code_len)
{
}

Dwarf_P_Fde::~Dwarf_P_Fde() throw()
{
	if (dpf_inst) {
		Dwarf_P_Frame_Pgm *ptr;
		while(dpf_inst) {
			ptr = dpf_inst->next;
			delete dpf_inst;
			dpf_inst = ptr;
		}
	}
    if (next) delete next;
}

	// добавить команду
void Dwarf_P_Fde::add_inst(
				Dwarf_Small op,
				Dwarf_Unsigned val1,
				Dwarf_Unsigned val2
				) throw(Dwarf_Error)
{
	Dwarf_P_Frame_Pgm   *curinst;
	int                 nbytes, nbytes1, nbytes2;
	Dwarf_Ubyte         db;
	Dwarf_Half          dh;
	Dwarf_Word          dw;
	char                *ptr;
	char buff1[ENCODE_SPACE_NEEDED];
	char buff2[ENCODE_SPACE_NEEDED];

	/* debug trace. uncomment if needed.
	printf ("add_fde: op = %d, val1 = 0x%llx, val2 = 0x%llx \n",
						 op, val1, val2);
	*/

	nbytes = 0;
	ptr = NULL;
	curinst = new Dwarf_P_Frame_Pgm;

	switch (op) {
		case DW_CFA_advance_loc:
                // выясняем наименьший размер памяти для записи смещения.
			if (val1 <= 0x3f) {
                    // помещается в 6 бит. кодируется в коде команды 
                    // DW_CFA_advance_loc
				db = Dwarf_Ubyte(val1);
				op |= db;
			}
			else if (val1 <= UCHAR_MAX) {
                    // помещается в 1 байт. помещается в однобайтовый параметр
                    // команды DW_CFA_advance_loc1
				op = DW_CFA_advance_loc1;
				db = Dwarf_Ubyte(val1);
				ptr = new char[1];
				memcpy((void *)ptr, (const void *)&db,1);
				nbytes = 1;
			}
			else if (val1 <= USHRT_MAX) {
                    // помещается в 2 байта. помещается в двухбайтовый параметр
                    // команды DW_CFA_advance_loc2
				op = DW_CFA_advance_loc2;
				dh = Dwarf_Half(val1);
				ptr = new char[2];
				dpf_debug->write_2(&dh,ptr);
				// memcpy((void *)ptr, (const void *)&dh,2);
				nbytes = 2;
			}
			else {
                    // всегда должен вмещаться в 4 байта. помещается в 
                    // чеырехбайтовый параметр команды DW_CFA_advance_loc4.
				op = DW_CFA_advance_loc4;
				dw = val1;
				ptr = new char[4];
				dpf_debug->write_4(&dw,ptr);
				// memcpy((void *)ptr, (const void *)&dw,4);
				nbytes = 4;
			}
			break;
		case DW_CFA_offset:
			if (val1 <= MAX_6_BIT_VALUE) {
                    // помещается в 6 бит. кодируется как часть команды
                    // DW_CFA_offset
				db = Dwarf_Ubyte(val1);
				op |= db;
				Dwarf::encode_leb128_nm(val2, &nbytes,buff1,sizeof(buff1));
				 ptr = new char [nbytes];
				 memcpy(ptr,buff1,nbytes);
			}
			else {
                    // не помещается в 6 бит. кодируется как leb128 параметр
                    // команды DW_CFA_offset_extended
				 op = DW_CFA_offset_extended;

				 Dwarf::encode_leb128_nm(val1, &nbytes1,buff1,sizeof(buff1));
				 Dwarf::encode_leb128_nm(val2, &nbytes2,buff2,sizeof(buff2));
				 ptr = new char [nbytes1+nbytes2];
				 memcpy(ptr, buff1, nbytes1);
				 memcpy(ptr+nbytes1, buff2, nbytes2);
				 nbytes = nbytes1 + nbytes2;
			}
			break;
		case DW_CFA_restore:
			if (val1 <= MAX_6_BIT_VALUE) {
                    // Когда номер регистра помещается в 6 бит, то
                    // он задается в коде команды DW_CFA_restore
				db = Dwarf_Ubyte(val1);
				op |= db;
			}
			else {
                    // номер регистра не помещается в 6 бит. Используем команду
                    // DW_CFA_restore_extended. В ней номер регистра кодируется
                    // как leb128 число.
				 op = DW_CFA_restore_extended;

				 Dwarf::encode_leb128_nm(val1, &nbytes,buff1,sizeof(buff1));
				 ptr = new char [nbytes];
				 memcpy(ptr, buff1, nbytes);
			}
			break;
		case DW_CFA_undefined:
		case DW_CFA_same_value:
			Dwarf::encode_leb128_nm(val1, &nbytes, buff1,sizeof(buff1));
			ptr = new char[nbytes];
			memcpy(ptr, buff1, nbytes);
			break;

		case DW_CFA_register:
		case DW_CFA_def_cfa:

			Dwarf::encode_leb128_nm(val1, &nbytes1,buff1,sizeof(buff1));
			Dwarf::encode_leb128_nm(val2, &nbytes2,buff2,sizeof(buff2));
			ptr = new char[nbytes1+nbytes2];
			memcpy(ptr, buff1, nbytes1);
			memcpy(ptr+nbytes1, buff2, nbytes2);
			nbytes = nbytes1 + nbytes2;
			break;

		case DW_CFA_def_cfa_register:
		case DW_CFA_def_cfa_offset:
			Dwarf::encode_leb128_nm(val1, &nbytes,buff1,sizeof(buff1));
			ptr = new char[nbytes];
			memcpy(ptr, buff1, nbytes);
			break;

		default:
			break;
	}

	curinst->dpfp_opcode = op;
	curinst->dpfp_args = ptr;
	curinst->dpfp_nbytes = nbytes;
	curinst->next = NULL;

	add_to_fde(curinst);
}

	// установить смещение
void Dwarf_P_Fde::fde_cfa_offset(Dwarf_Unsigned reg, Dwarf_Signed offset)
	throw(Dwarf_Error)
{
	Dwarf_Ubyte opc, regno;
	char *ptr;
	Dwarf_P_Frame_Pgm *curinst;
	int nbytes;
	char buff1[ENCODE_SPACE_NEEDED];

	curinst = new Dwarf_P_Frame_Pgm;

	opc = DW_CFA_offset;
	regno = Dwarf_Ubyte(reg);
	if (regno & 0xc0)
		throw Dwarf_Error_Pro_Fde_Overflow("number of register above 6 bit");

	opc = (unsigned char)(opc | regno);      // lower 6 bits are register number
	curinst->dpfp_opcode = opc;
	Dwarf::encode_leb128_nm(offset, &nbytes,
						buff1,sizeof(buff1));
	ptr = new char [nbytes];

	memcpy(ptr, buff1, nbytes);

	curinst->dpfp_args = ptr;
	curinst->dpfp_nbytes = nbytes;
	curinst->next = NULL;

	add_to_fde(curinst);

}

void Dwarf_P_Fde::add_to_fde(Dwarf_P_Frame_Pgm *curinst) throw()
{
	if (dpf_last_inst != NULL) {
		dpf_last_inst->next = curinst;
		dpf_last_inst = curinst;
		dpf_n_inst++;
		dpf_n_bytes += curinst->dpfp_nbytes + sizeof(Dwarf_Ubyte) ;
	}
	else {
		dpf_last_inst = dpf_inst = curinst;
		dpf_n_inst = 1;
		dpf_n_bytes = curinst->dpfp_nbytes + sizeof(Dwarf_Ubyte);
	}
}


//-------------------------------------------------------------------
//
// end of functions of class Dwarf_P_Fde
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// class Dwarf_P_Cie implemantation
//
//-------------------------------------------------------------------

Dwarf_P_Cie::Dwarf_P_Cie(Dwarf_P_Debug *dbg,Dwarf_Small version,char *augmenter,
	Dwarf_Small code_align,Dwarf_Small data_align,Dwarf_Small return_reg) throw() :
			dpc_version(version),dpc_aug(augmenter),dpc_code_align(code_align),
			dpc_data_align(data_align),dpc_ret_reg(return_reg),dpc_inst(NULL),
			dpc_n_inst(0),dpc_n_bytes(0),dpc_last_inst(NULL),next(NULL),dpc_debug(dbg)
{
}

Dwarf_P_Cie::~Dwarf_P_Cie()
{
	if (dpc_inst) {
		Dwarf_P_Frame_Pgm *ptr;
		while(dpc_inst) {
			ptr = dpc_inst->next;
			delete dpc_inst;
			dpc_inst = ptr;
		}
	}
    if (next) delete next;
}

void Dwarf_P_Cie::add_to_cie(Dwarf_P_Frame_Pgm *curinst) throw()
{
	if (dpc_last_inst != NULL) {
		dpc_last_inst->next = curinst;
		dpc_last_inst = curinst;
		dpc_n_inst++;
		dpc_n_bytes += curinst->dpfp_nbytes + sizeof(Dwarf_Ubyte) ;
	}
	else {
		dpc_last_inst = dpc_inst = curinst;
		dpc_n_inst = 1;
		dpc_n_bytes = curinst->dpfp_nbytes + sizeof(Dwarf_Ubyte);
	}
}

void Dwarf_P_Cie::add_inst(Dwarf_Small op,Dwarf_Unsigned val1,Dwarf_Unsigned val2)
	throw(Dwarf_Error)
{
	Dwarf_P_Frame_Pgm   *curinst;
	int                 nbytes, nbytes1, nbytes2;
	Dwarf_Ubyte         db;
	Dwarf_Half          dh;
	Dwarf_Word          dw;
	char                *ptr;
	char buff1[ENCODE_SPACE_NEEDED];
	char buff2[ENCODE_SPACE_NEEDED];

	/* debug trace. uncomment if needed.
	printf ("add_fde: op = %d, val1 = 0x%llx, val2 = 0x%llx \n",
						 op, val1, val2);
	*/

	nbytes = 0;
	ptr = NULL;
	curinst = new Dwarf_P_Frame_Pgm;

	switch (op) {
		case DW_CFA_advance_loc:
			if (val1 <= 0x3f) {
				db = Dwarf_Small(val1);
				op |= db;
			}
			else if (val1 <= UCHAR_MAX) {
				op = DW_CFA_advance_loc1;
				db = Dwarf_Small(val1);
				ptr = new char[1];
				memcpy((void *)ptr, (const void *)&db,1);
				nbytes = 1;
			}
			else if (val1 <= USHRT_MAX) {
				op = DW_CFA_advance_loc2;
				dh = Dwarf_Half(val1);
				ptr = new char[2];
				dpc_debug->write_2(&dh,ptr);
				// memcpy((void *)ptr, (const void *)&dh,2);
				nbytes = 2;
			}
			else {
				op = DW_CFA_advance_loc4;
				dw = val1;
				ptr = new char[4];
				dpc_debug->write_4(&dw,ptr);
				// memcpy((void *)ptr, (const void *)&dw,4);
				nbytes = 4;
			}
			break;
		case DW_CFA_offset:
			if (val1 <= MAX_6_BIT_VALUE) {
				db = Dwarf_Small(val1);
				op |= db;
				Dwarf::encode_leb128_nm(val2, &nbytes,buff1,sizeof(buff1));
				 ptr = new char [nbytes];
				 memcpy(ptr,buff1,nbytes);
			}
			else {
				 op = DW_CFA_offset_extended;

				 Dwarf::encode_leb128_nm(val1, &nbytes1,buff1,sizeof(buff1));
				 Dwarf::encode_leb128_nm(val2, &nbytes2,buff2,sizeof(buff2));
				 ptr = new char [nbytes1+nbytes2];
				 memcpy(ptr, buff1, nbytes1);
				 memcpy(ptr+nbytes1, buff2, nbytes2);
				 nbytes = nbytes1 + nbytes2;
			}
			break;
		case DW_CFA_undefined:
		case DW_CFA_same_value:
			Dwarf::encode_leb128_nm(val1, &nbytes, buff1,sizeof(buff1));
			ptr = new char[nbytes];
			memcpy(ptr, buff1, nbytes);
			break;

		case DW_CFA_register:
		case DW_CFA_def_cfa:

			Dwarf::encode_leb128_nm(val1, &nbytes1,buff1,sizeof(buff1));
			Dwarf::encode_leb128_nm(val2, &nbytes2,buff2,sizeof(buff2));
			ptr = new char[nbytes1+nbytes2];
			memcpy(ptr, buff1, nbytes1);
			memcpy(ptr+nbytes1, buff2, nbytes2);
			nbytes = nbytes1 + nbytes2;
			break;

		case DW_CFA_def_cfa_register:
		case DW_CFA_def_cfa_offset:
			Dwarf::encode_leb128_nm(val1, &nbytes,buff1,sizeof(buff1));
			ptr = new char[nbytes];
			memcpy(ptr, buff1, nbytes);
			break;

		default:
			break;
	}

	curinst->dpfp_opcode = op;
	curinst->dpfp_args = ptr;
	curinst->dpfp_nbytes = nbytes;
	curinst->next = NULL;

	add_to_cie(curinst);
}
