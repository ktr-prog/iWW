#include "types.h"
#include "gfx/VecFx32.h"
#include "room/FtrActorTable.h"
#include "game/TouchPicker.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020b5e5c.h"
#include "proto/main/unk_020b705c.h"
#include "proto/ov003/unk_ov003_022048c0.h"
#include "proto/ov003/unk_ov003_022187fc.h"
#include "proto/ov003/unk_ov003_0222e734.h"
#include "proto/ov004/unk_ov004_022048c0.h"
#include "proto/ov004/unk_ov004_022136d0.h"
#include "proto/ov004/unk_ov004_02213b90.h"
#include "proto/ov004/unk_ov004_02227e3c.h"
#include "proto/ov004/unk_ov004_02229660.h"
#include "proto/ov004/unk_ov004_02233074.h"

extern "C" u8 gFieldSceneKind;
extern "C" u8 gTouchPrevHeld;
extern "C" u8 gTouchPrevChanged;

inline BOOL IsMode0() { return gFieldSceneKind == 0; }
inline BOOL IsBoth() { return gTouchPrevHeld && gTouchPrevChanged; }
inline BOOL IsMode1() { return gFieldSceneKind == 1; }


typedef void *(*TouchTargetResolver)(s32 index);
#define FN(f) ((TouchTargetResolver)(f))

extern "C" TouchTargetResolver sTouchTargetResolvers[23];
extern "C" TouchTargetResolver sTouchTargetResolvers[23] = {
    FN(TouchTarget_ResolveNone), FN(TouchTarget_ResolvePlayer), FN(TouchTarget_ResolveVillager), FN(TouchTarget_ResolveSpNpc),
    FN(TouchTarget_ResolveNone), FN(TouchTarget_ResolveNone), FN(TouchTarget_ResolveBuildingAlt), FN(TouchTarget_ResolveBuilding),
    FN(TouchTarget_ResolveFurniture), FN(TouchTarget_ResolveVillagerBoard), FN(TouchTarget_ResolveNone), FN(TouchTarget_ResolveAtm),
    FN(TouchTarget_ResolveRecycleBox), FN(TouchTarget_ResolvePhone), FN(TouchTarget_ResolveMuseumInfo), FN(TouchTarget_ResolveFurniture),
    FN(TouchTarget_ResolveBoardSign), FN(TouchTarget_ResolveSnowball), FN(TouchTarget_ResolveSnowball), FN(TouchTarget_ResolveNone),
    FN(TouchTarget_ResolveNone), FN(TouchTarget_ResolveNone), FN(TouchTarget_ResolveNone),
};

extern "C" BOOL TouchPickResult_GetTarget(TouchPickResult *obj, VecFx32 *out, s32 *a, u8 *b) {
    if (out) {
        out->x = obj->targetX;
        out->y = obj->targetY;
        out->z = obj->targetZ;
    }
    if (a) {
        *a = obj->targetKind;
    }
    if (b) {
        *b = obj->targetIndex;
    }
    return TouchPickKind_HasTarget(obj->targetKind);
}

extern "C" void *TouchPick_GetTargetObject(TouchPickResult *a, s32 *pa, u8 *pb) {
    u8 tb;
    s32 ta;
    VecFx32 v;
    if (pa == NULL) {
        pa = &ta;
    }
    if (pb == NULL) {
        pb = &tb;
    }
    if (TouchPickResult_GetTarget(a, &v, pa, pb)) {
        return TouchTarget_Resolve(*pa, *pb);
    }
    return NULL;
}

extern "C" void *TouchPick_GetTappedObject(TouchPickResult *a, s32 *pa, u8 *pb) {
    if (IsBoth()) {
        return TouchPick_GetTargetObject(a, pa, pb);
    }
    return NULL;
}

extern "C" void *TouchTarget_ResolveNone(void) { return NULL; }

extern "C" void *TouchTarget_ResolvePlayer(s32 a) { return PlayerActor_GetCharacter(a); }

extern "C" void *TouchTarget_ResolveVillager(s32 a) { return NpcRegistry_FindVillager(a); }

extern "C" void *TouchTarget_ResolveSpNpc(s32 a) { return NpcRegistry_FindSpNpc(a); }

extern "C" void *TouchTarget_ResolveBuilding(s32 a) {
    if (IsMode0()) {
        return BuildingList_GetAt(a);
    }
    return NULL;
}

extern "C" void *TouchTarget_ResolveBuildingAlt(s32 a) { return TouchTarget_ResolveBuilding(a); }

extern "C" void *TouchTarget_ResolveFurniture(s32 a) {
    if (IsMode1()) {
        return FtrActorTable_GetInstance()->get(a);
    }
    return NULL;
}

extern "C" void *TouchTarget_ResolveVillagerBoard(s32 a) {
    if (IsMode0()) {
        return VillagerBoard_Get(a);
    }
    return NULL;
}

extern "C" void *TouchTarget_ResolveAtm(void) {
    if (IsMode1()) {
        return Atm_GetInstance();
    }
    return NULL;
}

extern "C" void *TouchTarget_ResolveMuseumInfo(s32 a) {
    if (IsMode1()) {
        return MuseumExhibitInfo_GetByIndex(a);
    }
    return NULL;
}

extern "C" void *TouchTarget_ResolveRecycleBox(void) {
    if (IsMode1()) {
        return RecycleBox_GetInstance();
    }
    return NULL;
}

extern "C" void *TouchTarget_ResolvePhone(void) {
    if (IsMode1()) {
        return RoomTelephone_GetInstance();
    }
    return NULL;
}

extern "C" void *TouchTarget_ResolveBoardSign(s32 a) {
    if (IsMode1()) {
        return RoomBoardSign_GetByIndex(a);
    }
    return NULL;
}

extern "C" void *TouchTarget_ResolveSnowball(s32 a) {
    if (IsMode0()) {
        return Snowball_FindByParam(a);
    }
    return NULL;
}

extern "C" void *TouchTarget_Resolve(s32 idx, s32 arg) {
    if (idx < 0x17) {
        return sTouchTargetResolvers[idx](arg);
    }
    return NULL;
}

