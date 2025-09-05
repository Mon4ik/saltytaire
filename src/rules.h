#ifndef RULES_H_
#define RULES_H_

#include <stddef.h>

#include "card.h"
#include "deck.h"

bool is_allowed_to_drop_into(Deck *deck, Cards *cursor_cards, CardLocation loc,
                             size_t loc_i);

#endif // !RULES_H_
