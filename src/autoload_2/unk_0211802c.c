#include "nitro/fs.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_0211802c.h"
#include "proto/autoload_2/unk_021182b8.h"
#include "proto/autoload_2/unk_02118894.h"
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

int FSi_OpenFileFastCommand(FSFile *file) {
    u32 out[2];
    FSStream s;
    FSArc *arc = file->arc;
    u32 id = file->arg.openfilefast.id.file_id;
    u32 off = id << 3;
    if (off >= arc->fat_size) return 1;
    s.arc = arc;
    s.pos = arc->fat + off;
    FSi_ReadTable(&s, out, 8);
    file->arg.openfiledirect.top = out[0];
    file->arg.openfiledirect.bottom = out[1];
    file->arg.openfiledirect.index = id;
    return FSi_TranslateCommand(file, 7);
}

int FSi_OpenFileDirectCommand(FSFile *file) {
    file->prop.file.start = file->arg.openfiledirect.top;
    file->prop.file.pos = file->arg.openfiledirect.top;
    file->prop.file.end = file->arg.openfiledirect.bottom;
    file->prop.file.own_id = file->arg.openfiledirect.index;
    return 0;
}

int FSi_CloseFileCommand(void) {
    return 0;
}

void FSi_ReleaseCommand(FSFile *file, u32 result) {
    u32 irq = OS_DisableInterrupts();
    FSFile *prev = file->prev;
    FSFile *next = file->next;
    if (prev) prev->next = next;
    if (next) next->prev = prev;
    file->prev = 0;
    file->next = file->prev;
    file->stat &= ~0x4f;
    file->error = result;
    OS_WakeupThread(&file->queue);
    OS_RestoreInterrupts(irq);
}

int FSi_TranslateCommand(FSFile *file, u32 cmd) {
    int ret;
    u32 bit = 1 << cmd;
    FSArc *arc = file->arc;
    if (FSi_IsBlocking(file) != 0) {
        arc->flag |= 0x200;
    } else {
        arc->flag |= 0x100;
    }
    if (arc->proc_mask & bit) {
        ret = arc->proc(file, cmd);
        switch (ret) {
        case 0:
        case 1:
        case 4:
            file->error = ret;
            break;
        case 8:
            arc->proc_mask &= ~bit;
            ret = 7;
            break;
        }
    } else {
        ret = 7;
    }
    if (ret == 7) {
        ret = data_0213a388[cmd](file);
    }
    if (ret == 6) {
        if (FSi_IsBlocking(file) != 0) {
            u32 irq = OS_DisableInterrupts();
            while (arc->flag & 0x200) OS_SleepThread(&arc->queue);
            ret = file->error;
            OS_RestoreInterrupts(irq);
        }
    } else if (FSi_IsBlocking(file) != 0) {
        arc->flag &= ~0x200;
        file->error = ret;
    } else {
        arc->flag &= ~0x100;
        FSi_ReleaseCommand(file, ret);
    }
    return ret;
}

int (*const data_0213a388[9])(FSFile *) = {
    FSi_ReadFileCommand,
    FSi_WriteFileCommand,
    FSi_SeekDirCommand,
    FSi_ReadDirCommand,
    FSi_FindPathCommand,
    FSi_GetPathCommand,
    FSi_OpenFileFastCommand,
    FSi_OpenFileDirectCommand,
    (int (*)(FSFile *))FSi_CloseFileCommand,
};
