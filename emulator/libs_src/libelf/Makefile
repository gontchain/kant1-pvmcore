# makefile <Dir: lib-dll>

include ../../headers/make.inc

DIR_OBJECTS  = .
PROGNAME = ../../libs/linux/libelf.a

OBJ_FILES= $(DIR_OBJECTS)/libelf.o \
	   $(DIR_OBJECTS)/liblib.o 

INCLUDE = -I$(DIR_OBJECTS)/include \
	  -I$(DIR_OBJECTS)/../../headers \
	  -I$(DIR_OBJECTS)/../../dbg_interface 

#FLAGS = 
#FLAG_C =
FLAGS = -Wno-deprecated -D_X86 -DNM6403 -Wredundant-decls
FLAG_C = -fPIC

#	-lc -m486
#FLAG_C = -fPIC -ggdb -Wall
FLAG_O = -shared    

ARHIEVER = ar
ARHIEVER_OPTS = rc

RANLIB = ranlib

$(PROGNAME): $(OBJ_FILES)
#	$(CC) $(FLAG_O) $(LIBRARIES) -o $(PROGNAME) $(OBJ_FILES)
	$(ARHIEVER) $(ARHIEVER_OPTS) $(PROGNAME) $(OBJ_FILES)
	$(RANLIB) $(PROGNAME)

$(DIR_OBJECTS)/libelf.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c $(DIR_OBJECTS)/src/libelf.cpp

$(DIR_OBJECTS)/liblib.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c $(DIR_OBJECTS)/src/liblib.cpp      

clean:
	rm -f $(DIR_OBJECTS)/src/*~
	rm -f $(DIR_OBJECTS)/*~
	rm -f $(DIR_OBJECTS)/*.o
	rm -f $(PROGNAME)