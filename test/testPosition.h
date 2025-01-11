#ifndef TEST_POSITION_H
#define TEST_POSITION_H

#include <stdio.h>
#include <stdbool.h>
#include "position.h"

bool test_make_position(char** message);
bool test_is_valid_position(char** message);
bool test_list_neighbors(char** message);

#endif // TEST_POSITION_H