#ifndef TALK_MSGUIPROC_H
#define TALK_MSGUIPROC_H

#include "types.h"
#include "sys/ProcBase.h"

class MsgUiProc : public GameProc {
public:
    MsgUiProc();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~MsgUiProc();
};

#endif
