#ifndef SND_SNDPOSNODE_H
#define SND_SNDPOSNODE_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "sys/FndList.h"
#include "snd/SndSeqHandle.h"

class SndPosList;

class SndPosNode {
public:
    void init(SndPosList *list);
    void play(s32 v, VecFx32 *p);
    void restart();
    void stop();
    BOOL isFinished();
    void updatePan();
    void playOnce(u32 v, VecFx32 *p);
    void setPitch(s32 v);
    void setBgmPan(VecFx32 *p);
    void release();

    /* 0x00 */ void *link[2];
    /* 0x08 */ SndSeqHandle h;
    /* 0x0c */ VecFx32 pos;
    /* 0x18 */ u16 id;
    /* 0x1a */ u8 b1a;
    /* 0x1b */ u8 b1b;
};

class SndPosList {
public:
    SndPosList *release();
    void init();
    void add(SndPosNode *node);
    void update();
    void remove(SndPosNode *node);
    void playAt(s32 v, VecFx32 *p);

    /* 0x00 */ FndList list;
    /* 0x0c */ SndSeqHandle h;
};

#endif
