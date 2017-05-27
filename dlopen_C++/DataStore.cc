#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>

#include "DataStore.h"

/*
 * Callback exported by the "DataStore" to a stored procedure.
 */
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

    // Open the user-supplied procedure that was compiled as a shared object.
    // RTLD_LAZY performs lazy symbol resolution on the shared object. This
    // can(should?) be replaced with RTLD_NOW to perform all symbol resolution
    // before dlopen() returns.
    testHandle = dlopen("./UserProcedure.so", RTLD_LAZY);

    if (testHandle == NULL) {
        fprintf(stdout, "Error in opening shared object: %s\n", dlerror());
        return (-1);
    }

    // This part is a little tricky. dlsym() returns a void*. According to
    // the ISO-C standard, casting from a void* to a function pointer will
    // result in undefined behavior. The workaround appears to be to cast
    // a pointer to the function-pointer to void** and then dereference it.
    *(void **)(&invoke) = dlsym(testHandle, "procedure_invoke");

    if (invoke == NULL) {
        fprintf(stdout, "Error in accessing symbol from shared object: %s\n",
                dlerror());
        return (-2);
    }

    // Invoke the "stored" procedure.
    (*invoke)();

    retVal = dlclose(testHandle);

    if (retVal != 0) {
        fprintf(stdout, "Error in closing shared object: %s\n", dlerror());
        return (-3);
    }

    return (0);
}
