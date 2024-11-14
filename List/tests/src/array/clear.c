#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

#include "list.h"
#include "tests/list.h"

Test(list_array, clear_func)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    list_array_s *list_array = (list_array_s *) list;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    cr_assert_eq(list->size, VALUE_SIZE);
    LIST_CALL(list,clear);
    cr_assert_eq(list->size, 0);
    cr_assert_eq(list_array->alloc_size, list_array->initial_capacity * list->element_size);
    free(list);
}

Test(list_array, clear_func_null_parameter_list, .signal = SIGABRT)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);

    list->clear(0);
    free(list);
}