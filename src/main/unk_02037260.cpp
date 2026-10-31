#include "types.h"
#include "proto/main/unk_02037260.h"

extern "C" u32 AcreAttr_GetType(u32 i);

extern const u32 sAcreTypeAttrs[0x37];

const u32 sAcreTypeAttrs[0x37] = {
    0x20,    0x20,    0x1020,  0x40,    0x48,    0x80,    0x88,    0x60,    0xa0,    0,       0x400,   1,
    0x800,   0x200,   2,       0x9000,  0x12000, 0x44000, 0x28000, 0x21000, 0x81000, 0x1000,  0x2000,  0x4000,
    0x8000,  0x10000, 0x20000, 0x40000, 0x1004,  0x2004,  0x4004,  0x8004,  0x10004, 0x20004, 0x40004, 0x1100,
    0x2100,  0x4100,  0x8100,  0x10100, 0x20100, 0x40100, 8,       0x1008,  0x8008,  0x10008, 0x20008, 0x40008,
    0x100c,  0x800c,  0x1000c, 0x2000c, 0x4000c, 0x10,    0,
};

extern "C" u32 AcreType_FindByAttr(u32 v) {
    const u32 *p = sAcreTypeAttrs;
    u32 i;
    for (i = 0; i < 0x37; i++) {
        if (v == *p++) {
            return i;
        }
    }
    return 0x36;
}


extern "C" u32 Acre_GetAttr(u32 x) {
    return AcreType_GetAttr(AcreAttr_GetType(x));
}

extern "C" u32 AcreType_GetAttr(s32 i) {
    if (i < 0x37) {
        return sAcreTypeAttrs[i];
    }
    return 0;
}

extern "C" u8 AcreType_CountRiverBits(u32 x) {
    u32 m = AcreType_GetAttr(x);
    if (m & 0x7f000) {
        u8 n = 0;
        if (m & 0x1000) n++;
        if (m & 0x2000) n++;
        if (m & 0x4000) n++;
        if (m & 0x8000) n++;
        if (m & 0x10000) n++;
        if (m & 0x20000) n++;
        if (m & 0x40000) n++;
        return n;
    }
    return 0;
}
