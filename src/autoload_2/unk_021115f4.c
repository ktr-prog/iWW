#include "proto/autoload_2/unk_021104ac.h"
#include "proto/autoload_2/unk_021115f4.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef int BOOL;

#define R8(a) (*(volatile u8 *)(a))
#define R16(a) (*(volatile u16 *)(a))
#define R32(a) (*(volatile u32 *)(a))

extern s32 data_0213bfec;
extern void MI_DmaCopy32(s32 dmaNo, const void *src, void *dst, u32 size);
extern void MIi_CpuCopy32(const void *src, void *dst, u32 size);

void GX_LoadBG1Char(const void *src, u32 offset, u32 size) {
    u8 *base = (u8 *)G2_GetBG1CharPtr();
    if (data_0213bfec != -1 && size > 0x30) {
        MI_DmaCopy32(data_0213bfec, src, base + offset, size);
    } else {
        MIi_CpuCopy32(src, base + offset, size);
    }
}
void GXS_LoadBG1Char(const void *src, u32 offset, u32 size) {
    u8 *base = (u8 *)G2S_GetBG1CharPtr();
    if (data_0213bfec != -1 && size > 0x30) {
        MI_DmaCopy32(data_0213bfec, src, base + offset, size);
    } else {
        MIi_CpuCopy32(src, base + offset, size);
    }
}
void GX_LoadBG2Char(const void *src, u32 offset, u32 size) {
    u8 *base = (u8 *)G2_GetBG2CharPtr();
    if (data_0213bfec != -1 && size > 0x30) {
        MI_DmaCopy32(data_0213bfec, src, base + offset, size);
    } else {
        MIi_CpuCopy32(src, base + offset, size);
    }
}
void GXS_LoadBG2Char(const void *src, u32 offset, u32 size) {
    u8 *base = (u8 *)G2S_GetBG2CharPtr();
    if (data_0213bfec != -1 && size > 0x30) {
        MI_DmaCopy32(data_0213bfec, src, base + offset, size);
    } else {
        MIi_CpuCopy32(src, base + offset, size);
    }
}
void GX_LoadBG3Char(const void *src, u32 offset, u32 size) {
    u8 *base = (u8 *)G2_GetBG3CharPtr();
    if (data_0213bfec != -1 && size > 0x30) {
        MI_DmaCopy32(data_0213bfec, src, base + offset, size);
    } else {
        MIi_CpuCopy32(src, base + offset, size);
    }
}
void GXS_LoadBG3Char(const void *src, u32 offset, u32 size) {
    u8 *base = (u8 *)G2S_GetBG3CharPtr();
    if (data_0213bfec != -1 && size > 0x30) {
        MI_DmaCopy32(data_0213bfec, src, base + offset, size);
    } else {
        MIi_CpuCopy32(src, base + offset, size);
    }
}
