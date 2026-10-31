#ifndef HOST_WGPU_DISPLAY_H
#define HOST_WGPU_DISPLAY_H

#include <stdint.h>

int wdisp_init(int software_ok);
void *wdisp_device(void);
void *wdisp_queue(void);
void wdisp_frame(const uint32_t *const deferred[2], const uint32_t *const lines[2], void *picture3d, int scale);
void wdisp_frame_2d(const void *gpuFrame, const uint8_t *const banks[9], const uint32_t *const lines[2],
                    void *picture3d, int scale);
int wdisp_read_2d(uint32_t *out);
const uint32_t *wdisp_screens(void);

enum { WDISP_X11 = 1, WDISP_WAYLAND = 2, WDISP_METAL = 3 };
int wdisp_attach(int kind, void *display, uint64_t window, int vsync);
int wdisp_presenting(void);
void wdisp_present(int w, int h);
void wdisp_overlay(const uint32_t *argb, int changed);
int wdisp_read_window(int w, int h, uint32_t *out);

static inline void wdisp_letterbox(int w, int h, float r[4]) {
    float s = (float)w / 256.0f < (float)h / 384.0f ? (float)w / 256.0f : (float)h / 384.0f;
    r[2] = 256.0f * s, r[3] = 384.0f * s;
    r[0] = ((float)w - r[2]) / 2.0f, r[1] = ((float)h - r[3]) / 2.0f;
}

#endif
