#include "cpu.h"
#include "disas_ppdl_insn.h"
#pragma GCC diagnostic ignored "-Wempty-body"
#pragma GCC diagnostic ignored "-Wparentheses"

#if defined(CONFIG_DEBUG)
#   define ERROR_PRINT(...)// printf("::GEN ERROR:: error in " __VA_ARGS__ "\n");
#   define INFO_PRINT(...)// printf("::GEN INFO:: " __VA_ARGS__ );
#else
#   define ERROR_PRINT(...)
#   define INFO_PRINT(...)
#endif

#define OPCODE(type) (type)ocode

int Scalar_checker(uint64_t insn) {
    if ( ((insn & 0x72300000) == 0x50100000)  ) {
        return 1;
    }
    if ( ((insn & 0xe2000000) == 0x20000000)  ) {
        return 1;
    }
    if ( ((insn & 0xe2000000) == 0x22000000)  ) {
        return 1;
    }
    if ( ((insn & 0xf0000000) == 0x70000000)  ) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0x52100000)  ) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0x56100000)  ) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0x5a100000)  ) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0x5e100000)  ) {
        return 1;
    }
    if ( ((insn & 0xfc300000) == 0x200000)  ) {
        return 1;
    }
    if ( ((insn & 0xfc300000) == 0x4200000)  ) {
        return 1;
    }
    if ( ((insn & 0xfc300000) == 0x8200000)  ) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0xc200000)  ) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0xe200000)  ) {
        return 1;
    }
    if ( ((insn & 0xfff00000) == 0x7300000)  ) {
            return 1;
        }
    if ( ((insn & 0xfff00000) == 0x6300000)  ) {
    return 1;
    }
    return 0;
}
int Scalar64_checker(uint64_t insn) {
    if ( ((insn & 0x72300000) == 0x40100000)) {
        return 1;
    }
    if ( ((insn & 0xfe000000) == 0x60000000)) {
        return 1;
    }
    if ( ((insn & 0xfe000000) == 0x64000000)) {
        return 1;
    }
    if ( ((insn & 0xfe000000) == 0x68000000)) {
        return 1;
    }
    if ( ((insn & 0xfe000000) == 0x6c000000)) {
        return 1;
    }
    if ( ((insn & 0xfe000000) == 0x62000000)) {
        return 1;
    }
    if ( ((insn & 0xfe000000) == 0x66000000)) {
        return 1;
    }
    if ( ((insn & 0xfe000000) == 0x6a000000)) {
        return 1;
    }
    if ( ((insn & 0xfe000000) == 0x6e000000)) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0x42100000)) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0x46100000)) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0x4a100000)) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0x4e100000)) {
        return 1;
    }
    if ( ((insn & 0xf0300000) == 0x40000000)) {
        return 1;
    }
    if ( ((insn & 0xfc300000) == 0x40200000)) {
        return 1;
    }
    if ( ((insn & 0xfc300000) == 0x44200000)) {
        return 1;
    }
    if ( ((insn & 0xfc300000) == 0x48200000)) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0x4c200000)) {
        return 1;
    }
    if ( ((insn & 0xfe300000) == 0x4e200000)) {
        return 1;
    }
    return 0;
}
int Vector_checker(uint64_t insn) {
    if ( ((insn & 0xe0380000) == 0x0)) {
         return 1;
    }
    if ( ((insn & 0xfe200000) == 0x0)) {
         return 1;
    }
    if ( ((insn & 0xfe200000) == 0x4000000)) {
         return 1;
    }
    if ( ((insn & 0xfe200000) == 0x8000000)) {
         return 1;
    }
    if ( ((insn & 0xfe200000) == 0x10000000)) {
         return 1;
    }
    if ( ((insn & 0xfe200000) == 0x14000000)) {
         return 1;
    }
    if ( ((insn & 0xfe200000) == 0x18000000)) {
         return 1;
    }
    if ( ((insn & 0xfe200000) == 0x1c000000)) {
         return 1;
    }
    if ( ((insn & 0xfe300000) == 0x2100000)) {
         return 1;
    }
    if ( ((insn & 0xfe300000) == 0x6100000)) {
         return 1;
    }
    if ( ((insn & 0xfe300000) == 0xa100000)) {
         return 1;
    }
    if ( ((insn & 0xfe300000) == 0x12100000)) {
         return 1;
    }
    if ( ((insn & 0xfe300000) == 0x16100000)) {
         return 1;
    }
    if ( ((insn & 0xfe300000) == 0x1a100000)) {
         return 1;
    }
    if ( ((insn & 0xfe300000) == 0x1e100000)) {
         return 1;
    }
    return 0;
}
int FloatVector_checker(uint64_t insn) {
    if ((insn & 0xf0000000) == 0xf0000000) {
        return 1;
    }
    if (( insn & 0xe6780000 ) == 0x80000000) {
        return 1;
    }
    if (( insn & 0xe6780000 ) == 0x82000000) {
        return 1;
    }
    if (( insn & 0xe6780000 ) == 0x84000000) {
        return 1;
    }
    if (( insn & 0xe67e0000 ) == 0x86020000) {
        return 1;
    }
    if (( insn & 0xe6780000 ) == 0x86000000) {
        return 1;
    }
    if (( insn & 0xe2380000 ) == 0x80080000) {
        return 1;
    }
    if (( insn & 0xe2380000 ) == 0x82080000) {
        return 1;
    }
    if (( insn & 0xe2380000 ) == 0x80100000) {
        return 1;
    }
    if (( insn & 0xe2380000 ) == 0x82100000) {
        return 1;
    }
    if (( insn & 0xe1f80000 ) == 0x80400000) {
        return 1;
    }
    if (( insn & 0xe1f80000 ) == 0x80c00000) {
        return 1;
    }
    if (( insn & 0xe1f81000 ) == 0x81400000) {
        return 1;
    }
    if (( insn & 0xe1f81000 ) == 0x81401000) {
        return 1;
    }
    if (( insn & 0xe1f80040 ) == 0x81c00040) {
        return 1;
    }
    if (( insn & 0xe1f80040 ) == 0x81c00000) {
        return 1;
    }
    return 0;
}
int FloatVector64_checker(uint64_t insn) {
    if ((insn & 0xf0300000) == 0xc0000000) {
        return 1;
    }
    return 0; //[TODO]: Add more insns
}

int Arithm_checker(uint64_t insn) {
    if (( insn & 0xffff ) == 0x0) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x6000) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xa000) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xe000) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x6200) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xa200) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xe200) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x6400) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xa400) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xe400) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x6600) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xa600) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xe600) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x6800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xa800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xe800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x6a00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xaa00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xea00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x6c00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xac00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xec00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x6e00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xae00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xee00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xf000) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xf200) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x7000) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x7200) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x7800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xb800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xf800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x4000) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x8000) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xc000) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x4200) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x8200) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xc200) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x4400) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x8400) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xc400) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x4600) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x8600) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xc600) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x4800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x8800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xc800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x4a00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x8a00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xca00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x4c00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x8c00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xcc00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x4e00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x8e00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xce00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x5000) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x9000) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xd000) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x5200) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x9200) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xd200) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x5800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x9800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xd800) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x5400) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x9400) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xd400) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x5a00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x9a00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xda00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x5600) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x9600) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xd600) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x5c00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x9c00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xdc00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x5e00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0x9e00) {
        return 1;
    }
    if (( insn & 0xfe00 ) == 0xde00) {
        return 1;
    }
    if (( insn & 0xf800 ) == 0x0) {
        return 1;
    }
    if (( insn & 0xf800 ) == 0x800) {
        return 1;
    }
    if (( insn & 0xf800 ) == 0x1000) {
        return 1;
    }
    if (( insn & 0xf800 ) == 0x1800) {
        return 1;
    }
    if (( insn & 0xf800 ) == 0x2000) {
        return 1;
    }
    if (( insn & 0xf800 ) == 0x2800) {
        return 1;
    }
    if (( insn & 0xf800 ) == 0x3000) {
        return 1;
    }
    if (( insn & 0xf800 ) == 0x3800) {
        return 1;
    }
    return 0;
}
int VectorALog_checker(uint64_t insn) {
    // Сдвиг на единицу в соответствии с потактовым симулятором
    insn = insn >> 1;
    if (( insn & 0xfff ) == 0x0) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0x840) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0x880) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0x8c0) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0x900) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0x940) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0x980) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0x9c0) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0xa00) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0xa40) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0xa80) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0xac0) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0xb00) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0xb40) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0xb80) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0x800) {
        return 1;
    }
    if (( insn & 0xfc0 ) == 0xbc0) {
        return 1;
    }
    if (( insn & 0xd80 ) == 0xc00) {
        return 1;
    }
    if (( insn & 0xd80 ) == 0xc80){
        return 1;
    }
    if (( insn & 0xd80 ) == 0xd00) {
        return 1;
    }
    if (( insn & 0xd80 ) == 0xd80) {
        return 1;
    }
    if (( insn & 0xce0 ) == 0x440) {
        return 1;
    }
    if (( insn & 0xcc0 ) == 0x400) {
        return 1;
    }
    if (( insn & 0xc80 ) == 0x0) {
        return 1;
    }
    if (( insn & 0xc80 ) == 0x80) {
        return 1;
    }
    if (( insn & 0xf80 ) == 0x480) {
        return 1;
    }
    return 0;
}

int GetInstLen(uint64_t ocode) {
    int is_insn32 = 0;
    int is_insn64 = 0;
    int res = 0;
    //if (Arithm_GetInstNum(ocode)) INFO_PRINT("found in: Arithm\n")
    //if (VectorALog_GetInstNum(ocode)) INFO_PRINT("found in: VectorALog\n");
    if (res = Scalar_GetInstNum(ocode)) INFO_PRINT("found in: Scalar, %d\n", res);
    if (res = Vector_GetInstNum(ocode)) INFO_PRINT("found in: Vector, %d\n", res);
    if (res = FloatVector_GetInstNum(ocode)) INFO_PRINT("found in: FloatVector, %d\n", res);
    if (res = Scalar64_GetInstNum(ocode)) INFO_PRINT("found in: Scalar64, %d\n", res);
    if (res = FloatVector64_GetInstNum(ocode)) INFO_PRINT("found in: FloatVector64, %d\n", res);

    is_insn32 = Scalar_GetInstNum(ocode) + Vector_GetInstNum(ocode) + FloatVector_GetInstNum(ocode);
    is_insn64 = Scalar64_GetInstNum(ocode) + FloatVector64_GetInstNum(ocode);
    if (is_insn64)
        return 2;
    else if (is_insn32)
        return 1;
    return 0;
}

int Arithm_GetInstNum(uint64_t ocode) {
    if (  ((OPCODE(uint16_t)&0x0ffff) == 0x00)  ){ return 1;}//;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x06000)  ){ return 2;}// $GRk = $GRj - $GRi noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0a000)  ){ return 3;}// $GRj - $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0e000)  ){ return 4;}// $GRk = $GRj - $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x06200)  ){ return 5;}// $GRk = $GRj - $GRi + -1 +carry noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0a200)  ){ return 6;}// $GRj - $GRi + -1 + carry;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0e200)  ){ return 7;}// $GRk= $GRj - $GRi + -1 + carry;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x06400)  ){ return 8;}// $GRk = $GRj + 1 noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0a400)  ){ return 9;}// $GRj + 1;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0e400)  ){ return 10;}// $GRk = $GRj + 1;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x06600)  ){ return 11;}// $GRk = $GRj + carry noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0a600)  ){ return 12;}// $GRj + carry;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0e600)  ){ return 13;}// $GRk= $GRj + carry;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x06800)  ){ return 14;}// $GRk = $GRj + -1 noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0a800)  ){ return 15;}// $GRj + -1;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0e800)  ){ return 16;}// $GRk = $GRj + -1;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x06a00)  ){ return 17;}// $GRk = $GRj + -1 +carry noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0aa00)  ){ return 18;}// $GRj + -1 + carry;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0ea00)  ){ return 19;}// $GRk = $GRj + -1 + carry;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x06c00)  ){ return 20;}// $GRk = $GRj + $GRi noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0ac00)  ){ return 21;}// $GRj + $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0ec00)  ){ return 22;}// $GRk = $GRj + $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x06e00)  ){ return 23;}// $GRk= $GRj + $GRi + carry noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0ae00)  ){ return 24;}// $GRj + $GRi + carry;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0ee00)  ){ return 25;}// $GRk= $GRj + $GRi + carry;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0f000)  ){ return 26;}// $GRk=$GRi *: $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0f200)  ){ return 27;}// $GRk= $GRi * $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x07000)  ){ return 28;}// $GRk=$GRi *: $GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x07200)  ){ return 29;}// $GRk= $GRi * $GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x07800)  ){ return 30;}// $GRk = -$GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0b800)  ){ return 31;}// -$GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0f800)  ){ return 32;}// $GRk = -$GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x04000)  ){ return 33;}// $GRk=false noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x08000)  ){ return 34;}// false;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0c000)  ){ return 35;}// $GRk=false;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x04200)  ){ return 36;}// $GRk=not $GRj and not $GRi noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x08200)  ){ return 37;}// not $GRj and not $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0c200)  ){ return 38;}// $GRk=not $GRj and not $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x04400)  ){ return 39;}// $GRk = $GRj & not $GRi noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x08400)  ){ return 40;}// $GRj & not $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0c400)  ){ return 41;}// $GRk= $GRj & not $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x04600)  ){ return 42;}// $GRk=not $GRi noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x08600)  ){ return 43;}// not $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0c600)  ){ return 44;}// $GRk=not $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x04800)  ){ return 45;}// $GRk =not $GRj & $GRi noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x08800)  ){ return 46;}// not $GRj & $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0c800)  ){ return 47;}// $GRk = not $GRj & $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x04a00)  ){ return 48;}// $GRk=not $GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x08a00)  ){ return 49;}// not $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0ca00)  ){ return 50;}// $GRk = not $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x04c00)  ){ return 51;}// $GRk = $GRi xor $GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x08c00)  ){ return 52;}// $GRi xor $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0cc00)  ){ return 53;}// $GRk = $GRi xor $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x04e00)  ){ return 54;}// $GRk = not $GRi or not $GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x08e00)  ){ return 55;}// not $GRi or not $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0ce00)  ){ return 56;}// $GRk = not $GRi or not $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x05000)  ){ return 57;}// $GRk = $GRi and $GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x09000)  ){ return 58;}// $GRi and $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0d000)  ){ return 59;}// $GRk = $GRi and $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x05200)  ){ return 60;}// $GRk = $GRi xor not $GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x09200)  ){ return 61;}// $GRi xor not $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0d200)  ){ return 62;}// $GRk = $GRi xor not $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x05800)  ){ return 63;}// $GRk = $GRi noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x09800)  ){ return 64;}// $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0d800)  ){ return 65;}// $GRk = $GRi;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x05400)  ){ return 66;}// $GRk = $GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x09400)  ){ return 67;}// $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0d400)  ){ return 68;}// $GRk = $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x05a00)  ){ return 69;}// $GRk = $GRi or not $GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x09a00)  ){ return 70;}// $GRi or not $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0da00)  ){ return 71;}// $GRk = $GRi or not $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x05600)  ){ return 72;}// $GRk = not $GRi or $GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x09600)  ){ return 73;}// not $GRi or $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0d600)  ){ return 74;}// $GRk = not $GRi or $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x05c00)  ){ return 75;}// $GRk = $GRi or $GRj noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x09c00)  ){ return 76;}// $GRi or $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0dc00)  ){ return 77;}// $GRk = $GRi or $GRj;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x05e00)  ){ return 78;}// $GRk=true noflags;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x09e00)  ){ return 79;}// true;
    if (  ((OPCODE(uint16_t)&0x0fe00) == 0x0de00)  ){ return 80;}// $GRk=true;
    if (  ((OPCODE(uint16_t)&0x0f800) == 0x00)     ){ return 81;}// $GRk = $GRi R<< $shift_arg ;
    if (  ((OPCODE(uint16_t)&0x0f800) == 0x0800)   ){ return 82;}// $GRk = $GRi R>> $shift_arg;
    if (  ((OPCODE(uint16_t)&0x0f800) == 0x01000)  ){ return 83;}// $GRk=$GRi << $shift_arg;
    if (  ((OPCODE(uint16_t)&0x0f800) == 0x01800)  ){ return 84;}// $GRk=$GRi >> $shift_arg;
    if (  ((OPCODE(uint16_t)&0x0f800) == 0x02000)  ){ return 85;}// $GRk=$GRi A<< $shift_arg;
    if (  ((OPCODE(uint16_t)&0x0f800) == 0x02800)  ){ return 86;}// $GRk=$GRi A>> $shift_arg;
    if (  ((OPCODE(uint16_t)&0x0f800) == 0x03000)  ){ return 87;}// $GRk=$GRi C<< $shift_arg;
    if (  ((OPCODE(uint16_t)&0x0f800) == 0x03800)  ){ return 88;}// $GRk=$GRi C>> $shift_arg;
    else{ return 0; }
}
int VectorALog_GetInstNum(uint64_t ocode) {
    if (  ((OPCODE(uint16_t)&0x0fff) == 0x00)    ){ return 1;}//;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0840)  ){ return 2;}//not $FPX $X and not $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0880)  ){ return 3;}//$FPX $X and not $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x08c0)  ){ return 4;}//not $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0900)  ){ return 5;}//not $FPX $X and $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0940)  ){ return 6;}//not $FPX $X;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0980)  ){ return 7;}//$FPX $X xor $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x09c0)  ){ return 8;}//not $FPX $X or not $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0a00)  ){ return 9;}//$FPX $X and $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0a40)  ){ return 10;}//not $FPX $X xor $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0a80)  ){ return 11;}//$FPX $X;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0ac0)  ){ return 12;}//$FPX $X or not $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0b00)  ){ return 13;}//$FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0b40)  ){ return 14;}//not $FPX $X or $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0b80)  ){ return 15;}//$FPX $X or $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0800)  ){ return 16;}//vfalse;
    if (  ((OPCODE(uint16_t)&0x0fc0) == 0x0bc0)  ){ return 17;}//vtrue;
    if (  ((OPCODE(uint16_t)&0x0d80) == 0x0c00)  ){ return 18;}//$FPX $X - $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0d80) == 0x0c80)  ){ return 19;}//$FPX $X + 1;
    if (  ((OPCODE(uint16_t)&0x0d80) == 0x0d00)  ){ return 20;}//$FPX $X - 1;
    if (  ((OPCODE(uint16_t)&0x0d80) == 0x0d80)  ){ return 21;}//$FPX $X + $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0ce0) == 0x0440)  ){ return 22;}//mask $M, shift $X, $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0cc0) == 0x0400)  ){ return 23;}//mask $M, $FPX $X, $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0c80) == 0x00)    ){ return 24;}// vsum $M, $SH $FPX $X, $FPY $Y;
    if (  ((OPCODE(uint16_t)&0x0c80) == 0x080)   ){ return 25;}// vsum $M, $SH $FPX $X, $FPY vr;
    if (  ((OPCODE(uint16_t)&0x0f80) == 0x0480)  ){ return 26;}// store vregs
    else{ return 0; }
}
int Scalar_GetInstNum(uint64_t ocode) {
    if (  ((OPCODE(uint32_t)&0x072300000) == 0x050100000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 1;}//nul with $ar_arg
    if (  ((OPCODE(uint32_t)&0x072300000) == 0x050100000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 2;}//$ar_arg
    if (  ((OPCODE(uint32_t)&0x0e2000000) == 0x020000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 3;}//$Rdst = [$MaVal] $ar_inst
    if (  ((OPCODE(uint32_t)&0x0e2000000) == 0x022000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 4;}//[$MaVal] = $Rdst $ar_inst
    if (  ((OPCODE(uint32_t)&0x0f0000000) == 0x070000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 5;}//$dst_reg = $src_reg set $ar_inst
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x052100000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 6;}//$arj = $ari addr $ar_inst
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x056100000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 7;}//$arj = $ari addr $ar_inst
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x05a100000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 8;}//$arj = $ari addr $ar_inst
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x05e100000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 9;}//$arj = $ari addr $ar_inst
    if (  ((OPCODE(uint32_t)&0x0fc300000) == 0x0200000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 10;}//$cond $is_call $areg with $ar_inst
    if (  ((OPCODE(uint32_t)&0x0fc300000) == 0x04200000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 11;}//$cond $is_call $areg with $ar_inst
    if (  ((OPCODE(uint32_t)&0x0fc300000) == 0x08200000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 12;}//$cond $is_call $areg with $ar_inst
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x0c200000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 13;}//$cond skip $areg $ar_inst
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x0e200000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 14;}//$cond callrel $areg $ar_inst
    if (  ((OPCODE(uint32_t)&0x0fff00000) == 0x07300000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 15;}//$cond return $ar_inst
    if (  ((OPCODE(uint32_t)&0x0fff00000) == 0x06300000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 16;}//$cond ireturn $ar_inst
    else{ return 0; }
}
int Scalar64_GetInstNum(uint64_t ocode) {
    if (  ((OPCODE(uint64_t)&0x072300000) == 0x040100000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 1;}//$const_arg $ar_arg
    if (  ((OPCODE(uint64_t)&0x0fe000000) == 0x060000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 2;}//$Rdst=[$const_arg] $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe000000) == 0x064000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 3;}//$Rdst=[$Rsrc+=$const_arg] $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe000000) == 0x068000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 4;}//$Rdst=[$Rsrc=$const_arg] $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe000000) == 0x06c000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 5;}//$Rdst=[$Rsrc+$const_arg] $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe000000) == 0x062000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 6;}//[$const_arg] = $Rdst $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe000000) == 0x066000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 7;}//[$Rsrc+=$const_arg]=$Rdst $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe000000) == 0x06a000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 8;}//[$Rsrc=$const_arg]=$Rdst $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe000000) == 0x06e000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 9;}//[$Rsrc+$const_arg]=$Rdst $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe300000) == 0x042100000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 10;}//$arj = $ari $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe300000) == 0x046100000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 11;}//$arj = $ari + $const_arg $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe300000) == 0x04a100000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 12;}//$arj =  $const_arg addr $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe300000) == 0x04e100000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 13;}//$arj = pc + $const_arg addr $ar_inst
    if (  ((OPCODE(uint64_t)&0x0f0300000) == 0x040000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 14;}//$dst = $const_arg set $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fc300000) == 0x040200000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 15;}//$cond $is_call $areg $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fc300000) == 0x044200000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 16;}//$cond $is_call $areg + $const_arg $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fc300000) == 0x048200000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 17;}//$cond $is_call $const_arg $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe300000) == 0x04c200000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 18;}//$cond skip $const_arg $ar_inst
    if (  ((OPCODE(uint64_t)&0x0fe300000) == 0x04e200000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 19;}//$cond callrel $const_arg $ar_inst
    else{ return 0; }
}
int Vector_GetInstNum(uint64_t ocode) {
    if (  ((OPCODE(uint32_t)&0x0e0380000) == 0x00)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 1;}//$rep_val $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe200000) == 0x00)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 2;}//$rep_val $RW   = [$ARi] $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe200000) == 0x04000000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 3;}//$rep_val $RW   = [$ARi] $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe200000) == 0x08000000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 4;}//$rep_val $RW   = [$ARi] $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe200000) == 0x010000000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 5;}//$rep_val $RW   = [$ARi] $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe200000) == 0x014000000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 6;}//$rep_val $RW   = [$ARi] $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe200000) == 0x018000000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 7;}//$rep_val $RW   = [$ARi] $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe200000) == 0x01c000000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 8;}//$rep_val $RW   = [$ARi] $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x02100000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 9;}//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x06100000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 10;}//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x0a100000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 11;}//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x012100000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 12;}//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x016100000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 13;}//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x01a100000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 14;}//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
    if (  ((OPCODE(uint32_t)&0x0fe300000) == 0x01e100000)  && (VectorALog_GetInstNum( (ocode>>1)&0xFFF) ) ){ return 15;}//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
    else{ return 0; }
}
int FloatVector_GetInstNum(uint64_t ocode) {
    if (  ((OPCODE(uint32_t)&0x0f0000000) == 0x0f0000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 1;}//$dst_reg = $src_reg set $ar_inst
    if (  ((OPCODE(uint32_t)&0x0e6780000) == 0x080000000)  ){ return 2;}//instruction_3.1
    if (  ((OPCODE(uint32_t)&0x0e6780000) == 0x082000000)  ){ return 3;}//instruction_3.2
    if (  ((OPCODE(uint32_t)&0x0e6780000) == 0x084000000)  ){ return 4;}//instruction_3.3
    if (  ((OPCODE(uint32_t)&0x0e67e0000) == 0x086020000)  ){ return 5;}//
    if (  ((OPCODE(uint32_t)&0x0e6780000) == 0x086000000)  ){ return 6;}//
    if (  ((OPCODE(uint32_t)&0x0e2380000) == 0x080080000)  ){ return 7;}//
    if (  ((OPCODE(uint32_t)&0x0e2380000) == 0x082080000)  ){ return 8;}//
    if (  ((OPCODE(uint32_t)&0x0e2380000) == 0x080100000)  ){ return 9;}//
    if (  ((OPCODE(uint32_t)&0x0e2380000) == 0x082100000)  ){ return 10;}//
    if (  ((OPCODE(uint32_t)&0x0e1f80000) == 0x080400000)  ){ return 11;}//$celld $vrd = $cells $vrs1;
    if (  ((OPCODE(uint32_t)&0x0e1f80000) == 0x080c00000)  ){ return 12;}//$celld $vrd = $cells $ms mask ? $vrs1 : $vrs0;
    if (  ((OPCODE(uint32_t)&0x0e1f81000) == 0x081400000)  ){ return 13;}//$cells .packer = $vrs1 with $df <= $sf
    if (  ((OPCODE(uint32_t)&0x0e1f81000) == 0x081401000)  ){ return 14;}//$cells .packer = $vrs1 with $df <= $sf
    if (  ((OPCODE(uint32_t)&0x0e1f80040) == 0x081c00040)  ){ return 15;}//$celld rep $rep_cnt $vrd = .packer
    if (  ((OPCODE(uint32_t)&0x0e1f80040) == 0x081c00000)  ){ return 16;}//$celld rep $rep_cnt $vrd = .packer;
    else{ return 0; }
}
int FloatVector64_GetInstNum(uint64_t ocode) {
    if (  ((OPCODE(uint64_t)&0x0f0300000) == 0x0c0000000)  && (Arithm_GetInstNum( (ocode>>0)&0xFFFF) ) ){ return 1;}//$dst_reg set $const_arg set $ar_inst
    else{ return 0; }
}
