#ifndef NNSYS_G3D_RT_H
#define NNSYS_G3D_RT_H




typedef struct G3dAnmObj {
    int frame;
    int ratio;
    void *resAnm;
    void *funcAnm;
    struct G3dAnmObj *next;
    void *resTex;
    unsigned char priority;
    unsigned char numMapData;
    unsigned short mapData[1];
} G3dAnmObj;

typedef struct G3dRenderObj {
    unsigned int flag;
    void *resMdl;
    G3dAnmObj *anmMat;
    void *funcBlendMat;
    G3dAnmObj *anmJnt;
    void *funcBlendJnt;
    G3dAnmObj *anmVis;
    void *funcBlendVis;
    void *cbFunc;
    unsigned char cbCmd;
    unsigned char cbTiming;
    unsigned short dummy_;
    void *cbInitFunc;
    void *ptrUser;
    unsigned char *ptrUserSbc;
    void *recJntAnm;
    void *recMatAnm;
    unsigned int hintMatAnmExist[2];
    unsigned int hintJntAnmExist[2];
    unsigned int hintVisAnmExist[2];
} G3dRenderObj;

typedef struct G3dMatAnmResult {
    unsigned int flag;
    unsigned int prmMatColor0;
    unsigned int prmMatColor1;
    unsigned int prmPolygonAttr;
    unsigned int prmTexImage;
    unsigned int prmTexPltt;
    int scaleS, scaleT;
    short sinR, cosR;
    int transS, transT;
    unsigned short origWidth, origHeight;
    int magW, magH;
} G3dMatAnmResult;

typedef struct G3dJntAnmResult {
    unsigned int flag;
    int scale[3];
    int scaleEx0[3];
    int scaleEx1[3];
    int rot[9];
    int trans[3];
} G3dJntAnmResult;

typedef struct G3dVisAnmResult {
    int isVisible;
} G3dVisAnmResult;

typedef struct G3dRS {
    unsigned char *c;
    G3dRenderObj *pRenderObj;
    unsigned int flag;
    void (*cbVecFunc[32])(struct G3dRS *);
    unsigned char cbVecTiming[32];
    unsigned char currentNode;
    unsigned char currentMat;
    unsigned char currentNodeDesc;
    unsigned char dummy_;
    G3dMatAnmResult *pMatAnmResult;
    G3dJntAnmResult *pJntAnmResult;
    G3dVisAnmResult *pVisAnmResult;
    unsigned int isMatCached[2];
    unsigned int isScaleCacheOne[2];
    unsigned int isEnvCached[2];
    unsigned char *pResNodeInfo;
    unsigned char *pResMat;
    unsigned char *pResShp;
    int posScale;
    int invPosScale;
    void (*funcJntScale)(G3dJntAnmResult *, const int *, const unsigned char *, unsigned int);
    void (*funcJntMtx)(void *);
    void (*funcTexMtx)(void *);
    G3dMatAnmResult tmpMatAnmResult;
    G3dJntAnmResult tmpJntAnmResult;
    G3dVisAnmResult tmpVisAnmResult;
} G3dRS;

#define G3D_SBC_NODEDESC 6
#define G3D_SBC_BB 7
#define G3D_SBC_BBY 8
#define G3D_SBC_NODEMIX 10
#define G3D_SBC_ENVMAP 12

#define G3D_ANMOBJ_SIZE(n) ((unsigned int)((__builtin_offsetof(G3dAnmObj, mapData) + 2 * (n) + 3) & ~3u))

#endif
