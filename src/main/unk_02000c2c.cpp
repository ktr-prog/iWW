#include "types.h"
#include "host_mem.h"
#include "game/FxVec3.h"
#include "sys/DebugText.h"
#include "sys/ProcBase.h"
#include "sys/QNode.h"
#include "sys/OSThread.h"
#include "nitro/io_access.h"
#include "sys/Heap.h"
#include "proto/main/unk_02000c2c.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_0210f154.h"
#include "proto/autoload_2/unk_0210fa84.h"
#include "proto/autoload_2/unk_021104ac.h"
#include "proto/autoload_2/unk_021127c0.h"
#include "proto/autoload_2/unk_02113b6c.h"
#include "proto/autoload_2/unk_02114cd8.h"
#include "proto/autoload_2/unk_02114d84.h"
#include "proto/autoload_2/unk_02114ef4.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_020376c0.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/main/unk_0206d5b8.h"
#include "proto/main/unk_020b0a80.h"
#include "proto/main/unk_020b7f7c.h"
#include "proto/main/unk_020de408.h"
#include "proto/main/unk_020e0408.h"
#include "proto/main/unk_0204cc1c.h"

typedef volatile u16 vu16;
typedef volatile u32 vu32;

extern "C" {

extern u32 gTaskPhase;
extern QNode *gTaskCurrentNode;
extern u16 gProcCreateProfile;
extern u8 gProcCreateStep;
extern OSThreadInfo data_021fcc2c;
extern u32 data_021fce88;
extern char data_02135f44[];
extern u8 data_021fccfc[];
extern const char sCrashRegNames[55];

const char *sPanicFile;
const char sCrashRegNames[55] = "CPSR00R01R02R03R04R05R06R07R08R09R10R11R12SP LR PC4SPs";
const char *sPanicMessage;
u32 *sCrashContext;
u8 sCrashScreenState;
u32 sCrashSP;
u32 sCrashTimeMs;
u32 sPanicLine;
u32 sCrashPC;
u32 sCrashPrevKeys;
u16 *sCrashScreenMain;
u16 *sCrashScreenSub;

void OS_EnableInterrupts(void);
void Main_RunWifiUtility(void);
void OS_ResetSystem(u32 a);
u32 OS_GetProcMode(void);
void OS_DisableInterrupts(void);
void GX_SetBankForSubBG(u32 a);
void GX_LoadBG1Char(void *a, u32 b, u32 c);
void GXS_LoadBG1Char(void *a, u32 b, u32 c);
void GX_LoadBGPltt(void *a, u32 b, u32 c);
void GXS_LoadBGPltt(void *a, u32 b, u32 c);
void MIi_CpuClearFast(u32 data, void *dest, u32 size);
const char *Task_GetPhaseName(u32 a);
u32 OS_GetIrqStackStatus(void);
u32 OS_GetStackStatus(OSThread *a);
u8 *OS_GetDTCMAddress(void);

void Fatal_PanicV(const char *a, u32 b, const char *c, void *d) {
    {
        extern void host_panic(const char *file, u32 line, const char *fmt, void *args);
        host_panic(a, b, c, d);
    }
    OS_DisableInterrupts();
    sPanicFile = a;
    sPanicLine = b;
    sPanicMessage = data_02135f44;
    OS_VSNPrintf(data_02135f44, 0x80, c, *(DS_VA_LIST *)&d);
    Fatal_Trap();
}

void Fatal_Panic(const char *fmt, ...) {
    extern void host_panic_v(const char *file, u32 line, const char *fmt, __builtin_va_list *args);
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    host_panic_v("", 0, fmt, &ap);
}

BOOL CrashScreen_IsValidAddress(uptr addr, u32 len) {
    return HostMem_IsGameRam((const void *)addr, len) ? TRUE : FALSE;
}

void CrashScreen_DumpWords(u16 *dst, uptr src, u32 size) {
    u16 color = 0xd000;
    DebugText col;
    u32 *p;
    uptr end;
    col.unk_00 = color;
    col.charBase = color;
    p = (u32 *)(src & ~(uptr)3);
    size &= ~3;
    end = src + size;
    while ((uptr)p < end) {
        if (!CrashScreen_IsValidAddress((uptr)p, 4)) {
            break;
        }
        col.charBase = color;
        DebugText_Printf(&col, dst, "%08x", *p);
        dst += 8;
        color ^= 0x3000;
        p++;
    }
}

void CrashScreen_DrawStack(void) {
    u16 *buf = sCrashScreenSub;
    DebugText col;
    OSContext *ctx;
    u32 v;
    col.unk_00 = 0xd000;
    col.charBase = 0xd000;
    ctx = (OSContext *)sCrashContext;
    if (ctx != NULL) {
        v = ctx->r[13];
    } else {
        v = sCrashSP;
    }
    DebugText_Printf(&col, buf + 0x20, "SP = %08X", v);
    if (CrashScreen_IsValidAddress(v, 4)) {
        CrashScreen_DumpWords(buf + 0x40, v, 0x160);
    }
}

void CrashScreen_DrawMain(void) {
    u16 *buf = sCrashScreenMain;
    DebugText col;
    u32 n;
    u32 v;
    QNode *pp;
    u32 *p6;
    s32 i;
    u32 *q;
    OSThread *thr;
    OSThread *node;
    u32 r;
    col.unk_00 = 0xd000;
    col.charBase = 0xd000;
    DebugText_Printf(&col, buf + 0x20, "%10ums", sCrashTimeMs);
    DebugText_Print(&col, buf, (const char *)gBuildTime);
    n = gTaskPhase;
    if (n != 0 && (s32)n < 6) {
        DebugText_Printf(&col, buf + 0xc0, "LoopProc %1u:%s", n, Task_GetPhaseName(n));
    }
    v = 0xffff;
    pp = gTaskCurrentNode;
    if (pp != NULL) {
        ProcBase *cfg = (ProcBase *)pp->owner;
        if (cfg != NULL) {
            v = cfg->profile;
        }
    } else {
        v = gProcCreateProfile;
    }
    if (v != 0xffff) {
        DebugText_Printf(&col, buf + 0xe0, "ProfName[%d]Step[%u]", v, gProcCreateStep);
    }
    p6 = sCrashContext;
    if (p6 != NULL) {
        for (i = 0; (u32)i < 0x12; i++) {
            DebugText_Printf(&col, buf + ((i + 2) << 5) + 0x14, "%.3s:%08X", sCrashRegNames + i * 3, p6[i]);
        }
        p6 = sCrashContext;
        q = &p6[0x19];
        DebugText_Printf(&col, buf + 0x294, "SPSR%08X", p6[0x19]);
        DebugText_Printf(&col, buf + 0x2b4, "CP15%08X", q[1]);
    } else {
        DebugText_Printf(&col, buf + 0x214, "SP  %08X", sCrashSP);
        DebugText_Printf(&col, buf + 0x254, "PC4 %08X", sCrashPC);
    }
    if (sPanicFile != 0) {
        DebugText_Printf(&col, buf + 0x240, "%s:%u", sPanicFile, sPanicLine);
        DebugText_Print(&col, buf + 0x260, sPanicMessage);
    }
    r = OS_GetProcMode();
    thr = data_021fcc2c.current;
    DebugText_Printf(&col, buf + 0x40, "ID:%u mode:%02x", thr->id, r);
    DebugText_Printf(&col, buf + 0x60, "S:%08x-%08x", thr->stackTop, thr->stackBottom);
    r = OS_GetIrqStackStatus();
    if (r != 0) {
        DebugText_Printf(&col, buf + 0x80, "IrqStkErr%u", r);
    } else {
        node = data_021fcc2c.list;
        r = 0;
        while (node != NULL) {
            r = OS_GetStackStatus(node);
            if (r != 0) {
                break;
            }
            node = node->next;
        }
        if (node != NULL) {
            DebugText_Printf(&col, buf + 0x80, "StkErr%u:%u:%x", r, node->id, node->stackWarningOffset);
        }
    }
}

void CrashScreen_Fill(u32 a, u16 *b, u32 c) {
    MIi_CpuClearFast(a, b, c);
}

void CrashScreen_Clear(void) {
    u16 *t = sCrashScreenSub;
    CrashScreen_Fill(0x7f007f, sCrashScreenMain, 0x800);
    CrashScreen_Fill(0x7f007f, t, 0x800);
}

void CrashScreen_InitDisplay(void) {
    Gfx_ResetDisplayRegs();
    IO_OR((vu16 *)0x4000304, 1);
    IO_W((vu16 *)0x4000050, 0);
    IO_W((vu16 *)0x4001050, 0);
    GX_SetBankForBG(0x40);
    GX_SetBankForSubBG(0x80);
    IO_W((vu32 *)0x4000000, (IO_R((vu32 *)0x4000000) & 0xffffe0ff) | 0x200);
    IO_W((vu32 *)0x4001000, (IO_R((vu32 *)0x4001000) & 0xffffe0ff) | 0x200);
    IO_W((vu16 *)0x400000a, (IO_R((vu16 *)0x400000a) & 0x43) | 0x400);
    IO_W((vu16 *)0x400100a, (IO_R((vu16 *)0x400100a) & 0x43) | 0x400);
    GX_LoadBG1Char(sCrashFontChars, 0, 0x1000);
    GXS_LoadBG1Char(sCrashFontChars, 0, 0x1000);
    GX_LoadBGPltt(sCrashFontPalette, 0x1a0, 0x60);
    GXS_LoadBGPltt(sCrashFontPalette, 0x1a0, 0x60);
    *(vu16 *)HW_PLTT = 0x7c00;
    *(vu16 *)(HW_PLTT + 0x18) = 0x7c00;
    *(vu16 *)(HW_PLTT + 0x400) = 0x7c00;
    *(vu16 *)(HW_PLTT + 0x418) = 0x7c00;
    sCrashScreenMain = (u16 *)G2_GetBG1ScrPtr();
    sCrashScreenSub = (u16 *)G2S_GetBG1ScrPtr();
    CrashScreen_Clear();
    GX_DispOn();
    IO_OR((vu32 *)0x4001000, 0x10000);
}

void CrashScreen_WaitVBlank(void) {
    while ((s32)IO_R((vu16 *)0x4000006) >= 0xc0) {
    }
    while ((s32)IO_R((vu16 *)0x4000006) < 0xc0) {
    }
}

void CrashScreen_Frame(void) {
    u32 state = sCrashScreenState;
    u32 keys = (IO_R((vu16 *)0x4000130) | *HW_SYSWORK(vu16, buttonXY));
    u32 trig, prev, held;
    keys = (keys ^ 0x2fff) & 0x2fff;
    keys = (u16)keys & 0x3ff;
    prev = sCrashPrevKeys;
    trig = keys & (prev ^ keys);
    sCrashPrevKeys = keys;
    switch (state) {
    case 0:
        trig &= 0x2000;
        if (trig != 0) {
            state = 5;
        }
        if (keys == 0x321) {
            state = (u8)(state + 1);
        }
        break;
    case 1:
        if (keys == 0) {
            state = (u8)(state + 1);
        }
        break;
    case 2:
        if ((keys & ~0x82) != 0) {
            state = 0;
        } else if (keys == 0x82) {
            state = (u8)(state + 1);
        }
        break;
    case 3:
        if (keys == 0) {
            state = (u8)(state + 1);
        }
        break;
    case 4:
        if ((keys & ~0xc) != 0) {
            state = 0;
        } else if (keys == 0xc) {
            state = (u8)(state + 1);
        }
        break;
    case 5:
        CrashScreen_InitDisplay();
        CrashScreen_DrawMain();
        state = (u8)(state + 1);
    case 6:
        CrashScreen_DrawMain();
        CrashScreen_DrawStack();
        held = keys & 4;
        if (held != 0) {
            if ((trig & 1) != 0 && held != 0) {
                if (OS_GetProcMode() == 0x1f) {
                    Heap *a = gRootHeap;
                    Heap *b = gCurrentHeap;
                    Heap *c = gProcHeap;
                    if ((keys & 0x20) != 0) {
                        a->dump();
                    } else if ((keys & 0x10) != 0) {
                        c->dump();
                    } else if ((keys & 0x40) != 0) {
                        b->dump();
                    }
                }
            }
            if ((trig & 2) != 0 && held != 0) {
                BlockMap_DebugStub();
            }
        }
        break;
    }
    CrashScreen_WaitVBlank();
    sCrashScreenState = state;
}

void CrashScreen_Run(void) {
    vu16 *ime = (vu16 *)0x4000208;
    u64 t;
    (void)IO_R(ime);
    IO_W(ime, 0);
    t = OS_GetTick();
    sCrashTimeMs = (u32)((t << 6) / 0x82ea);
    for (;;) {
        CrashScreen_Frame();
    }
}



void FxVec3_Construct(void) {}

void LitCedarPos_Construct(u32 *p) {
    p[0] = 0;
    p[1] = 0;
}

void FxVec3_Destruct(void *) {}

void NitroMain(void) {
    vu16 *ime;
    OS_InitTick();
    OS_InitAlarm();
    OS_InitThread();
    OS_SetUserExceptionHandler((void *)Fatal_ExceptionCallback, data_021fccfc);
    ime = (vu16 *)0x4000208;
    (void)IO_R(ime);
    IO_W(ime, 1);
    OS_EnableInterrupts();
    Main_InitDwc();
    if (*HW_SYSWORK(u32, resetParameter) == 1) {
        Main_RunWifiUtility();
        ime = (vu16 *)0x4000208;
        (void)IO_R(ime);
        IO_W(ime, 1);
        OS_ResetSystem(2);
    }
    Main_Init();
    Main_Loop();
}
}
