#ifndef SAVE_SAVEMANAGER_H
#define SAVE_SAVEMANAGER_H

#include "types.h"
#include "sys/ProcBase.h"
#include "talk/TalkMsgRequest.h"
#include "game/NibblePair.h"
#include "save/TownCompress.h"


class Heap;

class SaveManager;

class SaveManagerTalk : public TalkMsgRequest {
public:
    SaveManagerTalk();
    virtual ~SaveManagerTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);

    void setOwner(SaveManager *v);

    /* 0x44 */ SaveManager *owner;
};

typedef void (SaveManager::*SaveManagerActFn)();

struct SaveManagerActEntry {
    SaveManagerActFn enter;
    SaveManagerActFn exec;
};

class SaveManager : public GameProc {
public:
    typedef s32 (SaveManager::*Fn)();

    SaveManager() {
        hostDateTime = 0;
        hostDateTimeHi = 0;
    }
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();

    s32 verifyStepChoose();
    s32 verifyStepSlot1();
    s32 verifyStepSlot0();
    s32 verifyStepReset();
    s32 verifySlotsStep();
    void setTransferReceived(u32 i, u8 v);
    u32 isTransferReceived(u32 i);
    void setTransferDest(u32 i, u8 v);
    u32 getTransferDest(u32 i);
    u32 func_020a148c();
    void restoreVillagerTransfer();
    void backupVillagerTransfer();
    BOOL func_020a15c8(u32 v);
    void func_020a15f8();
    void showSequence2Msg0B();
    void showSequence2Msg0A();
    void execAct1F();
    void enterAct1F();
    void execAct1E();
    void enterAct03();
    void execAct02();
    void enterAct02();
    void execAct01();
    void enterAct01();
    void execAct00();
    void enterAct00();
    void setState(s32 idx);
    void startTalk(const char *str, u8 flag);
    void enterAct14();
    void execAct14();
    void enterAct15();
    void execAct15();
    void enterAct16();
    void execAct16();
    void enterAct17();
    void execAct17();
    void enterAct18();
    void execAct18();
    void enterAct19();
    void execAct13();
    void enterAct13();
    void execAct12();
    void enterAct12();
    void execAct11();
    void enterAct11();
    void execAct10();
    void enterAct10();
    void execAct0F();
    void enterAct0F();
    void execAct0E();
    void enterAct0E();
    void execAct0D();
    void enterAct0D();
    void execAct0C();
    void enterAct0C();
    void execAct0B();
    void enterAct0B();
    void execAct0A();
    void enterAct0A();
    void execAct09();
    void enterAct09();
    void execAct08();
    void enterAct08();
    void execAct07();
    void enterAct07();
    void execAct06();
    void enterAct06();
    void execAct05();
    void enterAct05();
    void execAct04();
    void enterAct04();
    void execAct03();
    void enterAct1E();
    void execAct1D();
    void enterAct1D();
    void execAct1C();
    void enterAct1C();
    void execAct1B();
    void enterAct1B();
    void execAct1A();
    void enterAct1A();
    void execAct19();
    void runSendAct10(u8 *p, u32 base);
    BOOL allPeersSentAct10();
    void runGatherPeersInScene(u8 *p, u32 base, u32 x, u32 y);
    s32 runSyncedSaveClient(u8 *p, u32 base, u32 fail, u8 a5, u8 a6, u8 a7, u32 a8);
    typedef s32 (SaveManager::*SlotStepFn)(s32);
    s32 stepPrepare(s32 idx);
    s32 stepChecksum(s32 mode);
    s32 stepReadBack(s32 idx);
    s32 stepFindDirty(s32 idx);
    s32 stepWriteDirty(s32 idx);
    s32 stepCommit(s32 idx);
    s32 eraseSlotStep(s32 idx);
    s32 verifySlotStep(s32 idx);
    s32 loadSlotStep(s32 idx);
    BOOL memEqual(u8 *p, u8 *q, s32 n);
    s32 saveSlotStep(s32 arg);

    /* 0x50 */ s32 act;
    /* 0x54 */ SaveManagerTalk talk;
    /* 0x9c */ u8 slotStep;
    /* 0x9d */ u8 actStep;
    /* 0x9e */ u8 blockCursor;
    /* 0x9f */ u8 unk_9f;
    /* 0xa0 */ s16 dirtyFirstBlock;
    /* 0xa2 */ s16 unk_a2;
    /* 0xa4 */ s32 dirtySize;
    /* 0xa8 */ Heap *bufferHeap;
    /* 0xac */ u8 *workBuf;
    /* 0xb0 */ u8 *readBackBuf;
    /* 0xb4 */ void *saveDataCopy;
    /* 0xb8 */ void *playerDataCopy;
    /* 0xbc */ void *villagerTransferBackup;
    /* 0xc0 */ u8 *letterStorage;
    /* 0xc4 */ TownCompressBuffer *townCompressBuf;
    /* 0xc8 */ TownCompressThread *townCompressThread;
    /* 0xcc */ u16 hostWaitTimer;
    /* 0xce */ u16 memberMask;
    /* 0xd0 */ u16 hostMemberMask;
    /* 0xd2 */ u8 sessionJoined;
    /* 0xd3 */ u8 hostDataIndex;
    /* 0xd4 */ u8 sendChunk;
    /* 0xd5 */ u8 joinReady;
    /* 0xd6 */ u8 dateTimeReceived;
    /* 0xd7 */ u8 pad_d7;
    /* 0xd8 */ u32 hostDateTime;
    /* 0xdc */ u32 hostDateTimeHi;
    /* 0xe0 */ u8 joinDone;
    /* 0xe1 */ u8 ctrlAct12;
    /* 0xe2 */ u8 recvAct07;
    /* 0xe3 */ u8 recvAct04[4];
    /* 0xe7 */ u8 recvAct02[4];
    /* 0xeb */ u8 ctrlAct0E[4];
    /* 0xef */ u8 recvAct03;
    /* 0xf0 */ u8 recvAct06[4];
    /* 0xf4 */ u8 ctrlAct10[4];
    /* 0xf8 */ u8 ctrlAct11[4];
    /* 0xfc */ u8 ctrlAct14Aid;
    /* 0xfd */ u8 ctrlAct17;
    /* 0xfe */ u8 freePlayerSlot;
    /* 0xff */ u8 transferDests[4];
    /* 0x103 */ u8 transferReceived[4];
    /* 0x107 */ u8 noSaveData;
    /* 0x108 */ u8 unk_108;
    /* 0x109 */ NibblePair slotStatus;
    /* 0x10a */ NibblePair slotOrder;
};

extern "C" void *AxMail_Construct(void *p);
extern "C" void *AxMail_Destruct(void *p);
class AxMail {
public:
    AxMail() { AxMail_Construct(this); }
    ~AxMail() { AxMail_Destruct(this); }
    u32 unk_00[0x42];
};

extern "C" void AxBbsNotice_Construct(void);
extern "C" void AxBbsNotice_Destruct(void);
class AxBbsNotice {
public:
    AxBbsNotice() { AxBbsNotice_Construct(); }
    ~AxBbsNotice() { AxBbsNotice_Destruct(); }
    u8 unk_00[0xd2];
};

#endif
