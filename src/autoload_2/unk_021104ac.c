#include "nitro/io_access.h"
#include "host_mem.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "uptr.h"
typedef signed short s16;
typedef signed int s32;
typedef int BOOL;

#define R8(a) (*(volatile u8 *)(a))
#define R16(a) (*(volatile u16 *)(a))
#define R32(a) (*(volatile u32 *)(a))

extern void MI_Copy36B(const void *src, void *dst);
extern void GX_SendFifo48B(const void *src, void *dst);

void G3_LoadMtx43(const void *m) {
    IO_W(&R32(0x04000400), 0x17);
    GX_SendFifo48B(m, (void *)0x04000400);
}
void G3_MultMtx43(const void *m) {
    IO_W(&R32(0x04000400), 0x19);
    GX_SendFifo48B(m, (void *)0x04000400);
}
void G3_MultMtx33(const void *m) {
    IO_W(&R32(0x04000400), 0x1a);
    MI_Copy36B(m, (void *)0x04000400);
}
void G2x_SetBGyAffine_(u32 *out, const s32 *m, s32 cx, s32 cy, s32 x, s32 y) {
    s32 dx, dy, px, py;
    IO_W(&out[0], (u16)(s16)(m[0] >> 4) | ((u16)(s16)(m[1] >> 4) << 16));
    IO_W(&out[1], (u16)(s16)(m[2] >> 4) | ((u16)(s16)(m[3] >> 4) << 16));
    dx = x - cx;
    dy = y - cy;
    px = m[0] * dx + m[1] * dy + (cx << 12);
    py = m[2] * dx + m[3] * dy + (cy << 12);
    IO_W(&out[2], px >> 4);
    IO_W(&out[3], py >> 4);
}
void G2x_SetBlendAlpha_(u32 *p, u32 a, u32 b, u32 c, u32 d) {
    IO_W(p, ((a | 0x40) | (b << 8)) | ((c | (d << 8)) << 16));
}
void G2x_SetBlendBrightness_(u16 *p, u32 a, s32 v) {
    if (v < 0) {
        IO_W(&p[0], a | 0xc0);
        IO_W(&p[2], -v);
    } else {
        IO_W(&p[0], a | 0x80);
        IO_W(&p[2], v);
    }
}
void G2x_SetBlendBrightnessExt_(u16 *p, u32 a, u32 b, u32 c, u32 d, s32 v) {
    IO_W(&p[1], c | (d << 8));
    if (v < 0) {
        IO_W(&p[0], a | 0xc0 | (b << 8));
        IO_W(&p[2], -v);
    } else {
        IO_W(&p[0], a | 0x80 | (b << 8));
        IO_W(&p[2], v);
    }
}
void G2x_ChangeBlendBrightness_(u16 *p, s32 v) {
    u16 c = p[0];
    if (v < 0) {
        if ((c & 0xc0) == 0x80) p[0] = (c & ~0xc0) | 0xc0;
        p[2] = -v;
    } else {
        if ((c & 0xc0) == 0xc0) p[0] = (c & ~0xc0) | 0x80;
        p[2] = v;
    }
}
void *G2_GetBG0ScrPtr(void) {
    u32 scr = (IO_R(&R16(0x04000008)) & 0x1f00) >> 8;
    u32 base = ((IO_R(&R32(0x04000000)) & 0x38000000) >> 27) << 16;
    return HostVram_CpuPtr(0x06000000 + base + (scr << 11));
}
void *G2S_GetBG0ScrPtr(void) {
    return HostVram_CpuPtr(0x06200000 + (((IO_R(&R16(0x04001008)) & 0x1f00) >> 8) << 11));
}
void *G2_GetBG1ScrPtr(void) {
    u32 scr = (IO_R(&R16(0x0400000a)) & 0x1f00) >> 8;
    u32 base = ((IO_R(&R32(0x04000000)) & 0x38000000) >> 27) << 16;
    return HostVram_CpuPtr(0x06000000 + base + (scr << 11));
}
void *G2S_GetBG1ScrPtr(void) {
    return HostVram_CpuPtr(0x06200000 + (((IO_R(&R16(0x0400100a)) & 0x1f00) >> 8) << 11));
}
void *G2_GetBG2ScrPtr(void) {
    u32 mode = IO_R(&R32(0x04000000)) & 7;
    u32 cnt = IO_R(&R16(0x0400000c));
    u32 base = ((IO_R(&R32(0x04000000)) & 0x38000000) >> 27) << 16;
    u32 scr = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0: case 1: case 2: case 3: case 4:
        return HostVram_CpuPtr(0x06000000 + base + (scr << 11));
    case 5:
        if (cnt & 0x80) return HostVram_CpuPtr(0x06000000 + (scr << 14));
        return HostVram_CpuPtr(0x06000000 + base + (scr << 11));
    case 6:
        return HostVram_CpuPtr(0x06000000);
    default:
        return 0;
    }
}
void *G2S_GetBG2ScrPtr(void) {
    u32 mode = IO_R(&R32(0x04001000)) & 7;
    u32 cnt = IO_R(&R16(0x0400100c));
    u32 scr = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0: case 1: case 2: case 3: case 4:
        return HostVram_CpuPtr(0x06200000 + (scr << 11));
    case 5:
        if (cnt & 0x80) return HostVram_CpuPtr(0x06200000 + (scr << 14));
        return HostVram_CpuPtr(0x06200000 + (scr << 11));
    case 6:
        return 0;
    default:
        return 0;
    }
}
void *G2_GetBG3ScrPtr(void) {
    u32 mode = IO_R(&R32(0x04000000)) & 7;
    u32 cnt = IO_R(&R16(0x0400000e));
    u32 base = ((IO_R(&R32(0x04000000)) & 0x38000000) >> 27) << 16;
    u32 scr = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0: case 1: case 2:
        return HostVram_CpuPtr(0x06000000 + base + (scr << 11));
    case 3: case 4: case 5:
        if (cnt & 0x80) return HostVram_CpuPtr(0x06000000 + (scr << 14));
        return HostVram_CpuPtr(0x06000000 + base + (scr << 11));
    case 6:
        return 0;
    default:
        return 0;
    }
}
void *G2S_GetBG3ScrPtr(void) {
    u32 mode = IO_R(&R32(0x04001000)) & 7;
    u32 cnt = IO_R(&R16(0x0400100e));
    u32 scr = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0: case 1: case 2:
        return HostVram_CpuPtr(0x06200000 + (scr << 11));
    case 3: case 4: case 5:
        if (cnt & 0x80) return HostVram_CpuPtr(0x06200000 + (scr << 14));
        return HostVram_CpuPtr(0x06200000 + (scr << 11));
    case 6:
        return 0;
    default:
        return 0;
    }
}
void *G2_GetBG0CharPtr(void) {
    u32 cnt = (IO_R(&R16(0x04000008)) & 0x3c) >> 2;
    u32 base = ((IO_R(&R32(0x04000000)) & 0x07000000) >> 24) << 16;
    return HostVram_CpuPtr(0x06000000 + base + (cnt << 14));
}
void *G2S_GetBG0CharPtr(void) {
    return HostVram_CpuPtr(0x06200000 + (((IO_R(&R16(0x04001008)) & 0x3c) >> 2) << 14));
}
void *G2_GetBG1CharPtr(void) {
    u32 cnt = (IO_R(&R16(0x0400000a)) & 0x3c) >> 2;
    u32 base = ((IO_R(&R32(0x04000000)) & 0x07000000) >> 24) << 16;
    return HostVram_CpuPtr(0x06000000 + base + (cnt << 14));
}
void *G2S_GetBG1CharPtr(void) {
    return HostVram_CpuPtr(0x06200000 + (((IO_R(&R16(0x0400100a)) & 0x3c) >> 2) << 14));
}
void *G2_GetBG2CharPtr(void) {
    s32 mode = IO_R(&R32(0x04000000)) & 7;
    u32 cnt = IO_R(&R16(0x0400000c));
    if (mode < 5 || !(cnt & 0x80)) {
        u32 base = ((IO_R(&R32(0x04000000)) & 0x07000000) >> 24) << 16;
        return HostVram_CpuPtr(0x06000000 + base + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}
void *G2S_GetBG2CharPtr(void) {
    s32 mode = IO_R(&R32(0x04001000)) & 7;
    u32 cnt = IO_R(&R16(0x0400100c));
    if (mode < 5 || !(cnt & 0x80)) return HostVram_CpuPtr(0x06200000 + (((cnt & 0x3c) >> 2) << 14));
    return 0;
}
void *G2_GetBG3CharPtr(void) {
    s32 mode = IO_R(&R32(0x04000000)) & 7;
    u32 cnt = IO_R(&R16(0x0400000e));
    if (mode < 3 || (mode < 6 && !(cnt & 0x80))) {
        u32 base = ((IO_R(&R32(0x04000000)) & 0x07000000) >> 24) << 16;
        return HostVram_CpuPtr(0x06000000 + base + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}
void *G2S_GetBG3CharPtr(void) {
    s32 mode = IO_R(&R32(0x04001000)) & 7;
    u32 cnt = IO_R(&R16(0x0400100e));
    if (mode < 3 || (mode < 6 && !(cnt & 0x80))) return HostVram_CpuPtr(0x06200000 + (((cnt & 0x3c) >> 2) << 14));
    return 0;
}
void GX_VRAMCNT_SetLCDC_(u32 mask) {
    if (mask & 0x001) IO_W(&R8(0x04000240), 0x80);
    if (mask & 0x002) IO_W(&R8(0x04000241), 0x80);
    if (mask & 0x004) IO_W(&R8(0x04000242), 0x80);
    if (mask & 0x008) IO_W(&R8(0x04000243), 0x80);
    if (mask & 0x010) IO_W(&R8(0x04000244), 0x80);
    if (mask & 0x020) IO_W(&R8(0x04000245), 0x80);
    if (mask & 0x040) IO_W(&R8(0x04000246), 0x80);
    if (mask & 0x080) IO_W(&R8(0x04000248), 0x80);
    if (mask & 0x100) IO_W(&R8(0x04000249), 0x80);
}
