rem arguments
rem %1 - library name
rem %2 - abs file name
rem %3 (optional) - bsp file

if exist log_arch.bin del log_arch.bin

echo run simulation and profiling
if %3=='' ( %~dp0\cemu.exe -nw -p profile_res.txt %1 %2 ) else ( %~dp0\cemu.exe -nw -p profile_res.txt -bsp %3 %1 %2)
echo generate html 

rem if exist profiler_res.txt %~dp0\htmler\python.exe %~dp0\main.py profiler_res.txt profile.html
if exist profile_res.txt python.exe %~dp0\htmler\main.py profile_res.txt profile.html

if exist log_arch.bin del log_arch.bin
