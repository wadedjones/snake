#include "game.h"
#include <raylib.h>
#include <stdio.h>

char score[5] = {0};
char lives[5] = {0};

void game_init(Game_Stats *game) {
  game->lives = 3;
  game->score = 0;
  game->screen = TITLE;
}

void game_title(Game_Stats *game) {
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
  DrawText("SNAKE", 30, 30, 40, GREEN);
  DrawText("Press Enter to play...", 80, 100, 20, WHITE);
  if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
    game->screen = PLAY;
  }
}

void game_hud(Game_Stats *game) {
  sprintf(score, "%ld", game->score);
  sprintf(lives, "%ld", game->lives);
  DrawLine(0, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT, WHITE);
  DrawText("Score", 20, 415, 20, WHITE);
  DrawText(score, 90, 415, 20, WHITE);
  DrawText("Lives", 310, 415, 20, WHITE);
  DrawText(lives, 380, 415, 20, WHITE);
}

void game_over(Game_Stats *game) {
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
  DrawText("You Died...", 150, 200, 50, RED);
  game->lives = 3;
  game->score = 0;
}

void draw_grid(void) {
  int cell_size = 10;
  for (size_t i = 0; i < GAME_WIDTH; i++) {
    for (size_t j = 0; j < GAME_HEIGHT; j++) {
      DrawRectangleLines(i * cell_size, j * cell_size, cell_size, cell_size,
                         BLACK);
    }
  }
}
