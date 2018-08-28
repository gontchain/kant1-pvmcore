#make file
MYMAKE = make
#tools
CC = g++
LD = ld
ARHIEVER = ar
ARHIEVER_OPTS = rc
RANLIB = ranlib

SYSTEMC_INC=systemc/include

#c flags 
FLAGS = -Wno-deprecated -D_X86 -DNM6403 -Wredundant-decls
FLAG_C = -std=gnu++98 -fPIC -DLINOS -g3 -fpermissive -O3 -finline-functions
FLAG_O_LIB = -shared

LIBRARIES= -lc -lstdc++ -ldl -lpthread

CLEAN_DIR= rm -f

DIR_OBJECTS  = ./obj

