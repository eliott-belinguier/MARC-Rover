#ifndef _ROVERRUN_MARC_H_
#define _ROVERRUN_MARC_H_

#include "loc.h"
#include "moves.h"

typedef struct marc {
  t_localisation loc;
  unsigned int move_count[U_TURN + 1];
} marc_s;

#endif