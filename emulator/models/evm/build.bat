

..\..\bins\ppdl.exe evm.hdl -s evm_sim
..\..\bins\ppdl.exe evm.hdl -a evm_asm 
..\..\bins\ppdl.exe evm.hdl -xml evm.xml

if exist evm_asm.h move evm_asm.h  assembler\
if exist evm_asm.cpp move evm_asm.cpp  assembler\
if exist evm_sim.h move evm_sim.h  simulator\
if exist evm_sim.cpp move evm_sim.cpp  simulator\

