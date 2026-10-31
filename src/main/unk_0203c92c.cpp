#include "types.h"
#include "game/Unk_0203c92c_Bits.h"
#include "player/PlayerOptions.h"
#include "proto/main/unk_0203c92c.h"
#include "proto/main/unk_02097444.h"
#include "player/PlayerData.h"

extern "C" {
void MI_CpuCopy8(void *src, void *dst, u32 n);
}


PlayerOptions sPlayerOptions;
extern "C" PlayerOptions *PlayerOptions_Get() { return &sPlayerOptions; }

extern "C" BOOL PlayerOptions_IsHiragana() { return sPlayerOptions.isHiragana(); }

extern "C" void PlayerOptions_SetHiragana(s32 x) {
    if (x == 1) sPlayerOptions.setHiragana();
    else sPlayerOptions.clearHiragana();
    sPlayerOptions.markHiraganaChanged();
}

extern "C" BOOL PlayerOptions_IsStereo() { return sPlayerOptions.isStereo(); }

extern "C" void PlayerOptions_SetStereo(s32 x) {
    if (x == 1) sPlayerOptions.setStereo();
    else sPlayerOptions.clearStereo();
    sPlayerOptions.markStereoChanged();
}

extern "C" u32 PlayerOptions_GetTalkVoice() { return sPlayerOptions.getTalkVoice(); }

extern "C" void PlayerOptions_SetTalkVoice(u32 v) {
    sPlayerOptions.setTalkVoice(v);
    sPlayerOptions.markTalkVoiceChanged();
}

extern "C" void PlayerOptions_Commit() {
    PlayerOptions *r5, *r4;
    u8 l;
    r5 = static_cast<PlayerOptions *>(PlayerData_GetCurrent()->getOptions());
    r4 = PlayerOptions_Get();
    if (r4->isHiraganaChanged()) {
        if (PlayerOptions_IsHiragana() == 1) r5->setHiragana();
        else r5->clearHiragana();
    }
    if (r4->isStereoChanged()) {
        if (PlayerOptions_IsStereo() == 1) r5->setStereo();
        else r5->clearStereo();
    }
    if (r4->isTalkVoiceChanged()) {
        r5->setTalkVoice(PlayerOptions_GetTalkVoice());
    }
    PlayerOptions_CopyOut(r5, &l);
    r4->reset();
    PlayerOptions_CopyIn(r4, &l);
}

extern "C" void PlayerOptions_OnConstruct() {}

extern "C" void PlayerOptions_ConstructInPlayer() {}

extern "C" void PlayerOptions_DestructInPlayer() {}

extern "C" void PlayerOptions_OnDestruct() {}

void PlayerOptions::resetValues() {
    clearHiragana();
    clearStereo();
    setTalkVoice(0);
}

extern "C" void PlayerOptions_CopyOut(void *src, void *dst) { MI_CpuCopy8(src, dst, 1); }

extern "C" void PlayerOptions_CopyIn(void *dst, void *src) { MI_CpuCopy8(src, dst, 1); }

BOOL PlayerOptions::isHiragana() {
    if (((PlayerOptionBits *)&options)->hiragana) return TRUE;
    return FALSE;
}

void PlayerOptions::setHiragana() { options = (options & ~1) | 1; }

void PlayerOptions::clearHiragana() { options &= ~1; }

BOOL PlayerOptions::isStereo() {
    if (((PlayerOptionBits *)&options)->stereo) return TRUE;
    return FALSE;
}

void PlayerOptions::setStereo() { options |= 2; }

void PlayerOptions::clearStereo() { options &= ~2; }

u32 PlayerOptions::getTalkVoice() { return ((PlayerOptionBits *)&options)->talkVoice; }

void PlayerOptions::setTalkVoice(u32 v) {
    options = (options & ~0xc) | (((u8)v & 3) << 2);
}

PlayerOptions::PlayerOptions() { PlayerOptions_OnConstruct(); }

PlayerOptions::~PlayerOptions() { PlayerOptions_OnDestruct(); }

void PlayerOptions::reset() {
    resetValues();
    changedMask &= ~1;
    changedMask &= ~2;
    changedMask &= ~4;
}

BOOL PlayerOptions::isHiraganaChanged() {
    if (((Unk_0203c92c_Bits1 *)&changedMask)->b0) return TRUE;
    return FALSE;
}

BOOL PlayerOptions::isStereoChanged() {
    if (((Unk_0203c92c_Bits1 *)&changedMask)->b1) return TRUE;
    return FALSE;
}

BOOL PlayerOptions::isTalkVoiceChanged() {
    if (((Unk_0203c92c_Bits1 *)&changedMask)->b2) return TRUE;
    return FALSE;
}

void PlayerOptions::markHiraganaChanged() { changedMask = (changedMask & ~1) | 1; }

void PlayerOptions::markStereoChanged() { changedMask |= 2; }

void PlayerOptions::markTalkVoiceChanged() { changedMask |= 4; }

