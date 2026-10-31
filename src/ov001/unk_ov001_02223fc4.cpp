#include "types.h"
#include "nitro/fs.h"
#include "net/WfcPool.h"
#include "uptr.h"
#include "proto/autoload_2/unk_02118894.h"
#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_02225924.h"

#pragma thumb off

struct WfcFsWork {
    void *archiveTables;
    u32 fileSlotStorage[0x20];
    WfcPool *fileSlotPool;
    FSArc archive;
    u16 lockId;
};
#if !HOST64
static_assert(sizeof(WfcFsWork) == 0xe8, "DS layout");
#endif

extern "C" {
void WfcPool_Put(WfcPool *, void *);
void *WfcPool_Get(WfcPool *);
u32 strlen(const char *);
BOOL FS_OpenFile(FSFile *file, const char *path);
s32 FS_ReadFile(FSFile *file, void *dst, s32 len);
BOOL FS_CloseFile(FSFile *file);
void MI_UncompressLZ8(const void *src, void *dst);
void FS_NotifyArchiveAsyncEnd(FSArc *arc, u32 result);
void CARDi_ReadRom(u32 cmd, u32 off, void *dst, u32 len, void (*cb)(void *), void *arg, BOOL async);
void CARD_LockRom(u32 id);
void CARD_UnlockRom(u32 id);
BOOL FS_ChangeDir(const char *path);
BOOL FS_UnloadArchive(FSArc *arc);
void OS_ReleaseLockID(u16 id);
u32 OS_GetLockID();
BOOL FS_RegisterArchiveName(FSArc *arc, const char *name, int len);
void FS_SetArchiveProc(FSArc *arc, int (*proc)(FSFile *, u32), u32 mask);
BOOL FS_LoadArchive(FSArc *arc, uptr base, u32 fat, u32 fat_size, u32 fnt, u32 fnt_size, FSIoFunc rd, FSIoFunc wr);
u32 FS_LoadArchiveTables(FSArc *arc, void *mem, u32 mem_max);
s32 OS_SPrintf(char *dst, const char *fmt, ...);
}

extern "C" const char sWfcArchiveName[4];
extern "C" const char sWfcArchiveName[4] = "dwc";
extern "C" WfcFsWork *sWfcFs = 0;

extern "C" void WfcFs_MountArchive() {
    u32 a[2];
    u32 b[2];
    FSFile o;
    char path[0x80];
    u32 r4;
    sWfcFs = (WfcFsWork *)WfcHeap_AllocClear(sizeof(WfcFsWork), 4);
    FS_InitFile(&o);
    if (FS_OpenFile(&o, "rom:/dwc/utility.bin") == 0) {
        Fatal_Trap();
    }
    sWfcFs->lockId = OS_GetLockID();
    r4 = o.prop.file.start;
    FS_ReadFile(&o, a, 8);
    FS_ReadFile(&o, b, 8);
    FS_CloseFile(&o);
    FS_InitArchive(&sWfcFs->archive);
    if (FS_RegisterArchiveName(&sWfcFs->archive, sWfcArchiveName, 3) == 0) {
        Fatal_Trap();
    }
    FS_SetArchiveProc(&sWfcFs->archive, WfcFs_ArchiveProc, 0x602);
    if (FS_LoadArchive(&sWfcFs->archive, r4, b[0], b[1], a[0], a[1], WfcFs_ReadCallback, WfcFs_WriteCallback) == 0) {
        Fatal_Trap();
    }
    u32 tablesSize = FS_LoadArchiveTables(&sWfcFs->archive, 0, 0);
    sWfcFs->archiveTables = WfcHeap_Alloc(tablesSize, 4);
    FS_LoadArchiveTables(&sWfcFs->archive, sWfcFs->archiveTables, tablesSize);
    sWfcFs->fileSlotPool = WfcPool_CreateFrom(0x20, sWfcFs->fileSlotStorage, 4);
    OS_SPrintf(path, "%s:/", sWfcArchiveName);
    FS_ChangeDir(path);
}

extern "C" void WfcFs_UnmountArchive() {
    FS_ChangeDir("rom:/");
    FS_UnloadArchiveTables(&sWfcFs->archive);
    FS_UnloadArchive(&sWfcFs->archive);
    FS_ReleaseArchiveName(&sWfcFs->archive);
    OS_ReleaseLockID(sWfcFs->lockId);
    sWfcFs->lockId = 0;
    WfcHeap_FreeAndClear(&sWfcFs->archiveTables);
    sWfcFs->archiveTables = 0;
    WfcHeap_FreeAndClear((void **)&sWfcFs);
}

extern "C" int WfcFs_ArchiveProc(FSFile *file, u32 cmd) {
    switch (cmd) {
    case 9:
        CARD_LockRom(sWfcFs->lockId);
        return 0;
    case 10:
        CARD_UnlockRom(sWfcFs->lockId);
        return 0;
    case 1:
        return 4;
    default:
        return 8;
    }
}

extern "C" int WfcFs_ReadCallback(FSArc *arc, void *dst, u32 pos, u32 size) {
    CARDi_ReadRom(-1, pos + arc->base, dst, size, WfcFs_OnReadDone, arc, 1);
    return 6;
}

extern "C" void WfcFs_OnReadDone(void *arc) {
    FS_NotifyArchiveAsyncEnd((FSArc *)arc, 0);
}

extern "C" int WfcFs_WriteCallback(FSArc *arc, void *src, u32 pos, u32 size) {
    return TRUE;
}

extern "C" void *WfcFs_LoadFile(void *name, u32 *outSize, s32 c) {
    void *p;
    FSFile o;
    s32 r6;
    u32 n;
    WfcPool_Get(sWfcFs->fileSlotPool);
    FS_InitFile(&o);
    if (FS_OpenFile(&o, (const char *)name) == 0) {
        Fatal_Trap();
    }
    n = o.prop.file.end - o.prop.file.start;
    if (outSize != 0) {
        *outSize = n;
    }
    if (WfcUtil_StrEndsWith(name, ".l", 2) != 0) {
        r6 = -4;
    } else {
        r6 = c;
    }
    p = WfcHeap_Alloc(n, r6);
    FS_ReadFile(&o, p, n);
    FS_CloseFile(&o);
    if (r6 > 0) {
        return p;
    }
    u32 v = *(u32 *)p >> 8;
    if (outSize != 0) {
        *outSize = v;
    }
    void *q = WfcHeap_Alloc(v, c);
    MI_UncompressLZ8(p, q);
    WfcHeap_FreeAndClear(&p);
    return q;
}

extern "C" void WfcFs_FreeFile(void *p, ...) {
    WfcHeap_FreeAndClear(&p);
    WfcPool_Put(sWfcFs->fileSlotPool, p);
}

extern "C" BOOL WfcUtil_StrEndsWith(const void *a, const void *b, s32 n) {
    s32 la = strlen((const char *)a);
    s32 lb = strlen((const char *)b);
    if (la < n || lb < n) {
        return FALSE;
    }
    return memcmp((const u8 *)a + (la - n), (const u8 *)b + (lb - n), n) == 0;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02223fc4) {
    HOST_OVERLAY_VAR(sWfcFs),
    HOST_OVERLAY_VARS_END
};
