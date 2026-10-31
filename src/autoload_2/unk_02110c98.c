#include "nitro/io_access.h"
#include "proto/autoload_2/unk_02110c98.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef int BOOL;

#define R8(a) (*(volatile u8 *)(a))
#define R16(a) (*(volatile u16 *)(a))
#define R32(a) (*(volatile u32 *)(a))

typedef struct { s32 x, y, z; } VecFx32;
typedef struct { s32 m[4][3]; } MtxFx43;

extern u32 data_0213bfec;
extern void MI_DmaFill32Async(u32 dmaNo, void *dst, u32 data, u32 size, void *cb, void *arg);
extern void MI_DmaFill32(u32 dmaNo, void *dst, u32 data, u32 size);
extern void MIi_CpuClear32(u32 data, void *dst, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern void MI_Copy32B(const void *src, void *dst);
extern void MI_Copy36B(const void *src, void *dst);
extern void MI_Copy64B(const void *src, void *dst);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern s32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void GXi_NopClearFifo128_(void *dst);
extern s32 G3X_GetMtxStackLevelPJ(u32 *p);
extern s32 G3X_GetMtxStackLevelPV(u32 *p);

void G3i_LookAt_(const VecFx32 *pos, const VecFx32 *up, const VecFx32 *target, BOOL send, MtxFx43 *mtx) {
    VecFx32 vLook, vRight, vUp;
    s32 tx, ty, tz;
    volatile u32 *fifo;
    vLook.x = pos->x - target->x;
    vLook.y = pos->y - target->y;
    vLook.z = pos->z - target->z;
    VEC_Normalize(&vLook, &vLook);
    VEC_CrossProduct(up, &vLook, &vRight);
    VEC_Normalize(&vRight, &vRight);
    VEC_CrossProduct(&vLook, &vRight, &vUp);
    if (send) {
        IO_W(&R32(0x04000440), 2);
        fifo = (volatile u32 *)0x0400045c;
        IO_W(fifo, vRight.x);
        IO_W(fifo, vUp.x);
        IO_W(fifo, vLook.x);
        IO_W(fifo, vRight.y);
        IO_W(fifo, vUp.y);
        IO_W(fifo, vLook.y);
        IO_W(fifo, vRight.z);
        IO_W(fifo, vUp.z);
        IO_W(fifo, vLook.z);
    }
    tx = -VEC_DotProduct(pos, &vRight);
    ty = -VEC_DotProduct(pos, &vUp);
    tz = -VEC_DotProduct(pos, &vLook);
    if (send) {
        IO_W(fifo, tx);
        IO_W(fifo, ty);
        IO_W(fifo, tz);
    }
    if (mtx) {
        mtx->m[0][0] = vRight.x;
        mtx->m[0][1] = vUp.x;
        mtx->m[0][2] = vLook.x;
        mtx->m[1][0] = vRight.y;
        mtx->m[1][1] = vUp.y;
        mtx->m[1][2] = vLook.y;
        mtx->m[2][0] = vRight.z;
        mtx->m[2][1] = vUp.z;
        mtx->m[2][2] = vLook.z;
        mtx->m[3][0] = tx;
        mtx->m[3][1] = ty;
        mtx->m[3][2] = tz;
    }
}
void G3X_Init(void) {
    G3X_ClearFifo();
    IO_W(&R32(0x04000504), 0);
    while (IO_R(&R32(0x04000600)) & 0x08000000) {
    }
    IO_W(&R16(0x04000060), 0);
    IO_W(&R32(0x04000600), 0);
    IO_W(&R32(0x04000010), 0);
    IO_OR(&R16(0x04000060), 0x2000);
    IO_OR(&R16(0x04000060), 0x1000);
    IO_AND(&R16(0x04000060), ~0x3002);
    IO_W(&R16(0x04000060), (IO_R(&R16(0x04000060)) & ~0x3000) | 0x10);
    IO_AND(&R16(0x04000060), 0xcffb);
    IO_OR(&R32(0x04000600), 0x8000);
    IO_W(&R32(0x04000600), (IO_R(&R32(0x04000600)) & ~0xc0000000) | 0x80000000);
    G3X_InitMtxStack();
    IO_W(&R32(0x04000350), 0);
    IO_W(&R16(0x04000354), 0x7fff);
    IO_W(&R16(0x04000356), 0);
    IO_W(&R32(0x04000358), 0);
    IO_W(&R16(0x0400035c), 0);
    IO_AND(&R16(0x04000008), ~3);
    G3X_InitTable();
    IO_W(&R32(0x040004a4), 0x1f0080);
    IO_W(&R32(0x040004a8), 0);
    IO_W(&R32(0x040004ac), 0);
}
void G3X_Reset(void) {
    while (IO_R(&R32(0x04000600)) & 0x08000000) {
    }
    IO_OR(&R32(0x04000600), 0x8000);
    IO_OR(&R16(0x04000060), 0x2000);
    IO_OR(&R16(0x04000060), 0x1000);
    G3X_ResetMtxStack();
    IO_W(&R32(0x040004a4), 0x1f0080);
    IO_W(&R32(0x040004a8), 0);
    IO_W(&R32(0x040004ac), 0);
}
void G3X_ClearFifo(void) {
    GXi_NopClearFifo128_((void *)0x04000400);
    while (IO_R(&R32(0x04000600)) & 0x08000000) {
    }
}
void G3X_InitMtxStack(void) {
    u32 a, b;
    IO_OR(&R32(0x04000600), 0x8000);
    while (G3X_GetMtxStackLevelPV(&a) != 0) {
    }
    while (G3X_GetMtxStackLevelPJ(&b) != 0) {
    }
    IO_W(&R32(0x04000440), 3);
    IO_W(&R32(0x04000454), 0);
    IO_W(&R32(0x04000440), 0);
    if (b != 0) IO_W(&R32(0x04000448), b);
    IO_W(&R32(0x04000454), 0);
    IO_W(&R32(0x04000440), 2);
    IO_W(&R32(0x04000448), a);
    IO_W(&R32(0x04000454), 0);
}
void G3X_ResetMtxStack(void) {
    u32 a, b;
    IO_OR(&R32(0x04000600), 0x8000);
    while (G3X_GetMtxStackLevelPV(&a) != 0) {
    }
    while (G3X_GetMtxStackLevelPJ(&b) != 0) {
    }
    IO_W(&R32(0x04000440), 3);
    IO_W(&R32(0x04000454), 0);
    IO_W(&R32(0x04000440), 0);
    if (b != 0) IO_W(&R32(0x04000448), b);
    IO_W(&R32(0x04000440), 2);
    IO_W(&R32(0x04000448), a);
    IO_W(&R32(0x04000454), 0);
}
void G3X_SetFog(s32 enable, s32 mode, s32 shift, s32 offset) {
    if (enable != 0) {
        IO_W(&R16(0x0400035c), offset);
        IO_W(&R16(0x04000060), (u16)((IO_R(&R16(0x04000060)) & ~0x3f40) | ((shift << 8) | (mode << 6) | 0x80)));
    } else {
        IO_AND(&R16(0x04000060), 0xcf7f);
    }
}
s32 G3X_GetClipMtx(void *dst) {
    if (IO_R(&R32(0x04000600)) & 0x08000000) return -1;
    MI_Copy64B((void *)0x04000640, dst);
    return 0;
}
s32 G3X_GetVectorMtx(void *dst) {
    if (IO_R(&R32(0x04000600)) & 0x08000000) return -1;
    MI_Copy36B((void *)0x04000680, dst);
    return 0;
}
void G3X_SetFogTable(const void *t) {
    MI_Copy32B(t, (void *)0x04000360);
}
void G3X_SetToonTable(const void *t) {
    MIi_CpuCopy16(t, (void *)0x04000380, 0x40);
}
void G3X_SetClearColor(u32 rgb, u32 alpha, u32 depth, u32 polyId, u32 fog) {
    u32 c = rgb | (alpha << 16) | (polyId << 24);
    if (fog) c |= 0x8000;
    IO_W(&R32(0x04000350), c);
    IO_W(&R16(0x04000354), depth);
}
void G3X_InitTable(void) {
    s32 i;
    if (data_0213bfec != -1) {
        MI_DmaFill32Async(data_0213bfec, (void *)0x04000330, 0, 16, 0, 0);
        MI_DmaFill32(data_0213bfec, (void *)0x04000360, 0, 96);
    } else {
        {
            volatile u32 z = 0;
            MIi_CpuClear32(z, (void *)0x04000330, 16);
        }
        {
            volatile u32 z = 0;
            MIi_CpuClear32(z, (void *)0x04000360, 96);
        }
    }
    for (i = 0; i < 32; i++) IO_W(&R32(0x040004d0), 0);
}
s32 G3X_GetMtxStackLevelPV(u32 *p) {
    if (IO_R(&R32(0x04000600)) & 0x4000) return -1;
    *p = (IO_R(&R32(0x04000600)) & 0x1f00) >> 8;
    return 0;
}
s32 G3X_GetMtxStackLevelPJ(u32 *p) {
    if (IO_R(&R32(0x04000600)) & 0x4000) return -1;
    *p = (IO_R(&R32(0x04000600)) & 0x2000) >> 13;
    return 0;
}
void G3X_SetHOffset(u32 v) {
    IO_W(&R32(0x04000010), v);
}
