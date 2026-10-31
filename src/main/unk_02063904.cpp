#include "types.h"
#include "nitro/fs.h"

#include "ds_stdarg.h"
#include "gfx/G3dResAccess.h"
#include "game/Random.h"
#include "proto/autoload_2/unk_020e7500.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_021127c0.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_02055c38.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"


struct FileLzHeader {
    u32 magic;
    union {
        u32 w;
        struct {
            u32 lg : 4;
            u32 rest : 28;
        } b;
    };
};

extern "C" {
void MI_CpuCopy8(const void *src, void *dst, u32 n);
}

extern "C" {
void MI_CpuFill8(void *p, u32 v, u32 n);
}

extern "C" {
s32 FX_Div(s32 a, s32 b);
}

extern "C" {
s32 func_01ffcb0c(s32 a, s32 b);
}


extern "C" {
s32 FS_UnloadOverlay(s32 a, s32 b);
}


extern "C" {
BOOL FS_OpenFileFast(void *f, FSFileID id);
}

extern "C" {
BOOL FS_CloseFile(void *f);
}

extern "C" {
s32 FS_SeekFile(void *f, s32 off, s32 z);
}

extern "C" {
s32 FS_ReadFile(void *f, void *dst, u32 n);
}

extern "C" {
void MI_UncompressLZ8(const void *src, void *dst);
}

extern "C" {
u32 _u32_div_f(u32 a, u32 b);
}


struct FileBlockCache {
    u16 tbl[0x100];
    u32 raw[0x400];
    u8 out[0x1000];
};


extern "C" {
enum FileBlockType { Unk_02063d18_T0 = 0, Unk_02063d18_T10 = 0x10, Unk_02063d18_TF0 = 0xf0 };
}


extern "C" BOOL File_Exists(const char *a) {
    FSFile f;
    BOOL r = File_Open(&f, a);
    if (r) FS_CloseFile(&f);
    return r;
}

extern "C" void File_ReadRangeByPath(const char *a, void *dst, u32 size, u32 off) {
    FSFile f;
    File_OpenOrPanic(&f, a);
    File_ReadRange(&f, dst, size, off);
    FS_CloseFile(&f);
}

extern "C" void File_ReadRangeById(FSFileID id, void *dst, u32 size, u32 off) {
    FSFile f;
    FS_InitFile(&f);
    if (FS_OpenFileFast(&f, id)) {
        File_ReadRange(&f, dst, size, off);
        FS_CloseFile(&f);
    }
}

extern "C" void File_ReadRange(FSFile *f, void *dst, u32 size, u32 off) {
    FileLzHeader hdr;
    u32 n, nblk, base;
    s32 len, c;
    u32 end, lo, hi;
    u32 blk, i;
    s32 a, b;

    FS_SeekFile(f, 0, 0);
    if (FS_ReadFile(f, &hdr, 8) == -1) return;
    if (hdr.magic == 0x37375a4c || hdr.magic == 0x4c5a3737) {
        if ((hdr.w & 0xf0) != 0xf0) return;
        if ((u32)(f->prop.file.end - f->prop.file.start) > 0xffff) return;
        blk = 0x20 << hdr.b.lg;
        sFileBlockCache.tbl[0] = 0;
        n = ((_u32_div_f((hdr.w >> 8) - 1, blk) + 1)) * 2;
        FS_ReadFile(f, (u8 *)sFileBlockCache.tbl + 2, n);
        base = n + 8;
        end = off + size;
        nblk = _u32_div_f(end - 1, blk) + 1;
        for (i = _u32_div_f(off, blk); i < nblk; i++) {
            hi = blk * (i + 1);
            if (off >= hi) continue;
            lo = blk * i;
            if (end <= lo) continue;
            if (f->prop.file.own_id != sFileBlockCacheFileId || i != sFileBlockCacheIndex) {
                sFileBlockCacheFileId = f->prop.file.own_id;
                sFileBlockCacheIndex = i;
                u16 *tp = sFileBlockCache.tbl + i;
                u32 t0 = tp[0];
                len = tp[1] - t0;
                FS_SeekFile(f, base + t0, 0);
                FS_ReadFile(f, sFileBlockCache.raw, len);
                u32 w = sFileBlockCache.raw[0];
                FileBlockType ty = (FileBlockType)(w & 0xf0);
                u32 sz = w >> 8;
                if (ty == Unk_02063d18_T0) {
                    MI_CpuCopy8((u8 *)sFileBlockCache.raw + 4, sFileBlockCache.out, sz);
                } else {
                    MI_UncompressLZ8(sFileBlockCache.raw, sFileBlockCache.out);
                }
            }
            a = off - lo;
            if (a < 0) a = 0;
            b = hi - end;
            if (b < 0) b = 0;
            c = blk - a - b;
            MI_CpuCopy8(sFileBlockCache.out + a, dst, c);
            dst = (u8 *)dst + c;
        }
    } else {
        FS_SeekFile(f, off, 0);
        FS_ReadFile(f, dst, size);
    }
}

extern "C" s32 File_LoadOverlay(s32 x) { return File_LoadOverlayEx(0, x); }

extern "C" s32 File_UnloadOverlay(s32 x) { return FS_UnloadOverlay(0, x); }

extern "C" void BlinkTimer_Construct() {}

extern "C" void BlinkTimer_Destruct() {}

extern "C" void BlinkTimer_StartBlink(u8 *p) {
    p[1] = (Random_Next(&gRandom.seed) >> 31) + 1;
}

extern "C" BOOL BlinkTimer_Update(u8 *p) {
    u32 t = p[0];
    if (t == 0) {
        t = p[1];
        if (t == 0) {
            BlinkTimer_StartBlink(p);
            p[0] = Random_NextBelow(&gRandom.seed, 0x5a) + 0x1e;
        } else {
            p[1] = t - 1;
            return TRUE;
        }
    } else {
        p[0] = t - 1;
    }
    return FALSE;
}

extern "C" void BlinkTimer_Clear(u8 *p) {
    p[1] = 0;
    p[0] = p[1];
}

extern "C" void BlinkTimer_BlinkNow(u8 *p) {
    p[0] = 0;
    if (p[1] == 0) BlinkTimer_StartBlink(p);
}

extern "C" s32 Math_AngleToSide(s32 x) {
    if (x > 0 && x < 0x8000) return 0;
    if (x > -0x8000 && x < 0) return 1;
    return 2;
}

extern "C" s32 Math_AngleToDir4(s32 x) {
    if (x <= -0x6000) return 2;
    if (x <= -0x2000) return 3;
    if (x <= 0x2000) return 0;
    if (x <= 0x6000) return 1;
    return 2;
}

extern "C" s32 Math_AngleToDir8(s32 x) {
    if (x <= -0x7556) return 4;
    if (x <= -0x4aaa) return 5;
    if (x <= -0x3556) return 6;
    if (x <= -0xaaa) return 7;
    if (x <= 0xaaa) return 0;
    if (x <= 0x3556) return 1;
    if (x <= 0x4aaa) return 2;
    if (x <= 0x7556) return 3;
    return 4;
}

#pragma thumb off
extern "C" u32 Random_GlobalBelow(u32 n) { return Random_NextBelow(&gRandom.seed, n); }

extern "C" u32 Random_GlobalBelow2(u32 n) { return Random_NextBelow(&gRandom.seed, n); }
#pragma thumb reset

extern "C" s32 Math_EaseRampProgress(s32 x, s32 lo, s32 hi, s32 a, s32 b) {
    if (x >= hi) return 0x1000;
    if (x <= lo) return 0;
    s32 w = hi - lo;
    s32 t = x - lo;
    if (w < a + b) return 0;
    s32 k = FX_Div(0x1000, w * 2 - a - b);
    s32 r = 0;
    if (a != 0) {
        if (t <= a) {
            s32 v = FX_Div(func_01ffcb0c(k, func_01ffcb0c(t, t)), a);
            if (v > 0x1000) return 0x1000;
            return v;
        }
        r = func_01ffcb0c(k, a);
    }
    if (t <= w - b) {
        r = r + (func_01ffcb0c(k, t - a) << 1);
        if (r > 0x1000) return 0x1000;
        return r;
    }
    r += func_01ffcb0c(k, w - a - b) << 1;
    if (b != 0) {
        r += func_01ffcb0c(k, b);
        if (t < w) {
            r -= FX_Div(func_01ffcb0c(k, func_01ffcb0c(w - t, w - t)), b);
        }
    }
    if (r > 0x1000) r = 0x1000;
    return r;
}

extern "C" void G3dRes_CopyTexByName(void *a, void *b, const char *c, const char *d) {
    void *p = ((G3dResAccess *)a)->findTexData(c);
    s32 i = ((G3dResAccess *)b)->findTexIdx(d);
    void *q = ((G3dResAccess *)b)->getTexData(i);
    u32 n = ((G3dResAccess *)b)->getTexSize(i);
    MI_CpuCopy8(p, q, n);
}

extern "C" void G3dRes_CopyPlttByName(void *a, void *b, const char *c, const char *d) {
    void *p = ((G3dResAccess *)a)->findPlttData(c);
    s32 i = ((G3dResAccess *)b)->findPlttIdx(d);
    void *q = ((G3dResAccess *)b)->getPlttData(i);
    u32 n = ((G3dResAccess *)b)->getPlttSize(i);
    MI_CpuCopy8(p, q, n);
}

extern "C" BOOL Mem_Differs(const void *a, const void *b, u32 n) {
    if (memcmp(a, b, n)) return TRUE;
    return FALSE;
}

extern "C" s32 Str_SPrintf(char *buf, const char *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    return Str_VSPrintf(buf, fmt, va);
}

extern "C" s32 Str_VSPrintf(char *buf, const char *fmt, va_list va) { return Str_VSNPrintf(buf, 0x7fffffff, fmt, va); }

extern "C" s32 Str_VSNPrintf(char *buf, u32 n, const char *fmt, va_list va) { return OS_VSNPrintf(buf, n, fmt, va); }

extern "C" void TownId_Construct() {}

extern "C" void TownId_Destruct() {}

extern "C" void TownId_Clear(u16 *p) {
    MI_CpuFill8(p + 1, 0, 8);
    *p = 0;
}

extern "C" void TownId_Assign(void *dst, void *src) { MI_CpuCopy8(src, dst, 10); }

extern "C" void TownId_CopyFrom(u16 *dst, u16 *src) {
    *dst = *src;
    MI_CpuCopy8(src + 1, dst + 1, 8);
}

extern "C" void TownId_CopyTo(u16 *src, u16 *dst) {
    *dst = *src;
    MI_CpuCopy8(src + 1, dst + 1, 8);
}

extern "C" u16 *TownId_GetName(u16 *p) { return p + 1; }

extern "C" BOOL TownId_IsValid(u16 *p) {
    BOOL r = FALSE;
    if (*p != 0) r = TRUE;
    return r;
}

extern "C" void TownId_SetId(u16 *p, u16 v) { *p = v; }

extern "C" u16 TownId_GenerateId(void *p) {
    u32 r = (u16)Random_GlobalBelow(0x7fff);
    r |= 0x8000;
    return (u16)r;
}

extern "C" void TownId_InitWithName(u16 *p, const void *src) {
    TownId_Clear(p);
    MI_CpuCopy8(src, p + 1, 8);
    *p = TownId_GenerateId(p);
}


u8 sFileBlockCacheIndex;

u16 sFileBlockCacheFileId;

FileBlockCache sFileBlockCache;
