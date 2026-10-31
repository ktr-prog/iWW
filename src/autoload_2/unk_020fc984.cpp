#include "ds_div.h"
#include "gfx/SplReal.h"
#include "types.h"
#include "gfx/SplPtclTypes.h"
#include "gfx/SplParticleViews.h"
#include "gfx/VecFx32.h"
#include "gfx/V3.h"
#include "gfx/SplTex.h"
#include "gfx/MagF.h"
#include "gfx/P.h"
#include "nitro/mtx.h"
#include "gfx/SplEmitterE.h"

struct P;







struct Res {
#ifdef HOST64
    Hdr * hdr;
    u8 p4[0x8];
    Tex * p8;
    u8 pc[0x8];
    Tab * p10;
#else
    Hdr *hdr;
    u8 p4[4];
    Tex *p8;
    u8 pc[4];
    Tab *p10;
#endif
};









extern "C" {
extern u32 data_021f5c3c;
extern const s16 data_02135f44[];
extern "C" s16 data_0213bba4[2];
s16 data_0213bba4[2] = {0, 0x1000};
extern u16 data_021f5c40;
extern u16 data_021f5c44;
extern u32 data_021f5c48;
extern void (*data_021f5c4c)(u32, u32);

void VEC_Fx16CrossProduct(const VecFx16 *a, const VecFx16 *b, VecFx16 *out);
s32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
void VEC_Fx16Normalize(const VecFx16 *src, VecFx16 *dst);
s32 VEC_Fx16DotProduct(const VecFx16 *a, const VecFx16 *b);
void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
void MTX_RotX33_(MtxFx33 *m, s32 s, s32 c);
void MTX_RotY33_(MtxFx33 *m, s32 s, s32 c);
void MTX_RotZ33_(MtxFx33 *m, s32 s, s32 c);
void MTX_MultVec33(const VecFx32 *v, const MtxFx33 *m, VecFx32 *dst);
u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 old);
void OSi_UnlockVram(u32 a, u32 b);
s32 OSi_TryLockVram(u32 a, u32 b);
void PXI_Init(void);
s32 PXI_IsCallbackReady(u32 a, u32 b);
void PXI_SetFifoRecvCallback(u32 a, void *b);
s32 PXI_SendWordByFifo(u32 a, u32 b, u32 c);
s32 OS_GetLockID(void);
void WvrDummyAsyncCallback(u32 a, u32 b);
void WvrReceiveCallback(u32 a, u32 b);
void spl_rndm_get_arb_vec_xyz(VecFx32 *v);
void spl_rndm_get_arb_vec_xy(VecFx32 *v);
void spl_push_front(PList *l, P *n);
P *spl_pop_front(PList *l);
void spl_set_cross_to_axis(E *e);
void spl_set_circle_axis(VecFx32 *out, const VecFx32 *in, E *e);
}

static inline s32 FX_Mul(s32 a, s32 b) {
    return (s32)(((s64)a * b + 0x800) >> 12);
}

#define SIN_IDX(i) (data_02135f44[((i) >> 4) * 2])
#define COS_IDX(i) (data_02135f44[((i) >> 4) * 2 + 1])

#define LCG() (data_021f5c3c = data_021f5c3c * 0x5eedf715 + 0x1b0cb173)

extern "C" void WvrDummyAsyncCallback(u32 a, u32 b) {
}

extern "C" void spl_rndm_get_arb_vec_xyz(VecFx32 *v) {
    data_021f5c3c = data_021f5c3c * 0x5eedf715 + 0x1b0cb173;
    v->x = (s32)data_021f5c3c >> 8;
    data_021f5c3c = data_021f5c3c * 0x5eedf715 + 0x1b0cb173;
    v->y = (s32)data_021f5c3c >> 8;
    data_021f5c3c = data_021f5c3c * 0x5eedf715 + 0x1b0cb173;
    v->z = (s32)data_021f5c3c >> 8;
    VEC_Normalize(v, v);
}

extern "C" void spl_rndm_get_arb_vec_xy(VecFx32 *v) {
    data_021f5c3c = data_021f5c3c * 0x5eedf715 + 0x1b0cb173;
    v->x = (s32)data_021f5c3c >> 8;
    data_021f5c3c = data_021f5c3c * 0x5eedf715 + 0x1b0cb173;
    v->y = (s32)data_021f5c3c >> 8;
    v->z = 0;
    VEC_Normalize(v, v);
}

extern "C" void spl_push_front(PList *l, P *n) {
    if (l->head == 0) {
        l->head = n;
        n->next = 0;
        n->prev = n->next;
    } else {
        n->next = l->head;
        n->prev = 0;
        l->head->prev = n;
        l->head = n;
    }
    l->count++;
}

extern "C" P *spl_pop_front(PList *l) {
    P *r = 0;
    P *n = l->head;
    if (n != 0) {
        r = n;
        l->head = n->next;
        if (l->head != 0) {
            n->next->prev = 0;
        }
        l->count--;
    }
    return r;
}

extern "C" P *spl_del(PList *l, P *n) {
    if (n->next == 0) {
        if (l->head == n) {
            l->head = 0;
        } else {
            n->prev->next = 0;
        }
    } else {
        if (l->head == n) {
            l->head = n->next;
            l->head->prev = 0;
        } else {
            n->next->prev = n->prev;
            n->prev->next = n->next;
        }
    }
    l->count--;
    return n;
}

extern "C" void spl_calc_gravity(GravF *f, P *p, VecFx32 *acc) {
    acc->x += f->x;
    acc->y += f->y;
    acc->z += f->z;
}

extern "C" void spl_calc_random(RandF *f, P *p, VecFx32 *acc) {
    if (DS_MOD(p->age, f->intv) != 0) {
        return;
    }
    data_021f5c3c = data_021f5c3c * 0x5eedf715 + 0x1b0cb173;
    acc->x += (f->x * (s32)(data_021f5c3c >> 23) - (f->x << 8)) >> 8;
    data_021f5c3c = data_021f5c3c * 0x5eedf715 + 0x1b0cb173;
    acc->y += (f->y * (s32)(data_021f5c3c >> 23) - (f->y << 8)) >> 8;
    data_021f5c3c = data_021f5c3c * 0x5eedf715 + 0x1b0cb173;
    acc->z += (f->z * (s32)(data_021f5c3c >> 23) - (f->z << 8)) >> 8;
}

extern "C" void spl_calc_magnet(MagF *f, P *p, VecFx32 *acc) {
    acc->x += (f->force * (f->x - p->pos.x - p->vel.x)) >> 12;
    acc->y += (f->force * (f->y - p->pos.y - p->vel.y)) >> 12;
    acc->z += (f->force * (f->z - p->pos.z - p->vel.z)) >> 12;
}

extern "C" void spl_calc_spin(SpinF *f, P *p, VecFx32 *acc) {
    MtxFx33 m;
    switch (f->axis) {
    case 0:
        MTX_RotX33_(&m, SIN_IDX(f->angle), COS_IDX(f->angle));
        break;
    case 1:
        MTX_RotY33_(&m, SIN_IDX(f->angle), COS_IDX(f->angle));
        break;
    case 2:
        MTX_RotZ33_(&m, SIN_IDX(f->angle), COS_IDX(f->angle));
        break;
    }
    MTX_MultVec33(&p->pos, &m, &p->pos);
}

extern "C" void spl_calc_scfield(CollF *f, P *p, VecFx32 *acc, E *e) {
    s32 y = f->y;
    if (e->w5c != (s32)0x80000000) {
        y = e->w5c;
    }
    s32 a;
    switch (f->type) {
    case 0:
        a = p->epos.y;
        if (a < y) {
            if (a + p->pos.y > y) {
                p->pos.y = y - a;
                p->age = p->life;
                return;
            }
        }
        if (a < y) {
            return;
        }
        if (a + p->pos.y < y) {
            p->pos.y = y - a;
            p->age = p->life;
        }
        return;
    case 1:
        a = p->epos.y;
        if (a < y) {
            if (a + p->pos.y > y) {
                p->pos.y = y - a;
                p->vel.y = -FX_Mul(p->vel.y, f->coef);
                return;
            }
        }
        if (a < y) {
            return;
        }
        if (a + p->pos.y < y) {
            p->pos.y = y - a;
            p->vel.y = -FX_Mul(p->vel.y, f->coef);
        }
        return;
    }
}

extern "C" void spl_calc_convergence(ConvF *f, P *p, VecFx32 *acc) {
    p->pos.x += FX_Mul(f->coef, f->x - p->pos.x);
    p->pos.y += FX_Mul(f->coef, f->y - p->pos.y);
    p->pos.z += FX_Mul(f->coef, f->z - p->pos.z);
}

extern "C" void spl_scl_in_out(P *p, Ctx *c, s32 t) {
    AnimRec *r = c->rec4;
    s32 t1 = r->t1;
    s32 t2 = r->t2;
    if (t < t1) {
        p->s34 = r->s0 + DS_DIV((t * (r->s2 - r->s0)), t1);
        return;
    }
    if (t < t2) {
        p->s34 = r->s2;
        return;
    }
    p->s34 = r->s4 + DS_DIV(((t - 255) * (r->s4 - r->s2)), (255 - t2));
}

extern "C" void spl_clr_in_out(P *p, Ctx *c, s32 t) {
    ColRec *r = c->rec8;
    Hdr *h = c->hdr;
    s32 t1 = r->b4;
    s32 t2 = r->b5;
    s32 t3 = r->b6;
    if (t < t1) {
        p->col = r->c0;
        return;
    }
    if (t < t2) {
        u16 A = h->col;
        u16 B = r->c0;
        s32 ar = A & 31;
        s32 br = B & 31;
        s32 ag = (A >> 5) & 31;
        s32 bg = (B >> 5) & 31;
        s32 ab = (A >> 10) & 31;
        s32 bb = (B >> 10) & 31;
        if (r->f2 == 0) {
            p->col = ar | (ag << 5) | (ab << 10);
            return;
        }
        s32 d = t2 - t1;
        s32 u = t - t1;
        p->col = (br + DS_DIV((u * (ar - br)), d)) | ((bg + DS_DIV((u * (ag - bg)), d)) << 5) | ((bb + DS_DIV((u * (ab - bb)), d)) << 10);
        return;
    }
    if (t < t3) {
        u16 C = r->c2;
        u16 A = h->col;
        s32 ar = A & 31;
        s32 cr = C & 31;
        s32 ag = (A >> 5) & 31;
        s32 cg = (C >> 5) & 31;
        s32 ab = (A >> 10) & 31;
        s32 cb = (C >> 10) & 31;
        if (r->f2 == 0) {
            p->col = cr | (cg << 5) | (cb << 10);
            return;
        }
        s32 d = t3 - t2;
        s32 u = t - t2;
        p->col = (ar + DS_DIV((u * (cr - ar)), d)) | ((ag + DS_DIV((u * (cg - ag)), d)) << 5) | ((ab + DS_DIV((u * (cb - ab)), d)) << 10);
        return;
    }
    p->col = r->c2;
}

extern "C" void spl_alp_in_out(P *p, Ctx *c, s32 t) {
    AlphaRec *r = c->recc;
    s32 t1 = r->t1;
    s32 t2 = r->t2;
    s32 v;
    if (t < t1) {
        v = DS_DIV((t * (r->c.g - r->c.r)), t1) + r->c.r;
    } else if (t < t2) {
        v = r->c.g;
    } else {
        v = DS_DIV(((t - 255) * (r->c.b - r->c.g)), (255 - t2)) + r->c.b;
    }
    data_021f5c3c = data_021f5c3c * 0x5eedf715 + 0x1b0cb173;
    p->fl.alpha = (u16)((v * (255 - ((r->b2 * (s32)(data_021f5c3c >> 24)) >> 8))) >> 8);
}

extern "C" void spl_tex_ptn_anm(P *p, Ctx *c, s32 t) {
    Tab *a = c->rec10;
    s32 i;
    for (i = 0; i < a->x.b.n; i++) {
        if (t < (i + 1) * a->x.b.step) {
            p->b2c = a->v[i];
            return;
        }
    }
}

extern "C" void spl_chld_scl_out(P *p, Ctx *c, s32 t) {
    s32 s = c->rec14->sc;
    p->s34 = s + ((s - 0x1000) * (t - 255)) / 255;
}

extern "C" void spl_chld_alp_out(P *p, void *x, s32 t) {
    p->fl.alpha = (u16)(((255 - t) * 31) / 255);
}

extern "C" void spl_set_cross_to_axis(E *e) {
    VecFx16 a;
    a.x = data_0213bba4[0];
    a.y = data_0213bba4[1];
    a.z = 0;
    VecFx16 b;
    switch (e->res->hdr->f.axis) {
    case 2:
        b.x = 0x1000;
        b.y = 0;
        b.z = 0;
        break;
    case 1:
        b.x = 0;
        b.y = 0x1000;
        b.z = 0;
        break;
    case 0:
        b.x = 0;
        b.y = 0;
        b.z = 0x1000;
        break;
    default:
        VEC_Fx16Normalize(&e->dir, &b);
        break;
    }
    s32 d = VEC_Fx16DotProduct(&a, &b);
    if (d == 0x1000 || d == -0x1000) {
        a.x = 0x1000;
        a.y = 0;
        a.z = 0;
    }
    e->ax1.x = FX_Mul(b.y, a.z) - FX_Mul(b.z, a.y);
    e->ax1.y = FX_Mul(b.z, a.x) - FX_Mul(b.x, a.z);
    e->ax1.z = FX_Mul(b.x, a.y) - FX_Mul(b.y, a.x);
    e->ax2.x = FX_Mul(b.y, e->ax1.z) - FX_Mul(b.z, e->ax1.y);
    e->ax2.y = FX_Mul(b.z, e->ax1.x) - FX_Mul(b.x, e->ax1.z);
    e->ax2.z = FX_Mul(b.x, e->ax1.y) - FX_Mul(b.y, e->ax1.x);
    VEC_Fx16Normalize(&e->ax1, &e->ax1);
    VEC_Fx16Normalize(&e->ax2, &e->ax2);
}

extern "C" void spl_set_circle_axis(VecFx32 *out, const VecFx32 *in, E *e) {
    VecFx16 c;
    VEC_Fx16CrossProduct(&e->ax1, &e->ax2, &c);
    VEC_Fx16Normalize(&c, &c);
    out->x = FX_Mul(in->z, c.x) + (FX_Mul(in->x, e->ax1.x) + FX_Mul(in->y, e->ax2.x));
    out->y = FX_Mul(in->z, c.y) + (FX_Mul(in->x, e->ax1.y) + FX_Mul(in->y, e->ax2.y));
    out->z = FX_Mul(in->z, c.z) + (FX_Mul(in->x, e->ax1.z) + FX_Mul(in->y, e->ax2.z));
}

extern "C" void spl_gen_ptcl(E *e, PList *freeList) {
    Res *res = e->res;
    Hdr *h = res->hdr;
    s32 i;
    s32 sum = h->rate + e->phase;
    e->phase = sum & 0xfff;
    s32 count = sum >> 12;
    u32 t = h->f.type;
    if (t == 2 || t == 3 || (u32)(t - 5) <= 4) {
        spl_set_cross_to_axis(e);
    }
    i = 0;
    if (count <= 0) {
        return;
    }
    s32 sa, sb;
    s32 ang = 0;
    do {
        P *p = spl_pop_front(freeList);
        if (p == 0) {
            return;
        }
        spl_push_front(&e->list, p);
        switch (h->f.type) {
        case 0:
            p->pos.x = p->pos.y = p->pos.z = 0;
            break;
        case 1:
            spl_rndm_get_arb_vec_xyz(&p->pos);
            p->pos.x = FX_Mul(p->pos.x, e->radius);
            p->pos.y = FX_Mul(p->pos.y, e->radius);
            p->pos.z = FX_Mul(p->pos.z, e->radius);
            break;
        case 2: {
            VecFx32 v;
            spl_rndm_get_arb_vec_xy(&v);
            v.x = FX_Mul(v.x, e->radius);
            v.y = FX_Mul(v.y, e->radius);
            v.z = 0;
            spl_set_circle_axis(&p->pos, &v, e);
            break;
        }
        case 3: {
            VecFx32 v;
            s32 q = DS_DIV(ang, count);
            ang += 0x10000;
            v.x = FX_Mul(SIN_IDX(q), e->radius);
            v.y = FX_Mul(COS_IDX(q), e->radius);
            v.z = 0;
            spl_set_circle_axis(&p->pos, &v, e);
            break;
        }
        case 4: {
            spl_rndm_get_arb_vec_xyz(&p->pos);
            LCG();
            p->pos.x = FX_Mul(FX_Mul(p->pos.x, e->radius), ((((s32)(data_021f5c3c >> 23) << 12) - 0x100000) >> 8));
            LCG();
            p->pos.y = FX_Mul(FX_Mul(p->pos.y, e->radius), ((((s32)(data_021f5c3c >> 23) << 12) - 0x100000) >> 8));
            LCG();
            p->pos.z = FX_Mul(FX_Mul(p->pos.z, e->radius), ((((s32)(data_021f5c3c >> 23) << 12) - 0x100000) >> 8));
            break;
        }
        case 5: {
            VecFx32 v;
            spl_rndm_get_arb_vec_xy(&v);
            LCG();
            v.x = FX_Mul(FX_Mul(v.x, e->radius), ((((s32)(data_021f5c3c >> 23) << 12) - 0x100000) >> 8));
            LCG();
            v.y = FX_Mul(FX_Mul(v.y, e->radius), ((((s32)(data_021f5c3c >> 23) << 12) - 0x100000) >> 8));
            spl_set_circle_axis(&p->pos, &v, e);
            break;
        }
        case 8: {
            VecFx16 c;
            VecFx32 w;
            spl_rndm_get_arb_vec_xyz(&p->pos);
            VEC_Fx16CrossProduct(&e->ax1, &e->ax2, &c);
            w.x = c.x;
            w.y = c.y;
            w.z = c.z;
            if (VEC_DotProduct(&w, &p->pos) <= 0) {
                p->pos.x = -p->pos.x;
                p->pos.y = -p->pos.y;
                p->pos.z = -p->pos.z;
            }
            p->pos.x = FX_Mul(p->pos.x, e->radius);
            p->pos.y = FX_Mul(p->pos.y, e->radius);
            p->pos.z = FX_Mul(p->pos.z, e->radius);
            break;
        }
        case 9: {
            VecFx16 c;
            VecFx32 w;
            spl_rndm_get_arb_vec_xyz(&p->pos);
            VEC_Fx16CrossProduct(&e->ax1, &e->ax2, &c);
            w.x = c.x;
            w.y = c.y;
            w.z = c.z;
            if (VEC_DotProduct(&w, &p->pos) < 0) {
                p->pos.x = -p->pos.x;
                p->pos.y = -p->pos.y;
                p->pos.z = -p->pos.z;
            }
            LCG();
            p->pos.x = FX_Mul(FX_Mul(p->pos.x, e->radius), ((((s32)(data_021f5c3c >> 23) << 12) - 0x100000) >> 9) + 0x800);
            LCG();
            p->pos.y = FX_Mul(FX_Mul(p->pos.y, e->radius), ((((s32)(data_021f5c3c >> 23) << 12) - 0x100000) >> 9) + 0x800);
            LCG();
            p->pos.z = FX_Mul(FX_Mul(p->pos.z, e->radius), ((((s32)(data_021f5c3c >> 23) << 12) - 0x100000) >> 9) + 0x800);
            break;
        }
        case 6: {
            VecFx32 v;
            spl_rndm_get_arb_vec_xy(&p->vel);
            v.x = FX_Mul(p->vel.x, e->radius);
            v.y = FX_Mul(p->vel.y, e->radius);
            LCG();
            v.z = (e->len * (s32)(data_021f5c3c >> 23) - (e->len << 8)) >> 8;
            spl_set_circle_axis(&p->pos, &v, e);
            break;
        }
        case 7: {
            VecFx32 v;
            spl_rndm_get_arb_vec_xy(&p->vel);
            LCG();
            v.x = FX_Mul(FX_Mul(p->vel.x, e->radius), ((((s32)(data_021f5c3c >> 23) << 12) - 0x100000) >> 8));
            LCG();
            v.y = FX_Mul(FX_Mul(p->vel.y, e->radius), ((((s32)(data_021f5c3c >> 23) << 12) - 0x100000) >> 8));
            LCG();
            v.z = (e->len * (s32)(data_021f5c3c >> 23) - (e->len << 8)) >> 8;
            spl_set_circle_axis(&p->pos, &v, e);
            break;
        }
        }
        LCG();
        sa = (e->w4c * (h->b3e + 255 - ((h->b3e * (s32)(data_021f5c3c >> 24)) >> 7))) >> 8;
        LCG();
        sb = (e->w50 * (h->b3e + 255 - ((h->b3e * (s32)(data_021f5c3c >> 24)) >> 7))) >> 8;
        VecFx32 dir;
        if (h->f.type == 6) {
            VecFx32 w;
            w.x = FX_Mul(p->vel.x, e->ax1.x) + FX_Mul(p->vel.y, e->ax2.x);
            w.y = FX_Mul(p->vel.x, e->ax1.y) + FX_Mul(p->vel.y, e->ax2.y);
            w.z = FX_Mul(p->vel.x, e->ax1.z) + FX_Mul(p->vel.y, e->ax2.z);
            VEC_Normalize(&w, &dir);
        } else if (p->pos.x == 0 && p->pos.y == 0 && p->pos.z == 0) {
            spl_rndm_get_arb_vec_xyz(&dir);
        } else {
            VEC_Normalize(&p->pos, &dir);
        }
        V3Arr *src = (V3Arr *)&e->pos;
        V3Arr *dst = (V3Arr *)&p->epos;
        p->vel.x = FX_Mul(dir.x, sa) + FX_Mul(e->dir.x, sb);
        p->vel.y = FX_Mul(dir.y, sa) + FX_Mul(e->dir.y, sb);
        p->vel.z = FX_Mul(dir.z, sa) + FX_Mul(e->dir.z, sb);
        *dst = *src;
        LCG();
        p->w30 = (e->w54 * (h->b3c + 255 - ((h->b3c * (s32)(data_021f5c3c >> 24)) >> 7))) >> 8;
        p->s34 = 0x1000;
        if (h->f.f9 && res->p8->b0) {
            LCG();
            u32 r = data_021f5c3c >> 20;
            u16 cols[3];
            Tex *tx = res->p8;
            cols[0] = tx->c0;
            cols[1] = h->col;
            cols[2] = tx->c1;
            p->col = cols[r % 3];
        } else {
            p->col = h->col;
        }
        p->fl.col = e->b69;
        p->fl.alpha = 31;
        if (h->f.f13) {
            LCG();
            p->rot0 = data_021f5c3c;
        } else {
            p->rot0 = 0;
        }
        if (!h->f.f12) {
            p->rot1 = 0;
        } else {
            LCG();
            s32 d = h->s36 - h->s34;
            s32 r = data_021f5c3c >> 20;
            p->rot1 = (u32)(d * r + (h->s34 << 12)) >> 12;
        }
        LCG();
        p->life = ((e->h58 * (255 - ((h->b3d * (s32)(data_021f5c3c >> 24)) >> 8))) >> 8) + 1;
        p->age = 0;
        if (h->f.f11 && res->p10->x.bf.f16) {
            LCG();
            Tab *tb = res->p10;
            p->b2c = tb->v[DS_UMOD((data_021f5c3c >> 20), tb->x.b.n)];
        } else if (h->f.f11 && !res->p10->x.bf.f16) {
            p->b2c = res->p10->v[0];
        } else {
            p->b2c = h->b43;
        }
        p->h28 = DS_DIV(0xffff, res->hdr->b44);
        p->h2a = DS_DIV(0xffff, p->life);
        p->b2d = 0;
        if (h->f.f20) {
            LCG();
            p->b2d = data_021f5c3c >> 24;
        }
        i++;
    } while (i < count);
}

u32 data_021f5c3c;

#ifdef HOST64
static_assert(__builtin_offsetof(Res, hdr) == 0x0, "Res.hdr");
static_assert(__builtin_offsetof(Res, p4) == 0x8, "Res.p4");
static_assert(__builtin_offsetof(Res, p8) == 0x10, "Res.p8");
static_assert(__builtin_offsetof(Res, pc) == 0x18, "Res.pc");
static_assert(__builtin_offsetof(Res, p10) == 0x20, "Res.p10");
#endif

#ifdef HOST64
static_assert(__builtin_offsetof(P, next) == 0x0, "P.next");
static_assert(__builtin_offsetof(P, prev) == 0x8, "P.prev");
static_assert(__builtin_offsetof(P, pos) == 0x10, "P.pos");
static_assert(__builtin_offsetof(P, vel) == 0x1c, "P.vel");
static_assert(__builtin_offsetof(P, rot0) == 0x28, "P.rot0");
static_assert(__builtin_offsetof(P, rot1) == 0x2a, "P.rot1");
static_assert(__builtin_offsetof(P, life) == 0x2c, "P.life");
static_assert(__builtin_offsetof(P, age) == 0x2e, "P.age");
static_assert(__builtin_offsetof(P, h28) == 0x30, "P.h28");
static_assert(__builtin_offsetof(P, h2a) == 0x32, "P.h2a");
static_assert(__builtin_offsetof(P, b2c) == 0x34, "P.b2c");
static_assert(__builtin_offsetof(P, b2d) == 0x35, "P.b2d");
static_assert(__builtin_offsetof(P, fl) == 0x36, "P.fl");
static_assert(__builtin_offsetof(P, w30) == 0x38, "P.w30");
static_assert(__builtin_offsetof(P, s34) == 0x3c, "P.s34");
static_assert(__builtin_offsetof(P, col) == 0x3e, "P.col");
static_assert(__builtin_offsetof(P, epos) == 0x40, "P.epos");
#endif

#ifdef HOST64
static_assert(__builtin_offsetof(E, p0) == 0x0, "E.p0");
static_assert(__builtin_offsetof(E, list) == 0x10, "E.list");
static_assert(__builtin_offsetof(E, p10) == 0x20, "E.p10");
static_assert(__builtin_offsetof(E, res) == 0x30, "E.res");
static_assert(__builtin_offsetof(E, p1c) == 0x38, "E.p1c");
static_assert(__builtin_offsetof(E, pos) == 0x3c, "E.pos");
static_assert(__builtin_offsetof(E, p2c) == 0x48, "E.p2c");
static_assert(__builtin_offsetof(E, phase) == 0x56, "E.phase");
static_assert(__builtin_offsetof(E, dir) == 0x58, "E.dir");
static_assert(__builtin_offsetof(E, p42) == 0x5e, "E.p42");
static_assert(__builtin_offsetof(E, radius) == 0x60, "E.radius");
static_assert(__builtin_offsetof(E, len) == 0x64, "E.len");
static_assert(__builtin_offsetof(E, w4c) == 0x68, "E.w4c");
static_assert(__builtin_offsetof(E, w50) == 0x6c, "E.w50");
static_assert(__builtin_offsetof(E, w54) == 0x70, "E.w54");
static_assert(__builtin_offsetof(E, h58) == 0x74, "E.h58");
static_assert(__builtin_offsetof(E, p5a) == 0x76, "E.p5a");
static_assert(__builtin_offsetof(E, w5c) == 0x78, "E.w5c");
static_assert(__builtin_offsetof(E, p60) == 0x7c, "E.p60");
static_assert(__builtin_offsetof(E, b68) == 0x84, "E.b68");
static_assert(__builtin_offsetof(E, b69) == 0x85, "E.b69");
static_assert(__builtin_offsetof(E, p6a) == 0x86, "E.p6a");
static_assert(__builtin_offsetof(E, ax1) == 0x88, "E.ax1");
static_assert(__builtin_offsetof(E, ax2) == 0x8e, "E.ax2");
#endif
