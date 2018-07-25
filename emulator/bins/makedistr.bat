if '%1'=='' goto error_build

if exist %PPDL_DIR%\%1_out rmdir %PPDL_DIR%\%1_out /S /Q

mkdir %PPDL_DIR%\%1_out

copy %PPDL_DIR%\models\%1\*.dll %PPDL_DIR%\%1_out

copy %PPDL_DIR%\distrib_lib\*.dll %PPDL_DIR%\%1_out
copy %PPDL_DIR%\bins\PdDebugger.exe %PPDL_DIR%\%1_out
copy %PPDL_DIR%\bins\rundbg.* %PPDL_DIR%\%1_out

if '%2'=='' goto end_ok
echo PdDebugger.exe %2 %%1 >%PPDL_DIR%\%1_out\run.bat 

:end_ok	
echo ok 
exit /B



:error_build
echo can't build distrib 