#ifndef SND_BGMVOLUMEMIXER_H
#define SND_BGMVOLUMEMIXER_H

#include "types.h"

class BgmManager;

class BgmVolumeChannel {
public:
    BgmVolumeChannel();
    ~BgmVolumeChannel();
    void set(s32 a, s32 b, u8 c);
    void clear();

    /* 0x00 */ u8 changed;
    /* 0x01 */ u8 masked;
    /* 0x02 */ u8 pad_02[2];
    /* 0x04 */ s32 volume;
    /* 0x08 */ s32 fadeFrames;
    /* 0x0c */ s32 state;
};

class BgmVolumeMixer {
public:
    BgmVolumeMixer(BgmManager *owner);
    ~BgmVolumeMixer();
    void clearMasks();
    void clearChanged();
    void applyVolume();
    void maskForTopRequest();
    void updateRequestVolume(BgmVolumeChannel *e);
    void updateSceneDuck(BgmVolumeChannel *e);
    void updatePositionDuck(BgmVolumeChannel *e);
    void updateFireworkDuck(BgmVolumeChannel *e);
    void updateFishDuck(BgmVolumeChannel *e);
    void updateTalkDuck(BgmVolumeChannel *e);
    void updateMenuDuck(BgmVolumeChannel *e);
    void updateChannel0(BgmVolumeChannel *e);
    void updateChannels();
    void endFireworkDuck();
    void startFireworkDuck();
    void endFishDuck();
    void startFishDuck();
    void endMenuDuck();
    void setMenuDuck(s32 i);
    void endTalkDuck();
    void startTalkDuck();
    void reset();
    void update();
    void exit();
    void init();

    /* 0x00 */ BgmManager *manager;
    /* 0x04 */ BgmVolumeChannel channels[8];
    /* 0x84 */ s32 talkDuckHold;
};

#endif
