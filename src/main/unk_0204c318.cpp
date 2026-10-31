#include "types.h"
#include "sys/ClockDate.h"
#include "game/Unk_0204da0c_Size.h"
#include "game/Unk_0204da0c_Map.h"
#include "town/TownState.h"
#include "proto/main/unk_0204c318.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0204cc1c.h"






extern "C" {
void Clock_GetDate(void *p);
s32 Date_IsAfterOrEqual(void *a, void *b);
s32 Date_GetWeekday(u32 a, u32 b, u32 c);
void TownState_ClearUnk0c(void *p);
void TownState_ClearUnk16(void *p);
void TownState_ClearEvents(void *p);
void TownState_PickNextWeekDate(void *p, void *q);
void Town_ReplaceSouthCedars(void *p);
void Town_InitNew();
}

extern const u16 sNativeFruitTrees[6];
const u16 sNativeFruitTrees[6] = {0x3b, 0x43, 0x4b, 0x33, 0x53, 0};

static inline BOOL Unk_0204c318_InRange(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

extern "C" void TownState_Construct() {}

extern "C" void TownState_Destruct() {}

extern "C" void Town_SetNativeFruitTrees(TownState *p);

extern "C" void TownState_InitNew(TownState *p) {
    Clock_GetDate(p);
    p->nativeFruit = Random_GlobalBelow(5);
    Date_GetWeekday(p->lastUpdate.year, p->lastUpdate.month, p->lastUpdate.day);
    TownState_PickNextWeekDate(p, p);
    TownState_ClearUnk0c(p);
    TownState_ClearUnk16(p);
    Town_SetNativeFruitTrees(p);
    Town_ReplaceSouthCedars(p);
    TownState_ClearEvents(p);
    ClockDate *s;
    s32 i;
    for (s = p->playerDates, i = 0; i < 4; i++) {
        s->day = 1;
        s->month = 1;
        s->year = 0;
        s->pad_03 = 0;
        s++;
    }
    p->perfectStreak = -1;
    p->eventUpdateDay = 1;
    p->eventUpdateMonth = 1;
    p->eventUpdateYear = 0;
    p->unk_57 = 0;
    Town_InitNew();
    p->unk_6b = 0;
    p->unk_6a = 0xff;
    p->unk_69 = 0xff;
    p->unk_68 = 0xff;
    p->unk_22 = 0;
}

extern "C" void TownState_Reset(TownState *p) {
    Clock_GetDate(p);
    p->nativeFruit = 0;
    p->nextWeekDay = 1;
    p->nextWeekMonth = 1;
    p->nextWeekYear = 0;
    p->unk_0b = 0;
    TownState_ClearUnk0c(p);
    TownState_ClearUnk16(p);
    TownState_ClearEvents(p);
    ClockDate *s;
    s32 i;
    for (s = p->playerDates, i = 0; i < 4; i++) {
        s->day = 1;
        s->month = 1;
        s->year = 0;
        s->pad_03 = 0;
        s++;
    }
    p->perfectStreak = -1;
    p->eventUpdateDay = 1;
    p->eventUpdateMonth = 1;
    p->eventUpdateYear = 0;
    p->unk_57 = 0;
}

extern "C" void TownState_ClampDate(ClockDate *p) {
    ClockDate t;
    Clock_GetDate(&t);
    if (Date_IsAfterOrEqual(&t, p) == 0) {
        p->day = t.day;
        p->month = t.month;
        p->year = t.year;
        p->pad_03 = t.pad_03;
    }
}

extern "C" void Town_SetNativeFruitTrees(TownState *p) {
    BlockMap *m = TownBlockMap_Get();
    if (m) {
        s32 w = m->width << 4;
        s32 h = m->height << 4;
        s32 x, y, cx, cy;
        y = 0;
        u16 v = sNativeFruitTrees[p->nativeFruit];
        for (; y < h; y++) {
            x = 0;
            if (w > 0) {
                goto test;
            loop:
                cx = x >> 4;
                cy = y >> 4;
                {
                    u16 *t = BlockMap_GetItemPtr(m, cx, cy, x - (cx << 4), y - (cy << 4), 0);
                    if (t) {
                        if (Unk_0204c318_InRange(t, 0x2f, 0x56)) {
                            u16 nv = v;
                            BlockMap_SetItemAtUnit(m, &nv, x, y, 0);
                            BlockMap_ClearBuriedAtUnit(m, x, y);
                        }
                    }
                }
                x++;
            test:
                if (x < w) goto loop;
            }
        }
    }
}
