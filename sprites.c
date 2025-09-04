#include "raylib.h"

#include "sprites.h"

void sprites_init(Sprites *sprites) {
  sprites->cards = LoadTexture("assets/cards.png");
}
void sprites_free(Sprites sprites) { UnloadTexture(sprites.cards); }
