#include "game.h"
#include "raylib.h"

const int screenWidth = 900;
const int screenHeight = 600;

const int virtualScreenWidth = 300;
const int virtualScreenHeight = 200;

const float virtualRatio = (float)screenWidth / (float)virtualScreenWidth;

int main(void) {
  InitWindow(screenWidth, screenHeight, "saltytare");

  Game game = {0};
  game_init(&game);

  RenderTexture2D target =
      LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);
  Camera2D screenSpaceCamera = {0}; // Smoothing camera
  screenSpaceCamera.zoom = 1.0f;

  Rectangle sourceRec = {0.0f, 0.0f, (float)target.texture.width,
                         -(float)target.texture.height};
  Rectangle destRec = {-virtualRatio, -virtualRatio,
                       screenWidth + (virtualRatio * 2),
                       screenHeight + (virtualRatio * 2)};
  Vector2 origin = {0.0f, 0.0f};

  while (!WindowShouldClose()) {
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
