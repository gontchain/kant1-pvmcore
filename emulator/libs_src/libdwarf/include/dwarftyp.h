//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//                Интерфейсный файл dwarftyp.hpp                        //
//                                                                      //
//  Файл определяет типы данных используемые функциями                  //
//  библиотеки libdwarf                                                 //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:32p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef _DWARF_TYPES_H
#define _DWARF_TYPES_H

//-------------------------------------------------------------------//
// Типы с которыми работают функции библиотеки
//-------------------------------------------------------------------//

typedef int             Dwarf_Bool;
typedef unsigned long   Dwarf_Off;
typedef unsigned long   Dwarf_Unsigned;
typedef unsigned short  Dwarf_Half;
typedef unsigned char   Dwarf_Small;
typedef signed long     Dwarf_Signed;
typedef unsigned long   Dwarf_Addr;

typedef void        *   Dwarf_Ptr;      // указатель на инструментальной 
                                        // машине

typedef Dwarf_Unsigned  Dwarf_Tag;

#ifndef _BOOL_
#define _BOOL_
const Dwarf_Bool True = 1;
const Dwarf_Bool False = 0;
#endif


#endif		// _DWARF_TYPES_h
