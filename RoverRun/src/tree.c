#include <stdlib.h>

#include "tree.h"

static int _fake_node_cmp(tree_node_s *node1, tree_node_s *node2)
{
    return 0;
}

tree_s tree_empty()
{
  tree_s tree;

  tree.root = 0;
  return tree;
}

tree_node_s *tree_node_empty()
{
    tree_node_s *node = malloc(sizeof(tree_node_s));

    if (node == NULL)
      return NULL;
    node->move = 0;
    node->costs = 0;
    node->alive = 1;
    node->childs = LIST_ARRAY_INIT(sizeof(tree_node_s), _fake_node_cmp);
    if (node->childs == NULL) {
        free(node);
        return NULL;
    }
    return node;
}

void node_add_node(tree_node_s *parent, tree_node_s *child)
{
    LIST_CALL(parent->childs, add, child);
}