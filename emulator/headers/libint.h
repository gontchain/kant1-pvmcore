//////////////////////////////////////////////////////////////////////////
//                                                                      //
//             Базовое программное обеспечение нейропроцессора          //
//                                                                      //
//     Библиотека доступа к объектным и исполняемым файла формата ELF   //
//                                                                      //
//                      Интерфейсный модуль libint.h                    //
//                                                                      //
//     Интерфейсный файл описывающий типы, классы, и методы классов     //
//     внутрение для библиотеки libelf                                  //
//                                                                      //
//                                                                      //
// Copyright (c) 1997-2005 RC Module                                    //
//  If this code works, it was written by Alex Ruzavin                  //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 9/20/05 10:11p   $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef _LIBINT_H
#define _LIBINT_H

/*#if _DEBUG && defined(_MSC_VER) && defined(_AFX_DEBUG_INCLUDE)

    // experiment
#define new(a) DEBUG_NEW

#else

void *operator new(size_t Size) throw(ELF_ERROR_XALLOC);
void operator delete(void *Type_ptr);
#if _MSC_VER > 1100 || !defined(_MSC_VER)
void *operator new[](size_t Size) throw(ELF_ERROR_XALLOC);
void operator delete[](void * Type_ptr);
#endif // _MSC_VER

#define new(a) new

#endif // _AFX_DEBUG_INCLUDE
*/


struct Elf32_Libhdr_f {
    public:
        Elf32_Word  lib_name;   // смещение имени с таблице строк
        Elf32_Word  lib_date;   // остальное как в Elf32_Libhdr
        Elf32_Off   lib_offset;
        Elf32_Word  lib_size;
        Elf32_Word  lib_mode;

        Elf32_Libhdr_f() 
            : lib_date(0),
            lib_offset(0),
            lib_size(0),
            lib_mode(0),
            lib_name(0)
        {  }
};

struct Elf32_LibSym_f {
    public:
        Elf32_Word  ls_name;   // смещение имени в таблице строк
        Elf32_Word  ls_index;  // номер элемента в котором символ определен
        Elf32_Sword ls_bind;   // связывание символа (GLOBAL,WEAK)
};

    // внутренний класс libelf. описывает блок данных провязанный в список
    // используется в классе ELF_FILE для хранения списка буфера строк
class ELF_INTERNAL_BLOCK {
    private:
        char * Buffer;
        Elf32_Word Size;
        ELF_INTERNAL_BLOCK * Next;

    public:
        ELF_INTERNAL_BLOCK() : Buffer(0), Size(0), Next(0) {  }
        ELF_INTERNAL_BLOCK( Elf32_Word BufferSize );
        ~ELF_INTERNAL_BLOCK();

        char * GetBuffer() const { return Buffer; }
        Elf32_Word GetSize() const { return Size; }
        ELF_INTERNAL_BLOCK * GetNext() const { return Next; }

        void AddBlock( ELF_INTERNAL_BLOCK * Block )
        {
            assert( Next == 0 );
            Next = Block;
        }
};

/*
class Elf32_T_Const_libhdr_f {
    private:

        static Elf_T_Type * Object;

    public:
        operator Elf_T_Type * () const
        {
            if ( Object )
                return Object;

            Object = new Elf_T_Int_Type< Elf32_T_Const_libhdr_f >;
            return Object;
        }

    public:
        static Elf32_Word Size() { return 20; } // sizeof(Elf32_Libhdr_f);

        static void ToF(unsigned char *dest,unsigned char *src,unsigned e);
        static void ToM(unsigned char *dest,unsigned char *src,unsigned e)
        {
            ToF(dest,src,e);
        }
};

class Elf32_T_libhdr_f : public Elf_T_Int_Type< Elf32_T_Const_libhdr_f > {
};

class Elf32_T_Const_libsym_f {
    private:

        static Elf_T_Type * Object;

    public:
        operator Elf_T_Type * () const
        {
            if ( Object )
                return Object;

            Object = new Elf_T_Int_Type< Elf32_T_Const_libsym_f >;
            return Object;
        }

    public:
        static Elf32_Word Size() { return 12; } // sizeof(Elf32_LibSym_f);

        static void ToF(unsigned char *dest,unsigned char *src,unsigned e);
        static void ToM(unsigned char *dest,unsigned char *src,unsigned e)
        {
            ToF(dest,src,e);
        }
};

class Elf32_T_libsym_f : public Elf_T_Int_Type< Elf32_T_Const_libsym_f > {
};

static const Elf32_T_Const_libhdr_f ELF32_T_LIBHDR_F;
static const Elf32_T_Const_libsym_f ELF32_T_LIBSYM_F;
*/

#endif // _LIBINT_H


//////////////////////////////////////////////////////////////////////////
//                                                                      //
//                   Конец интерфейсного модуля libint.hpp              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

