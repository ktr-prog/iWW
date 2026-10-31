#ifndef TALK_MSGTAG_H
#define TALK_MSGTAG_H

#include "types.h"

class MsgString;

class MsgTag {
public:
    MsgTag();
    u8 getArgU8();
    void getAltTextArgs(u32 *a, char **b, char **c);
    void getStrings3(char **a, char **b, char **c);
    void getStrings2(char **a, char **b);
    s32 getSlotIndex();
    BOOL isSlotTag();
    u32 readArgBytes8Strings2(u8 *a1, u8 *a2, u8 *a3, u8 *s0, u8 *s1, u8 *s2, u8 *s3, u8 *s4, MsgString *s5,
                              MsgString *s6);
    u32 getTrailingStringsSize();
    u32 readArgStrings5(u8 *a1, MsgString *a2, u8 *a3, MsgString *s0, u8 *s1, MsgString *s2, u8 *s3,
                        MsgString *s4, u8 *s5, MsgString *s6);
    u32 readArgStrings4(u8 *a1, MsgString *a2, u8 *a3, MsgString *s0, u8 *s1, MsgString *s2, u8 *s3,
                        MsgString *s4);
    u32 readArgStrings3(u8 *a1, MsgString *a2, u8 *a3, MsgString *s0, u8 *s1, MsgString *s2);
    u32 readArgStrings2(u8 *a1, MsgString *a2, u8 *a3, MsgString *s0);
    void getArgU16(u16 *out);
    void getArgBytes(u8 *buf, s32 n);
    void getArgs5(u8 *a, u8 *b, u8 *c, u8 *d, u8 *e);
    void getArgs4(u8 *a, u8 *b, u8 *c, u8 *d);
    void getArgs3(u8 *a, u8 *b, u8 *c);
    void getArgs2(u8 *a, u8 *b);
    void getArgs1(u8 *a);
    void parse(u8 *p);

    void eq(s32 x, s32 y, u8 *f) {
        if (group == x && id == y) *f = 1;
    }

    /* 0x00 */ s32 group;
    /* 0x04 */ s32 id;
    /* 0x08 */ u32 argLen;
    /* 0x0c */ char *args;
    /* 0x10 */ u8 *raw;
};

#endif
