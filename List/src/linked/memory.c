#include <stdlib.h>
#include <string.h>

#include "list/linked.h"

list_linked_node_s *__new_list_node(size_t element_size, const generic_t *element)
{
    list_linked_node_s *new_node = malloc(sizeof(list_linked_node_s) + element_size - sizeof(uint8_t));

    if (!new_node)
        return 0;
    new_node->next = 0;
    memcpy(&new_node->item, element, element_size);
    return new_node;
}