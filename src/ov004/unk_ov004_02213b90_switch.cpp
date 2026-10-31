#include "types.h"
#include "Unk_020d8c7c.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "gfx/VecFx32.h"
#include "game/Unk_ov004_022146ec_Bits.h"
#include "net/CommManager.h"
#include "talk/TalkWindowState.h"
#include "talk/MsgString9B.h"
#include "item/ItemName.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "room/MuseumExhibitInfo.h"
#include "game/TouchPickSphere.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_02094810.h"
#include "proto/ov004/unk_ov004_02213b90.h"
#include "proto/ov004/unk_ov004_02213b90_switch.h"

BOOL MuseumExhibitInfo::buildItemList() {
    if (isAutoTalkKind() == 0) {
        u16 **p = &items;
        *p = (u16 *)Mem_Alloc(itemCount * 2);
        if (*p) {
            u32 i;
            switch (kind) {
            case 0:
                for (i = 0; i < itemCount; i++) {
                    u32 v = sMuseumExhibitSpawnList[i];
                    u16 r;
                    if (v < 0x38) r = v + 0x12b0; else r = 0x12b0;
                    items[i] = r;
                }
                return TRUE;
            case 1:
                for (i = 0; i < itemCount; i++) {
                    u32 v = sMuseumExhibitSpawnList[i];
                    u16 r;
                    if (v < 0x38) r = v + 0x12e8; else r = 0x12e8;
                    items[i] = r;
                }
                return TRUE;
            case 2:
                for (i = 0; i < itemCount; i++) {
                    u32 v = sMuseumExhibitSpawnList[i];
                    u32 r;
                    if (v < 0x14) r = v * 4 + 0x3894; else r = 0x3894;
                    items[i] = r;
                }
                return TRUE;
            case 3:
                for (i = 0; i < itemCount; i++) {
                    u32 v = sMuseumExhibitSpawnList[i];
                    u32 r;
                    if (v < 0x34) r = v * 4 + 0x450c; else r = 0x450c;
                    items[i] = r;
                }
                return TRUE;
            default:
                return FALSE;
            }
        }
        return FALSE;
    }
    return TRUE;
}
