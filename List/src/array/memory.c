#include <stdlib.h>

#include "list/array.h"

int __new_list_allocation(list_array_s *list, size_t alloc_to_add)
{
    size_t alloc_size = list->alloc_size + alloc_to_add + list->initial_capacity * list->list.element_size;
    generic_t *new_ptr = realloc(list->items, alloc_size);

    if (!new_ptr)
        return -1;
    list->alloc_size = alloc_size;
    list->items = new_ptr;
    return 0;
}

int __free_excess_memory(list_array_s *list, size_t element_size)
{
    size_t alloc_size = list->alloc_size;
    size_t init_capacity_size = list->initial_capacity * element_size;
    size_t excess_memory = alloc_size - list->list.size * element_size;
    generic_t *new_ptr;

    if (excess_memory <= init_capacity_size)
        return 0;
    alloc_size = alloc_size - excess_memory + init_capacity_size;
    new_ptr = realloc(list->items, alloc_size);
    if (!new_ptr)
        return -1;
    list->items = new_ptr;
    list->alloc_size = alloc_size;
    return 0;
}