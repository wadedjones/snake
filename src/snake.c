#include "snake.h"
#include "screen.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Snake_Head *snake_init(void) {
  Snake_Head *snake = malloc(sizeof(Snake_Head));
  snake->len = 5;
  snake->speed = SNAKE_SPEED;
  snake->size = (Vector2){.x = SNAKE_SEG_SIZE, .y = SNAKE_SEG_SIZE};
  snake->score = 0;
  snake->level = 1;
  snake->lives = 3;
  float y_pos = 50.0f;

  /* Init 5 "segments" of the snake */
  for (size_t i = 0; i < snake->len; i++) {
    snake->snake_segments[i].pos =
        (Vector2){.x = (float)GAME_WIDTH / 2, .y = (float)y_pos};
    y_pos -= SNAKE_SEG_SIZE;
    snake->snake_segments[i].direction = DOWN;
  }

  return snake;
}

void snake_draw(Snake_Head *snake) {
  for (size_t i = 0; i < snake->len; i++) {
    DrawRectangleV(snake->snake_segments[i].pos, snake->size, WHITE);
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

void snake_get_key(Snake_Head *snake) {
  /* Check key pressed and the direction is not opposite of current direction
   * and x/y is within a 10x10 block */
  if (IsKeyPressed(KEY_LEFT) && snake->snake_segments[0].direction != RIGHT &&
      ((int)snake->snake_segments[0].pos.y % SNAKE_SEG_SIZE == 0)) {
    snake->snake_segments[0].direction = LEFT;
  } else if (IsKeyPressed(KEY_DOWN) &&
             snake->snake_segments[0].direction != UP &&
             ((int)snake->snake_segments[0].pos.x % SNAKE_SEG_SIZE == 0)) {
    snake->snake_segments[0].direction = DOWN;
  } else if (IsKeyPressed(KEY_UP) &&
             snake->snake_segments[0].direction != DOWN &&
             ((int)snake->snake_segments[0].pos.x % SNAKE_SEG_SIZE == 0)) {
    snake->snake_segments[0].direction = UP;
  } else if (IsKeyPressed(KEY_RIGHT) &&
             snake->snake_segments[0].direction != LEFT &&
             ((int)snake->snake_segments[0].pos.y % SNAKE_SEG_SIZE == 0)) {
    snake->snake_segments[0].direction = RIGHT;
  }
}

void snake_grow(Snake_Head *snake) {
  size_t len = snake->len;
  switch (snake->snake_segments[len - 1].direction) {
  case LEFT:
    snake->snake_segments[len].pos =
        (Vector2){.x = snake->snake_segments[len - 1].pos.x + SNAKE_SEG_SIZE,
                  .y = snake->snake_segments[len - 1].pos.y};
    break;
  case DOWN:
    snake->snake_segments[len].pos =
        (Vector2){.x = snake->snake_segments[len - 1].pos.x,
                  .y = snake->snake_segments[len - 1].pos.y - SNAKE_SEG_SIZE};
    break;
  case UP:
    snake->snake_segments[len].pos =
        (Vector2){.x = snake->snake_segments[len - 1].pos.x,
                  .y = snake->snake_segments[len - 1].pos.y + SNAKE_SEG_SIZE};
    break;
  case RIGHT:
    snake->snake_segments[len].pos =
        (Vector2){.x = snake->snake_segments[len - 1].pos.x - SNAKE_SEG_SIZE,
                  .y = snake->snake_segments[len - 1].pos.y};
    break;
  }
  snake->len++;
}

void snake_collision(Snake_Head *snake, Apple *apple) {

  /* Check if snake collides with wall */
  if ((snake->snake_segments[0].pos.x < 0) ||
      (snake->snake_segments[0].pos.y < 0) ||
      (snake->snake_segments[0].pos.x >= GAME_WIDTH) ||
      (snake->snake_segments[0].pos.y >= GAME_HEIGHT)) {
    snake_reset(snake);
  }

  /* Check if snake collides with itself */
  for (size_t i = 1; i < snake->len; i++) {
    if ((snake->snake_segments[0].pos.x == snake->snake_segments[i].pos.x) &&
        (snake->snake_segments[0].pos.y == snake->snake_segments[i].pos.y)) {
      snake_reset(snake);
    }
  }

  /* Check if snake collides with apple */
  if (snake->snake_segments[0].pos.x == apple->pos.x &&
      snake->snake_segments[0].pos.y == apple->pos.y) {
    snake->score += snake->speed;
    if (snake->score > (snake->speed * snake->speed / 2)) {
      snake->level++;
      snake->lives++;
      snake->speed += 5;
    }
    snake_grow(snake);
    apple_update(apple);
  }
}

void snake_reset(Snake_Head *snake) {
  if (snake->lives == 0) {
    free(snake);
    snake = snake_init();
    return;
  }
  // snake->len = 5;
  snake->lives--;
  float y_pos = 50.0f;

  for (size_t i = 0; i < snake->len; i++) {
    snake->snake_segments[i].pos =
        (Vector2){.x = (float)GAME_WIDTH / 2, .y = (float)y_pos};
    y_pos -= SNAKE_SEG_SIZE;
    snake->snake_segments[i].direction = DOWN;
  }
}

Apple *apple_init(void) {
  Apple *apple = malloc(sizeof(Apple));
  apple->pos = (Vector2){.x = 40, .y = 40};
  apple->size = (Vector2){.x = SNAKE_SEG_SIZE, .y = SNAKE_SEG_SIZE};

  /* Might add multiple apples at some point */
  apple->count = 0;
  return apple;
}

void apple_draw(Apple *apple) { DrawRectangleV(apple->pos, apple->size, RED); }

void apple_update(Apple *apple) {
  srand(time(NULL));
  int rand_x = rand() % GAME_WIDTH / 10 * 10;
  int rand_y = rand() % GAME_HEIGHT / 10 * 10;
  apple->pos = (Vector2){.x = rand_x, .y = rand_y};
  printf("x: %f, y %f\n", apple->pos.x, apple->pos.y);
}
