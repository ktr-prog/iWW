#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/Mtx43.h"
#include "net/CommManager.h"
#include "player/PlayerActor.h"
#include "player/PlayerData.h"
#include "player/PlayerFaceTexRef.h"
#include "town/Unk_0204e858_Grid.h"
#include "proto/main/unk_02004558.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_0205dfa4.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02097d1c.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/main/unk_0204cc1c.h"


extern "C" {
extern u8 gFieldSceneKind;
extern CommManager *gCommManager;
extern BlockMap *gSceneBlockMap;
BOOL Scene_InHouseRoom(void);
u32 ItemInfo_GetHoldableCount();
void ItemInfo_GetNthHoldable(u16 *out, s32 idx);
void PlayerActor_GetHeldItem(u16 *out, void *x);
s32 PlayerActor_GetHairStyle(void *p);
s32 PlayerActor_GetHairColor(void *p);
}

s32 sPlayerFrontItemDist = 0xccd;

extern "C" VecFx32 *PlayerActor_GetBodyPos(u32 idx) {
    PlayerActor *o = PlayerActor_Get(idx);
    if (o) return &o->bodyPos;
    return 0;
}

extern "C" void PlayerActor_GetSlotHeldItem(u16 *out, u32 idx) {
    PlayerActor *o = PlayerActor_Get(idx);
    u16 v[4];
    *out = 0xfff1;
    if (o) {
        PlayerActor_GetHeldItem(v, o);
        *out = v[0];
    }
}

extern "C" BOOL PlayerActor_SetHoldableItem(u32 a, u32 idx) {
    PlayerActor *o = PlayerActor_Get(idx);
    u16 v[8];
    if (!o) return FALSE;
    void *p = PlayerData_GetBySessionSlot(idx);
    if (o->animId >= 0xa1) {
        if (a == 0 || ItemInfo_GetHoldableCount() < a) {
            v[1] = 0xfff1;
            ((PlayerData *)(p))->setHeldItem(&v[1]);
        } else {
            ItemInfo_GetNthHoldable(&v[2], a - 1);
            ((PlayerData *)(p))->setHeldItem(&v[2]);
        }
        return FALSE;
    }
    if (a == 0 || ItemInfo_GetHoldableCount() < a) {
        v[3] = 0xfff1;
        ((PlayerData *)(p))->setHeldItem(&v[3]);
        v[4] = 0xfff1;
        HeldItemModel_SetItem(&o->heldItemModel, &v[4], 0);
        (o)->replayAnim();
    } else {
        ItemInfo_GetNthHoldable(&v[0], a - 1);
        ((PlayerData *)(p))->setHeldItem(&v[0]);
        HeldItemModel_SetItem(&o->heldItemModel, &v[0], p);
        (o)->replayAnim();
        HeldItemModel_Update(&o->heldItemModel);
    }
    return TRUE;
}

extern "C" BOOL PlayerActor_SetClothing(u16 *p, s32 kind, u32 idx) {
    void *q = PlayerData_GetBySessionSlot(idx);
    u16 v1, v2;
    if (!q) return FALSE;
    switch (kind) {
    case 0:
        ((PlayerData *)(q))->setShirt(p);
        break;
    case 1:
        ((PlayerData *)(q))->setFaceItem(p);
        break;
    case 2:
        ((PlayerData *)(q))->setHat(p);
        break;
    }
    PlayerActor *o = PlayerActor_Get(idx);
    if (!o) return FALSE;
    if (o->animId >= 0xa1) return FALSE;
    switch (kind) {
    case 0:
        (o)->setShirtTexture((void *)(void *)(p));
        (o)->requestShirtTexUpload();
        break;
    case 1:
        v1 = *p;
        o->requestFaceItemChange(&v1);
        break;
    case 2: {
        v2 = *p;
        s32 r4 = PlayerActor_GetHairStyle(o);
        s32 r3 = PlayerActor_GetHairColor(o);
        (o)->requestHatChange(&v2, r4, r3, 0);
        break;
    }
    }
    return TRUE;
}

extern "C" BOOL PlayerActor_SetSwollenFace(s32 a, u32 idx) {
    void *p = PlayerData_GetBySessionSlot(idx);
    if (!p) return FALSE;
    PlayerData_SetStungFace(p, a);
    PlayerActor *o = PlayerActor_Get(idx);
    if (!o) return FALSE;
    if (o->animId >= 0xa1) return FALSE;
    u32 v;
    if (a) {
        v = ((PlayerData *)(p))->getFaceType() + 0x10;
    } else {
        v = ((PlayerData *)(p))->getFaceType();
    }
    o->faceTex.load(v);
    return TRUE;
}

extern "C" BOOL PlayerActor_SetTan(u32 x, u32 idx) {
    void *p = PlayerData_GetBySessionSlot(idx);
    if (!p) return FALSE;
    ((PlayerData *)(p))->setTan(x);
    return TRUE;
}

extern "C" BOOL PlayerActor_SetHeadTilt(u32 a, u32 b, u32 idx) {
    PlayerActor *o = PlayerActor_Get(idx);
    if (o) {
        if (!o->testActionFlag(0x15)) {
            o->setActionFlag(0x15);
        }
        o->headPitchTarget = a;
        o->headYawTarget = b;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL PlayerActor_GetHeadPos(VecFx32Ctor *out, u32 idx) {
    PlayerActor *o = PlayerActor_Get(idx);
    if (o) {
        s32 a = o->headMtx.m[9];
        if (a == 0 && o->headMtx.m[10] == 0 && o->headMtx.m[11] == 0) return FALSE;
        out->x = a;
        out->y = o->headMtx.m[10];
        out->z = o->headMtx.m[11];
        WorldCurve_FromCurved(out, out);
        return TRUE;
    }
    return FALSE;
}

extern "C" void PlayerActor_GetHandMtx(Mtx43 *out, u32 idx) {
    PlayerActor *o = PlayerActor_Get(idx);
    *out = *(Mtx43 *)&o->itemHandMtx;
}

extern "C" u16 *PlayerActor_GetItemInFront() {
    PlayerActor *o = PlayerActor_Get(4);
    u16 *r = 0;
    VecFx32 buf;
    s32 a, b;
    if (!o) return 0;
    if (o->action != 2) return 0;
    PlayerActor_OffsetByAngle(&buf, o, &o->position, &o->rotY, &sPlayerFrontItemDist);
    BOOL t = gFieldSceneKind == 1 ? TRUE : FALSE;
    if (t) {
        if (Scene_InHouseRoom()) {
            if (gCommManager->localSlot == 0) {
                if (FtrMgr_FindFurnitureFacingPlayer(&a, &b, 0, 0) < 0) {
                    r = BlockMap_GetItemPtrAtPos(gSceneBlockMap, &buf, 0);
                }
            }
        }
    } else {
        BlockMap *g = gSceneBlockMap;
        if (BlockMap_IsBuriedAtPos(g, &buf)) return 0;
        r = BlockMap_GetItemPtrAtPos(g, &buf, 0);
    }
    return r;
}

extern "C" void PlayerActor_SetLocalExitId(s32 *p) {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        o->exitIndex = *p;
    }
}

extern "C" void PlayerActor_SetLocalExitKind(u32 *p) {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        o->exitMode = *p;
    }
}

extern "C" void PlayerActor_OnChatOpenNop() {}

extern "C" void PlayerActor_OnChatCloseNop() {}

extern "C" void PlayerActor_PlayLocalSe(u32 x) {
    PlayerActor *o = PlayerActor_Get(4);
    if (o) {
        o->playSe(x);
    }
}

