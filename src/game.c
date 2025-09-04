#include <stddef.h>

#include "card.h"
#include "constants.h"
#include "cursor.h"
#include "deck.h"
#include "game.h"
#include "raylib.h"
#include "raymath.h"
#include "sprites.h"

#define NOB_STRIP_PREFIX
#include "nob.h"

// CURSOR

static void tick_cursor(Game *game) {
  if (game->cursor.dragged_card == NULL)
    return;

  if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { // release cards
    Vector2 mouse_pos =
        Vector2Scale(GetMousePosition(), (float)1 / VIRTUAL_RATIO);

    // Drop into columns
    if (mouse_pos.y > CARD_HEIGHT + 10) {
      for (size_t column_n = 0; column_n < COLUMNS_N; column_n++) {
        float column_x = (CARD_WIDTH + 4) * column_n + 8;
        if (column_x < mouse_pos.x && mouse_pos.x < column_x + CARD_WIDTH) {
          game->cursor.dragged_card = NULL;
          
          

          deck_move_into(&game->deck, &game->cursor.cards, CardInColumn,
                         column_n);

          

          return;
        }
      }
    }

    game->cursor.dragged_card = NULL;
    deck_move_into(&game->deck, &game->cursor.cards, game->cursor.location,
                   game->cursor.location_index);
  }

  cursor_render(&game->cursor, &game->sprites);
}

static bool tick_card(Game *game, size_t column_i, size_t i, Vector2 card_pos) {
  Cards *column = &game->deck.columns[column_i];
  if (column->items[i].state == CardOpened &&
      game->cursor.dragged_card == NULL &&
      IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 mouse_pos =
        Vector2Scale(GetMousePosition(), (float)1 / VIRTUAL_RATIO);

    float max_x = card_pos.x + CARD_WIDTH;
    float max_y;
    if (column->count - 1 == i) {       // if it's last card
      max_y = card_pos.y + CARD_HEIGHT; // then check full height
    } else {
      max_y = card_pos.y + 10; // otherwise only top visible part
    }

    if (card_pos.x < mouse_pos.x && mouse_pos.x < max_x &&
        card_pos.y < mouse_pos.y && mouse_pos.y < max_y) {
      game->cursor.dragged_card = &column->items[i];
      game->cursor.location = CardInColumn;
      game->cursor.location_index = column_i;

      da_reserve(&game->cursor.cards, column->count - i);
      for (size_t j = 0; j < column->count - i; j++) {
        game->cursor.cards.items[game->cursor.cards.count++] =
            column->items[i + j];
      }
      column->count = i;

      return true;
    }
  }

  return false;
}

// GAME

void game_init(Game *game) {
  sprites_init(&game->sprites);
  deck_init(&game->deck);
}
void game_free(Game game) {
  deck_free(game.deck);
  sprites_free(game.sprites);
}

void game_tick(Game *game) {}

void game_draw(Game *game) {
  ClearBackground(DARKGREEN);

  for (size_t foundation_i = 0; foundation_i < FOUNDATION_N; foundation_i++) {
    Cards foundation = game->deck.foundation[foundation_i];

    if (foundation.count > 0) {
      // TODO
    } else {
      card_render(&(Card){.state = CardEmpty}, &game->sprites,
                  (Vector2){.x = 8, .y = 5});
    }
  }

  for (size_t column_i = 0; column_i < COLUMNS_N; column_i++) {
    Cards *column = &game->deck.columns[column_i];

    for (size_t i = 0; i < column->count; i++) {
      Card *card = &column->items[i];
      Vector2 card_pos = {.x = (CARD_WIDTH + 4) * column_i + 8,
                          .y = 10 * i + CARD_HEIGHT + 10};

      if (tick_card(game, column_i, i, card_pos))
        break;

      card_render(card, &game->sprites, card_pos);
    }
  }

  tick_cursor(game);
}
