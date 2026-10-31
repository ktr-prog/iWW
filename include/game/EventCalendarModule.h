#ifndef GAME_EVENTCALENDARMODULE_H
#define GAME_EVENTCALENDARMODULE_H

#include "types.h"
#include "sys/ProcBase.h"

class EventCalendarModule : public GameProc {
public:
    EventCalendarModule() {}
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
};

#endif
