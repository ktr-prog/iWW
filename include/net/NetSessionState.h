#ifndef NET_NETSESSIONSTATE_H
#define NET_NETSESSIONSTATE_H

#include "types.h"
#include "net/NetSessionParts.h"

class NetSessionState {
public:
    /* 0x00 */ NetSlotStatus slotStatus[4];
    /* 0x0c */ NetMoveRequest moveQueue[4];
    /* 0x2c */ NetMoveReady moveReady[4];
    /* 0x3c */ NetPendingStatus pendingStatus[4];
    /* 0x5c */ u8 becomesOwner;
    /* 0x60 */ s32 moveState;
    /* 0x64 */ s32 handoffSlot;
    /* 0x68 */ u8 memberAck[4];
    /* 0x6c */ s32 notifiedOwnerMover;
    /* 0x70 */ s32 stateSourceSlot;
    /* 0x74 */ s32 stateRequester;
    /* 0x78 */ s32 arrivingSlot;
    /* 0x7c */ u8 ownerAck;
    /* 0x80 */ s32 notifiedMemberMover;
    /* 0x84 */ u32 syncState[4];
    /* 0x94 */ s32 lastSyncSlot;
    /* 0x98 */ u16 syncMemberMask;
    /* 0x9c */ s32 syncPhase;
    /* 0xa0 */ s32 syncRequester;
    /* 0xa4 */ s32 syncKind;
    /* 0xa8 */ s32 memberSyncReply[4];
    /* 0xb8 */ s32 replyTimer;
    /* 0xbc */ u8 goDelay;
    /* 0xc0 */ s32 activeSyncKind;
    /* 0xc4 */ u8 ctrl07Received;

    NetSessionState();
    ~NetSessionState();
    u8 getCtrl07Received();
    void setCtrl07Received(u8 v);
    s32 getActiveSyncKind();
    void setActiveSyncKind(s32 v);
    u8 getGoDelay();
    void setGoDelay(u8 v);
    s32 getReplyTimer();
    void setReplyTimer(s32 v);
    void updateSyncClient();
    void resetAllMemberSyncReplies();
    void resetMemberSyncReply(s32 i);
    s32 getMemberSyncReply(s32 i);
    void setMemberSyncReply(s32 i, s32 v);
    void resetSyncKind();
    s32 getSyncKind();
    void setSyncKind(s32 v);
    void resetSyncRequester();
    s32 getSyncRequester();
    void setSyncRequester(s32 v);
    void resetSyncPhase();
    s32 getSyncPhase();
    void setSyncPhase(s32 v);
    u16 getSyncMemberMask();
    void setSyncMemberMask(u16 v);
    s32 getLastSyncSlot();
    void setLastSyncSlot(s32 v);
    void updateSyncHost();
    void resetSlot(s32 idx);
    void rejectSyncRequest(u32 a, u32 b);
    void resetSyncStates();
    u32 getSyncState(s32 i);
    void setSyncState(s32 i, u32 v);
    void notifyMovingMember();
    s32 getNotifiedMemberMover();
    void setNotifiedMemberMover(s32 v);
    u32 getOwnerAck();
    void setOwnerAck(u32 v);
    void updateArrivingSlot();
    s32 getArrivingSlot();
    void setArrivingSlot(s32 v);
    s32 getStateRequester();
    void setStateRequester(s32 v);
    s32 getStateSourceSlot();
    void setStateSourceSlot(s32 v);
    void notifyMovingOwner();
    s32 getNotifiedOwnerMover();
    void setNotifiedOwnerMover(s32 v);
    void clearMemberAcks();
    u32 getMemberAck(s32 i);
    void setMemberAck(s32 i, u32 v);
    s32 getHandoffSlot();
    void setHandoffSlot(s32 v);
    void updateMove();
    s32 getMoveState();
    void setMoveState(s32 v);
    u32 getBecomesOwner();
    void setBecomesOwner(u32 v);
    void flushStatusUpdates();
    void processMoveRequest(u32 *a, u32 *b);
    void sendMoveReady();
    void popMoveRequest();
    s32 peekMoveRequest();
    void startNextMove(u32 *a, u32 *b);
    void updateMoveQueue();
    void reset();
};

#endif
