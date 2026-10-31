typedef unsigned char u8;
typedef unsigned int u32;

#define CHARACTER_WIDTH     8
#define CHARACTER_HEIGHT    8
#define MATH_ROUNDUP(x, base)   (((x) + ((base) - 1)) & ~((base) - 1))
#define MATH_ROUNDDOWN(x, base) ((x) & ~((base) - 1))

typedef struct NNSG2dCharCanvas {
    u8 *charBase;
    int areaWidth;
    int areaHeight;
    u8 dstBpp;
    u8 reserved[3];
    u32 param;
    void *drawGlyph;
    void *clear;
    void *clearArea;
} NNSG2dCharCanvas;

typedef union OBJ1DParam {
    u32 packed;
    struct {
        unsigned baseWidthShift : 8;
        unsigned baseHeightShift : 8;
    };
} OBJ1DParam;

u32 GetCharIndex1D(u32 cx, u32 cy, u32 areaWidth, u32 areaHeight, u32 objWidth, u32 objHeight);
void ClearChar(void *pChar, int x, int y, int w, int h, u32 cl8, int bpp);

static inline int GetCharacterSize(const NNSG2dCharCanvas *pCC)
{
    return CHARACTER_HEIGHT * CHARACTER_WIDTH * pCC->dstBpp / 8;
}

static inline u32 SpreadColor32(const NNSG2dCharCanvas *pCC, int cl)
{
    u32 val = (u32)cl;

    if (pCC->dstBpp == 4) {
        val = (val << 4) | val;
        val |= val << 8;
        val |= val << 16;
    } else {
        val = (val << 8) | val;
        val |= val << 16;
    }

    return val;
}

void ClearArea1D(const NNSG2dCharCanvas *pCC, int cl, int x, int y, int w, int h)
{
    int ix, iy;
    int pcx, pcy, pcw, pch;
    int cx, cy;
    const int xw = x + w;
    const int yh = y + h;
    u32 cl8;
    OBJ1DParam p;

    cl8 = SpreadColor32(pCC, cl);

    p.packed = pCC->param;

    {
        const int left = MATH_ROUNDDOWN(x, CHARACTER_WIDTH);
        const int top = MATH_ROUNDDOWN(y, CHARACTER_HEIGHT);
        const int right = MATH_ROUNDUP(xw, CHARACTER_WIDTH);
        const int bottom = MATH_ROUNDUP(yh, CHARACTER_HEIGHT);

        const int areaWidth = pCC->areaWidth;
        const int areaHeight = pCC->areaHeight;
        const int baseWidthShift = (int)p.baseWidthShift;
        const int baseHeightShift = (int)p.baseHeightShift;

        const int charSize = GetCharacterSize(pCC);
        const int charBaseLineOffset = (int)pCC->param * charSize;
        const int bpp = pCC->dstBpp;
        const int cx_base = left / CHARACTER_WIDTH;
        u8 *const pCharBase = pCC->charBase;
        u8 *pChar;

        cy = top / CHARACTER_HEIGHT;

        for (iy = top; iy < bottom; iy += CHARACTER_HEIGHT) {
            pcy = (iy < y) ? y - iy : 0;
            pch = ((yh - iy > CHARACTER_HEIGHT) ? CHARACTER_HEIGHT : yh - iy) - pcy;
            pChar = pCharBase;

            cx = cx_base;
            for (ix = left; ix < right; ix += CHARACTER_WIDTH) {
                const u32 iChar = GetCharIndex1D((u32)cx, (u32)cy, (u32)areaWidth, (u32)areaHeight,
                                                 (u32)baseWidthShift, (u32)baseHeightShift);
                pcx = (ix < x) ? x - ix : 0;
                pcw = ((xw - ix > CHARACTER_WIDTH) ? CHARACTER_WIDTH : xw - ix) - pcx;

                pChar = pCharBase + iChar * charSize;

                ClearChar(pChar, pcx, pcy, pcw, pch, cl8, bpp);
                cx++;
            }
            cy++;
        }
    }
}
