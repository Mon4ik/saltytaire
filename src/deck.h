#ifndef DECK_H_
#define DECK_H_

#include <stddef.h>

#include "card.h"

static const size_t COLUMNS_N = 7;
static const size_t FOUNDATION_N = 4;
static const size_t TOTAL_CARDS_COUNT = 52;

typedef struct {
  Cards columns[COLUMNS_N];
  Cards foundation[FOUNDATION_N];
  Cards stock_pile;
  Cards waste_pile;
} Deck;

void deck_init(Deck *deck);
void deck_free(Deck deck);

Cards *deck_get(Deck *deck, CardLocation loc, size_t loc_index);
void deck_open_last(Deck *deck, CardLocation loc, size_t loc_index);
void deck_move_into(Deck *deck, Cards *source, CardLocation destination_loc,
                    size_t destination_index);

#endif // !DECK_H_
