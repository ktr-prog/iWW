#include "types.h"
#include "host_labels.h"
#include "host_overlay_vars.h"
#include "gfx/VecFx32.h"

#include "Unk_020d8c7c.h"
#include "item/ItemId.h"
#include "save/MuseumData.h"
#include "sys/ProcProfile.h"
#include "proto/main/unk_02052b50.h"
#include "proto/ov004/unk_ov004_02213b90.h"
#include "proto/ov004/unk_ov004_0223db88.h"
#include "proto/main/unk_0204cc1c.h"


struct MuseumInfoPointData {
    /* 0x00 */ VecFx32 pos;
    /* 0x0c */ s32 arc;
    /* 0x10 */ s16 angle;
    /* 0x12 */ s16 message;
    /* 0x14 */ u8 *itemList;
    /* 0x18 */ u8 itemCount;
    /* 0x19 */ u8 kind;
    /* 0x1a */ u8 pad_1a[2];
};

struct MuseumInfoPointDef {
    /* 0x00 */ VecFx32 pos;
    /* 0x0c */ u8 facingMask;
    /* 0x0d */ u8 kind;
    /* 0x0e */ s16 message;
    /* 0x10 */ const u8 *itemList;
    /* 0x14 */ u8 itemCount;
    /* 0x15 */ u8 pad_15[3];
};

struct MuseumInfoPointSet {
    u8 scene;
    MuseumInfoPointData *points;
    u32 numPoints;
};

typedef VecFx32 V3;
typedef MuseumInfoPointData Rec;



#define data_021ed0a0 HOST_LABEL(MuseumData *, data_021ed0a0)


extern "C" {
extern BlockMap *gSceneBlockMap;
extern const MuseumInfoPointSet sMuseumInfoPointsByScene[];

s32 FX_Div(s32 a, s32 b);
s32 Math_AngleDiffAbs(s32 a, s32 b);
s32 Scene_GetCurrent();
u32 MuseumInfoPoint_GetItemCount(Rec *r);
u8 *MuseumInfoPoint_GetItemList(Rec *r);
s16 MuseumInfoPoint_GetMessage(Rec *r);
u32 MuseumInfoPoint_GetKind(Rec *r);
s32 MuseumInfoPoint_GetArc(Rec *r);
s16 MuseumInfoPoint_GetAngle(Rec *r);
V3 *MuseumInfoPoint_GetPos(Rec *r);
void MuseumInfoPoint_Init(Rec *r, V3 *pos, s32 mask, u32 b, s16 c, u8 *d, u8 e);
}

class MuseumRoom : public GameProc {
public:
    MuseumRoom();
    virtual BOOL onCreate();
    virtual BOOL onExecute();
    virtual ~MuseumRoom();
    virtual BOOL setupExhibits();

    void spawnInfoPoints();
};

class MuseumFossilRoom : public MuseumRoom {
public:
    MuseumFossilRoom();
    virtual ~MuseumFossilRoom();
    virtual BOOL setupExhibits();
};

class MuseumRoomUnk53 : public MuseumRoom {
public:
    MuseumRoomUnk53();
    virtual ~MuseumRoomUnk53();
    virtual BOOL setupExhibits();
};

extern "C" Rec *MuseumInfoPoint_InitFromDef(Rec *r, const MuseumInfoPointDef *d);
struct MuseumInfoPoint : Rec {
    MuseumInfoPoint() {}
    MuseumInfoPoint(const MuseumInfoPointDef &d) { MuseumInfoPoint_InitFromDef(this, &d); }
    ~MuseumInfoPoint();
};

extern const u8 data_ov004_022441d0[9];
extern const u8 data_ov004_022441c4[9];
extern const u8 data_ov004_022441bc[8];
extern const u8 data_ov004_022441dc[9];
extern const u8 data_ov004_022441e8[10];
extern const u8 data_ov004_022441f4[11];
extern const u8 data_ov004_02244154[3];
extern const u8 data_ov004_02244168[3];
extern const u8 data_ov004_02244164[3];
extern const u8 data_ov004_0224415c[3];
extern const u8 data_ov004_02244160[3];
extern const u8 data_ov004_02244158[3];
extern const u8 data_ov004_02244114[1];
extern const u8 data_ov004_02244138[1];
extern const u8 data_ov004_022440f4[1];
extern const u8 data_ov004_022440e0[1];
extern const u8 data_ov004_022440c4[1];
extern const u8 data_ov004_02244108[1];
extern const u8 data_ov004_02244150[3];
extern const u8 data_ov004_02244144[3];
extern const u8 data_ov004_0224414c[3];
extern const u8 data_ov004_0224416c[4];
extern const u8 data_ov004_02244148[3];
extern const u8 data_ov004_02244140[2];
extern const u8 data_ov004_02244170[4];
extern const u8 data_ov004_0224413c[2];
extern const u8 data_ov004_02244118[1];
extern const u8 data_ov004_022440f8[1];
extern const u8 data_ov004_022440e4[1];
extern const u8 data_ov004_02244134[1];
extern const u8 data_ov004_02244184[6];
extern const u8 data_ov004_022441ac[7];
extern const u8 data_ov004_0224417c[6];
extern const u8 data_ov004_0224419c[6];
extern const u8 data_ov004_0224418c[6];
extern const u8 data_ov004_02244194[6];
extern const u8 data_ov004_022441b4[7];
extern const u8 data_ov004_02244174[5];
extern const u8 data_ov004_022441a4[7];
extern const u8 data_ov004_0224410c[1];
extern const u8 data_ov004_022440fc[1];
extern const u8 data_ov004_022440dc[1];
extern const u8 data_ov004_02244128[1];
extern const u8 data_ov004_0224411c[1];
extern const u8 data_ov004_02244104[1];
extern const u8 data_ov004_022440d0[1];
extern const u8 data_ov004_022440d8[1];
extern const u8 data_ov004_02244120[1];
extern const u8 data_ov004_022440ec[1];
extern const u8 data_ov004_022440e8[1];
extern const u8 data_ov004_02244124[1];
extern const u8 data_ov004_022440c8[1];
extern const u8 data_ov004_022440f0[1];
extern const u8 data_ov004_02244110[1];
extern const u8 data_ov004_0224412c[1];
extern const u8 data_ov004_022440d4[1];
extern const u8 data_ov004_02244130[1];
extern const u8 data_ov004_022440cc[1];
extern const u8 data_ov004_02244100[1];
extern const MuseumInfoPointDef sMuseumFishPointDefs23[4];
extern const MuseumInfoPointDef sMuseumFishPointDefs24[2];
extern const MuseumInfoPointDef sMuseumFossilPointDefs25[12];
extern const MuseumInfoPointDef sMuseumFossilPointDefs26[12];
extern const MuseumInfoPointDef sMuseumInsectPointDefs27[4];
extern const MuseumInfoPointDef sMuseumInsectPointDefs28[5];
extern const MuseumInfoPointDef sMuseumPaintingPointDefs29[20];

const u8 data_ov004_022440f4[1] = {0x2};
const u8 data_ov004_022441ac[7] = {0xa, 0x1a, 0x20, 0x24, 0x2d, 0x2e, 0x2f};
const u8 data_ov004_02244170[4] = {0x26, 0x27, 0x28, 0x29};
const MuseumInfoPointDef sMuseumPaintingPointDefs29[20] = {
    {{29696, 4608, 4096}, 1, 2, -1, data_ov004_0224410c, 1},
    {{35584, 4608, 4096}, 1, 2, -1, data_ov004_022440fc, 1},
    {{61952, 4608, 4096}, 1, 2, -1, data_ov004_022440dc, 1},
    {{68352, 4608, 4096}, 1, 2, -1, data_ov004_02244128, 1},
    {{94208, 4608, 4096}, 1, 2, -1, data_ov004_0224411c, 1},
    {{20736, 4608, 36864}, 1, 2, -1, data_ov004_02244104, 1},
    {{37888, 4608, 36864}, 1, 2, -1, data_ov004_022440d0, 1},
    {{68608, 4608, 36864}, 1, 2, -1, data_ov004_022440d8, 1},
    {{94208, 4608, 36864}, 1, 2, -1, data_ov004_02244120, 1},
    {{106496, 4608, 36864}, 1, 2, -1, data_ov004_022440ec, 1},
    {{20736, 4608, 69632}, 1, 2, -1, data_ov004_022440e8, 1},
    {{52224, 4608, 69632}, 1, 2, -1, data_ov004_02244124, 1},
    {{68864, 4608, 69632}, 1, 2, -1, data_ov004_022440c8, 1},
    {{94208, 4608, 69632}, 1, 2, -1, data_ov004_022440f0, 1},
    {{100864, 4608, 69632}, 1, 2, -1, data_ov004_02244110, 1},
    {{11264, 4608, 102400}, 1, 2, -1, data_ov004_0224412c, 1},
    {{37120, 4608, 102400}, 1, 2, -1, data_ov004_022440d4, 1},
    {{53248, 4608, 102400}, 1, 2, -1, data_ov004_02244130, 1},
    {{84992, 4608, 102400}, 1, 2, -1, data_ov004_022440cc, 1},
    {{106496, 4608, 102400}, 1, 2, -1, data_ov004_02244100, 1},
};
const MuseumInfoPointDef sMuseumFishPointDefs23[4] = {
    {{40192, 5120, 98560}, 1, 1, -1, data_ov004_022441d0, 9},
    {{98816, 5120, 98560}, 1, 1, -1, data_ov004_022441c4, 9},
    {{40192, 5120, 41216}, 1, 1, -1, data_ov004_022441bc, 8},
    {{98816, 5120, 41216}, 1, 1, -1, data_ov004_022441dc, 9},
};
MuseumInfoPoint sMuseumFishPoints23[4];
const u8 data_ov004_0224412c[1] = {0x1};
const u8 data_ov004_022441e8[10] = {0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c};
const MuseumInfoPointDef sMuseumFishPointDefs24[2] = {
    {{27136, 5120, 90112}, 1, 1, -1, data_ov004_022441e8, 10},
    {{105728, 5120, 90112}, 1, 1, -1, data_ov004_022441f4, 11},
};
MuseumInfoPoint sMuseumFishPoints24[2];
const u8 data_ov004_022440cc[1] = {0xf};
const u8 data_ov004_02244168[3] = {0xd, 0xe, 0xf};
const u8 data_ov004_02244140[2] = {0x1e, 0x1f};
const u8 data_ov004_02244144[3] = {0x1b, 0x1c, 0x1d};
const u8 data_ov004_022441b4[7] = {0x9, 0xb, 0x10, 0x11, 0x18, 0x2b, 0x35};
const MuseumInfoPointDef sMuseumInsectPointDefs28[5] = {
    {{97536, 5120, 22272}, 1, 0, -1, data_ov004_0224418c, 6},
    {{54272, 5120, 22272}, 1, 0, -1, data_ov004_02244194, 6},
    {{38400, 5120, 85760}, 2, 0, -1, data_ov004_022441b4, 7},
    {{67840, 5120, 51200}, 12, 0, -1, data_ov004_02244174, 5},
    {{67840, 5120, 87296}, 9, 0, -1, data_ov004_022441a4, 7},
};
const u8 data_ov004_022441bc[8] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
const u8 data_ov004_02244164[3] = {0x2a, 0x2b, 0x2c};
const u8 data_ov004_02244120[1] = {0xe};
const u8 data_ov004_022441dc[9] = {0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22};
const u8 data_ov004_022440d8[1] = {0xd};
const u8 data_ov004_022440dc[1] = {0x4};
const MuseumInfoPointDef sMuseumFossilPointDefs25[12] = {
    {{61440, 4096, 94208}, 1, 3, 34, data_ov004_02244154, 3},
    {{86016, 4096, 102400}, 1, 3, 36, data_ov004_02244168, 3},
    {{61440, 4096, 69632}, 1, 3, 32, data_ov004_02244164, 3},
    {{86016, 4096, 77824}, 1, 3, 20, data_ov004_0224415c, 3},
    {{61440, 4096, 45056}, 1, 3, 22, data_ov004_02244160, 3},
    {{86016, 4096, 53248}, 1, 3, 10, data_ov004_02244158, 3},
    {{86016, 4096, 28672}, 1, 3, -1, data_ov004_02244114, 1},
    {{94208, 4096, 28672}, 1, 3, -1, data_ov004_02244138, 1},
    {{102400, 4096, 28672}, 1, 3, -1, data_ov004_022440f4, 1},
    {{110592, 4096, 28672}, 1, 3, -1, data_ov004_022440e0, 1},
    {{118784, 4096, 28672}, 1, 3, -1, data_ov004_022440c4, 1},
    {{126976, 4096, 28672}, 1, 3, -1, data_ov004_02244108, 1},
};
MuseumInfoPoint sMuseumFossilPoints25[12];
const u8 data_ov004_022440f0[1] = {0x10};
const u8 data_ov004_02244110[1] = {0x5};
const u8 data_ov004_02244184[6] = {0xe, 0x19, 0x1e, 0x25, 0x33, 0x34};
const u8 data_ov004_02244118[1] = {0};
const u8 data_ov004_0224416c[4] = {0x30, 0x31, 0x32, 0x33};
ProcProfile sMuseumFossilRoomProfile = {(void *(*)())MuseumFossilRoom_Create, 0x52, 0x59};
const u8 data_ov004_0224418c[6] = {0x1f, 0x27, 0x28, 0x29, 0x2a, 0x2c};
const u8 data_ov004_02244130[1] = {0x7};
const u8 data_ov004_02244150[3] = {0x15, 0x16, 0x17};
const u8 data_ov004_02244100[1] = {0x6};
const u8 data_ov004_02244194[6] = {0x12, 0x13, 0x14, 0x21, 0x22, 0x26};
const u8 data_ov004_022441d0[9] = {0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8};
const u8 data_ov004_022440d0[1] = {0x12};
MuseumInfoPoint sMuseumFossilPoints26[12];
ProcProfile sMuseumRoomProfile = {(void *(*)())MuseumRoom_Create, 0x51, 0x58};
const u8 data_ov004_022440ec[1] = {0xb};
const u8 data_ov004_02244104[1] = {0};
const u8 data_ov004_0224417c[6] = {0, 0x1, 0x2, 0x3, 0x4, 0x8};
const u8 data_ov004_022440c4[1] = {0x8};
MuseumInfoPoint sMuseumInsectPoints27[4];
const u8 data_ov004_0224415c[3] = {0x20, 0x21, 0x22};
const u8 data_ov004_022440fc[1] = {0x11};
const MuseumInfoPointDef sMuseumFossilPointDefs26[12] = {
    {{53248, 4096, 102400}, 1, 3, 12, data_ov004_02244150, 3},
    {{77824, 4096, 102400}, 1, 3, 16, data_ov004_02244144, 3},
    {{53248, 4096, 77824}, 1, 3, 30, data_ov004_0224414c, 3},
    {{69632, 4096, 69632}, 1, 3, 24, data_ov004_0224416c, 4},
    {{53248, 4096, 53248}, 1, 3, 14, data_ov004_02244148, 3},
    {{94208, 4096, 45056}, 1, 3, 26, data_ov004_02244140, 2},
    {{69632, 4096, 20480}, 1, 3, 28, data_ov004_02244170, 4},
    {{94208, 4096, 20480}, 1, 3, 18, data_ov004_0224413c, 2},
    {{110592, 4096, 77824}, 1, 3, -1, data_ov004_02244118, 1},
    {{118784, 4096, 77824}, 1, 3, -1, data_ov004_022440f8, 1},
    {{110592, 4096, 61440}, 1, 3, -1, data_ov004_022440e4, 1},
    {{118784, 4096, 61440}, 1, 3, -1, data_ov004_02244134, 1},
};
const u8 data_ov004_0224411c[1] = {0xc};
const u8 data_ov004_02244138[1] = {0x9};
const u8 data_ov004_02244134[1] = {0x7};
MuseumInfoPoint sMuseumInsectPoints28[5];
const u8 data_ov004_022440c8[1] = {0xa};
const u8 data_ov004_02244158[3] = {0x12, 0x13, 0x14};
const u8 data_ov004_022440e0[1] = {0x6};
const u8 data_ov004_02244128[1] = {0x8};
const u8 data_ov004_022441c4[9] = {0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10, 0x19};
const u8 data_ov004_022440e4[1] = {0x3};
const u8 data_ov004_022441f4[11] = {0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};
const u8 data_ov004_02244154[3] = {0xa, 0xb, 0xc};
const u8 data_ov004_02244160[3] = {0x23, 0x24, 0x25};
const u8 data_ov004_02244114[1] = {0x4};
const MuseumInfoPointDef sMuseumInsectPointDefs27[4] = {
    {{61952, 5120, 86784}, 3, 0, -1, data_ov004_02244184, 6},
    {{61952, 5120, 51712}, 6, 0, -1, data_ov004_022441ac, 7},
    {{92416, 5120, 34560}, 8, 0, -1, data_ov004_0224417c, 6},
    {{92416, 5120, 86272}, 9, 0, -1, data_ov004_0224419c, 6},
};
const u8 data_ov004_02244124[1] = {0x2};
const u8 data_ov004_022440e8[1] = {0x3};
const MuseumInfoPointSet sMuseumInfoPointsByScene[7] = {
    {0x25, sMuseumFossilPoints25, 12},
    {0x26, sMuseumFossilPoints26, 12},
    {0x23, sMuseumFishPoints23, 4},
    {0x24, sMuseumFishPoints24, 2},
    {0x29, sMuseumPaintingPoints29, 20},
    {0x27, sMuseumInsectPoints27, 4},
    {0x28, sMuseumInsectPoints28, 5},
};
const u8 data_ov004_0224413c[2] = {0x10, 0x11};
const u8 data_ov004_02244174[5] = {0x15, 0x16, 0x17, 0x23, 0x31};
const u8 data_ov004_02244148[3] = {0x18, 0x19, 0x1a};
ProcProfile sMuseumRoomUnk53Profile = {(void *(*)())MuseumRoomUnk53_Create, 0x53, 0x5a};
const u8 data_ov004_0224419c[6] = {0x5, 0x6, 0x7, 0xf, 0x30, 0x32};
const u8 data_ov004_0224414c[3] = {0x2d, 0x2e, 0x2f};
const u8 data_ov004_0224410c[1] = {0x9};
MuseumInfoPoint sMuseumPaintingPoints29[20];

extern "C" void StaticInit_unk_ov004_0223db88(void) {
    for (u32 i = 0; i < sizeof sMuseumFishPoints23 / sizeof sMuseumFishPoints23[0]; i++) MuseumInfoPoint_InitFromDef(&sMuseumFishPoints23[i], &sMuseumFishPointDefs23[i]);
    for (u32 i = 0; i < sizeof sMuseumFishPoints24 / sizeof sMuseumFishPoints24[0]; i++) MuseumInfoPoint_InitFromDef(&sMuseumFishPoints24[i], &sMuseumFishPointDefs24[i]);
    for (u32 i = 0; i < sizeof sMuseumFossilPoints25 / sizeof sMuseumFossilPoints25[0]; i++) MuseumInfoPoint_InitFromDef(&sMuseumFossilPoints25[i], &sMuseumFossilPointDefs25[i]);
    for (u32 i = 0; i < sizeof sMuseumFossilPoints26 / sizeof sMuseumFossilPoints26[0]; i++) MuseumInfoPoint_InitFromDef(&sMuseumFossilPoints26[i], &sMuseumFossilPointDefs26[i]);
    for (u32 i = 0; i < sizeof sMuseumInsectPoints27 / sizeof sMuseumInsectPoints27[0]; i++) MuseumInfoPoint_InitFromDef(&sMuseumInsectPoints27[i], &sMuseumInsectPointDefs27[i]);
    for (u32 i = 0; i < sizeof sMuseumInsectPoints28 / sizeof sMuseumInsectPoints28[0]; i++) MuseumInfoPoint_InitFromDef(&sMuseumInsectPoints28[i], &sMuseumInsectPointDefs28[i]);
    for (u32 i = 0; i < sizeof sMuseumPaintingPoints29 / sizeof sMuseumPaintingPoints29[0]; i++) MuseumInfoPoint_InitFromDef(&sMuseumPaintingPoints29[i], &sMuseumPaintingPointDefs29[i]);
}
const u8 data_ov004_02244108[1] = {0x1};
const u8 data_ov004_022441a4[7] = {0xc, 0xd, 0x1b, 0x1c, 0x1d, 0x36, 0x37};
const u8 data_ov004_022440d4[1] = {0x13};

MuseumInfoPoint::~MuseumInfoPoint() {}

extern "C" void MuseumInfoPoint_Init(Rec *r, V3 *pos, s32 mask, u32 b, s16 c, u8 *d, u8 e) {
    s32 sum; u32 i; s32 last; s32 cnt;
    r->pos.x = pos->x;
    r->pos.y = pos->y;
    r->pos.z = pos->z;
    r->kind = b;
    r->message = c;
    r->itemList = d;
    r->itemCount = e;
    sum = 0;
    cnt = sum;
    last = sum;
    i = sum;
    do {
        if (((mask >> i) & 1) != 0) {
            sum += i << 14;
            last = (s16)(i << 14);
            cnt++;
        }
        i++;
    } while (i < 4);
    r->angle = FX_Div(sum << 12, cnt << 12) >> 12;
    if (cnt == 2) {
        if (Math_AngleDiffAbs(last, r->angle) >= 0x4000) {
            r->angle = r->angle + 0x8000;
        }
    }
    last = 0;
    i = last;
    do {
        if (((mask >> i) & 1) != 0) {
            s32 t = Math_AngleDiffAbs((s32)(i << 30) >> 16, r->angle);
            if (t > last) {
                last = t;
            }
        }
        i++;
    } while (i < 4);
    r->arc = last + 0x1300;
}

extern "C" Rec *MuseumInfoPoint_InitFromDef(Rec *r, const MuseumInfoPointDef *d) {
    VecFx32Ctor v(d->pos.x, d->pos.y, d->pos.z);
    MuseumInfoPoint_Init(r, (V3 *)&v, d->facingMask, d->kind, d->message, (u8 *)d->itemList, d->itemCount);
    return r;
}

extern "C" V3 *MuseumInfoPoint_GetPos(Rec *r) { return &r->pos; }

extern "C" s16 MuseumInfoPoint_GetAngle(Rec *r) {
    return r->angle;
}

extern "C" s32 MuseumInfoPoint_GetArc(Rec *r) {
    return r->arc;
}

extern "C" u32 MuseumInfoPoint_GetKind(Rec *r) {
    return r->kind;
}

extern "C" s16 MuseumInfoPoint_GetMessage(Rec *r) {
    return r->message;
}

extern "C" u8 *MuseumInfoPoint_GetItemList(Rec *r) {
    return r->itemList;
}

extern "C" u32 MuseumInfoPoint_GetItemCount(Rec *r) {
    return r->itemCount;
}

extern "C" MuseumRoom *MuseumRoom_Create() {
    return new MuseumRoom;
}

MuseumRoom::MuseumRoom() {}

MuseumRoom::~MuseumRoom() {}

BOOL MuseumRoom::onCreate() {
    spawnInfoPoints();
    setupExhibits();
    return TRUE;
}

BOOL MuseumRoom::setupExhibits() {
    return TRUE;
}

BOOL MuseumRoom::onExecute() {
    return TRUE;
}

void MuseumRoom::spawnInfoPoints() {
    s32 k = Scene_GetCurrent();
    u32 i;
    for (i = 0; i < 7; i++) {
        const MuseumInfoPointSet *e = &sMuseumInfoPointsByScene[i];
        if (k == e->scene) {
            u32 j, n;
            j = 0;
            n = e->numPoints;
            for (; j < n; j++) {
                Rec *rec = &e->points[j];
                u32 a = MuseumInfoPoint_GetKind(rec);
                V3 *b = MuseumInfoPoint_GetPos(rec);
                s32 c = MuseumInfoPoint_GetAngle(rec);
                s32 d = MuseumInfoPoint_GetArc(rec);
                s32 f = MuseumInfoPoint_GetMessage(rec);
                u8 *g = MuseumInfoPoint_GetItemList(rec);
                MuseumExhibitInfo_Spawn(a, b, c, d, f, g, MuseumInfoPoint_GetItemCount(rec));
            }
            break;
        }
    }
}

extern "C" MuseumFossilRoom *MuseumFossilRoom_Create() {
    return new MuseumFossilRoom;
}

MuseumFossilRoom::MuseumFossilRoom() {}

MuseumFossilRoom::~MuseumFossilRoom() {}

ItemId MuseumFossilRoom_setupExhibits_sa;
u8 MuseumFossilRoom_setupExhibits_sa_init;
ItemId MuseumFossilRoom_setupExhibits_sb;
u8 MuseumFossilRoom_setupExhibits_sb_init;
BOOL MuseumFossilRoom::setupExhibits() {
    s32 y, x;
    BlockMap *m = gSceneBlockMap;
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            u16 *p = (u16 *)BlockMap_GetItemPtr(m, 0, 0, x, y, 0);
            if (p != NULL) {
                BOOL k = FALSE;
                if (*p >= 0x450c && *p <= 0x45db) {
                    k = TRUE;
                }
                if (k) {
                    BOOL k2 = FALSE;
                    if (data_021ed0a0.isDonated(p)) {
                        k2 = TRUE;
                    }
                    if (!k2) {
                        if (!MuseumFossilRoom_setupExhibits_sa_init) {
                            HOST_STATIC_INIT(MuseumFossilRoom_setupExhibits_sa, ItemId(0x4a54));
                            MuseumFossilRoom_setupExhibits_sa_init = 1;
                        }
                        if (!MuseumFossilRoom_setupExhibits_sb_init) {
                            HOST_STATIC_INIT(MuseumFossilRoom_setupExhibits_sb, ItemId(0xfff1));
                            MuseumFossilRoom_setupExhibits_sb_init = 1;
                        }
                        s32 w = Ftr_GetUnk05(p);
                        u16 v = 0xfff1;
                        if (w == 0) {
                            v = MuseumFossilRoom_setupExhibits_sa.id;
                        } else {
                            v = MuseumFossilRoom_setupExhibits_sb.id;
                        }
                        BlockMap_SetItem(m, &v, 0, 0, x, y, 0);
                    }
                }
            }
        }
    }
    return TRUE;
}

extern "C" MuseumRoomUnk53 *MuseumRoomUnk53_Create() {
    return new MuseumRoomUnk53;
}

MuseumRoomUnk53::MuseumRoomUnk53() {}

MuseumRoomUnk53::~MuseumRoomUnk53() {}

BOOL MuseumRoomUnk53::setupExhibits() {
    return TRUE;
}

const u8 data_ov004_022440f8[1] = {0x5};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0223db88) {
    HOST_OVERLAY_VAR(sMuseumFishPoints23),
    HOST_OVERLAY_VAR(sMuseumFishPoints24),
    HOST_OVERLAY_VAR(sMuseumFossilPoints25),
    HOST_OVERLAY_VAR(sMuseumFossilRoomProfile),
    HOST_OVERLAY_VAR(sMuseumFossilPoints26),
    HOST_OVERLAY_VAR(sMuseumRoomProfile),
    HOST_OVERLAY_VAR(sMuseumInsectPoints27),
    HOST_OVERLAY_VAR(sMuseumInsectPoints28),
    HOST_OVERLAY_VAR(sMuseumRoomUnk53Profile),
    HOST_OVERLAY_VAR(sMuseumPaintingPoints29),
    HOST_OVERLAY_VAR(MuseumFossilRoom_setupExhibits_sa),
    HOST_OVERLAY_VAR(MuseumFossilRoom_setupExhibits_sa_init),
    HOST_OVERLAY_VAR(MuseumFossilRoom_setupExhibits_sb),
    HOST_OVERLAY_VAR(MuseumFossilRoom_setupExhibits_sb_init),
    HOST_OVERLAY_VARS_END
};
