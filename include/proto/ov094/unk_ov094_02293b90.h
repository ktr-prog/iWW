#ifndef PROTO_PROTO_OV094_UNK_OV094_02293B90_H
#define PROTO_PROTO_OV094_UNK_OV094_02293B90_H


#include "types.h"
#ifdef __cplusplus
#include "item/LetterView.h"
#include "menu/InventoryGridTypes.h"
#include "menu/LetterGrid.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sLetterGridColumnX
extern u8 sLetterGridColumnX[5];
#endif
#ifndef PROTO_LOCAL_sLetterIconPalettes
extern u8 sLetterIconPalettes[16];
#endif
#ifndef PROTO_LOCAL_sLetterIconChars
extern u16 sLetterIconChars[16];
#endif
#ifndef PROTO_LOCAL_data_ov094_02294c14
extern char data_ov094_02294c14[];
#endif
#ifndef PROTO_LOCAL_LetterGrid_ClearBits
void LetterGrid_ClearBits(u32 *bits);
#endif
#ifndef PROTO_LOCAL_LetterGrid_SetBit
void LetterGrid_SetBit(u32 *bits, s32 i);
#endif
#ifndef PROTO_LOCAL_LetterGrid_ClearBit
void LetterGrid_ClearBit(u32 *bits, s32 i);
#endif
#ifndef PROTO_LOCAL_LetterGrid_TestBit
BOOL LetterGrid_TestBit(u32 *bits, s32 i);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sLetterIconSprite
extern OamObjTemplate sLetterIconSprite;
#endif
#ifndef PROTO_LOCAL_sLetterMarkSprites
extern OamObjTemplate sLetterMarkSprites[3];
#endif
#ifndef PROTO_LOCAL_LetterGrid_DrawSlot
void LetterGrid_DrawSlot(LetterGrid *o, LetterView *letter, s32 idx, s32 x, s32 y0);
#endif
#ifndef PROTO_LOCAL_LetterGrid_GetSlotX
s32 LetterGrid_GetSlotX(LetterGrid *o, s32 i);
#endif
#ifndef PROTO_LOCAL_LetterGrid_GetSlotY
s32 LetterGrid_GetSlotY(LetterGrid *o, s32 i);
#endif
#ifndef PROTO_LOCAL_LetterGrid_IsSlotEmpty
BOOL LetterGrid_IsSlotEmpty(LetterGrid *o, s32 i);
#endif
#ifndef PROTO_LOCAL_LetterGrid_LoadPocketLetters
void LetterGrid_LoadPocketLetters(LetterGrid *o);
#endif
#ifndef PROTO_LOCAL_LetterGrid_SetLetters2D
void LetterGrid_SetLetters2D(LetterGrid *o, void *letters);
#endif
#ifndef PROTO_LOCAL_LetterGrid_SetLetters0A
void LetterGrid_SetLetters0A(LetterGrid *o, void *letters);
#endif
#ifndef PROTO_LOCAL_LetterGrid_SetLetters23
void LetterGrid_SetLetters23(LetterGrid *o, void *letters);
#endif
#ifndef PROTO_LOCAL_LetterGrid_SetLetterArray
void LetterGrid_SetLetterArray(LetterGrid *o, LetterView *p, s32 m, s32 n);
#endif
#ifndef PROTO_LOCAL_LetterGrid_GetIconIndex
s32 LetterGrid_GetIconIndex(LetterGrid *o, LetterView *h);
#endif
#ifndef PROTO_LOCAL_LetterGrid_StartPopAnim
void LetterGrid_StartPopAnim(LetterGrid *o);
#endif
#ifndef PROTO_LOCAL_LetterGrid_ResetScale
void LetterGrid_ResetScale(LetterGrid *o);
#endif
#ifndef PROTO_LOCAL_LetterGrid_UpdatePopAnim
BOOL LetterGrid_UpdatePopAnim(LetterGrid *o);
#endif
#ifndef PROTO_LOCAL_LetterGrid_GetPopScale
u8 LetterGrid_GetPopScale(LetterGrid *o);
#endif
}
#endif

#endif
