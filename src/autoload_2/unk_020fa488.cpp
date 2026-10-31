#include "gfx/SplReal.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/SplManager.h"
#include "gfx/SplRes.h"
#include "gfx/SplEmitterViews.h"
#include "gfx/SplTex.h"
#include "gfx/SplViews.h"
#include "gfx/SplNode.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_020fa398.h"
#include "proto/autoload_2/unk_020fa39c.h"
#include "proto/autoload_2/unk_020fa488.h"
#include "proto/autoload_2/unk_020fac28.h"
#include "proto/autoload_2/unk_021104ac.h"







struct Res {
#ifdef HOST64
    HdrW * p0;
    u8 p4[0x20];
    Blk14 * p14;
#else
    HdrW *p0;
    u8 p4[0x10];
    Blk14 *p14;
#endif
};




extern "C" {
void *MI_CpuFill8(void *p, u32 v, u32 n);
void spl_push_front(void *list, void *e);
void spl_gen_ptcl(void *e, void *l);
}













typedef u16 (*PosCb)(VecFx32 *, VecFx32);
typedef void (*SetFn)(s32, s32, s32, s32);
typedef void (*MkFn)(s32, s32, Mt *);

extern "C" {
extern s16 data_02135f44[];
extern MkFn data_0213bb9c[];
extern SetFn data_0213bb94[];
void MTX_Scale43_(Mt *m, s32 x, s32 y, s32 z);
void MTX_RotX43_(Mt *m, s32 s, s32 c);
void MTX_Concat43(Mt *a, Mt *b, Mt *ab);
}


static inline s32 FxMul(s32 a, s32 b) {
    return (s32)(((s64)a * b + 0x800) >> 12);
}

static inline u32 G3_PolygonAttr(u32 light, u32 mode, u32 cull, u32 id, u32 alpha, u32 misc) {
    return IO_W((volatile u32 *)0x040004a4, light | (mode << 4) | (cull << 6) | (id << 24) | (alpha << 16) | (misc << 8));
}

extern "C" {
void spl_draw_chld_pol(Mg2 *m, Nd *p, PosCb cb);
void spl_draw_pol(Mg2 *m, Nd *p, PosCb cb);
}


static inline void G3_Translate(s32 x, s32 y, s32 z) {
    IO_W((volatile u32 *)0x04000470, x);
    IO_W((volatile u32 *)0x04000470, y);
    IO_W((volatile u32 *)0x04000470, z);
}

extern "C" void spl_draw_pol(Mg2 *m, Nd *p, PosCb cb) {
    s32 alpha = (p->c46.a * (p->c46.b + 1)) >> 5;
    Mt mA;
    Mt mB;
    Mt mC;
    VecFx32 v;
    Rh *h;
    Mt mD;
    s32 idx;
    s32 x;
    s32 y;
    s32 r;
    u32 t = G3_PolygonAttr(m->w48, 0, 3, p->c46.id, alpha, 0);
    if (alpha == 0) return;
    idx = p->h32 >> 4;
    data_0213bb9c[m->cur->res->p0->k17](data_02135f44[idx * 2], data_02135f44[idx * 2 + 1], &mB);
    y = p->w48;
    x = FxMul(y, m->cur->res->p0->s48);
    switch (m->cur->res->p0->mode) {
        case 0:
            x = FxMul(x, p->s52);
            y = FxMul(y, p->s52);
            break;
        case 1:
            x = FxMul(x, p->s52);
            break;
        case 2:
            y = FxMul(y, p->s52);
            break;
    }
    MTX_Scale43_(&mC, x, y, y);
    MTX_Concat43(&mC, &mB, &mA);
    h = m->cur->res->p0;
    if (h->b23 == 0) {
        v.x = p->w8 + p->w56;
        v.y = p->w12 + p->w60;
        v.z = p->w16 + p->w64;
        r = cb(&v, v);
        G3_LoadMtx43((Mt *)m->mt);
    } else {
        v.x = p->w8 + p->w56 - h->w4;
        v.y = p->w12 + p->w60 - m->cur->res->p0->w8;
        v.z = p->w16 + p->w64 - m->cur->res->p0->w12;
        r = cb(&v, v);
        IO_W((volatile u32 *)0x04000454, 0);
        G3_Translate(m->cur->res->p0->w4, m->cur->res->p0->w8, m->cur->res->p0->w12);
        G3_MultMtx43((Mt *)m->mt);
    }
    G3_Translate(v.x, v.y, v.z);
    if (m->cur->res->p0->c80 & 0x10) {
        idx = r >> 4;
        MTX_RotX43_(&mD, data_02135f44[idx * 2], data_02135f44[idx * 2 + 1]);
        G3_MultMtx43(&mD);
    }
    G3_MultMtx43(&mA);
    {
        s32 dd = m->cur->h90;
        s32 cc = p->h54;
        IO_W((volatile u32 *)0x04000480, (u16)((((cc & 0x1f) * (dd & 0x1f)) >> 5) | (((cc & 0x3e0) * (dd & 0x3e0)) >> 15 << 5) | (((cc & 0x7c00) * (dd & 0x7c00)) >> 25 << 10)));
    }
    data_0213bb94[m->cur->res->p0->k19](m->cur->s96, m->cur->s98, m->cur->res->p0->s76, m->cur->res->p0->s78);
}

extern "C" void spl_draw_chld_pol(Mg2 *m, Nd *p, PosCb cb) {
    s32 alpha = (p->c46.a * (p->c46.b + 1)) >> 5;
    Mt mA;
    Mt mB;
    Mt mC;
    VecFx32 v;
    Rh *h;
    Mt mD;
    s32 idx;
    s32 x;
    s32 y;
    s32 r;
    u32 t = G3_PolygonAttr(m->w48, 0, 3, p->c46.id, alpha, 0);
    if (alpha == 0) return;
    idx = p->h32 >> 4;
    data_0213bb9c[m->cur->res->p14->k9](data_02135f44[idx * 2], data_02135f44[idx * 2 + 1], &mB);
    y = p->w48;
    x = FxMul(y, m->cur->res->p0->s48);
    switch (m->cur->res->p0->mode) {
        case 0:
            x = FxMul(x, p->s52);
            y = FxMul(y, p->s52);
            break;
        case 1:
            x = FxMul(x, p->s52);
            break;
        case 2:
            y = FxMul(y, p->s52);
            break;
    }
    MTX_Scale43_(&mC, x, y, y);
    MTX_Concat43(&mB, &mC, &mA);
    h = m->cur->res->p0;
    if (h->b23 == 0) {
        v.x = p->w8 + p->w56;
        v.y = p->w12 + p->w60;
        v.z = p->w16 + p->w64;
        r = cb(&v, v);
        G3_LoadMtx43((Mt *)m->mt);
    } else {
        v.x = p->w8 + p->w56 - h->w4;
        v.y = p->w12 + p->w60 - m->cur->res->p0->w8;
        v.z = p->w16 + p->w64 - m->cur->res->p0->w12;
        r = cb(&v, v);
        IO_W((volatile u32 *)0x04000454, 0);
        G3_Translate(m->cur->res->p0->w4, m->cur->res->p0->w8, m->cur->res->p0->w12);
        G3_MultMtx43((Mt *)m->mt);
    }
    G3_Translate(v.x, v.y, v.z);
    if (m->cur->res->p0->c80 & 0x10) {
        idx = r >> 4;
        MTX_RotX43_(&mD, data_02135f44[idx * 2], data_02135f44[idx * 2 + 1]);
        G3_MultMtx43(&mD);
    }
    G3_MultMtx43(&mA);
    {
        s32 dd = m->cur->h90;
        s32 cc = p->h54;
        IO_W((volatile u32 *)0x04000480, (u16)((((cc & 0x1f) * (dd & 0x1f)) >> 5) | (((cc & 0x3e0) * (dd & 0x3e0)) >> 15 << 5) | (((cc & 0x7c00) * (dd & 0x7c00)) >> 25 << 10)));
    }
    data_0213bb94[m->cur->res->p14->k11](m->cur->s100, m->cur->s102, 0, 0);
}

SetFn data_0213bb94[2] = {drawXYPlane, drawXZPlane};
MkFn data_0213bb9c[2] = {(MkFn)rotTypeY, (MkFn)rotTypeXYZ};
