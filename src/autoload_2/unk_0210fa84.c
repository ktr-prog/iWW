#include "nitro/io_access.h"
#include "proto/autoload_2/unk_0210fa84.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

extern u16 data_021fcbd8[13];

extern void GX_VRAMCNT_SetLCDC_(u32 mask);

#define reg_GX_DISPCNT (*(volatile u32 *)0x04000000)
#define reg_GX_DISP3DCNT (*(volatile u16 *)0x04000060)
#define VRAMCNT(n) (*(volatile u8 *)(0x04000240 + (n)))


void GX_SetBankForBG(int bank) {
    data_021fcbd8[0] = (u16)((data_021fcbd8[0] | data_021fcbd8[1]) & ~bank);
    data_021fcbd8[1] = bank;
    switch (bank) {
    case 0: break;
    case 8: IO_W(&VRAMCNT(3), 0x81); break;
    case 12: IO_W(&VRAMCNT(3), 0x89);
    case 4: IO_W(&VRAMCNT(2), 0x81); break;
    case 14: IO_W(&VRAMCNT(3), 0x91);
    case 6: IO_W(&VRAMCNT(2), 0x89);
    case 2: IO_W(&VRAMCNT(1), 0x81); break;
    case 15: IO_W(&VRAMCNT(3), 0x99);
    case 7: IO_W(&VRAMCNT(2), 0x91);
    case 3: IO_W(&VRAMCNT(1), 0x89);
    case 1: IO_W(&VRAMCNT(0), 0x81); break;
    case 11: IO_W(&VRAMCNT(0), 0x81); IO_W(&VRAMCNT(1), 0x89); IO_W(&VRAMCNT(3), 0x91); break;
    case 13: IO_W(&VRAMCNT(3), 0x91);
    case 5: IO_W(&VRAMCNT(0), 0x81); IO_W(&VRAMCNT(2), 0x89); break;
    case 9: IO_W(&VRAMCNT(0), 0x81); IO_W(&VRAMCNT(3), 0x89); break;
    case 10: IO_W(&VRAMCNT(1), 0x81); IO_W(&VRAMCNT(3), 0x89); break;
    case 0x70: IO_W(&VRAMCNT(6), 0x99);
    case 0x30: IO_W(&VRAMCNT(5), 0x91);
    case 0x10: IO_W(&VRAMCNT(4), 0x81); break;
    case 0x50: IO_W(&VRAMCNT(6), 0x91); IO_W(&VRAMCNT(4), 0x81); break;
    case 0x60: IO_W(&VRAMCNT(6), 0x89);
    case 0x20: IO_W(&VRAMCNT(5), 0x81); break;
    case 0x40: IO_W(&VRAMCNT(6), 0x81); break;
    }
    GX_VRAMCNT_SetLCDC_(data_021fcbd8[0]);
}

void GX_SetBankForOBJ(int bank) {
    data_021fcbd8[0] = (u16)((data_021fcbd8[0] | data_021fcbd8[2]) & ~bank);
    data_021fcbd8[2] = bank;
    switch (bank) {
    case 0: break;
    case 3: IO_W(&VRAMCNT(1), 0x8a);
    case 1: IO_W(&VRAMCNT(0), 0x82); break;
    case 2: IO_W(&VRAMCNT(1), 0x82); break;
    case 0x70: IO_W(&VRAMCNT(6), 0x9a);
    case 0x30: IO_W(&VRAMCNT(5), 0x92);
    case 0x10: IO_W(&VRAMCNT(4), 0x82); break;
    case 0x50: IO_W(&VRAMCNT(6), 0x92); IO_W(&VRAMCNT(4), 0x82); break;
    case 0x60: IO_W(&VRAMCNT(6), 0x8a);
    case 0x20: IO_W(&VRAMCNT(5), 0x82); break;
    case 0x40: IO_W(&VRAMCNT(6), 0x82); break;
    }
    GX_VRAMCNT_SetLCDC_(data_021fcbd8[0]);
}

void GX_SetBankForBGExtPltt(int bank) {
    data_021fcbd8[0] = (u16)((data_021fcbd8[0] | data_021fcbd8[7]) & ~bank);
    data_021fcbd8[7] = bank;
    switch (bank) {
    case 0: IO_AND(&reg_GX_DISPCNT, ~0x40000000); break;
    case 0x10: IO_OR(&reg_GX_DISPCNT, 0x40000000); IO_W(&VRAMCNT(4), 0x84); break;
    case 0x40: IO_OR(&reg_GX_DISPCNT, 0x40000000); IO_W(&VRAMCNT(6), 0x8c); break;
    case 0x60: IO_W(&VRAMCNT(6), 0x8c);
    case 0x20: IO_W(&VRAMCNT(5), 0x84); IO_OR(&reg_GX_DISPCNT, 0x40000000); break;
    }
    GX_VRAMCNT_SetLCDC_(data_021fcbd8[0]);
}

void GX_SetBankForOBJExtPltt(int bank) {
    data_021fcbd8[0] = (u16)((data_021fcbd8[0] | data_021fcbd8[8]) & ~bank);
    data_021fcbd8[8] = bank;
    switch (bank) {
    case 0x20: IO_OR(&reg_GX_DISPCNT, 0x80000000); IO_W(&VRAMCNT(5), 0x85); break;
    case 0x40: IO_OR(&reg_GX_DISPCNT, 0x80000000); IO_W(&VRAMCNT(6), 0x85); break;
    case 0: IO_AND(&reg_GX_DISPCNT, ~0x80000000); break;
    }
    GX_VRAMCNT_SetLCDC_(data_021fcbd8[0]);
}

void GX_SetBankForTex(int bank) {
    data_021fcbd8[0] = (u16)((data_021fcbd8[0] | data_021fcbd8[4]) & ~bank);
    data_021fcbd8[4] = bank;
    if (bank == 0) {
        IO_AND(&reg_GX_DISP3DCNT, 0xcffe);
    } else {
        IO_W(&reg_GX_DISP3DCNT, (u16)((IO_R(&reg_GX_DISP3DCNT) & ~0x3000) | 1));
        switch (bank) {
        case 0: break;
        case 5: IO_W(&VRAMCNT(0), 0x83); IO_W(&VRAMCNT(2), 0x8b); break;
        case 9: IO_W(&VRAMCNT(0), 0x83); IO_W(&VRAMCNT(3), 0x8b); break;
        case 10: IO_W(&VRAMCNT(1), 0x83); IO_W(&VRAMCNT(3), 0x8b); break;
        case 11: IO_W(&VRAMCNT(0), 0x83); IO_W(&VRAMCNT(1), 0x8b); IO_W(&VRAMCNT(3), 0x93); break;
        case 13: IO_W(&VRAMCNT(0), 0x83); IO_W(&VRAMCNT(2), 0x8b); IO_W(&VRAMCNT(3), 0x93); break;
        case 8: IO_W(&VRAMCNT(3), 0x83); break;
        case 12: IO_W(&VRAMCNT(3), 0x8b);
        case 4: IO_W(&VRAMCNT(2), 0x83); break;
        case 14: IO_W(&VRAMCNT(3), 0x93);
        case 6: IO_W(&VRAMCNT(2), 0x8b);
        case 2: IO_W(&VRAMCNT(1), 0x83); break;
        case 15: IO_W(&VRAMCNT(3), 0x9b);
        case 7: IO_W(&VRAMCNT(2), 0x93);
        case 3: IO_W(&VRAMCNT(1), 0x8b);
        case 1: IO_W(&VRAMCNT(0), 0x83); break;
        }
    }
    GX_VRAMCNT_SetLCDC_(data_021fcbd8[0]);
}

void GX_SetBankForTexPltt(int bank) {
    data_021fcbd8[0] = (u16)((data_021fcbd8[0] | data_021fcbd8[5]) & ~bank);
    data_021fcbd8[5] = bank;
    switch (bank) {
    case 0: break;
    case 0x40: IO_W(&VRAMCNT(6), 0x83); break;
    case 0x60: IO_W(&VRAMCNT(6), 0x8b);
    case 0x20: IO_W(&VRAMCNT(5), 0x83); break;
    case 0x70: IO_W(&VRAMCNT(6), 0x9b);
    case 0x30: IO_W(&VRAMCNT(5), 0x93);
    case 0x10: IO_W(&VRAMCNT(4), 0x83); break;
    }
    GX_VRAMCNT_SetLCDC_(data_021fcbd8[0]);
}

void GX_SetBankForClearImage(int bank) {
    data_021fcbd8[0] = (u16)((data_021fcbd8[0] | data_021fcbd8[6]) & ~bank);
    data_021fcbd8[6] = bank;
    switch (bank) {
    case 3: IO_W(&VRAMCNT(0), 0x93);
    case 2: IO_W(&VRAMCNT(1), 0x9b); IO_OR(&reg_GX_DISP3DCNT, 0x4000); break;
    case 12: IO_W(&VRAMCNT(2), 0x93);
    case 8: IO_W(&VRAMCNT(3), 0x9b); IO_OR(&reg_GX_DISP3DCNT, 0x4000); break;
    case 0: IO_AND(&reg_GX_DISP3DCNT, ~0x4000); break;
    case 1: IO_W(&VRAMCNT(0), 0x9b); IO_OR(&reg_GX_DISP3DCNT, 0x4000); break;
    case 4: IO_W(&VRAMCNT(2), 0x9b); IO_OR(&reg_GX_DISP3DCNT, 0x4000); break;
    }
    GX_VRAMCNT_SetLCDC_(data_021fcbd8[0]);
}
