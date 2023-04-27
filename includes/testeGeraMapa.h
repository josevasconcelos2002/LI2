#define ROWS 52
#define COL 211
#define WALL_PROB 0.48
#define ITERATIONS 10

void init_map(char map[ROWS][COL]);
void update_map(char map[ROWS][COL]);
void remove_isolated_walls(char map[ROWS][COL]);