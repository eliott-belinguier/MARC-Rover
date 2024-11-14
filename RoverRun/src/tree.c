#include <stdlib.h>

#include "map.h"
#include "tree.h"

#include <queue.h>

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
    node->childs = LIST_ARRAY_INIT(sizeof(tree_node_s *), _fake_node_cmp);
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

tree_node_s *node_add_cell_node(tree_node_s *parent, map_s map, position_s pos, t_move move)
{
    tree_node_s *node = tree_node_empty();

    node->move = move;
    node->costs = map.costs[pos.y][pos.x];
    node->alive = POSITION_IS_VALID(pos, map.width, map.height) && map.soils[pos.y][pos.y] != CREVASSE;
    node_add_node(parent, node);
    return node;
}

tree_s tree_from_map(map_s map, position_s start) {
    tree_s tree = tree_empty();
    tree_node_s *parent;
    list_s *node_queue = LIST_LINKED_INIT(sizeof(tree_node_s *), _fake_node_cmp);
    t_queue queue = createQueue(map.width * map.height * 2);
    position_s current;
    const int *direction_vector;
    position_s compute_pos;
    tree_node_s *compute_node;

    parent = tree_node_empty();
    parent->move = -1;
    parent->costs = map.costs[start.y][start.x];
    parent->alive = POSITION_IS_VALID(start, map.width, map.height) && map.soils[start][start.y] != CREVASSE;
    tree.root = parent;
    if (parent->alive == 0)
        return tree;
    enqueue(&queue, start);
    LIST_CALL(node_queue, add, &parent);
    while (queue.first != queue.last) {
        current = dequeue(&queue);
        LIST_CALL(node_queue, remove_index, 0, &parent);
        for (int i = 0; i < 4; ++i) {
            direction_vector = _direction_vectors[i];

            compute_pos = (position_s) {
                .x = current.x + direction_vector[0],
                .y = current.y + direction_vector[1]
            };
            compute_node = node_add_cell_node(parent, map, compute_pos, 0);
            if (POSITION_IS_VALID(compute_pos, map.width, map.height) && compute_node->alive) {
                enqueue(&queue, compute_pos);
                LIST_CALL(node_queue, add, &compute_node);
            }
        }
    }
    return tree;
}