#include "ds_div.h"
#include "host_tick.h"
#include "host_labels.h"
#include "town/TownBlockMap.h"
#include "uptr.h"
#include "item/Letter.h"
#include "player/PlayerId.h"
#include "sys/new.h"
#include "talk/EncodedString8.h"
#include "talk/MsgString25.h"
#include "talk/MsgString33.h"
#include "talk/MsgString9C.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "net/CommManager.h"
#include "actor/VillagerActor.h"
#include "npc/VillagerState.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "npc/VillagerId.h"
#include "npc/VillagerDataItemView.h"
#include "talk/EncodedStringBase.h"
#include "npc/VillagerStateTable.h"
#include "talk/MsgString.h"
#include "talk/EncodedString.h"
#include "talk/MsgString9B.h"
#include "game/EventDayEntry.h"





struct HousePos {
    u8 x;
    u8 z;
    HousePos();
    ~HousePos();
};

class VillagerDataItemView;
class LetterView;
#include "save/VillagerData.h"
#include "npc/VillagerPlan.h"
#include "npc/SickVillagerRecord.h"
#include "player/ErrandRecord.h"
#include "town/BlockMap.h"
#include "town/MapBlock.h"
#include "sys/ClockDate.h"





struct NullPlayerIdLocal : public PlayerId {
    NullPlayerIdLocal() : PlayerId((void *)NULL) {}
    ~NullPlayerIdLocal() { new (static_cast<PlayerId *>(this)) PlayerId(); }
    void clear() { PlayerId::clear(); }
};







class MsgString;




#include "talk/MsgString17B.h"
#include "talk/EncodedString10.h"
#include "talk/EncodedString16.h"
#include "talk/EncodedString16B.h"
#include "talk/MsgString11.h"


#include "talk/MsgString17.h"
#include "save/TownId.h"
#include "item/ItemPickSpec.h"
#include "item/LetterView.h"
#include "player/PlayerData.h"
#include "player/ForeignVillagerRecord.h"
#include "player/PlayerInventory.h"
#include "save/Pattern.h"
#include "save/TownExchangeRecord.h"
#include "sys/Heap.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_020b2c50.h"




struct SpNpcAnimHeapPool {
    void *p[4];
    SpNpcAnimHeapPool();
    ~SpNpcAnimHeapPool();
};
struct VillagerAnimHeapPool {
    void *p[8];
    VillagerAnimHeapPool();
    ~VillagerAnimHeapPool();
};
struct NpcTexPatBufPool {
    void *p[5];
    NpcTexPatBufPool();
    ~NpcTexPatBufPool();
};
class PlayerData;
typedef BOOL (*ImpressionCondFn)(PlayerData *player, s32 friendship, s32 mood);
struct ImpressionRule {
    s8 gender;
    ImpressionCondFn cond;
};
struct ClockDateTimeRaw {
    union {
        u32 v[2];
        u8 b[8];
        ClockDateTime dt;
    };
};

#include "proto/main/unk_02077ac4.h"
#include "proto/main/unk_02003008.h"
#include "proto/main/unk_020030d8.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0204cc1c.h"
#include "proto/main/unk_0209cb74.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_0204a780.h"
#define PROTO_LOCAL_StrBuf_ClearAlt
#define PROTO_LOCAL_EncodedString_SetRaw
#include "proto/main/unk_020501d4.h"
#define PROTO_LOCAL_EventSchedule_CollectDayAll
#include "proto/main/unk_0203f104.h"
#include "proto/main/unk_020a6974.h"
#include "proto/main/unk_02002b1c.h"


extern "C" {
void Villager_PickShownFurniture(VillagerData *p);
s32 Villager_IsFurnitureShown(VillagerData *p, s32 n);
void Villager_HideFurniture(VillagerData *p, s32 n);
void SaveVillagers_ClearTuneRequester(SaveVillagers *self);
void SaveVillagers_SetTuneRequester(SaveVillagers *self, VillagerId *u);
BOOL SaveVillagers_IsTuneRequester(SaveVillagers *self, VillagerId *u);
void OutdoorSchedule_Construct(OutdoorSchedule *p);
void OutdoorSchedule_Clear(OutdoorSchedule *self);
void OutdoorSchedule_ClearOutdoor(OutdoorSchedule *self);
BOOL OutdoorSchedule_SetOutdoorSlot(OutdoorSchedule *self, u32 i, s32 v);
s32 OutdoorSchedule_FindOutdoorSlotImpl(OutdoorSchedule *self, s32 x);
void OutdoorSchedule_RemoveOutdoor(OutdoorSchedule *self, s32 x);
void OutdoorSchedule_Remove(OutdoorSchedule *self, s32 x);
s32 OutdoorSchedule_FindOutdoorSlot(OutdoorSchedule *a, s32 b);
void OutdoorSchedule_ForceReroll(OutdoorSchedule *p);
BOOL OutdoorSchedule_IsRerollDue(OutdoorSchedule *self, ClockDateTime *out);
void OutdoorSchedule_PickRandom(OutdoorSchedule *self, s8 *out, s32 *cnt, s8 *list, u8 *players, s32 limit);
void OutdoorSchedule_AssignIndoor(OutdoorSchedule *self, s8 *list, s32 *cnt, VillagerState *slots);
void OutdoorSchedule_AssignOutdoor(OutdoorSchedule *self, s8 *list, s32 *cnt, VillagerState *slots, s32 n);
void OutdoorSchedule_AddBirthdayVisitor(OutdoorSchedule *self, s8 *out, s32 *cnt, s8 *list, u8 *players);
void OutdoorSchedule_ApplySleep(OutdoorSchedule *self, u8 *p, ClockDateTime *x);
void OutdoorSchedule_Reroll(OutdoorSchedule *self, u8 *p);
void OutdoorSchedule_Apply(OutdoorSchedule *self, u8 *p);
void OutdoorSchedule_Update(OutdoorSchedule *self, u8 *p, s32 keep);

extern u8 gFieldSceneKind;
extern BlockMap *gSceneBlockMap;
extern CommManager *gCommManager;
#define gSaveTownId HOST_LABEL(TownId *, gSaveTownId)
#define gSaveTownTune HOST_LABEL(long long *, gSaveTownTune)
s32 EventSchedule_CollectDayAll(EventDayEntry *out, const ClockDateTime *date);
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
void StrBuf_ClearAlt(EncodedStringBase *buf);
BOOL EncodedString_SetRaw(EncodedStringBase *buf, const void *src, s32 len);
extern const u8 sBadSpeciesPairs[4][2];
extern const u8 sAnimalKindByte2[36];
extern const u32 sLetterReplyGiftLists[3];
extern const u8 sPersonalityCompat[6][6];
extern const u16 sMonthlySickRoll[12];
extern const u8 sStarElementCompat[4][4];
extern const u8 sGoodSpeciesPairs[8][2];
extern const u8 sVillagerInfoTable[11700];
extern const u16 sPackedFurnitureItems[4];
extern const u8 sReservedErrandKinds[16];
extern const u32 sVillagerEventIds[11];
extern const u8 sSpNpcInfoTable[116];
extern const u8 sPersonalitySleepHours[6][4];
extern const ImpressionRule sImpressionRules[0x58];
extern const u32 sBirthdayGiftLists[3];
extern const u8 sStarSignEndDates[24];
extern const u8 sFurnitureTasteTextBase[8];
extern const s32 sRelationLevelThresholds[4];
void MI_CpuFill8(void *dst, u32 v, u32 n);
void MI_CpuCopy8(const void *src, void *dst, u32 n);
void __cxa_vec_ctor(void *array, size_t count, size_t size, void (*ctor)(void *), void (*dtor)(void *));
void __cxa_vec_cleanup(void *array, size_t count, size_t size, void (*dtor)(void *));
}


namespace nA {
extern "C" {

extern void *gSpNpcAnimPoolHeap;
extern void *gVillagerAnimPoolHeap;
extern void *gNpcTexPatBufHeap;
extern void *gCurrentHeap;
void *FrameHeap_Create(s32, void *);
void *Heap_AllocAligned(void *, s32, s32);
void File_LoadToBuffer(void *, void *, s32);
void SpNpcAnimPoolHeap_Destroy();
void SpNpcAnimPoolHeap_Create(void *parent);
void VillagerAnimPoolHeap_Destroy();
void VillagerAnimPoolHeap_Create(void *parent);
void NpcTexPatBufHeap_Destroy();
void NpcTexPatBufHeap_Create(void *parent);
void NpcModelHeap_Destroy();
void NpcModelHeap_Create(void *);
s32 NpcSpawn_GetSpNpcSlotCount();
s32 Scene_GetCurrent();
u8 Scene_GetMaxCharacters(s32);
u8 Scene_GetMaxPlayers(s32);
void *PlayerActor_GetCharacter(s32 id);
struct VillagerStateTable *VillagerStates_Get();
static inline BOOL Unk_02077d58_IsZero(u8 v)
{
    return v == 0 ? TRUE : FALSE;
}
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
static inline BOOL Unk_02077f68_R(u16 *p, u32 lo, u32 hi)
{
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}
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
}

namespace nB {
extern "C" {

BOOL Scene_InVillagerHouse();
BOOL Scene_InTown();
BOOL MapBlock_HasAllAttr(void *cell, s32 v);
static inline BOOL Unk_02078384_IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }
static inline MapBlock *Unk_02078738_GetCell(BlockMap *g, u32 x, u32 y) {
    if (x < g->width && y < g->height && g->blocks != NULL) {
        return &g->blocks[y * g->width + x];
    }
    return NULL;
}
}
}

namespace nC {
extern "C" {

struct Unk_020794ac_Entry { u8 *entries; u8 count; };
void *Insect_GetSpawnTable(s32);
}
}

namespace nD {
extern "C" {

void *Letter_GetSenderPlayer(void *);
void *Letter_GetRecipientVillager(void *);
s32 Scene_GetCurrent();
s32 Villager_SendBirthdayNoticeLetter(void *, void *);
void RoomScoreEvaluator_Construct(void *);
s32 HappyRoom_EvaluateVillagerRoom(void *evaluator, s32 b, u16 *c, s32 *d, s32 *e, s32 *f);
void RoomScoreEvaluator_Destruct(void *);
struct VillagerIdCopyLocal {
    u16 pad;
    VillagerId v;
    VillagerIdCopyLocal(void *p) { VillagerId_ConstructCopy(&v, (VillagerId *)p); }
    ~VillagerIdCopyLocal() { VillagerId_Destruct(&v); }
};
}
}

namespace nE {
extern "C" {

struct SickVillagerDateLocals {
    u8 date[4];
    ClockDateTimeWords time;
    u8 pad[4];
};
struct HouseVisitInviteGiftView {
    u8 pad_00[0x20];
    u8 giftKind : 3;
};
u32 EventAnnounce_GetCurrentEvent();
s32 Villager_MaybeCopyAblePattern(s32 a, s32 b);
s32 Villager_SendHouseVisitLetter(u32 a, PlayerId *b, VillagerId *c);
}
}

namespace nF {
extern "C" {

extern u8 data_021cc9ac[];
}
}

namespace nG {
extern "C" {

#define data_021e7f8c HOST_LABEL(u8 (*)[], data_021e7f8c)
}
}

namespace nH {
extern "C" {

BOOL SceneId_IsVillagerHouse(u32);
s32 SceneId_GetVillagerHouse(u32);
}
}

namespace nI {
extern "C" {

u8 LetterPaper_PickForPersonality(u32 i);
void Letter_ComposeVillagerMail(void *, u8 *, void *, u8 *, void *, void *, s32);
void Letter_ComposeVillagerMailZ(void *, u8 *, u8 *, u8 *, u8 *, void *, u8 *, void *, void *, s32);
s32 LetterDelivery_QueueOutgoing(void *, s32);
}
}

namespace nJ {
extern "C" {


static inline BOOL Unk_0207d3b0_InRange(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}
}
}

namespace nK {
extern "C" {

static inline BOOL Unk_0207d774_R(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}
namespace Unk_0207d67c_Ns {
}
static inline BOOL Unk_0207dd24_IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }
static inline BOOL Unk_0207dd24_Check(u16 *p) {
    BOOL f8 = TRUE, f7 = TRUE, f6 = TRUE, f5 = TRUE, f4 = TRUE, f3 = TRUE, f2 = TRUE, f1 = FALSE;
    u32 v = *p;
    if (v <= 5) f1 = TRUE;
    if (!f1) {
        if (v < 6 || v > 0xb) f2 = FALSE;
    }
    if (!f2) {
        if (v < 0xc || v > 0x11) f3 = FALSE;
    }
    if (!f3) {
        if ((v < 0x12 || v > 0x19) && v != 0x1c) f4 = FALSE;
    }
    if (!f4) {
        if ((v < 0x8a || v > 0x8f) && (v < 0x90 || v > 0x95) && (v < 0x96 || v > 0x9b) && (v < 0x9c || v > 0xa3) && v != 0xa5) f5 = FALSE;
    }
    if (!f5) {
        if (v != 0x1a) f6 = FALSE;
    }
    if (!f6) {
        if (v != 0xa4) f7 = FALSE;
    }
    if (!f7) {
        if (v != 0x1d) f8 = FALSE;
    }
    return f8;
}
static inline u16 *Unk_0207de6c_Cell(BlockMap *m, s32 x, s32 y) {
    s32 hx = x >> 4, hy = y >> 4;
    return (u16 *)BlockMap_GetItemPtr(m, hx, hy, x - (hx << 4), y - (hy << 4), 0);
}
BOOL Catalog_HasAllFish();
s32 Catalog_GetFishTotal(void);
s32 Catalog_CountFish(void);
s32 Catalog_HasAllInsects(void);
s32 Catalog_GetInsectTotal(void);
s32 Catalog_CountInsects(void);
s32 Weather_GetFallingPrecip(void);
void func_02133ef8(void *p, u32 n);
BOOL PlayerData_HasStungFace(void *p);
}
}

namespace nL {
extern "C" {

s32 Ftr_GetUnk05(u16 *);
s32 RoomFtrState_ResetVillagerHouse(s32);
void Item_ToPlacedForm(u16 *, u16 *, s32);
static inline BOOL Unk_0207e440_InRange(volatile u16 *p) {
    BOOL r = FALSE;
    u32 v1 = *p;
    u32 v2 = *p;
    if (v2 >= 0xf000 && v1 <= 0xf02f) r = TRUE;
    return r;
}
struct FurnitureDropSlots {
    s32 v[3];
};
}
}

namespace nM {
extern "C" {

s32 Item_GetFossilGroup(u16 *);
s32 RecycleBin_Add(u16);
void Item_ToPlacedForm(u16 *, u16 *, s32);
extern u8 __ptmf_null[];
static inline BOOL Unk_0207e940_InRange(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}
struct VillagerInfo28Bits {
    u8 v : 5;
};
}
}

namespace nN {
extern "C" {

struct EncodedString10Storage {
    u32 v[7];
};
u16 *PlayerId_GetTownId(void *p);
extern u32 data_021cc850;
extern u8 data_021cc8fc[];
extern u8 data_021cc868[];
struct Unk_0207fa50_Rec {
    u16 id;
    u8 pad[10];
};
}
}

namespace nO {
extern "C" {

void *Letter_GetSenderPlayer(void *p);
s32 TownId_GetNameString(void *a, void *b);
s32 MailText_SetSlot(s32 a, void *b);
s32 Villager_SendLetterWithPaper(void *a, u32 b, void *c, void *d, void *e, s32 f);
s32 ItemPick_One(void *a, void *b, void *c, void *d, s32 e, s32 f, void *g);
s32 MailCheck_GradeLetter(void *p);
s32 Letter_GetBodyLength(void *p);
void ItemPick_FromRange(u16 *out, s32 base, u32 cnt, u16 *list, u32 listLen, void *a5, s32 a6, s32 a7, void *rng, s32 a9);
static inline BOOL Unk_0207ff5c_B(s32 v) {
    if (v) {
        return TRUE;
    }
    return FALSE;
}
}
}

namespace nP {
extern "C" {

void *Letter_GetSenderPlayer(void *letter);
void Letter_Copy(void *dst, const void *src);
void Item_ToPlacedForm(u16 *, u16 *, s32);
void Letter_Clear(void *);
struct VillagerInfo {
    u8 pad_00[6];
    u16 furniture[10];
    u8 pad_1a[0x12];
    u16 shirt;
    u8 umbrella;
    u8 roomLayout;
    u8 wallpaper;
    u8 carpet;
    u8 trendTable[0x18];
    u8 personality;
};
}
}

namespace nQ {
extern "C" {

}
}

namespace nZ {
extern "C" {
}
}

namespace nZ {
extern "C" {
extern const u8 sBadSpeciesPairs[4][2] = {
    0x04, 0x1b, 0x09, 0x02, 0x00, 0x0a, 0x04, 0x20,
};
extern const u8 sAnimalKindByte2[36] = {
    0x00, 0x01, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x04, 0x00, 0x06, 0x00, 0x02, 0x01, 0x01, 0x00,
    0x03, 0x03, 0x00, 0x01, 0x02, 0x00, 0x02, 0x00, 0x01, 0x07, 0x04, 0x05, 0x00, 0x02, 0x02, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
VillagerData sTransferVillager;
extern const u32 sLetterReplyGiftLists[3] = {
    0x00000000, 0x00000004, 0x00000003,
};
extern const u8 sPersonalityCompat[6][6] = {
    0x28, 0x60, 0x08, 0x08, 0x28, 0x60, 0x60, 0x08, 0x28, 0x28, 0x60, 0x08, 0x08, 0x28, 0x60, 0x60,
    0x08, 0x28, 0x08, 0x28, 0x60, 0x28, 0x08, 0x60, 0x28, 0x60, 0x08, 0x08, 0x60, 0x28, 0x60, 0x08,
    0x28, 0x60, 0x28, 0x08,
};
extern const u16 sMonthlySickRoll[12] = {
    0x0c00, 0x0c00, 0x0800, 0x0c00, 0x0c00, 0x0800, 0x0c00, 0x0c00, 0x0800, 0x0c00, 0x0800, 0x0c00,
};
Unk_0207ed1c_Fn sVillagerTrendFilters[5] = {
    &VillagerDataItemView::isInsectItem, &VillagerDataItemView::isFishItem, &VillagerDataItemView::isFossilItem,
    &VillagerDataItemView::isShirtItem, &VillagerDataItemView::isTasteFurniture,
};
extern const u8 sStarElementCompat[4][4] = {
    0x80, 0x00, 0x30, 0x30, 0x00, 0x80, 0x30, 0x30, 0x30, 0x30, 0x80, 0x00, 0x30, 0x30, 0x00, 0x80,
};
extern const u8 sGoodSpeciesPairs[8][2] = {
    0x04, 0x09, 0x0d, 0x0e, 0x1d, 0x15, 0x03, 0x19, 0x05, 0x0a, 0x12, 0x02, 0x13, 0x00, 0x00, 0x00,
};
VillagerStateTable gVillagerStates;
u8 sVillagerLetterPath[0x28];
NpcTexPatBufPool sNpcTexPatBufPool;
extern const u8 sVillagerInfoTable[11700] = {
    0x8f, 0x9d, 0x74, 0x60, 0x01, 0x00, 0x88, 0x34, 0xb8, 0x37, 0xb8, 0x37, 0x6c, 0x34, 0x24, 0x30,
    0x84, 0x34, 0x44, 0x47, 0x80, 0x34, 0x7c, 0x34, 0xf1, 0xff, 0x02, 0x01, 0x01, 0x05, 0x01, 0x01,
    0x03, 0x01, 0x04, 0x00, 0x04, 0x04, 0x03, 0x09, 0x00, 0x02, 0x08, 0x00, 0x29, 0x00, 0x04, 0x23,
    0x2f, 0x22, 0x23, 0x28, 0x19, 0x0a, 0x14, 0x1e, 0x0f, 0x2d, 0x33, 0x13, 0x33, 0x07, 0x00, 0x08,
    0xcd, 0x08, 0x66, 0x0a, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x0c, 0x02, 0x01, 0x14, 0x11, 0x8a, 0x99,
    0x69, 0x74, 0x02, 0x00, 0x08, 0x33, 0xf1, 0xff, 0xd4, 0x37, 0xa8, 0x36, 0xb0, 0x36, 0xc8, 0x36,
    0x90, 0x36, 0x10, 0x33, 0x38, 0x37, 0x8c, 0x36, 0x02, 0x02, 0x01, 0x02, 0x01, 0x01, 0x03, 0x03,
    0x04, 0x04, 0x04, 0x07, 0x0a, 0x14, 0x21, 0x02, 0x09, 0x00, 0x1b, 0x00, 0x01, 0x17, 0x39, 0x3a,
    0x19, 0x28, 0x05, 0x1e, 0x14, 0x23, 0x32, 0x0a, 0x33, 0x13, 0x00, 0x08, 0x00, 0x04, 0x00, 0x08,
    0x66, 0x06, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x0a, 0x01, 0x01, 0x14, 0x11, 0x67, 0x8b, 0x9a, 0x74,
    0x0e, 0x00, 0x40, 0x30, 0x68, 0x30, 0x34, 0x30, 0xf1, 0xff, 0x20, 0x30, 0x50, 0x46, 0x3c, 0x37,
    0x50, 0x35, 0x74, 0x30, 0x4c, 0x36, 0x02, 0x01, 0x01, 0x02, 0x01, 0x05, 0x03, 0x00, 0x04, 0x02,
    0x04, 0x00, 0x0b, 0x09, 0x62, 0x03, 0x01, 0x00, 0xa0, 0x00, 0x0d, 0x17, 0x2b, 0x00, 0x2d, 0x14,
    0x0a, 0x32, 0x1e, 0x23, 0x0f, 0x19, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04,
    0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x04, 0x01, 0x14, 0x17, 0xc2, 0x9e, 0x58, 0x48, 0x4e, 0x00,
    0xc8, 0x30, 0xf4, 0x30, 0xec, 0x30, 0x0c, 0x30, 0xf1, 0xff, 0xe8, 0x30, 0x3c, 0x37, 0x60, 0x36,
    0xd8, 0x37, 0x40, 0x36, 0x00, 0x01, 0x01, 0x06, 0x01, 0x09, 0x03, 0x01, 0x04, 0x01, 0x04, 0x08,
    0x02, 0x10, 0x31, 0x00, 0x04, 0x00, 0xbe, 0x00, 0x0c, 0x20, 0x27, 0x19, 0x0f, 0x0a, 0x28, 0x23,
    0x32, 0x1e, 0x05, 0x14, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06,
    0xcd, 0x04, 0x66, 0x06, 0x04, 0x01, 0x14, 0x12, 0xdd, 0x8e, 0x56, 0x3f, 0x03, 0x00, 0x40, 0x35,
    0xf1, 0xff, 0x18, 0x37, 0x44, 0x37, 0xe0, 0x33, 0x74, 0x36, 0x1c, 0x34, 0xb4, 0x35, 0x3c, 0x34,
    0xe4, 0x33, 0x00, 0x02, 0x01, 0x09, 0x01, 0x04, 0x03, 0x00, 0x04, 0x09, 0x04, 0x03, 0x09, 0x1a,
    0x42, 0x07, 0x04, 0x00, 0x19, 0x00, 0x04, 0x06, 0x1d, 0x28, 0x14, 0x19, 0x28, 0x0f, 0x23, 0x1e,
    0x32, 0x0a, 0x66, 0x06, 0x9a, 0x09, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x08, 0x66, 0x06,
    0xcd, 0x0c, 0x01, 0x00, 0x03, 0x30, 0xd8, 0x77, 0x63, 0x4e, 0x04, 0x00, 0x50, 0x30, 0x20, 0x30,
    0x24, 0x30, 0x0c, 0x30, 0xc4, 0x37, 0xc0, 0x46, 0xd8, 0x3f, 0xf4, 0x45, 0xa0, 0x43, 0xb0, 0x46,
    0x00, 0x01, 0x01, 0x05, 0x01, 0x06, 0x03, 0x01, 0x04, 0x02, 0x04, 0x02, 0x09, 0x09, 0x63, 0x00,
    0x03, 0x00, 0x4a, 0x00, 0x0a, 0x16, 0x32, 0x33, 0x1e, 0x00, 0x0a, 0x28, 0x1e, 0x14, 0x0f, 0x32,
    0x00, 0x08, 0x33, 0x13, 0x00, 0x08, 0xcd, 0x08, 0x66, 0x0a, 0x66, 0x06, 0x9a, 0x05, 0xcd, 0x08,
    0x04, 0x00, 0x03, 0x16, 0xa1, 0x7b, 0x69, 0x7b, 0x05, 0x00, 0x40, 0x30, 0xf1, 0xff, 0xf1, 0xff,
    0x4c, 0x34, 0x70, 0x36, 0x58, 0x46, 0xf8, 0x40, 0x1c, 0x3c, 0x68, 0x36, 0x18, 0x3c, 0x01, 0x07,
    0x02, 0x01, 0x03, 0x00, 0x03, 0x03, 0x04, 0x03, 0x04, 0x00, 0x07, 0x01, 0x04, 0x02, 0x04, 0x00,
    0x11, 0x00, 0x04, 0x04, 0x29, 0x2d, 0x28, 0x0a, 0x32, 0x14, 0x19, 0x00, 0x2d, 0x19, 0x33, 0x07,
    0x9a, 0x11, 0x33, 0x13, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a, 0x02, 0x00,
    0x03, 0x04, 0xdf, 0x81, 0x4f, 0x51, 0x06, 0x00, 0x00, 0x30, 0x20, 0x30, 0x30, 0x44, 0x30, 0x44,
    0xf1, 0xff, 0x44, 0x36, 0xec, 0x45, 0x1c, 0x30, 0x18, 0x30, 0x10, 0x30, 0x01, 0x0a, 0x02, 0x02,
    0x01, 0x07, 0x03, 0x00, 0x04, 0x07, 0x04, 0x0b, 0x07, 0x16, 0x25, 0x09, 0x00, 0x00, 0x95, 0x00,
    0x05, 0x13, 0x2d, 0x1e, 0x14, 0x32, 0x28, 0x1e, 0x05, 0x0f, 0x14, 0x1e, 0x66, 0x0a, 0x33, 0x13,
    0x33, 0x07, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x08, 0x9a, 0x11, 0xcd, 0x0c, 0x02, 0x00, 0x03, 0x15,
    0x49, 0x63, 0xf7, 0x5d, 0x07, 0x00, 0x50, 0x30, 0xf1, 0xff, 0xf1, 0xff, 0xc8, 0x37, 0x4c, 0x35,
    0x28, 0x35, 0x7c, 0x37, 0x3c, 0x37, 0x20, 0x35, 0x24, 0x35, 0x03, 0x00, 0x04, 0x02, 0x00, 0x01,
    0x03, 0x01, 0x00, 0x01, 0x04, 0x07, 0x07, 0x11, 0x46, 0x03, 0x07, 0x00, 0x06, 0x00, 0x08, 0x07,
    0x1e, 0x02, 0x05, 0x23, 0x2d, 0x00, 0x0a, 0x1e, 0x1e, 0x28, 0x33, 0x13, 0x33, 0x13, 0x00, 0x08,
    0xcd, 0x08, 0x66, 0x0a, 0x66, 0x06, 0x9a, 0x05, 0x00, 0x0c, 0x01, 0x00, 0x0f, 0x02, 0x5d, 0x74,
    0xcf, 0x60, 0x08, 0x00, 0xf8, 0x34, 0x88, 0x30, 0xec, 0x43, 0x6c, 0x30, 0xf1, 0xff, 0xa8, 0x37,
    0x58, 0x36, 0x1c, 0x30, 0xa8, 0x37, 0x2c, 0x37, 0x01, 0x05, 0x00, 0x01, 0x01, 0x09, 0x03, 0x00,
    0x04, 0x04, 0x04, 0x00, 0x0c, 0x04, 0x67, 0x07, 0x06, 0x00, 0xb0, 0x00, 0x07, 0x10, 0x2b, 0x1f,
    0x05, 0x23, 0x19, 0x32, 0x0a, 0x23, 0x1e, 0x28, 0x00, 0x08, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x11,
    0x9a, 0x11, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a, 0x05, 0x00, 0x0f, 0x0a, 0x54, 0x72, 0xd3, 0x67,
    0x09, 0x00, 0xb4, 0x30, 0x10, 0x31, 0xf1, 0xff, 0x44, 0x37, 0xf1, 0xff, 0xa8, 0x35, 0xa8, 0x35,
    0xa8, 0x35, 0xa8, 0x35, 0xa8, 0x35, 0x00, 0x01, 0x01, 0x09, 0x01, 0x06, 0x03, 0x00, 0x04, 0x07,
    0x02, 0x02, 0x03, 0x04, 0x08, 0x04, 0x08, 0x00, 0x6f, 0x00, 0x08, 0x1e, 0x06, 0x25, 0x32, 0x0a,
    0x2d, 0x14, 0x28, 0x1e, 0x23, 0x14, 0x33, 0x07, 0x33, 0x07, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x09,
    0x00, 0x08, 0x9a, 0x11, 0xcd, 0x0c, 0x00, 0x00, 0x0f, 0x1c, 0x4a, 0x74, 0xe3, 0x5f, 0x1f, 0x00,
    0xf1, 0xff, 0xb8, 0x30, 0x24, 0x37, 0xa4, 0x30, 0x28, 0x30, 0xe8, 0x30, 0x20, 0x34, 0xa4, 0x47,
    0x60, 0x36, 0x98, 0x47, 0x01, 0x05, 0x01, 0x03, 0x04, 0x05, 0x03, 0x03, 0x04, 0x04, 0x04, 0x02,
    0x07, 0x0d, 0x2e, 0x09, 0x02, 0x00, 0x5a, 0x00, 0x00, 0x0b, 0x03, 0x17, 0x19, 0x23, 0x14, 0x00,
    0x32, 0x28, 0x0a, 0x1e, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06,
    0xcd, 0x04, 0x66, 0x06, 0x04, 0x00, 0x0f, 0x0b, 0x80, 0x80, 0x80, 0x80, 0x32, 0x00, 0x08, 0x33,
    0x00, 0x33, 0xf1, 0xff, 0xa8, 0x36, 0xf1, 0xff, 0xc0, 0x32, 0x38, 0x37, 0xdc, 0x46, 0xc0, 0x32,
    0x14, 0x33, 0x01, 0x01, 0x01, 0x05, 0x04, 0x05, 0x03, 0x00, 0x04, 0x08, 0x02, 0x01, 0x02, 0x02,
    0x66, 0x07, 0x00, 0x00, 0xe7, 0x00, 0x01, 0x09, 0x25, 0x12, 0x23, 0x28, 0x0a, 0x0f, 0x19, 0x1e,
    0x32, 0x14, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04,
    0x66, 0x06, 0x01, 0x01, 0x0f, 0x09, 0xcb, 0xc0, 0x4c, 0x29, 0x0a, 0x00, 0x40, 0x30, 0x48, 0x37,
    0x2c, 0x30, 0xc8, 0x37, 0x9c, 0x35, 0x6c, 0x35, 0xa4, 0x35, 0x7c, 0x37, 0x6c, 0x35, 0x7c, 0x37,
    0x02, 0x02, 0x04, 0x06, 0x01, 0x07, 0x03, 0x01, 0x04, 0x09, 0x04, 0x04, 0x04, 0x1e, 0x29, 0x06,
    0x05, 0x00, 0x8f, 0x00, 0x1d, 0x1a, 0x35, 0x21, 0x0a, 0x1e, 0x0f, 0x28, 0x1e, 0x14, 0x19, 0x32,
    0x9a, 0x11, 0x00, 0x08, 0x00, 0x08, 0xcd, 0x08, 0x66, 0x0a, 0x9a, 0x11, 0x9a, 0x05, 0xcd, 0x08,
    0x02, 0x00, 0x0d, 0x33, 0x80, 0x80, 0x80, 0x80, 0x32, 0x00, 0xb4, 0x30, 0x24, 0x37, 0x4c, 0x34,
    0xa0, 0x30, 0x38, 0x31, 0x34, 0x34, 0xec, 0x36, 0x64, 0x34, 0x88, 0x47, 0x94, 0x47, 0x01, 0x0c,
    0x02, 0x01, 0x04, 0x05, 0x03, 0x00, 0x04, 0x09, 0x03, 0x03, 0x0a, 0x1d, 0x0a, 0x03, 0x00, 0x00,
    0x3e, 0x00, 0x11, 0x23, 0x19, 0x18, 0x19, 0x32, 0x0a, 0x2d, 0x1e, 0x14, 0x0f, 0x28, 0x66, 0x06,
    0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x00, 0x00,
    0x0d, 0x1d, 0x70, 0x68, 0xd1, 0x57, 0x0b, 0x00, 0x7c, 0x31, 0x74, 0x31, 0x8c, 0x31, 0x68, 0x31,
    0x6c, 0x31, 0x80, 0x31, 0x88, 0x31, 0x70, 0x31, 0x78, 0x31, 0x84, 0x31, 0x00, 0x02, 0x02, 0x01,
    0x01, 0x05, 0x01, 0x0c, 0x04, 0x0b, 0x04, 0x09, 0x01, 0x01, 0x4a, 0x01, 0x08, 0x00, 0x78, 0x00,
    0x00, 0x20, 0x0a, 0x0a, 0x0a, 0x05, 0x28, 0x1e, 0x23, 0x0a, 0x14, 0x32, 0x66, 0x06, 0x9a, 0x11,
    0x00, 0x04, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x05, 0x9a, 0x11, 0x66, 0x0a, 0x00, 0x00, 0x00, 0x1c,
    0x52, 0x59, 0xd9, 0x7c, 0x0c, 0x00, 0xb4, 0x30, 0xe4, 0x30, 0xec, 0x30, 0xa0, 0x30, 0xcc, 0x30,
    0x3c, 0x35, 0xa4, 0x47, 0x10, 0x30, 0x5c, 0x36, 0x38, 0x37, 0x01, 0x04, 0x03, 0x03, 0x01, 0x0a,
    0x03, 0x00, 0x04, 0x02, 0x04, 0x05, 0x09, 0x19, 0x6b, 0x07, 0x09, 0x00, 0x51, 0x00, 0x0b, 0x0a,
    0x06, 0x03, 0x1e, 0x19, 0x0f, 0x19, 0x23, 0x28, 0x14, 0x0a, 0x00, 0x08, 0x9a, 0x11, 0x33, 0x07,
    0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x09, 0x03, 0x00, 0x00, 0x03, 0x66, 0x5f,
    0xcb, 0x70, 0x0d, 0x00, 0xb4, 0x30, 0x4c, 0x34, 0x44, 0x37, 0x10, 0x31, 0xd4, 0x37, 0xe4, 0x32,
    0x54, 0x37, 0xc0, 0x34, 0xcc, 0x36, 0x80, 0x37, 0x01, 0x0a, 0x02, 0x01, 0x04, 0x01, 0x03, 0x03,
    0x04, 0x07, 0x04, 0x08, 0x02, 0x1b, 0x0c, 0x00, 0x04, 0x00, 0x4a, 0x00, 0x0c, 0x0b, 0x18, 0x30,
    0x00, 0x0a, 0x23, 0x2d, 0x28, 0x14, 0x19, 0x05, 0x33, 0x07, 0x33, 0x07, 0x00, 0x08, 0x9a, 0x11,
    0x9a, 0x11, 0x66, 0x06, 0x9a, 0x05, 0x00, 0x0c, 0x04, 0x00, 0x00, 0x1b, 0x66, 0x50, 0xbd, 0x8d,
    0x0e, 0x00, 0x44, 0x35, 0x88, 0x30, 0x44, 0x37, 0x98, 0x30, 0x7c, 0x30, 0x28, 0x35, 0x80, 0x30,
    0x58, 0x36, 0x90, 0x30, 0x9c, 0x30, 0x01, 0x06, 0x02, 0x02, 0x01, 0x05, 0x03, 0x03, 0x04, 0x01,
    0x04, 0x04, 0x02, 0x03, 0x2d, 0x08, 0x04, 0x00, 0x73, 0x00, 0x18, 0x23, 0x1e, 0x02, 0x19, 0x28,
    0x14, 0x2d, 0x32, 0x19, 0x1e, 0x1e, 0x66, 0x0a, 0x00, 0x08, 0x00, 0x04, 0x9a, 0x11, 0x66, 0x06,
    0x9a, 0x11, 0x00, 0x08, 0x66, 0x0a, 0x05, 0x00, 0x00, 0x36, 0x61, 0x5b, 0xbf, 0x85, 0x0f, 0x00,
    0xf8, 0x34, 0xf1, 0xff, 0x44, 0x37, 0x34, 0x30, 0x2c, 0x30, 0xe0, 0x30, 0xf4, 0x34, 0x38, 0x34,
    0x3c, 0x47, 0x34, 0x34, 0x01, 0x07, 0x00, 0x02, 0x01, 0x01, 0x03, 0x00, 0x04, 0x04, 0x04, 0x00,
    0x0a, 0x08, 0x4e, 0x02, 0x03, 0x00, 0x6b, 0x00, 0x05, 0x0e, 0x18, 0x26, 0x0f, 0x1e, 0x00, 0x32,
    0x28, 0x0a, 0x28, 0x23, 0x66, 0x06, 0x9a, 0x09, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x11, 0x00, 0x08,
    0x9a, 0x11, 0xcd, 0x0c, 0x03, 0x00, 0x00, 0x28, 0x70, 0x64, 0xc8, 0x64, 0x10, 0x00, 0xe0, 0x34,
    0xc8, 0x37, 0x8c, 0x31, 0xc0, 0x37, 0xcc, 0x30, 0xd0, 0x34, 0xc8, 0x34, 0xd4, 0x34, 0xe8, 0x34,
    0xcc, 0x34, 0x01, 0x03, 0x01, 0x01, 0x01, 0x0c, 0x03, 0x03, 0x04, 0x01, 0x04, 0x04, 0x06, 0x11,
    0x6f, 0x05, 0x04, 0x00, 0x42, 0x00, 0x0f, 0x20, 0x1f, 0x2f, 0x0a, 0x00, 0x1e, 0x32, 0x19, 0x28,
    0x14, 0x23, 0x00, 0x08, 0x33, 0x03, 0x9a, 0x11, 0x9a, 0x11, 0x66, 0x0a, 0x66, 0x06, 0x9a, 0x05,
    0xcd, 0x08, 0x04, 0x00, 0x00, 0x33, 0x71, 0x80, 0xbb, 0x54, 0x11, 0x00, 0xb4, 0x30, 0xb0, 0x30,
    0x24, 0x37, 0xb8, 0x30, 0xa0, 0x30, 0x34, 0x34, 0x78, 0x37, 0x88, 0x36, 0x90, 0x36, 0x78, 0x37,
    0x00, 0x02, 0x01, 0x05, 0x03, 0x03, 0x03, 0x00, 0x04, 0x05, 0x04, 0x09, 0x04, 0x0b, 0x10, 0x05,
    0x03, 0x00, 0x65, 0x00, 0x07, 0x22, 0x18, 0x05, 0x19, 0x32, 0x19, 0x28, 0x14, 0x05, 0x1e, 0x0f,
    0x9a, 0x11, 0x33, 0x07, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a,
    0x00, 0x00, 0x00, 0x23, 0x6d, 0x5e, 0xbe, 0x77, 0x12, 0x00, 0x00, 0x30, 0x60, 0x30, 0x28, 0x37,
    0xe4, 0x30, 0x20, 0x30, 0xdc, 0x46, 0x58, 0x37, 0xa8, 0x37, 0x48, 0x34, 0x60, 0x36, 0x01, 0x04,
    0x01, 0x09, 0x00, 0x01, 0x03, 0x00, 0x04, 0x04, 0x04, 0x00, 0x05, 0x1d, 0x31, 0x05, 0x03, 0x00,
    0xba, 0x00, 0x0f, 0x08, 0x24, 0x17, 0x28, 0x1e, 0x23, 0x23, 0x14, 0x0a, 0x1e, 0x19, 0x66, 0x0a,
    0x00, 0x08, 0x33, 0x07, 0x9a, 0x11, 0x9a, 0x09, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x09, 0x05, 0x00,
    0x00, 0x03, 0x84, 0x7a, 0xab, 0x5a, 0x13, 0x00, 0x04, 0x31, 0x6c, 0x31, 0xf1, 0xff, 0xa0, 0x30,
    0x30, 0x37, 0xbc, 0x33, 0xc0, 0x33, 0xc8, 0x33, 0xcc, 0x33, 0xd0, 0x33, 0x00, 0x02, 0x01, 0x05,
    0x03, 0x03, 0x03, 0x01, 0x04, 0x00, 0x04, 0x03, 0x01, 0x0c, 0x52, 0x09, 0x07, 0x00, 0x12, 0x00,
    0x12, 0x1e, 0x08, 0x26, 0x00, 0x14, 0x23, 0x19, 0x28, 0x1e, 0x32, 0x0a, 0x66, 0x06, 0x9a, 0x11,
    0x00, 0x08, 0xcd, 0x08, 0x66, 0x0a, 0x66, 0x06, 0x9a, 0x11, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x1c,
    0x91, 0x66, 0xa9, 0x60, 0x14, 0x00, 0x88, 0x34, 0xf1, 0xff, 0x70, 0x34, 0x34, 0x44, 0xb8, 0x37,
    0x40, 0x37, 0x48, 0x35, 0x18, 0x46, 0x0c, 0x34, 0xfc, 0x37, 0x01, 0x04, 0x01, 0x0b, 0x01, 0x09,
    0x03, 0x03, 0x04, 0x02, 0x04, 0x00, 0x0b, 0x1d, 0x73, 0x06, 0x05, 0x00, 0x2a, 0x00, 0x04, 0x20,
    0x22, 0x22, 0x0f, 0x28, 0x19, 0x0a, 0x14, 0x05, 0x23, 0x2d, 0x00, 0x08, 0x33, 0x03, 0x00, 0x04,
    0x9a, 0x11, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a, 0x02, 0x01, 0x00, 0x19, 0x90, 0x80,
    0xc0, 0x30, 0x15, 0x00, 0x94, 0x35, 0xa8, 0x36, 0xb0, 0x37, 0x88, 0x32, 0xe0, 0x32, 0xb8, 0x32,
    0x74, 0x36, 0xd0, 0x31, 0x60, 0x35, 0xf4, 0x33, 0x01, 0x02, 0x02, 0x01, 0x01, 0x0c, 0x03, 0x00,
    0x04, 0x0b, 0x04, 0x05, 0x08, 0x01, 0x00, 0x01, 0x02, 0x00, 0x1e, 0x00, 0x06, 0x25, 0x3b, 0x3c,
    0x2d, 0x14, 0x0a, 0x23, 0x1e, 0x19, 0x28, 0x19, 0x33, 0x07, 0x33, 0x07, 0x33, 0x07, 0x9a, 0x11,
    0x9a, 0x11, 0x00, 0x08, 0x66, 0x06, 0xcd, 0x0c, 0x01, 0x01, 0x00, 0x2d, 0x62, 0x55, 0xc3, 0x86,
    0x54, 0x00, 0x90, 0x31, 0x94, 0x31, 0xa8, 0x31, 0x44, 0x37, 0xc8, 0x37, 0xb4, 0x31, 0x08, 0x35,
    0x9c, 0x31, 0x00, 0x35, 0xac, 0x31, 0x01, 0x0a, 0x01, 0x09, 0x01, 0x05, 0x03, 0x03, 0x04, 0x01,
    0x04, 0x02, 0x09, 0x1e, 0x2e, 0x00, 0x01, 0x00, 0xb3, 0x00, 0x05, 0x00, 0x19, 0x18, 0x0a, 0x14,
    0x05, 0x1e, 0x32, 0x28, 0x23, 0x14, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04,
    0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x05, 0x00, 0x00, 0x03, 0x83, 0x75, 0xa5, 0x63, 0x03, 0x00,
    0x40, 0x31, 0x5c, 0x31, 0x4c, 0x34, 0xf1, 0xff, 0x58, 0x31, 0x48, 0x34, 0x0c, 0x36, 0x38, 0x37,
    0x10, 0x36, 0x68, 0x34, 0x00, 0x01, 0x01, 0x0b, 0x01, 0x06, 0x03, 0x00, 0x04, 0x07, 0x04, 0x01,
    0x08, 0x0d, 0x11, 0x09, 0x07, 0x00, 0xd4, 0x00, 0x07, 0x19, 0x37, 0x38, 0x28, 0x14, 0x1e, 0x23,
    0x19, 0x0a, 0x1e, 0x05, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06,
    0xcd, 0x04, 0x66, 0x06, 0x04, 0x00, 0x00, 0x39, 0x73, 0xba, 0x65, 0x6e, 0x19, 0x00, 0xb4, 0x30,
    0x34, 0x44, 0xa0, 0x30, 0xdc, 0x30, 0xb0, 0x30, 0xa8, 0x30, 0x38, 0x37, 0xc0, 0x30, 0x38, 0x36,
    0x34, 0x35, 0x02, 0x01, 0x03, 0x00, 0x01, 0x05, 0x03, 0x03, 0x04, 0x0a, 0x04, 0x0b, 0x06, 0x18,
    0x04, 0x05, 0x03, 0x00, 0x60, 0x00, 0x11, 0x11, 0x00, 0x04, 0x2d, 0x19, 0x0f, 0x14, 0x23, 0x1e,
    0x05, 0x0a, 0x33, 0x07, 0x33, 0x07, 0x00, 0x08, 0xcd, 0x08, 0x9a, 0x11, 0x9a, 0x11, 0x9a, 0x05,
    0x00, 0x0c, 0x04, 0x00, 0x19, 0x0f, 0x5c, 0xa6, 0x5d, 0xa1, 0x1a, 0x00, 0x40, 0x30, 0x44, 0x37,
    0x04, 0x38, 0x34, 0x30, 0x44, 0x30, 0x38, 0x46, 0x20, 0x34, 0x1c, 0x34, 0x3c, 0x46, 0x20, 0x34,
    0x00, 0x02, 0x01, 0x09, 0x03, 0x03, 0x04, 0x03, 0x04, 0x02, 0x04, 0x08, 0x06, 0x0f, 0x25, 0x00,
    0x09, 0x00, 0x72, 0x00, 0x14, 0x1a, 0x03, 0x03, 0x05, 0x19, 0x1e, 0x23, 0x28, 0x14, 0x14, 0x0a,
    0x66, 0x0a, 0x00, 0x08, 0x00, 0x04, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x0a,
    0x03, 0x00, 0x19, 0x35, 0x69, 0xa2, 0x68, 0x8d, 0x1b, 0x00, 0x40, 0x31, 0xc8, 0x37, 0xf1, 0xff,
    0xec, 0x35, 0x60, 0x31, 0x54, 0x36, 0x68, 0x47, 0x64, 0x30, 0x80, 0x46, 0x88, 0x47, 0x00, 0x02,
    0x01, 0x07, 0x01, 0x06, 0x03, 0x00, 0x04, 0x07, 0x04, 0x06, 0x01, 0x02, 0x46, 0x02, 0x04, 0x00,
    0x48, 0x00, 0x17, 0x21, 0x28, 0x34, 0x1e, 0x0a, 0x23, 0x00, 0x2d, 0x14, 0x32, 0x19, 0x66, 0x06,
    0x9a, 0x11, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x08, 0x66, 0x06, 0xcd, 0x0c, 0x01, 0x00,
    0x19, 0x14, 0x65, 0xce, 0x5d, 0x70, 0x1c, 0x00, 0x98, 0x34, 0x2c, 0x33, 0xec, 0x35, 0xf1, 0xff,
    0xdc, 0x33, 0xf0, 0x37, 0x38, 0x37, 0x94, 0x37, 0xfc, 0x37, 0x78, 0x47, 0x00, 0x02, 0x01, 0x01,
    0x01, 0x0c, 0x03, 0x00, 0x04, 0x05, 0x04, 0x0b, 0x06, 0x0b, 0x67, 0x09, 0x00, 0x00, 0x87, 0x00,
    0x09, 0x11, 0x1e, 0x08, 0x14, 0x2d, 0x1e, 0x14, 0x0a, 0x28, 0x00, 0x32, 0x00, 0x08, 0x33, 0x03,
    0x9a, 0x11, 0xcd, 0x08, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x05, 0xcd, 0x08, 0x00, 0x00, 0x19, 0x1b,
    0x90, 0xaf, 0x75, 0x4c, 0x4b, 0x00, 0x5c, 0x32, 0xf1, 0xff, 0x30, 0x44, 0xec, 0x43, 0x34, 0x44,
    0x18, 0x35, 0x50, 0x34, 0x54, 0x34, 0x18, 0x47, 0x10, 0x46, 0x01, 0x04, 0x01, 0x0b, 0x03, 0x03,
    0x04, 0x00, 0x04, 0x04, 0x04, 0x02, 0x09, 0x1c, 0x69, 0x01, 0x06, 0x00, 0x80, 0x00, 0x16, 0x24,
    0x31, 0x00, 0x28, 0x19, 0x14, 0x2d, 0x0f, 0x0a, 0x32, 0x1e, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04,
    0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x01, 0x00, 0x19, 0x28, 0x80, 0x80,
    0x80, 0x80, 0x32, 0x00, 0x48, 0x33, 0x2c, 0x33, 0x6c, 0x31, 0x8c, 0x31, 0x00, 0x33, 0x0c, 0x31,
    0xf1, 0xff, 0x44, 0x33, 0x1c, 0x38, 0xf1, 0xff, 0x01, 0x0b, 0x01, 0x0c, 0x04, 0x06, 0x03, 0x01,
    0x04, 0x04, 0x04, 0x07, 0x02, 0x0a, 0x23, 0x05, 0x01, 0x00, 0x95, 0x00, 0x01, 0x16, 0x13, 0x13,
    0x1e, 0x1e, 0x14, 0x23, 0x00, 0x2d, 0x28, 0x05, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09,
    0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x00, 0x00, 0x19, 0x07, 0x94, 0x9c, 0x8b, 0x45,
    0x16, 0x00, 0x40, 0x30, 0x34, 0x30, 0x44, 0x37, 0x28, 0x30, 0xf1, 0xff, 0x4c, 0x36, 0x10, 0x30,
    0x64, 0x30, 0x44, 0x33, 0x38, 0x30, 0x01, 0x09, 0x02, 0x02, 0x01, 0x04, 0x03, 0x03, 0x04, 0x03,
    0x04, 0x08, 0x0a, 0x04, 0x21, 0x04, 0x06, 0x00, 0xbe, 0x00, 0x04, 0x0e, 0x27, 0x32, 0x1e, 0x23,
    0x05, 0x32, 0x0a, 0x00, 0x28, 0x14, 0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08, 0xcd, 0x08, 0x66, 0x0a,
    0x66, 0x06, 0x9a, 0x05, 0xcd, 0x08, 0x01, 0x00, 0x0c, 0x28, 0x79, 0xc3, 0x78, 0x4c, 0x17, 0x00,
    0xb4, 0x36, 0xf1, 0xff, 0x88, 0x32, 0x88, 0x32, 0xdc, 0x33, 0xa4, 0x32, 0xa8, 0x32, 0xb8, 0x32,
    0x9c, 0x32, 0x98, 0x46, 0x01, 0x02, 0x00, 0x02, 0x01, 0x0c, 0x03, 0x03, 0x01, 0x0a, 0x04, 0x0b,
    0x0a, 0x0a, 0x42, 0x04, 0x01, 0x00, 0x02, 0x00, 0x0f, 0x16, 0x12, 0x10, 0x2d, 0x19, 0x19, 0x14,
    0x0a, 0x00, 0x0f, 0x1e, 0x66, 0x06, 0x9a, 0x09, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x05,
    0x9a, 0x11, 0x66, 0x0a, 0x00, 0x00, 0x0c, 0x35, 0x74, 0xd3, 0x7f, 0x3a, 0x18, 0x00, 0xcc, 0x31,
    0xf1, 0xff, 0xf1, 0xff, 0xc8, 0x37, 0x70, 0x32, 0x54, 0x47, 0xd8, 0x31, 0x50, 0x47, 0x18, 0x45,
    0xd0, 0x31, 0x01, 0x01, 0x00, 0x01, 0x01, 0x0c, 0x03, 0x00, 0x04, 0x0a, 0x04, 0x09, 0x0a, 0x0e,
    0x63, 0x02, 0x09, 0x00, 0x8b, 0x00, 0x07, 0x00, 0x1a, 0x05, 0x0a, 0x1e, 0x32, 0x28, 0x14, 0x2d,
    0x1e, 0x14, 0x00, 0x08, 0x33, 0x03, 0x33, 0x07, 0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x06,
    0x9a, 0x09, 0x00, 0x00, 0x0c, 0x25, 0xba, 0xa4, 0x59, 0x49, 0x1d, 0x00, 0xc8, 0x30, 0xf1, 0xff,
    0xf1, 0xff, 0xec, 0x30, 0xdc, 0x30, 0x64, 0x44, 0xa8, 0x37, 0xd0, 0x30, 0x34, 0x37, 0xd4, 0x30,
    0x01, 0x09, 0x02, 0x01, 0x01, 0x01, 0x03, 0x03, 0x04, 0x00, 0x04, 0x04, 0x05, 0x0a, 0x08, 0x00,
    0x02, 0x00, 0xaf, 0x00, 0x00, 0x02, 0x03, 0x04, 0x19, 0x1e, 0x2d, 0x23, 0x23, 0x14, 0x0a, 0x28,
    0x33, 0x07, 0x33, 0x07, 0x00, 0x04, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x0a,
    0x04, 0x00, 0x0e, 0x0b, 0x80, 0x80, 0x80, 0x80, 0x32, 0x00, 0x50, 0x30, 0xc8, 0x37, 0xf1, 0xff,
    0x68, 0x30, 0x78, 0x36, 0x40, 0x47, 0x94, 0x44, 0x58, 0x37, 0x3c, 0x37, 0x3c, 0x47, 0x00, 0x01,
    0x02, 0x01, 0x03, 0x03, 0x03, 0x01, 0x04, 0x07, 0x04, 0x02, 0x08, 0x19, 0x03, 0x03, 0x02, 0x00,
    0x2e, 0x00, 0x1c, 0x19, 0x06, 0x20, 0x2d, 0x19, 0x1e, 0x0f, 0x23, 0x28, 0x00, 0x0a, 0x66, 0x06,
    0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x05, 0x00,
    0x0e, 0x20, 0xc3, 0xe5, 0x32, 0x26, 0x1e, 0x00, 0xf1, 0xff, 0x44, 0x37, 0xc4, 0x37, 0x14, 0x30,
    0x24, 0x30, 0x60, 0x36, 0x20, 0x46, 0x20, 0x46, 0x20, 0x46, 0xec, 0x36, 0x01, 0x0a, 0x02, 0x02,
    0x01, 0x0c, 0x03, 0x00, 0x04, 0x04, 0x04, 0x07, 0x06, 0x09, 0x29, 0x04, 0x08, 0x00, 0x25, 0x00,
    0x03, 0x1d, 0x2d, 0x21, 0x14, 0x32, 0x0a, 0x1e, 0x14, 0x28, 0x1e, 0x00, 0x66, 0x0a, 0x00, 0x08,
    0x33, 0x07, 0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x00, 0x11, 0x38,
    0xb9, 0xdc, 0x34, 0x32, 0x07, 0x00, 0xc8, 0x30, 0x04, 0x38, 0x2c, 0x30, 0x34, 0x30, 0x28, 0x37,
    0xb0, 0x39, 0xb8, 0x3a, 0xb4, 0x3b, 0xa0, 0x3a, 0xbc, 0x3a, 0x01, 0x09, 0x01, 0x03, 0x01, 0x01,
    0x03, 0x01, 0x04, 0x00, 0x04, 0x02, 0x0b, 0x08, 0x46, 0x02, 0x07, 0x00, 0xa8, 0x00, 0x16, 0x1c,
    0x04, 0x04, 0x1e, 0x0a, 0x00, 0x28, 0x32, 0x14, 0x19, 0x19, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04,
    0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x05, 0x00, 0x11, 0x00, 0x60, 0x70,
    0x8d, 0xa3, 0x1f, 0x00, 0x30, 0x31, 0xc8, 0x37, 0x10, 0x31, 0x98, 0x30, 0x28, 0x30, 0x7c, 0x37,
    0x0c, 0x47, 0x38, 0x34, 0x34, 0x34, 0x2c, 0x37, 0x01, 0x01, 0x00, 0x02, 0x01, 0x09, 0x03, 0x01,
    0x04, 0x09, 0x04, 0x06, 0x0c, 0x1b, 0x4a, 0x08, 0x09, 0x00, 0x46, 0x00, 0x0f, 0x22, 0x1b, 0x31,
    0x14, 0x19, 0x0f, 0x28, 0x23, 0x2d, 0x1e, 0x0a, 0x66, 0x06, 0x9a, 0x09, 0x9a, 0x11, 0xcd, 0x08,
    0x66, 0x0a, 0x66, 0x06, 0x9a, 0x11, 0x00, 0x0c, 0x03, 0x00, 0x04, 0x0a, 0x83, 0x72, 0x86, 0x85,
    0x20, 0x00, 0x40, 0x31, 0xf1, 0xff, 0xf1, 0xff, 0x24, 0x37, 0x5c, 0x31, 0xf1, 0xff, 0x04, 0x47,
    0x3c, 0x34, 0xa4, 0x35, 0x5c, 0x36, 0x01, 0x07, 0x00, 0x01, 0x01, 0x09, 0x03, 0x03, 0x04, 0x02,
    0x04, 0x06, 0x0b, 0x01, 0x6b, 0x01, 0x00, 0x00, 0xa3, 0x00, 0x1f, 0x09, 0x24, 0x06, 0x23, 0x14,
    0x2d, 0x14, 0x28, 0x1e, 0x0f, 0x23, 0x00, 0x08, 0x33, 0x03, 0x9a, 0x11, 0x00, 0x08, 0x9a, 0x11,
    0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a, 0x02, 0x00, 0x04, 0x05, 0x65, 0x68, 0x80, 0xb3, 0x21, 0x00,
    0x7c, 0x35, 0xf1, 0xff, 0x80, 0x35, 0xa8, 0x36, 0x48, 0x32, 0x58, 0x32, 0x84, 0x35, 0xec, 0x45,
    0x94, 0x34, 0x58, 0x32, 0x02, 0x01, 0x01, 0x02, 0x01, 0x06, 0x03, 0x00, 0x04, 0x09, 0x04, 0x00,
    0x0b, 0x04, 0x0c, 0x01, 0x09, 0x00, 0x23, 0x00, 0x01, 0x0c, 0x31, 0x36, 0x28, 0x0a, 0x1e, 0x05,
    0x19, 0x14, 0x00, 0x23, 0x33, 0x07, 0x33, 0x07, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x09, 0x9a, 0x11,
    0x66, 0x06, 0xcd, 0x0c, 0x00, 0x01, 0x04, 0x2e, 0x6b, 0x7d, 0x8f, 0x89, 0x22, 0x00, 0xf1, 0xff,
    0x28, 0x30, 0x48, 0x37, 0x34, 0x31, 0x2c, 0x30, 0x3c, 0x47, 0xe0, 0x3f, 0x5c, 0x36, 0x3c, 0x31,
    0x38, 0x30, 0x02, 0x02, 0x01, 0x01, 0x01, 0x04, 0x03, 0x01, 0x04, 0x07, 0x04, 0x0b, 0x05, 0x0d,
    0x2d, 0x07, 0x04, 0x00, 0x2c, 0x00, 0x16, 0x01, 0x26, 0x04, 0x28, 0x19, 0x23, 0x2d, 0x0a, 0x1e,
    0x32, 0x14, 0x9a, 0x11, 0x00, 0x08, 0x00, 0x08, 0xcd, 0x08, 0x66, 0x0a, 0x66, 0x06, 0x9a, 0x11,
    0xcd, 0x08, 0x00, 0x00, 0x04, 0x0d, 0x77, 0x7c, 0x85, 0x88, 0x23, 0x00, 0xf1, 0xff, 0x00, 0x31,
    0x8c, 0x38, 0x6c, 0x31, 0xe0, 0x33, 0xbc, 0x37, 0x64, 0x47, 0xf0, 0x33, 0xf4, 0x36, 0xe4, 0x33,
    0x00, 0x02, 0x01, 0x06, 0x01, 0x09, 0x03, 0x03, 0x04, 0x09, 0x04, 0x01, 0x08, 0x04, 0x4e, 0x06,
    0x03, 0x00, 0xfe, 0x00, 0x03, 0x06, 0x13, 0x08, 0x05, 0x23, 0x00, 0x28, 0x00, 0x19, 0x0a, 0x2d,
    0x66, 0x06, 0x9a, 0x09, 0x9a, 0x11, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a,
    0x00, 0x00, 0x04, 0x1c, 0x77, 0x74, 0x81, 0x94, 0x24, 0x00, 0x78, 0x30, 0x7c, 0x30, 0x68, 0x30,
    0xc8, 0x37, 0x6c, 0x30, 0xac, 0x33, 0x0c, 0x3b, 0x2c, 0x3e, 0x3c, 0x37, 0x90, 0x30, 0x00, 0x01,
    0x01, 0x07, 0x01, 0x06, 0x03, 0x00, 0x04, 0x04, 0x04, 0x00, 0x0a, 0x19, 0x6f, 0x03, 0x06, 0x00,
    0x9c, 0x00, 0x18, 0x04, 0x1d, 0x2d, 0x14, 0x00, 0x0a, 0x2d, 0x23, 0x28, 0x19, 0x1e, 0x00, 0x08,
    0x33, 0x03, 0x9a, 0x11, 0x9a, 0x11, 0x9a, 0x09, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x09, 0x05, 0x00,
    0x04, 0x31, 0x91, 0x86, 0x66, 0x83, 0x25, 0x00, 0xf1, 0xff, 0x38, 0x31, 0x4c, 0x34, 0x30, 0x44,
    0x4c, 0x34, 0xe8, 0x3f, 0x74, 0x36, 0x74, 0x30, 0x88, 0x35, 0x40, 0x36, 0x01, 0x07, 0x02, 0x01,
    0x01, 0x06, 0x03, 0x01, 0x04, 0x07, 0x04, 0x04, 0x06, 0x0a, 0x10, 0x02, 0x09, 0x00, 0x24, 0x00,
    0x08, 0x17, 0x23, 0x32, 0x14, 0x32, 0x19, 0x0a, 0x28, 0x1e, 0x19, 0x14, 0x33, 0x07, 0x9a, 0x11,
    0x00, 0x08, 0xcd, 0x08, 0x66, 0x0a, 0x66, 0x06, 0x9a, 0x11, 0x00, 0x0c, 0x00, 0x00, 0x04, 0x36,
    0x6b, 0x8c, 0x7e, 0x8b, 0x88, 0x00, 0x5c, 0x32, 0xf1, 0xff, 0xf1, 0xff, 0x20, 0x30, 0xc8, 0x37,
    0x58, 0x37, 0x0c, 0x45, 0x10, 0x45, 0x84, 0x37, 0xf8, 0x37, 0x01, 0x07, 0x01, 0x09, 0x01, 0x0c,
    0x03, 0x01, 0x04, 0x02, 0x04, 0x00, 0x0b, 0x10, 0x06, 0x02, 0x01, 0x00, 0x9a, 0x00, 0x00, 0x01,
    0x35, 0x2d, 0x1e, 0x0f, 0x2d, 0x05, 0x1e, 0x28, 0x0a, 0x00, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04,
    0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x03, 0x00, 0x04, 0x21, 0x90, 0x90,
    0x80, 0x60, 0x26, 0x00, 0x00, 0x30, 0xcc, 0x30, 0x48, 0x32, 0xf1, 0xff, 0xc4, 0x37, 0x08, 0x30,
    0xa8, 0x37, 0xa8, 0x37, 0x38, 0x36, 0x38, 0x36, 0x01, 0x09, 0x02, 0x02, 0x01, 0x05, 0x03, 0x00,
    0x04, 0x09, 0x04, 0x04, 0x02, 0x01, 0x31, 0x07, 0x02, 0x00, 0x1f, 0x00, 0x00, 0x1b, 0x2b, 0x1f,
    0x23, 0x19, 0x00, 0x14, 0x1e, 0x2d, 0x0a, 0x28, 0x66, 0x0a, 0x00, 0x08, 0x00, 0x04, 0x00, 0x08,
    0x66, 0x06, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a, 0x01, 0x00, 0x07, 0x0e, 0xb6, 0xa7, 0x63, 0x40,
    0x27, 0x00, 0x1c, 0x33, 0x2c, 0x33, 0x68, 0x32, 0x24, 0x30, 0xf1, 0xff, 0xe8, 0x33, 0x0c, 0x34,
    0x0c, 0x34, 0x4c, 0x37, 0xb8, 0x47, 0x01, 0x01, 0x00, 0x02, 0x01, 0x06, 0x03, 0x00, 0x04, 0x02,
    0x04, 0x06, 0x01, 0x03, 0x52, 0x04, 0x00, 0x00, 0x20, 0x00, 0x03, 0x25, 0x39, 0x03, 0x14, 0x00,
    0x0a, 0x1e, 0x23, 0x28, 0x14, 0x1e, 0x66, 0x06, 0x9a, 0x09, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x11,
    0x00, 0x08, 0x66, 0x06, 0xcd, 0x0c, 0x00, 0x00, 0x07, 0x2c, 0x98, 0x84, 0x64, 0x80, 0x28, 0x00,
    0x50, 0x30, 0x88, 0x30, 0x68, 0x30, 0x54, 0x30, 0xf1, 0xff, 0x74, 0x30, 0x2c, 0x37, 0xb0, 0x47,
    0x74, 0x35, 0xb4, 0x47, 0x01, 0x05, 0x00, 0x01, 0x01, 0x01, 0x03, 0x01, 0x04, 0x00, 0x04, 0x03,
    0x02, 0x17, 0x73, 0x00, 0x06, 0x00, 0x69, 0x00, 0x07, 0x1a, 0x23, 0x27, 0x1e, 0x28, 0x00, 0x14,
    0x0f, 0x14, 0x32, 0x0a, 0x00, 0x08, 0x33, 0x03, 0x00, 0x08, 0xcd, 0x08, 0x66, 0x0a, 0x66, 0x06,
    0x9a, 0x05, 0xcd, 0x08, 0x04, 0x00, 0x07, 0x2e, 0x71, 0x76, 0x86, 0x93, 0x29, 0x00, 0x90, 0x31,
    0xf1, 0xff, 0xb0, 0x31, 0x6c, 0x30, 0xc8, 0x37, 0x3c, 0x37, 0xa8, 0x37, 0x2c, 0x3e, 0x00, 0x3b,
    0x64, 0x36, 0x02, 0x01, 0x01, 0x0a, 0x01, 0x01, 0x03, 0x03, 0x04, 0x01, 0x04, 0x07, 0x04, 0x08,
    0x00, 0x08, 0x06, 0x00, 0x1a, 0x00, 0x08, 0x00, 0x17, 0x18, 0x14, 0x00, 0x0f, 0x23, 0x1e, 0x28,
    0x0a, 0x19, 0x33, 0x07, 0x33, 0x07, 0x00, 0x04, 0x9a, 0x11, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x08,
    0x66, 0x0a, 0x05, 0x01, 0x07, 0x31, 0x6b, 0x92, 0x81, 0x82, 0x2a, 0x00, 0x94, 0x35, 0x8c, 0x35,
    0xe0, 0x32, 0xdc, 0x32, 0xf1, 0xff, 0xbc, 0x33, 0x20, 0x37, 0xf4, 0x33, 0xf4, 0x33, 0xf4, 0x33,
    0x00, 0x02, 0x01, 0x09, 0x01, 0x0a, 0x03, 0x00, 0x04, 0x05, 0x04, 0x0a, 0x06, 0x1b, 0x21, 0x02,
    0x09, 0x00, 0x9a, 0x00, 0x09, 0x22, 0x24, 0x24, 0x28, 0x32, 0x14, 0x05, 0x2d, 0x1e, 0x0a, 0x00,
    0x66, 0x0a, 0x9a, 0x11, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x09,
    0x03, 0x00, 0x07, 0x30, 0x64, 0x61, 0xa8, 0x93, 0x2b, 0x00, 0x50, 0x30, 0xa0, 0x36, 0x2c, 0x33,
    0xc8, 0x37, 0x94, 0x31, 0x94, 0x36, 0x00, 0x35, 0x38, 0x33, 0x40, 0x33, 0x74, 0x36, 0x00, 0x02,
    0x01, 0x0a, 0x01, 0x03, 0x03, 0x00, 0x04, 0x04, 0x04, 0x00, 0x02, 0x0b, 0x42, 0x08, 0x04, 0x00,
    0x21, 0x00, 0x0a, 0x02, 0x17, 0x1f, 0x1e, 0x14, 0x05, 0x28, 0x2d, 0x23, 0x19, 0x32, 0x66, 0x06,
    0x9a, 0x09, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x05, 0x00, 0x0c, 0x04, 0x00,
    0x07, 0x04, 0x6f, 0x6c, 0xb7, 0x6e, 0x2c, 0x00, 0xc8, 0x30, 0xcc, 0x30, 0xf1, 0xff, 0xd4, 0x37,
    0x0c, 0x30, 0x34, 0x34, 0x4c, 0x36, 0x2c, 0x37, 0xe0, 0x30, 0x34, 0x36, 0x00, 0x01, 0x01, 0x05,
    0x01, 0x07, 0x02, 0x01, 0x04, 0x07, 0x04, 0x04, 0x0b, 0x11, 0x63, 0x08, 0x09, 0x00, 0x40, 0x00,
    0x16, 0x19, 0x05, 0x1b, 0x00, 0x14, 0x1e, 0x32, 0x19, 0x2d, 0x28, 0x0a, 0x00, 0x08, 0x33, 0x03,
    0x00, 0x04, 0x9a, 0x11, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a, 0x05, 0x00, 0x07, 0x0a,
    0x81, 0x9e, 0x6f, 0x72, 0x27, 0x00, 0xb4, 0x37, 0xd8, 0x32, 0xd8, 0x32, 0x30, 0x37, 0x6c, 0x31,
    0x28, 0x46, 0xf0, 0x34, 0x14, 0x38, 0x24, 0x46, 0x00, 0x35, 0x02, 0x02, 0x01, 0x04, 0x03, 0x03,
    0x03, 0x00, 0x04, 0x08, 0x04, 0x05, 0x02, 0x13, 0x23, 0x06, 0x09, 0x00, 0x1c, 0x00, 0x17, 0x05,
    0x08, 0x33, 0x14, 0x32, 0x23, 0x19, 0x2d, 0x1e, 0x28, 0x0a, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04,
    0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x04, 0x00, 0x07, 0x34, 0x74, 0x7d,
    0x71, 0x9e, 0x26, 0x00, 0xf1, 0xff, 0xa0, 0x36, 0x90, 0x38, 0xe0, 0x33, 0xec, 0x43, 0x94, 0x36,
    0x14, 0x37, 0x0c, 0x34, 0x98, 0x47, 0xe4, 0x33, 0x00, 0x02, 0x02, 0x01, 0x04, 0x05, 0x03, 0x00,
    0x04, 0x0b, 0x04, 0x02, 0x05, 0x19, 0x51, 0x01, 0x08, 0x00, 0x3c, 0x00, 0x08, 0x03, 0x21, 0x26,
    0x32, 0x28, 0x00, 0x14, 0x23, 0x19, 0x1e, 0x0f, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09,
    0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x00, 0x00, 0x07, 0x1e, 0x80, 0x80, 0x80, 0x80,
    0x32, 0x00, 0xb4, 0x37, 0x00, 0x36, 0x18, 0x37, 0xb0, 0x37, 0x44, 0x37, 0x64, 0x44, 0x98, 0x36,
    0x6c, 0x44, 0x64, 0x37, 0x68, 0x44, 0x02, 0x01, 0x01, 0x03, 0x01, 0x02, 0x03, 0x03, 0x03, 0x00,
    0x04, 0x00, 0x06, 0x19, 0x4e, 0x02, 0x03, 0x00, 0x6a, 0x00, 0x08, 0x1b, 0x09, 0x35, 0x28, 0x2d,
    0x00, 0x1e, 0x19, 0x23, 0x14, 0x32, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04,
    0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x00, 0x00, 0x07, 0x1f, 0xd4, 0x8a, 0x3d, 0x65, 0x2d, 0x00,
    0x00, 0x30, 0xf1, 0xff, 0x20, 0x30, 0x60, 0x30, 0xf1, 0xff, 0x3c, 0x36, 0x60, 0x37, 0x08, 0x30,
    0x1c, 0x30, 0x3c, 0x37, 0x01, 0x05, 0x01, 0x03, 0x00, 0x01, 0x03, 0x00, 0x04, 0x02, 0x04, 0x09,
    0x01, 0x14, 0x04, 0x03, 0x01, 0x00, 0x65, 0x00, 0x0c, 0x10, 0x1a, 0x1c, 0x1e, 0x14, 0x14, 0x32,
    0x23, 0x0a, 0x05, 0x28, 0x33, 0x07, 0x33, 0x07, 0x33, 0x07, 0x9a, 0x11, 0x9a, 0x09, 0x9a, 0x11,
    0x66, 0x06, 0xcd, 0x0c, 0x05, 0x00, 0x01, 0x38, 0xfa, 0x9e, 0x2d, 0x3b, 0x2e, 0x00, 0x48, 0x33,
    0xf1, 0xff, 0xf1, 0xff, 0x2c, 0x33, 0x18, 0x31, 0xf8, 0x45, 0x88, 0x47, 0xac, 0x30, 0xac, 0x46,
    0x6c, 0x37, 0x00, 0x02, 0x02, 0x01, 0x01, 0x0c, 0x03, 0x00, 0x04, 0x03, 0x04, 0x09, 0x07, 0x0e,
    0x25, 0x03, 0x06, 0x00, 0x22, 0x00, 0x00, 0x09, 0x26, 0x12, 0x2d, 0x0a, 0x32, 0x14, 0x05, 0x19,
    0x1e, 0x28, 0x66, 0x0a, 0x00, 0x08, 0x9a, 0x11, 0xcd, 0x08, 0x66, 0x0a, 0x66, 0x06, 0x9a, 0x11,
    0xcd, 0x08, 0x00, 0x00, 0x01, 0x1d, 0xff, 0x8a, 0x37, 0x40, 0x2f, 0x00, 0xcc, 0x32, 0xd8, 0x32,
    0xdc, 0x32, 0xe0, 0x32, 0xd8, 0x32, 0xe4, 0x32, 0xc4, 0x32, 0x4c, 0x37, 0xd8, 0x33, 0xd4, 0x32,
    0x01, 0x04, 0x00, 0x02, 0x01, 0x0c, 0x01, 0x0a, 0x04, 0x00, 0x04, 0x03, 0x0a, 0x03, 0x46, 0x01,
    0x07, 0x00, 0x20, 0x00, 0x09, 0x06, 0x11, 0x11, 0x32, 0x2d, 0x00, 0x19, 0x1e, 0x23, 0x28, 0x05,
    0x66, 0x06, 0x9a, 0x11, 0x00, 0x04, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a,
    0x00, 0x01, 0x01, 0x45, 0xc9, 0x87, 0x4d, 0x63, 0x30, 0x00, 0x90, 0x31, 0xb0, 0x30, 0x10, 0x31,
    0x44, 0x37, 0xf1, 0xff, 0x08, 0x31, 0xc0, 0x30, 0xfc, 0x30, 0x60, 0x36, 0x2c, 0x35, 0x01, 0x01,
    0x01, 0x03, 0x01, 0x0a, 0x03, 0x00, 0x03, 0x03, 0x04, 0x01, 0x0c, 0x08, 0x67, 0x03, 0x06, 0x00,
    0x3c, 0x00, 0x0f, 0x06, 0x1f, 0x18, 0x14, 0x1e, 0x00, 0x0a, 0x2d, 0x23, 0x32, 0x1e, 0x9a, 0x11,
    0x33, 0x03, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x09, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x09, 0x05, 0x00,
    0x01, 0x04, 0xce, 0x7d, 0x26, 0x8f, 0x8b, 0x00, 0x50, 0x30, 0xec, 0x30, 0xe4, 0x30, 0x0c, 0x30,
    0xcc, 0x30, 0x18, 0x35, 0x4c, 0x36, 0xa4, 0x34, 0x2c, 0x37, 0x18, 0x30, 0x01, 0x06, 0x01, 0x02,
    0x01, 0x09, 0x03, 0x00, 0x04, 0x04, 0x04, 0x00, 0x01, 0x1c, 0x4c, 0x03, 0x04, 0x00, 0xbb, 0x00,
    0x14, 0x01, 0x33, 0x2b, 0x14, 0x05, 0x1e, 0x32, 0x19, 0x14, 0x28, 0x0a, 0x66, 0x06, 0x33, 0x03,
    0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x03, 0x00, 0x01, 0x0a,
    0x65, 0x8c, 0x9b, 0x74, 0x31, 0x00, 0x30, 0x31, 0x34, 0x31, 0xf4, 0x30, 0x10, 0x31, 0xc8, 0x37,
    0x88, 0x36, 0x38, 0x37, 0xf0, 0x34, 0x94, 0x36, 0x14, 0x38, 0x02, 0x02, 0x01, 0x04, 0x01, 0x0a,
    0x03, 0x03, 0x04, 0x00, 0x04, 0x04, 0x02, 0x04, 0x29, 0x07, 0x01, 0x00, 0x67, 0x00, 0x11, 0x09,
    0x19, 0x18, 0x14, 0x19, 0x0f, 0x1e, 0x23, 0x32, 0x28, 0x14, 0x66, 0x0a, 0x9a, 0x11, 0x00, 0x04,
    0x9a, 0x11, 0x66, 0x06, 0x9a, 0x05, 0x9a, 0x11, 0x66, 0x0a, 0x03, 0x00, 0x10, 0x0c, 0x80, 0x80,
    0x80, 0x80, 0x32, 0x00, 0x60, 0x32, 0x70, 0x32, 0xf1, 0xff, 0x68, 0x32, 0x6c, 0x32, 0x58, 0x32,
    0x58, 0x32, 0x74, 0x32, 0x74, 0x32, 0xc4, 0x47, 0x02, 0x01, 0x01, 0x0b, 0x03, 0x01, 0x04, 0x06,
    0x04, 0x01, 0x04, 0x09, 0x02, 0x0d, 0x08, 0x09, 0x06, 0x00, 0x10, 0x00, 0x07, 0x21, 0x0f, 0x0f,
    0x14, 0x19, 0x05, 0x19, 0x0a, 0x1e, 0x28, 0x32, 0x9a, 0x11, 0x33, 0x07, 0x9a, 0x11, 0xcd, 0x08,
    0x66, 0x0a, 0x66, 0x06, 0x9a, 0x05, 0x00, 0x0c, 0x01, 0x01, 0x10, 0x2d, 0x73, 0x79, 0x92, 0x82,
    0x33, 0x00, 0xe0, 0x34, 0x74, 0x31, 0x30, 0x44, 0x8c, 0x31, 0xa8, 0x36, 0xc8, 0x47, 0xd0, 0x34,
    0xdc, 0x34, 0xd8, 0x34, 0xd4, 0x34, 0x00, 0x02, 0x01, 0x0c, 0x03, 0x00, 0x04, 0x05, 0x04, 0x04,
    0x04, 0x07, 0x02, 0x08, 0x4a, 0x09, 0x02, 0x00, 0x91, 0x00, 0x12, 0x23, 0x16, 0x2f, 0x0f, 0x19,
    0x0a, 0x32, 0x2d, 0x23, 0x28, 0x14, 0x66, 0x06, 0x9a, 0x09, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x09,
    0x00, 0x08, 0x66, 0x06, 0xcd, 0x0c, 0x01, 0x00, 0x10, 0x37, 0x96, 0xa1, 0x7e, 0x4b, 0x34, 0x00,
    0x1c, 0x33, 0xdc, 0x32, 0xb0, 0x37, 0xd8, 0x32, 0xf1, 0xff, 0x4c, 0x37, 0xe8, 0x46, 0xc4, 0x32,
    0xf4, 0x33, 0xc4, 0x32, 0x00, 0x01, 0x01, 0x09, 0x01, 0x07, 0x03, 0x01, 0x04, 0x09, 0x04, 0x05,
    0x06, 0x05, 0x6b, 0x03, 0x07, 0x00, 0x11, 0x00, 0x01, 0x09, 0x11, 0x11, 0x2d, 0x23, 0x19, 0x14,
    0x1e, 0x0a, 0x1e, 0x0f, 0x9a, 0x11, 0x33, 0x03, 0x9a, 0x11, 0xcd, 0x08, 0x66, 0x0a, 0x66, 0x06,
    0x9a, 0x05, 0xcd, 0x08, 0x02, 0x00, 0x10, 0x1a, 0x75, 0x85, 0xaa, 0x5c, 0x35, 0x00, 0xf1, 0xff,
    0xa8, 0x36, 0x44, 0x32, 0xf1, 0xff, 0x48, 0x32, 0x9c, 0x46, 0x78, 0x35, 0x30, 0x32, 0x78, 0x35,
    0x4c, 0x32, 0x01, 0x0c, 0x02, 0x01, 0x03, 0x03, 0x04, 0x00, 0x04, 0x03, 0x04, 0x02, 0x0a, 0x09,
    0x0c, 0x04, 0x09, 0x00, 0x24, 0x00, 0x14, 0x02, 0x0e, 0x0e, 0x0a, 0x28, 0x14, 0x00, 0x0f, 0x23,
    0x14, 0x1e, 0x9a, 0x11, 0x33, 0x07, 0x00, 0x04, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x05, 0x9a, 0x11,
    0x66, 0x0a, 0x01, 0x01, 0x10, 0x28, 0x80, 0xa3, 0x82, 0x5b, 0x36, 0x00, 0xb4, 0x37, 0xf1, 0xff,
    0xf1, 0xff, 0x48, 0x32, 0x0c, 0x30, 0x10, 0x36, 0xb0, 0x43, 0x20, 0x36, 0x64, 0x46, 0x90, 0x34,
    0x01, 0x09, 0x02, 0x02, 0x01, 0x0b, 0x03, 0x00, 0x04, 0x03, 0x04, 0x00, 0x08, 0x15, 0x2d, 0x06,
    0x00, 0x00, 0xa1, 0x00, 0x15, 0x06, 0x21, 0x3c, 0x05, 0x19, 0x32, 0x0a, 0x23, 0x14, 0x28, 0x1e,
    0x9a, 0x11, 0x9a, 0x11, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x09,
    0x02, 0x00, 0x10, 0x39, 0x86, 0x6b, 0x91, 0x7e, 0x37, 0x00, 0x08, 0x33, 0xf1, 0xff, 0xf1, 0xff,
    0xb0, 0x36, 0xf1, 0xff, 0x90, 0x36, 0x4c, 0x37, 0x10, 0x33, 0xe0, 0x36, 0x88, 0x36, 0x01, 0x02,
    0x00, 0x02, 0x01, 0x0a, 0x03, 0x01, 0x04, 0x07, 0x04, 0x0b, 0x01, 0x0d, 0x4e, 0x00, 0x06, 0x00,
    0x85, 0x00, 0x16, 0x1c, 0x0f, 0x39, 0x0a, 0x0f, 0x14, 0x23, 0x32, 0x1e, 0x2d, 0x19, 0x66, 0x06,
    0x9a, 0x09, 0x00, 0x08, 0x9a, 0x11, 0x66, 0x0a, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x0c, 0x04, 0x00,
    0x10, 0x2a, 0x68, 0x9d, 0x97, 0x64, 0x3b, 0x00, 0xb4, 0x37, 0x8c, 0x35, 0xf1, 0xff, 0xf0, 0x30,
    0xf4, 0x30, 0x30, 0x3e, 0xf0, 0x34, 0x68, 0x47, 0x88, 0x3b, 0x34, 0x37, 0x02, 0x02, 0x01, 0x05,
    0x01, 0x06, 0x03, 0x01, 0x04, 0x00, 0x04, 0x09, 0x07, 0x08, 0x08, 0x02, 0x03, 0x00, 0x2b, 0x00,
    0x07, 0x05, 0x2f, 0x1a, 0x2d, 0x1e, 0x1e, 0x19, 0x23, 0x0f, 0x32, 0x28, 0x66, 0x06, 0x33, 0x03,
    0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x00, 0x00, 0x10, 0x0d,
    0x58, 0x6d, 0xb7, 0x84, 0x38, 0x00, 0x50, 0x30, 0x60, 0x30, 0x98, 0x30, 0x6c, 0x30, 0x7c, 0x30,
    0x34, 0x37, 0x70, 0x30, 0x70, 0x37, 0x1c, 0x34, 0x74, 0x3e, 0x01, 0x06, 0x00, 0x01, 0x01, 0x02,
    0x03, 0x03, 0x04, 0x02, 0x04, 0x01, 0x03, 0x06, 0x6f, 0x00, 0x01, 0x00, 0x47, 0x00, 0x0a, 0x0f,
    0x04, 0x07, 0x14, 0x0a, 0x05, 0x28, 0x19, 0x32, 0x2d, 0x1e, 0x00, 0x08, 0x33, 0x03, 0x00, 0x04,
    0x00, 0x08, 0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x0a, 0x03, 0x00, 0x12, 0x00, 0x68, 0x5c,
    0xac, 0x90, 0x39, 0x00, 0x50, 0x30, 0xa4, 0x30, 0xb8, 0x30, 0xb0, 0x30, 0xf1, 0xff, 0x0c, 0x38,
    0xf8, 0x37, 0xbc, 0x33, 0x74, 0x36, 0x90, 0x30, 0x02, 0x02, 0x01, 0x0b, 0x03, 0x00, 0x04, 0x06,
    0x04, 0x00, 0x04, 0x08, 0x08, 0x18, 0x10, 0x07, 0x03, 0x00, 0x72, 0x00, 0x0e, 0x10, 0x35, 0x06,
    0x2d, 0x1e, 0x0a, 0x14, 0x23, 0x28, 0x19, 0x0f, 0x33, 0x07, 0x33, 0x07, 0x33, 0x07, 0x9a, 0x11,
    0x9a, 0x09, 0x9a, 0x11, 0x66, 0x06, 0xcd, 0x0c, 0x03, 0x00, 0x12, 0x41, 0xbc, 0x69, 0x3e, 0x9d,
    0x3a, 0x00, 0xf1, 0xff, 0x44, 0x37, 0x8c, 0x30, 0x88, 0x30, 0xf1, 0xff, 0xc8, 0x46, 0xa0, 0x33,
    0xa0, 0x33, 0x64, 0x36, 0x64, 0x36, 0x01, 0x06, 0x01, 0x07, 0x00, 0x01, 0x03, 0x01, 0x03, 0x03,
    0x04, 0x02, 0x09, 0x06, 0x31, 0x02, 0x03, 0x00, 0x1d, 0x00, 0x07, 0x25, 0x33, 0x2c, 0x19, 0x1e,
    0x0f, 0x1e, 0x2d, 0x00, 0x14, 0x28, 0x66, 0x0a, 0x00, 0x08, 0x9a, 0x11, 0xcd, 0x08, 0x9a, 0x11,
    0x66, 0x06, 0x9a, 0x05, 0xcd, 0x08, 0x02, 0x00, 0x1b, 0x2c, 0xc3, 0x7c, 0x39, 0x88, 0x0b, 0x00,
    0x00, 0x30, 0x6c, 0x34, 0xf1, 0xff, 0x48, 0x37, 0x6c, 0x34, 0x88, 0x47, 0x48, 0x35, 0xf1, 0xff,
    0x48, 0x35, 0xd0, 0x47, 0x00, 0x01, 0x01, 0x07, 0x03, 0x00, 0x03, 0x03, 0x04, 0x00, 0x04, 0x07,
    0x09, 0x0b, 0x0a, 0x01, 0x07, 0x00, 0x05, 0x00, 0x03, 0x26, 0x24, 0x24, 0x19, 0x32, 0x1e, 0x23,
    0x1e, 0x2d, 0x14, 0x0a, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06,
    0xcd, 0x04, 0x66, 0x06, 0x02, 0x00, 0x1b, 0x17, 0x80, 0x80, 0x80, 0x80, 0x32, 0x00, 0x08, 0x36,
    0xf1, 0xff, 0xf1, 0xff, 0xe0, 0x32, 0x48, 0x32, 0x5c, 0x35, 0x34, 0x37, 0xf1, 0xff, 0xac, 0x36,
    0xf1, 0xff, 0x02, 0x02, 0x01, 0x09, 0x01, 0x02, 0x03, 0x03, 0x04, 0x09, 0x04, 0x00, 0x09, 0x0c,
    0x6d, 0x01, 0x05, 0x00, 0x6d, 0x00, 0x04, 0x22, 0x0e, 0x0e, 0x19, 0x14, 0x1e, 0x1e, 0x28, 0x05,
    0x0a, 0x32, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04,
    0x66, 0x06, 0x01, 0x01, 0x1b, 0x2f, 0xae, 0xed, 0x28, 0x3d, 0x3b, 0x00, 0xf1, 0xff, 0x9c, 0x35,
    0x24, 0x30, 0x34, 0x30, 0x68, 0x30, 0x38, 0x30, 0x3c, 0x31, 0x0c, 0x38, 0x2c, 0x37, 0xa8, 0x35,
    0x00, 0x01, 0x01, 0x02, 0x01, 0x0c, 0x03, 0x00, 0x04, 0x03, 0x04, 0x09, 0x08, 0x12, 0x52, 0x04,
    0x08, 0x00, 0x90, 0x00, 0x1a, 0x0e, 0x23, 0x32, 0x28, 0x32, 0x23, 0x14, 0x1e, 0x0a, 0x00, 0x23,
    0x9a, 0x11, 0x9a, 0x09, 0x00, 0x04, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a,
    0x02, 0x00, 0x08, 0x13, 0x6d, 0xa1, 0xa6, 0x4c, 0x3c, 0x00, 0xf1, 0xff, 0x20, 0x30, 0x18, 0x37,
    0x24, 0x30, 0x34, 0x30, 0x74, 0x30, 0x70, 0x3d, 0x38, 0x30, 0x3c, 0x37, 0x64, 0x30, 0x00, 0x01,
    0x01, 0x04, 0x01, 0x09, 0x03, 0x00, 0x04, 0x02, 0x04, 0x03, 0x04, 0x04, 0x73, 0x01, 0x02, 0x00,
    0x08, 0x00, 0x01, 0x12, 0x21, 0x27, 0x19, 0x23, 0x0a, 0x2d, 0x32, 0x14, 0x1e, 0x28, 0x9a, 0x11,
    0x9a, 0x11, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x09, 0x01, 0x00,
    0x16, 0x37, 0x66, 0x7d, 0xde, 0x3f, 0x3d, 0x00, 0xe0, 0x34, 0xa0, 0x31, 0x40, 0x32, 0x40, 0x32,
    0x48, 0x32, 0x38, 0x37, 0xfc, 0x34, 0x54, 0x37, 0xfc, 0x34, 0x00, 0x35, 0x01, 0x04, 0x02, 0x01,
    0x01, 0x0c, 0x03, 0x01, 0x04, 0x03, 0x04, 0x00, 0x07, 0x0b, 0x00, 0x00, 0x04, 0x00, 0x01, 0x00,
    0x02, 0x21, 0x0f, 0x12, 0x0a, 0x1e, 0x0f, 0x28, 0x14, 0x19, 0x23, 0x2d, 0x33, 0x07, 0x33, 0x07,
    0x00, 0x08, 0x9a, 0x11, 0x66, 0x0a, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x0c, 0x04, 0x00, 0x16, 0x28,
    0x55, 0xa2, 0xcd, 0x3c, 0x3e, 0x00, 0xf1, 0xff, 0xec, 0x30, 0x0c, 0x30, 0x44, 0x37, 0x4c, 0x35,
    0xa8, 0x37, 0xd8, 0x30, 0xd8, 0x30, 0x3c, 0x36, 0x60, 0x36, 0x01, 0x06, 0x02, 0x02, 0x01, 0x07,
    0x03, 0x01, 0x04, 0x07, 0x04, 0x04, 0x01, 0x19, 0x21, 0x08, 0x00, 0x00, 0x2c, 0x00, 0x11, 0x25,
    0x2a, 0x1a, 0x05, 0x28, 0x23, 0x00, 0x0a, 0x32, 0x14, 0x1e, 0x66, 0x0a, 0x00, 0x08, 0x00, 0x04,
    0x00, 0x08, 0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x0a, 0x03, 0x00, 0x16, 0x38, 0x5d, 0xae,
    0xc1, 0x34, 0x3f, 0x00, 0xf1, 0xff, 0x34, 0x30, 0x7c, 0x30, 0x44, 0x30, 0x34, 0x30, 0x3c, 0x37,
    0x74, 0x30, 0x2c, 0x35, 0x80, 0x30, 0x90, 0x30, 0x01, 0x09, 0x00, 0x02, 0x01, 0x04, 0x03, 0x00,
    0x04, 0x07, 0x04, 0x01, 0x0a, 0x05, 0x42, 0x04, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x0f, 0x2e, 0x27,
    0x19, 0x1e, 0x28, 0x0f, 0x0a, 0x14, 0x23, 0x32, 0x9a, 0x11, 0x9a, 0x09, 0x33, 0x07, 0x66, 0x06,
    0x9a, 0x11, 0x00, 0x08, 0x66, 0x06, 0xcd, 0x0c, 0x00, 0x00, 0x16, 0x02, 0x6d, 0x9b, 0x90, 0x68,
    0x65, 0x00, 0x40, 0x31, 0xf1, 0xff, 0xf1, 0xff, 0x24, 0x37, 0x50, 0x31, 0x3c, 0x36, 0xac, 0x33,
    0xf1, 0xff, 0x64, 0x31, 0x94, 0x33, 0x01, 0x05, 0x01, 0x09, 0x03, 0x00, 0x04, 0x06, 0x04, 0x00,
    0x04, 0x09, 0x06, 0x10, 0x25, 0x04, 0x07, 0x00, 0x37, 0x00, 0x01, 0x00, 0x2a, 0x06, 0x19, 0x0f,
    0x32, 0x0a, 0x28, 0x14, 0x1e, 0x23, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04,
    0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x02, 0x01, 0x16, 0x2e, 0x71, 0xc6, 0x56, 0x73, 0x42, 0x00,
    0x78, 0x30, 0x8c, 0x30, 0xb0, 0x30, 0xf1, 0xff, 0x98, 0x30, 0x9c, 0x30, 0x2c, 0x37, 0x8c, 0x36,
    0x40, 0x36, 0x90, 0x30, 0x00, 0x01, 0x01, 0x06, 0x01, 0x05, 0x03, 0x00, 0x03, 0x01, 0x04, 0x05,
    0x07, 0x14, 0x25, 0x08, 0x01, 0x00, 0x72, 0x00, 0x02, 0x19, 0x2c, 0x25, 0x1e, 0x23, 0x0f, 0x0a,
    0x32, 0x19, 0x28, 0x14, 0x9a, 0x11, 0x00, 0x08, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x11, 0x00, 0x08,
    0x66, 0x06, 0x9a, 0x09, 0x05, 0x00, 0x15, 0x20, 0x86, 0xb6, 0x71, 0x53, 0x43, 0x00, 0xf8, 0x34,
    0xec, 0x30, 0xe4, 0x30, 0x44, 0x37, 0x4c, 0x35, 0xf4, 0x34, 0x40, 0x36, 0x34, 0x34, 0x3c, 0x36,
    0x5c, 0x36, 0x00, 0x02, 0x01, 0x0c, 0x01, 0x0a, 0x03, 0x03, 0x04, 0x04, 0x04, 0x01, 0x08, 0x13,
    0x46, 0x05, 0x06, 0x00, 0x5a, 0x00, 0x02, 0x25, 0x08, 0x19, 0x28, 0x0a, 0x0f, 0x05, 0x1e, 0x00,
    0x2d, 0x14, 0x9a, 0x11, 0x9a, 0x09, 0x00, 0x08, 0xcd, 0x08, 0x66, 0x0a, 0x9a, 0x11, 0x9a, 0x05,
    0x00, 0x0c, 0x03, 0x00, 0x15, 0x29, 0x80, 0x80, 0x80, 0x80, 0x32, 0x00, 0x30, 0x31, 0x18, 0x31,
    0xd4, 0x37, 0x2c, 0x31, 0x10, 0x31, 0xd8, 0x37, 0x5c, 0x36, 0x0c, 0x31, 0x04, 0x34, 0x1c, 0x31,
    0x01, 0x0b, 0x01, 0x0c, 0x04, 0x06, 0x03, 0x01, 0x04, 0x04, 0x04, 0x07, 0x04, 0x0c, 0x28, 0x00,
    0x04, 0x00, 0xc3, 0x00, 0x02, 0x25, 0x36, 0x37, 0x19, 0x0a, 0x23, 0x2d, 0x1e, 0x32, 0x28, 0x1e,
    0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06,
    0x03, 0x00, 0x15, 0x1c, 0xaa, 0x66, 0xa9, 0x47, 0x40, 0x00, 0x40, 0x35, 0x60, 0x30, 0xf1, 0xff,
    0x60, 0x30, 0x20, 0x30, 0x4c, 0x36, 0xd0, 0x40, 0x3c, 0x46, 0x64, 0x30, 0x2c, 0x37, 0x01, 0x02,
    0x00, 0x01, 0x01, 0x09, 0x03, 0x01, 0x04, 0x04, 0x04, 0x00, 0x0a, 0x0b, 0x63, 0x07, 0x05, 0x00,
    0x8c, 0x00, 0x1f, 0x00, 0x2e, 0x31, 0x19, 0x1e, 0x14, 0x28, 0x32, 0x2d, 0x23, 0x00, 0x00, 0x08,
    0x33, 0x03, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x05, 0xcd, 0x08, 0x03, 0x01,
    0x1d, 0x00, 0xa6, 0x79, 0x99, 0x48, 0x41, 0x00, 0x40, 0x30, 0xf1, 0xff, 0xf1, 0xff, 0x60, 0x30,
    0x9c, 0x35, 0x60, 0x3a, 0x7c, 0x37, 0x60, 0x36, 0xb0, 0x3a, 0xa4, 0x35, 0x02, 0x01, 0x01, 0x07,
    0x03, 0x03, 0x04, 0x06, 0x04, 0x07, 0x04, 0x04, 0x0b, 0x0c, 0x04, 0x02, 0x00, 0x00, 0x0f, 0x00,
    0x18, 0x04, 0x08, 0x17, 0x0a, 0x1e, 0x32, 0x1e, 0x00, 0x19, 0x14, 0x28, 0x33, 0x07, 0x33, 0x07,
    0x00, 0x04, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x0a, 0x05, 0x01, 0x1d, 0x1c,
    0xc1, 0x8d, 0x58, 0x5a, 0x44, 0x00, 0x08, 0x33, 0xb0, 0x36, 0xb0, 0x36, 0xb0, 0x36, 0xb0, 0x36,
    0x38, 0x37, 0x3c, 0x35, 0xb8, 0x36, 0xc0, 0x36, 0x6c, 0x44, 0x01, 0x01, 0x01, 0x0a, 0x01, 0x02,
    0x03, 0x03, 0x04, 0x00, 0x04, 0x04, 0x08, 0x08, 0x67, 0x01, 0x07, 0x00, 0x75, 0x00, 0x17, 0x16,
    0x39, 0x3a, 0x14, 0x32, 0x28, 0x23, 0x1e, 0x00, 0x05, 0x19, 0x00, 0x08, 0x9a, 0x11, 0x00, 0x04,
    0x00, 0x08, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a, 0x01, 0x01, 0x18, 0x0f, 0x80, 0x80,
    0x80, 0x80, 0x32, 0x00, 0xf1, 0xff, 0x88, 0x30, 0x20, 0x30, 0x88, 0x30, 0x20, 0x30, 0x20, 0x38,
    0x20, 0x38, 0x6c, 0x35, 0xc4, 0x36, 0x6c, 0x35, 0x01, 0x06, 0x01, 0x07, 0x01, 0x09, 0x03, 0x01,
    0x04, 0x02, 0x04, 0x07, 0x07, 0x17, 0x23, 0x02, 0x00, 0x00, 0xcb, 0x00, 0x06, 0x1f, 0x2e, 0x20,
    0x0a, 0x05, 0x23, 0x14, 0x1e, 0x0f, 0x19, 0x2d, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09,
    0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x02, 0x00, 0x18, 0x17, 0x27, 0x31, 0xfc, 0xac,
    0x45, 0x00, 0x88, 0x34, 0x04, 0x38, 0x44, 0x37, 0x14, 0x30, 0x0c, 0x30, 0x24, 0x36, 0x2c, 0x36,
    0xac, 0x34, 0x90, 0x34, 0x90, 0x34, 0x01, 0x06, 0x02, 0x01, 0x01, 0x05, 0x03, 0x00, 0x04, 0x0b,
    0x04, 0x07, 0x02, 0x12, 0x08, 0x07, 0x09, 0x00, 0xa1, 0x00, 0x04, 0x25, 0x09, 0x22, 0x14, 0x23,
    0x00, 0x1e, 0x0a, 0x32, 0x28, 0x0a, 0x33, 0x07, 0x33, 0x07, 0x33, 0x07, 0x9a, 0x11, 0x9a, 0x09,
    0x9a, 0x11, 0x66, 0x06, 0xcd, 0x0c, 0x03, 0x00, 0x0a, 0x20, 0x3d, 0x64, 0xe8, 0x77, 0x46, 0x00,
    0xb4, 0x37, 0xb8, 0x37, 0x20, 0x30, 0xf1, 0xff, 0x6c, 0x34, 0xfc, 0x45, 0x40, 0x37, 0x08, 0x46,
    0x48, 0x35, 0x18, 0x46, 0x01, 0x0b, 0x02, 0x02, 0x01, 0x01, 0x03, 0x03, 0x04, 0x00, 0x04, 0x0b,
    0x0a, 0x11, 0x29, 0x05, 0x00, 0x00, 0xa0, 0x00, 0x15, 0x16, 0x23, 0x22, 0x05, 0x28, 0x1e, 0x19,
    0x2d, 0x28, 0x0a, 0x32, 0x66, 0x0a, 0x00, 0x08, 0x9a, 0x11, 0xcd, 0x08, 0x9a, 0x11, 0x66, 0x06,
    0x9a, 0x05, 0xcd, 0x08, 0x02, 0x00, 0x0a, 0x19, 0x26, 0x3f, 0xf3, 0xa8, 0x47, 0x00, 0x90, 0x31,
    0xf4, 0x30, 0x44, 0x37, 0xa0, 0x31, 0x10, 0x31, 0x90, 0x36, 0x54, 0x37, 0x04, 0x35, 0x88, 0x36,
    0x00, 0x35, 0x01, 0x0c, 0x01, 0x02, 0x01, 0x0a, 0x03, 0x03, 0x04, 0x0b, 0x03, 0x00, 0x0c, 0x1c,
    0x4a, 0x09, 0x07, 0x00, 0x0e, 0x00, 0x1d, 0x05, 0x24, 0x34, 0x0a, 0x14, 0x19, 0x28, 0x05, 0x32,
    0x1e, 0x1e, 0x66, 0x06, 0x9a, 0x09, 0x9a, 0x11, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x08,
    0x66, 0x0a, 0x04, 0x00, 0x0a, 0x45, 0x39, 0x76, 0xd6, 0x7b, 0x48, 0x00, 0x78, 0x30, 0x4c, 0x35,
    0x24, 0x37, 0x88, 0x30, 0x98, 0x30, 0x68, 0x36, 0x1c, 0x37, 0xac, 0x36, 0x90, 0x30, 0x9c, 0x30,
    0x01, 0x06, 0x00, 0x01, 0x01, 0x0a, 0x03, 0x00, 0x04, 0x07, 0x04, 0x04, 0x07, 0x07, 0x6b, 0x07,
    0x03, 0x00, 0x73, 0x00, 0x02, 0x23, 0x1b, 0x1f, 0x23, 0x05, 0x0f, 0x0a, 0x2d, 0x14, 0x1e, 0x28,
    0x00, 0x08, 0x33, 0x03, 0x33, 0x07, 0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x09,
    0x05, 0x00, 0x0a, 0x36, 0x38, 0x5d, 0xf1, 0x7a, 0x24, 0x00, 0xb4, 0x30, 0xf1, 0xff, 0xf1, 0xff,
    0x10, 0x31, 0x98, 0x35, 0x80, 0x37, 0xec, 0x37, 0xd8, 0x34, 0xdc, 0x34, 0x54, 0x37, 0x00, 0x02,
    0x01, 0x05, 0x03, 0x00, 0x03, 0x03, 0x04, 0x01, 0x04, 0x0b, 0x07, 0x05, 0x72, 0x05, 0x09, 0x00,
    0x9b, 0x00, 0x10, 0x07, 0x1f, 0x0a, 0x19, 0x1e, 0x32, 0x28, 0x14, 0x14, 0x19, 0x23, 0x66, 0x06,
    0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x01, 0x00,
    0x0a, 0x2d, 0x4b, 0x68, 0xfa, 0x53, 0x5f, 0x00, 0xf1, 0xff, 0x34, 0x30, 0x10, 0x31, 0xf1, 0xff,
    0x9c, 0x35, 0x2c, 0x37, 0x60, 0x37, 0x38, 0x34, 0x38, 0x30, 0x38, 0x30, 0x00, 0x01, 0x01, 0x02,
    0x01, 0x0c, 0x03, 0x00, 0x04, 0x04, 0x03, 0x00, 0x08, 0x0e, 0x13, 0x01, 0x02, 0x00, 0xd5, 0x00,
    0x00, 0x0e, 0x14, 0x32, 0x32, 0x28, 0x19, 0x23, 0x0a, 0x1e, 0x14, 0x0f, 0x66, 0x06, 0x33, 0x03,
    0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x01, 0x00, 0x0a, 0x01,
    0x68, 0xff, 0x48, 0x51, 0x49, 0x00, 0x7c, 0x32, 0x68, 0x32, 0x64, 0x32, 0x6c, 0x32, 0x70, 0x32,
    0x58, 0x32, 0x58, 0x32, 0xd0, 0x31, 0xc8, 0x31, 0x74, 0x32, 0x02, 0x01, 0x01, 0x02, 0x01, 0x07,
    0x03, 0x03, 0x04, 0x06, 0x04, 0x0b, 0x09, 0x14, 0x0c, 0x05, 0x08, 0x00, 0x1b, 0x00, 0x17, 0x20,
    0x0f, 0x0f, 0x1e, 0x1e, 0x00, 0x14, 0x28, 0x2d, 0x32, 0x19, 0x33, 0x07, 0x9a, 0x11, 0x00, 0x08,
    0xcd, 0x08, 0x66, 0x0a, 0x66, 0x06, 0x9a, 0x11, 0x00, 0x0c, 0x02, 0x01, 0x17, 0x24, 0x4e, 0xff,
    0x74, 0x3f, 0x4a, 0x00, 0x90, 0x31, 0xf1, 0xff, 0x94, 0x31, 0xa0, 0x31, 0xd4, 0x37, 0xac, 0x31,
    0xd8, 0x36, 0x2c, 0x37, 0xa4, 0x31, 0xb4, 0x31, 0x01, 0x0a, 0x03, 0x03, 0x01, 0x01, 0x03, 0x01,
    0x04, 0x04, 0x04, 0x02, 0x06, 0x1a, 0x2d, 0x00, 0x06, 0x00, 0x4f, 0x00, 0x05, 0x24, 0x01, 0x01,
    0x1e, 0x23, 0x14, 0x14, 0x28, 0x00, 0x2d, 0x23, 0x66, 0x0a, 0x00, 0x08, 0x00, 0x04, 0x00, 0x08,
    0x9a, 0x11, 0x9a, 0x05, 0x9a, 0x11, 0x66, 0x0a, 0x03, 0x01, 0x17, 0x20, 0x56, 0x8f, 0xdd, 0x3e,
    0x4b, 0x00, 0x40, 0x31, 0x8c, 0x30, 0x4c, 0x35, 0x60, 0x30, 0x44, 0x37, 0xa0, 0x33, 0x88, 0x33,
    0x80, 0x36, 0xa0, 0x33, 0x88, 0x33, 0x00, 0x01, 0x01, 0x05, 0x01, 0x0b, 0x03, 0x00, 0x04, 0x00,
    0x04, 0x04, 0x0b, 0x0d, 0x4e, 0x09, 0x03, 0x00, 0xc1, 0x00, 0x02, 0x27, 0x2a, 0x06, 0x1e, 0x19,
    0x19, 0x32, 0x1e, 0x28, 0x00, 0x0f, 0x66, 0x06, 0x9a, 0x09, 0x9a, 0x11, 0x9a, 0x11, 0x9a, 0x09,
    0x00, 0x08, 0x66, 0x06, 0xcd, 0x0c, 0x05, 0x01, 0x1c, 0x1d, 0x4d, 0x71, 0xc5, 0x7d, 0x4c, 0x00,
    0x00, 0x30, 0x0c, 0x30, 0x14, 0x30, 0x20, 0x30, 0x24, 0x30, 0x20, 0x36, 0x08, 0x30, 0x3c, 0x37,
    0x50, 0x35, 0x44, 0x47, 0x00, 0x01, 0x04, 0x00, 0x03, 0x03, 0x03, 0x01, 0x04, 0x02, 0x04, 0x07,
    0x01, 0x0f, 0x6f, 0x02, 0x03, 0x00, 0x2a, 0x00, 0x04, 0x23, 0x22, 0x22, 0x2d, 0x05, 0x1e, 0x14,
    0x28, 0x0f, 0x00, 0x19, 0x00, 0x08, 0x33, 0x03, 0x00, 0x08, 0x9a, 0x11, 0x66, 0x0a, 0x9a, 0x11,
    0x9a, 0x05, 0xcd, 0x08, 0x03, 0x01, 0x1c, 0x19, 0x76, 0x71, 0xb6, 0x63, 0x4d, 0x00, 0x40, 0x31,
    0x9c, 0x35, 0x50, 0x31, 0x70, 0x36, 0x58, 0x31, 0xa0, 0x35, 0x94, 0x33, 0xac, 0x33, 0x2c, 0x45,
    0x28, 0x45, 0x01, 0x06, 0x02, 0x01, 0x01, 0x07, 0x03, 0x03, 0x04, 0x0b, 0x04, 0x09, 0x07, 0x04,
    0x10, 0x04, 0x05, 0x00, 0xd5, 0x00, 0x04, 0x24, 0x1e, 0x2d, 0x0a, 0x23, 0x28, 0x14, 0x0f, 0x19,
    0x1e, 0x2d, 0x33, 0x07, 0x9a, 0x11, 0x00, 0x04, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x05, 0x9a, 0x11,
    0x66, 0x0a, 0x02, 0x00, 0x1e, 0x20, 0x7a, 0x7c, 0x9e, 0x6c, 0x4e, 0x00, 0x30, 0x31, 0xf1, 0xff,
    0xf1, 0xff, 0x34, 0x30, 0x38, 0x31, 0x2c, 0x35, 0xa8, 0x37, 0x2c, 0x46, 0x34, 0x34, 0x4c, 0x37,
    0x01, 0x02, 0x02, 0x02, 0x01, 0x09, 0x03, 0x00, 0x04, 0x00, 0x04, 0x03, 0x0b, 0x13, 0x31, 0x03,
    0x02, 0x00, 0xac, 0x00, 0x1b, 0x01, 0x3a, 0x09, 0x00, 0x0a, 0x32, 0x1e, 0x14, 0x28, 0x19, 0x14,
    0x66, 0x0a, 0x9a, 0x11, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x09,
    0x05, 0x00, 0x1e, 0x14, 0xc7, 0x63, 0xd9, 0x4d, 0x6e, 0x00, 0x78, 0x30, 0x8c, 0x30, 0x28, 0x37,
    0xf1, 0xff, 0x88, 0x30, 0x1c, 0x37, 0x80, 0x30, 0x84, 0x30, 0x90, 0x30, 0x90, 0x36, 0x01, 0x06,
    0x01, 0x01, 0x01, 0x04, 0x03, 0x00, 0x04, 0x04, 0x04, 0x07, 0x01, 0x08, 0x25, 0x02, 0x08, 0x00,
    0xc2, 0x00, 0x19, 0x09, 0x07, 0x07, 0x23, 0x00, 0x14, 0x32, 0x0a, 0x28, 0x1e, 0x23, 0x66, 0x06,
    0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x01, 0x00,
    0x1e, 0x06, 0x54, 0x5a, 0x53, 0xff, 0x4f, 0x00, 0xf1, 0xff, 0x2c, 0x33, 0xcc, 0x30, 0x24, 0x37,
    0xc8, 0x37, 0x0c, 0x35, 0x54, 0x37, 0x04, 0x47, 0x08, 0x35, 0x5c, 0x47, 0x01, 0x06, 0x00, 0x02,
    0x01, 0x07, 0x03, 0x01, 0x04, 0x01, 0x04, 0x07, 0x01, 0x1b, 0x52, 0x05, 0x03, 0x00, 0x63, 0x00,
    0x0e, 0x0c, 0x0f, 0x1f, 0x14, 0x00, 0x05, 0x1e, 0x19, 0x28, 0x32, 0x0a, 0x66, 0x06, 0x9a, 0x11,
    0x00, 0x08, 0xcd, 0x08, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x05, 0x00, 0x0c, 0x03, 0x00, 0x1f, 0x1d,
    0x6d, 0x68, 0x73, 0xb8, 0x50, 0x00, 0x48, 0x33, 0x2c, 0x33, 0x64, 0x32, 0x6c, 0x32, 0x70, 0x32,
    0xf8, 0x37, 0x88, 0x31, 0xe8, 0x36, 0xd0, 0x31, 0x90, 0x35, 0x01, 0x05, 0x00, 0x02, 0x01, 0x06,
    0x03, 0x03, 0x04, 0x09, 0x04, 0x03, 0x01, 0x05, 0x73, 0x04, 0x02, 0x00, 0x36, 0x00, 0x0f, 0x16,
    0x13, 0x0a, 0x2d, 0x0a, 0x05, 0x28, 0x05, 0x19, 0x23, 0x1e, 0x00, 0x08, 0x9a, 0x11, 0x00, 0x04,
    0x00, 0x08, 0x66, 0x06, 0x9a, 0x05, 0x9a, 0x11, 0x66, 0x0a, 0x01, 0x00, 0x1f, 0x32, 0x79, 0x76,
    0x50, 0xc1, 0x51, 0x00, 0xf1, 0xff, 0xb8, 0x31, 0xbc, 0x31, 0xc4, 0x31, 0x34, 0x44, 0xd8, 0x31,
    0x0c, 0x35, 0xe8, 0x34, 0xd0, 0x31, 0xfc, 0x34, 0x02, 0x01, 0x01, 0x07, 0x01, 0x0c, 0x03, 0x00,
    0x04, 0x02, 0x04, 0x0a, 0x01, 0x1d, 0x00, 0x00, 0x01, 0x00, 0x52, 0x00, 0x14, 0x1a, 0x18, 0x19,
    0x2d, 0x14, 0x19, 0x28, 0x0a, 0x1e, 0x28, 0x32, 0x33, 0x07, 0x9a, 0x11, 0x33, 0x07, 0x66, 0x06,
    0x9a, 0x09, 0x00, 0x08, 0x9a, 0x11, 0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x25, 0x6e, 0x67, 0x4b, 0xe0,
    0x52, 0x00, 0x30, 0x31, 0x2c, 0x31, 0x34, 0x31, 0xf1, 0xff, 0xf1, 0xff, 0x24, 0x31, 0x50, 0x34,
    0x88, 0x47, 0x20, 0x47, 0x54, 0x34, 0x02, 0x02, 0x01, 0x02, 0x01, 0x07, 0x03, 0x01, 0x04, 0x03,
    0x04, 0x00, 0x04, 0x06, 0x21, 0x06, 0x00, 0x00, 0xb9, 0x00, 0x1d, 0x24, 0x09, 0x30, 0x1e, 0x32,
    0x14, 0x28, 0x0a, 0x1e, 0x23, 0x05, 0x66, 0x0a, 0x00, 0x08, 0x00, 0x08, 0xcd, 0x08, 0x9a, 0x11,
    0x66, 0x06, 0x9a, 0x11, 0xcd, 0x08, 0x02, 0x00, 0x1f, 0x13, 0x58, 0x7c, 0x58, 0xd4, 0x53, 0x00,
    0x78, 0x30, 0xe4, 0x30, 0x7c, 0x30, 0x44, 0x37, 0x8c, 0x30, 0x9c, 0x3b, 0x84, 0x30, 0x84, 0x30,
    0x2c, 0x3e, 0x44, 0x3b, 0x01, 0x06, 0x01, 0x0a, 0x03, 0x03, 0x04, 0x04, 0x04, 0x07, 0x04, 0x01,
    0x0a, 0x10, 0x42, 0x01, 0x05, 0x00, 0x5e, 0x00, 0x02, 0x1b, 0x2e, 0x02, 0x1e, 0x19, 0x0a, 0x23,
    0x2d, 0x1e, 0x28, 0x00, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x04, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x05,
    0x9a, 0x11, 0x66, 0x0a, 0x05, 0x00, 0x1f, 0x10, 0x56, 0x77, 0x67, 0xcc, 0x09, 0x00, 0x40, 0x35,
    0x44, 0x30, 0x4c, 0x35, 0x7c, 0x30, 0x60, 0x30, 0x48, 0x30, 0x3c, 0x37, 0x34, 0x36, 0x74, 0x30,
    0x64, 0x30, 0x01, 0x06, 0x01, 0x05, 0x01, 0x01, 0x03, 0x01, 0x04, 0x02, 0x04, 0x00, 0x01, 0x17,
    0x42, 0x08, 0x05, 0x00, 0xc4, 0x00, 0x02, 0x06, 0x3d, 0x2e, 0x14, 0x19, 0x00, 0x05, 0x1e, 0x2d,
    0x28, 0x1e, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04,
    0x66, 0x06, 0x05, 0x00, 0x1f, 0x31, 0x84, 0xcc, 0x5b, 0x55, 0x54, 0x00, 0x30, 0x31, 0xf1, 0xff,
    0xf1, 0xff, 0x68, 0x30, 0x2c, 0x31, 0xd4, 0x46, 0x3c, 0x36, 0x4c, 0x37, 0x38, 0x36, 0x2c, 0x35,
    0x01, 0x01, 0x01, 0x09, 0x03, 0x03, 0x03, 0x00, 0x04, 0x03, 0x04, 0x09, 0x07, 0x1a, 0x63, 0x05,
    0x01, 0x00, 0x3b, 0x00, 0x00, 0x03, 0x26, 0x26, 0x19, 0x14, 0x2d, 0x1e, 0x23, 0x0f, 0x1e, 0x28,
    0x00, 0x08, 0x33, 0x03, 0x33, 0x07, 0x9a, 0x11, 0x9a, 0x09, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x09,
    0x01, 0x00, 0x0b, 0x0e, 0x8a, 0xc9, 0x5a, 0x53, 0x55, 0x00, 0xb4, 0x30, 0xb0, 0x31, 0xf1, 0xff,
    0xa0, 0x31, 0x94, 0x31, 0x64, 0x46, 0x60, 0x46, 0x78, 0x37, 0x18, 0x35, 0x8c, 0x36, 0x01, 0x0a,
    0x02, 0x01, 0x01, 0x0c, 0x03, 0x01, 0x04, 0x00, 0x04, 0x04, 0x07, 0x1c, 0x04, 0x00, 0x02, 0x00,
    0xc6, 0x00, 0x0f, 0x04, 0x1f, 0x01, 0x14, 0x32, 0x1e, 0x0a, 0x2d, 0x00, 0x19, 0x28, 0x33, 0x07,
    0x33, 0x07, 0x00, 0x08, 0x9a, 0x11, 0x66, 0x0a, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x0c, 0x04, 0x00,
    0x0b, 0x36, 0xad, 0x92, 0x59, 0x68, 0x56, 0x00, 0x40, 0x31, 0xf1, 0xff, 0xf1, 0xff, 0x70, 0x36,
    0xc4, 0x37, 0xf4, 0x33, 0xf4, 0x33, 0x40, 0x34, 0x2c, 0x36, 0x10, 0x34, 0x01, 0x02, 0x02, 0x02,
    0x01, 0x09, 0x03, 0x01, 0x04, 0x04, 0x04, 0x03, 0x04, 0x07, 0x25, 0x06, 0x00, 0x00, 0x3a, 0x00,
    0x15, 0x06, 0x25, 0x30, 0x19, 0x00, 0x2d, 0x23, 0x1e, 0x28, 0x14, 0x0a, 0x9a, 0x11, 0x00, 0x08,
    0x9a, 0x11, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a, 0x02, 0x00, 0x0b, 0x11,
    0x8d, 0xd5, 0x50, 0x4e, 0x19, 0x00, 0x7c, 0x31, 0x8c, 0x31, 0x68, 0x31, 0xf1, 0xff, 0x74, 0x31,
    0xe4, 0x36, 0x6c, 0x37, 0x90, 0x36, 0x60, 0x34, 0x88, 0x36, 0x01, 0x03, 0x01, 0x01, 0x01, 0x0a,
    0x03, 0x03, 0x04, 0x08, 0x04, 0x05, 0x0c, 0x1e, 0x20, 0x08, 0x03, 0x00, 0x5b, 0x00, 0x10, 0x10,
    0x08, 0x19, 0x23, 0x00, 0x14, 0x19, 0x32, 0x0a, 0x1e, 0x28, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04,
    0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x00, 0x00, 0x0b, 0x0d, 0x7c, 0xaa,
    0x66, 0x74, 0x1d, 0x00, 0x40, 0x30, 0x20, 0x30, 0xc8, 0x37, 0x04, 0x38, 0xc4, 0x37, 0x1c, 0x36,
    0x14, 0x37, 0x14, 0x36, 0x68, 0x37, 0x0c, 0x36, 0x01, 0x09, 0x02, 0x01, 0x01, 0x07, 0x03, 0x00,
    0x04, 0x0b, 0x04, 0x02, 0x06, 0x02, 0x62, 0x00, 0x01, 0x00, 0x47, 0x00, 0x0a, 0x0f, 0x1d, 0x2d,
    0x19, 0x23, 0x0a, 0x1e, 0x28, 0x2d, 0x00, 0x14, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09,
    0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x03, 0x00, 0x0b, 0x2b, 0x6a, 0x5b, 0xd4, 0x67,
    0x57, 0x00, 0x40, 0x35, 0x44, 0x37, 0x7c, 0x30, 0x34, 0x30, 0xf0, 0x30, 0xb4, 0x31, 0x9c, 0x31,
    0x1c, 0x34, 0x9c, 0x30, 0xa4, 0x31, 0x01, 0x0a, 0x00, 0x02, 0x01, 0x09, 0x03, 0x00, 0x04, 0x01,
    0x04, 0x09, 0x05, 0x09, 0x46, 0x03, 0x04, 0x00, 0x5b, 0x00, 0x14, 0x04, 0x26, 0x25, 0x19, 0x1e,
    0x00, 0x14, 0x2d, 0x0a, 0x1e, 0x28, 0x66, 0x06, 0x9a, 0x09, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x11,
    0x9a, 0x11, 0x66, 0x06, 0xcd, 0x0c, 0x04, 0x00, 0x06, 0x08, 0x60, 0x53, 0xd4, 0x79, 0x58, 0x00,
    0x60, 0x32, 0xf1, 0xff, 0xf1, 0xff, 0x68, 0x32, 0x6c, 0x32, 0x4c, 0x46, 0x74, 0x32, 0x4c, 0x37,
    0x74, 0x32, 0x74, 0x32, 0x01, 0x0c, 0x00, 0x01, 0x01, 0x0a, 0x03, 0x01, 0x04, 0x02, 0x04, 0x04,
    0x03, 0x0e, 0x67, 0x08, 0x01, 0x00, 0x38, 0x00, 0x08, 0x20, 0x3a, 0x3b, 0x0a, 0x0f, 0x19, 0x14,
    0x23, 0x1e, 0x28, 0x2d, 0x00, 0x08, 0x33, 0x03, 0x00, 0x08, 0x9a, 0x11, 0x66, 0x0a, 0x9a, 0x11,
    0x9a, 0x05, 0xcd, 0x08, 0x04, 0x00, 0x06, 0x25, 0x65, 0x63, 0xcd, 0x6b, 0x59, 0x00, 0xb4, 0x37,
    0xb8, 0x37, 0xf1, 0xff, 0xf1, 0xff, 0x24, 0x30, 0x90, 0x34, 0x88, 0x35, 0x90, 0x34, 0xcc, 0x47,
    0x2c, 0x36, 0x02, 0x01, 0x01, 0x09, 0x03, 0x00, 0x04, 0x06, 0x04, 0x03, 0x04, 0x00, 0x03, 0x01,
    0x08, 0x06, 0x03, 0x00, 0x29, 0x00, 0x03, 0x04, 0x1c, 0x35, 0x05, 0x1e, 0x0a, 0x14, 0x32, 0x14,
    0x19, 0x28, 0x33, 0x07, 0x33, 0x07, 0x00, 0x04, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08,
    0x66, 0x0a, 0x03, 0x01, 0x06, 0x2e, 0x61, 0x5f, 0xf9, 0x47, 0x5a, 0x00, 0xf1, 0xff, 0xb8, 0x37,
    0x24, 0x30, 0x24, 0x30, 0x6c, 0x34, 0x8c, 0x34, 0x78, 0x34, 0x10, 0x46, 0x24, 0x33, 0x24, 0x33,
    0x02, 0x02, 0x01, 0x0a, 0x01, 0x05, 0x03, 0x00, 0x04, 0x07, 0x04, 0x0b, 0x0b, 0x03, 0x29, 0x09,
    0x08, 0x00, 0xd5, 0x00, 0x1e, 0x16, 0x23, 0x3c, 0x19, 0x2d, 0x0f, 0x1e, 0x28, 0x23, 0x0a, 0x19,
    0x66, 0x0a, 0x00, 0x08, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x09,
    0x01, 0x01, 0x06, 0x07, 0x66, 0x4f, 0xab, 0xa0, 0x5b, 0x00, 0xcc, 0x31, 0xf1, 0xff, 0xf1, 0xff,
    0x64, 0x33, 0x5c, 0x33, 0xb8, 0x33, 0x40, 0x37, 0xbc, 0x32, 0xe8, 0x32, 0xe4, 0x32, 0x02, 0x02,
    0x01, 0x07, 0x01, 0x01, 0x03, 0x01, 0x04, 0x09, 0x04, 0x0b, 0x0a, 0x1c, 0x4a, 0x06, 0x00, 0x00,
    0x8b, 0x00, 0x1a, 0x07, 0x15, 0x15, 0x0a, 0x28, 0x2d, 0x00, 0x14, 0x23, 0x23, 0x1e, 0x9a, 0x11,
    0x9a, 0x11, 0x00, 0x08, 0xcd, 0x08, 0x66, 0x0a, 0x66, 0x06, 0x9a, 0x05, 0x00, 0x0c, 0x02, 0x00,
    0x06, 0x2e, 0x69, 0x57, 0xd2, 0x6e, 0x5c, 0x00, 0x40, 0x35, 0xec, 0x30, 0x44, 0x30, 0x88, 0x30,
    0x4c, 0x35, 0x3c, 0x36, 0x10, 0x47, 0x58, 0x35, 0x2c, 0x37, 0x34, 0x36, 0x01, 0x06, 0x01, 0x05,
    0x01, 0x09, 0x03, 0x00, 0x04, 0x04, 0x04, 0x02, 0x0c, 0x10, 0x6b, 0x00, 0x04, 0x00, 0x64, 0x00,
    0x0a, 0x00, 0x08, 0x31, 0x32, 0x23, 0x0f, 0x1e, 0x14, 0x2d, 0x05, 0x0a, 0x00, 0x08, 0x33, 0x03,
    0x00, 0x04, 0x9a, 0x11, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a, 0x04, 0x00, 0x06, 0x23,
    0x63, 0x56, 0xc1, 0x86, 0x5d, 0x00, 0x1c, 0x33, 0xf1, 0xff, 0xec, 0x35, 0xb0, 0x37, 0x00, 0x33,
    0x4c, 0x37, 0xf0, 0x32, 0x20, 0x33, 0xf4, 0x32, 0xec, 0x32, 0x01, 0x05, 0x02, 0x01, 0x01, 0x01,
    0x03, 0x00, 0x04, 0x07, 0x04, 0x04, 0x06, 0x0e, 0x0c, 0x08, 0x04, 0x00, 0x5d, 0x00, 0x1c, 0x19,
    0x12, 0x12, 0x1e, 0x32, 0x14, 0x1e, 0x19, 0x0a, 0x23, 0x28, 0x33, 0x07, 0x33, 0x07, 0x33, 0x07,
    0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x06, 0xcd, 0x0c, 0x04, 0x00, 0x06, 0x0d, 0x5e, 0x49,
    0xb7, 0xa2, 0x5e, 0x00, 0x40, 0x31, 0x9c, 0x35, 0x70, 0x36, 0x44, 0x37, 0x4c, 0x34, 0xa4, 0x35,
    0x5c, 0x41, 0x64, 0x30, 0x48, 0x34, 0x48, 0x34, 0x01, 0x07, 0x01, 0x05, 0x01, 0x02, 0x03, 0x00,
    0x04, 0x06, 0x04, 0x07, 0x01, 0x09, 0x2d, 0x09, 0x00, 0x00, 0xac, 0x00, 0x18, 0x08, 0x24, 0x1a,
    0x28, 0x14, 0x00, 0x05, 0x1e, 0x2d, 0x0a, 0x19, 0x66, 0x0a, 0x00, 0x08, 0x00, 0x08, 0x9a, 0x11,
    0x66, 0x0a, 0x9a, 0x11, 0x9a, 0x05, 0xcd, 0x08, 0x05, 0x01, 0x06, 0x1a, 0x6e, 0x45, 0xc0, 0x8d,
    0x2a, 0x00, 0x88, 0x34, 0xb8, 0x37, 0xf1, 0xff, 0xf1, 0xff, 0xf1, 0xff, 0xf0, 0x42, 0x84, 0x34,
    0x14, 0x34, 0xbc, 0x33, 0x34, 0x3e, 0x00, 0x02, 0x02, 0x02, 0x01, 0x06, 0x03, 0x00, 0x04, 0x09,
    0x04, 0x00, 0x01, 0x15, 0x65, 0x06, 0x09, 0x00, 0x2a, 0x00, 0x04, 0x00, 0x14, 0x35, 0x32, 0x28,
    0x1e, 0x2d, 0x23, 0x05, 0x14, 0x0f, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04,
    0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x01, 0x01, 0x06, 0x3d, 0x80, 0x80, 0x80, 0x80, 0x32, 0x00,
    0x5c, 0x32, 0xf1, 0xff, 0xa0, 0x31, 0xd4, 0x37, 0xa0, 0x31, 0xfc, 0x37, 0xfc, 0x37, 0xc4, 0x47,
    0xc8, 0x47, 0xfc, 0x37, 0x01, 0x0a, 0x01, 0x06, 0x01, 0x05, 0x03, 0x03, 0x04, 0x01, 0x04, 0x07,
    0x0c, 0x19, 0x53, 0x00, 0x06, 0x00, 0x15, 0x00, 0x03, 0x1f, 0x0f, 0x0f, 0x23, 0x19, 0x0f, 0x0a,
    0x2d, 0x14, 0x1e, 0x28, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06,
    0xcd, 0x04, 0x66, 0x06, 0x04, 0x00, 0x06, 0x0f, 0xcd, 0xdc, 0x38, 0x1f, 0x5f, 0x00, 0xb4, 0x37,
    0xf1, 0xff, 0xf1, 0xff, 0x14, 0x30, 0x0c, 0x30, 0x1c, 0x30, 0x24, 0x36, 0x48, 0x35, 0x90, 0x34,
    0x20, 0x47, 0x01, 0x09, 0x02, 0x02, 0x01, 0x0b, 0x03, 0x03, 0x04, 0x03, 0x04, 0x00, 0x05, 0x06,
    0x4e, 0x01, 0x02, 0x00, 0x1e, 0x00, 0x00, 0x03, 0x2f, 0x3c, 0x28, 0x00, 0x32, 0x0f, 0x1e, 0x23,
    0x1e, 0x14, 0x66, 0x06, 0x9a, 0x11, 0x00, 0x04, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x05, 0x9a, 0x11,
    0x66, 0x0a, 0x01, 0x00, 0x1a, 0x2c, 0x80, 0x80, 0x80, 0x80, 0x32, 0x00, 0x78, 0x30, 0x88, 0x30,
    0x44, 0x37, 0x7c, 0x30, 0x68, 0x30, 0xd8, 0x33, 0x30, 0x46, 0x4c, 0x36, 0xd4, 0x30, 0xe8, 0x30,
    0x01, 0x06, 0x01, 0x09, 0x01, 0x04, 0x03, 0x01, 0x04, 0x01, 0x04, 0x00, 0x01, 0x18, 0x4b, 0x08,
    0x03, 0x00, 0xc0, 0x00, 0x02, 0x13, 0x1a, 0x1d, 0x0a, 0x23, 0x23, 0x28, 0x19, 0x32, 0x14, 0x1e,
    0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06,
    0x03, 0x01, 0x1a, 0x2a, 0x7d, 0x92, 0xa1, 0x50, 0x60, 0x00, 0xf1, 0xff, 0x68, 0x30, 0x18, 0x37,
    0x34, 0x30, 0x04, 0x38, 0x2c, 0x37, 0xa0, 0x3a, 0x38, 0x3b, 0x28, 0x3b, 0xc8, 0x3a, 0x01, 0x06,
    0x00, 0x01, 0x01, 0x09, 0x03, 0x00, 0x04, 0x00, 0x04, 0x03, 0x04, 0x10, 0x6f, 0x07, 0x05, 0x00,
    0x44, 0x00, 0x18, 0x1b, 0x03, 0x12, 0x19, 0x23, 0x0a, 0x32, 0x14, 0x1e, 0x2d, 0x23, 0x00, 0x08,
    0x33, 0x03, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x11, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x09, 0x03, 0x00,
    0x02, 0x15, 0x80, 0x88, 0x9c, 0x5c, 0x61, 0x00, 0x44, 0x35, 0x60, 0x30, 0xf1, 0xff, 0x60, 0x30,
    0xcc, 0x30, 0x58, 0x37, 0x2c, 0x37, 0x3c, 0x36, 0x64, 0x30, 0x28, 0x35, 0x01, 0x09, 0x01, 0x06,
    0x01, 0x0a, 0x03, 0x01, 0x04, 0x02, 0x04, 0x07, 0x03, 0x1c, 0x11, 0x07, 0x01, 0x00, 0x31, 0x00,
    0x05, 0x00, 0x2e, 0x25, 0x1e, 0x14, 0x05, 0x23, 0x19, 0x28, 0x32, 0x0a, 0x33, 0x07, 0x33, 0x07,
    0x00, 0x08, 0x9a, 0x11, 0x66, 0x0a, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x0c, 0x05, 0x00, 0x02, 0x03,
    0x3e, 0x55, 0xe5, 0x88, 0x62, 0x00, 0xe0, 0x34, 0x30, 0x37, 0xc8, 0x37, 0xa4, 0x30, 0x10, 0x31,
    0x48, 0x34, 0x68, 0x47, 0x90, 0x36, 0x68, 0x47, 0x88, 0x36, 0x01, 0x03, 0x01, 0x0a, 0x01, 0x02,
    0x03, 0x03, 0x04, 0x03, 0x01, 0x0c, 0x06, 0x08, 0x31, 0x05, 0x02, 0x00, 0x3e, 0x00, 0x05, 0x11,
    0x1f, 0x1a, 0x28, 0x1e, 0x00, 0x0a, 0x0f, 0x2d, 0x23, 0x14, 0x66, 0x0a, 0x9a, 0x11, 0x00, 0x04,
    0x00, 0x08, 0x9a, 0x11, 0x9a, 0x05, 0x00, 0x08, 0x66, 0x0a, 0x04, 0x00, 0x05, 0x0c, 0x3f, 0x63,
    0xec, 0x72, 0x63, 0x00, 0xe0, 0x34, 0x48, 0x37, 0xc8, 0x37, 0xf1, 0xff, 0x4c, 0x34, 0x58, 0x35,
    0xc4, 0x34, 0xcc, 0x34, 0xc0, 0x34, 0xc8, 0x34, 0x00, 0x02, 0x01, 0x0c, 0x04, 0x06, 0x03, 0x00,
    0x04, 0x01, 0x04, 0x04, 0x07, 0x03, 0x52, 0x08, 0x01, 0x00, 0x2d, 0x00, 0x0a, 0x12, 0x1f, 0x18,
    0x2d, 0x00, 0x28, 0x0a, 0x23, 0x1e, 0x32, 0x1e, 0x66, 0x06, 0x9a, 0x09, 0x33, 0x07, 0x66, 0x06,
    0x9a, 0x11, 0x9a, 0x11, 0x66, 0x06, 0xcd, 0x0c, 0x05, 0x00, 0x05, 0x04, 0x58, 0x66, 0xee, 0x54,
    0x64, 0x00, 0x48, 0x33, 0xbc, 0x31, 0x6c, 0x31, 0x74, 0x31, 0x6c, 0x32, 0x30, 0x34, 0x6c, 0x36,
    0xd4, 0x46, 0x38, 0x34, 0xcc, 0x46, 0x00, 0x02, 0x01, 0x05, 0x01, 0x0c, 0x03, 0x01, 0x04, 0x08,
    0x01, 0x0a, 0x06, 0x03, 0x73, 0x04, 0x03, 0x00, 0x71, 0x00, 0x12, 0x16, 0x0f, 0x2f, 0x32, 0x0a,
    0x0f, 0x28, 0x19, 0x1e, 0x14, 0x00, 0x00, 0x08, 0x9a, 0x11, 0x00, 0x08, 0xcd, 0x08, 0x66, 0x0a,
    0x66, 0x06, 0x9a, 0x11, 0xcd, 0x08, 0x00, 0x00, 0x05, 0x36, 0x2d, 0x5f, 0xf0, 0x84, 0x65, 0x00,
    0x78, 0x30, 0x88, 0x30, 0x28, 0x37, 0x7c, 0x30, 0x98, 0x30, 0x9c, 0x30, 0xa4, 0x36, 0x50, 0x36,
    0x64, 0x44, 0x9c, 0x36, 0x01, 0x01, 0x01, 0x03, 0x01, 0x09, 0x03, 0x03, 0x04, 0x02, 0x04, 0x01,
    0x09, 0x0a, 0x00, 0x08, 0x06, 0x00, 0x39, 0x00, 0x18, 0x21, 0x07, 0x20, 0x0a, 0x23, 0x0f, 0x2d,
    0x05, 0x28, 0x1e, 0x14, 0x9a, 0x11, 0x33, 0x07, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x05,
    0x00, 0x08, 0x66, 0x0a, 0x05, 0x00, 0x05, 0x31, 0x3e, 0x7a, 0xde, 0x6a, 0x66, 0x00, 0xe0, 0x34,
    0xec, 0x35, 0xa0, 0x31, 0x2c, 0x33, 0x68, 0x31, 0xec, 0x37, 0x34, 0x35, 0x4c, 0x46, 0x40, 0x46,
    0x48, 0x46, 0x01, 0x04, 0x01, 0x03, 0x01, 0x04, 0x03, 0x00, 0x04, 0x05, 0x04, 0x08, 0x07, 0x13,
    0x21, 0x00, 0x02, 0x00, 0xb1, 0x00, 0x16, 0x22, 0x17, 0x2f, 0x1e, 0x00, 0x0a, 0x28, 0x14, 0x14,
    0x14, 0x05, 0x9a, 0x11, 0x9a, 0x11, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x08, 0x66, 0x06,
    0x9a, 0x09, 0x04, 0x00, 0x05, 0x25, 0x70, 0x49, 0xff, 0x48, 0x67, 0x00, 0xc8, 0x30, 0xe4, 0x30,
    0x70, 0x36, 0x48, 0x37, 0xc4, 0x43, 0xa8, 0x37, 0xe0, 0x30, 0x54, 0x35, 0x74, 0x30, 0xf0, 0x32,
    0x01, 0x05, 0x01, 0x02, 0x01, 0x04, 0x03, 0x01, 0x04, 0x04, 0x04, 0x07, 0x07, 0x02, 0x42, 0x01,
    0x08, 0x00, 0x1f, 0x00, 0x07, 0x16, 0x3d, 0x1b, 0x14, 0x2d, 0x23, 0x28, 0x05, 0x1e, 0x00, 0x19,
    0x66, 0x06, 0x9a, 0x09, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x11, 0x66, 0x06, 0x9a, 0x05, 0x00, 0x0c,
    0x04, 0x01, 0x05, 0x22, 0x57, 0x7b, 0xd5, 0x59, 0x68, 0x00, 0x94, 0x35, 0x4c, 0x34, 0xd4, 0x37,
    0x8c, 0x31, 0xb0, 0x36, 0xb8, 0x36, 0x10, 0x33, 0x98, 0x37, 0x80, 0x37, 0xc8, 0x36, 0x01, 0x0a,
    0x01, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x01, 0x04, 0x07, 0x07, 0x0f, 0x63, 0x03, 0x06, 0x00,
    0x41, 0x00, 0x17, 0x25, 0x39, 0x18, 0x0a, 0x1e, 0x23, 0x1e, 0x28, 0x14, 0x19, 0x05, 0x00, 0x08,
    0x33, 0x03, 0x00, 0x04, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x11, 0x00, 0x08, 0x66, 0x0a, 0x03, 0x01,
    0x05, 0x26, 0x4b, 0x73, 0xe4, 0x5e, 0x56, 0x00, 0xf1, 0xff, 0xf4, 0x30, 0x10, 0x31, 0xc4, 0x37,
    0x20, 0x30, 0x78, 0x37, 0x38, 0x37, 0x4c, 0x36, 0x74, 0x37, 0x70, 0x37, 0x01, 0x01, 0x00, 0x02,
    0x01, 0x04, 0x03, 0x00, 0x04, 0x09, 0x04, 0x0b, 0x06, 0x13, 0x64, 0x00, 0x01, 0x00, 0x67, 0x00,
    0x14, 0x25, 0x1b, 0x1f, 0x0f, 0x23, 0x19, 0x0a, 0x14, 0x1e, 0x32, 0x05, 0x66, 0x06, 0x33, 0x03,
    0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x03, 0x00, 0x05, 0x05,
    0x5b, 0x4e, 0xfd, 0x5a, 0x34, 0x00, 0x40, 0x31, 0xec, 0x35, 0x24, 0x37, 0x58, 0x31, 0x50, 0x31,
    0x9c, 0x47, 0x38, 0x35, 0x58, 0x46, 0x2c, 0x35, 0x34, 0x35, 0x01, 0x09, 0x01, 0x07, 0x01, 0x05,
    0x03, 0x00, 0x04, 0x05, 0x04, 0x06, 0x07, 0x09, 0x04, 0x03, 0x00, 0x00, 0xb4, 0x00, 0x08, 0x20,
    0x2a, 0x34, 0x1e, 0x28, 0x19, 0x0a, 0x19, 0x14, 0x23, 0x2d, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04,
    0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x02, 0x00, 0x05, 0x29, 0x40, 0x67,
    0xe9, 0x70, 0x32, 0x00, 0xf8, 0x34, 0x60, 0x30, 0x44, 0x37, 0xa4, 0x30, 0xb8, 0x30, 0x48, 0x36,
    0x20, 0x34, 0x68, 0x36, 0xc0, 0x30, 0xbc, 0x30, 0x01, 0x05, 0x01, 0x01, 0x01, 0x0a, 0x03, 0x03,
    0x04, 0x02, 0x04, 0x01, 0x05, 0x02, 0x25, 0x01, 0x04, 0x00, 0x51, 0x00, 0x02, 0x22, 0x1b, 0x31,
    0x28, 0x14, 0x1e, 0x19, 0x23, 0x2d, 0x0a, 0x1e, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09,
    0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x05, 0x00, 0x05, 0x21, 0xb5, 0x8e, 0x78, 0x45,
    0x69, 0x00, 0x40, 0x31, 0xf1, 0xff, 0xf1, 0xff, 0x24, 0x37, 0x0c, 0x30, 0x58, 0x46, 0x88, 0x33,
    0x50, 0x46, 0x8c, 0x32, 0xa0, 0x33, 0x02, 0x01, 0x01, 0x02, 0x01, 0x06, 0x03, 0x00, 0x04, 0x06,
    0x04, 0x02, 0x08, 0x16, 0x04, 0x06, 0x08, 0x00, 0x86, 0x00, 0x11, 0x00, 0x34, 0x34, 0x14, 0x19,
    0x2d, 0x1e, 0x28, 0x00, 0x0a, 0x23, 0x33, 0x07, 0x33, 0x07, 0x9a, 0x11, 0x9a, 0x11, 0x9a, 0x09,
    0x00, 0x08, 0x66, 0x06, 0xcd, 0x0c, 0x02, 0x00, 0x13, 0x1b, 0xb3, 0x87, 0x79, 0x4d, 0x6a, 0x00,
    0x04, 0x31, 0x20, 0x30, 0x00, 0x31, 0xf0, 0x30, 0x10, 0x31, 0x58, 0x34, 0x50, 0x34, 0x54, 0x36,
    0x44, 0x46, 0x18, 0x43, 0x02, 0x02, 0x01, 0x05, 0x03, 0x03, 0x03, 0x00, 0x04, 0x00, 0x04, 0x04,
    0x08, 0x1a, 0x25, 0x05, 0x02, 0x00, 0x53, 0x00, 0x01, 0x0f, 0x2f, 0x33, 0x19, 0x28, 0x1e, 0x05,
    0x0a, 0x14, 0x0f, 0x23, 0x66, 0x0a, 0x00, 0x08, 0x00, 0x08, 0xcd, 0x08, 0x9a, 0x11, 0x66, 0x06,
    0x9a, 0x11, 0xcd, 0x08, 0x01, 0x01, 0x13, 0x12, 0x92, 0x75, 0xb5, 0x44, 0x6b, 0x00, 0x40, 0x31,
    0x88, 0x32, 0x60, 0x31, 0xd4, 0x31, 0x88, 0x32, 0x4c, 0x37, 0x60, 0x37, 0xd8, 0x31, 0x50, 0x37,
    0x68, 0x37, 0x01, 0x07, 0x01, 0x01, 0x01, 0x06, 0x03, 0x00, 0x04, 0x04, 0x04, 0x07, 0x0c, 0x13,
    0x46, 0x02, 0x08, 0x00, 0x3f, 0x00, 0x18, 0x23, 0x34, 0x34, 0x05, 0x0f, 0x14, 0x28, 0x1e, 0x0a,
    0x14, 0x23, 0x9a, 0x11, 0x9a, 0x09, 0x00, 0x04, 0x00, 0x08, 0x66, 0x06, 0x9a, 0x05, 0x9a, 0x11,
    0x66, 0x0a, 0x02, 0x00, 0x09, 0x26, 0x8c, 0x79, 0xa6, 0x55, 0x6c, 0x00, 0x30, 0x31, 0x2c, 0x31,
    0x28, 0x30, 0xf1, 0xff, 0x44, 0x37, 0xe8, 0x33, 0x18, 0x35, 0x18, 0x35, 0x14, 0x35, 0x2c, 0x35,
    0x00, 0x01, 0x01, 0x05, 0x01, 0x0b, 0x03, 0x00, 0x04, 0x09, 0x04, 0x03, 0x0b, 0x05, 0x67, 0x02,
    0x05, 0x00, 0x37, 0x00, 0x04, 0x1c, 0x23, 0x30, 0x1e, 0x32, 0x14, 0x28, 0x1e, 0x00, 0x14, 0x14,
    0x00, 0x08, 0x9a, 0x11, 0x33, 0x07, 0x66, 0x06, 0x9a, 0x09, 0x00, 0x08, 0x9a, 0x11, 0x9a, 0x09,
    0x02, 0x00, 0x09, 0x18, 0x8d, 0x70, 0xb0, 0x53, 0x3e, 0x00, 0x40, 0x31, 0xf1, 0xff, 0xf1, 0xff,
    0x50, 0x31, 0x48, 0x37, 0xf4, 0x46, 0xa4, 0x46, 0xfc, 0x43, 0xf8, 0x46, 0x34, 0x35, 0x01, 0x0b,
    0x01, 0x0c, 0x04, 0x06, 0x03, 0x01, 0x04, 0x04, 0x04, 0x07, 0x0b, 0x19, 0x47, 0x01, 0x00, 0x00,
    0x91, 0x00, 0x04, 0x05, 0x24, 0x06, 0x2d, 0x19, 0x32, 0x23, 0x28, 0x1e, 0x14, 0x14, 0x66, 0x06,
    0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x02, 0x00,
    0x09, 0x34, 0x80, 0x80, 0x80, 0x80, 0x32, 0x00, 0x50, 0x30, 0x28, 0x37, 0x68, 0x30, 0x88, 0x30,
    0x18, 0x37, 0x58, 0x30, 0x74, 0x30, 0x68, 0x36, 0xe0, 0x30, 0x20, 0x34, 0x01, 0x0b, 0x01, 0x0c,
    0x04, 0x06, 0x03, 0x01, 0x04, 0x04, 0x04, 0x07, 0x09, 0x11, 0x6f, 0x08, 0x06, 0x00, 0x73, 0x00,
    0x1b, 0x06, 0x23, 0x2e, 0x14, 0x23, 0x0f, 0x32, 0x28, 0x0a, 0x1e, 0x19, 0x66, 0x06, 0x33, 0x03,
    0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x05, 0x00, 0x09, 0x13,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x48, 0x33, 0xf1, 0xff, 0x4c, 0x34, 0xec, 0x33, 0xf1, 0xff,
    0xf4, 0x33, 0x6c, 0x37, 0x54, 0x36, 0xf0, 0x33, 0x48, 0x34, 0x00, 0x02, 0x01, 0x01, 0x03, 0x03,
    0x04, 0x05, 0x04, 0x0a, 0x04, 0x08, 0x06, 0x04, 0x46, 0x05, 0x09, 0x00, 0x0a, 0x00, 0x00, 0x11,
    0x12, 0x1a, 0x14, 0x00, 0x0a, 0x23, 0x14, 0x28, 0x0a, 0x05, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04,
    0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x01, 0x02, 0x20, 0x0c, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x00, 0xe0, 0x34, 0xf1, 0xff, 0xb8, 0x30, 0x44, 0x37, 0xa0, 0x30, 0xb4, 0x31,
    0xc8, 0x34, 0x94, 0x36, 0xa4, 0x36, 0xcc, 0x34, 0x02, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x00,
    0x04, 0x08, 0x04, 0x04, 0x08, 0x17, 0x02, 0x00, 0x06, 0x00, 0x4f, 0x00, 0x0a, 0x22, 0x17, 0x2f,
    0x14, 0x00, 0x0a, 0x23, 0x2d, 0x28, 0x0a, 0x05, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09,
    0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x03, 0x02, 0x20, 0x3b, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x00, 0x08, 0x36, 0xf1, 0xff, 0xf1, 0xff, 0x38, 0x31, 0x00, 0x33, 0x14, 0x35, 0x5c, 0x36,
    0x5c, 0x36, 0x24, 0x33, 0x24, 0x33, 0x01, 0x04, 0x01, 0x0b, 0x01, 0x09, 0x03, 0x00, 0x04, 0x00,
    0x04, 0x09, 0x01, 0x13, 0x4b, 0x07, 0x01, 0x00, 0x3f, 0x00, 0x1c, 0x25, 0x0f, 0x3c, 0x14, 0x2d,
    0x0a, 0x23, 0x14, 0x28, 0x0f, 0x05, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04,
    0x66, 0x06, 0xcd, 0x04, 0x66, 0x06, 0x00, 0x02, 0x20, 0x38, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
    0x50, 0x30, 0x68, 0x30, 0xd4, 0x37, 0xc8, 0x37, 0xcc, 0x30, 0xe8, 0x30, 0x4c, 0x36, 0x40, 0x37,
    0xa8, 0x37, 0xe0, 0x30, 0x00, 0x01, 0x01, 0x06, 0x01, 0x09, 0x03, 0x03, 0x04, 0x02, 0x04, 0x05,
    0x04, 0x01, 0x63, 0x08, 0x06, 0x00, 0xbc, 0x00, 0x14, 0x10, 0x1a, 0x05, 0x14, 0x00, 0x0a, 0x2d,
    0x14, 0x23, 0x0a, 0x05, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06,
    0xcd, 0x04, 0x66, 0x06, 0x04, 0x02, 0x20, 0x27, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0xb4, 0x37,
    0xf1, 0xff, 0xa8, 0x36, 0xec, 0x35, 0x00, 0x36, 0xcc, 0x36, 0x04, 0x36, 0xe8, 0x35, 0x4c, 0x37,
    0xfc, 0x35, 0x01, 0x05, 0x01, 0x04, 0x03, 0x00, 0x04, 0x0b, 0x04, 0x0a, 0x04, 0x04, 0x0c, 0x07,
    0x53, 0x06, 0x00, 0x00, 0x54, 0x00, 0x03, 0x12, 0x38, 0x39, 0x2d, 0x23, 0x0a, 0x28, 0x14, 0x1e,
    0x0a, 0x05, 0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04,
    0x66, 0x06, 0x02, 0x02, 0x20, 0x3a, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x78, 0x30, 0x20, 0x30,
    0x54, 0x30, 0x6c, 0x30, 0x60, 0x30, 0x74, 0x36, 0x68, 0x37, 0x8c, 0x37, 0xbc, 0x34, 0xe8, 0x36,
    0x01, 0x02, 0x01, 0x0a, 0x00, 0x01, 0x03, 0x03, 0x04, 0x01, 0x04, 0x00, 0x03, 0x15, 0x6d, 0x08,
    0x06, 0x00, 0x8a, 0x00, 0x16, 0x0e, 0x3d, 0x18, 0x0a, 0x19, 0x05, 0x23, 0x14, 0x28, 0x2d, 0x00,
    0x66, 0x06, 0x33, 0x03, 0x00, 0x04, 0x9a, 0x09, 0xcd, 0x04, 0x66, 0x06, 0xcd, 0x04, 0x66, 0x06,
    0x05, 0x02, 0x20, 0x40,
};
extern const u16 sPackedFurnitureItems[4] = {
    0x4a48, 0x4a4c, 0x4a50, 0x0000,
};
VillagerAnimHeapPool sVillagerAnimHeapPool;
extern const u8 sReservedErrandKinds[16] = {
    0x05, 0x06, 0x08, 0x09, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x14, 0x00, 0x00, 0x00,
};
}
}

namespace nQ {
extern "C" const u8 *VillagerInfo_Get(u32 n) {
    const u8 *r = 0;
    if (VillagerId_IsValidSpecies(n)) r = sVillagerInfoTable + n * 0x4e;
    return r;
}
}

namespace nQ {
extern "C" const u8 *SpNpc_GetInfo(u16 *p) {
    const u8 *r = 0;
    s32 idx = *p & 0xfff;
    s32 t = (s32)(*p & 0xf000) >> 12;
    if (t == 13) {
        if (idx < 0x26) r = sSpNpcInfoTable + idx * 3;
    }
    return r;
}
}

namespace nQ {
extern "C" BOOL Villager_GetSpeciesName(MsgString *buf, u32 x) {
    BOOL r = FALSE;
    if (VillagerId_IsValidSpecies(x)) {
        u8 k = x;
        String_Load(buf, &k, "st_npc_name");
        r = TRUE;
    }
    return r;
}
}

namespace nQ {
extern "C" BOOL Npc_GetName(MsgString *self, u16 *p) {
    s32 idx = *p & 0xfff;
    BOOL r = FALSE;
    s32 t = (s32)(*p & 0xf000) >> 12;
    if (t != 13) {
        if (t == 14) {
            VillagerData *q = SaveVillagers_Get(gSaveVillagers, idx);
            if (q) r = q->getVillagerId()->getName(self);
        }
    } else {
        if (idx < 0x26) {
            u8 k = idx;
            String_Load(self, &k, "st_spnpc_name");
            r = TRUE;
        }
    }
    return r;
}
}

namespace nQ {
extern "C" u32 Npc_GetVoiceType(u16 *p) {
    u32 idx = *p & 0xfff;
    u32 r = 5;
    s32 t = (s32)(*p & 0xf000) >> 12;
    if (t != 13) {
        if (t == 14) {
            VillagerData *q = SaveVillagers_Get(gSaveVillagers, idx);
            if (q) r = VillagerId_GetVoiceType(q->getVillagerId());
        }
    } else {
        const u8 *q = SpNpc_GetInfo(p);
        if (q) r = q[1];
    }
    return r;
}
}

namespace nQ {
extern "C" u32 Npc_GetInfoByte2(u16 *p) {
    u32 idx = *p & 0xfff;
    u32 r = 0;
    s32 t = (s32)(*p & 0xf000) >> 12;
    if (t != 13) {
        if (t == 14) {
            VillagerData *q = SaveVillagers_Get(gSaveVillagers, idx);
            if (q) r = Villager_GetInfoByte2(q);
        }
    } else {
        const u8 *q = SpNpc_GetInfo(p);
        if (q) r = q[2];
    }
    return r;
}
}

namespace nQ {
extern "C" s32 SpNpc_GetInfoByte0(u16 *p) {
    s8 r = 0;
    s32 t = (s32)(*p & 0xf000) >> 12;
    if (t == 13) {
        const s8 *q = (const s8 *)SpNpc_GetInfo(p);
        if (q) r = *q;
    }
    return r;
}
}

namespace nQ {
extern "C" BOOL Villager_GetDefaultCatchphrase(MsgString *buf, u32 x) {
    BOOL r = FALSE;
    if (VillagerId_IsValidSpecies(x)) {
        u8 k = x;
        String_Load(buf, &k, "st_npc_habit");
        r = TRUE;
    }
    return r;
}
}

namespace nQ {
extern "C" BOOL Villager_GetDefaultCatchphraseEncoded(EncodedString *self, u32 x) {
    MsgString11 local;
    BOOL r = FALSE;
    if (Villager_GetDefaultCatchphrase(&local, x)) {
        self->fromMsgString(&local);
        r = TRUE;
    }
    return r;
}
}

namespace nQ {
extern "C" u8 FurnitureTaste_GetTextIndex(u8 *p) {
    u8 r = 0;
    u32 c = p[0];
    switch (c) {
    case 0:
    case 1:
    case 2:
        r = sFurnitureTasteTextBase[c] + p[1] - 1;
        break;
    case 3:
        r = sFurnitureTasteTextBase[c] + p[1];
        break;
    case 4: {
        u32 d = p[1];
        if (d < 12) r = sFurnitureTasteTextBase[c] + d;
        break;
    }
    }
    return r;
}
}

namespace nQ {
extern "C" u32 Date_GetStarSign(u32 a, u32 b) {
    const u8 *p = sStarSignEndDates;
    u32 r = 0;
    u8 i;
    for (i = 0; i < 12; p += 2, i++) {
        u32 c = p[0];
        if (a < c || (a == c && b <= p[1])) {
            r = i;
            break;
        }
    }
    return r;
}
}

namespace nQ {
extern "C" u32 Date_GetStarSignOf(const u8 *p) {
    return Date_GetStarSign(p[0], p[1]);
}
}

namespace nQ {
extern "C" u32 Town_GetMaxOutdoorVillagers() {
    CommManager *o = gCommManager;
    if (o->isSlotActive(o->myAid)) return 0;
    return 4;
}
}

namespace nQ {
extern "C" const u8 *Personality_GetSleepHours(u32 idx) {
    if (idx >= 6) idx = 0;
    return sPersonalitySleepHours[idx];
}
}

namespace nQ {
extern "C" BOOL Personality_IsAsleep(u32 idx, ClockDateTime *buf) {
    const u8 *e = Personality_GetSleepHours(idx);
    ClockDateTimeWords t;
    t.words[0] = 0;
    t.words[1] = 0;
    t.dt.hour = e[0];
    t.dt.minute = e[1];
    if (DateTime_Compare(buf, &t.dt, 6) == 1) {
        s32 c;
        BOOL r;
        t.dt.hour = e[2];
        t.dt.minute = e[3];
        c = DateTime_Compare(buf, &t.dt, 6);
        r = FALSE;
        if (c == -1) r = TRUE;
        return r;
    }
    return FALSE;
}
}

MsgString11::MsgString11() {
    using namespace nQ;}

MsgString11::~MsgString11() {
    using namespace nQ;}

u32 MsgString11::capacity() {
    using namespace nQ; return 0xb; }

u8 *MsgString11::data() {
    using namespace nQ; return text; }

EncodedString10::EncodedString10() {
    using namespace nQ;}

EncodedString10::~EncodedString10() {
    using namespace nQ;}

u32 EncodedString10::capacity() {
    using namespace nQ; return 0xa; }

void EncodedString10::copyTo(void *dst, s32 n) {
    using namespace nQ;
    if (n >= 10) n = 10;
    MI_CpuCopy8(text, dst, n);
}

u8 *EncodedString10::data() {
    using namespace nQ; return text; }

MsgString17::MsgString17() {
    using namespace nQ;}

MsgString17::~MsgString17() {
    using namespace nQ;}

u32 MsgString17::capacity() {
    using namespace nQ; return 0x11; }

u8 *MsgString17::data() {
    using namespace nQ; return text; }

EncodedString16::EncodedString16() {
    using namespace nQ;}

EncodedString16::~EncodedString16() {
    using namespace nQ;}

u32 EncodedString16::capacity() {
    using namespace nQ; return 0x10; }

u8 *EncodedString16::data() {
    using namespace nQ; return text; }

MsgString17B::MsgString17B() {
    using namespace nQ;}

MsgString17B::~MsgString17B() {
    using namespace nQ;}

u32 MsgString17B::capacity() {
    using namespace nQ; return 0x11; }

u8 *MsgString17B::data() {
    using namespace nQ; return text; }

EncodedString16B::EncodedString16B() {
    using namespace nQ;}

EncodedString16B::~EncodedString16B() {
    using namespace nQ;}

u32 EncodedString16B::capacity() {
    using namespace nQ; return 0x10; }

u8 *EncodedString16B::data() {
    using namespace nQ; return text; }

HousePos::HousePos() {
    using namespace nQ;
    HousePos_Clear(&x);
}

HousePos::~HousePos() {
}

namespace nQ {
extern "C" void HousePos_Clear(u8 *p) {
    p[0] = 0xff;
    p[1] = 0xff;
}
}

namespace nQ {
extern "C" BOOL HousePos_IsValid(u8 *p) {
    if (p[0] != 0xff && p[1] != 0xff) return TRUE;
    return FALSE;
}
}

namespace nQ {
extern "C" void HousePos_Set(u8 *p, u8 a, u8 b) {
    p[0] = a;
    p[1] = b;
}
}

namespace nQ {
extern "C" void HousePos_SetFromUnit(u8 *out, s32 *in) {
    HousePos_Set(out, in[0], in[1]);
}
}

namespace nQ {
extern "C" VillagerMemory *VillagerMemory_Construct(VillagerMemory *self) {
    new (self->player) PlayerId(0);
    self->talkDate.words[0] = 0;
    self->talkDate.words[1] = 0;
    TownId_Construct();
    self->receivedItem = 0xfff1;
    VillagerMemory_Clear(self);
    return self;
}
}

namespace nQ {
extern "C" VillagerMemory *VillagerMemory_Destruct(VillagerMemory *self) {
    TownId_Destruct();
    new (self->player) PlayerId();
    return self;
}
}

namespace nQ {
extern "C" void VillagerMemory_Clear(VillagerMemory *self) {
    MI_CpuFill8(self, 0, sizeof(VillagerMemory));
    self->asPlayerId()->clear();
    self->talkDate.words[0] = 0;
    self->talkDate.words[1] = 0;
    self->receivedItem = 0xfff1;
}
}

namespace nQ {
extern "C" BOOL VillagerMemory_IsUsed(VillagerMemory *p) {
    return VillagerMemory_GetPlayerId(p)->isValid();
}
}

namespace nQ {
extern "C" BOOL VillagerMemory_InitForPlayer(VillagerMemory *self, PlayerId *a, TownId *b, ClockDateTime *c) {
    BOOL r = FALSE;
    if (a->isValid()) {
        VillagerMemory_Clear(self);
        VillagerMemory_RecordTalk(self, a, b, c);
        MI_CpuCopy8(a->getName(), self->nickname, 8);
        r = TRUE;
    }
    return r;
}
}

namespace nQ {
extern "C" void VillagerMemory_RecordTalk(VillagerMemory *self, PlayerId *a, TownId *b, ClockDateTime *c) {
    ClockDateTimeWords buf;
    buf.words[0] = 0;
    buf.words[1] = 0;
    if (a != 0 && a->isValid()) self->asPlayerId()->setRaw(a);
    if (b == 0) b = &gSaveTownId;
    if (c == 0) {
        Clock_GetDateTime(&buf.dt);
        c = &buf.dt;
    }
    if (VillagerMemory_UpdateTalkStreak(self, c)) VillagerMemory_AddStreakFriendship(self);
    TownId_Assign(VillagerMemory_GetTownId(self), b);
    MI_CpuCopy8(c, VillagerMemory_GetTalkDate(self), 8);
    self->setTownTune(&gSaveTownTune);
}
}

namespace nQ {
extern "C" ClockDateTime *VillagerMemory_GetTalkDate(VillagerMemory *p) {
    return &p->talkDate.dt;
}
}

namespace nQ {
extern "C" BOOL VillagerMemory_UpdateTalkStreak(VillagerMemory *self, ClockDateTime *p) {
    ClockDateTime *q = VillagerMemory_GetTalkDate(self);
    u16 v = 0;
    BOOL r = 0;
    if (DateTime_IsInvalid(&q->second) == 0) {
        if (DateTime_Compare(p, q, 0x3f) == 1) {
            s32 t = DateTime_DiffDays(q, p);
            if (t == 0) {
                v = self->flags.talkStreak;
            } else {
                if (t == 1) v = self->flags.talkStreak + 1;
                r = TRUE;
            }
        } else {
            r = TRUE;
        }
    } else {
        r = TRUE;
    }
    if (v > 4) v = 4;
    self->flags.talkStreak = v;
    return r;
}
}

namespace nQ {
extern "C" void VillagerMemory_AddStreakFriendship(VillagerMemory *p) {
    s32 v = p->flags.talkStreak;
    if (v > 4) v = 4;
    p->addFriendship((s8)(v + 1));
}
}

namespace nQ {
extern "C" TownId *VillagerMemory_GetTownId(VillagerMemory *p) {
    return &p->town;
}
}

namespace nQ {
extern "C" PlayerId *VillagerMemory_GetPlayerId(VillagerMemory *p) {
    return p->asPlayerId();
}
}

namespace nP {
extern "C" BOOL VillagerMemory_MatchesPlayer(PlayerId *a, PlayerId *b) {
    if (a->townId == b->townId && memcmp(a->townName, b->townName, 8) == 0 && a->equals(b) != 0) return TRUE;
    return FALSE;
}
}

s32 VillagerMemory::getFriendship() {
    using namespace nP; return friendship; }

#pragma dont_inline on
void VillagerMemory::setFriendship(s8 v) {
    using namespace nP; friendship = v; }
#pragma dont_inline reset

s32 VillagerMemory::addFriendship(s32 d) {
    using namespace nP;
    s32 t = friendship + d;
    if (t > 0x7f) t = 0x7f;
    else if (t < -0x80) t = -0x80;
    setFriendship(t);
    return (s8)t;
}

BOOL VillagerMemory::isLetterReceived() {
    using namespace nP; if (flags.f0 == 1) return TRUE; return FALSE; }

void VillagerMemory::setLetterReceived() {
    using namespace nP; flags.f0 = 1; }

void VillagerMemory::getNickname(void *out) {
    using namespace nP;
    EncodedString8 tmp;
    getNicknameEncoded(&tmp);
    ((MsgString *)(out))->fromEncoded(&tmp, 0, 0);
}

void VillagerMemory::getNicknameEncoded(EncodedString *out) {
    using namespace nP;
    StrBuf_ClearAlt(out);
    EncodedString_SetRaw(out, nickname, 8);
}

void VillagerMemory::setNicknameFromMsg(void *out) {
    using namespace nP;
    EncodedString8 tmp;
    tmp.fromMsgString((MsgString *)(out));
    tmp.copyTo(nickname, 8);
}

void VillagerMemory::setNickname(void *src, s32 n) {
    using namespace nP;
    MI_CpuFill8(nickname, 0, 8);
    if (n > 8) n = 8;
    MI_CpuCopy8(src, nickname, n);
}

BOOL VillagerMemory::hasCompliment() {
    using namespace nP; if (flags.f1 == 1) return TRUE; return FALSE; }

void VillagerMemory::getCompliment(void *out) {
    using namespace nP;
    EncodedString16 tmp;
    getComplimentEncoded(&tmp);
    EncodedString_SetRaw(&tmp, compliment, 0x10);
    ((MsgString *)(out))->fromEncoded(&tmp, 0, 0);
}

void VillagerMemory::getComplimentEncoded(EncodedString *out) {
    using namespace nP;
    StrBuf_ClearAlt(out);
    EncodedString_SetRaw(out, compliment, 0x10);
}

void VillagerMemory::setCompliment(void *src, s32 n) {
    using namespace nP;
    MI_CpuFill8(compliment, 0, 0x10);
    if (n > 0x10) n = 0x10;
    MI_CpuCopy8(src, compliment, n);
    flags.f1 = 1;
}

BOOL VillagerMemory::hasGreeting() {
    using namespace nP; if (flags.f3 == 1) return TRUE; return FALSE; }

void VillagerMemory::getGreeting(void *out) {
    using namespace nP;
    EncodedString16B tmp;
    getGreetingEncoded(&tmp);
    ((MsgString *)(out))->fromEncoded(&tmp, 0, 0);
}

void VillagerMemory::getGreetingEncoded(EncodedString *out) {
    using namespace nP;
    StrBuf_ClearAlt(out);
    EncodedString_SetRaw(out, greeting, 0x10);
}

void VillagerMemory::setGreeting(void *src, s32 n) {
    using namespace nP;
    MI_CpuFill8(greeting, 0, 0x10);
    if (n > 0x10) n = 0x10;
    MI_CpuCopy8(src, greeting, n);
    flags.f3 = 1;
}

void VillagerMemory::setReceivedItem(u16 *p) {
    using namespace nP; receivedItem = *p; }

u16 *VillagerMemory::getReceivedItem() {
    using namespace nP; return &receivedItem; }

BOOL VillagerMemory::hasTownTune() {
    using namespace nP; if (flags.f2 == 1) return TRUE; return FALSE; }

void VillagerMemory::setTownTune(long long *src) {
    using namespace nP;
    flags.f2 = 1;
    townTune = *src;
}

u32 VillagerMemory::getImpression() {
    using namespace nP; return impression; }

void VillagerMemory::setImpression(s32 v) {
    using namespace nP; impression = v; }

s32 VillagerMemory::pickUnusedTopic() {
    using namespace nP;
    u32 cnt = 0, idx = 0;
    s32 i;
    u32 n;
    if (usedTopicMask == -1) usedTopicMask = 0;
    i = 0;
    u32 m = usedTopicMask;
    for (; i < 32; i++) {
        if (((m >> i) & 1) == 0) cnt++;
    }
    n = Random_GlobalBelow(cnt);
    for (i = 0; i < 32; i++) {
        if (((usedTopicMask >> i) & 1) == 0) {
            if (n == 0) {
                idx = i;
                break;
            }
            n--;
        }
    }
    if (cnt == 1) usedTopicMask = 0;
    usedTopicMask = usedTopicMask | (1 << idx);
    return idx;
}

void VillagerMemory::setGiftGiven() {
    using namespace nP; flags.f4 = 1; }

BOOL VillagerMemory::isGiftGiven() {
    using namespace nP; if (flags.f4) return TRUE; return FALSE; }

void VillagerMemory::setTalkedToday() {
    using namespace nP; flags.f6 = 1; }

void VillagerMemory::clearTalkedToday() {
    using namespace nP; flags.f6 = 0; }

BOOL VillagerMemory::isTalkedToday() {
    using namespace nP; if (flags.f6) return TRUE; return FALSE; }

void VillagerMemory::setPartyGiftReceived() {
    using namespace nP; flags.f7 = 1; }

void VillagerMemory::clearPartyGiftReceived() {
    using namespace nP; flags.f7 = 0; }

BOOL VillagerMemory::isPartyGiftReceived() {
    using namespace nP; if (flags.f7) return TRUE; return FALSE; }

void VillagerMemory::setPartyGreeted() {
    using namespace nP; flags.f11 = 1; }

void VillagerMemory::clearPartyGreeted() {
    using namespace nP; flags.f11 = 0; }

BOOL VillagerMemory::isPartyGreeted() {
    using namespace nP; if (flags.f11) return TRUE; return FALSE; }

void VillagerMemory::setBirthdayLetterSent() {
    using namespace nP; flags.f12 = 1; }

void VillagerMemory::clearBirthdayLetterSent() {
    using namespace nP; flags.f12 = 0; }

BOOL VillagerMemory::isBirthdayLetterSent() {
    using namespace nP; if (flags.f12) return TRUE; return FALSE; }

void VillagerMemory::setNewYearLetterSent() {
    using namespace nP; flags.f13 = 1; }

void VillagerMemory::clearNewYearLetterSent() {
    using namespace nP; flags.f13 = 0; }

BOOL VillagerMemory::isNewYearLetterSent() {
    using namespace nP; if (flags.f13) return TRUE; return FALSE; }

void VillagerMemory::setFleaMarketVisited() {
    using namespace nP; flags.f14 = 1; }

void VillagerMemory::clearFleaMarketVisited() {
    using namespace nP; flags.f14 = 0; }

BOOL VillagerMemory::isFleaMarketVisited() {
    using namespace nP; if (flags.f14) return TRUE; return FALSE; }

void VillagerMemory::setFortuneGreeting() {
    using namespace nP; flags.f5 = 1; }

void VillagerMemory::clearFortuneGreeting() {
    using namespace nP; flags.f5 = 0; }

BOOL VillagerMemory::hasFortuneGreeting() {
    using namespace nP; if (flags.f5) return TRUE; return FALSE; }

VillagerData::VillagerData() {
    using namespace nP;
    __cxa_vec_ctor(this, 8, sizeof(VillagerMemory), (void (*)(void *))VillagerMemory_Construct, (void (*)(void *))VillagerMemory_Destruct);
    VillagerPlanBlock_Construct((VillagerPlanBlock *)planBlock);
    for (s32 i = 0; i < 10; i++) {
        new (&furniture[i]) ItemId();
    }
    VillagerId_Construct(&villagerId);
    for (s32 i = 0; i < 4; i++) {
        new (&receivedItems[i]) ItemId();
    }
    TownId_Construct();
    new (&housePos) HousePos();
    shirt = 0xfff1;
    TownId_Construct();
}

VillagerData::~VillagerData() {
    using namespace nP;
    TownId_Destruct();
    ((HousePos *)&housePos)->~HousePos();
    TownId_Destruct();
    for (s32 i = 4 - 1; i >= 0; i--) {
        ((ItemId *)&receivedItems[i])->~ItemId();
    }
    VillagerId_Destruct(&villagerId);
    for (s32 i = 10 - 1; i >= 0; i--) {
        ((ItemId *)&furniture[i])->~ItemId();
    }
    VillagerPlanBlock_Destruct((VillagerPlanBlock *)planBlock);
    __cxa_vec_cleanup(this, 8, sizeof(VillagerMemory), (void (*)(void *))VillagerMemory_Destruct);
}

void VillagerData::clear() {
    using namespace nP;
    MI_CpuFill8(this, 0, 0x700);
    VillagerId_Clear(&villagerId);
    shirt = 0x11a8;
    clearCatchphrase();
    for (s32 i = 0; i < 8; i++) VillagerMemory_Clear(&memories[i]);
    TownId_Clear(&movedFromTown.townId);
    for (s32 i = 0; i < 10; i++) furniture[i] = 0xfff1;
    HousePos_Clear(housePos);
    VillagerPlanBlock_Clear((VillagerPlanBlock *)planBlock);
    moveInKind = 3;
    Letter_Clear(&letter);
    Villager_ClearReceivedItems(this);
    TownId_Clear(&letterTown.townId);
}

void VillagerData::copyFrom(void *src) {
    using namespace nP; MI_CpuCopy8(src, this, 0x700); }

void VillagerData::setup(u32 id, u32 a, void *b, u8 c) {
    using namespace nP;
    const VillagerInfo *rec = (const VillagerInfo *)VillagerInfo_Get(id);
    u32 t = 0;
    EncodedString10 tmp;
    if (rec) t = rec->personality;
    villagerId.set(id, t, b);
    StrBuf_ClearAlt(&tmp);
    if (Villager_GetDefaultCatchphraseEncoded(&tmp, id)) {
        tmp.copyTo(catchphrase, 10);
    }
    if (rec) {
        u32 h = rec->shirt;
        u16 t2;
        if (h < 0x100) t2 = h + 0x11a8;
        else t2 = 0x11a8;
        shirt = t2;
        for (s32 i = 0; i < 10; i++) furniture[i] = rec->furniture[i];
        Villager_SetWallpaper(this, rec->wallpaper);
        Villager_SetCarpet(this, rec->carpet);
        VillagerPlanBlock_RollTrend(Villager_GetPlan(this), rec->trendTable, c);
        Villager_PickRoomLayout(this, VillagerPlanBlock_GetPlan(Villager_GetPlan(this))->getState(), 0);
        roomLayout = rec->roomLayout;
        if (VillagerPlanBlock_GetPlan(Villager_GetPlan(this))->getState() == 2) {
            roomLayout = roomLayout % 10;
        }
        Villager_PickShownFurniture(this);
        umbrella = rec->umbrella;
    }
    Villager_SetMoveInKind(this, a);
}

VillagerId *VillagerData::getVillagerId() {
    using namespace nP; return &villagerId; }

Pattern *VillagerData::getPattern() {
    using namespace nP; return &pattern; }

Letter *VillagerData::getLetter() {
    using namespace nP; return &letter; }

s32 VillagerData::receiveLetterFrom(LetterView *id) {
    using namespace nP;
    VillagerMemory *e = 0;
    volatile u16 v[2];
    void *p = Letter_GetSenderPlayer(id);
    BOOL r = FALSE;
    if (p) {
        PlayerId buf(*(const PlayerId *)(p));
        if (buf.isValid()) {
            e = (VillagerMemory *)Villager_FindMemory(this, &buf);
        }
        new (&buf) PlayerId();
    }
    if (e) {
        e->setLetterReceived();
        Letter_Copy(&letter, id);
        TownId_Assign(&letterTown, &gSaveTownId);
        v[0] = ((LetterView *)(void *)(id))->getPresent();
        if (v[0] != 0xfff1) {
            Item_ToPlacedForm((u16 *)&v[1], (u16 *)&v[0], 1);
            if (Item_IsFurniture((u16 *)&v[1]) == 0) {
                BOOL f = FALSE;
                u32 x = v[1];
                u32 y = v[1];
                if (y >= 0x1100 && x <= 0x1143) f = TRUE;
                if (!f) {
                    if (x < 0x1144 || x > 0x1187) goto done;
                }
            }
            Villager_AddReceivedItem(this, (u16 *)&v[0]);
        }
    done:
        r = TRUE;
    }
    return r;
}

BOOL VillagerData::hasLetterFrom(u16 *p) {
    using namespace nO;
    void *m;
    void *r6 = Letter_GetSenderPlayer(&letter);
    if (((PlayerId *)(p))->isValid() && r6) {
        PlayerId o(*(const PlayerId *)(r6));
        u16 *oh = (u16 *)&o;
        if (p[0] == oh[0] && !memcmp(p + 1, oh + 1, 8) && ((PlayerId *)(void *)(p))->equals(&o) && (m = Villager_FindMemory(this, p)) != 0 && ((VillagerMemory *)(void *)(m))->isLetterReceived()) {
            new (&o) PlayerId();
            return TRUE;
        }
        new (&o) PlayerId();
    }
    return FALSE;
}

void VillagerData::replyToLetter(void *p, void *q) {
    using namespace nO;
    VillagerId *r;
    u32 v1c;
    char *x;
    u8 c;
    u16 res, ha, hb, hc, hd;
    u32 v30;
    u32 t1[2], t3[2], t5[2], t2[2], t4[2], t6[2];
    r = getVillagerId();
    if (p == 0) return;
    if (((PlayerData *)(p))->testFlag(1)) return;
    if (!((VillagerId *)(r))->isValid()) return;
    void *r7 = ((PlayerData *)(p))->getPlayerId();
    if (!((PlayerId *)(void *)(r7))->isValid()) return;
    void *e = Villager_FindMemory(this, r7);
    s32 k = MailCheck_GradeLetter(q);
    MsgString9B o;
    switch (k) {
    case 1: {
        s32 t = Random_GlobalBelow(3);
        Villager_SendLetter(((u8 *)"re_bad"), t, r7, r, 0);
        if (e) {
            ((VillagerMemory *)(e))->addFriendship(-3);
        }
        break;
    }
    case 2: {
        res = 0xfff1;
        MsgString33 str80;
        v1c = 0;
        v30 = 0;
        ((PlayerId *)(r7))->getNameString(&o);
        MailText_SetSlot(0, &o);
        s32 i;
        for (i = 0; i < 6; i++) {
            x = TopicWord_PickRandom(&v30, i);
            str80.clear();
            c = v30;
            String_LoadResolveAltText(&str80, &c, x);
            MailText_SetSlot(i + 2, &str80);
        }
        if (((LetterView *)(q))->getPresent() != 0xfff1) {
            s32 w = Letter_GetBodyLength(q);
            if (w <= 0x20) {
                if (Random_GlobalBelow(2) == 0) {
                    ((ItemPickSpec *)(t1))->set(2, 0);
                    t2[0] = t1[0];
                    t2[1] = t1[1];
                    ItemPick_One(&ha, t2, 0, 0, 1, 1, 0);
                    res = ha;
                    ((ItemPickSpec *)t2)->~ItemPickSpec();
                    ((ItemPickSpec *)t1)->~ItemPickSpec();
                } else {
                    ItemPick_FromRange(&hb, 0x1518, 5, 0, 0, 0, 1, 10, 0, 1);
                    res = hb;
                }
            } else if (w <= 0x2f) {
                ((ItemPickSpec *)(t3))->set(0, 0);
                t4[0] = t3[0];
                t4[1] = t3[1];
                ItemPick_One(&hc, t4, 0, 0, 1, 1, 0);
                res = hc;
                ((ItemPickSpec *)t4)->~ItemPickSpec();
                ((ItemPickSpec *)t3)->~ItemPickSpec();
            } else {
                ((ItemPickSpec *)(t5))->set(sLetterReplyGiftLists[Random_GlobalBelow(3)], 0);
                t6[0] = t5[0];
                t6[1] = t5[1];
                ItemPick_One(&hd, t6, 0, 0, 1, 1, 0);
                res = hd;
                ((ItemPickSpec *)t6)->~ItemPickSpec();
                ((ItemPickSpec *)t5)->~ItemPickSpec();
            }
            if (res != 0xfff1) {
                v1c = 10;
            }
        }
        Villager_SendLetter4(((u8 *)"re_normal"), v1c, 10, r7, r, &res);
        if (e) {
            if (((LetterView *)(q))->getPresent() != 0xfff1) {
                ((VillagerMemory *)(e))->addFriendship(5);
            } else {
                ((VillagerMemory *)(e))->addFriendship(3);
            }
        }
        break;
    }
    }
}

namespace nO {
extern "C" void Villager_SendBirthdayLetter(VillagerData *t, void *p, void *q) {
    u16 h[2];
    ClockDateTimeWords buf;
    u32 o1[2];
    u32 o2[2];
    VillagerId *r10 = ((VillagerData *)(t))->getVillagerId();
    if (!p) {
        p = PlayerData_GetCurrent();
    }
    if (((VillagerId *)(r10))->isValid() && p) {
        void *r7 = ((PlayerData *)(p))->getPlayerId();
        if (((PlayerId *)(void *)(r7))->isValid() && !((TownId *)(void *)(r7))->getTownRelation() && !((PlayerData *)(void *)(p))->testFlag(1)) {
            u32 z = 0;
            buf.words[0] = z;
            buf.words[1] = z;
            u8 *r5 = (u8 *)((PlayerData *)(void *)(p))->getBirthday();
            u32 ok = 0;
            if (q == 0) {
                Clock_GetDateTime(&buf.dt);
            } else {
                MI_CpuCopy8(q, &buf, 8);
            }
            if (r5[1] == buf.dt.month && r5[0] == buf.dt.day && buf.dt.hour >= 6) {
                ok = 1;
            }
            if (ok) {
                void *e = Villager_FindMemory(t, r7);
                if (e) {
                    if (((VillagerMemory *)(e))->getFriendship() >= 0x40) {
                        if (!((VillagerMemory *)(e))->isBirthdayLetterSent()) {
                            h[0] = 0xfff1;
                            u16 *hp = 0;
                            ((ItemPickSpec *)(o1))->set(sBirthdayGiftLists[Random_GlobalBelow(3)], 0);
                            o2[0] = o1[0];
                            o2[1] = o1[1];
                            ItemPick_One(&h[1], o2, hp, hp, 1, 1, hp);
                            h[0] = h[1];
                            ((ItemPickSpec *)o2)->~ItemPickSpec();
                            if (h[0] != 0xfff1) {
                                hp = h;
                            }
                            if (Villager_SendLetterWithPaper(((u8 *)"ev_birth"), (u8)Random_GlobalBelow(3), r7, r10, hp, -1)) {
                                ((VillagerMemory *)(e))->setBirthdayLetterSent();
                            }
                            ((ItemPickSpec *)o1)->~ItemPickSpec();
                        }
                    }
                }
            }
        }
    }
}
}

void VillagerData::sendBirthdayLetters(void *a) {
    using namespace nO;
    if (gSavePlayers != 0) {
        s32 i;
        for (i = 0; i < 4; i++) {
            void *p = PlayerData_GetResident(gSavePlayers, i);
            if (p) {
                Villager_SendBirthdayLetter(this, p, a);
            }
        }
    }
}

namespace nO {
extern "C" void Villager_SendNewYearLetter(VillagerData *t, void *p, void *q) {
    ClockDateTimeWords buf;
    u8 buf2[8];
    VillagerId *r7 = ((VillagerData *)(t))->getVillagerId();
    if (!p) {
        p = PlayerData_GetCurrent();
    }
    if (((VillagerId *)(r7))->isValid() && p) {
        void *r6 = ((PlayerData *)(p))->getPlayerId();
        if (((PlayerId *)(void *)(r6))->isValid() && !((TownId *)(void *)(r6))->getTownRelation() && !((PlayerData *)(void *)(p))->testFlag(1)) {
            u32 ok = 0;
            buf.words[0] = ok;
            buf.words[1] = ok;
            if (q == 0) {
                Clock_GetDateTime(&buf.dt);
            } else {
                MI_CpuCopy8(q, &buf, 8);
            }
            MI_CpuCopy8(&buf, buf2, 8);
            if (Unk_0207ff5c_B(Event_GetState(0x13, buf2, 0))) {
                if (buf.dt.hour >= 6) {
                    ok = 1;
                }
            }
            if (ok) {
                void *e = Villager_FindMemory(t, r6);
                if (e) {
                    if (((VillagerMemory *)(e))->getFriendship() >= 0x40) {
                        if (!((VillagerMemory *)(e))->isNewYearLetterSent()) {
                            MsgString25 str;
                            String_FormatNumber(&str, buf.dt.year + 0x7d0, 4, 0, 0, 0);
                            MailText_SetSlot(2, &str);
                            if (Villager_SendLetterWithPaper(((u8 *)"ev_newyear"), (u8)Random_GlobalBelow(3), r6, r7, 0, 2)) {
                                ((VillagerMemory *)(e))->setNewYearLetterSent();
                            }
                        }
                    }
                }
            }
        }
    }
}
}

void VillagerData::sendNewYearLetters(void *a) {
    using namespace nO;
    if (gSavePlayers != 0) {
        s32 i;
        for (i = 0; i < 4; i++) {
            void *p = PlayerData_GetResident(gSavePlayers, i);
            if (p) {
                if (((PlayerId *)(((PlayerData *)(p))->getPlayerId()))->isValid()) {
                    Villager_SendNewYearLetter(this, p, a);
                }
            }
        }
    }
}

namespace nO {
extern "C" void Villager_SendByeLetter(VillagerData *t, void *p) {
    VillagerId *r6 = ((VillagerData *)(t))->getVillagerId();
    if (((VillagerId *)(r6))->isValid()) {
        if (p) {
            void *q = ((PlayerData *)(p))->getPlayerId();
            if (((PlayerId *)(q))->isValid()) {
                if (!((TownId *)(q))->getTownRelation()) {
                    if (Villager_FindMemory(t, q)) {
                        MsgString9C obj;
                        TownId *g = &gSaveTownId;
                        if (g != 0) {
                            if (TownId_IsValid(&g->townId)) {
                                TownId_GetNameString(g, &obj);
                                MailText_SetSlot(2, &obj);
                            }
                        }
                        Villager_SendLetterWithPaper(((u8 *)"byebye"), (u8)Random_GlobalBelow(5), q, r6, 0, -1);
                    }
                }
            }
        }
    }
}
}

void VillagerData::updateMemoriesFromPlayers() {
    using namespace nO;
    if (((VillagerId *)(getVillagerId()))->isValid()) {
        if (gSavePlayers != 0) {
            s32 i;
            for (i = 0; i < 4; i++) {
                void *p = PlayerData_GetResident(gSavePlayers, i);
                if (p) {
                    if (((PlayerId *)(((PlayerData *)(p))->getPlayerId()))->isValid()) {
                        Villager_SendByeLetter(this, p);
                    }
                }
            }
        }
    }
}

s32 VillagerData::findLetterSenderMemory() {
    using namespace nO;
    void *p = Letter_GetSenderPlayer(&letter);
    if (p) {
        PlayerId obj(*(const PlayerId *)(p));
        if (obj.isValid()) {
            s32 r = Villager_FindMemoryIndex(memories, &obj);
            VillagerMemory *m = Villager_GetMemory(memories, r);
            if (m) {
                if (((VillagerMemory *)(m))->isLetterReceived()) {
                    new (&obj) PlayerId();
                    return r;
                }
            }
        }
        new (&obj) PlayerId();
    }
    return -1;
}

BOOL VillagerData::hasLetterSenderMemory() {
    using namespace nO;
    s32 t = findLetterSenderMemory();
    BOOL r = FALSE;
    s32 m = -1;
    if (t != m) {
        r = TRUE;
    }
    return r;
}

u16 *VillagerData::getShirt() {
    using namespace nO;
    return &shirt;
}

void VillagerData::setShirt(u16 *p) {
    using namespace nO;
    shirt = *p;
}

namespace nO {
extern "C" void Villager_GetDefaultShirt(u16 *out, void *idx) {
    *out = 0x11a8;
    if (((VillagerId *)(((VillagerData *)(idx))->getVillagerId()))->isValid()) {
        const u8 *p = VillagerInfo_Get(VillagerId_GetSpecies(((VillagerData *)(void *)(idx))->getVillagerId()));
        if (p) {
            u32 v = *(u16 *)(p + 0x2c);
            *out = v < 0x100 ? (u16)(0x11a8 + v) : 0x11a8;
        }
    }
}
}

namespace nO {
extern "C" void Villager_GetUmbrella(u16 *out, VillagerData *o) {
    u16 r = 0x1380;
    *out = r;
    u32 v = o->umbrella;
    if (v < 0x20) {
        if (v < 0x20) {
            r = v + 0x1380;
        }
        *out = r;
    }
}
}

void VillagerData::setUmbrella(u16 *p) {
    using namespace nO;
    BOOL r = FALSE;
    u32 v = *p;
    if (v >= 0x1380 && v <= 0x139f) {
        r = TRUE;
    }
    if (r) {
        s32 i;
        if (v >= 0x1380 && v <= 0x139f) {
            i = v - 0x1380;
        } else {
            i = -1;
        }
        umbrella = i;
    }
}

namespace nO {
extern "C" void Villager_GetDefaultUmbrella(u16 *out, void *idx) {
    *out = 0x1380;
    if (((VillagerId *)(((VillagerData *)(idx))->getVillagerId()))->isValid()) {
        const u8 *p = VillagerInfo_Get(VillagerId_GetSpecies(((VillagerData *)(void *)(idx))->getVillagerId()));
        if (p) {
            u32 v = p[0x2e];
            *out = v < 0x20 ? (u16)(0x1380 + v) : 0x1380;
        }
    }
}
}

s32 VillagerData::findFreeSlot(s32 n) {
    using namespace nO;
    VillagerData *p = this;
    s32 i;
    for (i = 0; i < n; i++) {
        if (!p->villagerId.isValid()) {
            return i;
        }
        p++;
    }
    return -1;
}

const void *VillagerData::getInfo28() {
    using namespace nO;
    const u8 *r = 0;
    if (((VillagerId *)(getVillagerId()))->isValid()) {
        const u8 *p = VillagerInfo_Get(VillagerId_GetSpecies(((VillagerData *)(void *)(this))->getVillagerId()));
        if (p) {
            r = p + 0x28;
        }
    }
    return r;
}

void VillagerData::clearCatchphrase() {
    using namespace nO;
    MI_CpuFill8(catchphrase, 0x85, 10);
}

void VillagerData::getCatchphrase(MsgString *dst, void *flag) {
    using namespace nO;
    u8 b;
    EncodedString10 buf;
    dst->clear();
    if (flag && Villager_HasFlea(this)) {
        b = Random_GlobalBelow(0x10);
        String_Load(dst, &b, "st_itchy");
    } else {
        getCatchphraseEncoded(&buf);
        ((MsgString *)(dst))->fromEncoded(&buf, 0, 0);
    }
}

void VillagerData::getCatchphraseEncoded(EncodedString *p) {
    using namespace nO;
    StrBuf_ClearAlt(p);
    EncodedString_SetRaw(p, catchphrase, 10);
}

namespace nN {
extern "C" void Villager_SetCatchphraseFromMsg(VillagerData *a, MsgString *b) {
    EncodedString10 s;
    StrBuf_ClearAlt(&s);
    s.fromMsgString(b);
    Villager_SetCatchphraseEncoded(a, &s);
}
}

namespace nN {
extern "C" void Villager_SetCatchphraseEncoded(VillagerData *a, EncodedString10 *b) {
    b->copyTo(a->catchphrase, 10);
}
}

namespace nN {
extern "C" void Villager_SetCatchphrase(VillagerData *a, void *b, s32 c) {
    MI_CpuFill8(a->catchphrase, 0, 10);
    if (c > 10) {
        c = 10;
    }
    MI_CpuCopy8(b, a->catchphrase, c);
}
}

namespace nN {
extern "C" const u8 *Villager_GetBirthday(VillagerData *a) {
    const u8 *r = NULL;
    const u8 *p = VillagerInfo_Get(VillagerId_GetSpecies(a->getVillagerId()));
    if (p != NULL) {
        r = p + 0x26;
    }
    return r;
}
}

namespace nN {
extern "C" s32 Villager_GetUpcomingBirthdayDay(VillagerData *a, s32 b, u8 *c) {
    if (a->getVillagerId()->isValid() != 0 && Villager_GetIndex(a) != -1) {
        u32 id = Villager_GetIndex(a);
        ClockDateTimeWords v;
        ClockDateTimeWords w;
        EventDayEntry recs[7];
        s32 i;
        s32 j;
        s32 n;
        v.words[0] = 0;
        v.words[1] = 0;
        if (c == NULL) {
            Clock_GetDateTime(&v.dt);
        } else {
            MI_CpuCopy8(c, &v, 8);
        }
        for (i = 0; i <= b; i++) {
            EventDayEntry *e = recs;
            MI_CpuCopy8(&v, &w, 8);
            n = EventSchedule_CollectDayAll(recs, &w.dt);
            for (j = 0; j < n; e++, j++) {
                if (e->eventId == id) {
                    return v.dt.year;
                }
            }
            DateTime_AddDays(&v.dt, 1);
        }
    }
    return -1;
}
}

namespace nN {
extern "C" BOOL Villager_CanAttendParty(VillagerData *a) {
    if (a->getVillagerId()->isValid() != 0) {
        u32 r7 = SaveVillagers_GetUnk3830Index(Item_GetSaveData() + 0x8a3c);
        void *r6 = PlayerData_GetCurrent();
        BOOL r = FALSE;
        if (r7 != Villager_GetIndex(a) && Villager_GetResidentStatus(a) == 3 && r6 != NULL) {
            PlayerErrands *q = ((PlayerData *)r6)->getErrands();
            VillagerId *u = a->getVillagerId();
            if (HouseVisitInvite_IsFrom(&q->houseVisitInvite, u) == 0) {
                r = TRUE;
            }
        }
        return r;
    }
    return FALSE;
}
}

namespace nN {
extern "C" u32 Villager_GetStarSign(VillagerData *a) {
    const u8 *p = Villager_GetBirthday(a);
    u32 r = 0xc;
    if (p != NULL) {
        r = Date_GetStarSignOf(p);
    }
    return r;
}
}

namespace nN {
extern "C" u32 Villager_GetAnimalKind(VillagerData *a) {
    u32 r = 0x21;
    const u8 *p = VillagerInfo_Get(VillagerId_GetSpecies(a->getVillagerId()));
    if (p != NULL) {
        r = p[0x4c];
    }
    return r;
}
}

namespace nN {
extern "C" u32 Villager_GetInfoByte2(VillagerData *a) {
    u32 i = Villager_GetAnimalKind(a);
    if (i >= 0x21) {
        i = 0;
    }
    return sAnimalKindByte2[i];
}
}

namespace nN {
extern "C" const u8 *Villager_GetFashionTaste(VillagerData *a) {
    const u8 *r = NULL;
    const u8 *p = VillagerInfo_Get(VillagerId_GetSpecies(a->getVillagerId()));
    if (p != NULL) {
        r = p;
        r += 0x29;
    }
    return r;
}
}

namespace nN {
extern "C" const u8 *Villager_GetInfo(VillagerData *a) {
    const u8 *r = NULL;
    const u8 *p = VillagerInfo_Get(VillagerId_GetSpecies(a->getVillagerId()));
    if (p != NULL) {
        r = p;
    }
    return r;
}
}

namespace nN {
extern "C" const u8 *Villager_GetFurnitureTaste(VillagerData *t, u32 i) {
    const u8 *r = NULL;
    if (i < 6) {
        const u8 *p = VillagerInfo_Get(VillagerId_GetSpecies(t->getVillagerId()));
        if (p != NULL) {
            r = p + 0x1a + i * 2;
        }
    }
    return r;
}
}

namespace nN {
extern "C" u8 Villager_GetFurnitureTasteScore(VillagerData *a, u16 *b) {
    const u8 *p = Villager_GetFurnitureTaste(a, Villager_GetFurnitureTasteIndex(a));
    if (p != NULL) {
        return Furniture_ScoreAttribute(b, p[0], p[1]);
    }
    return 0;
}
}

namespace nN {
extern "C" const u8 *Villager_GetInfo3a(VillagerData *a) {
    const u8 *p = VillagerInfo_Get(VillagerId_GetSpecies(a->getVillagerId()));
    if (p != NULL) {
        return p + 0x3a;
    }
    return NULL;
}
}

namespace nN {
extern "C" BOOL Villager_IsValidMemoryIndex(VillagerMemory *t, u32 i) {
    if (i < 8) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nN {
extern "C" s32 Villager_FindMemoryIndex(VillagerMemory *t, void *id) {
    s32 i = 0;
    for (; i < 8; i++) {
        if (VillagerMemory_MatchesPlayer(t[i].asPlayerId(), (PlayerId *)id) != 0) {
            return i;
        }
    }
    return -1;
}
}

namespace nN {
extern "C" VillagerMemory *Villager_GetMemory(VillagerMemory *t, u32 i) {
    VillagerMemory *e = NULL;
    if (Villager_IsValidMemoryIndex(t, i)) {
        e = &t[i];
    }
    return e;
}
}

namespace nN {
extern "C" VillagerMemory *Villager_FindMemory(void *a, void *b) {
    return Villager_GetMemory((VillagerMemory *)a, Villager_FindMemoryIndex((VillagerMemory *)a, b));
}
}

namespace nN {
extern "C" s32 Villager_FindFreeMemoryIndex(VillagerMemory *t) {
    static NullPlayerIdLocal s;
    s.clear();
    return Villager_FindMemoryIndex(t, &s);
}
}

namespace nN {
extern "C" s32 Villager_FindMemoryIndexById(VillagerMemory *t, void *id) {
    s32 i = 0;
    for (; i < 8; i++) {
        if (((PlayerId *)(VillagerMemory_GetPlayerId(&t[i])))->equals((PlayerId *)(id)) != 0) {
            return i;
        }
    }
    return -1;
}
}

namespace nN {
extern "C" s32 Villager_GetMaxFriendship(VillagerMemory *t) {
    s32 best = -0x80;
    s32 i = 0;
    do {
        if (VillagerMemory_IsUsed(t) != 0) {
            s32 v = ((VillagerMemory *)(t))->getFriendship();
            if (v > best) {
                best = v;
            }
        }
        t++;
        i++;
    } while (i < 8);
    return best;
}
}

namespace nN {
extern "C" s32 Villager_GetMinutesSinceLastTalk(VillagerMemory *t, ClockDateTime *o) {
    s32 best = 0x7fffffff;
    s32 i = 0;
    for (; i < 8; t++, i++) {
        if (VillagerMemory_IsUsed(t) != 0) {
            ClockDateTime *p = VillagerMemory_GetTalkDate(t);
            s32 r = DateTime_Compare(o, p, 0x3f);
            if (r == 1) {
                s32 d = DateTime_DiffMinutes(p, o);
                if (d < best) {
                    best = d;
                }
            } else if (r == -1) {
                s32 d = DateTime_DiffMinutes(o, p);
                if (d < best) {
                    best = d;
                }
            } else {
                return 0;
            }
        }
    }
    return best;
}
}

namespace nN {
extern "C" s32 Villager_PickMemoryToReplace(VillagerMemory *t, s32 (*cb)(void *, void *, void *)) {
    s32 res = -1;
    if (TownId_IsValid(&gSaveTownId.townId) != 0) {
        VillagerMemory *best = NULL;
        s32 i = 0;
        do {
            if (VillagerMemory_IsUsed(t) != 0) {
                if (cb(VillagerMemory_GetPlayerId(t), &gSaveTownId, gSavePlayers) != 0) {
                    if (best != NULL) {
                        if (((VillagerMemory *)(best))->isLetterReceived() == ((VillagerMemory *)(t))->isLetterReceived()) {
                            if (((VillagerMemory *)(best))->getFriendship() > ((VillagerMemory *)(t))->getFriendship()) {
                                best = t;
                                res = i;
                            } else if (((VillagerMemory *)(best))->getFriendship() == ((VillagerMemory *)(t))->getFriendship()) {
                                ClockDateTime *pa = VillagerMemory_GetTalkDate(best);
                                ClockDateTime *pb = VillagerMemory_GetTalkDate(t);
                                if (DateTime_Compare(pa, pb, 0x3f) == 1) {
                                    best = t;
                                    res = i;
                                }
                            }
                        } else if (((VillagerMemory *)(t))->isLetterReceived() == 0) {
                            best = t;
                            res = i;
                        }
                    } else {
                        best = t;
                        res = i;
                    }
                }
            }
            t++;
            i++;
        } while (i < 8);
    }
    return res;
}
}

namespace nN {
extern "C" s32 VillagerMemory_IsFormerResident(void *a, void *townId, void *players) {
    u16 *p = (u16 *)townId;
    BOOL r = FALSE;
    u16 *q = (u16 *)PlayerId_GetTownId(a);
    if (p[0] == q[0] && memcmp(p + 1, q + 1, 8) == 0) {
        if (PlayerDataArray_FindById((u8 *)players, (u16 *)a) == ~r) {
            r = TRUE;
        }
    }
    return r;
}
}

namespace nN {
extern "C" s32 Villager_PickFormerResidentMemoryToReplace(VillagerMemory *t) {
    return Villager_PickMemoryToReplace(t, VillagerMemory_IsFormerResident);
}
}

namespace nN {
extern "C" s32 VillagerMemory_IsOtherTown(void *a, u16 *p, void *c) {
    u16 *q = PlayerId_GetTownId(a);
    if (p[0] != q[0] || memcmp(p + 1, q + 1, 8) != 0) {
        return 1;
    }
    return 0;
}
}

namespace nN {
extern "C" s32 Villager_PickOtherTownMemoryToReplace(VillagerMemory *t) {
    return Villager_PickMemoryToReplace(t, (s32 (*)(void *, void *, void *))VillagerMemory_IsOtherTown);
}
}

namespace nN {
extern "C" s32 Villager_PickMemorySlotForNew(VillagerMemory *t) {
    s32 r = Villager_FindFreeMemoryIndex(t);
    if (r == -1) {
        r = Villager_PickFormerResidentMemoryToReplace(t);
    }
    if (r == -1) {
        r = Villager_PickOtherTownMemoryToReplace(t);
    }
    return r;
}
}

namespace nN {
extern "C" VillagerMemory *Villager_GetMemorySlotForNew(VillagerMemory *t) {
    return Villager_GetMemory(t, Villager_PickMemorySlotForNew(t));
}
}

namespace nN {
extern "C" VillagerMemory *Villager_FindOrCreateMemory(VillagerMemory *t, void *b) {
    VillagerMemory *e = Villager_FindMemory(t, b);
    if (e == NULL) {
        e = Villager_GetMemorySlotForNew(t);
        if (e != NULL) {
            VillagerMemory_InitForPlayer(e, (PlayerId *)b, 0, 0);
        }
    }
    return e;
}
}

namespace nN {
extern "C" s32 Villager_CollectOtherMemories(VillagerMemory *t, VillagerMemory **out, void *id0, s32 mode) {
    PlayerId *id = (PlayerId *)id0;
    s32 n = 0;
    if (id->isValid() != 0) {
        s32 i = 0;
        do {
            VillagerMemory *e = &t[i];
            if (VillagerMemory_IsUsed(e) != 0 && VillagerMemory_MatchesPlayer(e->asPlayerId(), id) == 0) {
                switch (mode) {
                case 0: {
                    TownId *p = VillagerMemory_GetTownId(e);
                    if (p->townId == gSaveTownId.townId && memcmp(p->townName, gSaveTownId.townName, 8) == 0) {
                        out[n] = e;
                        n++;
                    }
                    break;
                }
                case 1: {
                    TownId *p = VillagerMemory_GetTownId(e);
                    if (p->townId != gSaveTownId.townId || memcmp(p->townName, gSaveTownId.townName, 8) != 0) {
                        out[n] = e;
                        n++;
                    }
                    break;
                }
                default:
                    out[n] = e;
                    n++;
                    break;
                }
            }
            i++;
        } while (i < 8);
    }
    return n;
}
}

namespace nN {
extern "C" s32 Villager_CountMemories(VillagerMemory *t) {
    s32 n = 0;
    s32 i = 0;
    do {
        if (VillagerMemory_IsUsed(t) != 0) {
            n++;
        }
        t++;
        i++;
    } while (i < 8);
    return n;
}
}

namespace nN {
extern "C" BOOL Villager_IsMoreAttachedThan(void *a, void *b, ClockDateTime *c) {
    s32 x, y;
    if (((VillagerId *)(void *)(((VillagerData *)(void *)(a))->getVillagerId()))->isValid() == 0) {
        return FALSE;
    }
    if (((VillagerId *)(void *)(((VillagerData *)(void *)(b))->getVillagerId()))->isValid() == 0) {
        return TRUE;
    }
    x = Villager_CountMemories((VillagerMemory *)a);
    y = Villager_CountMemories((VillagerMemory *)b);
    if (x > y) {
        return TRUE;
    }
    if (x < y) {
        return FALSE;
    }
    x = ((VillagerData *)(void *)((VillagerMemory *)a))->hasLetterSenderMemory();
    y = ((VillagerData *)(void *)((VillagerMemory *)b))->hasLetterSenderMemory();
    if (x != 0) {
        if (y == 0) {
            return TRUE;
        }
    } else if (y != 0) {
        return FALSE;
    }
    x = Villager_GetMaxFriendship((VillagerMemory *)a);
    y = Villager_GetMaxFriendship((VillagerMemory *)b);
    if (x > y) {
        return TRUE;
    }
    if (x < y) {
        return FALSE;
    }
    x = Villager_GetMinutesSinceLastTalk((VillagerMemory *)a, c);
    y = Villager_GetMinutesSinceLastTalk((VillagerMemory *)b, c);
    if (x < y) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nN {
extern "C" void Villager_GetNicknameFor(void *a, void *b, void *c) {
    VillagerMemory *e = Villager_FindMemory(a, c);
    if (e == NULL || ((PlayerId *)(void *)(c))->isValid() == 0 || ((VillagerMemory *)(void *)(e))->getFriendship() <= -10) {
        ((PlayerId *)(c))->getNameString((MsgString *)(b));
    } else {
        ((VillagerMemory *)(e))->getNickname(b);
    }
}
}

namespace nN {
extern "C" VillagerMemory *Villager_SetNicknameFromMsgFor(void *a, void *b, void *c) {
    VillagerMemory *e = Villager_FindMemory(a, c);
    if (e != NULL) {
        ((VillagerMemory *)(e))->setNicknameFromMsg(b);
    }
    return e;
}
}

namespace nN {
extern "C" VillagerMemory *Villager_SetNicknameFor(void *a, void *b, u32 c, void *d) {
    VillagerMemory *e = Villager_FindMemory(a, d);
    if (e != NULL) {
        e->setNickname(b, c);
    }
    return e;
}
}

namespace nN {
extern "C" void Villagers_ShareNickname(VillagerData *a, void *b, void *c) {
    VillagerMemory *e1, *e2;
    void *t;
    if (c == NULL) {
        c = PlayerData_GetCurrent();
    }
    if (c != NULL) {
        t = ((PlayerData *)(c))->getPlayerId();
        if (((PlayerId *)(void *)(t))->isValid() != 0 && (((VillagerData *)(void *)(a))->getVillagerId())->isValid() != 0 && (((VillagerData *)(void *)(b))->getVillagerId())->isValid() != 0) {
            VillagerMemory *r6 = NULL, *r7 = NULL;
            e1 = Villager_FindMemory(b, t);
            e2 = Villager_FindMemory(a, t);
            MsgString9B s1;
            MsgString9B s2;
            if (e1 != NULL && e2 != NULL) {
                ((PlayerId *)(t))->getNameString((MsgString *)(&s2));
                ((VillagerMemory *)(e1))->getNickname(&s1);
                if (((MsgString *)(&s2))->equals((MsgString *)(&s1)) == 0) {
                    r7 = e1;
                    r6 = e2;
                } else {
                    ((MsgString *)(&s1))->clear();
                    ((VillagerMemory *)(e2))->getNickname(&s1);
                    if (((MsgString *)(&s2))->equals((MsgString *)(&s1)) == 0) {
                        r7 = e2;
                        r6 = e1;
                    }
                }
                if (r7 != NULL && r6 != NULL) {
                    ((MsgString *)(&s1))->clear();
                    ((VillagerMemory *)(r7))->getNickname(&s1);
                    ((VillagerMemory *)(r6))->setNicknameFromMsg(&s1);
                }
            }
        }
    }
}
}

void VillagerDataItemView::getComplimentFor(void *a, void *c) {
    using namespace nM;
    void *o = Villager_FindMemory(this, c);
    if (o) {
        if (((PlayerId *)(c))->isValid()) {
            if (((VillagerMemory *)(o))->hasCompliment()) {
                ((VillagerMemory *)(o))->getCompliment(a);
            }
        }
    }
}

void VillagerDataItemView::setComplimentFor(void *a, s32 n, void *c) {
    using namespace nM;
    void *o = Villager_FindMemory(this, c);
    if (o) {
        ((VillagerMemory *)(o))->setCompliment(a, n);
    }
}

BOOL VillagerDataItemView::getGreetingFor(void *a, void *c) {
    using namespace nM;
    void *o = Villager_FindMemory(this, c);
    BOOL r = FALSE;
    if (o) {
        if (((PlayerId *)(c))->isValid()) {
            if (((VillagerMemory *)(o))->hasGreeting()) {
                ((VillagerMemory *)(o))->getGreeting(a);
                r = TRUE;
            }
        }
    }
    return r;
}

void VillagerDataItemView::setGreetingFor(void *a, s32 n, void *c) {
    using namespace nM;
    void *o = Villager_FindMemory(this, c);
    if (o) {
        ((VillagerMemory *)(o))->setGreeting(a, n);
    }
}

u8 *VillagerDataItemView::getMovedFromTownId() {
    using namespace nM;
    return movedFromTown;
}

void VillagerDataItemView::clearHousePos() {
    using namespace nM;
    HousePos_Clear(housePos);
}

s32 VillagerDataItemView::hasHousePos() {
    using namespace nM;
    return HousePos_IsValid(housePos);
}

u8 *VillagerDataItemView::getHousePos() {
    using namespace nM;
    return housePos;
}

void VillagerDataItemView::setHousePos(u8 *p) {
    using namespace nM;
    housePos[0] = p[0];
    housePos[1] = p[1];
}

void VillagerDataItemView::placeHouseMarker() {
    using namespace nM;
    TownBlockMap *r4 = TownBlockMap_Get();
    if (r4 != 0) {
        if (hasHousePos() != 0) {
            u8 *r2 = getHousePos();
            u16 v = 0x500a;
            BlockMap_RemoveStructure(r4, r2[0], r2[1], &v);
        }
    }
}

BOOL VillagerDataItemView::getRoomLayout(s32 *o1, s32 *o2) {
    using namespace nM;
    void *t;
    BOOL r = FALSE;
    if (((VillagerId *)(((VillagerData *)(this))->getVillagerId()))->isValid() != 0) {
        if (VillagerInfo_Get(VillagerId_GetSpecies(((VillagerData *)(void *)(this))->getVillagerId())) != 0) {
            t = VillagerPlanBlock_GetPlan(Villager_GetPlan((VillagerData *)this));
            if (((VillagerPlan *)(void *)(t))->getState() == 2 ||
                ((((VillagerPlan *)(void *)(t))->getState() == 8 || ((VillagerPlan *)(void *)(t))->getState() == 9 || ((VillagerPlan *)(void *)(t))->getState() == 10 ||
                  ((VillagerPlan *)(void *)(t))->getState() == 11) &&
                 ((VillagerPlan *)(void *)(t))->hasState2Flag() != 0)) {
                *o1 = 3;
                *o2 = roomLayout % 10;
            } else {
                *o1 = 2;
                *o2 = roomLayout;
            }
            r = TRUE;
        }
    }
    return r;
}

s32 VillagerDataItemView::getInfo28Item() {
    using namespace nM;
    const VillagerInfo28Bits *b = (const VillagerInfo28Bits *)((VillagerData *)(this))->getInfo28();
    s32 r = 0;
    if (b) {
        r = (s32)b->v >> 2;
        if (r < 0 || r >= 5) {
            r = 0;
        }
    }
    return 0x1010 + r;
}

BOOL VillagerDataItemView::isValidFurnitureIndex(s32 idx) {
    using namespace nM;
    if ((u32)idx < 10) {
        return TRUE;
    }
    return FALSE;
}

s32 VillagerDataItemView::getSlotFromLayoutCode(u16 *pp) {
    using namespace nM;
    volatile u16 *p = pp;
    s32 idx = -1;
    BOOL f = FALSE;
    u32 v = *p;
    if (v >= 0xf000 && v <= 0xf02f) {
        f = TRUE;
    }
    if (f) {
        if (v >= 0xf000 && v <= 0xf02f) {
            idx = (*p - 0xf000) >> 2;
        } else {
            idx = -1;
        }
        if (idx >= 3) {
            idx -= 2;
        }
    }
    return idx;
}

PlacedFurnitureItem VillagerDataItemView::getFurnitureAt(s32 idx) {
    using namespace nM;
    PlacedFurnitureItem out;
    out.v = 0xfff1;
    if (isValidFurnitureIndex(idx)) {
        out.v = furniture[idx];
        if (out.v != 0xfff1) {
            u16 tmp;
            Item_ToPlacedForm(&tmp, &out.v, 1);
            out.v = tmp;
        }
    }
    return out;
}

u16 *VillagerDataItemView::getFurniture() {
    using namespace nM;
    return furniture;
}

BOOL VillagerDataItemView::getSlotRange(s32 *lo, s32 *hi, s32 mode, s32 type, u8 flag) {
    using namespace nM;
    BOOL r = FALSE;
    switch (mode) {
    case 0:
        *lo = 5;
        *hi = 10;
        r = TRUE;
        break;
    case 1:
        *lo = 1;
        *hi = 5;
        if (type == 2 || (type == 8 && flag)) {
            *lo = 3;
        }
        r = TRUE;
        break;
    case 2:
        *lo = 0;
        if (type == 2 || (type == 8 && flag)) {
            *hi = 3;
        } else {
            *hi = 1;
        }
        r = TRUE;
        break;
    }
    return r;
}

s32 VillagerDataItemView::pickEmptySlot(s32 lo, s32 hi) {
    using namespace nM;
    s32 res;
    if (isValidFurnitureIndex(lo)) {
        u16 *p = furniture + lo;
        u16 mask = 0;
        s32 cnt = 0;
        for (; lo < hi; p++, lo++) {
            if (isValidFurnitureIndex(lo) && *p == 0xfff1) {
                mask |= 1 << lo;
                cnt++;
            }
        }
        res = Random_PickSetBit(mask, cnt, 10);
    } else {
        res = -1;
    }
    return res;
}

s32 VillagerDataItemView::findCheapestSlot(s32 lo, s32 hi) {
    using namespace nM;
    s32 res;
    if (isValidFurnitureIndex(lo)) {
        u16 *p = furniture + lo;
        s32 min = 99999;
        volatile s32 best = -1;
        for (; lo < hi; p++, lo++) {
            if (isValidFurnitureIndex(lo) && *p != 0xfff1) {
                s32 v = Item_GetPrice(p);
                if (v <= min) {
                    best = lo;
                    min = v;
                }
            }
        }
        res = best;
    } else {
        res = -1;
    }
    return res;
}

BOOL VillagerDataItemView::isInsectItem(u16 *p) {
    using namespace nM;
    BOOL r = FALSE;
    if (*p >= 0x12b0 && *p <= 0x12e7) {
        r = TRUE;
    }
    if (r) {
        return TRUE;
    }
    return FALSE;
}

BOOL VillagerDataItemView::isFishItem(u16 *p) {
    using namespace nM;
    BOOL r = FALSE;
    if (*p >= 0x12e8 && *p <= 0x131f) {
        r = TRUE;
    }
    if (r) {
        return TRUE;
    }
    return FALSE;
}

BOOL VillagerDataItemView::isFossilItem(u16 *p) {
    using namespace nM;
    BOOL r = FALSE;
    if (*p >= 0x450c && *p <= 0x45db) {
        r = TRUE;
    }
    if (r) {
        return TRUE;
    }
    return FALSE;
}

BOOL VillagerDataItemView::isShirtItem(u16 *p) {
    using namespace nM;
    BOOL r = FALSE;
    if (*p >= 0x11a8 && *p <= 0x12a7) {
        r = TRUE;
    }
    if (r) {
        return TRUE;
    }
    return FALSE;
}

BOOL VillagerDataItemView::isTasteFurniture(u16 *item) {
    using namespace nM;
    BOOL r = FALSE;
    BOOL ok = FALSE;
    if (Item_IsFurniture(item)) {
        if (!Unk_0207e940_InRange(item, 0x450c, 0x45db)) {
            ok = TRUE;
        }
    }
    if (ok) {
        if (Villager_GetFurnitureTasteScore(reinterpret_cast<VillagerData *>(this), item) > 0) {
            r = TRUE;
        }
    }
    return r;
}

Unk_0207ed1c_Fn VillagerDataItemView::getTrendFilter(s32 type) {
    using namespace nM;
    u8 k = 3;
    u32 idx = PlanState_GetGroupIndex(&k, type);
    if (k == 0 && idx < 5) {
        return sVillagerTrendFilters[idx];
    }
    return *(Unk_0207ed1c_Fn *)__ptmf_null;
}

BOOL VillagerDataItemView::matchesTrend(u16 *p, s32 type) {
    using namespace nM;
    Unk_0207ed1c_Fn f = getTrendFilter(type);
    BOOL r = TRUE;
    if (f) {
        if (!(this->*f)(p)) {
            r = FALSE;
        }
    }
    return r;
}

s32 VillagerDataItemView::pickNonTrendSlot(s32 type, s32 lo, s32 hi) {
    using namespace nM;
    s32 res;
    if (isValidFurnitureIndex(lo)) {
        u16 *p = furniture + lo;
        u16 mask = 0;
        s32 cnt = 0;
        for (; lo < hi; p++, lo++) {
            if (isValidFurnitureIndex(lo) && *p != 0xfff1 && !matchesTrend(p, type)) {
                mask |= 1 << lo;
                cnt++;
            }
        }
        res = Random_PickSetBit(mask, cnt, 10);
    } else {
        res = -1;
    }
    return res;
}

namespace nM {
extern "C" BOOL Villager_DiscardItem(u16 *p) {
    if (RecycleBin_Add(*p) != 0) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nM {
extern "C" BOOL Villager_DiscardItemMaybe(u16 *p) {
    if (Random_GlobalBelow(2) == 0) {
        if (RecycleBin_Add(*p) != 0) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}
}

s32 VillagerDataItemView::freeSlotInRange(s32 mode, s32 type, u8 a, u8 c) {
    using namespace nM;
    s32 lo = 0, hi = 0;
    s32 r;
    if (getSlotRange(&lo, &hi, mode, type, a)) {
        r = pickEmptySlot(lo, hi);
        if (r == -1) {
            r = pickNonTrendSlot(type, lo, hi);
            if (r == -1 && c) {
                r = findCheapestSlot(lo, hi);
            }
            if (r != -1) {
                Villager_DiscardItemMaybe(furniture + r);
            }
        }
        if (r != -1) {
            furniture[r] = 0xfff1;
        }
        return r;
    } else {
        return -1;
    }
}

s32 VillagerDataItemView::getFossilPartIndex(u16 *item) {
    using namespace nM;
    if (Unk_0207e940_InRange(item, 0x450c, 0x45db)) {
        s32 want = Item_GetFossilGroup(item);
        if ((u32)want < 0x18) {
            u16 tmp = 0xfff1;
            u32 i;
            for (i = 0; i < 0x34; i++) {
                tmp = i < 0x34 ? 0x450c + i * 4 : 0x450c;
                if (want == Item_GetFossilGroup(&tmp)) {
                    s32 r;
                    if (Unk_0207e940_InRange(item, 0x450c, 0x45db)) {
                        r = (*item - 0x450c) >> 2;
                    } else {
                        r = -1;
                    }
                    return r - i;
                }
            }
        }
    }
    return -1;
}

BOOL VillagerDataItemView::tryPlaceFossil(u16 *item, s32 mode, s32 type, u8 a, u8 b) {
    using namespace nM;
    s32 lo, hi;
    if (Unk_0207e940_InRange(item, 0x450c, 0x45db)) {
        if (mode == 2) {
            lo = 0;
            hi = 0;
            if (getSlotRange(&lo, &hi, mode, type, a)) {
                s32 range = hi - lo;
                s32 idx = getFossilPartIndex(item);
                s32 slot = 0;
                if (idx >= 0) {
                    slot = lo + DS_MOD(idx, range);
                }
                if (isValidFurnitureIndex(slot)) {
                    u16 *p = furniture + slot;
                    if (*p == 0xfff1) {
                        *p = *item;
                        return TRUE;
                    }
                    BOOL occupied = matchesTrend(p, type);
                    if (b) {
                        PlanErrand *v10;
                        ErrandRecord *v14;
                        v10 = VillagerPlanBlock_GetErrand(Villager_GetPlan((VillagerData *)this));
                        v14 = PlanErrand_GetRecord(v10);
                        Item_GetPrice(item);
                        Item_GetPrice(p);
                        if (type == 2) {
                            s32 lim = 0x18;
                            if (v14->isActive() != 0 && v14->getKind() == 2 &&
                                PlanErrand_GetStep(v10) >= 2 && PlanErrand_GetFossilGroup(v10) < 0x18) {
                                lim = PlanErrand_GetFossilGroup(v10);
                            }
                            if (lim < 0x18) {
                                if (lim == Item_GetFossilGroup(item)) {
                                    Villager_DiscardItemMaybe(p);
                                    *p = *item;
                                    return TRUE;
                                } else if (occupied) {
                                    if (lim == Item_GetFossilGroup(p)) {
                                        Villager_DiscardItemMaybe(item);
                                        goto fail;
                                    } else {
                                        Villager_DiscardItemMaybe(p);
                                        *p = *item;
                                        return TRUE;
                                    }
                                } else {
                                    Villager_DiscardItemMaybe(p);
                                    *p = *item;
                                    return TRUE;
                                }
                            } else {
                                Villager_DiscardItemMaybe(p);
                                *p = *item;
                                return TRUE;
                            }
                        } else {
                            Villager_DiscardItemMaybe(p);
                            *p = *item;
                            return TRUE;
                        }
                    } else {
                        if (occupied) {
                            Villager_DiscardItemMaybe(item);
                            goto fail;
                        } else {
                            Villager_DiscardItemMaybe(p);
                            *p = *item;
                            return TRUE;
                        }
                    }
                }
            }
        }
    }
fail:
    return FALSE;
}

namespace nL {
extern "C" BOOL Villager_PlaceItemInHouse(VillagerData *a, u16 *b) {
    u16 v[1];
    if (*b != 0xfff1) {
        VillagerPlan *plan;
        s32 r7, s8, n, f;
        Item_ToPlacedForm(v, b, 1);
        plan = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
        r7 = plan->getState();
        s8 = plan->hasState2Flag();
        if (Item_IsFurniture(v) != 0) {
            s32 r6 = ((VillagerDataItemView *)(a))->matchesTrend((u16 *)(b), r7);
            n = Ftr_GetUnk05(v);
            f = 0;
            if (*b >= 0x450c && *b <= 0x45db) f = 1;
            if (f != 0 && n == 2) {
                return ((VillagerDataItemView *)(a))->tryPlaceFossil((u16 *)(b), n, r7, s8, r6);
            }
            r6 = ((VillagerDataItemView *)(a))->freeSlotInRange(n, r7, s8, r6);
            if (((VillagerDataItemView *)(a))->isValidFurnitureIndex(r6) != 0) {
                a->furniture[r6] = *b;
                return TRUE;
            }
            Villager_DiscardItemMaybe(b);
        } else {
            f = 0;
            if (*b >= 0x1100 && *b <= 0x1143) f = 1;
            if (f != 0) {
                Villager_SetWallpaper(a, (u8)((*b >= 0x1100 && *b <= 0x1143) ? *b - 0x1100 : -1));
            } else if (*b >= 0x1144 && *b <= 0x1187) {
                Villager_SetCarpet(a, (u8)((*b >= 0x1144 && *b <= 0x1187) ? *b - 0x1144 : -1));
            }
        }
    }
    return FALSE;
}
}

namespace nL {
extern "C" s32 Villager_CountFurnitureLike(VillagerData *a, u16 *b) {
    u16 *p = a->furniture;
    s32 cnt = 0;
    s32 i = 0;
    s32 z2 = 0;
    s32 z1 = 0;
    do {
        s32 r;
        if (Item_IsFurniture(p) != 0) {
            s32 t = Item_GetFurnitureIndex(p);
            r = (t == Item_GetFurnitureIndex(b)) ? 1 : z1;
        } else {
            r = (*p == *b) ? 1 : z2;
        }
        if (r != 0) cnt++;
        p++; i++;
    } while (i < 10);
    return cnt;
}
}

namespace nL {
extern "C" s32 Villager_CountFurniture(VillagerData *a) {
    u16 *p = a->furniture;
    s32 cnt = 0;
    s32 i;
    for (i = 0; i < 10; p++, i++) {
        if (*p != 0xfff1) cnt++;
    }
    return cnt;
}
}

namespace nL {
extern "C" void Villager_DropRandomFurniture(VillagerData *a) {
    s32 cnt, r6, i;
    s32 s8, sc;
    s32 x, y;
    FurnitureDropSlots tbl;
    if (a->getVillagerId()->isValid() != 0) {
        if (Villager_CountFurniture(a) >= 7) {
            if (Random_GlobalBelow(2) == 0) {
                void *r4 = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
                s8 = ((VillagerPlan *)(void *)(r4))->getState();
                sc = ((VillagerPlan *)(void *)(r4))->hasState2Flag();
                tbl = *(FurnitureDropSlots *)data_020e05ac;
                s32 *p = tbl.v;
                cnt = 0;
                x = 0;
                y = 0;
                for (r6 = 0; r6 < 3; r6++) {
                    if (((VillagerDataItemView *)(a))->getSlotRange(&x, &y, r6, s8, sc) != 0) {
                        p[r6] = ((VillagerDataItemView *)(a))->pickNonTrendSlot(s8, x, y);
                        if (((VillagerDataItemView *)(a))->isValidFurnitureIndex(p[r6]) != 0) cnt++;
                    }
                }
                if (cnt > 0) {
                    r6 = Random_GlobalBelow(cnt);
                    if (r6 < 3) {
                        for (i = 0; i < 3; i++) {
                            s32 r7 = tbl.v[i];
                            if (((VillagerDataItemView *)(a))->isValidFurnitureIndex(r7) != 0) {
                                if (r6 == 0) {
                                    u16 *q = &a->furniture[r7];
                                    if (*q != 0xfff1) Villager_DiscardItem(q);
                                    *q = 0xfff1;
                                    break;
                                }
                                r6--;
                            }
                        }
                    }
                }
            }
        }
    }
}
}

namespace nL {
extern "C" void Villager_ClearFurnitureSlots1To2(VillagerData *a) {
    u16 *p = &a->furniture[1];
    s32 i;
    for (i = 0; i < 2; p++, i++) *p = 0xfff1;
}
}

namespace nL {
extern "C" void Villager_GetPackedFurniture(u16 *out, void *a, u16 *in) {
    *out = 0xfff1;
    if (Item_IsFurniture(in) != 0) {
        s32 r = Ftr_GetUnk05(in);
        if (r < 3) *out = sPackedFurnitureItems[r];
    }
}
}

namespace nL {
extern "C" void Villager_ResolveRoomLayout(VillagerData *a, u16 *b) {
    u16 x, y, z;
    s32 i, idx;
    BOOL r7;
    x = 0xfff1;
    r7 = (Villager_GetResidentStatus(a) != 3) ? 1 : 0;
    i = 0;
    for (i = 0; i < 0x100; b++, i++) {
        BOOL f = FALSE;
        if (*b >= 0xf000 && *b <= 0xf02f) f = TRUE;
        if (f) {
            idx = ((VillagerDataItemView *)(a))->getSlotFromLayoutCode((u16 *)(b));
            y = ((VillagerDataItemView *)a)->getFurnitureAt(idx).v;
            x = y;
            if (r7) {
                if (Item_IsFurniture(&x)) {
                    if (Villager_IsFurnitureShown(a, idx)) {
                        Villager_GetPackedFurniture(&z, a, &x);
                        x = z;
                    } else {
                        x = 0xfff1;
                    }
                }
            }
            if (Item_IsFurniture(&x)) {
                Item_SetFurnitureDirection(&x, *b & 3);
                *b = x;
            } else {
                *b = 0xfff1;
            }
        }
    }
}
}

namespace nL {
extern "C" void Villager_PlaceReceivedItems(VillagerData *a) {
    if (gCommManager->isSlotActive(gCommManager->myAid) == 0) {
        if (a->getVillagerId()->isValid() != 0) {
            u16 *r4 = Villager_GetReceivedItem(a, 0);
            BOOL r6 = FALSE;
            s32 i = 0;
            do {
                if (Villager_PlaceItemInHouse(a, r4) != 0) r6 = TRUE;
                r4++; i++;
            } while (i < 4);
            Villager_ClearReceivedItems(a);
            if (r6 != 0) {
                RoomFtrState_ResetVillagerHouse(Villager_GetIndex(a));
            }
            PlanErrand_MarkReady(VillagerPlanBlock_GetErrand(Villager_GetPlan(a)));
        }
    }
}
}

namespace nL {
extern "C" void Villager_PickRoomLayout(VillagerData *a, s32 b, s32 c) {
    if (b == 2) {
        a->roomLayout = Random_GlobalBelow(10);
        Villager_ClearFurnitureSlots1To2(a);
    } else {
        a->roomLayout = Random_GlobalBelow(0x28);
        if (c != 0) Villager_ClearFurnitureSlots1To2(a);
    }
}
}

namespace nL {
extern "C" s32 Villager_GetFurnitureSlotAt(VillagerData *a, u32 *b, u8 *c, s32 d) {
    if (c != 0) {
        u32 y = b[1];
        u32 x = b[0];
        if (x < 16 && y < 16) {
            s32 i;
            u8 *e = c;
            for (i = 0; i < d; e += 4, i++) {
                if (b[0] == e[2] && b[1] == e[3]) {
                    u16 code = *(u16 *)e;
                    if (Unk_0207e440_InRange(&code)) return ((VillagerDataItemView *)(a))->getSlotFromLayoutCode((u16 *)(&code));
                }
            }
        }
    }
    return -1;
}
}

namespace nL {
extern "C" BOOL Villager_RemoveFurnitureAt(VillagerData *a, u32 *b, u8 *c, s32 d) {
    s32 r4 = Villager_GetFurnitureSlotAt(a, b, c, d);
    if (((VillagerDataItemView *)(a))->isValidFurnitureIndex(r4) != 0) {
        a->furniture[r4] = 0xfff1;
        Villager_HideFurniture(a, r4);
        return TRUE;
    }
    return FALSE;
}
}

namespace nL {
extern "C" BOOL Villager_HasShownFurnitureAt(VillagerData *a, u32 *b, u8 *c, s32 d) {
    s32 r4 = Villager_GetFurnitureSlotAt(a, b, c, d);
    if (((VillagerDataItemView *)(a))->isValidFurnitureIndex(r4) != 0) {
        if (a->furniture[r4] != 0xfff1) {
            if (Villager_IsFurnitureShown(a, r4) != 0) return TRUE;
        }
    }
    return FALSE;
}
}

namespace nL {
extern "C" u32 Villager_GetWallpaper(VillagerData *a) { return a->wallpaper; }
}

namespace nL {
extern "C" u32 Villager_GetCarpet(VillagerData *a) { return a->carpet; }
}

namespace nL {
extern "C" void Villager_SetWallpaper(VillagerData *a, u8 b) { a->wallpaper = b; }
}

namespace nL {
extern "C" void Villager_SetCarpet(VillagerData *a, u8 b) { a->carpet = b; }
}

namespace nL {
extern "C" u32 Villager_GetInfo4d(VillagerData *a) {
    const u8 *p = VillagerInfo_Get(VillagerId_GetSpecies(a->getVillagerId()));
    if (p != 0) return p[0x4d];
    return 0;
}
}

namespace nL {
extern "C" s32 Villager_FindOwnIndex(VillagerData *a) {
    u8 *g = gSaveVillagers;
    s32 r = -1;
    if (g != 0) {
        r = SaveVillagers_FindIndex(g, a->getVillagerId());
    }
    return r;
}
}

namespace nL {
extern "C" s32 Villager_GetIndex(VillagerData *a) { return Villager_FindOwnIndex(a); }
}

namespace nL {
extern "C" VillagerState *Villager_GetState(VillagerData *a) {
    VillagerStateTable *r4 = VillagerStates_Get();
    return VillagerStateTable_GetEntry(r4, Villager_FindOwnIndex(a));
}
}

namespace nL {
extern "C" s32 Villager_GetWhereabouts(VillagerData *a) {
    s32 r4 = 0;
    if (a->getVillagerId()->isValid() != 0) {
        VillagerState *st = Villager_GetState(a);
        if (gCommManager->isSlotActive(gCommManager->myAid) != 0) {
            if (VillagerState_GetPresence(st) == 2) r4 = 2;
            else r4 = 1;
        } else {
            switch (VillagerState_GetRole(st)) {
            case 0:
                if (VillagerState_GetPresence(st) == 2) r4 = 2;
                else r4 = 1;
                break;
            case 2:
                r4 = 3;
                break;
            case 3:
                r4 = 4;
                break;
            case 5:
                r4 = 6;
                break;
            case 6:
                r4 = 7;
                break;
            case 4:
                r4 = 5;
                break;
            case 1:
            default:
                r4 = 0;
                break;
            }
        }
    }
    return r4;
}
}

namespace nL {
extern "C" BOOL Villager_IsHouseAvailable() { return TRUE; }
}

namespace nL {
extern "C" void *Villager_GetPlan(VillagerData *a) { return a->planBlock; }
}

namespace nL {
extern "C" s32 Villager_GetTrend(VillagerData *a, MsgString *out) {
    if ((u32)VillagerPlanBlock_GetPlan(a->planBlock)->getStateGroup() <= 1) {
        return VillagerPlan::getTrendName(out, VillagerPlanBlock_GetPlan(a->planBlock)->getState());
    } else {
        return VillagerPlan::getTrendName(out, 7);
    }
}
}

namespace nL {
extern "C" s32 Villager_GetResidentStatus(VillagerData *a) {
    if (Villager_IsMovingOut(a) != 0) return 0;
    if (Villager_IsMovingIn(a) != 0) return 1;
    if (Villager_IsJustMovedIn(a) != 0) return 2;
    return 3;
}
}

namespace nL {
extern "C" BOOL Villager_IsMovingOut(VillagerData *a) {
    if (a->getVillagerId()->isValid() != 0) {
        if (VillagerPlanBlock_GetPlan(Villager_GetPlan(a))->getState() == 9) return TRUE;
    }
    return FALSE;
}
}

namespace nL {
extern "C" BOOL Villager_IsMovingIn(VillagerData *a) {
    if (a->getVillagerId()->isValid() != 0) {
        if (VillagerPlanBlock_GetPlan(Villager_GetPlan(a))->getState() == 0xa) return TRUE;
    }
    return FALSE;
}
}

namespace nL {
extern "C" BOOL Villager_IsJustMovedIn(VillagerData *a) {
    if (a->getVillagerId()->isValid() != 0) {
        if (VillagerPlanBlock_GetPlan(Villager_GetPlan(a))->getState() == 0xb) return TRUE;
    }
    return FALSE;
}
}

namespace nL {
extern "C" BOOL Villager_CanBeTalkPartner(VillagerData *a) {
    PlayerErrands *r4 = PlayerData_GetCurrent()->getErrands();
    if (a->getVillagerId()->isValid() != 0) {
        if (Villager_GetResidentStatus(a) == 3) {
            if (Villager_GetWhereabouts(a) != 2) {
                if (Villager_IsInPlayerErrand(a, r4) == 0) return TRUE;
            }
        }
    }
    return FALSE;
}
}

namespace nL {
extern "C" BOOL Villager_IsInPlayerErrand(VillagerData *a, PlayerErrands *b) {
    VillagerId *r4 = a->getVillagerId();
    if (r4->isValid() != 0) {
        PlayerErrandSlot *r7 = PlayerErrands_GetSlot(b, 0);
        PlayerErrandSlot *s0 = PlayerErrands_GetSlot(b, 1);
        HouseVisitInvite *s4 = &b->houseVisitInvite;
        VillagerId *r5;
        if (PlayerErrandSlot_GetRecord(r7)->isActive() != 0) {
            if (((r5 = (VillagerId *)(PlayerErrandSlot_GetVillager(r7, 0))), (r5->townId == r4->townId && memcmp(r5->townName, r4->townName, 8) == 0 && r5->species == r4->species)) || ((r5 = (VillagerId *)(PlayerErrandSlot_GetVillager(r7, 1))), (r5->townId == r4->townId && memcmp(r5->townName, r4->townName, 8) == 0 && r5->species == r4->species))) return TRUE;
        }
        if (PlayerErrandSlot_GetRecord(s0)->isActive() != 0) {
            if (((r5 = (VillagerId *)(PlayerErrandSlot_GetVillager(s0, 0))), (r5->townId == r4->townId && memcmp(r5->townName, r4->townName, 8) == 0 && r5->species == r4->species)) || ((r5 = (VillagerId *)(PlayerErrandSlot_GetVillager(s0, 1))), (r5->townId == r4->townId && memcmp(r5->townName, r4->townName, 8) == 0 && r5->species == r4->species))) return TRUE;
        }
        if (Arbeit_IsLetterRecipient(b, r4) != 0) return TRUE;
        if (HouseVisitInvite_IsFrom(s4, r4) != 0) return TRUE;
    }
    return FALSE;
}
}

namespace nL {
extern "C" u32 Villager_GetMoveInKind(VillagerData *a) { return a->moveInKind; }
}

namespace nL {
extern "C" void Villager_SetMoveInKind(VillagerData *a, u32 b) { a->moveInKind = b; }
}

namespace nL {
extern "C" void Villager_GetFriendName(void *a, MsgString *b) {
    void *r = SaveVillagers_FindFriendOf(gSaveVillagers, (u8 *)a);
    if (r != 0) {
        if (((VillagerData *)(void *)(r))->getVillagerId()->isValid() != 0) {
            ((VillagerData *)(void *)(r))->getVillagerId()->getName(b);
        }
    }
}
}

namespace nK {
extern "C" void Villager_GetEnemyName(void *a, MsgString *b) {
    void *r = SaveVillagers_FindEnemyOf(gSaveVillagers, (u8 *)a);
    if (r) {
        if (((VillagerId *)(((VillagerData *)(r))->getVillagerId()))->isValid()) {
            ((VillagerId *)(((VillagerData *)(r))->getVillagerId()))->getName(b);
        }
    }
}
}

namespace nK {
extern "C" void Villager_GetRandomOtherName(VillagerData *a, MsgString *b) {
    void *v;
    func_02133ef8(&v, 4);
    v = ((VillagerData *)a)->getVillagerId();
    void *r = SaveVillagers_PickRandomExcept(gSaveVillagers, &v, 1);
    if (r) {
        if (((VillagerId *)(((VillagerData *)(r))->getVillagerId()))->isValid()) {
            ((VillagerId *)(((VillagerData *)(r))->getVillagerId()))->getName(b);
        }
    }
}
}

namespace nK {
extern "C" BOOL ImpressionCond_PlayerFaceFlag(PlayerData *a, s32 b, s32 c) { return PlayerData_HasStungFace(a); }
}

namespace nK {
extern "C" BOOL ImpressionCond_WeedsAround(PlayerData *, s32, s32 ) {
    VecFx32 *tb = PlayerActor_GetBodyPos(4);
    if (Unk_0207dd24_IsZero(gFieldSceneKind) && tb) {
        BlockMap *m = gSceneBlockMap;
        if (m) {
            s32 cnt = 0;
            s32 xy[2];
            xy[0] = 0;
            xy[1] = 0;
            FieldPos_ToUnit(&xy[0], &xy[1], tb);
            s32 x, y;
            for (y = xy[1] - 1; y <= xy[1] + 1; y++) {
                for (x = xy[0] - 1; x <= xy[0] + 1; x++) {
                    s32 hx, hy;
                    long yy = y;
                    hx = x >> 4;
                    hy = yy >> 4;
                    u16 *c = (u16 *)BlockMap_GetItemPtr(m, hx, hy, x - (hx << 4), yy - (hy << 4), 0);
                    if (c) {
                        BOOL r = FALSE;
                        if (*c >= 0x21 && *c <= 0x24) r = TRUE;
                        if (r) {
                            cnt++;
                            if (cnt >= 3) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_FlowersAround(PlayerData *, s32, s32 ) {
    VecFx32 *tb = PlayerActor_GetBodyPos(4);
    if (Unk_0207dd24_IsZero(gFieldSceneKind) && tb) {
        BlockMap *m = gSceneBlockMap;
        if (m) {
            s32 cnt = 0;
            s32 xy[2];
            xy[0] = 0;
            xy[1] = 0;
            FieldPos_ToUnit(&xy[0], &xy[1], tb);
            s32 x, y, hx, hy;
            for (y = xy[1] - 1; y <= xy[1] + 1; y++) {
                for (x = xy[0] - 1; x <= xy[0] + 1; x++) {
                    long yy = y;
                    hx = x >> 4;
                    hy = yy >> 4;
                    u16 *c = (u16 *)BlockMap_GetItemPtr(m, hx, hy, x - (hx << 4), yy - (hy << 4), 0);
                    if (c) {
                        if (Unk_0207dd24_Check(c)) {
                            cnt++;
                            if (cnt >= 2) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_FewVillagers(PlayerData *, s32, s32 ) {
    BOOL r = FALSE;
    if (SaveVillagers_Count(gSaveVillagers) <= 4) r = TRUE;
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_VillagerEventToday(PlayerData *a, s32, s32 ) {
    if (VillagerEvent_GetTodayIndex() != 0xb) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_Mood1(PlayerData *a, s32 b, s32 c) {
    if (c == 1) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_Mood2or4(PlayerData *a, s32 b, s32 c) {
    if (c == 2 || c == 4) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_HoldingNet(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHeldItem();
    BOOL k = TRUE;
    if (!Unk_0207d774_R(p, 0x1376, 0x1376)) {
        if (*p < 0x1377 || *p > 0x1377) k = FALSE;
    }
    return k;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_HoldingAxe(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHeldItem();
    BOOL k = TRUE;
    if (!Unk_0207d774_R(p, 0x136b, 0x1372)) {
        if (*p < 0x1373 || *p > 0x1373) k = FALSE;
    }
    return k;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_HoldingRod(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHeldItem();
    BOOL k = TRUE;
    if (!Unk_0207d774_R(p, 0x1374, 0x1374)) {
        if (*p < 0x1375 || *p > 0x1375) k = FALSE;
    }
    return k;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_HoldingWateringCan(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHeldItem();
    BOOL k = TRUE;
    if (!Unk_0207d774_R(p, 0x1378, 0x1378)) {
        if (*p < 0x1379 || *p > 0x1379) k = FALSE;
    }
    return k;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingHat13c1(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHat();
    BOOL r;
    u16 g[2];
    if (Item_IsFurniture(p)) {
        g[0] = 0x13c1;
        s32 x = Item_GetFurnitureIndex(p);
        r = x == Item_GetFurnitureIndex(&g[0]);
    } else {
        r = *p == 0x13c1;
    }
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingHat13b2(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHat();
    BOOL r;
    u16 g[2];
    if (Item_IsFurniture(p)) {
        g[0] = 0x13b2;
        s32 x = Item_GetFurnitureIndex(p);
        r = x == Item_GetFurnitureIndex(&g[0]);
    } else {
        r = *p == 0x13b2;
    }
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingHat13a8(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHat();
    BOOL r;
    u16 g[2];
    if (Item_IsFurniture(p)) {
        g[0] = 0x13a8;
        s32 x = Item_GetFurnitureIndex(p);
        r = x == Item_GetFurnitureIndex(&g[0]);
    } else {
        r = *p == 0x13a8;
    }
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingHat13bc(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHat();
    BOOL r;
    u16 g[2];
    if (Item_IsFurniture(p)) {
        g[0] = 0x13bc;
        s32 x = Item_GetFurnitureIndex(p);
        r = x == Item_GetFurnitureIndex(&g[0]);
    } else {
        r = *p == 0x13bc;
    }
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingHat1405(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHat();
    BOOL r;
    u16 g[2];
    if (Item_IsFurniture(p)) {
        g[0] = 0x1405;
        s32 x = Item_GetFurnitureIndex(p);
        r = x == Item_GetFurnitureIndex(&g[0]);
    } else {
        r = *p == 0x1405;
    }
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingHat13e6(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHat();
    BOOL r;
    u16 g[2];
    if (Item_IsFurniture(p)) {
        g[0] = 0x13e6;
        s32 x = Item_GetFurnitureIndex(p);
        r = x == Item_GetFurnitureIndex(&g[0]);
    } else {
        r = *p == 0x13e6;
    }
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingHat13ea(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHat();
    BOOL r;
    u16 g[2];
    if (Item_IsFurniture(p)) {
        g[0] = 0x13ea;
        s32 x = Item_GetFurnitureIndex(p);
        r = x == Item_GetFurnitureIndex(&g[0]);
    } else {
        r = *p == 0x13ea;
    }
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingHat13f5(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHat();
    BOOL r;
    u16 g[2];
    if (Item_IsFurniture(p)) {
        g[0] = 0x13f5;
        s32 x = Item_GetFurnitureIndex(p);
        r = x == Item_GetFurnitureIndex(&g[0]);
    } else {
        r = *p == 0x13f5;
    }
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingHat13e3(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHat();
    BOOL r;
    u16 g[2];
    if (Item_IsFurniture(p)) {
        g[0] = 0x13e3;
        s32 x = Item_GetFurnitureIndex(p);
        r = x == Item_GetFurnitureIndex(&g[0]);
    } else {
        r = *p == 0x13e3;
    }
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingHat13e4(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHat();
    BOOL r;
    u16 g[2];
    if (Item_IsFurniture(p)) {
        g[0] = 0x13e4;
        s32 x = Item_GetFurnitureIndex(p);
        r = x == Item_GetFurnitureIndex(&g[0]);
    } else {
        r = *p == 0x13e4;
    }
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingHat1406(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHat();
    BOOL r;
    u16 g[2];
    if (Item_IsFurniture(p)) {
        g[0] = 0x1406;
        s32 x = Item_GetFurnitureIndex(p);
        r = x == Item_GetFurnitureIndex(&g[0]);
    } else {
        r = *p == 0x1406;
    }
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_FlowerAccessory(PlayerData *a, s32, s32 ) {
    BOOL k2 = TRUE;
    BOOL k1 = k2;
    if (!Unk_0207d774_R(((PlayerData *)(a))->getHeldItem(), 0x137c, 0x137c)) {
        if (!Unk_0207d774_R(((PlayerData *)(a))->getHat(), 0x1408, 0x1428)) k1 = FALSE;
    }
    if (!k1) {
        if (!Unk_0207d774_R(((PlayerData *)(void *)(a))->getFaceItem(), 0x1471, 0x1491)) k2 = FALSE;
    }
    return k2;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_HoldingUmbrella(PlayerData *a, s32, s32 ) {
    u16 *p = ((PlayerData *)(a))->getHeldItem();
    BOOL k = TRUE;
    if (!Unk_0207d774_R(p, 0x1380, 0x139f)) {
        if (*p < 0x13a0 || *p > 0x13a7) k = FALSE;
    }
    return k;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_Raining(PlayerData *, s32, s32 ) {
    if (Weather_GetFallingPrecip() == 1) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_Snowing(PlayerData *, s32, s32 ) {
    if (Weather_GetFallingPrecip() == 2) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_WearingShirt12a8(PlayerData *a, s32, s32 ) {
    BOOL r = Unk_0207d774_R(((PlayerData *)(a))->getShirt(), 0x12a8, 0x12af);
    if (r) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_TimeOfDay0(PlayerData *, s32, s32 ) {
    if (Clock_GetTimeOfDay() == 0) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_TimeOfDay3(PlayerData *, s32, s32 ) {
    if (Clock_GetTimeOfDay() == 3) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_PocketsFull(PlayerData *a, s32, s32 ) {
    s32 t = ((PlayerInventory *)(void *)(((PlayerData *)(void *)((void *)a))->getInventory()))->findEmptyPocket();
    BOOL r = FALSE;
    s32 m = -1;
    if (t == m) r = TRUE;
    return r;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_FriendshipVeryLow(PlayerData *a, s32 b, s32) {
    if (b <= -0x50) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_FriendshipLow(PlayerData *a, s32 b, s32) {
    if (b <= -0x1e) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_FriendshipHigh(PlayerData *a, s32 b, s32) {
    if (b >= 0x46 && b < 0x6e) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_FriendshipVeryHigh(PlayerData *a, s32 b, s32) {
    if (b >= 0x6e) return TRUE;
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_HalfInsectsCaught(PlayerData *a, s32 b, s32 c) {
    if (ImpressionCond_AllInsectsCaught(a, b, c) == 0) {
        if (ImpressionCond_AllFishCaught(a, b, c) == 0) {
            s32 h = (u32)Catalog_GetInsectTotal() >> 1;
            if (Catalog_CountInsects() >= h) return TRUE;
            return FALSE;
        }
    }
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_AllInsectsCaught(PlayerData *, s32, s32 ) { return Catalog_HasAllInsects(); }
}

namespace nK {
extern "C" BOOL ImpressionCond_HalfFishCaught(PlayerData *a, s32 b, s32 c) {
    if (ImpressionCond_AllFishCaught(a, b, c) == 0) {
        s32 h = (u32)Catalog_GetFishTotal() >> 1;
        if (Catalog_CountFish() >= h) return TRUE;
        return FALSE;
    }
    return FALSE;
}
}

namespace nK {
extern "C" BOOL ImpressionCond_AllFishCaught(PlayerData *a, s32 b, s32 c) { return Catalog_HasAllFish(); }
}

namespace nJ {
extern "C" BOOL ImpressionCond_BellsUpTo300(PlayerData *a, s32, s32 ) {
    if (((PlayerInventory *)(void *)(((PlayerData *)(void *)((void *)a))->getInventory()))->getTotalBells(1) <= 300) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_BellsUpTo1000(PlayerData *a, s32, s32 ) {
    if (((PlayerInventory *)(void *)(((PlayerData *)(void *)((void *)a))->getInventory()))->getTotalBells(1) <= 1000) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_Bells10000To20000(PlayerData *a, s32, s32 ) {
    s32 v = ((PlayerInventory *)(void *)(((PlayerData *)(void *)((void *)a))->getInventory()))->getTotalBells(1);
    if (v >= 10000 && v < 20000) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_Bells20000To40000(PlayerData *a, s32, s32 ) {
    s32 v = ((PlayerInventory *)(void *)(((PlayerData *)(void *)((void *)a))->getInventory()))->getTotalBells(1);
    if (v >= 20000 && v < 40000) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_Bells40000To60000(PlayerData *a, s32, s32 ) {
    s32 v = ((PlayerInventory *)(void *)(((PlayerData *)(void *)((void *)a))->getInventory()))->getTotalBells(1);
    if (v >= 40000 && v < 60000) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_BellsOver60000(PlayerData *a, s32, s32 ) {
    if (((PlayerInventory *)(void *)(((PlayerData *)(void *)((void *)a))->getInventory()))->getTotalBells(1) >= 60000) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_AccessoryHairD(PlayerData *a, s32 b, s32 c) {
    BOOL r = FALSE;
    if (Unk_0207d3b0_InRange(((PlayerData *)((void *)a))->getFaceItem(), 0x1431, 0x1470)) {
        if (ImpressionCond_Hair0(a, b, c) || ImpressionCond_Hair1(a, b, c) || ImpressionCond_Hair4(a, b, c) || ImpressionCond_Hair5(a, b, c) ||
            ImpressionCond_Hair7(a, b, c)) {
            r = TRUE;
        }
    }
    return r;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_AccessoryHairC(PlayerData *a, s32 b, s32 c) {
    BOOL r = FALSE;
    if (Unk_0207d3b0_InRange(((PlayerData *)((void *)a))->getFaceItem(), 0x1431, 0x1470)) {
        if (ImpressionCond_Hair2(a, b, c) || ImpressionCond_Hair3(a, b, c) || ImpressionCond_Hair6(a, b, c)) {
            r = TRUE;
        }
    }
    return r;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_AccessoryHairB(PlayerData *a, s32 b, s32 c) {
    BOOL r = FALSE;
    if (Unk_0207d3b0_InRange(((PlayerData *)((void *)a))->getFaceItem(), 0x1431, 0x1470)) {
        if (ImpressionCond_Hair2(a, b, c) || ImpressionCond_Hair4(a, b, c) || ImpressionCond_Hair6(a, b, c)) {
            r = TRUE;
        }
    }
    return r;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_AccessoryHairA(PlayerData *a, s32 b, s32 c) {
    BOOL r = FALSE;
    if (Unk_0207d3b0_InRange(((PlayerData *)((void *)a))->getFaceItem(), 0x1431, 0x1470)) {
        if (ImpressionCond_Hair0(a, b, c) || ImpressionCond_Hair1(a, b, c) || ImpressionCond_Hair3(a, b, c) || ImpressionCond_Hair5(a, b, c) ||
            ImpressionCond_Hair7(a, b, c)) {
            r = TRUE;
        }
    }
    return r;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_Hair0(PlayerData *a, s32 b, s32 c) {                                                     if (((PlayerData *)(a))->getHairStyle() == 0 || ((PlayerData *)(a))->getHairStyle() == 8) {                              return TRUE;                                                                 }                                                                                return FALSE;                                                                }
}

namespace nJ {
extern "C" BOOL ImpressionCond_Hair1(PlayerData *a, s32 b, s32 c) {                                                     if (((PlayerData *)(a))->getHairStyle() == 1 || ((PlayerData *)(a))->getHairStyle() == 9) {                              return TRUE;                                                                 }                                                                                return FALSE;                                                                }
}

namespace nJ {
extern "C" BOOL ImpressionCond_Hair2(PlayerData *a, s32 b, s32 c) {                                                     if (((PlayerData *)(a))->getHairStyle() == 2 || ((PlayerData *)(a))->getHairStyle() == 10) {                              return TRUE;                                                                 }                                                                                return FALSE;                                                                }
}

namespace nJ {
extern "C" BOOL ImpressionCond_Hair3(PlayerData *a, s32 b, s32 c) {                                                     if (((PlayerData *)(a))->getHairStyle() == 3 || ((PlayerData *)(a))->getHairStyle() == 11) {                              return TRUE;                                                                 }                                                                                return FALSE;                                                                }
}

namespace nJ {
extern "C" BOOL ImpressionCond_Hair4(PlayerData *a, s32 b, s32 c) {                                                     if (((PlayerData *)(a))->getHairStyle() == 4 || ((PlayerData *)(a))->getHairStyle() == 12) {                              return TRUE;                                                                 }                                                                                return FALSE;                                                                }
}

namespace nJ {
extern "C" BOOL ImpressionCond_Hair5(PlayerData *a, s32 b, s32 c) {                                                     if (((PlayerData *)(a))->getHairStyle() == 5 || ((PlayerData *)(a))->getHairStyle() == 13) {                              return TRUE;                                                                 }                                                                                return FALSE;                                                                }
}

namespace nJ {
extern "C" BOOL ImpressionCond_Hair6(PlayerData *a, s32 b, s32 c) {                                                     if (((PlayerData *)(a))->getHairStyle() == 6 || ((PlayerData *)(a))->getHairStyle() == 14) {                              return TRUE;                                                                 }                                                                                return FALSE;                                                                }
}

namespace nJ {
extern "C" BOOL ImpressionCond_Hair7(PlayerData *a, s32 b, s32 c) {                                                     if (((PlayerData *)(a))->getHairStyle() == 7 || ((PlayerData *)(a))->getHairStyle() == 15) {                              return TRUE;                                                                 }                                                                                return FALSE;                                                                }
}

namespace nJ {
extern "C" BOOL ImpressionCond_FourResidents(PlayerData *a, s32, s32 ) {
    if (((TownId *)(void *)(((PlayerData *)(void *)((void *)a))->getPlayerId()))->getTownRelation() == 0 && PlayerDataArray_CountUsed(gSavePlayers) == 4) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_TwoPlusResidents(PlayerData *a, s32, s32 ) {
    if (((TownId *)(void *)(((PlayerData *)(void *)((void *)a))->getPlayerId()))->getTownRelation() == 0 && PlayerDataArray_CountUsed(gSavePlayers) >= 2) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_Winter(PlayerData *, s32, s32 ) {
    ClockDateTimeWords d;
    u32 v;
    d.words[0] = 0;
    d.words[1] = 0;
    Clock_GetDateTime(&d.dt);
    v = d.dt.month;
    if (v == 12 || (v >= 1 && v <= 2)) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_Autumn(PlayerData *, s32, s32 ) {
    ClockDateTimeWords d;
    u32 v;
    d.words[0] = 0;
    d.words[1] = 0;
    Clock_GetDateTime(&d.dt);
    v = d.dt.month;
    if (v >= 9 && v <= 11) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_Summer(PlayerData *, s32, s32 ) {
    ClockDateTimeWords d;
    u32 v;
    d.words[0] = 0;
    d.words[1] = 0;
    Clock_GetDateTime(&d.dt);
    v = d.dt.month;
    if (v >= 6 && v <= 8) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" BOOL ImpressionCond_Always(PlayerData *, s32, s32 ) {
    return TRUE;
}
}

namespace nJ {
extern "C" u32 Impression_Evaluate(PlayerData *a, s32 b, s32 c) {
    s32 t = ((PlayerId *)a->getPlayerId())->getGender();
    const ImpressionRule *e = sImpressionRules;
    u32 ret = 0x58;
    s32 i;
    for (i = 0; i < 0x58; e++, i++) {
        if (e->gender == 2 || e->gender == t) {
            if (e->cond(a, b, c)) {
                ret = (u8)i;
                break;
            }
        }
    }
    return ret;
}
}

namespace nJ {
extern "C" u32 Villager_UpdateImpression(VillagerData *self, VillagerMemory *r, PlayerData *p) {
    u32 ret = 0x58;
    if (((VillagerData *)self)->getVillagerId()->isValid()) {
        if (p == 0) {
            p = PlayerData_GetCurrent();
        }
        if (p != 0 && r == 0) {
            r = Villager_FindMemory(self, p->getPlayerId());
        }
        if (r != 0) {
            ret = r->getFriendship();
            ret = Impression_Evaluate(p, ret, VillagerState_GetMood(Villager_GetState(self)));
            r->setImpression(ret);
        }
    }
    return ret;
}
}

namespace nJ {
extern "C" void Villager_GetImpressionText(void *self, MsgString *out, PlayerData *p) {
    VillagerMemory *r;
    if (p == 0) {
        p = PlayerData_GetCurrent();
    }
    r = 0;
    if (p != 0) {
        r = Villager_FindMemory(self, p->getPlayerId());
    }
    if (r != 0) {
        u32 v = r->getImpression();
        if (v < 0x58) {
            u8 b = v;
            String_Load(out, &b, "st_impress");
        }
    }
}
}

namespace nJ {
extern "C" void Villager_ClearReceivedItems(VillagerData *self) {
    u16 *p = self->receivedItems;
    s32 i;
    for (i = 0; i < 4; p++, i++) {
        *p = 0xfff1;
    }
}
}

namespace nJ {
extern "C" u16 *Villager_GetReceivedItem(VillagerData *self, u32 idx) {
    if (idx < 4) {
        return &self->receivedItems[idx];
    }
    return NULL;
}
}

namespace nJ {
extern "C" void Villager_CompactReceivedItems(VillagerData *self) {
    s32 i;
    s32 j;
    for (i = 0; i < 3; i++) {
        if (self->receivedItems[i] == 0xfff1) {
            for (j = i + 1; j < 4; j++) {
                if (self->receivedItems[j] != 0xfff1) {
                    self->receivedItems[i] = self->receivedItems[j];
                    self->receivedItems[j] = 0xfff1;
                    break;
                }
            }
            if (j == 4) {
                break;
            }
        }
    }
}
}

namespace nJ {
extern "C" void Villager_AddReceivedItem(VillagerData *self, u16 *val) {
    u16 tmp;
    s32 idx;
    Villager_CompactReceivedItems(self);
    tmp = 0xfff1;
    idx = Villager_FindReceivedItem(self, &tmp);
    if (idx != -1) {
        self->receivedItems[idx] = *val;
    } else {
        s32 i = 0;
        s32 n;
        do {
            n = i + 1;
            self->receivedItems[i] = self->receivedItems[n];
            i = n;
        } while (n < 3);
        self->receivedItems[3] = *val;
    }
    VillagerSync_Items(self, Villager_GetReceivedItem(self, 0));
}
}

namespace nJ {
extern "C" s32 Villager_FindReceivedItem(VillagerData *self, u16 *key) {
    u16 *p = Villager_GetReceivedItem(self, 0);
    s32 i;
    BOOL z0 = FALSE;
    BOOL z1 = FALSE;
    for (i = 0; i < 4; p++, i++) {
        BOOL r;
        if (Item_IsFurniture(key)) {
            r = (Item_GetFurnitureIndex(key) == Item_GetFurnitureIndex(p)) ? TRUE : z0;
        } else {
            r = (*key == *p) ? TRUE : z1;
        }
        if (r) {
            return i;
        }
    }
    return -1;
}
}

namespace nJ {
extern "C" BOOL Villager_RemoveReceivedItem(VillagerData *self, u16 *key) {
    s32 idx = Villager_FindReceivedItem(self, key);
    if (idx != -1) {
        self->receivedItems[idx] = 0xfff1;
        Villager_CompactReceivedItems(self);
        VillagerSync_Items(self, Villager_GetReceivedItem(self, 0));
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" void Villager_PickRandomReceivedItem(u16 *out, VillagerData *self) {
    u16 *p;
    s32 cnt;
    s32 i;
    *out = 0xfff1;
    p = Villager_GetReceivedItem(self, 0);
    cnt = 0;
    for (i = 0; i < 4; i++) {
        if (p[i] != 0xfff1) {
            cnt++;
        }
    }
    if (cnt > 0) {
        cnt = Random_GlobalBelow(cnt);
        for (i = 0; i < 4; p++, i++) {
            if (*p != 0xfff1) {
                if (cnt == 0) {
                    *out = *p;
                    break;
                }
                cnt--;
            }
        }
    }
}
}

namespace nJ {
extern "C" void Villager_GetMostValuableReceivedItem(u16 *out, VillagerData *self) {
    u16 *p;
    s32 best;
    s32 i;
    *out = 0xfff1;
    p = Villager_GetReceivedItem(self, 0);
    best = 0;
    for (i = 0; i < 4; p++, i++) {
        if (*p != 0xfff1) {
            s32 r = Item_GetPrice(p);
            if (r >= best) {
                *out = *p;
                best = r;
            }
        }
    }
}
}

namespace nJ {
extern "C" BOOL Villager_HasFlea(VillagerData *self) {
    s32 a = VillagerStates_Get()->fleaVillager;
    s32 b = SaveVillagers_FindIndex(gSaveVillagers, ((VillagerData *)(void *)(self))->getVillagerId());
    if (((VillagerId *)(void *)(((VillagerData *)(void *)(self))->getVillagerId()))->isValid() && a != -1 && b == a) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" void Villager_RemoveFlea(VillagerData *self) {
    if (Villager_HasFlea(self)) {
        VillagerStates_Get()->fleaVillager = -1;
    }
}
}

namespace nJ {
extern "C" BOOL Villager_IsGreeter(VillagerData *self) {
    s32 a = VillagerStates_Get()->greeter;
    s32 b = SaveVillagers_FindIndex(gSaveVillagers, ((VillagerData *)(void *)(self))->getVillagerId());
    if (((VillagerId *)(void *)(((VillagerData *)(void *)(self))->getVillagerId()))->isValid() && b == a) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nJ {
extern "C" u32 Villager_GetFurnitureTasteIndex(VillagerData *self) {
    return self->furnitureTasteIndex;
}
}

namespace nJ {
extern "C" void Villager_NextFurnitureTaste(VillagerData *self) {
    self->furnitureTasteIndex++;
    if (self->furnitureTasteIndex >= 6) {
        self->furnitureTasteIndex = 0;
    }
}
}

namespace nJ {
extern "C" BOOL Villager_IsFreeOfPlayerErrands(VillagerData *a) {
    u8 *g = gSavePlayers;
    s32 i;
    for (i = 0; i < 4; i++) {
        PlayerData *t = (PlayerData *)PlayerData_GetResident(g, i);
        if (((PlayerId *)t->getPlayerId())->isValid()) {
            if (Villager_IsInPlayerErrand(a, t->getErrands())) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
}

namespace nI {
extern "C" void Villager_StartMovingOut(VillagerData *a, void *b) {
    if (((VillagerId *)(((VillagerData *)(a))->getVillagerId()))->isValid()) {
        VillagerPlan *r4 = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
        if (r4->getState() == 2 || (r4->getState() == 8 && r4->hasState2Flag() != 0)) {
            r4->flags.state2Flag = 1;
        }
        r4->setState(9);
        MI_CpuCopy8(b, VillagerPlan_GetPlanTime(r4), 8);
        PlanErrand_Clear(VillagerPlanBlock_GetErrand(Villager_GetPlan(a)));
    }
}
}

namespace nI {
extern "C" void Villager_StartMovingIn(VillagerData *a, void *b) {
    if (((VillagerId *)(((VillagerData *)(a))->getVillagerId()))->isValid()) {
        VillagerPlan *r6 = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
        r6->setState(10);
        MI_CpuCopy8(b, VillagerPlan_GetPlanTime(r6), 8);
        PlanErrand_Clear(VillagerPlanBlock_GetErrand(Villager_GetPlan(a)));
    }
}
}

namespace nI {
extern "C" s32 Villager_IsMoveTimeReached(VillagerData *a, ClockDateTime *b) {
    VillagerId *r5 = a->getVillagerId();
    VillagerPlan *plan = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
    if (r5->isValid() && plan->isValidState()) {
        const u8 *r5b = Personality_GetSleepHours(VillagerId_GetPersonality(r5));
        ClockDateTime *r4 = VillagerPlan_GetPlanTime(plan);
        if (DateTime_IsInvalid(&r4->second) == 0) {
            ClockDateTimeWords tmpw;
            tmpw.words[0] = 0;
            tmpw.words[1] = 0;
            MI_CpuCopy8(r4, &tmpw, 8);
            tmpw.dt.hour = r5b[2];
            tmpw.dt.minute = r5b[3];
            if (r4->hour > r5b[2] || (r5b[2] == r4->hour && r5b[3] == r4->minute)) DateTime_AddDays(&tmpw.dt, 1);
            if (DateTime_Compare(b, &tmpw.dt, 0x3e) == 1) return TRUE;
            return FALSE;
        }
    }
    return FALSE;
}
}

namespace nI {
extern "C" void Villager_ShareTrendWith(VillagerData *a, VillagerData *b) {
    if (((VillagerId *)(((VillagerData *)(a))->getVillagerId()))->isValid() && ((VillagerId *)(((VillagerData *)(b))->getVillagerId()))->isValid()) {
        s16 *r6 = (s16 *)Villager_GetInfo3a((VillagerData *)a);
        if (r6) {
            VillagerPlan *r4 = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
            r4->addTrendOf(VillagerPlanBlock_GetPlan(Villager_GetPlan(b)), r6);
        }
    }
}
}

namespace nI {
extern "C" void Villager_RecordPlayerActivity(VillagerData *a, u32 kind, s32 v) {
    if (((VillagerData *)a)->getVillagerId()->isValid()) VillagerPlanBlock_GetPlan(Villager_GetPlan(a))->addPendingScore(kind, v);
}
}

namespace nI {
extern "C" void Villager_UpdateTrendDays(VillagerData *a, ClockDateTime *b) {
    VillagerPlan *r5 = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
    if (((VillagerData *)a)->getVillagerId()->isValid() && r5->isValidState() && ((VillagerPlan *)(void *)(r5))->hasTrend()) {
        ClockDateTime *r6 = VillagerPlan_GetStateDate(r5);
        s16 *r7 = (s16 *)Villager_GetInfo3a((VillagerData *)a);
        s32 r4;
        s32 cnt;
        ClockDateTimeWords tmp;
        if (DateTime_IsInvalid(&r6->second) == 0 && r7 != 0) {
            s32 d = DateTime_DiffMinutes(r6, b);
            if (d < 0) d = -d;
            cnt = d / 0x5a0;
            if (cnt > 0) {
                if (r5->isTrendOlderThanWeek(b)) {
                    tmp.words[0] = 0;
                    tmp.words[1] = 0;
                    r4 = cnt;
                    MI_CpuCopy8(VillagerPlan_GetPlanTime(r5), &tmp, 8);
                    d = DateTime_DiffMinutes(&tmp.dt, r6);
                    if (d < 0) d = -d;
                    if (d / 0x5a0 < 7) {
                        DateTime_AddDays(&tmp.dt, 6);
                        d = DateTime_DiffMinutes(&tmp.dt, b);
                        if (d < 0) d = -d;
                        r4 = d / 0x5a0;
                    }
                    for (; r4 > 0; ) {
                        if (r5->addRandomScores(r7) == 0) break;
                        r4--;
                    }
                    r5->applyPendingScores(r7);
                }
                DateTime_AddDays(r6, cnt);
            }
        }
    }
}
}

namespace nI {
extern "C" void Villager_InitPlanDateA(VillagerData *a, ClockDateTime *b) {
    VillagerPlan *plan = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
    if (((VillagerId *)(((VillagerData *)(a))->getVillagerId()))->isValid() && plan->isValidState()) {
        ClockDateTime *r4 = VillagerPlan_GetPlanTime(plan);
        if (DateTime_IsInvalid(&r4->second) != 0 || DateTime_Compare(b, r4, 0x3f) == -1) MI_CpuCopy8(b, r4, 8);
    }
}
}

namespace nI {
extern "C" void Villager_InitPlanDateB(VillagerData *a, ClockDateTime *b) {
    VillagerPlan *plan = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
    if (((VillagerId *)(((VillagerData *)(a))->getVillagerId()))->isValid() && plan->isValidState()) {
        ClockDateTime *r4 = VillagerPlan_GetStateDate(plan);
        if (DateTime_IsInvalid(&r4->second) != 0 || DateTime_Compare(b, r4, 0x3f) == -1) MI_CpuCopy8(b, r4, 8);
    }
}
}

namespace nI {
extern "C" s32 Villager_UpdatePlan(VillagerData *a, ClockDateTime *b) {
    VillagerId *r8 = ((VillagerData *)(a))->getVillagerId();
    void *r6 = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
    s32 r4 = 12;
    s32 r7 = ((VillagerPlan *)(void *)(r6))->getState();
    s32 t;
    if (((VillagerId *)(r8))->isValid() && ((VillagerPlan *)(void *)(r6))->isValidState()) {
        t = ((VillagerPlan *)(void *)(r6))->hasState2Flag();
        if (((VillagerPlan *)(void *)(r6))->getState() == 8) {
            if (Villager_IsMoveTimeReached(a, b)) r4 = ((VillagerPlan *)(void *)(r6))->finishTrendChange();
        } else {
            Villager_UpdateTrendDays(a, b);
            r4 = ((VillagerPlan *)(void *)(r6))->updateTopTrend();
        }
        if (r4 != 12) {
            if (Trend_IsValid(r7) == 0 || r7 != r4) {
                PlanErrand_Clear(VillagerPlanBlock_GetErrand(Villager_GetPlan(a)));
                void *r6b = VillagerState_GetErrand(Villager_GetState(a));
                ((ErrandRecord *)(void *)(r6b))->clear();
                if (PlanState_GetGroup(r4) == 0) {
                    u16 v = 0xfff1;
                    ((ErrandRecord *)(void *)(r6b))->start(r4, &v, 0);
                }
                if (Trend_IsValid(r4)) Villager_PickRoomLayout((VillagerData *)a, r4, t);
            }
        }
    }
    return r4;
}
}

namespace nI {
extern "C" s32 Villager_UpdatePlanState(VillagerData *a, void *b, void *c, ClockDateTime *d) {
    VillagerData *r6 = a;
    ClockDateTime *r5 = d;
    VillagerId *r8 = ((VillagerData *)(a))->getVillagerId();
    void *r7 = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
    s32 r4 = 12;
    s32 t = ((VillagerPlan *)(void *)(r7))->hasState2Flag();
    if (((VillagerId *)(r8))->isValid() && ((VillagerPlan *)(void *)(r7))->isValidState()) {
        switch (((VillagerPlan *)(void *)(r7))->getState()) {
        case 11:
            r4 = ((VillagerPlan *)(void *)(r7))->leaveState0B((VillagerPlan *)r5);
            if (r4 != 12) Villager_PickRoomLayout((VillagerData *)r6, r4, t);
            if (r4 != 12) {
                MI_CpuCopy8(r5, b, 8);
                if (*(long long *)c != 0) MI_CpuCopy8(r5, c, 8);
            }
            break;
        case 10:
            r4 = ((VillagerPlan *)(void *)(r7))->finishMovingIn(r5);
            if (r4 != 12) Villager_PickRoomLayout((VillagerData *)r6, r4, t);
            break;
        default:
            r4 = Villager_UpdatePlan(r6, r5);
            break;
        }
    }
    return r4;
}
}

namespace nI {
extern "C" void Villager_UpdatePlanErrand(VillagerData *a) {
    if (((VillagerId *)(((VillagerData *)(a))->getVillagerId()))->isValid()) {
        void *r6 = Villager_GetPlan(a);
        PlanErrand *r7 = VillagerPlanBlock_GetErrand(r6);
        ErrandRecord *r4 = PlanErrand_GetRecord(r7);
        if (r4->isActive()) {
            if (r4->getClass() == 0) {
                if (r4->getStep() == 3) {
                    if (r4->getKind() == 4) Villager_NextFurnitureTaste(a);
                    PlanErrand_Clear(r7);
                    VillagerPlanBlock_GetPlan(r6)->startTrendChange();
                }
            }
        }
    }
}
}

namespace nI {
extern "C" s32 Villager_CanGoOutdoors(VillagerData *a) {
    u16 *r5 = (u16 *)((VillagerData *)(a))->getVillagerId();
    s32 r = FALSE;
    if (((VillagerId *)(r5))->isValid() && Villager_GetResidentStatus((VillagerData *)a) == 3) {
        u16 *r4 = (u16 *)((SickVillagerRecord *)(void *)((void *)SaveVillagers_GetUnk3830(gSaveVillagers)))->getVillagerId();
        if (r5[0] == r4[0] && memcmp(r5 + 1, r4 + 1, 8) == 0 && ((u8 *)r5)[0xb] == ((u8 *)r4)[0xb]) {
        } else {
            r = TRUE;
        }
    }
    return r;
}
}

namespace nI {
extern "C" void Villager_PickShownFurniture(VillagerData *p) {
    u16 *q = p->furniture;
    u32 mask = 0;
    s32 cnt = 0;
    s32 i;
    s32 n, t;
    p->shownFurnitureMask = 0;
    i = 0;
    do {
        if (Item_IsFurniture(q)) {
            mask |= 1 << i;
            mask = (u16)mask;
            cnt++;
        }
        q++;
        t = i + 1;
        i = t;
    } while (t < 10);
    n = cnt;
    if (n > 5) n = 5;
    if (n > 3) n = Random_GlobalBelow(n - 2) + 3;
    if (cnt > 0) {
        for (; n > 0; n--) {
            s32 r = Random_PickSetBit(mask, cnt, 10);
            if (r != -1) {
                p->shownFurnitureMask |= 1 << r;
                mask &= ~(1 << r);
                mask = (u16)mask;
                cnt--;
            }
        }
    }
}
}

namespace nI {
extern "C" s32 Villager_IsFurnitureShown(VillagerData *p, s32 n) {
    if (((VillagerDataItemView *)(p))->isValidFurnitureIndex(n)) {
        if ((p->shownFurnitureMask >> n) & 1) return TRUE;
    }
    return FALSE;
}
}

namespace nI {
extern "C" void Villager_HideFurniture(VillagerData *p, s32 n) {
    if (((VillagerDataItemView *)(p))->isValidFurnitureIndex(n)) p->shownFurnitureMask &= ~(1 << n);
}
}

namespace nI {
extern "C" void Villager_ClearTalkedToday(u8 *p) {
    s32 i;
    for (i = 0; i < 8; p += sizeof(VillagerMemory), i++) ((VillagerMemory *)(p))->clearTalkedToday();
}
}

namespace nI {
extern "C" s32 Villager_IsAsleep(VillagerData *a, ClockDateTime *b) {
    if (((VillagerId *)(((VillagerData *)(a))->getVillagerId()))->isValid()) {
        ClockDateTimeWords v;
        v.words[0] = 0;
        v.words[1] = 0;
        if (b == 0) {
            Clock_GetDateTime(&v.dt);
            b = &v.dt;
        }
        return Personality_IsAsleep(VillagerId_GetPersonality(((VillagerData *)(void *)(a))->getVillagerId()), b);
    }
    return 0;
}
}

namespace nI {
extern "C" void Villager_SetFleaMarketVisited(VillagerData *a, void *b) {
    void *m;
    if (((VillagerId *)(void *)(((VillagerData *)(void *)(a))->getVillagerId()))->isValid() && ((PlayerId *)(void *)(b))->isValid() && (m = Villager_FindMemory(a, b)) != 0) ((VillagerMemory *)(m))->setFleaMarketVisited();
}
}

namespace nI {
extern "C" s32 Villager_UpdateVisitorRecord(VillagerData *a, void *b) {
    if (((VillagerId *)(((VillagerData *)(a))->getVillagerId()))->isValid()) {
        TownId *tbl = &gSaveTownId;
        if (b == 0) b = PlayerData_GetCurrent();
        if (b != 0 && tbl != 0) {
            void *r6;
            if (((PlayerId *)(r6 = ((PlayerData *)(b))->getPlayerId()))->isValid() && ((TownId *)(r6))->getTownRelation() == 1) {
                r6 = Villager_FindMemory(a, r6);
                if (r6 != 0) {
                    b = ((PlayerData *)(b))->getForeignVillagerRecord();
                    return ((ForeignVillagerRecord *)b)->offer(a->getVillagerId(), ((VillagerMemory *)(r6))->getFriendship(), tbl);
                }
            }
        }
    }
    return 0;
}
}

namespace nI {
extern "C" s32 Villager_SendLetter4(void *a, u32 b, u32 c, void *d, VillagerId *e, u16 *f) {
    u8 buf[5];
    u32 v1, v2, v3, v4;
    if (((PlayerId *)(d))->isValid() && ((VillagerId *)(e))->isValid()) {
        Letter obj;
        buf[0] = LetterPaper_PickForPersonality(VillagerId_GetPersonality(e));
        v1 = b + Random_GlobalBelow(c);
        v2 = b + Random_GlobalBelow(c);
        v3 = b + Random_GlobalBelow(c);
        v4 = b + Random_GlobalBelow(c);
        ((VillagerId *)(e))->makeFileName(sVillagerLetter4Path, 0x28, (const char *)a);
        buf[1] = v1;
        buf[2] = v2;
        buf[3] = v3;
        buf[4] = v4;
        Letter_ComposeVillagerMailZ(&obj, &buf[1], &buf[2], &buf[3], &buf[4], sVillagerLetter4Path, buf, e, d, 1);
        if (f) {
            u32 v = *f;
            if (v != 0xfff1) ((LetterView *)(void *)&obj)->setPresent(v, 1);
        }
        if (LetterDelivery_QueueOutgoing(&obj, 0)) {
            return TRUE;
        }
    }
    return FALSE;
}
}

namespace nI {
extern "C" s32 Villager_SendLetter(void *a, u32 b, void *c, VillagerId *d, u16 *e) {
    u8 buf[2];
    if (((PlayerId *)(c))->isValid() && ((VillagerId *)(d))->isValid()) {
        Letter obj;
        buf[0] = LetterPaper_PickForPersonality(VillagerId_GetPersonality(d));
        ((VillagerId *)(d))->makeFileName(sVillagerLetterPath, 0x28, (const char *)a);
        buf[1] = b;
        Letter_ComposeVillagerMail(&obj, &buf[1], sVillagerLetterPath, buf, d, c, 1);
        if (e) {
            u32 v = *e;
            if (v != 0xfff1) ((LetterView *)(void *)&obj)->setPresent(v, 1);
        }
        if (LetterDelivery_QueueOutgoing(&obj, 0)) {
            return TRUE;
        }
    }
    return FALSE;
}
}

namespace nH {
extern "C" void Villager_InitTalkUrge(VillagerData *self, void *x) {
    void *m;
    if (((VillagerId *)(((VillagerData *)(self))->getVillagerId()))->isValid()) {
        VillagerState *q = Villager_GetState(self);
        q->talkUrge = 0;
        if (x == NULL) {
            x = PlayerData_GetCurrent();
        }
        if (x != NULL && (((PlayerData *)(void *)(x))->getPlayerId())->isValid() && !((PlayerData *)(void *)(x))->testFlag(1) && (m = (void *)Villager_FindMemory(self, ((PlayerData *)(void *)(x))->getPlayerId())) != 0) {
            s32 t = ((VillagerMemory *)(m))->getFriendship();
            s32 v = ((t + 0x100) >> 7) * (Random_GlobalBelow(10) + 1);
            if (v < 0) {
                v = 0;
            } else if (v > 0x20) {
                v = 0x20;
            }
            q->talkUrge = v;
        }
    }
}
}

namespace nH {
extern "C" BOOL Villager_CanSeekPlayer(VillagerData *self) {
    if (((VillagerId *)(((VillagerData *)(self))->getVillagerId()))->isValid()) {
        VillagerState *q = Villager_GetState(self);
        if (q != NULL) {
            if (!VillagerState_GetMood(q) || VillagerState_GetMood(q) == 1) {
                return TRUE;
            }
        }
    }
    return FALSE;
}
}

namespace nH {
extern "C" void Villager_RaiseTalkUrge(VillagerData *self, void *x) {
    void *m;
    if (((VillagerId *)(((VillagerData *)(self))->getVillagerId()))->isValid()) {
        s32 v = 0;
        if (x == NULL) {
            x = PlayerData_GetCurrent();
        }
        if (x != NULL && (((PlayerData *)(void *)(x))->getPlayerId())->isValid() && !((PlayerData *)(void *)(x))->testFlag(1) && Villager_CanSeekPlayer(self) && (m = (void *)Villager_FindMemory(self, ((PlayerData *)(void *)(x))->getPlayerId())) != 0) {
            s32 t = ((VillagerMemory *)(m))->getFriendship();
            s32 k = Random_GlobalBelow(3);
            v = ((t + 0x100) >> 7) * k;
        }
        Villager_AddTalkUrge(self, v);
    }
}
}

namespace nH {
extern "C" BOOL Villager_IsTalkUrgeFull(VillagerData *self, void *x) {
    BOOL r;
    BOOL ok;
    if (x == NULL) {
        x = PlayerData_GetCurrent();
    }
    r = FALSE;
    ok = FALSE;
    if (x != NULL && (((PlayerData *)(void *)(x))->getPlayerId())->isValid() && !((PlayerData *)(void *)(x))->testFlag(1) && (((VillagerData *)(void *)(self))->getVillagerId())->isValid() && Villager_GetState(self)->talkUrge == 0x20) {
        ok = TRUE;
    }
    if (ok && Villager_CanSeekPlayer(self)) {
        r = TRUE;
    }
    return r;
}
}

namespace nH {
extern "C" void Villager_ClearTalkUrge(VillagerData *self) {
    if (((VillagerId *)(((VillagerData *)(self))->getVillagerId()))->isValid()) {
        VillagerState *q = Villager_GetState(self);
        q->talkUrge = 0;
    }
}
}

namespace nH {
extern "C" void Villager_HalveTalkUrge(VillagerData *self) {
    if (((VillagerId *)(((VillagerData *)(self))->getVillagerId()))->isValid()) {
        VillagerState *q = Villager_GetState(self);
        q->talkUrge = q->talkUrge >> 1;
    }
}
}

namespace nH {
extern "C" void Villager_DoubleTalkUrge(VillagerData *self) {
    if (((VillagerId *)(((VillagerData *)(self))->getVillagerId()))->isValid()) {
        VillagerState_DoubleTalkUrge(Villager_GetState(self));
    }
}
}

namespace nH {
extern "C" void Villager_AddTalkUrge(VillagerData *self, s32 d) {
    if (((VillagerId *)(((VillagerData *)(self))->getVillagerId()))->isValid()) {
        VillagerState *q = Villager_GetState(self);
        s32 v = d + q->talkUrge;
        if (v < 0) {
            v = 0;
        } else if (v > 0x20) {
            v = 0x20;
        }
        q->talkUrge = v;
    }
}
}

namespace nH {
extern "C" SaveVillagers *SaveVillagers_Construct(SaveVillagers *self) {
    for (s32 i = 0; i < 8; i++) {
        new (&self->villagers[i]) VillagerData();
    }
    VillagerRelations_Construct();
    OutdoorSchedule_Construct(&self->outdoorSchedule);
    ((SickVillagerRecord *)self->sickVillager)->constructRecord();
    self->lastMoveDate.words[0] = 0;
    self->lastMoveDate.words[1] = 0;
    self->lastMoveOutDate.words[0] = 0;
    self->lastMoveOutDate.words[1] = 0;
    return self;
}
}

namespace nH {
extern "C" SaveVillagers *SaveVillagers_Destruct(SaveVillagers *self) {
    ((SickVillagerRecord *)self->sickVillager)->destructRecord();
    OutdoorSchedule_Destruct();
    VillagerRelations_Destruct();
    for (s32 i = 8 - 1; i >= 0; i--) {
        self->villagers[i].~VillagerData();
    }
    return self;
}
}

namespace nH {
extern "C" void SaveVillagers_Clear(SaveVillagers *self) {
    s32 i;
    for (i = 0; i < 8; i++) {
        self->villagers[i].clear();
    }
    VillagerRelations_Clear(self->relations);
    OutdoorSchedule_Clear(&self->outdoorSchedule);
    ((SickVillagerRecord *)self->sickVillager)->resetRecord();
    self->nicknameDate[0] = 1;
    self->nicknameDate[1] = 1;
    self->nicknameDate[2] = 0;
    self->nicknameDate[3] = 0;
    self->lastMoveDate.words[0] = 0;
    self->lastMoveDate.words[1] = 0;
    self->lastMoveOutDate.words[0] = 0;
    self->lastMoveOutDate.words[1] = 0;
    self->lastMovedInIndex = -1;
    self->lastMovedOutSpecies = -1;
    MI_CpuFill8(&self->tune, 0, 2);
    MI_CpuFill8(self->speciesHistory, 0, 0x14);
}
}

namespace nH {
extern "C" BOOL SaveVillagers_IsValidIndex(u32 n) {
    if (n < 8) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nH {
extern "C" s32 SaveVillagers_FindIndex(u8 *base, VillagerId *p) {
    s32 result = -1;
    if (p->isValid()) {
        s32 i;
        for (i = 0; i < 8; i++) {
            VillagerId *q = ((VillagerData *)(base + i * sizeof(VillagerData)))->getVillagerId();
            if (p->townId == q->townId && memcmp(p->townName, q->townName, 8) == 0 && p->species == q->species) {
                result = i;
                break;
            }
        }
    }
    return result;
}
}

namespace nH {
extern "C" BOOL SaveVillagers_IsOccupied(u8 *base, s32 idx) {
    BOOL r = FALSE;
    if (SaveVillagers_IsValidIndex(idx)) {
        r = ((VillagerId *)(((VillagerData *)(base + idx * sizeof(VillagerData)))->getVillagerId()))->isValid();
    }
    return r;
}
}

namespace nH {
extern "C" VillagerData *SaveVillagers_Get(void *base, s32 idx) {
    VillagerData *r = NULL;
    if (SaveVillagers_IsValidIndex(idx)) {
        r = &((SaveVillagers *)base)->villagers[idx];
    }
    return r;
}
}

namespace nH {
extern "C" u8 *SaveVillagers_Find(u8 *base, VillagerId *x) {
    u8 *r = NULL;
    s32 idx = SaveVillagers_FindIndex(base, x);
    if (SaveVillagers_IsValidIndex(idx)) {
        r = base + idx * sizeof(VillagerData);
    }
    return r;
}
}

namespace nH {
extern "C" s32 Text_TrimmedLength(u8 *s, s32 n) {
    s += n - 1;
    for (; n > 0; n--, s--) {
        if (*s != 0 && *s != 0x85) {
            return n;
        }
    }
    return 0;
}
}

namespace nH {
extern "C" BOOL Mem_Equal(u8 *a, u8 *b, s32 n) {
    s32 i;
    for (i = 0; i < n; i++, a++, b++) {
        if (*a != *b) {
            return FALSE;
        }
    }
    return TRUE;
}
}

namespace nH {
extern "C" u8 *SaveVillagers_FindByName(u8 *base, u8 *a1, s32 a2, void *a3) {
    u8 *result;
    u8 *p;
    s32 n;
    s32 i;
    void *t;
    p = (u8 *)SaveVillagers_Get(base, 0);
    MsgString9B objA;
    EncodedString8 objB;
    result = NULL;
    n = Text_TrimmedLength(a1, a2);
    if (n > 0 && n <= 8) {
        for (i = 0; i < 8; i++) {
            if (((VillagerId *)(void *)(((VillagerData *)(void *)(p))->getVillagerId()))->isValid() && (a3 == NULL || Villager_FindMemory(p, a3))) {
                objA.clear();
                ((VillagerId *)(((VillagerData *)(p))->getVillagerId()))->getName(&objA);
                objB.fromMsgString(&objA);
                t = ((EncodedStringBase *)&objB)->data();
                {
                    s32 m = Text_TrimmedLength((u8 *)t, objB.EncodedString8::capacity());
                    if (m == n && Mem_Equal((u8 *)t, a1, m)) {
                        result = p;
                        break;
                    }
                }
            }
            p += sizeof(VillagerData);
        }
    }
    return result;
}
}

namespace nH {
extern "C" void *SaveVillagers_GetByHouseRoom(void *self, u32 x) {
    void *r = NULL;
    u32 c = (u8)x;
    if (SceneId_IsVillagerHouse(c)) {
        s32 t = SceneId_GetVillagerHouse(c);
        if (SaveVillagers_IsValidIndex(t)) {
            r = SaveVillagers_Get((u8 *)self, t);
        }
    }
    return r;
}
}

namespace nH {
extern "C" s32 SaveVillagers_FindFreeSlot(void *self) {
    return ((VillagerData *)(self))->findFreeSlot(8);
}
}

namespace nH {
extern "C" void *SaveVillagers_PickRandomExcept(u8 *base, void **arr, s32 n) {
    s32 cnt = 0;
    u8 *result = NULL;
    volatile s32 zero;
    u8 flags[8];
    s32 i;
    s32 j;
    s32 idx;
    MI_CpuFill8(flags, 0, 8);
    for (i = 0; i < 8; i++) {
        if (SaveVillagers_IsOccupied(base, i)) {
            flags[i] = 1;
            cnt++;
        }
    }
    zero = 0;
    for (j = 0; j < n; j++) {
        void **q = arr + j;
        if (*q != NULL) {
            idx = SaveVillagers_FindIndex(base, (VillagerId *)*q);
            if (SaveVillagers_IsValidIndex(idx)) {
                flags[idx] = zero;
                if (((VillagerId *)(*q))->isValid()) {
                    cnt--;
                }
            }
        }
    }
    if (cnt > 0) {
        s32 k = Random_GlobalBelow(cnt);
        for (i = 0; i < 8; i++) {
            if (flags[i] == 1) {
                if (k == 0) {
                    result = base + i * sizeof(VillagerData);
                    break;
                }
                k--;
            }
        }
    }
    return result;
}
}

namespace nH {
extern "C" s32 Random_PickSetBit(u32 mask, s32 cnt, s32 n) {
    if (cnt > 0) {
        s32 k = Random_GlobalBelow(cnt);
        s32 i;
        for (i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                if (k == 0) {
                    return i;
                }
                k--;
            }
        }
    }
    return -1;
}
}

namespace nH {
extern "C" void *SaveVillagers_PickRandomTalkPartner(u8 *base, void **arr, s32 n) {
    u8 mask = 0;
    s32 idx;
    s32 i;
    u8 m2;
    s32 cnt;
    u8 *p;
    for (i = 0; i < n; arr++, i++) {
        if (*arr != NULL) {
            idx = SaveVillagers_FindIndex(base, (VillagerId *)*arr);
            if (SaveVillagers_IsValidIndex(idx)) {
                mask |= 1 << idx;
            }
        }
    }
    idx = (s32)SaveVillagers_GetUnk3830Index(base);
    if (SaveVillagers_IsValidIndex(idx)) {
        mask |= 1 << idx;
    }
    p = base;
    m2 = 0;
    cnt = 0;
    for (i = 0; i < 8; i++) {
        VillagerId *r = ((VillagerData *)(p))->getVillagerId();
        if (((mask >> i) & 1) == 0 && ((VillagerId *)(r))->isValid() && Villager_CanBeTalkPartner((VillagerData *)p)) {
            m2 |= 1 << i;
            cnt++;
        }
        p += sizeof(VillagerData);
    }
    return SaveVillagers_Get(base, Random_PickSetBit(m2, cnt, 8));
}
}

namespace nH {
extern "C" void *SaveVillagers_FindBestFriendOf(u8 *base, void *x) {
    void *m;
    u8 *best = NULL;
    s32 bestv;
    s32 i;
    u8 *p;
    if (((PlayerId *)(x))->isValid()) {
        p = base;
        bestv = -128;
        for (i = 0; i < 8; i++) {
            if (((VillagerId *)(void *)(((VillagerData *)(void *)(p))->getVillagerId()))->isValid() && (m = (void *)Villager_FindMemory(p, x)) != 0) {
                s32 v = ((VillagerMemory *)(m))->getFriendship();
                if (best == NULL) {
                    best = p;
                    bestv = v;
                } else if (v > bestv) {
                    best = p;
                    bestv = v;
                } else if (v == bestv) {
                    if (Random_GlobalBelow(10) & 1) {
                        best = p;
                    }
                }
            }
            p += sizeof(VillagerData);
        }
    }
    if (best == NULL) {
        best = (u8 *)SaveVillagers_PickRandomExcept(base, 0, 0);
    }
    return best;
}
}

namespace nH {
extern "C" s32 SaveVillagers_CountImpl(u8 *base) {
    s32 cnt = 0;
    s32 i;
    for (i = 0; i < 8; i++) {
        if (((VillagerId *)(((VillagerData *)(base))->getVillagerId()))->isValid()) {
            cnt++;
        }
        base += sizeof(VillagerData);
    }
    return cnt;
}
}

namespace nH {
extern "C" s32 SaveVillagers_Count(u8 *base) {
    return SaveVillagers_CountImpl(base);
}
}

namespace nH {
extern "C" BOOL SpeciesBits_Test(s32 n, u32 *bits) {
    if (VillagerId_IsValidSpecies(n)) {
        if ((bits[n >> 5] >> (n & 0x1f)) & 1) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}
}

namespace nH {
extern "C" void SpeciesBits_Set(u32 *bits, s32 n) {
    if (VillagerId_IsValidSpecies(n)) {
        bits[n >> 5] |= 1 << (n & 0x1f);
    }
}
}

namespace nH {
extern "C" void SpeciesBits_Clear(SaveVillagers *unused, u32 *bits, s32 n) {
    if (VillagerId_IsValidSpecies(n)) {
        bits[n >> 5] &= ~(1 << (n & 0x1f));
    }
}
}

namespace nH {
extern "C" BOOL SpeciesBits_AllEligibleSet(u32 *bits) {
    s32 i;
    for (i = 0; i < 150; i++) {
        u8 *p = (u8 *)VillagerInfo_Get((u8)i);
        if (p != NULL && p[0x4b] < 2) {
            if (!SpeciesBits_Test((u8)i, bits)) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
}

namespace nG {
extern "C" void SaveVillagers_UpdateHistory(u32 *bits, SaveVillagers *p0) {
    VillagerData *p = (VillagerData *)p0;
    s32 i;
    if (SpeciesBits_AllEligibleSet(bits) != 0) {
        MI_CpuFill8(bits, 0, 0x14);
        for (i = 0; i < 8; p++, i++) {
            VillagerId *o = p->getVillagerId();
            if (o->isValid() != 0) {
                SpeciesBits_Set(bits, VillagerId_GetSpecies(o));
            }
        }
    }
}
}

namespace nG {
extern "C" s32 SaveVillagers_PickNewSpecies(SaveVillagers *self, u32 idx, s32 flag) {
    s32 cnt = 0;
    u32 *bits = self->speciesHistory;
    s32 i;
    VillagerData *p;
    MI_CpuFill8(sSpeciesCandidateBits, 0, 0x14);
    for (i = 0; i < 0x96; i++) {
        if (SpeciesBits_Test(i, bits) == 0) {
            u8 *e = (u8 *)VillagerInfo_Get(i);
            u32 b = e[0x4b];
            if (b < 2) {
                if (flag == 0 || b == 0) {
                    if (e[0x4a] == idx) {
                        SpeciesBits_Set(sSpeciesCandidateBits, i);
                        cnt++;
                    }
                }
            }
        }
    }
    if (cnt > 0) {
        s32 k;
        p = self->villagers;
        for (k = 0; k < 8; p++, k++) {
            VillagerId *o = p->getVillagerId();
            if (o->isValid() != 0) {
                u8 id = VillagerId_GetSpecies(o);
                if (SpeciesBits_Test(id, sSpeciesCandidateBits) != 0) {
                    SpeciesBits_Clear(self, sSpeciesCandidateBits, id);
                    cnt--;
                    if (cnt == 0) {
                        break;
                    }
                }
            }
        }
    }
    if (cnt > 0) {
        s32 r = Random_GlobalBelow(cnt);
        for (i = 0; i < 0x96; i++) {
            if (SpeciesBits_Test(i, sSpeciesCandidateBits) != 0) {
                if (r == 0) {
                    return i;
                }
                r--;
            }
        }
    }
    return -1;
}
}

namespace nG {
extern "C" u32 SaveVillagers_PickRarePersonality(SaveVillagers *self, s32 mask) {
    VillagerData *p = self->villagers;
    u8 counts[6];
    u8 best = 0;
    s32 n = 0;
    s32 bc = 9;
    s32 i;
    s32 j;
    u32 r;
    MI_CpuFill8(counts, 0, 6);
    for (i = 0; i < 8; p++, i++) {
        VillagerId *o = ((VillagerData *)(p))->getVillagerId();
        if (((VillagerId *)o)->isValid() != 0) {
            if (VillagerId_GetPersonality(o) < 6) {
                u32 t = VillagerId_GetPersonality(o);
                counts[t] = counts[t] + 1;
            }
        }
    }
    for (j = 0; j < 6; j++) {
        if (((mask >> j) & 1) == 0) {
            s32 c = counts[j];
            if (c < bc) {
                best = 1 << j;
                n = 1;
                bc = c;
            } else if (c == bc) {
                best = best | (1 << j);
                n++;
            }
        }
    }
    r = Random_PickSetBit(best, n, 6);
    return r < 6 ? (u8)r : 0;
}
}

namespace nG {
extern "C" void SaveVillagers_InitNewTown(SaveVillagers *self) {
    u8 mask = 0;
    s32 i;
    struct {
        u32 v[2];
    } z;
    SaveVillagers_Clear(self);
    for (i = 0; i < 3; i++) {
        u32 v = SaveVillagers_PickRarePersonality(self, mask);
        if (v < 6) {
            s32 t = SaveVillagers_PickNewSpecies(self, v, 1);
            if (t != -1) {
                self->villagers[i].setup((u8)t, 0, 0, 1);
                SpeciesBits_Set(self->speciesHistory, (u8)t);
                mask = mask | (1 << v);
            }
        }
    }
    Clock_GetDateTime(&self->lastMoveDate.dt);
    OutdoorSchedule_InitOrder(self->outdoorSchedule.order, (u8 *)self);
    Clock_GetDate(self->furnitureDropDate);
    self->lastSickIndex = -1;
}
}

namespace nG {
extern "C" void SaveVillagers_UpdateOutdoor(SaveVillagers *self, s32 x) {
    OutdoorSchedule_Update(&self->outdoorSchedule, (u8 *)self, x);
}
}

namespace nG {
extern "C" s32 SaveVillagers_IsOutdoors(SaveVillagers *self, VillagerId *o) {
    s32 t = OutdoorSchedule_FindOutdoorSlot(&self->outdoorSchedule, SaveVillagers_FindIndex((u8 *)self, o));
    s32 r = 0;
    if (t != -1) {
        r = 1;
    }
    return r;
}
}

namespace nG {
extern "C" void SaveVillagers_UpdatePlans(SaveVillagers *self) {
    ClockDateTimeWords buf;
    VillagerData *p = self->villagers;
    s32 i;
    buf.words[0] = 0;
    buf.words[1] = 0;
    Clock_GetDateTime(&buf.dt);
    for (i = 0; i < 8; p++, i++) {
        VillagerId *o = ((VillagerData *)(p))->getVillagerId();
        if (((VillagerId *)o)->isValid() != 0) {
            VillagerState *q = Villager_GetState(p);
            if (VillagerState_GetPresence(q) == 2 && VillagerState_GetRole(q) == 0 && OutdoorSchedule_FindOutdoorSlot(&self->outdoorSchedule, i) == -1
                && Personality_IsAsleep(VillagerId_GetPersonality(o), &buf.dt) == 0) {
                VillagerState_SetPresence(q, 1);
            }
        }
    }
}
}

namespace nG {
extern "C" s32 SaveVillagers_CanMoveIn(SaveVillagers *self, ClockDateTime *p) {
    if (SaveVillagers_Count((u8 *)self) < 8) {
        if (*(s64 *)&self->lastMoveOutDate == 0) {
            if (*(s64 *)&self->lastMoveDate == 0 || DateTime_IsInvalid(&self->lastMoveDate.dt.second) != 0) {
                return TRUE;
            }
            if (DateTime_Compare(p, &self->lastMoveDate.dt, 0x3f) == 1) {
                if (DateTime_DiffDays(&self->lastMoveDate.dt, p) >= 1) {
                    return TRUE;
                }
            }
        } else {
            if (DateTime_Compare(p, &self->lastMoveOutDate.dt, 0x3f) == 1) {
                s32 n = DateTime_DiffDays(&self->lastMoveOutDate.dt, p);
                if (n > 0) {
                    BOOL t;
                    if (n >= 8) {
                        t = TRUE;
                    } else if (Random_GlobalBelow(8 - n) == 0) {
                        t = TRUE;
                    } else {
                        t = FALSE;
                    }
                    if (t != 0) {
                        return TRUE;
                    }
                    return FALSE;
                }
            }
        }
    }
    return FALSE;
}
}

namespace nG {
extern "C" s32 SaveVillagers_PickMoveInSpecies(SaveVillagers *self) {
    u8 mask = 0;
    s32 i = 0;
    for (; i < 6; i++) {
        u32 v = SaveVillagers_PickRarePersonality(self, mask);
        s32 t;
        if (v >= 6) {
            break;
        }
        t = SaveVillagers_PickNewSpecies(self, v, 0);
        if (t != -1) {
            return t;
        }
        mask = mask | (1 << v);
    }
    return -1;
}
}

namespace nG {
extern "C" void SaveVillagers_TryRandomMoveIn(SaveVillagers *self, ClockDateTime *out) {
    if (SaveVillagers_CanMoveIn(self, out) != 0) {
        s32 x = SaveVillagers_FindFreeSlot(self);
        VillagerData *r7 = SaveVillagers_Get(self, x);
        if (r7 != 0) {
            s32 idx;
            ((VillagerData *)(r7))->clear();
            SaveVillagers_UpdateHistory(self->speciesHistory, self);
            idx = SaveVillagers_PickMoveInSpecies(self);
            if (idx != -1) {
                sTransferVillager.clear();
                sTransferVillager.setup((u8)idx, 1, 0, 0);
                SaveVillagers_MoveIn(self, r7, x, &sTransferVillager, 1, out);
            }
        }
        MI_CpuCopy8(out, &self->lastMoveDate, 8);
        if (*(s64 *)&self->lastMoveOutDate != 0) {
            MI_CpuCopy8(out, &self->lastMoveOutDate, 8);
        }
    }
}
}

namespace nG {
extern "C" void *SaveVillagers_FindBySpecies(SaveVillagers *self, u32 id) {
    VillagerData *p = self->villagers;
    s32 i;
    for (i = 0; i < 8; p++, i++) {
        VillagerId *o = (VillagerId *)((VillagerData *)(p))->getVillagerId();
        if (o->isValid() != 0 && id == VillagerId_GetSpecies(o)) {
            return p;
        }
    }
    return 0;
}
}

namespace nG {
extern "C" void SaveVillagers_SetLastMovedIn(SaveVillagers *self, s8 v) {
    self->lastMovedInIndex = v;
}
}

namespace nG {
extern "C" void SaveVillagers_SetLastMovedInById(SaveVillagers *self, VillagerId *o) {
    if (o->isValid() != 0) {
        s32 i = SaveVillagers_FindIndex((u8 *)self, o);
        if (SaveVillagers_IsValidIndex(i) != 0) {
            SaveVillagers_SetLastMovedIn(self, (s8)i);
        }
    }
}
}

namespace nG {
extern "C" void SaveVillagers_MoveIn(SaveVillagers *self, VillagerData *a, s32 idx, VillagerData *b, u8 c, ClockDateTime *out) {
    SaveVillagers_RefreshPlanStates(self);
    ((VillagerData *)(a))->copyFrom(b);
    Villager_StartMovingIn(a, out);
    ((VillagerDataItemView *)(a))->clearHousePos();
    Villager_SetMoveInKind(a, c);
    Villager_PickShownFurniture(a);
    OutdoorSchedule_AddToOrder(self->outdoorSchedule.order, idx);
    VillagerRelations_ResetSlot(self->relations, idx);
    SpeciesBits_Set(self->speciesHistory, VillagerId_GetSpecies(((VillagerData *)(a))->getVillagerId()));
    MI_CpuCopy8(out, &self->lastMoveDate, 8);
    if (*(s64 *)&self->lastMoveOutDate != 0) {
        MI_CpuCopy8(out, &self->lastMoveOutDate, 8);
    }
    SaveVillagers_SetLastMovedIn(self, (s8)idx);
}
}

namespace nG {
extern "C" void SaveVillagers_MoveOut(SaveVillagers *self, VillagerData *a, VillagerData *b, s32 idx, ClockDateTime *out) {
    ((VillagerDataItemView *)(b))->placeHouseMarker();
    ((VillagerDataItemView *)(b))->clearHousePos();
    TownId_Assign(((VillagerDataItemView *)(b))->getMovedFromTownId(), &gSaveTownId);
    self->lastMovedOutSpecies = VillagerId_GetSpecies(((VillagerData *)(b))->getVillagerId());
    OutdoorSchedule_Remove(&self->outdoorSchedule, idx);
    VillagerRelations_ResetSlot(self->relations, idx);
    if (a != 0) {
        ((VillagerData *)(a))->copyFrom(b);
    }
    ((VillagerData *)(b))->clear();
    MI_CpuCopy8(out, &self->lastMoveOutDate, 8);
}
}

namespace nG {
extern "C" void SaveVillagers_ProcessTransfer(SaveVillagers *self, ClockDateTime *arg) {
    VillagerData *r7;
    s32 idx;
    VillagerData *r4;

    r7 = (VillagerData *)func_020789a8(((TownExchangeRecord *)(data_021e7f8c))->getVillager());
    idx = SaveVillagers_FindMovingOutDue(self, arg);
    r4 = SaveVillagers_Get(self, idx);
    if (((VillagerId *)((VillagerData *)(r7))->getVillagerId())->isValid() == 0) {
        goto nomatch;
    }
    if (TownId_IsValid(&r7->movedFromTown.townId) == 0) {
        goto nomatch;
    }
    {
        TownId *g = &gSaveTownId;
        TownId *h = &r7->movedFromTown;
        if (h->townId == g->townId && memcmp(h->townName, g->townName, 8) == 0) {
            if (r4 == 0) {
                return;
            }
            ((VillagerData *)(r4))->updateMemoriesFromPlayers();
            if (Villager_IsMoreAttachedThan(r7, r4, arg) == 0) {
                SaveVillagers_MoveOut(self, r7, r4, idx, arg);
            } else {
                SaveVillagers_MoveOut(self, 0, r4, idx, arg);
            }
            return;
        }
    }
    if (SaveVillagers_FindBySpecies(self, VillagerId_GetSpecies(((VillagerData *)(r7))->getVillagerId())) == 0
        && self->lastMovedOutSpecies != VillagerId_GetSpecies(((VillagerData *)(r7))->getVillagerId())) {
        if (r4 == 0) {
            s32 x = SaveVillagers_FindFreeSlot(self);
            if (SaveVillagers_IsValidIndex(x) == 0) {
                return;
            }
            SaveVillagers_MoveIn(self, SaveVillagers_Get(self, x), x, r7, 2, arg);
            ((VillagerData *)(r7))->clear();
            return;
        }
        sTransferVillager.clear();
        sTransferVillager.copyFrom(r7);
        ((VillagerData *)(r4))->updateMemoriesFromPlayers();
        SaveVillagers_MoveOut(self, r7, r4, idx, arg);
        SaveVillagers_MoveIn(self, r4, idx, &sTransferVillager, 2, arg);
        return;
    }
    if (r4 == 0) {
        return;
    }
    ((VillagerData *)(r4))->updateMemoriesFromPlayers();
    if (Villager_IsMoreAttachedThan(r7, r4, arg) == 0) {
        SaveVillagers_MoveOut(self, r7, r4, idx, arg);
    } else {
        SaveVillagers_MoveOut(self, 0, r4, idx, arg);
    }
    return;
nomatch:
    if (r4 != 0) {
        ((VillagerData *)(r4))->updateMemoriesFromPlayers();
        SaveVillagers_MoveOut(self, r7, r4, idx, arg);
    }
}
}

namespace nG {
extern "C" s32 SaveVillagers_FindMovingOut(SaveVillagers *self) {
    VillagerData *p = self->villagers;
    s32 i;
    for (i = 0; i < 8; p++, i++) {
        if (Villager_IsMovingOut(p) != 0) {
            return i;
        }
    }
    return -1;
}
}

namespace nG {
extern "C" s32 SaveVillagers_FindMovingOutDue(SaveVillagers *self, ClockDateTime *name) {
    s32 idx = SaveVillagers_FindMovingOut(self);
    VillagerData *v = SaveVillagers_Get(self, idx);
    if (v != 0) {
        VillagerPlan *q = VillagerPlanBlock_GetPlan(Villager_GetPlan(v));
        s32 r = DateTime_Compare(name, VillagerPlan_GetPlanTime(q), 0x3f);
        s32 n = 0;
        if (r == 1) {
            n = DateTime_DiffDays(VillagerPlan_GetPlanTime(q), name);
        } else if (r == -1) {
            n = DateTime_DiffDays(name, VillagerPlan_GetPlanTime(q));
        }
        if (n >= 2) {
            return idx;
        }
    }
    return -1;
}
}

namespace nG {
extern "C" s32 SaveVillagers_FindJustMovedIn(VillagerData *p) {
    s32 i;
    for (i = 0; i < 8; p++, i++) {
        if (Villager_IsJustMovedIn(p) != 0) {
            return i;
        }
    }
    return -1;
}
}

namespace nF {
extern "C" BOOL SaveVillagers_ShouldStartMoveOut(SaveVillagers *self, ClockDateTime *x) {
    if (SaveVillagers_Count((u8 *)self) == 8) {
        s32 r6 = SaveVillagers_FindMovingOut(self);
        s32 r0 = SaveVillagers_FindJustMovedIn(self->villagers);
        if (r6 == -1 && r0 == -1) {
            if (DateTime_Compare(x, &self->lastMoveDate.dt, 0x3f) == 1) {
                s32 n = DateTime_DiffDays(&self->lastMoveDate.dt, x);
                if (n > 0) {
                    BOOL t;
                    if (n >= 4) {
                        t = TRUE;
                    } else if (Random_GlobalBelow(4 - n) == 0) {
                        t = TRUE;
                    } else {
                        t = FALSE;
                    }
                    if (t) {
                        return TRUE;
                    }
                    return FALSE;
                }
            }
        }
    }
    return FALSE;
}
}

namespace nF {
extern "C" s32 SaveVillagers_PickMoveOutCandidate(SaveVillagers *self) {
    VillagerData *p = self->villagers;
    s32 sp4 = SaveVillagers_GetUnk3830Index(self);
    u32 mask = 0;
    s32 cnt = 0;
    s32 r4 = 0;
    for (; r4 < 8; r4++) {
        if (r4 != self->lastMovedInIndex && r4 != sp4 && p->getVillagerId()->isValid() && Villager_IsFreeOfPlayerErrands(p)) {
            mask |= 1 << r4;
            mask = (u8)mask;
            cnt++;
        }
        p++;
    }
    return Random_PickSetBit(mask, cnt, 8);
}
}

namespace nF {
extern "C" void SaveVillagers_TryStartMoveOut(SaveVillagers *self, ClockDateTime *x) {
    if (SaveVillagers_ShouldStartMoveOut(self, x)) {
        s32 r = SaveVillagers_PickMoveOutCandidate(self);
        if (r != -1) {
            Villager_StartMovingOut(&self->villagers[r], x);
        }
    }
}
}

namespace nF {
extern "C" void SaveVillagers_UpdatePlanStates(SaveVillagers *self, ClockDateTimeRaw *x) {
    VillagerData *p = self->villagers;
    s32 i = 0;
    do {
        if (p->getVillagerId()->isValid()) {
            Villager_InitPlanDateA(p, &x->dt);
            Villager_InitPlanDateB(p, &x->dt);
            if (Villager_UpdatePlanState(p, &self->lastMoveDate, &self->lastMoveOutDate, &x->dt) != 0xc) {
                PlanErrand_Clear(VillagerPlanBlock_GetErrand(Villager_GetPlan(p)));
            }
        }
        p++;
        i++;
    } while (i < 8);
}
}

namespace nF {
extern "C" void SaveVillagers_RefreshPlanStates(SaveVillagers *self) {
    VillagerData *p = self->villagers;
    s32 i = 0;
    do {
        if (p->getVillagerId()->isValid()) {
            VillagerPlan *r6 = VillagerPlanBlock_GetPlan(Villager_GetPlan(p));
            BOOL r7 = r6->hasState2Flag();
            s32 r1 = r6->finishMovingIn(NULL);
            if (r1 != 0xc) {
                Villager_PickRoomLayout(p, r1, r7);
            }
        }
        p++;
        i++;
    } while (i < 8);
}
}

namespace nF {
extern "C" void SaveVillagers_UpdatePlansNow(SaveVillagers *self) {
    if (!gCommManager->isSlotActive(gCommManager->myAid)) {
        ClockDateTimeRaw b;
        b.v[0] = 0;
        b.v[1] = 0;
        Clock_GetDateTime(&b.dt);
        s32 i = 0;
        VillagerData *p = self->villagers;
        ClockDateTimeRaw *pb = &b;
        for (; i < 8; i++) {
            if (p->getVillagerId()->isValid()) {
                Villager_UpdatePlan(p, &pb->dt);
            }
            p++;
        }
    }
}
}

namespace nF {
extern "C" void SaveVillagers_DailyUpdate(SaveVillagers *self, s32 flag) {
    ClockDateTimeRaw b;
    b.v[0] = 0;
    b.v[1] = 0;
    Clock_GetDateTime(&b.dt);
    if (DateTime_Compare(&b.dt, &self->lastMoveDate.dt, 0x3f) == -1) {
        MI_CpuCopy8(&b, &self->lastMoveDate, 8);
        if (*(s64 *)&self->lastMoveOutDate != 0) {
            MI_CpuCopy8(&b, &self->lastMoveOutDate, 8);
        }
    }
    SaveVillagers_UpdatePlayerErrandKind15(self, &b.dt);
    SaveVillagers_UpdatePlanStates(self, &b);
    SaveVillagers_ProcessTransfer(self, &b.dt);
    SaveVillagers_TryStartMoveOut(self, &b.dt);
    SaveVillagers_TryRandomMoveIn(self, &b.dt);
    SaveVillagers_DailyFurnitureUpdate(self);
    SaveVillagers_DailyVillagerUpdate((u8 *)self, flag);
    SaveVillagers_UpdateSickVillager((u8 *)self);
    if (flag == 0) {
        SaveVillagers_UpdateBirthdayNotices((u8 *)self);
    }
    SaveVillagers_UpdateBirthdayParty((u8 *)self);
}
}

namespace nF {
extern "C" void SaveVillagers_DailyFurnitureUpdate(SaveVillagers *self) {
    ClockDateTimeRaw a;
    ClockDateTimeRaw b;
    DateTime_Make(a.b, self->furnitureDropDate, 0, 0, 0);
    b.v[0] = 0;
    b.v[1] = 0;
    Clock_GetDateTime(&b.dt);
    if (DateTime_Compare(&b.dt, &a.dt, 0x38)) {
        VillagerData *p = self->villagers;
        for (s32 i = 0; i < 8; i++) {
            Villager_DropRandomFurniture(p);
            p++;
        }
        Clock_GetDate(self->furnitureDropDate);
    }
}
}

namespace nF {
extern "C" s32 HousePos_FindNthValid(HousePos *p, s32 n, u32 k) {
    s32 i = 0;
    s32 res = -1;
    for (; i < n; p++, i++) {
        if (HousePos_IsValid(&p->x)) {
            if (k == 0) {
                res = i;
                break;
            }
            k--;
        }
    }
    return res;
}
}

namespace nZ {
extern "C" {
extern const u32 sVillagerEventIds[11] = {
    0x0000000d, 0x0000000c, 0x0000000f, 0x00000009, 0x0000000a, 0x0000000e, 0x00000010, 0x00000011,
    0x00000012, 0x00000013, 0x0000000b,
};
extern const u8 sSpNpcInfoTable[116] = {
    0x00, 0x00, 0x05, 0x00, 0x02, 0x05, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x08, 0x01,
    0x01, 0x08, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x05, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x02, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x00,
};
extern const u8 sPersonalitySleepHours[6][4] = {
    0x01, 0x1e, 0x08, 0x00, 0x02, 0x00, 0x06, 0x1e, 0x04, 0x1e, 0x0a, 0x00, 0x01, 0x00, 0x05, 0x00,
    0x02, 0x1e, 0x07, 0x00, 0x03, 0x1e, 0x09, 0x00,
};
}
}

namespace nF {
extern "C" void SaveVillagers_PlaceMissingHouses(u8 *self) {
    s32 n;
    TownBlockMap *g = TownBlockMap_Get();
    static HousePos arr[30];
    if (g != NULL) {
        n = 0;
        s32 w = g->unitsX;
        s32 h = g->unitsZ;
        s32 xy[2];
        s32 i;
        xy[0] = 0;
        xy[1] = 0;
        for (i = 0; i < 30; i++) {
            HousePos_Clear(&arr[i].x);
        }
        for (xy[1] = 0; xy[1] < h; xy[1]++) {
            for (xy[0] = 0; xy[0] < w; xy[0]++) {
                struct Q { s32 x, y; };
                struct L { static inline u16 *Cell(BlockMap *g, const Q &q) { s32 x = q.x; s32 y = q.y; s32 hx = x >> 4, hy = y >> 4; return BlockMap_GetItemPtr(g, hx, hy, x - (hx << 4), y - (hy << 4), 0); } };
                u16 *t = L::Cell(g, *(Q *)xy);
                if (t != NULL && *t == 0x500a) {
                    HousePos_SetFromUnit(&arr[n].x, xy);
                    n++;
                }
            }
        }
        if (n > 0) {
            u16 v = 0xfff1;
            u8 *p = self;
            for (i = 0; i < 8; i++) {
                if (((VillagerData *)(void *)(p))->getVillagerId()->isValid() && !((VillagerDataItemView *)(void *)(p))->hasHousePos()) {
                    s32 idx = HousePos_FindNthValid(arr, 30, Random_GlobalBelow(n));
                    v = Item_MakeNeighborHouse(i);
                    HousePos *e = &arr[idx];
                    if (BlockMap_PutStructure(g, &v, arr[idx].x, e->z)) {
                        ((VillagerDataItemView *)(p))->setHousePos(&e->x);
                    }
                    HousePos_Clear(&e->x);
                    n--;
                    if (n <= 0) {
                        break;
                    }
                }
                p += sizeof(VillagerData);
            }
        }
    }
}
}

namespace nF {
extern "C" u32 SaveVillagers_GetRelationLevel(u8 *self, s32 a, s32 b) {
    s32 v = VillagerRelations_GetScore(self + 0x3800, a, b);
    u32 r = 4;
    for (s32 i = 0; i < 4; i++) {
        if (v >= sRelationLevelThresholds[i]) {
            r = i;
            break;
        }
    }
    return r;
}
}

namespace nF {
extern "C" s32 SaveVillagers_GetRelationLevelOf(u8 *self, u8 *p1, u8 *p2) {
    s32 a = SaveVillagers_FindIndex(self, ((VillagerData *)(void *)(p1))->getVillagerId());
    s32 b = SaveVillagers_FindIndex(self, ((VillagerData *)(void *)(p2))->getVillagerId());
    if (a != b && SaveVillagers_IsValidIndex(a) && SaveVillagers_IsValidIndex(b)) {
        return SaveVillagers_GetRelationLevel(self, a, b);
    }
    return 4;
}
}

namespace nF {
extern "C" void SaveVillagers_AddRelation(u8 *self, u8 *a, u8 *b, s32 c) {
    if (!gCommManager->isOnline()) {
        s32 x = SaveVillagers_FindIndex(self, (VillagerId *)a);
        s32 y = SaveVillagers_FindIndex(self, (VillagerId *)b);
        VillagerRelations_Add(((SaveVillagers *)self)->relations, x, y, c);
    }
}
}

namespace nF {
extern "C" u8 *SaveVillagers_FindByRelation(u8 *self, u8 *p, BOOL (**cmp)(s32, s32), s32 best) {
    s32 r6 = SaveVillagers_FindIndex(self, ((VillagerData *)(void *)(p))->getVillagerId());
    u8 *r7 = NULL;
    if (((VillagerData *)(void *)(p))->getVillagerId()->isValid() && SaveVillagers_IsValidIndex(r6)) {
        for (s32 i = 0; i < 8; i++) {
            if (i != r6 && SaveVillagers_IsOccupied(self, i)) {
                s32 v = VillagerRelations_GetScore(self + 0x3800, r6, i);
                if ((*cmp)(best, v)) {
                    r7 = (u8 *)SaveVillagers_Get(self, i);
                    best = v;
                } else if (best == v) {
                    if (r7 == NULL || (Random_GlobalBelow(4) & 1) == 1) {
                        r7 = (u8 *)SaveVillagers_Get(self, i);
                    }
                }
            }
        }
    }
    return r7;
}
}

namespace nF {
extern "C" BOOL Relation_IsHigher(s32 a, s32 b) {
    if (b > a) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nF {
extern "C" BOOL Relation_IsLower(s32 a, s32 b) {
    if (b < a) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nF {
extern "C" u8 *SaveVillagers_FindFriendOf(u8 *self, u8 *p) {
    BOOL (*fn)(s32, s32) = Relation_IsHigher;
    return SaveVillagers_FindByRelation(self, p, &fn, (s32)0x80000000);
}
}

namespace nF {
extern "C" u8 *SaveVillagers_FindEnemyOf(u8 *self, u8 *p) {
    BOOL (*fn)(s32, s32) = Relation_IsLower;
    return SaveVillagers_FindByRelation(self, p, &fn, 0x7fffffff);
}
}

namespace nF {
extern "C" VillagerState *VillagerStates_GetEntry(u32 a) {
    return VillagerStateTable_GetEntry(VillagerStates_Get(), a);
}
}

namespace nF {
extern "C" s32 Villager_GetPlayerErrandKind(u8 *self, u8 *p, PlayerData *r4) {
    u16 *r5 = (u16 *)((VillagerData *)(void *)(p))->getVillagerId();
    s32 result = 0x16;
    if (r4 == NULL) {
        r4 = PlayerData_GetCurrent();
    }
    if (r4 != NULL) {
        PlayerErrands *errands = ((PlayerData *)r4)->getErrands();
        PlayerErrandSlot *a = PlayerErrands_GetSlot(errands, 0);
        PlayerErrandSlot *b = PlayerErrands_GetSlot(errands, 1);
        HouseVisitInvite *invite = &errands->houseVisitInvite;
        if (PlayerErrandSlot_GetRecord(a)->isActive()) {
            u16 *r7 = (u16 *)PlayerErrandSlot_GetVillager(a, 0);
            if (r7[0] == r5[0] && memcmp(r7 + 1, r5 + 1, 8) == 0 && ((u8 *)r7)[0xb] == ((u8 *)r5)[0xb]) {
                result = PlayerErrandSlot_GetRecord(a)->getKind();
                goto end;
            }
        }
        if (PlayerErrandSlot_GetRecord(b)->isActive()) {
            u16 *r7 = (u16 *)PlayerErrandSlot_GetVillager(b, 0);
            if (r7[0] == r5[0] && memcmp(r7 + 1, r5 + 1, 8) == 0 && ((u8 *)r7)[0xb] == ((u8 *)r5)[0xb]) {
                result = PlayerErrandSlot_GetRecord(b)->getKind();
                goto end;
            }
        }
        if (((ErrandRecord *)(void *)(((SickVillagerRecord *)(void *)(self + 0x3830))->getErrand()))->isActive()) {
            u16 *r7 = (u16 *)((SickVillagerRecord *)(self + 0x3830))->getVillagerId();
            if (r7[0] == r5[0] && memcmp(r7 + 1, r5 + 1, 8) == 0 && ((u8 *)r7)[0xb] == ((u8 *)r5)[0xb]) {
                result = ((ErrandRecord *)(void *)(((SickVillagerRecord *)(void *)(self + 0x3830))->getErrand()))->getKind();
                goto end;
            }
        }
        if (HouseVisitInvite_IsFrom(invite, (VillagerId *)r5)) {
            result = invite->errand.getKind();
        } else if (PlanErrand_GetRecord(VillagerPlanBlock_GetErrand(Villager_GetPlan((VillagerData *)(p))))->isActive()) {
            result = PlanErrand_GetRecord(VillagerPlanBlock_GetErrand(Villager_GetPlan((VillagerData *)(p))))->getKind();
        }
    }
end:
    return result;
}
}

namespace nF {
extern "C" s32 Villager_GetErrandKind(u8 *self, u8 *p, PlayerData *r5) {
    VillagerState *q = Villager_GetState((VillagerData *)(p));
    s32 r7 = 0x16;
    if (r5 == NULL) {
        r5 = PlayerData_GetCurrent();
    }
    if (q != NULL && r5 != NULL) {
        s32 r = Villager_GetPlayerErrandKind(self, p, r5);
        if ((u32)r < 0x16) {
            r7 = r;
        } else if (VillagerState_GetErrand(q)->isActive()) {
            r7 = VillagerState_GetErrand(q)->getKind();
        }
    }
    return r7;
}
}

namespace nF {
extern "C" BOOL SaveVillagers_ShouldAssignErrands(u8 *self) {
    if (gCommManager->isOnline()) {
        return FALSE;
    }
    u8 *p = self;
    s32 n = SaveVillagers_Count(self);
    s32 c5 = 0;
    s32 c4 = c5;
    s32 i = c5;
    PlayerData *zero = NULL;
    do {
        if (((VillagerData *)(void *)(p))->getVillagerId()->isValid()) {
            s32 r = Villager_GetErrandKind(self, p, zero);
            if (r == 0x16) {
                c5++;
            } else if (Errand_GetClass(r) != 1) {
                c4++;
            }
        }
        p += sizeof(VillagerData);
        i++;
    } while (i < 8);
    if (n >= c4 && ((n - c4) >> 1) < c5) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nF {
extern "C" void VillagerStates_ResetErrands() {
    VillagerState *p = VillagerStates_Get()->entries;
    for (s32 i = 0; i < 8; i++) {
        VillagerState_GetErrand(p)->clear();
        p++;
    }
}
}

namespace nE {
extern "C" void SaveVillagers_AssignErrands(void *bb) {
    u8 *b = (u8 *)bb;
    PlayerData *a = PlayerData_GetCurrent();
    s32 r5 = 0x11;
    s32 r4 = 8;
    if (a != 0) {
        u16 v[2];
        s32 idx = 0;
        s32 self = SaveVillagers_GetUnk3830Index(b);
        s32 i;
        MI_CpuFill8(sErrandKindTaken, 0, r5);
        MI_CpuFill8(sErrandVillagerDone, 0, r4);
        for (i = 0; i < 13; i++) {
            if (Errand_GetClassIndex(&idx, sReservedErrandKinds[i])) {
                sErrandKindTaken[idx] = 1;
                r5--;
            }
        }
        for (i = 0; i < 8; i++) {
            u8 *p = b + i * sizeof(VillagerData);
            if (((VillagerId *)((VillagerData *)(p))->getVillagerId())->isValid() && Villager_GetResidentStatus((VillagerData *)p) == 3 && i != self) {
                u32 t = Villager_GetErrandKind(b, p, a);
                if (t < 0x16) {
                    if (Errand_GetClass(t) == 1) {
                        if (Errand_GetClassIndex(&idx, t)) {
                            sErrandVillagerDone[i] = 1;
                            r4--;
                            sErrandKindTaken[idx] = 1;
                            r5--;
                        }
                    }
                }
            } else {
                sErrandVillagerDone[i] = 1;
                r4--;
            }
        }
        s32 zero = 0;
        for (i = 0; i < 8; i++) {
            u8 *p2;
            u8 *flag = &sErrandVillagerDone[i];
            if (*flag == 0) {
                p2 = b + i * sizeof(VillagerData);
                VillagerPlan *e = VillagerPlanBlock_GetPlan(Villager_GetPlan((VillagerData *)(p2)));
                if (e->hasTrend()) {
                    if (e->getStateGroup() == 0) {
                        ErrandRecord *x = VillagerState_GetErrand(Villager_GetState((VillagerData *)(p2)));
                        v[0] = 0xfff1;
                        x->start(e->getState(), v, zero);
                        *flag = 1;
                        r4--;
                    }
                }
            }
        }
        while (r4 > 0 && r5 > 0) {
            u8 *g;
            s32 m;
            s32 k2;
            u8 *f;
            s32 k;
            void *x;
            s32 j;
            k = Random_GlobalBelow(r4);
            for (j = 0; j < 8; j++) {
                f = &sErrandVillagerDone[j];
                if (*f == 0) {
                    if (k == 0) {
                        x = VillagerState_GetErrand(Villager_GetState((VillagerData *)(b + j * sizeof(VillagerData))));
                        k2 = Random_GlobalBelow(r5);
                        for (m = 0; m < 17; m++) {
                            g = &sErrandKindTaken[m];
                            if (*g == 0) {
                                if (k2 == 0) {
                                    v[1] = 0xfff1;
                                    ((ErrandRecord *)(void *)(x))->start((u8)(m + 5), &v[1], 0);
                                    *g = 1;
                                    r5--;
                                    break;
                                }
                                k2--;
                            }
                        }
                        *f = 1;
                        r4--;
                        break;
                    }
                    k--;
                }
            }
        }
    }
}
}

namespace nE {
extern "C" void SaveVillagers_UpdateErrands(u8 *b) {
    if (SaveVillagers_ShouldAssignErrands(b)) SaveVillagers_AssignErrands(b);
}
}

namespace nE {
extern "C" void SaveVillagers_UpdatePlayerErrandKind15(void *unused, ClockDateTime *q) {
    s32 i;
    for (i = 0; i < 4; i++) {
        void *e = PlayerData_GetResident(gSavePlayers, i);
        if (((PlayerId *)(void *)(((PlayerData *)(void *)(e))->getPlayerId()))->isValid()) {
            HouseVisitInvite *r4 = &((PlayerData *)(e))->getErrands()->houseVisitInvite;
            ErrandRecord *r6 = &r4->errand;
            if (r6->isActive()) {
                if (r6->getKind() == 0x15) {
                    if (r4->isValid()) {
                        if (r6->getStep() == 0) {
                            if (DateTime_DiffDays(ErrandRecord_GetTime(r6), q) < 0) HouseVisitInvite_Clear(r4);
                        } else if (((HouseVisitInviteGiftView *)r4)->giftKind != 0) {
                            s32 days = DateTime_DiffDays((ClockDateTime *)&r4->visitTime, q);
                            r6->setStep(4);
                            if (days) {
                                u32 bits = ((HouseVisitInviteGiftView *)r4)->giftKind;
                                if (Villager_SendHouseVisitLetter(bits, ((PlayerData *)e)->getPlayerId(), r4)) HouseVisitInvite_Clear(r4);
                            }
                        } else {
                            HouseVisitInvite_Clear(r4);
                        }
                    }
                }
            }
        }
    }
}
}

namespace nE {
extern "C" void SaveVillagers_DailyVillagerUpdate(u8 *p, s32 q) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (((VillagerId *)((VillagerData *)(p))->getVillagerId())->isValid()) {
            if (q == 0) {
                if (Villager_MaybeCopyAblePattern(i, 0)) {
                    u16 v = 0x12a8;
                    ((VillagerData *)(p))->setShirt((u16 *)(&v));
                }
            }
            Villager_UpdatePlanErrand((VillagerData *)(p));
            PlanErrand *a = VillagerPlanBlock_GetErrand(Villager_GetPlan((VillagerData *)(p)));
            ErrandRecord *c = PlanErrand_GetRecord(a);
            if (c->isActive()) {
                if (c->getStep() == 0) {
                    PlanErrand_GetPlayer(a)->clear();
                }
            }
            Villager_PlaceReceivedItems((VillagerData *)(p));
        }
        p += sizeof(VillagerData);
    }
}
}

namespace nE {
extern "C" SickVillagerRecord *SaveVillagers_GetUnk3830(void *p) {
    return (SickVillagerRecord *)((u8 *)p + 0x3830);
}
}

namespace nE {
extern "C" s32 SaveVillagers_GetUnk3830Index(void *p) {
    if (((ErrandRecord *)(void *)(((SickVillagerRecord *)(void *)((void *)SaveVillagers_GetUnk3830(p)))->getErrand()))->isActive()) {
        return SaveVillagers_FindIndex((u8 *)p, SaveVillagers_GetUnk3830(p)->getVillagerId());
    }
    return -1;
}
}

namespace nE {
extern "C" s32 SaveVillagers_PickSickVillager(void *pp, u32 idx) {
    u8 *b = (u8 *)pp;
    if (idx >= 12) return -1;
    u8 mask = 0;
    ClockDateTimeRaw d;
    d.v[0] = 0;
    d.v[1] = 0;
    u8 *p = b;
    s32 cnt = 0;
    s32 i;
    Clock_GetDateTime(&d.dt);
    for (i = 0; i < 8; i++) {
        if (i != *(s8 *)(b + 0x38ea)) {
            if (((VillagerId *)((VillagerData *)(p))->getVillagerId())->isValid()) {
                if (Villager_GetResidentStatus((VillagerData *)p) == 3) {
                    if (Villager_IsFreeOfPlayerErrands((VillagerData *)p)) {
                        if (Villager_GetUpcomingBirthdayDay((VillagerData *)p, 15, (u8 *)&d) == -1) {
                            mask |= 1 << i;
                            cnt++;
                        }
                    }
                }
            }
        }
        p += sizeof(VillagerData);
    }
    s32 r4 = Random_PickSetBit(mask, cnt, 8);
    VillagerData *v = SaveVillagers_Get(b, r4);
    if (v) {
        const u8 *q = Villager_GetInfo(v);
        if (!(Random_GlobalBelow(sMonthlySickRoll[idx]) >= q[3] + 0x80)) return r4;
    }
    return -1;
}
}

namespace nE {
extern "C" BOOL SaveVillagers_CanSomeoneGetSick(u8 *p) {
    if (SaveVillagers_Count(p) >= 7) return TRUE;
    return FALSE;
}
}

namespace nE {
extern "C" void SaveVillagers_AdvanceSickDay(void *pp) {
    u8 *b = (u8 *)pp;
    u32 c = b[0x38be];
    void *r = NULL;
    if (((SickVillagerRecord *)(void *)(b + 0x3830))->hasTodaysVisitor() || b[0x38b9]) {
        if (c == 0) c = 5;
        else if ((u8)c < 5) c--;
        b[0x38be] = c;
        r = ((SickVillagerRecord *)(void *)(b + 0x3830))->getVisitor(b[0x38be]);
    } else {
        u8 n = c + 1;
        if (n < 5) {
            b[0x38be] = n;
            r = ((SickVillagerRecord *)(void *)(b + 0x3830))->getVisitor(b[0x38be]);
        } else if ((u8)c < 5) {
            r = ((SickVillagerRecord *)(void *)(b + 0x3830))->getVisitor((u8)c);
        }
    }
    if (r) ((PlayerId *)(r))->clear();
}
}

namespace nE {
extern "C" void SaveVillagers_UpdateSickVillager(u8 *b) {
    SickVillagerDateLocals d;
    s32 r4, r6, r7;
    s32 v1, flag;
    s32 sel;
    sel = SaveVillagers_GetUnk3830Index(b);
    Clock_GetDate(d.date);
    if (sel != -1) {
        if (Date_IsAfterOrEqual(d.date, b + 0x38b6) == 0) {
            ((SickVillagerRecord *)(void *)(b + 0x3830))->resetRecord();
            return;
        }
        if (((SickVillagerRecord *)(void *)(b + 0x3830))->isRecovered()) {
            if (((SickVillagerRecord *)(b + 0x3830))->isRecentlyRecovered((ClockDate *)d.date) == 0) ((SickVillagerRecord *)(b + 0x3830))->resetRecord();
            return;
        }
        r7 = Date_DaysBetween(d.date, b + 0x38ba);
        if (r7 == 0) return;
        v1 = 0;
        r4 = 0;
        flag = 0;
        if (b[0x38b9] == 0) {
            if (Date_DaysBetween(d.date, b + 0x38b6) >= 10) {
                s32 t = Date_DaysBetween(b + 0x38ba, b + 0x38b6);
                if (t >= 0 && t < 10) v1 = 9 - t;
                flag = 1;
            }
        }
        if (r7 < 0) r6 = -r7; else r6 = r7;
        if (v1 > r6) v1 = r7;
        while (v1 > 0) {
            SaveVillagers_AdvanceSickDay(b);
            v1--;
            r6--;
            r4++;
        }
        if (flag) b[0x38b9] = 1;
        while (r6 > 0) {
            SaveVillagers_AdvanceSickDay(b);
            r6--;
            r4++;
            if (((SickVillagerRecord *)(void *)(b + 0x3830))->isRecovered()) break;
        }
        if (((SickVillagerRecord *)(void *)(b + 0x3830))->isRecovered()) {
            if (r6 >= 3 && r7 > 0) {
                ((SickVillagerRecord *)(void *)(b + 0x3830))->resetRecord();
                return;
            }
            if (r4 > 0) {
                DateTime_Make(&d.time.dt.second, b + 0x38ba, 0, 0, 0);
                if (r7 > 0) {
                    DateTime_AddDays(&d.time.dt, r4);
                    b[0x38bc] = d.time.dt.year;
                    b[0x38bb] = d.time.dt.month;
                    b[0x38ba] = d.time.dt.day;
                } else if (r6 > 0) {
                    ((SickVillagerRecord *)(void *)(b + 0x3830))->resetRecord();
                } else {
                    DateTime_SubDays(&d.time.dt, r4);
                    b[0x38bc] = d.time.dt.year;
                    b[0x38bb] = d.time.dt.month;
                    b[0x38ba] = d.time.dt.day;
                }
            }
        } else {
            MI_CpuCopy8(d.date, b + 0x38ba, 4);
        }
    } else {
        if (SaveVillagers_CanSomeoneGetSick(b)) {
            r4 = SaveVillagers_PickSickVillager(b, (u8)(d.date[1] - 1));
            if (r4 != -1) {
                void *q = SaveVillagers_Get(b, r4);
                if (q) {
                    if (((VillagerId *)((VillagerData *)(q))->getVillagerId())->isValid()) {
                        ((SickVillagerRecord *)(b + 0x3830))->startSickness(((VillagerData *)(q))->getVillagerId(), d.date);
                        b[0x38ea] = r4;
                        OutdoorSchedule_ForceReroll(&((SaveVillagers *)b)->outdoorSchedule);
                    }
                }
            }
        }
    }
}
}

namespace nE {
extern "C" void SaveVillagers_PickGreeter(u8 *base) {
    u8 *p = base;
    u8 mask = 0;
    s32 cnt = 0;
    s32 res = 0;
    s32 i;
    for (i = 0; i < 8; i++) {
        if (((VillagerId *)((VillagerData *)(p))->getVillagerId())->isValid()) {
            if (VillagerState_GetPresence(Villager_GetState((VillagerData *)(p))) == 0) {
                mask |= 1 << i;
                cnt++;
            }
        }
        p += sizeof(VillagerData);
    }
    s32 r = Random_PickSetBit(mask, cnt, 8);
    if (r != -1) {
        res = (u8)r;
    } else {
        u8 *p2;
        u8 m2;
        s32 c2;
        s32 j;
        m2 = 0;
        c2 = 0;
        p2 = base;
        j = 0;
        for (; j < 8; j++) {
            if (((VillagerId *)((VillagerData *)(p2))->getVillagerId())->isValid()) {
                if (Villager_GetResidentStatus((VillagerData *)p2) == 3) {
                    if (j != SaveVillagers_GetUnk3830Index(base)) {
                        m2 |= 1 << j;
                        c2++;
                    }
                }
            }
            p2 += sizeof(VillagerData);
        }
        r = Random_PickSetBit(m2, c2, 8);
        if (r != -1) res = (u8)r;
    }
    VillagerStates_Get()->greeter = res;
}
}

namespace nE {
extern "C" s32 VillagerEvent_GetTodayIndex() {
    ClockDateTimeRaw a;
    ClockDateTimeRaw b;
    const u32 *t = sVillagerEventIds;
    s32 i;
    a.v[0] = 0;
    a.v[1] = 0;
    Clock_GetDateTime(&a.dt);
    for (i = 0; i < 11; i++) {
        u32 v = *t;
        BOOL f;
        MI_CpuCopy8(&a, &b, 8);
        if (Event_GetState(v, &b, 0)) f = TRUE; else f = FALSE;
        if (f) {
            if (v == EventAnnounce_GetCurrentEvent()) return i;
        }
        t++;
    }
    return 11;
}
}

namespace nE {
extern "C" s32 VillagerEvent_FindUpcomingIndex(u32 n, void *src) {
    ClockDateTimeRaw a;
    ClockDateTimeRaw b;
    EventDayEntry buf[7];
    u32 i;
    a.v[0] = 0;
    a.v[1] = 0;
    if (src == NULL) {
        Clock_GetDateTime(&a.dt);
    } else {
        MI_CpuCopy8(src, &a, 8);
    }
    for (i = 0; i <= n; i++) {
        s32 cnt, k;
        EventDayEntry *e;
        e = buf;
        MI_CpuCopy8(&a, &b, 8);
        cnt = EventSchedule_CollectDayAll(buf, &b.dt);
        for (k = 0; k < cnt; k++) {
            s32 j;
            const u32 *t = sVillagerEventIds;
            for (j = 0; j < 11; j++) {
                if (e->eventId == *t) return j;
                t++;
            }
            e++;
        }
        DateTime_AddDays(&a.dt, 1);
    }
    return 11;
}
}

namespace nE {
extern "C" void SaveVillagers_InitTalkUrges(u8 *p, void *q) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (((VillagerId *)((VillagerData *)(p))->getVillagerId())->isValid()) {
            Villager_InitTalkUrge((VillagerData *)(p), q);
        }
        p += sizeof(VillagerData);
    }
}
}

namespace nE {
extern "C" void SaveVillagers_DoubleTalkUrges(u8 *p) {
    s32 i;
    if (gCommManager->isSlotActive(gCommManager->myAid) == 0) {
        for (i = 0; i < 8; i++) {
            if (((VillagerId *)((VillagerData *)(p))->getVillagerId())->isValid()) {
                Villager_DoubleTalkUrge((VillagerData *)(p));
            }
            p += sizeof(VillagerData);
        }
    }
}
}

namespace nD {
extern "C" void SaveVillagers_ApplyBadFortune(void *self0) {
    u8 *self = (u8 *)self0;
    if (gCommManager->isSlotActive(gCommManager->myAid) == 0) {
        s32 i;
        for (i = 0; i < 8; self += sizeof(VillagerData), i++) {
            if (((VillagerId *)(((VillagerData *)(self))->getVillagerId()))->isValid() != 0) {
                Villager_HalveTalkUrge((VillagerData *)(self));
            }
        }
    }
}
}

namespace nD {
extern "C" void SaveVillagers_GiveFortuneGreeting(void *self0, void *p) {
    u8 *self = (u8 *)self0;
    if (((PlayerId *)(p))->isValid() != 0) {
        u8 *s = self;
        u8 mask = 0;
        s32 cnt = 0;
        s32 i;
        for (i = 0; i < 8; s += sizeof(VillagerData), i++) {
            if (((VillagerId *)(((VillagerData *)(s))->getVillagerId()))->isValid() != 0) {
                if (VillagerState_GetPresence(Villager_GetState((VillagerData *)(s))) == 0) {
                    if (Villager_FindMemory(s, p) != 0) {
                        mask |= (1 << i);
                        cnt++;
                    }
                }
            }
        }
        s32 r4 = Random_PickSetBit(mask, cnt, 8);
        if (SaveVillagers_IsValidIndex(r4) == 0) {
            mask = 0;
            cnt = 0;
            s = self;
            for (i = 0; i < 8; s += sizeof(VillagerData), i++) {
                if (((VillagerId *)(((VillagerData *)(s))->getVillagerId()))->isValid() != 0) {
                    if (Villager_GetResidentStatus((VillagerData *)s) == 3) {
                        if (i != SaveVillagers_GetUnk3830Index(self)) {
                            if (Villager_FindMemory(s, p) != 0) {
                                mask |= (1 << i);
                                cnt++;
                            }
                        }
                    }
                }
            }
            r4 = Random_PickSetBit(mask, cnt, 8);
        }
        VillagerData *o = SaveVillagers_Get(self, r4);
        if (o != NULL) {
            if (((VillagerId *)(((VillagerData *)(o))->getVillagerId()))->isValid() != 0) {
                void *q = (void *)Villager_FindMemory(o, p);
                if (q != NULL) {
                    ((VillagerMemory *)(q))->setFortuneGreeting();
                }
            }
        }
    }
}
}

namespace nD {
extern "C" void SaveVillagers_ApplyGoodFortune(u8 *self, void *p) {
    if (gCommManager->isOnline() == 0) {
        SaveVillagers_GiveFortuneGreeting(self, p);
    }
    if (gCommManager->isSlotActive(gCommManager->myAid) == 0) {
        SaveVillagers_DoubleTalkUrges(self);
    }
}
}

namespace nD {
extern "C" void SaveVillagers_UpdateRoomInfo(void *self, s32 idx) {
    VillagerData *o = SaveVillagers_Get(self, idx);
    if (o != NULL) {
        if (((VillagerId *)(((VillagerData *)(o))->getVillagerId()))->isValid() != 0) {
            s32 v5 = 5;
            s32 z1 = 0;
            s32 z2 = 0;
            u16 h = 0;
            if (((VillagerId *)(((VillagerData *)(o))->getVillagerId()))->isValid() != 0) {
                VillagerState *r5 = Villager_GetState(o);
                if (r5 != NULL) {
                    u32 x[5];
                    RoomScoreEvaluator_Construct(x);
                    h = 0;
                    r5->roomScore = HappyRoom_EvaluateVillagerRoom(x, idx, &h, &v5, &z1, &z2);
                    r5->roomBonusFlags = h;
                    RoomScoreEvaluator_Destruct(x);
                }
            }
        }
    }
}
}

namespace nD {
extern "C" void SaveVillagers_UpdateAllRoomInfo(void *self) {
    s32 i;
    for (i = 0; i < 8; i++) {
        SaveVillagers_UpdateRoomInfo(self, i);
    }
}
}

namespace nD {
extern "C" void SaveVillagers_ResetMoods(u8 *self) {
    s32 i;
    for (i = 0; i < 8; i++) {
        u8 *s = self + i * sizeof(VillagerData);
        if (((VillagerId *)(((VillagerData *)(s))->getVillagerId()))->isValid() != 0) {
            VillagerState_SetMood(Villager_GetState((VillagerData *)(s)), 0);
            VillagerState_SetMoodTimer(Villager_GetState((VillagerData *)(s)), 0);
        }
    }
}
}

namespace nD {
extern "C" void SaveVillagers_UpdateBirthdayNotices(u8 *self) {
    ClockDateTimeWords buf;
    buf.words[0] = 0;
    buf.words[1] = 0;
    Clock_GetDateTime(&buf.dt);
    s32 i = 0;
    for (; i < 8; self += sizeof(VillagerData), i++) {
        VillagerId *o = ((VillagerData *)(self))->getVillagerId();
        if (((VillagerId *)(o))->isValid() != 0) {
            if (Villager_GetResidentStatus((VillagerData *)self) == 3) {
                s32 j;
                for (j = 0; j < 4; j++) {
                    void *r7 = PlayerData_GetResident(gSavePlayers, j);
                    if (r7 != NULL) {
                        void *a = ((PlayerData *)(r7))->getPlayerId();
                        if (((PlayerId *)(a))->isValid() != 0) {
                            if (((PlayerData *)(r7))->testFlag(1) == 0) {
                                s32 t = Villager_GetUpcomingBirthdayDay((VillagerData *)self, 7, &buf.dt.second);
                                if (t != -1) {
                                    s32 c = ((PlayerData *)(r7))->getBirthdayNoticeDay(i);
                                    if (c != t) {
                                        if (Villager_SendBirthdayNoticeLetter(a, o) != 0) {
                                            ((PlayerData *)(r7))->setBirthdayNoticeDay(i, (u8)t);
                                        }
                                    }
                                } else {
                                    ((PlayerData *)(r7))->setBirthdayNoticeDay(i, 0xff);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
}

namespace nD {
extern "C" s32 SaveVillagers_PickBirthdayGuest(void *self0, s32 x) {
    u8 *self = (u8 *)self0;
    u8 *s = self;
    s32 best = -100000;
    s32 cnt, i;
    u8 mask;
    mask = 0;
    cnt = 0;
    for (i = 0; i < 8; s += sizeof(VillagerData), i++) {
        if (i != x && Villager_CanAttendParty((VillagerData *)s) != 0) {
            s32 v = VillagerRelations_GetScore(self + 0x3800, x, i);
            if (v > best) {
                best = v;
                mask = (u8)(1 << i);
                cnt = 1;
            } else if (v == best) {
                mask |= (1 << i);
                cnt++;
            }
        }
    }
    return Random_PickSetBit(mask, cnt, 8);
}
}

namespace nD {
extern "C" s32 SaveVillagers_FindBirthdayVillager(void *self0, void *p0) {
    u8 *self = (u8 *)self0;
    u8 *p = (u8 *)p0;
    ClockDateTimeWords b;
    EventDayEntry out[7];
    void *r0 = PlayerData_GetCurrent();
    if (r0 != NULL && ((PlayerData *)(void *)(r0))->testFlag(1) == 0 && p[2] >= 6) {
        MI_CpuCopy8(p, &b, 8);
        s32 n = EventSchedule_CollectDayAll(out, &b.dt);
        u32 i;
        for (i = 0; (s32)i < 8; self += sizeof(VillagerData), i++) {
            if (((VillagerId *)(((VillagerData *)(self))->getVillagerId()))->isValid() != 0) {
                if (Villager_GetResidentStatus((VillagerData *)self) == 3) {
                    EventDayEntry *e = out;
                    s32 j;
                    for (j = 0; j < n; e++, j++) {
                        if (e->eventId == i) {
                            return i;
                        }
                    }
                }
            }
        }
    }
    return -1;
}
}

namespace nD {
extern "C" void SaveVillagers_UpdateBirthdayParty(u8 *self) {
    ClockDateTimeWords buf;
    buf.words[0] = 0;
    buf.words[1] = 0;
    s32 r6 = VillagerStates_GetBirthdayHost();
    Clock_GetDateTime(&buf.dt);
    s32 r4 = SaveVillagers_FindBirthdayVillager(self, &buf);
    if (r4 == -1) {
        VillagerStates_SetBirthdayHost(-1);
        VillagerStates_SetBirthdayGuest(-1);
    } else if (r4 == r6) {
        VillagerData *o = SaveVillagers_Get(self, VillagerStates_GetBirthdayGuest());
        if (o == NULL || Villager_CanAttendParty((VillagerData *)o) == 0) {
            VillagerStates_SetBirthdayGuest((s8)SaveVillagers_PickBirthdayGuest(self, r6));
        }
    } else if (r4 != r6) {
        r6 = SaveVillagers_PickBirthdayGuest(self, r4);
        VillagerStates_SetBirthdayHost((s8)r4);
        VillagerStates_SetBirthdayGuest((s8)r6);
        if (r4 == SaveVillagers_GetUnk3830Index(self)) {
            ((SickVillagerRecord *)(void *)(self + 0x3830))->resetRecord();
        }
    }
}
}

namespace nD {
extern "C" void SaveVillagers_ApplyBirthdayParty(u8 *self) {
    s32 r7 = VillagerStates_GetBirthdayHost();
    s32 w = VillagerStates_GetBirthdayGuest();
    u8 *s = self;
    s32 i;
    for (i = 0; i < 8; s += sizeof(VillagerData), i++) {
        if (((VillagerId *)(((VillagerData *)(s))->getVillagerId()))->isValid() != 0) {
            if (VillagerState_GetRole(Villager_GetState((VillagerData *)(s))) == 3) {
                VillagerState_ResetRole(Villager_GetState((VillagerData *)(s)));
            }
        }
    }
    if (r7 != -1) {
        VillagerData *o = SaveVillagers_Get(self, r7);
        if (o != NULL && ((VillagerId *)(((VillagerData *)(o))->getVillagerId()))->isValid() != 0) {
            VillagerState_SetRole(Villager_GetState(o), 0);
            o = SaveVillagers_Get(self, w);
            if (o != NULL) {
                if (((VillagerId *)(((VillagerData *)(o))->getVillagerId()))->isValid() != 0) {
                    VillagerState_SetRole(Villager_GetState(o), 3);
                }
            }
        } else {
            VillagerStates_SetBirthdayHost(-1);
            VillagerStates_SetBirthdayGuest(-1);
        }
    }
}
}

namespace nD {
extern "C" s32 SaveVillagers_PickFleaMarketBuyer(void *self0) {
    u8 *self = (u8 *)self0;
    void *r0 = PlayerData_GetCurrent();
    void *p;
    if (r0 != NULL) {
        p = ((PlayerData *)(r0))->getPlayerId();
    } else {
        p = NULL;
    }
    if (p != NULL && ((PlayerId *)(void *)(p))->isValid() != 0) {
        u8 mask = 0;
        s32 cnt = 0;
        s32 i;
        for (i = 0; i < 8; self += sizeof(VillagerData), i++) {
            if (((VillagerId *)(((VillagerData *)(self))->getVillagerId()))->isValid() != 0) {
                if (Villager_FindMemory(self, p) != 0) {
                    if (((VillagerMemory *)(void *)((void *)Villager_FindMemory(self, p)))->isFleaMarketVisited() == 0) {
                        if (VillagerState_GetPresence(Villager_GetState((VillagerData *)(self))) == 0) {
                            mask |= (1 << i);
                            cnt++;
                        }
                    }
                }
            }
        }
        return Random_PickSetBit(mask, cnt, 8);
    }
    return -1;
}
}

namespace nD {
extern "C" void SaveVillagers_PickFleaMarketBuyerNow(void *self) {
    VillagerStates_SetFleaMarketBuyer((s8)SaveVillagers_PickFleaMarketBuyer(self));
}
}

namespace nD {
extern "C" s32 SaveVillagers_FindBestFriendIndexOf(void *self0, void *p) {
    u8 *self = (u8 *)self0;
    if (((PlayerId *)(p))->isValid() != 0) {
        s32 best = -128;
        s32 cnt, i;
        u8 mask;
        mask = 0;
        cnt = 0;
        for (i = 0; i < 8; self += sizeof(VillagerData), i++) {
            if (((VillagerId *)(((VillagerData *)(self))->getVillagerId()))->isValid() != 0) {
                if (Villager_GetResidentStatus((VillagerData *)self) == 3) {
                    void *o = (void *)Villager_FindMemory(self, p);
                    if (o != NULL) {
                        s32 v = ((VillagerMemory *)(o))->getFriendship();
                        if (v == best) {
                            mask |= (1 << i);
                            cnt++;
                        } else if (v > best) {
                            best = v;
                            mask = (u8)(1 << i);
                            cnt = 1;
                        }
                    }
                }
            }
        }
        return Random_PickSetBit(mask, cnt, 8);
    }
    return -1;
}
}

namespace nD {
extern "C" void SaveVillagers_PickPlayerBirthdayVisitor(u8 *self, void *p) {
    VillagerStates_SetBirthdayVisitor(-1);
    if (Scene_GetCurrent() == 6) {
        if (p == NULL) {
            p = PlayerData_GetCurrent();
        }
        if (p != NULL) {
            if (((PlayerData *)(p))->testFlag(1) == 0) {
                if (((PlayerInventory *)(((PlayerData *)(p))->getInventory()))->findEmptyPocket() != -1) {
                    void *a = ((PlayerData *)(p))->getPlayerId();
                    u8 *r4 = ((PlayerData *)(p))->getBirthday();
                    if (*(u16 *)r4 != 0) {
                        if (((PlayerId *)(a))->isValid() != 0) {
                            ClockDateTimeRaw bb;
                            *(u32 *)&bb.b[0] = 0;
                            *(u32 *)&bb.b[4] = 0;
                            Clock_GetDateTime(&bb.dt);
                            u32 r7 = bb.b[5];
                            s32 tt = ((PlayerData *)(p))->getBirthdayTalkYear();
                            if (tt != r7) {
                                if (r4[1] == bb.b[4]) {
                                    if (r4[0] == bb.b[3]) {
                                        if (bb.b[2] >= 6) {
                                            s32 s = SaveVillagers_FindBestFriendIndexOf(self, a);
                                            if (SaveVillagers_IsValidIndex(s) != 0) {
                                                OutdoorSchedule_ForceReroll(&((SaveVillagers *)self)->outdoorSchedule);
                                            }
                                            VillagerStates_SetBirthdayVisitor((s8)s);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
}

namespace nD {
extern "C" BOOL SaveVillagers_IsNicknameCooldownOver(SaveVillagers *self, u8 *p) {
    BOOL r = TRUE;
    if (self->nicknameDate[3] != 0) {
        if (Date_IsAfterOrEqual(p, self->nicknameDate) != 0) {
            if (Date_DaysBetween(p, self->nicknameDate) < 14) {
                r = FALSE;
            }
        } else {
            if (Date_DaysBetween(self->nicknameDate, p) < 14) {
                r = FALSE;
            }
        }
    }
    return r;
}
}

namespace nD {
extern "C" void SaveVillagers_SetNicknameDate(SaveVillagers *self, void *p) {
    MI_CpuCopy8(p, self->nicknameDate, 4);
    self->nicknameDate[3] = 1;
}
}

namespace nD {
extern "C" BOOL SaveVillagers_AllKnowPlayer(u8 *self, void *p) {
    if (((PlayerId *)(p))->isValid() != 0) {
        u8 *s = (u8 *)SaveVillagers_Get(self, 0);
        u32 i;
        for (i = 0; (s32)i < 8; s += sizeof(VillagerData), i++) {
            if (((VillagerId *)(((VillagerData *)(s))->getVillagerId()))->isValid() != 0) {
                if (Villager_FindMemory(s, p) == 0) {
                    return FALSE;
                }
            }
        }
        return TRUE;
    }
    return FALSE;
}
}

namespace nD {
extern "C" s32 SaveVillagers_DeliverLetter(void *self, void *p) {
    if (p != NULL) {
        void *t = Letter_GetSenderPlayer(p);
        if (t != NULL) {
            PlayerId b(*(const PlayerId *)t);
            if (b.isValid() != 0) {
                void *q = PlayerDataArray_GetById(gSavePlayers, (u16 *)&b);
                void *name = Letter_GetRecipientVillager(p);
                if (q != NULL) {
                    Arbeit_OnLetterSent(((PlayerData *)(q))->getErrands(), p);
                }
                if (name != NULL) {
                    VillagerIdCopyLocal s(name);
                    if (s.v.isValid() != 0) {
                        void *o = SaveVillagers_Find((u8 *)self, &s.v);
                        if (o != NULL) {
                            ((VillagerData *)(o))->replyToLetter(q, p);
                            return ((VillagerData *)(o))->receiveLetterFrom((LetterView *)p);
                        }
                    }
                }
            }
        }
    }
    return 0;
}
}

namespace nC {
extern "C" void SaveVillagers_ClearTuneRequester(SaveVillagers *self) {
    self->tune.tuneRequested = 0;
    self->tune.tuneRequester = 0;
}
}

namespace nC {
extern "C" void SaveVillagers_SetTuneRequester(SaveVillagers *self, VillagerId *u) {
    s32 r = SaveVillagers_FindIndex((u8 *)self, u);
    if (SaveVillagers_IsValidIndex(r)) {
        self->tune.tuneRequested = 1;
        self->tune.tuneRequester = r;
    }
}
}

namespace nC {
extern "C" BOOL SaveVillagers_IsTuneRequester(SaveVillagers *self, VillagerId *u) {
    s32 r;
    if (self->tune.tuneRequested) {
        r = SaveVillagers_FindIndex((u8 *)self, u);
        if (SaveVillagers_IsValidIndex(r) && self->tune.tuneRequester == r) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}
}

namespace nC {
extern "C" void SaveVillagers_ClearTalkedToday(u8 *p) {
    s32 i;
    for (i = 0; i < 8; i++) {
        if (((VillagerId *)(void *)(((VillagerData *)(void *)(p))->getVillagerId()))->isValid()) {
            Villager_ClearTalkedToday(p);
        }
        p += sizeof(VillagerData);
    }
}
}

namespace nC {
extern "C" s32 VillagerFlea_GetMonthlyChance() {
    ClockDateTimeWords t;
    Unk_020794ac_Entry *e;
    u8 *q;
    s32 prev, i, n;
    t.words[0] = 0;
    t.words[1] = 0;
    Clock_GetDateTime(&t.dt);
    e = (Unk_020794ac_Entry *)Insect_GetSpawnTable(t.dt.month - 1);
    if (e) {
        q = e->entries;
        prev = 0;
        i = 0;
        n = e->count;
        for (; i < n; i++) {
            if (q[0] == 0x30) {
                return q[1] - prev;
            }
            prev = q[1];
            q += 2;
        }
    }
    return 0;
}
}

namespace nC {
extern "C" void SaveVillagers_PickFleaVillager(u8 *p, PlayerId *a1) {
    s32 mask, n, i, r, j, lim, bit;
    VillagerStates_Get()->fleaVillager = -1;
    if (a1) {
        if (a1->isValid()) {
            lim = VillagerFlea_GetMonthlyChance();
            mask = 0;
            n = 0;
            for (i = 0; i < 8; i++) {
                if (((VillagerId *)(void *)(((VillagerData *)(void *)(p))->getVillagerId()))->isValid() && Villager_FindMemory(p, a1) && !Villager_GetWhereabouts((VillagerData *)(p))) {
                    mask |= 1 << i;
                    mask = (u8)mask;
                    n++;
                }
                p += sizeof(VillagerData);
            }
            while (n > 0) {
                r = Random_GlobalBelow(n);
                n--;
                for (j = 0; j < 8; j++) {
                    bit = (mask >> j) & 1;
                    if (bit) {
                        if (r == 0) {
                            if (Random_GlobalBelow(100) < lim) {
                                VillagerStates_Get()->fleaVillager = j;
                                n = 0;
                            }
                            mask &= ~(1 << j);
                            mask = (u8)mask;
                            break;
                        }
                        r--;
                    }
                }
            }
        }
    }
}
}

namespace nC {
extern "C" void OutdoorSchedule_Construct(OutdoorSchedule *p) {
    p->lastReroll.words[0] = 0;
    p->lastReroll.words[1] = 0;
}
}

namespace nC {
extern "C" void OutdoorSchedule_Destruct() {}
}

namespace nC {
extern "C" void OutdoorSchedule_Clear(OutdoorSchedule *self) {
    OutdoorSchedule_ClearOrder(self, self);
    OutdoorSchedule_ClearOutdoor(self);
    self->lastReroll.words[0] = 0;
    self->lastReroll.words[1] = 0;
}
}

namespace nC {
extern "C" void OutdoorSchedule_ClearOrder(void *a, void *b) {
    MI_CpuFill8(b, 0xff, 8);
}
}

namespace nC {
extern "C" void OutdoorSchedule_CopyOrder(void *a, void *b, void *c) {
    MI_CpuCopy8(c, b, 8);
}
}

namespace nC {
extern "C" BOOL OutdoorSchedule_SetOrderEntry(u8 *self, s32 a, s32 v) {
    BOOL r = FALSE;
    if (SaveVillagers_IsValidIndex(a)) {
        self[a] = v;
        r = TRUE;
    }
    return r;
}
}

namespace nC {
extern "C" void OutdoorSchedule_AddToOrder(s8 *p, s32 x) {
    s32 i;
    s32 m1;
    if (SaveVillagers_IsValidIndex(x)) {
        i = 0;
        m1 = ~i;
        for (; i < 8; p++, i++) {
            if (*p == m1) {
                *p = x;
                break;
            }
        }
    }
}
}

namespace nC {
extern "C" void OutdoorSchedule_RemoveFromOrder(s8 *p, s32 x) {
    s32 i;
    s32 n;
    if (SaveVillagers_IsValidIndex(x)) {
        for (i = 0; i < 8; i++) {
            if (x == p[i]) {
                for (; i < 7; i = n) {
                    n = i + 1;
                    p[i] = p[n];
                }
                p[7] = ~0;
                break;
            }
        }
    }
}
}

namespace nC {
extern "C" void OutdoorSchedule_ClearOutdoor(OutdoorSchedule *self) {
    MI_CpuFill8(self->outdoorSlots, 0xff, 4);
}
}

namespace nC {
extern "C" BOOL OutdoorSchedule_SetOutdoorSlot(OutdoorSchedule *self, u32 i, s32 v) {
    if (i < 4) {
        self->outdoorSlots[i] = v;
        return TRUE;
    }
    return FALSE;
}
}

namespace nC {
extern "C" s32 OutdoorSchedule_FindOutdoorSlotImpl(OutdoorSchedule *self, s32 x) {
    s32 i;
    if (SaveVillagers_IsValidIndex(x)) {
        for (i = 0; i < 4; i++) {
            if (x == self->outdoorSlots[i]) {
                return i;
            }
        }
    }
    return ~0;
}
}

namespace nC {
extern "C" void OutdoorSchedule_RemoveOutdoor(OutdoorSchedule *self, s32 x) {
    u32 i = OutdoorSchedule_FindOutdoorSlotImpl(self, x);
    s32 n;
    if (i < 4) {
        for (n = i; n < 3; n = i) {
            i = n + 1;
            self->outdoorSlots[n] = self->outdoorSlots[i];
        }
        self->outdoorSlots[3] = ~0;
    }
}
}

namespace nC {
extern "C" void OutdoorSchedule_Remove(OutdoorSchedule *self, s32 x) {
    OutdoorSchedule_RemoveFromOrder((s8 *)self, x);
    OutdoorSchedule_RemoveOutdoor(self, x);
}
}

namespace nC {
extern "C" s32 OutdoorSchedule_FindOutdoorSlot(OutdoorSchedule *a, s32 b) {
    return OutdoorSchedule_FindOutdoorSlotImpl(a, b);
}
}

namespace nC {
extern "C" void OutdoorSchedule_InitOrder(s8 *out, u8 *p) {
    s32 i;
    s32 m1;
    i = 0;
    m1 = ~i;
    for (; i < 8; i++) {
        if (((VillagerId *)(void *)(((VillagerData *)(void *)(p))->getVillagerId()))->isValid()) {
            out[i] = i;
        } else {
            out[i] = m1;
        }
        p += sizeof(VillagerData);
    }
}
}

namespace nC {
extern "C" void OutdoorSchedule_ForceReroll(OutdoorSchedule *p) {
    p->lastReroll.words[0] = 0;
    p->lastReroll.words[1] = 0;
}
}

namespace nC {
extern "C" BOOL OutdoorSchedule_IsRerollDue(OutdoorSchedule *self, ClockDateTime *out) {
    s32 r;
    s32 c;
    if (*(u64 *)&self->lastReroll == 0 || DateTime_IsInvalid(&self->lastReroll.dt.second)) {
        return TRUE;
    }
    r = 0;
    c = DateTime_Compare(out, &self->lastReroll.dt, 0x3e);
    if (c == ~r) {
        r = DateTime_DiffMinutes(out, &self->lastReroll.dt);
    } else if (c == 1) {
        r = DateTime_DiffMinutes(&self->lastReroll.dt, out);
    }
    if (r >= 0x3c) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nC {
extern "C" void OutdoorSchedule_PickRandom(OutdoorSchedule *self, s8 *out, s32 *cnt, s8 *list, u8 *players, s32 limit) {
    u8 mask = 0;
    s32 n = mask;
    s8 *q1;
    s32 v;
    s32 id;
    s32 i;
    s32 bit;
    s32 r;
    s8 *q2;
    s32 j;
    id = SaveVillagers_GetUnk3830Index(Item_GetSaveData() + 0x8a3c);
    q1 = list;
    for (i = 0; i < 8; q1++, i++) {
        v = *q1;
        if (SaveVillagers_IsValidIndex(v) && v != id) {
            v = v * sizeof(VillagerData);
            if (Villager_CanGoOutdoors((VillagerData *)(players + v))) {
                mask |= 1 << i;
                mask = (u8)mask;
                n++;
                if (n >= 6) goto done;
            }
        }
    }
done:
    while (n > 0 && *cnt < limit) {
        r = Random_GlobalBelow(n);
        q2 = list;
        for (j = 0; j < 8; q2++, j++) {
            v = *q2;
            bit = mask;
            bit >>= j;
            bit &= 1;
            if (bit) {
                if (r == 0) {
                    out[*cnt] = v;
                    *cnt = *cnt + 1;
                    *q2 = ~0;
                    mask &= ~(1 << j);
                    mask = (u8)mask;
                    break;
                }
                r--;
            }
        }
        n--;
    }
}
}

namespace nC {
extern "C" void OutdoorSchedule_AssignIndoor(OutdoorSchedule *self, s8 *list, s32 *cnt, VillagerState *slots) {
    s32 i;
    s32 v;
    VillagerState *e;
    s32 z = 0;
    s32 m1 = ~z;
    for (i = 0; i < 8; list++, i++) {
        v = *list;
        if (SaveVillagers_IsValidIndex(v) && OutdoorSchedule_SetOrderEntry((u8 *)self, *cnt, v)) {
            *cnt = *cnt + 1;
            e = slots + v;
            VillagerState_SetPresence(e, 1);
            VillagerState_SetRole(e, z);
            *list = m1;
        }
    }
}
}

namespace nC {
extern "C" void OutdoorSchedule_AssignOutdoor(OutdoorSchedule *self, s8 *list, s32 *cnt, VillagerState *slots, s32 n) {
    s32 i;
    s32 v;
    VillagerState *e;
    s32 z = 0;
    for (i = 0; i < n; list++, i++) {
        v = *list;
        if (OutdoorSchedule_SetOrderEntry((u8 *)self, *cnt, v)) {
            *cnt = *cnt + 1;
            e = slots + v;
            VillagerState_SetPresence(e, z);
            VillagerState_SetRole(e, 1);
            OutdoorSchedule_SetOutdoorSlot(self, i, v);
        }
    }
}
}

namespace nC {
extern "C" void OutdoorSchedule_AddBirthdayVisitor(OutdoorSchedule *self, s8 *out, s32 *cnt, s8 *list, u8 *players) {
    s32 id = VillagerStates_GetBirthdayVisitor();
    s32 i;
    s32 v;
    s32 z = 0;
    s32 m1;
    if (SaveVillagers_IsValidIndex(id)) {
        i = 0;
        m1 = ~i;
        for (; i < 8; list++, i++) {
            v = *list;
            if (SaveVillagers_IsValidIndex(v) && v == id) {
                if (((VillagerId *)(void *)(((VillagerData *)(void *)(players + v * sizeof(VillagerData)))->getVillagerId()))->isValid()) {
                    out[*cnt] = v;
                    *cnt = *cnt + 1;
                }
                *list = m1;
            }
        }
    }
}
}

namespace nC {
extern "C" void OutdoorSchedule_ApplySleep(OutdoorSchedule *self, u8 *p, ClockDateTime *x) {
    VillagerState *s;
    s32 i;
    s32 z = 0;
    s32 r;
    BOOL v;
    VillagerId *t;
    PlayerData *o = PlayerData_GetCurrent();
    if (o) {
        r = o->testFlag(1);
    } else {
        r = 0;
    }
    if (r) {
        v = TRUE;
    } else {
        v = FALSE;
    }
    s = VillagerStates_Get()->entries;
    for (i = 0; i < 8; i++) {
        t = ((VillagerData *)p)->getVillagerId();
        if (t->isValid()) {
            if (!v) {
                if (Personality_IsAsleep(VillagerId_GetPersonality(t), x)) {
                    VillagerState_SetPresence(s, 2);
                    VillagerState_SetRole(s, z);
                }
            }
        } else {
            VillagerState_SetPresence(s, 3);
            VillagerState_SetRole(s, 7);
        }
        p += sizeof(VillagerData);
        s++;
    }
}
}

namespace nC {
extern "C" void OutdoorSchedule_Reroll(OutdoorSchedule *self, u8 *p) {
    s8 l1[8];
    s8 l2[8];
    s32 a, c, n, b, i;
    VillagerState *slots;
    slots = VillagerStates_Get()->entries;
    a = 0;
    b = Town_GetMaxOutdoorVillagers();
    n = SaveVillagers_CountImpl(p);
    c = 0;
    for (i = 0; i < 8; i++) {
        VillagerState_SetPresence(&slots[i], 3);
    }
    OutdoorSchedule_CopyOrder(self, l1, self);
    OutdoorSchedule_ClearOrder(self, self);
    OutdoorSchedule_ClearOrder(self, l2);
    n = n * 3;
    if (b > (n >> 2)) {
        b = n >> 2;
    }
    OutdoorSchedule_ClearOutdoor(self);
    OutdoorSchedule_AddBirthdayVisitor(self, l2, &a, l1, p);
    OutdoorSchedule_PickRandom(self, l2, &a, l1, p, b);
    OutdoorSchedule_AssignIndoor(self, l1, &c, slots);
    OutdoorSchedule_AssignOutdoor(self, l2, &c, slots, a);
}
}

namespace nC {
extern "C" void OutdoorSchedule_Apply(OutdoorSchedule *self, u8 *p) {
    VillagerState *s = VillagerStates_Get()->entries;
    s32 i;
    s32 z0 = 0;
    s32 z1 = 0;
    for (i = 0; i < 8; i++) {
        if (((VillagerId *)(void *)(((VillagerData *)(void *)(p))->getVillagerId()))->isValid()) {
            if (OutdoorSchedule_FindOutdoorSlotImpl(self, i) != ~0) {
                VillagerState_SetPresence(s, z1);
                VillagerState_SetRole(s, 1);
            } else {
                VillagerState_SetPresence(s, 1);
                VillagerState_SetRole(s, z0);
            }
        } else {
            VillagerState_SetPresence(s, 3);
            VillagerState_SetRole(s, 7);
        }
        p += sizeof(VillagerData);
        s++;
    }
}
}

namespace nC {
extern "C" void OutdoorSchedule_Update(OutdoorSchedule *self, u8 *p, s32 keep) {
    ClockDateTimeWords t;
    VillagerState *slots;
    s32 i;
    t.words[0] = 0;
    t.words[1] = 0;
    slots = VillagerStates_Get()->entries;
    for (i = 0; i < 8; i++) {
        VillagerState_SetPresence(&slots[i], 3);
    }
    Clock_GetDateTime(&t.dt);
    if (OutdoorSchedule_IsRerollDue(self, &t.dt)) {
        OutdoorSchedule_Reroll(self, p);
        if (keep) {
            MI_CpuCopy8(&t, &self->lastReroll, 8);
        }
    } else {
        OutdoorSchedule_Apply(self, p);
    }
    OutdoorSchedule_ApplySleep(self, p, &t.dt);
}
}

namespace nC {
extern "C" void VillagerRelations_Construct() {}
}

namespace nC {
extern "C" void VillagerRelations_Destruct() {}
}

namespace nC {
extern "C" void VillagerRelations_Clear(void *p) {
    MI_CpuFill8(p, 0, 0x1c);
}
}

namespace nC {
extern "C" BOOL VillagerRelations_IsValidIndex(void *a, u32 i) {
    if (i < 0x1c) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nC {
extern "C" s32 VillagerRelations_PairIndex(s8 *a, s32 b, s32 c) {
    s32 r = 0;
    s32 lo = b;
    s32 i;
    if (b > c) {
        lo = c;
        c = b;
    }
    for (i = 0; i < lo; i++) {
        r += 7 - i;
    }
    return r + (c - lo - 1);
}
}

namespace nC {
extern "C" void VillagerRelations_ResetSlot(s8 *a, s32 x) {
    s32 i;
    s32 t;
    if (SaveVillagers_IsValidIndex(x)) {
        for (i = 0; i < 8; i++) {
            if (i != x) {
                t = VillagerRelations_PairIndex(a, x, i);
                if (VillagerRelations_IsValidIndex(a, t)) {
                    a[t] = 0;
                }
            }
        }
    }
}
}

namespace nC {
extern "C" void VillagerRelations_AddAt(s8 *a, s32 i, s32 d) {
    if (VillagerRelations_IsValidIndex(a, i)) {
        s32 t = d + a[i];
        s8 *p = &a[i];
        if (t > 127) {
            t = 127;
        } else if (t < -128) {
            t = -128;
        }
        *p = t;
    }
}
}

namespace nB {
extern "C" void VillagerRelations_Add(s8 *a, s32 p, s32 q, s32 r) {
    if (SaveVillagers_IsValidIndex(p) && SaveVillagers_IsValidIndex(q)) {
        VillagerRelations_AddAt(a, VillagerRelations_PairIndex(a, p, q), r);
    }
}
}

namespace nB {
extern "C" s32 VillagerRelations_GetStored(s8 *a, s32 p, s32 q) {
    s32 r = 0x80000000;
    if (SaveVillagers_IsValidIndex(p) && SaveVillagers_IsValidIndex(q)) {
        s32 k = VillagerRelations_PairIndex(a, p, q);
        if (VillagerRelations_IsValidIndex(a, k)) {
            r = ((s8 *)a)[k];
        }
    }
    return r;
}
}

namespace nB {
extern "C" s32 Relation_GetPersonalityScore(void *a, void *p, void *q) {
    s32 r = 0;
    if (((VillagerId *)(p))->isValid() && ((VillagerId *)(q))->isValid()) {
        u32 x = VillagerId_GetPersonality((VillagerId *)p);
        u32 y = VillagerId_GetPersonality((VillagerId *)q);
        r = sPersonalityCompat[x][y];
    }
    return r;
}
}

namespace nB {
extern "C" u32 Relation_GetStarElementScore(void *a, void *p, void *q) {
    u8 x = Villager_GetStarSign((VillagerData *)p) & 3;
    u8 y = Villager_GetStarSign((VillagerData *)q) & 3;
    return sStarElementCompat[x][y];
}
}

namespace nB {
extern "C" u32 Relation_GetSpeciesScore(void *a, void *p, void *q) {
    u32 x = Villager_GetAnimalKind((VillagerData *)p);
    u32 y = Villager_GetAnimalKind((VillagerData *)q);
    const u8 (*t)[2];
    s32 i;
    if (x == y) {
        return 0x40;
    }
    t = sGoodSpeciesPairs;
    for (i = 0; i < 7; t++, i++) {
        u32 a0 = (*t)[0];
        if ((a0 == x && (*t)[1] == y) || ((*t)[1] == x && a0 == y)) {
            return 0x80;
        }
    }
    t = sBadSpeciesPairs;
    for (i = 0; i < 4; t++, i++) {
        u32 a0 = (*t)[0];
        if ((a0 == x && (*t)[1] == y) || ((*t)[1] == x && a0 == y)) {
            return 0;
        }
    }
    return 0x20;
}
}

namespace nB {
extern "C" u32 Relation_GetInfoBonus(void *a, void *p, void *q) {
    const u8 *x = Villager_GetInfo((VillagerData *)p);
    const u8 *y = Villager_GetInfo((VillagerData *)q);
    u32 r = 0;
    if (x != NULL && y != NULL) {
        r = 0x3f;
    }
    return r;
}
}

namespace nB {
extern "C" u32 Relation_GetInfo04Diff(void *a, void *p, void *q) {
    const u8 *x = Villager_GetInfo((VillagerData *)p);
    const u8 *y = Villager_GetInfo((VillagerData *)q);
    u32 r = 0;
    if (x != NULL && y != NULL) {
        u32 yb = y[4];
        u32 xb = x[4];
        if (xb > yb) {
            r = xb - yb;
        } else {
            r = yb - xb;
        }
    }
    return r;
}
}

namespace nB {
extern "C" s32 Relation_CalcBaseScore(void *a, void *p, void *q) {
    s32 r = 0;
    if (p != NULL && ((VillagerId *)(((VillagerData *)(p))->getVillagerId()))->isValid() && q != NULL && ((VillagerId *)(((VillagerData *)(q))->getVillagerId()))->isValid()) {
        VillagerId *x = ((VillagerData *)(p))->getVillagerId();
        VillagerId *y = ((VillagerData *)(q))->getVillagerId();
        r = Relation_GetPersonalityScore(a, x, y);
        r += Relation_GetStarElementScore(a, p, q);
        r += Relation_GetSpeciesScore(a, p, q);
        r += Relation_GetInfoBonus(a, p, q);
        if (r < 200) {
            r -= Relation_GetInfo04Diff(a, p, q);
            if (r < 0) {
                r = -r;
            }
        }
    }
    return r;
}
}

namespace nB {
extern "C" s32 VillagerRelations_GetScore(void *a, s32 b, s32 c) {
    void *d = gSaveVillagers;
    void *r5 = SaveVillagers_Get(d, b);
    void *r4 = SaveVillagers_Get(d, c);
    s32 r = 0;
    if (r5 != NULL && ((VillagerId *)(((VillagerData *)(r5))->getVillagerId()))->isValid() && r4 != NULL && ((VillagerId *)(((VillagerData *)(r4))->getVillagerId()))->isValid()) {
        r = VillagerRelations_GetStored((s8 *)a, b, c);
        s32 t = Relation_CalcBaseScore(a, r5, r4);
        r = r * 5;
        r = t + (r >> 1);
    }
    return r;
}
}

namespace nB {
extern "C" void *VillagerTransfer_ConstructVillager(void *p) {
    new (p) VillagerData();
    return p;
}
}

namespace nB {
extern "C" void *VillagerTransfer_DestructVillager(void *p) {
    ((VillagerData *)(p))->~VillagerData();
    return p;
}
}

namespace nB {
extern "C" void *func_020789a8(void *p) { return p; }
}

namespace nB {
extern "C" BOOL Villager_IsActorInBox(u16 *h, s32 x0, s32 x1, s32 z0, s32 z1) {
    VillagerActor *o = (VillagerActor *)NpcRegistry_FindVillagerByHandle(h);
    if (o != NULL && o->isPickable()) {
        s32 *pos = &o->position.x;
        BOOL result = FALSE;
        BOOL b = FALSE;
        BOOL a = FALSE;
        if (o->position.x > x0 && o->position.x < x1) {
            a = TRUE;
        }
        if (a) {
            if (pos[2] > z0) {
                b = TRUE;
            }
        }
        if (b) {
            if (pos[2] < z1) {
                result = TRUE;
            }
        }
        return result;
    }
    return FALSE;
}
}

namespace nB {
extern "C" void SaveVillagers_NotifyPlayerActivity(u32 kind, VecFx32 *p) {
    if (gSaveVillagers != 0) {
        s32 b[4];
        ClockDateTimeRaw t;
        s32 z1;
        u16 h;
        s32 i;
        b[0] = 0;
        t.v[0] = 0;
        t.v[1] = 0;
        b[1] = 0;
        b[2] = 0;
        z1 = 0;
        h = 0xfff1;
        if (p != NULL) {
            b[0] = p->x - 0x10000;
            b[1] = p->x + 0x10000;
            b[2] = p->z - 0x1a000;
            z1 = p->z + 0xa000;
        }
        Clock_GetDateTime(&t.dt);
        for (i = 0; i < 8; i++) {
            VillagerData *o;
            b[3] = 1;
            o = SaveVillagers_Get(gSaveVillagers, i);
            if (o != NULL) {
                if (((VillagerId *)(((VillagerData *)(o))->getVillagerId()))->isValid()) {
                    if (VillagerPlanBlock_GetPlan(Villager_GetPlan(o))->isTrendOlderThanWeek((ClockDateTime *)&t)) {
                        if (p != NULL) {
                            h = (i & 0xfff) | 0xe000;
                            if (Villager_IsActorInBox(&h, b[0], b[1], b[2], z1)) {
                                b[3] = 2;
                            }
                        }
                        Villager_RecordPlayerActivity(o, kind, b[3]);
                    }
                }
            }
        }
        VillagerStates_Get()->idleFrames = 0;
    }
}
}

namespace nB {
extern "C" void VillagerTrend_OnFishCaught(VecFx32 *p) {
    if (!((CommManager *)(gCommManager))->isOnline()) {
        SaveVillagers_NotifyPlayerActivity(1, p);
    }
}
}

namespace nB {
extern "C" void VillagerTrend_OnInsectCaught(VecFx32 *p) {
    if (!((CommManager *)(gCommManager))->isOnline()) {
        SaveVillagers_NotifyPlayerActivity(0, p);
    }
}
}

namespace nB {
extern "C" void VillagerTrend_OnItemDug(VecFx32 *p) {
    if (!((CommManager *)(gCommManager))->isOnline()) {
        SaveVillagers_NotifyPlayerActivity(2, p);
    }
}
}

namespace nB {
extern "C" void VillagerTrend_OnClothesBought() {
    if (!((CommManager *)(gCommManager))->isOnline()) {
        SaveVillagers_NotifyPlayerActivity(3, NULL);
    }
}
}

namespace nB {
extern "C" void VillagerTrend_OnFurnitureBought() {
    if (!((CommManager *)(gCommManager))->isOnline()) {
        SaveVillagers_NotifyPlayerActivity(4, NULL);
    }
}
}

namespace nB {
extern "C" void VillagerTrend_NotifyUnk5(VecFx32 *p) {
    if (!((CommManager *)(gCommManager))->isOnline()) {
        SaveVillagers_NotifyPlayerActivity(5, p);
    }
}
}

namespace nB {
extern "C" BOOL TownMap_HasAttr8AtPos(VecFx32 *p) {
    BlockMap *g = gSceneBlockMap;
    if (g != NULL) {
        MapBlock *c = Unk_02078738_GetCell(g, p->x >> 17, p->z >> 17);
        if (c != NULL) {
            if (MapBlock_HasAllAttr(c, 8)) {
                return TRUE;
            }
        }
        return FALSE;
    }
    return FALSE;
}
}

namespace nB {
extern "C" void VillagerTrend_NotifyUnk6(VecFx32 *p) {
    if (!((CommManager *)(gCommManager))->isOnline()) {
        if (TownMap_HasAttr8AtPos(p)) {
            SaveVillagers_NotifyPlayerActivity(6, p);
        }
    }
}
}

namespace nB {
extern "C" void VillagerTrend_NotifyIdle() {
    if (!((CommManager *)(gCommManager))->isOnline()) {
        SaveVillagers_NotifyPlayerActivity(7, NULL);
    }
}
}

namespace nB {
extern "C" void VillagerTrend_TickIdle() {
    if (Scene_InTown()) {
        if (!((CommManager *)(gCommManager))->isOnline()) {
            if (VillagerStates_Get()->idleFrames > 0x4b0) {
                VillagerTrend_NotifyIdle();
            }
            VillagerStates_Get()->idleFrames++;
        }
    }
}
}

VillagerState::VillagerState() {
    using namespace nB;
    TrendScores_Construct(trendScores);
    heldItem = 0xfff1;
    TalkRepeat_Construct(&talkRepeat);
}

VillagerState::~VillagerState() {
    using namespace nB;
    TalkRepeat_Destruct(&talkRepeat);
    TrendScores_Destruct();
}

namespace nB {
extern "C" void VillagerState_Init(VillagerState *e) {
    MI_CpuFill8(e, 0, 0x2c);
    e->role = 0;
    e->presence = 3;
    e->errand.clear();
    TrendScores_Clear(e->trendScores);
    e->mood = 5;
    e->activity = 0xc;
    e->roomScore = 0;
    e->roomBonusFlags = 0;
    VillagerState_ClearHeldItem(e);
}
}

namespace nB {
extern "C" u32 VillagerState_GetRole(VillagerState *e) {
    CommManager *o = (CommManager *)gCommManager;
    if (((CommManager *)(o))->isSlotActive(o->myAid) && e->role != 7) {
        return 0;
    }
    return e->role;
}
}

namespace nB {
extern "C" void VillagerState_SetRole(VillagerState *e, u32 v) { e->role = v; }
}

namespace nB {
extern "C" void VillagerState_ResetRole(VillagerState *e) {
    switch (e->role) {
    case 0:
    case 1:
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        if (VillagerState_GetPresence(e) == 0) {
            e->role = 1;
        } else {
            e->role = 0;
        }
        break;
    }
}
}

namespace nB {
extern "C" u32 VillagerState_GetPresence(VillagerState *e) {
    CommManager *o = (CommManager *)gCommManager;
    if (((CommManager *)(o))->isSlotActive(o->myAid) && e->presence == 0) {
        return 1;
    }
    return e->presence;
}
}

namespace nB {
extern "C" void VillagerState_SetPresence(VillagerState *e, u32 v) { e->presence = v; }
}

namespace nB {
extern "C" ErrandRecord *VillagerState_GetErrand(VillagerState *e) { return &e->errand; }
}

namespace nB {
extern "C" u32 VillagerState_GetActivity(VillagerState *e) { return e->activity; }
}

namespace nB {
extern "C" void VillagerState_SetActivity(VillagerState *e, u32 v) { e->activity = v; }
}

namespace nB {
extern "C" u32 VillagerState_GetMood(VillagerState *e) { return e->mood; }
}

namespace nB {
extern "C" void VillagerState_SetMood(VillagerState *e, u32 v) { e->mood = v; }
}

namespace nB {
extern "C" void VillagerState_AddMoodTimer(VillagerState *e, s32 v) {
    s32 s = e->moodTimer + v;
    if (s >= 0xffff) {
        e->moodTimer = 0xffff;
        return;
    }
    e->moodTimer = s;
}
}

namespace nB {
extern "C" void VillagerState_SetMoodTimer(VillagerState *e, u16 v) { e->moodTimer = v; }
}

namespace nB {
extern "C" u32 VillagerState_GetMoodTimer(VillagerState *e) { return e->moodTimer; }
}

namespace nB {
extern "C" void VillagerState_TickMoodTimer(VillagerState *e) {
    if (e->moodTimer != 0) {
        e->moodTimer = e->moodTimer - (TICK_STEP_ENDS() ? 1 : 0);
    }
}
}

namespace nB {
extern "C" void VillagerState_SetUnk1dBit1(VillagerState *e) {
    if (!Scene_InVillagerHouse()) {
        e->flags |= 2;
    }
}
}

namespace nB {
extern "C" void VillagerState_DoubleTalkUrge(VillagerState *e) {
    s32 v = e->talkUrge << 1;
    if (v > 32) {
        v = 32;
    }
    e->talkUrge = v;
}
}

namespace nB {
extern "C" u16 *VillagerState_GetHeldItem(VillagerState *e) { return &e->heldItem; }
}

namespace nB {
extern "C" void VillagerState_SetHeldItem(VillagerState *e, u16 *p) { e->heldItem = *p; }
}

namespace nB {
extern "C" void VillagerState_ClearHeldItem(VillagerState *e) { e->heldItem = 0xfff1; }
}

namespace nB {
extern "C" TalkRepeat *VillagerState_GetTalkRepeat(VillagerState *e) { return &e->talkRepeat; }
}

namespace nB {
extern "C" void TalkRepeat_Construct(TalkRepeat *t) {}
}

namespace nB {
extern "C" void TalkRepeat_Destruct(TalkRepeat *t) {}
}

namespace nB {
extern "C" void TalkRepeat_Reset(TalkRepeat *t) {
    t->grace = 0;
    t->window = 0;
    t->count = 0;
}
}

namespace nB {
extern "C" void TalkRepeat_Tick(TalkRepeat *t, s32 v) {
    if (v == 0) {
        if (t->grace != 0) {
            t->grace = t->grace - 1;
        } else if (t->window != 0) {
            t->window = t->window - 1;
        }
        if (t->window == 0) {
            t->count = 0;
        }
    }
}
}

namespace nB {
extern "C" void TalkRepeat_Count(TalkRepeat *t) {
    if (t->grace != 0) {
        t->count = t->count + 1;
    }
}
}

namespace nB {
extern "C" void TalkRepeat_StartWindow(TalkRepeat *t) {
    t->grace = 40;
    t->window = 0x4b0;
}
}

namespace nB {
extern "C" s32 TalkRepeat_GetLevel(TalkRepeat *t) {
    if (Unk_02078384_IsZero(gFieldSceneKind)) {
        u32 v = t->count;
        if (v >= 10) {
            return 2;
        }
        if (v >= 7) {
            return 1;
        }
    }
    return 0;
}
}

namespace nB {
extern "C" BOOL VillagerStates_IsValidIndex(s32 i) {
    if (i >= 0 && i < 8) {
        return TRUE;
    }
    return FALSE;
}
}

namespace nB {
extern "C" void VillagerStateTable_Init(VillagerStateTable *m) {
    s32 i;
    for (i = 0; i < 8; i++) {
        VillagerState_Init(&m->entries[i]);
    }
    m->fleaVillager = -1;
    m->greeter = 0;
    m->birthdayHost = -1;
    m->birthdayGuest = -1;
    m->fleaMarketBuyer = -1;
    m->idleFrames = 0;
    m->birthdayVisitor = -1;
}
}

namespace nB {
extern "C" VillagerStateTable *VillagerStates_Get() { return &gVillagerStates; }
}

namespace nB {
extern "C" VillagerState *VillagerStateTable_GetEntry(VillagerStateTable *m, s32 i) {
    VillagerState *r = NULL;
    if (VillagerStates_IsValidIndex(i)) {
        r = &m->entries[i];
    }
    return r;
}
}

namespace nB {
extern "C" void VillagerStateTable_Destroy() {}
}

namespace nB {
extern "C" void VillagerStateTable_ResetRuntime(VillagerState *e) {
    s32 i = 0;
    s32 z1 = 0;
    s32 z2 = 0;
    s32 z3 = 0;
    for (; i < 8; e++, i++) {
        VillagerState_SetRole(e, z1);
        e->flags &= ~1;
        VillagerState_SetMood(e, z2);
        VillagerState_SetMoodTimer(e, z3);
        e->flags &= ~4;
        TalkRepeat_Reset(VillagerState_GetTalkRepeat(e));
    }
}
}

namespace nA {
extern "C" void VillagerStates_Init() {
    VillagerStateTable_Init(VillagerStates_Get());
}
}

namespace nA {
extern "C" void VillagerStates_Destroy() {
    VillagerStateTable_Destroy();
}
}

namespace nA {
extern "C" void VillagerStates_ResetRuntime() {
    VillagerStateTable_ResetRuntime(VillagerStates_Get()->entries);
}
}

namespace nA {
extern "C" void VillagerStates_ClearUnk1dBit0() {
    VillagerState *e = VillagerStates_Get()->entries;
    s32 i;
    for (i = 0; i < 8; e++, i++) {
        e->flags &= ~1;
    }
}
}

namespace nA {
extern "C" void VillagerStates_ClearUnk1dBit2() {
    VillagerState *e = VillagerStates_Get()->entries;
    s32 i;
    for (i = 0; i < 8; e++, i++) {
        e->flags &= ~4;
    }
}
}

namespace nA {
extern "C" void VillagerStates_ResetTalkRepeats() {
    VillagerState *p = VillagerStates_Get()->entries;
    s32 i;
    for (i = 0; i < 8; p++, i++) {
        TalkRepeat_Reset(VillagerState_GetTalkRepeat(p));
    }
}
}

namespace nA {
extern "C" void VillagerStates_ClearFleaVillager() {
    VillagerStates_Get()->fleaVillager = -1;
}
}

namespace nA {
extern "C" void VillagerStates_SetBirthdayHost(s32 v) {
    VillagerStates_Get()->birthdayHost = v;
}
}

namespace nA {
extern "C" s32 VillagerStates_GetBirthdayHost() {
    return VillagerStates_Get()->birthdayHost;
}
}

namespace nA {
extern "C" void VillagerStates_SetBirthdayGuest(s32 v) {
    VillagerStates_Get()->birthdayGuest = v;
}
}

namespace nA {
extern "C" s32 VillagerStates_GetBirthdayGuest() {
    return VillagerStates_Get()->birthdayGuest;
}
}

namespace nA {
extern "C" void VillagerStates_SetBirthdayVisitor(s32 v) {
    VillagerStates_Get()->birthdayVisitor = v;
}
}

namespace nA {
extern "C" s32 VillagerStates_GetBirthdayVisitor() {
    return VillagerStates_Get()->birthdayVisitor;
}
}

namespace nA {
extern "C" void VillagerStates_SetFleaMarketBuyer(s32 v) {
    VillagerStates_Get()->fleaMarketBuyer = v;
}
}

namespace nA {
extern "C" s32 VillagerStates_GetFleaMarketBuyer() {
    return VillagerStates_Get()->fleaMarketBuyer;
}
}

namespace nA {
extern "C" void VillagerStates_ResetIdleFrames() {
    VillagerStates_Get()->idleFrames = 0;
}
}

namespace nA {
extern "C" void SaveVillagers_OnNewDay(u8 *a, void *b) {
    s32 z1 = 0;
    s32 z2 = 0;
    s32 i;
    for (i = 0; i < 8; a += sizeof(VillagerData), i++) {
        if (((VillagerId *)(((VillagerData *)(a))->getVillagerId()))->isValid()) {
            s32 j;
            VillagerMemory *e;
            if (Villager_GetResidentStatus((VillagerData *)a) == 3) {
                Villager_PickShownFurniture((VillagerData *)(a));
            }
            e = Villager_GetMemory(((VillagerData *)a)->memories, z1);
            for (j = z2; j < 8; e++, j++) {
                if (VillagerMemory_IsUsed(e)) {
                    ((VillagerMemory *)(e))->clearTalkedToday();
                    ((VillagerMemory *)(e))->clearPartyGiftReceived();
                    ((VillagerMemory *)(e))->clearPartyGreeted();
                    ((VillagerMemory *)(e))->clearBirthdayLetterSent();
                    ((VillagerMemory *)(e))->clearNewYearLetterSent();
                    ((VillagerMemory *)(e))->clearFleaMarketVisited();
                    ((VillagerMemory *)(e))->clearFortuneGreeting();
                }
            }
            ((VillagerData *)(a))->sendBirthdayLetters((void *)(b));
            ((VillagerData *)(a))->sendNewYearLetters((void *)(b));
        }
    }
}
}

namespace nA {
extern "C" void *Field_FindPlayerAtUnit(s32 x, s32 y) {
    void *result = NULL;
    s32 ax = 0;
    s32 ay = 0;
    s32 i;
    for (i = 0; i < 4; i++) {
        void *o = PlayerActor_GetBodyPos(i);
        if (o != 0) {
            FieldPos_ToUnit(&ax, &ay, (VecFx32 *)o);
            if (ax == x && ay == y) {
                result = PlayerActor_GetCharacter(i);
                break;
            }
        }
    }
    return result;
}
}

namespace nA {
extern "C" BOOL Field_IsUnitOccupied(s32 a, s32 b) {
    BOOL r = Field_FindPlayerAtUnit(a, b) != NULL;
    if (r == 0) {
        r = NpcRegistry_FindAt(a, b) != NULL;
    }
    return r;
}
}

namespace nA {
extern "C" BOOL TownMap_IsUnitWalkable(s32 x, s32 y, BlockMap *grid) {
    BOOL result = FALSE;
    if (grid == 0) {
        grid = gSceneBlockMap;
    }
    if (grid != 0 && grid->isWalkable(x, y)) {
        s32 hx = x >> 4;
        s32 hy = y >> 4;
        u16 *c = (u16 *)BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), 0);
        if (c != 0) {
            u32 v = *c;
            if (v == 0xfff1) goto yes;
            if (Item_IsNormalItem(c)) goto yes;
            if (Unk_02077f68_R(c, 0xa7, 0xc6)) goto yes;
            if (Unk_02077d58_IsZero(gFieldSceneKind)) {
                if (Item_IsFurniture(c)) goto yes;
            }
            if (Item_IsTreeStage0(c)) goto yes;
            if (Unk_02077f68_C2(c)) goto yes;
            if (Unk_02077f68_C9(c)) {
            yes:
                if (!Field_IsUnitOccupied(x, y)) {
                    result = TRUE;
                }
            }
        }
    }
    return result;
}
}

namespace nA {
extern "C" BOOL TownMap_IsPosWalkable(VecFx32 *a, BlockMap *grid) {
    s32 x = 0;
    s32 y = 0;
    FieldPos_ToUnit(&x, &y, a);
    return TownMap_IsUnitWalkable(x, y, grid);
}
}

namespace nA {
extern "C" BOOL TownMap_FindBuildingAbove(s32 x, s32 y, s32 h, s32 *px, s32 *py) {
    s32 i;
    BlockMap *grid = gSceneBlockMap;
    if (grid != 0 && h >= 0) {
        for (i = 0; i <= h; i++) {
            s32 hx, hy, yy;
            long xx;
            u16 *c;
            yy = y - (i + 1);
            xx = x;
            hx = xx >> 4;
            hy = yy >> 4;
            c = (u16 *)BlockMap_GetItemPtr(grid, hx, hy, xx - (hx << 4), yy - (hy << 4), 0);
            if (c != 0) {
                BOOL r = FALSE;
                u32 v = *c;
                if (v >= 0x5000 && v <= 0x5021) {
                    r = TRUE;
                }
                if (r) {
                    if (px != 0 && py != 0) {
                        *px = x;
                        y -= i + 1;
                        *py = y;
                    }
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}
}

namespace nA {
extern "C" BOOL TownMap_FindBuildingAbovePos(VecFx32 *a, s32 h, s32 *px, s32 *py) {
    s32 x = 0;
    s32 y = 0;
    FieldPos_ToUnit(&x, &y, a);
    return TownMap_FindBuildingAbove(x, y, h, px, py);
}
}

namespace nA {
extern "C" void NpcHeapPools_CreateAll() {
    NpcModelHeap_Create(gCurrentHeap);
    NpcTexPatBufs_Create(gCurrentHeap);
    VillagerAnimHeaps_Create(gCurrentHeap);
    SpNpcAnimHeaps_Create(gCurrentHeap);
}
}

namespace nA {
extern "C" void NpcHeapPools_DestroyAll() {
    NpcModelHeap_Destroy();
    NpcTexPatBufs_Destroy();
    VillagerAnimHeaps_Destroy();
    SpNpcAnimHeaps_Destroy();
}
}

namespace nA {
extern "C" s32 NpcModelHeap_GetVillagerModelSize() {
    return 0x2bcc;
}
}

namespace nA {
extern "C" s32 NpcModelHeap_GetSpNpcModelSize() {
    return 0x31ec;
}
}

NpcTexPatBufPool::NpcTexPatBufPool() {
    s32 i;
    for (i = 0; i < 5; i++) {
        p[i] = 0;
    }
}

NpcTexPatBufPool::~NpcTexPatBufPool() {}

namespace nA {
extern "C" void NpcTexPatBufs_Create(void *parent) {
    NpcTexPatBufHeap_Create(parent);
    NpcTexPatBufPool_Alloc(sNpcTexPatBufPool.p);
    if (gNpcTexPatBufHeap != 0) {
        ((Heap *)(gNpcTexPatBufHeap))->adjust();
    }
}
}

namespace nA {
extern "C" void NpcTexPatBufs_Destroy() {
    NpcTexPatBufPool_Free(sNpcTexPatBufPool.p);
    NpcTexPatBufHeap_Destroy();
}
}

namespace nA {
extern "C" void *NpcTexPatBufPool_Get(void **p, s32 i) {
    return p[i];
}
}

namespace nA {
extern "C" void NpcTexPatBufPool_Alloc(void **p) {
    void *heap = gNpcTexPatBufHeap;
    s32 t = Unk_02077d58_Count();
    s32 n = t + NpcSpawn_GetSpNpcSlotCount();
    s32 i;
    for (i = 0; i < n; i++) {
        p[i] = Heap_AllocAligned(heap, 0x2f88, 4);
    }
}
}

namespace nA {
extern "C" void NpcTexPatBufPool_Free(void **p) {
    void *heap = gNpcTexPatBufHeap;
    s32 i;
    for (i = 0; i < 5; i++) {
        p[i] = 0;
    }
    if (heap != 0) {
        ((Heap *)(heap))->freeAll();
    }
}
}

VillagerAnimHeapPool::VillagerAnimHeapPool() {
    s32 i;
    for (i = 0; i < 8; i++) {
        p[i] = 0;
    }
}

VillagerAnimHeapPool::~VillagerAnimHeapPool() {}

namespace nA {
extern "C" void VillagerAnimHeaps_Create(void *parent) {
    VillagerAnimPoolHeap_Create(parent);
    VillagerAnimHeapPool_Alloc(sVillagerAnimHeapPool.p);
    if (gVillagerAnimPoolHeap != 0) {
        ((Heap *)(gVillagerAnimPoolHeap))->adjust();
    }
}
}

namespace nA {
extern "C" void VillagerAnimHeaps_Destroy() {
    VillagerAnimHeapPool_Free(sVillagerAnimHeapPool.p);
    VillagerAnimPoolHeap_Destroy();
}
}

namespace nA {
extern "C" void *VillagerAnimHeapPool_Get(void **p, s32 i) {
    return p[i];
}
}

namespace nA {
extern "C" void VillagerAnimHeapPool_Alloc(void **p) {
    void *heap = gVillagerAnimPoolHeap;
    s32 i;
    for (i = 0; i < 8; i++) {
        p[i] = FrameHeap_Create(0x7ac, heap);
    }
}
}

namespace nA {
extern "C" void VillagerAnimHeapPool_Free(void **p) {
    void *heap = gVillagerAnimPoolHeap;
    s32 i;
    for (i = 0; i < 8; i++) {
        if (p[i] != 0) {
            ((Heap *)(p[i]))->freeAll();
            p[i] = NULL;
        }
    }
    if (heap != 0) {
        ((Heap *)(heap))->freeAll();
    }
}
}

SpNpcAnimHeapPool::SpNpcAnimHeapPool() {
    s32 i;
    for (i = 0; i < 4; i++) {
        p[i] = 0;
    }
}

SpNpcAnimHeapPool::~SpNpcAnimHeapPool() {}

namespace nA {
extern "C" void SpNpcAnimHeaps_Create(void *parent) {
    SpNpcAnimPoolHeap_Create(parent);
    SpNpcAnimHeapPool_Alloc(sSpNpcAnimHeapPool.p);
    if (gSpNpcAnimPoolHeap != 0) {
        ((Heap *)(gSpNpcAnimPoolHeap))->adjust();
    }
}
}

namespace nA {
extern "C" void SpNpcAnimHeaps_Destroy() {
    SpNpcAnimHeapPool_Free(sSpNpcAnimHeapPool.p);
    SpNpcAnimPoolHeap_Destroy();
}
}

namespace nA {
extern "C" void *SpNpcAnimHeapPool_Get(void **p, s32 i) {
    return p[i];
}
}

namespace nA {
extern "C" void SpNpcAnimHeapPool_Alloc(void **p) {
    void *heap = gSpNpcAnimPoolHeap;
    s32 n = NpcSpawn_GetSpNpcSlotCount();
    s32 i;
    for (i = 0; i < n; i++) {
        p[i] = FrameHeap_Create(0x7ac, heap);
    }
}
}

namespace nA {
extern "C" void SpNpcAnimHeapPool_Free(void **p) {
    void *heap = gSpNpcAnimPoolHeap;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (p[i] != 0) {
            ((Heap *)(p[i]))->freeAll();
            p[i] = NULL;
        }
    }
    if (heap != 0) {
        ((Heap *)(heap))->freeAll();
    }
}
}

namespace nA {
extern "C" void NpcTexPatBufRef_Init(s32 *p) {
    *p = 5;
}
}

namespace nA {
extern "C" void NpcTexPatBufRef_Deinit() {}
}

namespace nA {
extern "C" void NpcTexPatBufRef_Assign(s32 *p, s32 v) {
    NpcTexPatBufRef_Set(p, v);
}
}

namespace nA {
extern "C" void NpcTexPatBufRef_Set(s32 *p, s32 v) {
    *p = v;
}
}

namespace nA {
extern "C" void NpcTexPatBufRef_LoadFile(s32 *p, void *dst) {
    void *t = NpcTexPatBufPool_Get(sNpcTexPatBufPool.p, *p);
    File_LoadToBuffer(dst, t, 0x2f88);
}
}

namespace nA {
extern "C" void *NpcTexPatBufRef_GetBuffer(s32 *p) {
    return NpcTexPatBufPool_Get(sNpcTexPatBufPool.p, *p);
}
}

namespace nA {
extern "C" void VillagerAnimHeapRef_Init(s32 *p) {
    *p = 8;
}
}

namespace nA {
extern "C" void VillagerAnimHeapRef_Deinit() {}
}

namespace nA {
extern "C" void VillagerAnimHeapRef_Assign(s32 *p, s32 x) {
    ((Heap *)(VillagerAnimHeapPool_Get(sVillagerAnimHeapPool.p, x)))->freeAll();
    *p = x;
}
}

namespace nA {
extern "C" void *VillagerAnimHeapRef_GetHeap(s32 *p) {
    return VillagerAnimHeapPool_Get(sVillagerAnimHeapPool.p, *p);
}
}

namespace nA {
extern "C" void SpNpcAnimHeapRef_Init(s32 *p) {
    *p = 4;
}
}

namespace nA {
extern "C" void SpNpcAnimHeapRef_Deinit() {}
}

namespace nA {
extern "C" void SpNpcAnimHeapRef_Assign(s32 *p, s32 x) {
    ((Heap *)(SpNpcAnimHeapPool_Get(sSpNpcAnimHeapPool.p, x)))->freeAll();
    *p = x;
}
}

namespace nA {
extern "C" void *SpNpcAnimHeapRef_GetHeap(s32 *p) {
    return SpNpcAnimHeapPool_Get(sSpNpcAnimHeapPool.p, *p);
}
}

namespace nZ {
extern "C" {
extern const ImpressionRule sImpressionRules[0x58] = {
    {2, ImpressionCond_PlayerFaceFlag},
    {2, ImpressionCond_WeedsAround},
    {0, ImpressionCond_FlowersAround},
    {1, ImpressionCond_FlowersAround},
    {0, ImpressionCond_FewVillagers},
    {1, ImpressionCond_FewVillagers},
    {0, ImpressionCond_VillagerEventToday},
    {1, ImpressionCond_VillagerEventToday},
    {0, ImpressionCond_Mood1},
    {1, ImpressionCond_Mood1},
    {0, ImpressionCond_Mood2or4},
    {1, ImpressionCond_Mood2or4},
    {2, ImpressionCond_HoldingNet},
    {2, ImpressionCond_HoldingAxe},
    {2, ImpressionCond_HoldingRod},
    {2, ImpressionCond_HoldingWateringCan},
    {2, ImpressionCond_WearingHat13c1},
    {2, ImpressionCond_WearingHat13b2},
    {2, ImpressionCond_WearingHat13a8},
    {2, ImpressionCond_WearingHat13bc},
    {2, ImpressionCond_WearingHat1405},
    {2, ImpressionCond_WearingHat13e6},
    {2, ImpressionCond_WearingHat13ea},
    {2, ImpressionCond_WearingHat13f5},
    {2, ImpressionCond_WearingHat13e3},
    {2, ImpressionCond_WearingHat13e4},
    {2, ImpressionCond_WearingHat1406},
    {1, ImpressionCond_FlowerAccessory},
    {0, ImpressionCond_FlowerAccessory},
    {1, ImpressionCond_HoldingUmbrella},
    {0, ImpressionCond_HoldingUmbrella},
    {1, ImpressionCond_Raining},
    {0, ImpressionCond_Raining},
    {1, ImpressionCond_Snowing},
    {0, ImpressionCond_Snowing},
    {1, ImpressionCond_WearingShirt12a8},
    {0, ImpressionCond_WearingShirt12a8},
    {1, ImpressionCond_TimeOfDay0},
    {0, ImpressionCond_TimeOfDay0},
    {1, ImpressionCond_TimeOfDay3},
    {0, ImpressionCond_TimeOfDay3},
    {2, ImpressionCond_PocketsFull},
    {1, ImpressionCond_FriendshipVeryLow},
    {0, ImpressionCond_FriendshipVeryLow},
    {1, ImpressionCond_FriendshipLow},
    {0, ImpressionCond_FriendshipLow},
    {1, ImpressionCond_FriendshipHigh},
    {0, ImpressionCond_FriendshipHigh},
    {1, ImpressionCond_FriendshipVeryHigh},
    {0, ImpressionCond_FriendshipVeryHigh},
    {1, ImpressionCond_HalfInsectsCaught},
    {1, ImpressionCond_AllInsectsCaught},
    {1, ImpressionCond_HalfFishCaught},
    {1, ImpressionCond_AllFishCaught},
    {0, ImpressionCond_HalfInsectsCaught},
    {0, ImpressionCond_AllInsectsCaught},
    {0, ImpressionCond_HalfFishCaught},
    {0, ImpressionCond_AllFishCaught},
    {2, ImpressionCond_BellsUpTo300},
    {2, ImpressionCond_BellsUpTo1000},
    {2, ImpressionCond_Bells10000To20000},
    {2, ImpressionCond_Bells20000To40000},
    {2, ImpressionCond_Bells40000To60000},
    {2, ImpressionCond_BellsOver60000},
    {1, ImpressionCond_AccessoryHairD},
    {1, ImpressionCond_AccessoryHairC},
    {0, ImpressionCond_AccessoryHairB},
    {0, ImpressionCond_AccessoryHairA},
    {1, ImpressionCond_Hair3},
    {1, ImpressionCond_Hair4},
    {1, ImpressionCond_Hair2},
    {1, ImpressionCond_Hair6},
    {1, ImpressionCond_Hair7},
    {0, ImpressionCond_Hair3},
    {0, ImpressionCond_Hair6},
    {0, ImpressionCond_Hair2},
    {0, ImpressionCond_Hair7},
    {0, ImpressionCond_Hair4},
    {2, ImpressionCond_FourResidents},
    {2, ImpressionCond_TwoPlusResidents},
    {1, ImpressionCond_Winter},
    {0, ImpressionCond_Winter},
    {1, ImpressionCond_Autumn},
    {0, ImpressionCond_Autumn},
    {1, ImpressionCond_Summer},
    {0, ImpressionCond_Summer},
    {1, ImpressionCond_Always},
    {0, ImpressionCond_Always},
};
extern const u32 sBirthdayGiftLists[3] = {
    0x00000000, 0x00000004, 0x00000003,
};
s32 data_020e05ac[3] = {-1, -1, -1};
extern const u8 sStarSignEndDates[24] = {
    0x01, 0x13, 0x02, 0x12, 0x03, 0x14, 0x04, 0x13, 0x05, 0x14, 0x06, 0x15, 0x07, 0x16, 0x08, 0x16,
    0x09, 0x16, 0x0a, 0x17, 0x0b, 0x16, 0x0c, 0x15,
};
u8 sErrandKindTaken[0x14];
SpNpcAnimHeapPool sSpNpcAnimHeapPool;
extern const u8 sFurnitureTasteTextBase[8] = {
    0x00, 0x02, 0x0e, 0x10, 0x14, 0x00, 0x00, 0x00,
};
u8 sVillagerLetter4Path[0x28];
extern const s32 sRelationLevelThresholds[4] = {
    0x190, 0x10e, 0x32, -0x3c,
};
u8 sErrandVillagerDone[8];
u32 sSpeciesCandidateBits[5];
}
}
