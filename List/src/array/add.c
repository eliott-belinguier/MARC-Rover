#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list/array.h"

ssize_t __list_array_func_add(list_array_s *list, const generic_t *element)
{
    size_t list_size;
    size_t element_size;
    size_t alloc_current_use;

    assert(list && element);
    list_size = list->list.size;
    element_size = list->list.element_size;
    alloc_current_use = list_size * element_size;
    if (alloc_current_use + element_size > list->alloc_size && __new_list_allocation(list, element_size) == -1)
        return -1;
    memcpy((char *) list->items + list_size * element_size, element, element_size);
    list->list.size += 1;
    return 1;
}