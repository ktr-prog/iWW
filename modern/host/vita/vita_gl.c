// GPU rendering path for the Vita, via vitaGL (OpenGL ES over GXM).
//
// Goal: move the DS 3D (and eventually the 2D composite) off the CPU software rasterizer and onto the Vita GPU,
// the way the iOS/desktop builds use WebGPU/Metal. This file owns the vitaGL context and the GPU draw path.
//
// Stage 1 (this commit): stand up vitaGL in the build and prove it initializes and presents on the device,
// without disturbing the working SDL path. It is OFF unless ACWW_GL=1 is set (acww-options.txt). When on, it
// initializes vitaGL and clears the screen to a solid colour each frame - a visible "GPU is alive" check before
// the DS geometry is wired onto it in stage 2. The frontend must NOT also create the SDL/GXM renderer in this
// mode (both would init GXM); vita_gl_enabled() lets frontend_sdl.c branch.

#include <stdlib.h>
#include <string.h>

#include <vitaGL.h>

#include "vita.h"

static int sOn = -1;   // -1 unknown, 0 off, 1 on
static int sReady;

int vita_gl_enabled(void) {
    if (sOn < 0) {
        const char *e = getenv("ACWW_GL");
        sOn = e && atoi(e) ? 1 : 0;
    }
    return sOn;
}

// Bring up the GPU context. Returns 1 on success. Call instead of creating the SDL renderer.
int vita_gl_init(void) {
    if (!vita_gl_enabled()) return 0;
    // a generous GXM command/vertex pool; tuned later once real geometry flows through
    vglInitExtended(0, 960, 544, 8 * 1024 * 1024, SCE_GXM_MULTISAMPLE_NONE);
    glClearDepthf(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glViewport(0, 0, 960, 544);
    sReady = 1;
    return 1;
}

// Present one frame. Stage 1: just clear + swap so we can confirm the GPU pipeline runs on hardware.
void vita_gl_present(void) {
    if (!sReady) return;
    glClearColor(0.1f, 0.4f, 0.1f, 1.0f);  // a calm green: "GPU path is live"
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    vglSwapBuffers(GL_FALSE);
}

void vita_gl_shutdown(void) {
    // vitaGL has no teardown entry point - GXM and its pools are reclaimed when the process exits, which on the
    // Vita is the only way out of the game. Just mark the context down so present() becomes a no-op.
    sReady = 0;
}
