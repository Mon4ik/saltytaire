#ifndef SPRITES_H_
#define SPRITES_H_

#include "raylib.h"

static const int CARD_WIDTH = 37;
static const int CARD_HEIGHT = 52;

typedef struct {
  Texture2D cards;
} Sprites;

void sprites_init(Sprites *sprites);
void sprites_free(Sprites sprites);

#endif // !SPRITES_H_
