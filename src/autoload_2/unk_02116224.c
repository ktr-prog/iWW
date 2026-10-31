#include "uptr.h"
#include "nitro/io_access.h"
typedef unsigned int u32;
typedef volatile u32 vu32;

extern void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 mode);
extern void MIi_CheckDma0SourceAddress(u32 dmaNo, uptr src, u32 size, u32 flags);
extern void MIi_DmaSetParams(u32 dmaNo, uptr src, uptr dest, u32 cnt);

void MIi_CardDmaCopy32(u32 dmaNo, uptr src, uptr dest, u32 size) {
    vu32 *dmaCntp;
    MIi_CheckAnotherAutoDMA(dmaNo, 0xffffffff);
    MIi_CheckDma0SourceAddress(dmaNo, src, size, 0x1000000);
    if (size == 0) return;
    dmaCntp = &((vu32 *)0x040000b0)[dmaNo * 3 + 2];
    while (IO_R(dmaCntp) & 0x80000000)
        ;
    MIi_DmaSetParams(dmaNo, src, dest, 0xaf000001);
}
