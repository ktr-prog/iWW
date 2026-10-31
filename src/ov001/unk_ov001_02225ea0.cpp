#include "types.h"
#include "host_mem.h"
#include "proto/ov001/unk_ov001_02225ea0.h"

#pragma thumb off

typedef volatile u16 vu16;

extern "C" {
s32 PM_SetLCDPower(u32 a);


u8 sWfcLcdOff;
}

void WfcUtil_UpdateLidPower() {
    if (sWfcLcdOff != 0) {
        if (((*HW_SYSWORK(vu16, buttonXY) & 0x8000) >> 15) != 0) return;
        if (PM_SetLCDPower(1) != 0) sWfcLcdOff = 0;
    } else {
        if (((*HW_SYSWORK(vu16, buttonXY) & 0x8000) >> 15) == 0) return;
        if (PM_SetLCDPower(0) != 0) sWfcLcdOff = 1;
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02225ea0) {
    HOST_OVERLAY_VAR(sWfcLcdOff),
    HOST_OVERLAY_VARS_END
};
