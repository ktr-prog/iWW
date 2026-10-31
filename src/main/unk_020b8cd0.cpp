#include "types.h"
#include "sys/PrioListNode.h"
#include "gfx/VramTask.h"

extern "C" {
u8 *NNS_G3dGetTex(u8 *p);
}



extern "C" u8 *Wallpaper_GetTex(u8 *p) {
    return NNS_G3dGetTex(p);
}

VramTask::VramTask() {
    state = 0;
    kind = 0xa;
    cost = 1;
}
