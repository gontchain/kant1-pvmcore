/*
 * PPDL address table
 *
 * Copyright (c) 2017 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#ifndef ADDR_TABLE_H
#define ADDR_TABLE_H

#include <string.h>

#define SIZE_ARR_ADDR_INFO 76
struct AddrInfo {
    unsigned long long addr;
    char description[600];
};

struct AddrInfo addrInfo[SIZE_ARR_ADDR_INFO];

unsigned int find_index_via_addr(unsigned long long);
#define get_addr_description(addr) find_index_via_addr(addr) == -1 ? "" : addrInfo[find_index_via_addr(addr)].description

unsigned int find_index_via_addr(unsigned long long addr) {
    unsigned int i;
    unsigned int ret = -1;
    for (i = 0; i < SIZE_ARR_ADDR_INFO; i++)
        if (addr == addrInfo[i].addr)
            ret = i;
    return ret;
}

void init_struct_addrInfo() {
    static short initialized = 0;
    if (initialized)
        return;
    initialized = 1;
    addrInfo[0].addr = 0x40000000; strcpy(addrInfo[0].description, "ID ЧТ Регистр идентификации процессорной системы. ");
    addrInfo[1].addr = 0x40000002; strcpy(addrInfo[1].description, "SYNC ЧТ/ЗП Регистр межпроцессорной синхронизации. ");
    addrInfo[2].addr = 0x40000004; strcpy(addrInfo[2].description, "GPIO ЧТ/ЗП Регистр входов и выходов общего назначения процессорной системы NMCell. Запись устанавливает значение на выходах общего назначения, чтение возвращает текущее состояние входов общего назначения. ");
    addrInfo[3].addr = 0x40000006; strcpy(addrInfo[3].description, "CPC ЧТ/ЗП Регистр управления передающей частью коммуникационного порта. ");
    addrInfo[4].addr = 0x40000800; strcpy(addrInfo[4].description, "TMC0 ЧТ/ЗП Регистр счётчика таймера 0 ");
    addrInfo[5].addr = 0x40000802; strcpy(addrInfo[5].description, "TMM0 ЧТ/ЗП Регистр настройки таймера 0 ");
    addrInfo[6].addr = 0x40000804; strcpy(addrInfo[6].description, "TMC1 ЧТ/ЗП Регистр счётчика таймера 1 ");
    addrInfo[7].addr = 0x40000806; strcpy(addrInfo[7].description, "TMM1 ЧТ/ЗП Регистр настройки таймера 1 ");
    addrInfo[8].addr = 0x40001000; strcpy(addrInfo[8].description, "CSR ЧТ/ЗП Регистр управления ");
    addrInfo[9].addr = 0x40001002; strcpy(addrInfo[9].description, "IRQMask ЧТ/ЗП Маска прерывания ");
    addrInfo[10].addr = 0x40001004; strcpy(addrInfo[10].description, "RdAddr ЧТ Регистр адреса чтения ");
    addrInfo[11].addr = 0x40001006; strcpy(addrInfo[11].description, "WrAddr ЧТ Регистр адреса записи");
    addrInfo[12].addr = 0x40001400; strcpy(addrInfo[12].description, "RD_MASK ЧТ/ЗП Маска защищаемых сегментов: 0 - обращение в данный сегмент по чтению разрешено, 1 - обращение в данный сегментпо чтению блокируется. ");
    addrInfo[13].addr = 0x40001402; strcpy(addrInfo[13].description, "RD_MASK_SET ЗП Побитовая установка регистра RD_MASK ");
    addrInfo[14].addr = 0x40001404; strcpy(addrInfo[14].description, "RD_MASK_CLEAR ЗП Побитовый сброс регистра RD_MASK ");
    addrInfo[15].addr = 0x40001406; strcpy(addrInfo[15].description, "RD_MASK_NULL ЗП Обнуление регистра RD_MASK ");
    addrInfo[16].addr = 0x40001408; strcpy(addrInfo[16].description, "RD_IRQ_STATUS_RAW ЧТ Статус запросов на прерывание без учёта маски: 0 - обращений по чтению в данный сегмент не было, 1 - зафиксировано обращение по чтению в данный сегмент. ");
    addrInfo[17].addr = 0x4000140A; strcpy(addrInfo[17].description, "RD_IRQ_STATUS_RAW_SET ЗП Побитовая установка RD_IRQ_STATUS_RAW (только для отладки) ");
    addrInfo[18].addr = 0x4000140C; strcpy(addrInfo[18].description, "RD_IRQ_STATUS_RAW_CLEAR ЗП Побитовый сброс регистра RD_IRQ_STATUS_RAW ");
    addrInfo[19].addr = 0x4000140E; strcpy(addrInfo[19].description, "RD_IRQ_STATUS_RAW_NULL ЗП Обнуление регистра RD_IRQ_STATUS_RAW ");
    addrInfo[20].addr = 0x40001410; strcpy(addrInfo[20].description, "RD_IRQ_MASK ЧТ/ЗП Маска запросов на прерывание от регистра RD_IRQ_STATUS_RAW: 0 - прерывание запрещено, 1 - прерывание разрешено. ");
    addrInfo[21].addr = 0x40001412; strcpy(addrInfo[21].description, "RD_IRQ_MASK_SET ЗП Побитовая установка регистра RD_IRQ_MASK ");
    addrInfo[22].addr = 0x40001414; strcpy(addrInfo[22].description, "RD_IRQ_MASK_CLEAR ЗП Побитовый сброс регистра RD_IRQ_MASK ");
    addrInfo[23].addr = 0x40001416; strcpy(addrInfo[23].description, "RD_IRQ_MASK_NULL ЗП Обнуление регистра RD_IRQ_MASK ");
    addrInfo[24].addr = 0x40001418; strcpy(addrInfo[24].description, "RD_IRQ_STATUS ЧТ Статус запросов на прерывание с учётом маски: 0 - нет запроса, 1 - есть запрос. ");
    addrInfo[25].addr = 0x4000141A; strcpy(addrInfo[25].description, "Зарезервировано - ");
    addrInfo[26].addr = 0x4000141C; strcpy(addrInfo[26].description, "Зарезервировано - ");
    addrInfo[27].addr = 0x4000141E; strcpy(addrInfo[27].description, "RD_IRQ_STATUS_NULL ЗП Обнуление незамаскированных запросов на прерывание (сбрасываются все биты регистра RD_IRQ_STATUS и все биты регистра RD_IRQ_STATUS_RAW, для которых установлен бит RD_IRQ_MASK). ");
    addrInfo[28].addr = 0x40001440; strcpy(addrInfo[28].description, "WR_MASK ЧТ/ЗП Маска защищаемых сегментов: 0 - обращение в данный сегмент по чтению разрешено, 1 - обращение в данный сегмент по чтению блокируется. ");
    addrInfo[29].addr = 0x40001442; strcpy(addrInfo[29].description, "WR_MASK_SET ЗП Побитовая установка регистра WR_MASK ");
    addrInfo[30].addr = 0x40001444; strcpy(addrInfo[30].description, "WR_MASK_CLEAR ЗП Побитовый сброс регистра WR_MASK ");
    addrInfo[31].addr = 0x40001446; strcpy(addrInfo[31].description, "WR_MASK_NULL ЗП Обнуление регистра WR_MASK ");
    addrInfo[32].addr = 0x40001448; strcpy(addrInfo[32].description, "WR_IRQ_STATUS_RAW ЧТ Статус запросов на прерывание без учёта маски: 0 - обращений по чтению в данный сегмент не было, 1 - зафиксировано обращение по чтению в данный сегмент. ");
    addrInfo[33].addr = 0x4000144A; strcpy(addrInfo[33].description, "WR_IRQ_STATUS_RAW_SET ЗП Побитовая установка WR_IRQ_STATUS_RAW (только для отладки) ");
    addrInfo[34].addr = 0x4000144C; strcpy(addrInfo[34].description, "WR_IRQ_STATUS_RAW_CLEAR ЗП Побитовый сброс регистра WR_IRQ_STATUS_RAW ");
    addrInfo[35].addr = 0x4000144E; strcpy(addrInfo[35].description, "WR_IRQ_STATUS_RAW_NULL ЗП Обнуление регистра WR_IRQ_STATUS_RAW ");
    addrInfo[36].addr = 0x40001450; strcpy(addrInfo[36].description, "WR_IRQ_MASK ЧТ/ЗП Маска запросов на прерывание от регистра WR_IRQ_STATUS_RAW: 0 - прерывание запрещено, 1 - прерывание разрешено. ");
    addrInfo[37].addr = 0x40001452; strcpy(addrInfo[37].description, "WR_IRQ_MASK_SET ЗП Побитовая установка регистра WR_IRQ_MASK ");
    addrInfo[38].addr = 0x40001454; strcpy(addrInfo[38].description, "WR_IRQ_MASK_CLEAR ЗП Побитовый сброс регистра WR_IRQ_MASK ");
    addrInfo[39].addr = 0x40001456; strcpy(addrInfo[39].description, "WR_IRQ_MASK_NULL ЗП Обнуление регистра WR_IRQ_MASK ");
    addrInfo[40].addr = 0x40001458; strcpy(addrInfo[40].description, "WR_IRQ_STATUS ЧТ Статус запросов на прерывание с учётом маски: 0 - нет запроса, 1 - есть запрос. ");
    addrInfo[41].addr = 0x4000145A; strcpy(addrInfo[41].description, "Зарезервировано - ");
    addrInfo[42].addr = 0x4000145C; strcpy(addrInfo[42].description, "Зарезервировано - ");
    addrInfo[43].addr = 0x4000145E; strcpy(addrInfo[43].description, "WR_IRQ_STATUS_NULL ЗП Обнуление незамаскированных запросов на прерывание (сбрасываются все биты регистра WR_IRQ_STATUS и все биты регистра WR_IRQ_STATUS_RAW, для которых установлен бит WR_IRQ_MASK). ");
    addrInfo[44].addr = 0x40000400; strcpy(addrInfo[44].description, "IRRL ЧТ Регистр запросов на прерывание с номерами от 0 до 31. Значение 1 в бите данного регистра показывает наличие запроса, для которого ещё не выполнена команда перехода по адресу-вектору прерывания. Программный сброс битов данного регистра производится только с помощью регистра IRRL_CLR. ");
    addrInfo[45].addr = 0x40000402; strcpy(addrInfo[45].description, "IRRL_SET ЧТ/ЗП Побитовая установка регистра IRRL. ");
    addrInfo[46].addr = 0x40000404; strcpy(addrInfo[46].description, "IRRL_CLR ЧТ/ЗП Побитовый сброс регистра IRRL. Программный сброс бита регистра IRRL следует делать, когда данный запрос замаскирован. ");
    addrInfo[47].addr = 0x40000406; strcpy(addrInfo[47].description, "- - Зарезервировано. ");
    addrInfo[48].addr = 0x40000408; strcpy(addrInfo[48].description, "IMRL ЧТ/ЗП Регистр маски прерываний с номерами о 0 до 31. Значение 0 - прерывание запрещено, 1 - прерывание разрешено. ");
    addrInfo[49].addr = 0x4000040A; strcpy(addrInfo[49].description, "IMRL_SET ЧТ/ЗП Побитовая установка регистра IMRL. ");
    addrInfo[50].addr = 0x4000040C; strcpy(addrInfo[50].description, "IMRL_CLR ЧТ/ЗП Побитовый сброс регистра IMRL. ");
    addrInfo[51].addr = 0x4000040E; strcpy(addrInfo[51].description, "IMRL_NULL ЧТ/ЗП Сброс всех битов регистра IMRL. ");
    addrInfo[52].addr = 0x40000410; strcpy(addrInfo[52].description, "IRPL ЧТ/ЗП Регистров приоритетов прерываний с номерами от 0 до 31. Значение 0 – высокий приоритет, 1 – низкий приоритет. ");
    addrInfo[53].addr = 0x40000412; strcpy(addrInfo[53].description, "IRPL_SET ЧТ/ЗП Побитовая установка регистра IRPL. ");
    addrInfo[54].addr = 0x40000414; strcpy(addrInfo[54].description, "IRPL_CLR ЧТ/ЗП Побитовый сброс регистра IRPL. ");
    addrInfo[55].addr = 0x40000416; strcpy(addrInfo[55].description, "IRPL_NULL ЧТ/ЗП Сброс всех битов регистра IRPL. ");
    addrInfo[56].addr = 0x40000418; strcpy(addrInfo[56].description, "IASL ЧТ Регистр подтверждения и статуса запросов с номерами от 0 до 31. Значение 0 - запрос обработан, 1 - запрос обрабатывается (выполнен или выполняется переход по адресу-вектору, но бит регистра IASL ещё не сброшен). ");
    addrInfo[57].addr = 0x4000041A; strcpy(addrInfo[57].description, "- - Зарезервировано. ");
    addrInfo[58].addr = 0x4000041C; strcpy(addrInfo[58].description, "IASL_CLR ЧТ/ЗП Побитовый сброс регистра IASL. ");
    addrInfo[59].addr = 0x4000041E; strcpy(addrInfo[59].description, "- - Зарезервировано. ");
    addrInfo[60].addr = 0x40000440; strcpy(addrInfo[60].description, "IRRH ЧТ Регистр запросов на прерывание с номерами от 32 до 39. Значение 1 в бите данного регистра показывает наличие запроса, для которого ещё не выполнена команда перехода по адресу-вектору прерывания. Программный сброс битов данного регистра производится только с помощью регистра IRRH_CLR. ");
    addrInfo[61].addr = 0x40000442; strcpy(addrInfo[61].description, "IRRH_SET ЧТ/ЗП Побитовая установка регистра IRRH. ");
    addrInfo[62].addr = 0x40000444; strcpy(addrInfo[62].description, "IRRH_CLR ЧТ/ЗП Побитовый сброс регистра IRRH. Программный сброс бита регистра IRRH следует делать, когда данный запрос замаскирован. ");
    addrInfo[63].addr = 0x40000446; strcpy(addrInfo[63].description, "- - Зарезервировано. ");
    addrInfo[64].addr = 0x40000448; strcpy(addrInfo[64].description, "IMRH ЧТ/ЗП Регистр маски прерываний с номерами о 0 до 31. Значение 0 - прерывание запрещено, 1 - прерывание разрешено. ");
    addrInfo[65].addr = 0x4000044A; strcpy(addrInfo[65].description, "IMRH_SET ЧТ/ЗП Побитовая установка регистра IMRH. ");
    addrInfo[66].addr = 0x4000044C; strcpy(addrInfo[66].description, "IMRH_CLR ЧТ/ЗП Побитовый сброс регистра IMRH. ");
    addrInfo[67].addr = 0x4000044E; strcpy(addrInfo[67].description, "IMRH_NULL ЧТ/ЗП Сброс всех битов регистра IMRH. ");
    addrInfo[68].addr = 0x40000450; strcpy(addrInfo[68].description, "IRPH ЧТ/ЗП Регистров приоритетов прерываний с номерами от 32 до 39. Значение 0 – высокий приоритет, 1 – низкий приоритет. ");
    addrInfo[69].addr = 0x40000452; strcpy(addrInfo[69].description, "IRPH_SET ЧТ/ЗП Побитовая установка регистра IRPH. ");
    addrInfo[70].addr = 0x40000454; strcpy(addrInfo[70].description, "IRPH_CLR ЧТ/ЗП Побитовый сброс регистра IRPH. ");
    addrInfo[71].addr = 0x40000456; strcpy(addrInfo[71].description, "IRPH_NULL ЧТ/ЗП Сброс всех битов регистра IRPH. ");
    addrInfo[72].addr = 0x40000458; strcpy(addrInfo[72].description, "IASH ЧТ Регистр подтверждения и статуса запросов с номерами от 32 до 39. Значение 0 - запрос обработан, 1 - запрос обрабатывается (выполнен или выполняется переход по адресу-вектору, но бит регистра IASH ещё не сброшен). ");
    addrInfo[73].addr = 0x4000045A; strcpy(addrInfo[73].description, "Зарезервировано. ");
    addrInfo[74].addr = 0x4000045C; strcpy(addrInfo[74].description, "IASH_CLR ЧТ/ЗП Побитовый сброс регистра IASH. ");
    addrInfo[75].addr = 0x4000045E; strcpy(addrInfo[75].description, "Зарезервировано.");
}

#endif
