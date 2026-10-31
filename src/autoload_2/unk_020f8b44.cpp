#include "gfx/SplReal.h"
#include "uptr.h"
#include "types.h"
#include "gfx/V3.h"
#include "gfx/SplEmitterViews.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_020f7a5c.h"
#include "proto/autoload_2/unk_020f8b44.h"
#include "proto/autoload_2/unk_0210c084.h"
#include "proto/autoload_2/unk_02111ccc.h"
#include "proto/autoload_2/unk_0211220c.h"



struct ResInfo {
    u32 pad0 : 14;
    u32 f14 : 1;
    u32 pad15 : 17;
    u32 w4;
    u32 w8;
    u32 wc;
    u8 pad10[0x22];
    u16 h32;
    u8 pad34[4];
    u16 h38;
};

struct Res {
#ifdef HOST64
    ResInfo * p0;
#else
    ResInfo *p0;
#endif
};

struct Fl {
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 pad : 27;
};

struct Fx3 {
    s32 x;
    s32 y;
    s32 z;
};

struct Entry {
#ifdef HOST64
    Entry * next;
    u8 p4[0x10];
    u32 w12;
    u8 hpad_0[0x4];
    uptr w16;
    u32 w20;
    u8 hpad_1[0x4];
    Res * res;
    Fl fl;
    s32 px;
    s32 py;
    s32 pz;
    u8 p2c[0xc];
    u16 h38;
    u8 p3a[0x2e];
    u32 pad68a : 16;
    u32 f16 : 3;
    u32 pad68b : 13;
#else
    Entry *next;
    u8 p4[8];
    u32 w12;
    u32 w16;
    u32 w20;
    Res *res;
    Fl fl;
    s32 px;
    s32 py;
    s32 pz;
    u8 p2c[0xc];
    u16 h38;
    u8 p3a[0x2e];
    u32 pad68a : 16;
    u32 f16 : 3;
    u32 pad68b : 13;
#endif
};

struct Mgr {
#ifdef HOST64
    uptr w0;
    Entry * act;
    u32 w8;
    u8 hpad_0[0x4];
    Entry * fr;
    u32 frCount;
    u8 hpad_1[0x4];
    SplRealPtclList freePtcl;
    u8 * tab;
    u8 p20[0x18];
    Entry * cur;
    s32 *w38;
#else
    u32 w0;
    Entry *act;
    u32 w8;
    Entry *fr;
    u32 frCount;
    SplRealPtclList freePtcl;
    u8 *tab;
    u8 p20[0x14];
    Entry *cur;
    s32 *w38;
#endif
};

struct EBits {
    u32 kind : 4;
    u32 pad : 13;
    u32 isref : 1;
    u32 idx : 8;
    u32 pad2 : 6;
};

struct SEnt {
    u32 w0;
    EBits b;
    u32 w8;
    u32 wc;
    u32 w16;
};

struct Slot {
#ifdef HOST64
    SEnt * e;
    u32 w4;
    u32 w8;
    u32 w12;
    u32 w16;
#else
    SEnt *e;
    u32 w4;
    u32 w8;
    u32 w12;
    u32 w16;
#endif
};

typedef u32 (*Cb)(u32, u32);

struct Fp {
#ifdef HOST64
    void *(*alloc)(u32);
    u8 p4[0x30];
    u8 * p1c;
    Slot * tab;
    u16 h24;
    u16 h26;
#else
    void *(*alloc)(u32);
    u8 p4[0x18];
    u8 *p1c;
    Slot *tab;
    u16 h24;
    u16 h26;
#endif
};


struct Item8 {
#ifdef HOST64
    void * fn;
    u8 * p4;
#else
    void *fn;
    u8 *p4;
#endif
};

struct Pool32 {
#ifdef HOST64
    u8 * p0;
    u8 * p4;
    u8 * p8;
    u8 * pc;
    u8 * p10;
    u8 * p14;
    Item8 * p18;
    u16 h1c;
    u16 pad1e;
    u8 hpad_0[0x4];
#else
    u8 *p0;
    u8 *p4;
    u8 *p8;
    u8 *pc;
    u8 *p10;
    u8 *p14;
    Item8 *p18;
    u16 h1c;
    u16 pad1e;
#endif
};

extern "C" {
void func_020f9690(Entry *e, void *list);
void spl_init(Entry *e, void *tab, void *v);
Entry *spl_pop_front(void *list);
void spl_push_front(void *list, Entry *e);
Entry *spl_del(void *list, Entry *e);
void spl_draw(Mgr *m, SplPosFn a);
void spl_calc(Mgr *m, Entry *e);
void spl_calc_gravity(void);
void spl_calc_random(void);
void spl_calc_magnet(void);
void spl_calc_spin(void);
void spl_calc_scfield(void);
void spl_calc_convergence(void);
void GX_LoadTexPltt(void *dst, u32 a, u32 n);
void GX_LoadTex(void *dst, u32 a, u32 n);
s32 SPL_LoadTexPlttByCallbackFunction(Fp *self, Cb cb);
u32 sAllocTexPalette(u32 a, u32 b);
s32 SPL_LoadTexByCallbackFunction(Fp *self, Cb cb);
u32 sAllocTex(u32 a, u32 b);
void *MI_CpuFill8(void *p, u32 v, u32 n);
}

extern "C" void SPL_Load(Fp *self, u8 *base) {
    s32 i;
    u32 off = 0;
    self->p1c = (u8 *)self->alloc(self->h24 * SPL_RES_SIZE);
    MI_CpuFill8(self->p1c, 0, self->h24 * SPL_RES_SIZE);
    for (i = 0; i < self->h24; i++) {
        Pool32 *p = (Pool32 *)(self->p1c + i * SPL_RES_SIZE);
        HdrBits h;
        p->p0 = base + off;
        off += 0x54;
        h = *(HdrBits *)p->p0;
        if (h.b8) {
            p->p4 = base + off;
            off += 12;
        } else {
            p->p4 = 0;
        }
        if (h.b9) {
            p->p8 = base + off;
            off += 12;
        } else {
            p->p8 = 0;
        }
        if (h.b10) {
            p->pc = base + off;
            off += 8;
        } else {
            p->pc = 0;
        }
        if (h.b11) {
            p->p10 = base + off;
            off += 12;
        } else {
            p->p10 = 0;
        }
        if (h.b16) {
            p->p14 = base + off;
            off += 20;
        } else {
            p->p14 = 0;
        }
        p->h1c = h.b24 + h.b25 + h.b26 + h.b27 + h.b28 + h.b29;
        if (p->h1c != 0) {
            Item8 *it = (Item8 *)self->alloc(p->h1c * SPL_FIELD_SIZE);
            p->p18 = it;
            it = p->p18;
            if (h.b24) {
                it->p4 = base + off;
                it->fn = (void *)spl_calc_gravity;
                off += 8;
                it++;
            }
            if (h.b25) {
                it->p4 = base + off;
                it->fn = (void *)spl_calc_random;
                off += 8;
                it++;
            }
            if (h.b26) {
                it->p4 = base + off;
                it->fn = (void *)spl_calc_magnet;
                off += 16;
                it++;
            }
            if (h.b27) {
                it->p4 = base + off;
                it->fn = (void *)spl_calc_spin;
                off += 4;
                it++;
            }
            if (h.b28) {
                it->p4 = base + off;
                it->fn = (void *)spl_calc_scfield;
                off += 8;
                it++;
            }
            if (h.b29) {
                it->p4 = base + off;
                it->fn = (void *)spl_calc_convergence;
                off += 16;
                it++;
            }
        } else {
            p->p18 = 0;
        }
    }
}

extern "C" s32 SPL_LoadTexByCallbackFunction(Fp *self, Cb cb) {
    s32 i;
    GX_BeginLoadTex();
    for (i = 0; i < self->h26; i++) {
        Slot *s = &self->tab[i];
        SEnt *e = s->e;
        if (e->b.isref != 0) {
            s->w4 = self->tab[e->b.idx].w4;
        } else {
            u32 r = cb(e->w8, e->b.kind == 5 ? 1 : 0);
            GX_LoadTex((u8 *)s->e + 32, r, e->w8);
            s->w4 = r;
        }
    }
    GX_EndLoadTex();
    return 1;
}

extern "C" s32 SPL_LoadTexPlttByCallbackFunction(Fp *self, Cb cb) {
    s32 i;
    GX_BeginLoadTexPltt();
    for (i = 0; i < self->h26; i++) {
        Slot *s = &self->tab[i];
        SEnt *e = s->e;
        u32 r = 0;
        if (e->w16 != 0) {
            r = cb(e->w16, e->b.kind == 2 ? 1 : 0);
            GX_LoadTexPltt((u8 *)s->e + e->wc, r, e->w16);
        }
        s->w8 = r;
    }
    GX_EndLoadTexPltt();
    return 1;
}

extern "C" s32 SPL_LoadTexByVRAMManager(Fp *self) {
    return SPL_LoadTexByCallbackFunction(self, sAllocTex);
}

extern "C" s32 SPL_LoadTexPlttByVRAMManager(Fp *self) {
    return SPL_LoadTexPlttByCallbackFunction(self, sAllocTexPalette);
}

extern "C" void SPL_Calc(Mgr *m) {
    Entry *e;
    for (e = m->act; e != 0;) {
        Entry *next;
        ResInfo *ri;
        ri = e->res->p0;
        next = e->next;
        if (e->fl.b4 == 0) {
            if (e->h38 >= ri->h32) {
                e->fl.b4 = 1;
                e->h38 = 0;
            }
        }
        if (e->fl.b2 == 0) {
            u32 t = e->f16;
            if (t == 0 || data_021f5c38 == t - 1) spl_calc(m, e);
        }
        if ((ri->f14 != 0 && ri->h38 != 0 && e->fl.b4 != 0 && e->h38 > ri->h38) || e->fl.b0 != 0) {
            if (e->w12 == 0 && e->w20 == 0) {
                spl_push_front(&m->fr, spl_del(&m->act, e));
            }
        }
        e = next;
    }
    data_021f5c38 += 1;
    if (data_021f5c38 > 1) data_021f5c38 = 0;
}

extern "C" void SPL_Draw(Mgr *m, s32 *viewMtx, SplPosFn cb) {
    Entry *e;
    IO_W((vu16 *)0x04000060, (u16)((IO_R((vu16 *)0x04000060) & ~0x3000) | 8));
    m->w38 = viewMtx;
    e = m->act;
    if (e == 0) return;
    do {
        m->cur = e;
        if (e->fl.b3 == 0) spl_draw(m, cb);
        e = e->next;
    } while (e != 0);
}

extern "C" Entry *SPL_Create(Mgr *m, s32 idx, void *p) {
    Entry *e = 0;
    if (m->fr != 0) {
        e = spl_pop_front(&m->fr);
        spl_init(e, m->tab + idx * SPL_RES_SIZE, p);
        spl_push_front(&m->act, e);
        if (e->res->p0->f14 != 0) e = 0;
    }
    return e;
}

extern "C" Entry *SPL_CreateWithInitialize(Mgr *m, u32 idx, void (*cb)(Entry *)) {
    Entry *e = 0;
    if (m->fr != 0) {
        Fx3 z = {0, 0, 0};
        e = spl_pop_front(&m->fr);
        spl_init(e, m->tab + idx * SPL_RES_SIZE, &z);
        if (cb != 0) cb(e);
        spl_push_front(&m->act, e);
        if (e->res->p0->f14 != 0) e = 0;
    }
    return e;
}

extern "C" void func_020f8b44(Mgr *m, Entry *e, Fx3 *v) {
    e->px = v->x + ((ResInfo *)e->res->p0)->w4;
    e->py = v->y + e->res->p0->w8;
    e->pz = v->z + e->res->p0->wc;
    func_020f9690(e, &m->freePtcl);
}

u16 data_021f5c38;

#ifdef HOST64
static_assert(__builtin_offsetof(Entry, next) == 0x0, "Entry.next");
static_assert(__builtin_offsetof(Entry, p4) == 0x8, "Entry.p4");
static_assert(__builtin_offsetof(Entry, w12) == 0x18, "Entry.w12");
static_assert(__builtin_offsetof(Entry, w16) == 0x20, "Entry.w16");
static_assert(__builtin_offsetof(Entry, w20) == 0x28, "Entry.w20");
static_assert(__builtin_offsetof(Entry, res) == 0x30, "Entry.res");
static_assert(__builtin_offsetof(Entry, fl) == 0x38, "Entry.fl");
static_assert(__builtin_offsetof(Entry, px) == 0x3c, "Entry.px");
static_assert(__builtin_offsetof(Entry, py) == 0x40, "Entry.py");
static_assert(__builtin_offsetof(Entry, pz) == 0x44, "Entry.pz");
static_assert(__builtin_offsetof(Entry, p2c) == 0x48, "Entry.p2c");
static_assert(__builtin_offsetof(Entry, h38) == 0x54, "Entry.h38");
static_assert(__builtin_offsetof(Entry, p3a) == 0x56, "Entry.p3a");
#endif

#ifdef HOST64
static_assert(__builtin_offsetof(Mgr, w0) == 0x0, "Mgr.w0");
static_assert(__builtin_offsetof(Mgr, act) == 0x8, "Mgr.act");
static_assert(__builtin_offsetof(Mgr, w8) == 0x10, "Mgr.w8");
static_assert(__builtin_offsetof(Mgr, fr) == 0x18, "Mgr.fr");
static_assert(__builtin_offsetof(Mgr, frCount) == 0x20, "Mgr.frCount");
static_assert(__builtin_offsetof(Mgr, freePtcl) == __builtin_offsetof(SplRealManager, freeParticles), "Mgr.freePtcl");
static_assert(__builtin_offsetof(Mgr, tab) == 0x38, "Mgr.tab");
static_assert(__builtin_offsetof(Mgr, p20) == 0x40, "Mgr.p20");
static_assert(__builtin_offsetof(Mgr, cur) == 0x58, "Mgr.cur");
static_assert(__builtin_offsetof(Mgr, w38) == 0x60, "Mgr.w38");
#endif

#ifdef HOST64
static_assert(__builtin_offsetof(Slot, e) == 0x0, "Slot.e");
static_assert(__builtin_offsetof(Slot, w4) == 0x8, "Slot.w4");
static_assert(__builtin_offsetof(Slot, w8) == 0xc, "Slot.w8");
static_assert(__builtin_offsetof(Slot, w12) == 0x10, "Slot.w12");
static_assert(__builtin_offsetof(Slot, w16) == 0x14, "Slot.w16");
#endif

#ifdef HOST64
static_assert(__builtin_offsetof(Item8, fn) == 0x0, "Item8.fn");
static_assert(__builtin_offsetof(Item8, p4) == 0x8, "Item8.p4");
#endif

#ifdef HOST64
static_assert(__builtin_offsetof(Pool32, p0) == 0x0, "Pool32.p0");
static_assert(__builtin_offsetof(Pool32, p4) == 0x8, "Pool32.p4");
static_assert(__builtin_offsetof(Pool32, p8) == 0x10, "Pool32.p8");
static_assert(__builtin_offsetof(Pool32, pc) == 0x18, "Pool32.pc");
static_assert(__builtin_offsetof(Pool32, p10) == 0x20, "Pool32.p10");
static_assert(__builtin_offsetof(Pool32, p14) == 0x28, "Pool32.p14");
static_assert(__builtin_offsetof(Pool32, p18) == 0x30, "Pool32.p18");
static_assert(__builtin_offsetof(Pool32, h1c) == 0x38, "Pool32.h1c");
static_assert(__builtin_offsetof(Pool32, pad1e) == 0x3a, "Pool32.pad1e");
#endif

#ifdef HOST64
static_assert(__builtin_offsetof(Res, p0) == 0x0, "Res.p0");
#endif

#ifdef HOST64
static_assert(__builtin_offsetof(Fp, alloc) == 0x0, "Fp.alloc");
static_assert(__builtin_offsetof(Fp, p4) == 0x8, "Fp.p4");
static_assert(__builtin_offsetof(Fp, p1c) == 0x38, "Fp.p1c");
static_assert(__builtin_offsetof(Fp, tab) == 0x40, "Fp.tab");
static_assert(__builtin_offsetof(Fp, h24) == 0x48, "Fp.h24");
static_assert(__builtin_offsetof(Fp, h26) == 0x4a, "Fp.h26");
#endif
