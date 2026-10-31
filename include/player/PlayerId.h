#ifndef PLAYER_PLAYERID_H
#define PLAYER_PLAYERID_H

#include "types.h"
#include "save/TownId.h"

class MsgString;

class PlayerId : public TownId {
public:
    PlayerId();
    PlayerId(void *o);
    PlayerId(const PlayerId &o);

    void setNameString(MsgString *x);
    void getNameString(MsgString *x);
    u8 *getName();
    void setName(void *src);
    s8 getGender();
    void setGender(u8 v);
    void setId(u16 v);
    u16 getId();
    void set(void *src, u16 a, s8 b, TownId *p);
    BOOL equals(PlayerId *o);
    BOOL isValid();
    void copyTo(PlayerId *o);
    void copyFrom(PlayerId *o);
    void clear();
    void setRaw(void *src);

    /* 0x0a */ u16 playerId;
    /* 0x0c */ u8 playerName[8];
    /* 0x14 */ s8 gender;
};

#endif
