#ifndef _ROVERRUN_MARC_H_
#define _ROVERRUN_MARC_H_

#include "map.h"
#include "tree.h"

typedef struct marc {
    map_s map;
    tree_s all_states;
} marc_s;

#endif