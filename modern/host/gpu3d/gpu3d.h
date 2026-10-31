
#ifndef ACWW_GPU3D_H
#define ACWW_GPU3D_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void gpu3d_reset(void);
void gpu3d_write8(uint32_t addr, uint8_t value);
void gpu3d_write16(uint32_t addr, uint16_t value);
void gpu3d_write32(uint32_t addr, uint32_t value);
uint32_t gpu3d_read32(uint32_t addr);

void gpu3d_frame(const uint8_t *const bank[9]);
const uint32_t *gpu3d_lines(void);
int gpu3d_use_wgpu(void *device, void *queue, int scale, int readback);
void *gpu3d_wgpu_picture(void);

typedef struct Gpu3dPolyInfo {
    int index;
    uint32_t attr, texparam, texpal;
    int nverts;
    int x[10], y[10];
    int32_t z[10], w[10];
    int translucent;
} Gpu3dPolyInfo;
int gpu3d_pixel_polygon(int x, int y, Gpu3dPolyInfo *info);
void gpu3d_set_diagnostics(int on);
void gpu3d_print_features(void);

typedef struct Gpu3dVertexOut {
    int32_t x, y;
    int32_t z, w;
    int32_t r, g, b;
    int16_t s, t;
    int32_t clipped;
    int32_t clip[4];
} Gpu3dVertexOut;
int gpu3d_poly_count(void);
int gpu3d_poly_get(int i, Gpu3dVertexOut *v, uint32_t *attr, uint32_t *texparam, uint32_t *texpal, int *flags);

typedef struct Gpu3dState {
    uint32_t pipe, fifo, flush, npolys, nverts, mtxmode, possp, projsp;
    int32_t vp, np, pp, slots, slotctr;
    int32_t proj[16], pos[16], vec[16], tex[16];
    int16_t light[4][3];
    uint8_t lightColor[4][3], material[4][3];
    int16_t normal[3];
    uint8_t vtxColor[3];
} Gpu3dState;
void gpu3d_state(Gpu3dState *s);
void gpu3d_debug_history(void);
void gpu3d_debug_poly(int i);
int gpu3d_debug_last_polygon(int *nout, int *clipped, unsigned *serial, int *type);

#ifdef __cplusplus
}
#endif

#endif
