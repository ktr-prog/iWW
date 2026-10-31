#ifndef SAVE_TOWNCOMPRESS_H
#define SAVE_TOWNCOMPRESS_H

#include "types.h"
#include "sys/OSThread.h"


class TownCompressThread {
public:
    /* 0x0000 */ OSThread thread;
    /* 0x00c0 */ u32 stackGuardLow;
    /* 0x00c4 */ u8 stack[0x1000];
    /* 0x10c4 */ u32 stackGuardHigh;
    /* 0x10c8 */ u8 done;

    u8 isDone();
    void start(u32 a);
    void kill();
    void init();
};

class TownCompressBuffer {
public:
    u32 size;
    u8 data[4];
    u8 dataBody[4];

    u32 getSize();
    void decompress();
    void compress();
};

#endif
