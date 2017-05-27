#include <cstdio>

#include "DataStore.h"

class TestProcedure {
  public:
    TestProcedure()
      : number(10)
      {}
    ~TestProcedure() {}

    void
    invoke(void)
    {
        printNumber(number);
    }

    int number;
};

extern "C" void procedure_invoke(void)
{
    fprintf(stdout, "========== Entered Tenant ==========\n");

    TestProcedure test;
    test.invoke();

    fprintf(stdout, "========== Exiting Tenant ==========\n");
}
