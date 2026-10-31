#ifndef NET_PLAYERNETSYNC_H
#define NET_PLAYERNETSYNC_H

#include "types.h"
#include "sys/ProcBase.h"


class PlayerNetSync : public GameProc {
public:
    static GameProc *create();
    PlayerNetSync();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~PlayerNetSync();
};

#endif
