@echo on

"%SIM_RUN%" simulator\VC8\simulator.vcproj /Rebuild  Release  >lib_compile_log.txt
@echo on
if ErrorLevel 1 goto error

echo dll build result: success, see lib_compile_log.txt for detail 
exit /B  

:error
echo error during the library compilation, see lib_compile_log.txt for detail
exit /B  
