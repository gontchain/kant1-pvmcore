del test.elf
del test.abs

asm.exe -6405 %1 -otest.elf
linker.exe test.elf .\libc.lib nm_test\testlib.elf