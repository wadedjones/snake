#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stddef.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 450
#define GAME_WIDTH 400
#define GAME_HEIGHT 400
#define FPS 10

typedef enum Current_Screen {
  TITLE,
  PLAY,
  GAME_OVER,
} Current_Screen;

typedef struct Game_Stats {
  size_t score;
  size_t lives;
  Current_Screen screen;
} Game_Stats;

/* Prototypes */
void game_init(Game_Stats *game);
void game_title(Game_Stats *game);
void game_hud(Game_Stats *game);
void game_over(Game_Stats *game);
void draw_grid(void);

#endif
