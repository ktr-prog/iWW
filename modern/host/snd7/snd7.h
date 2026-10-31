#ifndef HOST_SND7_H
#define HOST_SND7_H

#include <stddef.h>

#include "../host.h"

typedef int8_t s8;
typedef int16_t s16;
typedef signed long long s64;
typedef int BOOL;

#include "host_ptr32.h"
typedef u32 ptr32;
#define TRUE 1
#define FALSE 0

#define SND_PLAYER_COUNT 16
#define SND_CHANNEL_COUNT 16
#define SND_TRACK_COUNT 32
#define SND_TRACK_COUNT_PER_PLAYER 16
#define SND_ALARM_COUNT 8
#define SND_TRACK_MAX_CALL 3
#define SND_INST_MAX_KEYSPLIT 8
#define SND_BANK_MAX_WAVEARC 4
#define SND_VOL_DB_MIN (-723)

#define SND_ENV_ATTACK 0
#define SND_ENV_DECAY 1
#define SND_ENV_SUSTAIN 2
#define SND_ENV_RELEASE 3

#define SND_CHN_TYPE_PCM 0
#define SND_CHN_TYPE_PSG 1
#define SND_CHN_TYPE_NOISE 2

#define SND_CHN_SYNC_START 0x1
#define SND_CHN_SYNC_STOP 0x2
#define SND_CHN_SYNC_TIMER 0x4
#define SND_CHN_SYNC_VOLUME 0x8
#define SND_CHN_SYNC_PAN 0x10

#define SND_LFO_PITCH 0
#define SND_LFO_VOLUME 1
#define SND_LFO_PAN 2

#define SND_INST_ILLEGAL 0
#define SND_INST_PCM 1
#define SND_INST_PSG 2
#define SND_INST_NOISE 3
#define SND_INST_DIRECTPCM 4
#define SND_INST_DUMMY 5
#define SND_INST_DRUM_TABLE 16
#define SND_INST_KEY_SPLIT 17

struct SNDWaveParam {
    u8 format;
    u8 loopEnabled;
    u16 samplerate;
    u16 timer;
    u16 loopStart;
    u32 loopLength;
};

struct SNDLfoParam {
    u8 target;
    u8 speed;
    u8 depth;
    u8 range;
    u16 delay;
};

struct SNDLfo {
    struct SNDLfoParam param;
    u16 delayCounter;
    u16 counter;
};

struct SNDExChannel;
typedef void (*SNDExChannelCallback)(struct SNDExChannel *chn, int status, void *userData);

struct SNDExChannel {
    u8 id;
    u8 type;
    u8 envStatus;
    struct {
        u8 active : 1;
        u8 start : 1;
        u8 autoSweep : 1;
        u8 syncFlag : 5;
    } flags;
    u8 panRange;
    u8 rootMidiKey;
    s16 userDecay2;
    u8 midiKey;
    u8 velocity;
    s8 initPan;
    s8 userPan;
    s16 userDecay;
    s16 userPitch;
    s32 envAttenuation;
    s32 sweepCounter;
    s32 sweepLength;
    u8 envAttack;
    u8 envSustain;
    u16 envDecay;
    u16 envRelease;
    u8 priority;
    u8 pan;
    u16 volume;
    u16 timer;
    struct SNDLfo lfo;
    s16 sweepPitch;
    s32 length;
    struct SNDWaveParam waveParam;
    union {
        const void *waveDataPtr;
        s32 dutyCycle;
    };
    SNDExChannelCallback callback;
    void *callbackUserData;
    struct SNDExChannel *channelLLNext;
};

struct SNDBankData;

struct SNDPlayer {
    struct {
        u8 active : 1;
        u8 prepared : 1;
        u8 paused : 1;
    } flags;
    u8 playerId;
    u8 unk_2[2];
    u8 prio;
    u8 volume;
    s16 extFader;
    u8 tracks[SND_TRACK_COUNT_PER_PLAYER];
    u16 tempo;
    u16 tempoRatio;
    u16 tempoCounter;
    u8 unk_1E[2];
    struct SNDBankData *bank;
};

struct SNDTrack {
    struct {
        u8 active : 1;
        u8 noteWait : 1;
        u8 muted : 1;
        u8 tie : 1;
        u8 noteFinishWait : 1;
        u8 portamento : 1;
        u8 cmp : 1;
        u8 channelMask : 1;
    } flags;
    u8 panRange;
    u16 program;
    u8 volume;
    u8 expression;
    s8 pitchBend;
    u8 bendRange;
    s8 pan;
    s8 extPan;
    s16 extFader;
    s16 extPitch;
    u8 envAttack;
    u8 envDecay;
    u8 envSustain;
    u8 envRelease;
    u8 priority;
    s8 transpose;
    u8 portamentoKey;
    u8 portamentoTime;
    s16 sweepPitch;
    struct SNDLfoParam mod;
    u16 channelMask;
    s32 wait;
    const u8 *base;
    const u8 *cur;
    const u8 *posCallStack[SND_TRACK_MAX_CALL];
    u8 loopCount[SND_TRACK_MAX_CALL];
    u8 callStackDepth;
    struct SNDExChannel *channelLLHead;
};

struct SNDAlarm {
    u8 enable;
    u8 id;
    u16 unk_2;
    u64 tick;
    u64 period;
    u8 alarm[0x2c];
} __attribute__((packed, aligned(4)));

struct SNDWork {
    struct SNDExChannel channels[SND_CHANNEL_COUNT];
    struct SNDPlayer players[SND_PLAYER_COUNT];
    struct SNDTrack tracks[SND_TRACK_COUNT];
    struct SNDAlarm alarms[SND_ALARM_COUNT];
};

struct SNDSharedWork {
    u32 finishedCommandTag;
    u32 playerStatus;
    u16 channelStatus;
    u16 captureStatus;
    u8 unk_C[0x14];
    struct {
        s16 localVars[16];
        u32 tickCounter;
    } players[SND_PLAYER_COUNT];
    s16 globalVars[16];
};

struct SNDDriverInfo {
    u8 work[0x1180];
    u32 channelControls[SND_CHANNEL_COUNT];
    u32 workPtr;
    u32 lockedChannels;
    u8 unk_XXX[24];
};

struct SNDCommand {
    struct SNDCommand *llNext;
    s32 id;
    uintptr_t arg[4];
};

struct SNDBinaryFileHeader {
    s8 signature[4];
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
};

struct SNDBinaryBlockHeader {
    u32 type;
    u32 size;
};

struct SNDInstParam {
    u16 wave[2];
    u8 rootKey;
    u8 envAttack;
    u8 envDecay;
    u8 envSustain;
    u8 envRelease;
    u8 pan;
};

struct SNDInstData {
    u8 type;
    u8 unk_1;
    struct SNDInstParam param;
};

struct SNDKeySplit {
    u8 key[SND_INST_MAX_KEYSPLIT];
    struct SNDInstData instruments[];
};

struct SNDDrumSet {
    u8 minKey;
    u8 maxKey;
    struct SNDInstData instruments[];
};

struct SNDWaveArc;
struct SNDWaveArcLink {
    ptr32 waveArc;
    ptr32 waveArcLLnext;
};

struct SNDBankData {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    struct SNDWaveArcLink waveArcLinks[SND_BANK_MAX_WAVEARC];
    u32 instCount;
    u32 instOffsets[];
};

struct SNDWaveArc {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    ptr32 waveArcLLHead;
    u8 unk_1C[28];
    u32 waveCount;
    u32 waveOffsets[];
};

struct SNDWaveData {
    struct SNDWaveParam param;
    u8 sampleData[];
};

_Static_assert(offsetof(struct SNDExChannel, waveParam) == 0x38, "SNDExChannel.waveParam");
_Static_assert(offsetof(struct SNDPlayer, tempoRatio) == 0x1a, "SNDPlayer.tempoRatio");
_Static_assert(offsetof(struct SNDPlayer, bank) >= 0x20, "SNDPlayer: the ARM9's fields come first");
_Static_assert(offsetof(struct SNDTrack, wait) == 0x20, "SNDTrack.wait");
_Static_assert(sizeof(struct SNDAlarm) == 0x40, "SNDAlarm");
_Static_assert(sizeof(struct SNDSharedWork) == 0x280, "SNDSharedWork");
_Static_assert(sizeof(struct SNDWaveArcLink) == 8, "SNDWaveArcLink");
#if UINTPTR_MAX == 0xffffffffu
_Static_assert(sizeof(struct SNDExChannel) == 0x54, "SNDExChannel");
_Static_assert(sizeof(struct SNDPlayer) == 0x24, "SNDPlayer");
_Static_assert(sizeof(struct SNDTrack) == 0x40, "SNDTrack");
_Static_assert(offsetof(struct SNDTrack, channelLLHead) == 0x3c, "SNDTrack.channelLLHead");
_Static_assert(sizeof(struct SNDWork) == 0x1180, "SNDWork");
#endif
_Static_assert(sizeof(struct SNDDriverInfo) == 0x11e0, "SNDDriverInfo");
_Static_assert(offsetof(struct SNDDriverInfo, workPtr) == 0x11c0, "SNDDriverInfo.workPtr");
_Static_assert(sizeof(struct SNDInstData) == 0xc, "SNDInstData");
_Static_assert(sizeof(struct SNDBankData) == 0x3c, "SNDBankData");

extern struct SNDWork snd7_work;
extern struct SNDSharedWork *snd7_shared;
extern const s16 snd7_decibel_square_table[128];
u16 snd7_calc_timer(int timer, int pitch);
u16 snd7_calc_channel_volume(int value);
s8 snd7_sin_idx(int x);
u16 snd7_calc_random(void);
void snd7_skip_pause(void);
void snd7_skip_resume(void);
BOOL snd7_read_inst_data(const struct SNDBankData *bank, s32 program, s32 midiKey, struct SNDInstData *inst);
BOOL snd7_note_on(struct SNDExChannel *chn, s32 midiKey, s32 velocity, s32 length, const struct SNDBankData *bank,
                  const struct SNDInstData *inst);

void snd7_setup_channel_pcm(int ch, const void *data, int format, int loop, int loopStart, int loopLength,
                            int volume, int volumeDiv, int timer, int pan);
void snd7_setup_channel_psg(int ch, int duty, int volume, int volumeDiv, int timer, int pan);
void snd7_setup_channel_noise(int ch, int volume, int volumeDiv, int timer, int pan);
void snd7_stop_channel(int ch, int hold);
void snd7_set_channel_volume(int ch, int vol, int volDiv);
void snd7_set_channel_timer(int ch, int timer);
void snd7_set_channel_pan(int ch, int pan);
BOOL snd7_is_channel_active(int ch);
void snd7_set_master_pan(int pan);
u32 snd7_get_channel_control(int ch);
void snd7_set_surround_decay(int decay);
void snd7_setup_capture(int idx, int format, void *data, int size, BOOL loop, int capCtrlSrc, int capCtrlDst);
BOOL snd7_is_capture_active(int idx);

void snd7_exchannel_init(void);
void snd7_update_exchannel(void);
void snd7_exchannel_main(BOOL step);
BOOL snd7_start_exchannel_pcm(struct SNDExChannel *chn, const struct SNDWaveParam *wave, const void *data, s32 length);
BOOL snd7_start_exchannel_psg(struct SNDExChannel *chn, s32 duty, s32 length);
BOOL snd7_start_exchannel_noise(struct SNDExChannel *chn, s32 length);
void snd7_set_exchannel_attack(struct SNDExChannel *chn, s32 attack);
void snd7_set_exchannel_decay(struct SNDExChannel *chn, s32 decay);
void snd7_set_exchannel_sustain(struct SNDExChannel *chn, s32 sustain);
void snd7_set_exchannel_release(struct SNDExChannel *chn, s32 release);
void snd7_release_exchannel(struct SNDExChannel *chn);
BOOL snd7_is_exchannel_active(struct SNDExChannel *chn);
struct SNDExChannel *snd7_alloc_exchannel(u32 channelMask, int priority, u32 flags, SNDExChannelCallback callback,
                                          void *userData);
void snd7_free_exchannel(struct SNDExChannel *chn);
void snd7_stop_unlocked_channel(u32 channelMask, u32 weak);
void snd7_lock_channel(u32 channelMask, u32 weak);
void snd7_unlock_channel(u32 channelMask, u32 weak);
u32 snd7_get_locked_channel(u32 weak);
void snd7_invalidate_wave(const void *start, const void *end);
void snd7_init_lfo_param(struct SNDLfoParam *p);

void snd7_seq_init(void);
void snd7_seq_main(BOOL step);
void snd7_prepare_seq(int player, const void *seq, u32 offset, struct SNDBankData *bank);
void snd7_start_prepared_seq(int player);
void snd7_start_seq(int player, const void *seq, u32 offset, struct SNDBankData *bank);
void snd7_stop_seq(int player);
void snd7_pause_seq(int player, BOOL flag);
void snd7_skip_seq(int player, u32 ticks);
void snd7_set_track_mute(int player, u32 trackMask, int muteMode);
void snd7_set_track_allocatable_channel(int player, u32 trackMask, u32 channelMask);
void snd7_invalidate_seq(const void *start, const void *end);
void snd7_invalidate_bank(const void *start, const void *end);
void snd7_set_player_param(int player, u32 offset, u32 data, int size);
void snd7_set_track_param(int player, u32 trackMask, u32 offset, u32 data, int size);

typedef struct {
    u32 cnt;
    uintptr_t sad;
    u16 tmr;
    u16 pnt;
    u32 len;
} SpuChannelRegs;
extern SpuChannelRegs spu_ch[16];
extern u16 spu_soundcnt;
extern u8 spu_capcnt[2];
extern uintptr_t spu_capdad[2];
extern u16 spu_caplen[2];
void spu_cnt_written(int ch, u32 old);
void spu_capcnt_written(int idx, u8 old);
void spu_mix_until(u64 cycles);

void snd7_output(const s16 *lr, u32 frames);

#endif
