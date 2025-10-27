#pragma once
#include "raylib.h"
#include <raymath.h>

enum PLAYER_KEYBIND {
  PLAYER_KEYBIND_MOVE_LEFT,
  PLAYER_KEYBIND_MOVE_RIGHT,
  PLAYER_KEYBIND_MOVE_UP,
  PLAYER_KEYBIND_MOVE_DOWN
};

typedef struct {
  Rectangle rect;
  float accel;
  float friction;
  Vector2 vel;
  KeyboardKey keybinds[4];
  Color clr;
} Player;

inline void PlayerDraw(const Player p) { DrawRectangleRec(p.rect, p.clr); }

inline bool PlayerGetKeybindDown(const Player p, const enum PLAYER_KEYBIND kb) {
  return IsKeyDown(p.keybinds[kb]);
}

inline void PlayerMove(Player *p) {
  p->vel = Vector2Zero();
  if (PlayerGetKeybindDown(*p, PLAYER_KEYBIND_MOVE_LEFT))
    p->vel.x -= p->accel;
  if (PlayerGetKeybindDown(*p, PLAYER_KEYBIND_MOVE_RIGHT))
    p->vel.x += p->accel;
  if (PlayerGetKeybindDown(*p, PLAYER_KEYBIND_MOVE_UP))
    p->vel.y -= p->accel;
  if (PlayerGetKeybindDown(*p, PLAYER_KEYBIND_MOVE_DOWN))
    p->vel.y += p->accel;
}

inline void PlayerUpdate(Player *p, const float dt, Rectangle playing_area) {
  Vector2 moveAmount = {p->vel.x * dt, p->vel.y * dt};
  if ((p->rect.x + moveAmount.x < playing_area.x && moveAmount.x < 0) ||
      (p->rect.x + p->rect.width > playing_area.x + playing_area.width &&
       moveAmount.x > 0)) {
    p->vel.x = 0;
    moveAmount.x = 0;
  }
  if ((p->rect.y + moveAmount.y < playing_area.y && moveAmount.y < 0) ||
      (p->rect.y + p->rect.height > playing_area.y + playing_area.height &&
       moveAmount.y > 0)) {
    p->vel.y = 0;
    moveAmount.y = 0;
  }

  p->rect.x += moveAmount.x;
  p->rect.y += moveAmount.y;
}
