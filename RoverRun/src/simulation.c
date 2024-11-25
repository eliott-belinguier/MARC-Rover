#include "list.h"
#include "map.h"
#include "marc.h"

static int _fake_node_cmp(tree_node_s **node1, tree_node_s **node2)
{
    return 0;
}

list_s *_build_path(tree_node_s *node)
{
    list_s *path = LIST_ARRAY_INIT(sizeof(tree_node_s *), _fake_node_cmp);

    for (tree_node_s *current = node; current; current = current->parent)
        LIST_CALL(path, add, &current);
    return path;
}

list_s *find_path(marc_s marc)
{
    list_s *node_stack = LIST_LINKED_INIT(sizeof(tree_node_s *), _fake_node_cmp);
    tree_node_s *current;
    tree_node_s *child;

    if (!marc.all_states.root->alive)
        return _build_path(marc.all_states.root);
    LIST_CALL(node_stack, add, &marc.all_states.root);
    while (node_stack->size) {
        LIST_CALL(node_stack, remove_index, 0, &current);
        for (size_t i = 0; i < current->childs->size; ++i) {
            LIST_CALL(current->childs, get, i, &child);
            if (POSITION_IS_VALID(child->loc.pos, marc.map.width, marc.map.height)) {
                if (marc.map.soils[child->loc.pos.y][child->loc.pos.x] == BASE_STATION) {
                    LIST_CALL(node_stack, clear);
                    return _build_path(child);;
                }
                LIST_CALL(node_stack, add, &child);
            }
        }
    }
    return 0;
}
