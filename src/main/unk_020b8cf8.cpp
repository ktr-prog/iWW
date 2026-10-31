#include "types.h"
#include "item/ItemId.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_020b8cf8.h"


extern "C" BOOL Wallpaper_LoadTexture(void *dst, ItemId *p) {
    s32 idx;
    BOOL ok = FALSE;
    u16 v = p->id;
    if (v >= 0x1100 && v <= 0x1143) {
        ok = TRUE;
    }
    if (ok) {
        idx = v - 0x1100;
    } else {
        idx = -1;
    }
    if (idx != -1) {
        char buf[0x20];
        Str_SPrintf(buf, "/wall/wall_%d.nsbtx", idx);
        if (File_LoadToBuffer(buf, dst, -1)) {
            return TRUE;
        }
        return FALSE;
    }
    static ItemId def(0x1100);
    return Wallpaper_LoadTexture(dst, &def);
}
