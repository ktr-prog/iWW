#ifndef TALK_TALKREQUESTQUEUE_H
#define TALK_TALKREQUESTQUEUE_H

#include "types.h"
#include "sys/ProcBase.h"


class TalkRequestQueue : public GameProc {
public:
    TalkRequestQueue() {}
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL postExecute(u32 b);
    virtual BOOL onDraw();
};

#endif
