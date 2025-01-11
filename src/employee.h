#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__
#ifndef MAX_WORKERS_PER_PLAYER
  // #define MAX_WORKERS_PER_PLAYER 6
  #define MAX_WORKERS_PER_PLAYER 4
#endif
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



struct board_t; 

#define MAX_NAME 50
struct employee_t {
    char name[MAX_NAME];
    struct position_t* position;
    unsigned int cost[NUM_RESOURCES];
};
struct employee_placement_t {
   unsigned int employee;
   struct position_t* position;
};
struct employee_t employee_create(const char* name, const unsigned int cost[NUM_RESOURCES]);
void employee_print(const struct employee_t* e);
#endif // __EMPLOYEE_H__