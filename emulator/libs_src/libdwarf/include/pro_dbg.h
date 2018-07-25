//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//        Библиотека доступа к отладочной информации формата DWARF      //
//                                                                      //
//                Интерфейсный файл pro_attr.hpp                        //
//                                                                      //
//  Файл определяет служебные классы интерфейса создания                //
//  Dwarf_P_Rel, Dwarf_P_Section_Data и Dwarf_P_Abbrev                  //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:32p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// classes for relocation information

class Dwarf_P_Rel {
    public:

        Elf32_Rel	*dpr_rel;
        Dwarf_P_Rel	*next;

        Dwarf_P_Rel()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

        ~Dwarf_P_Rel() {
            if (dpr_rel != NULL) delete dpr_rel;
            if (next) delete next;
        }

        void set(Dwarf_Addr offset,Dwarf_Half sym_idx,Dwarf_Small type)
        {
            dpr_rel->r_offset = offset;
            dpr_rel->r_info = ELF32_R_INFO(sym_idx,type);
        }
};


// class stores a chunk of data pertaining to a section

class Dwarf_P_Section_Data {
	public:
		Dwarf_Unsigned          dpsd_elf_sect_no;   // elf section number
		char                    *dpsd_data;         // data contained in section
		Dwarf_Unsigned          dpsd_nbytes;        // bytes of data

		Dwarf_P_Section_Data    *next;              // pointer to next chunk

	public:
		Dwarf_P_Section_Data(Dwarf_Unsigned sect_no)
            : dpsd_elf_sect_no(sect_no),
            dpsd_data(NULL),
            dpsd_nbytes(0),
			next(NULL)	
        {  }

		~Dwarf_P_Section_Data()
		{
			if (dpsd_data) delete dpsd_data;
		}

		char *data() const { return dpsd_data; }

		Dwarf_Unsigned len() const { return dpsd_nbytes; }
};

class Dwarf_P_Abbrev {
	public:

		Dwarf_Unsigned      dpa_idx;        // index of abbreviation
		Dwarf_Tag           dpa_tag;        // tag of die
		Dwarf_Ubyte         dpa_children;   // if children are present
		Dwarf_Word          *dpa_attrs;     // holds names of attrs
		Dwarf_Word          *dpa_forms;     // forms of attributes
		Dwarf_Word          dpa_n_attr;     // num of attrs = # of forms

		Dwarf_P_Abbrev      *next;

		~Dwarf_P_Abbrev() {
			if (dpa_attrs) delete[] dpa_attrs;
			if (dpa_forms) delete[] dpa_forms;

         if (next) delete next;
		}
};
