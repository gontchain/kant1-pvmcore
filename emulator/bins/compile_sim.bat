echo off
if '%PPDL_DIR%' =='' set PPDL_DIR=%CD%
if '%PPDL_DIR%' =='' goto pause_exit

pushd %PPDL_DIR%
call pathconf.bat
popd

if exist log%1.txt del log%1.txt
pushd %PPDL_DIR%\models\%1
if exist lib_compile_log.txt del lib_compile_log.txt
call build_model.bat
popd

type %PPDL_DIR%\models\nm6405ca\sim_log.txt > log%1.txt

pause
exit /B

:pause_exit
pause
exit /B