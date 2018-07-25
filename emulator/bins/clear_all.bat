if exist asm.cpp del asm.cpp
if exist *.h   del *.h
if exist *_sim.cpp   del *_sim.cpp
if exist *_asm.cpp   del *_asm.cpp
if exist *.txt   del *.txt
if exist *.elf  del *.elf
if exist *.abs  del *.abs
if exist *.exp  del *.exp
if exist *.pdb  del *.pdb



if exist simulator\debug del simulator\debug /Q /S
if exist simulator\Release del simulator\Release /Q /S
if exist *.dll del *.dll
