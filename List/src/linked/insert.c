#include <assert.h>
#include <stdlib.h>

#include "list/linked.h"

ssize_t __list_linked_func_insert(list_linked_s *list, size_t index, const generic_t *element)
{
    list_linked_node_s *new_node;
    list_linked_node_s *prev;
    list_linked_node_s *current;

    assert(list && element);
    if (!index)
        return __list_linked_func_add(list, element);
    new_node = __new_list_node(list->list.element_size, element);
    if (!new_node)
        return -1;
    prev = list->items;
    current = prev->next;
    // 0 1 3 N
    //   p c
    for (size_t i = 1; i != index; ++i) {
        prev = current;
        current = current->next;
    }
    new_node->next = current;
    prev->next = new_node;
    list->list.size += 1;
    return 1;
}