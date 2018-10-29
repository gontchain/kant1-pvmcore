#include "evm.h"
#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

#define LIB_PATH "../qemu/ppdl-softmmu/libevm-ppdl.so"

typedef void* (*arbitrary)();

int main(int argc, char **argv) {
    void *handle = dlopen(LIB_PATH, RTLD_LAZY);
    if (!handle) { 
        fprintf(stderr, "dlopen failure: %s\n", dlerror()); 
        exit (EXIT_FAILURE);
    }
    arbitrary any_function;
    *(void**)(&any_function) = dlsym(handle, "RunProgram");
    any_function(argc, argv);
    dlclose(handle);
    return 0;
}
