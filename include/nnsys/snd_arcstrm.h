#ifndef NNSYS_SND_ARCSTRM_H
#define NNSYS_SND_ARCSTRM_H

#include "types.h"
#include "nitro/fs.h"
#include "sys/OSThread.h"
#include "nnsys/fnd_list.h"


typedef struct NNSSndFader {
    s32 origin;
    s32 target;
    s32 counter;
    s32 frame;
} NNSSndFader;

typedef enum { NNS_SND_STRM_FORMAT_PCM8, NNS_SND_STRM_FORMAT_PCM16 } NNSSndStrmFormat;

enum { STRM_FORMAT_PCM8, STRM_FORMAT_PCM16, STRM_FORMAT_ADPCM };

typedef __UINTPTR_TYPE__ NNSSndStrmBufAddr;
static inline void *NNSi_SndStrmBufPtr(NNSSndStrmBufAddr a) { return (void *)a; }
static inline __UINTPTR_TYPE__ NNSi_SndArm7Addr(const void *p) { return (__UINTPTR_TYPE__)p; }

typedef void (*NNSSndStrmCallback)(s32 status, int numChannels, NNSSndStrmBufAddr buffer[], u32 len,
                                   NNSSndStrmFormat format, void *arg);

typedef struct NNSSndArcStrmCallbackParam {
    u32 playerNo;
    u32 strmNo;
} NNSSndArcStrmCallbackParam;
typedef struct NNSSndArcStrmCallbackInfo {
    u32 strmNo;
    u32 offset;
} NNSSndArcStrmCallbackInfo;
typedef BOOL (*NNSSndArcStrmCallback)(s32 status, const NNSSndArcStrmCallbackParam *param,
                                      NNSSndArcStrmCallbackInfo *info, void *arg);

typedef struct NNSSndStrmData {
    u8 fileHeader[0x10];
    u8 blockHeader[8];
    u8 format;
    u8 loopFlag;
    u8 numChannels;
    u8 pad_;
    u16 sampleRate;
    u16 timer;
    u32 loopStart;
    u32 loopEnd;
    u32 dataOffset;
    u32 numBlocks;
    u32 blockSize;
    u32 blockSamples;
    u32 lastBlockSize;
    u32 lastBlockSamples;
} NNSSndStrmData;

typedef struct NNSSndStrmAdpcmState {
    s16 prevSample;
    u8 prevIndex;
    u8 padding;
} NNSSndStrmAdpcmState;

typedef struct NNSSndArcStrmInfo {
    u32 fileId;
    u8 volume;
    u8 playerPrio;
    u8 playerNo;
    u8 flags;
} NNSSndArcStrmInfo;

typedef struct NNSSndStrmPlayer {
#ifdef HOST64
    u8 stream[136] __attribute__((aligned(8)));
#else
    u8 stream[0x5c];
#endif
    FSFile file;
    u32 fileOffset;
    NNSSndStrmData info;
    NNSSndFader fader;
    NNSSndStrmAdpcmState adpcmState[6];
    BOOL activeFlag : 1;
    BOOL playFlag : 1;
    BOOL startFlag : 1;
    BOOL fadeOutFlag : 1;
    BOOL dirtyFlag : 1;
    BOOL finishFlag : 1;
    BOOL monoFlag : 1;
    volatile int finishCounter;
    volatile BOOL prepareFlag;
    volatile int commandCount;
    int allocChannelCount;
    u8 numChannels;
    u8 padding;
    u8 chNoList[6];
    void *buffer;
    u32 bufSize;
    NNSSndStrmCallback strmCallback;
    void *strmCallbackArg;
    NNSSndArcStrmCallback sndArcStrmCallback;
    void *sndArcStrmCallbackArg;
    int strmNo;
    int playerNo;
    struct NNSSndStrmPlayer **handle;
    int prio;
    int initVolume;
    int volume;
    u32 curSample;
} NNSSndStrmPlayer;

typedef struct NNSSndStrmLoadCommand {
    NNSFndLink link;
    NNSSndStrmPlayer *player;
    s32 status;
    int numChannels;
    NNSSndStrmBufAddr buffer[6];
    u32 bufLen;
} NNSSndStrmLoadCommand;

typedef struct NNSSndStrmThread {
    union {
        OSThread thread;
        u8 threadAndStack[0x4c0];
    };
    OSThreadQueue queue;
    u32 pad_4c8;
    OSMutex mutex;
    NNSFndList commandList;
} NNSSndStrmThread;

#endif
