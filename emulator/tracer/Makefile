include ../headers/make.inc

TARGETDIR=../bins
	    
#this locations must be changed within moving project directory
INCLUDE = -I../dbg_interface \
	  -I../headers\
	  -I../libs_src/simlib/headers\
	  -I../libs_src/libdwarf/include\
	  -I../libs_src/libelf/include\
	  -I../models/nm6403/simulator/include

# Define the target directories.
OBJDIR =./obj


all: $(TARGETDIR)/cemu

OBJS = $(OBJDIR)/main.o $(OBJDIR)/profiler.o 
USERLIBS =../libs/linux/libdwarf.a ../libs/linux/libelf.a

# Link or archive
$(TARGETDIR)/cemu: $(OBJS)
	$(CC) $(OBJS) $(USERLIBS) $(LIBRARIES) -o $@ 

# Compile source files into .o files
$(OBJDIR)/main.o: $(TARGETDIR) main.cpp
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE)  -c main.cpp -o $@

$(OBJDIR)/profiler.o: $(TARGETDIR) profiler.cpp
	$(CC) $(FLAGS) $(FLAG_C) $(INCLUDE) -c profiler.cpp -o $@ 

#external libraries
$(LIB_DIR)/libelf.a:
	$(MYMAKE) -C ../libs_src/libelf/
	
$(LIB_DIR)/libdwarf.a:
	$(MYMAKE) -C ../libs_src/libdwarf/
	
#### Clean target deletes all generated files ####
clean:
	$(CLEAN_DIR) $(TARGETDIR)/tracer $(TARGETDIR)/tracer.exe $(OBJDIR)/main.o $(OBJDIR)/profiler.o:
	
# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-i386-Linux
