#ifndef SAVE_MUSEUMDATA_H
#define SAVE_MUSEUMDATA_H

#include "types.h"

class MsgString;

class MuseumData {
public:
    s32 getDonationPercent();
    BOOL isFishComplete();
    BOOL isPaintingsComplete();
    BOOL isFossilsComplete();
    BOOL isInsectsComplete();
    BOOL isComplete();
    BOOL getDonorName(MsgString *x, u16 *id);
    void releasePlayerDonations(u32 v);
    void donate(u16 *id);
    BOOL sendCompletionLetters();
    void checkCompletionLetters();
    BOOL isDonated(u16 *id);
    u32 getDonationState(u16 *id);
    u32 getDonor(u16 *id);
    u8 *getEntry(u16 *id, s32 *out);
    void markFormerResident(u16 *id);
    void clearEntry(u16 *id);
    void clear();
    void destruct();
    MuseumData *construct();

    /* 0x00 */ u8 fossilDonors[0x1b];
    /* 0x1b */ u8 fishDonors[0x1d];
    /* 0x38 */ u8 insectDonors[0x1d];
    /* 0x55 */ u8 paintingDonors[0xb];
    /* 0x60 */ u8 completeDay;
    /* 0x61 */ u8 completeMonth;
    /* 0x62 */ u8 completeYear;
    /* 0x63 */ u8 unk_63;
};

#endif
