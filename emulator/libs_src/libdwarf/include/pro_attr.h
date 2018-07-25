//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Ѕазовое программное обеспечение нейропроцессора           //
//                                                                      //
//        Ѕиблиотека доступа к отладочной информации формата DWARF      //
//                                                                      //
//                »нтерфейсный файл pro_attr.hpp                        //
//                                                                      //
//  ‘айл определ€ет класс Dwarf_P_Attribute и производные от него       //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:32p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------//
// внутренний базовый класс дл€ хранени€ атрибута                       //
//----------------------------------------------------------------------//

class Dwarf_P_Attribute {
	protected:

		friend class Dwarf_P_Die;
		friend Dwarf_Signed Dwarf_P_Debug::generate_debuginfo(Dwarf_P_CU *);
		friend Dwarf_P_Abbrev *Dwarf_P_Debug::getabbrev(Dwarf_P_Die *,Dwarf_P_Abbrev *);

		Dwarf_Half      dpa_attribute;      // Attribute Value.
		Dwarf_Half      dpa_attribute_form; // Attribute Form.
		char        *   dpa_data;           // data, format given by form
		Dwarf_Unsigned  dpa_nbytes;         // no. of bytes of data
		Dwarf_Unsigned  dpa_rel_symidx;     // when attribute has a relocatable
                                            // value, holds index of symbol in
                                            // SYMTAB
		Dwarf_Small     dpa_rel_type;       // relocation type
		Dwarf_Unsigned  dpa_rel_offset;     // Offset of relocation within block

		Dwarf_P_Debug * dpa_dbg;

		Dwarf_P_Attribute *next;

	public:

		virtual Dwarf_Half attr() const { return dpa_attribute; };
		virtual Dwarf_Half form() { return dpa_attribute_form; }
		virtual char *get_data() = 0;
		virtual Dwarf_Unsigned get_len() = 0;

	public:
		Dwarf_P_Attribute(Dwarf_P_Debug *dbg,Dwarf_Half attr,Dwarf_Half form)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw()
#endif  // _MSC_VER
        ;

		~Dwarf_P_Attribute()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;
};

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

class Dwarf_P_A_String : public Dwarf_P_Attribute {
	private:
		friend class Dwarf_P_Die;

	public:
		Dwarf_P_A_String(Dwarf_P_Debug *dbg,Dwarf_Half attr,char *string)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		virtual char *get_data();
		virtual Dwarf_Unsigned get_len() ;
};

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

class Dwarf_P_A_Sdata : public Dwarf_P_Attribute {
	private:
		friend class Dwarf_P_Die;

	public:
		Dwarf_P_A_Sdata(Dwarf_P_Debug *dbg,Dwarf_Half attr, Dwarf_Signed signed_value)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		virtual char *get_data() ;
		virtual Dwarf_Unsigned get_len() ;
};

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

class Dwarf_P_A_Udata : public Dwarf_P_Attribute {
	private:
		friend class Dwarf_P_Die;

	public:
		Dwarf_P_A_Udata(Dwarf_P_Debug *dbg,Dwarf_Half attr, Dwarf_Unsigned unsigned_value)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		virtual char *get_data() ;
		virtual Dwarf_Unsigned get_len() ;
};

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

class Dwarf_P_A_Flag : public Dwarf_P_Attribute {
	private:
		friend class Dwarf_P_Die;

	public:
		Dwarf_P_A_Flag(Dwarf_P_Debug *dbg,Dwarf_Half attr, Dwarf_Small flag)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
        throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		virtual char *get_data() ;
		virtual Dwarf_Unsigned get_len() ;
};

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

class Dwarf_P_A_Addr : public Dwarf_P_Attribute {
	private:
		friend class Dwarf_P_Die;

	public:
		Dwarf_P_A_Addr(Dwarf_P_Debug *dbg,Dwarf_Half attr, Dwarf_Addr addr,
			Dwarf_Signed sym_idx)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		virtual char *get_data() ;
		virtual Dwarf_Unsigned get_len() ;
};

//----------------------------------------------------------------------//
//                                                                      //
// класс дл€ адреса с отложенным вычислением                            //
//                                                                      //
//----------------------------------------------------------------------//

class Dwarf_P_A_Addr_Delayed : public Dwarf_P_Attribute {
	private:
		friend class Dwarf_P_Die;

        Dwarf_Unsigned dpa_addr_index;

            // производит вычисление значени€ атрибута в момент требовани€
        void CalculateAddress() throw(Dwarf_Error);
	public:
		Dwarf_P_A_Addr_Delayed(
            Dwarf_P_Debug *dbg,
            Dwarf_Half attr, 
            Dwarf_Unsigned addr_index)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		virtual char *get_data() ;
		virtual Dwarf_Unsigned get_len() ;
};

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

class Dwarf_P_A_Ref : public Dwarf_P_Attribute {
	private:
		friend class Dwarf_P_Die;

		Dwarf_P_Die	*dpa_ref_die;     	// die pointer

            // внутрен€€ функци€ вычисл€ет все внутрение переменные объекта
        void CalculateValues() throw(Dwarf_Error);

	public:
		Dwarf_P_A_Ref(
            Dwarf_P_Debug *dbg,
            Dwarf_P_CU *cu,
            Dwarf_Half attr,
            Dwarf_P_Die *ref)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

            // перегружаем функцию выдающую форму атрибута т.к. форма
            // ссылки вычисл€етс€ только во врем€ записи в файл
		virtual Dwarf_Half form();

		virtual char *get_data() ;
		virtual Dwarf_Unsigned get_len() ;
};

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

class Dwarf_P_A_Ref_Delayed : public Dwarf_P_Attribute {
	private:
		friend class Dwarf_P_Die;

		Dwarf_P_Die *   dpa_ref_die;     	// die pointer
        Dwarf_Unsigned  dpa_die_index;      // die index
        Dwarf_P_CU  *   dpa_cu;

            // внутренн€€ функци€ вычисл€ет значение отложенной ссылки
        void CalculateReference() throw(Dwarf_Error);

            // внутрен€€ функци€ вычисл€ет все внутрение переменные объекта
        void CalculateValues() throw(Dwarf_Error);

	public:
		Dwarf_P_A_Ref_Delayed(
            Dwarf_P_Debug *dbg,
            Dwarf_P_CU *cu,
            Dwarf_Half attr,
            Dwarf_Unsigned die_index)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

            // перегружаем функцию выдающую форму атрибута т.к. форма
            // ссылки вычисл€етс€ только во врем€ записи в файл
		virtual Dwarf_Half form();

		virtual char *get_data();
		virtual Dwarf_Unsigned get_len();
};

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

class Dwarf_P_A_Location : public Dwarf_P_Attribute {
	private:
		friend class Dwarf_P_Die;

	public:
		Dwarf_P_A_Location(Dwarf_P_Debug *dbg,Dwarf_Half attr,Dwarf_P_Expr *loc_expr)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		virtual char *get_data() ;
		virtual Dwarf_Unsigned get_len() ;
};

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

class Dwarf_P_A_Offset : public Dwarf_P_Attribute {
	private:
		friend class Dwarf_P_Die;

	public:
		Dwarf_P_A_Offset(Dwarf_P_Debug *dbg,Dwarf_Half attr,Dwarf_Off offset,
			Dwarf_Signed sym_idx)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		virtual char *get_data();
		virtual Dwarf_Unsigned get_len() ;
};

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

class Dwarf_P_A_Block : public Dwarf_P_Attribute {
	private:
		friend class Dwarf_P_Die;

	public:
		Dwarf_P_A_Block(Dwarf_P_Debug *dbg,Dwarf_Half attr, Dwarf_Block block)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		virtual char *get_data() ;
		virtual Dwarf_Unsigned get_len() ;
};
