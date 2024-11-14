#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

#include "list.h"
#include "tests/list.h"

Test(list_linked, clear_func)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    list_linked_s *list_linked = (list_linked_s *) list;

    for (size_t i = 0; i < VALUE_SIZE; ++i)
        LIST_CALL(list, add, &values_init[i]);
    cr_assert_eq(list->size, VALUE_SIZE);
    LIST_CALL(list,clear);
    cr_assert_eq(list->size, 0);
    cr_assert_eq(list_linked->items, 0);
    free(list);
}

Test(list_linked, missing_parameter, .signal = SIGABRT)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);

    list->clear(0);
    free(list);
}