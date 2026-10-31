#include "types.h"
#include "gfx/HudObjGfx.h"
#include "proto/main/unk_02011690.h"
#include "proto/main/unk_020116e0.h"


extern "C" {
}

const char *HudObjGfx::getPalettePath(s32 mode) {
    if (mode >= 4) mode = Hud_GetSceneHudKind();
    const char *b = "/a_mes/a_mes_ten0_obj_ncl.bin";
    const char *a = "/a_mes/a_mes_ten1_obj_ncl.bin";
    const char *c = "/a_mes/a_mes_ten2_obj_ncl.bin";
    const char *r = "/a_mes/a_mes_obj_ncl.bin";
    if (mode == 2) r = a;
    else if (mode == 3) r = b;
    else if (countdownVariant != 0) r = c;
    return r;
}
