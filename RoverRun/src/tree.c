#include <stdlib.h>

#include "map.h"
#include "moves.h"
#include "tree.h"

#include <queue.h>
#include <string.h>

static int _fake_node_cmp(tree_node_s **node1, tree_node_s **node2)
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
    static unsigned int available_moves[7] = {22, 15, 7, 7, 21, 21, 7};
    tree_node_s *node = malloc(sizeof(tree_node_s));

    if (node == NULL)
      return NULL;
    node->move = 0;
    node->loc = {0};
    node->costs = 0;
    node->alive = 1;
    node->childs = LIST_ARRAY_INIT(sizeof(tree_node_s *), _fake_node_cmp);
    memcpy(node->move_count, available_moves, sizeof(available_moves));
    if (node->childs == NULL) {
        free(node);
        return NULL;
    }
    return node;
}

void node_add_node(tree_node_s *parent, tree_node_s *child)
{
    tree_node_s *current;
    size_t i = 0;

    memcpy(child->move_count, parent->move_count, sizeof(child->move));
    child->move_count[child->move] -= 1;
    if (parent->childs->size == 0) {
        LIST_CALL(parent->childs, add, &child);
        return;
    }
    for (; i < parent->childs->size; ++i) {
        LIST_CALL(parent->childs, get, i, &current);
        if (child->costs < current->costs)
            break;
    }
    LIST_CALL(parent->childs, insert, i, &child);
}

tree_node_s *node_add_cell_node(tree_node_s *parent, map_s map, t_move move, localisation_s localisation)
{
    tree_node_s *node;

    if (!parent->move_count[move])
        return NULL;
    node = tree_node_empty();
    node->move = move;
    node->loc = localisation;
    node->costs = map.costs[localisation.pos.y][localisation.pos.x];
    node->alive = POSITION_IS_VALID(localisation.pos, map.width, map.height) && map.soils[localisation.pos.y][localisation.pos.y] != CREVASSE;
    node_add_node(parent, node);
    return node;
}

tree_s tree_from_map(map_s map, localisation_s start) {
    tree_s tree = tree_empty();
    tree_node_s *parent;
    list_s *node_queue = LIST_LINKED_INIT(sizeof(tree_node_s *), _fake_node_cmp);

    localisation_s compute_loc;
    tree_node_s *compute_node;
    parent = tree_node_empty();
    parent->move = -1;
    parent->loc = start;
    parent->costs = map.costs[start.pos.y][start.pos.x];
    parent->alive = POSITION_IS_VALID(start.pos, map.width, map.height) && map.soils[start.pos.y][start.pos.x] != CREVASSE;
    tree.root = parent;
    if (parent->alive == 0)
        return tree;
    LIST_CALL(node_queue, add, &parent);
    while (node_queue->size) {
        LIST_CALL(node_queue, remove_index, 0, &parent);
        for (t_move move_inst = F_10; move_inst <= U_TURN; ++move_inst) {
            compute_loc = move(parent->loc, move_inst);
            compute_node = node_add_cell_node(parent, map, move_inst, compute_loc);
            if (compute_node && compute_node->alive)
                LIST_CALL(node_queue, add, &compute_node);
        }
    }
    free(node_queue);
    return tree;
}