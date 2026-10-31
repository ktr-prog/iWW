#ifndef MENU_MENUTABBAR_H
#define MENU_MENUTABBAR_H

#include "types.h"
#include "menu/MenuProc.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuErrorMessage.h"

class MenuTabBar : public MenuProc {
public:
    inline MenuTabBar() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    BOOL isJustOpened();
    void requestSaveOnClose();
    void showTab(u32 idx);
    void cancelVramTasks();
    void hideTabs();
    void showTabs();
    void releaseResources();
    void initTabBar();
    void stateSlideOut();
    void stateSlideIn();
    void stateLoad();
    void updateSaving();
    void updateOpenTabMenu();
    void updateIdle();
    void beginClose();
    u8 onTabMenuClosed();
    void selectTab(u32 idx);

    /* 0x91 */ u8 visible;
    /* 0x92 */ u8 slideY;
    /* 0x93 */ u8 curTab;
    /* 0x94 */ u8 tabsShown;
    /* 0x95 */ u8 lrSwitchEnabled;
    /* 0x96 */ u8 loadedTab;
    /* 0x97 */ u8 saveState;
    /* 0x98 */ u8 justOpened;
    /* 0x9c */ BgVramTaskPair vramTasks[3];
    /* 0x144 */ u32 commonObjChars[0x200];
    /* 0x944 */ u32 tabObjChars[0x200];
    /* 0x1144 */ u32 tabPalette[8];
    /* 0x1164 */ MenuErrorMessage errorMessage;
};

#endif
