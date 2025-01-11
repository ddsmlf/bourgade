#include "mine.h"

enum mine_type_t get_random_mine_type()
{
    enum mine_type_t mine_types[] = {FIELDS, LAKE, FOREST, QUARRY};
    return mine_types[rand() % 4];
}

struct building_t make_mine(enum mine_type_t mine_type, struct position_t* pos) {
  enum resource_t resource;
  char* name;
  switch (mine_type) {
    case FIELDS:
      name = "Fields";
      resource = CORN;
      break;
    case LAKE:
      name = "Lake";
      resource = FISH;
      break;
    case FOREST:
      name = "Forest";
      resource = WOOD;
      break;
    case QUARRY:
      name = "Quarry";
      resource = STONE;
      break;
  }
  unsigned int value[NUM_RESOURCES] = {0};
  unsigned int earns[NUM_RESOURCES] = {0};
  unsigned int costs[NUM_RESOURCES] = {0};
  unsigned int supplies[NUM_RESOURCES] = {0};
  supplies[resource] = 1;
  return make_building(name, value, earns, costs, supplies, 1, pos, NULL);
}

unsigned int calculate_cost(struct building_t* mines, unsigned int num_mines)
{
  bool visited[num_mines];
  for (unsigned int i = 0; i < num_mines; i++) { visited[i] = false; };
  unsigned int i = 0;
  unsigned int cost = 0;
  while (i < num_mines) {
    if (!visited[i]) {
      struct position_t* connected[num_mines];
      connected[0] = mines[i].position;
      visited[i] = true;
      unsigned int num_connected = 1;
      unsigned int current = 0;
      while (current < num_connected) {
        unsigned int j = 0;
        struct position_t* neighbours[MAX_NEIGHBORS] = {NULL};
        list_neighbors(connected[current], neighbours);
        while (j < MAX_NEIGHBORS && is_valid_position(neighbours[j])) {
          unsigned int k = 0;
          bool found = false;
          while (!found && k < num_mines) {
            found = mines[k].position == neighbours[j];
            if (found && !visited[k]) {
              visited[k] = true;
              connected[num_connected] = mines[k].position;
              num_connected++;
            }
            k++;
          }
          j++;
        }
        current++;
      }
      cost += num_connected; 
    }
    i++;
  }
  return cost;
}

// test si une mine est sur cette position
bool is_mine_here(const struct board_t *gb, struct position_t* pos)
{
  for (int i = 0; i < (int)(gb->num_building); i++)
  {
    if (gb->building[i].position == pos && gb->building[i].is_mine)
    {
      return true;
    }
  }
  return false;
}

void place_mines(struct board_t *gb){
  enum mine_type_t mine_types_min[] = {FIELDS, LAKE, FOREST, QUARRY};
  enum mine_type_t mine_types[MAX_MINE];
  for (int i = 0; i < MAX_MINE; i++)
  {
    if (i < 4)
      mine_types[i] = mine_types_min[i];
    else
      mine_types[i] = get_random_mine_type();
  }

  unsigned int A = MAX_X;
  unsigned int B = MAX_Y;
  unsigned int k = MAX_MINE;
  char axe = 'X';
  if ((MAX_X-1) < (MAX_Y-1))
  {
    A = MAX_Y;
    B = MAX_X;
    axe = 'Y';
  }
  unsigned int k1 = k / B;
  unsigned int reste = k % B;
  unsigned int k2 = k1 + 1;
  unsigned int dec = A / k1;
  unsigned int z = (dec / 2) + 1;
  unsigned int dec2 = (A / k2);
  unsigned int z2 = (dec2 / 2);

  unsigned int a_init = rand() % A;
  unsigned int b_init = rand() % B;

  unsigned int x, y, a, b, nb_lignes_placee;
  unsigned int reste_added = 0;
  for (unsigned int i = 0; i < MAX_MINE; i++)
  {
    nb_lignes_placee = (i - reste_added) / k1;
    b = (nb_lignes_placee + b_init) % B;

    // s'il y du reste a posé sur les dernieres lignes
    if (B - nb_lignes_placee <= reste){
      dec = dec2;
      if ( (i - (k1 * (B - reste))) % k2 == 0){
        
        if (reste_added > 0){
          z = z2;
        }
        reste_added += 1;
      }
    }
    a = (a_init + i * dec + z * b) % A;

    x = (axe == 'X') ? a : b;
    y = (axe == 'X') ? b : a;
    struct position_t *pos = make_position(x, y);
    if (gb->seed == 4)
    {
      int i = 0;
      while (!is_valid_position(pos) || is_mine_here(gb, pos) || !has_valid_neighbors(pos))
      {
        if (i % 2 == 0)
        {
          x = (x + 1) % (MAX_X-1);
        }
        else
        {
          y = (y + 1) % (MAX_Y-1);
        }
        pos = make_position(x, y);
      }
    }
    gb->building[i] = make_mine(mine_types[i], pos);
  }
}
