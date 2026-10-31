typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "uptr.h"
#include "host_mem.h"
typedef int s32;

extern s32 data_0213bfec;
void MI_DmaCopy32(s32 dmaNo, const void *src, void *dest, u32 size);
void MIi_CpuCopy32(const void *src, void *dest, u32 size);

static inline void copy32(s32 dmaNo, const void *src, void *dest, u32 size) {
    if (dmaNo != -1 && size > 48) {
        MI_DmaCopy32(dmaNo, src, dest, size);
    } else {
        MIi_CpuCopy32(src, dest, size);
    }
}

static inline void *G2_GetOBJCharPtr(void) {
    return HostVram_CpuPtr(0x06400000);
}

static inline void *G2S_GetOBJCharPtr(void) {
    return HostVram_CpuPtr(0x06600000);
}

void GX_LoadOBJ(const void *src, u32 offset, u32 size) {
    u8 *base = (u8 *)G2_GetOBJCharPtr();
    copy32(data_0213bfec, src, base + offset, size);
}

void GXS_LoadOBJ(const void *src, u32 offset, u32 size) {
    u8 *base = (u8 *)G2S_GetOBJCharPtr();
    copy32(data_0213bfec, src, base + offset, size);
}
