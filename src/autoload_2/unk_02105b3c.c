

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
#include "types64.h"
typedef int BOOL;
#define NULL 0

#include "nnsys/g3d_rt.h"
#include "proto/autoload_2/unk_02105b3c.h"
#include "proto/autoload_2/unk_0213bd28.h"
extern void NNS_G3dGeBufferOP_N(u32, void *, u32);
extern void NNS_G3dGeSendDL(void *, u32);

void NNS_G3dDraw1Mat1Shp(u8 *mdl, u32 matIdx, u32 shpIdx, BOOL sendMat)
{
    u32 buf[7];
    G3dMatAnmResult a;
    s32 sc1[3];
    s32 sc2[3];
    s32 ps = *(s32 *)(mdl + 0x1c);
    if (ps != 0x1000) {
        sc1[0] = ps;
        sc1[1] = ps;
        sc1[2] = ps;
        NNS_G3dGeBufferOP_N(0x1b, sc1, 3);
    }
    if (sendMat != 0) {
        u8 *m = mdl + *(u32 *)(mdl + 8);
        u8 *d = m + 4;
        u8 *dict = d + *(u16 *)(m + 10);
        u8 *mat = m + *(u32 *)(dict + *(u16 *)dict * matIdx + 4);
        if ((*(u32 *)(mat + 12) & 0x1f0000) == 0) {
            return;
        }
        buf[0] = 0x00293130;
        buf[1] = *(u32 *)(mat + 4);
        buf[2] = *(u32 *)(mat + 8);
        {
            u32 pa = *(u32 *)(mat + 12);
            buf[3] = pa;
            if (*(u16 *)(mat + 0x1e) & 0x20) {
                buf[3] = pa & ~0x1f0000;
            }
        }
        buf[4] = 0x2b2a;
        buf[5] = *(u32 *)(mat + 0x14);
        buf[6] = *(u16 *)(mat + 0x1c);
        NNS_G3dGeBufferOP_N(buf[0], &buf[1], 6);
        if (*(u16 *)(mat + 0x1e) & 1) {
            void (*fn)() = data_0213bd40[mdl[0x16]];
            u8 *p;
            a.flag = 8;
            a.origWidth = *(u16 *)(mat + 0x20);
            a.origHeight = *(u16 *)(mat + 0x22);
            a.magW = *(u32 *)(mat + 0x24);
            a.magH = *(u32 *)(mat + 0x28);
            p = mat + 0x2c;
            if (!(*(u16 *)(mat + 0x1e) & 2)) {
                const s32 *q = (const s32 *)p;
                a.scaleS = *(q + 0);
                a.scaleT = *(q + 1);
                p += 2 * sizeof(s32);
            } else {
                a.flag |= 1;
            }
            if (!(*(u16 *)(mat + 0x1e) & 4)) {
                const s16 *q = (const s16 *)p;
                a.sinR = *(q + 0);
                a.cosR = *(q + 1);
                p += 2 * sizeof(s16);
            } else {
                a.flag |= 2;
            }
            if ((*(u16 *)(mat + 0x1e) & 8) == 0) {
                a.transS = *(s32 *)p;
                a.transT = *(s32 *)(p + 4);
            } else {
                a.flag |= 4;
            }
            fn(&a);
        }
    }
    {
        u8 *s = mdl + *(u32 *)(mdl + 12);
        u8 *dict = s + *(u16 *)(s + 6);
        u8 *shp = s + *(u32 *)(dict + *(u16 *)dict * shpIdx + 4);
        NNS_G3dGeSendDL(shp + *(u32 *)(shp + 8), *(u32 *)(shp + 12));
    }
    ps = *(s32 *)(mdl + 0x20);
    if (ps != 0x1000) {
        sc2[0] = ps;
        sc2[1] = ps;
        sc2[2] = ps;
        NNS_G3dGeBufferOP_N(0x1b, sc2, 3);
    }
}
