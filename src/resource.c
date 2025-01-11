#include "resource.h"
#include "color.h"

const char* resource_to_string(enum resource_t r) {
  char* str[] = {"nothing", "corn", "fish", "wood", "stone", "gold", "ruby", "silver", "sapphire", "emerald"};
  return str[r];
}

const char* resource_to_short_string(enum resource_t r){
  char* str[] = {" ", "C", "F", "W", "S", "G", "R", "I", "P", "E"};
  return str[r];
}

const char* resource_color_start(enum resource_t r) {
  switch (r) {
    case NOTHING:  return color_start(BLACK);
    case CORN:     return color_start(YELLOW);
    case FISH:     return color_start(BLUE);
    case WOOD:     return color_start(GREEN);
    case STONE:    return color_start(BROWN);
    case GOLD:     return color_start(ORANGE);
    case RUBY:     return color_start(RED);
    case SILVER:   return color_start(WHITE);
    case SAPPHIRE: return color_start(VIOLET);
    case EMERALD:  return color_start(GREEN);
    default:       return color_start(BLACK);
  }
}


const char* resource_color_stop() {
    return color_stop();
}

int resource_le_than(unsigned int r1[NUM_RESOURCES], unsigned int r2[NUM_RESOURCES]){

    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (r1[i] > r2[i]) {
            return 0;
        }
    }
    return 1;
} 

void resource_add(unsigned int r1[NUM_RESOURCES], unsigned int r2[NUM_RESOURCES], unsigned int res[NUM_RESOURCES]){

    for (int i = 0; i < NUM_RESOURCES; i++) {
        res[i] = r1[i] + r2[i];
    }
}

void resource_sub(unsigned int r1[NUM_RESOURCES], unsigned int r2[NUM_RESOURCES], unsigned int res[NUM_RESOURCES]){
    for (int i = 0; i < NUM_RESOURCES; i++) {
        res[i] = r1[i] - r2[i];
    }
}