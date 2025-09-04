#ifndef CARD_H_
#define CARD_H_

#include <stdbool.h>
#include <stddef.h>

#include "sprites.h"

typedef enum { CardClosed, CardOpened, CardEmpty } CardState;
typedef enum { Clubs, Diamonds, Spades, Hearts } CardSuit;
typedef enum { R2, R3, R4, R5, R6, R7, R8, R9, R10, J, G, K, A } CardRank;

typedef enum { CardInColumn, CardInFoundation, CardInWastePile } CardLocation;

typedef struct {
  CardState state;
  CardSuit suit;
  CardRank rank;
} Card;

typedef struct {
  Card *items;
  size_t count;
  size_t capacity;
} Cards;

void card_render(Card *card, Sprites *sprites, Vector2 pos);

#endif // !CARD_H_
