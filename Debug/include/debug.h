#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef DEBUG

#include <stdio.h>

#define DEBUG_PRINTF(format, ...) printf(format, __VA_ARGS__)
#define DEBUG_DPRINTF(fd, format, ...) dprintf(fd, format, __VA_ARGS__)
#define DEBUG_INST(...) {__VA_ARGS__}

#else

#define DEBUG_PRINTF(format, ...) ((void) 0)
#define DEBUG_DPRINTF(format, ...) ((void) 0)
#define DEBUG_INST(...) ((void) 0)

#endif

#endif