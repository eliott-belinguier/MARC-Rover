#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

#include "list.h"
#include "tests/libc/realloc.h"
#include "tests/list.h"

Test(list_array, remove_func)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    int element;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    for (size_t i = 0; i < VALUE_SIZE_TO_REMOVE; ++i) {
        cr_assert_eq(list->size, VALUE_SIZE - i);
        cr_assert_eq(LIST_CALL(list, remove, &values_to_remove[i]), 1);
        cr_assert_eq(list->size, VALUE_SIZE - i - 1);
    }
    for (size_t i = 0; i < VALUE_SIZE_AFTER_REMOVE; ++i) {
        LIST_CALL(list, get, i, &element);
        cr_assert_eq(element, values_after_remove[i]);
    }
}

Test(list_array, remove_func_unfind_value)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    int element = 404;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    cr_assert_eq(LIST_CALL(list, remove, &element), 0);
    for (size_t i = 0; i < VALUE_SIZE; ++i) {
        LIST_CALL(list, get, i, &element);
        cr_assert_eq(element, values_init[i]);
    }
    cr_assert_eq(list->size, VALUE_SIZE);
}

Test(list_array, remove_func_null_parameter_list, .signal = SIGABRT)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    int element = 404;

    list->remove(0, &element);
    free(list);
}

Test(list_array, remove_func_null_compare_func, .signal = SIGABRT)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    int element = 404;

    list->func_element_compare = 0;
    LIST_CALL(list, remove, &element);
    free(list);
}

Test(list_array, remove_func_fail_realloc) {
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    list_array_s *list_array = (list_array_s *) list;
    size_t limit = list_array->initial_capacity - 1;
    int element;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    test_realloc_error = 1;
    for (size_t i = 0; i < VALUE_SIZE; ++i) {
        LIST_CALL(list, get, 0, &element);
        cr_assert_eq(LIST_CALL(list, remove, &element), i == limit ? -1 : 1);
    }
}