#include "rules.h"
#include "card.h"
#include "deck.h"
#include "raylib.h"

bool is_allowed_to_drop_into(Deck *deck, Cards *cursor_cards,
                             CardLocation dest_loc, size_t dest_loc_index) {
  if (cursor_cards->count == 0)
    return false; // dude, how?

  Cards *dest = deck_get(deck, dest_loc, dest_loc_index);
  Card cursor_top_card = cursor_cards->items[0];
  Card dest_top_card;

  switch (dest_loc) {

  case CardInColumn:
    if (dest->count == 0) {
      return cursor_top_card.rank == K;
    }

    dest_top_card = dest->items[dest->count - 1];

    if (dest_top_card.rank == R2) {
      return false;
    }

    if (dest_top_card.rank - 1 != cursor_top_card.rank) {
      return false;
    }

    return dest_top_card.suit % 2 != cursor_top_card.suit % 2;
  case CardInFoundation:
    if (dest->count == 0) {
      return cursor_top_card.rank == A;
    }

    dest_top_card = dest->items[dest->count - 1];

    if (dest_top_card.suit != cursor_top_card.suit)
      return false;

    if (dest_top_card.rank == A)
      return cursor_top_card.rank == R2;

    if (dest_top_card.rank == K) // king is max
      return false;

    return dest_top_card.rank + 1 == cursor_top_card.rank;
  case CardInWastePile:
    return false;
  }
}
