typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;

void NNS_G2dMapScrToChar256x16Pltt(u16 *dst, s32 w, s32 h, s32 stride, s32 idx, s32 pal);

void NNS_G2dMapScrToCharText(u16 *scrn, s32 w, s32 h, s32 x, s32 y, s32 scrW, s32 idx, s32 pal) {
    if (scrW <= 32) {
        NNS_G2dMapScrToChar256x16Pltt(scrn + (scrW * y + x), w, h, scrW, idx, pal);
    } else {
        u16 pl;
        s32 xe, ye, xx;
        ye = y + h;
        xe = x + w;
        pl = (u16)(pal << 12);
        for (; y < ye; y++) {
            u16 *row;
            row = scrn + ((y < 32) ? y : y + 32) * 32;
            for (xx = x; xx < xe; xx++) {
                row[(xx < 32) ? xx : xx + 992] = pl | idx;
                idx++;
            }
        }
    }
}

void NNS_G2dMapScrToChar256x16Pltt(u16 *dst, s32 w, s32 h, s32 stride, s32 idx, s32 pal) {
    u16 pl = (u16)(pal << 12);
    s32 j, i;
    for (i = 0; i < h; i++) {
        u16 *p = dst;
        for (j = 0; j < w; j++) {
            *p++ = pl | idx++;
        }
        dst += stride;
    }
}

