#include "raylib.h"

#include "constants.h"
#include "game.h"

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "saltytare");

  Game game = {0};
  game_init(&game);

  RenderTexture2D target =
      LoadRenderTexture(VIRTUAL_SCREEN_WIDTH, VIRTUAL_SCREEN_HEIGHT);
  Camera2D screenSpaceCamera = {0}; // Smoothing camera
  screenSpaceCamera.zoom = 1.0f;

  Rectangle sourceRec = {0.0f, 0.0f, (float)target.texture.width,
                         -(float)target.texture.height};
  Rectangle destRec = {-VIRTUAL_RATIO, -VIRTUAL_RATIO,
                       SCREEN_WIDTH + (VIRTUAL_RATIO * 2),
                       SCREEN_HEIGHT + (VIRTUAL_RATIO * 2)};
  Vector2 origin = {0.0f, 0.0f};

  while (!WindowShouldClose()) {
    game_tick(&game);
    BeginTextureMode(target);
    game_draw(&game);
    EndTextureMode();

    BeginDrawing();
    BeginMode2D(screenSpaceCamera);
    DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
    EndMode2D();
    EndDrawing();
  }

  UnloadRenderTexture(target);

  game_free(game);

  return 0;
}
