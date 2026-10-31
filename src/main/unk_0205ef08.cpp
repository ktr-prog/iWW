#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/Mtx43.h"
#include "game/GroundInfo.h"
#include "player/FishBobberStates.h"
#include "net/CommManager.h"
#include "sys/Heap.h"
#include "player/PlayerPaletteRef.h"
#include "proto/autoload_2/unk_020e7500.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205ef08.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_020a427c.h"
#include "proto/ov003/unk_ov003_0221ffb8.h"
#include "proto/main/unk_0204cc1c.h"


extern "C" {
extern CommManager *gCommManager;

BOOL SceneId_IsTown(u32 v);
s32 _s32_div_f(s32 a, s32 b);
}

struct PlayerPalettePool {
    u8 *buffers[4];
    PlayerPalettePool();
    ~PlayerPalettePool();
};

PlayerPalettePool sPlayerPalettePool;
char sPlayerPalettePathBuf[0x14];


extern "C" BOOL Fishing_StepArc(VecFx32 *a, s32 k, VecFx32 *b, s32 *c, u8 flag)
{
    s32 m, n, d, r1, r2;
    if (flag) {
        m = 0xccd;
        n = 5;
    } else {
        m = 0xccd;
        n = 0xa;
    }
    d = _s32_div_f(0x1000, n);
    r1 = Math_ApproachS32(&b->x, a->x, d, m, 0x19a);
    r2 = r1 + Math_ApproachS32(&b->z, a->z, d, m, 0x19a);
    if (*c < 0 && flag) {
        Math_ApproachS32(&b->y, a->y, d, 0xccd, 0x52);
    } else {
        b->y += *c;
        *c -= k;
    }
    return r2 == 0 ? TRUE : FALSE;
}

extern "C" BOOL ItemSync_Apply(u8 *p)
{
    struct {
        u8 t[2];
        u16 h[2];
    } l;
    BlockMap *o;
    BOOL r6;
    s32 x, y;
    u16 id = NetBuf_ReadU16(p);
    CommRecord_UnpackSource(p + 2, &l.t[0], &l.t[1]);
    r6 = l.t[1] ? TRUE : FALSE;
    x = *(s8 *)(p + 3);
    y = *(s8 *)(p + 4);
    if (SceneId_IsTown(l.t[0])) {
        o = TownBlockMap_Get();
        if (o != 0) {
            l.h[0] = id;
            BlockMap_SetItemAtUnit(o, &l.h[0], x, y, 0);
            if (r6) {
                BlockMap_SetBuriedAtUnit(o, x, y);
            } else {
                BlockMap_ClearBuriedAtUnit(o, x, y);
            }
            return TRUE;
        }
    } else {
        o = HouseRoomMaps_GetForScene(l.t[0]);
        if (o != 0) {
            l.h[1] = id;
            BlockMap_SetItemAtUnit(o, &l.h[1], x, y, 0);
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void ItemSync_ApplyAndBroadcast(u8 *p)
{
    if (ItemSync_Apply(p)) {
        if (gCommManager->isOnline()) {
            CommManager *q = gCommManager;
            q->beginRecord();
            q->writeRecord(p, 5);
            q->endRecord(0x12, 4);
        }
    }
}

extern "C" void ItemSync_SetAtUnit(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    u8 buf[5];
    NetBuf_WriteU16(buf, d);
    CommRecord_PackSource(buf + 2, c, e ? 1 : 0);
    buf[3] = a;
    buf[4] = b;
    if (NetArea_IsLocalOwner()) {
        ItemSync_ApplyAndBroadcast(buf);
    } else {
        CommManager *q = gCommManager;
        q->beginRecord();
        q->writeRecord(buf, 5);
        q->endRecord(0x13, 6);
    }
}

extern "C" void PlayerPalettePool_Create(Heap *parent)
{
    PlayerPaletteHeap_Create(parent);
    PlayerPalettePool_AllocBuffers(sPlayerPalettePool.buffers);
    if (gPlayerPaletteHeap) {
        static_cast<Heap *>(gPlayerPaletteHeap)->adjust();
    }
}

extern "C" void PlayerPalettePool_Destroy()
{
    PlayerPalettePool_FreeBuffers(sPlayerPalettePool.buffers);
    PlayerPaletteHeap_Destroy();
}

char *PlayerPalette_GetPath(u32 x)
{
    Str_SPrintf(sPlayerPalettePathBuf, "/PPal/%d/%d.nsbtx", x >> 5, x);
    return sPlayerPalettePathBuf;
}

extern "C" s32 PlayerPalette_GetSkinSize()
{
    return 0xe4;
}

extern "C" s32 PlayerPalette_GetHairSize()
{
    return 0xd4;
}

extern "C" s32 PlayerPalette_GetSlotSize()
{
    s32 a = PlayerPalette_GetSkinSize();
    return a + PlayerPalette_GetHairSize();
}

PlayerPalettePool::PlayerPalettePool() {}

PlayerPalettePool::~PlayerPalettePool() {}

extern "C" void PlayerPalettePool_AllocBuffers(u8 **out)
{
    Heap *h = static_cast<Heap *>(gPlayerPaletteHeap);
    u32 n = gCommManager->memberCount;
    u32 i;
    for (i = 0; i < n; i++) {
        out[i] = static_cast<u8 *>(Heap_AllocAligned(h, PlayerPalette_GetSlotSize(), 4));
    }
}

extern "C" void PlayerPalettePool_FreeBuffers(u8 **a)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        a[i] = NULL;
    }
    if (gPlayerPaletteHeap) {
        static_cast<Heap *>(gPlayerPaletteHeap)->freeAll();
    }
}

extern "C" u8 *PlayerPalettePool_GetBuffer(u8 **a, u32 i)
{
    return a[i];
}

PlayerPaletteRef::PlayerPaletteRef()
{
    slot = 4;
}

PlayerPaletteRef::~PlayerPaletteRef()
{
}

extern "C" void PlayerPaletteRef_Assign(u8 *p, u8 v)
{
    PlayerPaletteRef_SetSlot(p, v);
}

extern "C" void PlayerPaletteRef_SetSlot(u8 *p, u8 v)
{
    *p = v;
}

extern "C" u8 *PlayerPaletteRef_GetSkin(u8 *p)
{
    return PlayerPalettePool_GetBuffer(sPlayerPalettePool.buffers, *p);
}

extern "C" u8 *PlayerPaletteRef_GetHair(u8 *p)
{
    u8 *a = PlayerPaletteRef_GetSkin(p);
    return a + PlayerPalette_GetSkinSize();
}

extern "C" void PlayerPaletteRef_LoadSkin(u8 *x, u32 y) {
    u8 *dst = PlayerPaletteRef_GetSkin(x);
    const char *path = PlayerPalette_GetPath(y);
    File_LoadToBuffer(path, dst, PlayerPalette_GetSkinSize());
}

extern "C" void PlayerPaletteRef_LoadHair(u8 *x, u32 y) {
    u8 *dst = PlayerPaletteRef_GetHair(x);
    const char *path = PlayerPalette_GetPath(y);
    File_LoadToBuffer(path, dst, PlayerPalette_GetHairSize());
}

