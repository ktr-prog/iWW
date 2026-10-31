typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_02114d84.h"
typedef int s32;

extern void *data_021fce8c;
extern void *data_021fce90;
extern void *data_021fce94;
extern u16 data_021fcf18;
extern u16 data_021fcf1c;
extern s32 data_021fcf20;
extern volatile u64 data_021fcf24;

u32 OS_GetConsoleType(void);
void OSi_EnterTimerCallback(s32 n, void *callback, void *arg);
void OS_SetIrqFunction(u32 mask, void *func);
void OS_EnableIrqMask(u32 mask);
void OSi_ExceptionHandler(void);
void OSi_SetTimerReserved(s32 n);

#define reg_OS_TM0CNT_L (*(volatile u16 *)0x04000100)
#define reg_OS_TM0CNT_H (*(volatile u16 *)0x04000102)
void OS_InitTick(void) {
    if (data_021fcf1c) return;
    data_021fcf1c = 1;
    OSi_SetTimerReserved(0);
    data_021fcf24 = 0;
    IO_W(&reg_OS_TM0CNT_H, 0);
    IO_W(&reg_OS_TM0CNT_L, 0);
    IO_W(&reg_OS_TM0CNT_H, 0xc1);
    OS_SetIrqFunction(8, OSi_CountUpTick);
    OS_EnableIrqMask(8);
    data_021fcf20 = 0;
}

u16 OS_IsTickAvailable(void) {
    return data_021fcf1c;
}

void OSi_CountUpTick(void) {
    data_021fcf24++;
    if (data_021fcf20) {
        IO_W(&reg_OS_TM0CNT_H, 0);
        IO_W(&reg_OS_TM0CNT_L, 0);
        IO_W(&reg_OS_TM0CNT_H, 0xc1);
        data_021fcf20 = 0;
    }
    OSi_EnterTimerCallback(0, OSi_CountUpTick, 0);
}

u16 OS_GetTickLo(void) {
    return IO_R(&reg_OS_TM0CNT_L);
}

void OSi_SetTimerReserved(s32 n) {
    data_021fcf18 |= 1 << n;
}

u16 data_021fcf18;
u16 data_021fcf1c;
s32 data_021fcf20;
volatile u64 data_021fcf24;
