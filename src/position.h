#ifndef __POSITION_H__
#define __POSITION_H__
/** A bound for the abscissas (x) of the positions (i.e x < MAX_X). */
#ifndef MAX_X
  #define MAX_X 4
#endif

/** A bound for the ordinated (y) of the positions (i.e y < MAX_Y). */
#ifndef MAX_Y
  #define MAX_Y 3
#endif

/** The maximal number of valid positions. */
#ifndef MAX_POSITIONS
  #define MAX_POSITIONS ((MAX_X)*(MAX_Y))
#endif
/** The maximal number of neighbors of a position. */
#define MAX_NEIGHBORS 8

/** The maximal size of a string describing a position */
#define MAX_POS_STR 40

/** Abstract struct representing a position. A position is identified
    by its two coordinates in the plane, the abscissa in [0, MAX_X[
    and the ordinate in [0, MAX_Y[ */
struct position_t;

/** Initializes the positions depending on an integer `seed`.
    Can be called multiple times. Can also do nothing. */
void init_positions(unsigned int seed);

/** Creates a position in the board and returns its address.
    May return an invalid position. */
struct position_t* make_position(unsigned int x, unsigned int y);

/** Creates a position that is guaranteed to be invalid */
struct position_t* make_invalid_position();

/** Accessors that return the abscissa and ordinate of the position `p` */
unsigned int position_x(const struct position_t* p);
unsigned int position_y(const struct position_t* p);

/** Macros simplifying the creation and access to values of `p` */
#define POS(x,y) (make_position(x, y))
#define PX(p) (position_x(p))
#define PY(p) (position_y(p))

/** Fills the buffer `buf` with a description of the position `p`.
    `buf` must point to an address with sufficiently allocated
    memory. This function never writes more than MAX_POS_STR-1
    characters to `buf`. */
void position_to_string(const struct position_t* p, char* buf);

/** Returns a boolean telling if the position is valid and therefore
    can be used during the game. By definition, the position returned
    by `make_invalid_position()` is invalid. */
int is_valid_position(const struct position_t* p);

/** Returns an array containing up to MAX_NEIGHBORS positions,
    corresponding to the effective neighbors of `p`. If the array
    contains n < MAX_NEIGHBORS valid positions, then the element at
    position `n` is invalid (with regards to `is_valid_position`) */
void list_neighbors(const struct position_t* p, struct position_t** ns);



#endif // __POSITION_H__
