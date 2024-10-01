#include "apple.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

void apple_init(Apple *apple) {
  apple->pos = (Vector2){.x = 40, .y = 40};
  apple->size = (Vector2){.x = APPLE_SIZE, .y = APPLE_SIZE};

  /* Might add multiple apples at some point */
  apple->count = 0;
}

void apple_draw(Apple *apple) { DrawRectangleV(apple->pos, apple->size, RED); }

void apple_update(Apple *apple) {
  srand(time(NULL));
  int rand_x = rand() % GAME_WIDTH / 10 * 10;
  int rand_y = rand() % GAME_HEIGHT / 10 * 10;
  apple->pos = (Vector2){.x = rand_x, .y = rand_y};
}
