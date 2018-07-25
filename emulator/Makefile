# makefile <Dir: lib-dll>
include ./headers/make.inc


MODEL_DIR = ./models
LIB_DIR= ./libs/linux
  
LIBRARIES = $(LIB_DIR)/simlib.a $(LIB_DIR)/libelf.a $(LIB_DIR)/libdwarf.a $(MODEL_DIR)/nm6405ca/simulator/nm6405ca.so
		


		

all: $(LIBRARIES) ./tracer/tracer


$(LIB_DIR)/libelf.a:
	$(MYMAKE) -C ./libs_src/libelf/
	
$(LIB_DIR)/libdwarf.a:
	$(MYMAKE) -C ./libs_src/libdwarf/
	
$(LIB_DIR)/simlib.a:
	$(MYMAKE) -C ./libs_src/simlib/

$(MODEL_DIR)/risc_v/simulator/nm6405ca.so:
	$(MYMAKE) -C $(MODEL_DIR)/risc_v/simulator/

  ./tracer/tracer:
	$(MYMAKE) -C ./tracer
	
clean:
	$(MYMAKE) -C ./libs_src/libelf/  clean
	$(MYMAKE) -C ./libs_src/libdwarf/  clean
	$(MYMAKE) -C ./libs_src/simlib/ clean
	$(MYMAKE) -C $(MODEL_DIR)/risc_v/simulator/ clean
	$(MYMAKE) -C ./tracer clean
	
