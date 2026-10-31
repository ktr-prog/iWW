#include "types.h"
#include "host_mem.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_022265ac.h"
#include "proto/ov001/unk_ov001_02226f68.h"

extern "C" {
s32 OS_DisableIrqMask(s32);
s32 OS_EnableIrqMask(s32);
void OS_SetIrqMask(u32);
void OS_ResetRequestIrqMask(s32);
void (*OS_GetIrqFunction(u32 intrBit))(void);
void OS_SetIrqFunction(u32 intrBit, void (*function)(void));
void OS_EnableInterrupts(s32);
}

extern "C" void (*sWfcSavedVBlankHandler)(void) = 0;
extern "C" u32 sWfcSavedIrqMask = 0;

#pragma thumb off

void WfcIrq_Init()
{
    sWfcSavedIrqMask = IO_R((volatile u32 *)0x4000210);
    OS_SetIrqMask(0x40018);
    OS_EnableIrqMask(1);
    sWfcSavedVBlankHandler = OS_GetIrqFunction(1);
    OS_SetIrqFunction(1, WfcIrq_VBlank);
    OS_ResetRequestIrqMask(1);
    u16 t = IO_R((volatile u16 *)0x4000208);
    IO_W((volatile u16 *)0x4000208, 1);
    OS_EnableInterrupts(1);
}

void WfcIrq_Restore()
{
    u16 t = IO_R((volatile u16 *)0x4000208);
    IO_W((volatile u16 *)0x4000208, 0);
    OS_SetIrqMask(sWfcSavedIrqMask);
    OS_SetIrqFunction(1, sWfcSavedVBlankHandler);
}

void WfcIrq_VBlank()
{
    WfcTask_RunList(1);
    u32 *g = (u32 *)HW_DTCM_BLOCK;
    g += 0xc00;
    g[0x3fe] |= 1;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_022265ac) {
    HOST_OVERLAY_VAR(sWfcSavedVBlankHandler),
    HOST_OVERLAY_VAR(sWfcSavedIrqMask),
    HOST_OVERLAY_VARS_END
};
