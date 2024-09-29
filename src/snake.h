#ifndef SNAKE_H
#define SNAKE_H

#include <raylib.h>
#include <stddef.h>

#define SNAKE_SEG_SIZE 10
#define SNAKE_SPEED 10
#define SNAKE_OFFSET (SNAKE_SEG_SIZE - SNAKE_SPEED)

typedef enum Snake_Direction { LEFT, DOWN, UP, RIGHT } Snake_Direction;

typedef struct Snake_Seg {
  Vector2 pos;
  Snake_Direction direction;
} Snake_Seg;

typedef struct Snake_Head {
  Snake_Seg snake_segments[256];
  size_t len;
  Vector2 size;
  size_t speed;
  size_t score;
  size_t level;
  size_t lives;
} Snake_Head;

typedef struct Apple {
  size_t count;
  Vector2 size;
  Vector2 pos;
} Apple;

/* TODO change over stats from snake to game stats struct */
typedef struct Game_Stats {
  size_t score;
  size_t level;
  size_t lives;
} Game_Stats;

Snake_Head *snake_init(void);
void snake_draw(Snake_Head *snake);
void snake_move(Snake_Head *snake);
void snake_get_key(Snake_Head *snake);
void snake_collision(Snake_Head *snake, Apple *apple);
void snake_reset(Snake_Head *snake);
void snake_grow(Snake_Head *snake);
Apple *apple_init(void);
void apple_draw(Apple *apple);
void apple_update(Apple *apple);

#endif
