#include "types.h"
#include "item/Letter.h"
#include "game/Loc488.h"
#include "item/ItemName.h"
#include "item/LetterView.h"
#include "player/PlayerData.h"
#include "field/LooseSnowballs.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020af3f4.h"
#include "proto/main/unk_020af514.h"


extern "C" {
extern const u16 sSnowmanPrizeItems[];
}

extern "C" void Snowman_SendLetter(u32 idx) {
    if (idx < 13) {
        Loc488 l;
        l.b = sSnowmanPrizeItems[idx];
        PlayerData *obj = PlayerData_GetCurrent();
        if (obj) {
            Letter big;
            l.a = idx;
            ItemName s(&l.b);
            MailText_SetSlot(1, &s);
            Letter_ComposeFromMail((LetterView *)&big, (const u8 *)&l, "sp_npc_snowman", &data_020e2eb8, &data_020e2ebc,
                                   obj->getPlayerId());
            ((LetterView *)(&big))->setPresent(l.b, 1);
            LetterDelivery_QueueOutgoing(&big, 0);
        }
    }
}

extern "C" void Snowman_SendPrizeLetter() {
    PlayerData *obj = PlayerData_GetCurrent();
    if (obj) {
        u32 count = 0;
        for (u32 i = 0; i < 13; i++) {
            u16 t = sSnowmanPrizeItems[i];
            if (!Catalog_HasItem(obj->getCatalog(), &t)) count++;
        }
        if (count) {
            u32 r = (u32)Random_GlobalBelow(count);
            u32 c = 0;
            for (u32 i = 0; i < 13; i++) {
                u16 t = sSnowmanPrizeItems[i];
                if (!Catalog_HasItem(obj->getCatalog(), &t)) {
                    if (c == r) {
                        Snowman_SendLetter(i);
                        return;
                    }
                    c++;
                }
            }
        }
        Snowman_SendLetter((u32)Random_GlobalBelow(13));
    }
}

extern "C" LooseSnowballs *LooseSnowballs_Get() { return &gLooseSnowballs; }


u32 data_020e2ebc = 0x11;
u32 data_020e2eb8 = 0xa;

const u16 sSnowmanPrizeItems[13] = {0x31f8, 0x31f4, 0x31e0, 0x31ec, 0x3204, 0x31f0, 0x31fc, 0x31e4, 0x31e8, 0x3200, 0x1150, 0x110c, 0x36d4};
