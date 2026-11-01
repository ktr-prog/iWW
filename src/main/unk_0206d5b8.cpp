#include "uptr.h"
#include "types.h"
#include "sdk_linker_symbols.h"
#include "sys/StackPad.h"
#include "nitro/fs.h"
#include "talk/MsgStringAttr.h"
#include "sys/RecordFile.h"
#include "talk/EncodedStringBase.h"
#include "talk/EncodedString.h"
#include "game/InfoTableSet.h"
#include "talk/EncodedString40.h"
#include "ui/LetterRenderer.h"
#include "nitro/io_access.h"
#include "net/CommManager.h"
#include "proto/autoload_2/unk_020e8208.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_0210f154.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02114cd8.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/main/unk_02000c2c.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020116e0.h"
#include "proto/main/unk_02037734.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_020536dc.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206d5b8.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_020e1e2c.h"
#include "proto/main/unk_0209c390.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020af258.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov002/unk_ov002_022025cc.h"




extern "C" {
extern u16 gMainWaitingFrame;
extern CommManager *gCommManager;
extern u32 gFrameCounter;
extern OSThreadQueue gFrameWaitQueue;
extern OSThreadQueue gVBlankQueue;
extern u8 gBackup[];
void OverlayHandle_Unload(void *p);
u32 DWC_Init(void *p);
void Task_RunFrame(s32 v);
void Sky_SwapBuffers(void);
void HBlank_RunFrame(void);
void VramQueue2d_Run(void);
void Clock_Update(u32 v);
void Backup_GetStatus(void *p);
BOOL FS_OpenFileFast(FSFile *f, FSFileID p);
void FS_CloseFile(FSFile *f);
void FS_ConvertPathToFileID(void *p, void *q);
}



#pragma thumb off

#pragma thumb reset



RecordFile::RecordFile() {
    fileId.arc = 0;
    pageIndex = -1;
    recordCount = 0;
    data = 0;
    pageBuf = 0;
    recordSize = 0;
}

RecordFile::~RecordFile() {
    close();
}

BOOL RecordFile::open(void *path, s32 size, s32 count) {
    recordSize = size;
    recordCount = count;
    FS_ConvertPathToFileID(this, path);
    pageBuf = (u8 *)Mem_Alloc(size << 3);
    return TRUE;
}

void RecordFile::loadAll() {
    u32 size = recordSize * recordCount;
    if (data == 0) {
        data = (u8 *)Mem_Alloc(size);
    }
    Backup_GetStatus(gBackup);
    File_ReadRangeById(fileId, data, size, 0);
}

void RecordFile::freeAll() {
    if (data != 0) {
        Mem_Free(data);
        data = 0;
    }
}

void RecordFile::close() {
    fileId.arc = 0;
    pageIndex = -1;
    recordCount = 0;
    recordSize = 0;
    if (data != 0) {
        Mem_Free(data);
        data = 0;
    }
    if (pageBuf != 0) {
        Mem_Free(pageBuf);
        pageBuf = 0;
    }
}

u8 *RecordFile::getRecord(u32 idx) {
    if (data != 0) {
        return data + recordSize * idx;
    }
    u32 blk = idx >> 3;
    if (pageIndex == blk) {
        return pageBuf + recordSize * (idx & 7);
    }
    if (pageBuf != 0) {
        loadPage(idx);
        u32 off = recordSize * (idx & 7);
        pageIndex = blk;
        return pageBuf + off;
    }
    return 0;
}

void RecordFile::loadPage(u32 idx) {
    u32 blk = idx >> 3;
    FSFile file;
    Backup_GetStatus(gBackup);
    FS_InitFile(&file);
    if (FS_OpenFileFast(&file, fileId)) {
        u32 sz = recordSize << 3;
        File_ReadRange(&file, pageBuf, sz, blk * sz);
        FS_CloseFile(&file);
    }
}

BOOL InfoTableSet::open(void *a, s32 n0, void *b, s32 n1, void *c, s32 n2, s32 count) {
    alwaysTable.open(a, n0, count);
    indoorTable.open(b, n1, count);
    dmaTable.open(c, n2, count);
    alwaysTable.loadAll();
    return TRUE;
}

void InfoTableSet::close() {
    alwaysTable.close();
    indoorTable.close();
    dmaTable.close();
}

BOOL InfoTableSet::loadIndoor(s32 v) {
    if (v == 0) {
        indoorTable.loadAll();
    }
    return TRUE;
}

BOOL InfoTableSet::freeIndoor() {
    indoorTable.freeAll();
    return TRUE;
}

RecordFile *InfoTableSet::getAlways() {
    return &alwaysTable;
}

RecordFile *InfoTableSet::getIndoor() {
    return &indoorTable;
}

RecordFile *InfoTableSet::getDma() {
    return &dmaTable;
}

extern "C" void Fatal_ExceptionCallback(void *arg, void *p) {
    OS_SetUserExceptionHandler(0, 0);
    sCrashContext = (u32 *)arg;
    CrashScreen_Run();
}

extern "C" void Main_InitNop(void) {}

extern "C" void Main_WaitVBlank(void) {
    OS_SleepThread(&gVBlankQueue);
}

extern "C" void Main_WaitFrame(void) {
    OS_SleepThread(&gFrameWaitQueue);
}

#ifdef HOST
extern "C" BOOL HostTick_StepEnds(void);
extern "C" void HostTick_NoteInput(void);
extern "C" void HostTick_ClearInput(void);
extern "C" void HostTick_EnterLegacy(void);
extern "C" void HostTick_LeaveLegacy(void);
extern "C" u32 gHostTick;
extern "C" void host_touch_read(int held);
extern "C" u8 gTouchHeld;
#endif
extern "C" void Main_PreTaskUpdate(u32 r) {
    LidSleep_Update();
    Gfx_PreTaskUpdate();
    if (r != 0) {
        Comm_ProcessReceived(r);
    }
    Touch_Update();
#ifdef HOST
    host_touch_read(gTouchHeld);
#endif
    Pad_Update();
#ifdef HOST
    HostTick_NoteInput();
#endif
    SoftReset_Update();
    Clock_Update(r);
}

extern "C" void Main_PostTaskUpdate(u32 r) {
    if (r == 0) {
        NetSession_PostUpdate();
    }
    Comm_Update(r);
    Gfx_PostTaskUpdate();
#ifdef HOST
    if (HostTick_StepEnds()) gFrameCounter++;
    HostTick_ClearInput();
    gHostTick++;
#else
    gFrameCounter++;
#endif
    IO_W((volatile u32 *)0x4000540, 3);
}

extern "C" void Main_PostFrameUpdate(void) {
    Gfx_VBlankFlush();
    CommCaution_UpdateBlendRegs();
    VramQueue2d_Run();
}

extern "C" void Main_LateUpdate(u32 r) {
    TextLabel_FlushGroup0();
    HudObjGfx_FlushCameraButton();
    Sky_SwapBuffers();
    HBlank_RunFrame();
#ifdef HOST
    if (HostTick_StepEnds()) {
        HostTick_EnterLegacy();
        Snd_Update();
        HostTick_LeaveLegacy();
    }
#else
    Snd_Update();
#endif
}

extern "C" void Main_PreTaskHook(void) {
    Main_PreTaskStub();
}

extern "C" void Main_PostTaskHook(void) {
    Main_PostTaskStub();
}

extern "C" void Main_Loop(void) {
    u32 r;
    s32 b;
    GX_DispOn();
    IO_OR((volatile u32 *)0x4001000, 0x10000);
    LidSleep_Init();
    CommManager *v = gCommManager;
    u16 *flag = &gMainWaitingFrame;
    for (;;) {
        Net_Update();
        v->setLatchedErrorFlags(v->getErrorFlags());
        r = v->getLatchedErrorFlags();
        Main_PreTaskUpdate(r);
        Main_PreTaskHook();
        if (r != 0) {
            b = 1;
        } else {
            b = 0;
        }
        CommCaution_Update(b);
        Task_RunFrame(b);
        CommCaution_Draw();
        Main_PostTaskUpdate(r);
        Main_PostTaskHook();
        *flag = 1;
        Main_WaitFrame();
        *flag = 0;
        Main_PostFrameUpdate();
        Main_LateUpdate(r);
    }
}

extern "C" u32 Main_InitDwc(void) {
    void *p = Mem_AllocAligned(0x700, 0x20);
    OverlayHandle_Load((OverlayHandleView *)&gOverlayHandle, OVERLAY_65_ID);
    u32 r = DWC_Init(p);
    sDwcInitResult = r;
    OverlayHandle_Unload(&gOverlayHandle);
    Mem_Free(p);
    return r;
}

extern "C" u8 Main_TakeDwcInitResult(void) {
    u8 old = sDwcInitResult;
    sDwcInitResult = 4;
    return old;
}

u8 sDwcInitResult = 4;
