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

void OSi_UnlockVram(u32 mask, u16 data) {
    s32 i;
    u32 bits;
    u32 enabled = OS_DisableInterrupts();
    bits = mask & data_021fcf54 & 0x1ff;
    for (;;) {
        i = 31 - OsCountZeroBits(bits);
        if (i < 0) break;
        bits &= ~(1 << i);
        if (data == data_021fcf58[i]) {
            data_021fcf58[i] = 0;
            data_021fcf54 &= ~(1 << i);
        }
    }
    OS_RestoreInterrupts(enabled);
}

u32 data_021fcf54;
u16 data_021fcf58[9];
