#include "uptr.h"
#include "host_labels.h"
#include "types.h"
#include "npc/VillagerId.h"
#include "save/Unk_02085810_Rec.h"
#include "save/ContestRecord.h"
#include "game/GroundInfo.h"
#include "npc/VillagerDataItemView.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "player/PlayerSpNpcRecord.h"
#include "save/SaveData.h"
#include "save/VillagerData.h"
#include "town/BlockMap.h"
#include "town/TownSessionState.h"
#include "sys/ClockDateTime.h"
#include "proto/main/unk_020030d8.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02085940.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0204cc1c.h"





#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
extern u8 gFieldSceneKind;
extern BlockMap *gSceneBlockMap;
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
extern SaveData gSaveData;

struct Unk_02085490_Pt {
    s32 x, y;
    Unk_02085490_Pt(s32 px, s32 py) { x = px; y = py; }
};


Unk_02085490_Pt sVillagerGardenOffsets[14] = {
    Unk_02085490_Pt(-3, -2), Unk_02085490_Pt(2, -2), Unk_02085490_Pt(-3, -1), Unk_02085490_Pt(2, -1),
    Unk_02085490_Pt(-3, 0), Unk_02085490_Pt(2, 0), Unk_02085490_Pt(-3, 1), Unk_02085490_Pt(2, 1),
    Unk_02085490_Pt(-3, 2), Unk_02085490_Pt(-2, 2), Unk_02085490_Pt(-1, 2), Unk_02085490_Pt(0, 2),
    Unk_02085490_Pt(1, 2), Unk_02085490_Pt(2, 2)
};
Unk_02085490_Pt sGardenNeighbourOffsets[8] = {
    Unk_02085490_Pt(0, 1), Unk_02085490_Pt(0, -1), Unk_02085490_Pt(-1, 0), Unk_02085490_Pt(1, 0),
    Unk_02085490_Pt(-1, -1), Unk_02085490_Pt(1, -1), Unk_02085490_Pt(-1, 1), Unk_02085490_Pt(1, 1)
};
TownSessionState gTownSessionState;

extern "C" {
void MI_CpuFill8(void *p, u32 v, u32 n);
void MI_CpuCopy8(const void *src, void *dst, u32 n);
u8 *SaveVillagers_Get(u8 *base, s32 idx);
void Clock_GetDateTime(ClockDateTime *p);
void Clock_GetDate(u8 *out);
s32 Date_DaysBetween(u8 *a, u8 *b);
s32 Random_PickSetBit(u32, s32, s32);
s32 func_01ffcb0c(s32 v1, s32 v2);
s32 FX_Div(s32 numer, s32 denom);
s32 Item_GetFishBaseSize(u16 *);
s32 Item_GetInsectBaseSize(u16 *);
s32 Event_GetDaysSinceStart(s32);
s32 Event_GetState(s32, void *, s32);
}

struct ClockDateBytes {
    u8 b[4];
};

void ContestRecord::resetToday() {
    u8 d[8];
    clear();
    Clock_GetDate(d);
    dateYear = d[2];
    dateMonth = d[1];
    dateDay = d[0];
    kind = 0;
}

void ContestRecord::setKind(u32 v) { kind = v; }

void ContestRecord::setHolderPlayer(Unk_02085810_Base *src) { holderPlayer = *src; VillagerId_Clear(&holderVillager); }

void *ContestRecord::getHolderPlayer() { return this; }

void ContestRecord::setHolderVillager(VillagerId *src) { holderVillager = *src; ((PlayerId *)(this))->clear(); }

VillagerId *ContestRecord::getHolderVillager() { return &holderVillager; }

void ContestRecord::clearVotedVillager() { VillagerId_Clear(&votedVillager); }

void ContestRecord::setVotedVillager(VillagerId *src) { votedVillager = *src; }

VillagerId *ContestRecord::getVotedVillager() { return &votedVillager; }

extern "C" void ContestRecord_SetItem(ContestRecord *o, u16 *in) { o->item = *in; }

extern "C" void ContestRecord_GetItem(u16 *out, ContestRecord *o) { *out = o->item; }

void ContestRecord::setSize(s32 v) { size = v; }

u32 ContestRecord::getSize() { return size; }

extern "C" void ContestRecord_BeginContestDay(ContestRecord *self, u32 mode)
{
    ClockDateBytes t;
    s32 i;
    s32 z1 = 0;
    s32 z0 = 0;
    Clock_GetDate(t.b);
    if (self->dateYear == t.b[2] && self->dateMonth == t.b[1] && self->dateDay == t.b[0]) {
        return;
    }
    self->resetToday();
    for (i = 0; i < 4; i++) {
        void *o = PlayerData_GetResident(gSavePlayers, i);
        if (o != NULL && ((PlayerData *)(o))->isUsed() != 0) {
            switch (mode) {
            case 1:
                ((PlayerSpNpcRecord *)(((PlayerData *)(o))->getSpNpcRecord()))->setEnteredFishingTourney(z0);
                break;
            case 2:
                ((PlayerSpNpcRecord *)(((PlayerData *)(o))->getSpNpcRecord()))->setEnteredBugOff(z1);
                break;
            }
        }
    }
}

extern "C" void ContestRecord_BeginFestival(ContestRecord *self, u32 mode)
{
    ClockDateBytes t;
    s32 v;
    s32 i;
    Clock_GetDate(t.b);
    v = 0;
    switch (mode) {
    case 0:
        v = Event_GetDaysSinceStart(0xe);
        break;
    case 1:
        v = Event_GetDaysSinceStart(0x11);
        break;
    case 2:
        v = Event_GetDaysSinceStart(0x10);
        break;
    }
    s32 r = Date_DaysBetween(t.b, &self->dateDay);
    if (t.b[2] == self->dateYear && v != -1 && r <= 7 && r >= 0 && t.b[0] - v <= self->dateDay) {
        return;
    }
    switch (mode) {
    case 1:
        gSaveData.clearFlag(0x11);
        break;
    case 0:
    case 2:
        for (i = 0; i < 4; i++) {
            void *o = PlayerData_GetResident(gSavePlayers, i);
            if (o != NULL && ((PlayerData *)(o))->isUsed() != 0) {
                if (mode == 2) {
                    ((PlayerSpNpcRecord *)(((PlayerData *)(o))->getSpNpcRecord()))->resetAcornCount();
                    ((PlayerData *)(o))->clearFlag(0xf);
                } else {
                    ((PlayerSpNpcRecord *)(((PlayerData *)(o))->getSpNpcRecord()))->clearFestivalGift();
                }
            }
        }
        break;
    }
    self->resetToday();
}

extern "C" s32 Contest_GetCatchSize(u16 *p)
{
    s32 r = 0;
    s32 base = Random_GlobalBelow2(0x666) + 0xccd;
    BOOL in = r;
    u32 v = *p;
    if (v >= 0x12e8 && v <= 0x131f) {
        in = TRUE;
    }
    if (in) {
        r = FX_Div(func_01ffcb0c(Item_GetFishBaseSize(p) << 12, base), 0x28a4);
        if (r < 0x119a) {
            r = 0x119a;
        }
    } else if (v >= 0x12b0 && v <= 0x12e7) {
        r = func_01ffcb0c(Item_GetInsectBaseSize(p) << 12, base);
    }
    return r;
}

extern "C" s32 Contest_GetFlowerKind(u32 *out, u16 *p)
{
    BOOL f4 = TRUE, f3 = TRUE, f2 = TRUE, f1 = FALSE;
    u32 v = *p;
    if (v <= 5) f1 = TRUE;
    if (!f1) {
        if (v < 6 || v > 11) f2 = FALSE;
    }
    if (!f2) {
        if (v < 12 || v > 17) f3 = FALSE;
    }
    if (!f3) {
        if ((v < 18 || v > 25) && v != 28) f4 = FALSE;
    }
    if (f4 || v == 26 || (u16)(v + 0xffe3) <= 1) {
        if (v > 27) {
            *out = v - 1;
        } else {
            *out = v;
        }
        return TRUE;
    }
    return FALSE;
}

extern "C" s32 CountSetBits(u32 v)
{
    s32 n = 0;
    if (v != 0) {
        s32 i;
        for (i = 0; i < 32; i++) {
            if ((v >> i) & 1) {
                n++;
            }
        }
    }
    return n;
}

extern "C" s32 ContestRecord_ScoreVillagerGarden(VillagerData *obj, BlockMap *grid)
{
    VillagerId *k = obj->getVillagerId();
    s32 r = 0;
    s32 i, sx, sy, z1, z2, v;
    if (k->isValid() != 0) {
        u32 mask = r;
        u8 *q = ((VillagerDataItemView *)obj)->getHousePos();
        sx = q[0];
        sy = q[1];
        Unk_02085490_Pt *d = sVillagerGardenOffsets;
        s32 cnt = mask;
        v = cnt;
        i = cnt;
        z1 = cnt;
        z2 = cnt;
        for (i = 0; i < 14; i++) {
            s32 x = sx + d->x;
            s32 y = sy + d->y;
            s32 hx = x >> 4;
            s32 hy = y >> 4;
            u16 *cell = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), z1);
            v = z2;
            if (cell != NULL && Contest_GetFlowerKind((u32 *)&v, cell)) {
                if ((u32)v < 0x20) {
                    mask |= 1 << v;
                }
                cnt++;
            }
            d++;
        }
        r = CountSetBits(mask);
        r *= cnt;
    }
    return r;
}

extern "C" s32 Contest_IsNextToGroundAttr4(s32 *pos)
{
    Unk_02085490_Pt *p = sGardenNeighbourOffsets;
    s32 i;
    for (i = 0; i < 8; i++) {
        GroundInfo o;
        o.initAtUnit(pos[0] + p->x, pos[1] + p->y, 0, 0);
        if (o.attr == 4) {
            return TRUE;
        }
        p++;
    }
    return FALSE;
}

extern "C" s32 ContestRecord_ScorePlayerGarden(ContestRecord *self, BlockMap *grid)
{
    s32 r = 0;
    s32 a, b, c, d;
    u16 lo, hi;
    s32 x, y, hy, hx, sx, sy;
    s32 cnt, sel;
    u32 mask;
    s32 pos[2];
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    lo = 0x5014;
    hi = 0x501a;
    if (BlockMap_FindItemAllAttr(grid, &a, &b, &c, &d, &lo, &hi, 1, 0)) {
        mask = 0;
        sx = 0;
        sy = 0;
        cnt = 0;
        sel = 0;
        FieldUnit_FromBlockUnit(&sx, &sy, a, b, c, d);
        y = sy - 1;
        goto test1;
    loop1:
        x = sx - 5;
        if (x < sx + 5) {
            goto test0;
        loop0:
            hx = x >> 4;
            hy = y >> 4;
            {
                u16 *cell = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), 0);
                if (cell != NULL) {
                    if (Contest_GetFlowerKind((u32 *)&sel, cell)) {
                        pos[0] = x;
                        pos[1] = y;
                        if (Contest_IsNextToGroundAttr4(pos)) {
                            if ((u32)sel < 0x20) {
                                mask |= 1 << sel;
                            }
                            cnt++;
                        }
                    }
                }
            }
            x++;
        test0:
            if (x < sx + 5) goto loop0;
        }
        y++;
    test1:
        if (y < sy + 9) goto loop1;
        s32 pc = CountSetBits(mask);
        r = (pc * cnt + 2) / 3;
    }
    return r;
}

extern "C" void ContestRecord_JudgeGardens(ContestRecord *self)
{
    u32 mask;
    BlockMap *grid;
    s32 best, cnt, i;
    BOOL b = (gFieldSceneKind == 0);
    if (b) {
        grid = gSceneBlockMap;
        VillagerId_Clear(self->getHolderVillager());
        ((PlayerId *)self->getHolderPlayer())->clear();
        if (grid != NULL) {
            mask = 0;
            best = -1;
            cnt = 0;
            for (i = 0; i < 8; i++) {
                VillagerData *o = (VillagerData *)SaveVillagers_Get(gSaveVillagers, i);
                if (o != NULL && o->getVillagerId()->isValid() != 0) {
                    s32 v = ContestRecord_ScoreVillagerGarden(o, grid);
                    if (v > best) {
                        mask = (u8)(1 << i);
                        cnt = 1;
                        best = v;
                    } else if (v == best) {
                        mask = (u8)(mask | (1 << i));
                        cnt++;
                    }
                }
            }
            s32 w = ContestRecord_ScorePlayerGarden(self, grid);
            if (cnt == 0 || w > best || (w > 0 && w == best && Random_GlobalBelow(2) == 0)) {
                self->setHolderPlayer((Unk_02085810_Base *)PlayerData_GetCurrent()->getPlayerId());
            } else {
                VillagerData *o = (VillagerData *)SaveVillagers_Get(gSaveVillagers, Random_PickSetBit(mask, cnt, 8));
                if (o != NULL && o->getVillagerId()->isValid() != 0) {
                    self->setHolderVillager(o->getVillagerId());
                }
            }
        }
    }
}

TownSessionState::TownSessionState()
{
    VisitorPos_Construct();
    katie.construct();
    closingTime.construct();
    travel.construct();
    peteFall.construct();
    resetti.construct();
    visitorFlags.construct();
}

TownSessionState::~TownSessionState()
{
    visitorFlags.destruct();
    resetti.destruct();
    peteFall.destruct();
    travel.destruct();
    closingTime.destruct();
    katie.destruct();
    VisitorPos_Destruct();
}

extern "C" void TownSessionState_Reset(TownSessionState *self)
{
    self->closingTime.clearClosingTime();
    MI_CpuFill8(&self->flags, 0, 4);
    self->visitorFlags.clear();
    VisitorPos_Clear(self->visitorPos);
}

extern "C" BOOL TownSessionState_TestFlag(TownSessionState *self, u32 bit)
{
    u32 *w = &self->flags;
    BOOL r;
    s32 idx = bit >> 5;
    u32 b = bit & 0x1f;
    if (idx < 1) {
        r = TRUE;
        if (((r << b) & w[idx]) != 0) {
            goto done;
        }
    }
    r = FALSE;
done:
    return r;
}

extern "C" void TownSessionState_SetFlag(TownSessionState *self, u32 bit)
{
    u32 *w = &self->flags;
    s32 idx = bit >> 5;
    u32 b = bit & 0x1f;
    if (idx < 1) {
        w[idx] = *(volatile u32 *)&w[idx] | (1 << b);
    }
}

extern "C" void TownSessionState_ClearFlag(TownSessionState *self, u32 bit)
{
    u32 *w = &self->flags;
    s32 idx = bit >> 5;
    u32 b = bit & 0x1f;
    if (idx < 1) {
        w[idx] = ~(1 << b) & *(volatile u32 *)&w[idx];
    }
}

extern "C" ShopClosingTime *TownSessionState_GetClosingTime(TownSessionState *p) { return &p->closingTime; }

extern "C" TownTravelState *TownSessionState_GetTravelState(TownSessionState *p) { return &p->travel; }

extern "C" ResettiVisitFlag *TownSessionState_GetResettiFlag(TownSessionState *p) { return &p->resetti; }

extern "C" KatieVisitState *TownSessionState_GetKatieState(TownSessionState *p) { return &p->katie; }

extern "C" PeteFallState *TownSessionState_GetPeteFall(TownSessionState *p) { return &p->peteFall; }

extern "C" VisitorSpawnFlags *TownSessionState_GetVisitorFlags(TownSessionState *p) { return &p->visitorFlags; }

extern "C" u8 *TownSessionState_GetVisitorPos(TownSessionState *p) { return p->visitorPos; }

extern "C" void TownSessionState_CheckTortimerReward(TownSessionState *self)
{
    PlayerData *r5 = PlayerData_GetCurrent();
    if (r5 != NULL) {
        if (r5->getPlayerId()->isValid() != 0) {
            if (r5->testFlag(1) == 0) {
                if ((r5->testFlag(0x21) == 0 && Catalog_HasAllFish() != 0) ||
                    (r5->testFlag(0x22) == 0 && Catalog_HasAllInsects() != 0)) {
                    ClockDateTimeWords a;
                    s32 b[2];
                    a.words[0] = 0;
                    a.words[1] = 0;
                    Clock_GetDateTime(&a.dt);
                    MI_CpuCopy8(&a, b, 8);
                    if (Event_GetState(8, b, 0) == 0) {
                        TownSessionState_SetFlag(self, 8);
                    }
                }
            }
        }
    }
}

extern "C" TownSessionState *TownSessionState_Get()
{
    return &gTownSessionState;
}

