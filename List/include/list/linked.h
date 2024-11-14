#ifndef _LIST_LINKED_H_
#define _LIST_LINKED_H_

#include <stdint.h>

#include "list.h"

#define LIST_LINKED_INIT(element_size, compare_func) list_linked_init(element_size, (int (*)(const generic_t *, const generic_t *)) compare_func)

typedef struct list_linked_node {
    struct list_linked_node *next;
    uint8_t item;
} list_linked_node_s;

typedef struct list_linked {
    list_s list;
    list_linked_node_s *items;
} list_linked_s;

list_linked_node_s *__new_list_node(size_t element_size, const generic_t *element);

list_s *list_linked_init(size_t element_size, int (*compare_func)(const generic_t *, const generic_t *));
ssize_t __list_linked_func_add(list_linked_s *list, const void *buffer);
void __list_linked_func_clear(list_linked_s *list);
void __list_linked_func_get(list_linked_s *list, size_t index, generic_t *out_element);
ssize_t __list_linked_func_insert(list_linked_s *list, size_t index, const generic_t *element);
int __list_linked_func_remove(list_linked_s *list, const generic_t *element);
void __list_linked_func_remove_index(list_linked_s *list, size_t index, generic_t *out_element);

#endif