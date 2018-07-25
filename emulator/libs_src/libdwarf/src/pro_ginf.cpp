//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//               Реализационный модуль pro_ginf.cpp                     //
//                                                                      //
//  Файл реализует  функцию Dwarf_P_Debug::generate_debuginfo           //
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
// class Dwarf_P_Debug.
// function generate_debuginfo() implementation
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

    // вызывается функцией Dwarf_P_Debug::transform_to_disk()

Dwarf_Signed Dwarf_P_Debug::generate_debuginfo(Dwarf_P_CU *cu) throw(Dwarf_Error)
{
    Dwarf_Unsigned elfsectno;
    unsigned char *data;
    Dwarf_Signed cu_header_size;
    Dwarf_P_Abbrev *curabbrev, *abbrev_head, *abbrev_tail;
    Dwarf_P_Die *curdie;
    Dwarf_Word dw;
    Dwarf_Ubyte db;
    Dwarf_Half version;         // need 2 byte quantity
    Dwarf_Unsigned die_off;     // offset of die in debug_info
    Dwarf_Signed n_abbrevs = 0;

    Dwarf_Unsigned name_idx;    // index of section name into SYMTAB
    int firsttime;
    Dwarf_Small *start_sec;
    Dwarf_P_Rel *rel_head;
    Dwarf_P_Rel *rel_tail;      // linked list of relocation records
    Dwarf_Signed  rel_nbytes;   // number of bytes of relocation info

    abbrev_head = abbrev_tail = NULL;
    rel_head = rel_tail = NULL;
    USED(rel_head);
    rel_nbytes = 0;
    elfsectno = Dwarf::elf_sects[DEBUG_INFO];

   if (cu == NULL) return dpd_n_debug_sect;

        // write cu header
    cu_header_size = word_size() +      // length of info section
                        sizeof(Dwarf_Half) +    // version stamp
                        off_size() +   // offset into abbrev table
                        sizeof(Dwarf_Ubyte);    // size of target address

    data = get_new_chunk(elfsectno,cu_header_size);
    start_sec = data;

    dw = 0;                     // debug_info size, now zero
    write_4(&dw,data);
    data += sizeof(Dwarf_Word);

    version = CURRENT_VERSION_STAMP;    // assume this length will not change
    write_2(&version,data);
    data += sizeof(Dwarf_Half);

    dw = dpd_current_abbrev_offset;	    // offset into abbrev table for current CU
    write_4(&dw,data);
    data += sizeof(Dwarf_Word);

    db = Dwarf_Ubyte(addr_size());
    memcpy((void *)data, (const void *)&db,1);
    data++;

    USED(data);

    curdie = cu->dpc_root;
    if ( curdie == NULL ) {
        throw Dwarf_Error_Pro_CU("CU have no DIE. Can't generate CU");
    }

        // create AT_macro_info if appropriate
    if(dpd_first_macinfo != NULL)
        curdie->add_AT_macro_info(0);

        // create AT_stmt_list attribute if necessary
    if (cu->dpc_lines != NULL)
        curdie->add_AT_stmt_list();

    die_off = cu_header_size;           // ??? + dpd_current_info_offset;

        // Relocation for abbrev offset in cu header
        // store relocation record in linked list

    rel_head = rel_tail = new Dwarf_P_Rel();
    rel_tail->set(
                        dpd_current_info_offset +
                            off_size() +            // offset for  
                            sizeof(Dwarf_Half),     // abbrev offset field
                        Dwarf_Half(Dwarf::sect_name_idx[DEBUG_ABBREV]),
                        R_NC_BYTEPTR
                        );

    rel_nbytes += ELF32_T_REL_FSIZE;

        // pass 1: create abbrev info, get die offsets, calc relocations
    while (curdie != NULL) {
        int nbytes;
        Dwarf_P_Attribute *curattr;
        char *space;
        char buff1[ENCODE_SPACE_NEEDED];

        curdie->dpd_offset = die_off;
        curabbrev = getabbrev(curdie, abbrev_head);

        if (abbrev_head == NULL) {
            n_abbrevs = 1;
            curabbrev->dpa_idx = n_abbrevs;
            abbrev_tail = abbrev_head = curabbrev;
        } else {
                // check if its a new abbreviation, if yes, add to tail
            if (curabbrev->dpa_idx == 0) {
                n_abbrevs++;
                curabbrev->dpa_idx = n_abbrevs;
                abbrev_tail->next = curabbrev;
                abbrev_tail = curabbrev;
            }
        }
        Dwarf::encode_leb128_nm(curabbrev->dpa_idx,&nbytes,buff1,sizeof(buff1));

        space = new char[nbytes];

        memcpy(space,buff1,nbytes);
        curdie->dpd_abbrev = space;
        curdie->dpd_abbrev_nbytes = nbytes;
        die_off += nbytes;
        curattr = curdie->dpd_attrs;

        while (curattr) {
            if (curattr->dpa_rel_type != R_NC_NONE) {
                    // store relocation record in linked list
                if (rel_head == NULL) {
                    rel_head = new Dwarf_P_Rel();
                    rel_tail = rel_head;
                } else {
                    rel_tail->next = new Dwarf_P_Rel();
                    rel_tail = rel_tail->next;
                    rel_tail->next = NULL;
                }
                switch (curattr->attr()) {
					case DW_AT_stmt_list:
						curattr->dpa_rel_symidx = 
                            Dwarf::sect_name_idx[DEBUG_LINE];
						break;
					case DW_AT_macro_info:
						curattr->dpa_rel_symidx = 
                            Dwarf::sect_name_idx[DEBUG_MACINFO];
						break;
					default:
						break;
				}
				rel_tail->set(
                        die_off + curattr->dpa_rel_offset 
                            + dpd_current_info_offset,
                        Dwarf_Half(curattr->dpa_rel_symidx),
                        curattr->dpa_rel_type);

				rel_nbytes += ELF32_T_REL_FSIZE;
			}
			die_off += curattr->get_len();
			curattr = curattr->next;
		}

		    // depth first search
		if (curdie->dpd_child)
			 curdie = curdie->dpd_child;
		else {
			 while (curdie != NULL && curdie->dpd_right == NULL) {
				  curdie = curdie->dpd_parent;
				  die_off++;    // since we are writing a null die at the
                                // end of each sibling chain
			 }
			 if (curdie != NULL)
				  curdie = curdie->dpd_right;
		}
	}

	    // pass 2: Write out the die information

	curdie = cu->dpc_root;
	while (curdie != NULL) {
		Dwarf_P_Attribute *curattr;

		// index to abbreviation table
		data = get_chunk(elfsectno,curdie->dpd_abbrev_nbytes);
		memcpy((void *)data, (const void *)curdie->dpd_abbrev,curdie->dpd_abbrev_nbytes);

		// Attribute values - need to fill in all form attributes
		curattr = curdie->dpd_attrs;

		while (curattr) {
			data = get_chunk(elfsectno,curattr->get_len());
			memcpy((void *)data,(const void *)curattr->get_data(),curattr->get_len());
			curattr = curattr->next;
		}

		// depth first search
		if (curdie->dpd_child)
			 curdie = curdie->dpd_child;
		else {
			 while (curdie != NULL && curdie->dpd_right == NULL) {
				  data = get_chunk(elfsectno,1);
				  *data = '\0';
				  data++;
              USED(data);
				  curdie = curdie->dpd_parent;
			 }
			 if (curdie != NULL)
				  curdie = curdie->dpd_right;
		}
	}

	// write out debug_info size

	dw = die_off - word_size();  // dont include length field
	write_4(&dw,start_sec);

	// write out debug_abbrev section
	elfsectno = Dwarf::elf_sects[DEBUG_ABBREV];

	firsttime = 1;
	curabbrev = abbrev_head;
	while (curabbrev) {
		char *val;
		int nbytes;
		Dwarf_Unsigned idx;
		char buff1[ENCODE_SPACE_NEEDED];

		Dwarf::encode_leb128_nm(curabbrev->dpa_idx,&nbytes,buff1,sizeof(buff1));

		if (firsttime) {
			 data = get_new_chunk(elfsectno,nbytes);
			 firsttime = 0;
		}
		else
			 data = get_chunk(elfsectno,nbytes);

		val = buff1;
		memcpy((void *)data,(const void *)val, nbytes);
		Dwarf::encode_leb128_nm(curabbrev->dpa_tag,&nbytes,buff1,sizeof(buff1));

		val = buff1;
		data = get_chunk(elfsectno,nbytes);
		memcpy((void *)data,(const void *)val, nbytes);
		db = curabbrev->dpa_children;
		data = get_chunk(elfsectno,sizeof(Dwarf_Ubyte));
		memcpy((void *)data,(const void *)&db,sizeof(Dwarf_Ubyte));

		// add attributes and forms
		for (idx = 0; idx < curabbrev->dpa_n_attr; idx++) {
			Dwarf::encode_leb128_nm(curabbrev->dpa_attrs[idx],&nbytes,buff1,sizeof(buff1));
			val = buff1;
			data = get_chunk(elfsectno,nbytes);
			memcpy((void *)data,(const void *)val, nbytes);
			Dwarf::encode_leb128_nm(curabbrev->dpa_forms[idx],&nbytes,buff1,sizeof(buff1));
			val = buff1;
			data = get_chunk(elfsectno,nbytes);
			memcpy((void *)data,(const void *)val, nbytes);
		}
		data = get_chunk(elfsectno,2);      // два нуля обозначают конец
		*data = 0;									// списка атрибутов
		data++;
		*data = 0;

		curabbrev = curabbrev->next;
	}

	data = get_chunk(elfsectno,1);
	*data = 0;	// нуль это код аббревиатуры
					// означающей конец таблицы аббревиатур

	delete abbrev_head;

	if (rel_nbytes > 0) {
		Dwarf::reloc_sects[DEBUG_INFO] = dpd_func(".rel.debug_info", SHT_REL, 0,
				 SHN_UNDEF,Dwarf::elf_sects[DEBUG_INFO],&name_idx);

		if (Dwarf::reloc_sects[DEBUG_INFO] == (-1))
			throw Dwarf_Error_Pro_Elf("error creating section .rel.debug_info");

		// записываем секцию перемещения для секции .debug_info

		elfsectno = Dwarf::reloc_sects[DEBUG_INFO];
		write_reloc_section(rel_head,elfsectno,rel_nbytes);

        delete rel_head;    // удаляем когда более не нужна
    }

    return dpd_n_debug_sect;
}
