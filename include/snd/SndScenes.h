#ifndef SND_SNDSCENES_H
#define SND_SNDSCENES_H

#include "types.h"
#include "snd/SndSceneBase.h"
#include "snd/BgmBeatSync.h"


class SndScene01 : public SndSceneBase {
public:
    SndScene01();
    virtual ~SndScene01();
    virtual void load();
    virtual void beginTalk(s32 a);
    virtual void endTalk();
    virtual void setBankVariant(s32 a);
};

class SndScene02 : public SndScene01 {
public:
    SndScene02();
    virtual ~SndScene02();
    virtual void load();
};

class SndScene03 : public SndScene01 {
public:
    SndScene03();
    virtual ~SndScene03();
    virtual void load();
};

class SndScene10 : public SndSceneBase {
public:
    SndScene10();
    virtual ~SndScene10();
    virtual void load();
    virtual void update(s32 cameraDistance);
    virtual void beginTalk(s32 a);
    virtual void endTalk();
    virtual void onBgmChange(u32 a, u32 c);

    /* 0x08 */ BgmTempoTracker tempo;
    /* 0x1c */ u8 state;
    /* 0x1d */ u8 f1d;
};

class SndScene19 : public SndSceneBase {
public:
    SndScene19();
    virtual ~SndScene19();
    virtual void load();
};

class SndScene20 : public SndSceneBase {
public:
    SndScene20();
    virtual ~SndScene20();
    virtual void load();
};

class SndScene21 : public SndSceneBase {
public:
    SndScene21();
    virtual ~SndScene21();
    virtual void load();
};

class SndScene22 : public SndSceneBase {
public:
    SndScene22();
    virtual ~SndScene22();
    virtual void load();
};

class SndScene23 : public SndSceneBase {
public:
    SndScene23();
    virtual ~SndScene23();
    virtual void load();
};

class SndScene24 : public SndSceneBase {
public:
    SndScene24();
    virtual ~SndScene24();
    virtual void load();
};

class SndScene30 : public SndSceneBase {
public:
    SndScene30();
    virtual ~SndScene30();
    virtual void load();
};

class SndScene31 : public SndSceneBase {
public:
    SndScene31();
    virtual ~SndScene31();
    virtual void load();
};

class SndScene32 : public SndSceneBase {
public:
    SndScene32();
    virtual ~SndScene32();
    virtual void load();
};

class SndScene33 : public SndSceneBase {
public:
    SndScene33();
    virtual ~SndScene33();
    virtual void load();
};

class SndScene34 : public SndSceneBase {
public:
    SndScene34();
    virtual ~SndScene34();
    virtual void load();
};

class SndScene35 : public SndSceneBase {
public:
    SndScene35();
    virtual ~SndScene35();
    virtual void load();
};

class SndScene40 : public SndSceneBase {
public:
    SndScene40();
    virtual ~SndScene40();
    virtual void load();
};

class SndScene41 : public SndSceneBase {
public:
    SndScene41();
    virtual ~SndScene41();
    virtual void load();
    virtual void update(s32 cameraDistance);
    virtual void onBgmChange(u32 a, u32 c);

    /* 0x08 */ BgmBeatSync beatSync;
};

class SndScene42 : public SndSceneBase {
public:
    SndScene42();
    virtual ~SndScene42();
    virtual void load();
};

class SndScene43 : public SndSceneBase {
public:
    SndScene43();
    virtual ~SndScene43();
    virtual void load();
};

class SndScene44 : public SndSceneBase {
public:
    SndScene44();
    virtual ~SndScene44();
    virtual void load();
};

class SndScene45 : public SndSceneBase {
public:
    SndScene45();
    virtual ~SndScene45();
    virtual void load();
};

class SndScene46 : public SndSceneBase {
public:
    SndScene46();
    virtual ~SndScene46();
    virtual void load();
};

class SndScene47 : public SndSceneBase {
public:
    SndScene47();
    virtual ~SndScene47();
    virtual void load();
};

class SndScene48 : public SndSceneBase {
public:
    SndScene48();
    virtual ~SndScene48();
    virtual void load();
};

class SndScene50 : public SndSceneBase {
public:
    SndScene50();
    virtual ~SndScene50();
    virtual void load();
};

class SndScene51 : public SndSceneBase {
public:
    SndScene51();
    virtual ~SndScene51();
    virtual void load();
    virtual void fadeOutAll();
};

class SndScene52 : public SndSceneBase {
public:
    SndScene52();
    virtual ~SndScene52();
    virtual void load();
};

class SndScene60 : public SndScene01 {
public:
    SndScene60();
    virtual ~SndScene60();
    virtual void load();
};

class SndScene99 : public SndSceneBase {
public:
    SndScene99();
    virtual ~SndScene99();
    virtual void load();
};

#if __SIZEOF_POINTER__ == 4
static_assert(sizeof(SndScene10) == 0x20, "SndScene10");
static_assert(sizeof(SndScene41) == 0x38, "SndScene41");
#endif

#endif
