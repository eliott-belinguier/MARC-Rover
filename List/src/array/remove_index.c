#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list/array.h"

void __list_array_func_remove_index(list_array_s *list, size_t index, generic_t *out_element)
{
    size_t element_size;
    generic_t *list_items;
    generic_t *removed_item_ptr;

    assert(list && index < list->list.size);
    element_size = list->list.element_size;
    list_items = list->items;
    removed_item_ptr = __LIST_ARRAY_MEM_GET(list_items, element_size, index);
    if (out_element)
        memcpy(out_element, removed_item_ptr, element_size);
    memcpy(removed_item_ptr, __LIST_ARRAY_MEM_GET(list_items, element_size, index + 1), (list->list.size - index) * element_size);
    list->list.size -= 1;
    __free_excess_memory(list, element_size);
}