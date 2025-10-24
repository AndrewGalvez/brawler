#include "raylib.h"
#include "utils.h"

int main() {
  InitWindow(600, 450, "Peanut Butter");

  SetTargetFPS(60);

  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  InitAudioDevice();

  RenderTexture2D target = LoadRenderTexture(320, 240);

  while (!WindowShouldClose()) {
    ClearBackground(WHITE);

    BeginTextureMode(target);
    ClearBackground(BLACK);

    EndTextureMode();

    BeginDrawing();
    DrawRenderTexture(target, 320, 240);
    DrawFPS(0, 0);
    EndDrawing();
  }

  UnloadRenderTexture(target);

  CloseAudioDevice();

  CloseWindow();
  return 0;
}
