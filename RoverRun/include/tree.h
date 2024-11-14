#ifndef _ROVERRUN_TREE_H_
#define _ROVERRUN_TREE_H_

#include "list.h"
#include "moves.h"

typedef struct tree_node {
  t_move move;
  int costs;
  int alive;
  list_s *childs;
} tree_node_s;

typedef struct tree {
  tree_node_s *root;
} tree_s;

tree_s tree_empty();
tree_node_s *tree_node_empty();


#endif