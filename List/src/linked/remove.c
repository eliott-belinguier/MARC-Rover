#include <assert.h>
#include <stdlib.h>

#include "list/linked.h"

int __list_linked_func_remove(list_linked_s *list, const generic_t *element)
{
    int (*compare_func)(const generic_t *, const generic_t *);
    list_linked_node_s *prev = 0;
    list_linked_node_s *current;

    assert(list && list->list.func_element_compare);
    compare_func = list->list.func_element_compare;
    current = list->items;
    for (; current && compare_func(&current->item, element); prev = current, current = current->next);
    if (!current)
        return 0;
    if (prev)
        prev->next = current->next;
    else
        list->items = current->next;
    free(current);
    list->list.size -= 1;
    return 1;
}