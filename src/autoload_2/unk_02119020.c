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

BOOL FSi_SendCommand(FSFile *file, u32 cmd) {
    FSArc *arc = file->arc;
    u32 bit;
    u32 irq;
    FSFile *q;
    u32 irq2;
    file->command = cmd;
    file->error = 2;
    bit = 1 << cmd;
    file->stat |= 1;
    irq = OS_DisableInterrupts();
    if (arc->flag & 0x80) {
        FSi_ReleaseCommand(file, 3);
        OS_RestoreInterrupts(irq);
        return 0;
    }
    q = (FSFile *)&arc->list;
    if (bit & 0x1fc) {
        file->stat |= 4;
    }
    {
        FSFile *prev = file->prev;
        FSFile *next = file->next;
        if (prev) prev->next = next;
        if (next) next->prev = prev;
    }
    {
        while (q->next) q = q->next;
        q->next = file;
        file->prev = q;
        file->next = 0;
    }
    if (FSi_IsSuspended(arc) == 0 && (arc->flag & 0x10) == 0) {
        arc->flag |= 0x10;
        OS_RestoreInterrupts(irq);
        if (arc->proc_mask & 0x200) {
            arc->proc(file, 9);
        }
        irq2 = OS_DisableInterrupts();
        file->stat |= 0x40;
        if (FSi_IsBlocking(file) == 0) {
            OS_RestoreInterrupts(irq2);
            FSi_ExecuteAsyncCommand(file);
            return 1;
        }
        OS_RestoreInterrupts(irq2);
    } else {
        if (FSi_IsBlocking(file) == 0) {
            OS_RestoreInterrupts(irq);
            return 1;
        }
        do {
            OS_SleepThread(&file->queue);
        } while (!(file->stat & 0x40));
        OS_RestoreInterrupts(irq);
    }
    return FSi_ExecuteSyncCommand(file);
}

void FS_InitArchive(FSArc *arc) {
    MI_CpuFill8(arc, 0, sizeof(FSArc));
    arc->queue.tail = 0;
    arc->queue.head = arc->queue.tail;
    arc->queue2.tail = 0;
    arc->queue2.head = arc->queue2.tail;
}

FSArc *FS_FindArchive(const char *name, int len) {
    u32 pack = FSi_GetPackedName(name, len);
    u32 irq = OS_DisableInterrupts();
    FSArc *arc;
    for (arc = data_021fea68; arc && arc->name != pack; arc = arc->next) {
    }
    OS_RestoreInterrupts(irq);
    return arc;
}

BOOL FS_RegisterArchiveName(FSArc *arc, const char *name, int len) {
    BOOL ret = 0;
    u32 irq = OS_DisableInterrupts();
    if (!FS_FindArchive(name, len)) {
        FSArc *p = data_021fea68;
        if (!p) {
            data_021fea68 = arc;
            data_021fea6c.arc = arc;
            data_021fea6c.pos = 0;
            data_021fea6c.u.d.index = 0;
            data_021fea6c.u.d.own_id = 0;
        } else {
            while (p->next) p = p->next;
            p->next = arc;
            arc->prev = p;
        }
        arc->name = FSi_GetPackedName(name, len);
        ret = 1;
        arc->flag |= 1;
    }
    OS_RestoreInterrupts(irq);
    return ret;
}

void FS_ReleaseArchiveName(FSArc *arc) {
    if (arc->name) {
        u32 irq = OS_DisableInterrupts();
        if (arc->next) arc->next->prev = arc->prev;
        if (arc->prev) arc->prev->next = arc->next;
        arc->name = 0;
        arc->prev = 0;
        arc->next = arc->prev;
        arc->flag &= ~1;
        if (data_021fea6c.arc == arc) {
            data_021fea6c.pos = 0;
            data_021fea6c.arc = data_021fea68;
            data_021fea6c.u.d.index = 0;
            data_021fea6c.u.d.own_id = 0;
        }
        OS_RestoreInterrupts(irq);
    }
}

BOOL FS_LoadArchive(FSArc *arc, uptr base, u32 fat, u32 fat_size, u32 fnt, u32 fnt_size, FSIoFunc rd, FSIoFunc wr) {
    FSIoFunc r;
    FSIoFunc w;
    arc->base = base;
    arc->fat_size = fat_size;
    arc->fat_orig = fat;
    arc->fat = arc->fat_orig;
    arc->fnt_size = fnt_size;
    arc->fnt_orig = fnt;
    arc->fnt = arc->fnt_orig;
    r = rd;
    if (r == 0) r = FSi_ReadMemCallback;
    arc->read_orig = r;
    w = wr;
    if (w == 0) w = FSi_WriteMemCallback;
    arc->write = w;
    arc->read = arc->read_orig;
    arc->load_mem = 0;
    arc->flag |= 2;
    return 1;
}

FSArc *data_021fea68;
FSDirPos data_021fea6c;
