#include "uptr.h"
#include "host_mem.h"
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
extern u32 MBi_SendMP(void *p, u32 a, u32 b);
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
extern u32 MBi_BlockHeaderEnd(u32 a, u32 b, void *c);
extern u32 MBi_calc_cksum(const u16 *p, int len);
extern u32 MB_GetSegmentLength(FSFile *file);
extern BOOL MB_ReadSegment(FSFile *file, u32 *buf, u32 size);
extern void MBi_ReadSegmentHeader(u32 *seg, u32 lo, u32 hi, int clear);
extern BOOL MB_RegisterFile(const u8 *key, const MBRomHeader *info);
extern void MBi_MakeDownloadFileInfo(MBSegInfo *dst, const MBRomHeader *rom);
extern void MBi_SetSegmentInfo(const MBRomHeader *rom, const u32 *mode, MBRange *out, u32 *limit);

void MBi_InitSendFixedBeacon(void) {
    MBBuf *c;
    if (data_021fff8c.state != 2) return;
    c = data_021fff8c.cur;
    if (c->f4b2 == 0) {
        data_021fff8c.p10 = 9;
        data_021fff8c.p8 = c;
    } else {
        data_021fff8c.p10 = 4;
        data_021fff8c.p8 = c->f220;
    }
    data_021fff8c.state = 3;
}

void MBi_SendFixedBeacon(u32 a, u32 b, u32 c) {
    u8 *end;
    u8 *p8;
    end = &data_021fff8c.cur->f358;
    p8 = (u8 *)data_021fff8c.p8;
    if (p8 + 0x62 <= end) {
        data_021fffa0.c.b = 0x62;
    } else {
        volatile u16 zero = 0;
        data_021fffa0.c.b = (u8)(end - p8);
        MIi_CpuClear16(zero, data_021fffae + data_021fffa0.c.b, 0x62 - data_021fffa0.c.b);
    }
    MIi_CpuCopy16(data_021fff8c.p8, data_021fffae, data_021fffa0.c.b);
    data_021fffa0.ha = data_021fff8c.pf;
    data_021fffa0.hb = data_021fff8c.p10;
    data_021fffa0.b4 = (data_021fffa0.b4 & ~3) | (data_021fff8c.cur->f4b2 & 3);
    data_021fffa0.b5 = data_021fff8c.cur->f4b3;
    data_021fffa0.b6 = data_021fff8c.pe;
    data_021fffa0.w0 = data_021fff8c.cur->f4b8;
    data_021fffa0.b4 = (data_021fffa0.b4 & ~0xfc) | ((data_021fff8c.cur->f4b5 & 0x3f) << 2);
    data_021fffa0.b7 = data_021fff8c.p11++;
    data_021fffa0.h8 = 0;
    data_021fffa0.h8 = MBi_calc_cksum(data_021fffa8, 0x68);
    data_021fff8c.pf++;
    if (data_021fff8c.pf < data_021fff8c.p10) {
        data_021fff8c.p8 = (u8 *)data_021fff8c.p8 + 0x62;
    } else {
        data_021fff8c.state = 4;
    }
    WM_SetGameInfo(0, &data_021fffa0, 0x70, a, b, (u8)(c | 2));
}

void MBi_InitSendVolatBeacon(void) {
    data_021fff8c.cur->f4b0 = 1;
    data_021fff8c.pe = data_021fff8c.cur->f4b4;
    data_021fff8c.state = 5;
}

void MBi_SendVolatBeacon(u32 a, u32 b, u32 c) {
    u32 cnt;
    u8 *dst;
    int off;
    u32 diff;
    u32 bit;
    int i;
    if (data_021fff8c.pe != data_021fff8c.cur->f4b4) MBi_InitSendVolatBeacon();
    data_021fffa0.b4 = (data_021fffa0.b4 & ~3) | 2;
    data_021fffa0.b5 = data_021fff8c.cur->f4b3;
    data_021fffa0.b6 = data_021fff8c.pe;
    data_021fffa0.w0 = data_021fff8c.cur->f4b8;
    data_021fffa0.b4 = (data_021fffa0.b4 & ~0xfc) | ((data_021fff8c.cur->f4b5 & 0x3f) << 2);
    data_021fffa0.b7 = data_021fff8c.p11++;
    data_021fffa0.ha = data_021fff8c.cur->f358;
    data_021fffa0.c.h = data_021fff8c.cur->f35a;
    data_021fffa0.he = data_021fff8c.cur->f35c;
    if (data_021fff84 == 0 && data_021fff88 != 0) data_021fff88(data_021fff8c.cur->f4b8);
    for (i = 0; i < 8; i++) data_021fffa0.f68[i] = data_021fff8c.cur->f4a8[i];
    {
        volatile u16 zero = 0;
        MIi_CpuClear16(zero, data_021fffb0, 0x58);
    }
    cnt = 0;
    dst = (u8 *)data_021fffb0;
    diff = (u16)(data_021fff8c.cur->f4b0 ^ data_021fff8c.cur->f35a);
    for (off = i = 0; i < 15; i++) {
        bit = 2 << i;
        if (diff & bit) {
            MIi_CpuCopy16(data_021fff8c.cur->f35e + off, dst, 22);
            dst += 22;
            cnt++;
            data_021fff8c.cur->f4b0 |= bit;
            if (cnt == 4) break;
        }
        off += 22;
    }
    if (cnt < 4) data_021fffb0[cnt][0] &= ~0xf0;
    data_021fffa0.h8 = 0;
    data_021fffa0.h8 = MBi_calc_cksum(data_021fffa8, 0x68);
    if (data_021fff8c.cur->f4b0 == data_021fff8c.cur->f35a) data_021fff8c.state = 1;
    WM_SetGameInfo(0, &data_021fffa0, 0x70, a, b, (u8)(c | 2));
    if (data_021fff84 != 1) return;
    if (data_021fff88 == 0) return;
    data_021fff88(data_021fff8c.cur->f4b8);
}

u32 MBi_BlockHeaderEnd(u32 a, u32 b, void *c) {
    DC_FlushRange(c, (a + 31) & ~31);
    DC_WaitWriteBufferEmpty();
    return MBi_SendMP(c, a, b);
}

u32 MBi_calc_cksum(const u16 *p, int len) {
    u32 sum = 0;
    int n = len >> 1;
    while (n > 0) {
        sum += *p++;
        n--;
    }
    sum = (sum & 0xffff) + (sum >> 16);
    sum += sum >> 16;
    return (u16)(sum ^ 0xffff);
}

u32 MB_GetSegmentLength(FSFile *file) {
    u32 buf[24];
    u32 *hdr = 0;
    u32 size = 0;
    if (file != 0) {
        u32 pos = file->prop.file.pos - file->prop.file.start;
        if ((u32)FS_ReadFile(file, buf, 0x60) >= 0x60) hdr = buf;
        FS_SeekFile(file, pos, 0);
    } else {
        hdr = HW_SYSWORK(u32, romHeader);
    }
    if (hdr != 0) {
        size = hdr[11] + 0x268 + hdr[15];
        if (size < 0x10000) size = 0x10000;
    }
    return size;
}
