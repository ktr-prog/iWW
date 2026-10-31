#include "ds_div.h"
#include "host_mem.h"
#include "nitro/os_rtc.h"
#include "nitro/os_alarm.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_02114ef4.h"
#include "proto/autoload_2/unk_02117984.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/itcm/unk_01ffd784.h"
#include "proto/main/unk_0206d49c.h"
typedef int s32;

typedef struct {
    u8 pad0[2];
    u8 favoriteColor : 4;
    u8 pad2 : 4;
    u8 birthMonth;
    u8 birthDay;
    u8 pad5;
    u16 nickName[10];
    u8 nickNameLength;
    u8 pad1b;
    u16 comment[26];
    u8 commentLength;
    u8 pad51[0x13];
    u16 language : 3;
} OSSharedUserInfo;

extern OSAlarmQueue data_021fcf30;
extern u16 data_021fcf2c;
extern u16 data_021fcf38;
extern u32 data_021fcf3c, data_021fcf40;
extern u32 data_021fcf44[2];
extern u16 data_021fcf4c;
extern u16 data_021fcf50;

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 state);
void OS_DisableIrqMask(u32 mask);
void OS_EnableIrqMask(u32 mask);
void OS_SetIrqMask(u32 mask);
void OS_ResetRequestIrqMask(u32 mask);
void OSi_EnterTimerCallback(s32 n, void *callback, void *arg);
void OSi_SetTimerReserved(s32 n);
void OSi_AlarmHandler(void);
u32 OS_GetLockID(void);
void CARD_LockRom(u32 id);
void MI_StopDma(s32 dmaNo);
s32 PXI_SendWordByFifo(u32 tag, u32 data, s32 err);
s32 PXI_IsCallbackReady(u32 tag, u32 proc);
void PXI_SetFifoRecvCallback(u32 tag, void *callback);
void MIi_CpuCopy16(const void *src, void *dest, u32 size);
void MI_CpuCopy8(const void *src, void *dest, u32 size);
void OSi_CommonCallback(u32 tag, u32 data, s32 err);
void OSi_SendToPxi(u32 data);

#define reg_OS_TM1CNT_L (*(volatile u16 *)0x04000104)
#define reg_OS_TM1CNT_H (*(volatile u16 *)0x04000106)
void OSi_SetTimer(OSAlarm *alarm) {
    s64 delta;
    u16 cnt;
    u64 tick = OS_GetTick();
    IO_W(&reg_OS_TM1CNT_H, 0);
    delta = (s64)(alarm->fire - tick);
    OSi_EnterTimerCallback(1, OSi_AlarmHandler, 0);
    cnt = 0;
    if (delta < 0) {
        cnt = 0xfffe;
    } else if (delta < 0x10000) {
        cnt = (u16)~delta;
    }
    IO_W(&reg_OS_TM1CNT_L, cnt);
    IO_W(&reg_OS_TM1CNT_H, 0xc1);
    OS_EnableIrqMask(0x10);
}

void OS_InitAlarm(void) {
    if (data_021fcf2c) return;
    data_021fcf2c = 1;
    OSi_SetTimerReserved(1);
    data_021fcf30.head = 0;
    data_021fcf30.tail = 0;
    OS_DisableIrqMask(0x10);
}

u16 OS_IsAlarmAvailable(void) {
    return data_021fcf2c;
}

void OS_CreateAlarm(OSAlarm *alarm) {
    alarm->handler = 0;
    alarm->tag = 0;
}

void OSi_InsertAlarm(OSAlarm *alarm, u64 fire) {
    OSAlarm *next;
    OSAlarm *prev;
    u64 tick;
    u64 delta;
    if (alarm->period) {
        tick = OS_GetTick();
        fire = alarm->start;
        if (fire < tick) {
            delta = tick - fire;
            fire += alarm->period * (1 + DS_UDIV64(delta, alarm->period));
        }
    }
    alarm->fire = fire;
    for (next = data_021fcf30.head; next; next = next->next) {
        if ((s64)(fire - next->fire) < 0) {
            alarm->prev = next->prev;
            next->prev = alarm;
            alarm->next = next;
            if (alarm->prev) {
                alarm->prev->next = alarm;
                return;
            }
            data_021fcf30.head = alarm;
            OSi_SetTimer(alarm);
            return;
        }
    }
    alarm->next = 0;
    prev = data_021fcf30.tail;
    data_021fcf30.tail = alarm;
    alarm->prev = prev;
    if (prev) {
        prev->next = alarm;
        return;
    }
    data_021fcf30.tail = alarm;
    data_021fcf30.head = alarm;
    OSi_SetTimer(alarm);
}

void OS_SetAlarm(OSAlarm *alarm, u64 tick, void (*handler)(void *), void *arg) {
    u32 enabled;
    if (alarm == 0 || alarm->handler != 0) Fatal_Trap();
    enabled = OS_DisableInterrupts();
    alarm->period = 0;
    alarm->handler = handler;
    alarm->arg = arg;
    OSi_InsertAlarm(alarm, tick + OS_GetTick());
    OS_RestoreInterrupts(enabled);
}

void OS_CancelAlarm(OSAlarm *alarm) {
    u32 enabled = OS_DisableInterrupts();
    OSAlarm *next;
    if (alarm->handler == 0) {
        OS_RestoreInterrupts(enabled);
        return;
    }
    next = alarm->next;
    if (next == 0) {
        data_021fcf30.tail = alarm->prev;
    } else {
        next->prev = alarm->prev;
    }
    if (alarm->prev) {
        alarm->prev->next = next;
    } else {
        data_021fcf30.head = next;
        if (next) OSi_SetTimer(next);
    }
    alarm->handler = 0;
    alarm->period = 0;
    OS_RestoreInterrupts(enabled);
}

void OSi_ArrangeTimer(void) {
    OSAlarm *alarm;
    void (*handler)(void *);
    u64 tick;
    OSAlarm *next;
    u32 *dtcm = (u32 *)HW_DTCM_BLOCK;
    IO_W(&reg_OS_TM1CNT_H, 0);
    OS_DisableIrqMask(0x10);
    dtcm[0x3ff8 / 4] |= 0x10;
    tick = OS_GetTick();
    alarm = data_021fcf30.head;
    if (alarm == 0) return;
    if (tick < alarm->fire) {
        OSi_SetTimer(alarm);
        return;
    }
    next = alarm->next;
    data_021fcf30.head = next;
    if (next == 0) {
        data_021fcf30.tail = 0;
    } else {
        next->prev = 0;
    }
    handler = alarm->handler;
    if (alarm->period == 0) alarm->handler = 0;
    if (handler) handler(alarm->arg);
    if (alarm->period != 0) {
        alarm->handler = handler;
        OSi_InsertAlarm(alarm, 0);
    }
    if (data_021fcf30.head) OSi_SetTimer(data_021fcf30.head);
}

void OS_SetAlarmTag(OSAlarm *alarm, u32 tag) {
    alarm->tag = tag;
}

void OS_CancelAlarms(u32 tag) {
    u32 enabled;
    OSAlarm *alarm;
    OSAlarm *next;
    if (tag == 0) return;
    enabled = OS_DisableInterrupts();
    for (alarm = data_021fcf30.head, next = alarm ? alarm->next : 0; alarm; alarm = next, next = alarm ? alarm->next : 0) {
        if (alarm->tag == tag) OS_CancelAlarm(alarm);
    }
    OS_RestoreInterrupts(enabled);
}

u16 data_021fcf2c;
OSAlarmQueue data_021fcf30;
