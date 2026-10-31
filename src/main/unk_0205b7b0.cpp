#include "sys/Heap.h"
#include "types.h"
#include "player/AnimSlotRef.h"
#include "net/CommManager.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0203c638.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205c66c.h"
#include "proto/main/unk_0205ce0c.h"
#include "proto/main/unk_0205d1f8.h"
#include "proto/main/unk_0205d340.h"
#include "proto/main/unk_0205d480.h"
#include "proto/main/unk_0205d7d8.h"
#include "proto/main/unk_0205dfa4.h"
#include "proto/main/unk_0205edfc.h"
#include "proto/main/unk_0205ef08.h"
#include "proto/main/unk_0205f284.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02082d74.h"
#include "proto/main/unk_02093ff0.h"

#define ALIGN4(x) (((x) + 3) & ~3)
static inline u32 AL(u32 v, u32 a) {
    return (v + a - 1) & ~(a - 1);
}

struct CharaAnimCache {
    void *buffers[25];
    u16 animIds[25];
    u16 dataSizes[25];

    CharaAnimCache();
    ~CharaAnimCache();
    void setDataSize(s32 i, u32 v);
    u32 getDataSize(s32 i);
    s32 findSlotByAnim(s32 v);
    void setAnimId(s32 i, u32 v);
    u32 getAnimId(s32 i);
    void *getBuffer(s32 i);
    void freeBuffers();
    void allocBuffers();
};

extern "C" {
extern u8 gFieldSceneKind;
extern u32 data_020cbf94, data_020cbf98, data_020cbf9c, data_020cbfa0, data_020cbfa4;
extern u32 data_020c8b9c;
extern u32 data_020c8ba0;
extern CommManager *gCommManager;
extern const u8 sJointGroup3Ranges[4];
extern const u8 sJointGroup1Ranges[4];
extern const u8 sJointGroup0Ranges[4];
extern const u8 sJointGroup2Ranges[4];
extern const u8 sCharaAnimHoldPoseModes[];
extern const u16 sCharaAnimEyeAnims[];
extern const u16 sCharaAnimMouthAnims[];

s32 Town_GetMaxOutdoorVillagers(void);
void *Scene_GetCurrent(void);
s32 Scene_GetMaxCharacters(void *);
s32 Scene_GetMaxPlayers(void *);
u32 NpcModelHeap_GetVillagerModelSize(void);
u32 NpcModelHeap_GetSpNpcModelSize(void);
void MI_CpuCopy8(const void *, void *, u32);

}

extern const u8 sJointGroup3Ranges[4];
const u8 sJointGroup3Ranges[4] = {17, 17, 0, 0};
void *gVillagerAnimPoolHeap;
extern const u8 sJointGroup2Ranges[4];
const u8 sJointGroup2Ranges[4] = {9, 11, 12, 14};
void *gSpNpcAnimPoolHeap;
extern const u8 sJointGroup0Ranges[4];
const u8 sJointGroup0Ranges[4] = {12, 14, 0, 0};
extern const u16 data_020cab84[2];
const u16 data_020cab84[2] = {0x800, 0};
extern const u16 data_020cab80[2];
const u16 data_020cab80[2] = {0x400, 0};
void *gRoomBclHeap;
Heap *gNetHeap;
Heap *gModelCacheHeap;
Heap *gMenuHeap;
void *gBgHeap;
extern const u16 sCharaAnimMouthAnims[0x144];
const u16 sCharaAnimMouthAnims[0x144] = {
    367, 367, 367, 367, 367, 187, 188, 189, 189, 190, 190, 191, 367, 192, 191, 367,
    192, 193, 197, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367,
    367, 367, 367, 367, 367, 367, 367, 367, 194, 195, 196, 367, 367, 367, 367, 367,
    367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367,
    367, 367, 367, 367, 367, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208,
    209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
    225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240,
    241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 367, 367, 367, 367, 367,
    367, 252, 253, 254, 255, 256, 257, 258, 367, 367, 367, 367, 367, 259, 260, 261,
    262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277,
    278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 367, 367, 296,
    297, 298, 299, 300, 367, 367, 301, 302, 303, 307, 308, 367, 367, 367, 367, 304,
    367, 305, 367, 306, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367,
    367, 309, 310, 313, 313, 314, 367, 367, 367, 367, 291, 292, 293, 294, 295, 315,
    316, 317, 318, 319, 367, 320, 321, 322, 323, 324, 325, 326, 327, 367, 367, 328,
    367, 329, 367, 367, 367, 367, 367, 367, 367, 330, 367, 367, 367, 331, 332, 367,
    367, 367, 367, 367, 367, 367, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342,
    367, 367, 367, 343, 344, 345, 346, 347, 348, 349, 367, 367, 350, 351, 352, 353,
    352, 353, 354, 355, 354, 355, 367, 356, 357, 358, 359, 359, 360, 361, 362, 363,
    364, 367, 365, 366, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367,
    367, 367, 367, 367,
};
void *gFieldStructureHeap;
void *sSpecialInsectHeap;
void *sHeldInsectHeap;
void *sFieldInsectHeap;
void *sMuseumInsectHeap;
extern const u16 sCharaAnimEyeAnims[0x144];
const u16 sCharaAnimEyeAnims[0x144] = {
    367, 367, 367, 367, 367, 1, 2, 3, 3, 4, 4, 5, 6, 7, 5, 6,
    7, 8, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367,
    367, 367, 367, 367, 367, 367, 367, 367, 9, 10, 11, 367, 367, 367, 12, 367,
    367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367,
    367, 367, 367, 367, 367, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 0, 30, 31, 32, 0, 33, 34, 35, 36, 37,
    0, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
    53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 0, 66, 67,
    68, 69, 70, 71, 72, 73, 74, 367, 75, 76, 77, 78, 79, 80, 81, 82,
    83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98,
    99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 367, 367, 367,
    117, 118, 119, 120, 367, 367, 367, 121, 122, 367, 367, 367, 367, 367, 367, 123,
    367, 367, 367, 124, 367, 367, 367, 367, 367, 367, 367, 367, 125, 367, 367, 367,
    367, 367, 367, 126, 126, 127, 367, 367, 367, 367, 112, 113, 114, 115, 116, 128,
    129, 130, 131, 132, 367, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
    144, 145, 367, 367, 367, 367, 367, 367, 367, 146, 367, 367, 367, 147, 148, 149,
    150, 151, 367, 367, 367, 367, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161,
    367, 367, 367, 162, 163, 164, 165, 166, 167, 168, 367, 367, 169, 170, 171, 172,
    171, 172, 173, 174, 173, 174, 367, 175, 176, 177, 178, 178, 179, 180, 181, 182,
    183, 367, 184, 185, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367, 367,
    367, 367, 367, 367,
};
void *sFishFinHeap;
void *sFishDisplayHeap;
void *sMuseumAquariumHeap;
void *sCharaAnimHeap;
char sCharaAnimPathBuf[0x14];
void *gPlayerFaceTexHeap;
u8 *sJointGroupRanges[4] = {(u8 *)sJointGroup0Ranges, (u8 *)sJointGroup1Ranges, (u8 *)sJointGroup2Ranges, (u8 *)sJointGroup3Ranges};
void *gPlayerBodyModelHeap;
void *gPlayerHeadModelHeap;
void *gPlayerPaletteHeap;
void *gPlayerGlassesModelHeap;
void *gHeldItemModelHeap;
void *sFurnitureHeap;
void *gPlayerBodyAnimHeap;
void *gHeldItemAnimHeap;
void *sFishShadowHeap;
void *gNpcTexPatBufHeap;
extern const u8 sCharaAnimHoldPoseModes[0x144];
const u8 sCharaAnimHoldPoseModes[0x144] = {
    0, 0, 0, 2, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
    0, 1, 1, 3, 3, 3, 3, 2, 3, 3, 2, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 2, 2,
    3, 3, 2, 3, 3, 3, 2, 2, 2, 0, 3, 3, 0, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 2, 0, 3, 3, 3, 3, 3, 3, 3, 3,
    0, 3, 3, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3,
};
void *gCharaFaceAnimHeap;
void *gNpcModelHeap;
void *gPlayerActorHeap;
void *gCharaFaceAnimWorkHeap;
CharaAnimCache sCharaAnimCache;
void *gCharaClothTexHeap;
extern const u8 sJointGroup1Ranges[4];
const u8 sJointGroup1Ranges[4] = {9, 11, 0, 0};
u16 sCharaAnimJointGroups[0x144] = {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 3,
};
void *gFishBobberHeap;
void *gTownBclHeap;
u8 sJointGroupRangeCounts[4] = {1, 1, 2, 1};

enum Unk_0205b7cc_Zero { UNK_0205B7CC_ZERO = 0 };

extern "C" void CharaAnimCache_Create(Heap *parent) {
    CharaAnimHeap_Create(parent);
    sCharaAnimCache.allocBuffers();
    if (sCharaAnimHeap) ((Heap *)(sCharaAnimHeap))->adjust();
}

extern "C" void CharaAnimCache_Destroy() {
    sCharaAnimCache.freeBuffers();
    CharaAnimHeap_Destroy();
}

extern "C" char *CharaAnim_GetPath(u32 x) {
    u32 z = x >> 5;
    Str_SPrintf(sCharaAnimPathBuf, "/anm/%d/%d.nsbca", z, x);
    return sCharaAnimPathBuf;
}

extern "C" u32 CharaAnim_GetBodySlotSize() { return 0x15c0; }

extern "C" u32 CharaAnim_GetPartSlotSize() { return 0x270; }

extern "C" u32 CharaAnim_GetExtraSlotSize() { return 0x270; }

extern "C" u32 CharaAnim_GetEyeAnim(u32 i) { return sCharaAnimEyeAnims[i]; }

extern "C" u32 CharaAnim_GetMouthAnim(u32 i) { return sCharaAnimMouthAnims[i]; }

extern "C" u32 JointGroup_GetRangeCount(u32 i) { return sJointGroupRangeCounts[i]; }

extern "C" u32 JointGroup_GetRangeFirst(u32 a, u32 b) {
    JointGroup_GetRangeCount(a);
    return sJointGroupRanges[a][b * 2];
}

extern "C" u32 JointGroup_GetRangeLast(u32 a, u32 b) {
    JointGroup_GetRangeCount(a);
    u8 *q = sJointGroupRanges[a] + b * 2;
    return q[1];
}

extern "C" u32 CharaAnim_GetJointGroup(u32 i) { return sCharaAnimJointGroups[i]; }

extern "C" u32 CharaAnim_GetHoldPoseMode(u32 i) { return sCharaAnimHoldPoseModes[i]; }

CharaAnimCache::CharaAnimCache() {
    for (s32 i = 0; i < 0x19; i++) animIds[i] = 0x144;
}

CharaAnimCache::~CharaAnimCache() {}

void CharaAnimCache::allocBuffers() {
    Heap *heap = (Heap *)sCharaAnimHeap;
    u32 n = gCommManager->memberCount;
    u32 m = Scene_GetMaxPlayers(Scene_GetCurrent());
    if (n < m) m = n;
    u32 k = m ? m : 1;
    u32 v[4];
    v[0] = Scene_GetMaxCharacters(Scene_GetCurrent()) + NpcSpawn_GetSpNpcSlotCount() - k;
    v[1] = CharaAnim_GetBodySlotSize();
    v[2] = CharaAnim_GetPartSlotSize();
    v[3] = CharaAnim_GetExtraSlotSize();
    u32 i;
    for (i = 0; i < m; i++) buffers[i] = Heap_AllocAligned(heap, v[1], 4);
    for (i = 4; i < v[0] + 4; i++) buffers[i] = Heap_AllocAligned(heap, v[1], 4);
    for (i = 9; i < m + 9; i++) buffers[i] = Heap_AllocAligned(heap, v[2], 4);
    m = 4;
    for (i = 0xd; i < v[0] + 0xd; i++) buffers[i] = Heap_AllocAligned(heap, v[2], m);
    for (i = 0x12; i < v[0] + 0x12; i++) buffers[i] = Heap_AllocAligned(heap, v[3], m);
}

void CharaAnimCache::freeBuffers() {
    s32 i;
    for (i = 0; i < 0x19; i++) {
        buffers[i] = 0;
        animIds[i] = 0x144;
        dataSizes[i] = 0;
    }
    if (sCharaAnimHeap) ((Heap *)(sCharaAnimHeap))->freeAll();
}

void *CharaAnimCache::getBuffer(s32 i) { return buffers[i]; }

u32 CharaAnimCache::getAnimId(s32 i) { return animIds[i]; }

void CharaAnimCache::setAnimId(s32 i, u32 v) { animIds[i] = v; }

s32 CharaAnimCache::findSlotByAnim(s32 v) {
    s32 lo = 0, hi = 0x19;
    if (v < 0x137) hi = 9;
    else lo = 9;
    for (; lo < hi; lo++) {
        s32 c = animIds[lo];
        if (c == v) return lo;
    }
    return 0x19;
}

u32 CharaAnimCache::getDataSize(s32 i) { return dataSizes[i]; }

void CharaAnimCache::setDataSize(s32 i, u32 v) { dataSizes[i] = v; }

extern "C" void AnimSlotRef_Init(AnimSlotRef *p) { p->slot = 0x19; }

extern "C" void AnimSlotRef_Destruct() {}

extern "C" void AnimSlotRef_Assign(AnimSlotRef *p, u32 v) {
    AnimSlotRef_SetSlot(p, v);
    AnimSlotRef_Load(p, 0x144, 0, 0);
}

extern "C" void AnimSlotRef_SetSlot(AnimSlotRef *p, u32 v) { p->slot = v; }

extern "C" void AnimSlotRef_Load(AnimSlotRef *p, s32 a, s32 b, s32 c) {
    u32 cur = p->slot;
    if (a >= 0x144) {
        sCharaAnimCache.setAnimId(cur, 0x144);
        sCharaAnimCache.setDataSize(cur, 0);
        return;
    }
    if (c == 0 && a == sCharaAnimCache.getAnimId(cur)) return;
    if (b != 0) {
        s32 slot = sCharaAnimCache.findSlotByAnim(a);
        if (slot != 0x19) {
            AnimSlotRef_CopyFromSlot(p, slot);
            return;
        }
    }
    void *buf = sCharaAnimCache.getBuffer(cur);
    u32 sz;
    if ((s32)cur > 8) sz = CharaAnim_GetPartSlotSize();
    else sz = CharaAnim_GetBodySlotSize();
    s32 r = File_LoadToBuffer(CharaAnim_GetPath(a), buf, sz);
    if (r != 0) {
        sCharaAnimCache.setAnimId(cur, a);
        sCharaAnimCache.setDataSize(cur, r);
    }
}

extern "C" void AnimSlotRef_CopyFromSlot(AnimSlotRef *p, s32 v) {
    u32 cur = p->slot;
    if (v != cur) {
        u32 x = sCharaAnimCache.getAnimId(v);
        if (x != sCharaAnimCache.getAnimId(cur)) {
            u32 sz = sCharaAnimCache.getDataSize(v);
            if (sz != 0) {
                void *a = sCharaAnimCache.getBuffer(v);
                void *b = sCharaAnimCache.getBuffer(cur);
                if (a != 0 && b != 0) {
                    MI_CpuCopy8(a, b, sz);
                    sCharaAnimCache.setAnimId(cur, x);
                    sCharaAnimCache.setDataSize(cur, sz);
                }
            }
        }
    }
}

extern "C" void *AnimSlotRef_GetData(AnimSlotRef *p) { return sCharaAnimCache.getBuffer(p->slot); }

extern "C" u32 AnimSlotRef_GetAnimId(AnimSlotRef *p) { return sCharaAnimCache.getAnimId(p->slot); }

extern "C" Heap *NetHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    gNetHeap = h;
    return h;
}

extern "C" void NetHeap_Destroy() { gNetHeap->destroy2(); gNetHeap = NULL; }

extern "C" Heap *ModelCacheHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    gModelCacheHeap = h;
    return h;
}

extern "C" void ModelCacheHeap_Destroy() { gModelCacheHeap->destroy2(); gModelCacheHeap = NULL; }

extern "C" Heap *MenuHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    gMenuHeap = h;
    return h;
}

extern "C" void MenuHeap_Destroy() { gMenuHeap->destroy2(); gMenuHeap = NULL; }

extern "C" Heap *BgHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    gBgHeap = h;
    return h;
}

extern "C" void BgHeap_Destroy() { ((Heap *)(gBgHeap))->destroy2(); gBgHeap = 0; }

extern "C" Heap *FurnitureHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    sFurnitureHeap = h;
    return h;
}

extern "C" void FurnitureHeap_Destroy(void) {
    ((Heap *)(sFurnitureHeap))->destroy2();
    sFurnitureHeap = NULL;
}

extern "C" Heap *FieldStructureHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)FrameHeap_Create(size, parent);
    gFieldStructureHeap = h;
    return h;
}

extern "C" void FieldStructureHeap_Destroy(void) {
    ((Heap *)(gFieldStructureHeap))->destroy2();
    gFieldStructureHeap = NULL;
}

extern "C" Heap *SpecialInsectHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    sSpecialInsectHeap = h;
    return h;
}

extern "C" void SpecialInsectHeap_Destroy(void) {
    ((Heap *)(sSpecialInsectHeap))->destroy2();
    sSpecialInsectHeap = NULL;
}

extern "C" Heap *HeldInsectHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    sHeldInsectHeap = h;
    return h;
}

extern "C" void HeldInsectHeap_Destroy(void) {
    ((Heap *)(sHeldInsectHeap))->destroy2();
    sHeldInsectHeap = NULL;
}

extern "C" Heap *FieldInsectHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    sFieldInsectHeap = h;
    return h;
}

extern "C" void FieldInsectHeap_Destroy(void) {
    ((Heap *)(sFieldInsectHeap))->destroy2();
    sFieldInsectHeap = NULL;
}

extern "C" Heap *MuseumInsectHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    sMuseumInsectHeap = h;
    return h;
}

extern "C" void MuseumInsectHeap_Destroy(void) {
    ((Heap *)(sMuseumInsectHeap))->destroy2();
    sMuseumInsectHeap = NULL;
}

extern "C" Heap *FishShadowHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    sFishShadowHeap = h;
    return h;
}

extern "C" void FishShadowHeap_Destroy(void) {
    ((Heap *)(sFishShadowHeap))->destroy2();
    sFishShadowHeap = NULL;
}

extern "C" Heap *FishFinHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    sFishFinHeap = h;
    return h;
}

extern "C" void FishFinHeap_Destroy(void) {
    ((Heap *)(sFishFinHeap))->destroy2();
    sFishFinHeap = NULL;
}

extern "C" Heap *FishDisplayHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    sFishDisplayHeap = h;
    return h;
}

extern "C" void FishDisplayHeap_Destroy(void) {
    ((Heap *)(sFishDisplayHeap))->destroy2();
    sFishDisplayHeap = NULL;
}

extern "C" Heap *MuseumAquariumHeap_Create(u32 size, Heap *parent) {
    Heap *h = (Heap *)ExpHeap_Create(size, parent);
    sMuseumAquariumHeap = h;
    return h;
}

extern "C" void MuseumAquariumHeap_Destroy(void) {
    ((Heap *)(sMuseumAquariumHeap))->destroy2();
    sMuseumAquariumHeap = NULL;
}

extern "C" void CharaAnimHeap_Create(Heap *parent) {
    u32 s0 = 0, s1 = 0, s2 = 0, s3 = 0;
    u32 n = gCommManager->memberCount;
    u32 a = Scene_GetMaxPlayers(Scene_GetCurrent());
    if (n < a) {
        a = n;
    }
    u32 r = a != 0 ? a : 1;
    u32 c = Scene_GetMaxCharacters(Scene_GetCurrent());
    r = c + NpcSpawn_GetSpNpcSlotCount() - r;
    s0 += ALIGN4(CharaAnim_GetBodySlotSize());
    s1 += ALIGN4(CharaAnim_GetPartSlotSize());
    s2 += ALIGN4(CharaAnim_GetExtraSlotSize());
    u32 m = a + r;
    s3 += s0 * m;
    s3 += s1 * m;
    s3 += s2 * r;
    sCharaAnimHeap = FrameHeap_Create(s3, parent);
}

extern "C" void CharaAnimHeap_Destroy(void) {
    ((Heap *)(sCharaAnimHeap))->destroy2();
    sCharaAnimHeap = NULL;
}

extern "C" void CharaClothTexHeap_Create(Heap *parent) {
    u32 s = 0, t = 0;
    s += ALIGN4(ClothTex_GetBufferSize());
    s32 c = Scene_GetMaxCharacters(Scene_GetCurrent());
    s32 d = NpcSpawn_GetSpNpcSlotCount();
    t += s * (c + d + 1);
    gCharaClothTexHeap = FrameHeap_Create(t, parent);
}

extern "C" void CharaClothTexHeap_Destroy(void) {
    ((Heap *)(gCharaClothTexHeap))->destroy2();
    gCharaClothTexHeap = NULL;
}

extern "C" void PlayerFaceTexHeap_Create(Heap *parent) {
    u32 n = gCommManager->memberCount;
    u32 s = 0, t = 0;
    s += ALIGN4(PlayerFaceTex_GetBufferSize());
    t += s * n;
    gPlayerFaceTexHeap = FrameHeap_Create(t, parent);
}

extern "C" void PlayerFaceTexHeap_Destroy(void) {
    ((Heap *)(gPlayerFaceTexHeap))->destroy2();
    gPlayerFaceTexHeap = NULL;
}

extern "C" void CharaFaceAnimHeap_Create(Heap *parent) {
    u32 s = 0, t = 0;
    s += ALIGN4(CharaFaceAnim_GetSlotSize());
    s32 c = Scene_GetMaxCharacters(Scene_GetCurrent());
    s32 d = NpcSpawn_GetSpNpcSlotCount();
    t += s * (c + d);
    gCharaFaceAnimHeap = FrameHeap_Create(t, parent);
}

extern "C" void CharaFaceAnimHeap_Destroy(void) {
    ((Heap *)(gCharaFaceAnimHeap))->destroy2();
    gCharaFaceAnimHeap = NULL;
}

extern "C" void PlayerBodyModelHeap_Create(Heap *parent) {
    u32 n = gCommManager->memberCount;
    u32 s = 0, t = 0;
    s += ALIGN4(PlayerBodyModel_GetBufferSize());
    t += s * n;
    gPlayerBodyModelHeap = FrameHeap_Create(t, parent);
}

extern "C" void PlayerBodyModelHeap_Destroy(void) {
    ((Heap *)(gPlayerBodyModelHeap))->destroy2();
    gPlayerBodyModelHeap = NULL;
}

extern "C" void PlayerHeadModelHeap_Create(Heap *parent) {
    u32 n = gCommManager->memberCount;
    u32 s = 0, t = 0;
    s += ALIGN4(PlayerHead_GetBufferSize());
    t += s * n;
    gPlayerHeadModelHeap = FrameHeap_Create(t, parent);
}

extern "C" void PlayerHeadModelHeap_Destroy(void) {
    ((Heap *)(gPlayerHeadModelHeap))->destroy2();
    gPlayerHeadModelHeap = NULL;
}

extern "C" void PlayerPaletteHeap_Create(Heap *parent) {
    u32 n = gCommManager->memberCount;
    u32 s = 0, t = 0;
    s += PlayerPalette_GetSlotSize();
    t += s * n;
    gPlayerPaletteHeap = FrameHeap_Create(t, parent);
}

extern "C" void PlayerPaletteHeap_Destroy(void) {
    ((Heap *)(gPlayerPaletteHeap))->destroy2();
    gPlayerPaletteHeap = NULL;
}

extern "C" void PlayerGlassesModelHeap_Create(Heap *parent) {
    u32 n = gCommManager->memberCount;
    u32 s = 0, t = 0;
    s += ALIGN4(PlayerGlassesModel_GetBufferSize());
    t += s * n;
    gPlayerGlassesModelHeap = FrameHeap_Create(t, parent);
}

extern "C" void PlayerGlassesModelHeap_Destroy(void) {
    ((Heap *)(gPlayerGlassesModelHeap))->destroy2();
    gPlayerGlassesModelHeap = NULL;
}

extern "C" void HeldItemModelHeap_Create(Heap *parent) {
    u32 s = 0, t = 0;
    s += ALIGN4(HeldItem_GetModelBufferSize());
    s32 c = Scene_GetMaxCharacters(Scene_GetCurrent());
    s32 d = NpcSpawn_GetSpNpcSlotCount();
    t += s * (c + d);
    gHeldItemModelHeap = FrameHeap_Create(t, parent);
}

extern "C" void HeldItemModelHeap_Destroy(void) {
    ((Heap *)(gHeldItemModelHeap))->destroy2();
    gHeldItemModelHeap = NULL;
}

extern "C" void CharaFaceAnimWorkHeap_Create(Heap *parent) {
    u32 s = 0, t = 0;
    s += ALIGN4(CharaFaceAnimWork_GetHeapSize());
    s32 c = Scene_GetMaxCharacters(Scene_GetCurrent());
    s32 e = c + NpcSpawn_GetSpNpcSlotCount();
    t += ALIGN4(s + 0x48) * e;
    gCharaFaceAnimWorkHeap = FrameHeap_Create(t, parent);
}

extern "C" void CharaFaceAnimWorkHeap_Destroy(void) {
    ((Heap *)(gCharaFaceAnimWorkHeap))->destroy2();
    gCharaFaceAnimWorkHeap = NULL;
}

extern "C" void PlayerBodyAnimHeap_Create(Heap *parent) {
    u32 n = gCommManager->memberCount;
    u32 s = 0, t = 0;
    s += ALIGN4(PlayerBodyWork_GetHeapSize());
    t += ALIGN4(s + 0x48) * n;
    gPlayerBodyAnimHeap = FrameHeap_Create(t, parent);
}

extern "C" void PlayerBodyAnimHeap_Destroy(void) {
    ((Heap *)(gPlayerBodyAnimHeap))->destroy2();
    gPlayerBodyAnimHeap = NULL;
}

extern "C" void HeldItemAnimHeap_Create(Heap *parent) {
    u32 s = 0, t = 0;
    s += ALIGN4(HeldItem_GetAnimHeapSize());
    s32 c = Scene_GetMaxCharacters(Scene_GetCurrent());
    s32 e = c + NpcSpawn_GetSpNpcSlotCount();
    t += ALIGN4(s + 0x48) * e;
    gHeldItemAnimHeap = FrameHeap_Create(t, parent);
}

extern "C" void HeldItemAnimHeap_Destroy(void) {
    ((Heap *)(gHeldItemAnimHeap))->destroy2();
    gHeldItemAnimHeap = NULL;
}

extern "C" void FishBobberHeap_Create(Heap *parent) {
    u32 s = 0, t = 0;
    s += ALIGN4(FishBobber_GetModelSize());
    s32 c = Scene_GetMaxCharacters(Scene_GetCurrent());
    s32 d = NpcSpawn_GetSpNpcSlotCount();
    t += s * (c + d);
    gFishBobberHeap = FrameHeap_Create(t, parent);
}

extern "C" void FishBobberHeap_Destroy(void) {
    ((Heap *)(gFishBobberHeap))->destroy2();
    gFishBobberHeap = NULL;
}

extern "C" void NpcTexPatBufHeap_Create(Heap *parent) {
    s32 n;
    if (gFieldSceneKind == 0 ? TRUE : FALSE) {
        n = Town_GetMaxOutdoorVillagers();
    } else {
        n = Scene_GetMaxCharacters(Scene_GetCurrent()) - Scene_GetMaxPlayers(Scene_GetCurrent());
    }
    n += NpcSpawn_GetSpNpcSlotCount();
    u32 s = 0, t = 0;
    s += ALIGN4(data_020cbfa4);
    t += s * n;
    gNpcTexPatBufHeap = FrameHeap_Create(t, parent);
}

extern "C" void NpcTexPatBufHeap_Destroy(void) {
    ((Heap *)(gNpcTexPatBufHeap))->destroy2();
    gNpcTexPatBufHeap = NULL;
}

extern "C" void VillagerAnimPoolHeap_Create(Heap *parent) {
    u32 t = 0;
    u32 m = data_020cbf9c - 1;
    u32 k = ~m;
    u32 v = (data_020cbfa0 + m) & k;
    v = (v + 0x48 + m) & k;
    t += v * 8;
    gVillagerAnimPoolHeap = FrameHeap_Create(t, parent);
}

extern "C" void VillagerAnimPoolHeap_Destroy(void) {
    ((Heap *)(gVillagerAnimPoolHeap))->destroy2();
    gVillagerAnimPoolHeap = NULL;
}

extern "C" void SpNpcAnimPoolHeap_Create(Heap *parent) {
    u32 n = NpcSpawn_GetSpNpcSlotCount();
    u32 t = 0;
    u32 m = data_020cbf94 - 1;
    u32 k = ~m;
    u32 v = (data_020cbf98 + m) & k;
    v = (v + 0x48 + m) & k;
    t += v * n;
    gSpNpcAnimPoolHeap = FrameHeap_Create(t, parent);
}

extern "C" void SpNpcAnimPoolHeap_Destroy(void) {
    ((Heap *)(gSpNpcAnimPoolHeap))->destroy2();
    gSpNpcAnimPoolHeap = NULL;
}

extern "C" void *NpcModelHeap_Create(Heap *parent) {
    u32 t = 0;
    s32 n;
    if (gFieldSceneKind == 0 ? TRUE : FALSE) {
        n = Town_GetMaxOutdoorVillagers();
    } else {
        n = Scene_GetMaxCharacters(Scene_GetCurrent()) - Scene_GetMaxPlayers(Scene_GetCurrent());
    }
    s32 m = NpcSpawn_GetSpNpcSlotCount();
    u32 x = ALIGN4(ALIGN4(NpcModelHeap_GetVillagerModelSize()) + 0x48);
    t += x * n;
    x = ALIGN4(ALIGN4(NpcModelHeap_GetSpNpcModelSize()) + 0x48);
    u32 size = t + x * m;
    if (size != 0) {
        gNpcModelHeap = FrameHeap_Create(size, parent);
    }
    return gNpcModelHeap;
}

extern "C" void NpcModelHeap_Destroy(void) {
    if (gNpcModelHeap) {
        ((Heap *)(gNpcModelHeap))->destroy2();
    }
    gNpcModelHeap = NULL;
}

extern "C" void PlayerActorHeap_Create(Heap *parent) {
    u32 s = 0, t = 0;
    s += ALIGN4(PlayerActor_GetObjectSize());
    u32 a = PlayerActor_GetObjectAlign();
    s += AL(16, a);
    t += s * 4;
    gPlayerActorHeap = ExpHeap_Create(t, parent);
}

extern "C" void PlayerActorHeap_Destroy(void) {
    ((Heap *)(gPlayerActorHeap))->destroy2();
    gPlayerActorHeap = NULL;
}

extern "C" void TownBclHeap_Create(Heap *parent) {
    Unk_0205b7cc_Zero z = UNK_0205B7CC_ZERO;
    u32 s = (data_020c8ba0 + 3) & ~3;
    s = (s + FRAMEHEAP_OVERHEAD_ROUNDED) & ~3;
    gTownBclHeap = FrameHeap_Create(z + s, parent);
}

extern "C" void TownBclHeap_Destroy() {
    ((Heap *)(gTownBclHeap))->destroy2();
    gTownBclHeap = NULL;
}

extern "C" void RoomBclHeap_Create(Heap *parent) {
    Unk_0205b7cc_Zero z = UNK_0205B7CC_ZERO;
    u32 s = (data_020c8b9c + 3) & ~3;
    s = (s + FRAMEHEAP_OVERHEAD_ROUNDED) & ~3;
    u32 e = z + s;
    gRoomBclHeap = FrameHeap_Create(e, parent);
}

extern "C" void RoomBclHeap_Destroy() {
    ((Heap *)(gRoomBclHeap))->destroy2();
    gRoomBclHeap = NULL;
}

