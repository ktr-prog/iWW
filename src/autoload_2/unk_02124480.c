#include "nitro/fs.h"
#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
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
extern u8 data_021fff80;
extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32 irq);
extern BOOL MBi_IsStarted(void);
extern BOOL MBi_MakeBlockInfoTable(void *dst, void *seg);
extern BOOL MBi_IsTaskAvailable(void);
extern void MBi_InitTaskThread(void *p, u32 len);

extern MBBeacon data_021fffa0;
extern MBWork data_021fff8c;
extern void (*data_021fff88)(u32);
extern u32 data_021fff84;
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
extern u32 data_0213a3ec[3];
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

void MBi_MakeGameInfo(MBBuf *b, const u32 *info, const void *name) {
    volatile u16 zero16 = 0;
    u32 ok;
    MIi_CpuClear16(zero16, b, 0x4c0);
    b->f4b2 = 0;
    ok = MBi_ReadIconInfo((const char *)(uptr)info[3], b, 1) == 0;
    ok |= MBi_ReadIconInfo((const char *)(uptr)info[4], b, 0) == 0;
    if (ok) {
        volatile u32 zero32;
        b->f4b2 = 1;
        zero32 = 0;
        MIi_CpuClearFast(zero32, b, 0x220);
    }
    b->f4b8 = info[5];
    if (name != 0) MIi_CpuCopy16(name, b->f220, 0x16);
    b->f236 = ((u8 *)info)[0x18];
    MIi_CpuCopy16((const void *)(uptr)info[1], b->f238, (u16)(mystrlen((const u16 *)(uptr)info[1]) << 1));
    MIi_CpuCopy16((const void *)(uptr)info[2], b->f298, 0xc0);
    b->f358 = 1;
    b->f35a = 1;
    b->f4b0 = 1;
}

BOOL MBi_ReadIconInfo(const char *path, void *dst, u32 isChar) {
    FSFile f;
    u32 size = isChar ? 0x200 : 0x20;
    u8 *p = (u8 *)dst;
    if (isChar) p += 0x20;
    if (path == 0) return 0;
    FS_InitFile(&f);
    if (FS_OpenFile(&f, path) == 0) return 0;
    if (size != f.prop.file.end - f.prop.file.start) {
        FS_CloseFile(&f);
        return 0;
    }
    FS_ReadFile(&f, p, size);
    FS_CloseFile(&f);
    return 1;
}

void MB_UpdateGameInfoMember(MBBuf *b, const void *src, u32 mask, u32 w) {
    int i;
    u8 n = 1;
    MIi_CpuCopy16(src, b->f35e, 0x14a);
    for (i = 0; i < 15; i++) {
        if (mask & (2 << i)) n++;
    }
    b->f358 = n;
    b->f35a = mask | 1;
    b->f35c = w;
    b->f4b4++;
}

u32 mystrlen(const u16 *s) {
    u32 n = 0;
    while (*s++ != 0) n++;
    return n;
}

void MB_AddGameInfo(MBBuf *b) {
    if (data_021fff8c.head == 0) {
        data_021fff8c.head = b;
    } else {
        MBBuf *t = data_021fff8c.head;
        MBBuf *n = t->next;
        if (n != 0) {
            do {
                t = n;
                n = n->next;
            } while (n != 0);
        }
        t->next = b;
    }
    b->next = 0;
}

void MB_InitSendGameInfoStatus(void) {
    data_021fff8c.head = 0;
    data_021fff8c.cur = 0;
    data_021fff8c.state = 1;
    data_021fff88 = 0;
    MBi_ClearSendStatus();
}

void MBi_ClearSendStatus(void) {
    data_021fff8c.pd = 0;
    data_021fff8c.pe = 0;
    data_021fff8c.pf = 0;
    data_021fff8c.p10 = 0;
    data_021fff8c.p11 = 0;
}

void MB_SendGameInfoBeacon(u32 a, u32 b, u32 c) {
    for (;;) {
        switch (data_021fff8c.state) {
        case 0:
        case 1:
            if (MBi_ReadyBeaconSendStatus() == 0) return;
            break;
        case 2:
            MBi_InitSendFixedBeacon();
            break;
        case 3:
            MBi_SendFixedBeacon(a, b, c);
            return;
        case 4:
            MBi_InitSendVolatBeacon();
            break;
        case 5:
            MBi_SendVolatBeacon(a, b, c);
            return;
        case 6:
        default:
            break;
        }
    }
}
