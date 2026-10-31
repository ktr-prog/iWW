
#include "host.h"

void __sinit_020c5fa0(void) {}
extern u16 data_021fcbd8[];
void GX_VRAMCNT_SetLCDC_(u32 banks);
void GX_SetBankForARM7(u32 bank) {
    data_021fcbd8[0] = (u16)((data_021fcbd8[0] | data_021fcbd8[3]) & ~bank);
    data_021fcbd8[3] = (u16)bank;
    if (bank & 0x4) HostIo_Write(0x04000242, 1, 0x82);
    if (bank & 0x8) HostIo_Write(0x04000243, 1, 0x8a);
    GX_VRAMCNT_SetLCDC_(data_021fcbd8[0]);
}
void GX_SetBankForSubBG(u32 bank) {
    data_021fcbd8[0] = (u16)((data_021fcbd8[0] | data_021fcbd8[9]) & ~bank);
    data_021fcbd8[9] = (u16)bank;
    switch (bank) {
    case 0x4: HostIo_Write(0x04000242, 1, 0x84); break;
    case 0x180: HostIo_Write(0x04000249, 1, 0x81); /* fall through */
    case 0x80: HostIo_Write(0x04000248, 1, 0x81); break;
    default: break;
    }
    GX_VRAMCNT_SetLCDC_(data_021fcbd8[0]);
}
s32 parse_format__wide(void) { host_unimplemented("parse_format__wide"); return 0; }
