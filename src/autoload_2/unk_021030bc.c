typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

static inline u32 MATH_CountLeadingZerosInline(u32 x)
{
    return x == 0 ? 32 : __builtin_clz(x);
}
static inline u32 MATH_ILog2(u32 x) { return 31 - MATH_CountLeadingZerosInline(x); }

typedef struct ObjShift { u8 w; u8 h; } ObjShift;
extern const ObjShift data_02135cb8[4][4];

static inline void GetOBJShift(s32 *pw, s32 *ph, s32 w, s32 h)
{
    const int ws = (w >= 8) ? 3 : MATH_ILog2(w);
    const int hs = (h >= 8) ? 3 : MATH_ILog2(h);
    const ObjShift *p = &data_02135cb8[hs][ws];
    *pw = p->w;
    *ph = p->h;
}

static inline u32 LowBits(u32 v, u32 mask) { return v & ~mask; }

u32 GetCharIndex1D(u32 x, u32 y, s32 w, s32 h, s32 sw, s32 sh)
{
    u32 base = 0;
    u32 bh;
    u32 bw;
    u32 wm;
    u32 hm;
    for (;;) {
        wm = ~0 << sw;
        hm = ~0 << sh;
        bw = w & wm;
        bh = h & hm;
        if (bh <= y) {
            base += w * bh;
            if (bw > x) {
                w = bw;
                y -= bh;
                h -= bh;
            } else {
                h -= bh;
                base += bw * h;
                x -= bw;
                y -= bh;
                w -= bw;
            }
        } else {
            u32 lm = ~hm;
            if (bw <= x) {
                base += bw * bh;
                h = bh;
                x -= bw;
                w -= bw;
            } else {
                base += bw * (y & hm);
                return base + ((x & wm) << sh) + ((y & lm) << sw) + LowBits(x, wm);
            }
        }
        GetOBJShift(&sw, &sh, w, h);
    }
}
