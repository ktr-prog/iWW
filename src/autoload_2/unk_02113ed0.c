#include "sys/OSThread.h"
#include "host_mem.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

#include "ds_stdarg.h"
#include "proto/autoload_2/unk_021127c0.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02113ed0.h"
#include "proto/autoload_2/unk_02114ef4.h"
#include "proto/itcm/unk_01ffa3cc.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_0206d49c.h"

typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;

typedef struct {
    OSThreadQueue sendQueue;
    OSThreadQueue recvQueue;
    void **msgArray;
    s32 msgCount;
    s32 firstIndex;
    s32 usedCount;
} OSMessageQueue;

typedef struct {
    s32 len;
    char *ptr;
} StrBuf;

extern OSThreadInfo data_021fcc2c;
extern OSThread *data_021fcc30;
extern OSThread **data_021fcc24;
extern u32 data_021fcc14;
extern u32 data_021fcc18;
extern u32 data_021fcc1c;
extern void (*data_021fcc20)(OSThread *, OSThread *);
extern u32 data_021fcc28;
extern OSThread data_021fcc3c;
extern OSThread data_021fccfc;
extern u32 data_021fce84;
extern u32 data_0213bff0;

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 e);
u32 OS_GetProcMode(void);
void OS_LoadContext(OSThread *t);
BOOL OS_SaveContext(OSThread *t);
u32 OS_GetLockID(void);
u16 OS_ReadOwnerOfLockWord(void *p);
u32 OS_TryLockCartridge(u32 id);
void OS_UnlockCartridge(u32 id);
void MIi_CpuClear32(u32 data, void *dest, u32 size);

void *OS_SetSwitchThreadCallback(void (*cb)(OSThread *, OSThread *));
void OS_VSPrintf(char *dst, const char *fmt, va_list ap);
void OS_WakeupThreadDirect(OSThread *t);
u32 OS_DisableScheduler(void);
u32 OS_EnableScheduler(void);
void OSi_RemoveThreadFromList(OSThread *t);
void OSi_InsertThreadToList(OSThread *t);
OSThread *OSi_RemoveLinkFromQueue(OSThreadQueue *q);
void OSi_InsertLinkToQueue(OSThreadQueue *q, OSThread *t);
void OS_InitContext(OSContext *c, uptr pc, uptr sp);
void OSi_ExitThread_ArgSpecified(OSThread *t, void *arg);
void OSi_CancelThreadAlarmForSleep(OSThread *t);
void OS_SetThreadDestructor(OSThread *t, void (*d)(void *));
BOOL OS_SetThreadPriority(OSThread *t, u32 prio);
OSThread *OS_SelectThread(void);
void OSi_UnlockAllMutex(OSThread *t);
void OSi_EnqueueTail(OSThread *t, OSMutex *m);
OSMutex *OSi_RemoveMutexLinkFromQueue(OSMutex **q);
u32 OSi_DetectDeviceType(void);
BOOL func_02113ed0(void);
u32 OSi_GetUnusedThreadId(void);
void OSi_SleepAlarmCallback(void *arg);
void OS_WakeupThreadDirect(OSThread *t);
void OS_KillThreadWithPriority(OSThread *t, void *arg, u32 prio);
u32 OS_GetThreadPriority(OSThread *t);
void OS_CreateThread(OSThread *t, void (*f)(void *), void *arg, void *stack, u32 size, u32 prio);

BOOL func_02113ed0(void) {
    volatile u16 *p;
    if (*HW_SYSWORK_AT(volatile u16, bootCheckInfo, 0x10) == 0) p = HW_SYSWORK_AT(volatile u16, reserved_680, 0x194);
    else p = HW_SYSWORK_AT(volatile u16, bootCheckInfo, 0x14);
    return *p == 1;
}

