#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list/array.h"

ssize_t __list_array_func_insert(list_array_s *list, size_t index, const generic_t *element)
{
    size_t list_size;
    size_t element_size;
    size_t alloc_current_use;

    assert(list && element);
    list_size = list->list.size;
    if (index == list_size)
        return __list_array_func_add(list, element);
    element_size = list->list.element_size;
    alloc_current_use = list_size * element_size;
    if (alloc_current_use + element_size > list->alloc_size && __new_list_allocation(list, element_size) == -1)
        return -1;
    for (ssize_t i = list_size - 1; i != index; --i)
        memcpy((char *) list->items + (i + 1) * element_size, (char *) list->items + i * element_size, element_size);
    memcpy((char *) list->items + (index + 1) * element_size, (char *) list->items + index * element_size, element_size);
    memcpy((char *) list->items + index * element_size, element, element_size);
    list->list.size += 1;
    return 1;
}