//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//                 Реализационный модуль dw_frame.cpp                   //
//                                                                      //
//  Файл реализации функций классов Dwarf_Fde, Dwarf_Cie,               //
//                                  Dwarf_Fde_Tab, Dwarf_Cie_Tab        //
//                                                                      //
//                                                                      //
//  If this code works, it was                                          //
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
// class Dwarf_Cie_Tab
//
//-------------------------------------------------------------------

Dwarf_Cie_Tab::Dwarf_Cie_Tab(Dwarf_Unsigned c,Dwarf_Debug *dbg) throw(Dwarf_Error)
	:	Dwarf_Tab<Dwarf_Cie,Dwarf_Cie_Tab>(c) , debug(dbg)
{
}

//-------------------------------------------------------------------
// private used in Dwarf_Debug::read_fde_cie_table
//-------------------------------------------------------------------

Dwarf_Unsigned Dwarf_Cie_Tab::find(Dwarf_Off offset) throw(Dwarf_Error)
{
	Dwarf_Small *ptr = debug->dd_debug_frame + offset;
	if (table == NULL)
		throw Dwarf_Error_Internal(Dwarf::DWARFERR,"empty cie table in Dwarf_Cie_Tab::find");
	for (Dwarf_Unsigned i = 0;i < cnt;i++)
		if (table[i]->dc_cie_start == ptr) return i;
	throw Dwarf_Error_Frame(Dwarf::DWARFERR,"no CIE specified for FDE");
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return (~Dwarf_Word(0));
#endif
}

//-------------------------------------------------------------------
//
// class Dwarf_Cie
//
//-------------------------------------------------------------------

Dwarf_Cie::Dwarf_Cie(
        Dwarf_Unsigned l,
        char *a,
        Dwarf_Unsigned caf,
        Dwarf_Signed daf,
	    Dwarf_Small rar,
        Dwarf_Small *start,
        Dwarf_Small *istart,
        Dwarf_Debug *debug) 
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
    : dc_length(l),
    dc_augmentation(a),
    dc_code_alignment_factor(caf),
    dc_data_alignment_factor(daf),
    dc_return_address_register(rar),
	dc_cie_start(start),
    dc_cie_instr_start(istart),
    dc_debug(debug),
	dc_initial_table(NULL),
    next(NULL),
    table(NULL)
{
        // создаю таблицу для хранения правил данной CIE
    dc_initial_table = new Dwarf_Frame;

        // fill initial table in this cie
    dc_debug->exec_frame_instr(
            False,              // флаг - генерировать ли последовательность 
                                // инструкций
            False,              // флаг - искать ли правило для конкретного
                                // значения pc
            0,                  // значение pc для которого искать правило

            Dwarf_Addr(0),      // начальный адрес 

            dc_cie_instr_start, // начало байтов инструкций

            dc_cie_start + dc_length + dc_debug->dd_lsize,
                                // конкц байтов инструкций

            dc_initial_table,   // таблица для результата
            this                // CIE где хранятся начальные значения для
                                // регистров. В данном случае нужно только 
                                // для строки идентификации производителя
                                // информации о стеках вызовов
        );

}

Dwarf_Small Dwarf_Cie::version() const
{
	return DW_CIE_VERSION;
}

// all other functions made inline

// char *Dwarf_Cie::augmenter()
// Dwarf_Unsigned Dwarf_Cie::code_aligment_factor()
// Dwarf_Signed Dwarf_Cie::data_aligment_factor()
// Dwarf_Half Dwarf_Cie::return_address_register_rule()
// Dwarf_Frame *Dwarf_Cie::initial_instructions()

//-------------------------------------------------------------------
//
// end of functions of class Dwarf_Cie
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// class Dwarf_Fde_Tab
//
//-------------------------------------------------------------------
Dwarf_Fde_Tab::Dwarf_Fde_Tab(Dwarf_Unsigned count,Dwarf_Debug *dbg) throw(Dwarf_Error)
	:	Dwarf_Tab<Dwarf_Fde,Dwarf_Fde_Tab>(count),debug(dbg)
{
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

void Dwarf_Fde_Tab::convert_list(Dwarf_Fde *fde,Dwarf_Cie_Tab *cie_tab) throw(Dwarf_Error)
{
	for(Dwarf_Unsigned i = 0;i < cnt;i++) {
		if (fde == NULL)
			throw Dwarf_Error_Internal("bad short list in Dwarf_Fde_Tab::convert_list");
		table[i] = fde;
		fde->table = this;
		fde->df_cie_index = cie_tab->find(fde->df_cie_offset);
		fde->df_cie = (*cie_tab)[fde->df_cie_index];
		fde = fde->next;
	}
	if (fde != NULL)
		throw Dwarf_Error_Internal("bad long list in Dwarf_Fde_Tab::convert_list");
}

//-------------------------------------------------------------------
// request for pc address in table of FDE
//-------------------------------------------------------------------

Dwarf_Fde *Dwarf_Fde_Tab::at_pc(Dwarf_Addr pc_of_interest) 
    throw(Dwarf_No_Entry)
{
	Dwarf_Unsigned i;
	Dwarf_Fde *fde;

	for (i = 0; i < cnt; i++) {
		fde = *(table + i);
		if (pc_of_interest >= fde->df_initial_location &&
				pc_of_interest < fde->df_initial_location + 
                                    fde->df_address_range)

			return fde;
	}

    throw Dwarf_No_Entry();
#if _MSC_VER <= MY_MSC_VER && defined(_MSC_VER)
    return NULL;
#endif // _MSC_VER
}

//-------------------------------------------------------------------
//
// end of functions of class Dwarf_Fde_Tab
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// class Dwarf_Fde
//
//-------------------------------------------------------------------

Dwarf_Fde::Dwarf_Fde(
					Dwarf_Unsigned l,
					Dwarf_Addr offset,
					Dwarf_Addr init_loc,
					Dwarf_Small *init_loc_pos,
					Dwarf_Addr arange,
					Dwarf_Small *start,
					Dwarf_Small *istart,
					Dwarf_Debug *debug
					) throw(Dwarf_Error) :
	df_length(l),df_cie_offset(offset),df_cie_index(0),df_cie(NULL),
	df_initial_location(init_loc),df_initial_loc_pos(init_loc_pos),
	df_address_range(arange),df_fde_start(start),df_fde_instr_start(istart),
	df_debug(debug),next(NULL),table(NULL)
{
}

//-------------------------------------------------------------------
// execute FDE instructions up to location pc_requested
// return register rules
//-------------------------------------------------------------------

Dwarf_Reg_Rule *Dwarf_Fde::get_info_for_reg(Dwarf_Half column,
	Dwarf_Addr pc_requested,Dwarf_Addr& row_pc) throw(Dwarf_Error)
{
	Dwarf_Frame    *fde_table = 0;
	Dwarf_Reg_Rule *reg_rule = 0;
	try {
		fde_table = new Dwarf_Frame;
		reg_rule = new Dwarf_Reg_Rule;

		if (column > DW_FRAME_LAST_REG_NUM)
			throw Dwarf_Error_Frame(Dwarf::DWARFERR,"bad column in frame table specified");

		if (pc_requested < df_initial_location ||
						pc_requested >= df_initial_location + df_address_range)
			throw Dwarf_Error_Frame(Dwarf::DWARFERR,"PC requested not in address range of FDE");

		df_debug->exec_frame_instr (
											False,  			//	make_instr
											True,          // search pc flag
											pc_requested,	// search pc value
											df_initial_location,	// start location
											df_fde_instr_start,	// start instructions bytes
											df_fde_start + df_length + df_debug->dd_lsize, // end instr bytes
											fde_table,		// table for result
											df_cie			// CIE of init
											);

		reg_rule->drr_offset   = fde_table->df_reg[column].drr_offset;
		reg_rule->drr_register = fde_table->df_reg[column].drr_register;
		reg_rule->drr_is_off   = fde_table->df_reg[column].drr_is_off;

		delete fde_table;
		row_pc = fde_table->df_loc;	// return first pc of row

		return reg_rule;
	}
	catch(Dwarf_Error) {
		if (fde_table) delete fde_table;
		if (reg_rule) delete reg_rule;
		throw;
	}
}

//-------------------------------------------------------------------
// similary whith get_info_for_reg but get rules for all registers
//-------------------------------------------------------------------

Dwarf_Frame *Dwarf_Fde::get_info_for_all_reg(Dwarf_Addr pc_requested,
									Dwarf_Addr& row_pc) throw(Dwarf_Error)
{
	Dwarf_Frame    *fde_table = new Dwarf_Frame;

	try {

		if (pc_requested < df_initial_location ||
						pc_requested >= df_initial_location + df_address_range)
			throw Dwarf_Error_Frame(Dwarf::DWARFERR,"PC requested not in address range of FDE");

		df_debug->exec_frame_instr (	False,  			//	make_instr
											True,          // search pc flag
											pc_requested,	// search pc value
											df_initial_location,	// start location
											df_fde_instr_start,	// start instructions bytes
											df_fde_start + df_length + df_debug->dd_lsize, // end instr bytes
											fde_table,		// table for result
											df_cie			// CIE of init
											);

		row_pc = fde_table->df_loc;	// return first pc of row

		return fde_table;
	}
	catch(Dwarf_Error) {
		if (fde_table) delete fde_table;
		throw;
	}
}

//-------------------------------------------------------------------
// expand FDE instructions into list of Dwarf_Frame_Op elementes
//-------------------------------------------------------------------

Dwarf_Frame_Tab *Dwarf_Fde::expand_frame_instructions() throw(Dwarf_Error)
{
	 return df_debug->exec_frame_instr (
										True,			// make_instr
										False,		    // search pc
										0,
										0,				// start location
										df_fde_instr_start,	// start instruction bytes
										df_fde_start + df_length + df_debug->dd_lsize, // end instr bytes
										0,			    // table for result
										0			    // CIE for init
										);
}

//-------------------------------------------------------------------
//
// class Dwarf_Frame_Tab
//
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// end of functions of class Dwarf_Frame_Tab
//
//-------------------------------------------------------------------
