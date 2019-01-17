rem example of generation of the PPDL VM description from ontology tree
echo top dir is %1
echo current dir %CD%
echo script dir %~dp0
set BASE_PATH=%~dp0
%BASE_PATH%build_ppdl.exe %1
%BASE_PATH%..\emulator\bins\ppdl.exe res_vm.hdl -s res-sim
