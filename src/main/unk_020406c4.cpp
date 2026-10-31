#include "types.h"
#include "game/EventWeekSlots.h"
#include "sys/ClockDateTime.h"
#include "proto/main/unk_020406c4.h"
#include "proto/main/unk_02063904.h"


extern "C" {

void DateTime_AddDays(ClockDateTime *, s32);
void MI_CpuCopy8(void *, void *, u32);
s32 EventSchedule_CollectAtNoon(void *, s32, void *);

BOOL WeekVisitors_ListContains(void *, u8 *p, u32 v);
}

extern const u32 sWeekVisitorWeights[7];
extern const u32 sWeekVisitorIds[7];
const u32 sWeekVisitorWeights[7] = {0xc, 0xc, 0xc, 0xc, 0x14, 0x14, 0xc};
const u32 sWeekVisitorIds[7] = {0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x3e};

extern "C" s32 WeekVisitors_FindFreeDays(void *, s32 *out, ClockDateTime *x)
{
    s32 i;
    s32 cnt = 0;
    u8 a[8];
    u8 b[0x58];
    DateTime_AddDays(x, 1);
    for (i = 0; i < 5; i++) {
        MI_CpuCopy8(x, a, 8);
        if (EventSchedule_CollectAtNoon(b, 7, a) <= 0) {
            *out = 1;
            cnt++;
        } else {
            *out = 0;
        }
        DateTime_AddDays(x, 1);
        out++;
    }
    return cnt;
}

extern "C" s32 WeekVisitors_PickFreeDay(void *, s32 *arr, s32 n)
{
    s32 r = Random_GlobalBelow(n);
    s32 i = 0;
    s32 res = -1;
    for (; i < 5; arr++, i++) {
        if (*arr == 1 && --r < 0) {
            res = i;
            break;
        }
    }
    return res;
}

extern "C" BOOL WeekVisitors_ListContains(void *, u8 *p, u32 v)
{
    BOOL result = FALSE;
    s32 i;
    for (i = 0; i <= 5; p++, i++) {
        if (*p != 99 && *p == v) {
            result = TRUE;
            break;
        }
    }
    return result;
}

extern "C" s32 WeekVisitors_PickRandom(EventWeekSlots *s, u8 *a) {
    s32 ids[7];
    s32 wts[7];
    s32 i;
    s32 sum;
    s32 k;
    s32 r;
    s32 m;
    s32 res = 0x63;
    s32 j;

    for (i = 0; i < 7; i++) {
        ids[i] = 0x63;
        wts[i] = 0;
    }
    sum = 0;
    k = 0;
    j = 0;
    for (; j < 7; j++) {
        s32 id = sWeekVisitorIds[j];
        if (WeekVisitors_ListContains(s, a, id) == 0) {
            ids[k] = id;
            wts[k] = sWeekVisitorWeights[j];
            k++;
            sum += sWeekVisitorWeights[j];
        }
    }
    if (sum > 0) {
        r = Random_GlobalBelow(sum);
        for (m = 0; m < k; m++) {
            r -= wts[m];
            if (r < 0) {
                res = ids[m];
                break;
            }
        }
    }
    return res;
}

