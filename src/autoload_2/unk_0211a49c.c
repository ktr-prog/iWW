#include "sys/DtorEntry.h"
#include "host_mem.h"
#include "nitro/fs.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/autoload_2/unk_02119f84.h"
#include "proto/autoload_2/unk_0211a258.h"
#include "proto/autoload_2/unk_0211a49c.h"
#include "proto/autoload_2/unk_0211a6c0.h"
#include "proto/autoload_2/unk_0211dc4c.h"
#include "proto/main/unk_0206d49c.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;

typedef struct {
    u32 w[23];
} MD5Context;

typedef struct {
    u8 b[20];
} Digest20;

typedef struct DtorEntry DtorEntry;

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void MI_CpuFill8(void *dst, u32 v, u32 n);
extern void MI_CpuCopy8(const void *src, void *dst, u32 n);
extern int FSi_TranslateCommand(FSFile *file, u32 cmd);
extern void FSi_ReleaseCommand(FSFile *file, u32 result);
extern void FS_NotifyArchiveAsyncEnd(FSArc *arc, u32 result);
extern void FS_SetArchiveProc(FSArc *arc, int (*proc)(FSFile *, u32), u32 mask);
extern void FS_LoadArchive(FSArc *arc, uptr base, u32 fat, u32 fat_size, u32 fnt, u32 fnt_size,
                          int (*read)(FSArc *, void *, u32, u32), int (*write)(FSArc *, void *, u32, u32));
extern void FS_RegisterArchiveName(FSArc *arc, const char *name, int len);
extern BOOL FSi_SendCommand(FSFile *file, u32 cmd);
extern u32 OS_GetLockID(void);
extern void CARD_UnlockRom(u32);
extern void CARD_LockRom(u32);
extern void CARDi_ReadRom(u32 dma, u32 src, void *dst, u32 len, void (*cb)(FSArc *), FSArc *arg, BOOL async);
extern void DC_FlushRange(u32 addr, u32 len);
extern void DC_InvalidateRange(u32 addr, u32 len);
extern void IC_InvalidateRange(u32 addr, u32 len);
extern void MIi_UncompressBackward(u32 addr);
extern void DGT_Hash2CalcHmac(void *digest, const void *data, u32 len, const void *key, u32 keylen);
extern void DGT_Hash1Reset(MD5Context *ctx);
extern void DGT_Hash1SetSource(MD5Context *ctx, const void *data, u32 len);
extern void DGT_Hash1GetDigest_R(void *digest, MD5Context *ctx);

extern FSDirPos data_021fea6c;
extern u32 data_021fea78;
extern u32 data_021fea7c;
extern u32 data_021fea80;
extern FSOvtCache data_021fea84;
extern FSOvtCache data_021fea8c;
extern FSArc data_021fea94;
extern char data_0213bff8[];
extern u8 *data_0213bffc;
extern u32 data_0213c000;
extern DtorEntry *data_0220066c;
extern Digest20 data_020e74ec[];
extern Digest20 data_020e74ec_end[];

#define REG_BOOTTYPE (*HW_SYSWORK(volatile u16, wmBootBuf))

static inline BOOL IsBusy(volatile FSFile *f) {
    BOOL r;
    r = (f->stat & 1) != 0;
    return r;
}
static inline BOOL IsCanceled(volatile FSFile *f) {
    BOOL r;
    r = (f->stat & 2) != 0;
    return r;
}
static inline BOOL IsBlocking(volatile FSFile *f) {
    BOOL r;
    r = (f->stat & 4) != 0;
    return r;
}
static inline BOOL IsSuspended(volatile FSArc *a) {
    BOOL r;
    r = (a->flag & 8) != 0;
    return r;
}
static inline BOOL IsStarted(volatile FSArc *a) {
    BOOL r;
    r = (a->flag & 0x10) != 0;
    return r;
}
static inline const FSROMTable *GetFNT(void) {
    return HW_SYSWORK_AT(const FSROMTable, romHeader, 0x40);
}
static inline const FSROMTable *GetFAT(void) {
    return HW_SYSWORK_AT(const FSROMTable, romHeader, 0x48);
}
static inline BOOL IsLoaded(volatile FSArc *a) {
    BOOL r;
    r = (a->flag & 2) != 0;
    return r;
}
static inline BOOL IsIdle(volatile FSFile *f) {
    BOOL r;
    r = (f->stat & 0x44) == 0;
    return r;
}

int FSi_RomArchiveProc(FSFile *file, u32 cmd);
u32 FSi_ReadDummyCallback(void);
u32 FSi_EmptyArchiveProc(void);
u32 FSi_WriteDummyCallback(void);
int FSi_ReadRomCallback(FSArc *arc, void *dst, u32 src, u32 len);
void FSi_InitRom(u32 dma);
BOOL FS_OpenFileFast(FSFile *file, FSFileID id);
BOOL FS_OpenFileDirect(FSFile *file, FSArc *arc, u32 start, u32 end, int id);
BOOL FS_ConvertPathToFileID(FSFileID *id, const char *path);
BOOL FSi_FindPath(FSFile *file, const char *path, FSFileID *id, FSDirPos *pos);
s32 FSi_ReadFileCore(FSFile *file, void *dst, s32 len, BOOL async);
s32 FS_ReadFile(FSFile *file, void *dst, s32 len);
BOOL FS_CloseFile(FSFile *file);
BOOL FS_WaitAsync(FSFile *file);
BOOL FSi_CompareDigest(const u8 *expected, const void *data, u32 len);
BOOL FS_LoadOverlayImage(FSOverlayInfo *p);
BOOL FS_LoadOverlayInfo(FSOverlayInfo *p, int target, u32 id);
BOOL FS_UnloadOverlayImage(FSOverlayInfo *p);
u32 FSi_GetOverlayBinarySize(const FSOverlayInfoHeader *h);

static void FSi_SetOverlayHeader(FSOverlayInfoHeader *h, const u32 *r) {
    h->id = r[0];
    h->ram_address = r[1];
    h->ram_size = r[2];
    h->bss_size = r[3];
    h->sinit_init = (void (**)(void))(uptr)r[4];
    h->sinit_init_end = (void (**)(void))(uptr)r[5];
    h->file_id = r[6];
    h->compressed = r[7] & 0xffffff;
    h->flag = r[7] >> 24;
}

BOOL FSi_LoadOverlayInfoCore(FSOverlayInfo *p, int target, u32 id, FSArc *arc, u32 offset_arm9, u32 len_arm9, u32 offset_arm7, u32 len_arm7) {
    FSROMTable pr[1];
    u32 pos;
    if (target == 0) {
        pr->offset = offset_arm9;
        pr->length = len_arm9;
    } else {
        pr->offset = offset_arm7;
        pr->length = len_arm7;
    }
    pos = id * 32;
    if (pos >= pr->length) return 0;
    {
        FSFile file[1];
        FS_InitFile(file);
        if (!FS_OpenFileDirect(file, arc, pr->offset + pos, pr->offset + pr->length, -1)) return 0;
        u32 rec[8];
        if (FS_ReadFile(file, rec, 32) != 32) {
            FS_CloseFile(file);
            return 0;
        }
        FS_CloseFile(file);
        FSi_SetOverlayHeader(&p->header, rec);
        p->target = target;
        if (!FS_OpenFileFast(file, FS_GetOverlayFileID(&p->header))) return 0;
        p->start = file->prop.file.start;
        p->length = file->prop.file.end - file->prop.file.start;
        FS_CloseFile(file);
        return 1;
    }
}

static inline const FSROMTable *GetOVT(int target) {
    return (target == 0) ? HW_SYSWORK_AT(const FSROMTable, romHeader, 0x50) : HW_SYSWORK_AT(const FSROMTable, romHeader, 0x58);
}
BOOL FS_LoadOverlayInfo(FSOverlayInfo *p, int target, u32 id) {
    const FSOvtCache *t = (target == 0) ? &data_021fea84 : &data_021fea8c;
    if (t->ptr) {
        FSFile file[1];
        const u32 pos = id * 32;
        if (pos >= t->size) return 0;
        u32 rec[8];
        MI_CpuCopy8(t->ptr + pos, rec, 32);
        FSi_SetOverlayHeader(&p->header, rec);
        p->target = target;
        FS_InitFile(file);
        if (!FS_OpenFileFast(file, FS_GetOverlayFileID(&p->header))) return 0;
        p->start = file->prop.file.start;
        p->length = file->prop.file.end - file->prop.file.start;
        FS_CloseFile(file);
        return 1;
    } else {
        const FSROMTable *const rom9 = GetOVT(0);
        const FSROMTable *const rom7 = GetOVT(1);
        return FSi_LoadOverlayInfoCore(p, target, id, &data_021fea94, rom9->offset, rom9->length, rom7->offset, rom7->length);
    }
}
