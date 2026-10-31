#include "types.h"
#include "gfx/VecFx32.h"
#include "snd/SndEnvChannel.h"
#include "snd/SndSeEmitter.h"
#include "gfx/Mtx43.h"
#include "gfx/Model.h"
#include "gfx/DebugColor.h"
#include "town/Unk_0204e858_Grid.h"
#include "gfx/BgModelCache.h"
#include "field/GroundSoundSrc.h"
#include "snd/RainSndChannel.h"
#include "sys/new.h"
#include "proto/main/unk_02036c58.h"
#include "proto/ov003/unk_ov003_02217908.h"








extern "C" {
extern void *gSceneBlockMap;
extern void *gCamera;
extern s32 data_020c8cbc;

s32 Vec_DistXZ(VecFx32 *a, VecFx32 *b);
}

extern "C" {
DebugColor data_ov003_02235460(31, 20, 20, 31);
DebugColor data_ov003_02235474(20, 20, 31, 31);
DebugColor data_ov003_02235470(31, 31, 20, 31);
DebugColor data_ov003_0223546c(20, 31, 20, 31);
DebugColor data_ov003_02235468(20, 31, 31, 31);
DebugColor data_ov003_02235464(20, 24, 24, 31);
}


extern "C" BOOL FieldGround_DrawBackdrop(Model *p) {
    if (gCamera != 0) {
        p->drawScaled(0);
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL FieldGround_ReleaseBackdrop(Model *p) {
    p->clearResource();
    return TRUE;
}

extern "C" BgAcreModel *FieldGround_GetBlockAcre(GroundSoundSrc *r, u32 x, u32 y) {
    Unk_0204e858_Grid *g = (Unk_0204e858_Grid *)gSceneBlockMap;
    if (g != 0) {
        TownBlockCell *c;
        if (x < g->width && y < g->height && g->blocks != 0) {
            c = &g->blocks[y * g->width + x];
        } else {
            c = 0;
        }
        if (c != 0) {
            return c->bgModel;
        }
    }
    return 0;
}

extern "C" void *FieldGround_GetBlockBgObjects(GroundSoundSrc *r, u32 x, u32 y) {
    BgAcreModel *s = FieldGround_GetBlockAcre(r, x, y);
    if (s != 0) {
        return s->bsd;
    }
    return 0;
}

extern "C" GroundSoundSrc *FieldGround_FindSoundSrc(GroundSoundSrc *out, VecFx32 *pos) {
    u8 *obj;
    u32 n;
    FieldGround_ResetSoundSrc(out);
    s32 cx = pos->x >> 17;
    s32 cz = pos->z >> 17;
    s32 dy, dx;
    for (dy = -1; dy <= 1; dy++) {
        for (dx = -1; dx <= 1; dx++) {
            VecFx32CtorDtor base;
            s32 xx = cx + dx;
            base.x = xx << 17;
            base.z = (cz + dy) << 17;
            obj = (u8 *)FieldGround_GetBlockBgObjects(out, xx, cz + dy);
            if (obj != 0) {
                u32 i;
                n = BgMgt_GetCount((s16 *)obj);
                for (i = 0; i < n; i++) {
                    VecFx32 e = BgMgt_GetEntry(obj, i);
                    switch (e.x) {
                    case 5:
                    case 15:
                    case 17:
                    case 18: {
                        VecFx32 p;
                        p.x = base.x + e.y;
                        p.y = 0;
                        p.z = base.z + e.z;
                        FieldGround_ConsiderSoundSrc(out, Vec_DistXZ(&p, pos), &p, e.x);
                    }
                    }
                }
            }
        }
    }
    return out;
}

extern "C" BOOL FieldGround_ConsiderSoundSrc(GroundSoundSrc *r, s32 d, VecFx32 *p, s32 k) {
    if (d < r->distance) {
        r->pos.x = p->x;
        r->pos.y = p->y;
        r->pos.z = p->z;
        r->distance = d;
        r->kind = k;
        r->found = 1;
        return TRUE;
    }
    return FALSE;
}

extern "C" void FieldGround_EndSoundSrc() {
}

extern "C" void FieldGround_ResetSoundSrc(GroundSoundSrc *r) {
    r->found = 0;
    r->pos.x = 0;
    r->pos.y = 0;
    r->pos.z = 0;
    r->kind = 0x11;
    r->distance = data_020c8cbc << 3;
}

extern "C" VecFx32 *FieldGround_GetSoundSrcPos(GroundSoundSrc *r) {
    if (r->found != 0) {
        return &r->pos;
    }
    return 0;
}

extern "C" s32 FieldGround_GetSoundSrcKind(GroundSoundSrc *r) {
    return r->kind;
}

extern "C" void FieldGround_InitEnvChannel(RainSndChannel *p) {
    new (p) RainSndChannel;
}

extern "C" void FieldGround_DestroyEnvChannel() {
}

extern "C" void FieldGround_ResetEnvChannel(SndEnvChannel *p) {
    p->callReset();
}

extern "C" void FieldGround_PlayEnvSe(SndEnvChannel *p, VecFx32 *v, u32 a) {
    VecFx32 t;
    t.x = v->x;
    t.y = v->y;
    t.z = v->z;
    p->callUpdateRelative(&t);
    p->callRequest(a);
}

extern "C" void FieldGround_ReleaseEnvChannel(SndEnvChannel *p) {
    p->callRelease();
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02217908) {
    HOST_OVERLAY_VAR(data_ov003_02235460),
    HOST_OVERLAY_VAR(data_ov003_02235474),
    HOST_OVERLAY_VAR(data_ov003_02235470),
    HOST_OVERLAY_VAR(data_ov003_0223546c),
    HOST_OVERLAY_VAR(data_ov003_02235468),
    HOST_OVERLAY_VAR(data_ov003_02235464),
    HOST_OVERLAY_VARS_END
};
