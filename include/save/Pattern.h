#ifndef SAVE_PATTERN_H
#define SAVE_PATTERN_H

#include "types.h"
#include "save/EncodedName8.h"
#include "save/PatternOrder.h"
#include "save/Unk_020942c8.h"


class EncodedString16Buf;

class PatternInfo : public Unk_020942c8 {
public:
    PatternInfo();
    ~PatternInfo();
    /* 0x16 */ EncodedTitle16 title;
    /* 0x26 */ struct {
        u8 lo : 4;
        u8 hi : 4;
    } tastePalette;

    void setTaste(u32 v);
    u8 getTaste();
    void setTitleRaw(u8 *src);
    void setTitleEncoded(EncodedString16Buf *o);
    void setTitle(void *x);
    void getTitleRaw(u8 *dst);
    void getTitleEncoded(EncodedString16Buf *o);
    void getTitle(void *x);
    Unk_020942c8 *getAuthor();
    void setAuthor(Unk_020942c8 *src);
    void setAuthorToCurrentPlayer();
    void setPalette(u32 v);
    u8 getPalette();
    u8 *getPaletteData();
    BOOL infoEquals(PatternInfo *o);
};

class Pattern {
public:
    Pattern();
    ~Pattern();
    /* 0x000 */ s64 pixels[0x40];
    /* 0x200 */ PatternInfo info;

    PatternInfo *getInfo();
    void fill(u32 v);
    void setPixels(void *dst);
    u8 *getPixels();
    BOOL equals(Pattern *o);
};

class TownFlagPattern {
public:
    /* 0x0 */ Pattern pixels;
    TownFlagPattern();
    ~TownFlagPattern();
};

class AbleSistersPatterns {
public:
    AbleSistersPatterns();
    ~AbleSistersPatterns();
    /* 0x0 */ Pattern patterns[8];

    Pattern *getPattern(u8 i);
    void initDefaultPatterns();
};

class PlayerPatterns {
public:
    PlayerPatterns();
    ~PlayerPatterns();
    /* 0x0000 */ Pattern patterns[8];
    /* 0x1140 */ PatternOrder patternOrder;

    PatternOrder *getPatternOrder();
    Pattern *getPatternByOrder(u32 i);
    Pattern *getPattern(u8 i);
    void replaceAuthorTown(Unk_020942c8 *a, Unk_020942c8 *b);
    void initDefaultPatterns(Unk_020942c8 *a);
};

static_assert(sizeof(PatternInfo) == 0x28, "PatternInfo: DS save layout");
static_assert(sizeof(Pattern) == 0x228 && __alignof__(Pattern) == 4, "Pattern: DS save layout");
static_assert(sizeof(AbleSistersPatterns) == 0x1140, "AbleSistersPatterns: SaveData::ableSistersPatterns");
static_assert(sizeof(PlayerPatterns) == 0x1148, "PlayerPatterns: the head of PlayerData");

#endif
