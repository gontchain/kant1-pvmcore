//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//               Реализационный модуль pro_gfrm.cpp                     //
//                                                                      //
//  Файл реализует  функцию Dwarf_P_Debug::generate_debugframe          //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:33p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------//
//		  Generate debug_frame section                             //
//---------------------------------------------------------------//

#include <string.h>

#include "libelf.h"
#include "dwarferr.h"
#include "dwarftyp.h"
#include "dwarf.h"
#include "libdwarf.h"
#include "dwarfint.h"

#include "pro_fram.h"
#include "pro_dbg.h"


Dwarf_Signed Dwarf_P_Debug::generate_debugframe() throw(Dwarf_Error)
{
	Dwarf_Signed elfsectno;
	int i;
	Dwarf_Signed firsttime, pad;	// pad for padding to align cies and fdes
	Dwarf_P_Cie *curcie;
	Dwarf_P_Fde *curfde;
	unsigned char *data;
	Dwarf_Word dw;
	Dwarf_Unsigned du;
	Dwarf_Ubyte db;
	Dwarf_Signed *cie_offs;		// holds byte offsets for links to fde's
	Dwarf_Signed cie_length;
	Dwarf_Signed cie_no;
	Dwarf_P_Rel *rel_head, *rel_tail;	// relocation pointers
	Dwarf_Unsigned  rel_nbytes;                 		// bytes in relocation section
	Dwarf_Unsigned   name_idx;                   		// holds index for rel section
	Dwarf_Unsigned cur_off;         		// current offset of written
													// data, held for relocation info

	if (dpd_frame_cies == NULL) return dpd_n_debug_sect;

	elfsectno = Dwarf::elf_sects[DEBUG_FRAME];

	curcie = dpd_frame_cies;
	cie_length = 0;
	rel_head = NULL;
	rel_tail = NULL;
	rel_nbytes = 0;
	cur_off = 0;
	USED(cur_off);
	cie_offs = new Dwarf_Signed[dpd_n_cie];
	firsttime = 1;
	// generate cie number as we go along
	cie_no = 1;
	while (curcie) {
		char *code_al;
		int c_bytes;
		char *data_al;
		int d_bytes;
		char buff1[ENCODE_SPACE_NEEDED];
		char buff2[ENCODE_SPACE_NEEDED];

		Dwarf::encode_leb128_nm(curcie->dpc_code_align,&c_bytes,buff1,sizeof(buff1));
		Dwarf::encode_leb128_nm(curcie->dpc_data_align,&d_bytes,buff2,sizeof(buff2));

		code_al = buff1;
		data_al = buff2;

		// get the correct offset
		if (firsttime)
			cie_offs[cie_no-1] = 0;
		else
			cie_offs[cie_no-1] = cie_offs[cie_no-2]+cie_length+word_size();
		cie_no++;
		cie_length = sizeof(Dwarf_Unsigned) +       // cie_id
						sizeof(Dwarf_Ubyte) +          // cie version
						strlen(curcie->dpc_aug)+1  +   // augmentation
						c_bytes +
						d_bytes +
						sizeof(Dwarf_Ubyte) +          // return reg address
						curcie->dpc_n_bytes;

		pad = Dwarf::PADDING(cie_length, word_size());
		cie_length += pad;
		if (firsttime) {
			data = get_new_chunk(elfsectno,cie_length + word_size());
			firsttime = 0;
		}
		else
			 data = get_chunk(elfsectno,cie_length + word_size());

		du = cie_length;

		dw = du;
		write_4(&dw,data);
		data += sizeof(Dwarf_Word);
		dw = DW_CIE_ID;
		write_4(&dw,data);
		data += sizeof(Dwarf_Word);

		db = curcie->dpc_version;
		memcpy((void *)data, (const void *)&db, sizeof(Dwarf_Ubyte));
		data += sizeof(Dwarf_Ubyte);
		strcpy((char *)data, curcie->dpc_aug);
		data += strlen(curcie->dpc_aug)+1;
		memcpy((void *)data, (const void *)code_al, c_bytes);
		data += c_bytes;
		memcpy((void *)data, (const void *)data_al, d_bytes);
		data += d_bytes;
		db = curcie->dpc_ret_reg;
		memcpy((void *)data, (const void *)&db, sizeof(Dwarf_Ubyte));
		data += sizeof(Dwarf_Ubyte);

		Dwarf_P_Frame_Pgm *curinst;
		curinst = curcie->dpc_inst;
		while (curinst) {
			db = curinst->dpfp_opcode;
			memcpy((void *)data, (const void *)&db, sizeof(Dwarf_Ubyte));
			data += sizeof(Dwarf_Ubyte);
			memcpy((void *)data, (const void *)curinst->dpfp_args,curinst->dpfp_nbytes);
			data += curinst->dpfp_nbytes;
			curinst = curinst->next;
		}

//		memcpy((void *)data, (const void *)curcie->dpc_inst, curcie->dpc_inst);
//		data += curcie->dpc_inst;

		for (i = 0 ; i < pad ; i++) {
			*data = DW_CFA_nop;
			data++;
		}
		curcie = curcie->next;
	}

	// calculate current offset
	cur_off = cie_offs[cie_no-2] + cie_length + word_size();

	// write out fde's
	curfde = dpd_frame_fdes;
	while (curfde) {
		Dwarf_P_Frame_Pgm *curinst;
		long fde_length;
		int pad;

		fde_length = curfde->dpf_n_bytes +
						  word_size() +            // cie pointer
						  word_size() +            // initial loc
						  word_size();             // address range

		// store relocation for cie pointer
		if (rel_head == NULL) {
			rel_head = new Dwarf_P_Rel();
			rel_tail = rel_head;
		} else {
			rel_tail->next = new Dwarf_P_Rel();
			rel_tail = rel_tail->next;
			rel_tail->next = NULL;
		}

		rel_tail->set(	cur_off + word_size(),	//  + for length field
								Dwarf_Half(Dwarf::sect_name_idx[DEBUG_FRAME]),
								R_NC_BYTEPTR
								);

		rel_nbytes += ELF32_T_REL_FSIZE;

		// store relocation information for initial location
		rel_tail->next = new Dwarf_P_Rel();
		rel_tail = rel_tail->next;
		rel_tail->next = NULL;
		rel_tail->set(// 2* for length and cie_ptr fields
							cur_off+2*word_size(),
							Dwarf_Half(curfde->dpf_r_symidx),
							R_NC_ADDR);

		rel_nbytes += ELF32_T_REL_FSIZE;

		// adjust for padding
		pad = Dwarf::PADDING(fde_length, word_size());
		fde_length += pad;

		cur_off += fde_length + word_size();

		// write out fde
		data = get_chunk(elfsectno,fde_length + word_size());
		du = fde_length;

		dw = du;
		write_4(&dw,data);
		data += sizeof(Dwarf_Word);

		dw = cie_offs[curfde->dpf_cie->index()-1];
		write_4(&dw,data);
		data += sizeof(Dwarf_Word);

		dw = curfde->dpf_initloc;
		write_4(&dw,data);
		data += sizeof(Dwarf_Word);

		dw = curfde->dpf_addr_range;
		write_4(&dw,data);
		data += sizeof(Dwarf_Word);

		curinst = curfde->dpf_inst;
		while (curinst) {
			db = curinst->dpfp_opcode;
			memcpy((void *)data, (const void *)&db, sizeof(Dwarf_Ubyte));
			data += sizeof(Dwarf_Ubyte);
			memcpy((void *)data, (const void *)curinst->dpfp_args,curinst->dpfp_nbytes);
			data += curinst->dpfp_nbytes;
			curinst = curinst->next;
		}
		// padding
		for (i = 0 ; i < pad ; i++) {
			*data = DW_CFA_nop;
			data++;
		}
		curfde = curfde->next;
	}

    delete[] cie_offs;  // более не нужен

    if (rel_nbytes > 0) {
        Dwarf::reloc_sects[DEBUG_FRAME] = dpd_func(".rel.debug_frame", SHT_REL, 0,
            SHN_UNDEF, Dwarf::elf_sects[DEBUG_FRAME], &name_idx);

        if (Dwarf::reloc_sects[DEBUG_FRAME] == -1)
            throw Dwarf_Error_Pro_Elf("error creating section .rel.debug_frame");

            // write out relocation records
        elfsectno = Dwarf::reloc_sects[DEBUG_FRAME];
        write_reloc_section(rel_head,elfsectno,rel_nbytes);

        delete rel_head;    // удаляем когда более не нужна
	}

	return dpd_n_debug_sect;
}
