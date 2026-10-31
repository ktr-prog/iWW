#ifndef NPC_SPNPCKATIE_H
#define NPC_SPNPCKATIE_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/SpNpcActor.h"
#include "talk/SpNpcKatieTalk.h"
#include "gfx/Mtx43.h"

class SpNpcKatie : public SpNpcActor {
public:
    SpNpcKatie() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual ~SpNpcKatie() {}
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL mainAct08();
    BOOL setupAct08();
    BOOL mainAct06();
    BOOL setupAct06();
    BOOL mainAct05();
    BOOL setupAct05();
    BOOL mainAct04();
    BOOL setupAct04();
    BOOL mainAct07();
    BOOL setupAct07();
    BOOL mainAct03();
    BOOL setupAct03();
    BOOL mainAct02();
    BOOL setupAct02();
    BOOL mainAct01();
    BOOL setupAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    /* 0x654 */ s32 act;
    /* 0x658 */ SpNpcKatieTalk talk;
    /* 0x70c */ u8 unk_70c;
    /* 0x70d */ u8 escortDeclined;
    /* 0x70e */ u16 stuckTimer;
    /* 0x710 */ u16 waitTimer;
    /* 0x714 */ VecFx32 prevPos;
    /* 0x720 */ s32 effectHandle;
    /* 0x724 */ u8 reunionStep;
};

#endif
