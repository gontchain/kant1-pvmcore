//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//               Реализационный модуль pro_gpub.cpp                     //
//                                                                      //
//  Файл реализует  функцию Dwarf_P_Debug::transform_pubname_to_disk    //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:33p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------
//
// class Dwarf_P_Pubname to disk transformation
//
//-------------------------------------------------------------------

#include <string.h>

#include "libelf.h"
#include "dwarferr.h"
#include "dwarftyp.h"
#include "dwarf.h"
#include "libdwarf.h"
#include "dwarfint.h"

#include "pro_dbg.h"
#include "pro_pubn.h"

Dwarf_Signed Dwarf_P_Debug::transform_pubname_to_disk(Dwarf_P_CU *cu)
                                                           throw(Dwarf_Error)
{
      // Общее число байтов в секции .debug_pubnames
   Dwarf_Unsigned pubname_num_bytes;

      // Общее число байтов исключая поле длины
   Dwarf_Unsigned adjusted_length;

      // Указатель на первый байт буфера секции .debug_pubnames
   Dwarf_Small *pubname;

      // указатель для сканирования списка символов
   Dwarf_P_Pubname *given_pubname;

      // для заполнения буфера данных секции .debug_pubnames
   Dwarf_Small *pubname_ptr;

      // Указатель на первый байт буфера секции .rel.debug_pubnames
   Dwarf_Small *pubname_reloc;

      // Используется для записи 0
   const Dwarf_Unsigned big_zero = 0;

      // используется для сканирования списка буферов данных секций
   Dwarf_P_Section_Data *debug_sect;

      // размер секции .debug_info
   Dwarf_Unsigned debug_info_size;

      // указатель на запись в таблице перемещений
   Elf32_Rel *elf32_reloc;

      // используется как параметр callback функции создания секции
   Dwarf_Unsigned name_idx;

   // ---------- BEGIN CODE ----------

   if (cu->dpc_pubname == NULL)  // если нет символов то не работаем
      return dpd_n_debug_sect;

      // Вычисляем размер секции .debug_info
      // не будет работать в случае более одной CU
   debug_info_size = 0;
   for (debug_sect = dpd_debug_sects; debug_sect != NULL;
       debug_sect = debug_sect->next)
       if (debug_sect->dpsd_elf_sect_no == Dwarf_Unsigned(Dwarf::elf_sects[DEBUG_INFO]))
           debug_info_size += debug_sect->dpsd_nbytes;

       // Размер заголовка секции .debug_pubnames
   pubname_num_bytes =
       word_size() +     // Размер поля длины
       half_size() +     // Размер поля версии
       off_size()  +     // Размер поля смещения в секции .debug_info
                         // информации данной CU

       word_size();      // Размер поля размера в секции .debug_info.
                         // информации данной CU

      // Add the Size of the names portion.
   for (given_pubname = cu->dpc_pubname; given_pubname != NULL;
                      given_pubname = given_pubname->next)
      pubname_num_bytes +=
           off_size() +              // Размер смещения DIE
           strlen(given_pubname->name()) + 1; // Размер имени глобального имени

       // Добавляем размер последнего нулевого смещения
   pubname_num_bytes += off_size();

   pubname = get_new_chunk(Dwarf::elf_sects[DEBUG_PUBNAMES], pubname_num_bytes);
   pubname_ptr = pubname;

      // Записываем измененную длину секции .debug_pubnames
   adjusted_length = pubname_num_bytes - word_size();
   write_4(&adjusted_length, pubname_ptr);
   pubname_ptr += word_size();

      // Записываем версию в 2 байтах
   Dwarf_Half dh = CURRENT_VERSION_STAMP;
   write_2(&dh, pubname_ptr);

   pubname_ptr += half_size();

      // Записываем смещение данной CU в секции .debug_info
   write_4(&cu->dpc_info_offset, pubname_ptr);
   pubname_ptr += off_size();

      // Записываем размер CU в секции .debug_info.
   write_4( &debug_info_size, pubname_ptr);
   pubname_ptr += word_size();

   Dwarf::reloc_sects[DEBUG_PUBNAMES] = dpd_func(".rel.debug_pubnames",
            SHT_REL, 0, SHN_UNDEF, Dwarf::elf_sects[DEBUG_PUBNAMES], &name_idx);

   pubname_reloc = get_new_chunk(Dwarf::reloc_sects[DEBUG_PUBNAMES],
                                 sizeof(Elf32_Rel));

      // Write relocation record for .debug_info offset.
   elf32_reloc = (Elf32_Rel *)pubname_reloc;
   elf32_reloc->r_offset = word_size() + half_size();
   elf32_reloc->r_info = ELF32_R_INFO(
            Elf32_Half(Dwarf::sect_name_idx[DEBUG_INFO]),
            R_NC_BYTEPTR);

   for (given_pubname = cu->dpc_pubname; given_pubname != NULL;
      given_pubname = given_pubname->next) {

         // Записываем смещение DIE относительно начала CU
      write_4( &(given_pubname->die()->dpd_offset), pubname_ptr);
      pubname_ptr += off_size();

         // Записываем имя символа
      strcpy((char *)pubname_ptr, given_pubname->name());
      pubname_ptr += strlen(given_pubname->name()) + 1;
   }

   write_4(&big_zero, pubname_ptr);

   return dpd_n_debug_sect;
}
