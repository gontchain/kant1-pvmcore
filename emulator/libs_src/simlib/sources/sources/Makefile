# makefile <Dir: lib-dll>

DIR_OBJECTS  = .
PROGNAME = $(DIR_OBJECTS)/source-lib

OBJ_FILES= $(DIR_OBJECTS)/lib_dll_main.o 
#	$(DIR_OBJECTS)/sim_thread.o

CC  = g++
INCLUDE =
#DIR_BASE = /home/us/common/Int/linux/simulat12
DIR_BASE = /home/petro/Desktop/Yuri_new/ppdl/libs_src
DIR_INCLUDE_HEADERS = ../headers 
INCLUDE_INCLUDE_HEADERS = -I$(DIR_BASE)/$(DIR_INCLUDE_HEADERS) -I$(DIR_BASE)/../dbg_interface
INCLUDE_SIMLIB_HEADERS  = -I$(DIR_BASE)/simlib/headers

INCLUDE_HEADERS = $(INCLUDE_INCLUDE_HEADERS) $(INCLUDE_SIMLIB_HEADERS)

FLAGS = -Wno-deprecated
FLAG_C = -fPIC
#	-lc -m486
#FLAG_C = -fPIC -ggdb -Wall
FLAG_O = -shared 

.SUFFIXES: .o .cpp
.cpp.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) $(INCLUDE_HEADERS) -c $<

$(PROGNAME): $(OBJ_FILES)         

clean:
	rm -f $(DIR_OBJECTS)/*~
	rm -f $(DIR_OBJECTS)/*.o
