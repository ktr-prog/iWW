#include "types.h"
#include "snd/Melody.h"
#include "save/SaveData.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0206d988.h"

extern SaveData gSaveData;

extern "C" {
s32 data_020ddf8c = -1;

s64 func_02133540(u32, u32, u32);
}

MelodyPlayer::~MelodyPlayer()
{
}

extern "C" {

void Melody_Pack(u32 *dst, u8 *src) {
    s32 i;
    dst[0] = 0;
    dst[1] = 0;
    for (i = 0; i < 16; i++) {
        s32 v = src[i] & 0xf;
        *(s64 *)dst |= (s64)v << (i * 4);
    }
}

void Melody_Unpack(u32 *src, u8 *dst) {
    s32 i;
    for (i = 0; i < 16; i++) {
        dst[i] = (u8)(func_02133540(src[0], src[1], i * 4) & 0xf);
    }
}

}

extern "C" {

void Melody_ResetToDefault() { Melody_SaveDefaultPattern(); }

void Melody_SetPacked(u32 *a) {
    Melody_Unpack(a, gMelodyEditPattern);
    Melody_ApplyEditPattern();
}

void Melody_ApplyEditPattern() { Snd_MelodySetPattern(&gMelodyPlayer, gMelodyEditPattern); }

void Melody_PlayEditPattern(u32 a) { Snd_MelodyPlayPattern(&gMelodyPlayer, a, gMelodyEditPattern); }

void Melody_Play(u32 a) { Snd_MelodyPlay(&gMelodyPlayer, a); }

void Melody_PlayAt(VecFx32 *pos, u32 b) { Snd_MelodyPlayAt(&gMelodyPlayer, pos, b); }

void Melody_StartTrackA(s32 a) {
    Snd_MelodyStartTrackA(&gMelodyPlayer);
    if (a != 0) {
        sMelodyTimer = 0x190;
    } else {
        sMelodyTimer = 0x14;
    }
}

void Melody_PlayNote(u32 a) { Snd_MelodyPlayNote(&gMelodyPlayer, a); }

BOOL Melody_IsBusy() {
    if (sMelodyTimer != 0 || Snd_MelodyIsPlaying(&gMelodyPlayer)) {
        return TRUE;
    }
    return FALSE;
}

void Melody_PlayRandom(u32 a) { Snd_MelodyPlayRandom(&gMelodyPlayer, a); }

void Melody_SaveRandomPattern() {
    u8 *p = Snd_MelodyApplyRandomPattern(&gMelodyPlayer);
    if (p) {
        Melody_Pack((u32 *)&gSaveData.townTune, p);
    }
}

void Melody_SaveDefaultPattern() {
    u8 *p = Snd_MelodyGetDefaultPattern();
    if (p) {
        Melody_Pack((u32 *)&gSaveData.townTune, p);
    }
}

void Melody_Init(void) {
    Snd_MelodyInit(&gMelodyPlayer);
    data_020ddf8c = -1;
    Melody_ApplyEditPattern();
}

void Melody_Update(void) {
    if (sMelodyTimer != 0) {
        sMelodyTimer--;
    }
    data_020ddf8c = (s32)Snd_MelodyUpdate(&gMelodyPlayer);
}

}

s32 sMelodyTimer;
u8 gMelodyEditPattern[0x10];
MelodyPlayer gMelodyPlayer;
