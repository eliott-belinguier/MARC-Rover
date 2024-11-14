#include <assert.h>
#include <stdlib.h>

#include "list/linked.h"

void __list_linked_func_clear(list_linked_s *list)
{
    list_linked_node_s *current;
    list_linked_node_s *next;

    assert(list);
    for (current = list->items; current; current = next) {
        next = current->next;
        free(current);
    }
    list->items = 0;
    list->list.size = 0;
}