//////////////////////////////////////////////////////////////////////////
//                                                                      //
//            Базовое программное обеспечение нейропроцессора           //
//                                                                      //
//       Библиотека доступа к отладочной информации формата DWARF       //
//                                                                      //
//               Реализационный модуль pro_garn.cpp                     //
//                                                                      //
//  Файл реализует  функцию Dwarf_P_Debug::transform_arange_to_disk     //
//                                                                      //
//                                                                                         //
//  If this code works, it was                                                         //
//  If not, I don't know who wrote it.                                  //
//                                                                      //
// $Revision:: 1     $      $Date:: 7/21/05 5:33p    $                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------
//
// class Dwarf_P_Arange
//
//---------------------------------------------------------

#include <string.h>

#include "libelf.h"
#include "dwarferr.h"
#include "dwarftyp.h"
#include "dwarf.h"
#include "libdwarf.h"
#include "dwarfint.h"

#include "pro_aran.h"
#include "pro_dbg.h"

Dwarf_Signed Dwarf_P_Debug::transform_arange_to_disk(Dwarf_P_CU *cu) throw(Dwarf_Error)
{
		 // общее число байтов в секции .debug_aranges
	Dwarf_Unsigned arange_num_bytes;

		 // число байтов которое надо прибавить к началу самих диапазонов
		 // чтобы выровнять по границе двух адресов
	Dwarf_Small remainder;

		 // общее число байтов исключая само поле длины
	Dwarf_Unsigned adjusted_length;

		 // общее число байтов в секции .rel.debug_aranges
	Dwarf_Unsigned arange_reloc_num_bytes;

		 // указатель на первый байт буфера для секции .debug_aranges
	Dwarf_Small *arange;

		 // указатель используется при заполнении секции .debug_aranges
	Dwarf_Small *arange_ptr;

		 // указатель на первый байт буфера для секции .rel.debug_aranges
	Dwarf_Small *arange_reloc;

		 // указатель используется при заполнении секции .rel.debug_aranges
	Dwarf_Small *arange_reloc_ptr;

		 // указатель для сканирования списка адресных диапазонов
	Dwarf_P_Arange *given_arange;

		 // Используется когда нужно записать 0 в буфер
	const Dwarf_Unsigned  big_zero = 0;

		 // запись перемещения. используется далее
	Elf32_Rel *elf32_reloc;

      // индекс символа соответствующего секции .rel.debug_arange
	Dwarf_Unsigned name_idx;

      // временная переменная для записи 4-х байтовых величин в файл
   Dwarf_Unsigned dw;

	// -------- BEGIN CODE ----------

   if (cu->dpc_arange == NULL)  // если нет символов то не работаем
      return dpd_n_debug_sect;

      // Размер начальных байтов секции .debug_aranges
   arange_num_bytes =   word_size() +   // размер поля длины.
                        half_size() +   // размер поля версии.
                        word_size() +   // размер смещения в .debug_info.
                        byte_size() +   // размер поля размера адреса.
                        byte_size();    // размер поля размера сегмента.

      // Выравнивает размер так, что информация об адресных диапазонах
      // начинается со смещения выровненного на двойную величину адреса
      // так требует стандарт DWARF v2.

   remainder = Dwarf_Small(arange_num_bytes % (2 * addr_size()));
   if (remainder != 0)
      arange_num_bytes += ( 2 * addr_size() ) - remainder;

      // Добавляет байты для самих адресных диапазонов
   arange_num_bytes += word_size() * 2 * (cu->dpc_arange_count + 1);

      // выделяем память
   arange = get_new_chunk (Dwarf::elf_sects[DEBUG_ARANGES], arange_num_bytes);
   arange_ptr = arange;

      // Записываем общую длину секции .debug_aranges
   adjusted_length = arange_num_bytes - word_size();
   write_4(&adjusted_length, arange_ptr);
   arange_ptr += word_size();

      // Записываем версию .

   Dwarf_Half dh = CURRENT_VERSION_STAMP;
   write_2(&dh,arange_ptr);

   arange_ptr += half_size();

      // Записываем смещенние в секции .debug_info

   write_4(&(cu->dpc_info_offset),arange_ptr);
   arange_ptr += word_size();

      // Записываем размер адреса
   *arange_ptr = Dwarf_Small(addr_size());  // на нейропроцессоре адрес всегда 32 бита
   arange_ptr++;

       // Записываем размер сегментной части адреса.
       // на нейропроцессоре всегда 0.
   *arange_ptr = 0;
   arange_ptr++;

       // Пропускаем байты для выравнивания начала информации об диапазонах
       // по границе двойного размера адреса
   if (remainder != 0)
       arange_ptr += (2*addr_size()) - remainder;

   arange_reloc_num_bytes = ELF32_T_REL_FSIZE * (cu->dpc_arange_count + 1);

   Dwarf::reloc_sects[DEBUG_ARANGES] = dpd_func(".rel.debug_aranges", SHT_REL, 0,
                     SHN_UNDEF, Dwarf::elf_sects[DEBUG_ARANGES], &name_idx);

   if (Dwarf::reloc_sects[DEBUG_ARANGES] == -1)
		throw Dwarf_Error_Pro_Elf("error creating section .rel.debug_aranges");

   arange_reloc = get_new_chunk ( Dwarf::reloc_sects[DEBUG_ARANGES],
                                 arange_reloc_num_bytes);

   arange_reloc_ptr = arange_reloc;

      // Создаем запись в таблице перемещений для смещения в секции .debug_info
   elf32_reloc = (Elf32_Rel *)arange_reloc_ptr;
   elf32_reloc->r_offset = cu->dpc_info_offset + word_size() + half_size();
   elf32_reloc->r_info = ELF32_R_INFO(Elf32_Half(Dwarf::sect_name_idx[DEBUG_INFO]), R_NC_BYTEPTR);

   arange_reloc_ptr += ELF32_T_REL_FSIZE;

   for (given_arange = cu->dpc_arange; given_arange != NULL;
               given_arange = given_arange->next) {

         // Создаем запись в таблице перемещения для адреса начала диапазона
      elf32_reloc = (Elf32_Rel *)arange_reloc_ptr;
      elf32_reloc->r_offset = arange_ptr - arange; // если более 1 CU, то переделать
      elf32_reloc->r_info = ELF32_R_INFO(Elf32_Half(given_arange->sym_idx()), R_NC_ADDR);
      arange_reloc_ptr += ELF32_T_REL_FSIZE;

           // Записываем начало диапазона
      dw = given_arange->addr();
      write_4(&dw, arange_ptr);
      arange_ptr += word_size();

           // Записываем длину диапазона
      dw = given_arange->len();
      write_4(&dw, arange_ptr);
      arange_ptr += word_size();
   }

   write_4(&big_zero, arange_ptr);
   arange_ptr += word_size();
   write_4(&big_zero, arange_ptr);

	return dpd_n_debug_sect;
}
