#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

#include "list.h"
#include "tests/libc/malloc.h"
#include "tests/list.h"

Test(list_linked, init_func)
{
    list_s *list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    list_linked_s *list_linked = (list_linked_s *) list;

    cr_assert_eq(list->size, 0);;
    cr_assert_eq(list_linked->items, 0);
    cr_assert_eq(list->func_element_compare, (int (*)(const generic_t *, const generic_t *)) list_test_default_func_compare);
    free(list);
}

Test(list_linked, init_func_fail_element_size, .signal = SIGABRT)
{
    LIST_LINKED_INIT(0, list_test_default_func_compare);
}

Test(list_linked, init_func_null_parameter_func_compare, .signal = SIGABRT)
{
    LIST_LINKED_INIT(sizeof(int), 0);
}

Test(list_linked, init_func_null_parameter_element_size_and_func_compare, .signal = SIGABRT)
{
    LIST_LINKED_INIT(0, 0);
}

Test(list_linked, init_func_fail_list_alloc)
{
    list_s *list;

    test_malloc_error = 1;
    list = LIST_LINKED_INIT(sizeof(int), list_test_default_func_compare);
    cr_assert_eq(list, 0);
    free(list);
}