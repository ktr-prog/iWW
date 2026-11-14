// GPU rendering path for the Vita, via vitaGL (OpenGL ES over GXM).
//
// Goal: move the DS image onto the Vita GPU, the way the iOS/desktop builds use WebGPU/Metal. This file owns the
// vitaGL context and the GPU draw path, and is the default on the Vita (set ACWW_GL=0 to force the old SDL/GXM
// software-blit renderer instead).
//
// Stage 1 (now): vitaGL owns the display and presents the composited DS canvas as a GPU-textured, letterboxed
// quad - the full game image, drawn by the GPU, replacing the SDL renderer's CPU blit. The DS 3D is still
// software-rasterized into the canvas at this stage; stage 2 moves that geometry onto the GPU for the frame-rate
// win. The frontend uses SDL for input and audio only when this path is active (both vitaGL and SDL's renderer
// would init GXM, and only one may).

#include <stdlib.h>
#include <string.h>

#include <vitaGL.h>

#include "vita.h"

#define SCREEN_W 960
#define SCREEN_H 544

static int sOn = -1;   // -1 unknown, 0 off, 1 on
static int sReady;
static GLuint sTex;
static int sTexW, sTexH;   // currently-allocated texture size

// GPU is the default on the Vita. Only an explicit ACWW_GL=0 falls back to the SDL/GXM software-blit renderer.
int vita_gl_enabled(void) {
    if (sOn < 0) {
        const char *e = getenv("ACWW_GL");
        sOn = (e && atoi(e) == 0) ? 0 : 1;
    }
    return sOn;
}

// Bring up the GPU context. Returns 1 on success (the frontend falls back to the SDL renderer on 0).
int vita_gl_init(void) {
    if (!vita_gl_enabled()) return 0;
    // legacy pool != 0 so immediate mode (glBegin/glVertex) works for the fullscreen quad; a generous GXM
    // command/vertex budget that is tuned once real geometry flows through in stage 2.
    vglInitExtended(0x100000, SCREEN_W, SCREEN_H, 8 * 1024 * 1024, SCE_GXM_MULTISAMPLE_NONE);
    glViewport(0, 0, SCREEN_W, SCREEN_H);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    sReady = 1;
    return 1;
}

// Present one frame: upload the composited DS canvas (XRGB8888, i.e. B,G,R,X in memory == GL_BGRA bytes, a
// zero-conversion upload in vitaGL) and draw the sub-rectangle [sx,sy,sw,sh] of it, scaled to FIT the 960x544
// screen (letterbox, original 4:3 aspect kept, black bars at the sides).
void vita_gl_present_canvas(const void *pixels, int canvas_w, int canvas_h, int sx, int sy, int sw, int sh) {
    if (!sReady) return;

    if (!sTex) glGenTextures(1, &sTex);
    glBindTexture(GL_TEXTURE_2D, sTex);
    if (canvas_w != sTexW || canvas_h != sTexH) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, canvas_w, canvas_h, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        sTexW = canvas_w;
        sTexH = canvas_h;
    } else {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, canvas_w, canvas_h, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
    }

    // FIT: the larger scale that still fits both axes (letterbox, keep aspect)
    float scale = (float)SCREEN_W / sw;
    if ((float)SCREEN_H / sh < scale) scale = (float)SCREEN_H / sh;
    float dw = sw * scale, dh = sh * scale;
    float dx = (SCREEN_W - dw) * 0.5f, dy = (SCREEN_H - dh) * 0.5f;

    // texcoords for the source sub-rectangle
    float u0 = (float)sx / canvas_w, u1 = (float)(sx + sw) / canvas_w;
    float v0 = (float)sy / canvas_h, v1 = (float)(sy + sh) / canvas_h;

    // pixel-space orthographic projection, origin top-left (y down) to match the canvas's row order
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof(0.0f, SCREEN_W, SCREEN_H, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, sTex);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(u0, v0); glVertex2f(dx,      dy);
    glTexCoord2f(u1, v0); glVertex2f(dx + dw, dy);
    glTexCoord2f(u1, v1); glVertex2f(dx + dw, dy + dh);
    glTexCoord2f(u0, v1); glVertex2f(dx,      dy + dh);
    glEnd();

    vglSwapBuffers(GL_FALSE);
}

void vita_gl_shutdown(void) {
    // vitaGL has no teardown entry point - GXM and its pools are reclaimed when the process exits, which on the
    // Vita is the only way out of the game. Just mark the context down so present becomes a no-op.
    sReady = 0;
}
