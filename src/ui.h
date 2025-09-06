#ifndef UI_H_
#define UI_H_

#include <stddef.h>

#include "raylib.h"

// Constants

static const int SCREEN_WIDTH = 900;
static const int SCREEN_HEIGHT = 600;

static const int VIRTUAL_SCREEN_WIDTH = 300;
static const int VIRTUAL_SCREEN_HEIGHT = 200;

static const float VIRTUAL_RATIO =
    (float)SCREEN_WIDTH / (float)VIRTUAL_SCREEN_WIDTH;

static const int CARD_WIDTH = 37;
static const int CARD_HEIGHT = 52;

static const int VERTICAL_NASTING_PADDING = 10;
static const int HORIZONTAL_NASTING_PADDING = 8;

static const int HORIZONTAL_GAP = 4;

static const int SCREEN_HORIZONTAL_PADDING = 8;
static const int SCREEN_VERTICAL_PADDING = 5;

// Positions calculations

Vector2 get_mouse_pos();

Vector2 get_stock_pile_pos();
Vector2 get_waste_pile_pos(size_t card_index);

Vector2 get_foundation_pos(size_t foundation_index);

Vector2 get_column_pos(size_t column_index, size_t index);

#endif // !UI_H_
