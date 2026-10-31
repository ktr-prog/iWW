#ifndef SND_TVSOUND_H
#define SND_TVSOUND_H

#include "types.h"
#include "uptr.h"

class TvSound {
public:
    virtual void reset();
    virtual void release();
    virtual void vfunc_08(s32 id, void *arg);
    virtual void turnOn(s32 v);
    virtual void turnOff();
    virtual void startSounds();

    void startSe(s32 code, void *handle);
    void updatePosition(void *arg);

    void callTurnOff();
    void callTurnOn(s32 a);
    void callUpdate(s32 a, void *b);
    void callRelease();
    void callReset();

    /* 0x04 */ void *a;
    /* 0x08 */ void *b;
    /* 0x0c */ u8 c12;
};


class TvSoundProgram0 : public TvSound {
public:
    virtual void startSounds();
};

class TvSoundProgram1 : public TvSound {
public:
    virtual void startSounds();
};

class TvSoundProgram2 : public TvSound {
public:
    virtual void reset();
    virtual void vfunc_08(s32 id, void *arg);
    virtual void startSounds();

    /* 0x0d */ s8 d13;
};

class TvSoundProgram3 : public TvSound {
public:
    virtual void vfunc_08(s32 id, void *arg);
    virtual void startSounds();

    /* 0x0d */ s8 d13;
};

class TvSoundProgram5 : public TvSound {
public:
    virtual void vfunc_08(s32 id, void *arg);
    virtual void startSounds();

    /* 0x0d */ s8 d13;
};

class TvSoundProgram9 : public TvSound {
public:
    virtual void vfunc_08(s32 id, void *arg);
    virtual void startSounds();
};

class TvSoundWeather : public TvSound {
public:
    virtual void vfunc_08(s32 id, void *arg);
    virtual void startSounds();

    void pickNextLoop();

    /* 0x0d */ u8 c13;
    /* 0x0e */ u8 c14;
    /* 0x0f */ u8 c15;
};


class TvSoundProgram4 : public TvSound {
public:
    virtual void vfunc_08(s32 id, void *arg);
    virtual void startSounds();

    s32 pollVariable();

    /* 0x0e */ s16 e14;
    /* 0x10 */ s32 w16;
};

class TvSoundProgram6 : public TvSound {
public:
    virtual void vfunc_08(s32 id, void *arg);
    virtual void startSounds();

    /* 0x0d */ u8 d13;
};

class TvSoundProgram7 : public TvSound {
public:
    virtual void reset();
    virtual void vfunc_08(s32 id, void *arg);
    virtual void startSounds();

    /* 0x0e */ u16 e14;
    /* 0x10 */ u16 g16;
    /* 0x12 */ u16 h18;
    /* 0x14 */ u16 i20;
};

class TvSoundProgram8 : public TvSound {
public:
    virtual void reset();
    virtual void vfunc_08(s32 id, void *arg);
    virtual void startSounds();

    /* 0x0e */ u16 e14;
    /* 0x10 */ u16 g16;
};

class TvSoundProgram10 : public TvSound {
public:
    virtual void reset();
    virtual void vfunc_08(s32 id, void *arg);
    virtual void startSounds();

    /* 0x0d */ u8 d13;
    /* 0x0e */ u16 e14;
    /* 0x10 */ u16 g16;
    /* 0x12 */ u16 h18;
};

#ifndef HOST64
static_assert(sizeof(TvSoundProgram0) == 0x10 && sizeof(TvSoundProgram2) == 0x10 && sizeof(TvSoundWeather) == 0x10, "");
static_assert(sizeof(TvSoundProgram4) == 0x14 && sizeof(TvSoundProgram6) == 0x10 && sizeof(TvSoundProgram7) == 0x18, "");
static_assert(sizeof(TvSoundProgram8) == 0x14 && sizeof(TvSoundProgram10) == 0x14, "");
#endif

#endif
