//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//                Интерфейсный файл dwarfint.hpp                        //
//                                                                      //
//  Файл определяет внутренние константы реализации библиотеки          //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:32p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef _DWARFINT_H
#define _DWARFINT_H

typedef unsigned long   Dwarf_Word;
typedef signed char     Dwarf_Sbyte;
typedef unsigned char   Dwarf_Ubyte;
typedef signed short    Dwarf_Shalf;
typedef long            Dwarf_Sword;
typedef Dwarf_Small     *Dwarf_Byte_Ptr;

//const Dwarf_Bool True = 1;
//const Dwarf_Bool False = 0;


    // чтобы не было warnings - assigned value that is never used.
#define USED(a) (void)a;

#define _DWARF_DIAGNOSTIC 0

    // для отладки
#if _DEBUG && _DWARF_DIAGNOSTIC
#define DEBUG(a) cout << a;
#else
#define DEBUG(a)
#endif

// контанты для внутреннего использования

#ifndef UCHAR_MAX       // в Win32 уже определены
const Dwarf_Unsigned UCHAR_MAX = Dwarf_Small(-1);
const Dwarf_Unsigned USHRT_MAX = Dwarf_Half(-1);
const Dwarf_Unsigned UINT_MAX = Dwarf_Unsigned(-1);
#endif // UCHAR_MAX

// defined used to get at the elf section numbers and section name
//	indices in symtab for the dwarf sections


// константы для получения индексов секций dwarf в файле elf
// и для получения индексов символов секций dwarf в символьной таблице
// файла elf.

const size_t DEBUG_INFO      = 0;
const size_t DEBUG_LINE      = 1;
const size_t DEBUG_ABBREV    = 2;
const size_t DEBUG_FRAME     = 3;
const size_t DEBUG_ARANGES   = 4;
const size_t DEBUG_PUBNAMES  = 5;
const size_t DEBUG_STR       = 6;
const size_t DEBUG_MACINFO   = 7;

 // число секций debug_* не включая секции перемещений

const size_t NUM_DEBUG_SECTIONS  = DEBUG_MACINFO + 1;

class Dwarf {
    public:

            // массивы для хранения индексов секций elf, индексов 
            // символов секций в символьной таблице файла
            // и индексов секций перемещений

            // индексы секций elf
        static Dwarf_Signed elf_sects[NUM_DEBUG_SECTIONS];
            // индексы символов секций в таблице символов файла
        static Dwarf_Signed sect_name_idx[NUM_DEBUG_SECTIONS];
            // индексы секций перемещений для секций dwarf
        static Dwarf_Signed reloc_sects[NUM_DEBUG_SECTIONS];

            // имена секций в интерфейсе создания
        static char *sectnames[];

            // длины команд строчной информации в интерфейсе создания
        static Dwarf_Ubyte std_opcode_len[];

            // строка augmentation
        static const char *DW_DEBUG_FRAME_AUGMENTER_STRING;

            // пустая строка тоже может быть строкой augmentation
        static const char *DW_EMPTY_STRING;

        static const char *DWARFERR;
        static const char *DWARF_PRO_ERR;

        static Dwarf_Signed get_opc(Dwarf_Unsigned addr_adv,Dwarf_Signed line_adv);

        static Dwarf_Unsigned decode_leb128_uword(Dwarf_Small *&ptr)
            throw(Dwarf_Error);

        static Dwarf_Signed decode_leb128_sword(Dwarf_Small *&ptr) 
            throw(Dwarf_Error);

        static void skip_leb128_word(Dwarf_Small *ptr) throw(Dwarf_Error);


        //-------------------------------------------------------------
        //  Кодурует число val в формате leb128.
        //-------------------------------------------------------------

        // В случае ошибки порождает throw Dwarf_Error_Pro_Encode.
        // буфер для записи числа - параметр space
        // длина буфера параметр splen.
        // число использованных байтов возвращается через параметр nbytes
        // Кодирует как число без знака
        static void encode_leb128_nm(
            Dwarf_Unsigned val,
            int *nbytes,
            char *space,
            int splen) throw(Dwarf_Error);

        // В случае ошибки порождает throw Dwarf_Error_Pro_Encode.
        // буфер для записи числа - параметр space
        // длина буфера параметр splen.
        // число использованных байтов возвращается через параметр nbytes
		// Кодирует как число со знаком

        static void encode_signed_leb128_nm(Dwarf_Signed value, int *nbytes, char *space, int splen)
            throw(Dwarf_Error);


        static Dwarf_Unsigned decode_u_leb128(Dwarf_Small *leb128,
                                    Dwarf_Unsigned& leb128_length);

        static Dwarf_Signed decode_s_leb128(Dwarf_Small *leb128,
                                    Dwarf_Unsigned& leb128_length);

        static int string_valid(void *startptr, void *endptr);

            // вычисляет число байт которое необходимо дабавить, чтобы
            // выровнять n по границе k байт.
            // Подразумевается, что n и k больше нуля.
        static inline Dwarf_Signed PADDING(Dwarf_Signed n, Dwarf_Signed k)
        {
            return ( (k)-1 - ((n)-1)%(k) );
        }


        //-------------------------------------------------------------------
        //
        // Зависимая от операционной системы функция. 
        // Собирает вместе именя каталога и имя файла
        // Сделано под DOS и Windows.
        // Должна работать и под Unix.
        //
        //-------------------------------------------------------------------

        static char * make_full_name(const char *dir,const char *file)
            throw(Dwarf_Error)
        {
            char *name = new char [strlen(dir) + 1 + strlen(file) + 1];

            strcpy(name,dir);
            if ( name[strlen(name) - 1] != '\\' || name[strlen(name) - 1] != '/' ) {
                strcat(name,"/");
            }
            strcat(name,file);
            return name;
        }

        //-------------------------------------------------------------------
        //
        // Зависимая от операционной системы функция. 
        // Собирает вместе два имени каталога и имя файла
        // Сделано под DOS и Windows.
        // Должна работать и под Unix.
        //
        //-------------------------------------------------------------------

        static char * make_full_name(
                const char *main_dir,
                const char *dir,
                const char *file
            ) throw(Dwarf_Error)
        {
            char *name = new char [strlen(main_dir) + 1 + strlen(dir) + 1 + strlen(file) + 1];

            strcpy(name,main_dir);
            if ( name[strlen(name) - 1] != '\\' || name[strlen(name) - 1] != '/' ) {
                strcat(name,"/");
            }
            strcat(name,dir);
            if ( name[strlen(name) - 1] != '\\' || name[strlen(name) - 1] != '/' ) {
                strcat(name,"/");
            }
            strcat(name,file);
            return name;
        }

/*  Эта функция заменена на has_full_path()
        //-------------------------------------------------------------------
        //
        // Зависимая от операционной системы функция. Выдает флаг - содержит
        // ли имя name в себе полный путь или нет.
        // Сделано под DOS и Windows.
        // Возможно будет работать и под Unix.
        //
        //-------------------------------------------------------------------

        static Dwarf_Bool has_path(const char *name)
        {
                // если имя начинается с '\' или '/', то оно содержит 
                // полный путь.
                // Замечание: Windows полное имя может начинаться с '\\'
                // двух обратных косых, не требует дополнительной проверки
            if ( *name == '/' ) return True;
            if ( *name == '\\' ) return True;

                // если имя содержит ':', то оно содержит полный путь
                // специфично для DOS-Windows ("D:\users\dir")
                // Для UNIX эту строчку надо убрать !!!
            if ( strchr( name, ':' ) != NULL ) return True;

	        return False;
        }
*/
        //-------------------------------------------------------------------
        //
        // Зависимая от операционной системы функция. Выдает флаг - является
        // ли путь name, полным путем или нет.
        // Сделано под DOS и Windows.
        // Возможно будет работать и под Unix.
        //
        //-------------------------------------------------------------------

        static Dwarf_Bool has_full_path(const char *name)
        {
                // если имя содержит ':', то оно содержит полный путь
                // специфично для DOS-Windows ("D:\users\dir")
                // Для UNIX эту строчку надо убрать !!!
            if ( strchr(name,':') != NULL ) return True;

                // Замечание: Windows полное имя может начинаться с '\\',
                // двух обратных косых, не требует дополнительной проверки
	        if ( (*name == '\\') || (*name == '/') ) return True;

	        return False;
        }
};

    // константы для интерфейса создания.

    // минимальный размер памяти в одном куске
    // при создании отладочной информации
const size_t CHUNK_SIZE = 4096;

    // для кодирования фреймов вызова
const Dwarf_Small MAX_6_BIT_VALUE = 0x3f;


    // для кодирования информации о строках
const Dwarf_Small VERSION = 2;

    // минимальный размер инструкции в минимально адресуемых словах памяти
const Dwarf_Small MIN_INST_LENGTH = 1;


const Dwarf_Bool DEFAULT_IS_STMT = True;

const Dwarf_Small OPCODE_BASE = 10;
const Dwarf_Small MAX_OPCODE = 255;
const Dwarf_Small STD_OPCODE_LEN = 9;

const Dwarf_Sbyte LINE_BASE = Dwarf_Sbyte(-1);
const Dwarf_Small LINE_RANGE = 4;

const Dwarf_Unsigned MAX_LINE_DIFF  = UINT_MAX;

const Dwarf_Shalf OPC_INCS_ZERO		= -1;
const Dwarf_Shalf OPC_OUT_OF_RANGE  = -2;
const Dwarf_Shalf LINE_OUT_OF_RANGE = -3;

    // максимальная длина выражения location expression
const size_t MAXIMUM_LOC_EXPR_LENGTH = 20;
const size_t ENCODE_SPACE_NEEDED = (2*sizeof(Dwarf_Unsigned));

const Dwarf_Small MORE_BYTES = 0x80;
const Dwarf_Small DATA_MASK = 0x7f;
const Dwarf_Small DIGIT_WIDTH = 7;
const Dwarf_Small SIGN_BIT = 0x40;

    // константы для интерфейса чтения
const Dwarf_Unsigned ABBREV_HASH_TABLE_SIZE = 1000;
const Dwarf_Small DW_EXTENDED_OPCODE = 0;

    // константы для единицы компиляции
const Dwarf_Half CURRENT_VERSION_STAMP = 2;
const Dwarf_Unsigned CU_VERSION_STAMP_SIZE = sizeof(Dwarf_Half);
const Dwarf_Unsigned CU_ADDRESS_SIZE_SIZE = sizeof(Dwarf_Small);

    // константы для фреймовых операций
const Dwarf_Word DW_CIE_ID          = ~((Dwarf_Word)0x0L);
const Dwarf_Small DW_CIE_VERSION    = 1;

	//static const char *DW_CIE_AUGMENTER_STRING_V0 = "z";
const Dwarf_Ubyte DW_DEBUG_FRAME_VERSION = 1;

	// Значение поля смещения для Cie.
const Dwarf_Word DW_CIE_OFFSET = ~((Dwarf_Word)0x0L);

const Dwarf_Ubyte DW_FRAME_INSTR_OPCODE_SHIFT = 6;
const Dwarf_Ubyte DW_FRAME_INSTR_OFFSET_MASK  = 0x3f;


#endif // _DWARFINT_H
