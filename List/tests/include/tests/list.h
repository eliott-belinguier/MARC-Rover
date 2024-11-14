#ifndef _TEST_LIST_H_
#define _TEST_LIST_H_

#define VALUE_SIZE 22
#define VALUE_SIZE_TO_REMOVE 5
#define VALUE_SIZE_AFTER_REMOVE (VALUE_SIZE - VALUE_SIZE_TO_REMOVE)

static const int values_init[] = {1, 2, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
static const int values_index_to_remove[] = {5, 0, 0, 18, 17};
static const int values_to_remove[] = {6, 1, 2, 22, 21};
static const int values_to_remove_revert[] = {17, 22, 21, 1, 2};
static const int values_after_remove[] = {2, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
static const int values_after_remove_revert[] = {20, 19, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 2};

int list_test_default_func_compare(int nb1, int nb2);

#endif