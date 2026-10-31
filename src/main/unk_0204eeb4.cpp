#include "types.h"
#include "uptr.h"
#include "nitro/fs.h"
#include "gfx/VecFx32.h"
#include "town/Unk_0204e858_Grid.h"
#include "sys/OverlaySlot.h"
#include "town/MapBlockEntry.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_0211a6c0.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_0204f134.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206d49c.h"


OverlaySlot sOverlaySlots[12];

static inline TownBlockCell *Unk_0204e858_GetCell(Unk_0204e858_Grid *g, u32 x, u32 y) {
    if (x < g->width && y < g->height && g->blocks != NULL) {
        return &g->blocks[y * g->width + x];
    }
    return NULL;
}

static inline BOOL Unk_0204e8b0_Bit(u16 *m, u32 x, u32 y) {
    BOOL r = FALSE;
    if (x >= 16 || y >= 16) {
    } else {
        r = TRUE;
    }
    if (r) {
        if (x < 16) {
            u32 v = m[y];
            r = TRUE;
            if ((v & (r << x)) != 0) {
                return r;
            }
        }
        r = FALSE;
    } else {
        r = FALSE;
    }
    return r;
}

namespace Unk_0204eba0_Ns {
}



extern "C" {
void OverlayMgr_UnloadSlot(OverlaySlot *e);
BOOL FS_LoadOverlayInfo(FSOverlayInfo *p, int target, u32 id);
void Clock_GetDayMonth(void *p);
}

extern "C" void OverlayMgr_UnloadSlot(OverlaySlot *e);


extern "C" u32 FishTable_GetHourSlot(u32 r) {
    u32 v = 0;
    if ((r >= 4 && r < 9) || (r >= 16 && r < 21)) {
        v = 0;
    } else if (r >= 9 && r < 16) {
        v = 1;
    } else if ((r >= 21 && r <= 24) || r < 4) {
        v = 2;
    } else if (r >= 4) {
    }
    return v;
}

extern "C" BOOL FishTable_IsLateMonth(u8 v) {
    if (v > 15) {
        return TRUE;
    }
    return FALSE;
}

extern "C" u8 FishTable_GetPeriod(u8 x) {
    u8 t[4];
    if (x >= 1 && x <= 7) {
        return x;
    }
    if (x == 8) {
        Clock_GetDayMonth(&t[0]);
        if (FishTable_IsLateMonth(t[0]) != 0) {
            x = x + 1;
        }
        return x;
    }
    if (x == 9) {
        Clock_GetDayMonth(&t[2]);
        if (FishTable_IsLateMonth(t[2]) == 0) {
            return x + 1;
        }
        return x + 2;
    }
    if (x >= 10 && x <= 12) {
        return x + 2;
    }
    return 1;
}

extern "C" s32 Fish_GetWaterKind(s32 r) {
    if (r < 0 || r >= 0x38) {
        return 0;
    }
    if (r >= 0x23) {
        return 3;
    }
    if (r >= 9 && r <= 11) {
        return 2;
    }
    return 1;
}

extern "C" void OverlayMgr_GetInfo(void *p, u32 id) {
    FS_LoadOverlayInfo((FSOverlayInfo *)p, 0, id);
}

extern "C" void OverlayMgr_LoadOverlay(u32 id) {
    File_LoadOverlay(id);
}

extern "C" void OverlayMgr_UnloadOverlay(u32 id) {
    File_UnloadOverlay(id);
}

extern "C" void OverlayMgr_LoadSlot(OverlaySlot *e, u32 id) {
    FSOverlayInfo info;
    OverlayMgr_GetInfo(&info, id);
    OverlayMgr_LoadOverlay(id);
    e->overlayId = id;
    e->refCount = 1;
    e->unk_02 = 0;
    e->ramStart = info.header.ram_address;
    e->ramSize = info.header.ram_size + info.header.bss_size;
}

extern "C" void OverlayMgr_UnloadSlot(OverlaySlot *e) {
    FSOverlayInfo info;
    u32 id = e->overlayId;
    OverlayMgr_UnloadOverlay(id);
    OverlayMgr_GetInfo(&info, id);
    e->overlayId = 0xff;
    e->refCount = 0;
    e->unk_02 = 0;
    e->ramStart = 0;
    e->ramSize = 0;
}

extern "C" void OverlayMgr_Acquire(u32 id) {
    OverlaySlot *free = NULL;
    s32 i;
    u32 lo, hi;
    FSOverlayInfo info;
    for (i = 0; (u32)i < 12; i++) {
        OverlaySlot *e = &sOverlaySlots[i];
        if (e->overlayId == id) {
            e->refCount++;
            return;
        }
        if (((volatile OverlaySlot *)e)->overlayId == 0xff && free == NULL) {
            free = e;
        }
    }
    OverlayMgr_GetInfo(&info, id);
    FS_GetOverlayFileID(&info.header);
    for (i = 0, lo = info.header.ram_address, hi = lo + (info.header.ram_size + info.header.bss_size); (u32)i < 12; i++) {
        OverlaySlot *e = &sOverlaySlots[i];
        if (e->overlayId != id && ((volatile OverlaySlot *)e)->overlayId != 0xff && e->ramStart + e->ramSize > lo && hi > e->ramStart) {
            if (e->refCount == 0) {
                OverlayMgr_UnloadSlot(e);
                if (free == NULL) {
                    free = e;
                }
            } else {
                Fatal_Trap();
            }
        }
    }
    if (free != NULL) {
        OverlayMgr_LoadSlot(free, id);
    }
}

extern "C" void OverlayMgr_Release(u32 id) {
    OverlaySlot *e = NULL;
    for (s32 i = 0; (u32)i < 12; i++) {
        OverlaySlot *c = &sOverlaySlots[i];
        if (c->overlayId == id) {
            e = c;
            if (c->refCount != 0) {
                c->refCount--;
            }
        }
    }
    if (e == NULL) {
        Fatal_Trap();
    }
    if (e->refCount == 0) {
        OverlayMgr_UnloadSlot(e);
    }
}

extern "C" void OverlayMgr_Init() {
    for (s32 i = 0; (u32)i < 12; i++) {
        sOverlaySlots[i].overlayId = 0xff;
        sOverlaySlots[i].refCount = 0;
        sOverlaySlots[i].unk_02 = 0;
        sOverlaySlots[i].ramStart = 0;
        sOverlaySlots[i].ramSize = 0;
    }
}

