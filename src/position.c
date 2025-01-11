#include "position.h"
#include <stdio.h>

#define IND(x,y) (MAX_X*y + x)
struct position_t
{
    unsigned int x;
    unsigned int y;
};
static struct position_t invalid = {-1, -1};
static struct position_t positions[MAX_POSITIONS];
static unsigned int seed_t;

void init_positions(unsigned int seed) { 
    seed_t = seed; // 1= card sur axe x y, 2 = car sur axe diagonales, 3 = torique, 4 = infernal, le reste = normal
    
    for(int i = 0; i < MAX_POSITIONS; i++){ 
        positions[i].x = i % MAX_X;
        positions[i].y = i / MAX_X;
        if (seed == 4 && (i % 2 == 0)){
            positions[i].x = MAX_X;
            positions[i].y = MAX_Y;
        }
    }
}

int is_valid_position(const struct position_t *p)
{
    if (p == NULL) {
        return 0;
    }
    unsigned int x = p->x;
    unsigned int y = p->y;
    int index = IND(x, y);
    return (index < MAX_POSITIONS && positions[index].x == x && positions[index].y == y);
}

struct position_t* make_position(unsigned int x, unsigned int y) {
    int index = IND(x, y);

    if (index < MAX_POSITIONS && positions[index].x == x && positions[index].y == y) {
        return &positions[index];
    } else {
        return &invalid;
    }
}

unsigned int position_x(const struct position_t* p) { return p->x; }
unsigned int position_y(const struct position_t* p) { return p->y; }

void position_to_string(const struct position_t *p, char *buf)
{
    if (p == NULL || !is_valid_position(p)) {
        snprintf(buf, MAX_POS_STR, "(invalid)");
    } else {
        snprintf(buf, MAX_POS_STR, "(%d,%d)", p->x, p->y);
    }
}

struct position_t *make_invalid_position()
{
    return &invalid;
}

void list_neighbors(const struct position_t *p, struct position_t **ns)
{
    unsigned int n = 0;
    if (is_valid_position(p)) {
        unsigned int x = p->x;
        unsigned int y = p->y;
        int directions[8][2];
        switch (seed_t) {
            case 1:
            case 3:
                directions[0][0] = 0; directions[0][1] = 1;
                directions[1][0] = 0; directions[1][1] = 2;
                directions[2][0] = 0; directions[2][1] = -1;
                directions[3][0] = 0; directions[3][1] = -2;
                directions[4][0] = 1; directions[4][1] = 0;
                directions[5][0] = 2; directions[5][1] = 0;
                directions[6][0] = -1; directions[6][1] = 0;
                directions[7][0] = -2; directions[7][1] = 0;
                break;
            case 2:
                directions[0][0] = 1; directions[0][1] = 1;
                directions[1][0] = 1; directions[1][1] = -1;
                directions[2][0] = -1; directions[2][1] = 1;
                directions[3][0] = -1; directions[3][1] = -1;
                directions[4][0] = -2; directions[4][1] = 2;
                directions[5][0] = 2; directions[5][1] = -2;
                directions[6][0] = 2; directions[6][1] = 2;
                directions[7][0] = -2; directions[7][1] = -2;
                break;
            default:
                directions[0][0] = -1; directions[0][1] = 1;
                directions[1][0] = -1; directions[1][1] = 0;
                directions[2][0] = -1; directions[2][1] = 1;
                directions[3][0] = 0; directions[3][1] = 1;
                directions[4][0] = 0; directions[4][1] = -1;
                directions[5][0] = 1; directions[5][1] = -1;
                directions[6][0] = 1; directions[6][1] = 0;
                directions[7][0] = 1; directions[7][1] = 1;
                break;
        }
        for (int i = 0; i < 8; ++i) {
            int nx_s = (int)x + directions[i][0];
            int ny_s = (int)y + directions[i][1];
            if (seed_t == 3) {
                nx_s = (nx_s + (MAX_X-1)) % (MAX_X-1);
                ny_s = (ny_s + (MAX_Y-1)) % (MAX_Y-1);
            }
            if (nx_s >= 0 && ny_s >= 0) {
                unsigned int nx = (unsigned int)nx_s;
                unsigned int ny = (unsigned int)ny_s;
                struct position_t *neighbor = make_position(nx, ny);
                if (is_valid_position(neighbor) && n < MAX_NEIGHBORS) {
                    ns[n++] = neighbor;
                }
            }
        }
    }
    while (n < MAX_NEIGHBORS) {
        ns[n++] = make_invalid_position();
    }
}
