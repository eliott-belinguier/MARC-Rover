#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <errno.h>
#include <signal.h>

#include "list.h"
#include "tests/libc/realloc.h"
#include "tests/list.h"

Test(list_array, remove_index_func)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    int element;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    errno = 0;
    for (size_t i = 0; i < VALUE_SIZE_TO_REMOVE; ++i) {
        cr_assert_eq(list->size, VALUE_SIZE - i);
        LIST_CALL(list, remove_index, values_index_to_remove[i], &element);
        cr_assert_eq(element, values_to_remove[i]);
        cr_assert_eq(list->size, VALUE_SIZE - i - 1);
    }
    for (size_t i = 0; i < VALUE_SIZE_AFTER_REMOVE; ++i) {
        LIST_CALL(list, get, i, &element);
        cr_assert_eq(element, values_after_remove[i]);
    }
}

Test(list_array, remove_index_func_null_parameter_output)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
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
        cr_assert_eq(element, values_after_remove[i]);
    }
}

Test(list_array, remove_index_func_null_parameter_list, .signal = SIGABRT)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    int element = 0;

    list->remove_index(0, 0, &element);
    free(list);
}

Test(list_array, remove_index_func_paramater_index_out_of_bounds, .signal = SIGABRT)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    int element = 0;

    LIST_CALL(list, remove_index, 1, &element);
    free(list);
}