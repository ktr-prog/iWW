#include "types.h"
#include "net/WfcRect.h"
#include "sys/StackPad.h"
#include "nitro/io_access.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov001/unk_ov001_02225924.h"

#pragma thumb off



typedef volatile u16 vu16;
typedef volatile u32 vu32;

extern "C" {
u32 OS_DisableIrqMask(u32 a);
void OS_EnableIrqMask(u32 a);
void NNS_FndFreeToExpHeap(void *heap, void *p);
void *NNS_FndAllocFromExpHeapEx(void *heap, u32 size, u32 b);
void NNS_FndDestroyExpHeap(void *heap);
void *NNS_FndCreateExpHeapEx(void *buf, u32 size, u32 b);
void MI_CpuFill8(void *p, u32 v, u32 size);

void WfcUtil_RectFromPosSize(WfcPoint *a, WfcPoint *b, WfcRect *out);
void WfcUtil_SetRect(u32 a, u32 b, u32 c, u32 d, WfcRect *out);
void WfcUtil_SetPoint(u32 a, u32 b, WfcPoint *out);
void WfcGx_SetWindowPlanes(u32 eng, u32 which, u32 v, u32 on);
void WfcGx_SetWindowRect(u32 eng, u32 which, WfcRect *r);
void WfcGx_HidePlanes(u32 eng, u32 m);
void WfcGx_ShowPlanes(u32 eng, u32 m);
void WfcHeap_Free(void *p);
void WfcHeap_FreeAndClear(void **pp);
void *WfcHeap_AllocClear(u32 size, u32 b);
void *WfcHeap_Alloc(u32 size, u32 b);
void WfcHeap_Destroy();
void WfcHeap_Init(void *buf);

void *sWfcHeap;
}

static inline void Unk_ov001_02225ae8_Set(uptr ha, uptr va, WfcRect *r) {
    u32 x1 = r->left;
    u32 x2 = r->right;
    u32 y1 = r->top;
    u32 y2 = r->bottom;
    *(vu16 *)ha = ((x1 << 8) & 0xff00) | (x2 & 0xff);
    *(vu16 *)va = ((y1 << 8) & 0xff00) | (y2 & 0xff);
}

void WfcHeap_Init(void *buf) {
    MI_CpuFill8(buf, 0, 0x40000);
    sWfcHeap = NNS_FndCreateExpHeapEx(buf, 0x40000, 0);
    if (sWfcHeap == 0) Fatal_Trap();
}

void WfcHeap_Destroy() {
    NNS_FndDestroyExpHeap(sWfcHeap);
    sWfcHeap = 0;
}

void *WfcHeap_Alloc(u32 size, u32 b) {
    void *p;
    u32 irq = OS_DisableIrqMask(1);
    p = NNS_FndAllocFromExpHeapEx(sWfcHeap, size, b);
    if (p == 0) Fatal_Trap();
    OS_EnableIrqMask(irq);
    return p;
}

void *WfcHeap_AllocClear(u32 size, u32 b) {
    void *p = WfcHeap_Alloc(size, b);
    MI_CpuFill8(p, 0, size);
    return p;
}

void WfcHeap_FreeAndClear(void **pp) {
    u32 irq = OS_DisableIrqMask(1);
    if (*pp == 0) return;
    NNS_FndFreeToExpHeap(sWfcHeap, *pp);
    OS_EnableIrqMask(irq);
    *pp = 0;
}

void WfcHeap_Free(void *p) {
    u32 irq = OS_DisableIrqMask(1);
    if (p == 0) return;
    NNS_FndFreeToExpHeap(sWfcHeap, p);
    OS_EnableIrqMask(irq);
}

void WfcGx_ShowPlanes(u32 eng, u32 m) {
    if (eng == 1) {
        u32 t = (IO_R((vu32 *)0x4001000) & 0x1f00) >> 8;
        IO_W((vu32 *)0x4001000, (IO_R((vu32 *)0x4001000) & ~0x1f00) | ((m | t) << 8));
    } else {
        u32 t = (IO_R((vu32 *)0x4000000) & 0x1f00) >> 8;
        IO_W((vu32 *)0x4000000, (IO_R((vu32 *)0x4000000) & ~0x1f00) | ((m | t) << 8));
    }
}

void WfcGx_HidePlanes(u32 eng, u32 m) {
    if (eng == 1) {
        u32 t = (IO_R((vu32 *)0x4001000) & 0x1f00) >> 8;
        IO_W((vu32 *)0x4001000, (IO_R((vu32 *)0x4001000) & ~0x1f00) | ((~m & t) << 8));
    } else {
        u32 t = (IO_R((vu32 *)0x4000000) & 0x1f00) >> 8;
        IO_W((vu32 *)0x4000000, (IO_R((vu32 *)0x4000000) & ~0x1f00) | ((~m & t) << 8));
    }
}

void WfcGx_SetWindowRect(u32 eng, u32 which, WfcRect *r) {
    StackPad4 pad;
    if (eng == 1) {
        if (which == 0) {
            Unk_ov001_02225ae8_Set(0x4001040, 0x4001044, r);
        } else {
            Unk_ov001_02225ae8_Set(0x4001042, 0x4001046, r);
        }
    } else {
        if (which == 0) {
            Unk_ov001_02225ae8_Set(0x4000040, 0x4000044, r);
        } else {
            Unk_ov001_02225ae8_Set(0x4000042, 0x4000046, r);
        }
    }
}

void WfcGx_SetWindowPlanes(u32 eng, u32 which, u32 v, u32 on) {
    switch (which) {
    case 0:
        if (eng == 1) {
            vu16 *r = (vu16 *)0x4001048;
            u32 t = (IO_R(r) & ~0x3f) | v;
            if (on != 0) t |= 0x20;
            IO_W((vu16 *)0x4001048, t);
        } else {
            u32 t = (IO_R((vu16 *)0x4000048) & ~0x3f) | v;
            if (on != 0) t |= 0x20;
            IO_W((vu16 *)0x4000048, t);
        }
        break;
    case 1:
        if (eng == 1) {
            u32 t = (IO_R((vu16 *)0x4001048) & ~0x3f00) | (v << 8);
            if (on != 0) t |= 0x2000;
            IO_W((vu16 *)0x4001048, t);
        } else {
            u32 t = (IO_R((vu16 *)0x4000048) & ~0x3f00) | (v << 8);
            if (on != 0) t |= 0x2000;
            IO_W((vu16 *)0x4000048, t);
        }
        break;
    case 2:
        if (eng == 1) {
            u32 t = (IO_R((vu16 *)0x400104a) & ~0x3f00) | (v << 8);
            if (on != 0) t |= 0x2000;
            IO_W((vu16 *)0x400104a, t);
        } else {
            u32 t = (IO_R((vu16 *)0x400004a) & ~0x3f00) | (v << 8);
            if (on != 0) t |= 0x2000;
            IO_W((vu16 *)0x400004a, t);
        }
        break;
    case 3:
        if (eng == 1) {
            u32 t = (IO_R((vu16 *)0x400104a) & ~0x3f) | v;
            if (on != 0) t |= 0x20;
            IO_W((vu16 *)0x400104a, t);
        } else {
            u32 t = (IO_R((vu16 *)0x400004a) & ~0x3f) | v;
            if (on != 0) t |= 0x20;
            IO_W((vu16 *)0x400004a, t);
        }
        break;
    }
}

void WfcUtil_SetPoint(u32 a, u32 b, WfcPoint *out) {
    out->x = a;
    out->y = b;
}

void WfcUtil_SetRect(u32 a, u32 b, u32 c, u32 d, WfcRect *out) {
    out->left = a;
    out->top = b;
    out->right = c;
    out->bottom = d;
}

void WfcUtil_RectFromPosSize(WfcPoint *a, WfcPoint *b, WfcRect *out) {
    out->left = a->x;
    out->top = a->y;
    out->right = a->x + b->x;
    out->bottom = a->y + b->y;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02225924) {
    HOST_OVERLAY_VAR(sWfcHeap),
    HOST_OVERLAY_VARS_END
};
