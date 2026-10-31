#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "menu/MenuSlide.h"
#include "menu/MenuProc.h"
#include "menu/PocketMenu.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02034048.h"
#include "proto/main/unk_02060b9c.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/ov096/unk_02294c40.h"
#include "proto/ov097/unk_0229b280.h"

extern "C" {
s32 Item_IsFurniture(u16 *p);
s32 FieldAction_RequestDrop(s32 a, s32 b);
}

extern "C" CommManager *gCommManager;





extern "C" {
}


static inline BOOL Unk_ov097_Range(volatile u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    u32 x = *p;
    u32 y = *p;
    if (y >= lo && x <= hi) {
        r = TRUE;
    }
    return r;
}

void PocketMenu::actionUseCarpet() {
    if (!PocketMenu_CanEditRoom()) {
        PocketMenu_ReturnToIdle(this);
        PocketMenu_ShowMessage(this, 23, 0xff, 1);
    } else {
    u16 v0;
    volatile u16 v1;
    u32 k = actionTarget;
    v0 = PocketMenu_GetItem(this, k);
    requestCameraPop();
    v1 = *(u16 *)RoomWallFloor_SetCarpet(&v0, 0, 1, 1);
    BOOL r = FALSE;
    u32 x = v1;
    u32 y = v1;
    if (y >= 0x1144 && x <= 0x1187) {
        r = TRUE;
    }
    if (r) {
        Shared_PocketMenu_SetSlotItem(this, k, x, 0);
    } else {
        PocketMenu_ClearSlotItem(this, k);
    }
    PocketMenu_ReturnToIdle(this);
    }
}

void PocketMenu::actionUseWallpaper() {
    if (!PocketMenu_CanEditRoom()) {
        PocketMenu_ReturnToIdle(this);
        PocketMenu_ShowMessage(this, 24, 0xff, 1);
    } else {
    u16 v0;
    volatile u16 v1;
    u32 k = actionTarget;
    v0 = PocketMenu_GetItem(this, k);
    requestCameraPop();
    v1 = *(u16 *)RoomWallFloor_SetWallpaper(&v0, 0, 1, 1);
    BOOL r = FALSE;
    u32 x = v1;
    u32 y = v1;
    if (y >= 0x1100 && x <= 0x1143) {
        r = TRUE;
    }
    if (r) {
        Shared_PocketMenu_SetSlotItem(this, k, x, 0);
    } else {
        PocketMenu_ClearSlotItem(this, k);
    }
    PocketMenu_ReturnToIdle(this);
    }
}

extern "C" void PocketMenu_AddRoomItemOptions(PocketMenu *self, s32 a) {
    if (PocketMenu_CanEditRoom()) {
        volatile u16 v = a;
        BOOL r = FALSE;
        u32 x = v;
        u32 y = v;
        if (y >= 0x1144 && x <= 0x1187) {
            r = TRUE;
        }
        if (r) {
            ChoiceIdList_Add(self->optionList, 0xc, 0x13);
        } else if (x >= 0x1100 && x <= 0x1143) {
            ChoiceIdList_Add(self->optionList, 0xb, 0x12);
        }
    }
}

extern "C" s32 PocketMenu_RequestDropIndoor(PocketMenu *self, s32 a) {
    u16 in = a;
    u16 v;
    u32 out;
    Item_ToPlacedForm(&v, &in, 0);
    if (Item_IsFurniture(&v)) {
        switch (FtrMgr_FindPlacementForPlayer(&out, &v, 1)) {
        case 0:
            PocketMenu_ReturnToIdle(self);
            PocketMenu_ShowMessage(self, 3, 0xff, 0);
            Snd_PlaySe(0x73);
            return 0;
        case 1:
            PocketMenu_ReturnToIdle(self);
            PocketMenu_ShowMessage(self, 5, 0xff, 1);
            Snd_PlaySe(0x73);
            return 0;
        case 2:
            PocketMenu_ReturnToIdle(self);
            PocketMenu_ShowMessage(self, 3, 0xff, 0);
            Snd_PlaySe(0x73);
            return 0;
        default:
            FtrMgr_SpawnFromArg(out);
            break;
        }
    } else {
    self->fieldRequest = FieldAction_RequestDrop(gCommManager->myAid, a);
    if (self->fieldRequest == -1) {
        PocketMenu_ReturnToIdle(self);
        PocketMenu_ShowMessage(self, 3, 0xff, 0);
        Snd_PlaySe(0x73);
        return 0;
    }
    return 2;
    }
    return 1;
}

extern "C" BOOL PocketMenu_CanEditRoom() {
    CommManager *g = gCommManager;
    if (g->isOnline()) {
        if (g->myAid != 0 || Room_CountOccupants() > 1) {
            return FALSE;
        }
    } else if (Room_CountOccupants() > 1) {
        return FALSE;
    }
    return TRUE;
}

