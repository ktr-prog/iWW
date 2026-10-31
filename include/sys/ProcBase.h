#ifndef SYS_PROCBASE_H
#define SYS_PROCBASE_H

#include "types.h"
#include "sys/TreeNode.h"
#include "sys/QNode.h"

class Heap;

class ProcBase {
public:
    static void *operator new(size_t size);
    static void operator delete(void *ptr);

    ProcBase();
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual void postCreate(s32 status);
    virtual BOOL onDelete();
    virtual BOOL preDelete();
    virtual BOOL postDelete(s32 status);
    virtual BOOL onExecute();
    virtual BOOL preExecute();
    virtual BOOL postExecute(u32 status);
    virtual BOOL onDraw();
    virtual BOOL preDraw();
    virtual BOOL postDraw(s32 status);
    virtual BOOL onDeleteRequest();
    virtual BOOL createHeapFitted(u32 size, Heap *parent);
    virtual BOOL createHeap(u32 size, Heap *parent);
    virtual BOOL allocResources();
    virtual ~ProcBase();

    void taskConnect();
    void taskExecute();
    void taskDraw();
    void taskCreate();
    void taskDelete();

    /* 0x04 */ u32 id;
    /* 0x08 */ u32 param;
    /* 0x0c */ u16 profile;
    /* 0x0e */ u8 state;
    /* 0x0f */ u8 deletePending;
    /* 0x10 */ u8 activatePending;
    /* 0x11 */ u8 createRetry;
    /* 0x12 */ u8 group;
    /* 0x13 */ u8 procFlags;
    /* 0x14 */ TreeNode treeNode;
    /* 0x28 */ QNode executeNode;
    /* 0x38 */ QNode drawNode;
    /* 0x48 */ void *seq;
    /* 0x4c */ Heap *procHeap;
};

typedef BOOL (ProcBase::*ProcPhaseFn)();
typedef void (ProcBase::*ProcPhasePostFn)(s32);
extern "C" s32 ProcBase_RunPhase(ProcBase *p, ProcPhaseFn main, ProcPhaseFn pre, ProcPhasePostFn post);

class GameProc : public ProcBase {
public:
    GameProc() {}
    virtual void postCreate(s32 status);
    virtual ~GameProc() {}
};

#endif
