#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>

#include "DataStore.h"

void
printNumber(int number) {
    fprintf(stdout, "========== Entered DStore ==========\n");

    fprintf(stdout, "Number: %d\n", number);

    fprintf(stdout, "========== Exiting DStore ==========\n");
}

int
main(void)
{
    void* testHandle = NULL;
    void (*invoke)(void) = NULL;
    int retVal = 0;

    testHandle = dlopen("./UserProcedure.so", RTLD_LAZY);

    if (testHandle == NULL) {
        fprintf(stdout, "Error in opening shared object: %s\n", dlerror());
        return (-1);
    }

    *(void **)(&invoke) = dlsym(testHandle, "procedure_invoke");

    if (invoke == NULL) {
        fprintf(stdout, "Error in accessing symbol from shared object: %s\n",
                dlerror());
        return (-2);
    }

    (*invoke)();

    retVal = dlclose(testHandle);

    if (retVal != 0) {
        fprintf(stdout, "Error in closing shared object: %s\n", dlerror());
        return (-3);
    }

    return (0);
}
