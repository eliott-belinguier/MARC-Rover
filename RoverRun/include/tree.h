#ifndef _ROVERRUN_TREE_H_
#define _ROVERRUN_TREE_H_

#include "list.h"
#include "moves.h"

typedef struct tree_node {
  t_move move;
  localisation_s loc;
  unsigned int costs;
  int alive;
  list_s *childs;
  unsigned int move_count[U_TURN + 1];
} tree_node_s;

typedef struct tree {
  tree_node_s *root;
} tree_s;

tree_s tree_empty();
tree_node_s *tree_node_empty();
void node_add_node(tree_node_s *parent, tree_node_s *child);
tree_node_s *node_add_cell_node(tree_node_s *parent, map_s map, t_move move, localisation_s localisation);
tree_s tree_from_map(map_s map, localisation_s start);


#endif