#define ROWS 52
#define COLS 211
#define WALL_PROB 0.48
#define ITERATIONS 10

void init_map(char map[ROWS][COLS]);
void update_map(char map[ROWS][COLS]);
void remove_isolated_walls(char map[ROWS][COLS]);