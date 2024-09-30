#ifndef GAME_H
#define GAME_H

#include <stddef.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 450
#define GAME_WIDTH 400
#define GAME_HEIGHT 400
#define FPS 10

typedef struct Game_Stats {
  size_t score;
  size_t level;
  size_t lives;
} Game_Stats;

/* Prototypes */
void game_init(Game_Stats *game);
void game_start(Game_Stats *game);
void game_over(Game_Stats *game);

#endif
