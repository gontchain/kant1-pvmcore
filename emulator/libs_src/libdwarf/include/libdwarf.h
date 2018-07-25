//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//        Библиотека доступа к отладочной информации формата DWARF      //
//                                                                      //
//                Интерфейсный файл libdwarf.hpp                        //
//                                                                      //
//  Основной интерфейсный файл библиотеки. Определяет основные классы.  //
//                                                                      //
// Copyright (c) 1997-2006 RC Module                                    //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 2     $      $Date:: 6/02/06 3:23p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef _LIBDWARF_H
#define _LIBDWARF_H

#include "libelf.h"

//#include "dwarferr.h" - пользователь должен включить их отдельно
//#include "dwarf.h"

// Включать в следующем порядке
//
// #include <dwarftyp.h>
// #include <dwarf.h>
// #include <dwarferr.h>
// #include <libdwarf.h>


//-------------------------------------------------------------------//
// константы специфичные для нейрочипа
//-------------------------------------------------------------------//

const Dwarf_Half DW_FRAME_UNDEFINED_VAL = 1034;
const Dwarf_Half DW_FRAME_SAME_VAL = 1035;

// taken as meaning 'same value' as caller had, not a column
// or register number
// Only present at libdwarf runtime. Never on disk.
// DW_FRAME_* Values present on disk are in dwarf.h

//-------------------------------------------------------------------//
//
// шаблон для контейнерных классов
//
//-------------------------------------------------------------------//

template<class XElem,class Tab> class Dwarf_Tab {
	protected:
		Dwarf_Unsigned cnt;
		XElem **table;

	public:
		void convert_list(XElem *elem)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
			throw(Dwarf_Error)
#endif  // _MSC_VER
			;

		Dwarf_Tab(Dwarf_Unsigned count)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;


		virtual ~Dwarf_Tab()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;


		virtual XElem *getnext(XElem *elem) const
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;


		virtual XElem *operator[] (Dwarf_Unsigned index) const
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;


			// число элементов таблицы
		Dwarf_Unsigned	count() const { return cnt; }
};

template <class XElem,class Tab> void Dwarf_Tab<XElem,Tab>::convert_list(XElem *elem)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
    throw(Dwarf_Error)
#endif
{
    for(Dwarf_Unsigned i = 0;i < cnt;i++) {
        if (elem == NULL)
            throw Dwarf_Error_Internal("bad short list in Dwarf_Tab::convert_list");
        table[i] = elem;
        elem->table = (Tab *)this;
        elem = elem->Next();
    }

	if (elem != NULL)
		throw Dwarf_Error_Internal("bad long list in Dwarf_Tab::convert_list");
}

template <class XElem,class Tab> Dwarf_Tab<XElem,Tab>::Dwarf_Tab(
	Dwarf_Unsigned count)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
    throw(Dwarf_Error)
#endif
    : cnt(count)
{
	try {
		table = new XElem *[count];
		for (Dwarf_Unsigned i = 0;i < count;i++)
			table[i] = NULL;
	}
	catch(Dwarf_Error) {
		cnt = 0;
		if (table) {
			for (Dwarf_Unsigned i = 0;i < cnt;i++)
				if (table[i]) delete table[i];
			delete[] table;
		}
		throw;
	}
}

template <class XElem,class Tab> Dwarf_Tab<XElem,Tab>::~Dwarf_Tab()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
	throw(Dwarf_Error)
#endif
{
	if (table) {
		for (Dwarf_Unsigned i = 0;i < cnt;i++)
			if (table[i]) delete table[i];
		delete[] table;
	}
}

template <class XElem,class Tab> XElem *Dwarf_Tab<XElem,Tab>::getnext(
            XElem *elem) const
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
	throw(Dwarf_Error)
#endif
{
	if (elem == NULL) return table[0];
	if (elem->Table() != (Tab *)this)
		throw Dwarf_Error_Tab_Match("Dwarf error - ","element not match table");
	return elem->Next();
}

template <class XElem,class Tab> XElem *Dwarf_Tab<XElem,Tab>::operator[]
	(Dwarf_Unsigned index) const
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
        throw(Dwarf_Error)
#endif
{
	if (index >= cnt)
		throw Dwarf_Error_Tab_Range("Dwarf error - ",
			"bad index in table Dwarf_Tab");
	return table[index];
}

//-------------------------------------------------------------------//
// контейнеры для соответствующих классов
//-------------------------------------------------------------------//

class Dwarf_Line_Tab;
class Dwarf_Global_Tab;
class Dwarf_Arange_Tab;
class Dwarf_Macro_Tab;
class Dwarf_Frame_Tab;
class Dwarf_Filename_Tab;
class Dwarf_Dirs_Tab;

class Dwarf_Cie_Tab;
class Dwarf_Fde_Tab;
class Dwarf_Abbrev_Tab;

//-------------------------------------------------------------------//
// классы общие для обоих интерфейсов
//-------------------------------------------------------------------//

class Dwarf_Loc;
class Dwarf_Locdesc;
class Dwarf_Locdesc_Tab;
class Dwarf_Block;
class Dwarf_Frame_Op;
class Dwarf_Macro_Details;

class Dwarf_Loc {
	private:
		friend class Dwarf_Locdesc;
		friend class Dwarf_Attribute;
        friend void Dwarf_Tab<Dwarf_Loc, Dwarf_Locdesc>::convert_list(Dwarf_Loc *);

        Dwarf_Loc       *next;
        Dwarf_Locdesc   *table;
    public:
        Dwarf_Small     dl_atom;
        Dwarf_Unsigned	dl_number;
        Dwarf_Unsigned	dl_number2;
        Dwarf_Unsigned	dl_offset;

        Dwarf_Loc(Dwarf_Small atom,Dwarf_Unsigned number,Dwarf_Unsigned number2,
            Dwarf_Unsigned offset);

        Dwarf_Loc * Next() const { return next; }

        Dwarf_Locdesc * Table() const { return table; }
};

class Dwarf_Locdesc : public Dwarf_Tab < Dwarf_Loc, Dwarf_Locdesc> {
	private:
        friend class Dwarf_Locdesc_Tab;
        friend class Dwarf_Attribute;
        friend void Dwarf_Tab<Dwarf_Locdesc,Dwarf_Locdesc_Tab>
                        ::convert_list(Dwarf_Locdesc *);

		Dwarf_Locdesc		*next;
		Dwarf_Locdesc_Tab	*table;

		Dwarf_Addr		dl_lopc;
		Dwarf_Addr		dl_hipc;

		Dwarf_Locdesc(Dwarf_Unsigned count);

	public:
		Dwarf_Addr lowpc() const { return dl_lopc; }
		Dwarf_Addr highpc() const { return dl_hipc; }

        Dwarf_Locdesc * Next() const { return next; }

        Dwarf_Locdesc_Tab * Table() const { return table; }
};

class Dwarf_Locdesc_Tab : public Dwarf_Tab<Dwarf_Locdesc,Dwarf_Locdesc_Tab> {
    private:
        friend class Dwarf_Attribute;

        Dwarf_Locdesc_Tab(Dwarf_Unsigned count) :
            Dwarf_Tab<Dwarf_Locdesc,Dwarf_Locdesc_Tab>(count) {}
    public:
};

class Dwarf_Block {
	public:
		Dwarf_Unsigned	db_len;
		Dwarf_Ptr		db_data;

        Dwarf_Block() : db_len(0), db_data(NULL) {  }
};

class Dwarf_Frame_Op {
	private:
		friend class Dwarf_Debug;
		friend void Dwarf_Tab<Dwarf_Frame_Op,Dwarf_Frame_Tab>
                ::convert_list(Dwarf_Frame_Op *);

		Dwarf_Frame_Op	*next;
		Dwarf_Frame_Tab	*table;
	public:
		Dwarf_Small		dfo_fp_base_op;
		Dwarf_Small		dfo_extended_op;
		Dwarf_Half		dfo_register;
		Dwarf_Signed	dfo_offset;
		Dwarf_Off		dfo_instr_offset;

		Dwarf_Frame_Op(Dwarf_Small b,Dwarf_Small e,Dwarf_Half r, Dwarf_Signed o,
			Dwarf_Off io) : next(0), table(0), dfo_fp_base_op(b),dfo_extended_op(e),
            dfo_register(r),dfo_offset(o),dfo_instr_offset(io) {}

        Dwarf_Frame_Op * Next() const { return next; }

        Dwarf_Frame_Tab * Table() const { return table; }
};

class Dwarf_Macro_Details {
	private:

		friend class Dwarf_CU;
		friend void Dwarf_Tab<Dwarf_Macro_Details,Dwarf_Macro_Tab>
            ::convert_list(Dwarf_Macro_Details *);

		Dwarf_Macro_Details 	*next;
		Dwarf_Macro_Tab 		*table;
	public:
//		Dwarf_Off   	dmd_offset;		// ? m.b. need ?
		Dwarf_Small     dmd_type;
		Dwarf_Signed    dmd_lineno;
		Dwarf_Signed    dmd_fileindex;
		char        *   dmd_macro;

        Dwarf_Macro_Details * Next() const { return next; }

        Dwarf_Macro_Tab * Table() const { return table; }
};

//-------------------------------------------------------------------//
//
// Dwarf Consumer Interface
//
//-------------------------------------------------------------------//

//-------------------------------------------------------------------//
//
// набор классов интерфейса пользователя
//
//-------------------------------------------------------------------//

class Dwarf_Debug;
class Dwarf_CU;
class Dwarf_Die;
class Dwarf_Line;
class Dwarf_Global;
class Dwarf_Attribute;
class Dwarf_Fde;
class Dwarf_Cie;
class Dwarf_Frame;
class Dwarf_Arange;
class Dwarf_Abbrev;
class Dwarf_Abbrev_Attribute;
class Dwarf_Filename;
class Dwarf_Dirname;


//-------------------------------------------------------------------//
//
// детализация общих классов
//
//-------------------------------------------------------------------//


//-------------------------------------------------------------------//
//
// детализация классов интерфейса пользователя
//
//-------------------------------------------------------------------//

//-------------------------------------------------------------------//
//
// класс Dwarf_Debug описывает всю отладочную информацию находящуюся в файле
//
//-------------------------------------------------------------------//

class Dwarf_Debug {
    private:
        friend class Dwarf_CU;
        friend class Dwarf_Abbrev;
        friend class Dwarf_Cie_Tab;
        friend class Dwarf_Cie;
        friend class Dwarf_Fde;
        friend class Dwarf_Die;
        friend class Dwarf_Attribute;

        ELF         *   dd_elf;     // elf file
		Dwarf_Small     dd_encode;  // data encoding from elf
		Dwarf_Small     dd_lsize;   // length size in bytes

		Dwarf_CU        *dd_cu_list;    // list of CU

		Dwarf_Fde_Tab	*dd_fde_data;		// table of Dwarf_Fde
		Dwarf_Cie_Tab	*dd_cie_data;		// table of Dwarf_Cie

		Dwarf_Small		*dd_debug_info;		// .debuf_info section bytes
		Dwarf_Small		*dd_debug_abbrev;   // .debuf_abbrev section bytes
		Dwarf_Small		*dd_debug_line;     // .debuf_line section bytes
		Dwarf_Small		*dd_debug_loc;      // .debuf_loc section bytes
		Dwarf_Small		*dd_debug_aranges;  // .debuf_aranges section bytes
		Dwarf_Small		*dd_debug_macinfo;  // .debuf_macinfo section bytes
		Dwarf_Small		*dd_debug_pubnames; // .debuf_pubnames section bytes
		Dwarf_Small		*dd_debug_str;      // .debuf_str section bytes
		Dwarf_Small		*dd_debug_frame;    // .debuf_frame section bytes

		Dwarf_Unsigned		dd_debug_info_size;		// .debuf_info section size
		Dwarf_Unsigned		dd_debug_abbrev_size;   // .debuf_abbrev section size
		Dwarf_Unsigned		dd_debug_line_size;		// .debuf_line section size
		Dwarf_Unsigned		dd_debug_loc_size;      // .debuf_loc section size
		Dwarf_Unsigned		dd_debug_aranges_size;  // .debuf_aranges section size
		Dwarf_Unsigned		dd_debug_macinfo_size;  // .debuf_macinfo section size
		Dwarf_Unsigned		dd_debug_pubnames_size; // .debuf_pubnames section size
		Dwarf_Unsigned		dd_debug_str_size;      // .debuf_str section size
		Dwarf_Unsigned		dd_debug_frame_size;    // .debuf_frame section size

		Dwarf_Global_Tab	*dd_global_tab;	// таблица глобальных символов
		Dwarf_Arange_Tab	*dd_arange_tab;	// таблица диапазонов адресов

	private:

		void read(Dwarf_Unsigned *dest,void *src)
		{
            ELF::ToM( ELF32_T_WORD,
                (unsigned char *)dest,
                (unsigned char *)src,
                dd_encode,
                1 );
		}

		void read_2(Dwarf_Half *dest,void *src)
		{
            ELF::ToM( ELF32_T_HALF,
                (unsigned char *)dest,
                (unsigned char *)src,
                dd_encode,
                1);
		}

	protected:

            // internal function: read all CU from section .debug_info
            // and build list of CU
		void read_CU_list() throw(Dwarf_Error);

            // internal function: read all FDE and CIE from section
            //	.debug_frame, and build table of FDE and CIE
		void read_fde_cie_table() throw(Dwarf_Error);

        Dwarf_Small *get_augment_string(Dwarf_Small *offset)
            throw(Dwarf_Error);

		Dwarf_Frame_Tab *exec_frame_instr(
            Dwarf_Bool	make_instr,
            Dwarf_Bool	search_pc,
            Dwarf_Addr	search_pc_val,
            Dwarf_Addr	loc,
            Dwarf_Small	*start_instr_ptr,
            Dwarf_Small	*final_instr_ptr,
            Dwarf_Frame	*table,
            Dwarf_Cie	*cie) throw(Dwarf_Error);

	public:

			// читает информацию о глобальных символах
		void read_global(void) throw(Dwarf_Error,Dwarf_No_Entry);

			// читает информацию о адресных диапазонах
		void read_arange(void) throw(Dwarf_Error,Dwarf_No_Entry);

			// создает дескриптор отладочной
			// информации файла
		Dwarf_Debug(ELF *elf)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

			// уничтожает дескриптор отладочной информации
			// файла
		~Dwarf_Debug()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

			// возвращает дескриптор файла Elf связанного с Dwarf_Debug
		ELF *getelf() const { return dd_elf; }

			// выдает следующий CU
			// если cu = 0, то выдает первый CU
		Dwarf_CU *next_cu(Dwarf_CU *cu) throw(Dwarf_Error);

			// выдает DIE по смещению в секции .debug_info
			// смещение должно указывать на начало информации DIE
			// если смещение неверно, то результат не определен
		Dwarf_Die *offdie(Dwarf_Off offset) throw(Dwarf_No_Entry);

			// выдает CU по смещению в секции .debug_info.
			// смещение должно указывать на начало байтов заголовка CU
			// если CU не найдено то порождает исключение Dwarf_No_Entry
		Dwarf_CU *offcu(Dwarf_Off offset) throw(Dwarf_No_Entry);

			// выдает CU который содержит в себе данное смещение
		Dwarf_CU *cu_include_off(Dwarf_Off offset) throw(Dwarf_No_Entry);

	// функции работающие с информацией о стеках вызовов.

			// выдает таблицу CIE для всего файла
		Dwarf_Cie_Tab *get_cieinfo() throw(Dwarf_No_Entry);

			// выдает таблицу FDE для файла
		Dwarf_Fde_Tab *get_fdeinfo() throw(Dwarf_No_Entry);

	// функции работы с глобальными символами

			// выдает таблицу глобальных символов
		Dwarf_Global_Tab *get_globalinfo() throw(Dwarf_Error,Dwarf_No_Entry);

	// функции работы с информацией о адресных диапазонах

			// выдает таблицу информации о адресных диапазонах
		Dwarf_Arange_Tab *get_arangeinfo() throw(Dwarf_Error,Dwarf_No_Entry);

	// функции работающие с таблицей аббревиатур
	// ( внутренний уровень )

    // пока не реализована
    // Dwarf_Abbrev *next_abbrev(Dwarf_Abbrev *abbrev);

};

//-------------------------------------------------------------------//
//
// класс описывающий компиляционную единицу
//
//-------------------------------------------------------------------//

class Dwarf_CU {
    private:
        friend class Dwarf_Debug;
        friend class Dwarf_Die;
        friend class Dwarf_Attribute;
        friend class Dwarf_Line;

	        // from CU header
		Dwarf_Unsigned      dc_length;				// length of CU
		Dwarf_Half          dc_version_stamp;		// version of DWARF (==2)
		Dwarf_Signed        dc_abbrev_offset;		// offset in abbrev table
		Dwarf_Small         dc_address_size;		// size of address on target machine

		Dwarf_Unsigned      dc_debug_info_offset;   // offset in .debug_info section

		Dwarf_Abbrev_Tab    *dc_abbrev_table;		// hash table for abbreviation

		Dwarf_Debug         *dc_debug;				// Dwarf_Debug for this CU
		Dwarf_CU            *next;					// next CU in list

		Dwarf_Die           *dc_first_die;				// root die in tree

		Dwarf_Filename_Tab  *dc_files;			// table of file names
		Dwarf_Line_Tab      *dc_lines;			// table of line information
		Dwarf_Dirs_Tab      *dc_dirs;			// table of directories names

		Dwarf_Bool		dc_is_line_info_read;	// flag line info already readed
		Dwarf_Small		*dc_comp_dir;		// каталог в котором проходила компиляция

		Dwarf_Macro_Tab	*dc_macro_tab;	// таблица макрорасширений

		Dwarf_CU(Dwarf_Off offset,Dwarf_Debug *dbg)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		~Dwarf_CU()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

			// читает информацию о макрокомандах
		void read_macro(void) throw(Dwarf_Error,Dwarf_No_Entry);

	public:

			// читает информацию о строках
		void read_line_info() throw(Dwarf_Error,Dwarf_No_Entry);

		Dwarf_Unsigned	length() const { return dc_length; }

		Dwarf_Half version() const { return dc_version_stamp; }

		Dwarf_Unsigned	abbrev_offset() const { return dc_abbrev_offset; }

		Dwarf_Half address_size() const { return dc_address_size; }

			// выдает DIE - вершину дерева
		Dwarf_Die *get_first_die() throw(Dwarf_Error,Dwarf_No_Entry);

			// выдает DIE по смещению относительно начала CU
		Dwarf_Die *off_cu_die(Dwarf_Off offset) throw(Dwarf_No_Entry,Dwarf_Error);

	// функции работы с информацией о строках

		Dwarf_Line_Tab	*get_lineinfo() throw( Dwarf_Error, Dwarf_No_Entry );

	// функции работы с именами файлов

			// выдает массив имен файлов исходного текста
		Dwarf_Filename_Tab *srcfiles() throw(Dwarf_Error);

			// выдает массив каталогов файлов исходного текста
        Dwarf_Dirs_Tab *srcdirs() throw(Dwarf_Error);

            // выдает каталог в котором проходила компиляция
		const Dwarf_Small * comp_dir() throw(Dwarf_Error);

	// функции работы с макросами
    // пока не реализована

			// выдает таблицу содержащую макрокоманды
		Dwarf_Macro_Tab *get_macroinfo() throw(Dwarf_Error,Dwarf_No_Entry);

};

//-------------------------------------------------------------------//
// класс описывает конкретную DIE
//-------------------------------------------------------------------//

class Dwarf_Die {
    private:
        friend class Dwarf_CU;
        friend class Dwarf_Attribute;

        Dwarf_Abbrev*   dd_abbrev;      // link for abbrev for this die

        Dwarf_Die   *   dd_child_list;  // list of children of this die
        Dwarf_Die   *   dd_next_sibling;// next sibling of this die
        Dwarf_Die   *   dd_parent;      // parent die of this die

        Dwarf_CU    *   dd_cu;          // cu what contain this die

        Dwarf_Off	dd_die_offset;		// offset die in section .debug_info
        Dwarf_Off	dd_die_end_offset;  // end of possible DIE information

        Dwarf_Attribute *dd_attr_list;  // list DIE attributes

            // internal routine for loading subtree with this die as root
        void read_subtree(Dwarf_Unsigned& offset,Dwarf_Bool is_root)
            throw(Dwarf_Error);

            // ищет DIE начинающуюся со смещения offset
            // смещение полное - от начала секции .debug_info
        Dwarf_Die *findoff(Dwarf_Off offset)
            throw(Dwarf_Error,Dwarf_No_Entry);

        Dwarf_Die(
            Dwarf_Unsigned& offset,
            Dwarf_Unsigned end_offset,
            Dwarf_CU *cu,
            Dwarf_Die *parent)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

        ~Dwarf_Die()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

	public:

	// функции работы с деревом DIE

			// выдать следующий элемент дерева в порядке обхода дерева в глубину
			// слева направо
		Dwarf_Die *next() const;

			// сын текущей DIE
		Dwarf_Die *child() const { return dd_child_list; }

			// брат текущей DIE
		Dwarf_Die *sibling() const { return dd_next_sibling; }

			// отец текущей DIE
		Dwarf_Die *parent() const { return dd_parent; }

	// функции для обращения к CU

			// выдает указатель на CU, к
			// которой принадлежит DIE
		Dwarf_CU *get_cu() const { return dd_cu; }

	// функции запроса информации DIE

			// выдает тег текущей DIE
		Dwarf_Half tag() const throw(Dwarf_Error);

			// имеет ли детей
		Dwarf_Bool has_child() const throw(Dwarf_Error);

			// смещение DIE в секции
		Dwarf_Off dieoffset() const { return dd_die_offset; }

			// смещение DIE в CU
		Dwarf_Off die_cu_offset() const throw(Dwarf_Error);

	// функции запроса атрибутов DIE

		Dwarf_Bool hasattr(Dwarf_Half attr)     // имеет ли атрибут
             throw();

		Dwarf_Attribute *attr(Dwarf_Half attr)	// взять атрибут
             throw(Dwarf_No_Entry);

			// выдает следующий атрибут DIE после attr, если attr = 0,
			// то выдает первый атрибут. Если attr последний атрибут,
			// то выдает 0.
		Dwarf_Attribute *nextattr(Dwarf_Attribute *attr)
             throw(Dwarf_Error);

	// функции запроса значения некоторых часто требуемых атрибутов

			// атрибут DW_AT_name
			// имя DIE
		char *name() throw(Dwarf_Error,Dwarf_No_Entry);

			// атрибуты DW_AT_low_pc и DW_AT_high_pc
			// границы в адресном пространстве,
			// где определена данная DIE
		Dwarf_Addr lowpc() throw(Dwarf_Error,Dwarf_No_Entry);

		Dwarf_Addr highpc() throw(Dwarf_Error,Dwarf_No_Entry);

			// атрибут DW_AT_byte_size
		Dwarf_Unsigned	bytesize() throw(Dwarf_Error,Dwarf_No_Entry);

			// атрибут DW_AT_bit_size
		Dwarf_Unsigned	bitsize() throw(Dwarf_Error,Dwarf_No_Entry);

			// атрибут DW_AT_bit_offset
		Dwarf_Unsigned	bitoffset() throw(Dwarf_Error,Dwarf_No_Entry);

			// атрибут DW_AT_language
		Dwarf_Unsigned	srclang() throw(Dwarf_Error,Dwarf_No_Entry);

			// атрибут DW_AT_ordering
		Dwarf_Unsigned	arrayorder() throw(Dwarf_Error,Dwarf_No_Entry);

};

//-------------------------------------------------------------------//
//
// класс Dwarf_Attribute описывает конкретный атрибут конкретной DIE
//
//-------------------------------------------------------------------//

class Dwarf_Attribute {
    private:
        friend class Dwarf_Die;

        Dwarf_Die       *   da_die;
		Dwarf_Attribute *   next;       // next attribute in list

        Dwarf_Abbrev_Attribute  *   da_abbrev;  // abbreviation for this attribute
        Dwarf_Small             *   da_data;
        Dwarf_Unsigned              da_length;  // length of info for this attribute

        Dwarf_Attribute(
                            Dwarf_Abbrev_Attribute *abbrev_ptr,
                            Dwarf_Small *& info_ptr,
                            Dwarf_Die *die)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

        ~Dwarf_Attribute()
        {
                // delete next in list
            if (next) delete next;

                // delete this
        }

        Dwarf_Unsigned get_size(Dwarf_Debug *dbg,Dwarf_Unsigned form,
            Dwarf_Small *val_ptr);

        Dwarf_CU *check() throw(Dwarf_Error);

        Dwarf_Locdesc *get_locdesc(Dwarf_Small *ptr,Dwarf_Unsigned len,
            Dwarf_Debug *dbg) throw(Dwarf_Error);

    public:

            // возвращает значение атрибута
        Dwarf_Half attr() const;

            // функции запроса формы значения атрибута

            // имеет ли данную форму
        Dwarf_Bool hasform(Dwarf_Half form) const;

            // какую имеет форму
        Dwarf_Half form() const;

            // функции запроса значения атрибута в какой либо форме

            // выдает значение ссылку в виде числа
        Dwarf_Off form_ref_off() throw(Dwarf_Error);

            // выдать значение ссылку в виде
            // указателя на соответствующий DIE
        Dwarf_Die *form_ref() throw(Dwarf_Error);

            // выдает значение адрес
        Dwarf_Addr form_addr() throw(Dwarf_Error);

            // выдает значение флаг
        Dwarf_Bool form_flag() throw(Dwarf_Error);

            // выдает значение константу без знака
        Dwarf_Unsigned	form_udata() throw(Dwarf_Error);

            // выдает значение константу со знаком
        Dwarf_Signed form_sdata() throw(Dwarf_Error);

            // выдает значение блок в виде указателя
            // на объект Dwarf_Block
        Dwarf_Block	*form_block() throw(Dwarf_Error);

            // выдает значение строку
        char *form_string() throw(Dwarf_Error);

            // выдает таблицу элементов списка дескрипторов положения.
            // первый элемент таблицы всегда существует, но может быть единственным.
            // функция имеет значение для следующих атрибутов:
            // DW_AT_location, DW_AT_data_member_location, DW_AT_use_location
            // DW_AT_vtable_elem_location, DW_AT_string_length,
            // DW_AT_return_addr
        Dwarf_Locdesc_Tab *form_loc() throw(Dwarf_Error);
};

//-------------------------------------------------------------------//
// класс Dwarf_Line содержит информацию о строках исходного текста
//-------------------------------------------------------------------//

class Dwarf_Line {
    private:
        friend class Dwarf_Line_Tab;
        friend void Dwarf_CU::read_line_info(void);
        friend void Dwarf_Tab<Dwarf_Line,Dwarf_Line_Tab>::convert_list(Dwarf_Line *);

        Dwarf_Addr      dl_address;     // значение pc для машинной команды
        Dwarf_Unsigned  dl_file;        // индекс файла исходного текста
        Dwarf_Unsigned  dl_line;        // номер строки исходного текста
        Dwarf_Half      dl_column;      // номер колонки исходного текста
        Dwarf_Small     dl_is_stmt;     // является ли началом предложения
        Dwarf_Small     dl_basic_block;	// является ли началом базового блока
        Dwarf_Small     dl_end_sequence;// является ли первой инструкцией после
										// конца последовательности

		Dwarf_CU        *dl_cu;			// ссылка на содержащий CU

		Dwarf_Line		*next;
		Dwarf_Line_Tab	*table;

        Dwarf_Line() : dl_cu(NULL), next(NULL), table(NULL)
        {  }

	public:

	// функции выдающие параметры строки

			// является ли началом statement
		Dwarf_Bool      is_beginstatement() const { return dl_is_stmt; }

			// является ли концом последовательности
		Dwarf_Bool      is_endsequence() const { return dl_end_sequence; }

			// является ли началом блока
		Dwarf_Bool      is_beginblock() const { return dl_basic_block; }

		Dwarf_Unsigned  lineno() const { return dl_line; }
		Dwarf_Addr      addr() const { return dl_address; }
		Dwarf_Signed    column() const { return dl_column; };
		char            *srcfile() throw(Dwarf_Error);

            // выдает файл для данной строки
        Dwarf_Filename  *file() throw(Dwarf_Error);

        Dwarf_Line * Next() const { return next; }

        Dwarf_Line_Tab * Table() const { return table; }
};

//-------------------------------------------------------------------//
//
//-------------------------------------------------------------------//

class Dwarf_Dirname {
	private:
		friend class Dwarf_Dirs_Tab;
		friend void  Dwarf_CU::read_line_info(void);
		friend void Dwarf_Tab<Dwarf_Dirname,Dwarf_Dirs_Tab>
                ::convert_list(Dwarf_Dirname * );

        friend class Dwarf_P_CU;

		char            *ddn_name;
		Dwarf_Dirname   *next;
		Dwarf_Dirs_Tab  *table;
	public:
		Dwarf_Dirname(Dwarf_Small *ptr) : ddn_name((char *)(ptr)),
				next(NULL),table(NULL) {}

		char *name() const { return ddn_name; }

        Dwarf_Dirname * Next() const { return next; }
        Dwarf_Dirs_Tab * Table() const { return table; }
};

//-------------------------------------------------------------------//
//
//-------------------------------------------------------------------//

class Dwarf_Filename {
    private:
        friend void Dwarf_CU::read_line_info(void);
        friend class Dwarf_Filename_Tab;
        friend void Dwarf_Tab<Dwarf_Filename,Dwarf_Filename_Tab>
                ::convert_list(Dwarf_Filename * );

        char            *df_name;
        Dwarf_Unsigned  df_dir_index;
        Dwarf_Unsigned  df_time_last_mod;
        Dwarf_Unsigned  df_file_length;

		Dwarf_Filename      *next;
		Dwarf_Filename_Tab  *table;
	public:
		Dwarf_Filename(Dwarf_Small *ptr) : df_name((char *)(ptr)),
				next(NULL),table(NULL) {  }

            // выдает имя файла
		const char *name() const { return df_name; }

            // выдает индекс каталога в таблице каталогов CU
		Dwarf_Unsigned dir_index() const { return df_dir_index; }

            // выдает время последней модификации файла
		Dwarf_Unsigned time_last_mod() const { return df_time_last_mod; }

            // выдает размер файла
		Dwarf_Unsigned file_length() const { return df_file_length; }

            // выдает полное имя файла.
            // символьную строку надо уничтожить после использования.
        char * fullname() throw (Dwarf_Error);

        Dwarf_Filename * Next() const { return next; }

        Dwarf_Filename_Tab * Table() const { return table; }
};

//-------------------------------------------------------------------//
//
//-------------------------------------------------------------------//

class Dwarf_Global {
    private:
        friend void Dwarf_Debug::read_global(void);
        friend void Dwarf_Tab<Dwarf_Global,Dwarf_Global_Tab>
                ::convert_list(Dwarf_Global *);

            // смещение DIE для данного глобального символа в
            // соответствующей компиляционной единице (CU)
        Dwarf_Off           dg_cu_offset;

            // Имя глобального символа
        Dwarf_Small         *dg_name;

            // Длина в секции .debug_pubnames набора глобальных символов
            // для данной компиляционной единицы (CU)
        Dwarf_Unsigned      dg_length;

            // смещение в секции .debug_info единицы компиляции (CU)
            // для данного набора глобальных символов
        Dwarf_Off           dg_info_offset;

            // размер в секции .debug_info единицы компиляции (CU)
            // для данного набора глобальных символов
        Dwarf_Unsigned      dg_info_length;

        Dwarf_Global        *next;
        Dwarf_Global_Tab    *table;

        Dwarf_Global(
                Dwarf_Unsigned plen,
                Dwarf_Off ioffset,
                Dwarf_Unsigned ilen,
			    Dwarf_Off off,
                Dwarf_Small *name
            ) : dg_cu_offset(off),
                dg_name(name),
				dg_length(plen),
				dg_info_offset(ioffset),
                dg_info_length(ilen),
                next(0),
                table(0)
        {}

	public:

			// имя глобального символа
		char *name() const { return (char *)dg_name; }

			// смещение в секции .debug_info DIE описывающей данный символ
		Dwarf_Off	die_offset() const { return dg_cu_offset + dg_info_offset; }

			// смещение в секции заголовка CU, содержащей данный символ
		Dwarf_Off	cu_offset() const { return dg_info_offset; }

		Dwarf_Die	*get_die() const throw(Dwarf_Error);

        Dwarf_Global * Next() const { return next; }
        Dwarf_Global_Tab * Table() const { return table; }
};

//-------------------------------------------------------------------//
//
//-------------------------------------------------------------------//

class Dwarf_Arange {
    private:
        friend class Dwarf_Arange_Tab;
        friend class Dwarf_Debug;
        friend void Dwarf_Tab<Dwarf_Arange,Dwarf_Arange_Tab>
                ::convert_list(Dwarf_Arange *);

			 // Starting address of the arange, ie low-pc.
		Dwarf_Addr      da_address;

			 // Length of the arange.
		Dwarf_Unsigned  da_length;

			 // Offset into .debug_info of the start of the
			 // compilation-unit containing this set of aranges.
		Dwarf_Off       da_info_offset;

			 // Corresponding Dwarf_Debug.
		Dwarf_Debug     *da_debug;

		Dwarf_Arange        *next;
		Dwarf_Arange_Tab    *table;

		Dwarf_Arange (
            Dwarf_Addr address,
            Dwarf_Unsigned length,
            Dwarf_Off offset,
			Dwarf_Debug *debug)
                : da_address(address),
                da_length(length),
				da_info_offset(offset),
                da_debug(debug),
                next(NULL),
                table(NULL)
        {  }

	public:

		Dwarf_Off		cu_offset() const { return da_info_offset; }
		Dwarf_Addr		address() const { return da_address; }
		Dwarf_Unsigned	length() const { return da_length; }
		Dwarf_CU        *cu() const { return da_debug->offcu(da_info_offset); }

        Dwarf_Arange * Next() const { return next; }
        Dwarf_Arange_Tab * Table() const { return table; }
};

//-------------------------------------------------------------------//
//
// класс Dwarf_Line_Tab содержит информацию о всех строках в CU
//
//-------------------------------------------------------------------//

class Dwarf_Line_Tab : public Dwarf_Tab<Dwarf_Line,Dwarf_Line_Tab> {
    private:
        friend void Dwarf_CU::read_line_info(void);

        Dwarf_Line_Tab(Dwarf_Unsigned count) :
            Dwarf_Tab<Dwarf_Line,Dwarf_Line_Tab>(count) {}
    public:

        enum Slide {
            DW_DLS_BACKWARD = -1,   // найти строку с меньшим адресом
            DW_DLS_NOSLIDE  = 0,    // найти строку точно с таким адресом
            DW_DLS_FORWARD  = 1     // найти строку с большим адресом
        };

            // выдает первую строку с наименьшим расстоянием до pc
        Dwarf_Line * pcline( Dwarf_Addr pc , Dwarf_Line_Tab::Slide slide)
            throw (Dwarf_No_Entry);
};

//-------------------------------------------------------------------//
//
// класс Dwarf_Filename_Tab содержит информацию о всех строках в CU
//
//-------------------------------------------------------------------//

class Dwarf_Filename_Tab : public Dwarf_Tab<Dwarf_Filename,Dwarf_Filename_Tab> {
	private:
		friend void Dwarf_CU::read_line_info(void);

        Dwarf_CU * dftCU;       // указатель на CU

		Dwarf_Filename_Tab(Dwarf_Unsigned count, Dwarf_CU * cu )
            : Dwarf_Tab<Dwarf_Filename,Dwarf_Filename_Tab>(count),
            dftCU( cu )
        {}

	public:

        Dwarf_CU * get_cu() const { return dftCU; }
};

//-------------------------------------------------------------------//
//
// класс Dwarf_Dirname_Tab содержит информацию о всех строках в CU
//
//-------------------------------------------------------------------//

class Dwarf_Dirs_Tab : public Dwarf_Tab<Dwarf_Dirname,Dwarf_Dirs_Tab> {
	private:
		friend void Dwarf_CU::read_line_info(void);

		Dwarf_Dirs_Tab(Dwarf_Unsigned count) :
			Dwarf_Tab<Dwarf_Dirname,Dwarf_Dirs_Tab>(count) {}
	public:
};

//-------------------------------------------------------------------//
//
// класс Dwarf_Global_Tab содержит информацию о всех глобальных символах CU
//
//-------------------------------------------------------------------//

class Dwarf_Global_Tab : public Dwarf_Tab<Dwarf_Global,Dwarf_Global_Tab> {
	private:
		friend Dwarf_Debug::~Dwarf_Debug();
		friend void Dwarf_Debug::read_global(void);
		friend class Dwarf_Global;

        Dwarf_Debug	*dgt_debug;

        Dwarf_Debug *get_debug() const { return dgt_debug; }

        Dwarf_Global_Tab(Dwarf_Unsigned count,Dwarf_Debug *dbg) :
            Dwarf_Tab<Dwarf_Global,Dwarf_Global_Tab>(count),dgt_debug(dbg) {}
    public:
};

//-------------------------------------------------------------------//
//
// класс Dwarf_Arange_Tab содержит информацию о адресных диапазонах CU
//
//-------------------------------------------------------------------//

class Dwarf_Arange_Tab : public Dwarf_Tab<Dwarf_Arange,Dwarf_Arange_Tab> {
	private:
		friend Dwarf_Debug::~Dwarf_Debug();
		friend void Dwarf_Debug::read_arange(void);

		Dwarf_Arange_Tab(Dwarf_Unsigned count) :
			Dwarf_Tab<Dwarf_Arange,Dwarf_Arange_Tab>(count) {}
	public:
            // возвращает диапазон адресов в который попадает address или
			// порождает исключение типа Dwarf_No_Entry в случае отсутствия
			// такого диапазона
		Dwarf_Arange *get_arange(Dwarf_Addr address)
            throw(Dwarf_Error,Dwarf_No_Entry);
};

//-------------------------------------------------------------------//
//
// класс Dwarf_Macro_Tab содержит информацию о макросах CU
//
//-------------------------------------------------------------------//

class Dwarf_Macro_Tab : public Dwarf_Tab<Dwarf_Macro_Details,Dwarf_Macro_Tab> {
    private:
        friend class Dwarf_CU;
//		friend Dwarf_CU::~Dwarf_CU();
//		friend Dwarf_CU::read_macro();

        Dwarf_Macro_Tab(Dwarf_Unsigned count) :
            Dwarf_Tab<Dwarf_Macro_Details,Dwarf_Macro_Tab>(count) {}
    public:
};

//-------------------------------------------------------------------//
//
// нижний уровень. машинно-зависимая информация.
//
//-------------------------------------------------------------------//

//-------------------------------------------------------------------//
//
// classes for Frame operations
//
//-------------------------------------------------------------------//

//-------------------------------------------------------------------//
//	This class denotes the rule for a register in a row of
//	the frame table.
//-------------------------------------------------------------------//

class Dwarf_Reg_Rule {
	public:

		//	Is a flag indicating whether the rule includes
		//	the offset field, ie whether the ru_offset field
		//	is valid or not.  Actually not sure that it is
		//	needed since the offset is always additive, and
		//	no offset is the same as a 0 offset.

		//	Guess needed mostly for Dwarf_Fde::get_info_for_reg().

	Dwarf_Small		drr_is_off;

		  // Register involved in this rule
	Dwarf_Half		drr_register;

		  // Offset to add to register, if indicated by ru_is_off
	Dwarf_Addr		drr_offset;

	Dwarf_Reg_Rule() :
        drr_is_off(0),
        drr_register(DW_FRAME_SAME_VAL),
        drr_offset(0) { }
};


//-------------------------------------------------------------------//
//	 This class represents a row of the frame table.
//	 df_loc is the pc value for this row, and df_reg
//	 contains the rule for each column.
//-------------------------------------------------------------------//

class Dwarf_Frame {
	public:

		// Pc value corresponding to this row of the frame table.
	Dwarf_Addr      df_loc;

		// Rules for all the registers in this row.
	Dwarf_Reg_Rule  df_reg[DW_FRAME_LAST_REG_NUM];

		// pointer fo next row
	Dwarf_Frame     *next;

    Dwarf_Frame() : df_loc(0), next(NULL) {  }
};

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

class Dwarf_Cie {
    private:

        friend class Dwarf_Debug;
        friend class Dwarf_Cie_Tab;
        friend void Dwarf_Tab<Dwarf_Cie,Dwarf_Cie_Tab>
                        ::convert_list(Dwarf_Cie *);
        //friend Dwarf_Tab<Dwarf_Cie,Dwarf_Cie_Tab>
        //        ::Dwarf_Tab<Dwarf_Cie,Dwarf_Cie_Tab>(Dwarf_Unsigned count);
        //friend Dwarf_Tab<Dwarf_Cie,Dwarf_Cie_Tab>
        //        ::~Dwarf_Tab<Dwarf_Cie,Dwarf_Cie_Tab>();

        Dwarf_Cie		* next;
        Dwarf_Cie_Tab	* table;

        Dwarf_Unsigned  dc_length;
        char            *dc_augmentation;
        Dwarf_Unsigned  dc_code_alignment_factor;
        Dwarf_Signed    dc_data_alignment_factor;
        Dwarf_Small     dc_return_address_register;
        Dwarf_Small     *dc_cie_start;          // offset in .debuf_frame
        Dwarf_Small     *dc_cie_instr_start;    // offset of instruction bytes
        Dwarf_Debug     *dc_debug;              // debug descriptor
        Dwarf_Frame     *dc_initial_table;

	protected:

		Dwarf_Cie(
			Dwarf_Unsigned len,
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
        ;

	public:
        ~Dwarf_Cie()
        {
            if ( dc_initial_table ) delete dc_initial_table;
        }

		Dwarf_Small	version() const;
		char *augmenter() const
		{
			return dc_augmentation;
		}

		Dwarf_Unsigned	code_aligment_factor() const
		{
			return dc_code_alignment_factor;
		}

		Dwarf_Signed data_aligment_factor() const
		{
			return dc_data_alignment_factor;
		}

		Dwarf_Half return_address_register_rule()
		{
			return dc_return_address_register;
		}

		Dwarf_Ptr init_instructions()
		{
			return (Dwarf_Ptr)dc_cie_instr_start;
		}

		Dwarf_Unsigned init_instruction_length()
		{
			return dc_length + dc_debug->dd_lsize -
						(dc_cie_instr_start - dc_cie_start);
		}

        Dwarf_Cie * Next() const { return next; }
        Dwarf_Cie_Tab * Table() const { return table; }
};

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

class Dwarf_Cie_Tab : public Dwarf_Tab<Dwarf_Cie,Dwarf_Cie_Tab> {
	private:
		friend class Dwarf_Debug;
		friend class Dwarf_Fde_Tab;

		Dwarf_Debug	*debug;

		Dwarf_Cie_Tab(Dwarf_Unsigned c,Dwarf_Debug *dbg)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

			// find cie from offset
			// return index
		Dwarf_Unsigned find(Dwarf_Off offset) throw(Dwarf_Error);

	public:
};

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

class Dwarf_Fde {
    private:
        friend class Dwarf_Debug;
        friend class Dwarf_Fde_Tab;
        friend void Dwarf_Tab<Dwarf_Fde,Dwarf_Fde_Tab>::convert_list(Dwarf_Fde *);

		Dwarf_Fde		*next;
		Dwarf_Fde_Tab	*table;

		Dwarf_Unsigned	df_length;
		Dwarf_Addr		df_cie_offset;
		Dwarf_Signed	df_cie_index;
		Dwarf_Cie		*df_cie;
		Dwarf_Addr		df_initial_location;
		Dwarf_Small		*df_initial_loc_pos;
		Dwarf_Addr		df_address_range;
		Dwarf_Small		*df_fde_start;
		Dwarf_Small		*df_fde_instr_start;
		Dwarf_Debug		*df_debug;


		Dwarf_Fde(
					Dwarf_Unsigned l,
					Dwarf_Addr offset,
					Dwarf_Addr init_loc,
					Dwarf_Small *init_loc_pos,
					Dwarf_Addr arange,
					Dwarf_Small *start,
					Dwarf_Small *istart,
					Dwarf_Debug *debug
					)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

	public:

		Dwarf_Addr low_pc() const { return df_initial_location; }

		Dwarf_Addr high_pc() const
		{
			return df_initial_location + df_address_range;
		}

		Dwarf_Unsigned	func_length() const
		{
			return df_address_range;
		}

		Dwarf_Small	*fde_instructions()
		{
			return df_fde_instr_start;
		}

		Dwarf_Unsigned fde_instruction_length()
		{
			return df_length + df_debug->dd_lsize -
						(df_fde_instr_start - df_fde_start);
		}

		Dwarf_Signed cie_index() const
		{
			return df_cie_index;
		}

			// return CFA info for register column for requested address
		Dwarf_Reg_Rule *get_info_for_reg(
                Dwarf_Half column,
				Dwarf_Addr pc_request,
                Dwarf_Addr& row_pc) throw(Dwarf_Error);

			// return CFA info for all registers for requested address
		Dwarf_Frame *get_info_for_all_reg(
                Dwarf_Addr pc_request,
				Dwarf_Addr& row_pc) throw(Dwarf_Error);

		Dwarf_Frame_Tab *expand_frame_instructions() throw(Dwarf_Error);

        Dwarf_Fde * Next() const { return next; }
        Dwarf_Fde_Tab * Table() const { return table; }
};

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

class Dwarf_Fde_Tab : public Dwarf_Tab<Dwarf_Fde,Dwarf_Fde_Tab> {
    private:
        friend class Dwarf_Debug;

        Dwarf_Debug	*debug;

        Dwarf_Fde_Tab(Dwarf_Unsigned count,Dwarf_Debug *dbg)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

			// fill table from list
		void convert_list(Dwarf_Fde *fde,Dwarf_Cie_Tab *cie_tab)
            throw(Dwarf_Error);

	public:

		Dwarf_Fde	*at_pc(Dwarf_Addr pc_of_interest) throw(Dwarf_No_Entry);
};

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

class Dwarf_Frame_Tab : public Dwarf_Tab<Dwarf_Frame_Op,Dwarf_Frame_Tab> {
	private:
		friend class Dwarf_Debug;

		Dwarf_Frame_Tab(Dwarf_Unsigned count) :
			Dwarf_Tab<Dwarf_Frame_Op,Dwarf_Frame_Tab>(count) {}
	public:
		~Dwarf_Frame_Tab() throw(Dwarf_Error) {}
};

//-------------------------------------------------------------------//
//
// конкретный аттрибут в таблице аббревиатур
//
//-------------------------------------------------------------------//

class Dwarf_Abbrev_Attribute {
	private:
		friend class Dwarf_Abbrev;

		Dwarf_Half	daa_num;
		Dwarf_Half	daa_form;

//		Dwarf_Off offset();
//			// смещение в секции .debug_abbrev ( not need ??? )

		Dwarf_Abbrev_Attribute() : daa_num(0), daa_form(0) {}

	public:

			// код аттрибута
		Dwarf_Half attr_num() const { return daa_num; }

			// код формы аттрибута
		Dwarf_Half form() const { return daa_form; }

};

//-------------------------------------------------------------------//
//
// the abbreviation for DIE
//
//-------------------------------------------------------------------//

class Dwarf_Abbrev {
	private:
		friend class Dwarf_Abbrev_Tab;
		friend class Dwarf_CU;
//      friend class Dwarf_Die;

		Dwarf_Unsigned          da_code;    // код аббревиатуры
		Dwarf_Half              da_tag;     // тег  DIE
		Dwarf_Half              da_has_child;   // флаг имеет ли детей
		Dwarf_Abbrev_Tab        *table;         // ссылка на таблицу аббревиатур
		Dwarf_Abbrev_Attribute  *da_attr_table;	// таблица заголовков атрибутов
		Dwarf_Unsigned          da_count;   // число заголовков атрибутов
		Dwarf_Abbrev            *next;      // ссылка на следующую аббревиатуру в списке

		Dwarf_Abbrev(Dwarf_Off& offset,Dwarf_Debug *debug)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		~Dwarf_Abbrev()
		{
			if (da_attr_table) delete[] da_attr_table;
		}

	public:
		Dwarf_Unsigned code() const { return da_code; }

			//	выдает тег данного элемента таблицы аббревиатур
		Dwarf_Half tag() const { return da_tag; }

			// выдает флаг наличия детей
		Dwarf_Signed has_child() const { return da_has_child; }

		Dwarf_Unsigned attr_count() const { return da_count; }

			// выдает конкретный аттрибут по индексу
		Dwarf_Abbrev_Attribute *get_abbrev_entry(Dwarf_Unsigned index) const
            throw(Dwarf_Error);
};

//-------------------------------------------------------------------//
//
// the table of abbreviations (hash table)
//
//-------------------------------------------------------------------//

class Dwarf_Abbrev_Tab {
	private:
   	friend class Dwarf_CU;

		Dwarf_Unsigned		dat_elem_count;
		Dwarf_Unsigned		dat_hash_size;
		Dwarf_Abbrev		**table;

			// insert element into hash table
		void insert(Dwarf_Abbrev *elem) throw(Dwarf_Error);

	public:
		Dwarf_Abbrev_Tab(Dwarf_Unsigned size)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;
		~Dwarf_Abbrev_Tab()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;


			// find element in abbreviation table on code
      Dwarf_Abbrev *find_at_code(Dwarf_Unsigned code) throw(Dwarf_Error);
};

//-------------------------------------------------------------------//
//
// end of the table of abbreviations
//
//-------------------------------------------------------------------//

//-------------------------------------------------------------------//
//===================================================================//
//                                                                   //
// Dwarf Producer Interace                                           //
//                                                                   //
//===================================================================//
//-------------------------------------------------------------------//

//-------------------------------------------------------------------
//
// набор классов интерфейса производителя
//
//-------------------------------------------------------------------

	// классы доступные пользователю (используются для порождения информации)

class Dwarf_P_Debug;
class Dwarf_P_CU;
class Dwarf_P_Die;
class Dwarf_P_Expr;
class Dwarf_P_Cie;
class Dwarf_P_Fde;

	// классы не доступные пользователю ( используются внутри библиотеки )

class Dwarf_P_Attribute;
class Dwarf_P_A_Location;
class Dwarf_P_F_Entry;
class Dwarf_P_Inc_Dir;
class Dwarf_P_Line;
class Dwarf_P_Frame_Pgm;
class Dwarf_P_Arange;
class Dwarf_P_Pubname;
class Dwarf_P_Section_Data;
class Dwarf_P_Rel;
class Dwarf_P_Abbrev;
class Dwarf_P_Macinfo;

	// классы общие для обоих интерфейсов

//class Dwarf_Locdesc;
//class Dwarf_Block;
//class Dwarf_Frame_Op;
//class Dwarf_Macro_Details;

//-------------------------------------------------------------------//
//
// детализация классов интерфейса производителя
//
//-------------------------------------------------------------------//

class Dwarf_P_Debug {
	private:
        friend class Dwarf_P_A_Addr_Delayed;
        friend class Dwarf_P_A_Ref_Delayed;

		friend class Dwarf_P_Die;
		friend class Dwarf_P_Attribute;

        // ИЗМЕНЕНО 15.10.97 Ч.А.
        // теперь в объекте не хранится дескриптор ELF файла
	//ELF	*elf;

		 // This holds information about each debug section
	Dwarf_P_Section_Data	*dpd_debug_sects;

		 // Pointer to the last section
	Dwarf_P_Section_Data	*dpd_last_debug_sect;

		 // Number of debug data sections
	Dwarf_Unsigned	dpd_n_debug_sect;

		 // List of cie's for the debug unit
	Dwarf_P_Cie    *dpd_frame_cies;

		// Number of cie entries
	Dwarf_Unsigned	dpd_n_cie;

		 // Pointer to the last entry
	Dwarf_P_Cie    *dpd_last_cie;

		 // List of fde's for the debug unit
	Dwarf_P_Fde    *dpd_frame_fdes;

		 // Number of fde's.
	Dwarf_Unsigned dpd_n_fde;

		 // Pointer to the last entry
	Dwarf_P_Fde    *dpd_last_fde;

		 // Pointer to list of strings
	char           *dpd_strings;

		 // Pointer to chain of macroinfo
	Dwarf_P_Macinfo	*dpd_first_macinfo;

		 // Pointer to last macroinfo.
	Dwarf_P_Macinfo   *dpd_current_macinfo;

		 // Number of macroinfo.
	Dwarf_Signed	dpd_macinfo_count;

		// current offset for abbreviation table ( used in generate_debuginfo)
	Dwarf_Unsigned dpd_current_abbrev_offset;

		// current offset for debug_info section for current CU ( used in generate_debuginfo)
	Dwarf_Unsigned dpd_current_info_offset;

		// offset for next debug_line section for current CU ( used in generate_debuginfo)
	Dwarf_Unsigned dpd_next_line_offset;

	Dwarf_Small 	dpd_encode;	// data encoding
	Dwarf_P_CU		*dpd_head_cu_list;
	Dwarf_P_CU		*dpd_end_cu_list;

	private:
   		// функции генерации байтов отладочной информации

		Dwarf_Signed generate_debugline(Dwarf_P_CU *cu) throw(Dwarf_Error);

		Dwarf_Signed generate_debugframe() throw(Dwarf_Error);

		Dwarf_Signed transform_macro_info_to_disk() throw(Dwarf_Error);

		Dwarf_Signed generate_debuginfo(Dwarf_P_CU *cu) throw(Dwarf_Error);

		Dwarf_Signed transform_arange_to_disk(Dwarf_P_CU *cu)
            throw(Dwarf_Error);

		Dwarf_Signed transform_pubname_to_disk(Dwarf_P_CU *cu)
            throw(Dwarf_Error);

			// функции для выделения памяти кусками не менее 4-х Кбайт.
			// в этой памяти накапливаются выходные данные отладочной информации

			// выдает указатель на память размером nbytes, возможно в том же
			// куске
		unsigned char *get_chunk(Dwarf_Unsigned sect_no,Dwarf_Unsigned nbytes)
            throw(Dwarf_Error);

			// выдает указатель на память размером nbytes, в новом куске
		unsigned char *get_new_chunk(
            Dwarf_Unsigned sect_no,
            Dwarf_Unsigned nbytes) throw(Dwarf_Error);

		void write_reloc_section(
            Dwarf_P_Rel *rel_head,
            Dwarf_Signed relsectno,
			Dwarf_Unsigned rel_nbytes) throw(Dwarf_Error);

		Dwarf_P_Abbrev *getabbrev(Dwarf_P_Die *die, Dwarf_P_Abbrev *head)
            throw(Dwarf_Error);

		int match_attr(
            Dwarf_P_Attribute *attr,
            Dwarf_P_Abbrev *abbrev,
            int no_attr);

	public:

	// callback функции для получения отложенной информации
	// функции создаются пользователем и подаются в библиотеку как
	// параметры

			// callback для создания секций объектного файла Elf
			// если все нормально то возвращает Elf индекс созданной секции,
			// в случае ошибки возвращает (-1).

        typedef Dwarf_Signed (*Dwarf_Callback_Section)(
                    // подаваемые параметры
                char *name,                         // имя секции
                Dwarf_Unsigned type,                // поле типа секции заголовка секции
                Dwarf_Unsigned flags,               // поле флагов заголовка секции
                Dwarf_Unsigned link,                // поле связи заголовка секции
                Dwarf_Unsigned info,                // поле информации заголовка секции

                    // возвращаемые параметры
                Dwarf_Unsigned *sect_name_index     // индекс символа связанного с
                                                    // данной секцией в таблице
                                                    // символов файла
			);

			// callback для разрешения неразрешенных ссылок на адреса меток
			// возвращает 0 если все нормально
			// в случае ошибки возвращает не 0.

		typedef int (*Dwarf_Callback_Addr) (
					// подаваемые параметры
				Dwarf_Unsigned	addr_index,		// номер идентифицирующий адрес

					// возвращаемые параметры
				Dwarf_Addr		*pc_value,		// значение адреса
				Dwarf_Signed	*symbol_index	// индекс символа Elf относительно
														// которого перемещается данный адрес
			);

			// callback для разрешения неразрешенных ссылок на DIE
			// возвращает 0 если все нормально
			// в случае ошибки возвращает не 0.

		typedef int (*Dwarf_Callback_Ref) (
					// подаваемые параметры
				Dwarf_Unsigned	die_index,		// номер идентифицирующий DIE

					// возвращаемые параметры
				Dwarf_P_Die		**ref_die		// указатель на DIE специфицированную
												// номером die_index
			);

	private:

        Dwarf_Callback_Section  dpd_func;       // callback for creation section
        Dwarf_Callback_Addr     dpd_func_addr;  // callback for calculation of addresses
        Dwarf_Callback_Ref      dpd_func_ref;   // callback for calculation of references

	public:

            // параметр encode задает кодировку байтов на целевой машине
		Dwarf_P_Debug( Dwarf_Small encode )
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		~Dwarf_P_Debug()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

	// функции выдачи результата

            // преобразовать отладочную информацию в массив байтов
            // основная функция интерфейса создания отладочной информации
		Dwarf_Signed transform_to_disk(
                Dwarf_Callback_Section  section_func,
                Dwarf_Callback_Addr     addr_func,
                Dwarf_Callback_Ref      ref_func
			) throw(Dwarf_Error);

			// выдать байты отладочной информации по секциям
		Dwarf_Ptr get_section_bytes(
				Dwarf_Signed 	dwarf_section,
				Dwarf_Signed 	*elf_section,
				Dwarf_Unsigned	*length
			) throw();

			// записать отладочную информацию в файл elf
		void write_section_to_disk( ELF *elf ) throw(Dwarf_Error);

            // Выдает дескриптор Elf хранимый в объекте.
            // теперь в объекте не хранится дескриптор ELF файла
        //ELF *getelf() const { return elf; }

	// функции работы с CU

		Dwarf_P_CU *new_cu() throw(Dwarf_Error);
			// создать новую CU

		Dwarf_P_CU *next_cu(Dwarf_P_CU *cu) const throw(Dwarf_Error);
			// выдать следующую CU

	// функции работы с стеком вызовов ( FDE и CIE )

		Dwarf_P_Cie	*new_cie(	char *augmenter,
							Dwarf_Small code_align,
							Dwarf_Small data_align,
							Dwarf_Small ret_addr_reg
							) throw(Dwarf_Error);
			// создать новую CIE

		Dwarf_P_Fde	*new_fde(
							Dwarf_P_Cie *cie,
							Dwarf_Addr addr,
							Dwarf_Unsigned code_len,
							Dwarf_Signed sym_idx
							) throw(Dwarf_Error);
			// создать новую FDE

	public: // internal functions

		void write_2(Dwarf_Half *src,char *dest)
		{
            ELF::ToF( ELF32_T_HALF,(Dwarf_Small *)dest,(Dwarf_Small *)src,dpd_encode, 1);
		}

			// dest <= src;
		void write_4(Dwarf_Unsigned *src,char *dest)
		{
            ELF::ToF( ELF32_T_WORD,(Dwarf_Small *)dest,(Dwarf_Small *)src,dpd_encode, 1);
		}

		void write_2(const Dwarf_Half *src,unsigned char *dest)
		{
            ELF::ToF( ELF32_T_HALF, (Dwarf_Small *)dest,(Dwarf_Small *)src,dpd_encode, 1);
		}

			// dest <= src;
		void write_4(const Dwarf_Unsigned *src,unsigned char *dest)
		{
            ELF::ToF( ELF32_T_WORD, (Dwarf_Small *)dest,(Dwarf_Small *)src,dpd_encode, 1);
		}
		Dwarf_Addr addr_size() const { return ELF32_T_ADDR_FSIZE; }
		Dwarf_Off off_size() const { return ELF32_T_OFF_FSIZE; }
        Dwarf_Off half_size() const { return ELF32_T_HALF_FSIZE; }
        Dwarf_Off byte_size() const { return ELF32_T_BYTE_FSIZE; }
        Dwarf_Off word_size() const { return ELF32_T_WORD_FSIZE; }
};

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

class Dwarf_P_CU {
    private:
        friend class Dwarf_P_Debug;
        friend class Dwarf_P_Die;

			 // Holds an array of file entry information, null terminated
		Dwarf_P_F_Entry	*dpc_file_entries;

			 // last file entry
		Dwarf_P_F_Entry   *dpc_last_file_entry;

			 // Number of file entries, needed to return index of file
		Dwarf_Unsigned    dpc_n_file_entries;

			 // Has the directories used to search for source files
		Dwarf_P_Inc_Dir   *dpc_inc_dirs;

			 // Last include directory
		Dwarf_P_Inc_Dir   *dpc_last_inc_dir;

			 // Number of include directories, needed to return dir index
		Dwarf_Unsigned    dpc_n_inc_dirs;

			 // Has all the line number info for the stmt program
		Dwarf_P_Line      *dpc_lines;

			 // Handle to the last line number entry.
		Dwarf_P_Line      *dpc_last_line;

			// pointer to the root of DIE tree

		Dwarf_P_Die		*dpc_root;

			 // Pointer to chain of aranges
		Dwarf_P_Arange *dpc_arange;

			 // Pointer to last arange
		Dwarf_P_Arange *dpc_last_arange;

			 // Number of aranges
		Dwarf_Signed    dpc_arange_count;

          // Pointer to chain of pubnames.
      Dwarf_P_Pubname *dpc_pubname;

          // Pointer to last pubname.
      Dwarf_P_Pubname *dpc_last_pubname;

          // Number of pubnames.
      Dwarf_Signed dpc_pubname_count;

		Dwarf_P_Debug 	*dpc_debug;
      Dwarf_Unsigned dpc_line_offset;  // смещение информации о строках для
                                       // данной CU в секции .debug_line

      Dwarf_Unsigned dpc_info_offset;  // смещение начала информации данной CU
                                       // в секции .debug_info


		Dwarf_P_CU		*next;

		Dwarf_P_CU(Dwarf_P_Debug *dbg)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw()
#endif  // _MSC_VER
        ;

		~Dwarf_P_CU()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		void int_add_line_entry( Dwarf_Unsigned file_index,
									Dwarf_Addr code_address,
									Dwarf_Unsigned symidx,
									Dwarf_Unsigned line_no,
									Dwarf_Signed col_no,
									Dwarf_Bool is_stmt_begin,
									Dwarf_Bool is_bb_begin,
									Dwarf_Small opc
									) throw(Dwarf_Error);

	public:

		Dwarf_P_Debug *get_debug() const { return dpc_debug; }

			// делает DIE вершину дерева для данного CU
		Dwarf_P_Die *make_root() throw(Dwarf_Error);

        Dwarf_P_Die *get_root() const { return dpc_root; }

	// функции работы с номерами строк

			// добавить новую строку
		void add_line_entry(
					Dwarf_Unsigned file_index,
					Dwarf_Addr code_offset,
					Dwarf_Unsigned lineno,
					Dwarf_Signed column_number,
					Dwarf_Bool is_source_stmt_begin,
					Dwarf_Bool is_basic_block_begin
					) throw(Dwarf_Error);

			// установить адрес начала блока
		void lne_set_address(Dwarf_Addr offset, Dwarf_Unsigned symidx)
            throw(Dwarf_Error);

			// установить конец последовательности
		void lne_end_sequence(Dwarf_Addr end_address) throw(Dwarf_Error);

			// добавить имя каталог
		Dwarf_Unsigned add_directory_decl(char *name) throw(Dwarf_Error);

			// добавить имя файла
		Dwarf_Unsigned add_file_decl(
						char *name,
						Dwarf_Unsigned dir_idx,
						Dwarf_Unsigned time_mod,
						Dwarf_Unsigned length
						) throw(Dwarf_Error);

	// функции работы с диапазонами адресов

			// добавить диапазон
		void add_arange(
							Dwarf_Addr begin_address,
							Dwarf_Unsigned length,
							Dwarf_Signed symbol_index) throw(Dwarf_Error);

	// функции работы с макрокомандами

		void def_macro(
               Dwarf_Unsigned lineno,
					char *name,
					char *value);
			// макрокоманда define

		void undef_macro(Dwarf_Unsigned lineno,char *name);
			// макрокоманда undefine

		void start_macro_file(Dwarf_Unsigned lineno, Dwarf_Unsigned file_index);
			// макрокоманда include

		void end_macro_file();
			// конец include
};

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

class Dwarf_P_Die {
    private:
        friend class Dwarf_P_CU;
        friend Dwarf_Signed Dwarf_P_Debug::generate_debuginfo(Dwarf_P_CU *);
        friend Dwarf_P_Abbrev *Dwarf_P_Debug::getabbrev(Dwarf_P_Die *,Dwarf_P_Abbrev *);
        friend Dwarf_Signed Dwarf_P_Debug::transform_pubname_to_disk(Dwarf_P_CU *cu);
        friend class Dwarf_P_A_Ref;
        friend class Dwarf_P_A_Ref_Delayed;

		Dwarf_Unsigned      dpd_offset;        		// offset in debug info
		char                *dpd_abbrev;            // abbreviation
		Dwarf_Unsigned		dpd_abbrev_nbytes;      // # of bytes in abbrev
		Dwarf_Tag           dpd_tag;
		Dwarf_P_Die         *dpd_parent;            // parent of current die
		Dwarf_P_Die         *dpd_child;             // first child
//		Dwarf_P_Die         dpd_left;               // left sibling
		Dwarf_P_Die			*dpd_right;             // right sibling
		Dwarf_P_Attribute   *dpd_attrs;   				// list of attributes
		Dwarf_P_Attribute   *dpd_last_attr;         // last attribute
		Dwarf_Unsigned      dpd_n_attr;             // number of attributes

		Dwarf_P_CU          *dpd_cu;

		Dwarf_P_Die(Dwarf_P_CU *cu,Dwarf_P_Die *parent,Dwarf_Tag tag)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw()
#endif  // _MSC_VER
        ;

		~Dwarf_P_Die()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		void add_at_to_die(Dwarf_P_Attribute *attrib) throw(Dwarf_Error);

		void add_AT_macro_info(Dwarf_Unsigned offset) throw(Dwarf_Error);

		void add_AT_stmt_list() throw(Dwarf_Error);

	public:

		Dwarf_P_Debug *get_debug() const { return dpd_cu->get_debug(); }
		Dwarf_P_CU *get_cu() const { return dpd_cu; }

	// функции создания новых DIE

		Dwarf_P_Die *new_child(Dwarf_Tag new_tag) throw(Dwarf_Error);

		Dwarf_P_Die *new_sibling(Dwarf_Tag new_tag) throw(Dwarf_Error);

	// функции просмотра дерева DIE

			// выдать следующий элемент дерева в порядке обхода дерева в глубину
			// слева направо
		Dwarf_P_Die *next() const;

			// сын текущей DIE
		Dwarf_P_Die *child() const { return dpd_child; }

			// брат текущей DIE
		Dwarf_P_Die *sibling() const { return dpd_right; }

			// отец текущей DIE
		Dwarf_P_Die *parent() const { return dpd_parent; }

	// функции добавления атрибутов к DIE

		void add_AT_location_expr(Dwarf_Half attr,Dwarf_P_Expr *loc_expr)
            throw(Dwarf_Error);

		void add_AT_name(char *name) throw(Dwarf_Error);

		void add_AT_comp_dir(char *directory) throw(Dwarf_Error);

		void add_AT_producer(char *producer) throw(Dwarf_Error);

		void add_AT_const_value_signedint(Dwarf_Signed signed_value)
            throw(Dwarf_Error);

		void add_AT_const_value_unsignedint(Dwarf_Unsigned unsigned_value)
            throw(Dwarf_Error);

		void add_AT_const_value_string(char *string)
            throw(Dwarf_Error);

		void add_AT_targ_address(
                Dwarf_Half attr,
                Dwarf_Unsigned pc_value,
			    Dwarf_Signed sym_index) throw(Dwarf_Error);

			// адрес с отложенным вычислением
		void add_AT_targ_address_delayed(
                Dwarf_Half attr,
			    Dwarf_Unsigned addr_index) throw(Dwarf_Error);

		void add_AT_unsigned_const(Dwarf_Half attr,Dwarf_Unsigned value)
            throw(Dwarf_Error);

		void add_AT_signed_const(Dwarf_Half attr,Dwarf_Signed value)
            throw(Dwarf_Error);

		void add_AT_reference(Dwarf_Half attr,Dwarf_P_Die *otherdie)
            throw(Dwarf_Error);

			// ссылка на другой DIE с отложенным вычислением
		void add_AT_reference_delayed(
                Dwarf_Half attr,
                Dwarf_Unsigned die_index
            ) throw(Dwarf_Error);

		void add_AT_flag(Dwarf_Half attr,Dwarf_Small flag)
            throw(Dwarf_Error);

		void add_AT_string(Dwarf_Half attr,char *string)
            throw(Dwarf_Error);

        void add_AT_block(Dwarf_Half attr, Dwarf_Block block)
            throw(Dwarf_Error);

	// функции работы с глобальными именами

		void add_pubname(char *pubname_name)
            throw(Dwarf_Error);
};

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

class Dwarf_P_Expr {
    private:
        friend class Dwarf_P_A_Location;

        Dwarf_Small		*dpe_byte_stream;
        Dwarf_Unsigned	dpe_next_byte_offset;
        Dwarf_Signed	dpe_reloc_sym_index;
        Dwarf_Unsigned	dpe_reloc_offset;

        Dwarf_P_Debug	*dpe_dbg;

//      friend class Dwarf_P_Die;
	public:
		Dwarf_P_Expr(Dwarf_P_Debug *dbg)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw(Dwarf_Error)
#endif  // _MSC_VER
        ;

		~Dwarf_P_Expr()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw()
#endif  // _MSC_VER
        ;

		Dwarf_Unsigned add_expr_gen(
								Dwarf_Small opcode,
								Dwarf_Unsigned val1,
								Dwarf_Unsigned val2
								) throw(Dwarf_Error);

		Dwarf_Unsigned add_expr_addr(
								Dwarf_Addr address,
								Dwarf_Signed sym_index
								) throw(Dwarf_Error);

		Dwarf_Unsigned	current_offset() const;

			// выдать выражение в виде массива байтов
		Dwarf_Ptr get_bytes() const;

			// выдать длину массива байтов
		Dwarf_Unsigned get_length() const;

		Dwarf_P_Debug *get_debug() const { return dpe_dbg; }
};

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

class Dwarf_P_Cie {
	private:
   	friend class Dwarf_P_Debug;


		Dwarf_Small	dpc_version;
		char        *dpc_aug;       	// augmentation
		Dwarf_Small	dpc_code_align; 	// alignment of code
		Dwarf_Small	dpc_data_align;
		Dwarf_Small	dpc_ret_reg;    	// return register #
//		char			*dpc_inst;      	// initial instruction
//		long			dpc_inst_bytes;	// no of init_inst

			// frame instructions
		Dwarf_P_Frame_Pgm	*dpc_inst;

			// number of instructions
		long              dpc_n_inst;

			// number of bytes of inst
		long              dpc_n_bytes;

			// pointer to last inst
		Dwarf_P_Frame_Pgm *dpc_last_inst;

		Dwarf_Unsigned  dpc_index;
		Dwarf_P_Cie     *next;
		Dwarf_P_Debug   *dpc_debug;


		Dwarf_P_Cie(Dwarf_P_Debug *dbg,Dwarf_Small version,char *augmenter,
			Dwarf_Small code_align,Dwarf_Small data_align,Dwarf_Small return_reg)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw()
#endif  // _MSC_VER
        ;

		~Dwarf_P_Cie();

  		void add_to_cie(Dwarf_P_Frame_Pgm *curinst) throw();

	public:
		void add_inst(
				Dwarf_Small op,
				Dwarf_Unsigned val1,
				Dwarf_Unsigned val2
				) throw(Dwarf_Error);
			// добавить команду

		Dwarf_Unsigned index() const { return dpc_index; }
};

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

class Dwarf_P_Fde {
	private:
   	friend class Dwarf_P_Debug;

			// number of bytes
		Dwarf_Unsigned	dpf_length;

			// index to asso. cie
		Dwarf_P_Cie		*dpf_cie;

			// address of first location
		Dwarf_Addr     dpf_initloc;

			// relocation section symbol ptr
		Dwarf_Unsigned dpf_r_symidx;

			// bytes of instr for this fde
		Dwarf_Addr     dpf_addr_range;

			// instructions
		Dwarf_P_Frame_Pgm	*dpf_inst;

			// number of instructions
		long dpf_n_inst;

			// number of bytes of inst
		long dpf_n_bytes;

			// pointer to last inst
		Dwarf_P_Frame_Pgm *dpf_last_inst;

		Dwarf_P_Fde *next;
		Dwarf_P_Debug *dpf_debug;

		Dwarf_P_Fde(Dwarf_P_Debug *dbg,Dwarf_P_Cie *cie_index,Dwarf_Addr init_loc,
			Dwarf_Unsigned sym_idx,Dwarf_Addr code_len)
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw()
#endif  // _MSC_VER
        ;

		~Dwarf_P_Fde()
#if _MSC_VER > MY_MSC_VER || !defined(_MSC_VER)
            throw()
#endif  // _MSC_VER
        ;

		void add_to_fde(Dwarf_P_Frame_Pgm *curinst) throw();

	public:
		void add_inst(
				Dwarf_Small op,
				Dwarf_Unsigned val1,
				Dwarf_Unsigned val2
				) throw(Dwarf_Error);
			// добавить команду

		void fde_cfa_offset(Dwarf_Unsigned reg, Dwarf_Signed offset)
            throw(Dwarf_Error);
			// установить смещение
};

#endif	// ifndef _LIBDWARF_H
