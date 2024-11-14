#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list/array.h"

int __list_array_func_remove(list_array_s *list, const generic_t *element)
{
    int (*compare_func)(const generic_t *, const generic_t *);
    size_t element_size;
    size_t list_size;
    generic_t *list_items;
    size_t i;

    assert(list && list->list.func_element_compare);
    compare_func = list->list.func_element_compare;
    element_size = list->list.element_size;
    list_size = list->list.size;
    list_items = list->items;

    for (i = 0; i < list_size && compare_func(__LIST_ARRAY_MEM_GET(list_items, element_size, i), element); ++i);
    if (i == list_size)
        return 0;
    memcpy(__LIST_ARRAY_MEM_GET(list_items, element_size, i), __LIST_ARRAY_MEM_GET(list_items, element_size, i + 1), (list_size - i) * element_size);
    list->list.size -= 1;
    if (__free_excess_memory(list, element_size) == -1)
        return -1;
    return 1;
}