#ifndef MENU_POPUPCHOICEMENU_H
#define MENU_POPUPCHOICEMENU_H

#include "types.h"
#include "menu/PopupChoiceRow.h"
#include "menu/MenuLabelButton.h"
#include "menu/MenuTitleBalloon.h"
#include "menu/MenuSlide.h"
#include "menu/PopupChoiceIdList.h"

class PopupChoiceMenu {
public:
    PopupChoiceMenu();
    virtual ~PopupChoiceMenu();

    void placeAboveBalloon(LabelBalloon *p);
    void placeAbove(s32 a, s32 b);
    void placeAt(s32 a, s32 b);
    void placeNearPoint(s32 a, s32 b);
    void placeCentered(s32 a, s32 b);
    void init(s32 a, s32 b, const char *path);

    /* 0x04 */ u32 rowCharBase;
    /* 0x08 */ s32 scrollX;
    /* 0x0c */ s32 scrollY;
    /* 0x10 */ u32 bgPriority;
    /* 0x14 */ u16 flags;
    /* 0x16 */ u8 state;
    /* 0x17 */ u8 request;
    /* 0x18 */ u8 stateStep;
    /* 0x19 */ u8 openLeftward;
    /* 0x1a */ u8 layer;
    /* 0x1b */ u8 textWidthTiles;
    /* 0x1c */ u8 numRows;
    /* 0x1d */ u8 numPages;
    /* 0x1e */ u8 decideDelay;
    /* 0x1f */ u8 decidedRow;
    /* 0x20 */ u8 addresseePage;
    /* 0x21 */ volatile u8 titleRefreshDelay;
    /* 0x22 */ u8 pad_22[2];
    /* 0x24 */ const char *screenFile;
    /* 0x28 */ PopupChoiceRow rows[5];
    /* 0x190 */ MenuLabelButton pageButton;
    /* 0x200 */ MenuTitleBalloon title;
    /* 0x2bc */ MenuSlide slide;
    /* 0x2d8 */ u8 addresseeIds[0x19];
};

class PopupChoiceMenuBody : public PopupChoiceMenu {
public:
    void load2dString(MsgString *buf, u32 c);
    void clearFlags(u32 m);
    void setFlags(u32 m);
    BOOL testFlags(u32 m);
    s32 applyAddressee(void *p, u32 id);
    s32 getAddresseeKind(u32 id);
    u32 pickAddressee(u32 a, u32 b);
    u32 getPageCount();
    u32 getRowCount();
    s32 getRowY(s32 v);
    s32 getRowX();
    s32 hitTestRow(s32 x, s32 y);
    s32 hitTestRowOrLast(s32 x, s32 y);
    s32 hitTestRowOr(s32 x, s32 y, s32 d);
    void loadAddresseePage(PopupChoiceIdList *r);
    void setRowsFromIds(PopupChoiceIdList *r, s32 f);
    s32 addCustomRow(PopupChoiceIdList *r, void *s, u32 v);
    void renderRows();
    void resetRowColors();
    void freeRowTexts();
    BOOL isClosed();
    BOOL isOpen();
    void buildAddresseeList();
};

#endif
