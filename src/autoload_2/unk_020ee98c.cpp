#include "types.h"
#include "sys/CmdSeq.h"
#include "snd/PlayCtx.h"
#include "snd/SndSeBytes4.h"
#include "snd/SndMgr.h"
#include "snd/SndSeGroup.h"
#include "sys/FndList.h"
#include "sys/TaskList.h"
#include "sys/ListNode.h"
#include "snd/Player.h"
#include "proto/autoload_2/unk_020ed81c.h"
#include "proto/autoload_2/unk_020ee98c.h"
#include "proto/autoload_2/unk_020ef150.h"
#include "proto/autoload_2/unk_020f0dec.h"
#include "proto/autoload_2/unk_021093f4.h"
#include "proto/autoload_2/unk_0210c084.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_0206d49c.h"


extern "C" void SndMgr_PlayTalkVoice(SndMgr *o, s32 mode, u32 kind, u32 a, u32 b) {
    s32 z;
    s32 y;
    s32 x;
    s32 v;
    u32 t;
    u32 m;
    u32 r;
    if (o->voiceType == 5) Fatal_Trap();
    z = 0;
    switch (mode) {
    case 0:
        if (a == 37) return;
        if (b == 37) return;
        if (a == 39 || b == 39) {
            SndMgr_PlaySe(&gSndMgr, 44);
            goto tail;
        }
        y = z;
        x = z;
        switch (kind) {
        case 0:
            t = data_021f5b64;
            if (t == 4) {
                if (data_021f5b60 == 1) {
                    data_021f5b60 = 0;
                } else {
                    data_021f5b60 = 1;
                }
            }
            m = data_021f5b60;
            if (m == 1) {
                data_021f5b48 += 1;
                y = data_021f5b48 * 40;
                if (y > 160) y = 160;
            }
            if (t > 4 && m == 1) {
                y -= (t - 4) << 5;
                if (y < 96) y = 96;
            }
            if (a == 16 || b == 16) {
                data_021f5b58 += 1;
            } else {
                data_021f5b58 = 0;
            }
            if (data_021f5b58 >= 2) {
                y = 172;
                x = 20;
            }
            break;
        case 1:
            if (data_021f5b54 != 0) {
                data_021f5b54 -= 1;
            } else {
                data_021f5b54 = (u8)(((u8)OS_GetTick()) >> 6) + 10;
            }
            switch (data_021f5b54) {
            case 0:
            case 8:
                y = 240;
                x = 125;
                break;
            case 1:
            case 9:
                y = 180;
                x = 110;
                break;
            case 2:
            case 10:
                y = 150;
                x = 90;
                break;
            case 4:
            case 12:
                y = 190;
                x = 125;
                break;
            case 5:
            case 13:
                y = 120;
                x = 110;
                break;
            case 6:
            case 14:
                y = 90;
                x = y;
                break;
            default:
                y = -77;
                x = 105;
                break;
            }
            break;
        case 2:
            r = data_021f5b54;
            if (r == 0) {
                data_021f5b4c = (u8)(((u8)OS_GetTick()) >> 6) + 14;
                data_021f5b54 = 1;
            } else if (r == data_021f5b4c) {
                data_021f5b54 = 0;
                if (data_021f5b50 == 0) {
                    data_021f5b50 = 1;
                } else {
                    data_021f5b50 = 0;
                }
            } else {
                data_021f5b54 = r + 1;
            }
            r = data_021f5b50;
            if (r == 0) {
                y = -(data_021f5b54 << 3);
            } else {
                y = 300 - (data_021f5b54 << 3);
            }
            if (r == 0) {
                x = (u8)(-(data_021f5b54 << 2));
            } else {
                x = (u8)(20 - (data_021f5b54 << 2));
            }
            if (data_021f5b6c == 0) data_021f5b54 = 1;
            break;
        case 3:
            if (data_021f5b54 != 0) {
                data_021f5b54 -= 1;
            } else {
                data_021f5b54 = (u8)(((u8)OS_GetTick()) >> 6) + 10;
            }
            switch (data_021f5b54) {
            case 0:
            case 8:
                y = 90;
                x = 100;
                break;
            case 1:
            case 9:
                y = 30;
                x = 85;
                break;
            case 2:
            case 10:
                y = 0;
                x = 65;
                break;
            case 4:
            case 12:
                y = 40;
                x = 100;
                break;
            case 5:
            case 13:
                y = -30;
                x = 85;
                break;
            case 6:
            case 14:
                y = -60;
                x = 65;
                break;
            default:
                y = -227;
                x = 80;
                break;
            }
            break;
        case 4:
            t = data_021f5b64;
            if (t == 4) {
                if (data_021f5b60 == 1) {
                    data_021f5b60 = 0;
                } else {
                    data_021f5b60 = 1;
                }
            }
            m = data_021f5b60;
            if (m == 1) {
                data_021f5b48 += 1;
                y = data_021f5b48 * 40;
                if (y > 160) y = 160;
            }
            if (t > 4 && m == 1) {
                y -= (t - 4) << 5;
                if (y < 96) y = 96;
            }
            if (a == 16 || b == 16) {
                data_021f5b58 += 1;
            } else {
                data_021f5b58 = 0;
            }
            if (data_021f5b58 >= 2) {
                y = 172;
                x = 20;
            }
            y += 128;
            break;
        }
        z += y;
        v = (u8)(x + 80);
        if (a == 0 || a == 38 || a == 39 || a == 40 || a == 41 || b == 0 || (u16)(b + 0xffda) <= 3) {
            data_021f5b6c = 0;
            data_021f5b68 = 0;
            data_021f5b64 = 0;
        }
        if (a == 42 || b == 42 || a == 43 || b == 43) {
            data_021f5b68 += 1;
            data_021f5b64 = 0;
        }
        data_021f5b64 += 1;
        data_021f5b6c += 1;
        if (a == 40 || a == 41 || a == 38) {
            if (a == 40) {
                sVoicePendingSyllable = data_021f5b74;
                z = 384;
                v = 110;
            }
            if (a == 41) {
                sVoicePendingSyllable = data_021f5b74;
                z = 256;
                v = 127;
            }
            m = sVoicePendingSyllable;
            if (a == 38) {
                v = 90;
                z = -128;
            }
            sVoicePendingVolume = v;
            sVoicePendingPitch = z;
            if (m != 0) {
                u32 id = SndMgr_GetVoiceSeqIndex(o, m);
                SndMgr_PlayVoice(o, (u16)(id + 1), SndMgr_ClampVolume(o, v), z);
            }
            sVoicePendingSyllable = 0;
            return;
        } else if (b == 40 || b == 41 || b == 38) {
            m = sVoicePendingSyllable;
            if (b == 40) {
                z = 384;
                v = 110;
            }
            if (b == 41) {
                z = 256;
                v = 127;
            }
            if (b == 38) {
                v = 90;
                z = -128;
            }
            sVoicePendingVolume = v;
            sVoicePendingPitch = z;
            if (m != 0) {
                u32 id = SndMgr_GetVoiceSeqIndex(o, m);
                SndMgr_PlayVoice(o, (u16)(id + 1), SndMgr_ClampVolume(o, v), z);
            }
            sVoicePendingSyllable = 0;
            t = SndVoice_GetSyllable(a, b);
            if (t != 95) sVoicePendingSyllable = t;
            return;
        } else {
            t = SndVoice_GetSyllable(a, b);
            if (t == 95) goto tail;
            sVoicePendingSyllable = t;
            sVoicePendingVolume = v;
            sVoicePendingPitch = z;
        }
tail:
        data_021f5b78 = a;
        data_021f5b74 = b;
        return;
    case 1:
        SndMgr_PlaySe(&gSndMgr, 44);
        break;
    case 2:
        break;
    }
}

s32 sVoicePendingPitch;
u16 sVoicePendingSyllable;
u16 data_021f5b74;
u16 data_021f5b78;
u8 data_021f5b68;
u8 data_021f5b64;
u8 data_021f5b60;
u8 data_021f5b48;
u8 data_021f5b4c;
u8 data_021f5b6c;
u8 data_021f5b50;
u8 sVoicePendingVolume;
u8 data_021f5b54;
u8 data_021f5b58;
