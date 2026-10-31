#ifndef PLAYER_FISHBOBBERSTATES_H
#define PLAYER_FISHBOBBERSTATES_H

#include "types.h"
#include "player/FishBobber.h"

class FishBobberStates : public FishBobber {
public:
    void updateCastSwing();
    void updateAct09();
    void updateEscape();
    void updateReelIn();
    void updateHooked();
    void updateBite();
    void updateFloat();
    void updateCast();
    void updateCastFail();
    void updateHeld();
    void updateIdle();
};

#endif
