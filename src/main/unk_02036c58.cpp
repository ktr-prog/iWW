#include "sys/NNSFndArchive.h"
#include "host_labels.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "game/Unk_02036c60_Vec.h"
#include "game/Unk_02037674_V3.h"
#include "game/Unk_021e5890_T.h"
#include "gfx/BgModelCache.h"
#include "town/TownMap.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02101048.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02036c58.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"

extern "C" const u32 data_020c8b9c;
extern "C" const u32 data_020c8ba0;

extern "C" {
s32 NNS_FndMountArchive(NNSFndArchive *, const void *, void *);
void NNS_FndUnmountArchive(NNSFndArchive *);
void *NNS_G3dGetMdlSet(void *);
void *func_021065dc(void *);
void *func_021065f8(void *, s32);
void *func_02106618(void *);
void *func_02106634(void *, s32);
void *func_02106654(void *);
void *func_02106670(void *, s32);
void *func_02106690(void *);
void *func_021066ac(void *, s32);
void *NNS_G3dGetTex(void *);
void Gfx3d_LoadTexAndPltt(void *, s32);
void *Gfx3d_CopyTex(void *, void *);
void MI_CpuCopy8(void *, void *, u32);
#define data_021e5890 HOST_LABEL(Unk_021e5890_T *, data_021e5890)
}

extern "C" {
#define gSaveTownMap HOST_LABEL(TownMap *, gSaveTownMap)
s32 Scene_GetCurrent(void);
}
extern const u8 sBgHeapSizeByRoom[];




extern "C" void *BgModel_LoadFile(const char *a, u32 *b) {
    return File_LoadAlloc(a, gBgHeap, 4, b);
}

BgModelCache::BgModelCache() {
    clearEntries();
}

BgModelCache::~BgModelCache() {}

void BgModelCache::clearEntries() {
    BgAcreModel *p; BgAcreBcl *q; u32 i; u32 j;
    p = acres;
    for (i = 0; i < 0x1f; p++, i++) {
        p->acreId = 0xffff;
        p->arc = 0;
        p->mdl = 0;
        p->bcl = 0;
        p->jntAnm = 0;
        p->matAnm = 0;
        p->texSrtAnm = 0;
        p->bsd = 0;
        p->tex = 0;
        p->mgt = 0;
        p->mgtCount = 0;
    }
    q = bclCache;
    for (j = 0; j < 9; q++, j++) {
        q->acreId = 0xffff;
        q->bcl = 0;
    }
    groundTex = 0;
    groundMatAnm = 0;
    groundTexSrtAnm = 0;
    riverPatAnm = 0;
    riverPatTex = 0;
    withAnims = 0;
    heapSize = 0;
    unk_620 = 0;
    unk_624 = 0;
    unk_628 = 0;
    unk_62c = 0;
}

BOOL BgModelCache::setup(u32 flag) {
    s32 t = Scene_GetCurrent();
    if (t == 0x2c) {
        gSaveTownMap.updateGroundSeason();
    }
    clearEntries();
    withAnims = flag;
    t = Scene_GetCurrent();
    u32 v;
    if ((u32)t < 0x33) {
        v = sBgHeapSizeByRoom[t];
    } else {
        v = 0xac;
    }
    heapSize = (u8)v << 10;
    BgHeap_Create(heapSize, 0);
    if (flag != 0 || t == 0xb || t == 0x2f || (u8)(t + 0xf4) <= 2) {
        loadGroundTexture();
    }
    if (flag != 0) {
        loadGroundAnims();
    }
    return TRUE;
}

extern "C" s32 BgModel_GetGrassType(void *)
{
    return gSaveTownMap.getGrassType();
}

void BgModelCache::loadGroundTexture()
{
    char buf[0x20];
    s32 a = BgModel_GetGrassType(this);
    s32 b = BgModel_GetGrassType(this);
    void *p;
    Str_SPrintf(buf, "/bg/ct%d/grd_set%d%c.nsbtx", a, b, ((u32)(data_021e5890.groundSeasonBits << 24) >> 26) + 0x61);
    p = File_LoadAlloc(buf, gCurrentHeap, -4, 0);
    void **q = &groundTex;
    *q = NNS_G3dGetTex(p);
    Gfx3d_LoadTexAndPltt(*q, 0);
    groundTex = Gfx3d_CopyTex(groundTex, gBgHeap);
    if (p) {
        Mem_Free(p);
    }
}

void BgModelCache::loadGroundAnims()
{
    NNSFndArchive file;
    void *p = BgModel_LoadFile("/bg/grd_anm.arc", 0);
    if (NNS_FndMountArchive(&file, "BG", p)) {
        groundMatAnm = func_02106634(func_02106618(NNS_FndGetArchiveFileByName("BG:a/grd_set.nsbma")), 0);
        groundTexSrtAnm = func_02106670(func_02106654(NNS_FndGetArchiveFileByName("BG:a/grd_set.nsbta")), 0);
        riverPatAnm = func_021066ac(func_02106690(NNS_FndGetArchiveFileByName("BG:a/riv.nsbtp")), 0);
        riverPatTex = NNS_G3dGetTex(NNS_FndGetArchiveFileByName("BG:a/riv_itp.nsbtx"));
        beBPatAnm = func_021066ac(func_02106690(NNS_FndGetArchiveFileByName("BG:a/beB.nsbtp")), 0);
        beBPatTex = NNS_G3dGetTex(NNS_FndGetArchiveFileByName("BG:a/beB_itp.nsbtx"));
        NNS_FndUnmountArchive(&file);
    }
}

void *BgModel_LoadBcl(s32 id, void *heap)
{
    char buf[0x20];
    NNSFndArchive file;
    void *p, *r, *t;
    Str_SPrintf(buf, "/bg/a%d/%04x.arc", id >> 4, id);
    p = File_LoadAlloc(buf, gCurrentHeap, -4, 0);
    r = 0;
    if (NNS_FndMountArchive(&file, "BG", p)) {
        t = NNS_FndGetArchiveFileByName("BG:a/bcl/bcl0");
        NNS_FndUnmountArchive(&file);
        r = Heap_Alloc((Heap *)heap, 0x180);
        MI_CpuCopy8(t, r, 0x180);
    }
    if (p) {
        Mem_Free(p);
    }
    return r;
}

void *BgModelCache::getAcreBcl(s32 id)
{
    u32 i, j;
    void *r = 0;
    BgAcreModel *e = acres;
    BgAcreBcl *s;
    for (i = 0; i < 0x1f; e++, i++) {
        if (e->acreId == id) {
            r = e->bcl;
            break;
        }
    }
    s = bclCache;
    for (j = 0; j < 9; s++, j++) {
        if (s->bcl == 0) {
            if (r) {
                s->acreId = id;
                s->bcl = r;
            } else {
                s->bcl = BgModel_LoadBcl(id, gBgHeap);
                s->acreId = id;
            }
            return s->bcl;
        }
        if (s->acreId == id) {
            return s->bcl;
        }
    }
    return 0;
}

BgAcreModel *BgModelCache::getAcre(s32 id)
{
    void *heap = gBgHeap;
    BgAcreModel *e = acres;
    struct { void *tmp; char buf[0x20]; NNSFndArchive file; } l;
    u32 i;
    for (i = 0; i < 0x1f; e++, i++) {
        if (e->arc == 0) {
            s32 hi = id >> 4;
            void *p;
            Str_SPrintf(l.buf, "/bg/a%d/%04x.arc", hi, id);
            e->arc = BgModel_LoadFile(l.buf, &e->arcSize);
            if (NNS_FndMountArchive(&l.file, "BG", e->arc)) {
                u8 *q = (u8 *)NNS_G3dGetMdlSet(NNS_FndGetArchiveFileByName("BG:a/bmd/bmd0"));
                e->mdl = q + *(s32 *)(q + *(u16 *)(q + 0xe) + 0xc);
                e->bcl = NNS_FndGetArchiveFileByName("BG:a/bcl/bcl0");
                e->bsd = NNS_FndGetArchiveFileByName("BG:a/bsd/bsd0");
                p = NNS_FndGetArchiveFileByName("BG:a/bca/bca0");
                if (p) {
                    e->jntAnm = func_021065f8(func_021065dc(p), 0);
                }
                p = NNS_FndGetArchiveFileByName("BG:a/bma/bma0");
                if (p) {
                    e->matAnm = func_02106634(func_02106618(p), 0);
                }
                p = NNS_FndGetArchiveFileByName("BG:a/bta/bta0");
                if (p) {
                    e->texSrtAnm = func_02106670(func_02106654(p), 0);
                }
                p = NNS_FndGetArchiveFileByName("BG:a/mgt/mgt0");
                if (p) {
                    e->mgt = (u8 *)p + 2;
                    e->mgtCount = *(s16 *)p;
                }
                NNS_FndUnmountArchive(&l.file);
            }
            if (((id & 0xf000) >> 12) == 1) {
                Str_SPrintf(l.buf, "/bg/t%d/%04x.nsbtx", hi, id);
                p = File_LoadAlloc(l.buf, gCurrentHeap, -4, 0);
                if (p) {
                    l.tmp = NNS_G3dGetTex(p);
                    Gfx3d_LoadTexAndPltt(l.tmp, 0);
                    e->tex = Gfx3d_CopyTex(l.tmp, heap);
                    if (p) {
                        Mem_Free(p);
                    }
                }
            }
            e->acreId = id;
            return e;
        }
        if (e->acreId == id) {
            return e;
        }
    }
    return 0;
}

BOOL BgModelCache::reset()
{
    BgAcreModel *e = acres;
    BgAcreBcl *s;
    u32 i, j;
    for (i = 0; i < 0x1f; e++, i++) {
        e->acreId = 0xffff;
        e->arc = 0;
        e->mdl = 0;
        e->bcl = 0;
        e->jntAnm = 0;
        e->matAnm = 0;
        e->texSrtAnm = 0;
        e->bsd = 0;
        e->mgt = 0;
        e->mgtCount = 0;
        e->tex = 0;
    }
    s = bclCache;
    for (j = 0; j < 9; s++, j++) {
        s->acreId = 0xffff;
        s->bcl = 0;
    }
    groundTex = 0;
    withAnims = 0;
    heapSize = 0;
    BgHeap_Destroy();
    return TRUE;
}

void *BgModelCache::getGroundTex() { return groundTex; }

void *BgModelCache::getGroundMatAnm() { return groundMatAnm; }

void *BgModelCache::getGroundTexSrtAnm() { return groundTexSrtAnm; }

void *BgModelCache::getRiverPatAnm() { return riverPatAnm; }

void *BgModelCache::getRiverPatTex() { return riverPatTex; }

void *BgModelCache::getBeBPatAnm() { return beBPatAnm; }

void *BgModelCache::getBeBPatTex() { return beBPatTex; }

extern "C" s32 BgMgt_GetCount(s16 *p)
{
    return *p;
}

VecFx32 BgMgt_GetEntry(u8 *base, s32 idx)
{
    VecFx32 v;
    BgMgtEntry *e = (BgMgtEntry *)(base + 2);
    v.x = e[idx].a;
    v.y = e[idx].b << 12;
    v.z = e[idx].c << 12;
    return v;
}

extern "C" BgModelCache *BgModelCache_Get(void)
{
    return &gBgModelCache;
}

const u8 sBgHeapSizeByRoom[0x34] = {
    0xac, 0x0a, 0x0a, 0x0a, 0x0a, 0x0b, 0x0e, 0x0e, 0x0e, 0x14, 0x18, 0x2a, 0x2a, 0x2a, 0x2a, 0x0c, 0x19, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0c, 0x0c, 0x0f, 0x11, 0x0c, 0x19, 0x0c, 0x6e, 0x1a, 0x1f, 0x17, 0x0c, 0x0d, 0x12, 0x13, 0x37, 0xac, 0xac, 0xac, 0x28, 0x14, 0x2a, 0x32, 0xac, 0x14, 0x00
};

BgModelCache gBgModelCache;


const u32 data_020c8b9c = 0x7c8;
const u32 data_020c8ba0 = 0x3648;
