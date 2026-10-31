#include "types.h"
#include "Unk_020d8c7c.h"
#include "sys/ClockDateTime.h"
#include "sys/ProcProfile.h"
#include "proto/main/unk_020039ec.h"
#include "proto/ov004/unk_ov004_0222bcfc.h"



class NewYearCountdown : public GameProc {
public:
    NewYearCountdown();
    virtual ~NewYearCountdown();
    virtual BOOL onCreate();
    virtual BOOL onExecute();

    /* 0x50 */ u8 prevSecondDigit;
    /* 0x51 */ u8 secondDigit;
    /* 0x52 */ u8 muteFirstTick;
    /* 0x53 */ u8 midnightSePlayed;
};

extern "C" {
u32 Scene_GetCurrent(void);
void Clock_GetDateTime(void *p);
}

extern "C" const u8 sNewYearCountdownScenes[0x34] = {
    0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0
};

extern "C" ProcProfile sNewYearCountdownProfile = { (void *(*)())NewYearCountdown_Create, 0x2a, 0x30 };

extern "C" NewYearCountdown *NewYearCountdown_Create() {
    return new NewYearCountdown;
}

NewYearCountdown::NewYearCountdown() {}
NewYearCountdown::~NewYearCountdown() {}

BOOL NewYearCountdown::onCreate() {
    muteFirstTick = 1;
    return TRUE;
}

BOOL NewYearCountdown::onExecute() {
    u32 idx = Scene_GetCurrent();
    ClockDateTime t;
    ((u32 *)&t)[0] = 0;
    ((u32 *)&t)[1] = 0;
    Clock_GetDateTime(&t);
    if (idx < 0x33) {
        if (sNewYearCountdownScenes[idx] != 0) {
            if (t.month == 0xc && t.day == 0x1f) {
                u32 secs = 0x15180 - (t.second + (t.minute * 0x3c + t.hour * 0xe10));
                u32 h = secs / 0xe10;
                secs = secs - h * 0xe10;
                u32 m = secs / 0x3c;
                secs = secs - m * 0x3c;
                secondDigit = secs % 10;
                if (secondDigit != prevSecondDigit) {
                    if (h == 0) {
                        if (m == 1 && secs == 0) {
                            if (muteFirstTick == 0) Snd_PlaySe(0x62);
                        } else if (m == 0) {
                            if (secs == 0) {
                                if (muteFirstTick == 0) Snd_PlaySe(0x61);
                            } else if (secs <= 10) {
                                if (muteFirstTick == 0) Snd_PlaySe(0x60);
                            } else {
                                if (muteFirstTick == 0) Snd_PlaySe(0x62);
                            }
                        }
                        muteFirstTick = 0;
                    }
                }
                prevSecondDigit = secondDigit;
            } else if (t.month == 1) {
                if (t.day == 1 && t.hour == 0 && t.minute == 0 && t.second == 0) {
                    if (midnightSePlayed == 0) {
                        Snd_PlaySe(0x61);
                        midnightSePlayed = 1;
                    }
                }
            }
        }
    }
    return TRUE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0222bcfc) {
    HOST_OVERLAY_VAR(sNewYearCountdownProfile),
    HOST_OVERLAY_VARS_END
};
