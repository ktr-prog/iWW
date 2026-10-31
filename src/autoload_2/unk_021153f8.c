#include "nitro/os_rtc.h"
#include "nitro/os_alarm.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "proto/autoload_2/unk_02114ef4.h"
#include "proto/autoload_2/unk_021153f8.h"
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
void OS_InitVAlarm(void) {
    if (data_021fcf38) return;
    data_021fcf38 = 1;
    data_021fcf44[0] = 0;
    data_021fcf44[1] = 0;
    OS_DisableIrqMask(4);
    data_021fcf40 = 0;
    data_021fcf3c = 0;
}

u16 data_021fcf38;
u32 data_021fcf40;
u32 data_021fcf3c;
u32 data_021fcf44[2];
