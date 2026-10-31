#include "types.h"
#include "net/WfcConfigSlot.h"
#include "net/WfcMoveMbWork.h"
#include "net/WfcMoveParams.h"
#include "nitro/wm.h"
#include "proto/autoload_2/unk_02124c40.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov001/unk_ov001_02220ad8.h"
#include "proto/ov001/unk_ov001_022218a4.h"
#include "proto/ov001/unk_ov001_02222e84.h"

#pragma thumb off

struct WfcMoveSharedRecord {
    u16 command;
    u8 pad_02[0x42];
};

struct WfcMoveWork {
    u8 sendBuf[0x100];
    WfcMoveSharedRecord sharedRecv[2];
    u8 pad_188[0x200 - 0x188];
    u16 blockIndex;
    u16 unk_202;
    u32 failCount;
    u32 sharedRecvValid[16];
    u8 pad_248[0x648 - 0x248];
    u16 tgid;
    u16 channel;
    u8 configBuf[0xa50 - 0x64c];
    u8 configHead[0x40];
    u8 state;
    u8 prevState;
    u8 languageCode;
    u8 isHandshakeDone;
    u32 ackCount;
    u32 mbFrameCount;
    u32 waitTimer;
    u8 *childInfos[1];
    WfcConfigData *config;
    u8 pad_aa8[4];
    u8 request;
    u8 pad_aad[3];
    void *sendBuffer;
    MBGameRegistry registry;
    u8 pad_af0[0x10];
    u8 moveMbWork[1];
};
#if !HOST64
static_assert(__builtin_offsetof(WfcMoveWork, registry) == 0xab4 && __builtin_offsetof(WfcMoveWork, moveMbWork) == 0xb00,
              "DS layout");
#endif

extern "C" {
void MI_CpuFill8(void *, s32, s32);
void MI_CpuCopy8(void *, void *, s32);
u8 *MB_CommGetChildUser(u32 n);
u32 WM_GetNextTgid();
void DWCi_BACKUPlRead(void *);

WfcConfigData *WfcConfig_Get();
}

extern "C" WfcMoveWork *sWfcMove = 0;

#define H (sWfcMove)


extern "C" void WfcMove_Init(WfcMoveWork *self, const WfcMoveParams *a) {
    sWfcMove = self;
    WfcMoveMb_SetWork(self->moveMbWork);
    sWfcMove->tgid = 0;
    sWfcMove->channel = 0;
    sWfcMove->state = 1;
    sWfcMove->prevState = 1;
    sWfcMove->waitTimer = 0;
    WfcMove_ClearBuffers();
    sWfcMove->registry.romFilePathp = a->romFilePath;
    sWfcMove->registry.gameNamep = a->gameName;
    sWfcMove->registry.gameIntroductionp = a->gameIntroduction;
    sWfcMove->registry.iconCharPathp = a->iconCharPath;
    sWfcMove->registry.iconPalettePathp = a->iconPalettePath;
    sWfcMove->registry.ggid = a->ggid;
    sWfcMove->languageCode = a->languageCode;
    sWfcMove->registry.maxPlayerNum = 2;
    OS_GetTick();
    DWCi_BACKUPlRead(sWfcMove->configBuf);
    OS_GetTick();
    sWfcMove->config = WfcConfig_Get();
}

extern "C" BOOL WfcMove_RequestCancel() {
    WfcMoveWork *s = sWfcMove;
    u32 st = s->state;
    if (st == 1 || st == 0x14 || st == 0x17 || st == 0x1a || st == 0x1d) {
        s->state = 0x22;
        sWfcMove->request = 0;
        return TRUE;
    }
    if (st == 4 || st == 5 || st == 6 || st == 0xd) {
        if (st == 4) {
            if (s->mbFrameCount < 6) {
                return FALSE;
            }
        }
        MB_End();
        sWfcMove->state = 0x10;
        sWfcMove->request = 2;
        return TRUE;
    }
    if ((u8)(st + 0xf7) <= 1) {
        s->state = 0x20;
        return TRUE;
    }
    if (st == 0xc) {
        s->state = 0x22;
        return TRUE;
    }
    BOOL r = FALSE;
    if (st == 2) {
        r = FALSE;
    } else {
        r = st - st;
    }
    return r;
}

extern "C" void WfcMove_ResetSession() {
    WfcMoveWh_SetGgid(sWfcMove->registry.ggid);
    sWfcMove->state = 1;
    sWfcMove->tgid = WM_GetNextTgid();
    MI_CpuCopy8(sWfcMove->config, sWfcMove->configHead, 0x40);
    sWfcMove->isHandshakeDone = 0;
    sWfcMove->failCount = 0;
    sWfcMove->tgid = sWfcMove->tgid + 1;
}

extern "C" BOOL WfcMove_Start() {
    u32 st = sWfcMove->state;
    if (st == 1 || st == 0x1a || st == 0x1d) {
        WfcMove_ResetSession();
        WfcMoveWh_Initialize();
        sWfcMove->state = 2;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL WfcMove_StartDownload() {
    WfcMoveWork *s = sWfcMove;
    if (s->state != 5) {
        return FALSE;
    }
    s->state = 6;
    WfcMoveMb_StartDownloadAll();
    return TRUE;
}

extern "C" void WfcMove_Update() {
    switch (sWfcMove->state) {
    case 1:
        if (sWfcMove->request == 1) {
            sWfcMove->request = 0;
            WfcMove_Start();
            return;
        }
        if (sWfcMove->request != 2) return;
        sWfcMove->request = 0;
        sWfcMove->state = 0x22;
        return;
    case 2:
        WfcMove_StepMeasureChannel();
        return;
    case 3:
        WfcMove_StepInitMb();
        sWfcMove->state = 4;
        return;
    case 4:
        sWfcMove->mbFrameCount++;
        WfcMove_StepMb();
        return;
    case 5:
    case 6:
        WfcMove_StepMb();
        return;
    case 7:
        WfcMove_StepStartDataShare();
        return;
    case 8:
    case 9:
    case 10:
        WfcMove_StepDataShare();
        return;
    case 11:
        WfcMove_SetDone();
        return;
    case 16:
        sWfcMove->waitTimer = 0;
        sWfcMove->state = 0x11;
        return;
    case 17:
        if ((u32)sWfcMove->waitTimer++ <= 0x1e) return;
        WfcMove_TryEnd();
        return;
    case 18:
        MB_End();
        sWfcMove->waitTimer = 0;
        sWfcMove->state = 0x16;
        return;
    case 19:
        if ((u32)sWfcMove->waitTimer++ <= 0x1e) return;
        if (WfcMoveWh_GetSysState() != 1) return;
        WfcMoveWh_End();
        sWfcMove->state = 0x14;
        return;
    case 21:
        DWCi_MOV_WH_Finalize();
        sWfcMove->waitTimer = 0;
        sWfcMove->state = 0x16;
        return;
    case 22:
        if ((u32)sWfcMove->waitTimer++ <= 0x1e) return;
        if (WfcMoveWh_GetSysState() != 1) return;
        WfcMoveWh_End();
        sWfcMove->state = 0x17;
        return;
    case 24:
        DWCi_MOV_WH_Finalize();
        sWfcMove->waitTimer = 0;
        sWfcMove->state = 0x19;
        return;
    case 25:
        if ((u32)sWfcMove->waitTimer++ <= 0x1e) return;
        if (WfcMoveWh_GetSysState() != 1) return;
        WfcMoveWh_End();
        sWfcMove->state = 0x1a;
        return;
    case 27:
        DWCi_MOV_WH_Finalize();
        sWfcMove->waitTimer = 0;
        sWfcMove->state = 0x1c;
        return;
    case 28: {
        u32 c = sWfcMove->waitTimer++;
        if (c <= 0x1e) return;
        if (WfcMoveWh_GetSysState() == 1) {
            WfcMoveWh_End();
            sWfcMove->state = 0x1d;
            return;
        }
        u32 t = sWfcMove->waitTimer;
        if (t % 30 != 1) return;
        if (t <= 0x37) return;
        DWCi_MOV_WH_Finalize();
        return;
    }
    case 32:
        DWCi_MOV_WH_Finalize();
        sWfcMove->waitTimer = 0;
        sWfcMove->state = 0x21;
        return;
    case 33:
        if ((u32)sWfcMove->waitTimer++ <= 0x1e) return;
        if (WfcMoveWh_GetSysState() != 1) return;
        WfcMoveWh_End();
        sWfcMove->state = 0x22;
        return;
    case 30:
        DWCi_MOV_WH_Finalize();
        break;
    case 34:
        break;
    }
}

extern "C" void WfcMove_GetState(u8 *a, u8 *b) {
    *a = sWfcMove->state;
    if (sWfcMove->state != sWfcMove->prevState) *b = 1;
    else *b = 0;
    sWfcMove->prevState = sWfcMove->state;
}

extern "C" u8 *WfcMove_GetChildUser() {
    return MB_CommGetChildUser(1);
}

extern "C" void WfcMove_StepMeasureChannel() {
    switch (WfcMoveWh_GetSysState()) {
    case 1:
        WfcMoveWh_StartMeasureChannel();
        return;
    case 7:
        sWfcMove->channel = WfcMoveWh_DecideChannel();
        sWfcMove->mbFrameCount = 0;
        sWfcMove->state = 3;
        return;
    case 0:
        sWfcMove->mbFrameCount = 0;
        sWfcMove->state = 3;
        return;
    case 9:
        WfcMoveWh_Reset();
        return;
    default:
        Fatal_Trap();
    case 3:
        return;
    }
}

extern "C" void WfcMove_StepInitMb() {
    WfcMoveMb_Init(sWfcMove->registry.ggid, sWfcMove->tgid);
}

extern "C" void WfcMove_StepMb() {
    switch (WfcMoveMb_GetState()) {
    case 1:
        WfcMoveMb_StartParent(&sWfcMove->registry, sWfcMove->channel);
        return;
    case 2:
        if (WfcMoveMb_GetChildMask(2) != 0) { sWfcMove->state = 5; return; }
        if (WfcMoveMb_GetChildMask(3) != 0 || WfcMoveMb_GetChildMask(4) != 0) { sWfcMove->state = 6; return; }
        if (sWfcMove->state != 5) return;
        if (WfcMoveMb_GetChildMask(2) == 0) sWfcMove->state = 0xd;
        return;
    case 3:
        if (WfcMoveMb_IsAllBootable() != 0) { WfcMoveMb_StartRebootAll(); return; }
        if ((u8)(sWfcMove->state + 0xfa) > 1) return;
        if (WfcMoveMb_GetChildMask(3) == 0) sWfcMove->state = 0x12;
        return;
    case 5:
        sWfcMove->state = 7;
        return;
    case 7:
        WfcMoveMb_Cancel();
        sWfcMove->state = 1;
        return;
    case 0:
        switch (WfcMoveWh_GetSysState()) {
        case 1: WfcMoveWh_End(); return;
        case 0: sWfcMove->state = 0x1f; return;
        case 3: return;
        default: sWfcMove->state = 0x1f; return;
        }
    }
}

extern "C" void WfcMove_StepStartDataShare() {
    WfcMove_ClearBuffers();
    WfcMoveWh_SetJudgeCallback((void *)WfcMove_JudgeChild);
    sWfcMove->state = 8;
}

extern "C" void WfcMove_StepDataShare() {
    switch (WfcMoveWh_GetSysState()) {
    case 1:
        WfcMoveWh_ParentConnect(4, sWfcMove->tgid + 1, sWfcMove->channel);
        return;
    case 4:
    case 5:
    case 6: {
        s32 v = sWfcMove->blockIndex;
        WfcMove_SendBlock(0, v, (u8 *)sWfcMove->config + (v % 16) * 0x40);
        WfcMove_ProcessRecv();
        if (sWfcMove->state == 0x1b) return;
        if (sWfcMove->failCount > 0x1e0) {
            sWfcMove->state = 0x1b;
            return;
        }
        if (WfcMove_GetChildReply() == 0x10 || WfcMove_GetChildReply() == 0x20) {
            WfcMove_GetChildReply();
            sWfcMove->state = 10;
            return;
        }
        if (WfcMove_GetChildReply() == 0x40) { sWfcMove->state = 11; return; }
        if (WfcMove_GetChildReply() == 0xff) { sWfcMove->state = 0x1b; return; }
        if (WfcMove_GetChildReply() == 0x50) { sWfcMove->state = 0x15; return; }
        if (WfcMove_GetChildReply() == 0x60) { sWfcMove->state = 0x18; return; }
        if (WfcMove_GetChildReply() == 0x70) { sWfcMove->state = 0x1b; return; }
        if (WfcMove_GetChildReply() == 0) { sWfcMove->state = 8; return; }
        if (WfcMove_GetChildReply() == 0xbd) sWfcMove->state = 9;
        else sWfcMove->state = 0x1f;
        break;
    }
    }
}

extern "C" void WfcMove_SetDone() {
    sWfcMove->state = 12;
}

extern "C" s32 WfcMove_TryEnd() {
    if (WfcMoveWh_GetSysState() != 1) return 0;
    WfcMoveWh_End();
    sWfcMove->state = 1;
    return 1;
}

extern "C" s32 WfcMove_JudgeChild(WMStartParentCallback *a) {
    s32 r = WfcMoveMb_FindAidByMac(a->macAddress);
    if (r == 0) return 0;
    sWfcMove->childInfos[r - 1] = WfcMoveMb_GetChildInfo(r);
    return 1;
}

extern "C" void WfcMove_ClearBuffers() {
    MI_CpuFill8(sWfcMove->sharedRecv, 0, 0x100);
    MI_CpuFill8(sWfcMove->sendBuf, 0, 0x100);
    sWfcMove->sendBuffer = sWfcMove->sendBuf;
}

extern "C" void WfcMove_SendBlock(u32 a, u32 b, void *src) {
    WfcMoveWork *h = H;
    u16 i;
    if (h->isHandshakeDone == 1) {
        *(u16 *)h->sendBuffer = a;
        *((u16 *)H->sendBuffer + 1) = b;
        MI_CpuCopy8(src, (u8 *)H->sendBuffer + 4, 0x40);
    } else {
        h->failCount = h->failCount + 1;
        *(u16 *)H->sendBuffer = 0xbc;
        *((u8 *)H->sendBuffer + 4) = H->languageCode;
    }
    if (WfcMoveWh_GetSysState() != 5) {
        return;
    }
    if (DWCi_MOV_WH_StepDataSharing(H->sendBuf) == 0) {
        H->failCount = H->failCount + 4;
        return;
    }
    h = H;
    if (h->isHandshakeDone == 0) {
        h->failCount = h->failCount + 1;
    } else {
        h->failCount = 0;
        if (WfcMoveWh_GetConnectedBitmap() != 3) {
            H->state = 0x1b;
            return;
        }
    }
    for (i = 0; i < 2; i++) {
        void *s = WfcMoveWh_GetSharedData(i);
        if (s != 0) {
            MI_CpuCopy8(s, &H->sharedRecv[i], 0x44);
            H->sharedRecvValid[i] = 1;
        } else {
            H->sharedRecvValid[i] = 0;
        }
    }
}

extern "C" void WfcMove_ProcessRecv() {
    s32 i;
    for (i = 0; i < 16; i++) {
        WfcMoveWork *h = H;
        if (h->sharedRecvValid[i] != 0) {
            WfcMoveSharedRecord *r = &h->sharedRecv[(u32)i];
            if (i == 1) {
                if (h->isHandshakeDone == 1) {
                    if (r->command != 0x10) {
                        return;
                    }
                    h->ackCount = h->ackCount + 1;
                    h = H;
                    if ((h->ackCount & 1) == 0) {
                        h->blockIndex = h->blockIndex + 1;
                        h = H;
                        if (h->blockIndex >= 0x24) {
                            h->blockIndex = 0;
                        }
                    }
                } else {
                    h->unk_202 = 0xbc;
                    if (r->command == 0xbd) {
                        H->isHandshakeDone = 1;
                        H->blockIndex = 0;
                        H->ackCount = 0;
                    }
                }
            }
        }
    }
}

extern "C" s32 WfcMove_GetChildReply() {
    return H->sharedRecv[1].command;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02222e84) {
    HOST_OVERLAY_VAR(sWfcMove),
    HOST_OVERLAY_VARS_END
};
