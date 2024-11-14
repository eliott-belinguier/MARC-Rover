#include <assert.h>

#include <stdlib.h>

#include "list/array.h"

void __list_array_func_clear(list_array_s *list)
{
    size_t alloc_size;

    assert(list);
    alloc_size = list->initial_capacity * list->list.element_size;;
    list->list.size = 0;
    list->alloc_size = alloc_size;
    list->items = realloc(list->items, alloc_size);
}