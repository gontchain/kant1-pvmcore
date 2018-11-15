set header_path=%2\..\include\%3.h
set filecpp_path=%2\..\sources\%3.cpp

echo project path is %2

echo header_path = %header_path%
echo filecpp_path = %filecpp_path%


if exist %header_path% (attrib -r %header_path%
del %header_path%)
if exist %filecpp_path% (attrib -r %filecpp_path%
del %filecpp_path%)

echo ppdl output path is %2

..\..\..\..\bins\ppdl.exe %1 -s %2%3

move %2\%3.h %header_path%
move %2\%3.cpp %filecpp_path%

set header_path=
set filecpp_path=
