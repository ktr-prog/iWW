#include "types.h"
#include "host_labels.h"
#include "net/CommManager.h"
#include "town/TownUpdateThread.h"
#include "game/EventDayEntry.h"
#include "game/Unk_02042104_Date.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/main/unk_02041868.h"
#include "proto/main/unk_02097444.h"
#include "proto/ov003/unk_ov003_02225800.h"


struct TownJunkInsectFlags { u8 spawnFlies; u8 spawnAnts; u8 pad[2]; };


extern OSThreadInfo data_021fcc2c;

extern CommManager *gCommManager;
extern TownUpdater gTownUpdater;
extern volatile u32 gTownEval[];
extern u8 gSaveData[];
#define data_021ed20c HOST_LABEL(u8 (*)[], data_021ed20c)

u8 sTownBbsUpdateCtx[4];
TownJunkInsectFlags gTownJunkInsectFlags;


extern "C" {
void Town_GetEnvironmentRank();
s32 Scene_InTown();
s32 Scene_InTownUnk31();
BOOL OS_IsThreadTerminated(OSThread *t);
void OS_KillThread(OSThread *t, void *arg);
void TownUpdateThread_Kill(TownUpdateThread *p);
void TownUpdateThread_Destroy();
void TownJunkInsects_InitFromEval(TownJunkInsectFlags *p);
void MI_CpuCopy8(void *src, void *dst, u32 n);
void Clock_GetDateTime(Unk_02042104_Date *d);
void DateTime_SubHours(Unk_02042104_Date *d, u32 n);
void DateTime_SubDays(Unk_02042104_Date *d, s32 n);
u32 Date_GetWeekday(u32 a, u32 b, u32 c);
s32 TownBbs_GetDaysToPost(void *o, u8 *a, Unk_02042104_Date *d);
void TownBbs_CatchUpPelicanDate(void *o, u8 *base, Unk_02042104_Date *d);
void TownBbs_PostDays(void *o, u8 *base, s32 cnt, Unk_02042104_Date *d, s32 flag);
void TownBbs_PostEventsForDay(void *o, u8 *base, Unk_02042104_Date *d);
s32 Game_IsIntroPeriod();
s32 DateTime_DiffDays(Unk_02042104_Date *a, Unk_02042104_Date *b);
void DateTime_AddDays(Unk_02042104_Date *a, s32 n);
void TownState_PickNextWeekDate(void *a, u8 *b);
void TownBbs_PostPelicanNotice(void *o, struct SaveData *save, Unk_02042104_Date *d);
void TownBbs_PostSlogan(void *o, struct SaveData *save, Unk_02042104_Date *d);
s32 EventSchedule_CollectDayAll(EventDayEntry *z, Unk_02042104_Date *d);
void TownBbs_PostDayEvents(void *o, EventDayEntry *z, Unk_02042104_Date *d);
void TownUpdateThread_Main(void *arg);
u32 DC_FlushAll();
void Town_AdvanceDays(void *r, u8 *a, u8 *b, u32 c, u32 d, u32 e);
void MI_CpuFill8(void *p, u32 v, u32 n);
s32 TownUpdateThread_StartCtx(TownUpdateThread *p);
void TownUpdateThread_SetArgs(TownUpdateThread *p, u8 *a, u8 *b, u32 c, u8 d);
void TownUpdateThread_Init(TownUpdateThread *p);
void OS_CreateThread(OSThread *th, void (*fn)(void *), void *arg, void *stack, u32 size, u32 prio);
void OS_WakeupThreadDirect(OSThread *th);
}

extern "C" s32 TownBbs_GetDaysToPost(void *o, u8 *a, Unk_02042104_Date *d) {
    s32 r = 0;
    u8 v2 = a[2];
    if (v2 == 0xff && a[1] == 0xff && a[0] == 0xff) {
        r = 1;
        goto end;
    }
    if (v2 == d->c5 && a[1] == d->c4 && a[0] == d->c3) {
        goto end;
    }
    {
        Unk_02042104_Date t;
        *(u32 *)&t = 0;
        *((u32 *)&t + 1) = 0;
        *(u32 *)&t = 0;
        *((u32 *)&t + 1) = 0;
        t.c5 = a[2];
        t.c4 = a[1];
        t.c3 = a[0];
        r = DateTime_DiffDays(&t, d);
        if (r > 0x1f) {
            r = 0x1f;
        } else if (r < 0) {
            r = 1;
        }
    }
end:
    return r;
}

extern "C" void TownBbs_CatchUpPelicanDate(void *o, u8 *base, Unk_02042104_Date *d) {
    Unk_02042104_Date a;
    *(u32 *)&a = 0;
    *((u32 *)&a + 1) = 0;
    u8 *p = base + 0x15e5c;
    *(u32 *)&a = 0;
    *((u32 *)&a + 1) = 0;
    a.c5 = p[2];
    a.c4 = p[1];
    a.c3 = p[0];
    u8 *q = base + 0x15e54;
    while (DateTime_DiffDays(d, &a) < 0) {
        TownState_PickNextWeekDate(q, p);
        a.c5 = p[2];
        a.c4 = p[1];
        a.c3 = p[0];
    }
}

extern "C" void TownBbs_PostEventsForDay(void *o, u8 *base, Unk_02042104_Date *d) {
    Unk_02042104_Date x, y, w;
    EventDayEntry z[7];
    *(u32 *)&x = 0;
    *((u32 *)&x + 1) = 0;
    MI_CpuCopy8(d, &x, 8);
    MI_CpuCopy8(&x, &y, 8);
    if (EventSchedule_CollectDayAll(z, &y) > 0) {
        MI_CpuCopy8(&x, &w, 8);
        TownBbs_PostDayEvents(o, z, &w);
    }
    base[0x15e76] = 1;
}

extern "C" void TownBbs_PostDays(void *o, u8 *base, s32 cnt, Unk_02042104_Date *d, s32 flag0) {
    s32 f4 = 0;
    Unk_02042104_Date a, b, c, e;
    *(u32 *)&a = 0;
    *((u32 *)&a + 1) = 0;
    *(u32 *)&b = 0;
    *((u32 *)&b + 1) = 0;
    u8 *p = base + 0x15e5c;
    MI_CpuCopy8(d, &b, 8);
    s32 flag = flag0;
    if (base[0x15e76] != 0 || PlayerDataArray_CountUsed(base + 0xc) > 1 || Game_IsIntroPeriod() == 0) {
        f4 = 1;
    }
    while (cnt > 0) {
        *(u32 *)&a = 0;
        *((u32 *)&a + 1) = 0;
        a.c5 = p[2];
        a.c4 = p[1];
        a.c3 = p[0];
        if (DateTime_DiffDays(&b, &a) == 0) {
            MI_CpuCopy8(&a, &c, 8);
            TownBbs_PostPelicanNotice(o, (struct SaveData *)base, &c);
            TownState_PickNextWeekDate(base + 0x15e54, p);
        }
        if (flag == 1) {
            MI_CpuCopy8(&b, &e, 8);
            TownBbs_PostSlogan(o, (struct SaveData *)base, &e);
        }
        if (f4 != 0) {
            TownBbs_PostEventsForDay(o, base, &b);
        }
        cnt--;
        flag = (flag + 1) % 7;
        DateTime_AddDays(&b, 1);
    }
}

extern "C" void TownBbs_UpdateDaily() {
    u8 *base = gSaveData;
    Unk_02042104_Date d;
    *(u32 *)&d = 0;
    *((u32 *)&d + 1) = 0;
    Clock_GetDateTime(&d);
    DateTime_SubHours(&d, 6);
    u8 *p = data_021ed20c;
    s32 r = TownBbs_GetDaysToPost(sTownBbsUpdateCtx, p, &d);
    if (r != 0) {
        p[2] = d.c5;
        p[1] = d.c4;
        p[0] = d.c3;
        DateTime_SubDays(&d, r - 1);
        u32 x = Date_GetWeekday(d.c5, d.c4, d.c3);
        TownBbs_CatchUpPelicanDate(sTownBbsUpdateCtx, base, &d);
        TownBbs_PostDays(sTownBbsUpdateCtx, base, r, &d, x);
    } else if (base[0x15e76] == 0) {
        if (PlayerDataArray_CountUsed(base + 0xc) > 1 || Game_IsIntroPeriod() == 0) {
            TownBbs_PostEventsForDay(sTownBbsUpdateCtx, base, &d);
        }
    }
}

extern "C" void TownUpdateThread_Main(void *arg) {
    DC_FlushAll();
    TownUpdateThread *g = gTownUpdater.updateThread;
    (void)arg;
    Town_AdvanceDays(&gTownUpdater, g->lastDate, g->curDate, g->elapsedDays, g->prevDayRain, 1);
    Heap_SetThreadHeap(g->callerThread, g->heap);
    g->done = 1;
    OS_ExitThread();
}

extern "C" void TownUpdateThread_Init(TownUpdateThread *p) {
    p->hasArgs = 0;
    p->done = 0;
    p->started = 0;
    MI_CpuFill8(p, 0, sizeof(p->thread));
    p->threadState = 2;
}

extern "C" void TownUpdateThread_Create() {
    gTownUpdater.updateThread = (TownUpdateThread *)Heap_Alloc(gCurrentHeap, sizeof(TownUpdateThread));
    if (gTownUpdater.updateThread != 0) {
        TownUpdateThread_Init(gTownUpdater.updateThread);
    }
}

extern "C" void TownUpdateThread_SetArgs(TownUpdateThread *p, u8 *a, u8 *b, u32 c, u8 d) {
    MI_CpuCopy8(a, p->lastDate, 8);
    MI_CpuCopy8(b, p->curDate, 8);
    p->elapsedDays = c;
    p->prevDayRain = d;
    p->hasArgs = 1;
}

extern "C" void TownUpdateThread_Request(u8 *a, u8 *b, u32 c, u8 d) {
    if (gTownUpdater.updateThread != 0) {
        TownUpdateThread_SetArgs(gTownUpdater.updateThread, a, b, c, d);
    }
}

extern "C" s32 TownUpdateThread_StartCtx(TownUpdateThread *p) {
    if (p->hasArgs == 0) {
        return 0;
    }
    p->stackGuardLow = 0x3039;
    p->stackGuardHigh = 0x3039;
    p->done = 0;
    p->started = 1;
    OS_CreateThread(&p->thread, TownUpdateThread_Main, p->lastDate, &p->stackGuardHigh, 0x1000, 0x1e);
    p->callerThread = data_021fcc2c.current;
    p->heap = gCurrentHeap;
    Heap_SetThreadHeap(p->callerThread, NULL);
    Heap_SetThreadHeap(&p->thread, p->heap);
    OS_WakeupThreadDirect(&p->thread);
    return 1;
}

extern "C" s32 TownUpdateThread_Start() {
    s32 r = 0;
    if (gTownUpdater.updateThread != 0) {
        r = TownUpdateThread_StartCtx(gTownUpdater.updateThread);
        if (r == 0) {
            TownUpdateThread_Destroy();
        }
    }
    return r;
}

extern "C" BOOL TownUpdateThread_PollDone() {
    BOOL r = FALSE;
    TownUpdateThread *p = gTownUpdater.updateThread;
    if (p != 0) {
        if (p->done != 0) {
            TownUpdateThread_Destroy();
            r = TRUE;
        }
    }
    return r;
}

extern "C" void TownUpdateThread_Kill(TownUpdateThread *p) {
    if (p->started != 0) {
        if (OS_IsThreadTerminated(&p->thread) == 0) OS_KillThread(&p->thread, NULL);
    }
}

extern "C" void TownUpdateThread_Destroy() {
    TownUpdateThread *p = gTownUpdater.updateThread;
    if (p != 0) {
        TownUpdateThread_Kill(p);
        Heap_Free(gCurrentHeap, p);
        gTownUpdater.updateThread = 0;
    }
}

extern "C" void TownJunkInsects_InitFromEval(TownJunkInsectFlags *p) {
    if (((s32)(gTownEval[0x30 / 4] << 24) >> 31) != 0) {
        p->spawnFlies = 1;
    } else {
        p->spawnFlies = 0;
    }
    if (((s32)(gTownEval[0x30 / 4] << 25) >> 31) != 0) {
        p->spawnAnts = 1;
    } else {
        p->spawnAnts = 0;
    }
}

extern "C" void TownJunkInsects_Apply(TownJunkInsectFlags *p) {
    if (gCommManager->isSlotActive(gCommManager->myAid) != 0) return;
    if (Scene_InTown() == 0) {
        if (Scene_InTownUnk31() == 0) return;
    }
    if (p->spawnAnts != 0) sAntSpawnEnabled = 1;
    if (p->spawnAnts != 0 || p->spawnFlies != 0) Insect_EnableTrashFlies();
    p->spawnFlies = 0;
    p->spawnAnts = 0;
}

extern "C" void TownJunkInsects_Refresh() {
    Town_GetEnvironmentRank();
    TownJunkInsects_InitFromEval(&gTownJunkInsectFlags);
}

