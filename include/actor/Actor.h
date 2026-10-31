#ifndef ACTOR_ACTOR_H
#define ACTOR_ACTOR_H

#include "types.h"
#include "uptr.h"
#include "sys/ProcBase.h"
#include "gfx/VecFx32.h"
#include "actor/ActorListNode.h"
class ActorCollider;

extern "C" void List_Remove(void *list, void *node);

struct ActorList {
    uptr head;
    uptr tail;
    ActorList() {
        head = 0;
        tail = 0;
    }
};

extern ActorList gActorList;

class Actor : public GameProc {
public:
    Actor();
    virtual BOOL preCreate();
    virtual void postCreate(s32 status);
    virtual BOOL preDelete();
    virtual BOOL postDelete(s32 status);
    virtual BOOL preExecute();
    virtual BOOL postExecute(u32 status);
    virtual BOOL preDraw();
    virtual BOOL postDraw(s32 status);
    virtual ~Actor() { List_Remove(&gActorList, &listNode); }

    void calcModelMatrix(void *out);
    void updatePosition(ActorCollider *v);
    void calcVelocity();
    void applyVelocity(ActorCollider *v);
    void setCullParams(s32 a, s32 b, s32 c);
    static void *spawn(u32 profile, u32 param, void *pos, void *angle, void *parent);
    static void setSpawnTransform(void *a, void *b);
    static void *findByProfile(u32 id, Actor *o);
    static void *findById(u32 id);

    /* 0x50 */ ActorListNode listNode;
    /* 0x5c */ VecFx32 position;
    /* 0x68 */ VecFx32 prevPosition;
    /* 0x74 */ u8 viewPos[0x18];
    /* 0x8c */ s16 rotX;
    /* 0x8e */ s16 rotY;
    /* 0x90 */ s16 rotZ;
    /* 0x92 */ s16 moveAngleX;
    /* 0x94 */ s16 moveAngleY;
    /* 0x96 */ s16 moveAngleZ;
    /* 0x98 */ s32 speed;
    /* 0x9c */ s32 gravity;
    /* 0xa0 */ s32 maxFallSpeed;
    /* 0xa4 */ VecFx32 velocity;
    /* 0xb0 */ u32 actorFlags;
    /* 0xb4 */ s32 cullHeight;
    /* 0xb8 */ s32 cullRadius;
    /* 0xbc */ s32 cullDepth;
    /* 0xc0 */ u32 unk_c0;
    /* 0xc4 */ VecFx32 drawPos;
    /* 0xd0 */ u16 drawTilt;
    /* 0xd2 */ u16 pad_d2;
};

#endif
