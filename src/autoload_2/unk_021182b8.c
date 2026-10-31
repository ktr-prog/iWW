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

typedef struct {
    union {
        FSFileID file_id;
        FSDirPos dir_id;
    } u;
    u32 is_dir;
    u32 name_len;
    char name[128];
} FSDirEntry2;
int FSi_FindPathCommand(FSFile *file) {
    const u8 *path = (const u8 *)file->arg.findpath.path;
    const BOOL find_directory = file->arg.findpath.find_directory;
    FSi_TranslateCommand(file, 2);
    for (; *path; path += (*path ? 1 : 0)) {
        u32 is_directory;
        int name_len = 0;
        while ((is_directory = *(u8 *)(path + name_len)), FSi_IsPathChar(is_directory) != 0) {
            ++name_len;
        }
        if (is_directory || find_directory) {
            is_directory = 1;
        }
        if (name_len == 0) {
            return 1;
        } else if (*path == '.') {
            if (name_len == 1) {
                path += 1;
                continue;
            } else if ((name_len == 2) & (path[1] == '.')) {
                if (file->prop.dir.pos.u.d.own_id != 0) {
                    FSi_SeekDirDirect(file, file->prop.dir.parent);
                }
                path += 2;
                continue;
            }
        }
        if (name_len > 127) {
            return 1;
        } else {
            FSDirEntry2 etr;
            file->arg.rdent.ent = (FSEntry *)&etr;
            file->arg.rdent.skip = 0;
            for (;;) {
                if (FSi_TranslateCommand(file, 3) != 0) return 1;
                if ((is_directory != etr.is_dir) || (name_len != etr.name_len) || FSi_StrNICmp((const char *)path, etr.name, (u32)name_len)) continue;
                if (is_directory) {
                    path += name_len;
                    file->arg.pos = etr.u.dir_id;
                    FSi_TranslateCommand(file, 2);
                    break;
                } else {
                    if (find_directory) return 1;
                    *(FSFileID *)file->arg.findpath.result = etr.u.file_id;
                    return 0;
                }
            }
        }
    }
    if (!find_directory) return 1;
    *(FSDirPos *)file->arg.findpath.result = file->prop.dir.pos;
    return 0;
}

int FSi_GetPathCommand(FSFile *file) {
    FSEntry ent;
    FSFile tmp;
    FSArc *arc = file->arc;
    struct {
        void *buf;
        u32 buf_size;
        u16 len;
        u16 dirid;
    } *arg = (void *)&file->arg.path;
    u32 dir;
    u32 target;
    char *buf;
    u32 len;
    u32 n;
    u32 i;
    u32 cnt;
    FS_InitFile(&tmp);
    tmp.arc = file->arc;
    if (FSi_IsDirOnly(file) != 0) {
        dir = file->prop.dir.pos.u.d.own_id;
        target = 0x10000;
    } else {
        target = file->prop.file.own_id;
        if (arg->len != 0) {
            dir = arg->dirid;
        } else {
            i = 0;
            cnt = 0;
            dir = 0x10000;
            do {
                FSi_SeekDirDirect(&tmp, i);
                if (i == 0) cnt = tmp.prop.dir.parent;
                tmp.arg.rdent.ent = &ent;
                tmp.arg.rdent.skip = 1;
                if (FSi_TranslateCommand(&tmp, 3) == 0) {
                    for (;;) {
                        if (ent.is_dir == 0 && ent.pos.u.file_id == target) {
                            dir = tmp.prop.dir.pos.u.d.own_id;
                            break;
                        }
                        if (FSi_TranslateCommand(&tmp, 3) != 0) break;
                    }
                }
                if (dir != 0x10000) break;
                i++;
            } while (i < cnt);
        }
    }
    if (dir == 0x10000) {
        arg->len = 0;
        return 1;
    }
    if (arg->len == 0) {
        cnt = 0;
        if (arc->name <= 0xff) {
            cnt += 1;
        } else if (arc->name <= 0xff00) {
            cnt += 2;
        } else {
            cnt += 3;
        }
        cnt += 2;
        if (target != 0x10000) cnt += ent.name_len;
        i = dir;
        if (i != 0) {
            FSi_SeekDirDirect(&tmp, dir);
            do {
                FSi_SeekDirDirect(&tmp, tmp.prop.dir.parent);
                tmp.arg.rdent.ent = &ent;
                tmp.arg.rdent.skip = 1;
                if (FSi_TranslateCommand(&tmp, 3) == 0) {
                    for (;;) {
                        if (ent.is_dir != 0 && ent.pos.u.d.own_id == i) {
                            cnt += ent.name_len + 1;
                            break;
                        }
                        if (FSi_TranslateCommand(&tmp, 3) != 0) break;
                    }
                }
                i = tmp.prop.dir.pos.u.d.own_id;
            } while (i != 0);
        }
        arg->len = cnt + 1;
        arg->dirid = dir;
    }
    buf = (char *)arg->buf;
    if (buf == 0) return 0;
    len = arg->len;
    if (arg->buf_size < len) return 1;
    {
    u32 pos = 0;
    u32 n = FSi_NameLen2(arc->name);
    MI_CpuCopy8(arc, buf + pos, n);
    pos += n;
    MI_CpuCopy8(":/", buf + pos, 2);
    pos += 2;
    }
    FSi_SeekDirDirect(&tmp, dir);
    if (target != 0x10000) {
        tmp.arg.rdent.ent = &ent;
        tmp.arg.rdent.skip = 0;
        if (FSi_TranslateCommand(&tmp, 3) == 0) {
            for (;;) {
                if (ent.is_dir == 0 && ent.pos.u.file_id == target) break;
                if (FSi_TranslateCommand(&tmp, 3) != 0) break;
            }
        }
        target = ent.name_len + 1;
        MI_CpuCopy8(ent.name, buf + len - target, target);
        len -= target;
    } else {
        *(buf + len - 1) = 0;
        len -= 1;
    }
    if (dir != 0) {
        do {
            FSi_SeekDirDirect(&tmp, tmp.prop.dir.parent);
            tmp.arg.rdent.ent = &ent;
            tmp.arg.rdent.skip = 0;
            *(buf + len - 1) = '/';
            len -= 1;
            if (FSi_TranslateCommand(&tmp, 3) == 0) {
                for (;;) {
                    if (ent.is_dir != 0 && ent.pos.u.d.own_id == dir) {
                        n = ent.name_len;
                        MI_CpuCopy8(ent.name, buf + len - n, n);
                        len -= n;
                        break;
                    }
                    if (FSi_TranslateCommand(&tmp, 3) != 0) break;
                }
            }
            dir = tmp.prop.dir.pos.u.d.own_id;
        } while (dir != 0);
    }
    return 0;
}
