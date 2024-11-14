#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list/linked.h"

void __list_linked_func_remove_index(list_linked_s *list, size_t index, generic_t *out_element)
{
    size_t i = 0;
    list_linked_node_s *prev = 0;
    list_linked_node_s *current;

    assert(list && index < list->list.size);
    current = list->items;
    for (; current && i != index; ++i, prev = current, current = current->next);
    assert(current);
    if (out_element)
        memcpy(out_element, &current->item, list->list.element_size);
    if (prev)
        prev->next = current->next;
    else
        list->items = current->next;
    free(current);
    list->list.size -= 1;
}