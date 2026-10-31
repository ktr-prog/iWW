#ifndef UI_HUDPROC_H
#define UI_HUDPROC_H

#include "types.h"
#include "sys/ProcBase.h"

class HudProc : public GameProc {
public:
    HudProc();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~HudProc();
};

#endif
