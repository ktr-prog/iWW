#include "types.h"
#include "proto/main/unk_02057180.h"


u16 sTexDimSizes[8] = {0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400};

extern "C" u32 G3dTex_GetTexelCount(u32 v) {
    return sTexDimSizes[(v & 0x700000) >> 20] * sTexDimSizes[(v & 0x3800000) >> 23];
}

extern "C" u32 G3dTex_GetImageSize(u32 v) {
    u32 r = G3dTex_GetTexelCount(v);
    switch ((v & 0x1c000000) >> 26) {
    case 2:
        r >>= 2;
        break;
    case 3:
        r >>= 1;
        break;
    case 5:
        r >>= 2;
        break;
    case 7:
        r <<= 1;
        break;
    }
    return r;
}
