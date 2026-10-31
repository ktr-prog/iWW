#include "types.h"
#include "host_labels.h"
#include "nitro/fs.h"
#include "net/CommManager.h"
#include "npc/VillagerState.h"
#include "npc/ErrandRecord.h"
#include "npc/VillagerMemory.h"
#include "save/VillagerData.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "save/BbsPost.h"
#include "npc/VillagerStateTable.h"
#include "save/BbsBoard.h"
#include "talk/MsgString.h"
#include "talk/EncodedString.h"
#include "talk/EncodedString192.h"
#include "talk/EncodedString41.h"
#include "ui/LabelString.h"
#include "field/FieldAction.h"






struct VillagerShirtRecvStackPad {
    s32 v[1];
    VillagerShirtRecvStackPad() {}
    ~VillagerShirtRecvStackPad() {}
};

#include "net/FriendEntry.h"
#include "net/DwcFriendControl.h"
#include "save/SaveManager.h"

struct VillagerSyncLocals {
    u8 b;
    u16 h;
};

struct OverlayHandleView {
    s32 overlayId;
    u8 isLoading;
    u8 pad[3];
    FSOverlayInfo info;
};

struct Unk_02076fc8_D {
    u8 a, b, c;
    u8 pad;
};


class EncodedStringBase;






class MsgString193 : public MsgString {
public:
    MsgString193();
    virtual ~MsgString193();
    virtual u32 capacity();
    virtual u8 *data();

    u8 text[0xc1];
};






#include "sys/OverlayHandle.h"
#include "game/NibblePair.h"
#include "gfx/VecFx32.h"
#include "player/PlayerData.h"
#include "save/TownExchangeRecord.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/autoload_2/unk_02119f84.h"
#include "proto/autoload_2/unk_0211a258.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/main/unk_02038474.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_0203eb60.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_020514a4.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205ef08.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206f804.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_02082d74.h"
#include "proto/main/unk_0208f0b0.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_0209c390.h"
#include "proto/main/unk_0209c4a8.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020a6388.h"
#include "proto/main/unk_020a65fc.h"
#include "proto/main/unk_020a6914.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov003/unk_ov003_02225800.h"
#include "proto/ov003/unk_ov003_0222e5e0.h"
#include "save/TownCompress.h"
#include "proto/main/unk_0204cc1c.h"

namespace n7 {

extern "C" {
extern CommManager *gCommManager;
}
extern "C" {
extern void *sSpNpcAnimHeapPool[];
}
extern "C" {
extern void *sVillagerAnimHeapPool[];
}
extern "C" {
extern void *sNpcTexPatBufPool[];
}
extern "C" {
extern u8 gFieldSceneKind;
}
extern "C" {
extern BlockMap *gSceneBlockMap;
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
void *SpNpcAnimHeapPool_Get(void **, s32);
}
extern "C" {
void *VillagerAnimHeapPool_Get(void **, s32);
}
extern "C" {
void *NpcTexPatBufPool_Get(void **, s32);
}
extern "C" {
void SpNpcAnimHeapPool_Free(void **);
}
extern "C" {
void SpNpcAnimHeapPool_Alloc(void **);
}
extern "C" {
void VillagerAnimHeapPool_Free(void **);
}
extern "C" {
void VillagerAnimHeapPool_Alloc(void **);
}
extern "C" {
void NpcTexPatBufPool_Free(void **);
}
extern "C" {
void NpcTexPatBufPool_Alloc(void **);
}
extern "C" {
s32 Town_GetMaxOutdoorVillagers();
}
extern "C" {
s32 Scene_GetCurrent();
}
extern "C" {
s32 Scene_GetMaxCharacters(s32);
}
extern "C" {
s32 Scene_GetMaxPlayers(s32);
}
extern "C" {
}
extern "C" {
}
extern "C" {
BOOL func_0204e418(void *, s32, s32);
}
extern "C" {
BOOL Item_IsNormalItem(void *);
}
extern "C" {
BOOL Field_IsUnitOccupied(s32, s32);
}
extern "C" {
s32 Field_FindPlayerAtUnit(s32, s32);
}
extern "C" {
BOOL TownMap_FindBuildingAbove(s32, s32, s32, s32 *, s32 *);
}
extern "C" {
BOOL TownMap_IsUnitWalkable(s32, s32, void *);
}
extern "C" {
BOOL Item_IsFurniture(u16 *);
}
extern "C" {
BOOL Item_IsTreeStage0(void *);
}
extern "C" {
struct VillagerStateTable *VillagerStates_Get();
}
extern "C" {
void *VillagerState_GetTalkRepeat(void *);
}
extern "C" {
s32 TalkRepeat_Reset(void *);
}
extern "C" {
s32 VillagerStateTable_ResetRuntime(void *);
}
extern "C" {
s32 VillagerStateTable_Destroy(void *);
}
extern "C" {
s32 VillagerStateTable_Init(void *);
}
extern "C" {
void *func_020805c4(void *);
}
extern "C" {
BOOL func_020030b4(void *);
}
extern "C" {
s32 Villager_GetResidentStatus(void *);
}
extern "C" {
s32 Villager_PickShownFurniture(void *);
}
extern "C" {
VillagerMemory *Villager_GetMemory(VillagerMemory *, u32);
}
extern "C" {
BOOL VillagerMemory_IsUsed(void *);
}
extern "C" {
void func_02080a88(void *);
}
extern "C" {
void func_02080a54(void *);
}
extern "C" {
void func_02080a18(void *);
}
extern "C" {
void func_020809dc(void *);
}
extern "C" {
void func_020809a0(void *);
}
extern "C" {
void func_02080964(void *);
}
extern "C" {
void func_02080930(void *);
}
extern "C" {
void func_02080078(void *, s32);
}
extern "C" {
void func_0207ff14(void *, s32);
}
extern "C" {
void *SpNpcAnimHeapRef_GetHeap(s32 *p);
}
extern "C" {
void SpNpcAnimHeapRef_Assign(s32 *p, s32 x);
}
extern "C" {
void SpNpcAnimHeapRef_Deinit();
}
extern "C" {
void SpNpcAnimHeapRef_Init(s32 *p);
}
extern "C" {
void *VillagerAnimHeapRef_GetHeap(s32 *p);
}
extern "C" {
void VillagerAnimHeapRef_Assign(s32 *p, s32 x);
}
extern "C" {
void VillagerAnimHeapRef_Deinit();
}
extern "C" {
void VillagerAnimHeapRef_Init(s32 *p);
}
extern "C" {
void *NpcTexPatBufRef_GetBuffer(s32 *p);
}
extern "C" {
void NpcTexPatBufRef_LoadFile(s32 *p, void *dst);
}
extern "C" {
void NpcTexPatBufRef_Assign(s32 *p, s32 v);
}
extern "C" {
void NpcTexPatBufRef_Set(s32 *p, s32 v);
}


static inline BOOL Unk_02077d58_IsZero(u8 v)
{
    return v == 0 ? TRUE : FALSE;
}extern "C" {
void SpNpcAnimHeaps_Create(void *);
}
extern "C" {
void VillagerAnimHeaps_Destroy();
}
extern "C" {
void NpcTexPatBufs_Destroy();
}
extern "C" {
static inline s32 Unk_02077d58_Count()
{
    s32 t;
    if (Unk_02077d58_IsZero(gFieldSceneKind)) {
        t = Town_GetMaxOutdoorVillagers();
    } else {
        t = Scene_GetMaxCharacters(Scene_GetCurrent());
        t -= Scene_GetMaxPlayers(Scene_GetCurrent());
    }
    return t;
}
}
extern "C" {
void NpcTexPatBufs_Create(void *);
}
extern "C" {
void VillagerAnimHeaps_Create(void *);
}
extern "C" {
void SpNpcAnimHeaps_Create(void *);
}
extern "C" {
static inline BOOL Unk_02077f68_R(u16 *p, u32 lo, u32 hi)
{
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}
}
extern "C" {
static inline BOOL Unk_02077f68_C2(u16 *p)
{
    BOOL k2 = TRUE, k1 = TRUE;
    u32 v = *p;
    if (v != 0x25 && v != 0x5c) k1 = FALSE;
    if (!k1) {
        if (v != 0xc7) k2 = FALSE;
    }
    return k2;
}
}
extern "C" {
static inline BOOL Unk_02077f68_C9(u16 *p)
{
    BOOL h = TRUE, g = TRUE, f = TRUE, e = TRUE, d = TRUE, cc = TRUE, b = TRUE, a = FALSE;
    u32 v = *p;
    if (v <= 5) a = TRUE;
    if (!a) {
        if (v < 6 || v > 11) b = FALSE;
    }
    if (!b) {
        if (v < 12 || v > 17) cc = FALSE;
    }
    if (!cc) {
        if ((v < 18 || v > 25) && v != 0x1c) d = FALSE;
    }
    if (!d) {
        if ((v < 0x8a || v > 0x8f) && (v < 0x90 || v > 0x95) && (v < 0x96 || v > 0x9b) && (v < 0x9c || v > 0xa3) && v != 0xa5) e = FALSE;
    }
    if (!e) {
        if (v != 0x1a) f = FALSE;
    }
    if (!f) {
        if (v != 0xa4) g = FALSE;
    }
    if (!g) {
        if (v != 0x1d) h = FALSE;
    }
    return h;
}
}


extern "C" void CommVillager_PackHeader(u8 *p, s32 a, s32 b)
{
    *p = ((a << 4) & 0xf0) | (b & 0xf);
}
extern "C" void CommVillager_UnpackHeader(s32 *a, s32 *b, u8 *p)
{
    *a = (*p >> 4) & 0xf;
    *b = *p & 0xf;
}
extern "C" void CommSend_VillagerMemoryInit(s32 a, s32 b)
{
    u8 buf;
    if (gCommManager->isOnline()) {
        CommVillager_PackHeader(&buf, a, b);
        CommManager *t = gCommManager;
        t->beginRecord();
        t->writeRecord((u8 *)(&buf), 1);
        t->endRecord(0x36, 4);
    }
}
}

namespace n6 {
extern "C" {
void MI_CpuCopy8(const void *src, void *dst, u32 n);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
u32 Villager_GetIndex(void *villager);
}
extern "C" {
BOOL SaveVillagers_IsValidIndex(u32 a);
}
extern "C" {
void *__cxa_vec_ctor(void *, u32, u32, void *(*)(void *), void *(*)(void *));
}
extern "C" {
void __cxa_vec_cleanup(void *, u32, u32, void *(*)(void *));
}
extern "C" {
}
extern "C" {
extern CommManager *gCommManager;
}


static inline BOOL R1(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}



extern "C" void VillagerSync_MemoryInit(void *villager, u32 b) {
    if (gCommManager->isOnline()) {
        u32 a = Villager_GetIndex(villager);
        if (SaveVillagers_IsValidIndex(a)) {
            CommSend_VillagerMemoryInit(a, b);
        }
    }
}

extern "C" void CommSend_VillagerMemorySetPlayer(u32 a, u32 b) {
    if (gCommManager->isOnline()) {
        u8 buf[1];
        CommVillager_PackHeader(buf, a, b);
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord((u8 *)(buf), 1);
        g->endRecord(0x37, 4);
    }
}

extern "C" void VillagerSync_MemorySetPlayer(void *villager, u32 b) {
    if (gCommManager->isOnline()) {
        u32 a = Villager_GetIndex(villager);
        if (SaveVillagers_IsValidIndex(a)) {
            CommSend_VillagerMemorySetPlayer(a, b);
        }
    }
}

extern "C" void CommSend_VillagerImpression(u32 a, u32 b, u32 c) {
    if (gCommManager->isOnline()) {
        u8 buf[1];
        CommVillager_PackHeader(buf, a, b);
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord((u8 *)(buf), 1);
        g->writeRecord((u8 *)(&c), 1);
        g->endRecord(0x38, 4);
    }
}

extern "C" void VillagerSync_Impression(void *villager, u32 b, u32 c) {
    if (gCommManager->isOnline()) {
        u32 a = Villager_GetIndex(villager);
        if (SaveVillagers_IsValidIndex(a)) {
            CommSend_VillagerImpression(a, b, c);
        }
    }
}

extern "C" void CommSend_VillagerFriendship(u32 a, u32 b, u32 c) {
    if (gCommManager->isOnline()) {
        u8 buf[1];
        CommVillager_PackHeader(buf, a, b);
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord((u8 *)(buf), 1);
        g->writeRecord((u8 *)(&c), 1);
        g->endRecord(0x39, 4);
    }
}

extern "C" void VillagerSync_Friendship(void *villager, u32 b, u32 c) {
    if (gCommManager->isOnline()) {
        u32 a = Villager_GetIndex(villager);
        if (SaveVillagers_IsValidIndex(a)) {
            CommSend_VillagerFriendship(a, b, c);
        }
    }
}

extern "C" void CommVillager_PackReceivedItem(u8 *out, s32 a, s32 b, u16 *c) {
    CommVillager_PackHeader(out + 2, a, b);
    NetBuf_WriteU16(out, *c);
}

extern "C" void CommVillager_UnpackReceivedItem(s32 *o0, s32 *o1, u16 *o2, u8 *src) {
    CommVillager_UnpackHeader(o0, o1, src + 2);
    *o2 = NetBuf_ReadU16(src);
}

extern "C" void CommSend_VillagerReceivedItem(u32 a, u32 b, u16 *c) {
    if (gCommManager->isOnline()) {
        u8 buf[3];
        CommVillager_PackReceivedItem(buf, a, b, c);
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord((u8 *)(buf), 3);
        g->endRecord(0x3e, 4);
    }
}

extern "C" void VillagerSync_ReceivedItem(void *villager, u32 b, u16 *c) {
    if (gCommManager->isOnline()) {
        u32 a = Villager_GetIndex(villager);
        if (SaveVillagers_IsValidIndex(a)) {
            CommSend_VillagerReceivedItem(a, b, c);
        }
    }
}

extern "C" void CommVillager_PackAct3C(u8 *out, s32 a, s32 b, u32 c) {
    out[0] = ((a << 4) & 0xf0) | (b & 0xf);
    out[1] = c;
}

extern "C" void CommVillager_UnpackAct3C(s32 *o0, u8 *o1, u8 *o2, u8 *src) {
    *o0 = (src[0] >> 4) & 0xf;
    *o1 = src[0] & 0xf;
    *o2 = src[1];
}

extern "C" void CommSend_VillagerAct3C(u32 a, u32 b, u32 c) {
    if (gCommManager->isOnline()) {
        u8 buf[2];
        CommVillager_PackAct3C(buf, a, c, b);
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord((u8 *)(buf), 2);
        g->endRecord(0x3c, 4);
    }
}

extern "C" void VillagerSync_Act3C(void *villager, u32 b, u32 c) {
    if (gCommManager->isOnline()) {
        u32 a = Villager_GetIndex(villager);
        if (SaveVillagers_IsValidIndex(a)) {
            CommSend_VillagerAct3C(a, b, c);
        }
    }
}
extern "C" void VillagerSync_Act3C00(void *villager, u32 b) { VillagerSync_Act3C(villager, b, 0); }
extern "C" void VillagerSync_Act3C01(void *villager) { VillagerSync_Act3C(villager, 0, 1); }
extern "C" void VillagerSync_Act3C02(void *villager) { VillagerSync_Act3C(villager, 1, 2); }
extern "C" void VillagerSync_Act3C03(void *villager, u32 b) { VillagerSync_Act3C(villager, b, 3); }
extern "C" void VillagerSync_Act3C04(void *villager, u32 b) { VillagerSync_Act3C(villager, b, 4); }

extern "C" void VillagerSync_Act3C05(void *villager, u32 b) { VillagerSync_Act3C(villager, b, 5); }

extern "C" void CommVillager_PackAct3D(u8 *out, s32 a, u32 b, u16 *c, s32 d, u8 e) {
    out[2] = (d & 7) | (((a << 4) & 0xf0) | ((e & 1) << 3));
    out[3] = b;
    NetBuf_WriteU16(out, *c);
}

extern "C" void CommVillager_UnpackAct3D(s32 *o0, u8 *o1, u16 *o2, s32 *o3, u8 *o4, u8 *src) {
    *o0 = (src[2] >> 4) & 0xf;
    *o3 = src[2] & 7;
    *o4 = (src[2] >> 3) & 1;
    *o1 = src[3];
    *o2 = NetBuf_ReadU16(src);
}

extern "C" void CommSend_VillagerAct3D(u32 a, u32 b, u16 *c, u32 d, u8 e) {
    if (gCommManager->isOnline()) {
        u8 buf[4];
        CommVillager_PackAct3D(buf, a, b, c, d, e ? 1 : 0);
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord((u8 *)(buf), 4);
        g->endRecord(0x3d, 4);
    }
}

extern "C" void VillagerSync_Act3D(void *villager, u32 b, u16 *c, u32 d, u8 e) {
    if (gCommManager->isOnline()) {
        u32 a = Villager_GetIndex(villager);
        if (SaveVillagers_IsValidIndex(a)) {
            CommSend_VillagerAct3D(a, b, c, d, e);
        }
    }
}

extern "C" void CommSend_VillagerAct3F(u32 a, u16 *b) {
    if (gCommManager->isOnline()) {
        u8 buf[3];
        CommVillager_PackItem(buf, a, b);
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord((u8 *)(buf), 3);
        g->endRecord(0x3f, 4);
    }
}

extern "C" void VillagerSync_Act3F(void *villager, u16 *b) {
    if (gCommManager->isOnline()) {
        u32 a = Villager_GetIndex(villager);
        if (SaveVillagers_IsValidIndex(a)) {
            CommSend_VillagerAct3F(a, b);
        }
    }
}

extern "C" void CommVillager_PackItem(u8 *out, s32 a, u16 *b) {
    NetBuf_WriteU16(out, *b);
    out[2] = a;
}

extern "C" void CommVillager_UnpackItem(s32 *out, u16 *dst, u8 *src) {
    *out = src[2];
    *dst = NetBuf_ReadU16(src);
}

extern "C" void CommSend_VillagerShirt(u32 a, u16 *b) {
    if (gCommManager->isOnline()) {
        if (R1(b, 0x11a8, 0x12a7)) {
            u8 buf[3];
            CommVillager_PackItem(buf, a, b);
            CommManager *g = gCommManager;
            g->beginRecord();
            g->writeRecord((u8 *)(buf), 3);
            g->endRecord(0x3a, 4);
        }
    }
}

extern "C" void VillagerSync_Shirt(void *villager, u16 *b) {
    if (gCommManager->isOnline()) {
        u32 a = Villager_GetIndex(villager);
        if (SaveVillagers_IsValidIndex(a)) {
            CommSend_VillagerShirt(a, b);
        }
    }
}

extern "C" void CommVillager_PackItems(u8 *out, s32 a, u16 *src) {
    s32 i;
    for (i = 0; i < 4; i++) {
        NetBuf_WriteU16(out + i * 2, *src);
        src++;
    }
    out[8] = a;
}

extern "C" void CommVillager_UnpackItems(s32 *out, u16 *dst, u8 *src) {
    s32 i;
    *out = src[8];
    for (i = 0; i < 4; i++) {
        *dst = NetBuf_ReadU16(src + i * 2);
        dst++;
    }
}

extern "C" void CommSend_VillagerItems(u32 a, u16 *b) {
    if (gCommManager->isOnline() && b) {
        u8 buf[9];
        CommVillager_PackItems(buf, a, b);
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord((u8 *)(buf), 9);
        g->endRecord(0x3b, 4);
    }
}

extern "C" void VillagerSync_Items(void *villager, u16 *b) {
    if (gCommManager->isOnline()) {
        u32 a = Villager_GetIndex(villager);
        if (SaveVillagers_IsValidIndex(a)) {
            CommSend_VillagerItems(a, b);
        }
    }
}}

BbsPost::BbsPost() {
    using namespace n6;}

BbsPost::~BbsPost() {
    using namespace n6;}
namespace n6 {


extern "C" u8 *BbsPost_GetText(BbsPost *p) { return p->text; }}

void BbsPost::init(u8 *src) {
    using namespace n6;
    day = src[0];
    month = src[1];
    year = src[2];
    flags = 0;
    Mem_Clear(this, 0xc0);
}

u8 BbsPost::getDay() {
    using namespace n6; return day; }

u8 BbsPost::getMonth() {
    using namespace n6; return month; }

u8 BbsPost::getYear() {
    using namespace n6; return year; }

BOOL BbsPost::isRead(s32 i) {
    using namespace n6;
    if (i < 0 || i >= 4) return TRUE;
    if (flags & (1 << i)) return TRUE;
    return FALSE;
}

void BbsPost::setRead(s32 i) {
    using namespace n6;
    if (i >= 0 && i < 4) {
        flags |= (u8)(1 << i);
    }
}

BOOL BbsPost::isFreeText() {
    using namespace n6;
    if (flags & 0x10) return TRUE;
    return FALSE;
}


void BbsPost::markFreeText() {
    using namespace n6; flags |= 0x10; }

BbsBoard::BbsBoard() {
    using namespace n6;}


BbsBoard::~BbsBoard() {
    using namespace n6;}

BbsPost *BbsBoard::postAt(s32 idx) {
    using namespace n6; return &posts[idx]; }


BbsPost *BbsBoard::getPost(s32 idx) {
    using namespace n6; return postAt(idx); }


void BbsBoard::clear() {
    using namespace n6;
    postCount = 0;
    noticeId = 0;
}


void BbsBoard::reset() {
    using namespace n6;
    clear();
    Bbs_PostMsgToday(0, sBbsDefaultKey);
    Bbs_PostMsgToday(1, sBbsDefaultKey);
}


u8 BbsBoard::getPostCount() {
    using namespace n6; return postCount; }


BbsPost *BbsBoard::addPost() {
    using namespace n6;
    if (postCount < 15) {
        postCount++;
        return &posts[postCount - 1];
    } else {
        removePost(0);
        postCount = 15;
        return &posts[postCount - 1];
    }
}

u16 BbsBoard::getNoticeId() {
    using namespace n6; return noticeId; }


void BbsBoard::setNoticeId(u16 v) {
    using namespace n6; noticeId = v; }


void BbsBoard::removePost(s32 idx) {
    using namespace n6;
    s32 i;
    for (i = idx; i < postCount - 1; i++) {
        MI_CpuCopy8(&posts[i + 1], &posts[i], 0xc4);
    }
    postCount--;
}

MsgString193::MsgString193() {
    using namespace n6; clear(); }

MsgString193::~MsgString193() {
    using namespace n6;}

u32 MsgString193::capacity() {
    using namespace n6; return 0xc1; }


u8 *MsgString193::data() {
    using namespace n6; return text; }

namespace n5 {
struct Unk_02076f28_T;
extern "C" {
void MI_CpuCopy8(const void *, void *, u32);
}
extern "C" {
}
extern "C" {
}
extern "C" {
VillagerState *VillagerStates_GetEntry(u32 a);
}
extern "C" {
void VillagerState_SetPresence(VillagerState *e, u32 v);
}
extern "C" {
ErrandRecord *VillagerState_GetErrand(VillagerState *e);
}
extern "C" {
u32 VillagerState_GetPresence(VillagerState *e);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
extern CommManager *gCommManager;
}
extern "C" {
}
extern "C" {
}
extern "C" {
void FS_LoadOverlayImage(void *p);
}
extern "C" {
void *__cxa_vec_ctor(void *, u32, u32, void *(*)(void *), void *(*)(void *));
}
extern "C" {
void __cxa_vec_cleanup(void *, u32, u32, void *(*)(void *));
}
extern "C" {
void MI_CpuFill8(void *p, u32 v, u32 n);
}
extern "C" {
void Clock_GetDate(void *p);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
void *Msg_SkipLines(void *p, s32 i);
}
extern "C" {
}
extern "C" {
void func_020a791c(void *p);
}
extern "C" {
void func_020a78ac(void *p);
}
extern "C" {
u64 _ll_mul(u64 a, u64 b);
}
extern "C" {
FriendEntry *FriendList_GetEntries(FriendEntry *p);
}
extern "C" {
#define data_021e87d8 HOST_LABEL(u8 (*)[], data_021e87d8)
}
extern "C" {
extern u8 gU8None[];
}



struct Unk_02076f28_T {
    s32 a, b, c;
    ~Unk_02076f28_T() { ((DwcFriendData *)this)->~DwcFriendData(); }
};




extern "C" void Bbs_LoadMsg(MsgString *a, u32 b, const char *c) {
    volatile u8 v = *gU8None;
    v = (u8)b;
    MailText_LoadBbs(a, (u8 *)&v, c);
}}


EncodedString192::EncodedString192() {
    using namespace n5;}

EncodedString192::~EncodedString192() {
    using namespace n5;}

u32 EncodedString192::capacity() {
    using namespace n5; return 0xc0; }

u8 *EncodedString192::data() {
    using namespace n5; return text; }
namespace n5 {


extern "C" BOOL BbsPost_SetTextFromMsg(BbsPost *self, MsgString193 *r1) {
    LabelString o1;
    EncodedString41 o2;
    u8 *buf = BbsPost_GetText(self);
    s32 n = 0;
    s32 i = n;
    for (; i < 6; i++) {
        void *e = Msg_SkipLines(r1->text, i);
        if (e != NULL) {
            ((MsgString *)(&o1))->setLine((u8 *)(e));
            ((EncodedString *)(&o2))->fromMsgString((MsgString *)(&o1));
            StrBuf_GetBytes((StrBuf *)&o2, buf + n, 0x28);
            n = n + ((EncodedString41 *)(&o2))->getLength();
            buf[n] = 0x86;
            n = n + 1;
        } else {
            ((MsgString *)(&o1))->clear();
            buf[n] = 0x86;
            n++;
        }
    }
    return TRUE;
}

extern "C" void Bbs_PostMsgDated(u32 a, const char *b, u32 c, u32 d, u8 e) {
    MsgString193 o;
    u8 l[3];
    Bbs_LoadMsg(&o, a, b);
    BbsPost *r = ((BbsBoard *)(data_021e87d8))->addPost();
    l[2] = c;
    l[1] = d;
    l[0] = e;
    r->init(l);
    BbsPost_SetTextFromMsg(r, &o);
}

extern "C" void Bbs_PostMsgToday(u32 a, const char *b) {
    Unk_02076fc8_D d;
    Clock_GetDate(&d);
    Bbs_PostMsgDated(a, b, d.c, d.b, d.a);
}

extern "C" void Bbs_AddPost(void *dst) {
    u32 loc;
    BbsPost *r = ((BbsBoard *)(data_021e87d8))->addPost();
    Clock_GetDate(&loc);
    r->init((u8 *)(&loc));
    r->markFreeText();
    MI_CpuCopy8(dst, BbsPost_GetText(r), 0xc0);
}

extern "C" u8 Bbs_GetPostCount(void) { return ((BbsBoard *)(data_021e87d8))->getPostCount(); }

}
DwcFriendData::DwcFriendData() {}
DwcFriendData::~DwcFriendData() {}
namespace n5 {

extern "C" void *DwcFriendData_Copy(void *p, void *q) {
    MI_CpuCopy8(q, p, 12);
    return p;
}

extern "C" s32 DwcFriendData_Compare(void *self, Unk_02076f28_T *src) {
    Unk_02076f28_T t = *src;
    return Net_IsSameFriendData(self, &t);
}

extern "C" void DwcFriendData_Clear(void *p) { MI_CpuFill8(p, 0, 0xc); }

extern "C" BOOL DwcFriendData_IsValid(void *p) {
    if (Net_GetFriendDataType(p) != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL DwcFriendData_IsFriendKey(void *p) {
    if (Net_GetFriendDataType(p) == 2) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL DwcFriendData_FromCodeDigits(void *out, u8 *data, void *userData) {
    u8 tmp[12];
    u64 acc = 0;
    u64 i = 0;
    do {
        u64 m = _ll_mul(acc, 10);
        acc = m + (u32)data[i];
        i++;
    } while (i < 12);
    if (!Net_FriendKeyToFriendData(userData, tmp, acc)) {
        return FALSE;
    }
    MI_CpuCopy8(tmp, out, 12);
    return TRUE;
}

extern "C" BOOL DwcFriendData_ToCodeDigits(void *friendData, u8 *buf) {
    u64 v;
    s32 i;
    if (Net_GetFriendDataType(friendData) != 2) {
        return FALSE;
    }
    v = Net_GetFriendKey(friendData);
    for (i = 11; i >= 0; i--) {
        buf[i] = (u8)(v % 10);
        v = v / 10;
    }
    return TRUE;
}

extern "C" BOOL DwcFriendData_IsNotFriendKey(void *p) {
    if (DwcFriendData_IsFriendKey(p) == 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void *DwcFriendData_GetBytes(void *p) { return p; }

extern "C" void *FriendList_Construct(void *p) {
    __cxa_vec_ctor(p, 0x20, 0x1c, FriendEntry_Construct, FriendEntry_Destruct);
    return p;
}

extern "C" void *FriendList_Destruct(void *p) {
    __cxa_vec_cleanup(p, 0x20, 0x1c, FriendEntry_Destruct);
    return p;
}

extern "C" void FriendList_Clear(FriendEntry *base) {
    s32 i;
    for (i = 0; i < 0x20; i++) {
        FriendEntry_Clear(&base[i]);
    }
}

extern "C" FriendEntry *FriendList_GetEntries(FriendEntry *p) { return p; }

extern "C" void FriendList_Compact(FriendEntry *list) {
    FriendEntry *base = FriendList_GetEntries(list);
    s32 i, n;
    n = 0;
    i = n;
    for (; i < 0x20; i++) {
        FriendEntry *e = &base[i];
        if (DwcFriendData_IsValid(FriendEntry_GetFriendData(e))) {
            if (i != n) {
                FriendEntry_Copy(&base[n], e);
                FriendEntry_Clear(e);
            }
            n++;
        }
    }
}
extern "C" void FriendList_SetChecksum(u8 *p, u16 v) { ((FriendList *)p)->checksum = v; }

extern "C" u16 FriendList_GetChecksum(u8 *p) { return ((FriendList *)p)->checksum; }

extern "C" void *FriendEntry_Construct(void *p) {
    new (p) DwcFriendData();
    return p;
}

extern "C" void *FriendEntry_Destruct(void *p) {
    ((DwcFriendData *)p)->~DwcFriendData();
    return p;
}

extern "C" void *FriendEntry_Copy(void *p, void *q) {
    MI_CpuCopy8(q, p, 0x1c);
    return p;
}


extern "C" void FriendEntry_Clear(void *pp) {
    FriendEntry *p = (FriendEntry *)pp;
    DwcFriendData_Clear(p->friendData);
    Mem_Clear(p->playerName, 8);
    Mem_Clear(p->townName, 8);
}
extern "C" void *FriendEntry_GetFriendData(void *p) { return p; }
extern "C" u8 *FriendEntry_GetPlayerName(u8 *p) { return ((FriendEntry *)p)->playerName; }

extern "C" u8 *FriendEntry_GetTownName(u8 *p) { return ((FriendEntry *)p)->townName; }

extern "C" u8 *PlayerWifiData_Construct(u8 *p) {
    new (((PlayerWifiData *)p)->ownFriendData) DwcFriendData();
    return p;
}

extern "C" u8 *PlayerWifiData_Destruct(u8 *p) {
    ((DwcFriendData *)((PlayerWifiData *)p)->ownFriendData)->~DwcFriendData();
    return p;
}

extern "C" void PlayerWifiData_Create(u8 *p) {
    Net_CreateUserData(p, 0x41444d45);
    void *r = DwcFriendData_GetBytes(((PlayerWifiData *)p)->ownFriendData);
    Net_MakeOwnFriendData(p, r);
}
extern "C" s64 PlayerWifiData_GetFriendCode(void *p) { return Net_GetOwnFriendKey(p); }
extern "C" s32 PlayerWifiData_HasUserId(void *p) { return Net_HasWifiUserId(p); }

extern "C" s32 PlayerWifiData_IsConfigValid(void *p) { return Net_IsWifiConfigValid(p); }

extern "C" void *PlayerWifiData_GetDwcUserData(void *p) { return p; }

extern "C" u8 *PlayerWifiData_GetOwnFriendData(u8 *p) { return ((PlayerWifiData *)p)->ownFriendData; }

extern "C" void PlayerWifiData_SetChecksum(u8 *p, u16 v) { ((PlayerWifiData *)p)->checksum = v; }

extern "C" u16 PlayerWifiData_GetChecksum(u8 *p) { return ((PlayerWifiData *)p)->checksum; }

}
OverlayHandle::~OverlayHandle() {}
namespace n5 {

extern "C" void OverlayHandle_Unload(OverlayHandleView *s) {
    FS_EndOverlay(&s->info);
    s->overlayId = -1;
}

extern "C" void OverlayHandle_Load(OverlayHandleView *s, s32 v) {
    s->isLoading = 1;
    s->overlayId = v;
    OverlayMgr_GetInfo(&s->info, v);
    FS_LoadOverlayImage(&s->info);
    FS_StartOverlay(&s->info.header);
    s->isLoading = 0;
}

extern "C" s32 Comm_AidToPeerIndex(s32 x) {
    if (x >= Net_GetMyAid()) {
        x--;
    }
    return x;
}

extern "C" void CommPacket_SetAckHeader(u8 *p, s32 a) { *p = a & 3; }

extern "C" void CommPacket_SetHeader(u8 *p, s32 a, s32 b) { *p = ((b & 0x1f) << 2) | 0x80 | (a & 3); }

extern "C" BOOL CommPacket_IsControl(u8 *p) {
    if ((*p & 0x80) != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" u32 CommPacket_GetAck(u8 *p) { return *p & 3; }

extern "C" u32 CommPacket_GetType(u8 *p) { return (*p >> 2) & 0x1f; }

extern "C" void *NetHeap_Alloc(s32 a, s32 b) { return Heap_AllocAligned((Heap *)gNetHeap, a, b); }

extern "C" void NetHeap_Free(void *a) { Heap_Free(gNetHeap, a); }

extern "C" BOOL Comm_HasSendCredit(u32 mask) {
    s32 i = 3;
    CommManager *g = gCommManager;
    u32 one = 1;
    for (; i >= 0; i--) {
        if (!g->isSlotActive(i)) continue;
        if (g->isMyAid(i)) continue;
        u32 t = (u16)(one << i);
        t &= mask;
        if (t == 0) continue;
        if (g->getSendCredit(i)) continue;
        return FALSE;
    }
    return TRUE;
}

extern "C" BOOL Comm_HasSendCreditAll(void) { return Comm_HasSendCredit(0xf); }

extern "C" BOOL Comm_IsWifi(void) {
    s32 r = Net_GetMode();
    switch (r) {
    case 3:
    case 4:
        return TRUE;
    }
    return FALSE;
}

extern "C" void CommRecord_PackSource(u8 *p, s32 v, s32 w) { p[0] = ((w << 6) & 0xc0) | (v & 0x3f); }

extern "C" void CommRecord_UnpackSource(u8 *p, u8 *a, u8 *out) {
    if (out != NULL) {
        *out = ((u32)p[0] >> 6) & 3;
    }
    *a = p[0] & 0x3f;
}

extern "C" void NetBuf_Pack20(u8 *p, s32 v, u8 hi) {
    p[0] = ((hi << 4) & 0xf0) | ((v >> 16) & 0xf);
    p[1] = v >> 8;
    p[2] = v;
}

extern "C" void NetBuf_Unpack20(u8 *p, u32 *out, u8 *out2) {
    if (out2 != NULL) {
        *out2 = ((u32)p[0] >> 4) & 0xf;
    }
    *out = (p[2] & 0xff) | (((p[0] << 16) & 0xf0000) | ((p[1] << 8) & 0xff00));
}

extern "C" void NetBuf_PackPair20(u8 *p, s32 v, s32 x) {
    p[0] = v >> 8;
    p[1] = v;
    NetBuf_Pack20(p + 2, x, (u8)((v >> 16) & 0xf));
}

extern "C" void NetBuf_UnpackPair20(u8 *p, u32 *out, u32 *x) {
    u8 t;
    NetBuf_Unpack20(p + 2, x, &t);
    *out = (p[1] & 0xff) | (((t << 16) & 0xf0000) | ((p[0] << 8) & 0xff00));
}

extern "C" void NetBuf_PackTriple20(u8 *p, s32 a, s32 x, s32 y, u8 z) {
    NetBuf_PackPair20(p, a, x + 0x80000);
    NetBuf_Pack20(p + 5, y, z);
}

extern "C" void NetBuf_UnpackTriple20(u8 *p, u32 *out, s32 *x, u32 *y, u8 *z) {
    NetBuf_UnpackPair20(p, out, (u32 *)x);
    *x = *x - 0x80000;
    NetBuf_Unpack20(p + 5, y, z);
}

extern "C" void NetBuf_WriteS16B(void *dst, s16 v) { MI_CpuCopy8(&v, dst, 2); }

extern "C" s16 NetBuf_ReadS16B(void *src) {
    s16 v;
    MI_CpuCopy8(src, &v, 2);
    return v;
}

extern "C" void NetBuf_WriteS16(void *dst, s16 v) { MI_CpuCopy8(&v, dst, 2); }

extern "C" s16 NetBuf_ReadS16(void *src) {
    s16 v;
    MI_CpuCopy8(src, &v, 2);
    return v;
}

extern "C" void NetBuf_WriteU16(void *dst, u16 v) { MI_CpuCopy8(&v, dst, 2); }

extern "C" u16 NetBuf_ReadU16(void *src) {
    u16 v;
    MI_CpuCopy8(src, &v, 2);
    return v;
}

extern "C" void CommRecord_SetLength(void *dst, u16 v) { MI_CpuCopy8(&v, dst, 2); }

extern "C" u16 CommRecord_GetLength(void *src) {
    u16 v;
    MI_CpuCopy8(src, &v, 2);
    return v;
}

extern "C" void CommBlock_WriteAct00(void) {}

extern "C" void CommBlock_WriteAct01(void) {
    VillagerSyncLocals t;
    u32 v;
    VillagerSyncLocals *tp = &t;
    VillagerState *p;
    s32 i;
    CommManager *ctx;
    t.b = 3;
    i = 0;
    ctx = gCommManager;
    for (; i < 8; i++) {
        p = VillagerStates_GetEntry(i);
        if (p != NULL) {
            t.b = (u8)VillagerState_GetPresence(p);
        } else {
            t.b = 3;
        }
        ctx->appendControl(&t.b, 1);
        ctx->appendControl(VillagerState_GetErrand(p), 12);
        v = p->roomScore;
        ctx->appendControl(&v, 4);
        t.h = p->roomBonusFlags;
        ctx->appendControl(&t.h, 2);
    }
}

extern "C" void CommBlock_ReadAct00(void) {}

extern "C" void CommBlock_ReadAct01(u8 *buf) {
    VillagerSyncLocals t;
    ErrandRecord obj;
    u32 v;
    u32 z8 = 0, zc = 0, z10 = 0;
    VillagerSyncLocals *tp = &t;
    s32 i;
    t.b = 3;
    for (i = 0; i < 8; i++) {
        VillagerState *p = VillagerStates_GetEntry(i);
        t.b = 3;
        MI_CpuCopy8(buf, &t.b, 1);
        VillagerState_SetPresence(p, t.b);
        MI_CpuCopy8(buf + 1, &obj, 12);
        ErrandRecord *q = VillagerState_GetErrand(p);
        u32 a = obj.getKind();
        u16 *b = obj.getItem();
        q->start(a, b, z8);
        v = zc;
        MI_CpuCopy8(buf + 13, &v, 4);
        p->roomScore = v;
        t.h = z10;
        MI_CpuCopy8(buf + 17, &t.h, 2);
        p->roomBonusFlags = t.h;
        buf += 0x13;
    }
}

}

namespace n4 {
extern "C" {
extern CommManager *gCommManager;
}
extern "C" {
extern u8 gFieldSceneKind;
}
extern "C" {
extern void (*const sCommBlockWriters[])(u32);
}
extern "C" {
extern void (*const sCommBlockReaders[])(u8 *, u32);
}
extern "C" {
extern const u8 sCommSyncVarVarSizes[];
}
extern "C" {
extern const u16 sCommSyncVarVarOffsets[];
}
extern "C" {
extern void (*const sCommSyncVarInitHandlers[])(void *);
}
extern "C" {
extern void (*const sCommSyncVarPackHandlers[])(void *, void *, u32);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
void Shop_OnPurchaseAck(u32 a);
}
extern "C" {
void Shop_OnPurchaseRecord(void *p, u32 a);
}
extern "C" {
void PatternSrc_ApplyNetMove(void *p);
}
extern "C" {
void RoomWallFloor_ApplyRecv(void *p);
}
extern "C" {
}
extern "C" {
void MI_CpuFill8(void *p, u32 a, u32 b);
}
extern "C" {
void MI_CpuCopy8(const void *src, void *dst, u32 n);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
static inline BOOL Unk_02075e60_IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }
}


extern "C" s32 CommBlock_BuildPacket(u32 a) {
    struct { u16 len; u8 hdr[3]; } l;
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend() == 0) {
        return 0;
    }
    CommManager *g = gCommManager;
    g->clearControlLen();
    CommPacket_SetHeader(g->getSendBuf(4), 0, 0xd);
    g->setControlLen(1);
    s32 i = 0;
    goto test0;
loop0:
    {
        u32 s = g->getControlLen();
        u8 *dst = (u8 *)(g)->getSendBuf(4) + s;
        g->setControlLen(s + 3);
        sCommBlockWriters[i](a);
        u32 e = g->getControlLen();
        if (e <= s + 3) {
            g->setControlLen(s);
        } else {
            l.len = e - s - 3;
            MI_CpuCopy8(&l.len, l.hdr, 2);
            l.hdr[2] = i;
            MI_CpuCopy8(l.hdr, dst, 3);
        }
    }
    i++;
test0:
    if (i < 2) goto loop0;
    return 1;
}
extern "C" void CommBlock_ParseAll(u8 *p, u32 n) {
    struct { u8 id; u8 pad; u16 len; } h;
    u8 buf[3];
    while (n != 0) {
        MI_CpuCopy8(p, buf, 3);
        p += 3;
        n -= 3;
        MI_CpuCopy8(buf, &h.len, 2);
        MI_CpuCopy8(buf + 2, &h.id, 1);
        u32 len = h.len;
        u32 id = *(volatile u8 *)&h.id;
        sCommBlockReaders[id](p, len);
        p += len;
        n -= len;
    }
}
extern "C" u32 CommSyncVar_GetVarSize(u32 i) { return sCommSyncVarVarSizes[i]; }
extern "C" u32 CommSyncVar_GetVarOffset(u32 i) { return sCommSyncVarVarOffsets[i]; }
extern "C" void CommSyncVar_InitVillager0(void *a) { NpcNetRecord_InitVillagerVar(a, 0xc); }
extern "C" void CommSyncVar_InitVillager1(void *a) { NpcNetRecord_InitVillagerVar(a, 0xd); }
extern "C" void CommSyncVar_InitVillager2(void *a) { NpcNetRecord_InitVillagerVar(a, 0xe); }
extern "C" void CommSyncVar_InitVillager3(void *a) { NpcNetRecord_InitVillagerVar(a, 0xf); }
extern "C" void CommSyncVar_InitVillager4(void *a) { NpcNetRecord_InitVillagerVar(a, 0x10); }
extern "C" void CommSyncVar_InitVillager5(void *a) { NpcNetRecord_InitVillagerVar(a, 0x11); }
extern "C" void CommSyncVar_InitVillager6(void *a) { NpcNetRecord_InitVillagerVar(a, 0x12); }
extern "C" void CommSyncVar_InitVillager7(void *a) { NpcNetRecord_InitVillagerVar(a, 0x13); }
extern "C" void CommSyncVar_InitVar(u32 i) {
    void (*f)(void *) = sCommSyncVarInitHandlers[i];
    if (f) {
        void *o = gCommManager->getSyncVar(i);
        f(o);
    }
}
extern "C" void CommSyncVar_PackPos(u8 *a, s32 *b) { NetBuf_PackPair20(a, b[0], b[2]); }
extern "C" void CommSyncVar_PackPlayerPos0(u8 *a, s32 *b) { CommSyncVar_PackPos(a, b); }
extern "C" void CommSyncVar_PackPlayerPos1(u8 *a, s32 *b) { CommSyncVar_PackPos(a, b); }
extern "C" void CommSyncVar_PackPlayerPos2(u8 *a, s32 *b) { CommSyncVar_PackPos(a, b); }
extern "C" void CommSyncVar_PackPlayerPos3(u8 *a, s32 *b) { CommSyncVar_PackPos(a, b); }
extern "C" void CommSyncVar_PackAngle(void *a, s16 *b) { NetBuf_WriteS16B(a, *b); }
extern "C" void CommSyncVar_PackPlayerAngle0(void *a, s16 *b) { CommSyncVar_PackAngle(a, b); }
extern "C" void CommSyncVar_PackPlayerAngle1(void *a, s16 *b) { CommSyncVar_PackAngle(a, b); }
extern "C" void CommSyncVar_PackPlayerAngle2(void *a, s16 *b) { CommSyncVar_PackAngle(a, b); }
extern "C" void CommSyncVar_PackPlayerAngle3(void *a, s16 *b) { CommSyncVar_PackAngle(a, b); }
extern "C" void CommSyncVar_PackVar08(void *a) { PlayerActor_PackNetState(a, 0x8); }
extern "C" void CommSyncVar_PackVar09(void *a) { PlayerActor_PackNetState(a, 0x9); }
extern "C" void CommSyncVar_PackVar0A(void *a) { PlayerActor_PackNetState(a, 0xa); }
extern "C" void CommSyncVar_PackVar0B(void *a) { PlayerActor_PackNetState(a, 0xb); }
extern "C" void CommSyncVar_PackVillager0(void *a) { NpcNetRecord_PackVillager(a, 0xc); }
extern "C" void CommSyncVar_PackVillager1(void *a) { NpcNetRecord_PackVillager(a, 0xd); }
extern "C" void CommSyncVar_PackVillager2(void *a) { NpcNetRecord_PackVillager(a, 0xe); }
extern "C" void CommSyncVar_PackVillager3(void *a) { NpcNetRecord_PackVillager(a, 0xf); }
extern "C" void CommSyncVar_PackVillager4(void *a) { NpcNetRecord_PackVillager(a, 0x10); }
extern "C" void CommSyncVar_PackVillager5(void *a) { NpcNetRecord_PackVillager(a, 0x11); }
extern "C" void CommSyncVar_PackVillager6(void *a) { NpcNetRecord_PackVillager(a, 0x12); }
extern "C" void CommSyncVar_PackVillager7(void *a) { NpcNetRecord_PackVillager(a, 0x13); }
extern "C" void CommSyncVar_PackPlayerMsg0(u8 *a, ChatBalloon *b) { ChatBalloon_PackSyncVar(a, 0x14, b); }
extern "C" void CommSyncVar_PackPlayerMsg1(u8 *a, ChatBalloon *b) { ChatBalloon_PackSyncVar(a, 0x15, b); }
extern "C" void CommSyncVar_PackPlayerMsg2(u8 *a, ChatBalloon *b) { ChatBalloon_PackSyncVar(a, 0x16, b); }
extern "C" void CommSyncVar_PackPlayerMsg3(u8 *a, ChatBalloon *b) { ChatBalloon_PackSyncVar(a, 0x17, b); }
extern "C" void CommSyncVar_PackVar18(void *a, void *b) { InsectNetSync_PackVar(a, 0x18); }
extern "C" void CommSyncVar_PackVar19(void *a, void *b) { InsectNetSync_PackVar(a, 0x19); }
extern "C" void CommSyncVar_PackVar1A(void *a, void *b) { InsectNetSync_PackVar(a, 0x1a); }
extern "C" void CommSyncVar_PackVar1B(void *a, void *b) { InsectNetSync_PackVar(a, 0x1b); }
extern "C" void CommSyncVar_PackVar1C(void *a, void *b) { InsectNetSync_PackVar(a, 0x1c); }
extern "C" void CommSyncVar_PackVar1D(void *a, void *b) { InsectNetSync_PackVar(a, 0x1d); }
extern "C" void CommSyncVar_PackVar1E(void *a, void *b) { InsectNetSync_PackVar(a, 0x1e); }
extern "C" void CommSyncVar_PackVar1F(void *a, void *b) { InsectNetSync_PackVar(a, 0x1f); }
extern "C" void CommSyncVar_PackSpNpc00(void *a) { NpcNetRecord_PackSpNpc(a, 0x20); }
extern "C" void CommSyncVar_PackSpNpc01(void *a) { NpcNetRecord_PackSpNpc(a, 0x21); }
extern "C" void CommSyncVar_PackSpNpc02(void *a) { NpcNetRecord_PackSpNpc(a, 0x22); }
extern "C" void CommSyncVar_PackSpNpc03(void *a) { NpcNetRecord_PackSpNpc(a, 0x23); }
extern "C" void CommSyncVar_PackSpNpc04(void *a) { NpcNetRecord_PackSpNpc(a, 0x24); }
extern "C" void CommSyncVar_PackSpNpc05(void *a) { NpcNetRecord_PackSpNpc(a, 0x25); }
extern "C" void CommSyncVar_PackSpNpc06(void *a) { NpcNetRecord_PackSpNpc(a, 0x26); }
extern "C" void CommSyncVar_PackSpNpc07(void *a) { NpcNetRecord_PackSpNpc(a, 0x27); }
extern "C" void CommSyncVar_PackSpNpc08(void *a) { NpcNetRecord_PackSpNpc(a, 0x28); }
extern "C" void CommSyncVar_PackSpNpc09(void *a) { NpcNetRecord_PackSpNpc(a, 0x29); }
extern "C" void CommSyncVar_PackSpNpc0A(void *a) { NpcNetRecord_PackSpNpc(a, 0x2a); }
extern "C" void CommSyncVar_PackSpNpc0B(void *a) { NpcNetRecord_PackSpNpc(a, 0x2b); }
extern "C" void CommSyncVar_PackSpNpc0C(void *a) { NpcNetRecord_PackSpNpc(a, 0x2c); }
extern "C" void CommSyncVar_PackSpNpc0D(void *a) { NpcNetRecord_PackSpNpc(a, 0x2d); }
extern "C" void CommSyncVar_PackSpNpc0E(void *a) { NpcNetRecord_PackSpNpc(a, 0x2e); }
extern "C" void CommSyncVar_PackSpNpc0F(void *a) { NpcNetRecord_PackSpNpc(a, 0x2f); }
extern "C" void CommSyncVar_PackSpNpc10(void *a) { NpcNetRecord_PackSpNpc(a, 0x30); }
extern "C" void CommSyncVar_PackSpNpc11(void *a) { NpcNetRecord_PackSpNpc(a, 0x31); }
extern "C" void CommSyncVar_PackSpNpc12(void *a) { NpcNetRecord_PackSpNpc(a, 0x32); }
extern "C" void CommSyncVar_PackSpNpc13(void *a) { NpcNetRecord_PackSpNpc(a, 0x33); }
extern "C" void CommSyncVar_PackSpNpc14(void *a) { NpcNetRecord_PackSpNpc(a, 0x34); }
extern "C" void CommSyncVar_PackSpNpc15(void *a) { NpcNetRecord_PackSpNpc(a, 0x35); }
extern "C" void CommSyncVar_PackSpNpc16(void *a) { NpcNetRecord_PackSpNpc(a, 0x36); }
extern "C" void CommSyncVar_PackSpNpc17(void *a) { NpcNetRecord_PackSpNpc(a, 0x37); }
extern "C" void CommSyncVar_PackSpNpc18(void *a) { NpcNetRecord_PackSpNpc(a, 0x38); }
extern "C" void CommSyncVar_PackSpNpc19(void *a) { NpcNetRecord_PackSpNpc(a, 0x39); }
extern "C" void CommSyncVar_PackSpNpc1A(void *a) { NpcNetRecord_PackSpNpc(a, 0x3a); }
extern "C" void CommSyncVar_PackSpNpc1B(void *a) { NpcNetRecord_PackSpNpc(a, 0x3b); }
extern "C" void CommSyncVar_PackSpNpc1C(void *a) { NpcNetRecord_PackSpNpc(a, 0x3c); }
extern "C" void CommSyncVar_PackSpNpc1D(void *a) { NpcNetRecord_PackSpNpc(a, 0x3d); }
extern "C" void CommSyncVar_PackSpNpc1E(void *a) { NpcNetRecord_PackSpNpc(a, 0x3e); }
extern "C" void CommSyncVar_PackSpNpc1F(void *a) { NpcNetRecord_PackSpNpc(a, 0x3f); }
extern "C" void CommSyncVar_PackSpNpc20(void *a) { NpcNetRecord_PackSpNpc(a, 0x40); }
extern "C" void CommSyncVar_PackSpNpc21(void *a) { NpcNetRecord_PackSpNpc(a, 0x41); }
extern "C" void CommSyncVar_PackSpNpc22(void *a) { NpcNetRecord_PackSpNpc(a, 0x42); }
extern "C" void CommSyncVar_PackSpNpc23(void *a) { NpcNetRecord_PackSpNpc(a, 0x43); }
extern "C" void CommSyncVar_PackSpNpc24(void *a) { NpcNetRecord_PackSpNpc(a, 0x44); }
extern "C" void CommSyncVar_PackSpNpc25(void *a) { NpcNetRecord_PackSpNpc(a, 0x45); }
extern "C" void CommSyncVar_SetVar(u32 a, void *b, u32 c, s32 d) {
    CommManager *g = gCommManager;
    s32 r = g->isSyncVarDirty(a);
    u32 sz = CommSyncVar_GetVarSize(a);
    void *obj = g->getSyncVar(a);
    if (r == 0 && d == 0) {
        MI_CpuCopy8(obj, g->syncCompareBuf, sz);
    }
    sCommSyncVarPackHandlers[a](obj, b, c);
    if (d != 0) {
        g->setSyncVarDirty(a, 1);
    } else if (r == 0) {
        CommManager *h = gCommManager;
        s32 v = Mem_Differs(obj, h->syncCompareBuf, sz);
        h->setSyncVarDirty(a, v);
    }
}
extern "C" void CommSyncVar_Init() {
    u8 *p = (u8 *)NetHeap_Alloc(0x68c, 4);
    gCommManager->setSyncVarBuf(p);
    if (p) {
        MI_CpuFill8(p, 0, 0x68c);
    }
    for (s32 i = 0; i < 0x46; i++) {
        CommSyncVar_InitVar(i);
    }
}
extern "C" void CommRecv_RoomWallFloor(u32 a) {
    u8 buf[4];
    gCommManager->readRecord(buf, a);
    RoomWallFloor_ApplyRecv(buf);
}
extern "C" void CommRecv_PatternMove(u32 a) {
    u8 buf[4];
    gCommManager->readRecord(buf, a);
    PatternSrc_ApplyNetMove(buf);
}
extern "C" void CommRecv_SubCommand(u32 a, u32 b, u32 c, u32 d) {
    Heap *g = gCurrentHeap;
    u8 *r = (u8 *)Heap_AllocTail(g, a);
    gCommManager->readRecord(r, a);
    CommSub_Dispatch(r, d);
    Heap_Free(g, r);
}
extern "C" void CommRecv_CharInteract(u32 a, u32 b, u32 c, u32 d) {
    u8 buf[8];
    gCommManager->readRecord(buf, a);
    CharInteractSync_Dispatch(buf, d);
}
extern "C" void CommRecv_FurnitureState(u32 a) {
    u32 buf[1];
    gCommManager->readRecord((u8 *)buf, a);
    FtrSync_OnStateRecord(buf);
}
extern "C" void CommRecv_HouseRoomFlag(u32 a) {
    u8 buf[4];
    gCommManager->readRecord(buf, a);
    FtrSync_OnRoomLightRecord((Unk_0205218c_B *)buf);
}
extern "C" void CommRecv_RoomItemSet(u32 a, u32 b, u32 c) {
    u8 buf[8];
    gCommManager->readRecord(buf, 4);
    FtrSync_OnTopItemRecord(c, (Unk_020520a8_W *)buf);
}
extern "C" void CommRecv_FurnitureRemove(u32 a, u32 b, u32 c) {
    u8 buf[8];
    gCommManager->readRecord(buf, 4);
    FtrSync_OnRemoveRecord(c, (Unk_02052134_W *)buf);
}
extern "C" void CommRecv_FurniturePlace(u32 a, u32 b, u32 c) {
    u8 buf[8];
    gCommManager->readRecord(buf, 4);
    FtrSync_OnPlaceRecord(c, (FtrPlaceRecord *)buf);
}
extern "C" void CommRecv_FurnitureUseRequest(u32 a) {
    u8 buf[4];
    gCommManager->readRecord(buf, a);
    FtrSync_OnToggleRecord((Unk_02051fcc_W *)buf);
}
extern "C" void CommRecv_SpotReserveRequest(u32 a, u32 b, u32 c, u32 d) {
    u8 buf[8];
    gCommManager->readRecord(buf, 3);
    SpotSync_OnReserveRequest(buf, d);
}
extern "C" void CommRecv_SpotReserveGranted() { SpotSync_OnReserveReply(1); }
extern "C" void CommRecv_SpotReserveDenied() { SpotSync_OnReserveReply(0); }
extern "C" void CommRecv_SpotRelease(u32 a, u32 b, u32 c, u32 d) { SpotSync_OnRelease(d); }
extern "C" void CommRecv_BuildingState(u32 a) {
    u16 buf[2];
    gCommManager->readRecord((u8 *)buf, a);
    Building_ApplyStateRecord(buf);
}
extern "C" void CommRecv_BuildingEnter(u32 a, u32 b, u32 c, u32 d) {
    u8 buf[8];
    gCommManager->readRecord(buf, a);
    BuildingOccupancy_OnEnterRecord((Flags1 *)buf, d);
}
extern "C" void CommRecv_BuildingLeave(u32 a, u32 b, u32 c, u32 d) {
    u8 buf[8];
    gCommManager->readRecord(buf, a);
    BuildingOccupancy_OnLeaveRecord(buf, d);
}
extern "C" void CommRecv_Act25(u32 a) {
    NibblePair buf[4];
    gCommManager->readRecord((u8 *)buf, a);
    RoomObjSync_OnRecv(buf);
}
extern "C" void CommRecv_ShopPurchase(u32 a, u32 b, u32 c, u32 d) {
    u8 buf[8];
    gCommManager->readRecord(buf, a);
    Shop_OnPurchaseRecord(buf, d);
}
extern "C" void CommRecv_ShopPurchaseAck(u32 a, u32 b, u32 c, u32 d) { Shop_OnPurchaseAck(d); }
extern "C" void CommRecv_FieldActorClaimRequest(u32 a, u32 b, u32 c, u32 d) {
    struct L { volatile u8 b; volatile u8 f; } l;
    l.f = 1;
    CommManager *g = gCommManager;
    g->readRecord((u8 *)((void *)&l), a);
    if (Unk_02075e60_IsZero(gFieldSceneKind)) {
        l.f = Insect_NetClaim(l.b);
    }
    g->beginRecord();
    if (l.f == 0) {
        l.b &= 0xf;
        l.b |= d << 4;
        l.b += 0x10;
        g = gCommManager;
        g->writeRecord((u8 *)((void *)&l), 1);
        g->endRecord(0x29, 7);
    } else {
        g = gCommManager;
        g->writeRecord((u8 *)((void *)&l.f), 1);
        g->endRecord(0x29, d);
    }
}
extern "C" void CommRecv_FieldActorClaimResult(u32 a) {
    volatile u8 n;
    if (Unk_02075e60_IsZero(gFieldSceneKind)) {
        CommManager *g = gCommManager;
        g->readRecord((u8 *)((void *)&n), a);
        u32 v = n;
        u32 h = (v << 20) >> 24;
        n = (v & 0xf) | 0x10;
        u32 t = n;
        if (t == 1) {
            sInsectCatchResult = 1;
        } else {
            h--;
            if (h == (u32)g->myAid) {
                sInsectCatchResult = 0;
                Insect_OnClaimGranted(t);
            } else {
                sInsectCatchResult = 1;
            }
        }
    }
}
extern "C" void CommRecv_FieldActorRelease(u32 a) {
    u8 b;
    gCommManager->readRecord(&b, a);
    if (Unk_02075e60_IsZero(gFieldSceneKind)) {
        Insect_CancelCatch(b);
    }
}
}

namespace n3 {
extern "C" {
s32 Scene_GetCurrent();
}
extern "C" {
}
extern "C" {
VillagerData *SaveVillagers_Get(void *, s32);
}
extern "C" {
void *Villager_GetReceivedItem(void *, s32);
}
extern "C" {
}
extern "C" {
void *Villager_GetPlan(void *p);
}
extern "C" {
}
extern "C" {
}
extern "C" {
VillagerState *Villager_GetState(void *);
}
extern "C" {
ErrandRecord *VillagerState_GetErrand(VillagerState *e);
}
extern "C" {
}
extern "C" {
}
extern "C" {
s32 PlanErrand_AdvanceStep(void *);
}
extern "C" {
VillagerMemory *Villager_GetMemory(VillagerMemory *, u32);
}
extern "C" {
s32 VillagerMemory_IsUsed(void *);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
s32 VillagerMemory_RecordTalk(void *, void *, u8 *, s32);
}
extern "C" {
s32 VillagerMemory_InitForPlayer(void *, void *, u8 *, s32);
}
extern "C" {
s32 FieldAction_OnNetResult(void *, s32);
}
extern "C" {
s32 FishDisplay_OnNetPacket(void *, s32);
}
extern "C" {
BOOL Item_IsFurniture(u16 *);
}
extern "C" {
s32 Item_GetFurnitureIndex(void *);
}
extern "C" {
u16 ItemInfo_GetHoldableIndex(u16 *);
}
extern "C" {
}
extern "C" {
}
extern "C" {
s32 PendingUnit_IndexAt(Vec2 *, u32);
}
extern "C" {
BOOL Field_IsUnitClearOfOthersForAid(Vec2 *, u32);
}
extern "C" {
PendingUnit *PendingUnit_Get(u32 i);
}
extern "C" {
void FieldAction_HostProcess(FieldActionRequestMsg *, u8, s32);
}
extern "C" {
extern CommManager *gCommManager;
}
extern "C" {
#define gSaveVillagers HOST_LABEL(u32 (*)[], gSaveVillagers)
}
extern "C" {
#define gSaveTownId HOST_LABEL(u8 (*)[], gSaveTownId)
}
extern "C" {
extern u8 gFieldSceneKind;
}


static inline void *G() { return gCommManager; }

static inline BOOL Unk_02075680_R(volatile u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    u16 a = *p;
    u16 b = *p;
    if (b >= lo && a <= hi) r = TRUE;
    return r;
}

static inline BOOL Unk_02075d38_Same(BOOL a) {
    return a;
}

static inline BOOL Unk_02075e1c_IsZero(u8 v) {
    return v == 0 ? TRUE : FALSE;
}



extern "C" void CommRecv_FieldActorRemove(u32 n) {
    u8 buf;
    gCommManager->readRecord((u8 *)(&buf), n);
    if (Unk_02075e1c_IsZero(gFieldSceneKind)) {
        if (buf < 4) {
            HeldInsect_Remove(buf, 0);
        } else {
            Insect_OnNetRemove(buf);
        }
    }
}

extern "C" void CommRecv_FishDisplay(s32 n, s32 b, s32 c, s32 d) {
    u8 buf[8];
    gCommManager->readRecord((u8 *)(buf), n);
    FishDisplay_OnNetPacket(buf, d);
}

extern "C" void CommRecv_ClothesChange(s32 n, s32 b, s32 c, u32 d) {
    u16 h, v;
    u8 buf[4];
    u32 k;
    gCommManager->readRecord((u8 *)(buf), n);
    PlayerActor_UnpackClothesChange(buf, &h, &k);
    v = h;
    switch (k) {
    case 0:
    case 1:
    case 2:
        PlayerActor_SetClothing(&v, k, d);
        break;
    case 3: {
        void *r7 = PlayerData_GetBySessionSlot(d);
        u16 *r5 = (u16 *)((PlayerData *)(r7))->getHeldItem();
        BOOL same;
        if (Item_IsFurniture(&v) != 0) {
            s32 r6 = Item_GetFurnitureIndex(&v);
            if (r6 == Item_GetFurnitureIndex(r5)) same = TRUE; else same = FALSE;
        } else {
            if (v == *r5) same = TRUE; else same = FALSE;
        }
        if (!same) {
            u16 r = ItemInfo_GetHoldableIndex(&v);
            ((PlayerData *)(r7))->setHeldItem(&v);
            PlayerActor_SetHoldableItem(r + 1, d);
        }
        break;
    }
    }
}

extern "C" void CommRecv_HairChange(s32 n, s32 b, s32 c, u32 d) {
    u8 buf[3];
    gCommManager->readRecord((u8 *)(buf), n);
    PlayerActor_UnpackHair(&buf[0], &buf[1], &buf[2]);
    void *r4 = PlayerData_GetBySessionSlot(d);
    ((PlayerData *)(r4))->setHairStyle(buf[1]);
    ((PlayerData *)(r4))->setHairColor(buf[2]);
}

extern "C" void CommRecv_FaceChange(s32 n, s32 b, s32 c, s32 d) {
    u8 buf[4];
    gCommManager->readRecord((u8 *)(buf), n);
    PlayerActor_SetSwollenFace(buf[0], d);
}

extern "C" void CommRecv_TanChange(s32 n, s32 b, s32 c, s32 d) {
    u8 buf[4];
    gCommManager->readRecord((u8 *)(buf), n);
    PlayerActor_SetTan(buf[0], d);
}

extern "C" void CommRecv_ItemActionRequest(s32 a, s32 b, s32 c, u32 d) {
    BlockMap *grid;
    volatile u16 c1, b1, c2, b2, a1, a2;
    FieldActionRequestMsg buf;
    Vec2 pt, pt2;
    grid = TownBlockMap_Get();
    if (grid != NULL) {
        BOOL ok;
        gCommManager->readRecord((u8 *)(&buf), 8);
        ok = FALSE;
        a1 = buf.unit;
        u16 t1 = a1;
        b1 = t1;
        c1 = t1;
        s32 x = c1 >> 8;
        s32 y = b1 & 0xff;
        s32 hx = x >> 4;
        s32 hy = y >> 4;
        u16 *cell = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), buf.layer);
        if (cell != NULL) {
            if (*cell == buf.oldItem) {
                a2 = buf.unit;
                u16 t2 = a2;
                b2 = t2;
                c2 = t2;
                s32 x2, y2;
                pt.x = x2 = c2 >> 8;
                pt.y = y2 = b2 & 0xff;
                s32 idx = PendingUnit_IndexAt(&pt, buf.layer);
                if (idx < 0) {
                    pt2.x = x2;
                    pt2.y = y2;
                    if (Field_IsUnitClearOfOthersForAid(&pt2, d) != 0) ok = TRUE;
                } else {
                    PendingUnit *q = PendingUnit_Get(idx);
                    if (q->aid == buf.aid) {
                        if (q->committed != 0) {
                            if (q->pending == 0) ok = TRUE;
                        }
                    }
                }
            }
        }
        FieldAction_HostProcess(&buf, ok, d);
    }
}

extern "C" void CommRecv_ItemActionResult(s32 a, s32 b, s32 c) {
    u8 buf[14];
    gCommManager->readRecord((u8 *)(buf), 0xe);
    FieldAction_OnNetResult(buf, c);
}

extern "C" void CommRecv_ObjectUseRequest(s32 a, s32 b, s32 c, s32 d) {
    u8 buf[4];
    gCommManager->readRecord(buf, 1);
    RoomEntry_RecvEnterRequest(buf, d);
}

extern "C" void CommRecv_ObjectUseReply() {
    u8 buf[4];
    gCommManager->readRecord(buf, 1);
    RoomEntry_RecvEnterReply(buf);
}

extern "C" void CommRecv_ObjectUseRelease(s32 a, s32 b, s32 c, s32 d) {
    u8 buf[4];
    gCommManager->readRecord(buf, 1);
    RoomEntry_RecvLeave(buf, d);
}

extern "C" void CommRecv_VillagerMemoryInit(s32 n, s32 b, s32 c, u32 d) {
    u8 buf[4];
    s32 id, x;
    gCommManager->readRecord(buf, n);
    CommVillager_UnpackHeader(&id, &x, buf);
    VillagerData *r0 = SaveVillagers_Get(gSaveVillagers, id);
    if (r0 != NULL) {
        VillagerMemory *r5 = Villager_GetMemory(r0->memories, x);
        if (r5 != NULL) {
            void *r1 = PlayerData_GetBySessionSlot(d)->getPlayerId();
            VillagerMemory_InitForPlayer(r5, r1, gSaveTownId, 0);
        }
    }
}

extern "C" void CommRecv_VillagerMemorySetPlayer(s32 n, s32 b, s32 c, u32 d) {
    u8 buf[4];
    s32 id, x;
    gCommManager->readRecord(buf, n);
    CommVillager_UnpackHeader(&id, &x, buf);
    VillagerData *r0 = SaveVillagers_Get(gSaveVillagers, id);
    if (r0 != NULL) {
        VillagerMemory *r5 = Villager_GetMemory(r0->memories, x);
        if (r5 != NULL) {
            void *r1 = PlayerData_GetBySessionSlot(d)->getPlayerId();
            VillagerMemory_RecordTalk(r5, r1, gSaveTownId, 0);
        }
    }
}

extern "C" void CommRecv_VillagerImpression() {
    u8 b[2];
    s32 id, x;
    CommManager *r5 = gCommManager;
    r5->readRecord((u8 *)(b), 1);
    CommVillager_UnpackHeader(&id, &x, b);
    VillagerData *r0 = SaveVillagers_Get(gSaveVillagers, id);
    if (r0 != NULL) {
        VillagerMemory *r4 = Villager_GetMemory(r0->memories, x);
        if (r4 != NULL) {
            r5->readRecord((u8 *)(b + 1), 1);
            r4->setImpression(b[1]);
        }
    }
}

extern "C" void CommRecv_VillagerFriendship() {
    s8 b[2];
    s32 id, x;
    CommManager *r5 = gCommManager;
    r5->readRecord((u8 *)(b), 1);
    CommVillager_UnpackHeader(&id, &x, (u8 *)b);
    VillagerData *r0 = SaveVillagers_Get(gSaveVillagers, id);
    if (r0 != NULL) {
        VillagerMemory *r4 = Villager_GetMemory(r0->memories, x);
        if (r4 != NULL) {
            r5->readRecord((u8 *)(b + 1), 1);
            r4->setFriendship(b[1]);
        }
    }
}

extern "C" void CommRecv_VillagerReceivedItem() {
    struct { u16 x; u8 y[3]; } l;
    s32 id;
    s32 k;
    l.x = 0xfff1;
    gCommManager->readRecord((u8 *)(l.y), 3);
    CommVillager_UnpackReceivedItem(&id, &k, &l.x, l.y);
    VillagerData *r0 = SaveVillagers_Get(gSaveVillagers, id);
    if (r0 != NULL) {
        VillagerMemory *r4 = Villager_GetMemory(r0->memories, k);
        if (r4 != NULL) {
            if (VillagerMemory_IsUsed(r4) != 0) {
                r4->setReceivedItem(&l.x);
            }
        }
    }
}

extern "C" void CommRecv_Act3C() {
    struct { u8 a; u8 b; u8 c[2]; } l;
    s32 id;
    l.a = 6;
    l.b = 0;
    gCommManager->readRecord(l.c, 2);
    CommVillager_UnpackAct3C(&id, &l.a, &l.b, l.c);
    void *r0 = SaveVillagers_Get(gSaveVillagers, id);
    if (r0 != NULL) {
        PlanErrand *r4 = (PlanErrand *)VillagerPlanBlock_GetErrand((u8 *)Villager_GetPlan(r0));
        switch (l.a) {
        case 0:
            if (((ErrandRecord *)(PlanErrand_GetRecord(r4)))->isActive()) {
                ((ErrandRecord *)(PlanErrand_GetRecord(r4)))->setStep(l.b);
            }
            break;
        case 1:
            PlanErrand_ResetProgress(r4);
            break;
        case 2:
            if (((ErrandRecord *)(PlanErrand_GetRecord(r4)))->isActive()) {
                PlanErrand_AdvanceStep(r4);
            }
            break;
        case 3:
            if (((ErrandRecord *)(PlanErrand_GetRecord(r4)))->isActive()) {
                PlanErrand_SetFossilGroup(r4, l.b);
            }
            break;
        case 4:
            if (((ErrandRecord *)(PlanErrand_GetRecord(r4)))->isActive()) {
                PlanErrand_SetFlag(r4, l.b);
            }
        case 5:
            if (((ErrandRecord *)(PlanErrand_GetRecord(r4)))->isActive()) {
                r4->count = l.b;
            }
            break;
        }
    }
}

extern "C" void CommRecv_Act3D() {
    struct { u8 a; u8 b; u16 c; } l;
    u8 buf[4];
    s32 id;
    s32 n;
    l.a = 0x16;
    l.c = 0xfff1;
    n = 4;
    l.b = 0;
    gCommManager->readRecord(buf, 4);
    CommVillager_UnpackAct3D(&id, &l.a, &l.c, &n, &l.b, buf);
    void *r6 = SaveVillagers_Get(gSaveVillagers, id);
    if (r6 != NULL) {
        PlanErrand *r7 = (PlanErrand *)VillagerPlanBlock_GetErrand((u8 *)Villager_GetPlan(r6));
        void *r4 = NULL;
        BOOL t = l.b ? TRUE : FALSE;
        BOOL r5 = t ? TRUE : FALSE;
        VillagerState_GetErrand(Villager_GetState(r6))->clear();
        if (n < 4) {
            void *q = PlayerData_GetBySessionSlot(n);
            if (q != NULL) {
                r4 = ((PlayerData *)(q))->getPlayerId();
            }
        }
        PlanErrand_Assign(r7, l.a, &l.c, r4, r5);
    }
}

extern "C" void CommRecv_Act3F() {
    struct { u16 x; u8 y[4]; } l;
    s32 id;
    l.x = 0xfff1;
    gCommManager->readRecord((u8 *)(l.y), 4);
    CommVillager_UnpackItem(&id, &l.x, l.y);
    void *r0 = SaveVillagers_Get(gSaveVillagers, id);
    if (r0 != NULL) {
        PlanErrand *r5 = (PlanErrand *)VillagerPlanBlock_GetErrand((u8 *)Villager_GetPlan(r0));
        void *r4 = PlanErrand_GetRecord(r5);
        if (((ErrandRecord *)r4)->isActive()) {
            if (((ErrandRecord *)r4)->getKind() == 0) {
                if (Unk_02075680_R(&l.x, 0x12b0, 0x12e7)) goto set;
            }
            if (((ErrandRecord *)r4)->getKind() == 1) {
                if (Unk_02075680_R(&l.x, 0x12e8, 0x131f)) {
                set:
                    u16 *p = PlanErrand_GetShownItem(r5);
                    *p = l.x;
                }
            }
        }
    }
}

extern "C" void CommRecv_VillagerShirt() {
    struct { u16 x; u8 y[3]; } l;
    s32 id;
    VillagerShirtRecvStackPad pad;
    l.x = 0xfff1;
    gCommManager->readRecord((u8 *)(l.y), 3);
    CommVillager_UnpackItem(&id, &l.x, l.y);
    void *r0 = SaveVillagers_Get(gSaveVillagers, id);
    if (r0 != NULL) {
        BOOL r4 = Unk_02075680_R(&l.x, 0x11a8, 0x12a7);
        if (r4) ((VillagerData *)r0)->setShirt(&l.x);
    }
}

extern "C" void CommRecv_VillagerItems() {
    s32 id;
    u16 arr[4];
    u8 buf[9];
    void *r5;
    s32 i;
    arr[0] = 0xfff1;
    arr[1] = 0xfff1;
    arr[2] = 0xfff1;
    arr[3] = 0xfff1;
    gCommManager->readRecord((u8 *)(buf), 9);
    CommVillager_UnpackItems(&id, arr, buf);
    r5 = SaveVillagers_Get(gSaveVillagers, id);
    if (r5 != NULL) {
        for (i = 0; i < 4; i++) {
            u16 *p = (u16 *)Villager_GetReceivedItem(r5, i);
            if (p != NULL) {
                *p = arr[i];
            }
        }
    }
}

extern "C" void CommRecv_PeerNetState(s32 a, s32 b, s32 c, u32 d) {
    u8 v;
    gCommManager->readRecord((u8 *)(&v), 1);
    NetSession_SetSyncState(d, v);
}

extern "C" void CommRecv_OwnNetState() {
    CommManager *o = gCommManager;
    u8 b;
    o->readRecord((u8 *)(&b), 1);
    NetSession_SetSyncState(o->myAid, b);
}

extern "C" void CommRecv_Act02(s32 a, s32 b, s32 c, s32 d) {
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get() != 0) {
            SaveManager_SetRecvAct02(SaveManager_Get(), d, 1);
        }
    }
}

extern "C" void CommRecv_Act03() {
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get() != 0) {
            SaveManager_Get();
            SaveManager_SetRecvAct03(1);
        }
    }
}

extern "C" void CommRecv_Act04(s32 a, s32 b, s32 c, s32 d) {
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get() != 0) {
            SaveManager_SetRecvAct04(SaveManager_Get(), d, 1);
        }
    }
}}

namespace n2 {
extern "C" {
extern CommManager *gCommManager;
}
extern "C" {
extern void (*const sCommRecvHandlers[])(u32, u32, u32, u32);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
void MI_CpuCopy8(const void *, void *, u32);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
s32 Scene_GetCurrent();
}


extern "C" void CommRecv_PlayerLeft() {
    u8 t;
    gCommManager->readRecord(&t, 1);
    Comm_RemoveMember(t);
}
extern "C" void CommRecv_Act06(u32 a, u32 b, u32 c, u32 d) {
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get()) {
            SaveManager_SetRecvAct06(SaveManager_Get(), d, 1);
        }
    }
}
extern "C" void CommRecv_Act07() {
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get()) {
            SaveManager_SetRecvAct07(SaveManager_Get(), 1);
        }
    }
}
extern "C" void CommRecv_Act08(u32 a, u32 b, u32 c, u32 d) {
    u8 t[2];
    NetSceneMsg_Init();
    gCommManager->readRecord(t, 1);
    NetSceneMsg_Get(t, t + 1);
    NetArea_QueueMoveRequest(d, t[1]);
    NetSceneMsg_Fini();
}
extern "C" void CommRecv_SlotStatus() {
    struct { u8 t[4]; u32 pad; s32 w1; s32 w2; } l;
    NetStatusMsg_Init(l.t + 3);
    gCommManager->readRecord(l.t + 3, 2);
    NetStatusMsg_Unpack(l.t + 3, &l.w1, l.t, l.t + 1, l.t + 2, &l.w2);
    NetArea_SetSlotStatus(l.w1, l.t[0], l.t[1], l.t[2], l.w2);
    NetStatusMsg_Fini(l.t + 3);
}
extern "C" void CommRecv_Act0A(u32 a, u32 b, u32 c, u32 d) {
    u8 t[4];
    gCommManager->readRecord(t, 1);
    NetArea_SetMoveReady(d, t[0]);
}
extern "C" void CommRecv_Act0B(u32 a, u32 b, u32 c, u32 d) {
    struct { u8 t[4]; u32 pad; s32 w; } l;
    NetStatusUpdateMsg_Init(l.t + 3);
    gCommManager->readRecord(l.t + 3, 2);
    NetStatusUpdateMsg_Unpack(l.t + 3, l.t, l.t + 1, l.t + 2, &l.w);
    NetArea_SetPendingStatus(d, l.t[0], l.t[1], l.t[2], l.w);
    NetStatusUpdateMsg_Fini(l.t + 3);
}
extern "C" void CommRecv_Act0C(u32 a, u32 b, u32 c, u32 d) {
    u8 msg[4];
    s32 v[4];
    NetSyncMsg_Init();
    CommManager *g = gCommManager;
    g->readRecord(msg, 1);
    NetSyncMsg_Unpack(msg, v + 1, v + 2, v + 3);
    if (d == 0) NetSession_SetMemberSyncReply(g->myAid, v[1]);
    else NetSession_SetMemberSyncReply(d, v[1]);
    if (v[2] < 4) NetSession_SetSyncKind(v[2]);
    if (v[3] < 4) NetSession_SetSyncRequester(v[3]);
    NetSyncMsg_Fini();
}
extern "C" void CommRecv_Act0D(u32 a, u32 b, u32 c, u32 d) { NetArea_SetMemberAck(d, 1); }
extern "C" void CommRecv_Act0E(u32 a, u32 b, u32 c, u32 d) { NetArea_SetStateRequester(d); }
extern "C" void CommRecv_Act0F(u32 n) {
    CommManager *g = gCommManager;
    g->readRecord((u8 *)((void *)g->getAuxBufA()), n);
    g->setAuxLenA(n);
    NetArea_OnStateAReceived();
}
extern "C" void CommRecv_Act10(u32 n) {
    CommManager *g = gCommManager;
    g->readRecord((u8 *)((void *)g->getAuxBufB()), n);
    g->setAuxLenB(n);
}
extern "C" void CommRecv_Act11() { NetArea_SetOwnerAck(1); }
extern "C" void CommRecv_ItemSet(u32 n) {
    u32 i = 0;
    CommManager *g = gCommManager;
    u8 buf[5];
    while (i < n) {
        g->readRecord((u8 *)(buf), 5);
        ItemSync_Apply(buf);
        i += 5;
    }
}
extern "C" void CommRecv_ItemSetRequest(u32 n) {
    u32 i = 0;
    CommManager *g = gCommManager;
    s32 z = 0;
    u8 buf[7];
    while (i < n) {
        g->readRecord((u8 *)(buf + 2), 5);
        u32 v = NetBuf_ReadU16(buf + 2);
        CommRecord_UnpackSource(buf + 4, buf, buf + 1);
        ItemSync_SetAtUnit(((s8 *)buf)[5], ((s8 *)buf)[6], buf[0], v, buf[1] ? 1 : z);
        i += 5;
    }
}
extern "C" void CommRecv_Dispatch(u32 idx, u8 *x, u32 a, u32 b, u8 c, u32 d) {
    gCommManager->setReadPtr(x);
    sCommRecvHandlers[idx](a, b, c, d);
}
extern "C" BOOL CommSend_MemberInfo(u32 a) {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend()) {
        if (Comm_HasSendCredit(a)) {
            CommManager *g = gCommManager;
            g->isMyAid(0);
            u8 *b = g->getSendBuf(4);
            CommPacket_SetHeader(b, 0, 0);
            u32 m = 0;
            u32 i = 0;
            for (i = 0; i < 4; i++) {
                if (g->isSlotActive(i)) {
                    m |= (u8)(1 << i);
                }
            }
            m &= 0xf;
            u32 r = (u8)m;
            r |= (((u8)PlayerSession_GetDataIndex(0)) << 6) & 0xc0;
            b[1] = r;
            g = gCommManager;
            return g->sendPackets(g->getSendBuf(4), 2, a, 0, 0, 0, 0, 0, 0);
        }
    }
    return FALSE;
}
extern "C" BOOL CommSend_Chunked(u8 *p, void *data, u32 size, u32 type, u32 maskw) {
    u32 cnt = size / 0xffb;
    u32 rem = size % 0xffb;
    if (rem != 0) cnt++;
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend()) {
        if (Comm_HasSendCredit(*(u16 *)&maskw)) {
            u32 off = *p * 0xffb;
            u32 left = size - off;
            if (left > 0xffb) left = 0xffb;
            CommManager *g = gCommManager;
            u8 *b = g->getSendBuf(4);
            CommPacket_SetHeader(b, 0, type);
            MI_CpuCopy8(&off, b + 1, 4);
            MI_CpuCopy8((u8 *)data + off, b + 5, left);
            if (g->sendPackets(g->getSendBuf(4), left + 5, *(u16 *)&maskw, 0, 0, 0, 0, 0, 0)) {
                (*p)++;
            }
        }
    }
    if (*p >= cnt) return TRUE;
    return FALSE;
}
extern "C" BOOL CommSend_TownChunk(u8 *p, u32 v) {
    TownCompressBuffer *d = SaveManager_GetTownCompressBuf();
    u32 n = d->getSize();
    u32 sz;
    if (n == 0) sz = 0x15fe4; else sz = n + 4;
    return CommSend_Chunked(p, d, sz, 1, v);
}
extern "C" BOOL CommSend_VillagerTransfer(u8 *p) {
    void *d = TownExchange_GetForAid(4);
    if (((TownExchangeRecord *)(d))->isValid()) {
        return CommSend_Chunked(p, d, 0x84c, 2, 1);
    }
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend()) {
        if (Comm_HasSendCredit(1)) {
            CommManager *g = gCommManager;
            CommPacket_SetHeader(g->getSendBuf(4), 0, 2);
            return g->sendPackets(g->getSendBuf(4), 1, 1, 0, 0, 0, 0, 0, 0);
        }
    }
    return FALSE;
}
extern "C" BOOL CommSend_VillagerTransferReply(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    s32 vals[3];
    s32 aids[3];
    u8 *bufs[3];
    s32 offs[3];
    u16 masks[3];
    u32 i;
    s32 mode;
    CommManager *g;
    NetOverlay_AssertAny();
    if (!Net_IsReadyToSend()) goto fail;
    vals[0] = a; vals[1] = c; vals[2] = e;
    aids[0] = b; aids[1] = d; aids[2] = f;
    func_02133ef8(bufs, 0xc);
    func_02133ef8(offs, 0xc);
    func_02133ef8(masks, 6);
    i = 0;
    g = gCommManager;
    for (; i < 3; i++) {
        mode = vals[i];
        if (mode != 3) {
            bufs[i] = g->getSendBuf(i + 1);
            u8 *bb = bufs[i];
            CommPacket_SetHeader(bb, 0, 3);
            offs[i] = offs[i] + 1;
            if (mode == 0) {
                bb[1] = 0;
                offs[i] = offs[i] + 1;
            } else if (mode == 1) {
                bb[1] = 1;
                offs[i] = offs[i] + 1;
            } else {
                MI_CpuCopy8(TownExchange_GetForAid(aids[i]), bb + 1, 0x84c);
                offs[i] = offs[i] + 0x84c;
            }
            masks[i] = 1 << (i + 1);
        }
    }
    if (a == 3 && c == 3) {
        if (e == 3) goto yes;
    }
    if (Comm_HasSendCredit((u16)(masks[0] | masks[1] | masks[2]))) {
        return g->sendPackets(bufs[0], offs[0], masks[0], bufs[1], offs[1], masks[1], bufs[2], offs[2], masks[2]);
    }
    return FALSE;
yes:
    return TRUE;
fail:
    return FALSE;
}
extern "C" BOOL CommSend_PlayerData(u8 *p, u32 v) {
    return CommSend_Chunked(p, (void *)PlayerData_Get(PlayerSession_GetDataIndex(gCommManager->localSlot)), sizeof(PlayerData), 4, v);
}
extern "C" BOOL CommSend_SyncVarChunk(u8 *p, u32 v) {
    return CommSend_Chunked(p, gCommManager->getSyncVarBuf(), 0x68c, 0xc, v);
}
extern "C" BOOL CommSend_BuiltPacket(u32 a) {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend()) {
        if (Comm_HasSendCredit(a)) {
            CommManager *g = gCommManager;
            u8 *b = g->getSendBuf(4);
            return g->sendPackets(b, g->getControlLen(), a, 0, 0, 0, 0, 0, 0);
        }
    }
    return FALSE;
}
extern "C" BOOL CommCtrl_SendAct08() {
    u32 a = Comm_GetRemoteMask();
    if (a != 0) {
        NetOverlay_AssertAny();
        if (Net_IsReadyToSend()) {
            if (Comm_HasSendCredit(a)) {
                CommManager *g = gCommManager;
                g->isMyAid(0);
                u8 *b = g->getSendBuf(4);
                CommPacket_SetHeader(b, 0, 8);
                b[1] = 1;
                return g->sendPackets(g->getSendBuf(4), 2, a, 0, 0, 0, 0, 0, 0);
            }
        }
        return FALSE;
    }
    return TRUE;
}
extern "C" BOOL CommCtrl_SendAct07() {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend()) {
        if (Comm_HasSendCredit(1)) {
            CommManager *g = gCommManager;
            CommPacket_SetHeader(g->getSendBuf(4), 0, 7);
            return g->sendPackets(g->getSendBuf(4), 1, 1, 0, 0, 0, 0, 0, 0);
        }
    }
    return FALSE;
}
extern "C" BOOL CommSend_JoinDone(u32 a) {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend()) {
        if (Comm_HasSendCredit(a)) {
            CommManager *g = gCommManager;
            CommPacket_SetHeader(g->getSendBuf(4), 0, 0xb);
            return g->sendPackets(g->getSendBuf(4), 1, a, 0, 0, 0, 0, 0, 0);
        }
    }
    return FALSE;
}
extern "C" BOOL CommSend_JoinReady() {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend()) {
        if (Comm_HasSendCredit(1)) {
            CommManager *g = gCommManager;
            g->isMyAid(0);
            CommPacket_SetHeader(g->getSendBuf(4), 0, 9);
            return g->sendPackets(g->getSendBuf(4), 1, 1, 0, 0, 0, 0, 0, 0);
        }
    }
    return FALSE;
}
}

namespace n1 {
extern "C" {
extern void (*const sCommCtrlHandlers[])(void *, s32, s32);
}
extern "C" {
extern CommManager *gCommManager;
}
extern "C" {
s32 Scene_GetCurrent();
}
extern "C" {
void MI_CpuCopy8(const void *, void *, u32);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
s32 Clock_GetDateTime(void *);
}


extern "C" s32 CommSend_DateTime(u32 a) {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend() != 0 && Comm_HasSendCredit(a) != 0) {
        CommManager *g = gCommManager;
        g->isMyAid(0);
        u8 *p = g->getSendBuf(4);
        CommPacket_SetHeader(p, 0, 0xa);
        u32 t[2];
        t[0] = 0;
        t[1] = 0;
        Clock_GetDateTime(t);
        MI_CpuCopy8(t, p + 1, 8);
        return g->sendPackets(g->getSendBuf(4), 9, a, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
extern "C" s32 CommCtrl_SendAct0E(u8 a, u32 b) {
    if (b != 0) {
        NetOverlay_AssertAny();
        if (Net_IsReadyToSend() != 0 && Comm_HasSendCredit(b) != 0) {
            CommManager *g = gCommManager;
            u8 *p = g->getSendBuf(4);
            CommPacket_SetHeader(p, 0, 0xe);
            p[1] = a;
            return g->sendPackets(g->getSendBuf(4), 2, b, 0, 0, 0, 0, 0, 0);
        }
        return 0;
    }
    return 1;
}
extern "C" s32 CommSend_SlotStatusAll(s32 a) {
    u16 m = 1 << a;
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend() != 0 && Comm_HasSendCredit(m) != 0) {
        u8 *p = gCommManager->getSendBuf(4);
        u32 len = 0;
        u32 j;
        CommPacket_SetHeader(p, 0, 0xf);
        p++;
        len++;
        for (j = 0; j < 4; j++) {
            struct {
                u8 r, g, b;
                u8 col[2];
            } l;
            NetArea_GetSlotStatus(j, &l.r, &l.g, &l.b);
            NetStatusUpdateMsg_Init(l.col);
            NetStatusUpdateMsg_Pack(l.col, l.r, l.g, l.b, 7);
            MI_CpuCopy8(l.col, p, 2);
            p += 2;
            len += 2;
            NetStatusUpdateMsg_Fini(l.col);
        }
        CommManager *g = gCommManager;
        return g->sendPackets(g->getSendBuf(4), len, m, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
extern "C" s32 CommCtrl_SendAct10() {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend() != 0 && Comm_HasSendCredit(1) != 0) {
        CommManager *g = gCommManager;
        g->isMyAid(0);
        CommPacket_SetHeader(g->getSendBuf(4), 0, 0x10);
        return g->sendPackets(g->getSendBuf(4), 1, 1, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
extern "C" s32 CommCtrl_SendAct11() {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend() != 0 && Comm_HasSendCredit(1) != 0) {
        CommManager *g = gCommManager;
        CommPacket_SetHeader(g->getSendBuf(4), 0, 0x11);
        return g->sendPackets(g->getSendBuf(4), 1, 1, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
extern "C" s32 CommCtrl_SendAct12(u32 a) {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend() != 0 && Comm_HasSendCredit(a) != 0) {
        CommManager *g = gCommManager;
        g->isMyAid(0);
        CommPacket_SetHeader(g->getSendBuf(4), 0, 0x12);
        return g->sendPackets(g->getSendBuf(4), 1, a, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
extern "C" s32 CommCtrl_SendAct13() {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend() != 0 && Comm_HasSendCredit(1) != 0) {
        CommManager *g = gCommManager;
        CommPacket_SetHeader(g->getSendBuf(4), 0, 0x13);
        Comm_GetRemoteMask();
        return g->sendPackets(g->getSendBuf(4), 1, 1, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
extern "C" s32 CommCtrl_SendAct14() {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend() != 0 && Comm_HasSendCredit(1) != 0) {
        CommManager *g = gCommManager;
        g->isMyAid(0);
        CommPacket_SetHeader(g->getSendBuf(4), 0, 0x14);
        return g->sendPackets(g->getSendBuf(4), 1, 1, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
extern "C" s32 CommSend_PlayerDataToHost(u8 *a) {
    PlayerData *r = PlayerData_Get(PlayerSession_GetDataIndex(gCommManager->localSlot));
    return CommSend_Chunked(a, r, sizeof(PlayerData), 0x15, 1);
}
extern "C" s32 CommSend_LetterStorageToHost(u8 *a) {
    u8 *r = PlayerData_GetLetterStorage(PlayerData_Get(PlayerSession_GetDataIndex(gCommManager->localSlot)));
    return CommSend_Chunked(a, r, 0x477c, 0x16, 1);
}
extern "C" s32 CommCtrl_SendAct17() {
    NetOverlay_AssertAny();
    if (Net_IsReadyToSend() != 0 && Comm_HasSendCredit(1) != 0) {
        CommManager *g = gCommManager;
        g->isMyAid(0);
        CommPacket_SetHeader(g->getSendBuf(4), 0, 0x17);
        return g->sendPackets(g->getSendBuf(4), 1, 1, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
extern "C" void CommCtrl_RecvMemberInfo(u8 *a) {
    if (Scene_GetCurrent() == 0xc) {
        if (SaveManager_Get() != 0) {
            s32 v = *a;
            SaveManager_SetHostMemberMask(SaveManager_Get(), v & 0xf);
            SaveManager_SetHostDataIndex(SaveManager_Get(), (v >> 6) & 3);
        }
    }
}
extern "C" void CommCtrl_RecvTownChunk(u8 *a, s32 b) {
    u32 n;
    if (Scene_GetCurrent() == 0xc) {
        MI_CpuCopy8(a, &n, 4);
        TownCompressBuffer *p = SaveManager_GetTownCompressBuf();
        MI_CpuCopy8(a + 4, (u8 *)p + n, b - 4);
        s32 r = p->getSize();
        u32 lim;
        if (r == 0) {
            lim = 0x15fe4;
        } else {
            lim = r + 4;
        }
        if (n + (b - 4) >= lim) {
            SaveManager_GetTownCompressThread()->start(0);
        }
    }
}
extern "C" void CommCtrl_RecvVillagerTransfer(u8 *a, s32 b, s32 c) {
    u32 n;
    if (b != 0) {
        MI_CpuCopy8(a, &n, 4);
        u8 *q = (u8 *)TownExchange_GetForAid(c);
        MI_CpuCopy8(a + 4, (void *)(q + n), b - 4);
    } else {
        TownExchange_Clear(TownExchange_GetForAid(c));
    }
    if (Scene_GetCurrent() == 0xd || Scene_GetCurrent() == 0x2f) {
        if (SaveManager_Get() != 0) {
            SaveManager_Get()->setTransferReceived(c, 1);
        }
    }
}
extern "C" void CommCtrl_RecvVillagerTransferReply(u8 *a, s32 b) {
    if (b == 1) {
        if (*a != 0) {
            TownExchange_Clear(TownExchange_GetForAid(4));
        }
    } else {
        MI_CpuCopy8(a, (void *)TownExchange_GetForAid(4), 0x84c);
    }
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get() != 0) {
            SaveManager_Get()->setTransferReceived(gCommManager->myAid, 1);
        }
    }
}
extern "C" void CommCtrl_RecvVisitorPlayerData(u8 *a, s32 b, s32 c) {
    u32 n;
    MI_CpuCopy8(a, &n, 4);
    s32 t = c + 3;
    u8 *q = (u8 *)PlayerData_Get(t);
    MI_CpuCopy8(a + 4, q + n, b - 4);
    PlayerSession_SetDataIndex(c, t);
}
extern "C" void CommCtrl_RecvNetState(u8 *a, s32 b, s32 c) {
    NetSession_SetSyncState(c, *a);
}
extern "C" void CommCtrl_Act06(u8 *a) {
    s32 v = *a;
    NetSession_SetSyncState(3, v & 7);
    NetSession_SetSyncMemberMask((v >> 4) & 0xf);
}
extern "C" void CommCtrl_Act07() {
    NetSession_SetCtrl07Received(1);
}
extern "C" void CommCtrl_Act08(u8 *a) {
    CommManager *g = gCommManager;
    if (g->getPendingMode() == 3) {
        g->setPendingMode(*a);
    }
}
extern "C" void CommCtrl_RecvJoinReady() {
    if (Scene_GetCurrent() == 0xd || Scene_GetCurrent() == 0x2f) {
        if (SaveManager_Get() != 0) {
            SaveManager_SetJoinReady(SaveManager_Get(), 1);
        }
    }
}
extern "C" void CommCtrl_RecvDateTime(void *a) {
    if (Scene_GetCurrent() == 0xc) {
        if (SaveManager_Get() != 0) {
            MI_CpuCopy8(a, (void *)SaveManager_GetHostDateTime(SaveManager_Get()), 8);
            SaveManager_SetDateTimeReceived(SaveManager_Get(), 1);
        }
    }
}
extern "C" void CommCtrl_RecvJoinDone() {
    if (Scene_GetCurrent() == 0xd || Scene_GetCurrent() == 0x2f) {
        if (SaveManager_Get() != 0) {
            SaveManager_SetJoinDone(SaveManager_Get(), 1);
        }
    }
}
extern "C" void CommCtrl_RecvSyncVarChunk(u8 *a, s32 b) {
    u32 n;
    MI_CpuCopy8(a, &n, 4);
    u8 *q = gCommManager->getSyncVarBuf();
    MI_CpuCopy8(a + 4, q + n, b - 4);
}
extern "C" void CommCtrl_RecvStateBlocks(u8 *a, s32 b, s32 c) {
    CommBlock_ParseAll(a, b);
}
extern "C" void CommCtrl_Act0E(u8 *a, s32 b, s32 c) {
    if (Scene_GetCurrent() == 0x2e || Scene_GetCurrent() == 9) {
        SaveManager *p = SaveManager_Get();
        if (p != 0) {
            if (Net_GetMyAid() == 0) {
                SaveManager_SetCtrlAct0E(p, c, *a);
            } else {
                SaveManager_SetCtrlAct0E(p, 0, *a);
            }
        }
    }
}
extern "C" void CommCtrl_RecvSlotStatusAll(u8 *a) {
    struct {
        u8 r, g, b;
        u8 col[2];
    } l;
    s32 out;
    u32 i;
    for (i = 0; i < 4; i++) {
        NetStatusUpdateMsg_Init(l.col);
        MI_CpuCopy8(a, l.col, 2);
        NetStatusUpdateMsg_Unpack(l.col, &l.r, &l.g, &l.b, &out);
        NetArea_SetSlotStatus(i, l.r, l.g, l.b, out);
        a += 2;
        NetStatusUpdateMsg_Fini(l.col);
    }
}
extern "C" void CommCtrl_Act10(void *a, s32 b, s32 c) {
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get() != 0) {
            SaveManager_SetCtrlAct10(SaveManager_Get(), c, 1);
        }
    }
}
extern "C" void CommCtrl_Act11(void *a, s32 b, s32 c) {
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get() != 0) {
            SaveManager_SetCtrlAct11(SaveManager_Get(), c, 1);
        }
    }
}
extern "C" void CommCtrl_Act12() {
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get() != 0) {
            SaveManager_SetCtrlAct12(SaveManager_Get(), 1);
        }
    }
}
extern "C" void CommCtrl_Act13(void *a, s32 b, s32 c) {
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get() != 0) {
            SaveManager_SetRecvAct06(SaveManager_Get(), c, 1);
        }
    }
}
extern "C" void CommCtrl_Act14(void *a, s32 b, s32 c) {
    SaveManager_SetCtrlAct14Aid(c);
}
extern "C" void CommCtrl_RecvPlayerDataToHost(u8 *a, s32 b) {
    u32 n;
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get() != 0) {
            MI_CpuCopy8(a, &n, 4);
            s32 r = SaveManager_Get()->func_020a148c();
            CommManager *g = gCommManager;
            g->localSlot = 0;
            PlayerSession_SetDataIndex(g->localSlot, r);
            u8 *q = (u8 *)PlayerData_GetCurrent();
            MI_CpuCopy8(a + 4, q + n, b - 4);
        }
    }
}
extern "C" void CommCtrl_RecvLetterStorageToHost(u8 *a, s32 b) {
    u32 n;
    MI_CpuCopy8(a, &n, 4);
    u8 *q = PlayerData_GetLetterStorage(PlayerData_GetCurrent());
    MI_CpuCopy8(a + 4, (void *)(q + n), b - 4);
}
extern "C" void CommCtrl_Act17() {
    if (Scene_GetCurrent() == 0x2e) {
        if (SaveManager_Get() != 0) {
            SaveManager_SetCtrlAct17(SaveManager_Get(), 1);
        }
    }
}
extern "C" void CommCtrl_Dispatch(void *a, s32 b, s32 c, u32 idx) {
    sCommCtrlHandlers[idx](a, b, c);
}
}

namespace n0 {
extern "C" {
typedef void (*FPT_data_020cbb1c)(u32);
typedef void (*FPT_data_020cbb24)(u8 *, u32);
typedef void (*FPT_data_020cbb74)(void *, s32, s32);
typedef void (*FPT_data_020cbc60)(u32, u32, u32, u32);
typedef void (*FPT_data_020cbd60)(void *);
typedef void (*FPT_data_020cbe78)(void *, void *, u32);
}
}
namespace n0 {
extern "C" {
extern const FPT_data_020cbb1c sCommBlockWriters[2];
const FPT_data_020cbb1c sCommBlockWriters[2] = {
    (FPT_data_020cbb1c)CommBlock_WriteAct00,
    (FPT_data_020cbb1c)CommBlock_WriteAct01
};
}
}
namespace n0 {
extern "C" {
extern const FPT_data_020cbb24 sCommBlockReaders[2];
const FPT_data_020cbb24 sCommBlockReaders[2] = {
    (FPT_data_020cbb24)CommBlock_ReadAct00,
    (FPT_data_020cbb24)CommBlock_ReadAct01
};
}
}
namespace n0 {
extern "C" {
extern const u8 sCommSyncVarVarSizes[72];
const u8 sCommSyncVarVarSizes[72] = {0x5, 0x5, 0x5, 0x5, 0x2, 0x2, 0x2, 0x2, 0xc, 0xc, 0xc, 0xc, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x29, 0x29, 0x29, 0x29, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x0, 0x0};
}
}
namespace n0 {
extern "C" {
extern const FPT_data_020cbd60 sCommSyncVarInitHandlers[70];
const FPT_data_020cbd60 sCommSyncVarInitHandlers[70] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (FPT_data_020cbd60)CommSyncVar_InitVillager0,
    (FPT_data_020cbd60)CommSyncVar_InitVillager1,
    (FPT_data_020cbd60)CommSyncVar_InitVillager2,
    (FPT_data_020cbd60)CommSyncVar_InitVillager3,
    (FPT_data_020cbd60)CommSyncVar_InitVillager4,
    (FPT_data_020cbd60)CommSyncVar_InitVillager5,
    (FPT_data_020cbd60)CommSyncVar_InitVillager6,
    (FPT_data_020cbd60)CommSyncVar_InitVillager7,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};
}
}
char *sBbsDefaultKey = data_020e0548;
char data_020e0548[] = "bbs_default";
namespace n0 {
extern "C" {
extern const FPT_data_020cbb74 sCommCtrlHandlers[24];
const FPT_data_020cbb74 sCommCtrlHandlers[24] = {
    (FPT_data_020cbb74)CommCtrl_RecvMemberInfo,
    (FPT_data_020cbb74)CommCtrl_RecvTownChunk,
    (FPT_data_020cbb74)CommCtrl_RecvVillagerTransfer,
    (FPT_data_020cbb74)CommCtrl_RecvVillagerTransferReply,
    (FPT_data_020cbb74)CommCtrl_RecvVisitorPlayerData,
    (FPT_data_020cbb74)CommCtrl_RecvNetState,
    (FPT_data_020cbb74)CommCtrl_Act06,
    (FPT_data_020cbb74)CommCtrl_Act07,
    (FPT_data_020cbb74)CommCtrl_Act08,
    (FPT_data_020cbb74)CommCtrl_RecvJoinReady,
    (FPT_data_020cbb74)CommCtrl_RecvDateTime,
    (FPT_data_020cbb74)CommCtrl_RecvJoinDone,
    (FPT_data_020cbb74)CommCtrl_RecvSyncVarChunk,
    (FPT_data_020cbb74)CommCtrl_RecvStateBlocks,
    (FPT_data_020cbb74)CommCtrl_Act0E,
    (FPT_data_020cbb74)CommCtrl_RecvSlotStatusAll,
    (FPT_data_020cbb74)CommCtrl_Act10,
    (FPT_data_020cbb74)CommCtrl_Act11,
    (FPT_data_020cbb74)CommCtrl_Act12,
    (FPT_data_020cbb74)CommCtrl_Act13,
    (FPT_data_020cbb74)CommCtrl_Act14,
    (FPT_data_020cbb74)CommCtrl_RecvPlayerDataToHost,
    (FPT_data_020cbb74)CommCtrl_RecvLetterStorageToHost,
    (FPT_data_020cbb74)CommCtrl_Act17
};
}
}
namespace n0 {
extern "C" {
extern const FPT_data_020cbc60 sCommRecvHandlers[64];
const FPT_data_020cbc60 sCommRecvHandlers[64] = {
    (FPT_data_020cbc60)CommRecv_PeerNetState,
    (FPT_data_020cbc60)CommRecv_OwnNetState,
    (FPT_data_020cbc60)CommRecv_Act02,
    (FPT_data_020cbc60)CommRecv_Act03,
    (FPT_data_020cbc60)CommRecv_Act04,
    (FPT_data_020cbc60)CommRecv_PlayerLeft,
    (FPT_data_020cbc60)CommRecv_Act06,
    (FPT_data_020cbc60)CommRecv_Act07,
    (FPT_data_020cbc60)CommRecv_Act08,
    (FPT_data_020cbc60)CommRecv_SlotStatus,
    (FPT_data_020cbc60)CommRecv_Act0A,
    (FPT_data_020cbc60)CommRecv_Act0B,
    (FPT_data_020cbc60)CommRecv_Act0C,
    (FPT_data_020cbc60)CommRecv_Act0D,
    (FPT_data_020cbc60)CommRecv_Act0E,
    (FPT_data_020cbc60)CommRecv_Act0F,
    (FPT_data_020cbc60)CommRecv_Act10,
    (FPT_data_020cbc60)CommRecv_Act11,
    (FPT_data_020cbc60)CommRecv_ItemSet,
    (FPT_data_020cbc60)CommRecv_ItemSetRequest,
    (FPT_data_020cbc60)CommRecv_RoomWallFloor,
    (FPT_data_020cbc60)CommRecv_PatternMove,
    (FPT_data_020cbc60)CommRecv_SubCommand,
    (FPT_data_020cbc60)CommRecv_CharInteract,
    (FPT_data_020cbc60)CommRecv_FurnitureState,
    (FPT_data_020cbc60)CommRecv_HouseRoomFlag,
    (FPT_data_020cbc60)CommRecv_RoomItemSet,
    (FPT_data_020cbc60)CommRecv_FurnitureRemove,
    (FPT_data_020cbc60)CommRecv_FurniturePlace,
    (FPT_data_020cbc60)CommRecv_FurnitureUseRequest,
    (FPT_data_020cbc60)CommRecv_SpotReserveRequest,
    (FPT_data_020cbc60)CommRecv_SpotReserveGranted,
    (FPT_data_020cbc60)CommRecv_SpotReserveDenied,
    (FPT_data_020cbc60)CommRecv_SpotRelease,
    (FPT_data_020cbc60)CommRecv_BuildingState,
    (FPT_data_020cbc60)CommRecv_BuildingEnter,
    (FPT_data_020cbc60)CommRecv_BuildingLeave,
    (FPT_data_020cbc60)CommRecv_Act25,
    (FPT_data_020cbc60)CommRecv_ShopPurchase,
    (FPT_data_020cbc60)CommRecv_ShopPurchaseAck,
    (FPT_data_020cbc60)CommRecv_FieldActorClaimRequest,
    (FPT_data_020cbc60)CommRecv_FieldActorClaimResult,
    (FPT_data_020cbc60)CommRecv_FishDisplay,
    (FPT_data_020cbc60)CommRecv_ClothesChange,
    (FPT_data_020cbc60)CommRecv_HairChange,
    (FPT_data_020cbc60)CommRecv_FaceChange,
    (FPT_data_020cbc60)CommRecv_TanChange,
    (FPT_data_020cbc60)CommRecv_FieldActorRelease,
    (FPT_data_020cbc60)CommRecv_FieldActorRemove,
    (FPT_data_020cbc60)CommRecv_ItemActionRequest,
    (FPT_data_020cbc60)CommRecv_ItemActionResult,
    (FPT_data_020cbc60)CommRecv_ObjectUseRequest,
    (FPT_data_020cbc60)CommRecv_ObjectUseReply,
    (FPT_data_020cbc60)CommRecv_ObjectUseRelease,
    (FPT_data_020cbc60)CommRecv_VillagerMemoryInit,
    (FPT_data_020cbc60)CommRecv_VillagerMemorySetPlayer,
    (FPT_data_020cbc60)CommRecv_VillagerImpression,
    (FPT_data_020cbc60)CommRecv_VillagerFriendship,
    (FPT_data_020cbc60)CommRecv_VillagerShirt,
    (FPT_data_020cbc60)CommRecv_VillagerItems,
    (FPT_data_020cbc60)CommRecv_Act3C,
    (FPT_data_020cbc60)CommRecv_Act3D,
    (FPT_data_020cbc60)CommRecv_VillagerReceivedItem,
    (FPT_data_020cbc60)CommRecv_Act3F
};
}
}
OverlayHandle gOverlayHandle;
namespace n0 {
extern "C" {
extern const FPT_data_020cbe78 sCommSyncVarPackHandlers[70];
const FPT_data_020cbe78 sCommSyncVarPackHandlers[70] = {
    (FPT_data_020cbe78)CommSyncVar_PackPlayerPos0,
    (FPT_data_020cbe78)CommSyncVar_PackPlayerPos1,
    (FPT_data_020cbe78)CommSyncVar_PackPlayerPos2,
    (FPT_data_020cbe78)CommSyncVar_PackPlayerPos3,
    (FPT_data_020cbe78)CommSyncVar_PackPlayerAngle0,
    (FPT_data_020cbe78)CommSyncVar_PackPlayerAngle1,
    (FPT_data_020cbe78)CommSyncVar_PackPlayerAngle2,
    (FPT_data_020cbe78)CommSyncVar_PackPlayerAngle3,
    (FPT_data_020cbe78)CommSyncVar_PackVar08,
    (FPT_data_020cbe78)CommSyncVar_PackVar09,
    (FPT_data_020cbe78)CommSyncVar_PackVar0A,
    (FPT_data_020cbe78)CommSyncVar_PackVar0B,
    (FPT_data_020cbe78)CommSyncVar_PackVillager0,
    (FPT_data_020cbe78)CommSyncVar_PackVillager1,
    (FPT_data_020cbe78)CommSyncVar_PackVillager2,
    (FPT_data_020cbe78)CommSyncVar_PackVillager3,
    (FPT_data_020cbe78)CommSyncVar_PackVillager4,
    (FPT_data_020cbe78)CommSyncVar_PackVillager5,
    (FPT_data_020cbe78)CommSyncVar_PackVillager6,
    (FPT_data_020cbe78)CommSyncVar_PackVillager7,
    (FPT_data_020cbe78)CommSyncVar_PackPlayerMsg0,
    (FPT_data_020cbe78)CommSyncVar_PackPlayerMsg1,
    (FPT_data_020cbe78)CommSyncVar_PackPlayerMsg2,
    (FPT_data_020cbe78)CommSyncVar_PackPlayerMsg3,
    (FPT_data_020cbe78)CommSyncVar_PackVar18,
    (FPT_data_020cbe78)CommSyncVar_PackVar19,
    (FPT_data_020cbe78)CommSyncVar_PackVar1A,
    (FPT_data_020cbe78)CommSyncVar_PackVar1B,
    (FPT_data_020cbe78)CommSyncVar_PackVar1C,
    (FPT_data_020cbe78)CommSyncVar_PackVar1D,
    (FPT_data_020cbe78)CommSyncVar_PackVar1E,
    (FPT_data_020cbe78)CommSyncVar_PackVar1F,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc00,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc01,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc02,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc03,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc04,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc05,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc06,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc07,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc08,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc09,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc0A,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc0B,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc0C,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc0D,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc0E,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc0F,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc10,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc11,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc12,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc13,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc14,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc15,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc16,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc17,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc18,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc19,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc1A,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc1B,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc1C,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc1D,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc1E,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc1F,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc20,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc21,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc22,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc23,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc24,
    (FPT_data_020cbe78)CommSyncVar_PackSpNpc25
};
}
}
namespace n0 {
extern "C" {
extern const u16 sCommSyncVarVarOffsets[70];
const u16 sCommSyncVarVarOffsets[70] = {0x0, 0x5, 0xa, 0xf, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x28, 0x34, 0x40, 0x4c, 0x6a, 0x88, 0xa6, 0xc4, 0xe2, 0x100, 0x11e, 0x13c, 0x165, 0x18e, 0x1b7, 0x1e0, 0x1e7, 0x1ee, 0x1f5, 0x1fc, 0x203, 0x20a, 0x211, 0x218, 0x236, 0x254, 0x272, 0x290, 0x2ae, 0x2cc, 0x2ea, 0x308, 0x326, 0x344, 0x362, 0x380, 0x39e, 0x3bc, 0x3da, 0x3f8, 0x416, 0x434, 0x452, 0x470, 0x48e, 0x4ac, 0x4ca, 0x4e8, 0x506, 0x524, 0x542, 0x560, 0x57e, 0x59c, 0x5ba, 0x5d8, 0x5f6, 0x614, 0x632, 0x650, 0x66e};
}
}
