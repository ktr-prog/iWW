#include "types.h"
#include "proto/autoload_2/unk_020fe4b4.h"

extern "C" {

void OSi_UnlockVram(u32 a, u32 b);
void PXI_SetFifoRecvCallback(u32 a, void *b);
}

extern "C" void WvrReceiveCallback(u32 tag, u32 data) {
    void (*cb)(u32, u32) = data_021f5c4c;
    u32 arg = data_021f5c48;
    u32 lo = data & 0xff;
    u32 hi = data & 0xffff0000;
    switch (hi) {
    case 0x10000:
        if (lo == 7) {
            if (data_021f5c44 != 0) {
                if (data_021f5c40 != 0) {
                    OSi_UnlockVram(data_021f5c44, data_021f5c40);
                    data_021f5c44 = 0;
                }
            }
        }
        break;
    case 0x20000:
        if (lo == 0) {
            if (data_021f5c44 != 0) {
                if (data_021f5c40 != 0) {
                    OSi_UnlockVram(data_021f5c44, data_021f5c40);
                    data_021f5c44 = 0;
                }
            }
        }
        PXI_SetFifoRecvCallback(15, 0);
        break;
    }
    if (cb != 0) {
        data_021f5c4c = 0;
        data_021f5c48 = 0;
        cb(arg, lo);
    }
}

void (*data_021f5c4c)(u32, u32);
u32 data_021f5c48;
volatile u16 data_021f5c44;
volatile u16 data_021f5c40;
