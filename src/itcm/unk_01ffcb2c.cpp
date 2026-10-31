#include "types.h"
#include "gfx/VecFx32.h"
#include "game/CollisionMap.h"
#include "town/TownBlockCell.h"
#include "gfx/Camera.h"
#include "gfx/HBlankTask.h"
#include "gfx/NNSG3dRS.h"
#include "nitro/io_access.h"
#include "proto/itcm/unk_01ffcb2c.h"
#include "proto/itcm/unk_01ffcfc0.h"

struct CellGrid {
    /* 0x00 */ TownBlockCell *cells;
    /* 0x04 */ s32 w;
};


extern "C" {
extern HBlankTask *sHBlankListHead;
}

static inline CollisionBlockRef *At(s32 x, s32 z) {
    CollisionMap *g = gCurCollisionMap;
    if (x >= 0 && z >= 0 && (u32)x < g->numBlocksX && (u32)z < g->numBlocksZ) {
        return &g->blocks[z][x];
    }
    return 0;
}

extern "C" void HBlank_Handler(void) {
    if (IO_R((vu16 *)0x04000006) < 192) {
        HBlankTask *n = sHBlankListHead;
        if (n != 0) {
            do {
                if (n->param != 0) {
                    n->param();
                }
                n = n->next;
            } while (n != 0);
        }
    }
}

extern "C" BOOL func_01ffcc10(void *a, NNSG3dRS *o) {
    if ((o->c[0] & 0x1f) != 6) {
        return TRUE;
    }
    if (o->pRenderObj->recJntAnm == 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TownBlockMap_IsBuried(CellGrid *g, s32 x, s32 z) {
    s32 cx = x >> 4;
    s32 cz = z >> 4;
    u16 row = g->cells[cx + cz * g->w].buried[z - (cz << 4)];
    if ((row & (1 << (x - (cx << 4)))) == 0) {
        return FALSE;
    }
    return TRUE;
}

extern "C" void Camera_GetLookAtPoint(VecFx32 *out, Camera *c) {
    VecFx32 t;
    Camera_GetLookAtOffset(&t, c);
    Vec_Add(out, (VecFx32 *)&c->currentFocus, &t);
}

extern "C" void Camera_GetLookAtOffset(VecFx32 *out, Camera *c) {
    Vec_Add(out, (VecFx32 *)&c->currentOffset, (VecFx32 *)&c->unk_84);
}

extern "C" CollisionBlockRef *CollisionMap_GetBlockRef(s32 x, s32 z) {
    CollisionBlockRef *p = At(x, z);
    if (p != 0) {
        return p;
    }
    return 0;
}

extern "C" u32 Ground_GetUnitAttr(s32 x, s32 y) {
    CollisionBlockRef *c = CollisionMap_GetBlockRef(x >> 4, y >> 4);
    u32 v;
    if (c != 0) {
        v = c->attrs[(x & 15) + ((y & 15) << 4)];
    } else {
        v = 21;
    }
    return v;
}

