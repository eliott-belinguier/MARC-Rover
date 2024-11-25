#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "moves.h"
#include "queue.h"
#include "tree.h"

#define LOC_SOIL(map, loc) (map).soils[(loc).pos.y][(loc).pos.x]
#define RAND(min, max) ((min) + rand() % ((max) - (min) + 1))
#define SWITCH_VALUE(type, val1, val2)      \
    {                                       \
        type tmp;                           \
                                            \
        tmp = val1;                         \
        val1 = val2;                        \
        val2 = tmp;                         \
    }

static int _fake_node_cmp(tree_node_s **node1, tree_node_s **node2)
{
    return 0;
}

static void _random_move(t_move move_inst[U_TURN + 1])
{
    t_move *random_move;

    for (t_move i = F_10; i <= U_TURN; ++i)
        move_inst[i] = i;
    for (size_t i = 0; i <= U_TURN; ++i) {
        random_move = &move_inst[RAND(0, U_TURN - i)];
        SWITCH_VALUE(t_move, move_inst[U_TURN - i - 1], *random_move);
    }
}

static localisation_s _compute_move_by_soil(map_s map, localisation_s loc, t_move move_inst)
{
    if (LOC_SOIL(map, loc) != ERG)
        return move(loc, move_inst);
    switch (move_inst) {
        case F_10:
        case B_10:
        case T_LEFT:
        case T_RIGHT:
            return loc;
            break;
        case F_20:
            return move(loc, F_10);
        case F_30:
            return move(loc, F_20);
        case U_TURN:
            return move(loc, RAND(0, 1) ? T_LEFT : T_RIGHT);
    }
    return loc;
}

tree_s tree_empty()
{
  tree_s tree;

  tree.root = 0;
  return tree;
}

tree_node_s *tree_node_empty(map_s map)
{
    static unsigned int available_moves[7] = {22, 15, 7, 7, 21, 21, 7};
    tree_node_s *node = malloc(sizeof(tree_node_s));
    size_t map_size;

    if (node == NULL)
      return NULL;
    node->move = 0;
    node->loc = (localisation_s) {0};
    node->costs = 0;
    node->alive = 1;
    node->childs = LIST_ARRAY_INIT(sizeof(tree_node_s *), _fake_node_cmp);
    memcpy(node->move_count, available_moves, sizeof(available_moves));
    map_size = map.width * map.height;
    node->visited = malloc(sizeof(uint8_t) *map_size);
    memset(node->visited, 0, sizeof(uint8_t) * map_size);
    if (node->childs == NULL) {
        free(node);
        return NULL;
    }
    if (!node->visited) {
        free(node->childs);
        free(node);
    }
    return node;
}

void node_add_node(map_s map, tree_node_s *parent, tree_node_s *child)
{
    tree_node_s *current;
    size_t i = 0;

    memcpy(child->move_count, parent->move_count, sizeof(unsigned int) * (U_TURN + 1));
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
    position_s position;

    if (!parent->move_count[move])
        return NULL;
    node = tree_node_empty(map);
    node->move = move;
    node->loc = localisation;
    memcpy(node->visited, parent->visited, sizeof(uint8_t) * map.width * map.height);
    if (POSITION_IS_VALID(localisation.pos, map.width, map.height)) {
        node->costs = map.costs[localisation.pos.y][localisation.pos.x];
        node->alive = map.soils[localisation.pos.y][localisation.pos.x] != CREVASSE;
        position = node->loc.pos;
        node->visited[position.y * map.width + position.x] = 1;
    } else {
        node->costs = COST_UNDEF;
        node->alive = 0;
    }
    node_add_node(map, parent, node);
    return node;
}



tree_s tree_from_map(map_s map, localisation_s start) {
    t_move move_inst[U_TURN + 1];
    tree_s tree = tree_empty();
    tree_node_s *parent;
    list_s *node_queue = LIST_LINKED_INIT(sizeof(tree_node_s *), _fake_node_cmp);
    size_t move_limit;

    localisation_s compute_loc;
    tree_node_s *compute_node;
    parent = tree_node_empty(map);
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
        _random_move(move_inst);
        move_limit = LOC_SOIL(map, parent->loc) == REG ? 4 : U_TURN + 1;
        for (size_t i = 0; i < move_limit; ++i) {
            compute_loc = _compute_move_by_soil(map, parent->loc, move_inst[i]);
            compute_node = node_add_cell_node(parent, map, move_inst[i], compute_loc);
            if (compute_node && compute_node->alive && !parent->visited[compute_loc.pos.y * map.width + compute_loc.pos.x])
                LIST_CALL(node_queue, add, &compute_node);
            else if (compute_node) {
                free(compute_node->childs);
                free(compute_node->visited);
                free(compute_node);
            }
        }
    }
    free(node_queue);
    return tree;
}