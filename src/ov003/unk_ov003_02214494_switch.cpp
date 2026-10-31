#include "types.h"
#include "field/Unk_ov003_02214494_Views.h"
#include "talk/TalkWindowState.h"
#include "game/ReddPassword.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "town/ReddTent.h"

















void ReddTent::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 6:
        BuildingActor::onInteractionEvent(a, b);
        break;
    case 0:
    case 1:
        setTentState(1);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
        break;
    case 8:
        setTentState(0);
        break;
    }
}
