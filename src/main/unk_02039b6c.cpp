#include "types.h"

extern "C" {
void MI_CpuCopy8(void *src, void *dst, u32 size);
void DateTime_SubHours(void *p, u32 n);
u32 Date_GetWeekday(u32 a, u32 b, u32 c);
}

extern "C" void RecycleBin_Construct() {}

extern "C" void RecycleBin_Destruct() {}

extern "C" void RecycleBin_Clear(u16 *p) {
    for (s32 i = 0; i < 15; i++) {
        p[i] = 0xfff1;
    }
}

extern "C" void RecycleBin_AdvanceDays(u16 *arr, void *src, s32 n) {
    if (n != 0) {
        if (n >= 4) {
            RecycleBin_Clear(arr);
        } else {
            u32 b[2];
            b[0] = 0;
            b[1] = 0;
            MI_CpuCopy8(src, b, 8);
            DateTime_SubHours(b, 6);
            switch (Date_GetWeekday(((u8 *)b)[5], ((u8 *)b)[4], ((u8 *)b)[3])) {
            case 0:
                break;
            case 1:
            case 4:
                RecycleBin_Clear(arr);
                break;
            case 2:
            case 5:
                if (n >= 2) {
                    RecycleBin_Clear(arr);
                }
                break;
            case 3:
            case 6:
                if (n >= 3) {
                    RecycleBin_Clear(arr);
                }
                break;
            }
        }
    }
}
