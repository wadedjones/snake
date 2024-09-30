#ifndef SNAKE_H
#define SNAKE_H

#include <raylib.h>
#include <stddef.h>

#define SNAKE_SIZE 10
#define SNAKE_SPEED 10

typedef enum Snake_Direction { LEFT, DOWN, UP, RIGHT } Snake_Direction;

typedef struct Snake_Seg {
  Vector2 pos;
  Snake_Direction direction;
} Snake_Seg;

typedef struct Snake_Head {
  Snake_Seg snake_segments[256];
  size_t len;
  Vector2 size;
} Snake_Head;

typedef struct Apple {
  size_t count;
  Vector2 size;
  Vector2 pos;
} Apple;

/* Prototypes */

void snake_init(Snake_Head *snake);
void snake_draw(Snake_Head *snake);
void snake_move(Snake_Head *snake);
void get_key_press(Snake_Head *snake);
void snake_collision(Snake_Head *snake, Apple *apple);
void snake_reset(Snake_Head *snake);
void snake_grow(Snake_Head *snake);
Apple *apple_init(void);
void apple_draw(Apple *apple);
void apple_update(Apple *apple);

#endif
