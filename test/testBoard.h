#ifndef TEST_BOARD_H
#define TEST_BOARD_H

#include <stdbool.h>
#include "board.h"
#include "position.h"

bool test_init_board(char **message);
bool test_is_position_free(char **message);
bool test_list_empty_positions(char **message);
bool test_list_affordable_buildings(char **message);
bool test_collect_resources(char **message);
bool test_collect_resources_test(char **message);
bool test_find_free_employees(char **message);
bool test_get_building_id(char **message);
bool test_pay_employees(char **message);
bool test_count_players(char **message);
bool test_activate_building(char **message);
bool test_eliminate_player(char **message);
bool test_construct_building(char **message);

#endif // TEST_BOARD_H
