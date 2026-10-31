#ifndef UI_LETTERTEXTLINE_H
#define UI_LETTERTEXTLINE_H

#include "types.h"
#include "talk/MsgString.h"

class EncodedString;
class TextLabel;

class LetterTextLine : public MsgString {
public:
    LetterTextLine();
    virtual ~LetterTextLine();
    virtual u32 capacity();
    virtual u8 *data();

    void setNameHighlight(u8 a, u8 b);
    void setHighlight(u8 a, u8 b, u32 c);
    void clearText();
    void setTextWithMarks(EncodedString *src, BOOL b);
    void setText(EncodedString *src);
    void redrawIfDirty(BOOL b);
    void createLabel();
    void freeLabel();
    void setTarget(u16 v, u32 x);

    /* 0x12 */ u8 text[0x2a];
    /* 0x3c */ TextLabel *textLabel;
    /* 0x40 */ u16 charBase;
    /* 0x42 */ u8 bgIndex;
    /* 0x43 */ u8 isSubScreen;
    /* 0x44 */ u8 isDirty;
    /* 0x45 */ u8 highlightStart;
    /* 0x46 */ u8 highlightLength;
    /* 0x47 */ u8 highlightAlt;
    /* 0x48 */ u8 nameHighlightStart;
    /* 0x49 */ u8 nameHighlightLength;
};

#endif
