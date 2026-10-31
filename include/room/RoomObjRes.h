#ifndef ROOM_ROOMOBJRES_H
#define ROOM_ROOMOBJRES_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "snd/SndSeEmitter.h"


class RoomObjRes;
struct RoomObjTexHandle;
class RoomObjSe;

extern "C" {
void *RoomObjRes_GetBca(RoomObjRes *self, u32 i);
void *RoomObjRes_GetBma(RoomObjRes *self, u32 i);
void *RoomObjRes_GetBta(RoomObjRes *self, u32 i);
void RoomObjRes_Free(RoomObjRes *self);
s32 RoomObjRes_Load(RoomObjRes *self, const char *s);
void *RoomObjRes_GetModel(RoomObjRes *self);
void RoomObjTex_Construct(RoomObjTexHandle *self);
void RoomObjTex_Destruct(RoomObjTexHandle *self);
void RoomObjTex_Reset(RoomObjTexHandle *self);
s32 RoomObjTex_Load(RoomObjTexHandle *self, const char *s);
void *RoomObjTex_Get(RoomObjTexHandle *self);
RoomObjSe *RoomObj_ConstructSe(RoomObjSe *self);
RoomObjSe *RoomObj_DestructSe(RoomObjSe *self);
void RoomObj_PlaySe(void *self, s32 v);
void RoomObj_DeactivateSe(void *self);
void RoomObj_SetSePos(RoomObjSe *self, VecFx32 *v);
void RoomObj_ActivateSe(void *self);
}

class RoomObjRes {
public:
    RoomObjRes();
    ~RoomObjRes();
    void clear();
    inline void *RoomObjRes_GetBca(u32 i) { return ::RoomObjRes_GetBca(this, i); }
    inline void RoomObjRes_Free() { ::RoomObjRes_Free(this); }
    inline void RoomObjRes_Load(const char *s) { ::RoomObjRes_Load(this, s); }
    inline void *RoomObjRes_GetModel() { return ::RoomObjRes_GetModel(this); }

    /* 0x00 */ void *archive;
    /* 0x04 */ void *model;
    /* 0x08 */ void *bcas[13];
    /* 0x3c */ void *bmas[13];
    /* 0x70 */ void *btas[13];
};

class RoomObjSe {
public:
    inline void RoomObj_PlaySe(s32 v) { ::RoomObj_PlaySe(this, v); }
    inline void RoomObj_DeactivateSe() { ::RoomObj_DeactivateSe(this); }
    inline void RoomObj_SetSePos(VecFx32 *v) { ::RoomObj_SetSePos(this, v); }
    inline void RoomObj_ActivateSe() { ::RoomObj_ActivateSe(this); }

    /* 0x00 */ SndSeEmitter emitter;
};

#endif
