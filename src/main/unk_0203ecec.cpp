#include "types.h"
#include "Unk_020d8c7c.h"
#include "talk/TalkRequestList.h"
#include "game/SceneInfo.h"
#include "game/EventScheduleRule.h"
#include "game/Unk_0203f3a0_L.h"
#include "game/EventDayEntry.h"
#include "game/Unk_0203f42c_L.h"
#include "talk/TalkRequestEntry.h"
#include "gfx/WorldCurve.h"
#include "game/EventCalendarModule.h"
#include "gfx/Camera.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209eb94.h"
#include "player/PlayerData.h"










extern "C" {
extern EventScheduleRule sEventSchedule[99];
}

extern "C" {
extern s32 (*sCharInteractSyncRecvFns[])(u8 *, s32);
}

extern "C" {
extern TalkRequestEntry sTalkRequestPool[15];
}

extern "C" {
extern u8 data_021e87d8[];
}

extern "C" {
extern Camera *gCamera;
}

extern "C" {
extern SceneInfo *gCurSceneInfo;
}

extern "C" {
extern s32 data_020c8cb8;
}

s32 sWorldCurveZScale = data_020c8cb8;
WorldCurve gWorldCurve;

extern "C" {
extern s16 data_02135f44[];
}

extern "C" {
}

extern "C" {
extern s32 sEventsOnlineRefresh;
}

extern "C" {
extern u8 gBackup[];
}

extern "C" {
extern EventDayEntry data_021c3bdc[7];
}

extern "C" {
extern u8 gTodayEvents[];
}

extern "C" {
s32 MI_CpuFill8(void *dst, s32 v, s32 n);
}

extern "C" {
void MI_CpuCopy8(void *src, void *dst, s32 n);
}

extern "C" {
s32 List_Remove(void *list, void *node);
}

extern "C" {
void func_02065cd4(void *p);
}

extern "C" {
void func_02065cc8(void *p);
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
s32 func_02098878(s32 p);
}

extern "C" {
}

extern "C" {
}

extern "C" {
s32 func_020771e4(void *p);
}

extern "C" {
s32 func_020771d8(void *p, s32 v);
}

extern "C" {
}

extern "C" {
}

extern "C" {
s32 FX_Div(s32 a, s32 b);
}

extern "C" {
s32 func_01ffcb0c(s32 a, s32 b);
}

extern "C" {
s32 FX_Sqrt(s32 a);
}

extern "C" {
s16 Math_Atan2(s32 a, s32 b);
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
}

extern "C" {
s32 func_02098044(s32 p, s32 v);
}

extern "C" {
s32 func_02072e44(u32 v);
}

extern "C" {
s32 Event_RefreshToday(s32 v);
}

extern "C" {
s32 Backup_GetStatus(void *p);
}

extern "C" {
s32 Event_RefreshIfDateChanged(void *p);
}

extern "C" {
s32 EventWeekSlots_UpdateToday(s32 v);
}

extern "C" {
s32 EventWeekSlots_IsSeenToday(void);
}

extern "C" {
s32 Game_IsIntroPeriod(void);
}

extern "C" {
void EventSchedule_CollectDay(void *out, void *in, s32 v);
}

extern "C" {
s32 DateTime_DiffMinutes(void *a, void *b);
}

extern "C" {
void Clock_GetDateTime(void *a);
}

extern "C" {
s32 DateTime_DiffDays(void *a, void *b);
}

extern "C" {
u32 Date_GetWeekday(u32 v, u32 a, u32 b);
}

extern "C" {
void EventDayList_Clear(void *a, s32 n);
}

extern "C" {
s32 EventSchedule_Match(EventDayEntry *out, EventScheduleRule *e, u32 v, Unk_0203f218_Ver w);
}

extern "C" {
s32 EventSchedule_IsBlocked(EventScheduleRule *e, Unk_0203f218_Ver w, EventDayEntry *tmp, EventDayEntry *out, s32 n, s32 x, s32 y);
}

extern "C" {
void Event_AdjustToDay(EventDayEntry *tmp, Unk_0203f218_Ver w);
}

extern "C" {
s32 Event_GetStateAt(s32 a, u8 *b, s32 c);
}

extern "C" {
s32 EventDayList_GetState(s32 a, u8 *b, EventDayEntry *c);
}

extern "C" {
EventDayEntry *EventDayList_Find(u32 id, EventDayEntry *tbl);
}

static inline BOOL IsOne(u8 v) { return v == 1 ? TRUE : FALSE; }
static inline BOOL IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }


extern "C" s32 EmotionSlots_Get(u8 *p, s32 i) { return p[i]; }

extern "C" void EmotionSlots_Set(u8 *p, s32 i, u32 v) { p[i] = v; }

extern "C" void EmotionSlots_Clear(u8 *p) {
    for (s32 i = 0; i < 4; i++) {
        p[i] = 0xff;
    }
}

extern "C" s32 Emotion_CountLearned(void) {
    u8 *p; s32 i, n;
    p = PlayerData_GetCurrent()->getEmotions();
    n = 0;
    for (i = 0; i < 4; i++) {
        if (EmotionSlots_Get(p, i) != 0xff) {
            n++;
        }
    }
    return n;
}

extern "C" s32 Emotion_FindFreeSlot(void) { return Emotion_FindSlot(0xff); }

extern "C" void Emotion_SetSlot(s32 i, s32 v) { EmotionSlots_Set(PlayerData_GetCurrent()->getEmotions(), i, v); }

extern "C" s32 Emotion_GetSlot(s32 i) { return EmotionSlots_Get(PlayerData_GetCurrent()->getEmotions(), i); }

extern "C" s32 Emotion_FindSlot(u32 id) {
    u8 *p = PlayerData_GetCurrent()->getEmotions();
    for (s32 i = 0; i < 4; i++) {
        if (id == (u32)EmotionSlots_Get(p, i)) {
            return i;
        }
    }
    return -1;
}

#pragma thumb off
extern "C" u32 WorldCurve_AngleToDistance(u32 x) {
    s32 v = FX_Div((x & 0xffff) << 12, 0x10000000);
    return (s32)(((s64)v * 0xc4ec6 + 0x800) >> 12);
}
#pragma thumb on

extern "C" s32 WorldCurve_ToCurved(VecFx32 *out, const VecFx32 *in) {
    if (IsOne(gCurSceneInfo->isOutdoor)) {
        s32 base = in->y + 0x1f576;
        if (in->z <= (*(volatile s32 *)&gWorldCurve.z) - gWorldCurve.flatDistance) {
            s32 t = in->z - ((*(volatile s32 *)&gWorldCurve.z) - gWorldCurve.flatDistance);
            if (t < 0) {
                t = -t;
            }
            base -= func_01ffcb0c(gWorldCurve.dropSlope, t);
        }
        s32 ang = (FX_Div(in->z, sWorldCurveZScale) * 0x2999) << 4 >> 16;
        out->x = in->x;
        s32 idx = (u16)ang >> 4;
        out->y = func_01ffcb0c(base, data_02135f44[idx * 2 + 1]);
        out->z = func_01ffcb0c(base, data_02135f44[idx * 2]);
        return ang;
    }
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    return 0;
}

extern "C" s32 WorldCurve_Apply(VecFx32 *out, const VecFx32 *in) {
    if (IsOne(gCurSceneInfo->isOutdoor)) {
        s32 base = in->y + 0x1f576;
        s32 ang = (FX_Div(in->z, sWorldCurveZScale) * 0x2999) << 4 >> 16;
        out->x = in->x;
        s32 idx = (u16)ang >> 4;
        out->y = func_01ffcb0c(base, data_02135f44[idx * 2 + 1]);
        out->z = func_01ffcb0c(base, data_02135f44[idx * 2]);
        return ang;
    }
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    return 0;
}

extern "C" s32 WorldCurve_FromCurved(VecFx32 *out, const VecFx32 *in) {
    if (IsOne(gCurSceneInfo->isOutdoor)) {
        s32 ang = Math_Atan2(in->z, in->y);
        out->x = in->x;
        s32 a = func_01ffcb0c(in->z, in->z);
        s32 b = func_01ffcb0c(in->y, in->y);
        out->y = FX_Sqrt(b + a) - 0x1f576;
        out->z = WorldCurve_AngleToDistance(ang);
        return ang;
    }
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    return 0;
}

extern "C" s16 WorldCurve_GetHorizonAngle(const VecFx32 *o) {
    if (IsOne(gCurSceneInfo->isOutdoor)) {
        s32 a = func_01ffcb0c(o->z, o->z);
        s32 b = func_01ffcb0c(o->y, o->y);
        s32 c = func_01ffcb0c(0x1f576, 0x1f576);
        s32 r = FX_Sqrt(b + a - c);
        s32 x = Math_Atan2(o->z, o->y);
        s32 y = Math_Atan2(r, 0x1f576);
        return x - y;
    }
    return 0;
}

extern "C" s32 WorldCurve_GetAngleScale(void) { return 0x2999; }

extern "C" s32 WorldCurve_GetRadius(void) { return 0x1f576; }

WorldCurve::WorldCurve() {
    x = 0;
    y = 0;
    z = 0;
    centerAngle = 0;
    dropSlope = FX_Div(0x1000, 0xa000);
    flatDistance = 0xe000;
}

WorldCurve::~WorldCurve() {}

extern "C" void WorldCurve_Update(WorldCurve *o, const VecFx32 *in) {
    o->x = in->x;
    o->y = in->y;
    o->z = in->z;
    if (gCamera) {
        s32 v = gCamera->getPitch();
        if (v > 0x27f7) {
            v = 0x27f7;
        } else if (v < 0x21fd) {
            v = 0x21fd;
        }
        o->flatDistance = func_01ffcb0c(-0x2c00, FX_Div((v - 0x27f7) << 12, (s32)0xffa06000)) + 0xe000;
    }
    if (IsOne(gCurSceneInfo->isOutdoor)) {
        o->centerAngle = (FX_Div(o->z, sWorldCurveZScale) * 0x2999) >> 12;
    } else {
        o->centerAngle = 0;
    }
}


extern "C" {
}

extern "C" {
}

