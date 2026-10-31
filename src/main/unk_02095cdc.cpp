#include "player/PlayerId.h"
#include "host_labels.h"
#include "types.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "town/TownBlockMap.h"
#include "game/Unk_02095774_Ent.h"
#include "save/MotherLetterState.h"
#include "item/Letter.h"
#include "item/LetterView.h"
#include "item/PlayerMailbox.h"
#include "item/LetterStorage.h"
#include "item/LetterOutbox.h"
#include "item/FutureLetter.h"
#include "item/BottleLetterRecord.h"
#include "item/ItemPickSpec.h"
#include "player/PlayerData.h"
#include "save/TownExchangeRecord.h"
#include "sys/ClockDateTime.h"
#include "item/MotherLetterDate.h"
#include "npc/VillagerId.h"
#include "proto/main/unk_020030d8.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_020637e4.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f4f0.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_0208eeac.h"
#include "proto/main/unk_0208f0b0.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02096c10.h"
#include "proto/main/unk_02097110.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_0204cc1c.h"









struct ZeroedDateTimeWords {
    union {
        ClockDateTime dt;
        u32 words[2];
    };
    ZeroedDateTimeWords() { words[0] = 0; words[1] = 0; }
};
struct ZeroedDateTimeWords2 : ZeroedDateTimeWords {
    ZeroedDateTimeWords2() { words[0] = 0; words[1] = 0; }
};

static inline LetterView *LetterFields(Letter *l) { return (LetterView *)l; }









inline BOOL Unk_0209579c_IsTwo(u8 v) {
    if (v == 2) return TRUE;
    return FALSE;
}

inline u16 Unk_02095f38_F(u32 v) {
    if (v < 5) return (u16)(v + 0x1518);
    return 0x1518;
}
extern CommManager *gCommManager;
extern u32 sPlayerPosSyncVars[];
extern u32 sPlayerAngleSyncVars[];
extern u32 sPlayerStateSyncVars[];
extern const u8 sThrownBottleReturnOdds[];
#define data_021e7f8c HOST_LABEL(TownExchangeRecord *, data_021e7f8c)
#define data_021eceac HOST_LABEL(BottleLetterRecord *, data_021eceac)
extern u8 gU8None[];
#define data_021ed150 HOST_LABEL(SaveTownStateView *, data_021ed150)
#define data_021ecfa8 HOST_LABEL(u8 (*)[], data_021ecfa8)
extern const u32 sSeasonLetterPaperCounts[];
extern const u8 *sSeasonLetterPapers[];
extern const u32 sPersonalityLetterPaperCounts[];
extern const u8 *sPersonalityLetterPapers[];
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
#define data_021eb98c HOST_LABEL(LetterOutbox *, data_021eb98c)
#define data_021e935c HOST_LABEL(PlayerMailbox (*)[], data_021e935c)

extern "C" {
ProcBase *func_02002d3c(s32 a, s32 b);
void *Town_GetUpdater();
s32 Town_WashUpBottle(void *p);
s32 SaveVillagers_DeliverLetter(void *self, void *p);
s32 SaveVillagers_FindIndex(u8 *base, VillagerId *p);
BOOL SaveVillagers_IsValidIndex(u32 n);
s32 Date_GetNthWeekdayDay(u32 a, u32 b, s32 c, s32 d);
void DateTime_AddDays(ClockDateTime *p, s32 n);
s32 DateTime_Compare(ClockDateTime *a, ClockDateTime *b, u32 mask);
void Clock_GetDateTime(ClockDateTime *p);
void MI_CpuCopy8(const void *, void *, u32);
}

inline BOOL Unk_02095dcc_R(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

extern const u8 sAutumnLetterPapers[0x4];
extern const u8 sWinterLetterPapers[0x4];
extern const u8 sSpringLetterPapers[0x4];
extern const u8 sSummerLetterPapers[0x4];
extern const u8 sThrownBottleReturnOdds[0x8];
extern const u32 sSeasonLetterPaperCounts[4];
extern const u32 sPersonalityLetterPaperCounts[6];
extern const u8 sLetterPapersPersonality1[0x1c];
extern const u8 sLetterPapersPersonality2[0x20];
extern const u8 sLetterPapersPersonality4[0x24];
extern const u8 sLetterPapersPersonality0[0x24];
extern const u8 sLetterPapersPersonality3[0x24];
extern const u8 sLetterPapersPersonality5[0x24];

extern "C" s32 LetterDelivery_DeliverOutgoing(void) {
    Letter *base = data_021eb98c.getLetter(0);
    s32 n = LetterList_Compact(base, 10);
    s32 i;
    volatile s32 flag = 0;
    volatile s32 zero = 0;
    for (i = 0; i < n; i++) {
        Letter *p = &base[i];
        if (LetterFields(p)->getState() != 0) {
            s32 idx = LetterDelivery_FindAddresseePlayer(p);
            if (idx == -2) {
                Letter_Clear(LetterFields(p));
            } else if (idx != ~zero) {
                if (LetterDelivery_PutInMailbox(p, idx, flag) != 0) {
                    Letter_Clear(LetterFields(p));
                }
            } else {
                if (LetterDelivery_FindAddresseeVillager(p) < 0) {
                    Letter_Clear(LetterFields(p));
                } else {
                    LetterDelivery_SendToVillager(p);
                    Letter_Clear(LetterFields(p));
                }
            }
        }
    }
    return LetterList_Compact(base, 10);
}

extern "C" BOOL LetterDelivery_IsMailboxFull(s32 idx) {
    if (idx == -1) {
        idx = PlayerData_GetCurrent()->getIndex();
    }
    Letter *p = data_021e935c[idx].getLetter(0);
    s32 i;
    for (i = 0; i < 10; p++, i++) {
        if (LetterFields(p)->getState() == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

extern "C" BOOL LetterDelivery_PutInMailbox(Letter *e, s32 idx, u32 flag) {
    Letter *p = data_021e935c[idx].getLetter(0);
    s32 i;
    for (i = 0; i < 10; p++, i++) {
        if (LetterFields(p)->getState() == 0) {
            Letter_Copy(LetterFields(p), LetterFields(e));
            if (flag) {
                Letter_MarkSent(LetterFields(p));
            }
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" BOOL LetterDelivery_PutInAddresseeMailbox(Letter *e) {
    s32 i = LetterDelivery_FindAddresseePlayer(e);
    if (i < 0) {
        return FALSE;
    }
    return LetterDelivery_PutInMailbox(e, i, 0);
}

extern "C" void LetterDelivery_SendToVillager(Letter *e) {
    SaveVillagers_DeliverLetter(gSaveVillagers, e);
}

extern "C" BOOL LetterDelivery_QueueOutgoing(Letter *e, BOOL flag) {
    s32 i;
    Letter *p = data_021eb98c.getLetter(0);
    for (i = 0; i < 10; p++, i++) {
        if (LetterFields(p)->getState() == 0) {
            Letter_Copy(LetterFields(p), LetterFields(e));
            if (flag) {
                Letter_MarkSent(LetterFields(p));
            }
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" BOOL LetterDelivery_HasKnownAddressee(Letter *e) {
    s32 r = LetterDelivery_FindAddresseePlayer(e);
    if (r == -2) {
        return FALSE;
    }
    if (r == -1) {
        r = LetterDelivery_FindAddresseeVillager(e);
        if (r == -2) {
            return FALSE;
        }
        if (r == -1) {
            return FALSE;
        }
    }
    return TRUE;
}

extern "C" s32 LetterDelivery_FindAddresseePlayer(Letter *letter) {
    LetterParty *r4 = Letter_GetRecipientPlayer(LetterFields(letter));
    s32 res;
    if (r4 == 0) return -1;
    PlayerId tmp((void *)NULL);
    tmp.copyFrom((PlayerId *)r4);
    res = PlayerDataArray_FindById(gSavePlayers, (u16 *)&tmp);
    if (PlayerData_IsResidentIndex(res)) {
        new (&tmp) PlayerId();
        return res;
    }
    new (&tmp) PlayerId();
    return -2;
}

extern "C" s32 LetterDelivery_FindAddresseeVillager(Letter *letter) {
    u8 *r5 = gSaveVillagers;
    LetterParty *r4 = Letter_GetRecipientVillager(LetterFields(letter));
    VillagerId tmp;
    s32 res;
    if (r4 == 0) return -1;
    VillagerId_Construct(&tmp);
    VillagerId_CopyFrom(&tmp, (VillagerId *)r4);
    res = SaveVillagers_FindIndex(r5, &tmp);
    if (SaveVillagers_IsValidIndex(res)) {
        VillagerId_Destruct(&tmp);
        return res;
    }
    VillagerId_Destruct(&tmp);
    return -2;
}

extern "C" s32 LetterList_Compact(Letter *base, s32 n) {
    s32 i = 0, j = i;
    for (; i < n; i++) {
        Letter *e = &base[i];
        if (LetterFields(e)->getState()) {
            if (i != j) {
                Letter_Copy(LetterFields(&base[j]), LetterFields(e));
                Letter_Clear(LetterFields(e));
            }
            j++;
        }
    }
    return j;
}

extern "C" s32 LetterList_CountUsed(Letter *base, s32 n) {
    s32 i, cnt;
    cnt = 0;
    i = cnt;
    for (; i < n; i++) {
        if (LetterFields(&base[i])->getState()) cnt++;
    }
    return cnt;
}

extern "C" void LetterDelivery_PostOfficeClosedNop(void) {}

extern "C" s32 LetterDelivery_HasFutureLetter(PlayerData *p) {
    if (p == 0) p = PlayerData_GetCurrent();
    if (((LetterView *)FutureLetter_GetLetter(PlayerData_GetFutureLetter(p)))->getState() != 0) return 1;
    return 0;
}

extern "C" s32 LetterDelivery_HasFreeOutgoingSlot(void) {
    s32 i;
    Letter *p = data_021eb98c.getLetter(0);
    for (i = 0; i < 10; p++, i++) {
        if (LetterFields(p)->getState() == 0) return 1;
    }
    return 0;
}

extern "C" void LetterDelivery_Update(void) {
    u8 *r5;
    if ((gCommManager)->isOnline()) return;
    LetterOutbox *const g = &data_021eb98c;
    r5 = g->getLastDeliveryTime();
    ClockDateTimeWords A;
    ClockDateTimeWords Y, Z;
    s32 z0, z1, z2;
    s32 i;
    u8 *r6;
    PlayerData *s0;
    Letter *s4;
    A.words[0] = 0; A.words[1] = 0;
    Clock_GetDateTime(&A.dt);
    Y.words[0] = 0; Y.words[1] = 0; Z.words[0] = 0; Z.words[1] = 0;
    if (g->testFlag(1)) {
        Y.words[0] = 0; Y.words[1] = 0;
        Y.dt.year = r5[2];
        Y.dt.month = r5[1];
        Y.dt.day = r5[0];
        MI_CpuCopy8(&Y, &Z, 8);
        if (r5[3] < 9) {
            r5[3] = 9;
            Z.dt.hour = 0x11;
        } else if (r5[3] < 0x11) {
            r5[3] = 0x11;
            Z.dt.hour = 9;
            DateTime_AddDays(&Z.dt, 1);
        } else {
            r5[3] = 9;
            DateTime_AddDays(&Y.dt, 1);
            Z.dt.hour = 0x11;
            DateTime_AddDays(&Z.dt, 1);
        }
        Y.dt.hour = r5[3];
        if (DateTime_Compare(&A.dt, &Y.dt, 0x3c) != -1) {
            LetterDelivery_DeliverOutgoing();
            if (DateTime_Compare(&A.dt, &Z.dt, 0x3c) != -1) LetterDelivery_DeliverOutgoing();
        }
    } else {
        g->setFlag(1);
    }
    z2 = 0; z1 = 0; z0 = 0;
    for (i = 0; i < 4; i++) {
        if (PlayerDataArray_IsUsed(gSavePlayers, i)) {
            s0 = (PlayerData *)PlayerData_GetResident(gSavePlayers, i);
            r6 = ((FutureLetter *)PlayerData_GetFutureLetter(s0))->getDeliveryDate();
            s4 = (Letter *)FutureLetter_GetLetter(PlayerData_GetFutureLetter(s0));
            if (LetterFields(s4)->getState()) {
                Y.words[0] = z0; Y.words[1] = z0;
                Y.dt.year = r6[2];
                Y.dt.month = r6[1];
                Y.dt.day = r6[0];
                Y.dt.hour = 9;
                if (DateTime_Compare(&A.dt, &Y.dt, 0x3c) != ~z2) {
                    if (LetterDelivery_PutInMailbox(s4, i, z1)) ((FutureLetter *)PlayerData_GetFutureLetter(s0))->clearFutureLetter();
                }
            }
        }
    }
    r5[2] = A.dt.year;
    r5[1] = A.dt.month;
    r5[0] = A.dt.day;
    r5[3] = A.dt.hour;
}

extern "C" u8 LetterPaper_PickRandom(u32 a, u32 b) {
    if (Random_GlobalBelow(10) < 3) return LetterPaper_PickForMonth(b);
    return LetterPaper_PickForPersonality(a);
}

extern "C" u8 LetterPaper_PickForPersonality(u32 i) {
    return sPersonalityLetterPapers[i][Random_GlobalBelow(sPersonalityLetterPaperCounts[i])];
}

extern "C" u8 LetterPaper_PickForMonth(u32 x) {
    s32 i;
    if (x <= 2 || x == 12) i = 3;
    else if (x <= 5) i = 0;
    else if (x <= 8) i = 1;
    else i = 2;
    return sSeasonLetterPapers[i][Random_GlobalBelow(sSeasonLetterPaperCounts[i])];
}

extern "C" void LetterDelivery_DeliverReceivedLetter(void) {
    void *r6 = data_021ecfa8;
    if (ReceivedLetter_HasLetter(r6) != 0) {
        if (LetterDelivery_IsMailboxFull(-1) == 0) {
            Letter *r5 = (Letter *)ReceivedLetter_GetLetter(r6);
            s32 r4 = PlayerData_GetCurrent()->getIndex();
            Letter_SetRecipientResident(LetterFields(r5), r4);
            Letter_MarkReceived(LetterFields(r5));
            if (LetterDelivery_PutInMailbox(r5, r4, 0) != 0) ReceivedLetter_Clear(r6);
        }
    }
}

extern "C" void MotherLetter_OnNewDay(Unk_02096354_Arg *p, s32 n) {
    PlayerData *r6 = PlayerData_GetCurrent();
    MotherLetterState *r4;
    if (r6 == 0) return;
    if (n < 1) return;
    if (LetterDelivery_HasFreeOutgoingSlot() == 0) {
        if (LetterDelivery_IsMailboxFull(-1) == 1) return;
    }
    r4 = (MotherLetterState *)PlayerData_GetMotherLetterState(r6);
    MotherLetter_ResetOtherMonths((u8)p->month);
    if (r4->checkLastDate((s32 *)p) != 0) return;
    if (MotherLetter_TrySendBirthday(p) != 0) {
        r4->setBirthdayLetterYear((u8)p->year);
        r4->setLastDate((s32 *)p);
        return;
    }
    if (MotherLetter_TrySendHoliday(p) != 0) {
        r4->setLastDate((s32 *)p);
        return;
    }
    if (Random_GlobalBelow(10) < 2) {
        if (MotherLetter_TrySendRandom(p) != 0) {
            r4->setLastDate((s32 *)p);
            return;
        }
    }
    r4->setLastDate((s32 *)p);
}

extern "C" s32 MotherLetter_TrySendBirthday(Unk_02096354_Arg *p) {
    PlayerData *r5 = PlayerData_GetCurrent();
    MotherLetterState *r6 = (MotherLetterState *)PlayerData_GetMotherLetterState(r5);
    u8 *q = r5->getBirthday();
    if (*(u16 *)q == 0) return 0;
    if (p->year == r6->getBirthdayLetterYear()) return 0;
    s32 r;
    ZeroedDateTimeWords2 A;
    A.dt.year = p->year;
    A.dt.month = q[1];
    A.dt.day = q[0];
    ZeroedDateTimeWords2 B;
    B.dt.year = p->year;
    B.dt.month = p->month;
    B.dt.day = p->day;
    ZeroedDateTimeWords C;
    MI_CpuCopy8(&A, &C, 8);
    DateTime_AddDays(&C.dt, 7);
    r = 0;
    if (C.dt.year != A.dt.year) {
        C.dt.year = A.dt.year;
        if (DateTime_Compare(&B.dt, &C.dt, 0x38) == 1) {
            if (DateTime_Compare(&B.dt, &A.dt, 0x38) == -1) goto end;
        }
        r = 1;
    } else {
        if (DateTime_Compare(&B.dt, &C.dt, 0x38) == 1) goto end;
        if (DateTime_Compare(&B.dt, &A.dt, 0x38) == -1) goto end;
        r = 1;
    }
end:
    if (r) r = MotherLetter_SendRandomUnsent(0x20, 2, (u8)p->month, 1);
    return r;
}

extern "C" s32 MotherLetter_TrySendHoliday(Unk_02096354_Arg *p) {
    s32 c = p->day;
    s32 b = p->month;
    if (b == c) return MotherLetter_SendRandomUnsent(c * 2 - 2, 2, (u8)b, 1);
    if (b == 4 && c == 1) return MotherLetter_SendRandomUnsent(0x1c, 2, (u8)b, 1);
    if (b == 12 && c == 0x18) return MotherLetter_SendRandomUnsent(0x1e, 2, (u8)b, 1);
    if (b == 6) {
        if (p->day == Date_GetNthWeekdayDay((u8)p->year, (u8)b, 0, 3))
            return MotherLetter_SendRandomUnsent(0x1a, 2, (u8)p->month, 1);
    }
    if (p->month == 5) {
        if (p->day == Date_GetNthWeekdayDay((u8)p->year, (u8)p->month, 0, 2))
            return MotherLetter_SendRandomUnsent(0x18, 2, (u8)p->month, 1);
    }
    return 0;
}

extern "C" s32 MotherLetter_TrySendRandom(Unk_02096354_Arg *p) {
    s32 r6 = MotherLetter_GetMonthFirst((u8)p->month);
    s32 r7 = MotherLetter_GetMonthCount((u8)p->month);
    s32 r4 = MotherLetter_CountUnsent(r6, r7);
    if (r4 == r7) {
        return MotherLetter_SendRandomUnsent(r6, r7, (u8)p->month, 0);
    }
    if (Random_GlobalBelow(r4 + MotherLetter_CountUnsent(0x22, 0x38)) < r4) {
        return MotherLetter_SendRandomUnsent(r6, r7, (u8)p->month, 0);
    }
    return MotherLetter_SendRandomUnsent(0x22, 0x38, (u8)p->month, 1);
}

extern "C" u32 MotherLetter_GetMonthFirst(u8 v) { return sMotherMonthLetterFirst[v - 1] + 0x5a; }

extern "C" u8 MotherLetter_GetMonthCount(u8 v) { return sMotherMonthLetterCount[v - 1]; }

extern "C" void MotherLetter_ResetOtherMonths(s32 x) {
    s32 i;
    for (i = 1; i <= 12; i++) {
        if (i != x) {
            s32 t = MotherLetter_GetMonthFirst((u8)i);
            MotherLetter_ClearSent(t, MotherLetter_GetMonthCount((u8)i));
        }
    }
}

extern "C" s32 MotherLetter_CountUnsent(s32 a, s32 n) {
    MotherLetterState *g = (MotherLetterState *)PlayerData_GetMotherLetterState(PlayerData_GetCurrent());
    s32 cnt = 0, i = cnt;
    for (; i < n; a++, i++) {
        if (g->isSent(a) == 0) cnt++;
    }
    return cnt;
}

extern "C" s32 MotherLetter_GetNthUnsent(s32 a, s32 n, s32 k) {
    MotherLetterState *g = (MotherLetterState *)PlayerData_GetMotherLetterState(PlayerData_GetCurrent());
    s32 cnt = 0, idx = a, i = cnt;
    for (; i < n; idx++, i++) {
        if (g->isSent(idx) == 0) {
            if (cnt == k) return idx;
            cnt++;
        }
    }
    return a;
}

extern "C" void MotherLetter_ClearSent(s32 a, s32 n) {
    MotherLetterState *g = (MotherLetterState *)PlayerData_GetMotherLetterState(PlayerData_GetCurrent());
    s32 i;
    for (i = 0; i < n; a++, i++) g->clearSent(a);
}

extern "C" s32 MotherLetter_SendRandomUnsent(s32 a, s32 b, s32 c, s32 d) {
    MotherLetterState *g;
    s32 v8, vc;
    s32 r7;
    g = (MotherLetterState *)PlayerData_GetMotherLetterState(PlayerData_GetCurrent());
    r7 = MotherLetter_CountUnsent(a, b);
    if (r7 == 0) {
        if (d == 0) return 0;
        r7 = b;
        MotherLetter_ClearSent(a, b);
        d = 0;
    }
    v8 = MotherLetter_GetNthUnsent(a, b, Random_GlobalBelow(r7));
    vc = MotherLetter_Send(v8, c);
    if (vc != 0) {
        if (r7 == 1 && d == 1) MotherLetter_ClearSent(a, b);
        else g->setSent(v8);
    }
    return vc;
}

extern "C" s32 MotherLetter_Send(s32 a, s32 b) {
    u8 rec[3];
    Letter letter;
    PlayerId *r4;
    Letter_Clear(LetterFields(&letter));
    r4 = PlayerData_GetCurrent()->getPlayerId();
    rec[0] = gU8None[0];
    rec[0] = MotherLetter_GetMsgIndex(a);
    rec[1] = 1;
    if (a == 0x1a) rec[1] = 0x12;
    rec[2] = LetterPaper_PickRandom(3, b);
    Letter_ComposeFromMail(LetterFields(&letter), rec, MotherLetter_GetFileName(a), rec + 1, rec + 2, r4);
    u32 t = MotherLetter_GetPresent(a);
    if (t != 0xfff1) LetterFields(&letter)->setPresent(t, 1);
    if (LetterDelivery_PutInAddresseeMailbox(&letter)) {
        return 1;
    }
    if (LetterDelivery_QueueOutgoing(&letter, 0)) {
        return 1;
    }
    return 0;
}

extern "C" const char *MotherLetter_GetFileName(s32 a) {
    if (a >= 0 && a < 0x22) return "mother_day";
    if (a >= 0x22 && a < 0x5a) return "mother_always";
    return "mother_season";
}

extern "C" u16 MotherLetter_GetPresent(s32 code) {
    u16 buf[4];
    buf[0] = 0xfff1;
    switch (code) {
    case 0x23:
    case 0x32:
    case 0x5f:
    case 0x73:
        {
            ItemPickSpec o1;
            o1.set(2, 0);
            ItemPick_One(&buf[1], &o1, 0, 0, 1, 1, 0);
            buf[0] = buf[1];
        }
        return buf[0];
    case 0x4a:
        ItemPick_FromRange(&buf[2], 0x1380, 0x20, 0, 0, 0, 1, 10, 0, 1);
        buf[0] = buf[2];
        return buf[0];
    case 0x1e:
    case 0x1f:
        {
            ItemPickSpec o2;
            o2.set(0, 0);
            ItemPick_One(&buf[3], &o2, 0, 0, 1, 1, 0);
            buf[0] = buf[3];
        }
        return buf[0];
    case 0x25:
    case 0x37:
    case 0x38:
    case 0x51: {
        u16 r4 = Unk_02095f38_F(data_021ed150.nativeFruit);
        s32 n = Random_GlobalBelow(4);
        u32 j;
        for (j = 0; j < 5; j++) {
            u16 k = Unk_02095f38_F(j);
            if (k == r4) continue;
            if (n > 0) {
                n--;
            } else {
                return k;
            }
        }
        return 0x1518;
    }
    case 0x2e:
        return 0x149b;
    case 0:
    case 1:
        return 0x14a4;
    case 0x6e:
    case 0x6f:
        return 0x1542;
    case 0x72:
        return 0x1518;
    case 0x48:
        return 0x3648;
    case 0x47:
        return 0x3420;
    }
    return 0xfff1;
}

extern "C" u8 MotherLetter_GetMsgIndex(s32 x) {
    if (x >= 0 && x < 0x22) return x;
    if (x >= 0x22 && x < 0x5a) return x - 0x22;
    return x - 0x5a;
}

extern "C" s32 BottleLetter_Open() {
    Letter *r5 = Inventory_GetEmptyLetter();
    if (r5 == NULL) return FALSE;
    Letter *o = (Letter *)BottleLetterRecord_GetLetter(&data_021eceac);
    if (!LetterFields(o)->getState()) {
        Letter_Clear(LetterFields(o));
        return TRUE;
    }
    PlayerData *t = PlayerData_GetCurrent();
    u16 buf = 0x1033;
    Catalog_SetItem(t->getCatalog(), &buf, 0, 1);
    Letter_Copy(LetterFields(r5), LetterFields(o));
    Letter_Clear(LetterFields(o));
    CommManager *g = gCommManager;
    if ((g)->isOnline() && g->myAid != 0) CommSub_Send(7, 0);
    return TRUE;
}

extern "C" s32 BottleLetter_CreateGameLetter(u8 *p) {
    Letter *o = (Letter *)BottleLetterRecord_GetLetter(&data_021eceac);
    if (LetterFields(o)->getState()) return FALSE;
    if (BottleLetter_PlaceBottle() == 0) return FALSE;
    Letter_ComposeBottleMail(LetterFields(o), p, "ev_bottle");
    return TRUE;
}

extern "C" s32 BottleLetter_PlaceBottle() {
    return Town_WashUpBottle(Town_GetUpdater());
}

extern "C" s32 BottleLetter_IsBottleInTown() {
    TownBlockMap *g = TownBlockMap_Get();
    s32 y, x, hx, hy;
    u16 *c;
    for (y = 0; y < g->unitsZ; y++) {
        x = 0;
        goto test0;
    loop0:
        hx = x >> 4;
        hy = y >> 4;
        c = BlockMap_GetItemPtr(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
        if (c) {
            if (Unk_02095dcc_R(c, 0x1520, 0x1520)) return TRUE;
        }
        x++;
        hy = y;
        y = hy;
    test0:
        if (x < g->unitsX) goto loop0;
    }
    return FALSE;
}

extern "C" void BottleLetter_OnNewDay(s32 a) {
    if (a > 0) {
        if (BottleLetter_IsBottleInTown() == 0) {
            BottleLetterRecord *const o = &data_021eceac;
            if (((LetterView *)BottleLetterRecord_GetLetter(o))->getState()) {
                BottleLetter_PlaceBottle();
            } else if (Random_GlobalBelow(10) == 7) {
                u8 v = gU8None[0];
                s32 r = o->pickUnusedMessage();
                v = r;
                if (BottleLetter_CreateGameLetter(&v)) o->setMessageUsed(r);
            }
        }
    }
}

extern "C" void BottleLetter_WashUpThrownBottle() {
    TownExchangeRecord *const o = &data_021e7f8c;
    if (o->isValid()) {
        Letter *r4 = (Letter *)TownExchange_GetLetter(o);
        if (LetterFields(r4)->getState()) {
            s32 t = o->getUnkFlag();
            switch (t) {
            case 0: {
                s32 u = o->getCounter();
                if (u == 0) return;
                if (u < 5) {
                    if (Random_GlobalBelow(sThrownBottleReturnOdds[u]) != 1) return;
                }
                break;
            }
            case 1:
                break;
            }
            o->resetCounter();
            Letter_MarkSent(LetterFields(r4));
            Letter_Copy((LetterView *)BottleLetterRecord_GetLetter(&data_021eceac), LetterFields(r4));
            Letter_Clear(LetterFields(r4));
            if (BottleLetter_IsBottleInTown() == 0) BottleLetter_PlaceBottle();
        }
    }
}

extern const u8 sWinterLetterPapers[0x4];
extern const s32 data_020d0428;
extern const u8 sSpringLetterPapers[0x4];
extern const u8 sAutumnLetterPapers[0x4];
extern const u8 sSummerLetterPapers[0x4];
extern const u8 sThrownBottleReturnOdds[0x8];
extern const u32 sSeasonLetterPaperCounts[4];
extern const u32 sPersonalityLetterPaperCounts[6];
extern const u8 sLetterPapersPersonality1[0x1c];
extern const u8 sLetterPapersPersonality2[0x20];
extern const u8 sLetterPapersPersonality4[0x24];
extern const u8 sLetterPapersPersonality0[0x24];
extern const u8 sLetterPapersPersonality3[0x24];
extern const u8 sLetterPapersPersonality5[0x24];
extern const u8 *sSeasonLetterPapers[4];
extern const u8 *sPersonalityLetterPapers[6];

u8 sMotherMonthLetterCount[0xc] = {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x08, 0x02, 0x02, 0x02, 0x02};

const s32 data_020d0428 = 0x2000;

const u8 sSpringLetterPapers[0x4] = {0x00, 0x05, 0x1b, 0x00};

const u8 sAutumnLetterPapers[0x4] = {0x07, 0x2d, 0x00, 0x00};

const u8 sSummerLetterPapers[0x4] = {0x00, 0x04, 0x1b, 0x2b};

const u8 sThrownBottleReturnOdds[0x8] = {0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00};

const u32 sSeasonLetterPaperCounts[4] = {0x3, 0x4, 0x2, 0x2};

const u8 sWinterLetterPapers[0x4] = {0x06, 0x0e, 0x00, 0x00};

const u32 sPersonalityLetterPaperCounts[6] = {0x22, 0x1b, 0x1d, 0x23, 0x22, 0x24};

const u8 sLetterPapersPersonality1[0x1c] = {0x08, 0x09, 0x0f, 0x13, 0x14, 0x15, 0x16, 0x21, 0x22, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2e, 0x30, 0x31, 0x32, 0x33, 0x34, 0x38, 0x39, 0x3b, 0x3c, 0x3f, 0x00};

const u8 sLetterPapersPersonality2[0x20] = {0x08, 0x09, 0x0f, 0x12, 0x13, 0x14, 0x15, 0x21, 0x22, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2e, 0x30, 0x31, 0x33, 0x34, 0x36, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x00, 0x00, 0x00};

const u8 sLetterPapersPersonality4[0x24] = {0x08, 0x09, 0x0a, 0x0b, 0x0d, 0x0f, 0x14, 0x17, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2c, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x3b, 0x3c, 0x3d, 0x3f, 0x00, 0x00};

const u8 sLetterPapersPersonality0[0x24] = {0x08, 0x09, 0x0b, 0x0d, 0x0f, 0x14, 0x15, 0x16, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2e, 0x30, 0x31, 0x32, 0x33, 0x34, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x00, 0x00};

const u8 sLetterPapersPersonality3[0x24] = {0x08, 0x09, 0x0a, 0x0b, 0x0d, 0x03, 0x0f, 0x14, 0x17, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2c, 0x2e, 0x2f, 0x30, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x3a, 0x3c, 0x3d, 0x3e, 0x3f, 0x00};

const u8 sLetterPapersPersonality5[0x24] = {0x08, 0x09, 0x0a, 0x0d, 0x03, 0x0f, 0x12, 0x13, 0x17, 0x20, 0x21, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2c, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x3a, 0x3c, 0x3d, 0x3e, 0x3f};

u8 sMotherMonthLetterFirst[0xc] = {0x1a, 0x1c, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x12, 0x14, 0x16, 0x18};

const u8 *sSeasonLetterPapers[4] = {sSpringLetterPapers, sSummerLetterPapers, sAutumnLetterPapers, sWinterLetterPapers};

const u8 *sPersonalityLetterPapers[6] = {sLetterPapersPersonality0, sLetterPapersPersonality1, sLetterPapersPersonality2, sLetterPapersPersonality3, sLetterPapersPersonality4, sLetterPapersPersonality5};
