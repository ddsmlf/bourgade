#ifndef __RESOURCE_H__
#define __RESOURCE_H__

/** The number of resources in play for a game. Can be between 5 and
    10. The default number of resources is 6 */
#ifndef NUM_RESOURCES
#define NUM_RESOURCES 6
#endif

#if NUM_RESOURCES < 6
#undef NUM_RESOURCES
#define NUM_RESOURCES 6
#endif

#if NUM_RESOURCES > 10
#undef NUM_RESOURCES
#define NUM_RESOURCES 10
#endif

/** Enumeration defining the possible resources in the world */
enum resource_t
{
  NOTHING = 0,
  CORN = 1,
  FISH = 2,
  WOOD = 3,
  STONE = 4,
  GOLD = 5,
  RUBY = 6,
  SILVER = 7,
  SAPPHIRE = 8,
  EMERALD = 9,
  MAX_RESOURCES = 10, // The maximal number of resources possible
};

/** Return a string describing the resource `r` */
const char *resource_to_string(enum resource_t r);

/** Return a short string (using at most one character) describing the
    resource `r`. */
const char *resource_to_short_string(enum resource_t r);

/** Returns a string describing the color of the resource. Can be the
    start of an ANSI code, as in `color_start`. */
const char *resource_color_start(enum resource_t r);

/** Returns the string that shall be printed to reset the color of the
    text, as in `color_stop`. */
const char *resource_color_stop();

/** Returns an integer telling if `r1` is less than `r2` in terms of
    resources meaning that all the elements of `r1` are less than or
    equal to the elements of `r2` of the same index. */
int resource_le_than(unsigned int r1[NUM_RESOURCES],
                    unsigned int r2[NUM_RESOURCES]);

/** Stores into `res` the addition of `r1` + `r2` element by
    element. In this function, `res` can be the same address as `r1`. */
void resource_add(unsigned int r1[NUM_RESOURCES],
                unsigned int r2[NUM_RESOURCES],
                  unsigned int res[NUM_RESOURCES]);

/** Stores into `res` the subtraction of `r1` - `r2` element by
    element. Assumes that `resource_le_than(r2, r1)` is true. In this
    function, `res` can be the same address as `r1`. */
void resource_sub(unsigned int r1[NUM_RESOURCES],
                unsigned int r2[NUM_RESOURCES],
                  unsigned int res[NUM_RESOURCES]);

#endif // __RESOURCE_H__
