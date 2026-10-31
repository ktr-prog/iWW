#include "talk/MsgString25.h"
#include "host_labels.h"
#include "talk/MsgString9C.h"
#include "types.h"
#include "item/Letter.h"
#include "save/SaveData.h"
#include "item/LetterView.h"
#include "player/PlayerData.h"
#include "save/TownId.h"
#include "player/PlayerBank.h"
#include "proto/autoload_2/unk_0211ea4c.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_020637e4.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097110.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b2c50.h"



extern SaveData gSaveData;
#define gSaveTownId HOST_LABEL(TownId *, gSaveTownId)
extern "C" u8 sFatalEntered;

s32 data_020e1e08 = 6;
s32 data_020e1e04 = 0x1c;
s32 data_020e1e00 = 6;
s32 data_020e1dfc = 0x1c;
s32 data_020e1df8 = 0x10;
s32 data_020e1e0c = 0x1c;

extern "C" s32 Startup_OnCardPulledOut() {
    sFatalEntered = 1;
    return 1;
}

extern "C" void Startup_SetCardPulledOutCallback() { CARD_SetPulledOutCallback(Startup_OnCardPulledOut); }

extern "C" void PlayerBank_Construct() {}

extern "C" void PlayerBank_Destruct() {}

extern "C" void PlayerBank_Clear(PlayerBank *p) {
    p->balance = 0;
    p->donationLevel = 0;
}

extern "C" u32 PlayerBank_GetBalance(PlayerBank *p) { return p->balance; }

extern "C" void PlayerBank_SetBalance(PlayerBank *p, u32 v) { p->balance = v; }

extern "C" s32 Donation_GetTotal() { return gSaveData.donationTotal; }

extern "C" void Donation_SetTotal(s32 v) {
    if (v > 999999999) v = 999999999;
    gSaveData.donationTotal = v;
}

extern "C" u32 PlayerBank_GetDonationLevel(PlayerBank *p) { return p->donationLevel; }

extern "C" void PlayerBank_SetDonationLevel(PlayerBank *p, u32 v) { p->donationLevel = v; }

extern "C" void PlayerBank_PayInterest(s32 n) {
    PlayerData *s = PlayerData_GetCurrent();
    PlayerBank *o = s->getBankAccount();
    if (MenuCtrl_IsClockMovedForward() == 0) {
        if (n > 0) {
            s32 m = PlayerBank_GetBalance(o);
            n = m / 2000 * n * 10;
            if (n > 99999) {
                n = 99999;
            }
            if (n != 0) {
                if (m != 999999999) {
                    s32 t = m + n;
                    if (t > 999999999) {
                        t = 999999999;
                    }
                    PlayerBank_SetBalance(o, t);
                    Letter e;
                    u8 ch = 0;
                    MsgString25 str;
                    String_FormatNumber(&str, n, 10, 1, 0, 0);
                    MailText_SetSlot(1, &str);
                    Letter_ComposeFromMail((LetterView *)&e, &ch, "sp_npc_pelican", &data_020e1e08, &data_020e1e04, s->getPlayerId());
                    LetterDelivery_PutInAddresseeMailbox(&e);
                }
            }
        }
    }
}

extern "C" void PlayerBank_SendMilestoneLetter(s32 n) {
    PlayerData *s = PlayerData_GetCurrent();
    PlayerBank *o = s->getBankAccount();
    if (n > 0) {
        s32 m = PlayerBank_GetBalance(o);
        if (m >= 1000000) {
            u32 col = 0x37dc;
            s32 k = 0;
            if (m == 999999999) {
                k = 4;
                col = 0x3874;
            } else if (m >= 500000000) {
                k = 3;
                col = 0x4a44;
            } else if (m >= 100000000) {
                k = 2;
                col = 0x4a40;
            } else if (m >= 10000000) {
                k = 1;
                col = 0x3700;
            }
            s32 bit = k + 0x11;
            if (s->testFlag(bit) == 0) {
                u8 ch;
                ch = k + 0x15;
                Letter e;
                MsgString9C town;
                TownId_GetNameString(&gSaveTownId, &town);
                MailText_SetSlot(0, &town);
                Letter_ComposeFromMail((LetterView *)&e, &ch, "sp_npc_pelican", &data_020e1e00, &data_020e1dfc, s->getPlayerId());
                ((LetterView *)(&e))->setPresent(col, 1);
                if (LetterDelivery_PutInAddresseeMailbox(&e)) {
                    s->setFlag(bit);
                }
            }
        }
    }
}

extern "C" void PlayerBank_SendDonationLetter(s32 n) {
    PlayerData *s = PlayerData_GetCurrent();
    PlayerBank *o = s->getBankAccount();
    if (n > 0) {
        if (s->testFlag(0x16)) {
            s32 id = PlayerBank_GetDonationLevel(o);
            Letter e;
            u8 ch;
            ch = id;
            u32 v;
            Letter_ComposeFromMail((LetterView *)&e, &ch, "sp_npc_pelican", &data_020e1df8, &data_020e1e0c, s->getPlayerId());
            v = 0xfff1;
            if (id > 13) goto hi;
            if (id >= 13) goto c13;
            switch (id) {
            case 0: goto done;
            case 1: goto c1;
            case 4: goto c4;
            case 7: goto c7;
            case 10: goto c10;
            }
            goto done;
        hi:
            if (id > 16) goto hi2;
            switch (id) {
            case 16: goto c16;
            }
            goto done;
        hi2:
            switch (id) {
            case 20: goto c20;
            }
            goto done;
        c1: v = 0x13fe; goto done;
        c4: v = 0x13ff; goto done;
        c7: v = 0x1400; goto done;
        c10: v = 0x1401; goto done;
        c13: v = 0x1402; goto done;
        c16: v = 0x1403; goto done;
        c20: v = 0x1404;
        done:
            if (v != 0xfff1) {
                ((LetterView *)(&e))->setPresent(v, 1);
            }
            if (LetterDelivery_PutInAddresseeMailbox(&e)) {
                s->clearFlag(0x16);
            }
        }
    }
}

