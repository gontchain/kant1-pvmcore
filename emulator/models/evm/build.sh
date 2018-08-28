#!/bin/bash

../../bins/ppdl evm.hdl -s evm_sim
../../bins/ppdl evm.hdl -a evm_asm
../../bins/ppdl evm.hdl -xml evm.xml

if [ -e evm_asm.h ]; then
    mv evm_asm.h assembler/
fi
if [ -e evm_asm.cpp ]; then
    mv evm_asm.cpp assembler/
fi
if [ -e evm_sim.h ]; then
    mv evm_sim.h simulator/
fi
if [ -e evm_sim.cpp ]; then
    mv evm_sim.cpp simulator/
fi
