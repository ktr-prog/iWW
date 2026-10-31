#ifndef SND_SNDSCENEBASE_H
#define SND_SNDSCENEBASE_H

#include "types.h"

class SndSceneBase {
public:
    SndSceneBase();
    virtual ~SndSceneBase();
    virtual void vfunc_08();
    virtual void load();
    virtual void update(s32 cameraDistance);
    virtual void fadeOutAll();
    virtual void unload();
    virtual void beginTalk(s32 a);
    virtual void endTalk();
    virtual void setBankVariant(s32 a);
    virtual void onBgmChange(u32 a, u32 c);
    void stopPlayers(s32 v);
    void setupHeaps(u32 a, s32 b);
    void createPlayer4Heap();
    void createPlayer11Heaps(s32 n);
    void createPlayer5Heap();
    void createPlayer6Heaps();
    void createPlayer17Heaps();
    void createPlayer18And19Heaps();
    void createPlayer13Heap();
    void createPlayer12Heaps();

    /* 0x04 */ s8 id;
    /* 0x05 */ u8 f5;
    /* 0x06 */ u8 f6;
};

#endif
