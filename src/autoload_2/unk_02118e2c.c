#include "nitro/fs.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_0211802c.h"
#include "proto/autoload_2/unk_021182b8.h"
#include "proto/autoload_2/unk_02118894.h"
#include "proto/autoload_2/unk_02118e2c.h"
#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void MI_CpuFill8(void *dst, u32 v, u32 n);
extern void MI_CpuCopy8(const void *src, void *dst, u32 n);
extern BOOL FS_OpenFileDirect(FSFile *, FSArc *, u32, u32, int);
extern s32 FS_ReadFile(FSFile *, void *, s32);
extern void FS_CloseFile(FSFile *);
extern u32 FSi_GetPackedName(const char *, int);
extern int FSi_ReadMemoryCore(FSArc *, void *, u32, u32);
extern int FSi_ReadMemCallback(FSArc *, void *, u32, u32);
extern int FSi_WriteMemCallback(FSArc *, void *, u32, u32);
extern char data_0213bff4[];
extern FSArc *data_021fea68;
extern FSDirPos data_021fea6c;

static inline BOOL FSi_IsBlocking(FSFile *f) {
    return !!(f->stat & 4);
}

static inline BOOL FSi_IsSuspended(FSArc *a) {
    return !!(a->flag & 8);
}

static inline BOOL FSi_IsStarted(FSArc *a) {
    return !!(a->flag & 2);
}

static inline BOOL FSi_IsTableLoaded(FSArc *a) {
    return !!(a->flag & 4);
}

static inline BOOL FSi_IsPathChar(u32 c) {
    BOOL r = 0;
    if (c != 0 && c != '/' && c != '\\') r = 1;
    return r;
}

static inline BOOL FSi_IsDirOnly(FSFile *f) {
    return !!(f->stat & 0x20);
}

static inline u32 FSi_NameLen(u32 name) {
    u32 l = 0;
    if (name <= 0xff) {
        l += 1;
    } else if (name <= 0xff00) {
        l += 2;
    } else {
        l += 3;
    }
    return l;
}

static inline u32 FSi_NameLen2(u32 name) {
    if (name <= 0xff) return 1;
    if (name <= 0xff00) return 2;
    return 3;
}

int FSi_TranslateCommand(FSFile *file, u32 cmd);
void FSi_ReleaseCommand(FSFile *file, u32 result);
int FSi_SeekDirDirect(FSFile *file, u32 id);
void FSi_ReadTable(FSStream *s, void *dst, u32 len);
int FSi_StrNICmp(const char *a, const char *b, u32 n);
void FS_NotifyArchiveAsyncEnd(FSArc *arc, u32 result);
void FS_SetArchiveProc(FSArc *arc, int (*proc)(FSFile *, u32), u32 mask);
BOOL FS_ResumeArchive(FSArc *arc);
BOOL FS_SuspendArchive();
u32 FS_LoadArchiveTables(FSArc *arc, void *mem, u32 mem_max);
BOOL FS_UnloadArchive(FSArc *arc);
BOOL FS_LoadArchive(FSArc *arc, uptr base, u32 fat, u32 fat_size, u32 fnt, u32 fnt_size, FSIoFunc rd, FSIoFunc wr);
BOOL FS_RegisterArchiveName(FSArc *arc, const char *name, int len);
BOOL FSi_SendCommand(FSFile *file, u32 cmd);

u32 FS_LoadArchiveTables(FSArc *arc, void *mem, u32 mem_max) {
    u32 need = ((u32)(s32)(arc->fat_size + arc->fnt_size + 32) + 31) & ~31;
    if (need <= mem_max) {
        u8 *tbl = (u8 *)(((uptr)mem + 31) & ~(uptr)31);
        FSFile file;
        FS_InitFile(&file);
        if (FS_OpenFileDirect(&file, arc, arc->fat, arc->fat + arc->fat_size, -1)) {
            if (FS_ReadFile(&file, tbl, arc->fat_size) < 0) {
                MI_CpuFill8(tbl, 0, arc->fat_size);
            }
            FS_CloseFile(&file);
        }
        arc->fat = (u32)(tbl - (u8 *)mem);
        tbl += arc->fat_size;
        if (FS_OpenFileDirect(&file, arc, arc->fnt, arc->fnt + arc->fnt_size, -1)) {
            if (FS_ReadFile(&file, tbl, arc->fnt_size) < 0) {
                MI_CpuFill8(tbl, 0, arc->fnt_size);
            }
            FS_CloseFile(&file);
        }
        arc->fnt = (u32)(tbl - (u8 *)mem);
        arc->load_mem = mem;
        arc->read = FSi_ReadMemoryCore;
        arc->flag |= 4;
    }
    return need;
}
