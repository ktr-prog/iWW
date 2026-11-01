#ifndef GPU3D_INTERNAL_H
#define GPU3D_INTERNAL_H

#include "gpu3d.h"

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

enum { MAX_VERTICES = 6144 * 4, MAX_POLYGONS = 2048 * 4 };

typedef struct G3Vertex {
    s32 pos[4];
    s32 color[3];
    s16 tex[2];
    u8 clipped;
    u8 screenDone;
    s32 x, y;
    s32 hx, hy;
    int dbgLight;
    u8 farAxis;
    s32 farPos[4], farColor[3];
    u8 dbgClips;
    s32 dbgClip[8];
} G3Vertex;

typedef struct G3Polygon {
    G3Vertex *v[10];
    int nv;
    s32 z[10];
    s32 w[10];
    u32 attr, texparam, texpal;
    u8 wbuffer, facing, translucent, shadowMask, shadow, line, degenerate;
    int vtop, vbottom;
    s32 ytop, ybottom, xtop, xbottom;
    u32 sortKey;
    int index;
    int sub;
    s32 vp[6];
    s16 clipk, yofs;
    G3Vertex orig[4];
    int norig;
} G3Polygon;

typedef struct G3RenderState {
    G3Polygon *poly[MAX_POLYGONS];
    int npoly;
    int wbuffer, manualSort;
    u32 dispcnt;
    u16 clearColor, clearAttrHi;
    u16 clearDepth, clearOffset;
    u8 alphaRef;
    u16 toon[32];
    u16 edge[8];
    u32 fogColor;
    u16 fogOffset;
    u8 fogTable[32];
    int yofs;
    u32 serial;
} G3RenderState;

extern G3RenderState gG3Render;
extern const uint8_t *const *gG3Banks;
extern u8 gG3VramCnt[9];

void g3_render(void);
int g3_rebuild_polygon(G3Polygon *dst, const G3Polygon *src, const s32 (*pos)[4], G3Vertex *vbuf, int room);
const u32 *g3_frame_lines(void);
int g3_tall_supported(void);
int g3_frame_tall(void);
extern int gG3Yofs;
int g3_shown_yofs(void);
#define G3_YOFS (g3_tall_supported() ? gG3Yofs : 0)
enum { G3_MAX_ROWS = 640 };
int g3_raster_pixel_polygon(int x, int y);
void g3_raster_diagnostics(int on);

int g3w_init(void *device, void *queue, int scale);
void g3w_render(const G3RenderState *r, const u8 *img, const u8 *pal, u32 *out);
void *g3w_picture(void);

void g3_feature(int id);
enum {
    F_CMD = 0,
    F_POLYMODE = 0x80,
    F_TEXFMT = 0x84,
    F_TEXGEN = 0x8c,
    F_LIGHT = 0x90,
    F_SHININESS_TABLE,
    F_CLIP,
    F_FARCLIP_HIDE,
    F_CULLED,
    F_ONEDOT_HIDE,
    F_TRANSLUCENT,
    F_WIREFRAME,
    F_DEPTH_EQUAL,
    F_FOG_POLY,
    F_WBUFFER,
    F_ZBUFFER_POLYS,
    F_MANUAL_SORT,
    F_STACK_ERROR,
    F_RAM_OVERFLOW,
    F_FIFO_QUEUED,
    F_SWAP_QUEUED,
    F_FIFO_FULL,
    F_TEX_REPEAT,
    F_TEX_FLIP,
    F_TEX_CLAMP,
    F_COLOR0_TRANSPARENT,
    F_TRANS_DEPTH_UPDATE,
    F_LINE_POLY,
    F_TEXTURE_OFF,
    F_TOON_HIGHLIGHT,
    F_ALPHA_TEST,
    F_ALPHA_BLEND,
    F_ANTIALIAS,
    F_EDGE_MARK,
    F_FOG_ALPHA_ONLY,
    F_FOG,
    F_REAR_BITMAP,
    F_BOX_TEST, F_POS_TEST, F_VEC_TEST,
    F_READ_CLIPMTX, F_READ_VECMTX, F_READ_RAMCOUNT, F_READ_POSRESULT, F_READ_VECRESULT, F_READ_RDLINES,
    F_GEOM_OFF_WRITE,
    F_SHADOW_MASK, F_SHADOW,
    F_COUNT
};

#endif
