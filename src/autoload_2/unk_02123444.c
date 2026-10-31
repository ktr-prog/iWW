#include "nitro/fs.h"
#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/autoload_2/unk_02123444.h"
#include "proto/autoload_2/unk_02123e58.h"
#include "proto/autoload_2/unk_02124480.h"
#include "proto/autoload_2/unk_02125c94.h"
#include "proto/main/unk_0206d49c.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "uptr.h"
typedef int s32;
typedef signed char s8;
typedef int BOOL;

typedef struct MBBuf {
    u8 pad0[0x220];
    u8 f220[0x16];
    u8 f236;
    u8 pad237;
    u8 f238[0x60];
    u8 f298[0xc0];
    u8 f358;
    u8 pad359;
    u16 f35a;
    u16 f35c;
    u8 f35e[0x14a];
    u8 f4a8[8];
    u16 f4b0;
    u8 f4b2;
    u8 f4b3;
    u8 f4b4;
    u8 f4b5;
    u8 pad4b6[2];
    u32 f4b8;
    struct MBBuf *next;
} MBBuf;

typedef struct MBWork {
    MBBuf *head;
    MBBuf *cur;
    void *p8;
    u8 state;
    u8 pd;
    u8 pe;
    u8 pf;
    u8 p10;
    u8 p11;
} MBWork;

typedef struct MBBeacon {
    u32 w0;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
    u16 h8;
    u8 ha;
    u8 hb;
    union {
        u8 b;
        u16 h;
    } c;
    u16 he;
    u8 pad10[0x68 - 0x10];
    u8 f68[8];
} MBBeacon;

typedef struct MBSeg {
    u32 addr;
    u32 size;
} MBSeg;

typedef struct MBRomHeader {
    u32 w[9];
    u32 arm9Entry;
    MBSeg arm9;
    u32 arm7Off;
    u32 arm7Entry;
    MBSeg arm7;
    u8 rest[0x160 - 0x40];
} MBRomHeader;

typedef struct MBRange {
    u32 start;
    u32 addr;
    u32 size;
    u32 flags;
} MBRange;

typedef struct MBSegInfo {
    u32 arm9Entry;
    u32 arm7Entry;
    u32 pad8;
    MBRange r[3];
    u8 hdr[0x88];
} MBSegInfo;

typedef struct MBEnt {
    MBSegInfo seg;
    u8 name[0x20];
    MBBuf buf;
    u8 x[0x14];
    const u8 *key;
    const MBRomHeader *info;
    u8 pad5c0[6];
    u16 f5c6;
    u8 pad5c8[2];
    u8 used;
    u8 pad5cb;
    const u8 *p0;
    const u8 *p1;
} MBEnt;

typedef struct MBBig {
    u8 pad0[0x1300];
    u8 f1300[0x224];
    u8 count;
    u8 pad1525[0x1788 - 0x1525];
    MBEnt ent[16];
} MBBig;

extern MBBig *data_0220001c;
u8 data_021fff80;
extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32 irq);
extern BOOL MBi_IsStarted(void);
extern BOOL MBi_MakeBlockInfoTable(void *dst, void *seg);
extern BOOL MBi_IsTaskAvailable(void);
extern void MBi_InitTaskThread(void *p, u32 len);

MBBeacon data_021fffa0;
MBWork data_021fff8c;
void (*data_021fff88)(u32);
u32 data_021fff84;
#define data_021fffa8 ((u16 *)((u8 *)&data_021fffa0 + 8))
#define data_021fffae ((u8 *)&data_021fffa0 + 0xe)
#define data_021fffb0 (*(u8 (*)[4][22])((u8 *)&data_021fffa0 + 0x10))
extern u32 MBi_calc_cksum(const u16 *p, int len);
extern void WM_SetGameInfo(u32 a, void *p, u32 len, u32 b, u32 c, u32 d);

extern void MIi_CpuClear16(u32 value, void *dst, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern BOOL FS_OpenFile(FSFile *file, const char *path);
extern s32 FS_ReadFile(FSFile *file, void *dst, s32 len);
extern BOOL FS_SeekFile(FSFile *file, s32 pos, u32 origin);
extern void DC_FlushRange(void *addr, u32 len);
extern void DC_WaitWriteBufferEmpty(void);
extern void MI_CpuFill8(void *dst, u32 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern const u32 data_0213a3ec[3];
extern void MBi_MakeDownloadFileInfo(MBSegInfo *dst, const MBRomHeader *rom);
extern void MBi_SetSegmentInfo(const MBRomHeader *rom, const u32 *mode, MBRange *out, u32 *limit);
extern void MBi_AttachCacheBuffer(void *ctx, u32 addr, u32 len, void *data, u32 mode);
extern void DC_FlushRange(void *addr, u32 len);
typedef struct MBRegion {
    u32 start;
    u32 len;
} MBRegion;
extern MBRegion *data_0213c204;
extern char data_0213c208[];
extern u8 AutoloadCallback[];
extern BOOL FS_OpenFileDirect(FSFile *file, void *arc, u32 top, u32 bottom, int id);
extern void MBi_SendMP(void *p, u32 a, u32 b);
extern void FS_CloseFile(FSFile *file);
extern u32 mystrlen(const u16 *s);
extern BOOL MBi_ReadIconInfo(const char *path, void *dst, u32 isChar);

extern BOOL MBi_ReadyBeaconSendStatus(void);
extern void MBi_SendFixedBeacon(u32 a, u32 b, u32 c);
extern void MBi_SendVolatBeacon(u32 a, u32 b, u32 c);
extern void MBi_ReadSegmentHeader(u32 *seg, u32 lo, u32 hi, int clear);

extern void MBi_MakeGameInfo(MBBuf *b, const u32 *info, const void *name);
extern BOOL MBi_ReadIconInfo(const char *path, void *dst, u32 isChar);
extern void MB_UpdateGameInfoMember(MBBuf *b, const void *src, u32 mask, u32 w);
extern u32 mystrlen(const u16 *s);
extern void MB_AddGameInfo(MBBuf *b);
extern void MB_SendGameInfoBeacon(u32 a, u32 b, u32 c);
extern BOOL MBi_ReadyBeaconSendStatus(void);
extern void MBi_SendFixedBeacon(u32 a, u32 b, u32 c);
extern void MBi_SendVolatBeacon(u32 a, u32 b, u32 c);
extern void MBi_BlockHeaderEnd(u32 a, u32 b, void *c);
extern u32 MBi_calc_cksum(const u16 *p, int len);
extern u32 MB_GetSegmentLength(FSFile *file);
extern BOOL MB_ReadSegment(FSFile *file, u32 *buf, u32 size);
extern void MBi_ReadSegmentHeader(u32 *seg, u32 lo, u32 hi, int clear);
extern BOOL MB_RegisterFile(const u8 *key, const MBRomHeader *info);
extern void MBi_MakeDownloadFileInfo(MBSegInfo *dst, const MBRomHeader *rom);
extern void MBi_SetSegmentInfo(const MBRomHeader *rom, const u32 *mode, MBRange *out, u32 *limit);

void MBi_ReadSegmentHeader(u32 *seg, u32 lo, u32 hi, int clear) {
    u32 base = seg[0];
    u32 len = seg[3];
    if (lo < 0x4000) lo = 0x4000;
    if (hi > 0x8000) hi = 0x8000;
    if (lo < base) lo = base;
    if (hi > base + len) hi = base + len;
    if (lo >= hi) return;
    if (clear) {
        MI_CpuFill8((u8 *)(uptr)seg[2] + lo, 0, hi - lo);
    } else {
        MI_CpuCopy8((u8 *)(uptr)seg[1] + lo, (u8 *)(uptr)seg[2] + lo, hi - lo);
    }
}

BOOL MB_RegisterFile(const u8 *key, const MBRomHeader *info) {
    MBEnt *e;
    u8 idx = 0xff;
    u32 irq = OS_DisableInterrupts();
    u32 off;
    u8 i;
    u8 seq;
    if (MBi_IsStarted() == 0) {
        OS_RestoreInterrupts(irq);
        return 0;
    }
    if (data_0220001c->count + 1 > 16) {
        OS_RestoreInterrupts(irq);
        return 0;
    }
    for (i = 0; i < 16; i = (u8)(i + 1)) {
        if (data_0220001c->ent[i].key == key) {
            OS_RestoreInterrupts(irq);
            return 0;
        }
        if (data_0220001c->ent[i].used == 0) {
            idx = i;
            break;
        }
    }
    if (i == 16) {
        OS_RestoreInterrupts(irq);
        return 0;
    }
    off = idx * sizeof(MBEnt);
    data_0220001c->ent[idx].key = key;
    e = (MBEnt *)((u8 *)data_0220001c + 0x1788 + off);
    MBi_MakeDownloadFileInfo(&e->seg, info);
    MI_CpuCopy8(key + 0x1c, e->name, 0x20);
    if (MBi_MakeBlockInfoTable((u8 *)data_0220001c + 0x1d2c + off, e) == 0) {
        OS_RestoreInterrupts(irq);
        return 0;
    }
    MBi_MakeGameInfo((MBBuf *)((u8 *)data_0220001c + 0x186c + off), (const u32 *)key, data_0220001c->f1300 - 0 + 0);
    data_0220001c->ent[idx].buf.f4b5 = idx;
    MB_AddGameInfo((MBBuf *)((u8 *)data_0220001c + 0x186c + off));
    seq = data_021fff80;
    data_021fff80 = seq + 1;
    data_0220001c->ent[idx].buf.f4b3 = seq;
    data_0220001c->ent[idx].f5c6 = 1;
    data_0220001c->ent[idx].info = info;
    data_0220001c->ent[idx].p0 = (const u8 *)info + 0x1e8;
    data_0220001c->ent[idx].p1 = (const u8 *)info + 0x258;
    if (((const u32 *)data_0220001c->ent[idx].p0)[0x6c / 4] != 0) {
        if (MBi_IsTaskAvailable() == 0) {
            MBi_InitTaskInfo((u8 *)data_0220001c + 0x7ce0);
            MBi_InitTaskThread((u8 *)data_0220001c + 0x74e0, 0x800);
        }
    }
    data_0220001c->ent[idx].used = 1;
    data_0220001c->count++;
    OS_RestoreInterrupts(irq);
    return 1;
}

void MBi_MakeDownloadFileInfo(MBSegInfo *dst, const MBRomHeader *rom) {
    u32 limit = 0x22c0000;
    const u32 *m;
    MBRange *o;
    int i;
    const u8 *src;
    dst->arm9Entry = rom->arm9Entry;
    src = (const u8 *)rom + 0x160;
    dst->arm7Entry = rom->arm7Entry;
    o = dst->r;
    m = data_0213a3ec;
    for (i = 0; i < 3; i++) {
        MBi_SetSegmentInfo(rom, m, o, &limit);
        o++;
        m++;
    }
    MI_CpuCopy8(src, dst->hdr, 0x88);
}

void MBi_SetSegmentInfo(const MBRomHeader *rom, const u32 *mode, MBRange *out, u32 *limit) {
    switch (*mode) {
    case 0: {
        const MBSeg *p = &rom->arm9;
        if (p->addr >= 0x2000000 && p->addr < 0x22c0000 && p->addr + p->size <= 0x22c0000) {
            out->size = p->size;
            out->addr = p->addr;
            out->start = out->addr;
            out->flags &= ~1;
        } else {
            Fatal_Trap();
        }
        break;
    }
    case 1: {
        u32 wram;
        u32 bad;
        const MBSeg *p = &rom->arm7;
        u32 end = p->addr + p->size;
        wram = bad = 0;
        if (p->addr >= 0x2000000 && p->addr < 0x23fe800) {
            if (end > 0x2300000) {
                if (end < 0x23fe800 && p->size <= 0x40000) wram = 1;
                else bad = 1;
            }
        } else if (p->addr >= 0x37f8000 && p->addr < 0x380f000) {
            if (end <= 0x380f000) wram = 1;
            else bad = 1;
        } else {
            bad = 1;
        }
        if (bad == 1) Fatal_Trap();
        out->size = p->size;
        out->addr = p->addr;
        if (wram == 0) {
            out->start = out->addr;
        } else {
            out->start = *limit;
            *limit += out->size;
        }
        out->flags = (out->flags & ~1) | 1;
        break;
    }
    case 2:
        out->size = 0x160;
        out->addr = 0x27ffe00;
        out->start = out->addr;
        out->flags &= ~1;
        break;
    }
}
