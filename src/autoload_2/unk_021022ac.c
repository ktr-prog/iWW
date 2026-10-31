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

typedef union CharCanvasParam { u32 u; ObjShift objShift; } CharCanvasParam;

struct CharCanvas;
extern void DrawGlyph1D(void);
extern void ClearContinuous(void);
extern void ClearArea1D(void);
extern void InitCharCanvas(struct CharCanvas *cc, u8 *charBase, s32 w, s32 h, s32 mode, void (*dg)(void),
                           void (*cl)(void), void (*ca)(void), CharCanvasParam param);

void NNS_G2dCharCanvasInitForOBJ1D(struct CharCanvas *cc, u8 *charBase, s32 w, s32 h, s32 mode)
{
    CharCanvasParam param;
    const s32 ws = (w >= 8) ? 3 : MATH_ILog2(w);
    const s32 hs = (h >= 8) ? 3 : MATH_ILog2(h);
    {
        const ObjShift *p = &data_02135cb8[hs][ws];
        param.objShift.w = p->w;
        param.objShift.h = p->h;
    }
    InitCharCanvas(cc, charBase, w, h, mode, DrawGlyph1D, ClearContinuous, ClearArea1D, param);
}
