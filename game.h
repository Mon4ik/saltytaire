#ifndef GAME_H_
#define GAME_H_

#include "deck.h"
#include "sprites.h"

typedef struct {
  Sprites sprites;
  Deck deck;
} Game;

void game_init(Game *game);
void game_draw(Game *game);
void game_free(Game game);

#endif // !GAME_H_
