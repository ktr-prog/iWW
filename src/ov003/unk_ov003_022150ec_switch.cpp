#include "types.h"
#include "sys/ClockDateTime.h"
#include "gfx/NNSG3dRS.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "gfx/ModelAnim.h"
#include "gfx/Model.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "town/KatrinaTent.h"
#include "town/CountdownDigit.h"
#include "town/CountdownSign.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov003/unk_ov003_022150ec_switch.h"

















extern "C" s32 Scene_GetCurrent();
extern "C" {
extern u8 sCountdownSpawnIndex;
extern u32 sCountdownHours;
extern u32 sCountdownSeconds;
extern u32 sCountdownMinutes;
extern const s32 sCountdownDigitOffsetsX[6];
extern char data_ov003_02231750[];
extern char data_ov003_022318b8[];
void CountdownSign_ModelCallback(NNSG3dRS *p);
void Clock_GetDateTime(ClockDateTime *p);
void func_02094030(void *p);
void func_02094018(void *p);
void Npc_GetName(void *p, void *q);
}



class CountdownSign;
typedef void (CountdownSign::*Unk_02215614_Fn)();
typedef BOOL (CountdownSign::*Unk_02215680_Fn)();




extern "C" {
void CountdownSign_MaterialCallback(NNSG3dRS *o);
void CountdownSign_SetMaterialAlpha(CountdownSign *self, s32 a, NNSG3dRS *o);
}


BOOL CountdownDigit::initBuilding() {
    digitIndex = sCountdownSpawnIndex;
    digit = 0;
    setCharId(digitIndex);
    if (matAnim.allocMatAnm(model.resMdl, gFieldStructureHeap)) {
        matAnim.init(getBtaAnim(0), 1, 0x1000, 0);
        matAnim.addToRenderObj(model.getRenderObj());
    }
    isCounting = 1;
    prevDigit = 0xff;
    ClockDateTimeWords tm;
    tm.words[0] = 0;
    tm.words[1] = 0;
    Clock_GetDateTime(&tm.dt);
    if (tm.dt.month != 1) {
        switch (digitIndex) {
        case 0:
            digit = prevDigit = (sCountdownHours / 10) & 1;
            skipSe = 0;
            break;
        case 1:
            digit = prevDigit = sCountdownHours % 10;
            skipSe = 0;
            break;
        case 2:
            digit = prevDigit = sCountdownMinutes / 10;
            skipSe = 0;
            break;
        case 3:
            digit = prevDigit = sCountdownMinutes % 10;
            skipSe = 0;
            break;
        case 4:
            digit = prevDigit = sCountdownSeconds / 10;
            skipSe = 1;
            break;
        case 5:
            digit = prevDigit = sCountdownSeconds % 10;
            skipSe = 1;
            break;
        }
    }
    CountdownDigit_Update(this);
    return TRUE;
}


extern "C" void CountdownDigit_Update(CountdownDigit *o) {
    if (o->isCounting != 0) {
        ClockDateTimeWords l;
        l.words[0] = 0;
        l.words[1] = 0;
        Clock_GetDateTime(&l.dt);
        if (l.dt.month == 1) {
            goto clr;
        }
        switch (o->digitIndex) {
        case 0:
            o->digit = (sCountdownHours / 10) & 1;
            break;
        case 1:
            o->digit = sCountdownHours % 10;
            break;
        case 2:
            o->digit = sCountdownMinutes / 10;
            break;
        case 3:
            o->digit = sCountdownMinutes % 10;
            break;
        case 4:
            o->digit = sCountdownSeconds / 10;
            break;
        case 5:
            o->digit = sCountdownSeconds % 10;
            break;
        }
        s32 r;
        r = -1;
        if (sCountdownHours != 0) {
            goto done;
        }
        if (Scene_GetCurrent() == 0x2c) {
            goto done;
        }
        if (sCountdownMinutes == 1 && sCountdownSeconds == 0) {
            r = 3;
        } else if (sCountdownMinutes == 0 && sCountdownSeconds != 0) {
            if (sCountdownSeconds <= 10) {
                r = 2;
            } else {
                r = 3;
            }
        }
        if (o->prevDigit == o->digit) {
            goto done;
        }
        if (r != -1 && o->digitIndex == 5) {
            switch (r) {
            case 1:
                if (o->skipSe == 0) {
                    Snd_PlaySe(0x61);
                }
                break;
            case 2:
                if (o->skipSe == 0) {
                    Snd_PlaySe(0x60);
                }
                break;
            case 3:
                if (o->skipSe == 0) {
                    Snd_PlaySe(0x62);
                }
                break;
            }
            o->skipSe = 0;
        } else {
            o->skipSe = 0;
        }
        goto done;
    clr:
        o->isCounting = 0;
    }
done:
    o->prevDigit = o->digit;
}
