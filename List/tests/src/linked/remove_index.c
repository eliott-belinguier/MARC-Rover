#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <errno.h>
#include <signal.h>

#include "list.h"
#include "tests/libc/realloc.h"
#include "tests/list.h"

Test(list_linked, remove_index_func)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    int element;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    errno = 0;
    for (size_t i = 0; i < VALUE_SIZE_TO_REMOVE; ++i) {
        cr_assert_eq(list->size, VALUE_SIZE - i);
        LIST_CALL(list, remove_index, values_index_to_remove[i], &element);
        cr_assert_eq(element, values_to_remove_revert[i]);
        cr_assert_eq(list->size, VALUE_SIZE - i - 1);
    }
    for (size_t i = 0; i < VALUE_SIZE_AFTER_REMOVE; ++i) {
        LIST_CALL(list, get, i, &element);
        cr_assert_eq(element, values_after_remove_revert[i]);
    }
}

Test(list_linked, remove_index_func_null_parameter_output)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    int element;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    errno = 0;
    for (size_t i = 0; i < VALUE_SIZE_TO_REMOVE; ++i) {
        cr_assert_eq(list->size, VALUE_SIZE - i);
        LIST_CALL(list, remove_index, values_index_to_remove[i], 0);
        cr_assert_eq(list->size, VALUE_SIZE - i - 1);
    }
    for (size_t i = 0; i < VALUE_SIZE_AFTER_REMOVE; ++i) {
        LIST_CALL(list, get, i, &element);
        cr_assert_eq(element, values_after_remove_revert[i]);
    }
}

Test(list_linked, remove_index_func_null_parameter_list, .signal = SIGABRT)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    int element = 0;

    list->remove_index(0, 0, &element);
    free(list);
}

Test(list_linked, remove_index_func_paramater_index_out_of_bounds, .signal = SIGABRT)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    int element = 0;

    LIST_CALL(list, remove_index, 1, &element);
    free(list);
}

Test(list_linked, remove_index_func_paramater_index_out_of_bounds_2, .signal = SIGABRT)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    list_linked_s *list_linked = (list_linked_s *) list;
    list_linked_node_s *node_to_remove;
    int element;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    node_to_remove = list_linked->items;
    list_linked->items = node_to_remove->next;
    free(node_to_remove);
    LIST_CALL(list, remove_index, VALUE_SIZE - 1, &element);
}