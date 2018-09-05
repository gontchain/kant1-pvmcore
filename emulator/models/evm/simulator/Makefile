# makefile <Dir: lib-dll>
include ../../../headers/make.inc

PROGNAME = ./evm.so
OBJ_FILES = $(DIR_OBJECTS)/architecture.o $(DIR_OBJECTS)/evm_sim.o 
INCLUDE = -I./include -I./../../../headers -I./../../../dbg_interface -I./../../../peripheral -I../../../../$(SYSTEMC_INC)
LIB_DIR = ../../../libs/linux
SC_DIR = $(PWD)/../systemc/lib

LIBRARIES = $(LIB_DIR)/simlib.a $(LIB_DIR)/libelf.a $(LIB_DIR)/libdwarf.a $(SC_DIR)/libsystemc.a
		
	      

$(PROGNAME): $(OBJ_FILES) $(LIBRARIES)
	$(CC) $(FLAG_O_LIB) $(OBJ_FILES) $(LIBRARIES) -o $(PROGNAME) 

$(LIB_DIR)/simlib.a:
	$(MYMAKE) -C ../../../libs_src/simlib/

$(LIB_DIR)/libelf.a:
	$(MYMAKE) -C ../../../libs_src/libelf/
	
$(LIB_DIR)/libdwarf.a:
	$(MYMAKE) -C ../../../libs_src/libdwarf/
		
$(DIR_OBJECTS)/architecture.o:
	mkdir -p $(DIR_OBJECTS)
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c ./architecture.cpp -o $@
	
$(DIR_OBJECTS)/evm_sim.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c ./evm_sim.cpp -o $@

	
	
clean:
	rm -f $(DIR_OBJECTS)/*.*
	rm -f $(PROGNAME)
	rm -rf $(DIR_OBJECTS)
