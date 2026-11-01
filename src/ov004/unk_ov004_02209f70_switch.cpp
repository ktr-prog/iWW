#include "types.h"
#include "host_tick.h"
#include "room/Unk_ov004_0224882c_Buf.h"
#include "gfx/Mtx43.h"
#include "actor/ActorListNode.h"
#include "actor/CharacterListNode.h"
#include "room/FtrActorParts.h"
#include "gfx/AnimFrameCtrl.h"
#include "item/ItemId.h"
#include "game/CollisionVec2.h"
#include "game/LightLevel.h"
#include "gfx/G3dResAccess.h"
#include "room/FtrVisNodes.h"
#include "room/FtrSwitch.h"
#include "room/FtrClockHands.h"
#include "room/FtrAnimSet.h"
#include "room/FtrStackedSet.h"
#include "talk/TalkWindowState.h"
#include "game/BoxCollider.h"
#include "game/CollisionEdge.h"
#include "room/FtrTileList.h"
#include "room/FtrGlowMat.h"
#include "room/FtrStackLink.h"
#include "room/FtrTopItem.h"
#include "game/FxVec3.h"
#include "sys/ProcBase.h"
#include "gfx/ModelAnim.h"
#include "room/FtrCollider.h"
#include "gfx/MatTexVramTask.h"
#include "room/FtrGlowMatSet.h"
#include "room/FtrTopItems.h"
#include "room/FtrModelAnim.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/ModelResource.h"
#include "room/FtrModelRes.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "room/FtrActor.h"
#include "room/FtrNookway.h"
#include "room/FtrPhone.h"
#include "room/FtrSingingInsect.h"
#include "room/FtrComputer.h"
#include "room/FtrHeadwear.h"
#include "room/FtrKind25.h"
#include "room/FtrCarpetSample.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_020514a4.h"
#include "proto/main/unk_02063904.h"
#include "proto/ov004/unk_ov004_02204f24.h"
#include "proto/ov004/unk_ov004_02209f70_switch.h"
#include "proto/ov004/unk_ov004_02233074.h"
extern "C" {
extern u16 gFtrSoundNone;
}


BOOL FtrSingingInsect::updateActive() {
    u32 h = FtrSound_GetSe0(FtrActor_GetFtrIndex(this));
    if ((u16)(h + 0xfc07) <= 3) {
        switch (singPhase) {
        case 0:
            if (restTimer != 0) {
                restTimer -= TICK_STEP_ENDS() ? 1 : 0;
            }
            if (restTimer == 0) {
                singPhase = 1;
                loopCount = 0;
                prevAnimDone = 0;
                singFrames = 0;
                if (h != gFtrSoundNone) {
                    soundEmitter.play(h, &centerPos);
                }
            }
            break;
        case 1: {
            singFrames += TICK_STEP_ENDS() ? 1 : 0;
            u32 r = FtrActor_StepAnims(this);
            if (prevAnimDone != 0 && r != 0) {
                prevAnimDone = 0;
                playAnim(0, 1, 0x1000, 0);
                loopCount++;
                if (loopCount >= loopsPerPhrase) {
                    singPhase = 0;
                    if (h == 0x3fc) {
                        restTimer = 0x3c;
                    } else {
                        restTimer = 200;
                    }
                }
            }
            prevAnimDone = r;
            break;
        }
        }
    } else {
        switch (singPhase) {
        case 0:
            if (restTimer != 0) {
                restTimer -= TICK_STEP_ENDS() ? 1 : 0;
            }
            if (restTimer == 0) {
                singPhase = 1;
                loopCount = 0;
                prevAnimDone = 0;
                if (h != gFtrSoundNone) {
                    soundEmitter.play(h, &centerPos);
                }
            }
            break;
        case 1:
        case 2:
        case 3: {
            if (h == 0x3ff) {
                if (model.hasPassedFrame(0x14)) {
                    if (h != gFtrSoundNone) {
                        soundEmitter.play(h, &centerPos);
                    }
                }
            }
            u32 r = FtrActor_StepAnims(this);
            if (prevAnimDone != 0 && r != 0) {
                prevAnimDone = 0;
                playAnim(0, 1, 0x1000, 0);
                loopCount++;
                if (loopCount >= loopsPerPhrase) {
                    singPhase = (singPhase + 1) & 3;
                    loopCount = 0;
                    if (singPhase != 0) {
                        if (h != gFtrSoundNone) {
                            soundEmitter.play(h, &centerPos);
                        }
                    } else {
                        if (modelRes.getAnimSet()->getBva(0) != 0) {
                            restTimer = loopsPerPhrase * (u16)(anims[3].numFrames >> 12);
                        } else {
                            restTimer = loopsPerPhrase * (u16)(model.numFrames >> 12);
                        }
                    }
                }
            }
            prevAnimDone = r;
            break;
        }
        }
    }
    return TRUE;
}

BOOL FtrSingingInsect::initModel() {
    initAnims(0, 1, 0x1000, 0);
    s32 t = FtrSound_GetSe0(FtrActor_GetFtrIndex(this));
    switch (t) {
    case 0x3f9:
        loopCount = 4;
        loopsPerPhrase = loopCount;
        break;
    case 0x3fb:
        loopCount = 4;
        loopsPerPhrase = loopCount;
        break;
    case 0x3fa:
        loopCount = 4;
        loopsPerPhrase = loopCount;
        break;
    case 0x3fc:
        loopCount = 2;
        loopsPerPhrase = loopCount;
        break;
    default:
        loopCount = 1;
        loopsPerPhrase = loopCount;
        break;
    }
    singPhase = 0;
    restTimer = 0;
    if (spawnMode != 1) {
        if (t == 0x3fc) {
            restTimer = Random_GlobalBelow(0x3c);
        } else if ((u16)(t + 0xfc07) <= 2) {
            restTimer = Random_GlobalBelow(0xc8);
        } else {
            restTimer = Random_GlobalBelow(loopsPerPhrase * getAnimFrameCount(0));
        }
    }
    return TRUE;
}

