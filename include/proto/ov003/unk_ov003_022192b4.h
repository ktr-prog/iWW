#ifndef PROTO_PROTO_OV003_UNK_OV003_022192B4_H
#define PROTO_PROTO_OV003_UNK_OV003_022192B4_H


#include "types.h"
#include "sys/ProcProfile.h"
struct FieldItemFx;
struct FieldItemFxTable;
struct TreeAnim;
struct TreeAnimRequest;
struct TreeLeafFx;
struct TreeLeafFxCbs;
#ifndef __cplusplus
typedef struct FieldItemFx FieldItemFx;
typedef struct FieldItemFxTable FieldItemFxTable;
typedef struct TreeAnim TreeAnim;
typedef struct TreeAnimRequest TreeAnimRequest;
typedef struct TreeLeafFx TreeLeafFx;
typedef struct TreeLeafFxCbs TreeLeafFxCbs;
#endif
#ifdef __cplusplus
#include "field/FieldUnitPos.h"
#include "gfx/EffectSplEmitter.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/VecFx32.h"
#include "sys/Heap.h"
class EffectModel;
class FieldObjectManager;
class TreeAnimSet;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov003_02232eb4
extern char data_ov003_02232eb4[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_022333c0
extern char data_ov003_022333c0[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233790
extern char data_ov003_02233790[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234328
extern char data_ov003_02234328[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232c7c
extern char data_ov003_02232c7c[0x18];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233400
extern char data_ov003_02233400[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_022345d4
extern char data_ov003_022345d4[0x30];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233288
extern char data_ov003_02233288[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232ed0
extern char data_ov003_02232ed0[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232874
extern char data_ov003_02232874[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232f08
extern char data_ov003_02232f08[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232c64
extern char data_ov003_02232c64[0x18];
#endif
#ifndef PROTO_LOCAL_data_ov003_022337fc
extern char data_ov003_022337fc[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232cac
extern char data_ov003_02232cac[0x18];
#endif
#ifndef PROTO_LOCAL_data_ov003_022329b8
extern char data_ov003_022329b8[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233868
extern char data_ov003_02233868[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233420
extern char data_ov003_02233420[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_022329c8
extern char data_ov003_022329c8[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232dcc
extern char *data_ov003_02232dcc[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232cc4
extern char data_ov003_02232cc4[0x18];
#endif
#ifndef PROTO_LOCAL_data_ov003_022338b0
extern char data_ov003_022338b0[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232f24
extern char data_ov003_02232f24[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_022338d4
extern char data_ov003_022338d4[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223391c
extern char data_ov003_0223391c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232988
extern char data_ov003_02232988[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233820
extern char data_ov003_02233820[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232f5c
extern char data_ov003_02232f5c[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233988
extern char data_ov003_02233988[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022339ac
extern char data_ov003_022339ac[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022343a0
extern char data_ov003_022343a0[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233a18
extern char data_ov003_02233a18[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233480
extern char data_ov003_02233480[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233a84
extern char data_ov003_02233a84[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232cdc
extern char data_ov003_02232cdc[0x18];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233aa8
extern char data_ov003_02233aa8[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223263c
extern char *data_ov003_0223263c[1];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232f78
extern char data_ov003_02232f78[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233af0
extern char data_ov003_02233af0[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233b14
extern char data_ov003_02233b14[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232a28
extern char *data_ov003_02232a28[4];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232b18
extern char *data_ov003_02232b18[4];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223288c
extern char data_ov003_0223288c[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_022334a0
extern char data_ov003_022334a0[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233b80
extern char data_ov003_02233b80[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233bec
extern char data_ov003_02233bec[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232f94
extern char data_ov003_02232f94[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233c10
extern char data_ov003_02233c10[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232630
extern char *data_ov003_02232630[1];
#endif
#ifndef PROTO_LOCAL_sTreeAnimPaths
extern char *sTreeAnimPaths[32];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233c7c
extern char data_ov003_02233c7c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022329f8
extern char data_ov003_022329f8[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233004
extern char data_ov003_02233004[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232bec
extern char *data_ov003_02232bec[5];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232910
extern char * *data_ov003_02232910[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233020
extern char data_ov003_02233020[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223303c
extern char data_ov003_0223303c[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232d3c
extern char *data_ov003_02232d3c[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232654
extern char *data_ov003_02232654[1];
#endif
#ifndef PROTO_LOCAL_data_ov003_022343f0
extern char data_ov003_022343f0[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233ce8
extern char data_ov003_02233ce8[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233d0c
extern char data_ov003_02233d0c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233d30
extern char data_ov003_02233d30[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233090
extern char data_ov003_02233090[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233500
extern char data_ov003_02233500[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234418
extern char data_ov003_02234418[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232d84
extern char *data_ov003_02232d84[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233100
extern char data_ov003_02233100[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232d9c
extern char *data_ov003_02232d9c[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233138
extern char data_ov003_02233138[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234440
extern char data_ov003_02234440[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232998
extern char data_ov003_02232998[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234468
extern char data_ov003_02234468[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232db4
extern char *data_ov003_02232db4[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232aa8
extern char *data_ov003_02232aa8[4];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223294c
extern char * *data_ov003_0223294c[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233520
extern char data_ov003_02233520[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233e2c
extern char data_ov003_02233e2c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233e50
extern char data_ov003_02233e50[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223264c
extern char *data_ov003_0223264c[1];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232ac8
extern char *data_ov003_02232ac8[4];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233e74
extern char data_ov003_02233e74[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233e98
extern char data_ov003_02233e98[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233ebc
extern char data_ov003_02233ebc[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233f04
extern char data_ov003_02233f04[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233f28
extern char data_ov003_02233f28[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232898
extern char data_ov003_02232898[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233540
extern char data_ov003_02233540[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223285c
extern char data_ov003_0223285c[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233f70
extern char data_ov003_02233f70[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232a18
extern char *data_ov003_02232a18[4];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232b28
extern char *data_ov003_02232b28[4];
#endif
#ifndef PROTO_LOCAL_data_ov003_022331e0
extern char data_ov003_022331e0[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232dfc
extern char *data_ov003_02232dfc[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233fb8
extern char data_ov003_02233fb8[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234024
extern char data_ov003_02234024[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233218
extern char data_ov003_02233218[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233234
extern char data_ov003_02233234[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234048
extern char data_ov003_02234048[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233250
extern char data_ov003_02233250[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_022344e0
extern char data_ov003_022344e0[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_022340d8
extern char data_ov003_022340d8[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232634
extern char *data_ov003_02232634[1];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223326c
extern char data_ov003_0223326c[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233560
extern char data_ov003_02233560[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_022345a8
extern char data_ov003_022345a8[0x2c];
#endif
#ifndef PROTO_LOCAL_data_ov003_022340fc
extern char data_ov003_022340fc[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234508
extern char data_ov003_02234508[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232648
extern char *data_ov003_02232648[1];
#endif
#ifndef PROTO_LOCAL_data_ov003_022332c0
extern char data_ov003_022332c0[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_022332dc
extern char data_ov003_022332dc[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234120
extern char data_ov003_02234120[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022332f8
extern char data_ov003_022332f8[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234530
extern char data_ov003_02234530[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232638
extern char *data_ov003_02232638[1];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234558
extern char data_ov003_02234558[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_022328bc
extern char * *data_ov003_022328bc[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223418c
extern char data_ov003_0223418c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022335c0
extern u32 data_ov003_022335c0[8];
#endif
#ifndef PROTO_LOCAL_data_ov003_022341f8
extern char data_ov003_022341f8[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233384
extern char data_ov003_02233384[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223421c
extern char data_ov003_0223421c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232788
extern char *data_ov003_02232788[2];
#endif
#ifndef PROTO_LOCAL_sFieldObjectLoaders
extern BOOL (*sFieldObjectLoaders[9]) ();
#endif
#ifndef PROTO_LOCAL_data_ov003_02234288
extern char data_ov003_02234288[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_022328d4
extern char * *data_ov003_022328d4[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232904
extern char * *data_ov003_02232904[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_022335e0
extern char data_ov003_022335e0[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233604
extern char data_ov003_02233604[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232978
extern char data_ov003_02232978[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232868
extern char data_ov003_02232868[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233628
extern char data_ov003_02233628[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233694
extern char data_ov003_02233694[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232850
extern char data_ov003_02232850[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232e44
extern char data_ov003_02232e44[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_022336b8
extern char data_ov003_022336b8[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232e60
extern char data_ov003_02232e60[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234300
extern char data_ov003_02234300[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232e7c
extern char data_ov003_02232e7c[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233724
extern char data_ov003_02233724[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233748
extern char data_ov003_02233748[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022337b4
extern char data_ov003_022337b4[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232a48
extern char *data_ov003_02232a48[4];
#endif
#ifndef PROTO_LOCAL_data_ov003_022337d8
extern char data_ov003_022337d8[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232650
extern char *data_ov003_02232650[1];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234350
extern char data_ov003_02234350[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233440
extern char data_ov003_02233440[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223388c
extern char data_ov003_0223388c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232f40
extern char data_ov003_02232f40[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233940
extern char data_ov003_02233940[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233368
extern char data_ov003_02233368[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232934
extern char * *data_ov003_02232934[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_022329d8
extern char data_ov003_022329d8[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233460
extern char data_ov003_02233460[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233a60
extern char data_ov003_02233a60[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232a08
extern char data_ov003_02232a08[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233acc
extern char data_ov003_02233acc[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232ab8
extern char *data_ov003_02232ab8[4];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232940
extern char *data_ov003_02232940[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232d0c
extern char *data_ov003_02232d0c[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233ba4
extern char data_ov003_02233ba4[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022334e0
extern char data_ov003_022334e0[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233c34
extern char data_ov003_02233c34[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232720
extern char *data_ov003_02232720[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233ca0
extern char data_ov003_02233ca0[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022343c8
extern char data_ov003_022343c8[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233074
extern char data_ov003_02233074[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232d54
extern char *data_ov003_02232d54[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_022328ec
extern char * *data_ov003_022328ec[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_022330ac
extern char data_ov003_022330ac[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233d54
extern char data_ov003_02233d54[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022330e4
extern char data_ov003_022330e4[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233d9c
extern char data_ov003_02233d9c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234490
extern char data_ov003_02234490[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232820
extern char data_ov003_02232820[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223318c
extern char data_ov003_0223318c[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_022326e8
extern char *data_ov003_022326e8[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022331a8
extern char data_ov003_022331a8[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_022344b8
extern char data_ov003_022344b8[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233ee0
extern char data_ov003_02233ee0[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233f4c
extern char data_ov003_02233f4c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233f94
extern char data_ov003_02233f94[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234000
extern char data_ov003_02234000[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232778
extern char *data_ov003_02232778[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223406c
extern char data_ov003_0223406c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232e14
extern char *data_ov003_02232e14[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_022332a4
extern char data_ov003_022332a4[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232e2c
extern char *data_ov003_02232e2c[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234144
extern char data_ov003_02234144[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022328b0
extern char *data_ov003_022328b0[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_022335a0
extern char data_ov003_022335a0[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232bc8
extern char *data_ov003_02232bc8[4];
#endif
#ifndef PROTO_LOCAL_data_ov003_022341b0
extern char data_ov003_022341b0[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022341d4
extern char data_ov003_022341d4[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234580
extern char data_ov003_02234580[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232bd8
extern char *data_ov003_02232bd8[5];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232958
extern char data_ov003_02232958[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232968
extern char data_ov003_02232968[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_022342b0
extern char data_ov003_022342b0[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223364c
extern char data_ov003_0223364c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233670
extern char data_ov003_02233670[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232e98
extern char data_ov003_02232e98[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232838
extern char data_ov003_02232838[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232eec
extern char data_ov003_02232eec[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_022328a4
extern char * *data_ov003_022328a4[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232c14
extern char *data_ov003_02232c14[5];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233964
extern char data_ov003_02233964[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022339f4
extern char data_ov003_022339f4[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022328f8
extern char * *data_ov003_022328f8[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232af8
extern char *data_ov003_02232af8[4];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233b38
extern char data_ov003_02233b38[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232cf4
extern char *data_ov003_02232cf4[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_022330c8
extern char data_ov003_022330c8[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232fb0
extern char data_ov003_02232fb0[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232fcc
extern char data_ov003_02232fcc[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232fe8
extern char data_ov003_02232fe8[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232d24
extern char *data_ov003_02232d24[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233cc4
extern char data_ov003_02233cc4[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232d6c
extern char *data_ov003_02232d6c[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233dc0
extern char data_ov003_02233dc0[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233154
extern char data_ov003_02233154[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233e08
extern char data_ov003_02233e08[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232de4
extern char *data_ov003_02232de4[6];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233fdc
extern char data_ov003_02233fdc[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022331fc
extern char data_ov003_022331fc[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234090
extern char data_ov003_02234090[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233580
extern char data_ov003_02233580[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233314
extern char data_ov003_02233314[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223334c
extern char data_ov003_0223334c[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232880
extern char data_ov003_02232880[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232844
extern char data_ov003_02232844[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_022336dc
extern char data_ov003_022336dc[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223376c
extern char data_ov003_0223376c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022328c8
extern char *data_ov003_022328c8[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233844
extern char data_ov003_02233844[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022338f8
extern char data_ov003_022338f8[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022339d0
extern char data_ov003_022339d0[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022328e0
extern char * *data_ov003_022328e0[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233b5c
extern char data_ov003_02233b5c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232690
extern char data_ov003_02232690[0x8];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233c58
extern char data_ov003_02233c58[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233058
extern char data_ov003_02233058[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232644
extern char *data_ov003_02232644[1];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223311c
extern char data_ov003_0223311c[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233de4
extern char data_ov003_02233de4[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233330
extern char data_ov003_02233330[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234240
extern char data_ov003_02234240[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022342d8
extern char data_ov003_022342d8[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233700
extern char data_ov003_02233700[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022329a8
extern char data_ov003_022329a8[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232c94
extern char data_ov003_02232c94[0x18];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233170
extern char data_ov003_02233170[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_022329e8
extern char data_ov003_022329e8[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233bc8
extern char data_ov003_02233bc8[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233d78
extern char data_ov003_02233d78[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223282c
extern char data_ov003_0223282c[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_022331c4
extern char data_ov003_022331c4[0x1c];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232b58
extern char *data_ov003_02232b58[4];
#endif
#ifndef PROTO_LOCAL_data_ov003_022340b4
extern char data_ov003_022340b4[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234168
extern char data_ov003_02234168[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_022333a0
extern char data_ov003_022333a0[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234378
extern char data_ov003_02234378[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_022334c0
extern char data_ov003_022334c0[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234604
extern char *data_ov003_02234604[12];
#endif
#ifndef PROTO_LOCAL_data_ov003_02233a3c
extern char data_ov003_02233a3c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232640
extern char *data_ov003_02232640[1];
#endif
#ifndef PROTO_LOCAL_data_ov003_022333e0
extern char data_ov003_022333e0[0x20];
#endif
#ifndef PROTO_LOCAL_FieldObjectManager_Create
void *FieldObjectManager_Create();
#endif
#ifndef PROTO_LOCAL_FieldObj_GetShapeRecord
const u8 *FieldObj_GetShapeRecord(u16 *p);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadTextureFiles
BOOL FieldObj_LoadTextureFiles(void *self, void **a, void **b, char **names, s32 n);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadPaletteFiles
BOOL FieldObj_LoadPaletteFiles(void *self, void **a, void **b, char **names, s32 n);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadStones
BOOL FieldObj_LoadStones();
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadStumps
BOOL FieldObj_LoadStumps();
#endif
#ifndef PROTO_LOCAL_FieldObj_GetSeasonSet
s32 FieldObj_GetSeasonSet(void *self, s32 i);
#endif
#ifndef PROTO_LOCAL_FieldObj_GetTreeModelPath
void *FieldObj_GetTreeModelPath(void *self, s32 a, s32 i);
#endif
#ifndef PROTO_LOCAL_FieldObj_GetTreeAnimModelPath
void *FieldObj_GetTreeAnimModelPath(void *self, s32 a, s32 i);
#endif
#ifndef PROTO_LOCAL_FieldObj_GetPalmAnimModelPath
void *FieldObj_GetPalmAnimModelPath(void *self, s32 i);
#endif
#ifndef PROTO_LOCAL_FieldObj_GetTreeTexturePaths
char **FieldObj_GetTreeTexturePaths(void *self, s32 i);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadTreeTextures
BOOL FieldObj_LoadTreeTextures(void *self, void **a, void **b);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadCedarTextures
BOOL FieldObj_LoadCedarTextures(void *a, void **b, void **c);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadLitCedarTexture
BOOL FieldObj_LoadLitCedarTexture(void *a, void **b, void **c);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadPalmTextures
BOOL FieldObj_LoadPalmTextures(void *a, void **b, void **c);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadTreePalettes
BOOL FieldObj_LoadTreePalettes(void *a, void **b, void **c, void **d, void **e);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadCedarPalettes
BOOL FieldObj_LoadCedarPalettes(void *a, void **b, void **c, void **d, void **e);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadLitCedarPalette
BOOL FieldObj_LoadLitCedarPalette(void *a, void **b, void **c);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadTrees
BOOL FieldObj_LoadTrees();
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadFlowers
BOOL FieldObj_LoadFlowers();
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadGrass
BOOL FieldObj_LoadGrass();
#endif
#ifndef PROTO_LOCAL_FieldObj_GetGroundTexSet
u32 FieldObj_GetGroundTexSet();
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadHoles
BOOL FieldObj_LoadHoles();
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadCracks
BOOL FieldObj_LoadCracks();
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadTurnips
BOOL FieldObj_LoadTurnips();
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadDesigns
BOOL FieldObj_LoadDesigns();
#endif
#ifndef PROTO_LOCAL_Field_SetUnitItem
void Field_SetUnitItem(s32 x, s32 y, u32 tile, s32 flag);
#endif
#ifndef PROTO_LOCAL_Tree_KeepShaking
void Tree_KeepShaking(s32 id, s32 *pos);
#endif
#ifndef PROTO_LOCAL_Tree_DropFruit
void Tree_DropFruit(u16 *cell, s32 id, s32 *pos);
#endif
#ifndef PROTO_LOCAL_Tree_DropBeeHive
void Tree_DropBeeHive(s32 aid, s32 *p);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_StartBalloonDrop
s32 FieldItemFx_StartBalloonDrop(s32 a, s32 n);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_FindLandingUnit
s32 FieldItemFx_FindLandingUnit(s32 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov003_02232b48
extern TreeLeafFxCbs data_ov003_02232b48;
#endif
#ifndef PROTO_LOCAL_data_ov003_0223291c
extern VecFx32 *data_ov003_0223291c[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232b78
extern TreeLeafFxCbs data_ov003_02232b78;
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadIconModels
BOOL FieldObj_LoadIconModels(FieldObjectManager *self);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadStoneModels
BOOL FieldObj_LoadStoneModels(FieldObjectManager *self);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadStumpModels
BOOL FieldObj_LoadStumpModels(FieldObjectManager *self);
#endif
#ifndef PROTO_LOCAL_FieldObj_GetCedarModelPath
void *FieldObj_GetCedarModelPath(FieldObjectManager *self, s32 i);
#endif
#ifndef PROTO_LOCAL_FieldObj_GetCedarAnimModelPath
void *FieldObj_GetCedarAnimModelPath(FieldObjectManager *self, s32 i);
#endif
#ifndef PROTO_LOCAL_FieldObj_GetPalmModelPath
void *FieldObj_GetPalmModelPath(FieldObjectManager *self, s32 i);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadTreeSaplingModels
BOOL FieldObj_LoadTreeSaplingModels(FieldObjectManager *self, void **a, void **b, u32 *c);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadCedarSaplingModel
BOOL FieldObj_LoadCedarSaplingModel(FieldObjectManager *self, void **a, void **b, u32 *c);
#endif
#ifndef PROTO_LOCAL_FieldObj_LoadPalmSaplingModel
BOOL FieldObj_LoadPalmSaplingModel(FieldObjectManager *self, void **a, void **b, u32 *c);
#endif
#ifndef PROTO_LOCAL_TreeLeafFx_OnEffectInit
void TreeLeafFx_OnEffectInit(EffectEmitterEntry *self);
#endif
#ifndef PROTO_LOCAL_TreeLeafFx_OnEffectStep
s32 TreeLeafFx_OnEffectStep(EffectEmitterEntry *self);
#endif
#ifndef PROTO_LOCAL_TreeLeafFx_OnEffectUpdate
s32 TreeLeafFx_OnEffectUpdate(EffectEmitterEntry *self);
#endif
#ifndef PROTO_LOCAL_TreeAnimSet_ProcessRequest
void TreeAnimSet_ProcessRequest(TreeAnimSet *a, TreeAnimRequest *o);
#endif
#ifndef PROTO_LOCAL_TreeAnimSet_Request
void TreeAnimSet_Request(TreeAnimSet *a, s32 id, s32 *pos, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_TreeAnim_Init
void TreeAnim_Init(TreeAnim *o);
#endif
#ifndef PROTO_LOCAL_TreeAnim_Update
void TreeAnim_Update(TreeAnim *o);
#endif
#ifndef PROTO_LOCAL_TreeAnim_Draw
void TreeAnim_Draw(TreeAnim *o);
#endif
#ifndef PROTO_LOCAL_TreeAnim_Release
void TreeAnim_Release(TreeAnim *o);
#endif
#ifndef PROTO_LOCAL_TreeAnim_Begin
void TreeAnim_Begin(TreeAnim *o, s32 flag);
#endif
#ifndef PROTO_LOCAL_Tree_GetDropSide
s32 Tree_GetDropSide(s32 aid, VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_TreeAnim_DropItems
void TreeAnim_DropItems(TreeAnim *self, void *cell);
#endif
#ifndef PROTO_LOCAL_TreeAnim_Reset
void TreeAnim_Reset(TreeAnim *self);
#endif
#ifndef PROTO_LOCAL_TreeAnim_ModelCallback
void TreeAnim_ModelCallback(NNSG3dRS *rs);
#endif
#ifndef PROTO_LOCAL_TreeAnimSet_LoadAnims
void TreeAnimSet_LoadAnims(TreeAnimSet *set);
#endif
#ifndef PROTO_LOCAL_TreeAnimSet_FreeAnims
void TreeAnimSet_FreeAnims(TreeAnimSet *set);
#endif
#ifndef PROTO_LOCAL_TreeAnimSet_GetAnimPath
char *TreeAnimSet_GetAnimPath(TreeAnimSet *self, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_TreeAnimRequest_Resolve
void TreeAnimRequest_Resolve(TreeAnimRequest *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_ReleasePending
void FieldItemFx_ReleasePending(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_Finish
void FieldItemFx_Finish(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_Clear
void FieldItemFx_Clear(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdateToss
void FieldItemFx_UpdateToss(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdateHoleOpen
void FieldItemFx_UpdateHoleOpen(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdateHoleClose
void FieldItemFx_UpdateHoleClose(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_InitPop
void FieldItemFx_InitPop(FieldItemFx *self, FieldUnitPos *p);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdatePop
void FieldItemFx_UpdatePop(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_InitTreeDrop
void FieldItemFx_InitTreeDrop(FieldItemFx *self, FieldUnitPos *p, VecFx32 *q, s32 skip);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdateTreeDrop
void FieldItemFx_UpdateTreeDrop(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_InitTreeDropFloat
void FieldItemFx_InitTreeDropFloat(FieldItemFx *self, FieldUnitPos *p, VecFx32 *q);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdateTreeDropFloat
void FieldItemFx_UpdateTreeDropFloat(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_InitBeeHiveDrop
void FieldItemFx_InitBeeHiveDrop(FieldItemFx *self, FieldUnitPos *unit, VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdateBeeHiveDrop
void FieldItemFx_UpdateBeeHiveDrop(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_InitDigUpTree
void FieldItemFx_InitDigUpTree(FieldItemFx *self, FieldUnitPos *p, u32 ang);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdateDigUpTree
void FieldItemFx_UpdateDigUpTree(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_InitPlant
void FieldItemFx_InitPlant(FieldItemFx *self, FieldUnitPos *p, VecFx32 *q, u32 w);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdatePlant
void FieldItemFx_UpdatePlant(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_InitHoleShrink
void FieldItemFx_InitHoleShrink(FieldItemFx *self, FieldUnitPos *p);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdateHoleShrink
void FieldItemFx_UpdateHoleShrink(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_InitStrikeShake
void FieldItemFx_InitStrikeShake(FieldItemFx *self, FieldUnitPos *p);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdateStrikeShake
void FieldItemFx_UpdateStrikeShake(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_SplashPosCallback
void FieldItemFx_SplashPosCallback(EffectModel *p);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_InitBalloonDrop
void FieldItemFx_InitBalloonDrop(FieldItemFx *self, VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_UpdateBalloonDrop
void FieldItemFx_UpdateBalloonDrop(FieldItemFx *self);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_StartDigHole
s32 FieldItemFx_StartDigHole(s32 type, VecFx32 *v, s32 w);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_StartPitfallHole
s32 FieldItemFx_StartPitfallHole(s32 type, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_StartFillHole
s32 FieldItemFx_StartFillHole(s32 type, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_StartFillHoleWithItem
s32 FieldItemFx_StartFillHoleWithItem(s32 a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_StartDigUpTree
s32 FieldItemFx_StartDigUpTree(s32 a, VecFx32 *b, s32 c);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_StartHoleShrink
s32 FieldItemFx_StartHoleShrink(s32 a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_FieldItemFx_StartPitfallClose
s32 FieldItemFx_StartPitfallClose(s32 a, VecFx32 *b);
#endif
}
#ifndef PROTO_LOCAL_sTreeLeafFx
extern TreeLeafFx sTreeLeafFx;
#endif
#ifndef PROTO_LOCAL_sFieldItemFxTable
extern FieldItemFxTable sFieldItemFxTable;
#endif
#ifndef PROTO_LOCAL_sFieldObjectModelHeap
extern Heap *sFieldObjectModelHeap;
#endif
#ifndef PROTO_LOCAL_sFieldObjectManagerProfile
extern ProcProfile sFieldObjectManagerProfile;
#endif
#ifndef PROTO_LOCAL_gFieldObjectManager
extern FieldObjectManager *gFieldObjectManager;
#endif
#ifndef PROTO_LOCAL_sFieldObjectAnimHeap
extern Heap *sFieldObjectAnimHeap;
#endif
#endif

#endif
