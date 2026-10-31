#ifndef HOST_IOS_IOS_H
#define HOST_IOS_IOS_H

#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

void ios_safe_area(SDL_Window *window, float out[4]);
void ios_fatal_message(const char *text);
int host_main(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif
