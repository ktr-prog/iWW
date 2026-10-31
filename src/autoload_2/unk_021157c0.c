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

void OSi_InitVramExclusive(void) {
    s32 i;
    data_021fcf54 = 0;
    for (i = 0; i < 9; i++) {
        data_021fcf58[i] = 0;
    }
}

