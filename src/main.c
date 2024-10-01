#include "apple.h"
#include "game.h"
#include "snake.h"
#include <raylib.h>
#include <stdio.h>

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");

  /* Initialize all game elements */
  Snake_Head snake;
  Game_Stats game;
  Apple apple;
  snake_init(&snake);
  game_init(&game);
  apple_init(&apple);

  SetTargetFPS(FPS);

  /* Initialize Score value */
  char score[5] = {0};
  sprintf(score, "%ld", game.score);
  char lives[5] = {0};
  sprintf(lives, "%ld", game.lives);

  while (!WindowShouldClose()) {
    switch (game.screen) {
    case TITLE:
      if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
        game.screen = PLAY;
      }
      break;
    case PLAY:
      break;
    case GAME_OVER:
      if (IsKeyPressed(KEY_ENTER)) {
        game.screen = TITLE;
      }
      break;
    default:
      break;
    }
    BeginDrawing();
    ClearBackground(BLACK);
    switch (game.screen) {
    case TITLE: {
      game_title(&game);
    } break;
    case PLAY: {
      apple_draw(&apple);
      snake_draw(&snake);
      draw_grid();
      get_key_press(&snake);
      snake_move(&snake);
      snake_collision(&snake, &apple, &game);
      game_hud(&game);
    } break;
    case GAME_OVER:
      game_over(&game);
      break;
    default:
      break;
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
