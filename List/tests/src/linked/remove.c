#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

#include "list.h"
#include "tests/libc/realloc.h"
#include "tests/list.h"

Test(list_linked, remove_func)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
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
        cr_assert_eq(element, values_after_remove[VALUE_SIZE_AFTER_REMOVE - i - 1]);
    }
}

Test(list_linked, remove_func_unfind_value)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    int element = 404;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    cr_assert_eq(LIST_CALL(list, remove, &element), 0);
    for (size_t i = 0; i < VALUE_SIZE; ++i) {
        LIST_CALL(list, get, i, &element);
        cr_assert_eq(element, values_init[VALUE_SIZE - i - 1]);
    }
    cr_assert_eq(list->size, VALUE_SIZE);
}