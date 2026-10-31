#include "types.h"
#include "gfx/VecFx32.h"
#include "game/GroundInfoBase.h"
#include "gfx/NNSG3dResMatData.h"
#include "gfx/Mtx43.h"
#include "gfx/Model.h"
#include "gfx/CachedModel.h"
#include "game/GroundInfo.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_020643dc.h"
#include "proto/main/unk_020abbcc.h"
#include "proto/main/unk_020abea8.h"


extern "C" {
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
void NNS_G3dMdlSetMdlDiff(u8 *res, u32 i, u32 v);
void NNSi_G3dModifyMatFlag(u8 *res, BOOL on, u32 mask);
void Mtx43_SetTranslate(Mtx43 *m, s32 x, s32 y, s32 z);
void Mtx43_RotateX(Mtx43 *m, s32 angle);
s32 Ground_GetDefaultY(void);
BOOL Scene_InMuseumRoom(void);
extern u8 gFieldSceneKind;
}
extern Mtx43 data_021f47e0;

u32 sCharaShadowPolyId = 1;

NNSG3dResMatData *sCharaShadowMatData;
CachedModel sCharaShadowModel;

extern "C" BOOL CharaShadow_Load() {
    BOOL ret;
    if (sCharaShadowModel.load((void *)"/shadow/chara_shadow.nsbmd", 0)) {
        ret = TRUE;
    } else {
        ret = FALSE;
    }
    u8 *mdl = (u8 *)sCharaShadowModel.resMdl;
    u8 *mat = mdl + *(s32 *)(mdl + 8);
    sCharaShadowMatData = (NNSG3dResMatData *)(mat + *(s32 *)(mat + *(u16 *)(mat + 0xa) + 8));
    sCharaShadowPolyId = 1;
    NNSi_G3dModifyMatFlag((u8 *)sCharaShadowModel.resMdl, 1, 0x40);
    return ret;
}

extern "C" void CharaShadow_UpdateColor() {
    sCharaShadowPolyId = 1;
    u16 c = SceneLights_GetRoomColor();
    NNS_G3dMdlSetMdlDiff((u8 *)sCharaShadowModel.resMdl, 0, c);
}

extern "C" void CharaShadow_Unload() {
    sCharaShadowMatData = 0;
    sCharaShadowModel.release();
}

extern "C" void CharaShadow_DrawFaded(VecFx32 *pos, s32 a, s32 b, s32 c) {
    if (c == 0) {
        c = 1;
    }
    s32 r6 = 0x1000;
    if (c != 0x1f) {
        r6 = FX_Div((c - 1) << 12, 0x1e000);
    }
    CharaShadow_Draw(pos, a, b, r6);
}

extern "C" void CharaShadow_Draw(VecFx32 *pos, s32 a, s32 b, s32 c) {
    VecFx32 pos2;
    VecFx32 out;
    VecFx32 scale;
    s32 off, d, absd;
    if (a == 0) {
        return;
    }
    s32 lvl = ObjShadow_GetCharaAlpha(pos, a);
    off = 0;
    if (gFieldSceneKind == 0) {
        GroundInfo ground;
        ground.initAtPos(pos, 0, 0);
        off = ground.getHeight(0);
        if (off > 0) {
            off = 0;
        }
    } else if (Scene_InMuseumRoom()) {
        GroundInfo ground;
        ground.initAtPos(pos, 0, 0);
        off = ground.getHeight(0);
    }
    d = pos->y - off;
    if (d < 0) {
        absd = -d;
    } else {
        absd = d;
    }
    if (d != 0) {
        lvl -= func_01ffcb0c(absd, FX_Div(0x1f000, b)) >> 12;
    }
    if (c != 0x1000) {
        lvl = (lvl * c) >> 12;
    }
    if (lvl > 1) {
        if (d != 0) {
            s32 k = func_01ffcb0c(FX_Div(-0x1000, b), absd) + 0x1000;
            if (k >= 0xf33) {
                k = 0x1000;
            }
            a = func_01ffcb0c(a, k);
        }
        if (a > 0) {
            s32 t;
            pos2 = *pos;
            pos2.y = off + Ground_GetDefaultY();
            t = WorldCurve_ToCurved(&out, &pos2);
            Mtx43_SetTranslate(&data_021f47e0, out.x, out.y, out.z);
            Mtx43_RotateX(&data_021f47e0, t);
            sCharaShadowModel.mtx = data_021f47e0;
            scale.x = a;
            scale.y = 0x1000;
            scale.z = a;
            if (sCharaShadowMatData != 0) {
                sCharaShadowMatData->polyAttr &= 0xffe0ffff;
                sCharaShadowMatData->polyAttr |= (lvl & 0x1f) << 16;
                sCharaShadowMatData->polyAttr &= 0xc0ffffff;
                sCharaShadowMatData->polyAttr |= sCharaShadowPolyId << 24;
                sCharaShadowMatData->polyAttrMask |= 0x3f1f0000;
            }
            sCharaShadowModel.drawScaled((s32 *)&scale);
            sCharaShadowPolyId++;
            if (sCharaShadowPolyId > 0xb) {
                sCharaShadowPolyId = 1;
            }
        }
    }
}

extern "C" void CharaShadow_DrawPlayer(VecFx32 *pos, s32 a) {
    VecFx32 v;
    v = *pos;
    v.y = v.y - (Ground_GetDefaultY() + 0x800);
    CharaShadow_Draw(&v, a, 0xe00, 0x1000);
}
