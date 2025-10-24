#include "raylib.h"
#include "utils.h"
#include <raymath.h>

int main() {
  InitWindow(600, 600, "Peanut Butter");

  SetTargetFPS(60);

  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  InitAudioDevice();

  RenderTexture2D target = LoadRenderTexture(600, 600);

  Rectangle playing_area_display = {100, 100, 400, 400};
  Rectangle playing_area = {132, 132, 400 - 64, 400 - 64};

  Texture2D ring_img = LoadTexture("assets/ring.png");

  while (!WindowShouldClose()) {
    ClearBackground(WHITE);

    BeginTextureMode(target);
    ClearBackground(DARKGRAY);

    DrawTexturePro(ring_img, (Rectangle){0, 0, 100, 100}, playing_area_display,
                   Vector2Zero(), 0.0f, WHITE);

    EndTextureMode();

    BeginDrawing();
    DrawRenderTexture(target, 600, 600);

    DrawFPS(0, 0);
    EndDrawing();
  }

  UnloadRenderTexture(target);

  UnloadTexture(ring_img);

  CloseAudioDevice();

  CloseWindow();
  return 0;
}
