#ifndef GFX_SPLREAL_H
#define GFX_SPLREAL_H


#include "types.h"
#include "uptr.h"

struct SplRealParticle;
struct SplRealEmitter;

struct SplRealPtclList {
    SplRealParticle *head;
    s32 count;
};
struct SplRealEmtList {
    SplRealEmitter *head;
    s32 count;
};

struct SplRealParticle {
    SplRealParticle *next;
    SplRealParticle *prev;
    u8 body[0x3c];
};

struct SplRealEmitter {
    SplRealEmitter *next;
    SplRealEmitter *prev;
    SplRealPtclList particles;
    SplRealPtclList childParticles;
    void *resource;
    u8 body[0x5c];
    void (*callback)(SplRealEmitter *, u32);
    void *userData;
    u32 w80;
};

struct SplRealRes {
    void *hdr;
    void *blk[6];
    u16 numFields;
};

struct SplRealTex {
    void *data;
    u32 w4, w8, w12;
    u16 h16, h18;
};

struct SplRealField {
    void *fn;
    void *params;
};

struct SplRealManager {
    void *(*alloc)(u32);
    SplRealEmtList active;
    SplRealEmtList freeEmitters;
    SplRealPtclList freeParticles;
    SplRealRes *res;
    SplRealTex *tex;
    u16 numRes, numTex;
    u16 maxEmitters, maxParticles;
    u32 polyIds;
    u32 w30;
    SplRealEmitter *cur;
    void *mtx;
};

static struct {
    SplRealManager *m; SplRealEmitter *e; SplRealParticle *p; SplRealRes *r; SplRealTex *t; SplRealField *f;
} sSplRealTypes __attribute__((used, unused));

#define SPL_MANAGER_SIZE HOST_SIZED(0x3c, SplRealManager)
#define SPL_EMITTER_SIZE HOST_SIZED(0x84, SplRealEmitter)
#define SPL_PARTICLE_SIZE HOST_SIZED(0x44, SplRealParticle)
#define SPL_RES_SIZE HOST_SIZED(0x20, SplRealRes)
#define SPL_TEX_SIZE HOST_SIZED(0x14, SplRealTex)
#define SPL_FIELD_SIZE HOST_SIZED(8, SplRealField)

#endif
