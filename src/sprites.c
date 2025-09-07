#include "raylib.h"

#include "sprites.h"

void sprites_init(Sprites *sprites) {
  sprites->cards = LoadTexture("assets/cards.png");
  sprites->background = LoadTexture("assets/background.png");
}

void sprites_free(Sprites sprites) {
  UnloadTexture(sprites.cards);
  UnloadTexture(sprites.background);
}
