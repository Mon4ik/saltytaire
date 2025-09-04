#include <stddef.h>
#include <stdlib.h>

#include "card.h"
#include "deck.h"
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
}

void deck_free(Deck deck) {
  for (size_t i = 0; i < COLUMNS_N; i++)
    free(deck.columns[i].items);
}
