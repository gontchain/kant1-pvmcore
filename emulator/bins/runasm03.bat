del *.elf
del *.abs

"%NM_PATH%\bin\asm.exe" %1 -otest.elf
"%NM_PATH%\bin\linker.exe" test.elf .\libc.lib nm_test\testlib.elf