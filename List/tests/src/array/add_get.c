#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

#include "list.h"
#include "tests/libc/realloc.h"
#include "tests/list.h"

Test(list_array, add_and_get_func)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    int element;

    for (size_t i = 0; i < VALUE_SIZE; ++i) {
        cr_assert_eq(list->size, i);
        cr_assert_eq(LIST_CALL(list, add, &values_init[i]), 1);
        cr_assert_eq(list->size, i + 1);
    }
    for (size_t i = 0; i < VALUE_SIZE; ++i) {
        LIST_CALL(list, get, i, &element);
        cr_assert_eq(element, values_init[i]);
    }
}

Test(list_array, add_func_null_parameter_list, .signal = SIGABRT)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);

    list->add(0, &values_init[0]);
}

Test(list_array, add_func_fail_realloc)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    list_array_s *list_array = (list_array_s *) list;
    int value;

    for (size_t i = 0; i < list_array->initial_capacity; ++i) {
        value = i;
        cr_assert_eq(LIST_CALL(list, add, &value), 1);
    }
    test_realloc_error = 1;
    cr_assert_eq(LIST_CALL(list, add, &values_init[0]), -1);
    free(list);
}


Test(list_array, add_func_null_parameter_element, .signal = SIGABRT)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);

    LIST_CALL(list, add, 0);
}

Test(list_array, get_func_null_parameter_list, .signal = SIGABRT)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    int element;

    LIST_CALL(list, add, &values_init[0]);
    list->get(0, 0, &element);
}

Test(list_array, get_func_null_parameter_element, .signal = SIGABRT)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);

    LIST_CALL(list, add, &values_init[0]);
    LIST_CALL(list, get, 0, 0);
}

Test(list_array, get_func_parameter_index_out_of_bounds, .signal = SIGABRT)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    int element;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    LIST_CALL(list, get, VALUE_SIZE, &element);
}