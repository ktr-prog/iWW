#ifndef HOST_LABELS_H
#define HOST_LABELS_H

#ifdef __cplusplus
extern "C" {
#endif
extern char *const gHostLabel_data_02135e5d;
extern char *const gHostLabel_data_02135e5e;
extern char *const gHostLabel_data_02135e5f;
extern char *const gHostLabel_data_02136744;
extern char *const gHostLabel_data_02136f44;
extern char *const gHostLabel_data_02138f44;
extern char *const gHostLabel_data_02139f56;
extern char *const gHostLabel_data_02139f58;
extern char *const gHostLabel_data_0213bd5c;
extern char *const gHostLabel_data_0213bdc4;
extern char *const gHostLabel_data_0213bdcc;
extern char *const gHostLabel_data_0213bdf0;
extern char *const gHostLabel_data_0213bdfc;
extern char *const gHostLabel_data_0213be0c;
extern char *const gHostLabel_data_0213be14;
extern char *const gHostLabel_data_0213be38;
extern char *const gHostLabel_data_0213be44;
extern char *const gHostLabel_data_0213bf28;
extern char *const gHostLabel_data_021be810;
extern char *const gHostLabel_data_021e5890;
extern char *const gHostLabel_data_021e58a6;
extern char *const gHostLabel_data_021e58a7;
extern char *const gHostLabel_data_021e7f8c;
extern char *const gHostLabel_data_021e87d8;
extern char *const gHostLabel_data_021e935c;
extern char *const gHostLabel_data_021eb98c;
extern char *const gHostLabel_data_021ec31c;
extern char *const gHostLabel_data_021eceac;
extern char *const gHostLabel_data_021ecfa8;
extern char *const gHostLabel_data_021ed0a0;
extern char *const gHostLabel_data_021ed104;
extern char *const gHostLabel_data_021ed150;
extern char *const gHostLabel_data_021ed170;
extern char *const gHostLabel_data_021ed174;
extern char *const gHostLabel_data_021ed1b0;
extern char *const gHostLabel_data_021ed20c;
extern char *const gHostLabel_data_021ed284;
extern char *const gHostLabel_data_021ed29c;
extern char *const gHostLabel_data_021ed2b0;
extern char *const gHostLabel_data_021ed2c0;
extern char *const gHostLabel_data_021ed2d4;
extern char *const gHostLabel_data_021ed2e6;
extern char *const gHostLabel_data_021ed304;
extern char *const gHostLabel_data_021ed30c;
extern char *const gHostLabel_data_021f5be0;
extern char *const gHostLabel_data_021f6ac4;
extern char *const gHostLabel_data_021fcbda;
extern char *const gHostLabel_data_021fcbdc;
extern char *const gHostLabel_data_021fcbde;
extern char *const gHostLabel_data_021fcbe0;
extern char *const gHostLabel_data_021fcbe2;
extern char *const gHostLabel_data_021fcbe4;
extern char *const gHostLabel_data_021fcbe6;
extern char *const gHostLabel_data_021fcbe8;
extern char *const gHostLabel_data_021fcbea;
extern char *const gHostLabel_data_021fcbec;
extern char *const gHostLabel_data_021fcbee;
extern char *const gHostLabel_data_021fcbf0;
extern char *const gHostLabel_data_021feb0c;
extern char *const gHostLabel_data_02200324;
extern char *const gHostLabel_data_027e0088;
extern char *const gHostLabel_data_027e00d0;
extern char *const gHostLabel_data_027e0114;
extern char *const gHostLabel_data_027e0148;
extern char *const gHostLabel_data_027e0170;
extern char *const gHostLabel_data_027e0184;
extern char *const gHostLabel_data_027e01a8;
extern char *const gHostLabel_data_027e01c8;
extern char *const gHostLabel_data_027e01f8;
extern char *const gHostLabel_data_027e0228;
extern char *const gHostLabel_data_027e02c8;
extern char *const gHostLabel_gContestRecord;
extern char *const gHostLabel_gSaveAbleSistersPatterns;
extern char *const gHostLabel_gSaveBlancaFace;
extern char *const gHostLabel_gSaveEventWeekSlots;
extern char *const gHostLabel_gSaveFooter;
extern char *const gHostLabel_gSaveHappyRoomDate;
extern char *const gHostLabel_gSaveHouse;
extern char *const gHostLabel_gSaveLostAndFound;
extern char *const gHostLabel_gSavePlayers;
extern char *const gHostLabel_gSaveRecycleBin;
extern char *const gHostLabel_gSaveTownEventDate;
extern char *const gHostLabel_gSaveTownEvents;
extern char *const gHostLabel_gSaveTownFlag;
extern char *const gHostLabel_gSaveTownId;
extern char *const gHostLabel_gSaveTownMap;
extern char *const gHostLabel_gSaveTownState;
extern char *const gHostLabel_gSaveTownTune;
extern char *const gHostLabel_gSaveVillagers;
extern char *const gHostLabel_gSndBgmHandle;
extern char *const gHostLabel_p__sinit_020c2cd0;
#ifdef __cplusplus
}
#define HOST_LABEL_DEFINE(name, expr) extern "C" char *const gHostLabel_##name = (expr)
#else
#define HOST_LABEL_DEFINE(name, expr) char *const gHostLabel_##name = (expr)
#endif

#define HOST_LABEL(ptrtype, name) (*(ptrtype)gHostLabel_##name)

#endif
