#ifndef HOST_FRONTEND_UI_H
#define HOST_FRONTEND_UI_H

#include <SDL.h>
#include <stdint.h>

void ui_init(void);
uint32_t ui_keyboard_keys(const Uint8 *keyboard);
uint32_t ui_pad_keys(SDL_GameController *pad);
int ui_key_bound(SDL_Scancode sc);
int ui_event(const SDL_Event *e);
int ui_is_open(void);
const uint32_t *ui_overlay(int *changed);
void ui_open_settings(void);
void ui_toast(const char *msg);
int ui_tap(int x, int y);

#endif
