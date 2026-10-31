typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
typedef int s32;

extern u32 data_021fcf54;
extern u16 data_021fcf58[9];
extern volatile u64 data_021fcf24;

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 state);
u32 OsCountZeroBits(u32 x);
u16 OS_GetTickLo(void);

typedef int BOOL;
BOOL OSi_TryLockVram(u16 bank, u16 lockId) {
    u32 workMap;
    s32 zeroBits;
    u32 enabled = OS_DisableInterrupts();

    workMap = (u32)(bank & data_021fcf54);
    while (1) {
        zeroBits = (s32)(31 - OsCountZeroBits(workMap));
        if (zeroBits < 0) {
            break;
        }
        workMap &= ~(0x00000001 << zeroBits);
        if (data_021fcf58[zeroBits] != lockId) {
            (void)OS_RestoreInterrupts(enabled);
            return 0;
        }
    }

    workMap = (u32)(bank & 0x01ff);
    while (1) {
        zeroBits = (s32)(31 - OsCountZeroBits(workMap));
        if (zeroBits < 0) {
            break;
        }
        workMap &= ~(0x00000001 << zeroBits);
        data_021fcf58[zeroBits] = lockId;
        data_021fcf54 |= (0x00000001 << zeroBits);
    }

    (void)OS_RestoreInterrupts(enabled);
    return 1;
}
