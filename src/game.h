
#ifndef GAME_H_
#define GAME_H_

#include "cursor.h"
#include "deck.h"
#include "sprites.h"

typedef struct {
  Sprites sprites;
  Deck deck;
  Cursor cursor;
} Game;

void game_init(Game *game);
void game_free(Game game);

void game_tick(Game *game);
void game_draw(Game *game);

#endif // !GAME_H_
