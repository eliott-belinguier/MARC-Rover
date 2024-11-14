#ifndef _LIST_H_
#define _LIST_H_

#include <unistd.h>

#define LIST_CALL(list, method, ...) (list)->method(list, ##__VA_ARGS__)

typedef void generic_t;

typedef struct list {
    int (*func_element_compare)(const generic_t *element1, const generic_t *element2);
    ssize_t (*add)(struct list *list, const generic_t *element);
    void (*clear)(struct list *list);
    void (*get)(struct list *list, size_t index, generic_t *out_element);
    ssize_t (*insert)(struct list *list, size_t index, const generic_t *element);
    int (*remove)(struct list *list, const generic_t *element);
    void (*remove_index)(struct list *list, size_t index, generic_t *out_element);
    size_t element_size;
    size_t size;
} list_s;

#include "list/array.h"
#include "list/linked.h"

#endif