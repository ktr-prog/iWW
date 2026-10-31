#ifndef SYS_INPUTREPLAY_H
#define SYS_INPUTREPLAY_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void Input_ReplayKeys(u16 keys);
void Input_ReplayTouch(void);

#ifdef __cplusplus
}
#endif

#endif
