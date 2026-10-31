#pragma define_section DTCM ".dtcm" abs32 RWX

typedef unsigned int u32;
typedef signed int fx32;

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 m[4][4]; } MtxFx44;
typedef struct { fx32 m[4][3]; } MtxFx43;
typedef struct { fx32 m[3][3]; } MtxFx33;

typedef struct NNSG3dGlb {
    u32 cmd0;
    u32 mtxmode_proj;
    MtxFx44 projMtx;
    u32 mtxmode_posvec;
    MtxFx43 cameraMtx;
    u32 cmd1;
    u32 lightVec[4];
    u32 cmd2;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmViewPort;
    u32 cmd3;
    u32 lightColor[4];
    u32 cmd4;
    MtxFx33 prmBaseRot;
    VecFx32 prmBaseTrans;
    VecFx32 prmBaseScale;
    u32 prmTexImageParam;
    u32 flag;
    MtxFx43 invCameraMtx;
    MtxFx43 srtCameraMtx;
    MtxFx43 invSrtCameraMtx;
    MtxFx43 invBaseMtx;
    MtxFx44 invProjMtx;
    MtxFx44 invCameraProjMtx;
    VecFx32 camPos;
    VecFx32 camUp;
    VecFx32 camTarget;
} NNSG3dGlb;

#pragma section DTCM begin

NNSG3dGlb data_027e00c8;

#pragma section DTCM end

#include "host_labels.h"

HOST_LABEL_DEFINE(data_027e00d0, (char *)&data_027e00c8.projMtx.m[0]);
HOST_LABEL_DEFINE(data_027e0114, (char *)&data_027e00c8.cameraMtx.m[0]);
HOST_LABEL_DEFINE(data_027e0148, (char *)&data_027e00c8.lightVec[0]);
HOST_LABEL_DEFINE(data_027e0170, (char *)&data_027e00c8.lightColor[0]);
HOST_LABEL_DEFINE(data_027e0184, (char *)&data_027e00c8.prmBaseRot.m[0]);
HOST_LABEL_DEFINE(data_027e01a8, (char *)&data_027e00c8.prmBaseTrans.x);
HOST_LABEL_DEFINE(data_027e01c8, (char *)&data_027e00c8.invCameraMtx.m[0]);
HOST_LABEL_DEFINE(data_027e01f8, (char *)&data_027e00c8.srtCameraMtx.m[0]);
HOST_LABEL_DEFINE(data_027e0228, (char *)&data_027e00c8.invSrtCameraMtx.m[0]);
HOST_LABEL_DEFINE(data_027e02c8, (char *)&data_027e00c8.invCameraProjMtx.m[0]);
