# makefile <Dir: lib-dll>
include ../../headers/make.inc

DIR_OBJECTS  = .
PROGNAME = ../../libs/linux/libdwarf.a

OBJ_FILES= $(DIR_OBJECTS)/dw_abbrv.o\
	   $(DIR_OBJECTS)/dw_attr.o\
	   $(DIR_OBJECTS)/dw_cu.o\
	   $(DIR_OBJECTS)/dw_debug.o\
	   $(DIR_OBJECTS)/dw_die.o\
	   $(DIR_OBJECTS)/dw_frame.o\
	   $(DIR_OBJECTS)/libdwarf.o\
	   $(DIR_OBJECTS)/pro_aran.o\
	   $(DIR_OBJECTS)/pro_attr.o\
	   $(DIR_OBJECTS)/pro_cu.o\
	   $(DIR_OBJECTS)/pro_dbg.o\
	   $(DIR_OBJECTS)/pro_die.o\
	   $(DIR_OBJECTS)/pro_expr.o\
	   $(DIR_OBJECTS)/pro_fram.o\
	   $(DIR_OBJECTS)/pro_garn.o\
	   $(DIR_OBJECTS)/pro_ginf.o\
	   $(DIR_OBJECTS)/pro_glin.o\
	   $(DIR_OBJECTS)/pro_gpub.o\
	   $(DIR_OBJECTS)/pro_pubn.o

CC  = gcc
INCLUDE = -Iinclude \
	  -I../../headers \
	  -I../../dbg_interface

$(PROGNAME): $(OBJ_FILES)
	$(ARHIEVER) $(ARHIEVER_OPTS) $@ $(OBJ_FILES)
	
$(DIR_OBJECTS)/dw_abbrv.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/dw_abbrv.cpp -o $@

$(DIR_OBJECTS)/libdwarf.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/libdwarf.cpp -o $@

$(DIR_OBJECTS)/dw_attr.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/dw_attr.cpp -o $@

$(DIR_OBJECTS)/dw_cu.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/dw_cu.cpp -o $@

$(DIR_OBJECTS)/dw_debug.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/dw_debug.cpp -o $@

$(DIR_OBJECTS)/dw_die.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/dw_die.cpp -o $@

$(DIR_OBJECTS)/dw_frame.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/dw_frame.cpp -o $@

$(DIR_OBJECTS)/libdwarf.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/libdwarf.cpp -o $@

$(DIR_OBJECTS)/pro_aran.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_aran.cpp -o $@

$(DIR_OBJECTS)/pro_attr.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_attr.cpp -o $@

$(DIR_OBJECTS)/pro_cu.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_cu.cpp -o $@

$(DIR_OBJECTS)/pro_dbg.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_dbg.cpp -o $@

$(DIR_OBJECTS)/pro_die.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_die.cpp -o $@

$(DIR_OBJECTS)/pro_expr.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_expr.cpp -o $@

$(DIR_OBJECTS)/pro_fram.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_fram.cpp -o $@

$(DIR_OBJECTS)/pro_garn.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_garn.cpp -o $@

$(DIR_OBJECTS)/pro_gfrm.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_gfrm.cpp -o $@

$(DIR_OBJECTS)/pro_ginf.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_ginf.cpp -o $@

$(DIR_OBJECTS)/pro_glin.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_glin.cpp -o $@

$(DIR_OBJECTS)/pro_gpub.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_gpub.cpp -o $@

$(DIR_OBJECTS)/pro_pubn.o:
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c src/pro_pubn.cpp -o $@

clean:
	rm -f $(DIR_OBJECTS)/src/*~
	rm -f $(DIR_OBJECTS)/*~
	rm -f $(DIR_OBJECTS)/*.o
	rm -f $(PROGNAME)
