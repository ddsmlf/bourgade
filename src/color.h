#ifndef __COLOR_H__
#define __COLOR_H__

/** Boolean telling if the console should print colored strings. */
#ifndef COLOR_PRINTING_ENABLED
  #define COLOR_PRINTING_ENABLED 0
#endif

/** Enumeration defining the possible colors in the game */
enum color_t {
  BLACK      = 0,
  WHITE      = 1,
  ORANGE     = 2,
  PINK       = 3,
  VIOLET     = 4,
  YELLOW     = 5,
  BLUE       = 6,
  BROWN      = 7,
  GREEN      = 8,
  RED        = 9,
  SHINY      = 10,
  MAX_COLORS = 11,
};

/** Returns the string that shall be printed to switch the color of
    the text to `c`. Every character printed *after* that string will
    have color `c`. More details can be found in
    https://en.wikipedia.org/wiki/ANSI_escape_code

    Example:
    printf("%s azur %s normal ", color_start(BLUE), color_stop());
    prints " azur " in blue, then " normal " in the usual style. */
const char* color_start(enum color_t c);

/** Returns the string that shall be printed to reset the color of the
    text. Every character printed *after* that string will have the
    standard text color (cf. example above). */
const char* color_stop();

/** Returns a string that describes the color `c`. */
const char* color_to_string(enum color_t c);

#endif // __COLOR_H__
