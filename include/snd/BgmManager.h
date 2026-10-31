#ifndef SND_BGMMANAGER_H
#define SND_BGMMANAGER_H

#include "types.h"
#include "snd/BgmVolumeMixer.h"
#include "snd/BgmSceneFade.h"

class BgmManager;

class BgmRequest {
public:
    BgmRequest() { initEmpty(); }
    BgmRequest(s32 a, u32 b, s32 c, s32 d, u8 e) { init(a, b, c, d, e); }
    ~BgmRequest() { func_02036c18(); }
    BOOL tickLifetime();
    void copyFrom(BgmRequest *src);
    void clear();
    void func_02036c18();
    BgmRequest *init(s32 a, u32 b, s32 c, s32 d, u8 e);
    BgmRequest *initEmpty();

    /* 0x00 */ s32 priority;
    /* 0x04 */ u16 bgmId;
    /* 0x06 */ u8 pad_06[2];
    /* 0x08 */ s32 stopFadeFrames;
    /* 0x0c */ s32 volume;
    /* 0x10 */ u8 muteDucks;
    /* 0x11 */ u8 transient;
    /* 0x12 */ u8 playing;
    /* 0x13 */ u8 removePending;
    /* 0x14 */ u8 volumePending;
    /* 0x15 */ u8 pad_15[3];
    /* 0x18 */ s32 lifetime;
};

class BgmRequestView : public BgmRequest {
public:
    BOOL clearPlaying() { playing = 0; return FALSE; }
    BOOL clearVolumePending();
};

typedef BOOL (BgmRequestView::*Unk_02034574_Fn)();

class EventBgm {
public:
    BgmManager *manager;
    u16 newYearFanfareBgm;
    u16 newYearNightBgm;
    u16 newYearDayBgm;
    u16 countdownBgm;
    u16 fireworksBgm;
    u8 countdownFadeActive;
    u8 yearChanged;
    u8 keep;
    u8 active;
    virtual ~EventBgm();
    EventBgm(BgmManager *a);
    void updateYearChanged();
    void stopCountdownFade();
    void startCountdownFade(u32 a);
    void stopFireworks();
    void stopCountdown();
    void stopNewYearDay();
    s32 stopNewYearDayAlias() { stopNewYearDay(); return 0; }
    void stopNewYearNight();
    void stopNewYearFanfare();
    void playFireworks(u32 a);
    void playCountdown(u32 a);
    void playNewYearDay(u32 a);
    void playNewYearNight(u32 a);
    void playNewYearFanfare(u32 a);
    void updateFireworks(BOOL a);
    void updateCountdown(BOOL a);
    void updateNewYearDay(BOOL a);
    void updateEvents();
    void setKeep(u32 a);
    void end();
    void start();
    void stop();
    void update();
    void exit();
    void init();
};

class FieldSpecialBgm {
public:
    BgmManager *manager;
    u16 currentBgm;
    u8 keep;
    u8 active;

    FieldSpecialBgm(BgmManager *a);
    virtual ~FieldSpecialBgm();
    void stopBgm();
    void play(s32 a, u32 b, u32 c);
    void setKeep(u32 a);
    void end();
    void start();
    void stop();
    void update();
    void exit();
    void init();
};

class HourlyBgm {
public:
    BgmManager *manager;
    s32 hour;
    u16 currentBgm;
    u8 hourFadeActive;
    u8 keep;
    u8 active;

    HourlyBgm(BgmManager *v);
    virtual ~HourlyBgm();
    void updateHourFade();
    void stopHourFade();
    void startHourFade(u32 x);
    void updateHour();
    void stopHourBgm();
    void playHourBgm();
    void setKeep(u32 v);
    void end();
    void start();
    void stop();
    void update();
    void exit();
    void init();
};

class BgmCommandQueue {
public:
    BgmCommandQueue(BgmManager *owner);
    ~BgmCommandQueue() { func_02035740(); }
    void flush();
    void clear();
    BgmCommandQueue *init(BgmManager *owner);
    void requestVolume(s32 a, s32 b);
    void requestStop(s32 a);
    void requestPlay(u16 a);
    void func_02035740();

    BgmManager *manager;
    u8 playPending;
    u8 pad_05;
    u16 playBgmId;
    u8 stopPending;
    u8 pad_09[3];
    s32 stopFadeFrames;
    u8 volumePending;
    u8 pad_11[3];
    s32 volume;
    s32 volumeFrames;
};


class BgmClock {
public:
    BgmClock();
    ~BgmClock();
    s32 year;
    u16 dayMonth;
    u8 minute;
    u8 hour;
    s32 second;
    s32 prevYear;
    u16 prevDayMonth;
    u16 prevMinuteHour;
    s32 prevSecond;

    void update();
    BOOL hasYearChanged();
    BOOL hasHourChanged();
    BOOL isTimeInRange(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);
    BOOL isMinuteInRange(u32 a, u32 b, u32 c, u32 d);
    BOOL isAt(u16 *a, u16 *b);
};

class FieldBgm {
public:
    HourlyBgm hourlyBgm;
    FieldSpecialBgm specialBgm;
    EventBgm eventBgm;
    virtual ~FieldBgm();
    FieldBgm(BgmManager *a);
    void setKeep(u32 a);
    void end();
    void start();
    void stop();
    void update();
    void exit();
    void init();
};

class RoomBgm {
public:
    BgmManager *manager;
    u8 currentScene;
    u16 sceneBgm;
    u8 closingFadeActive;
    u8 closingMusicPlaying;
    u8 closingForced;
    u8 active;
    u8 keep;
    virtual ~RoomBgm();
    void stopClosingMusic();
    void updateSceneBgm();
    void updateClosingMusic();
    void stopSceneBgm();
    void playSceneBgm(s32 a);
    void setKeep(u32 a);
    void end();
    void start();
    void forceClosingMusic();
    void stop();
    void update();
    void exit();
    void init();
    RoomBgm(BgmManager *a);
};


class FaintBgm {
public:
    virtual ~FaintBgm();
    BgmManager *manager;
    u16 currentBgm;
    u8 silenceActive;
    FaintBgm(BgmManager *o);
    void stop();
    void exit();
    void init();
    void fadeOut();
    void startSilence();
    void play();
};

class BgmTracks {
public:
    virtual ~BgmTracks();
    BgmTracks();
};

class BgmManager {
public:
    BgmManager();
    ~BgmManager();

    void updateHourChime();
    void exit();
    void init();
    void forEachRequest(Unk_02034574_Fn fn);
    void insertAt(s32 idx);
    BgmRequest *findKeptBefore(s32 n);
    s32 findByBgm(u16 id);
    s32 findByPriority(s32 v);
    s32 findPlaying();
    s32 findInsertPos(BgmRequestView *key);
    void tickRequests();
    void startTop();
    void clearPlaying();
    void removeMarked();
    void updateStop();
    void updateRequests();
    void releaseBgm(u16 id);
    void releasePriority(s32 v);
    void push(BgmRequestView *e);
    void postUpdate();
    void update();

    /* 0x000 */ BgmRequest requests[16];
    /* 0x1c0 */ s32 numRequests;
    /* 0x1c4 */ BgmVolumeMixer mixer;
    /* 0x24c */ BgmClock clock;
    /* 0x264 */ FieldBgm fieldBgm;
    /* 0x2a0 */ RoomBgm roomBgm;
    /* 0x2b4 */ BgmCommandQueue commands;
    /* 0x2d0 */ BgmSceneFade sceneFade;
    /* 0x2e4 */ FaintBgm faintBgm;
    /* 0x2f0 */ BgmTracks tracks;
    /* 0x2f4 */ u8 hourChimeDisabled;
    /* 0x2f5 */ u8 pad_2f5[3];
};


#endif
