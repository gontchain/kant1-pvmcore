//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//               Реализационный модуль pro_dbg.cpp                      //
//                                                                      //
//  Файл реализации функций класса Dwarf_P_Debug                        //
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
// class Dwarf_P_Debug
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
#include "pro_dbg.h"
#include "pro_mac.h"

Dwarf_P_Debug::Dwarf_P_Debug( Dwarf_Small encode ) throw(Dwarf_Error) 
    : dpd_head_cu_list(NULL),
	dpd_end_cu_list(NULL),dpd_debug_sects(NULL),dpd_last_debug_sect(NULL),
	dpd_n_debug_sect(0),dpd_frame_cies(NULL),dpd_n_cie(0),dpd_frame_fdes(NULL),
	dpd_n_fde(0),dpd_last_fde(NULL),dpd_func(NULL),dpd_func_addr(NULL),dpd_func_ref(NULL),
	dpd_current_abbrev_offset(0),dpd_current_info_offset(0),dpd_next_line_offset(0),
	dpd_strings(NULL),dpd_first_macinfo(NULL),dpd_macinfo_count(0),
    dpd_encode( encode )
// ,elf(p_elf) // убрано 15.10.97 Ч.А.
{
    /* Убрано 15.10.97
	try {
		dpd_encode = elf->GetEhdr()->e_ident[EI_DATA];
	}
	catch(ELF_ERROR e) {
		throw Dwarf_Error_Pro_Elf(e);
	}
    */
}

Dwarf_P_Debug::~Dwarf_P_Debug() throw(Dwarf_Error)
{
	if (dpd_head_cu_list) delete dpd_head_cu_list;

	if (dpd_debug_sects) {
		Dwarf_P_Section_Data *ptr;
		while(dpd_debug_sects) {
			ptr = dpd_debug_sects->next;
			delete dpd_debug_sects;
         dpd_debug_sects = ptr;
		}
	}

	if (dpd_frame_cies) delete dpd_frame_cies;

	if (dpd_frame_fdes) delete dpd_frame_fdes;

//   if () delete;
}

Dwarf_Signed Dwarf_P_Debug::transform_to_disk(
				Dwarf_Callback_Section 	section_func,
				Dwarf_Callback_Addr     addr_func,
				Dwarf_Callback_Ref		ref_func
		) throw(Dwarf_Error)
{
		// Section data in written out in a number of
		// buffers. Each _generate_*() function returns
		// a cumulative count of buffers for all the
		// sections. get_section_bytes() returns these
		// buffers one at a time
	int	nbufs = 0;
	USED(nbufs);

		// Loop for all sections, and create section headers
	int   sect;

		// Index of section name into SYMTAB
		// to be passed to call back routine
	Dwarf_Unsigned name_idx;

    dpd_func = section_func;
    dpd_func_addr = addr_func;
    dpd_func_ref = ref_func;

		// Create dwarf section headers
	for (sect = 0; sect < NUM_DEBUG_SECTIONS; sect++) {
		long flags = 0;
		switch (sect) {

			case DEBUG_INFO :
				if (dpd_head_cu_list == NULL) continue;
				break;

			case DEBUG_LINE :
				if (dpd_head_cu_list->dpc_lines == NULL) continue;
				break;

			case DEBUG_ABBREV :
				if (dpd_head_cu_list == NULL) continue;
				break;

			case DEBUG_FRAME :
				if (dpd_frame_cies == NULL) continue;
//				flags = 0;
				break;

			case DEBUG_ARANGES :
				if (dpd_head_cu_list->dpc_arange == NULL) continue;
				break;

			case DEBUG_PUBNAMES :
				if (dpd_head_cu_list->dpc_pubname == NULL) continue;
				break;

			case DEBUG_STR :
				 if (dpd_strings == NULL) continue;
				 break;

			case DEBUG_MACINFO :
				 if (dpd_first_macinfo == NULL) continue;
				 break;
		}

        Dwarf::elf_sects[sect] = section_func(Dwarf::sectnames[sect], SHT_PROGBITS, flags,
            SHN_UNDEF, 0, &name_idx);

        if (Dwarf::elf_sects[sect] == (-1))
            throw Dwarf_Error_Pro_Elf("can't create elf section ",Dwarf::sectnames[sect]);

        Dwarf::sect_name_idx[sect] = name_idx;
	}

		//	Changing the order in which the sections are generated
		//	may cause problems because of relocations.

	nbufs = generate_debugline(dpd_head_cu_list);
	USED(nbufs);

	nbufs = generate_debugframe();
	USED(nbufs);

	nbufs = transform_macro_info_to_disk();
	USED(nbufs);

  	dpd_current_abbrev_offset = 0;   // offset for current CU information
	dpd_current_info_offset = 0;     // offset for current CU information

	nbufs = generate_debuginfo(dpd_head_cu_list);
	USED(nbufs);

//   dpd_current_aranges_offset = 0;  // offset for current CU information
	nbufs = transform_arange_to_disk(dpd_head_cu_list);
	USED(nbufs);

	nbufs = transform_pubname_to_disk(dpd_head_cu_list);

	return nbufs;
}

//---------------------------------------------------------------------
// Выдать буфер данных секции.
// section_idx это Elf индекс секции которой принадлежат данные.
// length возвращает длину возвращаемых данных
//---------------------------------------------------------------------

Dwarf_Ptr Dwarf_P_Debug::get_section_bytes(
		Dwarf_Signed 	dwarf_section,
		Dwarf_Signed 	*elf_section,
		Dwarf_Unsigned	*length) throw()
{
	Dwarf_Ptr buf;

	if(dpd_debug_sects == NULL) {
		return NULL;	// данных больше нет !
	}

	USED(dwarf_section);
	*elf_section = dpd_debug_sects->dpsd_elf_sect_no;
	*length = dpd_debug_sects->dpsd_nbytes;
	buf = (Dwarf_Ptr *)dpd_debug_sects->dpsd_data;

	Dwarf_P_Section_Data *ptr = dpd_debug_sects;
	dpd_debug_sects = dpd_debug_sects->next;

    ptr->dpsd_data = NULL;  // данные переходят к внешнему пользователю
	delete ptr;             // поэтому удаляем только сам элемент списка

    dpd_n_debug_sect--;

    return buf;
}

void Dwarf_P_Debug::write_section_to_disk( ELF * elf ) throw(Dwarf_Error)
{
	Dwarf_Ptr buf;
	Dwarf_Signed elf_section;
	Dwarf_Unsigned length;
	Dwarf_Signed num = 0;
	ELF_SCN *scn;
	ELF_DATA *data;

	try {
		while (1) {
			buf = get_section_bytes(num++,&elf_section,&length);
			if (buf == NULL) break;

			scn = elf->GetScn(elf_section);
			data = scn->NewData();
			data->d_buf = buf;
			data->d_size = length;
			data->d_type = ELF32_T_BYTE;
			data->d_align = ELF32_T_BYTE_FSIZE;
		}

        return;
    }
    catch(Dwarf_Error&) {
   	    throw;
    }
    catch (ELF_ERROR& x) {
        throw Dwarf_Error_Elf(x);
    }
}

	// функции работы с CU

Dwarf_P_CU *Dwarf_P_Debug::new_cu() throw(Dwarf_Error)
{
	if (dpd_head_cu_list == NULL) {
		dpd_head_cu_list = new Dwarf_P_CU(this);
		dpd_end_cu_list = dpd_head_cu_list;
	}
	else {
		throw Dwarf_Error_Pro_Internal("more when one CU not yet supported");
//		dpd_end_cu_list->next = new Dwarf_P_CU(this);
//		dpd_end_cu_list = dpd_end_cu_list->next;
	}
   return dpd_end_cu_list;
}

Dwarf_P_CU *Dwarf_P_Debug::next_cu(Dwarf_P_CU *cu) const throw(Dwarf_Error)
{
	if (cu == NULL) return dpd_head_cu_list;
	if (cu->get_debug() != this)
		throw Dwarf_Error_Pro_Debug("Dwarf_P_Debug and Dwarf_P_CU mismatch");
	return cu->next;

}

	// функции работы с стеком вызовов ( FDE и CIE )

Dwarf_P_Cie	*Dwarf_P_Debug::new_cie(
							char *augmenter,
							Dwarf_Small code_align,
							Dwarf_Small data_align,
							Dwarf_Small ret_addr_reg
							) throw(Dwarf_Error)
{
	Dwarf_P_Cie *curcie;

	if (dpd_frame_cies == NULL) {
		 dpd_frame_cies = new Dwarf_P_Cie(this,DW_CIE_VERSION,augmenter,code_align,
													data_align,ret_addr_reg);

		 curcie = dpd_frame_cies;
		 dpd_n_cie = 1;
		 dpd_last_cie = curcie;
	}
	else {
		 curcie = dpd_last_cie;
		 curcie->next = new Dwarf_P_Cie(this,DW_CIE_VERSION,augmenter,code_align,
													data_align,ret_addr_reg);

		 curcie = curcie->next;
		 dpd_n_cie++;
		 dpd_last_cie = curcie;
	}
	curcie->dpc_index = dpd_n_cie;
	return curcie;
}

Dwarf_P_Fde	*Dwarf_P_Debug::new_fde(
							Dwarf_P_Cie *cie,
							Dwarf_Addr addr,
							Dwarf_Unsigned code_len,
							Dwarf_Signed sym_idx
							) throw(Dwarf_Error)
{
	Dwarf_P_Fde *fde;

	fde = new Dwarf_P_Fde(this,cie,addr,sym_idx,code_len);

	Dwarf_P_Fde *curfde;

	curfde = dpd_last_fde;
	if (curfde == NULL) {
		dpd_frame_fdes = fde;
		dpd_last_fde = fde;
		dpd_n_fde = 1;
	}
	else {
		curfde->next = fde;
		dpd_last_fde = fde;
		dpd_n_fde++;
	}
	return fde;
}

//-------------------------------------------------------------------
//
// functions for generating debug information in class Dwarf_P_Debug
//
//-------------------------------------------------------------------

Dwarf_Signed Dwarf_P_Debug::transform_macro_info_to_disk() throw(Dwarf_Error)
{
	// now not yet realised
	return dpd_n_debug_sect;
}

// Storage handler. Gets either a new chunk of memory, or
//	a pointer in existing memory, from the linked list attached
//	to this object at dpd_debug_sects, depending on size of nbytes

unsigned char *Dwarf_P_Debug::get_chunk(Dwarf_Unsigned elfsectno,Dwarf_Unsigned nbytes)
			throw(Dwarf_Error)
{
	Dwarf_P_Section_Data *cursect;

	cursect = dpd_last_debug_sect;
	if (cursect == NULL || (cursect->len() + nbytes) > CHUNK_SIZE) {

		cursect = new Dwarf_P_Section_Data(elfsectno);

		if (dpd_debug_sects == NULL) {
			dpd_debug_sects = dpd_last_debug_sect = cursect;
		}
		else {
			dpd_last_debug_sect->next = cursect;
			dpd_last_debug_sect = cursect;
		}
		dpd_n_debug_sect++;
	}
	else
		cursect = dpd_last_debug_sect;

	if (cursect->data() == NULL) {
		cursect->dpsd_data = new char[nbytes > CHUNK_SIZE ? nbytes : CHUNK_SIZE];

		cursect->dpsd_nbytes = nbytes;
		return((Dwarf_Small *)cursect->data());
	}
	else {
			// There is enough space in the current buffer
		cursect->dpsd_nbytes += nbytes;
		return((Dwarf_Small *)(cursect->data() + cursect->len() - nbytes));
	}
}

			// выдает указатель на память размером nbytes, в новом куске
unsigned char *Dwarf_P_Debug::get_new_chunk(Dwarf_Unsigned elfsectno,
	Dwarf_Unsigned nbytes) throw(Dwarf_Error)
{
	Dwarf_P_Section_Data *cursect;

	cursect = new Dwarf_P_Section_Data(elfsectno);

	if (dpd_debug_sects == NULL) {
		dpd_debug_sects = dpd_last_debug_sect = cursect;
	}
	else {
		dpd_last_debug_sect->next = cursect;
		dpd_last_debug_sect = cursect;
	}
	dpd_n_debug_sect++;

	cursect->dpsd_data = new char[nbytes > CHUNK_SIZE ? nbytes : CHUNK_SIZE];

	cursect->dpsd_nbytes = nbytes;
	return((Dwarf_Small *)cursect->data());
}

void Dwarf_P_Debug::write_reloc_section(
		  Dwarf_P_Rel *rel_head,
		  Dwarf_Signed relsectno,
		  Dwarf_Unsigned rel_nbytes
		  ) throw(Dwarf_Error)
{
	unsigned char *data;

	if (rel_nbytes != 0) {
		data = get_new_chunk(relsectno,rel_nbytes);
		while (rel_head) {

            ELF::ToF( ELF32_T_REL, (unsigned char *)data, (unsigned char *)rel_head->dpr_rel,dpd_encode, 1);
			data += sizeof(Elf32_Rel);

			rel_head = rel_head->next;
		}
	}
}

Dwarf_P_Abbrev *Dwarf_P_Debug::getabbrev(Dwarf_P_Die *die, Dwarf_P_Abbrev *head)
	throw(Dwarf_Error)
{
    Dwarf_P_Abbrev *curabbrev;
    Dwarf_P_Attribute *curattr;
    int nattrs;
    int match;
    int res1;
    Dwarf_Word *forms = NULL;
    Dwarf_Word *attrs = NULL;   // holds attr and form names

	curabbrev = head;
	while (curabbrev != NULL) {
		if ((die->dpd_tag == curabbrev->dpa_tag) &&
			((die->child() != NULL && curabbrev->dpa_children == DW_CHILDREN_yes) ||
				 (die->child() == NULL && curabbrev->dpa_children == DW_CHILDREN_no)) &&
			(die->dpd_n_attr == curabbrev->dpa_n_attr)) {     // chance of a match
			 curattr = die->dpd_attrs;
			 match = 1;      // assume match found
			 while (match && curattr) {
				  res1 = match_attr(curattr, curabbrev,curabbrev->dpa_n_attr);
				  if (res1 == 0)
						match = 0;
				  curattr = curattr->next;
			 }
			 if (match == 1) return curabbrev;
		}
		curabbrev = curabbrev->next;
	}

	// no match, create new abbreviation
	if (die->dpd_n_attr != 0) {
		forms = new Dwarf_Word[die->dpd_n_attr];
		attrs = new Dwarf_Word[die->dpd_n_attr];
	}
	nattrs = 0;
	curattr = die->dpd_attrs;
	while (curattr) {
		attrs[nattrs] = curattr->attr();
		forms[nattrs] = curattr->form();
		nattrs++;
		curattr = curattr->next;
	}

	curabbrev = new Dwarf_P_Abbrev;

	if (die->dpd_child == NULL)
		 curabbrev->dpa_children = DW_CHILDREN_no;
	else
		 curabbrev->dpa_children = DW_CHILDREN_yes;

	curabbrev->dpa_tag = die->dpd_tag;
	curabbrev->dpa_attrs = attrs;
	curabbrev->dpa_forms = forms;
	curabbrev->dpa_n_attr = die->dpd_n_attr;
	curabbrev->dpa_idx = 0;

	curabbrev->next = NULL;

	return curabbrev;
}

int Dwarf_P_Debug::match_attr(Dwarf_P_Attribute *attr,Dwarf_P_Abbrev *abbrev,
	int no_attr)
{
	int i;
	int found = 0;

	for (i = 0; i < no_attr; i++) {
		if (attr->attr() == abbrev->dpa_attrs[i] &&
									attr->form() == abbrev->dpa_forms[i]) {
			found = 1;
			break;
		}
	}
	return found;
}


//-------------------------------------------------------------------
//
// end of functions of class Dwarf_P_Debug
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// functions of class Dwarf_P_Rel
//
//-------------------------------------------------------------------

Dwarf_P_Rel::Dwarf_P_Rel() throw (Dwarf_Error) : next(NULL),dpr_rel(NULL)
{
	dpr_rel = new Elf32_Rel;
}
