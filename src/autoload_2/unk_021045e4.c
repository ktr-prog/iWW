#include "nitro/io_access.h"
#include "host_labels.h"
#include "proto/autoload_2/unk_021045e4.h"
#include "proto/autoload_2/unk_02105d50.h"
#include "proto/itcm/unk_01ff8ad4.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef int BOOL;
#define NULL 0

typedef struct Shp {
    u8 pad0[0x10];
    u32 w10;
    u8 pad14[0x18];
    u16 w2c, w2e;
} Shp;
typedef struct Rs {
    u8 *code;
    u8 pad4[4];
    u32 flags;
    u8 pad0c[0x34];
    void (*cb)(struct Rs *);
    u8 pad44[0x55];
    u8 cbTiming;
    u8 pad9a[0x16];
    Shp *shp;
    u8 padb4[0x24];
    u8 *res;
} Rs;
extern u32 data_0213bd50[2];
extern u32 data_0213bd80[];
extern u8 data_027e00c8_dummy;
typedef union Glb {
    u32 w[0x99 + 1];
    struct { u8 pad[0xfc]; u32 flag; } n;
} Glb;
extern Glb data_027e00c8;
#define data_027e01a8 HOST_LABEL(u8 (*)[], data_027e01a8)
#define data_027e0184 HOST_LABEL(u8 (*)[], data_027e0184)
extern void NNS_G3dGeBufferOP_N(u32, void *, u32);
extern BOOL G3X_GetClipMtx(void *);
extern u8 *NNS_G3dGlbGetInvV(void);
extern u32 data_dummy_hw;

#define RUN_CB(t) \
    ((cbTiming == (t)) ? (rs->flags &= ~0x40, rs->cb(rs), cbTiming = (rs->cb != NULL) ? rs->cbTiming : 0, (rs->flags & 0x40)) : 0)

void NNSi_G3dFuncSbc_PRJMAP(Rs *rs)
{
    u32 cbTiming;
    u32 c0, c1, c2, c3;
    u32 m1[12];
    u32 m2[16];
    if ((rs->flags & 0x200) == 0 && (rs->flags & 1) != 0) {
        NNS_G3dGetCurrentMtx(m1, 0);
        c0 = 30;
        NNS_G3dGeBufferOP_N(19, &c0, 1);
        if ((rs->shp->w10 & 0xc0000000) != 0xc0000000) {
            rs->shp->w10 &= ~0xc0000000;
            rs->shp->w10 |= 0xc0000000;
            data_0213bd50[1] = rs->shp->w10;
            NNS_G3dGeBufferOP_N(data_0213bd50[0], &data_0213bd50[1], 1);
        }
        cbTiming = (rs->cb != NULL) ? rs->cbTiming : 0;
        if (!RUN_CB(1)) {
            Shp *s = rs->shp;
            u32 a = s->w2c, b = s->w2e;
            data_0213bd80[0] = a << 15;
            data_0213bd80[5] = (-b) << 15;
            data_0213bd80[12] = a << 15;
            data_0213bd80[13] = b << 15;
            NNS_G3dGeBufferOP_N(22, data_0213bd80, 16);
        }
        if (!RUN_CB(2)) {
            u8 *d = rs->res + 4;
            u8 *dict = d + *(u16 *)(rs->res + 10);
            u8 *m = rs->res + *(u32 *)(dict + *(u16 *)dict * rs->code[1] + 4);
            u32 mf = *(u16 *)(m + 0x1e);
            if (mf & 0x2000) {
                u8 *p = m + 0x2c;
                if ((mf & 2) == 0) p += 8;
                if ((mf & 4) == 0) p += 4;
                if ((mf & 8) == 0) p += 8;
                NNS_G3dGeBufferOP_N(24, p, 16);
            }
        }
        if (!RUN_CB(3)) {
            u32 f = data_027e00c8.n.flag;
            if (f & 1) {
                NNS_G3dGeBufferOP_N(28, data_027e01a8, 3);
                NNS_G3dGeBufferOP_N(26, data_027e0184, 9);
                NNS_G3dGeBufferOP_N(25, m1, 12);
            } else if (f & 2) {
                NNS_G3dGeBufferOP_N(25, m1, 12);
            } else {
                NNS_G3dGeBufferOP_N(25, NNS_G3dGlbGetInvV(), 12);
                NNS_G3dGeBufferOP_N(25, m1, 12);
            }
            NNS_G3dGeFlushBuffer();
            IO_W((volatile u32 *)0x04000440, 0);
            IO_W((volatile u32 *)0x04000444, 0);
            IO_W((volatile u32 *)0x04000454, 0);
            do {
            } while (G3X_GetClipMtx(m2) != 0);
            IO_W((volatile u32 *)0x04000448, 1);
            IO_W((volatile u32 *)0x04000440, 3);
            NNS_G3dGeBufferOP_N(22, m2, 16);
            {
                s32 px = (s32)m2[12] >> 4;
                s32 py = (s32)m2[13] >> 4;
                c1 = (u16)(s16)(px >> 8) | ((u16)(s16)(py >> 8) << 16);
                NNS_G3dGeBufferOP_N(34, &c1, 1);
            }
        }
        c2 = 2;
        NNS_G3dGeBufferOP_N(16, &c2, 1);
        c3 = 30;
        NNS_G3dGeBufferOP_N(20, &c3, 1);
    }
    rs->code += 3;
}
