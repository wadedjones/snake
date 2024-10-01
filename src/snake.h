#ifndef SNAKE_H
#define SNAKE_H

#include "apple.h"
#include "game.h"
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

/* Prototypes */
void snake_init(Snake_Head *snake);
void snake_draw(Snake_Head *snake);
void snake_move(Snake_Head *snake);
void get_key_press(Snake_Head *snake);
void snake_collision(Snake_Head *snake, Apple *apple, Game_Stats *game);
void snake_reset(Snake_Head *snake, Game_Stats *game);
void snake_grow(Snake_Head *snake);

#endif
