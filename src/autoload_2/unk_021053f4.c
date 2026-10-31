typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
#include "types64.h"
#include "host_labels.h"
#include "nitro/io_access.h"
typedef int BOOL;
#define NULL 0


#include "nnsys/g3d_rt.h"
#include "proto/autoload_2/unk_021053f4.h"
#include "proto/itcm/unk_01ff8ad4.h"
typedef G3dRS RS;
extern void NNS_G3dGeBufferOP_N(u32, void *, u32);

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
extern BOOL G3X_GetClipMtx(void *);
typedef struct Cb {
    s32 frame;
    s32 ratio;
    void *resAnm;
    void *funcAnm;
    struct Cb *next;
    const void *resTex;
    u8 priority;
    u8 n;
    u16 tbl[1];
} Cb;
extern u8 *NNS_G3dGlbGetWV(void);
extern u8 *NNS_G3dGlbGetInvWV(void);
extern u8 *NNS_G3dGlbGetInvV(void);
extern void MTX_Copy43To44_(void *, void *);
extern void MTX_Concat44(void *, void *, void *);
extern s32 VEC_Mag(void *);
extern void VEC_Normalize(void *, void *);
extern void MIi_CpuSend32(void *, void *, u32);
#define data_0213be38 HOST_LABEL(s32 (*)[3], data_0213be38)
#define data_0213be44 HOST_LABEL(s32 (*)[3], data_0213be44)
#define data_0213be14 HOST_LABEL(s32 (*)[9], data_0213be14)
#define data_0213be0c HOST_LABEL(u8 (*)[], data_0213be0c)
extern u32 data_0213be08[18];
#define data_0213bdf0 HOST_LABEL(s32 (*)[3], data_0213bdf0)
#define data_0213bdfc HOST_LABEL(s32 (*)[3], data_0213bdfc)
#define data_0213bdc4 HOST_LABEL(u8 (*)[], data_0213bdc4)
#define data_0213bdcc HOST_LABEL(u8 (*)[], data_0213bdcc)
extern u32 data_0213bdc0[18];

void updateHintVec_(u32 *bits, Cb *n)
{
    s32 i;
    if (n == NULL) {
        return;
    }
    do {
        for (i = 0; i < n->n; i++) {
            if (n->tbl[i] & 0x100) {
                bits[i >> 5] |= 1 << (i & 31);
            }
        }
        n = n->next;
    } while (n != NULL);
}

void NNSi_G3dFuncSbc_BB(RS *rs, u32 opt)
{
    u32 cmdlen = 2;
    s32 *trans = data_0213bdf0;
    s32 *scale = data_0213bdfc;
    u32 timing;
    u32 skip;
    if (rs->flag & 0x200) {
        if (opt == 0x40 || opt == 0x60) cmdlen++;
        if (opt == 0x20 || opt == 0x60) cmdlen++;
        rs->c += cmdlen;
        return;
    }
    if (opt == 0x40 || opt == 0x60) {
        cmdlen++;
        if ((rs->flag & 0x100) == 0) {
            u32 v;
            if (opt == 0x40) v = rs->c[2]; else v = rs->c[3];
            NNS_G3dGeBufferOP_N(0x14, &v, 1);
        }
    }
    timing = rs->cbVecFunc[G3D_SBC_BB] ? rs->cbVecTiming[G3D_SBC_BB] : 0;
    if (timing == 1) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[G3D_SBC_BB](rs);
        timing = rs->cbVecFunc[G3D_SBC_BB] ? rs->cbVecTiming[G3D_SBC_BB] : 0;
        skip = rs->flag & 0x40;
    } else {
        skip = 0;
    }
    if ((rs->flag & 0x100) == 0 && skip == 0) {
        s32 m[16];
        s32 m2[16];
        s32 m3[16];
        NNS_G3dGeFlushBuffer();
        IO_W((volatile u32 *)0x04000400, 0x00151110);
        IO_W((volatile u32 *)0x04000400, 0);
        IO_W((volatile u32 *)0x04000400, 0);
        while (G3X_GetClipMtx(m) != 0) {
        }
        if (data_027e00c8.n.flag & 1) {
            MTX_Copy43To44_(NNS_G3dGlbGetWV(), m2);
            MTX_Concat44(m, m2, m);
        } else if (data_027e00c8.n.flag & 2) {
            MTX_Copy43To44_(data_027e0114, m3);
            MTX_Concat44(m, m3, m);
        }
        trans[0] = m[12];
        trans[1] = m[13];
        trans[2] = m[14];
        scale[0] = VEC_Mag(&m[0]);
        scale[1] = VEC_Mag(&m[4]);
        scale[2] = VEC_Mag(&m[8]);
        if (data_027e00c8.n.flag & 1) {
            IO_W((volatile u32 *)0x04000400, 0x00171012);
            MIi_CpuSend32(data_0213bdc4, (void *)0x04000400, 8);
            MIi_CpuSend32(NNS_G3dGlbGetInvWV(), (void *)0x04000400, 0x30);
            IO_W((volatile u32 *)0x04000400, 0x1b19);
            MIi_CpuSend32(data_0213bdcc, (void *)0x04000400, 0x3c);
        } else if (data_027e00c8.n.flag & 2) {
            IO_W((volatile u32 *)0x04000400, 0x00171012);
            MIi_CpuSend32(data_0213bdc4, (void *)0x04000400, 8);
            MIi_CpuSend32(NNS_G3dGlbGetInvV(), (void *)0x04000400, 0x30);
            IO_W((volatile u32 *)0x04000400, 0x1b19);
            MIi_CpuSend32(data_0213bdcc, (void *)0x04000400, 0x3c);
        } else {
            MIi_CpuSend32(data_0213bdc0, (void *)0x04000400, 0x48);
        }
    }
    if (timing == 3) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[G3D_SBC_BB](rs);
        skip = rs->flag & 0x40;
    } else {
        skip = 0;
    }
    if (opt == 0x20 || opt == 0x60) {
        cmdlen++;
        if (skip == 0 && (rs->flag & 0x100) == 0) {
            u32 v = rs->c[2];
            NNS_G3dGeBufferOP_N(0x13, &v, 1);
        }
    }
    rs->c += cmdlen;
}

void NNSi_G3dFuncSbc_BBY(RS *rs, u32 opt)
{
    u32 cmdlen = 2;
    s32 *trans = data_0213be38;
    s32 *scale = data_0213be44;
    s32 *rot = data_0213be14;
    u32 timing;
    u32 skip;
    if (rs->flag & 0x200) {
        if (opt == 0x40 || opt == 0x60) cmdlen++;
        if (opt == 0x20 || opt == 0x60) cmdlen++;
        rs->c += cmdlen;
        return;
    }
    if (opt == 0x40 || opt == 0x60) {
        cmdlen++;
        if ((rs->flag & 0x100) == 0) {
            u32 v;
            if (opt == 0x40) v = rs->c[2]; else v = rs->c[3];
            NNS_G3dGeBufferOP_N(0x14, &v, 1);
        }
    }
    timing = rs->cbVecFunc[G3D_SBC_BBY] ? rs->cbVecTiming[G3D_SBC_BBY] : 0;
    if (timing == 1) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[G3D_SBC_BBY](rs);
        timing = rs->cbVecFunc[G3D_SBC_BBY] ? rs->cbVecTiming[G3D_SBC_BBY] : 0;
        skip = rs->flag & 0x40;
    } else {
        skip = 0;
    }
    if ((rs->flag & 0x100) == 0 && skip == 0) {
        s32 m[16];
        s32 m2[16];
        s32 m3[16];
        NNS_G3dGeFlushBuffer();
        IO_W((volatile u32 *)0x04000400, 0x00151110);
        IO_W((volatile u32 *)0x04000400, 0);
        IO_W((volatile u32 *)0x04000400, 0);
        while (G3X_GetClipMtx(m) != 0) {
        }
        if (data_027e00c8.n.flag & 1) {
            MTX_Copy43To44_(NNS_G3dGlbGetWV(), m2);
            MTX_Concat44(m, m2, m);
        } else if (data_027e00c8.n.flag & 2) {
            MTX_Copy43To44_(data_027e0114, m3);
            MTX_Concat44(m, m3, m);
        }
        trans[0] = m[12];
        trans[1] = m[13];
        trans[2] = m[14];
        scale[0] = VEC_Mag(&m[0]);
        scale[1] = VEC_Mag(&m[4]);
        scale[2] = VEC_Mag(&m[8]);
        if (m[5] != 0 || m[6] != 0) {
            VEC_Normalize(&m[4], rot + 3);
            rot[7] = -rot[5];
            rot[8] = rot[4];
        } else {
            VEC_Normalize(&m[8], rot + 6);
            rot[5] = -rot[7];
            rot[4] = rot[8];
        }
        if (data_027e00c8.n.flag & 1) {
            IO_W((volatile u32 *)0x04000400, 0x00171012);
            MIi_CpuSend32(data_0213be0c, (void *)0x04000400, 8);
            MIi_CpuSend32(NNS_G3dGlbGetInvWV(), (void *)0x04000400, 0x30);
            IO_W((volatile u32 *)0x04000400, 0x1b19);
            MIi_CpuSend32(data_0213be14, (void *)0x04000400, 0x3c);
        } else if (data_027e00c8.n.flag & 2) {
            IO_W((volatile u32 *)0x04000400, 0x00171012);
            MIi_CpuSend32(data_0213be0c, (void *)0x04000400, 8);
            MIi_CpuSend32(NNS_G3dGlbGetInvV(), (void *)0x04000400, 0x30);
            IO_W((volatile u32 *)0x04000400, 0x1b19);
            MIi_CpuSend32(data_0213be14, (void *)0x04000400, 0x3c);
        } else {
            MIi_CpuSend32(data_0213be08, (void *)0x04000400, 0x48);
        }
    }
    if (timing == 3) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[G3D_SBC_BBY](rs);
        skip = rs->flag & 0x40;
    } else {
        skip = 0;
    }
    if (opt == 0x20 || opt == 0x60) {
        cmdlen++;
        if (skip == 0 && (rs->flag & 0x100) == 0) {
            u32 v = rs->c[2];
            NNS_G3dGeBufferOP_N(0x13, &v, 1);
        }
    }
    rs->c += cmdlen;
}

void NNSi_G3dFuncSbc_BB();
void NNSi_G3dFuncSbc_BBY();
void NNSi_G3dFuncSbc_CALLDL();
void NNSi_G3dFuncSbc_ENVMAP();
void NNSi_G3dFuncSbc_MAT();
void NNSi_G3dFuncSbc_MAT_InternalDefault();
void NNSi_G3dFuncSbc_MTX();
void NNSi_G3dFuncSbc_NODE();
void NNSi_G3dFuncSbc_NODEDESC();
void NNSi_G3dFuncSbc_NODEMIX();
void NNSi_G3dFuncSbc_PRJMAP();
void NNSi_G3dFuncSbc_SHP();
void NNSi_G3dFuncSbc_SHP_InternalDefault();
void NNSi_G3dFuncSbc_NOP();
void NNSi_G3dFuncSbc_POSSCALE();
void NNSi_G3dFuncSbc_RET();
void (*data_0213be50[32])() = {
    NNSi_G3dFuncSbc_NOP,
    NNSi_G3dFuncSbc_RET,
    NNSi_G3dFuncSbc_NODE,
    NNSi_G3dFuncSbc_MTX,
    NNSi_G3dFuncSbc_MAT,
    NNSi_G3dFuncSbc_SHP,
    NNSi_G3dFuncSbc_NODEDESC,
    NNSi_G3dFuncSbc_BB,
    NNSi_G3dFuncSbc_BBY,
    NNSi_G3dFuncSbc_NODEMIX,
    NNSi_G3dFuncSbc_CALLDL,
    NNSi_G3dFuncSbc_POSSCALE,
    NNSi_G3dFuncSbc_ENVMAP,
    NNSi_G3dFuncSbc_PRJMAP,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
u32 data_0213bdc0[18] = {
    0x1b171012, 0x00000001, 0x00000002, 0x00001000, 0x00000000, 0x00000000,
    0x00000000, 0x00001000, 0x00000000, 0x00000000, 0x00000000, 0x00001000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
u32 data_0213be08[18] = {
    0x1b171012, 0x00000001, 0x00000002, 0x00001000, 0x00000000, 0x00000000,
    0x00000000, 0x00001000, 0x00000000, 0x00000000, 0x00000000, 0x00001000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
u32 data_0213bd80[16] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010000,
};
const u8 data_02135d38[9][4] = {
    {4, 5, 7, 8}, {3, 5, 6, 8}, {3, 4, 6, 7},
    {1, 2, 7, 8}, {0, 2, 6, 8}, {0, 1, 6, 7},
    {1, 2, 4, 5}, {0, 2, 3, 5}, {0, 1, 3, 4},
};
const u32 data_02135d18[8] = {0x00000000, 0x00007fff, 0x7fff0000, 0x7fff7fff, 0x00008000, 0x0000ffff, 0x7fff8000, 0x7fffffff};
void (*data_0213bd60[4])() = {
    NNSi_G3dFuncSbc_MAT_InternalDefault,
    0,
    0,
    0,
};
void (*data_0213bd70[4])() = {
    NNSi_G3dFuncSbc_SHP_InternalDefault,
    0,
    0,
    0,
};
u32 data_0213bd58[2] = {0x2a, 0};
u32 data_0213bd50[2] = {0x2a, 0};

void *data_021f5cc0;
u32 data_021f5cc4[0x500];

#include "host_labels.h"

HOST_LABEL_DEFINE(data_0213bd5c, (char *)&data_0213bd58[1]);
HOST_LABEL_DEFINE(data_0213bdc4, (char *)&data_0213bdc0[1]);
HOST_LABEL_DEFINE(data_0213bdcc, (char *)&data_0213bdc0[3]);
HOST_LABEL_DEFINE(data_0213bdf0, (char *)&data_0213bdc0[12]);
HOST_LABEL_DEFINE(data_0213bdfc, (char *)&data_0213bdc0[15]);
HOST_LABEL_DEFINE(data_0213be0c, (char *)&data_0213be08[1]);
HOST_LABEL_DEFINE(data_0213be14, (char *)&data_0213be08[3]);
HOST_LABEL_DEFINE(data_0213be38, (char *)&data_0213be08[12]);
HOST_LABEL_DEFINE(data_0213be44, (char *)&data_0213be08[15]);
HOST_LABEL_DEFINE(data_021f6ac4, (char *)&data_021f5cc4[896]);
