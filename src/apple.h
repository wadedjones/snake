#ifndef APPLE_H
#define APPLE_H

#include <raylib.h>
#include <stddef.h>

#define APPLE_SIZE 10

typedef struct Apple {
  size_t count;
  Vector2 size;
  Vector2 pos;
} Apple;

void apple_init(Apple *apple);
void apple_draw(Apple *apple);
void apple_update(Apple *apple);

#endif
