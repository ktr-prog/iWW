#ifndef ACTOR_SPNPCACTOR_H
#define ACTOR_SPNPCACTOR_H

#include "types.h"
#include "actor/NpcActor.h"
#include "npc/NpcResHandle.h"

class SpNpcActor : public NpcActor {
public:
    SpNpcActor() {}
    virtual ~SpNpcActor();
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL preDelete();
    virtual void getName(MsgString *buf);
    virtual u32 getGender();
    virtual BOOL canPlayTalkMelody();
    virtual void onTalkMelodyPlayed();
    virtual u16 getSpecies();
    /* 0xa8 */ virtual s32 getWalkAnimSpeedScale();

    BOOL loadAnimSet();
    void setColliderSize(s32 a, s32 b);

    /* 0x640 */ SpNpcAnimHeapHandle animHeapHandle;
    /* 0x648 */ s32 colliderRadius;
    /* 0x64c */ s32 colliderHeight;
    /* 0x650 */ u8 talkMelodyPlayed;
    /* 0x651 */ u8 actCounter;
};

#endif
