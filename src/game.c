#include "game.h"
#include "card.h"
#include "deck.h"
#include "raylib.h"
#include "sprites.h"
#include <stddef.h>

void game_init(Game *game) {
  sprites_init(&game->sprites);
  deck_init(&game->deck);
}

void game_draw(Game *game) {
  ClearBackground(DARKGREEN);

  for (size_t foundation_i = 0; foundation_i < FOUNDATION_N; foundation_i++) {
    Cards foundation = game->deck.foundation[foundation_i];

    if (foundation.count > 0) {
      // TODO
    } else {
      card_render(&(Card){.state = CardEmpty}, &game->sprites, (Vector2){ .x = 8, .y = 5 });
    }
  }

  for (size_t column_i = 0; column_i < COLUMNS_N; column_i++) {
    Cards column = game->deck.columns[column_i];
    for (size_t i = 0; i < column.count; i++) {
      card_render(&column.items[i], &game->sprites,
                  (Vector2){.x = (CARD_WIDTH + 4) * column_i + 8,
                            .y = 10 * i + CARD_HEIGHT + 10});
    }
  }
}

void game_free(Game game) {
  deck_free(game.deck);
  sprites_free(game.sprites);
}
