#include "nitro/io_access.h"
#include "host_mem.h"
#include "proto/autoload_2/unk_02112458.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

extern s32 data_021fcc10;
u32 OS_DisableInterrupts_IrqAndFiq(void);
u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts_IrqAndFiq(u32 state);
void OS_RestoreInterrupts(u32 state);
void OS_SpinWait(u32 cycles);
s32 MI_SwapWord(u32 lockID, void *lockp);
void MIi_CpuClear32(u32 data, void *dest, u32 size);
s32 OSi_DoTryLockByWord(u32 lockID, void *lockp, void (*ctrl)(void), s32 disable_irq);
s32 OSi_DoUnlockByWord(u32 lockID, void *lockp, void (*ctrl)(void), s32 disable_irq);
s32 OS_LockByWord(u32 lockID, void *lockp, void (*ctrl)(void));
s32 OS_UnlockByWord(u32 lockID, void *lockp, void (*ctrl)(void));

void OS_InitLock(void) {
    volatile u16 *lock = HW_SYSWORK(volatile u16, initLock);
    if (data_021fcc10) {
        return;
    }
    data_021fcc10 = 1;
    *HW_SYSWORK(volatile u32, initLock) = 0;
    OS_LockByWord(0x7e, HW_SYSWORK(void, initLock), 0);
    while (lock[3] != 0) {
        OSi_WaitByLoop();
    }
    *HW_SYSWORK(volatile u32, lockIdFlagMain) = 0xffffffff;
    *HW_SYSWORK_AT(volatile u32, lockIdFlagMain, 0x4) = 0xffff0000;
    {
        volatile u32 zero = 0;
        MIi_CpuClear32(zero, HW_SYSWORK(void, vramCLock), 0x28);
    }
    IO_OR((volatile u16 *)0x04000204, 0x800);
    IO_OR((volatile u16 *)0x04000204, 0x80);
    OS_UnlockByWord(0x7e, HW_SYSWORK(void, initLock), 0);
    OS_LockByWord(0x7f, HW_SYSWORK(void, initLock), 0);
}

s32 OSi_DoLockByWord(u32 lockID, void *lockp, void (*ctrl)(void), s32 disable_irq) {
    s32 lastLockFlag;
    while ((lastLockFlag = OSi_DoTryLockByWord(lockID, lockp, ctrl, disable_irq)) > 0) {
        OSi_WaitByLoop();
    }
    return lastLockFlag;
}

s32 OS_LockByWord(u32 lockID, void *lockp, void (*ctrl)(void)) {
    return OSi_DoLockByWord(lockID, lockp, ctrl, 0);
}

s32 OSi_DoUnlockByWord(u32 lockID, void *lockp, void (*ctrl)(void), s32 disable_irq) {
    u32 last;
    if (lockID != ((u16 *)lockp)[2]) {
        return -2;
    }
    if (disable_irq) {
        last = OS_DisableInterrupts_IrqAndFiq();
    } else {
        last = OS_DisableInterrupts();
    }
    ((u16 *)lockp)[2] = 0;
    if (ctrl) {
        ctrl();
    }
    *(u32 *)lockp = 0;
    if (disable_irq) {
        OS_RestoreInterrupts_IrqAndFiq(last);
    } else {
        OS_RestoreInterrupts(last);
    }
    return 0;
}

s32 OS_UnlockByWord(u32 lockID, void *lockp, void (*ctrl)(void)) {
    return OSi_DoUnlockByWord(lockID, lockp, ctrl, 0);
}

s32 OSi_DoTryLockByWord(u32 lockID, void *lockp, void (*ctrl)(void), s32 disable_irq) {
    u32 last;
    s32 lastLockFlag;
    if (disable_irq) {
        last = OS_DisableInterrupts_IrqAndFiq();
    } else {
        last = OS_DisableInterrupts();
    }
    lastLockFlag = MI_SwapWord(lockID, lockp);
    if (lastLockFlag == 0) {
        if (ctrl) {
            ctrl();
        }
        ((u16 *)lockp)[2] = (u16)lockID;
    }
    if (disable_irq) {
        OS_RestoreInterrupts_IrqAndFiq(last);
    } else {
        OS_RestoreInterrupts(last);
    }
    return lastLockFlag;
}

void OS_UnlockCartridge(u32 lockID) {
    OSi_DoUnlockByWord(lockID, HW_SYSWORK(void, ctrdgLock), OSi_FreeCartridgeBus, 1);
}

s32 OS_TryLockCartridge(u32 lockID) {
    return OSi_DoTryLockByWord(lockID, HW_SYSWORK(void, ctrdgLock), OSi_AllocateCartridgeBus, 1);
}

void OSi_AllocateCartridgeBus(void) {
    IO_AND((volatile u16 *)0x04000204, ~0x80);
}

void OSi_FreeCartridgeBus(void) {
    IO_OR((volatile u16 *)0x04000204, 0x80);
}

void OS_LockCard(u32 lockID) {
    OS_LockByWord(lockID, HW_SYSWORK(void, cardLock), OSi_AllocateCardBus);
}

void OS_UnlockCard(u32 lockID) {
    OS_UnlockByWord(lockID, HW_SYSWORK(void, cardLock), OSi_FreeCardBus);
}

void OSi_AllocateCardBus(void) {
    IO_AND((volatile u16 *)0x04000204, ~0x800);
}

void OSi_FreeCardBus(void) {
    IO_OR((volatile u16 *)0x04000204, 0x800);
}

u16 OS_ReadOwnerOfLockWord(void *p) {
    return ((u16 *)p)[2];
}

void OSi_WaitByLoop(void) {
    OS_SpinWait(0x1000);
}

s32 data_021fcc10;
