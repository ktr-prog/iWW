#ifndef PLAYER_UNK_02007694_H
#define PLAYER_UNK_02007694_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/Mtx43.h"
#include "player/PlayerChangeClothesArgs.h"
#include "player/PlayerActor.h"

class PlayerActionRequest;

class Unk_02007694 : public PlayerActor {
public:
    void resetRotXForAction(u32 a);
    void stopMovementForAction(u32 a);
    void clearActionWork();
    void endAction(u32 a);
    u8 getActionDonePriority(u32 a);
    u8 getActionPriority(u32 a);
    void updateBgCheckWork(u32 a, u32 b);
    u8 keepsBgCheckWork(u32 a);
    void calcModelMatrixCurved();
    void mainAct92();
    void netAct92();
    void setupAct92();
    void mainAct91();
    void endAct91();
    void netAct91();
    void setupAct91();
    void mainWaitMenu();
    void waitMenuCheckEnd();
    void netWaitMenu(u32 a);
    void setupWaitMenu(PlayerActionRequest *p);
    u32 requestWaitMenu(u32 a, u32 b, u32 c);
    void mainLowerHeldUpItem();
    void lowerHeldUpItemCheckEnd();
    void netLowerHeldUpItem(u32 a);
    void setupLowerHeldUpItem();
    u32 requestLowerHeldUpItem(u32 a, u32 b);
    void mainHoldUpItem();
    void holdUpItemCheckEnd();
    void holdUpItemUpdate();
    void changeClothesSpin();
    void changeClothesApply();
    void changeClothesHat();
    void changeClothesFaceItem();
    void changeClothesShirt();
    void changeClothesEffects();
    void endChangeClothes(u32 a);
    void netChangeClothes(s16 a);
    void setupChangeClothes(PlayerActionRequest *item);
    u32 requestChangeClothes(u16 a, u32 b, u32 c, u32 d, s16 e);
    void mainAct05();
    void netAct05(u32 a);
    void setupAct05(PlayerActionRequest *item);
    u32 requestAct05(u16 a, u32 b, u32 c);
    void mainSkidTurn();
    void skidCheckEnd();
    void skidDecelerate();
    void endSkidTurn(u32 a);
    void netSkidTurn();
    void setupSkidTurn(PlayerActionRequest *item);
    u32 requestSkidTurn(u16 a, u32 b, u32 c);
    void mainWalk();
    void walkNetCheckEnd(u8 *p);
    void walkCheckEnd(s16 *p);

    void func_0200d3f0(u32 a);
    void func_0200cee0(u32 a);
    void func_0200cdfc(u32 a);
    void func_02211e04(u32 a);
    void func_022246bc(u32 a);
    void func_02224224(u32 a);
    void func_02223ca0(u32 a);
    void func_02223a70(u32 a);
    void func_022237fc(u32 a);
    void func_0200b9bc(u32 a);
    void func_022115bc(u32 a);
    void func_0200ad58(u32 a);
    void func_0200a450(u32 a);
    void func_02222d74(u32 a);
    void func_022223a8(u32 a);
    void func_02222280(u32 a);
    void func_02221fdc(u32 a);
    void func_02221d2c(u32 a);
    void func_02221ae4(u32 a);
    void func_0222189c(u32 a);
    void func_02221768(u32 a);
    void func_02221558(u32 a);
    void func_0222148c(u32 a);
    void func_0222113c(u32 a);
    void func_02210708(u32 a);
    void func_02210404(u32 a);
    void func_020095b8(u32 a);
    void func_0220fdac(u32 a);
    void func_0220f33c(u32 a);
    void func_0220efd8(u32 a);
    void func_0220ecb8(u32 a);
    void func_0220e970(u32 a);
    void func_0220e43c(u32 a);
    void func_0220c2dc(u32 a);
    void func_0220ba90(u32 a);
    void func_0220ab20(u32 a);
    void func_0220a5e4(u32 a);
    void func_02209ef4(u32 a);
    void func_02209284(u32 a);
    void func_02208fb0(u32 a);
    void func_02208904(u32 a);
    void func_02208358(u32 a);
    void func_0220714c(u32 a);
    void func_02206e94(u32 a);
    void func_0221fa98(u32 a);
    void func_02206710(u32 a);
    void func_0220646c(u32 a);
    void func_022061e0(u32 a);
    void func_0226a910(u32 a);
    void func_0226a80c(u32 a);
    void func_02010914();
    void func_0201071c();
    void func_020109c4();
    void func_0201065c();
    void func_0200ce98(u32 a, u32 b, u32 c);
    void func_020103b4(u32 a, u32 b, u32 c);
    void func_0200e870();
    void func_02010358(u32 a, u32 b, u32 c);
    u32 func_0200e248(PlayerActionRequest *p);
    void func_0200ec1c(u32 a);
    void func_0200ec30(u32 a);
    void func_0200ecdc(u32 a);
    BOOL func_0200f4c0(u32 a);
    void func_02002b84(Mtx43 *out);
    void func_02010a58(s16 *p);
    void func_020105a8(void *a, u8 *b);
    void func_02010564(void *a, u8 *b);
    void func_020109ac();
    void func_020102ec();
    void func_02010050(u16 *p);
    BOOL func_0201000c();
    BOOL func_0200fab8(u16 *a, u32 b, u32 c, u32 d);
    BOOL func_0200fd90(u16 *a);
    void func_0200eb58(u32 a, u32 b);
    BOOL func_0200ef08();
    void func_0200e8d0();
    void func_02010a34(s32 *p);
    void func_0200ca60();
    void func_0200c7dc();
    void func_0200c778();
    u8 func_0200c900();
    s32 func_0200d640();
    u16 func_0200d5fc();
    void func_0200ff08();
};

#endif
