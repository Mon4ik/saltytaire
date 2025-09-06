#ifndef UI_H_
#define UI_H_

#include "raylib.h"
#include <stddef.h>

Vector2 get_mouse_pos();

Vector2 get_stock_pile_pos();
Vector2 get_waste_pile_pos(size_t card_index);

#endif // !UI_H_
