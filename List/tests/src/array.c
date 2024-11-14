#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>
#include <stdlib.h>
#include <gcov.h>

#include "list.h"
#include "tests/list.h"

extern void __gcov_flush(void);

static void __signal_abrt_handler(int signum)
{

    __gcov_dump();   // Write coverage data to files
    __gcov_reset();
    signal(signum, SIG_DFL);
    raise(signum);
}

static void __setup_signal_handler()
{
    signal(SIGABRT, __signal_abrt_handler);
}

TestSuite(list_array, .init = __setup_signal_handler);