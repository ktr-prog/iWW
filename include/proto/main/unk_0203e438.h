#ifndef PROTO_PROTO_MAIN_UNK_0203E438_H
#define PROTO_PROTO_MAIN_UNK_0203E438_H


#include "types.h"
#ifdef __cplusplus
#include "actor/Character.h"
#include "game/CharacterList.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Character_ResetList
void Character_ResetList(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Character_FindByCharId
Character *Character_FindByCharId(u32 id);
#endif
#ifndef PROTO_LOCAL_Character_FindInteractionTarget
Character *Character_FindInteractionTarget(Character *self);
#endif
}
#ifndef PROTO_LOCAL_gCharacterList
extern CharacterList gCharacterList;
#endif
#endif

#endif
