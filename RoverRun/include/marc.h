#ifndef _ROVERRUN_MARC_H_
#define _ROVERRUN_MARC_H_

#include "tree.h"

typedef struct marc {
    tree_s all_states;
    tree_node_s *current_state;
} marc_s;

#endif