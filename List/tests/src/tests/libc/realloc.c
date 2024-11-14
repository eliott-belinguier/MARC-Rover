#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int test_realloc_error = 0;

void *__libc_realloc(void *ptr, size_t size);

void *__test_realloc(void *ptr, size_t size)
{
    if (test_realloc_error == -1 || test_realloc_error > 0) {
        test_realloc_error -= (test_realloc_error > 0) ? 1 : 0;
        errno = ENOMEM;
        return 0;
    }
    if (test_realloc_error < -1)
        test_realloc_error += (test_realloc_error == -2) ? 3 : 1;
    return __libc_realloc(ptr, size);
}

void *realloc(void *ptr, size_t size) __attribute__((alias ("__test_realloc")));