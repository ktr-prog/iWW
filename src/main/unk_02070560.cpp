#include "gfx/TexPatVramAnim.h"
#include "host_labels.h"
#include "host_shared_calls.h"
#include "gfx/TexPatVramUploader.h"
#include "gfx/PatternTexCache.h"
#include "uptr.h"
#include "town/TownBlockCell.h"
#include "types.h"
#include "save/PatternOrder.h"
#include "game/Unk_020702ec_Date.h"
#include "save/EncodedName8.h"
#include "sys/OverlayHandle.h"
#include "save/MuseumData.h"
#include "sys/RecordFile.h"
#include "sys/new.h"
#include "save/Unk_020942c8.h"
#include "save/Pattern.h"
#include "save/BlancaFaceRecord.h"
#include "save/TownId.h"
#include "save/TownStyleRecordView.h"
#include "room/HouseRoom.h"
#include "talk/EncodedString16Buf.h"
#include "talk/MsgString.h"
#include "talk/MsgString9B.h"
#include "talk/MsgString9C.h"
#include "item/ItemId.h"
#include "item/ItemName.h"
#include "npc/VillagerId.h"
#include "npc/VillagerPlan.h"
#include "save/VillagerData.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "room/HouseData.h"
#include "save/SaveData.h"
#include "town/TownBlockMap.h"
#include "net/CommManager.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_0203c638.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_020637e4.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/main/unk_02070560.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov003/unk_ov003_02214dfc.h"
#include "proto/ov003/unk_ov003_022187fc.h"
#include "proto/main/unk_0204cc1c.h"


class StrBuf;
class GateHouse;
struct NNSG3dResTex;
class TexVramSlot;

extern "C" {
void MI_CpuCopy8(const void *src, void *dst, u32 n);
BOOL EncodedString_SetRaw(StrBuf *buf, const void *src, s32 len);
u32 Scene_GetCurrent();
BOOL Scene_InTown();
BOOL Gfx3d_LoadTexAndPltt(NNSG3dResTex *a, TexVramSlot *b);
void *ResCache_GetTex(void *a, u32 key);
u8 *SaveVillagers_Get(u8 *base, s32 idx);
u8 *Villager_GetFashionTaste(VillagerData *a);
void *Villager_GetPlan(VillagerData *a);
u16 *AbleShop_GetItem(void *s, u32 a, u16 *out);
void Item_FromPlacedForm(u16 *out, u16 *in);
u16 *MapBlock_GetItemPtr(void *cell, u32 x, u32 y, u32 z);
BOOL MapBlock_SetItem(void *cell, u16 *t, u32 x, u32 y, u8 z);

extern SaveData gSaveData;
extern CommManager *gCommManager;
extern u8 gFieldSceneKind[];
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
#define gSaveAbleSistersPatterns HOST_LABEL(AbleSistersPatterns *, gSaveAbleSistersPatterns)
#define gSaveBlancaFace HOST_LABEL(BlancaFaceRecord *, gSaveBlancaFace)
#define gSaveTownFlag HOST_LABEL(TownStyleRecordView *, gSaveTownFlag)
#define gSaveHouse HOST_LABEL(HouseData *, gSaveHouse)
#define data_021ed2d4 HOST_LABEL(u8 (*)[], data_021ed2d4)
extern u16 data_020cb6f4;
extern u16 data_020d03cc;
extern u16 data_020d03d0;
extern u16 data_020d03d4;
extern Pattern *(*const sPatternSourceGetters[10])(s32);
}

static inline PlayerId *AsPlayerId(Unk_020942c8 *p) { return (PlayerId *)(void *)p; }
static inline Unk_020942c8 *AsIdRecord(PlayerId *p) { return (Unk_020942c8 *)(void *)p; }
static inline Unk_020942c8 *TownIdOf(Unk_020942c8 *p) { return (Unk_020942c8 *)PlayerId_GetTownId(p); }


struct Unk_02070e4c_Bits {
    u32 a : 4;
    u32 b : 10;
    u32 c : 4;
    u32 d : 10;
    u32 e : 1;
    u32 f : 3;
};

struct PatternCopyBytes8 { u8 v[8]; };
struct PatternCopyBytes16 { u8 v[16]; };
struct PatternCopyPixels { u32 v[128]; };
struct PatternCopyView {
    PatternCopyPixels a;
    u16 b;
    PatternCopyBytes8 c;
    u16 d;
    PatternCopyBytes8 e;
    s8 f;
    u8 g;
    PatternCopyBytes16 h;
    u8 i;
};

BOOL PatternInfo::infoEquals(PatternInfo *o) {
    if (tastePalette.lo == o->tastePalette.lo && tastePalette.hi == o->tastePalette.hi && townId == o->townId &&
        memcmp(&townName, &o->townName, 8) == 0 && AsPlayerId(this)->equals(AsPlayerId(o)) != 0) {
        for (u32 i = 0; i < 16; i++) {
            if (title.b[i] != o->title.b[i]) return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}
PatternInfo::PatternInfo() {}
PatternInfo::~PatternInfo() {}
u8 *PatternInfo::getPaletteData() {
    PatternTexCache *p = PatternTexCache_Get();
    return p->getPalette(getPalette());
}
u8 PatternInfo::getPalette() {
    u8 f = *(u8 *)&tastePalette;
    u32 t = (u32)(f << 24) >> 28;
    t &= 0xf;
    return t;
}
void PatternInfo::setPalette(u32 v) {
    u8 &f = *(u8 *)&tastePalette;
    u32 t = v & 0xf;
    f = (f & ~0xf0) | ((u8)t & 0xf) << 4;
}
void PatternInfo::setAuthorToCurrentPlayer() {
    setAuthor(AsIdRecord(PlayerData_GetCurrent()->getPlayerId()));
}
void PatternInfo::setAuthor(Unk_020942c8 *src) {
    townId = src->townId;
    townName = src->townName;
    playerId = src->playerId;
    playerName = src->playerName;
    gender = src->gender;
    unk_15 = src->unk_15;
}
Unk_020942c8 *PatternInfo::getAuthor() { return this; }
void PatternInfo::getTitle(void *x) {
    EncodedString16Buf s;
    getTitleEncoded(&s);
    ((MsgString *)x)->fromEncoded(&s, 0, 0);
}
void PatternInfo::getTitleEncoded(EncodedString16Buf *o) {
    EncodedString_SetRaw((StrBuf *)(void *)o, title.b, 16);
}
void PatternInfo::getTitleRaw(u8 *dst) {
    *(EncodedTitle16 *)dst = *(EncodedTitle16 *)&title;
}
void PatternInfo::setTitle(void *x) {
    EncodedString16Buf s;
    s.fromMsgString((MsgString *)x);
    setTitleEncoded(&s);
}
void PatternInfo::setTitleEncoded(EncodedString16Buf *o) {
    o->copyTo(title.b, 16);
}
void PatternInfo::setTitleRaw(u8 *src) {
    *(EncodedTitle16 *)&title = *(EncodedTitle16 *)src;
}
u8 PatternInfo::getTaste() {
    return tastePalette.lo;
}
void PatternInfo::setTaste(u32 v) {
    u8 &f = *(u8 *)&tastePalette;
    f = (f & ~0xf) | ((u8)v & 0xf);
}
BOOL Pattern::equals(Pattern *o) {
    if (info.infoEquals(&o->info)) {
        u32 *p = (u32 *)pixels;
        u32 *q = (u32 *)o->pixels;
        for (u32 i = 0; i < 0x80; i++) {
            if (*p != *q) return FALSE;
            p++;
            q++;
        }
        return TRUE;
    }
    return FALSE;
}
Pattern::Pattern() {}
Pattern::~Pattern() {}
u8 *Pattern::getPixels() { return (u8 *)pixels; }
void Pattern::setPixels(void *dst) {
    MI_CpuCopy8(dst, getPixels(), 0x200);
}
void Pattern::fill(u32 v) {
    u8 b = v | (v << 4);
    u32 w = (b << 24) | ((b << 16) | (b | (b << 8)));
    u32 *p = (u32 *)pixels;
    u32 *end = (u32 *)(pixels + 0x40);
    while (p < end) *p++ = w;
}
PatternInfo *Pattern::getInfo() {
    return &info;
}
PlayerPatterns::PlayerPatterns() {}
PlayerPatterns::~PlayerPatterns() {}
void PlayerPatterns::initDefaultPatterns(Unk_020942c8 *a) {
    void *t = Mem_Alloc(0x1000);
    if (t) {
        if (t) PlayerPatternDefaults_Ctor(t);
        PlayerPatternDefaults_Load(t);
        for (s16 i = 0; (u32)i < 8; i++) {
            PlayerPatternDefaults_Extract(t, getPattern(i)->getPixels(), i);
            PatternPresetInfoFile *tbl = PatternPresetInfo_Get();
            PatternPresetInfo_Apply(tbl, getPattern(i)->getInfo(), i);
            getPattern(i)->getInfo()->setAuthor(a);
        }
        Mem_Free(t);
    }
    patternOrder.reset();
}
void PlayerPatterns::replaceAuthorTown(Unk_020942c8 *a, Unk_020942c8 *b) {
    for (u8 i = 0; i < 8; i++) {
        PatternInfo *s = getPattern(i)->getInfo();
        Unk_020942c8 *base = s->getAuthor();
        Unk_020942c8 *p = TownIdOf(base);
        if (p->townId == b->townId) {
            if (memcmp(&p->townName, &b->townName, 8) == 0) {
                if (AsPlayerId(base)->equals(AsPlayerId(a))) {
                    AsPlayerId(s->getAuthor())->setTown(AsPlayerId(TownIdOf(a)));
                }
            }
        }
    }
}
Pattern *PlayerPatterns::getPattern(u8 i) {
    return &patterns[i & 7];
}
Pattern *PlayerPatterns::getPatternByOrder(u32 i) {
    return &patterns[patternOrder.getSlot(i)];
}
PatternOrder *PlayerPatterns::getPatternOrder() {
    return &patternOrder;
}
PatternOrder::PatternOrder() {}
PatternOrder::~PatternOrder() {}
void PatternOrder::reset() {
    for (u8 i = 0; i < 8; i++) slots[i] = i;
}
void PatternOrder::swap(u32 a, u32 b) {
    u8 t = slots[a & 7];
    slots[a & 7] = slots[b & 7];
    slots[b & 7] = t;
}
u32 PatternOrder::getSlot(u32 i) {
    return (u8)(slots[i & 7] & 7);
}
AbleSistersPatterns::AbleSistersPatterns() {}
AbleSistersPatterns::~AbleSistersPatterns() {}
void AbleSistersPatterns::initDefaultPatterns() {
    void *t = Mem_Alloc(0x1000);
    if (t) {
        if (t) AblePatternDefaults_Ctor(t);
        AblePatternDefaults_Load(t);
        u16 g1 = data_020cb6f4;
        u16 g2 = data_020d03cc;
        for (s16 i = 0; (u32)i < 8; i++) {
            AblePatternDefaults_Extract(t, getPattern(i)->getPixels(), i);
            PatternPresetInfoFile *tbl = PatternPresetInfo_Get();
            PatternPresetInfo_Apply(tbl, getPattern(i)->getInfo(), i + 8);
            TownId_SetId(&TownIdOf(getPattern(i)->getInfo()->getAuthor())->townId, g1);
            AsPlayerId(getPattern(i)->getInfo()->getAuthor())->setId(g2);
        }
        Mem_Free(t);
    }
}
Pattern *AbleSistersPatterns::getPattern(u8 i) {
    return &patterns[i & 7];
}
TownFlagPattern::TownFlagPattern() {}
TownFlagPattern::~TownFlagPattern() {}

static inline BOOL Unk_0207116c_Eq1(u8 *p) { return *p == 1 ? TRUE : FALSE; }
static inline BOOL Unk_0207116c_Eq0(u8 *p) { return *p == 0 ? TRUE : FALSE; }

extern "C" void Pattern_CopyFields(PatternCopyView *dst, PatternCopyView *src);

extern "C" void TownFlagPattern_InitDefault(void *self) {
    void *buf = Mem_Alloc(0x200);
    if (buf != 0) {
        if (buf != 0) TownFlagPatternDefault_Ctor(buf);
        TownFlagPatternDefault_Load(buf);
        TownFlagPatternDefault_Extract(buf, ((Pattern *)TownFlagPattern_GetPattern(self))->getPixels());
        PatternPresetInfoFile *g = PatternPresetInfo_Get();
        PatternPresetInfo_Apply(g, ((Pattern *)TownFlagPattern_GetPattern(self))->getInfo(), 0x10);
        TownId_Assign(PlayerId_GetTownId(((Pattern *)TownFlagPattern_GetPattern(self))->getInfo()->getAuthor()),
                      gSaveData.townId);
        AsPlayerId(((Pattern *)TownFlagPattern_GetPattern(self))->getInfo()->getAuthor())->setId(data_020d03d4);
        Mem_Free(buf);
    }
}
extern "C" void *TownFlagPattern_GetPattern(void *p) { return p; }
extern "C" void Pattern_CopyFields(PatternCopyView *dst, PatternCopyView *src) {
    dst->a = src->a;
    dst->b = src->b;
    dst->c = src->c;
    dst->d = src->d;
    dst->e = src->e;
    dst->f = src->f;
    dst->g = src->g;
    dst->h = src->h;
    dst->i = src->i;
}
PresetPatternBuffer::PresetPatternBuffer() {}
PresetPatternBuffer::~PresetPatternBuffer() {}
BOOL PresetPatternBuffer::load(s32 n) {
    if ((u32)n < 0x20) {
        void *buf = Mem_Alloc(0x200);
        if (buf != 0) {
            if (buf != 0) PresetPatternFile_Ctor(buf);
            PresetPatternFile_Load(buf, n);
            PresetPatternFile_Extract(buf, getPattern()->getPixels());
            PatternPresetInfoFile *g = PatternPresetInfo_Get();
            PatternPresetInfo_Apply(g, getPattern()->getInfo(), n + 0x12);
            TownId_SetId(&TownIdOf(getPattern()->getInfo()->getAuthor())->townId, data_020cb6f4);
            AsPlayerId(getPattern()->getInfo()->getAuthor())->setId(data_020d03d0);
            Mem_Free(buf);
        }
        return TRUE;
    }
    return FALSE;
}
Pattern *PresetPatternBuffer::getPattern() { return &pattern; }
extern "C" PresetPatternBuffer *PresetPatternBuffer_Get(void) { return &sPresetPatternBuffer; }
void PatternTexCache::reset() {
    paletteFile.clear();
    PatternTexKeys_Clear(&texKeys);
    PatternTexCache_ClearDirty(this);
}
PatternTexCache::PatternTexCache() { reset(); }
PatternTexCache::~PatternTexCache() {}
extern "C" void PatternTexCache_ClearDirty(PatternTexCache *p) {
    u32 i;
    for (i = 0; i < 4; i++) data_021cbcac[i] = 0;
    sAbleDisplayDirtyBits = 0;
}
void PatternTexCache::setAbleDirty(s32 bit) { sAbleDisplayDirtyBits |= 1 << bit; }
BOOL PatternTexCache::testAndClearAbleDirty(s32 bit) {
    BOOL r;
    if (((sAbleDisplayDirtyBits >> bit) & 1) == 0) r = FALSE; else r = TRUE;
    sAbleDisplayDirtyBits &= ~(1 << bit);
    return r;
}
void PatternTexCache::load() {
    reset();
    paletteFile.load();
    createTextures();
    Heap *h = gCurrentHeap;
    ClothTexStorage *a, *c;
    TexPatVramTasks *b, *d;
    u32 i, j;
    sPlayerPatternTexWork = (ClothTexStorage *)Heap_Alloc(h, 8 * sizeof(ClothTexStorage));
    b = (TexPatVramTasks *)Heap_Alloc(h, 8 * sizeof(TexPatVramTasks));
    sPlayerPatternVramTasks = b;
    a = sPlayerPatternTexWork;
    for (i = 0; i < 8; i++) {
        if (a != 0) ClothTex_Construct();
        if (b != 0) new (b) TexPatVramTasks();
        a++;
        b++;
    }
    sAblePatternTexWork = (ClothTexStorage *)Heap_Alloc(h, 8 * sizeof(ClothTexStorage));
    d = (TexPatVramTasks *)Heap_Alloc(h, 8 * sizeof(TexPatVramTasks));
    sAblePatternVramTasks = d;
    c = sAblePatternTexWork;
    for (j = 0; j < 8; j++) {
        if (c != 0) ClothTex_Construct();
        if (d != 0) new (d) TexPatVramTasks();
        c++;
        d++;
    }
}
void PatternTexCache::unload() {
    paletteFile.unload();
    PatternTexCache_ResetKeys(this);
    Heap *h = gCurrentHeap;
    if (sPlayerPatternTexWork != 0) {
        Heap_Free(h, sPlayerPatternTexWork);
        sPlayerPatternTexWork = 0;
    }
    if (sPlayerPatternVramTasks != 0) {
        Heap_Free(h, sPlayerPatternVramTasks);
        sPlayerPatternVramTasks = 0;
    }
    if (sAblePatternTexWork != 0) {
        Heap_Free(h, sAblePatternTexWork);
        sAblePatternTexWork = 0;
    }
    if (sAblePatternVramTasks != 0) {
        Heap_Free(h, sAblePatternVramTasks);
        sAblePatternVramTasks = 0;
    }
}
u8 *PatternTexCache::getPlayerTexKey(s32 a, s32 b) { return PatternTexKeys_GetPlayer(&texKeys, a, b); }
u8 *PatternTexCache::getAbleTexKey(s32 i) { return PatternTexKeys_GetAble(&texKeys, i); }
u8 *PatternTexCache::getPalette(s32 i) { return PatternPaletteFile_GetPalette(&paletteFile, i); }
extern "C" PatternTexCache *PatternTexCache_Get(void) { return &sPatternTexCache; }
void PatternPaletteFile::clear() {
    fileData = 0;
    for (u32 i = 0; i < 16; i++) palettes[i] = 0;
}
PatternPaletteFile::PatternPaletteFile() { clear(); }
PatternPaletteFile::~PatternPaletteFile() {}
void PatternPaletteFile::load() {
    if (fileData == 0) {
        fileData = (u8 *)File_Load("/menu/desi/b_myd_ten0_obj.bpl");
        if (fileData != 0) {
            for (u32 i = 0; i < 16; i++) palettes[i] = fileData + i * 32;
        }
    }
}
void PatternPaletteFile::unload() {
    if (fileData != 0) {
        Mem_Free(fileData);
        fileData = 0;
    }
    clear();
}
extern "C" u8 *PatternPaletteFile_GetPalette(PatternPaletteFile *self, s32 i) { return self->palettes[i & 15]; }
PatternTexKeys::PatternTexKeys() { PatternTexKeys_Clear(this); }
PatternTexKeys::~PatternTexKeys() {}
extern "C" void PatternTexKeys_Clear(PatternTexKeys *p) {
    u8 i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 8; j++) sPlayerPatternTexKeys[i][j] = 0;
    for (j = 0; j < 8; j++) sAblePatternTexKeys[j] = 0;
}
void PatternTexCache::createTextures() {
    ClothTexStorage *a = (ClothTexStorage *)Mem_Alloc(sizeof(ClothTexStorage));
    ClothTexStorage *b = (ClothTexStorage *)Mem_Alloc(sizeof(ClothTexStorage));
    if (a != 0) {
        if (b != 0) {
            u8 i, j;
            u32 k1, k2;
            u16 v;
            u32 t;
            Pattern *e;
            u8 **row;
            u8 *src, *p;
            u16 *q, *sp;
            if (a != 0) ClothTex_Construct();
            if (b != 0) ClothTex_Construct();
            v = 0x11a8;
            ClothTex_LoadItem(a, &v, 0);
            i = 0;
        loop1:
            {
                j = 0;
                row = sPlayerPatternTexKeys[i];
            loop0:
                e = ((PlayerPatterns *)((PlayerData *)PlayerData_GetResident(gSaveData.players, i))->getPatterns())->getPattern(j);
                *b = *a;
                p = (u8 *)ClothTex_GetTexData(b);
                src = e->getPixels();
                for (k1 = 0; k1 < 0x200; k1++) *p++ = *src++;
                q = (u16 *)ClothTex_GetPlttData(b);
                sp = (u16 *)e->getInfo()->getPaletteData();
                for (k2 = 0; k2 < 0x10; k2++) *q++ = *sp++;
                if (Gfx3d_LoadTexAndPltt((NNSG3dResTex *)ClothTex_GetTex(b), NULL)) {
                    row[j] = (u8 *)ResCache_GetTex(ClothTex_GetTex(b), 0x4e554c4c);
                }
                j++;
                if (j < 8) goto loop0;
            }
            i++;
            if (i < 4) goto loop1;
            t = Scene_GetCurrent();
            if (t == 10) {
                for (j = 0; j < 8; j++) {
                    ClothTex_LoadPattern(b, gSaveAbleSistersPatterns.getPattern(j));
                    if (Gfx3d_LoadTexAndPltt((NNSG3dResTex *)ClothTex_GetTex(b), NULL)) {
                        sAblePatternTexKeys[j] = (u8 *)ResCache_GetTex(ClothTex_GetTex(b), 0x4e554c4c);
                    }
                }
            }
            Mem_Free(a);
            Mem_Free(b);
        }
    }
}
extern "C" void PatternTexCache_ResetKeys(PatternTexCache *p) { PatternTexKeys_Clear(&p->texKeys); }
extern "C" u8 *PatternTexKeys_GetPlayer(PatternTexKeys *self, s32 a, s32 b) { return sPlayerPatternTexKeys[a & 3][b & 7]; }
extern "C" u8 *PatternTexKeys_GetAble(PatternTexKeys *self, s32 i) { return sAblePatternTexKeys[i & 7]; }
PatternPresetInfoFile::PatternPresetInfoFile() {}
PatternPresetInfoFile::~PatternPresetInfoFile() {}
extern "C" void PatternPresetInfo_Open(PatternPresetInfoFile *p) { p->file.open((void *)"/myOrg/myD.bin", 0x2c, 0x32); }
extern "C" void PatternPresetInfo_Close(PatternPresetInfoFile *p) { p->file.close(); }
extern "C" BOOL PatternPresetInfo_Apply(PatternPresetInfoFile *tbl, PatternInfo *dst, s32 idx) {
    if (idx < 0x32) {
        u8 *rec = tbl->file.getRecord(idx);
        if (rec != 0) {
            ItemName title;
            title.set(rec + 2);
            dst->setTitle(&title);
            dst->setPalette(rec[0]);
            dst->setTaste(rec[1]);
            MsgString9C townName;
            townName.set(rec + 0x1e);
            MsgString9B playerName;
            playerName.set(rec + 0x13);
            TownId town;
            TownId_Construct();
            TownId_SetNameString((u8 *)&town, &townName);
            PlayerId author((void *)NULL);
            __builtin_memset((void *)&author, 0, sizeof(author));
            author.setNameString(&playerName);
            author.setTown(&town);
            dst->setAuthor(AsIdRecord(&author));
            TownId_Destruct();
            TownId_Destruct();
            return TRUE;
        }
    }
    return FALSE;
}
extern "C" PatternPresetInfoFile *PatternPresetInfo_Get(void) { return &sPatternPresetInfo; }
extern "C" void PlayerPatternDefaults_Ctor(void *p) {}
extern "C" void PlayerPatternDefaults_Load(void *p) { File_LoadToBuffer("menu/desi/b_myd_my_obj.bch", p, 0x1000); }
extern "C" BOOL PlayerPatternDefaults_Extract(void *a, void *b, s32 x) {
    if (x < 0 || x >= 8) return FALSE;
    Gfx2d_TilesInRow32ToLinear((u32 *)a, (u32 *)b, x * 4, 4, 4);
    return TRUE;
}
extern "C" void AblePatternDefaults_Ctor(void *p) {}
extern "C" void AblePatternDefaults_Load(void *p) { File_LoadToBuffer("menu/desi/b_myd_bu_obj.bch", p, 0x1000); }
extern "C" BOOL AblePatternDefaults_Extract(void *a, void *b, s32 x) {
    if (x < 0 || x >= 8) return FALSE;
    Gfx2d_TilesInRow32ToLinear((u32 *)a, (u32 *)b, x * 4, 4, 4);
    return TRUE;
}
extern "C" void TownFlagPatternDefault_Ctor(void *p) {}
extern "C" void TownFlagPatternDefault_Load(void *p) { File_LoadToBuffer("menu/desi/myc/obj0.bch", p, 0x200); }
extern "C" BOOL TownFlagPatternDefault_Extract(void *a, void *b) {
    Gfx2d_TilesToLinear4bpp((u32 *)a, (u32 *)b, 4, 4);
    return TRUE;
}
extern "C" void PresetPatternFile_Ctor(void *p) {}
extern "C" void PresetPatternFile_Load(void *dst, s32 n) {
    char buf[0x28];
    Str_SPrintf(buf, "menu/desi/myc/obj%d.bch", n + 2);
    File_LoadToBuffer(buf, dst, 0x200);
}
extern "C" BOOL PresetPatternFile_Extract(void *a, void *b) {
    Gfx2d_TilesToLinear4bpp((u32 *)a, (u32 *)b, 4, 4);
    return TRUE;
}
extern "C" BOOL PatternSrc_OnChanged(s32 cmd, s32 x) {
    switch (cmd) {
    case 0:
    case 9: {
        PlayerData *t = PlayerData_GetBySessionSlot(0);
        if (t != 0) {
            s32 v = t->getIndex();
            if (v != -1) PatternTex_UploadPlayer((u8)(v & 3), x);
        }
        return TRUE;
    }
    case 4:
        if (Unk_0207116c_Eq1(gFieldSceneKind)) {
            if (Scene_GetCurrent() == 10) {
                PatternTex_UploadAble(x);
                PatternTexCache_Get()->setAbleDirty(x & 7);
            }
        }
        return TRUE;
    case 5:
        if (Unk_0207116c_Eq0(gFieldSceneKind)) {
            if (Scene_InTown()) {
                BuildingActor *gate = (BuildingActor *)Shared_BuildingList_FindByItem(0x500b);
                if (gate) GateHouse_ApplyTownFlag((GateHouse *)gate);
            }
        }
        return TRUE;
    case 1:
    case 2:
    case 3:
    case 6:
    case 7:
    case 8:
    default:
        return FALSE;
    }
}

static inline s32 Unk_020707ec_K(u16 v, u32 lo, u32 hi) {
    if (v >= lo && v <= hi) {
        return (s32)(v - lo) >> 2;
    }
    return -1;
}
static inline s32 Unk_020707ec_K3(BOOL f, u16 v) {
    if (f) {
        return (s32)(v - 0x1188);
    }
    return -1;
}

extern "C" BOOL Villager_MaybeCopyAblePattern(s32 a, s32 b) {
    VillagerData *p = (VillagerData *)SaveVillagers_Get(gSaveVillagers, a);
    if (p != NULL) {
        if (p->getVillagerId()->isValid() != 0) {
            u32 val = *Villager_GetFashionTaste(p);
            s32 mode = VillagerPlanBlock_GetPlan(Villager_GetPlan(p))->getState();
            u32 rnd = Random_GlobalBelow(100);
            s32 fa, fb, fc;
            u16 bufw[2];
            fb = 0;
            fa = 0;
            fc = 0;
            if (mode == 3) {
                if (rnd < 15) {
                    fa = 1;
                    fb = 1;
                } else if (rnd < 20) {
                    fa = 1;
                } else if (rnd < 30) {
                    fc = 1;
                }
            } else {
                if (rnd < 10) {
                    fa = 1;
                    fb = 1;
                } else if (rnd < 15) {
                    fc = 1;
                }
            }
            if (fc) {
                *(volatile u16 *)&bufw[0] = 0xfff1;
                BOOL z = FALSE;
                for (s32 i = 0; (u32)i < 6; i++) {
                    AbleShop_GetItem(data_021ed2d4, i, &bufw[0]);
                    BOOL in1 = z;
                    u32 v = *(volatile u16 *)&bufw[0];
                    u32 w = *(volatile u16 *)&bufw[0];
                    if (w >= 0x1380 && v <= 0x139f) {
                        in1 = TRUE;
                    }
                    if (in1) break;
                    if (v >= 0x3e24 && v <= 0x3ea3) break;
                }
                {
                    BOOL in1 = FALSE;
                    u32 v = *(volatile u16 *)&bufw[0];
                    u32 w = *(volatile u16 *)&bufw[0];
                    if (w >= 0x1380 && v <= 0x139f) {
                        in1 = TRUE;
                    }
                    if (in1 || (v >= 0x3e24 && v <= 0x3ea3)) {
                        Item_FromPlacedForm(&bufw[1], &bufw[0]);
                    }
                }
            }
            if (fa) {
                AbleSistersPatterns *tbl = &gSaveAbleSistersPatterns;
                s32 cnt = 0;
                for (u32 j = 0; j < 8; j++) {
                    s32 x = tbl->getPattern((u8)j)->getInfo()->getTaste();
                    if (fb) {
                        if (x == val) cnt++;
                    } else {
                        if (x != val) cnt++;
                    }
                }
                if (cnt > 0) {
                    s32 pick = Random_GlobalBelow(cnt);
                    s32 k = 0;
                    s32 j;
                    for (j = 0; (u32)j < 8; j++) {
                        s32 x = tbl->getPattern((u8)j)->getInfo()->getTaste();
                        if (fb) {
                            if (x == val) {
                                if (pick == k) break;
                                k++;
                            }
                        } else {
                            if (x != val) {
                                if (pick == k) break;
                                k++;
                            }
                        }
                    }
                    return PatternSrc_Copy(4, (u8)(j & 7), 6, (u8)a, b);
                }
            }
        }
    }
    return FALSE;
}
extern "C" BOOL PatternSrc_Copy(u32 a, u32 b, u32 c, u32 d, u32 e) {
    Unk_02070e4c_Bits bits;
    s32 ta = PatternSrc_ResolveKind(a);
    s32 tc = PatternSrc_ResolveKind(c);
    if (tc == 7) {
        return FALSE;
    }
    Pattern *r4 = PatternSrc_Get(ta, b);
    Pattern *r6 = PatternSrc_Get(tc, d);
    *r6 = *r4;
    PatternSrc_OnChanged(tc, d);
    if (*(u8 *)&e) {
        if (gCommManager->isOnline()) {
            bits.a = ta;
            bits.b = b;
            bits.c = tc;
            bits.d = d;
            bits.e = 0;
            bits.f = 0;
            CommManager *g = gCommManager;
            g->beginRecord();
            g->writeRecord((u8 *)&bits, 4);
            g->endRecord(0x15, 4);
        }
    }
    return TRUE;
}
extern "C" s32 PatternSrc_ResolveKind(s32 t) {
    CommManager *g = gCommManager;
    if (g->isOnline() && t == 9) {
        return g->myAid;
    }
    return t;
}
extern "C" BOOL PatternSrc_Swap(u32 a, u32 b, u32 c, u32 d, u32 e) {
    Unk_02070e4c_Bits bits;
    s32 ta = PatternSrc_ResolveKind(a);
    s32 tc = PatternSrc_ResolveKind(c);
    if (ta == 7 || tc == 7) {
        return FALSE;
    }
    Pattern *r5 = PatternSrc_Get(ta, b);
    Pattern *r4 = PatternSrc_Get(tc, d);
    static Pattern tmp;
    tmp = *r4;
    *r4 = *r5;
    *r5 = tmp;
    PatternSrc_OnChanged(ta, b);
    PatternSrc_OnChanged(tc, d);
    if (*(u8 *)&e) {
        if (gCommManager->isOnline()) {
            bits.a = ta;
            bits.b = b;
            bits.c = tc;
            bits.d = d;
            bits.e = 1;
            bits.f = 0;
            CommManager *g = gCommManager;
            g->beginRecord();
            g->writeRecord((u8 *)&bits, 4);
            g->endRecord(0x15, 4);
        }
    }
    return TRUE;
}
extern "C" {
ClothTexStorage *sAblePatternTexWork;
}
PresetPatternBuffer sPresetPatternBuffer;
extern "C" {
TexPatVramTasks *sAblePatternVramTasks;
u8 *sPlayerPatternTexKeys[4][8];
}
extern "C" void Pattern_RemovePlayerItems(s32 p) {
    static ItemId t;
    s32 i, j;
    s32 m;
    s32 idx;
    s32 y2;
    s32 x2;
    MapBlock *cells;
    MapBlock *cell;
    TownBlockMap *g = TownBlockMap_Get();
    if (g != NULL) {
        s32 x, y;
        for (y = 1; y < g->height - 1; y++) {
            for (x = 1; x < g->width - 1; x++) {
                if ((u32)x < (u32)g->width && (u32)y < (u32)g->height && g->blocks != NULL) {
                    cell = g->blocks + (y * g->width + x);
                } else {
                    cell = NULL;
                }
                if (cell != NULL) {
                    i = 0;
                    do {
                        j = 0;
                        do {
                            u16 *v = MapBlock_GetItemPtr(cell, j, i, 0);
                            if (v != NULL) {
                                BOOL in = FALSE;
                                if (*v >= 0xa7 && *v <= 0xc6) {
                                    in = TRUE;
                                }
                                if (in) {
                                    if (p == (s32)(*v - 0xa7) / 8) {
                                        MapBlock_SetItem(cell, &t.id, j, i, 0);
                                    }
                                }
                            }
                            j++;
                        } while (j < 16);
                        i++;
                    } while (i < 16);
                }
            }
        }
    }
    m = 0;
    do {
        RoomBlockMap *g2 = HouseRoomMaps_Get(m);
        if (g2 != NULL) {
            if ((u32)g2->width > 0 && (u32)g2->height > 0 && g2->blocks != NULL) {
                cells = g2->blocks;
            } else {
                cells = NULL;
            }
            if (cells != NULL) {
                y2 = 0;
                do {
                    x2 = 0;
                    do {
                        u16 *v = MapBlock_GetItemPtr(cells, x2, y2, 0);
                        if (v != NULL) {
                            BOOL f = FALSE;
                            u16 val = *v;
                            if (val >= 0x3d84 && val <= 0x3e03) {
                                f = TRUE;
                            }
                            if (f) {
                                idx = ((Unk_020707ec_K(val, 0x3d84, 0x3e03) >> 3) & 3);
                                if (idx == p) {
                                    MapBlock_SetItem(cells, &t.id, x2, y2, 0);
                                }
                            } else if (val >= 0x3ea4 && val <= 0x3f23) {
                                idx = ((Unk_020707ec_K(val, 0x3ea4, 0x3f23) >> 3) & 3);
                                if (idx == p) {
                                    MapBlock_SetItem(cells, &t.id, x2, y2, 0);
                                }
                            } else if (val >= 0x3f24 && val <= 0x3fa3) {
                                idx = ((Unk_020707ec_K(val, 0x3f24, 0x3fa3) >> 3) & 3);
                                if (idx == p) {
                                    MapBlock_SetItem(cells, &t.id, x2, y2, 0);
                                }
                            } else if (val >= 0x4224 && val <= 0x42a3) {
                                idx = ((Unk_020707ec_K(val, 0x4224, 0x42a3) >> 3) & 3);
                                if (idx == p) {
                                    MapBlock_SetItem(cells, &t.id, x2, y2, 0);
                                }
                            }
                        }
                        x2++;
                    } while (x2 < 16);
                    y2++;
                } while (y2 < 16);
            }
        }
        HouseRoom *e = gSaveHouse.getRoom(m);
        if (e != NULL) {
            u16 tmp[2];
            u16 *pv1 = e->getWallpaper(NULL);
            BOOL f1 = FALSE;
            u16 v1 = *pv1;
            if (v1 >= 0x1188 && v1 <= 0x11a7) {
                f1 = TRUE;
            }
            if (f1) {
                u16 *pv2 = e->getWallpaper(NULL);
                BOOL f2 = FALSE;
                u16 v2 = *pv2;
                if (v2 >= 0x1188 && v2 <= 0x11a7) {
                    f2 = TRUE;
                }
                idx = ((Unk_020707ec_K3(f2, v2) >> 3) & 3);
                if (idx == p) {
                    tmp[0] = 0x113e;
                    e->setWallpaper(&tmp[0], 0);
                }
            }
            u16 *pv3 = e->getCarpet(NULL);
            BOOL f3 = FALSE;
            u16 v3 = *pv3;
            if (v3 >= 0x1188 && v3 <= 0x11a7) {
                f3 = TRUE;
            }
            if (f3) {
                u16 *pv4 = e->getCarpet(NULL);
                BOOL f4 = FALSE;
                u16 v4 = *pv4;
                if (v4 >= 0x1188 && v4 <= 0x11a7) {
                    f4 = TRUE;
                }
                idx = ((Unk_020707ec_K3(f4, v4) >> 3) & 3);
                if (idx == p) {
                    tmp[1] = 0x1182;
                    e->setCarpet(&tmp[1], 0);
                }
            }
        }
        m++;
    } while (m < 5);
}
extern "C" Pattern *PatternSrc_GetSessionPlayer(s32 a, s32 b) {
    if (gCommManager->isOnline()) {
        PlayerData *p = PlayerData_GetBySessionSlot(a);
        if (p) {
            return ((PlayerPatterns *)p->getPatterns())->getPattern(b);
        }
    }
    return 0;
}
extern "C" Pattern *PatternSrc_GetSessionPlayer0(s32 x) { return PatternSrc_GetSessionPlayer(0, x); }
extern "C" Pattern *PatternSrc_GetSessionPlayer1(s32 x) { return PatternSrc_GetSessionPlayer(1, x); }
extern "C" Pattern *PatternSrc_GetSessionPlayer2(s32 x) { return PatternSrc_GetSessionPlayer(2, x); }
extern "C" Pattern *PatternSrc_GetSessionPlayer3(s32 x) { return PatternSrc_GetSessionPlayer(3, x); }

extern "C" void PatternSrc_ApplyNetMove(Unk_0206fe80_Bits *p);

extern "C" Pattern *PatternSrc_GetAble(s32 x) {
    return gSaveAbleSistersPatterns.getPattern(x);
}
extern "C" Pattern *PatternSrc_GetTownFlag(s32 x) {
    return (Pattern *)TownFlag_GetPattern(gSaveTownFlag.getTownFlag());
}
extern "C" Pattern *PatternSrc_GetVillager(s32 x) {
    VillagerData *p = (VillagerData *)SaveVillagers_Get(gSaveVillagers, x);
    if (p) return (Pattern *)p->getPattern();
    return 0;
}
extern "C" Pattern *PatternSrc_GetPreset(s32 x) {
    PresetPatternBuffer *t = PresetPatternBuffer_Get();
    t->load(x);
    return t->getPattern();
}
extern "C" Pattern *PatternSrc_GetBlancaFace(s32 x) {
    return (Pattern *)gSaveBlancaFace.getPattern();
}
extern "C" Pattern *PatternSrc_GetCurrentPlayer(s32 i) {
    PlayerData *p = PlayerData_GetCurrent();
    if (p) return ((PlayerPatterns *)p->getPatterns())->getPattern(i);
    return 0;
}
extern "C" Pattern *PatternSrc_Get(s32 i, s32 a) {
    if (i < 10) return sPatternSourceGetters[i](a);
    return 0;
}
extern "C" BOOL PatternTex_UploadPlayer(u32 a, u32 b) {
    u8 x = a & 7;
    u8 y = b & 7;
    u8 *t = sPlayerPatternTexKeys[x][y];
    if (t && sPlayerPatternTexWork && sPlayerPatternVramTasks) {
        Pattern *q = ((PlayerPatterns *)((PlayerData *)PlayerData_GetResident(gSavePlayers, x))->getPatterns())->getPattern(y);
        ClothTexStorage *tex = &sPlayerPatternTexWork[y];
        ClothTex_LoadPattern(tex, q);
        ((TexPatVramUploader *)(void *)&sPlayerPatternVramTasks[y])->uploadByIdx(t, 0, 0, (u8 *)ClothTex_GetTex(tex), 0, 0);
        return TRUE;
    }
    return FALSE;
}
extern "C" BOOL PatternTex_UploadAble(u32 x) {
    u8 i = x & 7;
    u8 *t = sAblePatternTexKeys[i];
    if (t && sAblePatternTexWork && sAblePatternVramTasks) {
        ClothTexStorage *tex = &sAblePatternTexWork[i];
        ClothTex_LoadPattern(tex, gSaveAbleSistersPatterns.getPattern(x));
        ((TexPatVramUploader *)(void *)&sAblePatternVramTasks[i])->uploadByIdx(t, 0, 0, (u8 *)ClothTex_GetTex(tex), 0, 0);
        return TRUE;
    }
    return FALSE;
}
extern "C" void PatternSrc_ApplyNetMove(Unk_0206fe80_Bits *p) {
    Unk_0206fe80_Bits &v = *p;
    u32 a = v.a;
    u8 b = v.b;
    u32 c = v.c;
    u8 d = v.d;
    u32 e = v.e;
    if (e) {
        PatternSrc_Swap(a, b, c, d, 0);
    } else {
        PatternSrc_Copy(a, b, c, d, 0);
    }
}

PatternTexCache sPatternTexCache;
extern "C" {

ClothTexStorage *sPlayerPatternTexWork;
TexPatVramTasks *sPlayerPatternVramTasks;
u8 *sAblePatternTexKeys[8];

extern Pattern *(*const sPatternSourceGetters[10])(s32);
Pattern *(*const sPatternSourceGetters[10])(s32) = {
    PatternSrc_GetSessionPlayer0, PatternSrc_GetSessionPlayer1, PatternSrc_GetSessionPlayer2, PatternSrc_GetSessionPlayer3, PatternSrc_GetAble,
    PatternSrc_GetTownFlag, PatternSrc_GetVillager, PatternSrc_GetPreset, PatternSrc_GetBlancaFace, PatternSrc_GetCurrentPlayer,
};

u8 data_021cbcac[4];
u8 sAbleDisplayDirtyBits;
}

PatternPresetInfoFile sPatternPresetInfo;
