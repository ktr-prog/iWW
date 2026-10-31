typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
#include "types64.h"
#include "host_labels.h"
typedef int BOOL;
#define NULL 0


#include "nnsys/g3d_rt.h"
#include "proto/autoload_2/unk_02104978.h"
#include "proto/autoload_2/unk_02105d50.h"
typedef G3dRS RS;
extern void NNS_G3dGeBufferOP_N(u32, void *, u32);
extern void NNS_G3dGeSendDL(void *, u32);

typedef struct V3 { s32 x, y, z; } V3;
typedef union Glb {
    u32 w[0x99 + 1];
    struct {
    u32 w0, w4;
    u8 pad8[0x90];
    u32 ctl98;
    u8 pad9c[0x44];
    V3 e0;
    V3 scale;
    u32 pad_f8;
    u32 flag;
    } n;
} Glb;
extern Glb data_027e00c8;
#define data_027e0114 HOST_LABEL(u8 (*)[], data_027e0114)
#define data_027e0184 HOST_LABEL(u8 (*)[], data_027e0184)
extern u32 data_0213bd58[2];
#define data_0213bd5c HOST_LABEL(u32 *, data_0213bd5c)

static inline u32 rd32(u8 *p) { return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24); }
void NNSi_G3dFuncSbc_CALLDL(RS *rs)
{
    u32 timing;
    u32 skip;
    timing = rs->cbVecFunc[G3D_SBC_NODEMIX] ? rs->cbVecTiming[G3D_SBC_NODEMIX] : 0;
    if (timing == 1) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[G3D_SBC_NODEMIX](rs);
        timing = rs->cbVecFunc[G3D_SBC_NODEMIX] ? rs->cbVecTiming[G3D_SBC_NODEMIX] : 0;
        skip = rs->flag & 0x40;
    } else {
        skip = 0;
    }
    if (!(rs->flag & 0x100) && !skip) {
        u8 *c = rs->c;
        NNS_G3dGeSendDL(c + rd32(c + 1), rd32(c + 5));
    }
    if (timing == 3) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[G3D_SBC_NODEMIX](rs);
    }
    rs->c += 9;
}

#define CB_TIMING(rs, cb, t) ((rs)->cb ? (rs)->t : 0)
void NNSi_G3dFuncSbc_ENVMAP(RS *rs)
{
    u32 timing;
    u32 skip;
    u32 mode;
    u32 st;
    u32 m1;
    u32 m3;
    u32 m4;
    s32 mtx[9];
    V3 sc;
    if ((rs->flag & 0x200) == 0 && (rs->flag & 1)) {
        u32 w = rs->pMatAnmResult->prmTexImage;
        if ((w & 0xc0000000) != 0x80000000) {
            rs->pMatAnmResult->prmTexImage &= ~0xc0000000;
            rs->pMatAnmResult->prmTexImage |= 0x80000000;
            data_0213bd58[1] = rs->pMatAnmResult->prmTexImage;
            NNS_G3dGeBufferOP_N(data_0213bd58[0], &data_0213bd5c, 1);
        }
        mode = 3;
        NNS_G3dGeBufferOP_N(0x10, &mode, 1);
        timing = CB_TIMING(rs, cbVecFunc[G3D_SBC_ENVMAP], cbVecTiming[G3D_SBC_ENVMAP]);
        if (timing == 1) {
            rs->flag &= ~0x40;
            rs->cbVecFunc[G3D_SBC_ENVMAP](rs);
            timing = CB_TIMING(rs, cbVecFunc[G3D_SBC_ENVMAP], cbVecTiming[G3D_SBC_ENVMAP]);
            skip = rs->flag & 0x40;
        } else {
            skip = 0;
        }
        if (skip == 0) {
            u32 t = rs->pMatAnmResult->origWidth;
            u32 s = rs->pMatAnmResult->origHeight;
            sc.x = t << 15;
            sc.y = -s << 15;
            sc.z = 0x10000;
            NNS_G3dGeBufferOP_N(0x1b, &sc, 3);
            st = (u16)(s16)(t << 3) | ((u16)(s16)(s << 3) << 16);
            NNS_G3dGeBufferOP_N(0x22, &st, 1);
        }
        if (timing == 2) {
            rs->flag &= ~0x40;
            rs->cbVecFunc[G3D_SBC_ENVMAP](rs);
            timing = CB_TIMING(rs, cbVecFunc[G3D_SBC_ENVMAP], cbVecTiming[G3D_SBC_ENVMAP]);
            skip = rs->flag & 0x40;
        } else {
            skip = 0;
        }
        if (skip == 0) {
            u8 *d = rs->pResMat + 4;
            u8 *dict = d + *(u16 *)(rs->pResMat + 10);
            u8 *mat = rs->pResMat + *(u32 *)(dict + *(u16 *)dict * rs->c[1] + 4);
            u16 f = *(u16 *)(mat + 0x1e);
            if (f & 0x2000) {
                u8 *p = mat + 0x2c;
                if ((f & 2) == 0) p += 8;
                if ((f & 4) == 0) p += 4;
                if ((f & 8) == 0) p += 8;
                NNS_G3dGeBufferOP_N(0x18, p, 16);
            }
        }
        if (timing == 3) {
            rs->flag &= ~0x40;
            rs->cbVecFunc[G3D_SBC_ENVMAP](rs);
            skip = rs->flag & 0x40;
        } else {
            skip = 0;
        }
        if (skip == 0) {
            m1 = 2;
            NNS_G3dGeBufferOP_N(0x10, &m1, 1);
            NNS_G3dGetCurrentMtx(0, mtx);
            m3 = 3;
            NNS_G3dGeBufferOP_N(0x10, &m3, 1);
            if (data_027e00c8.n.flag & 1) {
                NNS_G3dGeBufferOP_N(0x1a, data_027e0114, 9);
                NNS_G3dGeBufferOP_N(0x1a, data_027e0184, 9);
                NNS_G3dGeBufferOP_N(0x1a, mtx, 9);
            } else if (data_027e00c8.n.flag & 2) {
                NNS_G3dGeBufferOP_N(0x1a, data_027e0114, 9);
                NNS_G3dGeBufferOP_N(0x1a, mtx, 9);
            } else {
                NNS_G3dGeBufferOP_N(0x1a, mtx, 9);
            }
        }
        m4 = 2;
        NNS_G3dGeBufferOP_N(0x10, &m4, 1);
    }
    rs->c += 3;
}
