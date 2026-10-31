#include "types.h"
#include "host_labels.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "player/PlayerData.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/ov003/unk_ov003_02217510.h"













extern "C" {
#define data_021ed104 HOST_LABEL(u8 (*)[], data_021ed104)

s32 Item_GetNookShopLevel(void *p);
void Clock_GetDateTime(void *p);
void Clock_GetMinuteHour(void *p);
BOOL NookShop_IsClosedOn(void *p, void *q);
BOOL NookShop_IsReopenDueNow(void *p);
void *NookShop_GetRenovation(void *p);
BOOL NookShop_IsClosedTomorrow(void *p);
BOOL NookShop_IsClosedToday(void *p);
}


class ShopBuilding : public BuildingActor {
public:
    ShopBuilding();
    virtual ~ShopBuilding();

    virtual BOOL initBuilding();
    virtual void setupTalkMsg();
    virtual BOOL isOpen();
    virtual BOOL playsDoorMelody();
    virtual char *getArcPath();
    virtual char *getTexPath();
    virtual char *getLightTexPath();

    BOOL isClosedToday();

    /* 0x2b0 */ s32 shopLevel;
};

extern "C" ShopBuilding *ShopBuilding_Create() {
    return new ShopBuilding;
}

ShopBuilding::ShopBuilding() {
}

ShopBuilding::~ShopBuilding() {
}

BOOL ShopBuilding::initBuilding() {
    shopLevel = Item_GetNookShopLevel(&itemId);
    return TRUE;
}

char *ShopBuilding::getArcPath() {
    return BuildingActor::getArcPath();
}

char *ShopBuilding::getTexPath() {
    return BuildingActor::getTexPath();
}

char *ShopBuilding::getLightTexPath() {
    return BuildingActor::getLightTexPath();
}

void ShopBuilding::setupTalkMsg() {
    struct {
        s32 pad0, pad1;
        s32 a, b;
    } l;
    setFileName("obj_etc_closed");
    if (shopLevel == -1) {
        if (entryFlags.f1) {
            setFileName("obj_etc_error");
            msgIndex = 0;
        } else {
            msgIndex = 4;
        }
    } else {
        void *x = PlayerData_GetCurrent();
        if (GameStart_IsActive() || ((PlayerData *)(x))->testFlag(0x23)) {
            setFileName("sp_etc_sequence4");
            msgIndex = 0x15;
        } else if (isClosedToday()) {
            msgIndex = 7;
        } else if (entryFlags.f1) {
            setFileName("obj_etc_error");
            msgIndex = 0;
        } else {
            BOOL k = FALSE;
            u8 *p = data_021ed104;
            if (((u8 *)NookShop_GetRenovation(p))[3]) {
                l.a = 0;
                l.b = 0;
                Clock_GetDateTime(&l.a);
                if (NookShop_IsClosedTomorrow(p)) {
                    if (*((u8 *)&l + 10) > 0xc) {
                        k = TRUE;
                    }
                } else if (NookShop_IsClosedToday(p)) {
                    k = TRUE;
                } else if (NookShop_IsReopenDueNow(p)) {
                    k = TRUE;
                }
            }
            if (k) {
                msgIndex = 7;
            } else {
                msgIndex = shopLevel & 3;
            }
        }
    }
}

BOOL ShopBuilding::isOpen() {
    struct {
        u8 a, b, c, d;
    } d;
    Clock_GetMinuteHour(&d);
    if (shopLevel == -1) {
        if (d.b >= 8 && d.b < 0x17) {
            return TRUE;
        }
        return FALSE;
    }
    void *x = PlayerData_GetCurrent();
    if (GameStart_IsActive() || (x && ((PlayerData *)(x))->testFlag(0x23))) {
        return FALSE;
    }
    if (x && ((PlayerData *)(x))->testFlag(1)) {
        return TRUE;
    }
    if (isClosedToday()) {
        return FALSE;
    }
    if (d.b >= 8) {
        if (d.b < 0x17) {
            goto range;
        }
    }
    return FALSE;
range:
    if (!NookShop_IsReopenDueNow(data_021ed104)) {
        return TRUE;
    }
    return FALSE;
}

BOOL ShopBuilding::isClosedToday() {
    if (shopLevel != -1) {
        struct {
            s32 a, b;
        } d;
        d.a = 0;
        d.b = 0;
        Clock_GetDateTime(&d);
        if (NookShop_IsClosedOn(data_021ed104, &d)) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL ShopBuilding::playsDoorMelody() {
    return TRUE;
}

extern "C" ActorProfile sShopBuildingProfile = {(void *(*)())ShopBuilding_Create, 0x21, 0x27, 0, 0xc8000, 0x12c000, 0x258000};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02217510) {
    HOST_OVERLAY_VAR(sShopBuildingProfile),
    HOST_OVERLAY_VARS_END
};
