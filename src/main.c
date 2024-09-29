#include "screen.h"
#include "snake.h"
#include <raylib.h>
#include <stdio.h>

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");
  Snake_Head *snake = snake_init();
  Apple *apple = apple_init();
  char score[5];
  char level[5];
  char lives[5];
  size_t snake_level = snake->level;
  size_t snake_speed = snake->speed;
  SetTargetFPS(snake_speed);

  while (!WindowShouldClose()) {
    if (snake->level != snake_level) {
      snake_level = snake->level;
      snake_speed = snake->speed;
      SetTargetFPS(snake_speed);
    }
    sprintf(score, "%ld", snake->score);
    sprintf(level, "%ld", snake->level);
    sprintf(lives, "%ld", snake->lives);
    apple_draw(apple);
    snake_get_key(snake);
    snake_move(snake);
    snake_collision(snake, apple);
    BeginDrawing();
    DrawLine(0, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT, WHITE);
    DrawText("Score", 20, 415, 20, WHITE);
    DrawText(score, 90, 415, 20, WHITE);
    DrawText("Lives", 165, 415, 20, WHITE);
    DrawText(lives, 235, 415, 20, WHITE);
    DrawText("Level", 310, 415, 20, WHITE);
    DrawText(level, 380, 415, 20, WHITE);
    ClearBackground(BLACK);
    snake_draw(snake);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
