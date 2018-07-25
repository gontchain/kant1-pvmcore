@echo off

if  exist %1 goto start_compilation
echo wrong input file name %1, stop process
exit /B  

:start_compilation
if exist %2.h del %2.h
if exist %2.cpp del %2.cpp

@echo on
%PPDL_DIR%\bins\ppdl.exe %1 -s %2 -a %3
@echo off

if exist %2.h goto run_compile
exit /B  

:run_compile
echo ppdl compilation complete, result: success

echo start library compilation

if exist lib_compile_log.txt del lib_compile_log.txt

@echo on
echo dbg ok


@echo off
"%SIM_RUN%" simulator\simulator.vcproj /Rebuild  Debug  >lib_compile_log.txt
@echo on

goto after_compile

:build_debug
@echo on
"%SIM_RUN%" simulator\simulator.vcproj /rebuild Debug >lib_compile_log.txt
@echo off



:after_compile
if ErrorLevel 1 goto error

if exist simulator.exp del simulator.exp

echo dll build result: success, see lib_compile_log.txt for detail 

@echo on
"%SIM_RUN%" assembler\assembler.vcproj /rebuild Debug >asm_compile_log.txt
@echo off
if ErrorLevel 1 goto error

if exist assembler.exp del assembler.exp

exit /B  

:error
echo error during the library compilation, see lib_compile_log.txt for detail
exit /B  
