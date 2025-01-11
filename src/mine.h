#ifndef __MINE_H
#define __MINE_H
#include "board.h"
#include <stdio.h>



/**
 * @enum mine_type_t
 * @brief Enumeration of different types of mines.
 */
enum mine_type_t {
    FIELDS,
    LAKE,
    FOREST,
    QUARRY
};

/**
 * @struct building_t make_mine
 * @brief Creates a mine of the specified type at the given position.
 * 
 * @param mine_type The type of the mine to be created.
 * @param pos The position where the mine will be placed.
 * @return A building_t structure representing the created mine.
 */
struct building_t make_mine(enum mine_type_t mine_type, struct position_t* pos);

/**
 * @enum mine_type_t get_random_mine_type
 * @brief Generates a random type of mine.
 * 
 * @return A randomly selected mine_type_t value.
 */
enum mine_type_t get_random_mine_type();

/**
 * @struct position_t *get_random_position
 * @brief Generates a random position on the board.
 * 
 * @return A pointer to a randomly generated position_t structure.
 */
struct position_t *get_random_position();

/**
 * @void place_mines
 * @brief Places mines on the game board in an initial random distribution.
 * 
 * @param gb Pointer to the game board structure where mines will be placed.
 * 
 * This function places mines on the game board in a random manner.
 */
void place_mines(struct board_t *gb);

/**
 * @unsigned int cost_calcul
 * @brief Calculates the cost of the initial placement of mines on the game board.
 * 
 * @param gb Pointer to the game board structure containing the mines.
 * @return The cost of the current mine placement.
 * 
 * This function evaluates the initial distribution of resource mines on the game board by calculating the cost. The cost is determined by identifying connected components of mines, where two mines are in the same component if they are connected by a path of neighboring mines. The cost is the sum of the squares of the sizes of these components.
 */
unsigned int cost_calcul(struct board_t *gb);

/**
 * @bool is_mine_here
 * @brief Checks if there is a mine at the given position on the game board.
 * 
 * @param gb Pointer to the game board structure.
 * @param pos Pointer to the position to be checked.
 * @return true if there is a mine at the given position, false otherwise.
 */
bool is_mine_here(const struct board_t *gb, struct position_t* pos);

#endif