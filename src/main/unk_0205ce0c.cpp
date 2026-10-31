#include "types.h"
#include "net/CommManager.h"
#include "actor/CharaFaceAnimRef.h"
#include "sys/Heap.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205ce0c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02082d74.h"


struct CharaFaceAnimPool {
    u8 *ptr[9];
    u16 a[2][9];
    u16 b[2][9];
    CharaFaceAnimPool();
    ~CharaFaceAnimPool();
    void setLoadedSize(u32 i, u32 j, u32 val);
    u32 getLoadedSize(u32 i, u32 j);
    u32 findAnim(u32 x);
    void setAnimId(u32 i, u32 j, u32 val);
    u32 getAnimId(u32 i, u32 j);
    u8 *getAnimBuffer(u32 i, u32 j);
    void freeBuffers();
    void allocBuffers();
};

extern "C" {
extern CommManager *gCommManager;
extern const u8 sCharaFaceAnimKinds[];

u32 Scene_GetCurrent();
u32 Scene_GetMaxPlayers(u32 a);
u32 Scene_GetMaxCharacters(u32 a);
void MI_CpuCopy8(const void *src, void *dst, u32 n);

}

extern "C" void CharaFaceAnimPool_Create(Heap *parent) {
    CharaFaceAnimHeap_Create(parent);
    sCharaFaceAnimPool.allocBuffers();
    if (gCharaFaceAnimHeap) ((Heap *)(gCharaFaceAnimHeap))->adjust();
}

extern "C" void CharaFaceAnimPool_Destroy() {
    sCharaFaceAnimPool.freeBuffers();
    CharaFaceAnimHeap_Destroy();
}

extern "C" char *CharaFaceAnim_GetPath(u32 x) {
    Str_SPrintf(sCharaFaceAnimPathBuf, "/FcAnm/%d/%d.nsbtp", x >> 5, x);
    return sCharaFaceAnimPathBuf;
}

extern "C" u32 CharaFaceAnim_GetAnimSize() { return 0x118; }
extern "C" u32 CharaFaceAnim_GetSlotSize() { return CharaFaceAnim_GetAnimSize() + 0x118; }
extern "C" u32 CharaFaceAnim_GetKind(u32 x) { return sCharaFaceAnimKinds[x]; }

CharaFaceAnimPool::CharaFaceAnimPool() {
    for (s32 i = 0; i < 9; i++) {
        for (s32 j = 0; j < 2; j++) b[j][i] = 0x16f;
    }
}

CharaFaceAnimPool::~CharaFaceAnimPool() {}

void CharaFaceAnimPool::allocBuffers() {
    Heap *heap = (Heap *)gCharaFaceAnimHeap;
    u32 n, i, m;
    n = gCommManager->memberCount;
    m = Scene_GetMaxPlayers(Scene_GetCurrent());
    if (n < m) m = n;
    for (i = 0; i < m; i++) {
        ptr[i] = (u8 *)Heap_AllocAligned(heap, CharaFaceAnim_GetSlotSize(), 4);
    }
    if (m == 0) m = 1;
    u32 q = Scene_GetMaxCharacters(Scene_GetCurrent());
    m = (q + NpcSpawn_GetSpNpcSlotCount()) - m;
    u32 al = 4;
    for (i = al; i < m + 4; i++) {
        ptr[i] = (u8 *)Heap_AllocAligned(heap, CharaFaceAnim_GetSlotSize(), al);
    }
}

void CharaFaceAnimPool::freeBuffers() {
    for (s32 i = 0; i < 9; i++) {
        ptr[i] = NULL;
        for (s32 j = 0; j < 2; j++) {
            b[j][i] = 0x16f;
            a[j][i] = 0;
        }
    }
    if (gCharaFaceAnimHeap) ((Heap *)(gCharaFaceAnimHeap))->freeAll();
}

u8 *CharaFaceAnimPool::getAnimBuffer(u32 i, u32 j) {
    if (j == 1) {
        u8 *t = ptr[i];
        return t + CharaFaceAnim_GetAnimSize();
    }
    return ptr[i];
}

u32 CharaFaceAnimPool::getAnimId(u32 i, u32 j) { return b[j][i]; }
void CharaFaceAnimPool::setAnimId(u32 i, u32 j, u32 val) { b[j][i] = val; }

u32 CharaFaceAnimPool::findAnim(u32 x) {
    u32 j = CharaFaceAnim_GetKind(x);
    s32 i;
    for (i = 0; i < 9; i++) {
        s32 c = getAnimId(i, j);
        if (c == x) return i;
    }
    return 9;
}

u32 CharaFaceAnimPool::getLoadedSize(u32 i, u32 j) { return a[j][i]; }
void CharaFaceAnimPool::setLoadedSize(u32 i, u32 j, u32 val) { a[j][i] = val; }

CharaFaceAnimRef::CharaFaceAnimRef() { v = 9; }
CharaFaceAnimRef::~CharaFaceAnimRef() {}

void CharaFaceAnimRef::assign(u32 x) {
    setSlot(x);
    load(0x16f, 0x16f, 0, 0);
}

void CharaFaceAnimRef::setSlot(u32 x) { v = x; }
void *CharaFaceAnimRef::getAnimBuffer(u32 j) { return sCharaFaceAnimPool.getAnimBuffer(v, j); }
void *CharaFaceAnimRef::getEyeAnimBuffer() { return getAnimBuffer(0); }
void *CharaFaceAnimRef::getMouthAnimBuffer() { return getAnimBuffer(1); }

void CharaFaceAnimRef::loadAnim(s32 a, s32 b, s32 c) {
    u32 st = v;
    u32 j = CharaFaceAnim_GetKind(a);
    if (c == 0) {
        if (a == sCharaFaceAnimPool.getAnimId(st, j)) return;
    }
    u8 *buf = sCharaFaceAnimPool.getAnimBuffer(st, j);
    s32 size;
    if (j == 0) {
        size = CharaFaceAnim_GetAnimSize();
    } else {
        size = CharaFaceAnim_GetSlotSize() - CharaFaceAnim_GetAnimSize();
    }
    if (b != 0) {
        u32 k = sCharaFaceAnimPool.findAnim(a);
        if (k != 9) {
            u8 *src = sCharaFaceAnimPool.getAnimBuffer(k, j);
            u32 n = sCharaFaceAnimPool.getLoadedSize(k, j);
            if (src != NULL && n != 0) {
                MI_CpuCopy8(src, buf, n);
                sCharaFaceAnimPool.setAnimId(st, j, a);
                sCharaFaceAnimPool.setLoadedSize(st, j, n);
            }
        }
    }
    s32 got = File_LoadToBuffer(CharaFaceAnim_GetPath(a), buf, size);
    if (got != 0) {
        sCharaFaceAnimPool.setAnimId(st, j, a);
        sCharaFaceAnimPool.setLoadedSize(st, j, got);
    }
}

void CharaFaceAnimRef::load(s32 a, s32 b, s32 c, s32 d) {
    u32 st = v;
    if (a >= 0x16f) {
        sCharaFaceAnimPool.setAnimId(st, 0, 0x16f);
        sCharaFaceAnimPool.setLoadedSize(st, 0, 0);
    } else {
        loadAnim(a, c, d);
    }
    if (b >= 0x16f) {
        sCharaFaceAnimPool.setAnimId(st, 1, 0x16f);
        sCharaFaceAnimPool.setLoadedSize(st, 1, 0);
    } else {
        loadAnim(b, c, d);
    }
}

extern const u8 sCharaFaceAnimKinds[0x170];
const u8 sCharaFaceAnimKinds[0x170] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
};

char sCharaFaceAnimPathBuf[0x14];
CharaFaceAnimPool sCharaFaceAnimPool;
