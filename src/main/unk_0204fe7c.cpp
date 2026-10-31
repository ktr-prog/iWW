#include "types.h"
#include "save/Backup.h"
#include "proto/autoload_2/unk_0211dc4c.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_0204fe7c.h"


extern "C" Backup gBackup;

extern "C" s32 CARD_TryWaitBackupAsync(void);
extern "C" s32 CARD_GetResultCode(void);
extern "C" void CARD_UnlockBackup(u16 v);
extern "C" void OS_ReleaseLockID(u16 v);
extern "C" s32 OS_GetLockID(void);
extern "C" void CARD_LockBackup(u16 v);
extern "C" s32 CARDi_RequestStreamCommand(uptr a, uptr b, u32 c, void (*callback)(void *), void *arg, s32 f, u32 g,
                                          u32 h, u32 i);

extern "C" void FishDisplay_RecvAct02(u8 *p, u32 v);
extern "C" void FishDisplay_RecvAct01(u8 *p, u32 v);
extern "C" void FishDisplay_RecvAct00(u8 *p, u32 v);

extern "C" s32 Backup_Write(Backup *g, u32 a, const void *b, u32 c);
extern "C" s32 Backup_WriteAsync(Backup *g, u32 a, const void *b, u32 c);
extern "C" s32 Backup_Read(Backup *g, void *a, u32 b, u32 c);
extern "C" s32 Backup_ReadAsync(Backup *g, void *a, u32 b, u32 c);
extern "C" s32 Backup_GetStatus(Backup *g);
extern "C" void Backup_EndAccess(Backup *g);
extern "C" u16 Save_Sum16(u16 *p, u32 n);
extern "C" u16 Save_CalcChecksum(u16 *p, u32 n, u32 m);
extern "C" void Backup_CancelAndWait(void);
extern "C" void FishDisplay_OnNetPacket(u8 *p, u32 v);

extern "C" void (*sFishDisplayNetHandlers[3])(u8 *, u32);
extern "C" void (*sFishDisplayNetHandlers[3])(u8 *, u32) = {FishDisplay_RecvAct00, FishDisplay_RecvAct01, FishDisplay_RecvAct02};

extern "C" s32 Backup_Write(Backup *g, u32 a, const void *b, u32 c) {
    s32 r = 1;
    if (a + c > g->totalSize) {
        return r;
    }
    g->lockId = OS_GetLockID();
    if (g->lockId == -3) {
        return r;
    }
    CARD_LockBackup((u16)g->lockId);
    if (CARDi_RequestStreamCommand((uptr)b, a, c, 0, 0, 0, 7, 10, 2) != 0) {
        r = 0;
    }
    CARD_UnlockBackup((u16)g->lockId);
    OS_ReleaseLockID((u16)g->lockId);
    g->lockId = -3;
    return r;
}

extern "C" s32 Backup_WriteAsync(Backup *g, u32 a, const void *b, u32 c) {
    s32 r = 1;
    if (a + c > g->totalSize) {
        return r;
    }
    g->lockId = OS_GetLockID();
    if (g->lockId == -3) {
        return r;
    }
    CARD_LockBackup((u16)g->lockId);
    CARDi_RequestStreamCommand((uptr)b, a, c, 0, 0, r, 7, 10, 2);
    if (Backup_GetStatus(g) == 3) {
        r = 3;
    } else {
        Backup_EndAccess(g);
    }
    return r;
}

extern "C" s32 Backup_Read(Backup *g, void *a, u32 b, u32 c) {
    s32 r = 1;
    if (c + b <= g->totalSize) {
        g->lockId = OS_GetLockID();
        if (g->lockId != -3) {
            CARD_LockBackup((u16)g->lockId);
            if (CARDi_RequestStreamCommand(c, (uptr)a, b, 0, 0, 0, 6, r, 0) != 0) {
                r = 0;
            }
            CARD_UnlockBackup((u16)g->lockId);
            OS_ReleaseLockID((u16)g->lockId);
            g->lockId = -3;
        }
    }
    return r;
}

extern "C" s32 Backup_ReadAsync(Backup *g, void *a, u32 b, u32 c) {
    s32 r = 1;
    if (c + b <= g->totalSize) {
        g->lockId = OS_GetLockID();
        if (g->lockId != -3) {
            CARD_LockBackup((u16)g->lockId);
            CARDi_RequestStreamCommand(c, (uptr)a, b, 0, 0, r, 6, r, 0);
            if (Backup_GetStatus(g) == 3) {
                r = 3;
            } else {
                Backup_EndAccess(g);
            }
        }
    }
    return r;
}

extern "C" s32 Backup_GetStatus(Backup *g) {
    s32 r;
    if (g->lockId == -3) {
        r = 4;
    } else if (CARD_TryWaitBackupAsync() == 0) {
        r = 3;
    } else if (CARD_GetResultCode() == 0) {
        r = 0;
    } else {
        r = 1;
    }
    return r;
}

extern "C" void Backup_EndAccess(Backup *g) {
    if (g->lockId != -3) {
        CARD_UnlockBackup((u16)g->lockId);
        OS_ReleaseLockID((u16)g->lockId);
        g->lockId = -3;
    }
}

extern "C" u16 Save_Sum16(u16 *p, u32 n) {
    u16 sum = 0;
    if ((n & 1) == 0) {
        for (; n != 0; p++, n -= 2) {
            sum = sum + *p;
        }
    }
    return sum;
}

extern "C" u16 Save_CalcChecksum(u16 *p, u32 n, u32 m) {
    u16 t = Save_Sum16(p, n) - m;
    return (u16)((~t & 0xffff) + 1);
}

extern "C" void Backup_CancelAndWait(void) {
    if (Backup_GetStatus(&gBackup) == 3) {
        s32 t = OS_GetTick();
        CARD_CancelBackupAsync();
        do {
            if (CARD_TryWaitBackupAsync() != 0) break;
        } while ((u32)(OS_GetTick() - t) < 0xcc8d);
        if (gBackup.lockId != -3) {
            CARD_UnlockBackup((u16)gBackup.lockId);
            OS_ReleaseLockID((u16)gBackup.lockId);
        }
    }
}

extern "C" void FishDisplay_OnNetPacket(u8 *p, u32 v) {
    if (*p < 3) {
        sFishDisplayNetHandlers[*p](p, v);
    }
}
