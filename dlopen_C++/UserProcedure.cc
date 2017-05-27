#include <cstdio>

#include "DataStore.h"

/*
 * A simple test class.
 */
class TestProcedure {
  public:
    TestProcedure()
      : number(10)
      {}
    ~TestProcedure() {}

    void
    invoke(void)
    {
        // Callback to the "DataStore".
        printNumber(number);
    }

    int number;
};

/*
 * The "stored" procedure to be invoked by the "DataStore".
 */
extern "C" void
procedure_invoke(void)
{
    fprintf(stdout, "========== Entered Tenant ==========\n");

    TestProcedure test;
    test.invoke();

    fprintf(stdout, "========== Exiting Tenant ==========\n");
}
