# makefile <Dir: lib-dll>
include ./headers/make.inc

MODEL_DIR = ./models
LIB_DIR= ./libs/linux

LIBRARIES = $(LIB_DIR)/simlib.a $(LIB_DIR)/libelf.a $(LIB_DIR)/libdwarf.a $(MODEL_DIR)/evm/simulator/evm.so

all: $(LIBRARIES) ./tracer/tracer


$(LIB_DIR)/libelf.a:
	$(MYMAKE) -C ./libs_src/libelf/

$(LIB_DIR)/libdwarf.a:
	$(MYMAKE) -C ./libs_src/libdwarf/

$(LIB_DIR)/simlib.a:
	$(MYMAKE) -C ./libs_src/simlib/

$(MODEL_DIR)/evm/simulator/evm.so:
	$(MYMAKE) -C $(MODEL_DIR)/evm/simulator/

  ./tracer/tracer:
	$(MYMAKE) -C ./tracer

clean:
	$(MYMAKE) -C ./libs_src/libelf/  clean
	$(MYMAKE) -C ./libs_src/libdwarf/  clean
	$(MYMAKE) -C ./libs_src/simlib/ clean
	$(MYMAKE) -C ./tracer clean
	
