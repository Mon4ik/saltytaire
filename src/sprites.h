#ifndef SPRITES_H_
#define SPRITES_H_

#include "raylib.h"

typedef struct {
  Texture2D cards;
  Texture2D background;
} Sprites;

void sprites_init(Sprites *sprites);
void sprites_free(Sprites sprites);

#endif // !SPRITES_H_
