# makefile <Dir: lib-dll>
include ../../headers/make.inc

DIR_OBJECTS  = .
PROGNAME = ../../libs/linux/simlib.a
TARG_DIR = ../../libs/linux/

OBJ_FILES = $(DIR_OBJECTS)/device.o \
	   $(DIR_OBJECTS)/sim_thread.o \
	   $(DIR_OBJECTS)/system.o \
	   $(DIR_OBJECTS)/swap_man.o \
	   $(DIR_OBJECTS)/system_mc.o \
	   $(DIR_OBJECTS)/tParseCfg.o

INCLUDE = -I$(DIR_OBJECTS)/headers \
	  -I$(DIR_OBJECTS)/../../headers \
	  -I$(DIR_OBJECTS)/../../dbg_interface 


$(PROGNAME): $(OBJ_FILES)
#	$(CC) $(FLAG_O) $(LIBRARIES) -o $(PROGNAME) $(OBJ_FILES)
	mkdir -p $(TARG_DIR)
	$(ARHIEVER) $(ARHIEVER_OPTS) $(PROGNAME) $(OBJ_FILES)
	$(RANLIB) $(PROGNAME)
	
$(DIR_OBJECTS)/device.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c $(DIR_OBJECTS)/sources/device.cpp
	
$(DIR_OBJECTS)/sim_thread.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c $(DIR_OBJECTS)/sources/sim_thread.cpp
	
$(DIR_OBJECTS)/system.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c $(DIR_OBJECTS)/sources/system.cpp
	
$(DIR_OBJECTS)/system_mc.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c $(DIR_OBJECTS)/sources/system_mc.cpp

$(DIR_OBJECTS)/swap_man.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c $(DIR_OBJECTS)/sources/swap_man.cpp

$(DIR_OBJECTS)/tParseCfg.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c $(DIR_OBJECTS)/sources/tParseCfg.cpp

#$(PROGNAME): $(OBJ_FILES) ../



clean:
	rm -f $(DIR_OBJECTS)/sources/*~
	rm -f $(DIR_OBJECTS)/sources/*.o
	rm -f $(DIR_OBJECTS)/*~
	rm -f $(DIR_OBJECTS)/*.o
	rm -f $(DIR_OBJECTS)/libsimlib.a
	rm -f $(PROGNAME)
	rm -rf $(TARG_DIR)
