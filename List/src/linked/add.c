#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list/linked.h"

ssize_t __list_linked_func_add(list_linked_s *list, const generic_t *element)
{
    list_linked_node_s *new_node;

    assert(list && element);
    new_node = __new_list_node(list->list.element_size, element);
    if (!new_node)
        return -1;
    new_node->next = list->items;
    list->items = new_node;
    list->list.size += 1;
    return 1;
}