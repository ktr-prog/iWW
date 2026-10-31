#include "uptr.h"
#include "host_labels.h"
#include "types.h"
#include "sys/ClockDateTime.h"
#include "save/DramaPart.h"
#include "gfx/VecFx32.h"
#include "player/PlayerSpNpcRecord.h"
#include "npc/VillagerId.h"
#include "save/Unk_02085810_Rec.h"
#include "save/BlancaFaceRecord.h"
#include "save/LostChildRecord.h"
#include "town/VisitorPos.h"
#include "save/ContestRecord.h"
#include "talk/MsgString9B.h"
#include "talk/MsgString25.h"
#include "item/ItemName.h"
#include "item/Letter.h"
#include "town/TownBlockMap.h"
#include "town/BlockMap.h"
#pragma opt_loop_invariants off
#define LB(o) (((u8 *)&l)[o])
#include "types.h"
#include "item/ItemPickSpec.h"
#include "item/LetterView.h"
#include "net/CommManager.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "save/MuseumData.h"
#include "save/Pattern.h"
#include "save/SaveData.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_020030d8.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02085940.h"
#include "proto/main/unk_02087e0c.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b2c50.h"





#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)




struct ContestLetterLocals {
    /* 0x00 */ u8 letterVariant;
    /* 0x02 */ u16 trophy;
    /* 0x04 */ u16 emptyItem;
    /* 0x06 */ u8 today[3];
    /* 0x0c */ u32 contestTime[2];
    /* 0x14 */ u32 now;
    /* 0x18 */ u32 nowHi;
};



#include "game/RoostGuestRoll.h"


struct Unk_02086340_T {
    u32 w0, w1;
};

#include "game/GulliverQuest.h"


#include "game/ReddLastSale.h"

extern SaveData gSaveData;

#include "game/TurnipMarket.h"



extern const VecXZ sGulliverSpotOffsets[];

extern const s16 sGulliverRepairedAngles[];


class Unk_02086e60;

#include "town/VisitorSpawnFlags.h"

#include "town/PeteFallState.h"


#include "town/TownTravelState.h"

#include "town/ResettiVisitFlag.h"

struct Unk_02086f38_Buf {
    s32 a, b;
};

#include "town/ShopClosingTime.h"

#include "town/KatieVisitState.h"



struct DramaScheduleEntry {
    u8 a;
    u8 b;
    u8 pad[2];
    u32 c;
};

#include "player/PlayerDailyTalkFlags.h"
#include "proto/main/unk_0204cc1c.h"






struct MissingLetterLocals {
    u8 a;
    u8 b;
    u16 h;
    u8 c[3];
    u8 pad;
};


extern "C" {
void Clock_GetDate(u8 *p);
s32 Item_IsFurniture(u16 *p);
u32 Item_GetFurnitureIndex(void *p);
void DateTime_Make(void *a, void *b, u32 c, u32 d, u32 e);
void Clock_GetDateTime(void *p);
void DateTime_SubDays(void *p, s32 v);
s32 DateTime_Compare(void *a, void *b, s32 c);
s32 DateTime_DiffDays(void *a, void *b);
s32 Event_GetDaysSinceStart(s32 a);
s32 Clock_GetWeekday();
s32 Math_IsInRange(u32 v, u32 lo, u32 hi);
s32 NookShop_GetLevel(void *p);
void *MI_CpuFill8(void *d, s32 v, u32 n);
void MI_CpuCopy8(void *, void *, u32);
s32 Date_GetWeekday(s32 a, s32 b, s32 c);
s32 TownMap_IsUnitWalkable(s32 x, s32 y, void *grid);
s32 Item_IsMarker(u16 *p);
s32 Item_IsTreeStage0(u16 *p);
extern BlockMap *gSceneBlockMap;
extern u8 data_021c47c4_dummy[];
s32 Date_GetNthWeekdayDay(u8 a, u32 b, u32 c, u32 d);
void DateTime_AddDays(void *, s32);
void ItemPickSpec_Destruct(void *);
extern CommManager *gCommManager;
extern const u8 data_020cf288[];
extern const u8 data_020cf328[];
extern s32 gGfxMainOnTop;
}


static inline BOOL Unk_0208709c_Chk(u16 *p) {
    BOOL f9 = TRUE;
    BOOL f8 = TRUE, f7 = TRUE, f6 = TRUE, f5 = TRUE, f4 = TRUE, f3 = TRUE, f2 = TRUE;
    BOOL f1 = FALSE;
    u32 v = *p;
    if (v >= 0x26 && v <= 0x2a) f1 = TRUE;
    if (f1 == 0) {
        if (!(v >= 0x5d && v <= 0x61)) f2 = FALSE;
    }
    if (f2 == 0) {
        if (!(v >= 0x2f && v <= 0x56)) f3 = FALSE;
    }
    if (f3 == 0) {
        if (!(v >= 0x57 && v <= 0x5b)) f4 = FALSE;
    }
    if (f4 == 0) {
        if (!(v >= 0x66 && v <= 0x68)) f5 = FALSE;
    }
    if (f5 == 0) {
        if (v != 0x69) f6 = FALSE;
    }
    if (f6 == 0) {
        if (!(v >= 0x6a && v <= 0x6c)) f7 = FALSE;
    }
    if (f7 == 0) {
        if (v != 0x6d) f8 = FALSE;
    }
    if (f8 == 0) {
        if (!(v >= 0xc8 && v <= 0xcf)) f9 = FALSE;
    }
    return f9;
}

static inline u16 *Unk_0208709c_Cell(BlockMap *map, s32 x, s32 y) {
    s32 hx = x >> 4;
    s32 hy = y >> 4;
    s32 lx = x - (hx << 4);
    s32 ly = y - (hy << 4);
    return BlockMap_GetItemPtr(map, hx, hy, lx, ly, 0);
}

static inline BOOL Unk_0208709c_In(u16 *p) {
    BOOL f = FALSE;
    if (*p >= 0x5000 && *p <= 0x5021) f = TRUE;
    return f;
}

extern "C" BOOL Cell_HitTest(void *p, s32 a, s32 b, s32 c, s32 d) {
    u32 *obj = (u32 *)p;
    s32 r7 = Oam_GetObjX(obj) - c;
    if (r7 > a) return FALSE;
    if (r7 + (c * 2 + Oam_GetObjWidth(obj)) < a) return FALSE;
    s32 t = Oam_GetObjY((s8 *)obj) - d;
    if (t > b) return FALSE;
    if (t + (d * 2 + Oam_GetObjHeight(obj)) >= b) return TRUE;
    return FALSE;
}

extern "C" s32 Cell_HitTestList(void *p, s32 n, s32 c, s32 d, s32 e, s32 f) {
    s32 i;
    for (i = 0; i < n; p = (u8 *)p + 8, i++) {
        if (Cell_HitTest(p, c, d, e, f)) {
            return i;
        }
    }
    return -1;
}

extern "C" s32 Oam_AllocAffine(u8 *self, s32 *cnt, s32 *v) {
    volatile s32 *vv = v;
    s32 a = (u32)(vv[0] << 12) >> 16;
    s32 b = (u32)(vv[1] << 12) >> 16;
    s32 c = (u32)(vv[2] << 12) >> 16;
    s32 d = (u32)(vv[3] << 12) >> 16;
    s32 i, n;
    i = 0;
    n = *cnt;
    for (; i < n; i += 4) {
        u16 *e = (u16 *)(self + i * 8);
        if (a == e[3] && b == e[7] && c == e[11] && d == e[15]) {
            return i >> 2;
        }
    }
    if (n < 128) {
        u16 *e = (u16 *)(self + n * 8);
        e[3] = v[0] >> 4;
        e[7] = v[1] >> 4;
        e[11] = v[2] >> 4;
        e[15] = v[3] >> 4;
        s32 r = *cnt >> 2;
        *cnt += 4;
        return r;
    }
    return -1;
}

extern "C" BOOL Oam_UseBufferA(s32 t) {
    switch (t) {
    case 0:
        return TRUE;
    case 1:
        return FALSE;
    case 2:
        if (gGfxMainOnTop == 1) return TRUE;
        return FALSE;
    case 3:
        if (gGfxMainOnTop == 0) return TRUE;
        return FALSE;
    }
    return FALSE;
}

extern "C" void PlayerSpNpcRecord_Construct() {}

extern "C" void PlayerSpNpcRecord_Destruct() {}

extern "C" void PlayerSpNpcRecord_InitNop() {}

u8 *PlayerSpNpcRecord::getArbeitDate() { return serviceDates + 4; }

void PlayerSpNpcRecord::stampArbeitDate() {
    u8 tmp[4];
    Clock_GetDate(tmp);
    serviceDates[6] = tmp[2];
    serviceDates[5] = tmp[1];
    serviceDates[4] = tmp[0];
}

u32 PlayerSpNpcRecord::getSableTalkCount() { return sableTalkCount; }

void PlayerSpNpcRecord::setSableTalkCount(u32 v) { sableTalkCount = v; }

u32 PlayerSpNpcRecord::getCafeVisits() { return cafeVisits; }

void PlayerSpNpcRecord::setCafeVisits(u32 v) {
    cafeVisits = v;
    if (cafeVisits > 15) cafeVisits = 15;
}

u32 PlayerSpNpcRecord::getHaircutCount() { return haircutCount; }

void PlayerSpNpcRecord::addHaircutCount(u32 v) {
    haircutCount = haircutCount + v;
    if (haircutCount > 16) haircutCount = 16;
}

u32 PlayerSpNpcRecord::getAcornsDelivered() { return acornsDelivered; }

void PlayerSpNpcRecord::addAcornsDelivered(s32 v) {
    s32 t = acornsDelivered;
    t = t + v;
    if (t > 255) t = 255;
    acornsDelivered = t;
}

u32 PlayerSpNpcRecord::getAcornPrizeStep() { return acornPrizeStep; }

void PlayerSpNpcRecord::advanceAcornPrizeStep() {
    acornPrizeStep = acornPrizeStep + 1;
    if (acornPrizeStep > 12) acornPrizeStep = 12;
}

u32 PlayerSpNpcRecord::getResetCount() { return resetCount; }

void PlayerSpNpcRecord::addResetCount() {
    resetCount = resetCount + 1;
    if (resetCount > 6) resetCount = 6;
}

u32 PlayerSpNpcRecord::getStyleScore() { return styleScore; }

void PlayerSpNpcRecord::addStyleScore(u32 v) {
    styleScore = styleScore + v;
    if (styleScore > 100) styleScore = 100;
}

u32 PlayerSpNpcRecord::hasEnteredFishingTourney() { return unk_10_0; }

void PlayerSpNpcRecord::setEnteredFishingTourney(s32 v) { unk_10 = (unk_10 & ~1) | (v & 1); }

u32 PlayerSpNpcRecord::hasEnteredBugOff() { return unk_10_1; }

void PlayerSpNpcRecord::setEnteredBugOff(s32 v) { unk_10 = (unk_10 & ~2) | ((v & 1) << 1); }

u32 PlayerSpNpcRecord::getFireworksGiven() { return unk_10_2; }

void PlayerSpNpcRecord::addFireworksGiven() {
    unk_10_2 = unk_10_2 + 1;
    if (unk_10_2 > 10) {
        unk_10_2 = 10;
    }
}

void PlayerSpNpcRecord::resetFireworksGiven() { unk_10_2 = 0; }

void PlayerSpNpcRecord::resetAcornCount() { acornsDelivered = 0; acornPrizeStep = 0; }

u32 PlayerSpNpcRecord::hasFestivalGift() { return unk_10_6; }

void PlayerSpNpcRecord::setFestivalGift() { unk_10_6 = 1; }

void PlayerSpNpcRecord::clearFestivalGift() { unk_10_6 = 0; }

extern "C" void *PlayerSpNpcRecord_GetInsuranceDate(void *p) { return p; }

void PlayerDailyTalkFlags::stampToday() {
    u8 tmp[4];
    Clock_GetDate(tmp);
    date[2] = tmp[2];
    date[1] = tmp[1];
    date[0] = tmp[0];
}

u32 PlayerSpNpcRecord::getInsuranceClaims() { return insuranceClaims; }

void PlayerSpNpcRecord::addInsuranceClaim() {
    insuranceClaims = insuranceClaims + 1;
    if (insuranceClaims >= 0xff) insuranceClaims = 0xff;
}

extern "C" void PlayerSpNpcRecord_SendMissingLetter() {
    MissingLetterLocals l;
    PlayerData *r4 = PlayerData_GetCurrent();
    if (r4 != NULL && r4->testFlag(0x36)) {
        Letter big;
        l.a = 0;
        l.a = Random_GlobalBelow(3);
        Clock_GetDate(l.c);
        l.b = LetterPaper_PickRandom(3, l.c[1]);
        Letter_ComposeFromMail((LetterView *)&big, &l.a, "sp_npc_missing", data_020e0c44, &l.b, r4->getPlayerId());
        {
            ItemPickSpec obj;
            obj.set(0, 0x1b);
            ItemPick_One(&l.h, &obj, 0, 0, 1, 1, 0);
            ((LetterView *)&big)->setPresent(l.h, 1);
        }
        if (LetterDelivery_QueueOutgoing(&big, 0)) {
            r4->clearFlag(0x36);
        }
    }
}

BOOL PlayerSpNpcRecord::sendInsuranceLetter(s32 idx, u16 *v) {
    Letter big;
    u8 c;
    BOOL r;
    c = 0;
    PlayerData *o = PlayerData_GetCurrent();
    c = idx;
    Letter_ComposeFromMail((LetterView *)&big, &c, "sp_npc_insurance", data_020e0c4c, data_020e0c54, o->getPlayerId());
    ((LetterView *)&big)->setPresent(*v, 1);
    if (LetterDelivery_QueueOutgoing(&big, 0)) {
        r = TRUE;
    } else {
        r = FALSE;
    }
    return r;
}

void PlayerSpNpcRecord::sendInsuranceLetters() {
    u16 h[3];
    s32 r6;
    MsgString25 bufA;
    void *obj = PlayerData_GetCurrent();
    MsgString9B bufB;
    PlayerSpNpcRecord *r7 = (PlayerSpNpcRecord *)((PlayerData *)(obj))->getSpNpcRecord();
    if (((PlayerData *)(obj))->testFlag(0x17)) {
        if (((PlayerData *)(obj))->testFlag(0x19)) {
            h[0] = 0x1492;
            s32 r = Random_GlobalBelow(2);
            if (sendInsuranceLetter(r, &h[0])) {
                ((PlayerData *)obj)->clearFlag(0x19);
            }
        }
        if (((PlayerData *)(obj))->testFlag(0x1a)) {
            h[1] = 0x1492;
            s32 r = Random_GlobalBelow(2);
            if (sendInsuranceLetter(r + 2, &h[1])) {
                ((PlayerData *)obj)->clearFlag(0x1a);
            }
        }
    }
    if (((PlayerData *)(obj))->testFlag(0x18)) {
        if (r7->getInsuranceClaims() >= 1) {
            String_FormatNumber(&bufA, r7->getInsuranceClaims(), 10, 0, 0, 0);
            MailText_SetSlot(3, &bufA);
            r6 = Random_GlobalBelow(2) + 4;
            u32 cnt = r7->getInsuranceClaims();
            if (cnt >= 10) {
                cnt = 10;
                r6 = 6;
            }
            String_FormatNumber(&bufA, cnt * 100, 10, 0, 0, 0);
            MailText_SetSlot(4, &bufA);
            h[2] = cnt + 0x1491;
            if (sendInsuranceLetter(r6, &h[2])) {
                insuranceClaims = 0;
            }
        }
    }
}

extern "C" void PlayerDailyTalkFlags_Construct() {}

extern "C" void PlayerDailyTalkFlags_Destruct() {}

void PlayerDailyTalkFlags::clearAll() {
    MI_CpuFill8(flags, 0, 8);
}

void PlayerDailyTalkFlags::setDate(u8 *src) {
    date[2] = src[2];
    date[1] = src[1];
    date[0] = src[0];
}

BOOL PlayerDailyTalkFlags::test(u32 i) {
    BOOL r;
    s32 w = i >> 5;
    u32 b = i & 0x1f;
    if (w < 2) {
        r = TRUE;
        if (((r << b) & flags[w]) != 0) {
            goto out;
        }
    }
    r = FALSE;
out:
    return r;
}

void PlayerDailyTalkFlags::set(u32 i) {
    u8 tmp[4];
    s32 w = i >> 5;
    u32 b = i & 0x1f;
    if (w < 2) {
        flags[w] = *(volatile u32 *)&flags[w] | (1 << b);
    }
    Clock_GetDate(tmp);
    setDate(tmp);
}

void PlayerDailyTalkFlags::clear(u32 i) {
    s32 w = i >> 5;
    u32 b = i & 0x1f;
    if (w < 2) {
        flags[w] = ~(1 << b) & *(volatile u32 *)&flags[w];
    }
}

extern "C" void DramaRecord_Construct() {}

extern "C" void DramaRecord_Destruct() {}

extern "C" void DramaRecord_Clear(DramaRecord *a) {
    MI_CpuFill8(a, 0xff, 1);
}

extern "C" void DramaRecord_GetLastPart(DramaRecord *a, Unk_020874e8_Bits *b) {
    MI_CpuCopy8(&a->lastPart, b, 1);
}

extern "C" void DramaRecord_SetLastPart(DramaRecord *a, Unk_020874e8_Bits *b) {
    Clock_GetDate((u8 *)&a->date);
    MI_CpuCopy8(b, &a->lastPart, 1);
}

extern "C" ClockDate *DramaRecord_GetDate(DramaRecord *p) {
    return &p->date;
}

extern "C" BOOL Drama_FindScheduledPart(s32 lim, s32 b, s32 c, Unk_020874e8_Bits *out) {
    ClockDateTimeWords s1, s2;
    s32 r4, r7, r6;
    u32 x4, x8, xc;
    s32 j;
    s32 v;
    DramaScheduleEntry *t1;
    const u8 *t2;
    u32 *t3;
    s1.words[0] = 0;
    s1.words[1] = 0;
    s1.dt.year = lim;
    s1.dt.month = b;
    s1.dt.day = c;
    r4 = lim - 1;
    goto test4;
loop4:
    if (r4 >= 0) {
        r7 = 0;
        goto test7;
    loop7:
        r6 = 0;
        t1 = (DramaScheduleEntry *)(data_020cf288 + r7 * 0x28);
        t2 = data_020cf328 + r7 * 0x8c;
        goto test6;
    loop6:
        DramaScheduleEntry *e;
        e = &t1[r6];
        x8 = t1[r6].a;
        if (x8 != 0) {
            x4 = e->b;
            xc = e->c;
        retry:
            s32 r;
            r = Date_GetNthWeekdayDay(r4, x8, xc, x4);
            if (r == -1) {
                x4 = (u8)(x4 - 1);
                goto retry;
            }
            s2.words[0] = 0;
            s2.words[1] = 0;
            s2.dt.year = r4;
            s2.dt.month = x8;
            s2.dt.day = r;
            j = 0;
            t3 = (u32 *)(t2 + r6 * 0x1c);
            for (; j < 7; j++) {
                v = t3[j];
                if (v == 0) continue;
                s32 t = DateTime_DiffDays(&s1, &s2);
                if (t == 0) {
                    t = -DateTime_DiffDays(&s2, &s1);
                }
                if (t + v > 0 && t <= 0) {
                    out->a = r7;
                    out->b = r6;
                    out->c = j;
                    return TRUE;
                }
                DateTime_AddDays(&s2, v);
            }
        }
        r6++;
    test6:
        if (r6 < 5) goto loop6;
        r7++;
    test7:
        if (r7 < 4) goto loop7;
    }
    r4++;
test4:
    if (r4 <= lim) goto loop4;
    return FALSE;
}

extern "C" BOOL Drama_GetAvailablePart(s32 a, s32 b, s32 c, Unk_020874e8_Bits *d) {
    if (((CommManager *)(gCommManager))->isOnline()) {
        return FALSE;
    }
    void *o = PlayerData_GetCurrent();
    if (((PlayerData *)(o))->testFlag(1)) {
        return FALSE;
    }
    if (!Drama_FindScheduledPart(a, b, c, d)) {
        return FALSE;
    }
    Unk_020874e8_Bits t;
    DramaRecord_GetLastPart(((PlayerData *)(o))->getDramaRecord(), &t);
    ClockDate *p = DramaRecord_GetDate(((PlayerData *)(o))->getDramaRecord());
    if (d->a == t.a && d->b == t.b && d->c == t.c) {
        if ((p->year == a && p->month == b && p->day == c) || (p->year == 0 && p->month == 0 && p->day == 0)) {
            return TRUE;
        }
        return FALSE;
    }
    if (d->c == 0) {
        switch (d->a) {
        case 0:
            if (((PlayerData *)(o))->testFlag(6)) {
                return TRUE;
            }
            break;
        case 2:
            if (((PlayerSpNpcRecord *)((PlayerData *)(o))->getSpNpcRecord())->getSableTalkCount() == 0xf) {
                return TRUE;
            }
            break;
        case 3:
            if (NookShop_GetLevel(gSaveData.nookShop) == 3) {
                return TRUE;
            }
            break;
        case 1:
            if (((PlayerData *)(o))->testFlag(8) || ((MuseumData *)gSaveData.museum)->isComplete()) {
                return TRUE;
            }
            break;
        }
    } else {
        u8 v = d->c - 1;
        if (d->a == t.a && d->b == t.b && v == t.c) {
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void *LostChildRecord_Construct(void *p) {
    TownId_Construct();
    return p;
}

extern "C" void *LostChildRecord_Destruct(void *p) {
    TownId_Destruct();
    return p;
}

extern "C" void LostChild_AdvanceDays(s32 n) {
    if (n >= 1) {
        LostChildRecord *const g = (LostChildRecord *)gSaveData.lostChild;
        s32 v = g->getDaysLeft() - n;
        if (v < 0) v = 0;
        if (v <= 0) {
            g->clear();
        } else {
            g->setDaysLeft((u8)v);
        }
        LostChild_LoadFromTown();
    }
}

extern "C" BOOL LostChild_IsKatieDue() {
    void *c = PlayerData_GetCurrent();
    if (c != 0) {
        LostChildRecord *p = (LostChildRecord *)((PlayerData *)(c))->getLostChildRecord();
        if (p->isKaitlinRole() == 0) {
            if (Math_IsInRange(p->getDaysLeft(), 1, 7) != 0) return TRUE;
        }
    }
    return FALSE;
}

extern "C" BOOL LostChild_IsKaitlinDue() {
    void *c = PlayerData_GetCurrent();
    if (c != 0) {
        LostChildRecord *p = (LostChildRecord *)((PlayerData *)(c))->getLostChildRecord();
        if (p->isKaitlinRole() == 1) {
            if (Math_IsInRange(p->getDaysLeft(), 1, 7) != 0) return TRUE;
        }
    }
    return FALSE;
}

extern "C" void LostChild_SaveToTown() {
    u8 *const g = gSaveData.lostChild;
    void *c = PlayerData_GetCurrent();
    if (c != 0 && g != 0) {
        MI_CpuCopy8(((PlayerData *)(c))->getLostChildRecord(), g, 12);
    }
}

extern "C" void LostChild_LoadFromTown() {
    u8 *const g = gSaveData.lostChild;
    void *a = PlayerData_GetCurrent();
    if (a != 0 && g != 0) {
        void *b = ((PlayerData *)(a))->getLostChildRecord();
        MI_CpuCopy8(g, b, 12);
        if (Math_IsInRange(((LostChildRecord *)g)->getDaysLeft(), 1, 7) == 0) ((PlayerData *)(a))->clearFlag(0x33);
    }
}

void LostChildRecord::clear() {
    TownId_Clear(getTownId());
    daysLeft = 0;
    kaitlinRole = 0;
    escorting = 0;
}

u16 *LostChildRecord::getTownId() { return (u16 *)this; }

void LostChildRecord::setTownId(void *src) { TownId_Assign(this, src); }

u32 LostChildRecord::getDaysLeft() { return daysLeft; }

void LostChildRecord::setDaysLeft(u8 v) { daysLeft = v; }

BOOL LostChildRecord::isKaitlinRole() { return kaitlinRole; }

void LostChildRecord::setKaitlinRole(u8 v) { kaitlinRole = v; }

BOOL LostChildRecord::isEscorting() {
    if (escorting) return TRUE;
    return FALSE;
}

void LostChildRecord::setEscorting() { escorting = 1; }

void LostChildRecord::clearEscorting() { escorting = 0; }

BlancaFaceRecord *BlancaFaceRecord::construct() {
    new (this) Pattern();
    return this;
}

BlancaFaceRecord *BlancaFaceRecord::destruct() {
    ((Pattern *)(this))->~Pattern();
    return this;
}

void BlancaFaceRecord::reset() {
    visitState = 0;
    resetPattern();
}

void BlancaFaceRecord::init() { reset(); }

void BlancaFaceRecord::resetPattern() {
    ((Pattern *)(getPattern()))->fill(0xf);
    ((PatternInfo *)(((Pattern *)(getPattern()))->getInfo()))->setPalette(0);
}

void *BlancaFaceRecord::getPattern() { return pattern; }

void BlancaFaceRecord::setState(u32 v) { visitState = v; }

u8 BlancaFaceRecord::getState() { return visitState; }

void BlancaFaceRecord::setConcept(u32 v) { concept = v; }

u8 BlancaFaceRecord::getConcept() { return concept; }

BOOL BlancaFaceRecord::isBlancaDue() {
    if (gSaveData.testFlag(0x13) == 0 && visitState == 2) return TRUE;
    return FALSE;
}

void BlancaFaceRecord::setChecksum(u32 v) { checksum = v; }

u16 BlancaFaceRecord::getChecksum() { return checksum; }

void KatieVisitState::construct() {}

void KatieVisitState::destruct() {}

void KatieVisitState::clear() {
    posX = 0;
    posZ = 0;
    following = 0;
}

extern "C" BOOL Field_IsClearSpot(s32 x, s32 y, BlockMap *map) {
    if (map == 0) goto fail;
    if (TownMap_IsUnitWalkable(x, y, map) == 0) goto fail;
    for (s32 i = 1; i <= 2; i++) {
        s32 ty = y + i;
        s32 hx = x >> 4;
        s32 hy = ty >> 4;
        s32 lx = x - (hx << 4);
        u16 *p = BlockMap_GetItemPtr(map, hx, hy, lx, ty - (hy << 4), 0);
        if (p == 0 || Unk_0208709c_In(p) || Item_IsMarker(p) != 0 || (Item_IsTreeStage0(p) == 0 && Unk_0208709c_Chk(p))) {
            return FALSE;
        }
        p = Unk_0208709c_Cell(map, x, y - i);
        if (p == 0 || Unk_0208709c_In(p)) {
            return FALSE;
        }
    }
    return TRUE;
fail:
    return FALSE;
}

void KatieVisitState::pickKatiePos() {
    BlockMap *map = TownBlockMap_Get();
    if (map != 0) {
        s32 cnt = 0;
        s32 bx = 0, by = 0;
        u32 *tbl = sKatieSpotRows;
        s32 x, y;
        MI_CpuFill8(tbl, 0, 0x80);
        FieldUnit_FromBlockUnit(&bx, &by, 2, 2, 0, 0);
        y = 0;
        do {
            x = 0;
            do {
                if (Field_IsClearSpot(bx + x, by + y, map) != 0) {
                    tbl[0] |= 1 << x;
                    cnt++;
                }
                x++;
            } while (x < 32);
            tbl++;
            y++;
        } while (y < 32);
        if (cnt > 0) {
            s32 x2, y2; s32 r = Random_GlobalBelow(cnt);
            tbl = sKatieSpotRows;
            y2 = 0;
            goto testy2;
loopy2:
            x2 = 0;
            goto testx2;
loopx2:
            if (((tbl[0] >> x2) & 1) != 0) {
                if (r == 0) {
                    VecFx32 v;
                    FieldPos_FromUnitCenter(&v, bx + x2, by + y2);
                    setPos(&v);
                    goto after;
                }
                r--;
            }
            x2++;
testx2:
            if (x2 < 32) goto loopx2;
after:
            if (x2 < 32) goto end;
            tbl++;
            y2++;
testy2:
            if (y2 < 32) goto loopy2;
        }
    }
end:
    following = 0;
}

void KatieVisitState::setPos(VecFx32 *v) {
    posX = v->x;
    posZ = v->z;
}

void KatieVisitState::getPos(VecFx32 *out) {
    out->x = posX;
    out->z = posZ;
}

BOOL KatieVisitState::isFollowing() {
    if (following != 0) return TRUE;
    return FALSE;
}

void KatieVisitState::setFollowing() { following = 1; }

void KatieVisitState::clearFollowing() { following = 0; }

void ShopClosingTime::construct() {
    raw[0] = 0;
    raw[1] = 0;
}

void ShopClosingTime::destruct() {}

void ShopClosingTime::clearClosingTime() {
    raw[0] = 0;
    raw[1] = 0;
}

ShopClosingTime *ShopClosingTime::getTime() { return this; }

void ShopClosingTime::setClosingTimeToday() {
    Clock_GetDateTime(this);
    hour = 0x17;
    minute = 0;
    second = 0;
}

BOOL ShopClosingTime::isPastClosingTime() {
    Unk_02086f38_Buf buf;
    buf.a = 0;
    buf.b = 0;
    Clock_GetDateTime(&buf);
    s32 t = DateTime_Compare(this, &buf, 0x3f);
    BOOL r = FALSE;
    if (t == -1) r = TRUE;
    return r;
}

void ResettiVisitFlag::construct() {}

void ResettiVisitFlag::destruct() {}

void ResettiVisitFlag::clear() { isPending = 0; }

BOOL ResettiVisitFlag::isSet() {
    if (isPending != 0) return TRUE;
    return FALSE;
}

void ResettiVisitFlag::set(u32 v) { isPending = v; }

void TownTravelState::construct() {}

void TownTravelState::destruct() {}

void TownTravelState::clearMode() { mode = 0; }

void TownTravelState::setMode(u32 v) { mode = v; }

u8 TownTravelState::getMode() { return mode; }

void TownTravelState::setAngle(s32 v) { angle = v; }

s16 TownTravelState::getAngle() { return angle; }

void PeteFallState::construct() {}

void PeteFallState::destruct() {}

void PeteFallState::clear() { MI_CpuFill8(this, 0, 12); }

void PeteFallState::setPos(VecFx32 *v) {
    fallPosX = v->x;
    fallPosZ = v->z;
}

void PeteFallState::getPos(VecFx32 *out) {
    out->x = fallPosX;
    out->z = fallPosZ;
}

BOOL PeteFallState::hasFallPos() {
    if (fallPosValid) return TRUE;
    return FALSE;
}

void PeteFallState::markFallPos() { fallPosValid = 1; }

void PeteFallState::unmarkFallPos() { fallPosValid = 0; }

BOOL PeteFallState::isVisitorActive() {
    if (visitorActive) return TRUE;
    return FALSE;
}

void PeteFallState::clearVisitorActive() { visitorActive = 0; }

void PeteFallState::setVisitorActive() { visitorActive = 1; }

s16 PeteFallState::getFacing() { return (s16)(facing << 14); }

extern "C" BOOL Field_IsClearSpotYX(s32 x, s32 y, BlockMap *map) { return Field_IsClearSpot(y, x, map); }

extern "C" BOOL Field_IsClearSpotXY(s32 x, s32 y, BlockMap *map) { return Field_IsClearSpot(x, y, map); }

extern "C" s32 Field_PickRandomInLine(s32 *out, BOOL (*cb)(s32, s32, BlockMap *), s32 arg, s32 cur, s32 limit, BlockMap *m, u16 *buf, s32 n) {
    s32 r, bit = 0, i = 0, cnt = 0, bi, ii, k;
    if (cur > limit) {
        s32 t = cur;
        cur = limit;
        limit = t;
    }
    MI_CpuFill8(buf, 0, n * 2);
    k = cur;
    goto test1;
loop1:
    if (cb(arg, k, m) != 0) {
        buf[i] |= 1 << bit;
        cnt++;
    }
    bit++;
    if (bit >= 16) {
        bit = 0;
        i++;
    }
    if (i >= n) goto done1;
    k++;
test1:
    if (k <= limit) goto loop1;
done1:
    if (cnt > 0) {
        r = Random_GlobalBelow(cnt);
        bi = 0; ii = 0;
        goto test2;
loop2:
        if (((buf[ii] >> bi) & 1) != 0) {
            if (r == 0) {
                *out = cur;
                return 1;
            }
            r--;
        }
        bi++;
        if (bi >= 16) {
            bi = 0;
            ii++;
        }
        if (ii >= n) goto fail;
        cur++;
test2:
        if (cur <= limit) goto loop2;
    }
fail:
    return 0;
}

BOOL PeteFallState::pickFallPos(VecFx32 *px, s32 flip) {
    s32 dir;
    BlockMap *map = gSceneBlockMap;
    if (map == 0) {
        unmarkFallPos();
        return FALSE;
    }
    s32 f1, f2, w, h;
    Vec2 *sel = 0;
    s32 sx = 0, sy = 0;
    w = map->unitsX;
    h = map->unitsZ;
    Vec2 p1, p2;
    u16 buf1[4], buf2[4];
    VecFx32 v;
    s32 a, b, c, d;
    s32 y;
    p1.x = 0;
    p1.y = 0;
    p2.x = 0;
    p2.y = 0;
    if (flip != 0) dir = -1; else dir = 1;
    FieldPos_ToUnit(&sx, &sy, px);
    a = sx + dir * 8 - flip;
    y = sy + 5;
    b = a;
    c = sy + 4;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    goto test;
loop:
    if (y < h) {
        p1.y = y;
        f1 = Field_PickRandomInLine(&p1.x, Field_IsClearSpotYX, y, a, sx, map, buf1, 4);
        if (a > 0 && a < w - 1) a += dir;
        y++;
    }
    if (b >= 0 && b < w) {
        p2.x = b;
        f2 = Field_PickRandomInLine(&p2.y, Field_IsClearSpotXY, b, sy, c, map, buf2, 4);
        b += dir;
        if (c < h - 1) c++;
    }
    if (f1 != 0) {
        if (f2 != 0) {
            if (Random_GlobalBelow(10) & 1) {
                sel = &p2;
                goto done;
            }
        }
        sel = &p1;
        goto done;
    } else if (f2 != 0) {
        sel = &p2;
        goto done;
    }
test:
    if (y < h) goto loop;
    if (b < 0) goto done;
    if (b < w) goto loop;
done:
    if (sel != 0) {
        FieldPos_FromUnitCenter(&v, sel->x, sel->y);
        setPos(&v);
        facing = Random_GlobalBelow(4);
        markFallPos();
        return TRUE;
    }
    unmarkFallPos();
    return FALSE;
}

void VisitorSpawnFlags::construct() {}

void VisitorSpawnFlags::destruct() {}

void VisitorSpawnFlags::clear() { MI_CpuFill8(this, 0, 1); }

void VisitorSpawnFlags::rollGulliverSpot() {
    gulliverSpot = Random_GlobalBelow(3);
    gulliverFacing = Random_GlobalBelow(4);
    gulliverSpotRolled = 1;
}

BOOL VisitorSpawnFlags::isVisitorSpawned() {
    if (visitorSpawned) return TRUE;
    return FALSE;
}

void VisitorSpawnFlags::clearVisitorSpawned() { visitorSpawned = 0; }

void VisitorSpawnFlags::setVisitorSpawned() { visitorSpawned = 1; }

void VisitorSpawnFlags::getGulliverSpawn(VecFx32 *v, u16 *out, VecFx32 *p) {
    if (gulliverSpotRolled == 0) ((VisitorSpawnFlags *)(this))->rollGulliverSpot();
    VecFx32 t;
    const VecXZ *tb = sGulliverSpotOffsets;
    const VecXZ *e = &tb[gulliverSpot];
    s32 z = p->z + e->z;
    s32 x = p->x + tb[gulliverSpot].x;
    t.x = x;
    t.y = 0;
    t.z = z;
    FieldPos_SnapToUnitCenter(v, &t);
    if (((GulliverQuest *)gSaveData.gulliverQuest)->getPartCount() >= 5) {
        *out = sGulliverRepairedAngles[gulliverSpot];
    } else if (((GulliverQuest *)gSaveData.gulliverQuest)->isStarted()) {
        *out = 0;
    } else {
        *out = gulliverFacing << 14;
    }
}

extern "C" void VisitorPos_Construct() {}

extern "C" void VisitorPos_Destruct() {}

extern "C" void VisitorPos_Clear(void *p) {
    MI_CpuFill8(p, 0, 8);
}

s32 VisitorPos::countFreeInAcre(s32 *pos, BlockMap *ctx) {
    s32 bx = 0, by = 0;
    s32 n = 0;
    s32 x, y;
    FieldUnit_FromBlockUnit(&bx, &by, pos[0], pos[1], 0, 0);
    s32 xe = bx + 16;
    s32 ye = by + 16;
    for (y = by; y < ye; y++) {
        for (x = bx; x < xe; x++) {
            if (Field_IsClearSpot(x, y, ctx)) n++;
        }
    }
    return n;
}

BOOL VisitorPos::pickFreeInAcre(VecFx32 *out, s32 *pos, BlockMap *ctx) {
    s32 n = 0;
    s32 bx = 0, by = 0;
    u16 arr[16];
    s32 x, y;
    MI_CpuFill8(arr, 0, 0x20);
    FieldUnit_FromBlockUnit(&bx, &by, pos[0], pos[1], 0, 0);
    for (y = 0; y < 16; y++) {
        u16 *pp;
        for (x = 0, pp = &arr[y]; x < 16; x++) {
            if (Field_IsClearSpot(bx + x, by + y, ctx)) {
                *pp |= 1 << x;
                n++;
            }
        }
    }
    if (n > 0) {
        s32 r = Random_GlobalBelow(n);
        for (x = 0; x < 16; x++) {
            u16 *qq;
            for (y = 0, qq = &arr[x]; y < 16; y++) {
                if ((*qq >> y) & 1) {
                    if (r == 0) {
                        FieldPos_FromUnitCenter(out, bx + y, by + x);
                        return TRUE;
                    }
                    r--;
                }
            }
        }
    }
    return FALSE;
}

BOOL VisitorPos::pickRandomPos() {
    u8 buf[4];
    s32 xy[2];
    VecFx32 out;
    s32 n;
    TownBlockMap *o = TownBlockMap_Get();
    if (o != NULL) {
        n = 0;
        xy[0] = 0;
        xy[1] = 0;
        s32 *s = &o->width;
        s32 w = s[0];
        s32 h = s[1];
        MI_CpuFill8(buf, 0, 4);
        for (xy[1] = 1; xy[1] < h - 1; xy[1]++) {
            for (xy[0] = 1; xy[0] < w - 1; xy[0]++) {
                if (countFreeInAcre(xy, o)) {
                    buf[xy[1] - 1] |= 1 << (xy[0] - 1);
                    n++;
                }
            }
        }
        if (n > 0) {
            s32 r = Random_GlobalBelow(n);
            for (xy[1] = 1; xy[1] < h - 1; xy[1]++) {
                for (xy[0] = 1; xy[0] < w - 1; xy[0]++) {
                    if ((buf[xy[1] - 1] >> (xy[0] - 1)) & 1) {
                        if (r == 0) {
                            pickFreeInAcre(&out, xy, o);
                            setPos(out.x, out.z);
                            return TRUE;
                        }
                        r--;
                    }
                }
            }
        }
    }
    return FALSE;
}

void VisitorPos::setPos(s32 a, s32 b) {
    x = a;
    z = b;
}

void VisitorPos::getPos(VecFx32 *out) const {
    out->x = x;
    out->z = z;
    out->y = 0;
}

extern "C" void TurnipMarket_Construct() {}

extern "C" void TurnipMarket_Destruct() {}

void TurnipMarket::clear() {
    pattern = 0xff;
    peakPrice = 0;
    weekStartDay = 1;
    weekStartMonth = 1;
    weekStartYear = 0;
    unk_03 = 0;
    purchaseDay = 1;
    purchaseMonth = 1;
    purchaseYear = 0;
    unk_07 = 0;
}

void TurnipMarket::init() {
    Unk_02086340_T t;
    generateWeek(0);
    t.w0 = 0;
    t.w1 = 0;
    Clock_GetDateTime(&t);
    setWeekDate(&t);
    setPurchaseDate(&t);
}

u8 TurnipMarket::calcPrice(s32 k, s32 z) {
    s32 t = Random_GlobalBelow2(z);
    return (u8)((prices[0] * (k + t)) >> 12);
}

void TurnipMarket::fillDecreasing(s32 i, s32 n) {
    s32 k = 0xca4;
    for (; i < n; k -= 0x66, i++) {
        prices[i] = calcPrice(k, 0x29);
    }
}

u8 TurnipMarket::calcLowPrice() {
    return calcPrice(0x666, 0x68f);
}

u8 TurnipMarket::calcMidPrice() {
    return calcPrice(0xccd, 0x9c3);
}

u8 TurnipMarket::calcHighPrice() {
    return calcPrice(0x1666, 0x9c3);
}

void TurnipMarket::generateSmallSpike() {
    s32 n = Random_GlobalBelow(6) + 7;
    fillDecreasing(2, n - 3);
    prices[n - 3] = calcMidPrice();
    prices[n - 2] = calcMidPrice();
    prices[n] = calcPrice(0x1b33, 0x4f6);
    prices[n - 1] = calcPrice(0x168f, 0x4a4);
    prices[n + 1] = calcPrice(0x168f, 0x4a4);
    fillDecreasing(n + 2, 0xe);
}

s32 TurnipMarket::rollPeakPrice() {
    s32 t = Random_GlobalBelow2(0x419a);
    peakPrice = (prices[0] * (t + 0x2000)) >> 12;
    return 0;
}

void TurnipMarket::generateWeek(s32 flag) {
    if (pattern != 0xff) {
        s32 r = Random_GlobalBelow(0x65);
        switch (pattern) {
        case 0:
            if (r < 0x1e) pattern = 1;
            else if (r < 0x41) pattern = 3;
            else if (r < 0x50) pattern = 2;
            break;
        case 1:
            if (r < 0x14) pattern = 3;
            else if (r < 0x41) pattern = 0;
            else if (r < 0x55) pattern = 2;
            break;
        case 2:
            if (r < 0x2d) pattern = 1;
            else if (r < 0x46) pattern = 3;
            else if (r < 0x5f) pattern = 0;
            break;
        case 3:
            if (r < 0x19) pattern = 1;
            else if (r < 0x46) pattern = 0;
            else if (r < 0x55) pattern = 2;
            break;
        }
        if (flag != 0) pattern = 2;
    } else {
        pattern = Random_GlobalBelow(4);
    }
    peakPrice = 0;
    MI_CpuFill8(&prices[0], 0, 0xe);
    prices[0] = Random_GlobalBelow(0x15) + 0x5a;
    prices[1] = prices[0];
    switch (pattern) {
    case 0:
        prices[2] = calcMidPrice();
        prices[3] = calcLowPrice();
        prices[4] = calcLowPrice();
        prices[5] = calcLowPrice();
        prices[6] = calcMidPrice();
        prices[7] = calcMidPrice();
        prices[8] = calcMidPrice();
        prices[9] = calcLowPrice();
        prices[10] = calcLowPrice();
        prices[11] = calcMidPrice();
        prices[12] = calcMidPrice();
        prices[13] = calcMidPrice();
        break;
    case 1: {
        s32 n = Random_GlobalBelow(4) + 8;
        prices[n] = rollPeakPrice();
        fillDecreasing(2, n - 2);
        prices[n - 1] = calcHighPrice();
        prices[n + 1] = calcHighPrice();
        prices[n - 2] = calcMidPrice();
        prices[n + 2] = calcMidPrice();
        fillDecreasing(n + 3, 0xe);
        break;
    }
    case 2:
        fillDecreasing(2, 0xe);
        break;
    case 3:
        generateSmallSpike();
        break;
    }
}

u16 TurnipMarket::getPrice() {
    Unk_02086340_T t;
    s32 i = 0;
    t.w0 = 0;
    t.w1 = 0;
    Clock_GetDateTime(&t);
    if (((u8 *)&t)[2] >= 12) i++;
    s32 k = Clock_GetWeekday();
    u8 b = prices[k + k + i];
    u16 r = b;
    if (r == 0) {
        u16 v = peakPrice;
        if (v != 0) r = v;
    }
    return r;
}

void TurnipMarket::spoilOnReset() {
    Unk_02086340_T t;
    if (MenuCtrl_IsClockMovedForward() != 0 || MenuCtrl_IsClockMovedBack() != 0) {
        t.w0 = 0;
        t.w1 = 0;
        Clock_GetDateTime(&t);
        generateWeek(1);
        setWeekDate(&t);
        setPurchaseDate(&t);
    }
}

void TurnipMarket::updateDay(s32 d) {
    struct {
        Unk_02086340_T a, b;
    } l;
    DateTime_Make(&l.a, this, 6, 0, 0);
    l.b.w0 = 0;
    l.b.w1 = 0;
    Clock_GetDateTime(&l.b);
    if (LB(0xa) < 6) {
        DateTime_SubDays(&l.b, 1);
        LB(0xa) = 6;
        LB(9) = 0;
        LB(8) = 0;
    }
    s32 r = DateTime_Compare(&l.b, &l.a, 0x38);
    checkTurnipExpiry();
    if (r == 1) {
        s32 t = Date_GetWeekday(LB(5), LB(4), LB(3));
        s32 u = Date_GetWeekday(LB(0xd), LB(0xc), LB(0xb));
        if (u < t || DateTime_DiffDays(&l.a, &l.b) >= 7) {
            generateWeek(0);
            setWeekDate(&l.b);
        }
    } else if (d < 0) {
        generateWeek(1);
        setWeekDate(&l.b);
        setPurchaseDate(&l.b);
    }
}

void TurnipMarket::setWeekDate(void *src) {
    Unk_02086340_T t;
    t.w0 = 0;
    t.w1 = 0;
    if (src == NULL) {
        Clock_GetDateTime(&t);
    } else {
        MI_CpuCopy8(src, &t, 8);
    }
    if (((u8 *)&t)[2] < 6) DateTime_SubDays(&t, 1);
    weekStartYear = ((u8 *)&t)[5];
    weekStartMonth = ((u8 *)&t)[4];
    weekStartDay = ((u8 *)&t)[3];
}

void TurnipMarket::checkTurnipExpiry() {
    struct {
        Unk_02086340_T a, b;
    } l;
    DateTime_Make(&l.a, &purchaseDay, 6, 0, 0);
    l.b.w0 = 0;
    l.b.w1 = 0;
    Clock_GetDateTime(&l.b);
    if (LB(0xa) < 6) {
        DateTime_SubDays(&l.b, 1);
        LB(0xa) = 6;
        LB(9) = 0;
        LB(8) = 0;
    }
    if (DateTime_Compare(&l.b, &l.a, 0x38) == 1) {
        if (DateTime_DiffDays(&l.a, &l.b) >= 7) {
            gSaveData.clearFlag(4);
            setPurchaseDate(&l.b);
        }
    }
}

void TurnipMarket::setPurchaseDate(void *src) {
    Unk_02086340_T t;
    t.w0 = 0;
    t.w1 = 0;
    if (src == NULL) {
        Clock_GetDateTime(&t);
    } else {
        MI_CpuCopy8(src, &t, 8);
    }
    if (((u8 *)&t)[2] < 6) DateTime_SubDays(&t, 1);
    purchaseYear = ((u8 *)&t)[5];
    purchaseMonth = ((u8 *)&t)[4];
    purchaseDay = ((u8 *)&t)[3];
}

ReddLastSale::ReddLastSale() {
    new (this) PlayerId();
    item = 0xfff1;
}

ReddLastSale::~ReddLastSale() {
    new (this) PlayerId();
}

void ReddLastSale::clear() {
    ((PlayerId *)this)->clear();
    item = 0xfff1;
}

extern "C" void ReddLastSale_Clear(ReddLastSale *p) {
    p->clear();
}

extern "C" void *ReddLastSale_GetBuyer(void *p) { return p; }

void ReddLastSale::setBuyer(const ReddLastSale *o) {
    townId = o->townId;
    townName = o->townName;
    playerId = o->playerId;
    playerName = o->playerName;
    gender = o->gender;
    unk_15 = o->unk_15;
}

void ReddLastSale::setItem(const ReddLastSale *o) {
    item = o->townId;
}

void ReddLastSale::copyItemFrom(const ReddLastSale *o) {
    townId = o->item;
}

extern "C" void GulliverQuest_Construct() {}

extern "C" void GulliverQuest_Destruct() {}

extern "C" void GulliverQuest_Clear(void *p) {
    MI_CpuFill8(p, 0, 1);
}

extern "C" void GulliverQuest_Init(void *p) {
    GulliverQuest_Clear(p);
}

s32 GulliverQuest::getPartCount() {
    return cnt;
}

void GulliverQuest::addPart() {
    cnt = cnt + 1;
}

BOOL GulliverQuest::isStarted() {
    if (flag == 1) return TRUE;
    return FALSE;
}

void GulliverQuest::start() {
    flag = 1;
}

extern "C" void RoostGuestRoll_Construct() {}

extern "C" void RoostGuestRoll_Destruct() {}

void RoostGuestRoll::clear() {
    morningGuest = 0;
    noonGuest = 0;
    afternoonGuest = 0;
    lateGuest = 0;
}

extern "C" void RoostGuestRoll_Init(void *p) {
    ((RoostGuestRoll *)(p))->roll();
}

void RoostGuestRoll::roll() {
    u32 a, b, c;
    morningGuest = Random_GlobalBelow(2);
    lateGuest = 1;
    a = Random_GlobalBelow(100);
    b = Random_GlobalBelow(100);
    c = Random_GlobalBelow(100);
    switch (Clock_GetWeekday()) {
    case 6:
        if (Math_IsInRange(a, 0, 0x4a)) noonGuest = 0;
        else if (Math_IsInRange(a, 0x4b, 0x54)) noonGuest = 1;
        else noonGuest = 2;
        if (Math_IsInRange(b, 0, 0x4a)) afternoonGuest = 0;
        else if (Math_IsInRange(b, 0x4b, 0x54)) afternoonGuest = 1;
        else afternoonGuest = 2;
        break;
    case 0:
        if (Math_IsInRange(a, 0, 0x31)) noonGuest = 0;
        else if (Math_IsInRange(a, 0x32, 0x3b)) noonGuest = 1;
        else if (Math_IsInRange(a, 0x3c, 0x46)) noonGuest = 2;
        else noonGuest = 4;
        if (Math_IsInRange(b, 0, 0x4a)) afternoonGuest = 0;
        else if (Math_IsInRange(b, 0x4b, 0x54)) afternoonGuest = 1;
        else if (Math_IsInRange(b, 0x55, 0x5e)) afternoonGuest = 2;
        else afternoonGuest = 3;
        break;
    default:
        if (Math_IsInRange(a, 0, 0x4a)) noonGuest = 0;
        else if (Math_IsInRange(a, 0x4b, 0x55)) noonGuest = 1;
        else noonGuest = 2;
        if (Math_IsInRange(b, 0, 0x4a)) afternoonGuest = 0;
        else if (Math_IsInRange(b, 0x4b, 0x55)) afternoonGuest = 1;
        else afternoonGuest = 2;
        if (Math_IsInRange(c, 0, 0x1d) && NookShop_GetLevel(gSaveData.nookShop) == 3) lateGuest = 1;
        else lateGuest = 0;
        break;
    }
    if (noonGuest == afternoonGuest) afternoonGuest = 0;
}

BOOL RoostGuestRoll::hasMorningGuest() { if (morningGuest) return TRUE; return FALSE; }

u32 RoostGuestRoll::getNoonGuest() { return noonGuest; }

u32 RoostGuestRoll::getAfternoonGuest() { return afternoonGuest; }

BOOL RoostGuestRoll::hasLateGuest() { if (lateGuest) return TRUE; return FALSE; }

void ContestRecord::postResultNotice() {
    if (((PlayerId *)(this))->isValid() == 0 && ((VillagerId *)(&holderVillager))->isValid() == 0) {
        gSaveData.clearFlag(0xf);
        return;
    }
    if (kind != 1 && kind != 2 && kind != 3) return;
    if (gSaveData.testFlag(0xf) == 0) return;
    MsgString9B rec;
    if (((PlayerId *)(this))->isValid() != 0) ((PlayerId *)(this))->getNameString((MsgString *)(&rec));
    else ((VillagerId *)(&holderVillager))->getName(&rec);
    if ((u8)(kind + 0xff) <= 1) {
        MailText_SetSlotMonth(0, dateMonth);
        MailText_SetSlotDayOrdinal(1, dateDay);
        MailText_SetSlot(4, &rec);
        if (size > 0) {
            MsgString25 num;
            if (kind == 1) String_FormatFixedPoint(&num, size, 1);
            else String_FormatNumber(&num, size >> 12, 3, 0, 0, 0);
            MailText_SetSlot(3, &num);
        }
        BOOL same;
        if (Item_IsFurniture(&item) != 0) {
            u16 v = 0xfff1;
            u32 a = Item_GetFurnitureIndex(&item);
            if (a == Item_GetFurnitureIndex(&v)) same = TRUE; else same = FALSE;
        } else {
            if (item == 0xfff1) same = TRUE; else same = FALSE;
        }
        if (same == 0) {
            ItemName str(&item);
            MailText_SetSlot(2, &str);
        }
    } else {
        MailText_SetSlot(0, &rec);
    }
    s32 k;
    if ((u8)(kind + 0xff) <= 1) k = Random_GlobalBelow(3);
    else k = Random_GlobalBelow(2);
    Bbs_PostMsgToday(k, sContestResultBbsFiles[kind]);
    gSaveData.clearFlag(0xf);
}

void ContestRecord::sendResultLetters() {
    if (((PlayerId *)(this))->isValid() == 0 && ((VillagerId *)(&holderVillager))->isValid() == 0) return;
    if (kind != 1 && kind != 2 && kind != 3) return;
    ContestLetterLocals l;
    Clock_GetDate(l.today);
    if (dateYear == 0) return;
    if (dateMonth == 0) return;
    if (dateDay == 0) return;
    DateTime_Make(l.contestTime, &dateDay, 6, 0, 0);
    l.now = 0;
    l.nowHi = 0;
    Clock_GetDateTime(&l.now);
    if (((u8 *)&l.now)[2] < 6) {
        DateTime_SubDays(&l.now, 1);
        ((u8 *)&l.now)[2] = 6;
        ((u8 *)&l.now)[1] = 0;
        ((u8 *)&l.now)[0] = 0;
    }
    s32 r6 = DateTime_Compare(&l.now, l.contestTime, 0x38);
    if (r6 == 1 && DateTime_DiffDays(l.contestTime, &l.now) >= 10) goto reset;
    if (r6 == -1 && DateTime_DiffDays(&l.now, l.contestTime) >= 10) {
    reset:
        clear();
        gSaveData.clearFlag(0xf);
        return;
    }
    if (kind != 3) {
        if (dateYear == l.today[2] && dateMonth == l.today[1] && dateDay == l.today[0]) return;
    } else {
        s32 r4 = Event_GetDaysSinceStart(0xe);
        Clock_GetDateTime(&l.now);
        if (r4 != -1) {
            if (r4 < 7) return;
            if (r4 == 7 && ((u8 *)&l.now)[2] < 6) return;
        }
        if (r6 == 1 && DateTime_DiffDays(l.contestTime, &l.now) < 1) return;
    }
    if (kind == 3 && ((PlayerId *)(this))->isValid() == 0) {
        postResultNotice();
        clear();
        return;
    }
    MsgString25 n1;
    MsgString25 n2;
    MsgString25 n3;
    Letter buf;
    MsgString9B rec;
    s32 i = 0;
    s32 ok, z10, z14, z1c, z20, z24, z2c;
    l.letterVariant = 0;
    z1c = 0; z14 = 0; z20 = 0; z24 = 0; z2c = 0; z10 = 0;
    for (; i < 4; i++) {
        ok = z10;
        void *r4 = PlayerData_GetResident(gSavePlayers, i);
        if (r4 == 0) continue;
        if (((PlayerData *)(r4))->isUsed() == 0) continue;
        void *r7 = ((PlayerData *)(r4))->getSpNpcRecord();
        if ((u8)(kind + 0xff) <= 1) {
            MailText_SetSlotMonth(z14, dateMonth);
            MailText_SetSlotDayOrdinal(1, dateDay);
            s32 f;
            if (Item_IsFurniture(&item) != 0) {
                l.emptyItem = 0xfff1;
                u32 t = Item_GetFurnitureIndex(&item);
                f = (t == Item_GetFurnitureIndex(&l.emptyItem)) ? 1 : z1c;
            } else {
                f = (item == 0xfff1) ? 1 : z20;
            }
            if (f == 0) {
                ItemName str(&item);
                MailText_SetSlot(2, &str);
            }
            if (size > 0) {
                if (kind == 1) String_FormatFixedPoint(&n1, size, 1);
                else String_FormatNumber(&n1, size >> 12, 3, z24, z24, z24);
                MailText_SetSlot(3, &n1);
            }
            if (kind == 1) ok = ((PlayerSpNpcRecord *)(r7))->hasEnteredFishingTourney();
            else ok = ((PlayerSpNpcRecord *)(r7))->hasEnteredBugOff();
        } else {
            PlayerId *p = ((PlayerData *)r4)->getPlayerId();
            if ((holderPlayer.townId == p->townId && memcmp(holderPlayer.townName, p->townName, 8) == 0 && ((PlayerId *)(this))->equals(p) != 0) || ((PlayerSpNpcRecord *)(r7))->hasFestivalGift() != 0) {
                l.letterVariant = Random_GlobalBelow(3);
                ((PlayerId *)(((PlayerData *)(r4))->getPlayerId()))->getNameString((MsgString *)(&rec));
                ((PlayerSpNpcRecord *)(r7))->clearFestivalGift();
                MailText_SetSlot(z2c, &rec);
                ok = 1;
            }
        }
        if (ok == 0) continue;
        if ((u8)(kind + 0xff) <= 1) {
            PlayerId *q = ((PlayerData *)r4)->getPlayerId();
            if (holderPlayer.townId == q->townId && memcmp(holderPlayer.townName, q->townName, 8) == 0 && ((PlayerId *)(this))->equals(q) != 0) {
                l.letterVariant = Random_GlobalBelow(3);
            } else {
                l.letterVariant = Random_GlobalBelow(3) + 3;
            }
            ((PlayerId *)(((PlayerData *)(r4))->getPlayerId()))->getNameString((MsgString *)(&rec));
            MailText_SetSlot(4, &rec);
        }
        PlayerId *w = ((PlayerData *)r4)->getPlayerId();
        Letter_ComposeFromMail((LetterView *)&buf, &l.letterVariant, sContestResultMailFiles[kind], data_020e0c50, data_020e0c48, w);
        PlayerId *x = ((PlayerData *)r4)->getPlayerId();
        if ((holderPlayer.townId == x->townId && memcmp(holderPlayer.townName, x->townName, 8) == 0 && ((PlayerId *)(this))->equals(x) != 0) || kind == 3) {
            l.trophy = 0x3878;
            if (kind == 2) l.trophy = 0x387c;
            else if (kind == 3) l.trophy = 0x3880;
            ((LetterView *)(&buf))->setPresent(l.trophy, 1);
        }
        LetterDelivery_PutInAddresseeMailbox(&buf);
    }
    postResultNotice();
    clear();
}

ContestRecord *ContestRecord::construct() {
    new (this) PlayerId();
    VillagerId_Construct(&holderVillager);
    VillagerId_Construct(&votedVillager);
    item = 0xfff1;
    return this;
}

ContestRecord *ContestRecord::destruct() {
    VillagerId_Destruct(&votedVillager);
    VillagerId_Destruct(&holderVillager);
    new (this) PlayerId();
    return this;
}

void ContestRecord::clear() {
    ((PlayerId *)(this))->clear();
    VillagerId_Clear(&holderVillager);
    VillagerId_Clear(&votedVillager);
    item = 0xfff1;
    size = 0;
}

extern const s16 sGulliverRepairedAngles[4];
extern const u8 data_020cf288[0xa0];
extern const u8 data_020cf328[0x230];
extern u8 data_020e0c4c[4];
extern const VecXZ sGulliverSpotOffsets[3];
extern u8 data_020e0c50[4];
extern u8 data_020e0c48[4];
extern u8 data_020e0c54[4];
extern u8 data_020e0c44[4];

char data_020e0c88[] = "ev_gardening";

const s16 sGulliverRepairedAngles[4] = {(s16)0x8000, 0x4000, (s16)0xc000, 0};

const u8 data_020cf288[0xa0] = {
    0x06, 0x02, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
    0x08, 0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x0b, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x03, 0x02, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x05, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x0a, 0x01, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
    0x0c, 0x03, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x0a, 0x03, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x09, 0x03, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0b, 0x01, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
};

const u8 data_020cf328[0x230] = {
    0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

char data_020e0c7c[] = "bbs_fishing";

u8 data_020e0c4c[4] = {0x7, 0, 0, 0};

u32 sKatieSpotRows[0x20];

const VecXZ sGulliverSpotOffsets[3] = {{0, 0x4000}, {-0x4000, 0}, {0x4000, 0}};

u8 data_020e0c50[4] = {0xf, 0, 0, 0};

char data_020e0c58[] = "ev_insect";

char data_020e0c98[] = "bbs_gardening";

char *sContestResultBbsFiles[4] = {data_020e0c7c, data_020e0c7c, data_020e0c64, data_020e0c98};

char *sContestResultMailFiles[4] = {data_020e0c70, data_020e0c70, data_020e0c58, data_020e0c88};

char data_020e0c70[] = "ev_fishing";

u8 data_020e0c48[4] = {0x10, 0, 0, 0};

char data_020e0c64[] = "bbs_insect";

u8 data_020e0c54[4] = {0x1e, 0, 0, 0};

u8 data_020e0c44[4] = {0xd, 0, 0, 0};
