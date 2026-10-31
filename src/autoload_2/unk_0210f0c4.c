#include "nitro/io_access.h"
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 data_0213bfe8;
extern u32 data_0213bfec;
extern u16 data_021fcbd0;
extern u16 data_021fcbd4;

#define reg_GX_DISPCNT (*(volatile u32 *)0x04000000)
#define reg_GXS_DB_DISPCNT (*(volatile u32 *)0x04001000)

void GX_SetGraphicsMode(u32 dispMode, u32 bgMode, u32 bg0_2d3d);
void GXS_SetGraphicsMode(u32 bgMode);

void GX_SetGraphicsMode(u32 dispMode, u32 bgMode, u32 bg0_2d3d) {
    u32 cnt = IO_R(&reg_GX_DISPCNT);
    data_021fcbd4 = (u16)dispMode;
    if (!data_0213bfe8) dispMode = 0;
    cnt &= ~(0x7 | 0x8 | 0xf0000);
    IO_W(&reg_GX_DISPCNT, (u32)(cnt | (dispMode << 16) | bgMode | (bg0_2d3d << 3)));
    if (!data_021fcbd4) data_0213bfe8 = 0;
}

void GXS_SetGraphicsMode(u32 bgMode) {
    IO_W(&reg_GXS_DB_DISPCNT, (u32)((IO_R(&reg_GXS_DB_DISPCNT) & ~0x7) | bgMode));
}

u16 data_021fcbd0;
u16 data_021fcbd4;
u32 data_0213bfec = 3;
u16 data_0213bfe8 = 1;
