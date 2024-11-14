#include <assert.h>
#include <string.h>

#include "list/array.h"

void __list_array_func_get(list_array_s *list, size_t index, generic_t *out_element)
{
    size_t element_size;

    assert(list && out_element && index < list->list.size);
    element_size = list->list.element_size;
    memcpy(out_element, __LIST_ARRAY_MEM_GET(list->items, element_size, index), element_size);
}