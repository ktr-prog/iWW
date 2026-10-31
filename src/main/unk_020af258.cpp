#include "types.h"
#include "host_mem.h"
#include "game/Unk_021c47c4.h"
#include "game/Unk_020aec00.h"
#include "game/ShopAckCounter.h"
#include "game/Elem2a.h"
#include "game/Loc488.h"
#include "game/NookShop.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_02060b9c.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020af258.h"
#include "proto/main/unk_020af3f4.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/ov003/unk_ov003_0222e734.h"
#include "proto/ov004/unk_ov004_02233074.h"


extern "C" {
u32 PM_GetBackLight(u32 *top, u32 *bottom);
u32 PM_SetBackLight(u32 target, u32 on);
u32 PM_SetLCDPower(u32 on);
BOOL PM_GetLCDPower(void);
extern u8 gFieldSceneKind;
}

u8 sLidSleepFlags;
u8 sLidSleepState;
u32 sLidSleepBacklightBottom;
u32 sLidSleepBacklightTop;

extern "C" BOOL Field_TryPushSnowball(VecFx32 *outPos, s16 *outAng, s32 *outVal, s32 speed, s16 ang) {
    BOOL outdoors = gFieldSceneKind == 0;
    if (outdoors && speed > 0) return Snowball_TryPushAny(outPos, outAng, outVal, speed, ang);
    return FALSE;
}

extern "C" void LidSleep_Init() {
    sLidSleepFlags = 0;
    sLidSleepState = 0;
}

extern "C" void LidSleep_Update() {
    switch (sLidSleepState) {
    case 0:
        if ((*HW_SYSWORK(vu16, buttonXY) & 0x8000) >> 15) {
            sLidSleepState = 1;
            LidSleep_BacklightOff();
            PM_SetLCDPower(0);
            Snd_VolumeOff();
        }
        break;
    case 1:
        if (!((*HW_SYSWORK(vu16, buttonXY) & 0x8000) >> 15)) {
            sLidSleepState = 2;
            LidSleep_BacklightRestore();
            LidSleep_WakeLcd();
        }
        break;
    case 2:
        LidSleep_WakeLcd();
        break;
    }
}

extern "C" void LidSleep_KeepSoundOff() { LidSleep_SetFlag(2); }

extern "C" void LidSleep_BacklightOff() {
    if (!LidSleep_TestFlag(1)) {
        PM_GetBackLight(&sLidSleepBacklightTop, &sLidSleepBacklightBottom);
        PM_SetBackLight(2, 0);
        LidSleep_SetFlag(1);
    }
}

extern "C" void LidSleep_BacklightRestore() {
    if (LidSleep_TestFlag(1)) {
        PM_SetBackLight(0, sLidSleepBacklightTop);
        PM_SetBackLight(1, sLidSleepBacklightBottom);
        LidSleep_ClearFlag(1);
    }
}

extern "C" void LidSleep_WakeLcd() {
    if (PM_GetLCDPower() == 1 || PM_SetLCDPower(1)) {
        if (!LidSleep_TestFlag(2)) Snd_VolumeOn();
        sLidSleepState = 0;
    }
}

extern "C" BOOL LidSleep_TestFlag(s32 m) {
    if (sLidSleepFlags & m) return TRUE;
    return FALSE;
}

extern "C" void LidSleep_SetFlag(s32 m) { sLidSleepFlags |= m; }

extern "C" void LidSleep_ClearFlag(s32 m) { sLidSleepFlags &= ~m; }

