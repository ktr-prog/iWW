#include "nitro/gxoam.h"

static inline u32 MATH_CountLeadingZerosInline(u32 x)
{
    return x == 0 ? 32 : __builtin_clz(x);
}
static inline u32 MATH_ILog2(u32 x) { return 31 - MATH_CountLeadingZerosInline(x); }

typedef struct ObjShift { u8 w; u8 h; } ObjShift;
extern const ObjShift data_02135cb8[4][4];
extern u32 OBJSizeToShape(const ObjShift *p);

static inline void G2_SetOBJPosition(GXOamAttr *oam, int x, int y)
{
    oam->attr01 = (oam->attr01 & ~0x01ff00ff) | ((u32)y & 0xff) | (((u32)x & 0x1ff) << 16);
}
static inline void G2_SetOBJShape(GXOamAttr *oam, u32 shape)
{
    oam->attr01 = (oam->attr01 & ~0xc000c000) | shape;
}
static inline void G2_SetOBJCharName(GXOamAttr *oam, int name)
{
    oam->attr2 = (u16)((oam->attr2 & ~0x3ff) | name);
}
static inline void G2_SetOBJColorMode(GXOamAttr *oam, int color)
{
    oam->attr01 = (oam->attr01 & ~0x2000) | (color << 13);
}

int NNS_G2dArrangeOBJ1D(GXOamAttr *oam, int areaWidth, int areaHeight, int x, int y, int color, int charName,
                        int vramMode)
{
    const int ws = (areaWidth >= 8) ? 3 : MATH_ILog2(areaWidth);
    const int hs = (areaHeight >= 8) ? 3 : MATH_ILog2(areaHeight);
    const ObjShift *p = &data_02135cb8[hs][ws];
    const int objWs = p->w;
    const int objHs = p->h;
    const u32 bw = areaWidth & (~0 << objWs);
    const u32 bh = areaHeight & (~0 << objHs);
    const int factor = (color == 0) ? 1 : 2;
    int usedObjs = 0;
    {
        const u32 shape = OBJSizeToShape(p);
        const int numX = areaWidth >> objWs;
        const int numY = areaHeight >> objHs;
        const int charStep = ((factor << objWs) << objHs) >> vramMode;
        int ox, oy;
        for (oy = 0; oy < numY; oy++) {
            const int py = y + ((oy << objHs) * 8);
            for (ox = 0; ox < numX; ox++) {
                const int px = x + ((ox << objWs) * 8);
                G2_SetOBJPosition(oam, px, py);
                G2_SetOBJShape(oam, shape);
                G2_SetOBJCharName(oam, charName);
                G2_SetOBJColorMode(oam, color);
                oam++;
                charName += charStep;
            }
        }
        usedObjs += numX * numY;
    }
    if (bw < areaWidth) {
        const int px = x + bw * 8;
        const int w = areaWidth - bw;
        const int n = NNS_G2dArrangeOBJ1D(oam, w, bh, px, y, color, charName, vramMode);
        oam += n;
        charName += (factor * w * bh) >> vramMode;
        usedObjs += n;
    }
    if (bh < areaHeight) {
        const int h = areaHeight - bh;
        const int n = NNS_G2dArrangeOBJ1D(oam, bw, h, x, y + bh * 8, color, charName, vramMode);
        oam += n;
        charName += (factor * bw * h) >> vramMode;
        usedObjs += n;
    }
    if (bw < areaWidth && bh < areaHeight) {
        const int n = NNS_G2dArrangeOBJ1D(oam, areaWidth - bw, areaHeight - bh, x + bw * 8, y + bh * 8, color,
                                          charName, vramMode);
        usedObjs += n;
    }
    return usedObjs;
}

const ObjShift data_02135cb8[4][4] = {
    {{0, 0}, {1, 0}, {2, 0}, {2, 0}},
    {{0, 1}, {1, 1}, {2, 1}, {2, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
    {{0, 2}, {1, 2}, {2, 3}, {3, 3}},
};
