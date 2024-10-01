#include "snake.h"
#include "game.h"
#include <raylib.h>

void snake_init(Snake_Head *snake) {
  snake->len = 3;
  snake->size = (Vector2){.x = SNAKE_SIZE, .y = SNAKE_SIZE};

  /* Init 3 "segments" of the snake */
  for (size_t i = 0; i < snake->len; i++) {
    size_t y_pos = 10;
    snake->snake_segments[i].pos =
        (Vector2){.x = (float)GAME_WIDTH / 2, .y = (float)y_pos};
    y_pos -= SNAKE_SIZE;
    snake->snake_segments[i].direction = DOWN;
  }
}

void snake_draw(Snake_Head *snake) {
  for (size_t i = 0; i < snake->len; i++) {
    if (i == 0) {
      DrawRectangleV(snake->snake_segments[i].pos, snake->size, LIGHTGRAY);
    } else {
      DrawRectangleV(snake->snake_segments[i].pos, snake->size, GREEN);
    }
  }
}

void snake_move(Snake_Head *snake) {
  /* Each segment becomes segment in front of it */
  for (size_t i = snake->len - 1; i > 0; i--) {
    snake->snake_segments[i] = snake->snake_segments[i - 1];
  }
  /* Move head of snake in direction of snake->direction */
  switch (snake->snake_segments[0].direction) {
  case LEFT:
    snake->snake_segments[0].pos.x -= SNAKE_SPEED;
    break;
  case DOWN:
    snake->snake_segments[0].pos.y += SNAKE_SPEED;
    break;
  case UP:
    snake->snake_segments[0].pos.y -= SNAKE_SPEED;
    break;
  case RIGHT:
    snake->snake_segments[0].pos.x += SNAKE_SPEED;
    break;
  }
}

void get_key_press(Snake_Head *snake) {
  /* Check key pressed and the direction is not opposite of current direction
   * and x/y is within a 10x10 block */
  if (IsKeyDown(KEY_LEFT) && snake->snake_segments[0].direction != RIGHT &&
      ((int)snake->snake_segments[0].pos.y % SNAKE_SIZE == 0)) {
    snake->snake_segments[0].direction = LEFT;
  } else if (IsKeyDown(KEY_DOWN) && snake->snake_segments[0].direction != UP &&
             ((int)snake->snake_segments[0].pos.x % SNAKE_SIZE == 0)) {
    snake->snake_segments[0].direction = DOWN;
  } else if (IsKeyDown(KEY_UP) && snake->snake_segments[0].direction != DOWN &&
             ((int)snake->snake_segments[0].pos.x % SNAKE_SIZE == 0)) {
    snake->snake_segments[0].direction = UP;
  } else if (IsKeyDown(KEY_RIGHT) &&
             snake->snake_segments[0].direction != LEFT &&
             ((int)snake->snake_segments[0].pos.y % SNAKE_SIZE == 0)) {
    snake->snake_segments[0].direction = RIGHT;
  }
}

void snake_grow(Snake_Head *snake) {
  size_t len = snake->len;
  switch (snake->snake_segments[len - 1].direction) {
  case LEFT:
    snake->snake_segments[len].pos =
        (Vector2){.x = snake->snake_segments[len - 1].pos.x + SNAKE_SIZE,
                  .y = snake->snake_segments[len - 1].pos.y};
    break;
  case DOWN:
    snake->snake_segments[len].pos =
        (Vector2){.x = snake->snake_segments[len - 1].pos.x,
                  .y = snake->snake_segments[len - 1].pos.y - SNAKE_SIZE};
    break;
  case UP:
    snake->snake_segments[len].pos =
        (Vector2){.x = snake->snake_segments[len - 1].pos.x,
                  .y = snake->snake_segments[len - 1].pos.y + SNAKE_SIZE};
    break;
  case RIGHT:
    snake->snake_segments[len].pos =
        (Vector2){.x = snake->snake_segments[len - 1].pos.x - SNAKE_SIZE,
                  .y = snake->snake_segments[len - 1].pos.y};
    break;
  }
  snake->len++;
}

void snake_collision(Snake_Head *snake, Apple *apple, Game_Stats *game) {

  /* Check if snake collides with wall */
  if ((snake->snake_segments[0].pos.x < 0) ||
      (snake->snake_segments[0].pos.y < 0) ||
      (snake->snake_segments[0].pos.x >= GAME_WIDTH) ||
      (snake->snake_segments[0].pos.y >= GAME_HEIGHT)) {
    snake_reset(snake, game);
  }

  /* Check if snake collides with itself */
  for (size_t i = 1; i < snake->len; i++) {
    if ((snake->snake_segments[0].pos.x == snake->snake_segments[i].pos.x) &&
        (snake->snake_segments[0].pos.y == snake->snake_segments[i].pos.y)) {
      snake_reset(snake, game);
    }
  }

  /* Check if snake collides with apple */
  if (snake->snake_segments[0].pos.x == apple->pos.x &&
      snake->snake_segments[0].pos.y == apple->pos.y) {
    game->score += 10;
    snake_grow(snake);
    apple_update(apple);
  }
}

void snake_reset(Snake_Head *snake, Game_Stats *game) {
  /* Reset all game stats and snake length */
  if (game->lives < 1) {
    game->screen = GAME_OVER;
    snake->len = 3;
    float y_pos = 50.0f;

    for (size_t i = 0; i < snake->len; i++) {
      snake->snake_segments[i].pos =
          (Vector2){.x = (float)GAME_WIDTH / 2, .y = (float)y_pos};
      y_pos -= SNAKE_SIZE;
      snake->snake_segments[i].direction = DOWN;
    }
  }

  /* Snake respawns at top of screen with same stats */
  game->lives--;
  float y_pos = 50.0f;

  for (size_t i = 0; i < snake->len; i++) {
    snake->snake_segments[i].pos =
        (Vector2){.x = (float)GAME_WIDTH / 2, .y = (float)y_pos};
    y_pos -= SNAKE_SIZE;
    snake->snake_segments[i].direction = DOWN;
  }
}
