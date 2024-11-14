#include <assert.h>
#include <stdlib.h>

#include "list/array.h"

struct test {
    int value : 2;
    int test : 4;
};

list_s *list_linked_init(size_t element_size, int (*compare_func)(const generic_t *, const generic_t *))
{
    list_linked_s *list;

    assert(element_size != 0 && compare_func);
    list = malloc(sizeof(list_linked_s));
    if (!list)
        return 0;
    *list = (list_linked_s) {
        .list = {
            .func_element_compare = (int (*)(const generic_t *, const generic_t *)) compare_func,
            .add = (ssize_t (*)(list_s *, const generic_t *)) __list_linked_func_add,
            .clear = (void (*)(list_s *)) __list_linked_func_clear,
            .get = (void (*)(list_s *, size_t, generic_t *)) __list_linked_func_get,
            .remove = (int (*)(list_s *, const generic_t *)) __list_linked_func_remove,
            .remove_index = (void (*)(list_s *, size_t, generic_t *)) __list_linked_func_remove_index,
            .element_size = element_size,
            .size = 0
        },
        .items = 0
    };
    return (list_s *) list;
}