#ifndef GAME_SKYPROC_H
#define GAME_SKYPROC_H

#include "types.h"
#include "sys/ProcBase.h"
#include "snd/RainSndChannel.h"

class SkyProc : public GameProc {
public:
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();

    /* 0x50 */ RainSndChannel envSndChannel;
};

#endif
