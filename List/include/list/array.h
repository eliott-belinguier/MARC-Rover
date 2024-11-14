#ifndef _LIST_ARRAY_H_
#define _LIST_ARRAY_H_

#include "list.h"

#define LIST_ARRAY_INIT_CAP 5

#define __LIST_ARRAY_MEM_GET(ptr, element_size, index) ((void *) (((char *) (ptr)) + (index) * (element_size)))

#define LIST_ARRAY_INIT(element_size, compare_func) list_array_init(element_size, (int (*)(const generic_t *, const generic_t *)) compare_func)

typedef struct list_array {
    list_s list;
    size_t initial_capacity;
    size_t alloc_size;
    generic_t *items;
} list_array_s;

int __new_list_allocation(list_array_s *list, size_t alloc_to_add);
int __free_excess_memory(list_array_s *list, size_t element_size);

list_s *list_array_init(size_t element_size, int (*compare_func)(const generic_t *, const generic_t *));
ssize_t __list_array_func_add(list_array_s *list, const generic_t *element);
void __list_array_func_clear(list_array_s *list);
void __list_array_func_get(list_array_s *list, size_t index, generic_t *out_element);
int __list_array_func_remove(list_array_s *list, const generic_t *element);
void __list_array_func_remove_index(list_array_s *list, size_t index, generic_t *out_element);

#endif