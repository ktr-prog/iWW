#include "types.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0221ea94.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02226f68.h"

#pragma thumb off

extern "C" {
s32 DC_FlushRange(void *, u32);
s32 GXS_LoadBG1Scr(void *, u32, u32);

}

char data_ov001_0222b46c[] = "char/jtTop.nsc.l";
char data_ov001_0222b480[] = "char/jtStep1.nsc.l";
char data_ov001_0222b494[] = "char/jtStep2.nsc.l";
char data_ov001_0222b4a8[] = "char/jtStep3.nsc.l";
char data_ov001_0222b4bc[] = "char/jtOption.nsc.l";
char *sWfcTopScreenPaths[5] = { data_ov001_0222b480, data_ov001_0222b494, data_ov001_0222b4a8, data_ov001_0222b4bc, data_ov001_0222b46c };
u8 *sWfcTopScreenData;

void WfcTop_LoadScreen(u32 i)
{
    void *p = WfcUtil_LocalizePath((u8 *)sWfcTopScreenPaths[i]);
    sWfcTopScreenData = (u8 *)WfcFs_LoadFile(p, 0, 4);
    WfcTask_Add(1, (void *)WfcTop_TransferTask, 0, 0x78);
}

void WfcTop_TransferTask(void *task)
{
    DC_FlushRange(sWfcTopScreenData, 0x600);
    GXS_LoadBG1Scr(sWfcTopScreenData, 0, 0x600);
    WfcFs_FreeFile(sWfcTopScreenData);
    WfcTask_RequestDelete(1, task);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221ea94) {
    HOST_OVERLAY_VAR(data_ov001_0222b46c),
    HOST_OVERLAY_VAR(data_ov001_0222b480),
    HOST_OVERLAY_VAR(data_ov001_0222b494),
    HOST_OVERLAY_VAR(data_ov001_0222b4a8),
    HOST_OVERLAY_VAR(data_ov001_0222b4bc),
    HOST_OVERLAY_VAR(sWfcTopScreenPaths),
    HOST_OVERLAY_VAR(sWfcTopScreenData),
    HOST_OVERLAY_VARS_END
};
