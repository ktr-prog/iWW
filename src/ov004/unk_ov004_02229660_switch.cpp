#include "types.h"
#include "proto/main/unk_020b4828.h"
#include "gfx/VecFx32.h"
#include "room/RoomTelephoneActEntry.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "actor/CharacterListNode.h"
#include "room/RoomTelephoneTypes.h"
#include "gfx/AnimFrameCtrl.h"
#include "room/RoomObjRes.h"
#include "room/RoomObjTex.h"
#include "talk/TalkWindowState.h"
#include "room/PhoneChoiceSet.h"
#include "gfx/CachedModel.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "room/RoomObjActor.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "room/RoomTelephone.h"
#include "net/CommManager.h"
#include "save/SaveData.h"
#include "talk/ChoiceList.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_020411dc.h"
#include "gfx/ScreenTransition.h"
#include "proto/main/unk_0203c92c.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0208eeac.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020b5e5c.h"
#include "proto/main/unk_020b7d10.h"
#include "proto/ov004/unk_ov004_0221e7a8.h"
#include "proto/ov004/unk_ov004_02229660.h"
#include "proto/ov004/unk_ov004_02229660_switch.h"















class TouchPicker;
class ChoiceList;


extern "C" {
extern CommManager *gCommManager;
extern u8 gSaveData[];
extern u8 gTalkMsgIndexNone[];

u32 Scene_GetCurrent();
void TalkRequest_AddPlayerTalk6(void *p, s32 a);
void TalkRequest_SetTargetDone(void *p);
s32 Vec_DistXZ(s32 *a, s32 *b);
}



typedef void (RoomTelephone::*RoomTelephoneActFn)();




extern "C" {
extern const u8 sRoomTelephoneChoiceMsgs[3];
extern const u8 sRoomTelephoneChoiceMsgsScene6[4];
extern const s32 sRoomTelephonePos[3];
extern const char sRoomTelephoneMsgFile[];
extern const char *data_ov004_0224e178;
extern PhoneChoiceSet data_ov004_0224e298;
extern PhoneChoiceSet data_ov004_0224e2a0;
extern PhoneChoiceSet data_ov004_0224e2a8;
}

void RoomTelephone::onChoice(u32 a_) {
    TalkWindowState *p = window;
    s32 t = ((p)->getChoiceList())->getResult();
    u32 r = 0;
    switch (msgIndex) {
    case 0xe:
    case 0x1f:
        if (Scene_GetCurrent() == 6) {
            r = sRoomTelephoneChoiceMsgsScene6[t];
        } else {
            r = sRoomTelephoneChoiceMsgs[t];
        }
        if (r == 0x17) {
            if (((SaveData *)(gSaveData))->testFlag(0x13) && ((SaveData *)(gSaveData))->testFlag(0x14)) {
                r = 0x42;
            } else if (!((SaveData *)(gSaveData))->testFlag(0x13) && ((SaveData *)(gSaveData))->testFlag(0x14)) {
                r = 0x41;
            } else if (((SaveData *)(gSaveData))->testFlag(0x13) && !((SaveData *)(gSaveData))->testFlag(0x14)) {
                r = 0x40;
            } else if (!((SaveData *)(gSaveData))->testFlag(0x13) && !((SaveData *)(gSaveData))->testFlag(0x14)) {
                r = 0x3f;
            }
        }
        break;
    case 0x14:
        switch (t) {
        case 0:
            PlayerOptions_SetHiragana(r);
            break;
        case 1:
            PlayerOptions_SetHiragana(1);
            break;
        }
        break;
    case 0x17:
        switch (t) {
        case 0:
            ((SaveData *)(gSaveData))->clearFlag(0x13);
            break;
        case 1:
            ((SaveData *)(gSaveData))->setFlag(0x13);
            break;
        }
        break;
    case 0x1a:
        switch (t) {
        case 0:
            ((SaveData *)(gSaveData))->clearFlag(0x14);
            break;
        case 1:
            ((SaveData *)(gSaveData))->setFlag(0x14);
            break;
        }
        break;
    case 0x1b:
        switch (t) {
        case 0:
            PlayerOptions_SetStereo(1);
            Snd_SetOutputMode(r);
            r = 0x1c;
            break;
        case 1:
            PlayerOptions_SetStereo(r);
            Snd_SetOutputMode(1);
            r = 0x1e;
            break;
        }
        break;
    case 0x11:
        prevTalkVoice = PlayerOptions_GetTalkVoice();
        switch (t) {
        case 0:
            PlayerOptions_SetTalkVoice(r);
            break;
        case 1:
            PlayerOptions_SetTalkVoice(1);
            break;
        case 2:
            PlayerOptions_SetTalkVoice(2);
            break;
        }
        break;
    case 0x2a:
    case 0x2b:
    case 0x2c:
        if (t == 1) {
            PlayerOptions_SetTalkVoice(prevTalkVoice);
        }
        break;
    }
    if (Scene_GetCurrent() != 6) {
        PlayerOptions_Commit();
    }
    if (r) {
        u8 b = r;
        (p)->setNextMessage(&b, (void *)(void *)(sRoomTelephoneMsgFile));
    }
}
