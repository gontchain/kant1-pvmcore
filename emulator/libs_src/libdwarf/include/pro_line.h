//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//        Библиотека доступа к отладочной информации формата DWARF      //
//                                                                      //
//                Интерфейсный файл pro_line.hpp                        //
//                                                                      //
//  Файл определяет служебные классы интерфейса создания                //
//  Dwarf_P_Inc_Dir, Dwarf_P_F_Entry и Dwarf_P_Line                     //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:32p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// This class is used to hold entries in the include directories
// part of statement prologue.

class Dwarf_P_Inc_Dir {
    public:

        char            *   dpid_name;	// name of directory
        Dwarf_P_Inc_Dir *   next;

        Dwarf_P_Inc_Dir() : dpid_name(NULL),next(NULL)
        {  }

        ~Dwarf_P_Inc_Dir() {
            if (dpid_name) delete dpid_name;
        }
};


// This class holds file entries for the statement prologue.
//

class Dwarf_P_F_Entry {
    public:
        char            *   dpfe_name; // name of file
        char            *   dpfe_args; // has dir index, time of modification,
                                    // length in bytes. Encodes as leb128
        int                 dpfe_nbytes;    // number of bytes in args
        Dwarf_P_F_Entry *   next;

        Dwarf_P_F_Entry() : 
            dpfe_name(NULL),
            dpfe_args(NULL),
            dpfe_nbytes(0),
            next(NULL)
        {  }

        ~Dwarf_P_F_Entry() {
            if (dpfe_name) delete dpfe_name;
            if (dpfe_args) delete dpfe_args;
        }
};



// class holding line number information for each of the producer
// line entries

class Dwarf_P_Line {
	public:

			// code address
		Dwarf_Addr      dpl_address;

			// file index, index into file entry
		Dwarf_Word      dpl_file;

			// line number
		Dwarf_Word      dpl_line;

			// column number
		Dwarf_Word      dpl_column;

			// whether its a beginning of a stmt
		Dwarf_Ubyte     dpl_is_stmt;

			// whether its a beginning of basic blk
		Dwarf_Ubyte     dpl_basic_block;

			// used to store opcodes set_address, and end_seq
		Dwarf_Ubyte     dpl_opc;

			// Used only for relocations.  Has index of symbol
			// relative to which relocation has to be done
			// (the S part in S + A)

		Dwarf_Unsigned  dpl_r_symidx;

			// for link into list
		Dwarf_P_Line  * next;

		Dwarf_P_Line() : 
                    dpl_address(0),
                    dpl_file(1),
                    dpl_line(1),
                    dpl_column(0),
			        dpl_is_stmt(Dwarf_Small(DEFAULT_IS_STMT)),
                    dpl_basic_block(Dwarf_Small(False)),
                    next(NULL)
		{ }

		void init()
		{
			dpl_address = 0;
			dpl_file = 1;
			dpl_line = 1;
			dpl_column = 0;
			dpl_is_stmt = DEFAULT_IS_STMT;
			dpl_basic_block = False;
		}
};
