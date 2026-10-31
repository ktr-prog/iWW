#include "nitro/fs.h"
#include "host_mem.h"
#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/autoload_2/unk_021239ec.h"
#include "proto/autoload_2/unk_02125c94.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "uptr.h"
typedef int s32;
typedef int BOOL;

extern s32 FS_ReadFile(FSFile *file, void *dst, s32 len);
extern BOOL FS_SeekFile(FSFile *file, s32 pos, u32 origin);
extern void FS_CloseFile(FSFile *file);
extern BOOL FS_OpenFileDirect(FSFile *file, void *arc, u32 top, u32 bottom, int id);
extern void DC_FlushRange(void *addr, u32 len);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern u32 AutoloadCallback[1];

typedef struct MBRegion {
    u32 start;
    u32 len;
} MBRegion;

typedef struct MBRomImageHeader {
    u8 pad00[0x20];
    u32 arm9RomOffset;
    u32 arm9Entry;
    u32 arm9RamAddr;
    u32 arm9Size;
    u32 arm7RomOffset;
    u32 arm7Entry;
    u32 arm7RamAddr;
    u32 arm7Size;
    u8 pad40[0x20];
    u32 romCtrl;
    u8 pad64[0x1c];
    u32 romSize;
    u8 pad84[0x160 - 0x84];
} MBRomImageHeader;

typedef struct MBiCacheInfo {
    u32 src;
    u32 len;
    u8 *ptr;
    u32 state;
} MBiCacheInfo;

typedef struct MBiCacheList {
    u32 lifetime;
    u32 recent;
    MBiCacheInfo *p_list;
    u32 size;
    char arc_name[4];
    u32 arc_name_len;
    void *arc_pointer;
    u8 reserved[0x30 - 0x1c];
    MBiCacheInfo list[4];
} MBiCacheList;

typedef struct MBSegmentSrc {
    u32 reserved;
    u32 arm9Src;
    u32 arm7Src;
    u32 pad;
} MBSegmentSrc;

typedef struct MBSegmentHeaderInfo {
    u32 romOffset;
    u32 ramDiff;
    u32 bufDiff;
    u32 len;
} MBSegmentHeaderInfo;

extern void MBi_AttachCacheBuffer(MBiCacheList *list, u32 src, u32 len, void *ptr, u32 state);
extern void MBi_ReadSegmentHeader(MBSegmentHeaderInfo *info, u32 start, u32 end, BOOL clear);

const MBRegion data_0213a3f8[3] = {{0x4000, 0x1000}, {0x7000, 0x1000}, {0, 0}};
const MBRegion *data_0213c204 = data_0213a3f8;

static inline void ReadRegion(MBSegmentHeaderInfo *info, const MBRegion *r) {
    MBi_ReadSegmentHeader(info, r->start, r->start + r->len, FALSE);
}

static inline u32 GetRomSize(const MBRomImageHeader *h) {
    u32 size = h->romSize;
    if (size == 0) {
        size = 0x1000000;
    }
    return size;
}

BOOL MB_ReadSegment(FSFile *file, void *buf, u32 len) {
    BOOL ret = FALSE;
    if (len >= 0x164) {
        MBRomImageHeader *rom = (MBRomImageHeader *)buf;
        u32 rest = len;
        u8 *p = (u8 *)buf;
        BOOL own = FALSE;
        MBiCacheList *cache = NULL;
        MBSegmentSrc *src = NULL;
        u32 top;
        u32 romSize;
        FSFile tmp;
        p += 0x160;
        rest -= 0x160;
        if (file != NULL) {
            top = (u32)(file->prop.file.pos - file->prop.file.start);
            if (FS_ReadFile(file, buf, 0x160) < 0x160) {
                rest = 0;
            }
            romSize = GetRomSize(rom);
        } else {
            romSize = GetRomSize(HW_SYSWORK(const MBRomImageHeader, romHeader));
            own = TRUE;
            FS_InitFile(&tmp);
            FS_OpenFileDirect(&tmp, FS_FindArchive("rom", 3), 0, romSize + 0x88, -1);
            file = &tmp;
            top = (u32)(file->prop.file.pos - file->prop.file.start);
            MI_CpuCopy8(HW_SYSWORK(void, romHeader), buf, 0x160);
            rom->romCtrl |= 0x00406000;
        }
        if (rest < 0x88) {
            rest = 0;
        } else {
            FS_SeekFile(file, (s32)(top + romSize), 0);
            FS_ReadFile(file, p, 0x88);
            p += 0x88;
            rest -= 0x88;
        }
        if (rest >= 0x70) {
            const char *name;
            int i;
            cache = (MBiCacheList *)p;
            MBi_InitCache(cache);
            p += 0x70;
            rest -= 0x70;
            MBi_AttachCacheBuffer(cache, 0, 0x160, buf, 3);
            name = (const char *)file->arc;
            for (i = 0; i < 3 && name[i] != 0; i++) {
            }
            MI_CpuCopy8(name, cache->arc_name, (u32)i);
            cache->arc_name_len = (u32)i;
        } else {
            rest = 0;
        }
        if (rest < 0x10) {
            rest = 0;
        } else {
            ((MBSegmentSrc *)p)->reserved = 0;
            ((MBSegmentSrc *)p)->arm9Src = rom->arm9RomOffset + (top + file->prop.file.start);
            ((MBSegmentSrc *)p)->arm7Src = rom->arm7RomOffset + (top + file->prop.file.start);
            src = (MBSegmentSrc *)p;
            p += 0x10;
            rest -= 0x10;
        }
        if (rest >= rom->arm9Size + rom->arm7Size) {
            u32 start = (u32)file->prop.file.start;
            FS_SeekFile(file, (s32)(src->arm9Src - start), 0);
            FS_ReadFile(file, p, (s32)rom->arm9Size);
            MBi_AttachCacheBuffer(cache, src->arm9Src, rom->arm9Size, p, 3);
            p += rom->arm9Size;
            FS_SeekFile(file, (s32)(src->arm7Src - start), 0);
            FS_ReadFile(file, p, (s32)rom->arm7Size);
            MBi_AttachCacheBuffer(cache, src->arm7Src, rom->arm7Size, p, 3);
            ret = TRUE;
        } else if (rest >= 0xcc00) {
            u32 start = (u32)file->prop.file.start;
            u32 s = src->arm9Src;
            FS_SeekFile(file, (s32)(s - start), 0);
            FS_ReadFile(file, p, 0x4400);
            MBi_AttachCacheBuffer(cache, s, 0x4400, p, 3);
            FS_SeekFile(file, (s32)(s + 0x4400 - start), 0);
            FS_ReadFile(file, p + 0x4400, 0x4400);
            MBi_AttachCacheBuffer(cache, s + 0x4400, 0x4400, p + 0x4400, 2);
            FS_SeekFile(file, (s32)(s + 0x8800 - start), 0);
            FS_ReadFile(file, p + 0x8800, 0x4400);
            MBi_AttachCacheBuffer(cache, s + 0x8800, 0x4400, p + 0x8800, 2);
            ret = TRUE;
        }
        FS_SeekFile(file, (s32)top, 0);
        if (own) {
            FS_CloseFile(&tmp);
            if (ret) {
                MBSegmentHeaderInfo info;
                const MBRegion *r = data_0213c204;
                info.romOffset = rom->arm9RomOffset;
                info.ramDiff = rom->arm9RamAddr - rom->arm9RomOffset;
                info.bufDiff = (u32)(uptr)cache->list[1].ptr - rom->arm9RomOffset;
                info.len = len;
                MBi_ReadSegmentHeader(&info, 0x4000, 0x8000, TRUE);
                for (; r->len != 0; r++) {
                    ReadRegion(&info, r);
                }
                {
                    u8 *dst = (u8 *)cache->list[1].ptr;
                    dst += ((u32)(uptr)&AutoloadCallback - rom->arm9RamAddr);
                    *(u32 *)dst = 0xe12fff1e;
                }
            }
        }
        if (ret) {
            DC_FlushRange(buf, len);
        }
    }
    return ret;
}
