

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
#include "types64.h"
#include "nitro/io_access.h"
typedef int BOOL;
#define NULL 0

#include "nnsys/g3d_rt.h"
#include "proto/autoload_2/unk_021040ac.h"
#include "proto/autoload_2/unk_02104d80.h"
#include "proto/autoload_2/unk_02105d50.h"
#include "proto/autoload_2/unk_021104ac.h"
#include "proto/autoload_2/unk_02110c98.h"
#include "proto/itcm/unk_01ff8ad4.h"

typedef struct EvpCache {
    s32 pos[16];
    s32 nrm[9];
} EvpCache;
extern EvpCache data_021f70c4[64];

extern BOOL G3X_GetClipMtx(void *);
extern BOOL G3X_GetVectorMtx(void *);
extern void MIi_CpuClearFast(u32, void *, u32);
static inline BOOL BitVecCheck(const u32 *vec, u32 idx) { return (BOOL)(vec[idx >> 5] & (1 << (idx & 31))); }
static inline void BitVecSet(u32 *vec, u32 idx) { vec[idx >> 5] |= 1 << (idx & 31); }
#define ACC(d, w, v) d += ((s64)(w) * (v)) >> 12
void NNSi_G3dFuncSbc_NODEMIX(G3dRS *rs)
{
    u32 had;
    s64 pw;
    u8 *e;
    u32 i;
    s32 *cur;
    s32 *prev;
    u32 idx;
    s32 w;
    u8 *mdl = (u8 *)rs->pRenderObj->resMdl;
    u8 *c = rs->c;
    u8 *inv = mdl + *(u32 *)(mdl + 0x10);
    u32 n = c[2];
    s32 pos[12];
    s32 nrm[12];
    volatile u32 zero = 0;
    e = c + 3;
    pw = 0;
    MIi_CpuClearFast(zero, pos, sizeof(pos));
    MIi_CpuClearFast(zero, nrm, sizeof(nrm));
    NNS_G3dGeFlushBuffer();
    IO_W((volatile u32 *)0x04000440, 0);
    IO_W((volatile u32 *)0x0400044c, 1);
    IO_W((volatile u32 *)0x04000454, 0);
    IO_W((volatile u32 *)0x04000440, 2);
    for (i = 0; i < n; i++) {
        idx = e[1];
        had = BitVecCheck(rs->isEnvCached, idx);
        cur = data_021f70c4[idx].pos;
        if (had == 0) {
            BitVecSet(rs->isEnvCached, idx);
            IO_W((volatile u32 *)0x04000450, e[0]);
            IO_W((volatile u32 *)0x04000440, 1);
            G3_MultMtx43(inv + idx * 0x54);
        }
        if (i != 0) {
            ACC(nrm[0], pw, prev[0]);
            ACC(nrm[1], pw, prev[1]);
            ACC(nrm[2], pw, prev[2]);
            ACC(nrm[3], pw, prev[3]);
            ACC(nrm[4], pw, prev[4]);
            ACC(nrm[5], pw, prev[5]);
            ACC(nrm[6], pw, prev[6]);
            ACC(nrm[7], pw, prev[7]);
            ACC(nrm[8], pw, prev[8]);
        }
        if (had == 0) {
            while (G3X_GetClipMtx(cur) != 0) {
            }
            IO_W((volatile u32 *)0x04000440, 2);
            G3_MultMtx33(inv + idx * 0x54 + 0x30);
        }
        prev = data_021f70c4[idx].nrm;
        w = e[2] << 4;
        ACC(pos[0], w, cur[0]);
        ACC(pos[1], w, cur[1]);
        ACC(pos[2], w, cur[2]);
        ACC(pos[3], w, cur[4]);
        ACC(pos[4], w, cur[5]);
        ACC(pos[5], w, cur[6]);
        ACC(pos[6], w, cur[8]);
        ACC(pos[7], w, cur[9]);
        ACC(pos[8], w, cur[10]);
        ACC(pos[9], w, cur[12]);
        ACC(pos[10], w, cur[13]);
        ACC(pos[11], w, cur[14]);
        pw = w;
        e += 3;
        if (had == 0) {
            while (G3X_GetVectorMtx(prev) != 0) {
            }
        }
    }
    ACC(nrm[0], pw, prev[0]);
    ACC(nrm[1], pw, prev[1]);
    ACC(nrm[2], pw, prev[2]);
    ACC(nrm[3], pw, prev[3]);
    ACC(nrm[4], pw, prev[4]);
    ACC(nrm[5], pw, prev[5]);
    ACC(nrm[6], pw, prev[6]);
    ACC(nrm[7], pw, prev[7]);
    ACC(nrm[8], pw, prev[8]);
    G3_LoadMtx43(nrm);
    IO_W((volatile u32 *)0x04000440, 1);
    G3_LoadMtx43(pos);
    IO_W((volatile u32 *)0x04000440, 0);
    IO_W((volatile u32 *)0x04000450, 1);
    IO_W((volatile u32 *)0x04000440, 2);
    IO_W((volatile u32 *)0x0400044c, rs->c[1]);
    rs->c += (rs->c[2] + 1) * 3;
}

EvpCache data_021f70c4[64];
