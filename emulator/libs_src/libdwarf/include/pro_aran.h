//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//        Библиотека доступа к отладочной информации формата DWARF      //
//                                                                      //
//                Интерфейсный файл pro_aran.hpp                        //
//                                                                      //
//  Файл определяет класс Dwarf_P_Arange                                //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:32p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef _PRO_ARAN_H
#define _PRO_ARAN_H

class Dwarf_P_Arange {
	private:

		Dwarf_Addr   	dpa_begin_address;
		Dwarf_Unsigned	dpa_length;
		Dwarf_Signed	dpa_symbol_index;

	public:

		Dwarf_P_Arange	*next;

		Dwarf_P_Arange(Dwarf_Addr addr,Dwarf_Unsigned length,Dwarf_Signed sym_idx)
			: dpa_begin_address(addr),dpa_length(length),dpa_symbol_index(sym_idx),
			next(NULL) { }

		~Dwarf_P_Arange()
		{
      	if (next) delete next;
		}

      Dwarf_Addr addr() const { return dpa_begin_address; }

      Dwarf_Unsigned len() const { return dpa_length; }

      Dwarf_Signed sym_idx() const { return dpa_symbol_index; }
};

#endif // _PRO_ARAN_H
