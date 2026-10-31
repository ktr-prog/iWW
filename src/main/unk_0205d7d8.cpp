#include "types.h"
#include "net/CommManager.h"
#include "sys/PrioListNode.h"
#include "gfx/TexVramSlot.h"
#include "gfx/TexTransfer.h"
#include "gfx/VramTask.h"
#include "gfx/TexVramTask.h"
#include "actor/CharaClothTexRef.h"
#include "player/FishBobber.h"
#include "player/HeldItemModel.h"
#include "player/PlayerHead.h"
#include "sys/Heap.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205c91c.h"
#include "proto/main/unk_0205d7d8.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"

extern "C" {
void *NNS_G3dGetTex(void *h);
s32 ItemInfo_TestFlag2(u16 *p);
s32 Item_IsFlowerItem(u16 *p);
s32 Item_GetFlowerItemOrdinal(u16 *p);
CharaClothTexRef *CharaClothTexPool_GetOwnRef();
s32 NNS_G3dTexGetRequiredSize(void *p);
s32 NNS_G3dTex4x4GetRequiredSize(void *p);
s32 NNS_G3dPlttGetRequiredSize(void *p);
extern CommManager *gCommManager;
}

static inline BOOL Unk_0205d4e4_IsTwo(u8 v) {
    return v == 2 ? TRUE : FALSE;
}

static inline BOOL Unk_0205d4e4_IsOne(u8 v) {
    return v == 1 ? TRUE : FALSE;
}

class PlayerHeadBank {
public:
    void *buffers[4];
    TexVramSlot vramSlots[4][2];
    TexVramTask texTasks[4][2];
    void *modelFiles[4][2];
    u8 modelIds[4][2];

    PlayerHeadBank();
    ~PlayerHeadBank();
    void setModelId(u32 i, u32 j, u32 v);
    s32 getModelId(u32 i, u32 j);
    TexVramTask *getTexTask(u32 i, u32 j);
    TexVramSlot *getVramSlot(u32 i, u32 j);
    void setModelFile(u32 i, u32 j, void *v);
    void *getModelFile(u32 i, u32 j);
    void *getBuffer(u32 i);
    void releaseAll(void);
    void setup(void);
};

static inline BOOL Unk_0205da08_InRange(u16 *p) {
    BOOL r = FALSE;
    if (*p >= 0x1429 && *p <= 0x1430) {
        r = TRUE;
    }
    return r;
}

static inline BOOL Unk_0205ddc8_In(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi)
        r = TRUE;
    return r;
}

static inline s32 Unk_0205ddc8_Idx(u32 v, u32 lo, u32 hi) {
    if (v >= lo && v <= hi)
        return v - lo;
    return -1;
}

extern "C" {
extern const u8 sPlayerHairModelIds[0x10];
extern const u8 sPlayerHatHairModelIds[0x10];
extern const u8 sFlowerHeadModelIds[0x18];
extern const u8 sFullHeadwearModelIds[0x20];
extern const u8 sHatModelIds[0x48];
}

const u8 sPlayerHatHairModelIds[0x10] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
const u8 sPlayerHairModelIds[0x10] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
const u8 sFlowerHeadModelIds[0x18] = {0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93,
                                0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x00, 0x00};
const u8 sFullHeadwearModelIds[0x20] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
                                0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f};
const u8 sHatModelIds[0x48] = {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
                                0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
                                0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
                                0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
                                0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87};

char sPlayerHeadPathBuf[0x14];
PlayerHeadBank sPlayerHeadBank;

#define MGR (&sPlayerHeadBank)

extern "C" BOOL HeldItemModel_IsBobberLanded(HeldItemModel *p) {
    return p->bobber.isInWater();
}

extern "C" void PlayerHeadBank_Init(Heap *parent) {
    PlayerHeadModelHeap_Create(parent);
    MGR->setup();
    if (gPlayerHeadModelHeap != NULL)
        static_cast<Heap *>(gPlayerHeadModelHeap)->adjust();
}

extern "C" void PlayerHeadBank_Destroy(void) {
    MGR->releaseAll();
    PlayerHeadModelHeap_Destroy();
}

extern "C" char *PlayerHead_GetModelPath(u32 a) {
    Str_SPrintf(sPlayerHeadPathBuf, "/PHead/%d/%d.nsbmd", a >> 5, a);
    return sPlayerHeadPathBuf;
}

extern "C" u32 PlayerHead_GetHairModelId(u32 i) { return sPlayerHairModelIds[i]; }
extern "C" u32 PlayerHead_GetHatHairModelId(u32 i) { return sPlayerHatHairModelIds[i]; }
extern "C" u32 PlayerHead_GetHatModelId(u32 i) { return sHatModelIds[i]; }
extern "C" u32 PlayerHead_GetFullHeadwearModelId(u32 i) { return sFullHeadwearModelIds[i]; }
extern "C" u32 PlayerHead_GetFlowerModelId(u32 i) { return sFlowerHeadModelIds[i]; }

extern "C" void PlayerHead_GetModelIds(s32 flag, u32 a, u16 *p, u32 *o1, u32 *o2) {
    u32 r = 0x9e;
    BOOL k = FALSE;
    if (*p >= 0x13a8 && *p <= 0x13c7)
        k = TRUE;
    if (k) {
        s32 t = Unk_0205ddc8_Idx(*p, 0x13a8, 0x13c7);
        if (t >= 0 && (u32)t < 0x20)
            a = PlayerHead_GetFullHeadwearModelId(t);
        else
            a = PlayerHead_GetFullHeadwearModelId(0);
    } else {
        u32 v = *p;
        if ((v >= 0x13c8 && v <= 0x1407) || (v >= 0x1429 && v <= 0x1430)) {
            if (ItemInfo_TestFlag2(p) == 0) {
                a = PlayerHead_GetHatHairModelId(a);
                goto done1;
            }
        }
        a = PlayerHead_GetHairModelId(a);
    }
done1:
    BOOL k2 = FALSE;
    if (*p >= 0x1429 && *p <= 0x1430)
        k2 = TRUE;
    if (k2) {
        if (flag == 0)
            r = 0x80;
        else
            r = 0x81;
    } else {
        u32 v = *p;
        if (v >= 0x13c8 && v <= 0x1407) {
            s32 t = Unk_0205ddc8_Idx(v, 0x13c8, 0x1407);
            if (t >= 0 && (u32)t < 0x48)
                r = PlayerHead_GetHatModelId(t);
        } else if (v >= 0x1408 && v <= 0x1428) {
            if (Item_IsFlowerItem(p) != 0) {
                s32 t = Item_GetFlowerItemOrdinal(p);
                if (t >= 0 && (u32)t < 0x16) {
                    r = PlayerHead_GetFlowerModelId(t);
                    if (r == 0x9c)
                        r = 0x9d;
                }
            }
        }
    }
    *o1 = a;
    *o2 = r;
}

extern "C" s32 PlayerHead_GetBufferSize(void) { return 0x2864; }
extern "C" s32 PlayerHead_GetTexVramSize(void) { return 0x1220; }
extern "C" s32 PlayerHead_GetTex4x4VramSize(void) { return 0; }
extern "C" s32 PlayerHead_GetPlttVramSize(void) { return 0xc0; }

PlayerHeadBank::PlayerHeadBank() {
    for (s32 i = 0; i < 4; i++) {
        buffers[i] = 0;
        modelFiles[i][0] = 0;
        modelFiles[i][1] = 0;
        modelIds[i][0] = 0x9e;
        modelIds[i][1] = 0x9e;
    }
}

PlayerHeadBank::~PlayerHeadBank() {}

void PlayerHeadBank::setup(void) {
    u32 n = gCommManager->memberCount;
    u32 i;
    for (i = 0; i < n; i++) {
        vramSlots[i][0].alloc(PlayerHead_GetTexVramSize(), PlayerHead_GetTex4x4VramSize(), PlayerHead_GetPlttVramSize());
    }
    Heap *heap = static_cast<Heap *>(gPlayerHeadModelHeap);
    for (i = 0; i < n; i++) {
        buffers[i] = Heap_AllocAligned(heap, PlayerHead_GetBufferSize(), 4);
    }
}

void PlayerHeadBank::releaseAll(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        vramSlots[i][0].clear();
        vramSlots[i][1].clear();
    }
    for (i = 0; i < 4; i++) {
        buffers[i] = NULL;
        modelFiles[i][0] = NULL;
        modelFiles[i][1] = NULL;
    }
    if (gPlayerHeadModelHeap) {
        static_cast<Heap *>(gPlayerHeadModelHeap)->freeAll();
    }
    for (i = 0; i < 4; i++) {
        modelIds[i][0] = 0x9e;
        modelIds[i][1] = 0x9e;
    }
}

void *PlayerHeadBank::getBuffer(u32 i) { return buffers[i]; }
void *PlayerHeadBank::getModelFile(u32 i, u32 j) { return modelFiles[i][j]; }
void PlayerHeadBank::setModelFile(u32 i, u32 j, void *v) { modelFiles[i][j] = v; }
TexVramSlot *PlayerHeadBank::getVramSlot(u32 i, u32 j) { return &vramSlots[i][j]; }
TexVramTask *PlayerHeadBank::getTexTask(u32 i, u32 j) { return &texTasks[i][j]; }
s32 PlayerHeadBank::getModelId(u32 i, u32 j) { return modelIds[i][j]; }
void PlayerHeadBank::setModelId(u32 i, u32 j, u32 v) { modelIds[i][j] = v; }

PlayerHead::PlayerHead() {
    slot = 4;
}
PlayerHead::~PlayerHead() {}
extern "C" void PlayerHead_SetSlot(u8 *p, u8 v) {
    *p = v;
}

extern "C" void PlayerHead_Release(u8 *p) {
    PlayerHead_CancelTexUpload(p);
    PlayerHead_SetModelFile(p, 0, 0);
    PlayerHead_SetModelFile(p, 1, 0);
    PlayerHead_SetModelId(p, 0, 0x9e);
    PlayerHead_SetModelId(p, 1, 0x9e);
}

extern "C" void PlayerHead_CancelTexUpload(u8 *p) {
    if (Unk_0205d4e4_IsOne(PlayerHead_GetTexTask(p, 0)->state)) {
        PlayerHead_GetTexTask(p, 0)->cancel();
    } else {
        PlayerHead_GetTexTask(p, 0)->clear();
    }
    if (Unk_0205d4e4_IsOne(PlayerHead_GetTexTask(p, 1)->state)) {
        PlayerHead_GetTexTask(p, 1)->cancel();
    } else {
        PlayerHead_GetTexTask(p, 1)->clear();
    }
}

extern "C" s32 PlayerHead_Load(u8 *p, s32 a, s32 b, u16 *c, void *d) {
    void *buf = PlayerHead_GetBuffer(p);
    s32 sz = PlayerHead_GetBufferSize();
    s32 r4 = File_LoadToBuffer(PlayerHead_GetModelPath(a), buf, sz);
    s32 res = 0;
    if (r4 != 0) {
        r4 = (r4 + 3) & ~3;
        PlayerHead_SetModelFile(p, res, buf);
        PlayerHead_SetModelId(p, 0, a);
        PlayerHead_SetModelId(p, 1, b);
        if (b < 0x9e) {
            buf = (u8 *)buf + r4;
            sz -= r4;
            res = File_LoadToBuffer(PlayerHead_GetModelPath(b), buf, sz);
            if (res != 0) {
                PlayerHead_SetModelFile(p, 1, buf);
                if (Unk_0205da08_InRange(c)) {
                    CharaClothTexRef *x = CharaClothTexPool_GetOwnRef();
                    x->loadItem(c, d, 0, 0);
                    void *m = NNS_G3dGetTex(CharaClothTexRef_GetBuffer(&x->v));
                    void *n = NNS_G3dGetTex(buf);
                    G3dRes_CopyTexByName(m, n, "cloth", "myD");
                    G3dRes_CopyPlttByName(m, n, "cloth", "myD");
                }
            } else {
                PlayerHead_SetModelId(p, 1, 0x9e);
            }
        }
    }
    return r4 + res;
}

extern "C" void PlayerHead_RelocateTextures(u8 *p) {
    void *q = NNS_G3dGetTex(PlayerHead_GetModelFile(p, 0));
    TexVramSlot *d0 = PlayerHead_GetVramSlot(p, 0);
    d0->relocateTexture(q);
    if (PlayerHead_GetModelId(p, 1) < 0x9e) {
        void *src = PlayerHead_GetModelFile(p, 1);
        if (src) {
            s32 a = NNS_G3dTexGetRequiredSize(q);
            s32 b = NNS_G3dTex4x4GetRequiredSize(q);
            s32 c = NNS_G3dPlttGetRequiredSize(q);
            void *q2 = NNS_G3dGetTex(src);
            s32 e = NNS_G3dTexGetRequiredSize(q2);
            s32 f = NNS_G3dTex4x4GetRequiredSize(q2);
            s32 g = NNS_G3dPlttGetRequiredSize(q2);
            TexVramSlot *d1 = PlayerHead_GetVramSlot(p, 1);
            u32 x = d0->makeTexKeyAt(d0->makeTexKey(a), e);
            u32 y = d0->makeTex4x4KeyAt(d0->makeTex4x4Key(b), f);
            u32 z = d0->makePlttKeyAt(d0->makePlttKey(c), g);
            d1->setKeys(x, y, z);
            d1->relocateTexture(q2);
        }
    }
}

extern "C" BOOL PlayerHead_PollTexUpload(u8 *p) {
    BOOL r6 = FALSE, r4 = FALSE;
    TexVramTask *o = PlayerHead_GetTexTask(p, r6);
    u8 st = o->state;
    if (Unk_0205d4e4_IsTwo(st)) {
        r6 = TRUE;
    } else if (!Unk_0205d4e4_IsOne(st)) {
        o->requestTexResource((u32 *)NNS_G3dGetTex(PlayerHead_GetModelFile(p, 0)), 1);
    }
    if (PlayerHead_GetModelId(p, 1) < 0x9e) {
        void *d = PlayerHead_GetModelFile(p, 1);
        TexVramTask *o2 = PlayerHead_GetTexTask(p, 1);
        u8 st2 = o2->state;
        if (Unk_0205d4e4_IsTwo(st2)) {
            r4 = TRUE;
        } else if (!Unk_0205d4e4_IsOne(st2)) {
            o2->requestTexResource((u32 *)NNS_G3dGetTex(d), 1);
        }
    } else {
        r4 = TRUE;
    }
    if (r6 && r4) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void *PlayerHead_GetBuffer(u8 *p) {
    return MGR->getBuffer(*p);
}
extern "C" void *PlayerHead_GetModelFile(u8 *p, s32 j) {
    return MGR->getModelFile(*p, j);
}
extern "C" void PlayerHead_SetModelFile(u8 *p, s32 j, void *v) {
    MGR->setModelFile(*p, j, v);
}
extern "C" TexVramSlot *PlayerHead_GetVramSlot(u8 *p, s32 j) {
    return MGR->getVramSlot(*p, j);
}
extern "C" TexVramTask *PlayerHead_GetTexTask(u8 *p, s32 j) {
    return MGR->getTexTask(*p, j);
}
extern "C" s32 PlayerHead_GetModelId(u8 *p, s32 j) {
    return MGR->getModelId(*p, j);
}
extern "C" void PlayerHead_SetModelId(u8 *p, s32 j, u32 v) {
    MGR->setModelId(*p, j, v);
}
