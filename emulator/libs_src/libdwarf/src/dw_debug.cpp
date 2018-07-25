//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Ѕазовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Ѕиблиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//                 –еализационный модуль dw_debug.cpp                   //
//                                                                      //
//  ‘айл реализации функций класса Dwarf_Debug                          //
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

//-------------------------------------------------------------------//
// class Dwarf_Debug realisation                                     //
//-------------------------------------------------------------------//

Dwarf_Debug::Dwarf_Debug (ELF *elf) throw(Dwarf_Error) 
    : dd_debug_info(NULL),
	dd_debug_abbrev(NULL),dd_debug_line(NULL),dd_debug_loc(NULL),
	dd_debug_aranges(NULL),dd_debug_macinfo(NULL),dd_debug_pubnames(NULL),
	dd_debug_str(NULL),dd_debug_frame(NULL),dd_debug_info_size(0),
	dd_debug_abbrev_size(0),dd_debug_line_size(0),dd_debug_loc_size(0),
	dd_debug_aranges_size(0),dd_debug_macinfo_size(0),dd_debug_pubnames_size(0),
	dd_debug_str_size(0),dd_debug_frame_size(0),dd_fde_data(NULL),
	dd_cie_data(NULL),dd_cu_list(NULL),dd_encode(ELFDATANONE),dd_global_tab(NULL)
	,dd_arange_tab(NULL)
{
	ELF_SCN	    *   scn  = 0;
	ELF_DATA    *   data = 0;
	USED(data);
	char        *   scn_name = 0;
	USED(scn_name);
	int             found = 0;
	char        *   pident = 0;

	if (!elf) throw Dwarf_Error_Debug(Dwarf::DWARFERR,"null elf");

	try {
		pident = elf->GetIdent(NULL);
	}
	catch(ELF_ERROR x) {
		throw Dwarf_Error_Elf(x);
	}

	try {
		if (pident[EI_CLASS] != ELFCLASS32)
			throw Dwarf_Error_Debug(Dwarf::DWARFERR,"not 32 bits class");

		dd_encode = pident[EI_DATA];
		dd_lsize = Dwarf_Small(ELF32_T_WORD_FSIZE);

		while(1) {
			scn = elf->NextScn(scn);
            if (scn == NULL) break;

			scn_name = scn->GetName();

			if (strncmp(scn_name,".debug_",7)) continue;

			if (strcmp(scn_name,".debug_info") == 0) {
				if (dd_debug_info != NULL)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"duplicate .debug_info section");
				data = scn->GetData(NULL);
				if (data->d_size == 0)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"no data in .debug_info section");
				dd_debug_info = (Dwarf_Small *)data->d_buf;
				dd_debug_info_size = data->d_size;
				found = 1;
				continue;
			}
			if (strcmp(scn_name,".debug_abbrev") == 0) {
				if (dd_debug_abbrev != NULL)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"duplicate .debug_abbrev section");
				data = scn->GetData(NULL);
				if (data->d_size == 0)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"no data in .debug_abbrev section");
				dd_debug_abbrev = (Dwarf_Small *)data->d_buf;
				dd_debug_abbrev_size = data->d_size;
				continue;
			}
			if (strcmp(scn_name,".debug_aranges") == 0) {
				if (dd_debug_aranges != NULL)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"duplicate .debug_aranges section");
				data = scn->GetData(NULL);
				if (data->d_size == 0)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"no data in .debug_aranges section");
				dd_debug_aranges = (Dwarf_Small *)data->d_buf;
				dd_debug_aranges_size = data->d_size;
				continue;
			}
			if (strcmp(scn_name,".debug_line") == 0) {
				if (dd_debug_line != NULL)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"duplicate .debug_line section");
				data = scn->GetData(NULL);
				if (data->d_size == 0)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"no data in .debug_line section");
				dd_debug_line = (Dwarf_Small *)data->d_buf;
				dd_debug_line_size = data->d_size;
				continue;
			}
			if (strcmp(scn_name,".debug_frame") == 0) {
				if (dd_debug_frame != NULL)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"duplicate .debug_frame section");
				data = scn->GetData(NULL);
				if (data->d_size == 0)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"no data in .debug_frame section");
				dd_debug_frame = (Dwarf_Small *)data->d_buf;
				dd_debug_frame_size = data->d_size;
				continue;
			}
			if (strcmp(scn_name,".debug_frame") == 0) {
				if (dd_debug_frame != NULL)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"duplicate .debug_frame section");
				data = scn->GetData(NULL);
				if (data->d_size == 0)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"no data in .debug_frame section");
				dd_debug_frame = (Dwarf_Small *)data->d_buf;
				dd_debug_frame_size = data->d_size;
				found = 1;
				continue;
			}
			if (strcmp(scn_name,".debug_loc") == 0) {
				if (dd_debug_loc != NULL)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"duplicate .debug_loc section");
				data = scn->GetData(NULL);
				if (data->d_size == 0)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"no data in .debug_loc section");
				dd_debug_loc = (Dwarf_Small *)data->d_buf;
				dd_debug_loc_size = data->d_size;
				continue;
			}
			if (strcmp(scn_name,".debug_macinfo") == 0) {
				if (dd_debug_macinfo != NULL)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"duplicate .debug_macinfo section");
				data = scn->GetData(NULL);
				if (data->d_size == 0)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"no data in .debug_macinfo section");
				dd_debug_macinfo = (Dwarf_Small *)data->d_buf;
				dd_debug_macinfo_size = data->d_size;
				continue;
			}
			if (strcmp(scn_name,".debug_pubnames") == 0) {
				if (dd_debug_pubnames != NULL)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"duplicate .debug_pubnames section");
				data = scn->GetData(NULL);
				if (data->d_size == 0)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"no data in .debug_pubnames section");
				dd_debug_pubnames = (Dwarf_Small *)data->d_buf;
				dd_debug_pubnames_size = data->d_size;
				continue;
			}
			if (strcmp(scn_name,".debug_str") == 0) {
				if (dd_debug_str != NULL)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"duplicate .debug_str section");
				data = scn->GetData(NULL);
				if (data->d_size == 0)
					throw Dwarf_Error_Debug(Dwarf::DWARFERR,"no data in .debug_str section");
				dd_debug_str = (Dwarf_Small *)data->d_buf;
				dd_debug_str_size = data->d_size;
				continue;
			}
		}
		if (found == 0)
			throw Dwarf_Error_Debug(Dwarf::DWARFERR,"no DWARF information");

		read_CU_list();

        try {
		    read_fde_cie_table();
        }
        catch (Dwarf_Error_Frame_Found) {   // если нет ни одной CIE или FDE
                                            // то продолжаем работать, как 
                                            // будто нет секции .debug_frame
                                            // вообще
        }

            // удал€ем массив байтов идентификации
        delete pident;
	}
	catch(Dwarf_Error&) {
		if (pident) delete pident;
		if (dd_cu_list) {
			Dwarf_CU *ptr = dd_cu_list;
			Dwarf_CU *ptr_delete;

			while(ptr != NULL) {
				ptr_delete = ptr;
				ptr = ptr->next;
				delete ptr_delete;
			}
		}
		dd_cu_list = 0;
		if (dd_fde_data) delete dd_fde_data;
		dd_fde_data = 0;
		if (dd_cie_data) delete dd_cie_data;
		dd_cie_data = 0;
		throw;
	}
	catch(ELF_ERROR& x) {
		if (pident) delete pident;
		if (dd_cu_list) {
			Dwarf_CU *ptr = dd_cu_list;
			Dwarf_CU *ptr_delete;

			while(ptr != NULL) {
				ptr_delete = ptr;
				ptr = ptr->next;
				delete ptr_delete;
			}
		}
		dd_cu_list = 0;
		if (dd_fde_data) delete dd_fde_data;
		dd_fde_data = 0;
		if (dd_cie_data) delete dd_cie_data;
		dd_cie_data = 0;
		throw Dwarf_Error_Elf(x);
	}
}

//-------------------------------------------------------------------
// destructor
//-------------------------------------------------------------------

Dwarf_Debug::~Dwarf_Debug() throw(Dwarf_Error)
{
	if (dd_fde_data) delete dd_fde_data;
	if (dd_cie_data) delete dd_cie_data;

	if (dd_global_tab) delete dd_global_tab;
	if (dd_arange_tab) delete dd_arange_tab;

	Dwarf_CU *ptr = dd_cu_list;
	Dwarf_CU *ptr_delete;

	while(ptr != NULL) {
		ptr_delete = ptr;
		ptr = ptr->next;
		delete ptr_delete;
	}
}

//-------------------------------------------------------------------
// begin internal private Dwarf_Debug function
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// read all CU at startup of Dwarf_debug
//-------------------------------------------------------------------

void Dwarf_Debug::read_CU_list() throw(Dwarf_Error)
{
	Dwarf_Off 	offset = 0;
	Dwarf_CU	 	*cu_context = NULL;
	USED(cu_context);
	Dwarf_CU		*cu_list_end = NULL;

	while(offset < dd_debug_info_size) {


		cu_context = new Dwarf_CU(offset,this);

		offset = offset + cu_context->length() + dd_lsize;

		if (dd_cu_list == NULL) {
			 dd_cu_list = cu_context;
			 cu_list_end = cu_context;
		}
		else {
			 cu_list_end->next = cu_context;
			 cu_list_end = cu_context;
		}

	}
}

//-------------------------------------------------------------------
// used in read_fde_cie_table
//-------------------------------------------------------------------

Dwarf_Small	*Dwarf_Debug::get_augment_string(Dwarf_Small *ptr) throw(Dwarf_Error)
{
	Dwarf_Unsigned length;
	Dwarf_Unsigned cie_id;
	Dwarf_Small    version;

	// Read the length field.
	read(&length,ptr);
	ptr += dd_lsize;

	// Read the Cie Id field.
	read(&cie_id,ptr);
	if (cie_id != DW_CIE_ID)
		throw Dwarf_Error_Frame("bad version stamp for frame");

	ptr += dd_lsize;

	// Read the version.
	version = *(Dwarf_Small *)ptr;
	ptr++;
	if (version != DW_CIE_VERSION)
		throw Dwarf_Error_Frame("bad version stamp for frame");

	// At this point, ptr is pointing at the augmentation string.
	return ptr;
}

//-------------------------------------------------------------------
// read all FDE and CIE entry
//-------------------------------------------------------------------

void Dwarf_Debug::read_fde_cie_table() throw(Dwarf_Error)
{
	Dwarf_Small		*frame_ptr;	// scan .debuf_frame section
	Dwarf_Small		*start_frame_ptr;	// pointer to start of current CIE or FDE

		// fields for current CIE
	Dwarf_Unsigned  length;
	Dwarf_Unsigned  offset;
	Dwarf_Small     version;
	Dwarf_Small     *augmentation;
	Dwarf_Word      code_alignment_factor;
	Dwarf_Sword     data_alignment_factor;
	Dwarf_Small     return_address_register;

		// fields for current FDE
	Dwarf_Addr      initial_location;
	Dwarf_Addr      address_range;

		// temporal list of CIE being read
	Dwarf_Cie       *new_cie;
	Dwarf_Cie       *head_cie_ptr = NULL;
	Dwarf_Cie       *cur_cie_ptr;
	Dwarf_Word      cie_count = 0;

		// temporal list of FDE being read
	Dwarf_Fde       *new_fde;
	Dwarf_Fde       *head_fde_ptr = NULL;
	Dwarf_Fde       *cur_fde_ptr;
	Dwarf_Word      fde_count = 0;

	frame_ptr = dd_debug_frame;

	if (frame_ptr == NULL) return;

	try {

		while (frame_ptr < (dd_debug_frame + dd_debug_frame_size)) {
			start_frame_ptr = frame_ptr;

			read(&length,frame_ptr);
			frame_ptr += dd_lsize;

			if ((length % dd_lsize) != 0)
				throw Dwarf_Error_Frame(Dwarf::DWARFERR,"error in length of frame");

			read(&offset,frame_ptr);
			frame_ptr += dd_lsize;
			if (offset == DW_CIE_ID) {	// if CIE entry

				version = *(Dwarf_Small *)frame_ptr;
				frame_ptr++;

				if (version != DW_CIE_VERSION)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"bad version stamp for frame CIE");

				augmentation = frame_ptr;
				frame_ptr = frame_ptr + strlen((char *)frame_ptr) + 1;
				if (strcmp((char *)augmentation,Dwarf::DW_DEBUG_FRAME_AUGMENTER_STRING) == 0 ||
					strcmp((char *)augmentation,Dwarf::DW_EMPTY_STRING) == 0) {

					code_alignment_factor = Dwarf::decode_leb128_uword(frame_ptr);
					data_alignment_factor = Dwarf::decode_leb128_uword(frame_ptr);

					return_address_register = *(Dwarf_Small *)frame_ptr;
					if (return_address_register > DW_FRAME_LAST_REG_NUM)
						throw Dwarf_Error_Cie(Dwarf::DWARFERR,
							"bad register specified for return address");
					frame_ptr++;

				}
				else {
					// we don't understand the augmentation string.
					// Can't read other field

					frame_ptr = start_frame_ptr + length + dd_lsize;

					// make dummy CIE
				}

				new_cie = new Dwarf_Cie(
												length,
												(char *)augmentation,
												code_alignment_factor,
												data_alignment_factor,
												return_address_register,
												start_frame_ptr,
												frame_ptr,
												this
												);
				cie_count++;

				if (head_cie_ptr == NULL)
					head_cie_ptr = cur_cie_ptr = new_cie;
				else {
					cur_cie_ptr->next = new_cie;
					cur_cie_ptr = new_cie;
				}

			}	// end of CIE entry
			else {	// if FDE entry

				Dwarf_Small *initloc = frame_ptr;

				read(&initial_location,frame_ptr);
				frame_ptr += dd_lsize;

				read(&address_range,frame_ptr);
				frame_ptr += dd_lsize;

				augmentation = get_augment_string(
                            (Dwarf_Small *)(dd_debug_frame + offset));

				if ((strcmp(
                            (char *) augmentation, 
                            Dwarf::DW_DEBUG_FRAME_AUGMENTER_STRING) != 0) &&

                   (strcmp(
                            (char *) augmentation, 
                            Dwarf::DW_EMPTY_STRING) != 0)) {

					 // don't understand augmentation
					 // m.b. do anything ??
				}

				new_fde = new Dwarf_Fde(
												length,
												offset,
												initial_location,
												initloc,
												address_range,
												start_frame_ptr,
												frame_ptr,
												this
												);
				fde_count++;
				if (head_fde_ptr == NULL)
					 head_fde_ptr = cur_fde_ptr = new_fde;
				else {
					 cur_fde_ptr->next = new_fde;
					 cur_fde_ptr = new_fde;
				}
			}	// end of FDE entry

				// skip to start of next frame
			frame_ptr = start_frame_ptr + length + dd_lsize;

		}	// end of while
	}		// end of try
	catch (Dwarf_Error) {
		if (head_cie_ptr) {
			cur_cie_ptr = head_cie_ptr;
			while(cur_cie_ptr) {
				cur_cie_ptr = head_cie_ptr->next;
				delete head_cie_ptr;
			}
		}
		if (head_fde_ptr) {
			cur_fde_ptr = head_fde_ptr;
			while(cur_fde_ptr) {
				cur_fde_ptr = head_fde_ptr->next;
				delete head_fde_ptr;
			}
		}
		throw;
	}

	// now transfer lists of CIE and FDE into table

	try {
		if (cie_count == 0)
			throw Dwarf_Error_Frame_Found(Dwarf::DWARFERR,
                                            "CIE entry not found");
		dd_cie_data = new Dwarf_Cie_Tab(cie_count,this);
		dd_cie_data->convert_list(head_cie_ptr);
	}
	catch (Dwarf_Error) {
		if (dd_cie_data) delete dd_cie_data;
		throw;
	}

	try {
    	if (fde_count == 0)
	    	throw Dwarf_Error_Frame_Found(Dwarf::DWARFERR,
                                            "FDE entry not fount");

		dd_fde_data = new Dwarf_Fde_Tab(fde_count,this);
		dd_fde_data->convert_list(head_fde_ptr,dd_cie_data);
	}
	catch (Dwarf_Error) {
       	if (dd_fde_data) delete dd_fde_data;
	}

}

//-------------------------------------------------------------------
// private function for execute frame operations
//-------------------------------------------------------------------

Dwarf_Frame_Tab *Dwarf_Debug::exec_frame_instr(
	Dwarf_Bool	make_instr,
	Dwarf_Bool	search_pc,
	Dwarf_Addr	search_pc_val,
	Dwarf_Addr	loc,
	Dwarf_Small	*start_instr_ptr,
	Dwarf_Small	*final_instr_ptr,
	Dwarf_Frame	*table,
	Dwarf_Cie	*cie
	) throw(Dwarf_Error)
{
	// pointer to the frame instructions.
	Dwarf_Small     *instr_ptr;

	Dwarf_Small     instr, opcode;
	Dwarf_Small     reg_no, reg_noA, reg_noB;
	Dwarf_Unsigned  factored_N_value;
	Dwarf_Addr      new_loc;
	Dwarf_Unsigned  adv_loc;

	Dwarf_Reg_Rule  reg[DW_FRAME_LAST_REG_NUM];

	// This is used to end executing frame instructions.
	// Becomes True when search_pc is True and loc
	// is greater than search_pc_val.
	Dwarf_Bool		search_over = False;

	// Used by the DW_FRAME_advance_loc instr
	// to hold the increment in pc value.
	Dwarf_Addr		adv_pc;

	// Contains the length in bytes of
	// an leb128 encoded number.
	Dwarf_Word     leb128_length;

	// Counts the number of frame instructions executed.
	Dwarf_Word     instr_count = 0;

	//	These contain the current fields
	//	of the current frame instruction.

	Dwarf_Small     fp_base_op = 0;
    USED(fp_base_op);
	Dwarf_Small     fp_extended_op;
	Dwarf_Half      fp_register;
	Dwarf_Unsigned  fp_offset;
	Dwarf_Off       fp_instr_offset;

	//	 Stack_table points to the row (Dwarf_Frame ie) being
	//	 pushed or popped by a remember or restore instruction.
	//	 Top_stack points to the top of the stack of rows.

	Dwarf_Frame       *stack_table;
	Dwarf_Frame       *top_stack = NULL;

	//		These are used only when make_instr is True.
	//	Curr_instr is a pointer to the current frame
	//	instruction executed.  Curr_instr_ptr,
	//	head_instr_list, and curr_instr_list are used
	//	to form a chain of Dwarf_Frame_Op structs.
	//	Dealloc_instr_ptr is used to deallocate the
	//	structs used to form the chain.  Head_instr_block
	//	points to a contiguous list of pointers to the
	//	Dwarf_Frame_Op structs executed.

	Dwarf_Frame_Tab	*instr_table;

	Dwarf_Frame_Op    *curr_instr;
	Dwarf_Frame_Op    *head_instr_chain = NULL;
	Dwarf_Frame_Op    *tail_instr_chain = NULL;


	// These are the alignment_factors taken from the
	// Cie provided.  When no input Cie is provided they
	// are set to 1, because only factored offsets are
	// required.

	Dwarf_Sword            code_alignment_factor = 1;
	Dwarf_Sword            data_alignment_factor = 1;

	// This flag indicates when an actual alignment factor
	//	 is needed.  So if a frame instruction that computes
	//	 an offset using an alignment factor is encountered
	//	 when this flag is set, an error is returned because
	//	 the Cie did not have a valid augmentation.

	Dwarf_Bool              need_augmentation = False;

	Dwarf_Word              i;

	// Initialize first row from associated Cie.
	if (cie != NULL && cie->dc_initial_table != NULL) {
		for (i = 0; i < DW_FRAME_LAST_REG_NUM; i++)
			reg[i] = cie->dc_initial_table->df_reg[i];
	}

    //  The idea here is that the code_alignment_factor and
    //  data_alignment_factor which are needed for certain
    //  instructions are valid only when the Cie has a proper
    //  augmentation string.  So if the augmentation is not
    //  right, only Frame instruction can be read.

	if (cie != NULL && cie->dc_augmentation != NULL) {
		code_alignment_factor = cie->dc_code_alignment_factor;
		data_alignment_factor = cie->dc_data_alignment_factor;
	}
	else need_augmentation = !make_instr;

	instr_ptr = start_instr_ptr;
	while (instr_ptr < final_instr_ptr && !search_over) {

		fp_instr_offset = instr_ptr - start_instr_ptr;
		instr = *(Dwarf_Small *)instr_ptr;
		instr_ptr = instr_ptr + sizeof(Dwarf_Small);

		fp_base_op = (Dwarf_Small)((instr & 0xc0)>>6);
		if ((instr & 0xc0) == 0x00) {
            opcode = instr; // is really extended op
            fp_extended_op = (Dwarf_Small)((instr & (~(0xc0))) & 0xff);
		} else {
			opcode = (Dwarf_Small)(instr & 0xc0); // is base op
			fp_extended_op = 0;
		}

		fp_register = 0;
		fp_offset = 0;
		switch (opcode) {

			case DW_CFA_advance_loc : { // base op
				fp_offset = adv_pc = instr & DW_FRAME_INSTR_OFFSET_MASK;

				if (need_augmentation)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"unknown augmentation in CIE");

				adv_pc = adv_pc * code_alignment_factor;

				search_over = search_pc && (loc+adv_pc > search_pc_val);
				// If gone past pc needed, retain old pc.
				if (!search_over) loc = loc + adv_pc;
				break;
			}

			case DW_CFA_offset : { // base op
				reg_no = Dwarf_Small(instr & DW_FRAME_INSTR_OFFSET_MASK);
				if (reg_no > DW_FRAME_LAST_REG_NUM)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"register number too high");

				factored_N_value =
					Dwarf::decode_u_leb128(instr_ptr,leb128_length);
				instr_ptr = instr_ptr + leb128_length;

				fp_register = reg_no;
				fp_offset = factored_N_value;

				if (need_augmentation)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"unknown augmentation in CIE");

				reg[reg_no].drr_is_off = 1;
				reg[reg_no].drr_register = DW_FRAME_CFA_COL;
				reg[reg_no].drr_offset = factored_N_value *
					data_alignment_factor;

				break;
			}

			case DW_CFA_restore : { // base op
                reg_no = Dwarf_Small(instr & DW_FRAME_INSTR_OFFSET_MASK);
				if (reg_no > DW_FRAME_LAST_REG_NUM)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"register number too high");

				fp_register = reg_no;

				if (cie != NULL && cie->dc_initial_table != NULL)
					reg[reg_no] = cie->dc_initial_table->df_reg[reg_no];
				else
					if (!make_instr)
						throw Dwarf_Error_Frame(Dwarf::DWARFERR,"no init value to restore");

				break;
			}
			case DW_CFA_set_loc : {
				read(&new_loc, instr_ptr);
				instr_ptr += dd_lsize;

				if (new_loc <= loc)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"new location less when old location");

				search_over = search_pc && (new_loc > search_pc_val);

				// If gone past pc needed, retain old pc.
				if (!search_over) loc = new_loc;
				fp_offset = new_loc;
				break;
			}

			case DW_CFA_advance_loc1 : {
				fp_offset = adv_loc = *(Dwarf_Small *)instr_ptr;
				instr_ptr = instr_ptr + sizeof(Dwarf_Small);

				if (need_augmentation)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"unknown augmentation in CIE");

				adv_loc *= code_alignment_factor;

				search_over = search_pc &&
					(loc + adv_loc > search_pc_val);

				// If gone past pc needed, retain old pc.
				if (!search_over) loc = loc + adv_loc;
				break;
			}

			case DW_CFA_advance_loc2 : {
				Dwarf_Half half_loc;
				read_2(&half_loc, instr_ptr);
				instr_ptr += sizeof(Dwarf_Half);
				adv_loc = half_loc;
				fp_offset = adv_loc;

				if (need_augmentation)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"unknown augmentation in CIE");

				adv_loc *= code_alignment_factor;

				search_over = search_pc &&
					(loc+adv_loc > search_pc_val);

				// If gone past pc needed, retain old pc.
				if (!search_over) loc = loc + adv_loc;
				break;
			}

			case DW_CFA_advance_loc4 : {
				read(&adv_loc, instr_ptr);
				instr_ptr += sizeof(Dwarf_Word);

				fp_offset = adv_loc;

				if (need_augmentation)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"unknown augmentation in CIE");

				adv_loc *= code_alignment_factor;

				search_over = search_pc &&
					(loc+adv_loc > search_pc_val);

				// If gone past pc needed, retain old pc.
				if (!search_over) loc = loc + adv_loc;
				break;
			}

			case DW_CFA_offset_extended : {
				 reg_no = Dwarf_Small(Dwarf::decode_leb128_uword(instr_ptr));

				if (reg_no > DW_FRAME_LAST_REG_NUM)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"register number too high");

				factored_N_value = Dwarf::decode_u_leb128(instr_ptr,leb128_length);
				instr_ptr = instr_ptr + leb128_length;

				if (need_augmentation)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"unknown augmentation in CIE");

				reg[reg_no].drr_is_off = 1;
				reg[reg_no].drr_register = DW_FRAME_CFA_COL;
				reg[reg_no].drr_offset = factored_N_value * data_alignment_factor;

				fp_register = reg_no;
				fp_offset = factored_N_value;
				break;
			}

			case DW_CFA_restore_extended : {
                reg_no = Dwarf_Small(Dwarf::decode_leb128_uword(instr_ptr));
				if (reg_no > DW_FRAME_LAST_REG_NUM)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"register number too high");

				if (cie != NULL && cie->dc_initial_table != NULL) {
					reg[reg_no] =
					cie->dc_initial_table->df_reg[reg_no];
				} else {
					if (!make_instr)
						throw Dwarf_Error_Frame(Dwarf::DWARFERR,"no init value to restore");
				}

				fp_register = reg_no;
				break;
			}
			case DW_CFA_undefined : {
                reg_no = Dwarf_Small(Dwarf::decode_leb128_uword(instr_ptr));
				if (reg_no > DW_FRAME_LAST_REG_NUM)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"register number too high");

				reg[reg_no].drr_is_off = 0;
				reg[reg_no].drr_register = DW_FRAME_UNDEFINED_VAL;
				reg[reg_no].drr_offset = 0;

				fp_register = reg_no;
				break;
			}

			case DW_CFA_same_value : {
                reg_no = Dwarf_Small(Dwarf::decode_leb128_uword(instr_ptr));
				if (reg_no > DW_FRAME_LAST_REG_NUM)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"register number too high");

				reg[reg_no].drr_is_off = 0;
				reg[reg_no].drr_register = DW_FRAME_SAME_VAL;
				reg[reg_no].drr_offset = 0;
				fp_register = reg_no;
				break;
			}

			case DW_CFA_register : {
				reg_noA = Dwarf_Small(Dwarf::decode_leb128_uword(instr_ptr));
				if (reg_noA > DW_FRAME_LAST_REG_NUM)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"register number too high");

				reg_noB = Dwarf_Small(Dwarf::decode_leb128_uword(instr_ptr));
				if (reg_noB > DW_FRAME_LAST_REG_NUM)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"register number too high");

				reg[reg_noA].drr_is_off = 0;
				reg[reg_noA].drr_register = reg_noB;
				reg[reg_noA].drr_offset = 0;

				fp_register = reg_noA;
				fp_offset = reg_noB;
				break;
			}
			case DW_CFA_remember_state : {
				stack_table = new Dwarf_Frame;

				for (i = 0; i < DW_FRAME_LAST_REG_NUM; i++)
					stack_table->df_reg[i] = reg[i];

				if (top_stack != NULL)
					stack_table->next = top_stack;
				top_stack = stack_table;

				break;
			}

			case DW_CFA_restore_state : {
				if (top_stack == NULL)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"pop on empty stack ");

				stack_table = top_stack;
				top_stack = stack_table->next;

				for (i = 0; i < DW_FRAME_LAST_REG_NUM; i++)
					reg[i] = stack_table->df_reg[i];

				delete stack_table;
				break;
			}
			case DW_CFA_def_cfa : {

				reg_no = Dwarf_Small(Dwarf::decode_leb128_uword(instr_ptr));
				if (reg_no > DW_FRAME_LAST_REG_NUM)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"register number too high");

				factored_N_value = Dwarf::decode_u_leb128(instr_ptr,leb128_length);
				instr_ptr = instr_ptr + leb128_length;

				if (need_augmentation)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"unknown augmentation in CIE");

				reg[DW_FRAME_CFA_COL].drr_is_off = 1;
				reg[DW_FRAME_CFA_COL].drr_register = reg_no;
				reg[DW_FRAME_CFA_COL].drr_offset = factored_N_value;

				fp_register = reg_no;
				fp_offset = factored_N_value;
				break;
			}

			case DW_CFA_def_cfa_register : {

				reg_no = Dwarf_Small(Dwarf::decode_leb128_uword(instr_ptr));
				if (reg_no > DW_FRAME_LAST_REG_NUM)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"register number too high");

				reg[DW_FRAME_CFA_COL].drr_is_off = 0;
				reg[DW_FRAME_CFA_COL].drr_register = reg_no;
				reg[DW_FRAME_CFA_COL].drr_offset = 0;
				fp_register = reg_no;
				break;
			}
			case DW_CFA_def_cfa_offset : {
				factored_N_value = Dwarf::decode_u_leb128(instr_ptr,leb128_length);
				instr_ptr = instr_ptr + leb128_length;

				if (need_augmentation)
					throw Dwarf_Error_Frame(Dwarf::DWARFERR,"unknown augmentation in CIE");
				reg[DW_FRAME_CFA_COL].drr_offset = factored_N_value;

				fp_offset = factored_N_value;
				break;
			}

			case DW_CFA_nop : {
				break;
			}
		}

		if (make_instr) {
			instr_count++;

			curr_instr = new Dwarf_Frame_Op(
													fp_base_op,
													fp_extended_op,
													fp_register,
													fp_offset,
													fp_instr_offset
													);

			if (head_instr_chain == NULL)
				head_instr_chain = tail_instr_chain = curr_instr;
			else {
				tail_instr_chain->next = curr_instr;
				tail_instr_chain = curr_instr;
			}
		}
	}

	//	If frame instruction decoding was right
	//	we would stop exactly at final_instr_ptr.

	if (instr_ptr > final_instr_ptr)
		throw Dwarf_Error_Frame(Dwarf::DWARFERR,"Frame operations decoding error");

	// Create the last row generated.
	if (table != NULL) {
		 table->df_loc = loc;
		 for (i = 0; i < DW_FRAME_LAST_REG_NUM; i++)
			  table->df_reg[i] = reg[i];
	}

	// Dealloc anything remaining on stack.
	for (; top_stack != NULL; ) {
		 stack_table = top_stack;
		 top_stack = top_stack->next;
		 delete stack_table;
	}

	if (make_instr) {
		 // Allocate list of pointers to Dwarf_Frame_Op's.
		 instr_table = new Dwarf_Frame_Tab(instr_count);

		 instr_table->convert_list(head_instr_chain);

		 return instr_table;

	}
	return NULL;
}

//-------------------------------------------------------------------
// внутренн€€ функци€. читает информацию о глобальных символах
//-------------------------------------------------------------------

void Dwarf_Debug::read_global(void) throw(Dwarf_Error,Dwarf_No_Entry)
{
		 // Sweeps the complete .debug_pubnames section.
	Dwarf_Small			*pubnames_ptr;

	Dwarf_Unsigned		length;

   	// длина части секции .debug_pubname дл€ текущего CU
	Dwarf_Unsigned		pu_length;

		// смещение начала CU дл€ текущего набора globals
	Dwarf_Unsigned		pu_info_offset;

		// длина CU дл€ текущего набора globals
	Dwarf_Unsigned		pu_info_length;

		 // Points to the context for the current set of global names,
		 // and contains information to identify the compilation-unit
		 // that the set refers to.
//	Dwarf_Global_Context        pubnames_context;

		 // Version number for the current set of pubnames.
	Dwarf_Half        version;

		 // Offset from the start of compilation-unit
		 // for the current global.
	Dwarf_Off         cu_offset;

		 // Counts the number of globals read.
	Dwarf_Unsigned    global_count = 0;

		 // Points to the current global read.
	Dwarf_Global      *global;

		 // Used to chain the Dwarf_Global_s structs for creating
		 // contiguous list of pointers to the structs.
	Dwarf_Global      *curr_chain = NULL;
    Dwarf_Global      *prev_chain = NULL;
    Dwarf_Global      *head_chain = NULL;

		 // Points to contiguous block of Dwarf_Global's to be returned.
//	Dwarf_Global_Tab	*ret_globals;

	// ---------- BEGIN CODE ----------

	if (dd_debug_pubnames == NULL)
		throw Dwarf_No_Entry();

	pubnames_ptr = dd_debug_pubnames;
	do {
		read(&length, pubnames_ptr);
		pubnames_ptr += dd_lsize;
		pu_length = length;

		read_2(&version, pubnames_ptr);
		pubnames_ptr += sizeof(Dwarf_Half);
		if (version != CURRENT_VERSION_STAMP)
			throw Dwarf_Error_Global(Dwarf::DWARFERR,
				"version stamp of pubnames incorrect");

		read(&pu_info_offset, pubnames_ptr);
		pubnames_ptr += dd_lsize;

		read(&pu_info_length, pubnames_ptr);
		pubnames_ptr += dd_lsize;

		if (pubnames_ptr > dd_debug_pubnames + dd_debug_pubnames_size)
			throw Dwarf_Error_Global(Dwarf::DWARFERR,
				"read pubnames past end of .debug_pubnames");

		read(&cu_offset, pubnames_ptr);
		pubnames_ptr += dd_lsize;

		while (cu_offset != 0) {

			global = new Dwarf_Global(
				length,			 // длина части секции .debug_pubnames относ€ща€с€ к текущему CU
				pu_info_offset, // смещение начала текущего CU в секции .debug_info
				pu_length,		 // длина текущего CU в секции .debug_info
				cu_offset,		 // смещение в текущем CU
				pubnames_ptr	 // им€ глобального символа
				);

			global_count++;

			pubnames_ptr = pubnames_ptr + strlen((char *)pubnames_ptr) + 1;

			read(&cu_offset, pubnames_ptr);
			pubnames_ptr += dd_lsize;

			if (pubnames_ptr > dd_debug_pubnames + dd_debug_pubnames_size)
				throw Dwarf_Error_Global(Dwarf::DWARFERR,
					"read pubnames past end of .debug_pubnames");

			curr_chain = global;

				  // Put current global on singly_linked list.
			if (head_chain == NULL)
				head_chain = prev_chain = curr_chain;
			else {
				prev_chain->next = curr_chain;
				prev_chain = curr_chain;
			}
		}

	} while
		 (pubnames_ptr < dd_debug_pubnames + dd_debug_pubnames_size);

		 // Points to table block of Dwarf_Global's
	dd_global_tab = new Dwarf_Global_Tab(global_count,this);
	dd_global_tab->convert_list(head_chain);
}

//-------------------------------------------------------------------
// внутренн€€ функци€. читает информацию о диапазонах адресов
//-------------------------------------------------------------------

void Dwarf_Debug::read_arange(void) throw(Dwarf_Error,Dwarf_No_Entry)
{
		 // Sweeps the .debug_aranges section.
	Dwarf_Small         *arange_ptr;

		 // Start of arange header.  Used for rounding offset of
		 // arange_ptr to twice the tuple size.  Libdwarf requirement.
	Dwarf_Small         *header_ptr;

		 // Length of current set of aranges.
	Dwarf_Unsigned      length;

		 // Version of .debug_aranges header.
	Dwarf_Half          version;

		 // Offset of current set of aranges into .debug_info.
	Dwarf_Off           info_offset;

		 // Size in bytes of addresses in target.
	Dwarf_Small         address_size;

		 // Size in bytes of segment offsets in target.
	Dwarf_Small         segment_size;

	Dwarf_Small         remainder;

		 // Count of total number of aranges.
	Dwarf_Unsigned      arange_count = 0;

		 // Start address of arange.
	Dwarf_Addr          range_address;

		 // Length of arange.
	Dwarf_Unsigned      range_length;

	Dwarf_Arange        	*arange;
//	Dwarf_Arange			*arange_block;

//	Dwarf_Unsigned      i;

		 // Used to chain Dwarf_Aranges structs.
	Dwarf_Arange 		*curr_chain = NULL;
	Dwarf_Arange		*prev_chain = NULL;
	Dwarf_Arange		*head_chain = NULL;

	// ---------- BEGIN CODE ----------

	Dwarf_Debug *dbg = this;

	if (dbg->dd_debug_aranges == NULL)
		 throw Dwarf_No_Entry();

	arange_ptr = dbg->dd_debug_aranges;
	do {
		 header_ptr = arange_ptr;

			  // Length of aranges for this compilation-unit.
		 dbg->read(&length, arange_ptr);
		 arange_ptr += dbg->dd_lsize;

		 dbg->read_2(&version, arange_ptr);
		 arange_ptr += sizeof(Dwarf_Half);
		 length = length - sizeof(Dwarf_Half);

		 if (version != CURRENT_VERSION_STAMP)
			throw Dwarf_Error_Arange(Dwarf::DWARFERR,"bad version stamp");

		 dbg->read(&info_offset, arange_ptr);
		 arange_ptr += dbg->dd_lsize;
		 length = length - dbg->dd_lsize;

		 if (info_offset >= dbg->dd_debug_info_size)
			throw Dwarf_Error_Arange(Dwarf::DWARFERR,
				"offset into .debug_info in .debug_aranges bad");

		 address_size = *(Dwarf_Small *)arange_ptr;
		 arange_ptr = arange_ptr + sizeof(Dwarf_Small);
		 length = length - sizeof(Dwarf_Small);

		 segment_size = *(Dwarf_Small *)arange_ptr;
		 arange_ptr = arange_ptr + sizeof(Dwarf_Small);
		 length = length - sizeof(Dwarf_Small);

		 if (segment_size != 0)
			throw Dwarf_Error_Arange(Dwarf::DWARFERR,
				"segment size should be 0 for neurochip");

			  // Round arange_ptr offset to next multiple of address_size.
		 remainder = Dwarf_Small((arange_ptr-header_ptr) % (2 * address_size));
		 if (remainder != 0) {
			  arange_ptr = arange_ptr + (2*address_size) - remainder;
			  length = length - ((2*address_size) - remainder);
		 }
		 do {
			  dbg->read(&range_address, arange_ptr);
			  arange_ptr += dbg->dd_lsize;

			  length = length - dbg->dd_lsize;

			  dbg->read(&range_length, arange_ptr);
			  arange_ptr += dbg->dd_lsize;
			  length = length - dbg->dd_lsize;

			  if (range_address != 0 || range_length != 0) {

					arange = new Dwarf_Arange(range_address,range_length,info_offset,this);

					arange_count++;

					curr_chain = arange;

					if (head_chain == NULL)
						 head_chain = prev_chain = curr_chain;
					else {
						 prev_chain->next = curr_chain;
						 prev_chain = curr_chain;
					}
			  }
		 } while (range_address != 0 || range_length != 0);

		 if (length != 0)
			throw Dwarf_Error_Arange(Dwarf::DWARFERR,
				"length of arange section in .debug_aranges bad");

	} while (arange_ptr < dbg->dd_debug_aranges + dbg->dd_debug_aranges_size);

	if (arange_ptr != dbg->dd_debug_aranges + dbg->dd_debug_aranges_size)
		throw Dwarf_Error_Arange(Dwarf::DWARFERR,
			"aranges do not end at end of .debug_aranges");

	dd_arange_tab = new Dwarf_Arange_Tab(arange_count);
	dd_arange_tab->convert_list(head_chain);

}

//-------------------------------------------------------------------
// end of internal Dwarf_Debug function
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// public Dwarf_Debug function
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// get next compilation unit
//-------------------------------------------------------------------

Dwarf_CU *Dwarf_Debug::next_cu(Dwarf_CU *cu) throw(Dwarf_Error)
{
	if (cu == NULL) return dd_cu_list;
	if (cu->dc_debug != this)
		throw Dwarf_Error_CU("Dwarf error - ","debug CU mismatch");
	return cu->next;
}

//-------------------------------------------------------------------
// get DIE for offset in section .debug_info
//-------------------------------------------------------------------

Dwarf_Die *Dwarf_Debug::offdie(Dwarf_Off offset) throw(Dwarf_No_Entry)
{
	Dwarf_CU *cur_cu = cu_include_off(offset);

   return cur_cu->off_cu_die(offset - cur_cu->dc_debug_info_offset);
}

//-------------------------------------------------------------------
// get CU for offset in section .debug_info
//-------------------------------------------------------------------

Dwarf_CU *Dwarf_Debug::offcu(Dwarf_Off offset) throw(Dwarf_No_Entry)
{
	Dwarf_CU *cur_cu = dd_cu_list;

	while(cur_cu) {
		if (offset == cur_cu->dc_debug_info_offset)
			return(cur_cu);

        cur_cu = cur_cu->next;
	}
	throw Dwarf_No_Entry();
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return 0;
#endif
}

//-------------------------------------------------------------------
// get CU that include offset in section .debug_info
//-------------------------------------------------------------------

Dwarf_CU *Dwarf_Debug::cu_include_off(Dwarf_Off offset) throw(Dwarf_No_Entry)
{
    Dwarf_CU *cur_cu = dd_cu_list;

    while(cur_cu) {
        if (offset >= cur_cu->dc_debug_info_offset &&
                    offset < cur_cu->dc_debug_info_offset +
                    cur_cu->dc_length + dd_lsize)
            return(cur_cu);

        cur_cu = cur_cu->next;
    }
    throw Dwarf_No_Entry();
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return 0;
#endif
}

//-------------------------------------------------------------------
// get table of CIE entries from section .debuf_frame
//-------------------------------------------------------------------

Dwarf_Cie_Tab *Dwarf_Debug::get_cieinfo() throw(Dwarf_No_Entry)
{
    if (dd_cie_data == NULL) throw Dwarf_No_Entry();
	return dd_cie_data;
}

//-------------------------------------------------------------------
// get table of FDE entries from section .debug_frame
//-------------------------------------------------------------------

Dwarf_Fde_Tab *Dwarf_Debug::get_fdeinfo() throw(Dwarf_No_Entry)
{
    if (dd_fde_data == NULL) throw Dwarf_No_Entry();

	return dd_fde_data;
}

//-------------------------------------------------------------------
//
//-------------------------------------------------------------------

Dwarf_Global_Tab *Dwarf_Debug::get_globalinfo() throw(Dwarf_Error,Dwarf_No_Entry)
{
	if (dd_global_tab == NULL)
		read_global();

	return dd_global_tab;
}

//-------------------------------------------------------------------
//
//-------------------------------------------------------------------

Dwarf_Arange_Tab *Dwarf_Debug::get_arangeinfo() throw(Dwarf_Error,Dwarf_No_Entry)
{
	if (dd_arange_tab == NULL)
		read_arange();

	return dd_arange_tab;
}

//-------------------------------------------------------------------
// get abbreviation entry (for internal level interface)
// not yet realised
//-------------------------------------------------------------------
/*
Dwarf_Abbrev *Dwarf_Debug::next_abbrev(Dwarf_Abbrev *abbrev)
{
	USED(abbrev);
	throw Dwarf_Error_Internal(Dwarf::DWARFERR,
		"low-level abbreviation access not yet realised");
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return 0;
#endif
}
*/
