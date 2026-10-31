#ifndef TALK_CHOICEMENU_H
#define TALK_CHOICEMENU_H

#include "types.h"
#include "ui/UiWidget.h"
#include "ui/HandCursor.h"
#include "ui/ScrollKnob.h"
#include "ui/LabelButton.h"

class ChoiceList;
class TextLabel;

class ChoiceHandCursor : public HandCursor {
public:
    ChoiceHandCursor();
    virtual ~ChoiceHandCursor();
};

class ChoiceSlider : public UiWidget {
public:
    ChoiceSlider();
    virtual ~ChoiceSlider();
    virtual void draw();
    virtual void update();
    virtual void setOrigin(s32 a, s32 b);

    void startKnobRelease();
    void startKnobGrab();
    void hideKnob();
    void showKnob();
    BOOL isKnobAnimDone();
    void getKnobAnimOffset(s32 *x, s32 *y);
    s32 getTrackTop();
    s32 getTrackBottom();
    s32 getKnobY();
    s32 getKnobX();
    s32 getKnobOffsetY();
    void setPos(s32 v);

    /* 0x0c */ s32 value;
    /* 0x10 */ ScrollKnob knob;
};

class ChoiceWindow {
public:
    ChoiceWindow();
    virtual ~ChoiceWindow();
    virtual void update() = 0;
    virtual void draw() = 0;

    s32 hitTestRow(s32 x, s32 y);
    void setRowColor(s32 idx, u16 val);
    void setAllRowColors();
    void setScroll(s32 a, s32 b);
    void hideLayer();
    void showLayer();
    void flushRowColors();
    void uploadBg();
    void setupBgControl();
    void setWidth(s32 v);
    void setTopRow(s32 v);
    void fitWidth(u32 start, u32 end);
    void layout5Rows();
    void layout4Rows();
    void layout3Rows();
    void layout2Rows();
    void layout1Row();
    void freeBg();
    BOOL loadBg();
    BOOL loadBgFile(void *file);

    /* 0x04 */ u8 *bgScreen;
    /* 0x08 */ u16 rowColors[5];
    /* 0x12 */ u8 rowColorsDirty;
    /* 0x14 */ s32 width;
    /* 0x18 */ s16 scrollX;
    /* 0x1a */ s16 scrollY;
    /* 0x1c */ s16 topY;
    /* 0x1e */ s16 numRows;
};

class ChoiceSliderWindow : public ChoiceWindow {
public:
    ChoiceSliderWindow();
    virtual ~ChoiceSliderWindow();
    virtual void update();
    virtual void draw();

    void updateDecided();
    void enterDecided();
    void updateCursorReturn();
    void enterCursorReturn();
    void updateButtonUp();
    void updateButtonDown();
    void enterButtonDown();
    void updatePressing();
    void enterPressing();
    void updateButtonFocus();
    void enterButtonFocus();
    void updateReleased();
    void enterReleased();
    void updateReleasing();
    void enterReleasing();
    void updateGrabbed();
    void enterGrabbed();
    void updateGrabbing();
    void enterGrabbing();
    void updateSliderFocus();
    void enterSliderFocus();
    void updateHidden();
    void enterHidden();
    void setCursorAnim(s32 v);
    void requestClose();
    void requestPress();
    void requestButtonFocus();
    void releaseKnob();
    void grabKnob();
    void requestSliderFocus();
    s32 getState();
    BOOL isButtonFocused();
    BOOL isSliderFocused();
    s32 getTrackBottomY();
    s32 getTrackTopY();
    s32 getKnobY();
    s32 getKnobX();
    void setSliderPos(s32 v);
    void setCursorVisible(u8 v, BOOL flag);
    BOOL isKnobHeld();
    void close();
    void openWidgets();

    /* 0x020 */ ChoiceHandCursor cursor;
    /* 0x06c */ LabelButton okButton;
    /* 0x0dc */ ChoiceSlider slider;
    /* 0x134 */ s32 state;
    /* 0x138 */ u8 sliderFocusRequest;
    /* 0x139 */ u8 knobGrabbed;
    /* 0x13a */ u8 buttonFocusRequest;
    /* 0x13b */ u8 pressRequest;
    /* 0x13c */ u8 closeRequest;
    /* 0x13d */ u8 cursorVisible;
};

class ChoiceListWindow : public ChoiceWindow {
public:
    ChoiceListWindow();
    virtual ~ChoiceListWindow();
    virtual void update();
    virtual void draw();

    void setCursorVisible(u8 v, BOOL flag);
    BOOL blinkStep(s32 a);
    void resetBlink();
    void setCursorRow(s32 v);
    void startCursorSelect();
    void hideCursor();
    void startCursorAppear();
    BOOL isCursorSelectDone();
    BOOL isCursorPointing();

    /* 0x20 */ ChoiceHandCursor cursor;
    /* 0x6c */ s32 cursorRow;
    /* 0x70 */ s32 blinkCount;
    /* 0x74 */ u8 cursorVisible;
};



class ChoiceListCursor {
public:
    ChoiceListCursor(ChoiceWindow *window);
    ~ChoiceListCursor();
    void playDecideSe();
    BOOL updateKeys();
    BOOL updateTouch();
    BOOL checkDeviceSwitch();
    void freeLabels();
    void clearLabels();
    void redrawLabels();
    void createLabels();
    void resetKeyRepeat();
    void calcMaxWidth();
    BOOL isTouchMode();
    void update();
    void close();
    void hideText();
    void showText();
    void open();
    u32 getMaxWidth();
    s32 getResult();
    s32 getRow();
    s32 getCount();
    void setList(ChoiceList *p);

    /* 0x00 */ s32 row;
    /* 0x04 */ ChoiceWindow *listWindow;
    /* 0x08 */ TextLabel *labels[5];
    /* 0x1c */ u32 maxWidth;
    /* 0x20 */ ChoiceList *list;
    /* 0x24 */ s32 confirmDelay;
    /* 0x28 */ s32 repeatTimer;
    /* 0x2c */ s32 repeatDir;
};

class ChoiceSliderCursor {
public:
    ChoiceSliderCursor(ChoiceSliderWindow *window);
    ~ChoiceSliderCursor();

    void updateOkButton();
    void focusOkButton();
    void updateSlider();
    void focusSlider();
    BOOL isConfirmPressed();
    BOOL isOkButtonTapped();
    BOOL isGrabKeyReleased();
    BOOL isTouchReleased();
    BOOL isGrabKeyPressed();
    BOOL isKnobTouched();
    void updateGrab();
    void updateFocus();
    BOOL checkDeviceSwitch();
    void freeLabels();
    void clearLabels();
    void redrawLabels();
    void createLabels();
    void calcMaxWidth();
    BOOL isCursorHidden();
    BOOL isGrabbing();
    BOOL isOkButtonFocused();
    BOOL isSliderFocused();
    void update();
    void close();
    void hideText();
    void showText();
    void open();
    s32 getResult();
    u32 getMaxWidth();
    s32 getPos();
    void setList(ChoiceList *p);

    /* 0x00 */ ChoiceSliderWindow *sliderWindow;
    /* 0x04 */ s32 speed;
    /* 0x08 */ s32 sliderPos;
    /* 0x0c */ s32 prevPos;
    /* 0x10 */ s32 grabOffsetY;
    /* 0x14 */ TextLabel *labels[5];
    /* 0x28 */ u32 maxWidth;
    /* 0x2c */ s32 focus;
    /* 0x30 */ u8 grabbing;
    /* 0x31 */ u8 confirmedByStart;
    /* 0x34 */ ChoiceList *list;
};

class ChoiceDialog {
public:
    ChoiceDialog();
    virtual ~ChoiceDialog();
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual BOOL isClosed() = 0;
    virtual BOOL justDecided() = 0;
    void requestOpen();

    /* 0x04 */ u8 openRequest;
};

class ChoiceSliderDialog : public ChoiceDialog {
public:
    ChoiceSliderDialog();
    virtual ~ChoiceSliderDialog();
    virtual void update();
    virtual void draw();
    virtual BOOL isClosed();
    virtual BOOL justDecided();

    void layoutWindow();
    void updateClosing();
    void enterClosing();
    void updateSelecting();
    void enterSelecting();
    void updateOpening();
    void enterOpening();
    void updateClosed();
    void enterClosed();
    void setChoices(ChoiceList *p);

    /* 0x008 */ s32 state;
    /* 0x00c */ ChoiceSliderWindow window;
    /* 0x14c */ ChoiceSliderCursor cursor;
    /* 0x184 */ s32 scrollX;
    /* 0x188 */ s32 scrollY;
    /* 0x18c */ s32 slideTimer;
    /* 0x190 */ u8 decided;
};

class ChoiceListDialog : public ChoiceDialog {
public:
    ChoiceListDialog();
    virtual ~ChoiceListDialog();
    virtual void update();
    virtual void draw();
    virtual BOOL isClosed();
    virtual BOOL justDecided();

    void layoutWindow();
    void updateClosing();
    void enterClosing();
    void updateSelecting();
    void enterSelecting();
    void updateOpening();
    void enterOpening();
    void updateClosed();
    void enterClosed();
    void setChoices(ChoiceList *p);

    /* 0x08 */ s32 state;
    /* 0x0c */ ChoiceListWindow window;
    /* 0x84 */ ChoiceListCursor cursor;
    /* 0xb4 */ s32 scrollX;
    /* 0xb8 */ s32 scrollY;
    /* 0xbc */ s32 slideTimer;
    /* 0xc0 */ u8 decided;
};

class ChoiceMenu {
public:
    ChoiceMenu();
    ~ChoiceMenu();
    void draw();
    BOOL justDecided();
    BOOL isIdle();
    void open();
    void update();
    void setSliderChoices(ChoiceList *p);
    void setListChoices(ChoiceList *p);

    /* 0x000 */ ChoiceDialog *active;
    /* 0x004 */ ChoiceListDialog listDialog;
    /* 0x0c8 */ ChoiceSliderDialog sliderDialog;
    /* 0x25c */ u8 closedThisFrame;
};

#endif
