#ifndef __TEST_MINE_H
#define __TEST_MINE_H

#include <stdbool.h>
#include "mine.h"
#include "board.h"
#include "position.h"
#include <stdio.h>
#include <string.h>

bool test_make_mine(char **message);

bool test_get_random_mine_type(char **message);

bool test_place_mines(char **message);

bool test_is_mine_here(char **message);

#endif // __TEST_MINE_H
