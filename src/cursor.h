#ifndef CURSOR_H_
#define CURSOR_H_

#include <stddef.h>

#include "card.h"

typedef struct {
  Cards cards;
  Card *dragged_card;
  Vector2 dragging_offset;

  CardLocation location;
  size_t location_index;
} Cursor;

#endif // !CURSOR_H_
