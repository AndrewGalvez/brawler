#include "player.h"
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

  /* clang-format off */
  Player players[1] = {
    {
      .rect = (Rectangle){playing_area.x, playing_area.y, 50, 50},
      .accel = 120.0f,
      .friction = 120.0f,
      .vel = Vector2Zero(),
      .keybinds = {
	[PLAYER_KEYBIND_MOVE_DOWN] = KEY_S,
	[PLAYER_KEYBIND_MOVE_UP] = KEY_W,
	[PLAYER_KEYBIND_MOVE_LEFT] = KEY_A,
	[PLAYER_KEYBIND_MOVE_RIGHT] = KEY_D
      },
      .clr = BLUE
    }
  };
  /* clang-format on */

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    PlayerMove(&players[0]);
    PlayerUpdate(&players[0], dt, playing_area);

    ClearBackground(WHITE);

    BeginTextureMode(target);
    ClearBackground(DARKGRAY);

    DrawTexturePro(ring_img, (Rectangle){0, 0, 100, 100}, playing_area_display,
                   Vector2Zero(), 0.0f, WHITE);

    PlayerDraw(players[0]);

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
