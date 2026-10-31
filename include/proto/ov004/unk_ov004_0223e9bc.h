#ifndef PROTO_PROTO_OV004_UNK_OV004_0223E9BC_H
#define PROTO_PROTO_OV004_UNK_OV004_0223E9BC_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
class ShopStockPlacer;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ShopStock_GetLayout
const u32 *ShopStock_GetLayout();
#endif
#ifndef PROTO_LOCAL_ShopStock_GetItemCode
s32 ShopStock_GetItemCode(u16 *p);
#endif
#ifndef PROTO_LOCAL_ShopStock_IsForSale
BOOL ShopStock_IsForSale(u16 *p);
#endif
#ifndef PROTO_LOCAL_ShopStock_GetItemAt
u16 *ShopStock_GetItemAt(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_ShopStock_GetCode22Index
s32 ShopStock_GetCode22Index(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_ShopStock_FindTileOfStock
BOOL ShopStock_FindTileOfStock(s32 *px, s32 *py, s32 code);
#endif
#ifndef PROTO_LOCAL_ShopStock_GetItemAtTile
u16 *ShopStock_GetItemAtTile(s32 x, s32 y);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_ShopStockPlacer_Create
ShopStockPlacer *ShopStockPlacer_Create();
#endif
}
#ifndef PROTO_LOCAL_sShopStockPlacerProfile
extern ProcProfile sShopStockPlacerProfile;
#endif
#endif

#endif
