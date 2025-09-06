#include "ui.h"
#include "constants.h"
#include "sprites.h"

#include "raylib.h"
#include "raymath.h"
#include <stddef.h>

Vector2 get_mouse_pos() {
  return Vector2Scale(GetMousePosition(), (float)1 / VIRTUAL_RATIO);
}

Vector2 get_stock_pile_pos() {
  return (Vector2){.x = VIRTUAL_SCREEN_WIDTH - CARD_WIDTH - 8 - 1, .y = 5};
}

Vector2 get_waste_pile_pos(size_t card_index) {
  return (Vector2){.x = VIRTUAL_SCREEN_WIDTH - CARD_WIDTH - 8 - 1 -
                        (CARD_WIDTH - 8 - 20) * (3 - card_index + 1) - 23,
                   .y = 5};
}
