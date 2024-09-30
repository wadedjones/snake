#include "game.h"
#include "snake.h"
#include <raylib.h>
// #include <stdio.h>

void draw_grid(void);

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");
  Snake_Head snake;
  snake_init(&snake);
  SetTargetFPS(FPS);

  while (!WindowShouldClose()) {
    // sprintf(score, "%ld", snake->score);
    // sprintf(level, "%ld", snake->level);
    // sprintf(lives, "%ld", snake->lives);
    // apple_draw(apple);
    // snake_collision(snake, apple);
    get_key_press(&snake);
    BeginDrawing();
    ClearBackground(BLACK);
    // DrawLine(0, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT, WHITE);
    // DrawText("Score", 20, 415, 20, WHITE);
    // DrawText(score, 90, 415, 20, WHITE);
    // DrawText("Lives", 165, 415, 20, WHITE);
    // DrawText(lives, 235, 415, 20, WHITE);
    // DrawText("Level", 310, 415, 20, WHITE);
    // DrawText(level, 380, 415, 20, WHITE);
    snake_draw(&snake);
    draw_grid();
    EndDrawing();
    snake_move(&snake);
  }

  CloseWindow();
  return 0;
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
