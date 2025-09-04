#include "cursor.h"

void cursor_render(Cursor *cursor, Sprites *sprites) {
  for (size_t i = 0; i < cursor->cards.count; i++) {
    card_render(&cursor->cards.items[i], sprites,
                (Vector2){.x = (float)GetMouseX() / 3,
                          .y = ((float)GetMouseY() / 3) + i * 10});
  }
}
