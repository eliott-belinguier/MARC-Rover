#include <assert.h>
#include <stdlib.h>

#include "list/array.h"

list_s *list_array_init(size_t element_size, int (*compare_func)(const generic_t *, const generic_t *))
{
    list_array_s *list;

    assert(element_size != 0 && compare_func);
    list = malloc(sizeof(list_array_s));
    if (!list)
        return 0;
    *list = (list_array_s) {
        .list = {
            .func_element_compare = compare_func,
            .add = (ssize_t(*)(list_s *, const void *)) __list_array_func_add,
            .clear = (void (*)(list_s *)) __list_array_func_clear,
            .get = (void (*)(list_s *, size_t, generic_t *)) __list_array_func_get,
            .remove = (int (*)(list_s *, const generic_t *)) __list_array_func_remove,
            .remove_index = (void (*)(list_s *, size_t, generic_t *)) __list_array_func_remove_index,
            .element_size = element_size,
            .size = 0
        },
        .initial_capacity = LIST_ARRAY_INIT_CAP,
        .alloc_size = LIST_ARRAY_INIT_CAP * element_size
    };
    list->items = malloc(list->alloc_size);
    if (!list->items) {
        free(list);
        return 0;
    }
    return (list_s *) list;
}