//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//        Библиотека доступа к отладочной информации формата DWARF      //
//                                                                      //
//                Интерфейсный файл pro_fram.hpp                        //
//                                                                      //
//  Файл определяет служебный класс  интерфейса создания                //
//  Dwarf_P_Frame_Pgm                                                   //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:32p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

class Dwarf_P_Frame_Pgm {
	public:
		Dwarf_Ubyte	dpfp_opcode;     // opcode - includes reg #
		char        *dpfp_args;      // operands
		int         dpfp_nbytes;     // number of bytes in args

		Dwarf_P_Frame_Pgm   *next;

        Dwarf_P_Frame_Pgm() : dpfp_args(NULL),next(NULL) {  }

        ~Dwarf_P_Frame_Pgm() {
            if (dpfp_args) delete dpfp_args;
        }

};
