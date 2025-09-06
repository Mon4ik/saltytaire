#include <stdbool.h>
#include <stddef.h>

#define NOB_STRIP_PREFIX
#include "nob.h"

#include "card.h"
#include "cursor.h"
#include "deck.h"
#include "game.h"
#include "raylib.h"
#include "raymath.h"
#include "rules.h"
#include "sprites.h"
#include "ui.h"

void game_init(Game *game) {
  sprites_init(&game->sprites);
  deck_init(&game->deck);
}
void game_free(Game game) {
  deck_free(game.deck);
  sprites_free(game.sprites);
}

static void draw_foundation(Game *game) {
  for (size_t foundation_i = 0; foundation_i < FOUNDATION_N; foundation_i++) {
    Cards foundation = game->deck.foundation[foundation_i];

    card_render(foundation.count > 0 ? &foundation.items[foundation.count - 1]
                                     : &(Card){.state = CardEmpty},
                &game->sprites, get_foundation_pos(foundation_i));
  }
}

static void tick_stock_pile(Game *game) {
  if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    return;

  Vector2 stock_pile_pos = get_stock_pile_pos();
  Vector2 mouse_pos = get_mouse_pos();

  if (stock_pile_pos.x < mouse_pos.x &&
      mouse_pos.x < stock_pile_pos.x + CARD_WIDTH &&
      stock_pile_pos.y < mouse_pos.y &&
      mouse_pos.y < stock_pile_pos.y + CARD_HEIGHT) {

    if (game->deck.stock_pile.count > 0) {
      deck_take_from_stock(&game->deck);
    } else {
      deck_restock_pile(&game->deck);
    }
  }
}

static void draw_stock_pile(Game *game) {
  Vector2 stock_pile_pos = get_stock_pile_pos();

  if (game->deck.stock_pile.count > 0) {
    card_render(&(Card){.state = CardClosed}, &game->sprites, stock_pile_pos);
  } else {
    card_render(&(Card){.state = CardRepeat}, &game->sprites, stock_pile_pos);
  }
}

static void tick_waste_pile(Game *game) {
  if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
      game->cursor.dragged_card != NULL)
    return;

  Cards *waste_pile = &game->deck.waste_pile;
  if (waste_pile->count == 0)
    return;

  size_t last_card_index = waste_pile->count > 3 ? 2 : waste_pile->count - 1;
  Vector2 waste_pile_pos = get_waste_pile_pos(last_card_index);
  Vector2 mouse_pos = get_mouse_pos();

  if (waste_pile_pos.x < mouse_pos.x &&
      mouse_pos.x < waste_pile_pos.x + CARD_WIDTH &&
      waste_pile_pos.y < mouse_pos.y &&
      mouse_pos.y < waste_pile_pos.y + CARD_HEIGHT) {

    game->cursor.dragged_card = &waste_pile->items[waste_pile->count - 1];
    game->cursor.dragging_offset = Vector2Subtract(mouse_pos, waste_pile_pos);
    game->cursor.location = CardInWastePile;
    game->cursor.location_index = waste_pile->count - 1;

    da_reserve(&game->cursor.cards, 1);
    game->cursor.cards.items[game->cursor.cards.count++] =
        waste_pile->items[--waste_pile->count];
  }
}

static void draw_waste_pile(Game *game) {
  Cards waste_pile = game->deck.waste_pile;
  Card last_cards[3];
  size_t last_cards_len = 0;

  size_t i = 0;
  if (waste_pile.count >= 3) {
    i = waste_pile.count - 3;
  }
  for (; i < waste_pile.count; i++) {
    size_t last_cards_i = last_cards_len++;
    last_cards[last_cards_i] = waste_pile.items[i];
  }

  for (size_t i = 0; i < last_cards_len; i++) {
    card_render(&last_cards[i], &game->sprites, get_waste_pile_pos(i));
  }
}

static void tick_columns(Game *game) {
  if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
      game->cursor.dragged_card != NULL)
    return;

  Vector2 mouse_pos = get_mouse_pos();

  for (size_t column_index = 0; column_index < COLUMNS_N; column_index++) {
    Cards *column = &game->deck.columns[column_index];

    for (size_t i = 0; i < column->count; i++) {
      if (column->items[i].state != CardOpened)
        continue;

      Vector2 card_pos = get_column_pos(column_index, i);

      float max_x = card_pos.x + CARD_WIDTH;
      float max_y;
      if (column->count - 1 == i) {       // if it's last card
        max_y = card_pos.y + CARD_HEIGHT; // then check full height
      } else {
        max_y = card_pos.y +
                VERTICAL_NASTING_PADDING; // otherwise only top visible part
      }

      if (card_pos.x < mouse_pos.x && mouse_pos.x < max_x &&
          card_pos.y < mouse_pos.y && mouse_pos.y < max_y) {
        game->cursor.dragged_card = &column->items[i];
        game->cursor.dragging_offset = Vector2Subtract(mouse_pos, card_pos);
        game->cursor.location = CardInColumn;
        game->cursor.location_index = column_index;

        da_reserve(&game->cursor.cards, column->count - i);
        for (size_t j = 0; j < column->count - i; j++) {
          game->cursor.cards.items[game->cursor.cards.count++] =
              column->items[i + j];
        }
        column->count = i;

        return;
      }
    }
  }
}

static void draw_columns(Game *game) {
  for (size_t column_index = 0; column_index < COLUMNS_N; column_index++) {
    Cards column = game->deck.columns[column_index];

    for (size_t i = 0; i < column.count; i++) {
      card_render(&column.items[i], &game->sprites,
                  get_column_pos(column_index, i));
    }
  }
}

static bool handle_dropping_into_columns(Game *game, Vector2 mouse_pos) {
  for (size_t column_n = 0; column_n < COLUMNS_N; column_n++) {
    float column_x = (CARD_WIDTH + 4) * column_n + 8;
    if (column_x < mouse_pos.x && mouse_pos.x < column_x + CARD_WIDTH) {
      if (is_allowed_to_drop_into(&game->deck, &game->cursor.cards,
                                  CardInColumn, column_n)) {
        game->cursor.dragged_card = NULL;

        deck_open_last(&game->deck, game->cursor.location,
                       game->cursor.location_index);
        deck_move_into(&game->deck, &game->cursor.cards, CardInColumn,
                       column_n);

        return true;
      } else {
        return false;
      }
    }
  }

  return false;
}

static bool handle_dropping_into_foundation(Game *game, Vector2 mouse_pos) {
  if (game->cursor.cards.count != 1)
    return false;

  for (size_t foundation_i = 0; foundation_i < FOUNDATION_N; foundation_i++) {
    Vector2 foundation_pos = get_foundation_pos(foundation_i);
    Vector2 mouse_pos = get_mouse_pos();

    if (foundation_pos.x < mouse_pos.x &&
        mouse_pos.x < foundation_pos.x + CARD_WIDTH &&
        foundation_pos.y < mouse_pos.y &&
        mouse_pos.y < foundation_pos.y + CARD_HEIGHT &&
        is_allowed_to_drop_into(&game->deck, &game->cursor.cards,
                                CardInFoundation, foundation_i)) {

      game->cursor.dragged_card = NULL;
      deck_open_last(&game->deck, game->cursor.location,
                     game->cursor.location_index);

      Cards *foundation = deck_get(&game->deck, CardInFoundation, foundation_i);
      da_append(foundation, game->cursor.cards.items[0]);
      game->cursor.cards.count = 0;

      return true;
    }
  }
  return false;
}

static void tick_cursor(Game *game) {
  if (game->cursor.dragged_card == NULL)
    return;

  if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) { // release cards
    Vector2 mouse_pos =
        Vector2Scale(GetMousePosition(), (float)1 / VIRTUAL_RATIO);

    if (mouse_pos.y > CARD_HEIGHT + VERTICAL_NASTING_PADDING) {
      if (handle_dropping_into_columns(game, mouse_pos))
        return;
    } else {
      if (handle_dropping_into_foundation(game, mouse_pos))
        return;
    }

    // Return back
    game->cursor.dragged_card = NULL;
    deck_move_into(&game->deck, &game->cursor.cards, game->cursor.location,
                   game->cursor.location_index);
  }
}

static void draw_cursor(Game *game) {
  Vector2 mouse_pos = get_mouse_pos();

  for (size_t i = 0; i < game->cursor.cards.count; i++) {
    card_render(
        &game->cursor.cards.items[i], &game->sprites,
        (Vector2){.x = floorf(mouse_pos.x - game->cursor.dragging_offset.x),
                  .y = floorf(mouse_pos.y + i * VERTICAL_NASTING_PADDING -
                              game->cursor.dragging_offset.y)});
  }
}

void game_tick(Game *game) {
  tick_stock_pile(game);
  tick_waste_pile(game);

  tick_columns(game);

  tick_cursor(game);
}

void game_draw(Game *game) {
  ClearBackground(DARKGREEN);

  draw_foundation(game);

  draw_stock_pile(game);
  draw_waste_pile(game);

  draw_columns(game);

  draw_cursor(game);
}
