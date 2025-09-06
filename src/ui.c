#include "ui.h"

#include "raylib.h"
#include "raymath.h"
#include <stddef.h>

Vector2 get_mouse_pos() {
  return Vector2Scale(GetMousePosition(), (float)1 / VIRTUAL_RATIO);
}

Vector2 get_stock_pile_pos() {
  return (Vector2){.x = VIRTUAL_SCREEN_WIDTH - CARD_WIDTH -
                        HORIZONTAL_NASTING_PADDING - 1,
                   .y = SCREEN_VERTICAL_PADDING};
}

Vector2 get_waste_pile_pos(size_t card_index) {
  return (Vector2){.x = VIRTUAL_SCREEN_WIDTH - CARD_WIDTH -
                        HORIZONTAL_NASTING_PADDING - 1 -
                        (CARD_WIDTH - HORIZONTAL_NASTING_PADDING - 20) *
                            (3 - card_index + 1) -
                        23,
                   // i dont even know, whats happening at top
                   .y = SCREEN_VERTICAL_PADDING};
}

Vector2 get_foundation_pos(size_t foundation_index) {
  return (Vector2){.x = (CARD_WIDTH + HORIZONTAL_GAP) * foundation_index +
                        SCREEN_HORIZONTAL_PADDING,
                   .y = SCREEN_VERTICAL_PADDING};
}

Vector2 get_column_pos(size_t column_index, size_t index) {
  return (Vector2){.x = (CARD_WIDTH + HORIZONTAL_GAP) * column_index +
                        SCREEN_HORIZONTAL_PADDING,
                   .y = VERTICAL_NASTING_PADDING * index + CARD_HEIGHT +
                        SCREEN_VERTICAL_PADDING * 2};
}
