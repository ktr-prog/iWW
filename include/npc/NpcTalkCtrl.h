#ifndef NPC_NPCTALKCTRL_H
#define NPC_NPCTALKCTRL_H

#include "types.h"

class NpcActor;

extern "C" void NpcTalkCtrl_Destroy(void);
class NpcTalkCtrl {
public:
    NpcTalkCtrl();
    ~NpcTalkCtrl() { NpcTalkCtrl_Destroy(); }
    /* 0x00 */ s32 act07Variant;
    /* 0x04 */ s16 turnSpeed;
    /* 0x06 */ s16 turnAngle;
    /* 0x08 */ u8 state;
    /* 0x09 */ u8 requestedState;
    /* 0x0a */ u8 step;
    /* 0x0b */ u8 clearActorFlagOnEnd;
    /* 0x0c */ u8 keepCamera;
    /* 0x0d */ u8 stopAction;
    /* 0x0e */ u8 unk_0e;
    /* 0x0f */ u8 unk_0f;

    void mainState2(NpcActor *ctx);
    void state2Step1(NpcActor *ctx);
    void state2Step0(NpcActor *ctx);
    void setupState2(NpcActor *ctx);
    void mainState0(NpcActor *ctx);
    void state0Step2(NpcActor *ctx);
    void state0Step1(NpcActor *ctx);
    void state0Step0(NpcActor *ctx);
    void setupState0(NpcActor *ctx);
    void endTalk(NpcActor *ctx);
    void startTalkMessage(NpcActor *ctx);
    void updateSpeakerMouth(NpcActor *ctx);
    void update(NpcActor *ctx);
    void applyRequest(NpcActor *ctx);
    BOOL request(u8 b, u32 c, s16 d, s16 e, u8 f, u8 g);
    BOOL requestState4(u32 c, s32 d, s16 e, u8 g);
    BOOL requestTalk(u8 f, u8 g);
    BOOL requestTurnAndTalk(s16 d, s16 e, u8 g);
    BOOL isBusy();
    void reset();
    void mainState4(NpcActor* p);
    void state4Step0(NpcActor* p);
    void setupState4(NpcActor* p);
    void mainState3(NpcActor* p);
    void setupState3(NpcActor* p);
    void mainState1(NpcActor* p);
    void state1Step2(NpcActor* p);
    void state1Step1(NpcActor* p);
    void state1Step0(NpcActor* p);
    void setupState1(NpcActor* p);
};

#endif
