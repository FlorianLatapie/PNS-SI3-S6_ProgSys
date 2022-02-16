#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "sort.h"

static void (*sortlib)(int [], int);
static void *handle;

void sort_from_lib(int tab[], int size){
    sortlib(tab,size);
}

void load_library(char *library_name){
    char *error;

    handle = dlopen(library_name, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror();    /* Clear any existing error */

    sortlib = (void(*) (int[], int)) dlsym(handle, "sort");

    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
}

void unload_library(){
    dlclose(handle);
}