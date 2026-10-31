#include "proto/autoload_2/unk_021104ac.h"
#include "proto/autoload_2/unk_02111864.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

extern s32 data_0213bfec;
void MI_DmaCopy32(s32 dmaNo, const void *src, void *dest, u32 size);
void MIi_CpuCopy32(const void *src, void *dest, u32 size);
void MI_DmaCopy16(s32 dmaNo, const void *src, void *dest, u32 size);
void MIi_CpuCopy16(const void *src, void *dest, u32 size);

static inline void copy32(s32 dmaNo, const void *src, void *dest, u32 size) {
    if (dmaNo != -1 && size > 48) {
        MI_DmaCopy32(dmaNo, src, dest, size);
    } else {
        MIi_CpuCopy32(src, dest, size);
    }
}

static inline void copy16(s32 dmaNo, const void *src, void *dest, u32 size) {
    if (dmaNo != -1 && size > 28) {
        MI_DmaCopy16(dmaNo, src, dest, size);
    } else {
        MIi_CpuCopy16(src, dest, size);
    }
}

void GXS_LoadBG0Scr(const void *src, u32 offset, u32 size) {
    u8 *base = G2S_GetBG0ScrPtr();
    copy16(data_0213bfec, src, base + offset, size);
}

void GX_LoadBG1Scr(const void *src, u32 offset, u32 size) {
    u8 *base = G2_GetBG1ScrPtr();
    copy16(data_0213bfec, src, base + offset, size);
}

void GXS_LoadBG1Scr(const void *src, u32 offset, u32 size) {
    u8 *base = G2S_GetBG1ScrPtr();
    copy16(data_0213bfec, src, base + offset, size);
}

void GX_LoadBG2Scr(const void *src, u32 offset, u32 size) {
    u8 *base = G2_GetBG2ScrPtr();
    copy16(data_0213bfec, src, base + offset, size);
}

void GXS_LoadBG2Scr(const void *src, u32 offset, u32 size) {
    u8 *base = G2S_GetBG2ScrPtr();
    copy16(data_0213bfec, src, base + offset, size);
}

void GX_LoadBG3Scr(const void *src, u32 offset, u32 size) {
    u8 *base = G2_GetBG3ScrPtr();
    copy16(data_0213bfec, src, base + offset, size);
}

void GXS_LoadBG3Scr(const void *src, u32 offset, u32 size) {
    u8 *base = G2S_GetBG3ScrPtr();
    copy16(data_0213bfec, src, base + offset, size);
}

void GX_LoadBG0Char(const void *src, u32 offset, u32 size) {
    u8 *base = G2_GetBG0CharPtr();
    copy32(data_0213bfec, src, base + offset, size);
}

void GXS_LoadBG0Char(const void *src, u32 offset, u32 size) {
    u8 *base = G2S_GetBG0CharPtr();
    copy32(data_0213bfec, src, base + offset, size);
}

