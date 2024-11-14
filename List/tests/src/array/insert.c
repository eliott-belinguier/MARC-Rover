#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

#include "list.h"
#include "tests/list.h"

Test(list_array, insert_func)
{
    list_s *list = LIST_ARRAY_INIT(sizeof(int), list_test_default_func_compare);
    int element;

    for (size_t i = 1; i < VALUE_SIZE - 1; ++i) {
        if (i == VALUE_SIZE / 2)
            continue;
        LIST_CALL(list, add, &values_init[i]);
    }
    cr_assert_eq(LIST_CALL(list, insert, 0, &values_init[0]), 1);
    cr_assert_eq(LIST_CALL(list, insert, (VALUE_SIZE / 2), &values_init[VALUE_SIZE / 2]), 1);
    cr_assert_eq(LIST_CALL(list, insert, VALUE_SIZE - 1, &values_init[VALUE_SIZE - 1]), 1);
    for (size_t i = 0; i < VALUE_SIZE; ++i) {
        LIST_CALL(list, get, i, &element);
        cr_assert_eq(element, values_init[i]);
    }
}