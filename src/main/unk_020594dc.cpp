#include "item/Letter.h"
#include "host_labels.h"
#include "save/VillagerData.h"
#include "talk/MsgString25.h"
#include "talk/MsgString33.h"
#include "types.h"
#include "room/RoomScoreEvaluator.h"
#include "sys/ClockDateTime.h"
#include "town/BlockMap.h"
#include "save/SaveData.h"
#include "gfx/HBlankTask.h"
#include "item/ItemPickSpec.h"
#include "item/ItemName.h"
#include "item/LetterView.h"
#include "player/PlayerData.h"
#include "room/HouseData.h"
#include "room/HouseRoom.h"
#include "save/SaveData.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/main/unk_02003008.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_020594dc.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209c37c.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_020514a4.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_0204cc1c.h"



struct ItemPickResult {
    u16 v;
    ItemPickResult(u16 x) : v(x) {}
};

struct RoomSurfaceItem {
    u16 item;
    RoomSurfaceItem() {}
};

struct FtrFootprintBuf {
    u32 shapeIndex, direction, unk_08;
};



class RoomFengShui {
public:
    u8 westCount, southCount, eastCount;
    RoomFengShui();
    ~RoomFengShui();
    u8 getWestCount();
    u8 getSouthCount();
    u8 getEastCount();
    void clear();
    void evaluate(BlockMap *m);
    u8 countInStrip(BlockMap *m, s32 x0, s32 x1, s32 y0, s32 y1, s32 kind);
};


class RoomScoreSource {
public:
    RoomScoreSource();
    ~RoomScoreSource();
    virtual void *getRoomMap(s32 i) = 0;
    virtual RoomSurfaceItem getWallpaper(s32 key) = 0;
    virtual RoomSurfaceItem getCarpet(s32 key) = 0;
};

class VillagerRoomScoreSource : public RoomScoreSource {
public:
    VillagerRoomScoreSource();
    ~VillagerRoomScoreSource();
    virtual void *getRoomMap(s32 i);
    virtual RoomSurfaceItem getWallpaper(s32 key);
    virtual RoomSurfaceItem getCarpet(s32 key);
};

class HouseRoomScoreSource : public RoomScoreSource {
public:
    HouseRoomScoreSource();
    ~HouseRoomScoreSource();
    virtual void *getRoomMap(s32 i);
    virtual RoomSurfaceItem getWallpaper(s32 key);
    virtual RoomSurfaceItem getCarpet(s32 key);
};

extern "C" {
extern const u16 data_020cab80[];
extern const u16 data_020cab84[];
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
}
extern SaveData gSaveData;
extern "C" {
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
#define gSaveHappyRoomDate HOST_LABEL(u8 (*)[], gSaveHappyRoomDate)
#define gSaveHouse HOST_LABEL(u8 (*)[], gSaveHouse)
}

const u32 sHouseVisitGiftKinds[3] = { 0, 4, 3 };

u32 data_020dc07c[1] = { 0x1f };
u32 data_020dc080[1] = { 2 };
u32 data_020dc084[1] = { 2 };
u32 data_020dc088[1] = { 2 };
u32 data_020dc08c[1] = { 0x1f };
u32 data_020dc090[1] = { 0x1f };

extern "C" {
void MI_CpuFill8(void *dst, u32 v, u32 size);
void MIi_CpuClearFast(u32 v, void *dst, u32 n);
}

class HappyRoomSeriesScores {
public:
    u32 w[0x4a];
    HappyRoomSeriesScores() { MI_CpuFill8(this, 0, 0x128); }
    ~HappyRoomSeriesScores();
};

class HappyRoomFtrBitset {
public:
    u8 b[0xe0];
    HappyRoomFtrBitset() {
        volatile u32 z = 0;
        MIi_CpuClearFast(z, this, 0xe0);
    }
    ~HappyRoomFtrBitset();
};

class HappyRoomUnk06Masks {
public:
    u32 w[0x4a];
    u32 extra;
    HappyRoomUnk06Masks() {
        u32 i;
        for (i = 0; i < 0x4a; i++) w[i] = 0;
        extra = 0;
    }
    ~HappyRoomUnk06Masks();
};

u8 sFengShuiEastTotal;
u8 sFengShuiWestTotal;
u8 sFengShuiSouthTotal;
void *sHappyRoomVillagerMap;
char sVillagerLetterWithPaperPath[0x28];
HappyRoomSeriesScores sHappyRoomSeriesScores;
HappyRoomFtrBitset sHappyRoomLuckyFtr;
HappyRoomUnk06Masks sHappyRoomUnk06Masks;


extern "C" {
u8 FengShui_GetEastTotal();
u8 FengShui_GetSouthTotal();
u8 FengShui_GetWestTotal();
s32 HappyRoom_Evaluate(RoomScoreEvaluator *p, u16 *flags, s32 *pa, s32 *pb, s32 *pc, RoomScoreSource *source, s32 count, s32 base, u8 flag);
void HappyRoom_SendPrizeLetter(void *self, s32 n);
BOOL HappyRoom_SendScoreLetters(void *self, s32 a, s32 b, s32 c, s32 n);
BOOL RoomMap_GetFloorBounds(s32 *a, s32 *b, s32 *c, s32 *d, BlockMap *grid);
}

static inline BOOL Unk_0205a6bc_Range(u16 *p, u32 lo, u32 hi)
{
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

static inline BOOL Unk_0205a6bc_Max(s32 i, u32 v)
{
    if (i < 0x4a) {
        if (sHappyRoomSeriesScores.w[i] < v) {
            sHappyRoomSeriesScores.w[i] = v;
            return TRUE;
        }
    }
    return FALSE;
}

static inline u32 Unk_0205a930_Get(s32 i, u32 dflt)
{
    if (i < 0x4a) return sHappyRoomSeriesScores.w[i];
    return dflt;
}

static inline void Unk_0205a930_Clear(void *dst, u32 n)
{
    volatile u32 z = 0;
    MIi_CpuClearFast(z, dst, n);
}


extern "C" {
u8 *SaveVillagers_Find(u8 *base, u16 *x);
u8 *Villager_GetBirthday(VillagerData *a);
BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
s32 Item_GetFurnitureDirection(u16 *p);
BOOL Item_IsNormalItem(u16 *p);
s32 FX_Div(s32 a, s32 b);
void Debug_SetHappyRoomScore(s32 v);
void Debug_SetHappyRoomBonusFlags(u32 v);
s32 FtrClass_GetBasePoints(s32 v);
s32 Series_GetType(s32 v);
s32 ItemInfo_GetSeries(u16 *p);
void *SaveVillagers_Get(void *p, s32 k);
u32 Villager_GetCarpet(void *a);
u32 Villager_GetWallpaper(void *a);
void FtrFootprint_Destruct(FtrFootprintBuf *b);
void Clock_GetDateTime(ClockDateTime *p);
void DateTime_SubDays(ClockDateTime *p, s32 n);
s32 Date_GetWeekday(u32 a, u32 b, u32 c);
void DateTime_AddDays(ClockDateTime *p, s32 n);
s32 DateTime_Compare(ClockDateTime *a, ClockDateTime *b, u32 mask);
}

extern "C" {
}

extern "C" BOOL HBlank_Replace(HBlankTask *t, void (*a)(), void (*b)()) {
    t->unk_14 = b;
    t->nextParam = a;
    t->taskState = 2;
    return TRUE;
}

HappyRoomSeriesScores::~HappyRoomSeriesScores() {}

HappyRoomFtrBitset::~HappyRoomFtrBitset() {}

HappyRoomUnk06Masks::~HappyRoomUnk06Masks() {}

extern "C" void HappyRoomDate_Construct() {}

extern "C" void HappyRoomDate_Destruct() {}

extern "C" void HappyRoomDate_SetToday(u8 *out) {
    ClockDateTimeWords t;
    t.words[0] = 0;
    t.words[1] = 0;
    Clock_GetDateTime(&t.dt);
    out[0] = t.dt.day;
    out[1] = t.dt.month;
    out[2] = t.dt.year;
    out[3] = 0;
}

extern "C" void HappyRoomDate_Reset(u8 *out) {
    HappyRoomDate_SetToday(out);
}

extern "C" s32 HappyRoomDate_IsNewWeek(u8 *out) {
    struct {
        ClockDateTimeWords a, b, c;
    } l;
    l.a.words[0] = 0;
    l.a.words[1] = 0;
    Clock_GetDateTime(&l.a.dt);
    if (l.a.dt.hour < 6) {
        l.a.dt.hour = 7;
        DateTime_SubDays(&l.a.dt, 1);
    }
    l.b.words[0] = 0;
    l.b.words[1] = 0;
    Clock_GetDateTime(&l.b.dt);
    DateTime_SubDays(&l.b.dt, Date_GetWeekday(l.b.dt.year, l.b.dt.month, l.b.dt.day));
    if (l.b.dt.year > l.a.dt.year) DateTime_AddDays(&l.b.dt, 7);
    l.c.words[0] = 0;
    l.c.words[1] = 0;
    l.c.dt.year = out[2];
    l.c.dt.month = out[1];
    l.c.dt.day = out[0];
    l.c.dt.hour = 7;
    l.c.dt.minute = 0;
    l.c.dt.second = 0;
    if (DateTime_Compare(&l.a.dt, &l.c.dt, 0x38) == -1) {
        out[2] = l.a.dt.year;
        out[1] = l.a.dt.month;
        out[0] = l.a.dt.day;
        l.c.dt.year = out[2];
        l.c.dt.month = out[1];
        l.c.dt.day = out[0];
        l.c.dt.hour = 7;
        l.c.dt.minute = 0;
        l.c.dt.second = 0;
        return FALSE;
    }
    if (DateTime_Compare(&l.c.dt, &l.b.dt, 0x38) == -1) {
        s32 t = DateTime_Compare(&l.b.dt, &l.a.dt, 0x38);
        if (t == -1) goto yes;
        t = DateTime_Compare(&l.b.dt, &l.a.dt, 0x38);
        if (t == 0) {
        yes:
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void HappyRoomDate_SetEvalDay(u8 *out) {
    ClockDateTimeWords t;
    t.words[0] = 0;
    t.words[1] = 0;
    Clock_GetDateTime(&t.dt);
    if (t.dt.hour < 6) DateTime_SubDays(&t.dt, 1);
    out[0] = t.dt.day;
    out[1] = t.dt.month;
    out[2] = t.dt.year;
}

extern "C" u32 FengShui_GetTotal() {
    u32 a = FengShui_GetEastTotal();
    u32 b = FengShui_GetWestTotal();
    u32 c = FengShui_GetSouthTotal();
    return a + (b + c);
}

extern "C" u8 FengShui_GetWestTotal() { return sFengShuiWestTotal; }

extern "C" u8 FengShui_GetSouthTotal() { return sFengShuiSouthTotal; }

extern "C" u8 FengShui_GetEastTotal() { return sFengShuiEastTotal; }

extern "C" void FengShui_UpdateHouse() {
    u32 i;
    sFengShuiEastTotal = 0;
    sFengShuiSouthTotal = 0;
    sFengShuiWestTotal = 0;
    for (i = 0; i < 5; i++) {
        RoomFengShui s;
        BlockMap *m = (BlockMap *)HouseRoomMaps_Get(i);
        if (m != NULL) {
            s.evaluate(m);
            sFengShuiWestTotal += s.getWestCount();
            sFengShuiSouthTotal += s.getSouthCount();
            sFengShuiEastTotal += s.getEastCount();
        }
    }
}

void RoomFengShui::clear() {
    eastCount = 0;
    southCount = eastCount;
    westCount = southCount;
}

RoomFengShui::RoomFengShui() {
    clear();
}

RoomFengShui::~RoomFengShui() {}

u8 RoomFengShui::getWestCount() { return westCount; }

u8 RoomFengShui::getSouthCount() { return southCount; }

u8 RoomFengShui::getEastCount() { return eastCount; }

u8 RoomFengShui::countInStrip(BlockMap *m, s32 x0, s32 x1, volatile s32 y0, volatile s32 y1, volatile s32 kind) {
    u32 cnt = 0;
    u8 layer = 0;
    s32 f;
    u32 n, i;
    BOOL ok;
    s32 nx;
    FtrFootprintBuf buf;
    s32 y, x;
    s32 ya = y0;
    s32 yb = y1;
    do {
        for (y = ya; (u32)y <= (u32)yb; y++) {
            x = x0;
            if ((u32)x <= (u32)x1) {
                goto L_test;
            L_loop:
                {
                s32 hx = x >> 4;
                s32 hy = y >> 4;
                u16 *cell = (u16 *)BlockMap_GetItemPtr(m, hx, hy, x - (hx << 4), y - (hy << 4), layer);
                if (cell != NULL && Item_IsFurniture(cell)) {
                    f = Item_GetFurnitureIndex(cell);
                    FtrFootprint_Init((Unk_0205242c_Self *)&buf, cell);
                    n = FtrFootprint_GetTileCount((Unk_0205242c_Self *)&buf);
                    ok = TRUE;
                    for (i = 0; i < n; i++) {
                        nx = x + ((s16 *)FtrFootprint_GetTileOffset((Unk_0205242c_Self *)&buf, i))[0];
                        s32 ny = y + ((s16 *)FtrFootprint_GetTileOffset((Unk_0205242c_Self *)&buf, i))[1];
                        if (nx < x0 || nx > x1 || ny < y0 || ny > y1) {
                            ok = FALSE;
                            break;
                        }
                    }
                    if (ok) {
                        if (FtrInfo_GetColor1(f) == kind) cnt++;
                        if (FtrInfo_GetColor2(f) == kind) cnt++;
                    }
                    FtrFootprint_Destruct(&buf);
                }
            }
                x++;
            L_test:
                if ((u32)x <= (u32)x1) goto L_loop;
            }
        }
        layer++;
    } while (layer < 2);
    if (cnt < 0x100) return (u8)cnt;
    return 0xff;
}

void RoomFengShui::evaluate(BlockMap *m) {
    s32 v0, v1, v2, v3;
    RoomMap_GetFloorBounds(&v0, &v1, &v2, &v3, m);
    westCount = countInStrip(m, v0, v0 + 1, v2, v3, 1);
    southCount = countInStrip(m, v0, v1, v3 - 1, v3, 4);
    eastCount = countInStrip(m, v1 - 1, v1, v2, v3, 2);
}

extern "C" RoomScoreSource::RoomScoreSource() {}

extern "C" RoomScoreSource::~RoomScoreSource() {}

extern "C" HouseRoomScoreSource::HouseRoomScoreSource() {}

extern "C" HouseRoomScoreSource::~HouseRoomScoreSource() {}

extern "C" void *HouseRoomScoreSource::getRoomMap(s32 i) {
    return HouseRoomMaps_Get(i);
}

extern "C" RoomSurfaceItem HouseRoomScoreSource::getWallpaper(s32 key) {
    RoomSurfaceItem r;
    void *h = ((HouseData *)(gSaveHouse))->getRoom(key);
    r.item = *((HouseRoom *)(h))->getWallpaper((s32 *)(0));
    return r;
}

extern "C" RoomSurfaceItem HouseRoomScoreSource::getCarpet(s32 key) {
    RoomSurfaceItem r;
    void *h = ((HouseData *)(gSaveHouse))->getRoom(key);
    r.item = *((HouseRoom *)(h))->getCarpet((s32 *)(0));
    return r;
}

extern "C" VillagerRoomScoreSource::VillagerRoomScoreSource() {}

extern "C" VillagerRoomScoreSource::~VillagerRoomScoreSource() {}

extern "C" void *VillagerRoomScoreSource::getRoomMap(s32 i) {
    return sHappyRoomVillagerMap;
}

extern "C" RoomSurfaceItem VillagerRoomScoreSource::getWallpaper(s32 key) {
    RoomSurfaceItem r;
    void *vd = SaveVillagers_Get(gSaveVillagers, key);
    if (vd != 0) {
        u32 t = Villager_GetWallpaper(vd);
        if (t < 0x44) r.item = (u16)(t + 0x1100);
        else r.item = 0x1100;
    } else {
        r.item = 0x1100;
    }
    return r;
}

extern "C" RoomSurfaceItem VillagerRoomScoreSource::getCarpet(s32 key) {
    RoomSurfaceItem r;
    void *vd = SaveVillagers_Get(gSaveVillagers, key);
    if (vd != 0) {
        u32 t = Villager_GetCarpet(vd);
        if (t < 0x44) r.item = (u16)(t + 0x1144);
        else r.item = 0x1144;
    } else {
        r.item = 0x1144;
    }
    return r;
}

#pragma thumb off
extern "C" u32 HappyRoom_CalcLuckyBonus(u32 *p) {
    u32 s = 0;
    u32 i;
    for (i = 0; i < 0xde; i += 4) {
        s += MATH_CountPopulation(*(u32 *)((u8 *)p + i));
    }
    return s * 0x1e61;
}
#pragma thumb reset

extern "C" void RoomScoreEvaluator_Construct(RoomScoreEvaluator *p) {
    p->wallpaper = 0xfff1;
    p->carpet = 0xfff1;
}

extern "C" void RoomScoreEvaluator_Destruct() {}

extern "C" u32 HappyRoom_RateMainRoom(RoomScoreEvaluator *p, s32 *out) {
    BlockMap *m = (BlockMap *)HouseRoomMaps_Get(0);
    s32 x = 3;
    u32 flags = 0;
    if (m != NULL) {
        u32 i;
        void *h;
        u8 fl[2];
        u32 cnt;
        s32 v8, vc, v0;
        for (i = 0; i < 0x4a; i++) sHappyRoomUnk06Masks.w[i] = 0;
        sHappyRoomUnk06Masks.extra = 0;
        MI_CpuFill8(&sHappyRoomSeriesScores, 0, 0x128);
        RoomMap_GetFloorBounds((s32 *)p, (s32 *)&p->maxX, (s32 *)&p->minZ, (s32 *)&p->maxZ, m);
        p->wallpaper = 0x1100;
        p->carpet = 0x1144;
        h = ((HouseData *)(gSaveHouse))->getRoom(0);
        if (h != NULL) {
            p->wallpaper = *((HouseRoom *)(h))->getWallpaper((s32 *)(0));
            p->carpet = *((HouseRoom *)(h))->getCarpet((s32 *)(0));
        }
        fl[0] = 0;
        fl[1] = 0;
        ((RoomScoreEvaluator *)p)->calcPenalty(m, &fl[0], &fl[1]);
        ((RoomScoreEvaluator *)p)->collectUnk06Kinds(m);
        cnt = 0;
        v8 = ((RoomScoreEvaluator *)p)->scoreSeries(m, &cnt);
        vc = ((RoomScoreEvaluator *)p)->scoreThemes(m);
        v0 = ((RoomScoreEvaluator *)p)->scoreSets(m);
        if (fl[1] != 0) {
            x--;
            flags |= 1;
        }
        if (fl[0] != 0) {
            x--;
            flags |= 2;
        }
        if ((sHappyRoomUnk06Masks.extra & 0xf) == 0xf) {
            x++;
            flags |= 4;
        }
        if (vc != 0 || v0 != 0) {
            flags |= 8;
            x++;
        }
        if (vc == 0 || v0 == 0) {
            flags |= 0x40;
        }
        if (v8 != 0x4a) {
            x += 2;
            flags |= 0x10;
        } else if (cnt >= 5) {
            flags |= 0x20;
        }
    }
    if (out != NULL) *out = x;
    return flags;
}

extern "C" void HappyRoom_EvaluateHouse(void *evaluator) {
    RoomScoreEvaluator *a = (RoomScoreEvaluator *)evaluator;
    s32 v0;
    HouseRoomScoreSource ops;
    s32 v1, v2, v3;
    HappyRoom_Evaluate(a, (u16 *)&v0, &v1, &v2, &v3, &ops, 5, 0, 1);
}

extern "C" s32 HappyRoom_EvaluateVillagerRoom(void *evaluator, s32 b, u16 *c, s32 *d, s32 *e, s32 *f) {
    RoomScoreEvaluator *a = (RoomScoreEvaluator *)evaluator;
    s32 r;
    if (sHappyRoomVillagerMap == NULL) {
        sHappyRoomVillagerMap = VillagerRoomMap_Create(b, gCurrentHeap);
    }
    VillagerRoomScoreSource ops;
    r = HappyRoom_Evaluate(a, c, d, e, f, &ops, 1, b, 0);
    if (sHappyRoomVillagerMap != NULL) {
        VillagerRoomMap_Destroy(gCurrentHeap);
        sHappyRoomVillagerMap = NULL;
    }
    return r;
}

extern "C" s32 HappyRoom_Evaluate(RoomScoreEvaluator *p, u16 *flags, s32 *pa, s32 *pb, s32 *pc, RoomScoreSource *source, s32 count, s32 base, u8 flag)
{
    s32 total;
    s32 sel;
    s32 s10, s14, s18, s1c, s20, s24, s28, s2c, s30;
    s32 j;
    s32 idxA, cntA, cntB;
    u32 i;
    s32 pick, n, pick2, n2, t, x, kind, idx;
    u32 zero, zero2;
    s32 r7;
    u8 f[2];
    u32 k;
    *flags = 0;
    *pa = 0;
    *pb = 0;
    *pc = 0;
    MI_CpuFill8(&sHappyRoomSeriesScores, 0, 0x128);
    Unk_0205a930_Clear(&sHappyRoomLuckyFtr, 0xe0);
    for (k = 0; k < 0x4a; k++) sHappyRoomUnk06Masks.w[k] = 0;
    sHappyRoomUnk06Masks.extra = 0;
    total = 0;
    s10 = 0; s14 = 0; s18 = 0; s1c = 0; s20 = 0; s24 = 0; s28 = 0; s2c = 0; s30 = 0; j = 0;
    goto test0;
loop0:
    {
        idx = base + j;
        BlockMap *m = (BlockMap *)source->getRoomMap(idx);
        p->wallpaper = source->getWallpaper(idx).item;
        p->carpet = source->getCarpet(idx).item;
        RoomMap_GetFloorBounds((s32 *)p, (s32 *)&p->maxX, (s32 *)&p->minZ, (s32 *)&p->maxZ, m);
        RoomFengShui obj;
        obj.evaluate(m);
        p->scoreSeries(m, 0);
        p->scoreThemes(m);
        p->scoreSets(m);
        p->collectLuckyItems(m);
        p->collectUnk06Kinds(m);
        s10 += p->scoreBasePoints(m);
        s14 += p->scoreFengShui(&obj);
        s18 += p->scoreColorTheme(m);
        s1c += p->scoreFlagPairThemes(m, pb, pc);
        s20 += p->scoreCollection(m, pa);
        f[0] = 0;
        f[1] = 0;
        s24 -= p->calcPenalty(m, &f[0], &f[1]);
        if (f[0] != 0) s2c = 1;
        if (f[1] != 0) s30 = 1;
    }
    j++;
test0:
    if (j < count) goto loop0;
    total += s10;
    total += s14;
    total += s18;
    total += s1c;
    total += s20;
    total += s24;
    sel = 0; idxA = 0; cntA = 0; cntB = 0;
    for (i = 0; i < 0x4a; i++) {
        u32 v = Unk_0205a930_Get(i, sel);
        if (v != 0) {
            switch (Series_GetType(i)) {
            case 0:
                cntA++;
                break;
            case 1:
                if (v > 0xbb8) cntB++;
                break;
            case 2:
                s28 += v;
                break;
            }
        }
        total += v;
    }
    if (cntA != 0) {
        pick = Random_GlobalBelow(cntA);
        n = 0;
        for (i = 0; i < 0x4a; i++) {
            u32 v;
            zero = 0;
            v = Unk_0205a930_Get(i, zero);
            if (v != 0 && Series_GetType(i) == 0) {
                if (n == pick) {
                    sel = i;
                    break;
                }
                n = n + 1;
            }
        }
    }
    if (cntB != 0) {
        pick2 = Random_GlobalBelow(cntB);
        n2 = 0;
        for (i = 0; i < 0x4a; i++) {
            u32 v;
            zero2 = 0;
            v = Unk_0205a930_Get(i, zero2);
            if (v != 0 && Series_GetType(i) == 1) {
                if (n2 == pick2) {
                    idxA = i;
                    break;
                }
                n2 = n2 + 1;
            }
        }
    }
    r7 = 0;
    if ((sHappyRoomUnk06Masks.extra & 0xf) == 0xf) {
        BOOL found = FALSE;
        for (i = 0; i < 0x4a; i++) {
            if ((sHappyRoomUnk06Masks.w[i] & 0xf) == 0xf) {
                found = TRUE;
                break;
            }
        }
        if (found) r7 += 0x1388;
        else r7 += 0x3e8;
        total += r7;
    }
    t = HappyRoom_CalcLuckyBonus((u32 *)&sHappyRoomLuckyFtr);
    total += t;
    if (total < 0) total = 0;
    if (flags) {
        if (cntA != 0) {
            u32 v = Unk_0205a930_Get(sel, 0);
            if (v == 0x7530) *flags |= 1;
            else if (v == 0x61a8) *flags |= 2;
            else *flags |= 4;
        }
        if (cntB != 0) *flags |= 8;
        if (s28 >= 0xbb8) *flags |= 0x10;
        if (r7 > 0) *flags |= 0x20;
        if (s14 >= 0x1f4) *flags |= 0x40;
        if (s18 >= 0x7d0) *flags |= 0x80;
        if (s1c >= 0x7d0) *flags |= 0x100;
        if (s20 >= 0xbb8) *flags |= 0x200;
        if ((u32)t >= 0x1b58) *flags |= 0x400;
    }
    if (flag != 0) {
        if (HappyRoomDate_IsNewWeek(gSaveHappyRoomDate) == 0) {
            if (*DebugVar_GetPtr(0, 0x22) == 0) goto end;
        }
        {
            x = ((HouseData *)(gSaveHouse))->getLevel();
            u16 b;
            s32 nb;
            u32 q;
            kind = 0;
            b = 0;
            if (cntA != 0) {
                u32 v = Unk_0205a930_Get(sel, kind);
                if (v == 0x7530) b |= 1;
                else if (v == 0x61a8) b |= 2;
                else b |= 4;
            }
            if (cntB != 0) b |= 8;
            if (s28 >= 0x1388) b |= 0x10;
            if (r7 > 0) b |= 0x20;
            if (s14 >= 0x7d0) b |= 0x40;
            if (s18 >= 0x1770) b |= 0x80;
            if (s1c >= 0x1770) b |= 0x100;
            if (s20 >= 0xc80) b |= 0x200;
            if ((u32)t >= 0x1b58) b |= 0x400;
            if (s2c != 0) b |= 0x1000;
            if (s30 != 0) b |= 0x800;
            nb = 0;
            for (q = 0; q < 13; q++) {
                if (b & (1 << q)) nb++;
            }
            Debug_SetHappyRoomScore(total);
            Debug_SetHappyRoomBonusFlags(b);
            {
                BOOL ok;
                if (nb != 0) {
                    if (Random_GlobalBelow(2) == 0) ok = TRUE;
                    else ok = FALSE;
                } else {
                    ok = TRUE;
                }
                if (ok) {
                    if (total == 0) kind = 0;
                    else if (total <= 0x4e1f) kind = x + 1;
                    else if (total <= 0x1116f) kind = 8;
                    else if (total <= 0x1869f) kind = 9;
                    else kind = 10;
                } else {
                    s32 pk = Random_GlobalBelow(nb);
                    nb = 0;
                    for (q = 0; q < 13; q++) {
                        if (b & (1 << q)) {
                            if (pk == nb) {
                                kind = q;
                                kind = q + 0xb;
                                break;
                            }
                            nb++;
                        }
                    }
                }
            }
            if ((u32)(kind - 0xb) > 2) sel = idxA;
            if (HappyRoom_SendScoreLetters(p, kind, total, sel, *pa) != 0) {
                HappyRoom_SendPrizeLetter(p, total);
                HappyRoomDate_SetEvalDay(gSaveHappyRoomDate);
            }
        }
    }
end:
    return total;
}

s32 RoomScoreEvaluator::scoreSeries(BlockMap *grid, u32 *out)
{
    u32 max;
    u16 acc[0x94 / 2];
    u8 layer;
    u32 y, x;
    s32 i;
    u32 j;
    MI_CpuFill8(acc, 0, 0x94);
    max = 0;
    for (layer = 0; layer < 2; layer++) {
        for (y = minZ; y <= maxZ; y++) {
            s32 hx, hy;
            u16 *p;
            x = minX;
            if (x <= maxX) {
                goto test0;
            loop0:
                hx = (s32)x >> 4;
                hy = (s32)y >> 4;
                p = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer);
                if (p && Item_IsFurniture(p)) {
                    s32 id = Ftr_GetSeries(p);
                    if (Series_GetType(id) == 0) {
                        u32 b = Ftr_GetIndexInSeries(p);
                        acc[id] |= 1 << b;
                    }
                }
                x++;
            test0:
                if (x <= maxX) goto loop0;
            }
        }
    }
    if (Unk_0205a6bc_Range(&wallpaper, 0x1100, 0x1143)) {
        s32 k = ItemInfo_GetSeries(&wallpaper);
        if (Series_GetType(k) == 0) acc[k] |= data_020cab80[0];
    }
    if (Unk_0205a6bc_Range(&carpet, 0x1144, 0x1187)) {
        s32 k = ItemInfo_GetSeries(&carpet);
        if (Series_GetType(k) == 0) acc[k] |= data_020cab84[0];
    }
    for (j = 0; j < 0x4a; j++) {
        if (Series_GetType(ItemInfo_GetSeries(&carpet)) == 0) {
            u32 cnt = 0;
            u32 k = 0;
            s32 w = acc[j];
            for (; k < 12; k++) {
                if ((w >> k) & 1) cnt++;
            }
            if (cnt > max) max = cnt;
        }
    }
    if (out) *out = max;
    for (i = 0; (u32)i < 0x4a; i++) {
        if (Series_GetType(i) == 0 && acc[i] == 0xfff) {
            if (Unk_0205a6bc_Max(i, 30000)) return i;
        }
    }
    for (i = 0; (u32)i < 0x4a; i++) {
        if (Series_GetType(i) == 0) {
            u32 w = acc[i];
            if ((w & 0x3ff) == 0x3ff) {
                if ((w & 0x400) != 0 || (w & 0x800) != 0) {
                    if (Unk_0205a6bc_Max(i, 25000)) return 0x4a;
                }
            }
        }
    }
    for (i = 0; (u32)i < 0x4a; i++) {
        if (Series_GetType(i) == 0 && acc[i] == 0x3ff) {
            if (Unk_0205a6bc_Max(i, 20000)) return 0x4a;
        }
    }
    return 0x4a;
}

s32 RoomScoreEvaluator::scoreThemes(BlockMap *grid)
{
    u16 acc[0x94 / 2];
    u8 layer;
    u32 y, x;
    u32 i;
    s32 res;
    s32 lo, hi;
    volatile u32 zeroA, zeroB;
    MI_CpuFill8(acc, 0, 0x94);
    lo = ItemInfo_GetSeries(&wallpaper);
    hi = ItemInfo_GetSeries(&carpet);
    for (layer = 0; layer < 2; layer++) {
        for (y = minZ; y <= maxZ; y++) {
            s32 hx, hy;
            u16 *p;
            x = minX;
            if (x <= maxX) {
                goto test0;
            loop0:
                hx = (s32)x >> 4;
                hy = (s32)y >> 4;
                p = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer);
                if (p && Item_IsFurniture(p)) {
                    s32 id = Ftr_GetSeries(p);
                    if (Series_GetType(id) == 1) {
                        u32 b = Ftr_GetIndexInSeries(p);
                        acc[id] |= 1 << b;
                    }
                }
                x++;
            test0:
                if (x <= maxX) goto loop0;
            }
        }
    }
    res = 0;
    i = 0;
    zeroA = 0;
    zeroB = 0;
    for (; i < 0x4a; i++) {
        if (Series_GetType(i) == 1) {
            u32 bits = zeroA;
            u32 k;
            u32 n = FtrInfo_CountInSeries(i);
            for (k = zeroB; k < n; k++) {
                bits = (u16)(bits | (1 << k));
            }
            if (acc[i] >= bits) {
                if (i == lo && i == hi) {
                    if ((s32)i < 0x4a) {
                        u32 v = (n + 1) * 3000;
                        if (sHappyRoomSeriesScores.w[i] < v) sHappyRoomSeriesScores.w[i] = v;
                    }
                    res = 1;
                }
            } else {
                if (i == lo && i == hi) {
                    if ((s32)i < 0x4a) {
                        if (sHappyRoomSeriesScores.w[i] < 3000) sHappyRoomSeriesScores.w[i] = 3000;
                    }
                }
            }
        }
    }
    return res;
}

s32 RoomScoreEvaluator::scoreSets(BlockMap *grid)
{
    u16 acc[0x94 / 2];
    u8 layer;
    u32 y, x;
    u32 i;
    s32 res;
    MI_CpuFill8(acc, 0, 0x94);
    res = 0;
    for (layer = 0; layer < 2; layer++) {
        for (y = minZ; y <= maxZ; y++) {
            s32 hx, hy;
            u16 *p;
            x = minX;
            if (x <= maxX) {
                goto test0;
            loop0:
                hx = (s32)x >> 4;
                hy = (s32)y >> 4;
                p = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer);
                if (p && Item_IsFurniture(p)) {
                    s32 id = Ftr_GetSeries(p);
                    if (Series_GetType(id) == 2) {
                        u32 b = Ftr_GetIndexInSeries(p);
                        acc[id] |= 1 << b;
                    }
                }
                x++;
            test0:
                if (x <= maxX) goto loop0;
            }
        }
    }
    for (i = 0; i < 0x4a; i++) {
        if (Series_GetType(i) == 2) {
            u32 bits = 0;
            u32 k;
            u32 n = FtrInfo_CountInSeries(i);
            for (k = 0; k < n; k++) {
                bits = (u16)(bits | (1 << k));
            }
            if (acc[i] >= bits) {
                res = 1;
                if ((s32)i < 0x4a) {
                    u32 v = n * 1000;
                    if (sHappyRoomSeriesScores.w[i] < v) sHappyRoomSeriesScores.w[i] = v;
                }
            }
        }
    }
    return res;
}

void RoomScoreEvaluator::collectUnk06Kinds(BlockMap *grid)
{
    u8 layer;
    u32 y, x;
    for (layer = 0; layer < 2; layer++) {
        for (y = minZ; y <= maxZ; y++) {
            s32 hx, hy;
            u16 *p;
            x = minX;
            if (x <= maxX) {
                goto test0;
            loop0:
                hx = (s32)x >> 4;
                hy = (s32)y >> 4;
                p = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer);
                if (p && Item_IsFurniture(p)) {
                    s32 id = Item_GetFurnitureIndex(p);
                    s32 kind = FtrInfo_GetUnk06(id);
                    s32 idx = FtrInfo_GetSeries(id);
                    s32 bit = 0;
                    if (kind == 1) bit = 1;
                    else if (kind == 2) bit = 2;
                    else if (kind == 3) bit = 4;
                    else if (kind == 4) bit = 8;
                    *(volatile u32 *)&sHappyRoomUnk06Masks.w[idx] = bit | *(volatile u32 *)&sHappyRoomUnk06Masks.w[idx];
                    sHappyRoomUnk06Masks.extra |= bit;
                }
                x++;
            test0:
                if (x <= maxX) goto loop0;
            }
        }
    }
}

s32 RoomScoreEvaluator::scoreBasePoints(BlockMap *grid)
{
    u8 layer;
    u32 y, x;
    s32 total = 0;
    for (layer = 0; layer < 2; layer++) {
        for (y = minZ; y <= maxZ; y++) {
            s32 hx, hy;
            u16 *p;
            x = minX;
            if (x <= maxX) {
                goto test0;
            loop0:
                hx = (s32)x >> 4;
                hy = (s32)y >> 4;
                p = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer);
                if (p && Item_IsFurniture(p)) {
                    total += FtrClass_GetBasePoints(FtrInfo_GetClass(Item_GetFurnitureIndex(p)));
                }
                x++;
            test0:
                if (x <= maxX) goto loop0;
            }
        }
    }
    return total;
}

s32 RoomScoreEvaluator::scoreFengShui(RoomFengShui *o)
{
    s32 a = o->getEastCount();
    s32 b = o->getWestCount();
    return (a + (b + o->getSouthCount())) * 100;
}

s32 RoomScoreEvaluator::scoreColorTheme(BlockMap *grid)
{
    u32 n;
    u8 layer;
    u32 y, x, k, i, j;
    u8 counts[13];
    u16 ids[24];
    s32 cnt;
    MI_CpuFill8(counts, 0, 13);
    for (i = 0; i < 24; i++) {
        ids[i] = 0xffff;
    }
    n = 0;
    for (layer = 0; layer < 2; layer++) {
        for (y = minZ; y <= maxZ; y++) {
            s32 hx, hy;
            u16 *p;
            x = minX;
            if (x <= maxX) {
                goto test0;
            loop0:
                hx = (s32)x >> 4;
                hy = (s32)y >> 4;
                p = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer);
                if (p && Item_IsFurniture(p)) {
                    s32 id = Item_GetFurnitureIndex(p);
                    s32 t, u;
                    for (k = 0; k < 24; k++) {
                        u16 v = ids[k];
                        if (id == v) break;
                        if (v == 0xffff) {
                            ids[k] = id;
                            break;
                        }
                    }
                    t = FtrInfo_GetColor1(id);
                    u = FtrInfo_GetColor2(id);
                    counts[t]++;
                    counts[u]++;
                    n++;
                }
                x++;
            test0:
                if (x <= maxX) goto loop0;
            }
        }
    }
    if (n >= 10) {
        cnt = 0;
        for (k = 0; k < 24; k++) {
            if (ids[k] != 0xffff) cnt++;
        }
        j = 0;
        for (; j < 13; j++) {
            if (j != 0) {
                s32 q = FX_Div(counts[j] << 12, n << 13);
                if (q >= 0xe66) return cnt * 600;
                if (q >= 0xb33) return cnt * 200;
            }
        }
    }
    return 0;
}

s32 RoomScoreEvaluator::scoreFlagPairThemes(BlockMap *grid, s32 *out1, s32 *out2)
{
    u8 a_[3];
    u8 b_[3];
    u16 arr_[24];
    u32 y;
    u32 x;
    s32 total;
    s32 cnt;
    u8 layer;
    u8 layer2;
    u16 *p3;
    u16 *p4;
    s32 n;
    s32 k;
    u32 i;
    s32 v;
    u32 j;
    MI_CpuFill8(a_, 0, 3);
    MI_CpuFill8(b_, 0, 3);
    for (i = 0; i < 24; i++) arr_[i] = 0xffff;
    total = 0;
    for (i = 0; i < 24; i++) arr_[i] = 0xffff;
    cnt = 0;
    for (layer = 0; layer < 2; layer++) {
        for (y = minZ; y <= maxZ; y++) {
            x = minX;
            if (x <= maxX) {
            goto test3;
        loop3:
            {
                s32 hx = (s32)x >> 4;
                s32 hy = (s32)y >> 4;
                p3 = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer);
                if (p3 && Item_IsFurniture(p3)) {
                    v = Item_GetFurnitureIndex(p3);
                    for (j = 0; j < 24; j++) {
                        u16 *q = &arr_[j];
                        if (v == arr_[j]) break;
                        if (arr_[j] == 0xffff) { *q = v; break; }
                    }
                    k = Ftr_GetFlagPairA(p3);
                    a_[k] = a_[k] + 1;
                    cnt++;
                }
            }
            x++;
        test3:
            if (x <= maxX) goto loop3;
            }
        }
    }
    if ((u32)cnt >= 10) {
        n = 0;
        for (i = 0; i < 24; i++) if (arr_[i] != 0xffff) n++;
        for (i = 0; i < 3; i++) {
            if (i != 0) {
                s32 r = FX_Div(a_[i] << 12, cnt << 12);
                if (r >= 0xe66) { *out1 = i; total += n * 300; }
                else if (r >= 0xb33) { *out1 = i; total += n * 100; }
            }
        }
    }
    for (i = 0; i < 24; i++) arr_[i] = 0xffff;
    cnt = 0;
    for (layer2 = 0; layer2 < 2; layer2++) {
        for (y = minZ; y <= maxZ; y++) {
            x = minX;
            if (x <= maxX) {
            goto test4;
        loop4:
            {
                s32 hx = (s32)x >> 4;
                s32 hy = (s32)y >> 4;
                p4 = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer2);
                if (p4 && Item_IsFurniture(p4)) {
                    v = Item_GetFurnitureIndex(p4);
                    for (j = 0; j < 24; j++) {
                        u16 *q = &arr_[j];
                        if (v == arr_[j]) break;
                        if (arr_[j] == 0xffff) { *q = v; break; }
                    }
                    k = Ftr_GetFlagPairB(p4);
                    b_[k] = b_[k] + 1;
                    cnt++;
                }
            }
            x++;
        test4:
            if (x <= maxX) goto loop4;
            }
        }
    }
    if ((u32)cnt >= 10) {
        u32 ii;
        s32 nn = 0;
        for (i = 0; i < 24; i++) if (arr_[i] != 0xffff) nn++;
        for (ii = 0; ii < 3; ii++) {
            if (ii != 0) {
                s32 r = FX_Div(b_[ii] << 12, cnt << 12);
                if (r >= 0xe66) { *out2 = ii; total += nn * 300; }
                else if (r >= 0xb33) { *out2 = ii; total += nn * 100; }
            }
        }
    }
    return total;
}

s32 RoomScoreEvaluator::scoreCollection(BlockMap *grid, s32 *out)
{
    u8 counts[5];
    u8 layer;
    u32 y, x;
    s32 total;
    u32 i;
    MI_CpuFill8(counts, 0, 5);
    for (layer = 0; layer < 2; layer++) {
        for (y = minZ; y <= maxZ; y++) {
            x = minX;
            if (x <= maxX) {
            goto test2;
        loop2:
            {
                s32 hx = (s32)x >> 4;
                s32 hy = (s32)y >> 4;
                u16 *p = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer);
                if (p && Item_IsFurniture(p)) {
                    s32 k = Ftr_GetCollectionGroup(p);
                    counts[k] = counts[k] + 1;
                }
            }
            x++;
        test2:
            if (x <= maxX) goto loop2;
            }
        }
    }
    total = 0;
    for (i = 0; i < 5; i++) {
        if (i != 4) {
            u8 *q = &counts[i];
            if (counts[i] >= 8) {
                *out = i;
                total += *q * 400;
            }
        }
    }
    return total;
}

s32 RoomScoreEvaluator::calcPenalty(BlockMap *grid, u8 *f1, u8 *f2)
{
    u8 layer;
    u32 y, x;
    s32 total = 0;
    for (layer = 0; layer < 2; layer++) {
        for (y = minZ; y <= maxZ; y++) {
            x = minX;
            if (x <= maxX) {
            goto test1;
        loop1:
            {
                s32 hx = (s32)x >> 4;
                s32 hy = (s32)y >> 4;
                u16 *p = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer);
                if (p) {
                    if (Item_IsFurniture(p)) {
                        if (FtrInfo_TestAlwaysFlag4(Item_GetFurnitureIndex(p))) {
                            s32 r = Item_GetFurnitureDirection(p);
                            if (x == minX && r == 3) { *f1 = 1; total += 100; }
                            if (x == maxX && r == 1) { *f1 = 1; total += 100; }
                            if (y == minZ && r == 2) { *f1 = 1; total += 100; }
                            if (y == maxZ && r == 0) { *f1 = 1; total += 100; }
                        }
                    } else if (Item_IsNormalItem(p)) {
                        *f2 = 1;
                        total += 1;
                    }
                }
            }
            x++;
        test1:
            if (x <= maxX) goto loop1;
            }
        }
    }
    return total;
}

void RoomScoreEvaluator::collectLuckyItems(BlockMap *grid)
{
    u8 layer;
    u32 y, x;
    for (layer = 0; layer < 2; layer++) {
        for (y = minZ; y <= maxZ; y++) {
            x = minX;
            if (x <= maxX) {
            goto test0;
        loop0:
            {
                s32 hx = (s32)x >> 4;
                s32 hy = (s32)y >> 4;
                u16 *p = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), layer);
                if (p && Item_IsFurniture(p)) {
                    s32 v = Item_GetFurnitureIndex(p);
                    if (FtrInfo_IsLucky(v)) {
                        sHappyRoomLuckyFtr.b[v >> 3] |= 1 << (v & 7);
                    }
                }
            }
            x++;
        test0:
            if (x <= maxX) goto loop0;
            }
        }
    }
}

extern "C" BOOL HappyRoom_SendScoreLetters(void *self, s32 a, s32 b, s32 c, s32 n)
{
    MsgString25 score;
    u8 by[2];
    s32 i;
    s32 z = 0;
    if (String_FormatNumber(&score, b, 10, 1, 0, 0)) {
        MailText_SetSlot(1, &score);
        ItemName item(c);
        MailText_SetSlot(2, &item);
        if (n < 4) {
            MsgString33 kind;
            by[1] = n;
            String_LoadResolveAltText(&kind, &by[1], "st_furniture_letter");
            MailText_SetSlot(3, &kind);
        }
        for (i = 0; i < 4; i++) {
            PlayerData *p = (PlayerData *)PlayerData_GetResident(gSavePlayers, i);
            if (p && p->isUsed()) {
                if (DebugVar_GetPtr(z, 0x22)[0] != 0 || p->testFlag(0xe)) {
                    Letter letter;
                    by[0] = a;
                    Letter_ComposeFromMail((LetterView *)&letter, &by[0], "ev_happyroom", data_020dc088, data_020dc07c, p->getPlayerId());
                    LetterDelivery_PutInAddresseeMailbox(&letter);
                }
            }
        }
        return TRUE;
    }
    return FALSE;
}

extern "C" void HappyRoom_SendPrizeLetter(void *self, s32 n)
{
    s32 id;
    s32 t;
    s32 off;
    id = -1;
    t = 1;
    off = 0xfff1;
    if (gSaveData.testFlag(1) == 0) {
        if (n >= 0x11170) { id = 0x18; t = 1; off = 0x3854; }
    } else if (gSaveData.testFlag(2) == 0) {
        if (n >= 0x186a0) { id = 0x19; t = 2; off = 0x3858; }
    } else if (gSaveData.testFlag(0xb) == 0) {
        if (n >= 0x249f0) { id = 0x1a; t = 0xb; off = 0x385c; }
    }
    if (id != -1) {
        s32 i;
        s32 zero = 0;
        for (i = 0; i < 4; i++) {
            PlayerData *p = (PlayerData *)PlayerData_GetResident(gSavePlayers, i);
            u8 b;
            if (p && p->isUsed() && p->testFlag(0xe) && !LetterDelivery_IsMailboxFull(i)) {
                Letter letter;
                b = id;
                Letter_ComposeFromMail((LetterView *)&letter, &b, "ev_happyroom", data_020dc084, data_020dc08c, p->getPlayerId());
                ((LetterView *)&letter)->setPresent(off, 1);
                if (LetterDelivery_PutInAddresseeMailbox(&letter)) {
                    gSaveData.setFlag(t);
                    break;
                }
                if (LetterDelivery_QueueOutgoing(&letter, zero)) {
                    gSaveData.setFlag(t);
                    break;
                }
            }
        }
    }
}

extern "C" BOOL RoomMap_GetFloorBounds(s32 *a, s32 *b, s32 *c, s32 *d, BlockMap *grid)
{
    BOOL f0, f1, f2, f3;
    s32 y, x;
    *c = 16;
    *a = *c;
    *d = -16;
    *b = *d;
    f0 = FALSE; f1 = FALSE; f2 = FALSE; f3 = FALSE;
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            if (grid->canPlaceItem(x, y)) {
                if (x <= *a) { *a = x; f0 = TRUE; }
                if (x >= *b) { *b = x; f1 = TRUE; }
                if (y <= *c) { *c = y; f2 = TRUE; }
                if (y >= *d) { *d = y; f3 = TRUE; }
            }
        }
    }
    f0 = f0 & f1;
    f2 = f2 & f0;
    f3 = f3 & f2;
    if (f3) return TRUE;
    return FALSE;
}

extern "C" BOOL HappyRoom_SendWelcomeLetter()
{
    u8 b;
    PlayerData *p = PlayerData_GetCurrent();
    if (p && p->testFlag(3) && !p->testFlag(0xe)) {
        Letter letter;
        b = 0x1b;
        Letter_ComposeFromMail((LetterView *)&letter, &b, "ev_happyroom", data_020dc080, data_020dc090, p->getPlayerId());
        if (LetterDelivery_PutInAddresseeMailbox(&letter)) {
            p->setFlag(0xe);
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" BOOL Villager_SendLetterWithPaper(const char *r0, u8 r1, PlayerId *r2, VillagerId *r3, u16 *p, s32 v)
{
    if (SaveVillagers_Find(gSaveVillagers, (u16 *)r3)) {
        u8 buf[2];
        r3->makeFileName(sVillagerLetterWithPaperPath, 0x28, r0);
        buf[0] = r1;
        buf[1] = LetterPaper_PickForPersonality(VillagerId_GetPersonality(r3));
        if (v != -1) buf[1] = v;
        Letter letter;
        Letter_ComposeVillagerMail((LetterView *)&letter, buf, sVillagerLetterWithPaperPath, &buf[1], r3, r2, 1);
        if (p) ((LetterView *)&letter)->setPresent(*p, 1);
        if (LetterDelivery_PutInAddresseeMailbox(&letter)) {
            return TRUE;
        }
        if (LetterDelivery_QueueOutgoing(&letter, 0)) {
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" BOOL Villager_SendBirthdayNoticeLetter(PlayerId *a, VillagerId *b)
{
    u8 *r = SaveVillagers_Find(gSaveVillagers, (u16 *)b);
    if (r) {
        MailText_SetSlotMonth(2, *Villager_GetBirthday((VillagerData *)r));
        MailText_SetSlotDayOrdinal(3, Villager_GetBirthday((VillagerData *)r)[1]);
        return Villager_SendLetterWithPaper("ev_nbirth", Random_GlobalBelow(3), a, b, 0, 0x1a);
    }
    return FALSE;
}

extern "C" s32 Villager_SendHouseVisitLetter(u32 a, PlayerId *b, VillagerId *c)
{
    if (a < 1) {
        return 0;
    }
    if (a > 5) {
        return 0;
    }
    u16 res = 0xfff1;
    Random_GlobalBelow(3);
    Random_GlobalBelow(3);
    switch (a) {
    case 1: {
        ItemPickSpec o(0, 0);
        ItemPick_One(&res, &o, NULL, NULL, 1, 1, NULL);
        break;
    }
    case 2: {
        static ItemPickSpec t[3] = { ItemPickSpec(0, 1), ItemPickSpec(0, 2), ItemPickSpec(0, 3) };
        ItemPickSpec o = t[Random_GlobalBelow(3)];
        ItemPick_One(&res, &o, NULL, NULL, 1, 1, NULL);
        break;
    }
    case 3: {
        static ItemPickSpec t[3] = { ItemPickSpec(0, 0), ItemPickSpec(4, 0), ItemPickSpec(3, 0) };
        ItemPickSpec o = t[Random_GlobalBelow(3)];
        ItemPick_One(&res, &o, NULL, NULL, 1, 1, NULL);
        break;
    }
    case 4: {
        static ItemPickSpec t[9] = { ItemPickSpec(0, 1), ItemPickSpec(0, 2), ItemPickSpec(0, 3),
                                     ItemPickSpec(4, 1), ItemPickSpec(4, 2), ItemPickSpec(4, 3),
                                     ItemPickSpec(3, 1), ItemPickSpec(3, 2), ItemPickSpec(3, 3) };
        ItemPickSpec o = t[Random_GlobalBelow(9)];
        ItemPick_One(&res, &o, NULL, NULL, 1, 1, NULL);
        break;
    }
    case 0:
    default: {
        u8 *r6 = PlayerDataArray_GetById(gSavePlayers, (u16 *)b);
        u32 r4 = sHouseVisitGiftKinds[Random_GlobalBelow(3)];
        ItemPickSpec o(r4, 0);
        s32 x;
        ItemPick_One(&res, &o, r6, NULL, 1, 1, &x);
        if (res == 0xfff1) {
            ItemPickSpec o2(r4, x);
            ItemPick_OneSimple(&res, &o2);
        }
        break;
    }
    }
    return Villager_SendLetterWithPaper("re_q10", Random_GlobalBelow(3), b, c, &res, -1);
}

