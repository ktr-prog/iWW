#ifndef MENU_MENULAUNCHER_H
#define MENU_MENULAUNCHER_H

#include "types.h"
#include "menu/MenuProc.h"

class MenuLauncher : public MenuProc {
public:
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    void releaseResources();
    void initLauncher();
    void stateStart();
    void updateOpenRequested();
    void updateIdle();
    void onChildClosed();
    void setNextRequest(s32 a, s32 b);

    /* 0x91 */ u8 requestedMode;
};

#endif
