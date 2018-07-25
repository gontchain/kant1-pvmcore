//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//                Интерфейсный файл dwarferr.hpp                        //
//                                                                      //
//  Файл определяет типы исключительных ситуаций                        //
//  порождаемых функциями библиотеки                                    //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:32p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef _LIBDWARF_ERR_H
#define _LIBDWARF_ERR_H

class Dwarf_No_Entry {
};

class Dwarf_Error : public ELF_ERROR {
	public:
		Dwarf_Error(const char *s = 0,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : ELF_ERROR(s,s1,s2,s3) {}
		Dwarf_Error(ELF_ERROR &e) : ELF_ERROR(e) {}
};

class Dwarf_Error_Internal : public Dwarf_Error {
	public:
		Dwarf_Error_Internal(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_Debug : public Dwarf_Error {
	public:
		Dwarf_Error_Debug(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_CU : public Dwarf_Error {
	public:
		Dwarf_Error_CU(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_Abbrev : public Dwarf_Error {
	public:
		Dwarf_Error_Abbrev(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_Elf : public Dwarf_Error {
	public:
		Dwarf_Error_Elf(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
		Dwarf_Error_Elf(ELF_ERROR &e) : Dwarf_Error(e) {}
};

class Dwarf_Error_Frame : public Dwarf_Error {
	public:
		Dwarf_Error_Frame(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_Frame_Found : public Dwarf_Error_Frame {
	public:
		Dwarf_Error_Frame_Found(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Frame(s,s1,s2,s3) {}
};

class Dwarf_Error_Cie : public Dwarf_Error {
	public:
		Dwarf_Error_Cie(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_Fde : public Dwarf_Error {
	public:
		Dwarf_Error_Fde(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_Tab : public Dwarf_Error {
	public:
		Dwarf_Error_Tab(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_Tab_Range : public Dwarf_Error_Tab {
	public:
		Dwarf_Error_Tab_Range(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Tab(s,s1,s2,s3) {}
};

class Dwarf_Error_Tab_Match : public Dwarf_Error_Tab {
	public:
		Dwarf_Error_Tab_Match(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Tab(s,s1,s2,s3) {}
};

class Dwarf_Error_Die : public Dwarf_Error {
	public:
		Dwarf_Error_Die(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_Die_Attribute : public Dwarf_Error_Die {
	public:
		Dwarf_Error_Die_Attribute(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Die(s,s1,s2,s3) {}
};

class Dwarf_Error_CU_Line : public Dwarf_Error_CU {
	public:
		Dwarf_Error_CU_Line(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_CU(s,s1,s2,s3) {}
};

class Dwarf_Error_Arange : public Dwarf_Error {
	public:
		Dwarf_Error_Arange(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_Global : public Dwarf_Error {
	public:
		Dwarf_Error_Global(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_Macro : public Dwarf_Error {
	public:
		Dwarf_Error_Macro(const char *s,const char *s1 = 0,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error(s,s1,s2,s3) {}
};

class Dwarf_Error_Pro : public Dwarf_Error {
	public:
		Dwarf_Error_Pro(const char *s1,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error("Dwarf producer error - ",s1,s2,s3) {}
		Dwarf_Error_Pro(ELF_ERROR &e) : Dwarf_Error(e) {}
};

class Dwarf_Error_Pro_Internal: public Dwarf_Error_Pro {
	public:
		Dwarf_Error_Pro_Internal(const char *s1,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Pro(s1,s2,s3) {}
};

class Dwarf_Error_Pro_Encode : public Dwarf_Error_Pro {
	public:
		Dwarf_Error_Pro_Encode(const char *s1,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Pro(s1,s2,s3) {}
};

class Dwarf_Error_Pro_Expr : public Dwarf_Error_Pro {
	public:
		Dwarf_Error_Pro_Expr(const char *s1,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Pro(s1,s2,s3) {}
};

class Dwarf_Error_Pro_Attribute : public Dwarf_Error_Pro {
	public:
		Dwarf_Error_Pro_Attribute(const char *s1,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Pro(s1,s2,s3) {}
};

class Dwarf_Error_Pro_CU : public Dwarf_Error_Pro {
	public:
		Dwarf_Error_Pro_CU(const char *s1,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Pro(s1,s2,s3) {}
};

class Dwarf_Error_Pro_Debug : public Dwarf_Error_Pro {
	public:
		Dwarf_Error_Pro_Debug(const char *s1,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Pro(s1,s2,s3) {}
};

class Dwarf_Error_Pro_Fde : public Dwarf_Error_Pro {
	public:
		Dwarf_Error_Pro_Fde(const char *s1,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Pro(s1,s2,s3) {}
};

class Dwarf_Error_Pro_Fde_Overflow : public Dwarf_Error_Pro_Fde {
	public:
		Dwarf_Error_Pro_Fde_Overflow(const char *s1,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Pro_Fde(s1,s2,s3) {}
};

class Dwarf_Error_Pro_Elf : public Dwarf_Error_Pro {
	public:
		Dwarf_Error_Pro_Elf(const char *s1,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Pro(s1,s2,s3) {}
		Dwarf_Error_Pro_Elf(ELF_ERROR &e) : Dwarf_Error_Pro(e) {}
};

class Dwarf_Error_Pro_Line : public Dwarf_Error_Pro {
	public:
		Dwarf_Error_Pro_Line(const char *s1,const char *s2 = 0,
			const char *s3 = 0) : Dwarf_Error_Pro(s1,s2,s3) {}
};

    // Ошибка порождаемая при невозможности вычислить 
    // отложенную ссылку на DIE с индексом index
class Dwarf_Error_Pro_Attribute_Delayed_Ref : public Dwarf_Error_Pro_Attribute {
    protected:
        long index;
	public:
		Dwarf_Error_Pro_Attribute_Delayed_Ref(
                long ref_index,
                const char *s1,
                const char *s2 = 0,
			    const char *s3 = 0
            ) : Dwarf_Error_Pro_Attribute(s1,s2,s3),
            index( ref_index )
        {}

            // выдает индекс DIE на которую ссылаются
        long get_index() const { return index; }
};

    // Ошибка порождаемая при невозможности вычислить 
    // отложенную ссылку на символ с индексом index
class Dwarf_Error_Pro_Attribute_Delayed_Addr : public Dwarf_Error_Pro_Attribute {
    protected:
        long index;
	public:
		Dwarf_Error_Pro_Attribute_Delayed_Addr(
                long addr_index,
                const char *s1,
                const char *s2 = 0,
			    const char *s3 = 0
            ) : Dwarf_Error_Pro_Attribute(s1,s2,s3),
            index( addr_index )
        {}

            // выдает индекс символа на который невозможно 
            // вычислить ссылку
        long get_index() const { return index; }
};

#endif	// _LIBDWARF_ERR_H
