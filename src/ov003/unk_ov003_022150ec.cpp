#include "types.h"
#include "sys/ClockDateTime.h"
#include "gfx/NNSG3dRS.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "gfx/ModelAnim.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "town/KatrinaTent.h"
#include "town/CountdownDigit.h"
#include "town/CountdownSign.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/Model.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov003/unk_ov003_022150ec.h"
#include "proto/ov003/unk_ov003_022150ec_switch.h"
#include "gfx/G3dResAccess.h"















class CountdownDigit; class CountdownSign;
extern "C" CountdownDigit *CountdownDigit_Create();
extern "C" CountdownSign *CountdownSign_Create();
extern "C" ActorProfile sCountdownDigitProfile = {(void *(*)())CountdownDigit_Create, 0x26, 0x2c, 0, 0xc8000, 0x12c000, 0x258000};
extern "C" ActorProfile sCountdownSignProfile = {(void *(*)())CountdownSign_Create, 0x25, 0x2b, 0, 0xc8000, 0x12c000, 0x258000};
extern "C" u8 sCountdownSpawnIndex;
extern "C" u32 sCountdownHours;
extern "C" u32 sCountdownSeconds;
extern "C" u32 sCountdownMinutes;
u8 sCountdownSpawnIndex;
u32 sCountdownHours, sCountdownSeconds, sCountdownMinutes;
extern "C" const s32 sCountdownDigitOffsetsX[6] = {-0x1900,-0x1100,-0x500,0x300,0xf00,0x1700};
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




BOOL CountdownDigit::onExecute() {
    CountdownDigit_Update(this);
    void *r4 = model.getRenderObj();
    void *r2 = getBtaAnim(0);
    matAnim.replace(r4, r2, 1, 0x1000, digit);
    return TRUE;
}

CountdownDigit::CountdownDigit() {}
CountdownDigit::~CountdownDigit() {}

void *CountdownDigit::operator new(size_t size) {
    void *p = Heap_Alloc((Heap *)gFieldStructureHeap, size);
    memset(p, 0, size);
    return p;
}

void CountdownDigit::operator delete(void *p) {}

void CountdownSign::execNewYear() {
    matAnim.step();
    *(s32 *)matAnim.anmObj = matAnim.curFrame;
}

BOOL CountdownSign::enterNewYear() {
    matAnim.init(getBtaAnim(1), 0, 0x1000, 0);
    matAlpha = 1;
    return TRUE;
}

void CountdownSign::execCountdown() {
    matAnim.step();
    *(s32 *)matAnim.anmObj = matAnim.curFrame;
    ClockDateTimeWords tm;
    tm.words[0] = 0;
    tm.words[1] = 0;
    Clock_GetDateTime(&tm.dt);
    if (tm.dt.month == 1) {
        Snd_PlaySe(0x61);
        setDoorState(1);
    }
}

BOOL CountdownSign::enterCountdown() {
    matAnim.init(getBtaAnim(0), 0, 0x1000, 0);
    matAlpha = 0x1f;
    return TRUE;
}

void CountdownSign::updateDoorState() {
    static Unk_02215614_Fn tbl[3] = { &CountdownSign::execCountdown, &CountdownSign::execNewYear };
    if (doorState < 3) {
        (this->*tbl[doorState])();
    }
}

s32 CountdownSign::setDoorState(s32 arg) {
    u32 a = arg;
    static Unk_02215680_Fn tbl[3] = { &CountdownSign::enterCountdown, &CountdownSign::enterNewYear };
    if (a < 3) {
        if ((this->*tbl[a])()) {
            if (BuildingState_Set(itemId, a)) {
                doorState = a;
                return TRUE;
            }
        }
    }
    return FALSE;
}

char *CountdownSign::getLightTexPath() { return BuildingActor::getLightTexPath(); }
char *CountdownSign::getTexPath() { return BuildingActor::getTexPath(); }
char *CountdownSign::getArcPath() { return BuildingActor::getArcPath(); }

BOOL CountdownSign::onDelete() {
    for (u32 i = 0; i < 6; i++) {
        digits[i] = 0;
    }
    return TRUE;
}

BOOL CountdownSign::postDraw(s32 a) {
    if (a == 2) {
        if ((colliderFlags & 1) == 0) {
            for (u32 i = 0; i < 6; i++) {
                CountdownDigit *p = digits[i];
                if (p) {
                    if (p->isCounting) {
                        p->updateMatrix();
                    }
                }
            }
        }
    }
    return Character::postDraw(a);
}

BOOL CountdownSign::onExecute() {
    ClockDateTimeWords tw;
    tw.words[0] = 0;
    tw.words[1] = 0;
    Clock_GetDateTime(&tw.dt);
    ClockDateTime &t = tw.dt;
    u32 secs = 0x15180 - (t.second + (t.minute * 0x3c + t.hour * 0xe10));
    sCountdownSeconds = secs;
    u32 h = sCountdownSeconds / 0xe10;
    sCountdownHours = h;
    sCountdownSeconds = sCountdownSeconds - h * 0xe10;
    u32 m = sCountdownSeconds / 0x3c;
    sCountdownMinutes = m;
    sCountdownSeconds = sCountdownSeconds - m * 0x3c;
    return TRUE;
}

BOOL CountdownSign::initBuilding() {
    getResources();
    onExecute();
    u32 i = 0;
    VecFx32 v;
    do {
        s32 c = position.z + 0x500;
        s32 b = position.y + 0x2500;
        s32 a = position.x + sCountdownDigitOffsetsX[i];
        v.x = a;
        v.y = b;
        v.z = c;
        sCountdownSpawnIndex = i;
        digits[i] = (CountdownDigit *)Actor::spawn(0x26, 0x501f, &v, NULL, NULL);
        i++;
    } while (i < 6);
    model.setInitCallback(CountdownSign_ModelCallback, this);
    alphaMatIdx = ((G3dResAccess *)model.resMdl)->findMatIdx("m_cbs_Adt");
    if (matAnim.allocMatAnm(model.resMdl, gFieldStructureHeap)) {
        matAnim.init(getBtaAnim(0), 0, 0x1000, 0);
        matAnim.addToRenderObj(model.getRenderObj());
    }
    ClockDateTimeWords tm;
    tm.words[0] = 0;
    tm.words[1] = 0;
    Clock_GetDateTime(&tm.dt);
    if (tm.dt.month == 1) {
        setDoorState(1);
    } else {
        setDoorState(0);
    }
    return TRUE;
}

CountdownSign::CountdownSign() {
    alphaMatIdx = -1;
}
CountdownSign::~CountdownSign() {}

extern "C" {
void CountdownSign_MaterialCallback(NNSG3dRS *o);
void CountdownSign_SetMaterialAlpha(CountdownSign *self, s32 a, NNSG3dRS *o);

void CountdownSign_ModelCallback(NNSG3dRS *o) {
    o->cbVecFunc[4] = (void *)CountdownSign_MaterialCallback;
    o->cbVecTiming[4] = 2;
}

void CountdownSign_MaterialCallback(NNSG3dRS *o) {
    NNSG3dRenderObj *s = o->pRenderObj;
    if (s->ptrUser != 0) {
        CountdownSign_SetMaterialAlpha((CountdownSign *)s->ptrUser, o->c[1], o);
    }
}

CountdownDigit *CountdownDigit_Create() {
    return new CountdownDigit();
}

CountdownSign *CountdownSign_Create() {
    return new CountdownSign();
}

void CountdownSign_SetMaterialAlpha(CountdownSign *self, s32 a, NNSG3dRS *o) {
    if (a == self->alphaMatIdx) {
        o->pMatAnmResult->prmPolygonAttr &= ~0x1f0000;
        o->pMatAnmResult->prmPolygonAttr |= (u32)self->matAlpha << 16;
    }
}
}



BOOL CountdownDigit::needsMatrixUpdate() {
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_022150ec) {
    HOST_OVERLAY_VAR(sCountdownDigitProfile),
    HOST_OVERLAY_VAR(sCountdownSignProfile),
    HOST_OVERLAY_VAR(sCountdownSpawnIndex),
    HOST_OVERLAY_VAR(sCountdownHours),
    HOST_OVERLAY_VAR(sCountdownMinutes),
    HOST_OVERLAY_VAR(sCountdownSeconds),
    HOST_OVERLAY_VARS_END
};
