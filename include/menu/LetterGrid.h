#ifndef MENU_LETTERGRID_H
#define MENU_LETTERGRID_H

#include "types.h"
#include "menu/InventoryGridTypes.h"

class LabelBalloon;
class LetterView;

class LetterGrid {
public:
    LetterGrid();
    virtual ~LetterGrid();

    void drawFocus(s32 a, s32 b, s32 *mtx);
    void drawUnderlay(s32 a, s32 b, s32 c, s32 *mtx);
    void drawMark(s32 a, s32 b);
    void drawLetterIcon(s32 a, s32 b, u32 c, LetterView *e, s32 *mtx);
    s32 getLetterPalette(LetterView *o);
    void drawHeldLetter(s32 a, s32 b, void *letter);
    void drawLetters2D(s32 a, s32 b);
    void drawLetters23(s32 a, s32 b);
    void drawLetters0A(s32 a, s32 b);
    void drawPocketLetters(s32 a, s32 b);
    void setHighlighted(s32 i);
    BOOL isHighlighted(s32 i);
    void highlightLetterKinds(u32 flags);
    void clearLetter(s32 i);
    void setLetter(s32 i, const void *letter);
    LetterView *getLetter(s32 i);
    void markSlot(s32 i);
    void clearMarks();
    void setCursorSlot(u32 v);
    void clearCursorSlot();
    u32 getCursorLift();
    BOOL isCursorSlot(s32 v);
    void showLetterName(LabelBalloon *out, s32 idx);
    void setBalloonLetterText(LabelBalloon *out, LetterView *o);
    u32 findLetterInRange(s32 a, s32 b, s32 start, u8 end);
    u32 findLetterAt23(s32 a, s32 b);
    u32 findLetterAt0A(s32 a, s32 b);
    u32 findLetterAt2D(s32 a, s32 b);
    u32 findPocketLetterAt(s32 a, s32 b);
    void updateCursorLift();
    void init(s32 x);

    /* 0x04 */ LetterView *letterArray;
    /* 0x08 */ Bitset64 occupiedBits;
    /* 0x10 */ Bitset64 markedBits;
    /* 0x18 */ Bitset64 highlightedBits;
    /* 0x20 */ s32 objPriority;
    /* 0x24 */ u8 cursorSlot;
    /* 0x25 */ u8 cursorLiftTimer;
    /* 0x26 */ u8 popTimer;
    /* 0x27 */ u8 heldScale;
};

#endif
