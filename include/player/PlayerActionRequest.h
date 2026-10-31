#ifndef PLAYER_PLAYERACTIONREQUEST_H
#define PLAYER_PLAYERACTIONREQUEST_H

#include "types.h"
#include "player/PlayerActionRequestBase.h"
#include "player/PlayerChangeClothesArgs.h"
#include "player/PlayerInitWork.h"
#include "player/PlayerAct10Args.h"
#include "player/PlayerAct30Args.h"
#include "player/PlayerAct76Args.h"
#include "player/PlayerPickUpFanfareArgs.h"
#include "player/PlayerPickUpReachArgs.h"
#include "player/PlayerTurnToWork.h"
#include "player/PlayerWalkToArgs.h"

class PlayerActionRequest : public PlayerActionRequestBase {
public:
    PlayerActionRequest();
    ~PlayerActionRequest();
    void assign(s32 a, s32 b, s16 c);

    /* 0x00 */ s32 action;
    /* 0x04 */ s32 priority;
    /* 0x08 */ s16 netSeq;
    /* 0x0c */ union {
        PlayerActionPayload unk_0c;
        u16 unk_0c_h;
        PlayerChangeClothesArgs unk_0c_c2fc;
        u8 unk_0c_b[0x10];
        PlayerInitArgs unk_0c_d5b4;
        PlayerAct10Args act10;
        PlayerNetPickUpReachArgs emotion;
        PlayerPickUpReachArgs pickUpReach;
        PlayerAct30Args act30;
        PlayerWalkToArgs walkTo;
        PlayerTurnToArgs turnTo;
        PlayerAct76Args act76;
        PlayerPickUpFanfareArgs pickUpFanfare;
        PlayerPickUpFanfareStowArgs pickUpFanfareStow;
    };
};

#ifndef HOST64
static_assert(sizeof(PlayerActionRequest) == 0x1c, "PlayerActionRequest");
#endif

#endif
