typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

extern u16 data_021fcbd8[13];

extern void GX_VRAMCNT_SetLCDC_(u32 mask);


void GX_SetBankForLCDC(u32 bank);

void GX_SetBankForLCDC(u32 bank) {
    data_021fcbd8[0] |= bank;
    GX_VRAMCNT_SetLCDC_(bank);
}
