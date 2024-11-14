#include <assert.h>
#include <string.h>

#include "list/linked.h"

void __list_linked_func_get(list_linked_s *list, size_t index, generic_t *out_element)
{
    size_t i = 0;
    list_linked_node_s *current;

    assert(list && out_element && index < list->list.size);
    current = list->items;
    for (; current && i != index; ++i, current = current->next);
    assert(current);
    memcpy(out_element, &current->item, list->list.element_size);
}