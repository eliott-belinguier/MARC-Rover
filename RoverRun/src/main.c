#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "map.h"
#include "marc.h"

#define USAGE_MESSAGE                                       \
    "Error: Invalid arguments.\n"                           \
    "Usage: %s <map> <start_x> <start_y>\n"                 \
    "  <map>       : Path to the map file.\n"               \
    "  <start_x>   : Starting x-coordinate (integer).\n"    \
    "  <start_y>   : Starting y-coordinate (integer).\n"    \

// Définitions pour les couleurs ANSI
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

static int _str_to_unsigned_int(const char *str, unsigned long *number_out)
{
    char *ptr_end = 0;
    unsigned long value;

    errno = 0;
    if (!number_out)
        return -1;
    value = strtoul(str, &ptr_end, 10);
    if (errno == ERANGE || value > 0xFFFFFFFF) {
        errno == ERANGE;
        return -1;
    }
    if (*ptr_end)
        return -1;
    *number_out = value;
    return 0;
}

static int _coord_parse(const char *str, const char *coord_name, unsigned int coord_max, unsigned int *coord_out)
{
    unsigned long value;

    if (!coord_out)
        return EINVAL;

    if (_str_to_unsigned_int(str, &value) == -1) {
        fprintf(stderr, RED "Error: The " YELLOW "%s" RED " coordinate is invalid: " RESET, coord_name);
        if (errno == ERANGE)
            fprintf(stderr, RED "value out of range (" YELLOW "0" RED " to " YELLOW "%u" RED ")." RESET "\n", coord_max);
        else
            fprintf(stderr, RED "the string " YELLOW "\"%s\"" RED " is not a valid number." RESET "\n", str);
        return EINVAL;
    }

    if (value >= coord_max) {
        fprintf(stderr, RED "Error: The " YELLOW "%s" RED " coordinate is invalid: "RED "value out of range (" YELLOW "0" RED " to " YELLOW "%u" RED ")." RESET "\n", coord_name, coord_max);
        return EINVAL;
    }

    *coord_out = (unsigned int)value;
    return 0;
}


int main(int argc, char **argv)
{
    marc_s marc = {0};
    t_map map;
    int exit_result;

    DEBUG_PRINTF("%s\n", "Debug mode enabled.");
    if (argc < 4) {
        fprintf(stderr, USAGE_MESSAGE, argv[0]);
        return EINVAL;
    }
    map = createMapFromFile(argv[1]);
    exit_result = _coord_parse(argv[2], "x", map.x_max, (unsigned int *) &marc.loc.pos.x);
    if (exit_result)
        return exit_result;
    exit_result = _coord_parse(argv[3], "y", map.x_max, (unsigned int *) &marc.loc.pos.y);
    if (exit_result)
        return exit_result;
    return 0;
}