#include "types.h"
#include "item/ItemId.h"
#include "game/Unk_02034250_Id.h"
#include "net/CommManager.h"
#include "room/HouseData.h"
#include "room/HouseRoom.h"
#include "player/PlayerData.h"
#include "save/SaveData.h"
#include "proto/main/unk_02034048.h"
#include "proto/main/unk_02097444.h"
#include "proto/ov004/unk_ov004_0222a500.h"

ItemId::ItemId() { id = 0xfff1; }


extern "C" {
extern u8 gFieldSceneKind;
extern CommManager *gCommManager;

s32 Item_SetDesign(u16 *out, s32 a, s32 b);
s32 Scene_GetCurrent();
BOOL SceneId_IsHouseRoom(s32 a);

}

extern SaveData gSaveData;
extern ItemId sRoomWallFloorNoItem;
extern ItemId sSceneWallpapers[0x33];
extern ItemId sSceneCarpets[0x33];

static inline BOOL Unk_020341c0_IsOne(u8 v) { return v == 1 ? TRUE : FALSE; }


struct RoomWallFloorPacket {
    u16 item;
    u16 id : 6;
    u16 f6 : 1;
    u16 f7 : 1;
    u16 f8 : 1;
};

extern "C" void RoomWallFloor_MakeDesignItem(u16 *out, s32 a) {
    u32 x = a & 7;
    u32 y = 0;
    PlayerData *p = PlayerData_GetCurrent();
    if (p) {
        y = PlayerDataArray_FindById(gSaveData.players, (u16 *)p->getPlayerId()) & 3;
    }
    Item_SetDesign(out, y, x);
}

extern "C" void RoomWallFloor_Send(u16 *id, s32 a, s32 b, s32 c) {
    if (gCommManager->isOnline()) {
        Unk_02034320_Pkt pkt;
        pkt.a = *id;
        pkt.b = (pkt.b & ~0x3f) | (Scene_GetCurrent() & 0x3f);
        pkt.b = (pkt.b & ~0x40) | ((b & 1) << 6);
        pkt.b = (pkt.b & ~0x80) | (((u16)a & 1) << 7);
        pkt.b = (pkt.b & ~0x100) | ((c & 1) << 8);
        CommManager *obj = gCommManager;
        obj->beginRecord();
        obj->writeRecord((u8 *)(&pkt), 4);
        obj->endRecord(0x14, 4);
    }
}

extern "C" void *RoomWallFloor_SetWallpaper(u16 *id, s32 a, s32 b, s32 c) {
    u16 t = *id;
    void *r;
    if (Unk_020341c0_IsOne(gFieldSceneKind)) {
        r = RoomShell_SetWallpaper(&t, a, b);
        if (c != 0) {
            RoomWallFloor_Send(&t, a, 1, b);
        }
        return r;
    }
    return &sRoomWallFloorNoItem.id;
}

extern "C" void *RoomWallFloor_SetWallpaperDesign(s32 a, s32 b, s32 c, s32 d) {
    u16 id;
    RoomWallFloor_MakeDesignItem(&id, a);
    return RoomWallFloor_SetWallpaper(&id, b, c, d);
}

extern "C" void *RoomWallFloor_SetCarpet(u16 *id, s32 a, s32 b, s32 c) {
    u16 t = *id;
    void *r;
    if (Unk_020341c0_IsOne(gFieldSceneKind)) {
        r = RoomShell_SetCarpet(&t, a, b);
        if (c != 0) {
            RoomWallFloor_Send(&t, a, 0, b);
        }
        return r;
    }
    return &sRoomWallFloorNoItem.id;
}

extern "C" void *RoomWallFloor_SetCarpetDesign(s32 a, s32 b, s32 c, s32 d) {
    u16 id;
    RoomWallFloor_MakeDesignItem(&id, a);
    return RoomWallFloor_SetCarpet(&id, b, c, d);
}

extern "C" BOOL RoomWallFloor_RestoreWallpaper(s32 a) {
    if (Unk_020341c0_IsOne(gFieldSceneKind)) {
        RoomWallFloor_SetWallpaper(RoomShell_GetPrevWallpaper(), 0, 0, a);
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL RoomWallFloor_RestoreCarpet(s32 a) {
    if (Unk_020341c0_IsOne(gFieldSceneKind)) {
        RoomWallFloor_SetCarpet((u16 *)RoomShell_GetPrevCarpet(), 0, 0, a);
        return TRUE;
    }
    return FALSE;
}

extern "C" void RoomWallFloor_Set(u16 *a, s32 b, s32 c, s32 d, u8 e)
{
    if (c != 0) {
        RoomWallFloor_SetWallpaper(a, b, d, e);
    } else {
        RoomWallFloor_SetCarpet(a, b, d, e);
    }
}

extern "C" void RoomWallFloor_ClearScenes()
{
    u32 i;
    for (i = 0; i < 0x33; i++) {
        sSceneCarpets[i].id = 0xfff1;
        sSceneWallpapers[i].id = sSceneCarpets[i].id;
    }
}

extern "C" BOOL RoomWallFloor_SetSceneWallpaper(u32 i, u16 *v)
{
    if (i < 0x33) {
        sSceneWallpapers[i].id = *v;
        return TRUE;
    }
    return FALSE;
}

extern "C" u16 *RoomWallFloor_GetSceneWallpaper(u32 i)
{
    if (i < 0x33) {
        return &sSceneWallpapers[i].id;
    }
    return &sRoomWallFloorNoItem.id;
}

extern "C" BOOL RoomWallFloor_SetSceneCarpet(u32 i, u16 *v)
{
    if (i < 0x33) {
        sSceneCarpets[i].id = *v;
        return TRUE;
    }
    return FALSE;
}

extern "C" u16 *RoomWallFloor_GetSceneCarpet(u32 i)
{
    if (i < 0x33) {
        return &sSceneCarpets[i].id;
    }
    return &sRoomWallFloorNoItem.id;
}

extern "C" void RoomWallFloor_ApplyRecv(RoomWallFloorPacket *p)
{
    u16 tmp = p->item;
    u8 id = p->id;
    u32 f7 = p->f7;
    BOOL f6;
    if (p->f6 != 0) {
        f6 = TRUE;
    } else {
        f6 = FALSE;
    }
    s32 f8;
    if (p->f8 != 0) {
        f8 = 1;
    } else {
        f8 = 0;
    }
    if (p->id == Scene_GetCurrent()) {
        RoomWallFloor_Set(&tmp, f7, f6, f8, 0);
    } else if (SceneId_IsHouseRoom(id)) {
        HouseRoom *r = ((HouseData *)gSaveData.house)->getRoomForScene(id);
        if (r != NULL) {
            if (f6) {
                r->setWallpaper(&tmp, f7);
                RoomWallFloor_SetSceneWallpaper(id, &tmp);
            } else {
                r->setCarpet(&tmp, f7);
                RoomWallFloor_SetSceneCarpet(id, &tmp);
            }
        }
    } else if (f6) {
        RoomWallFloor_SetSceneWallpaper(id, &tmp);
    } else {
        RoomWallFloor_SetSceneCarpet(id, &tmp);
    }
}

ItemId sRoomWallFloorNoItem;
ItemId sSceneWallpapers[0x33];
ItemId sSceneCarpets[0x33];
