#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

#include "list.h"
#include "tests/libc/malloc.h"
#include "tests/list.h"

Test(list_linked, add_and_get_func)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    int element;

    for (size_t i = 0; i < VALUE_SIZE; ++i) {
        cr_assert_eq(list->size, i);
        cr_assert_eq(LIST_CALL(list, add, &values_init[i]), 1);
        cr_assert_eq(list->size, i + 1);
    }
    for (size_t i = 0; i < VALUE_SIZE; ++i) {
        LIST_CALL(list, get, i, &element);
        cr_assert_eq(element, values_init[VALUE_SIZE - i - 1]);
    }
}

Test(list_linked, add_func_null_parameter_list, .signal = SIGABRT)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);

    list->add(0, &values_init[0]);
}

Test(list_linked, add_func_null_parameter_element, .signal = SIGABRT)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);

    LIST_CALL(list, add, 0);
}

Test(list_linked, get_func_null_parameter_list, .signal = SIGABRT)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    int element;

    LIST_CALL(list, add, &values_init[0]);
    list->get(0, 0, &element);
}

Test(list_linked, get_func_null_parameter_element, .signal = SIGABRT)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);

    LIST_CALL(list, add, &values_init[0]);
    LIST_CALL(list, get, 0, 0);
}

Test(list_linked, get_func_paramater_index_out_of_bounds, .signal = SIGABRT)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    int element;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    LIST_CALL(list, get, VALUE_SIZE, &element);
}

Test(list_linked, get_func_parameter_index_out_of_bounds_2, .signal = SIGABRT)
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
    LIST_CALL(list, get, VALUE_SIZE - 1, &element);
}


Test(list_linked, add_and_get_func_fail_malloc)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);

    test_malloc_error = 1;
    cr_assert_eq(list->size, 0);
    cr_assert_eq(LIST_CALL(list, add, &values_init[0]), -1);
    cr_assert_eq(list->size, 0);
}