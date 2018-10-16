#ifndef DISAS_PPDL_INSN_H
#define DISAS_PPDL_INSN_H

int Scalar_checker(uint64_t);
int Scalar64_checker(uint64_t);
int Vector_checker(uint64_t) ;
int FloatVector_checker(uint64_t);
int Arithm_checker(uint64_t);
int VectorALog_checker(uint64_t);
int FloatVector64_checker(uint64_t);

int GetInstLen(uint64_t);

int Arithm_GetInstNum(uint64_t);
int VectorALog_GetInstNum(uint64_t);
int Scalar_GetInstNum(uint64_t);
int Scalar64_GetInstNum(uint64_t);
int Vector_GetInstNum(uint64_t);
int FloatVector_GetInstNum(uint64_t);
int FloatVector64_GetInstNum(uint64_t);

#endif // DISAS_PPDL_INSN_H
