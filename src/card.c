#include "card.h"
#include "raylib.h"
#include "sprites.h"
#include <stdio.h>

static Rectangle get_sprite(Card *card) {
  float x, y;
  switch (card->state) {
  case CardClosed:
    x = 1 * CARD_WIDTH;
    y = 4 * CARD_HEIGHT;
    break;
  case CardOpened:
    x = card->rank * CARD_WIDTH;
    y = card->suit * CARD_HEIGHT;
    break;
  case CardEmpty:
    x = 0;
    y = 4 * CARD_HEIGHT;
    break;
  }

  return (Rectangle){x, y, .width = CARD_WIDTH, .height = CARD_HEIGHT};
}

void card_render(Card *card, Sprites *sprites, Vector2 pos) {
  DrawTextureRec(sprites->cards, get_sprite(card), pos, WHITE);
}
