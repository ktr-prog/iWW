#include "uptr.h"
#include "host_mem.h"
#include "host_ptr32.h"
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "proto/autoload_2/unk_02114cd8.h"
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
void OS_InitException(void) {
    void *buf = gHostSysWork.excpVector;
    if (0) {
        data_021fce94 = buf;
    } else {
        data_021fce94 = 0;
    }
    if (data_021fce94 == 0 || (OS_GetConsoleType() & 0x40000000) == 0) {
        u32 *vec = (u32 *)(HW_DTCM_BLOCK + 0x3000);
        gHostSysWork.excpVector = (void *)OSi_ExceptionHandler;
        vec[0xfdc / 4] = HostPtr32_Of((const void *)OSi_ExceptionHandler);
    }
    data_021fce8c = 0;
}

void OS_SetUserExceptionHandler(void *handler, void *arg) {
    data_021fce8c = handler;
    data_021fce90 = arg;
}

void *data_021fce8c;
void *data_021fce94;
void *data_021fce90;
u32 data_021fce98[32];
