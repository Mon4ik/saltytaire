#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "card.h"
#include "deck.h"

#define NOB_STRIP_PREFIX
#include "nob.h"
#include "raylib.h"

void deck_init(Deck *deck) {
  Cards cards = {.items = malloc(TOTAL_CARDS_COUNT * sizeof(Card)),
                 .capacity = TOTAL_CARDS_COUNT};

  for (int suit = Clubs; suit <= Hearts; suit++) {
    for (int rank = R2; rank <= A; rank++) {
      cards.items[cards.count++] =
          (Card){.state = CardClosed, .suit = suit, .rank = rank};
    }
  }

  // shuffle cards
  for (size_t i = 0; i < cards.count; i++) {
    size_t j = GetRandomValue(0, cards.count - 1);

    Card temp = cards.items[i];
    cards.items[i] = cards.items[j];
    cards.items[j] = temp;

    // card_print(&cards.items[i]);
  }

  for (size_t column = 0; column < COLUMNS_N; column++) {
    Cards column_cards = {.items = malloc((column + 1) * sizeof(Card)),
                          .capacity = column + 1};

    for (size_t card_n = 0; card_n < column + 1; card_n++) {
      column_cards.items[column_cards.count++] = cards.items[--cards.count];
    }
    column_cards.items[column_cards.count - 1].state = CardOpened;

    deck->columns[column] = column_cards;
  }

  da_reserve(&deck->stock_pile, cards.count);
  for (size_t i = 0; i < cards.count; i++) {
    cards.items[i].state = CardOpened;
    deck->stock_pile.items[deck->stock_pile.count++] = cards.items[i];
  }

  da_free(cards);
}

void deck_free(Deck deck) {
  for (size_t i = 0; i < COLUMNS_N; i++)
    free(deck.columns[i].items);

  da_free(deck.stock_pile);
}

Cards *deck_get(Deck *deck, CardLocation loc, size_t loc_index) {
  switch (loc) {
  case CardInColumn:
    return &deck->columns[loc_index];
  case CardInFoundation:
    return &deck->foundation[loc_index];
  case CardInWastePile:
    return &deck->waste_pile;
  }
}

void deck_open_last(Deck *deck, CardLocation loc, size_t loc_index) {
  Cards *dest = deck_get(deck, loc, loc_index);

  if (dest->count > 0)
    dest->items[dest->count - 1].state = CardOpened;
}

void deck_move_into(Deck *deck, Cards *source, CardLocation destination_loc,
                    size_t destination_index) {
  Cards *destination;
  switch (destination_loc) {
  case CardInColumn:
    destination = &deck->columns[destination_index];
    break;
  case CardInFoundation:
    destination = &deck->foundation[destination_index];
    break;
  case CardInWastePile:
    destination = &deck->waste_pile;
    break;
  }

  da_reserve(destination, destination->count + source->count);
  for (size_t i = 0; i < source->count; i++) {
    destination->items[destination->count++] = source->items[i];
  }
  source->count = 0;
}

void deck_take_from_stock(Deck *deck) {
  if (deck->stock_pile.count == 0)
    return; // double check it

  da_append(&deck->waste_pile, deck->stock_pile.items[0]);
  for (size_t i = 1; i < deck->stock_pile.count; i++) {
    deck->stock_pile.items[i - 1] = deck->stock_pile.items[i];
  }
  deck->stock_pile.count--;
}

void deck_restock_pile(Deck *deck) {
  memcpy(deck->stock_pile.items, deck->waste_pile.items,
         sizeof(Card) * deck->waste_pile.count);
  deck->stock_pile.count = deck->waste_pile.count;
  deck->waste_pile.count = 0;
}
