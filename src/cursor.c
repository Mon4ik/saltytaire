#include "cursor.h"
#include <math.h>

void cursor_render(Cursor *cursor, Sprites *sprites) {
  for (size_t i = 0; i < cursor->cards.count; i++) {
    card_render(&cursor->cards.items[i], sprites,
                (Vector2){.x = floorf((float)GetMouseX() / 3 -
                                      cursor->dragging_offset.x),
                          .y = floorf(((float)GetMouseY() / 3) + i * 10 -
                                      cursor->dragging_offset.y)});
  }
}
