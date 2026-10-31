#include "proto/autoload_2/unk_0210fa84.h"
#include "host_mem.h"
#include "proto/autoload_2/unk_02111ccc.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "uptr.h"
typedef int s32;

extern s32 data_0213bfec;
void MI_DmaCopy32(s32 dmaNo, const void *src, void *dest, u32 size);
void MIi_CpuCopy32(const void *src, void *dest, u32 size);
void MI_DmaCopy16(s32 dmaNo, const void *src, void *dest, u32 size);
void MIi_CpuCopy16(const void *src, void *dest, u32 size);
extern u32 data_021fcbf8;
extern s32 data_021fcbfc;
extern const u16 data_02139f44[8];
extern u32 data_021fcbf4, data_021fcc00, data_021fcc04, data_021fcc08;
void MI_WaitDma(s32 dmaNo);
s32 GX_ResetBankForTexPltt(void);
void MI_DmaCopy32Async(s32 dmaNo, const void *src, void *dest, u32 size, void *callback, void *arg);

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

void GX_EndLoadTex(void) {
    if (data_0213bfec != -1) {
        MI_WaitDma(data_0213bfec);
    }
    GX_SetBankForTex(data_021fcc00);
    data_021fcc08 = 0;
    data_021fcc04 = 0;
    data_021fcbf4 = 0;
    data_021fcc00 = 0;
}

void GX_BeginLoadTexPltt(void) {
    s32 v = GX_ResetBankForTexPltt();
    data_021fcbfc = v;
    data_021fcbf8 = (u32)data_02139f44[v >> 4] << 12;
}

void GX_LoadTexPltt(const void *src, u32 offset, u32 size) {
    u8 *dest = (u8 *)HostVram_CpuPtr(data_021fcbf8 + offset);
    if (data_0213bfec != -1) {
        MI_DmaCopy32Async(data_0213bfec, src, dest, size, 0, 0);
    } else {
        MIi_CpuCopy32(src, dest, size);
    }
}

void GX_EndLoadTexPltt(void) {
    if (data_0213bfec != -1) {
        MI_WaitDma(data_0213bfec);
    }
    GX_SetBankForTexPltt(data_021fcbfc);
    data_021fcbfc = 0;
    data_021fcbf8 = 0;
}

void GX_LoadBGPltt(const void *src, u32 offset, u32 size) {
    copy16(data_0213bfec, src, (u8 *)HW_PLTT + offset, size);
}

void GXS_LoadBGPltt(const void *src, u32 offset, u32 size) {
    copy16(data_0213bfec, src, (u8 *)(HW_PLTT + 0x400) + offset, size);
}

void GX_LoadOBJPltt(const void *src, u32 offset, u32 size) {
    copy16(data_0213bfec, src, (u8 *)(HW_PLTT + 0x200) + offset, size);
}

void GXS_LoadOBJPltt(const void *src, u32 offset, u32 size) {
    copy16(data_0213bfec, src, (u8 *)(HW_PLTT + 0x600) + offset, size);
}

void GX_LoadOAM(const void *src, u32 offset, u32 size) {
    copy32(data_0213bfec, src, (u8 *)HW_OAM + offset, size);
}

void GXS_LoadOAM(const void *src, u32 offset, u32 size) {
    copy32(data_0213bfec, src, (u8 *)(HW_OAM + 0x400) + offset, size);
}

const u16 data_02139f44[8] = {0x0000, 0x6880, 0x6890, 0x6880, 0x6894, 0x0000, 0x6890, 0x6880};

u32 data_021fcbf8;
u32 data_021fcbf4;
u32 data_021fcc08;
s32 data_021fcbfc;
u32 data_021fcc00;
u32 data_021fcc04;
