#include <errno.h>
#include <stdlib.h>

int test_malloc_error = 0;

void *__libc_malloc(size_t size);

void *__test_malloc(size_t size)
{
    if (test_malloc_error == -1 || test_malloc_error > 0) {
        test_malloc_error -= test_malloc_error > 0 ? 1 : 0;
        errno = ENOMEM;
        return 0;
    }
    if (test_malloc_error < -1)
        test_malloc_error += test_malloc_error == -2 ? 3 : 1;
    return __libc_malloc(size);
}

void *malloc(size_t size) __attribute__((alias ("__test_malloc")));