#if HOST_FRONTEND_SDL

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_syswm.h>
#if defined(__APPLE__)
#include <SDL_metal.h>
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coro.h"
#include "frontend.h"
#include "frontend_ui.h"
#include "host.h"
#include "plat.h"
#include "render.h"
#include "savestate.h"
#include "host_features.h"
#include "wgpu_display.h"

#if HOST_IOS
#include "ios/ios.h"
#include "ios/touch_controls.h"
static TcLayout sLayout;
static TcState sTouch;
static int sShowControls = 1;
static SDL_Texture *sButtonTex[TC_COUNT][16];
static int sButtonW[TC_COUNT], sButtonH[TC_COUNT];
static SDL_Texture *sStickBase, *sStickKnob[2];
static int sStickW;
static SDL_Texture *sSharp;
static int sSharpK;
static volatile int sInBackground;
static float sPt = 1;
#endif

static AcwwShm *sShm;
static SDL_Window *sWin;
static SDL_Renderer *sRen;
static SDL_Texture *sTex, *sOverlayTex;
static int sGpu;
static SDL_AudioDeviceID sDev;
static int sScale = 2, sMute;
static SDL_GameController *sPads[4];

#define AUDIO_TARGET 2200.0
static unsigned sDry, sSkips, sCalls;
static double sLevelSum;
static void audio_callback(void *user, Uint8 *stream, int len) {
    AcwwShm *shm = user;
    int16_t *out = (int16_t *)stream;
    uint32_t want = (uint32_t)len / 4, w = __atomic_load_n(&shm->audio_write, __ATOMIC_ACQUIRE);
    static uint32_t r;
    static double frac;
    static int primed, init;
    if (!init) { init = 1; r = w; }
    double target = AUDIO_TARGET + want;
    uint32_t level = w - r;
    if (level > ACWW_AUDIO_FRAMES / 2 || level > 4 * target) {
        if (primed) sSkips++;
        r = w - (uint32_t)target;
        level = (uint32_t)target;
    }
    sLevelSum += level;
    sCalls++;
    if (!primed && level >= target / 2 + want) primed = 1;
    double err = (level - target) / target;
    double ratio = 1.0 + 0.005 * (err < -1 ? -1 : err > 1 ? 1 : err);
    int mute = __atomic_load_n(&sMute, __ATOMIC_RELAXED);
    uint32_t i = 0;
    for (; primed && i < want; i++) {
        if (w - r < 2) { primed = 0; sDry++; break; }
        const int16_t *a = &shm->audio[(r % ACWW_AUDIO_FRAMES) * 2], *b = &shm->audio[((r + 1) % ACWW_AUDIO_FRAMES) * 2];
        out[i * 2] = mute ? 0 : (int16_t)(a[0] + (b[0] - a[0]) * frac);
        out[i * 2 + 1] = mute ? 0 : (int16_t)(a[1] + (b[1] - a[1]) * frac);
        frac += ratio;
        while (frac >= 1.0) { frac -= 1.0; r++; }
    }
    memset(out + i * 2, 0, (want - i) * 4);
    __atomic_store_n(&shm->audio_read, r, __ATOMIC_RELEASE);
}

#if defined(__APPLE__)
static SDL_MetalView sMetalView;
#endif

static void sdl_quit(void) {
    if (getenv("ACWW_AUDIO_INFO") && sCalls)
        fprintf(stderr, "frontend: sound: %u underruns, %u skips, mean queue %.0f frames\n", sDry, sSkips,
                sLevelSum / sCalls);
    if (sDev) SDL_CloseAudioDevice(sDev);
    sDev = 0;
#if defined(__APPLE__)
    if (sMetalView) SDL_Metal_DestroyView(sMetalView);
    sMetalView = 0;
#endif
    SDL_Quit();
}

static void open_audio(void) {
    if (getenv("ACWW_MUTE") || SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) return;
    SDL_AudioSpec want, have;
    memset(&want, 0, sizeof want);
    want.freq = ACWW_AUDIO_RATE;
    want.format = AUDIO_S16SYS;
    want.channels = 2;
    want.samples = getenv("ACWW_AUDIO_SAMPLES") ? (Uint16)atoi(getenv("ACWW_AUDIO_SAMPLES")) : 512;
    want.callback = audio_callback;
    want.userdata = sShm;
    sDev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (!sDev) { fprintf(stderr, "frontend: no sound: %s\n", SDL_GetError()); return; }
#if HOST_IOS
    if (1)
#else
    if (getenv("ACWW_AUDIO_INFO"))
#endif
        fprintf(stderr, "frontend: sound %d Hz, format %04x, %d channels, %d frames (%s)\n", have.freq, have.format,
                have.channels, have.samples, SDL_GetCurrentAudioDriver());
    SDL_PauseAudioDevice(sDev, 0);
}

enum { FE_STACK = 8 * 1024 * 1024 };
static void *sGameSp;
static void frame_body(void);
#if !HOST_IOS
static void *sFeSp;
static void fe_main(void *arg) {
    (void)arg;
    for (;;) {
        frame_body();
        host_coro_switch(&sFeSp, sGameSp);
    }
}
#else
extern void *gHostMainSp;
void frontend_backend_main_loop(void) {
    for (;;) {
        frame_body();
        host_coro_switch(&gHostMainSp, sGameSp);
    }
}

static int SDLCALL app_events(void *user, SDL_Event *e) {
    (void)user;
    if (e->type == SDL_APP_WILLENTERBACKGROUND || e->type == SDL_APP_DIDENTERBACKGROUND) sInBackground = 1;
    if (e->type == SDL_APP_DIDENTERFOREGROUND) sInBackground = 0;
    return 1;
}
#endif

AcwwShm *frontend_backend_open(const char *argv0) {
    (void)argv0;
    SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");
    SDL_SetHint(SDL_HINT_GAMECONTROLLER_USE_BUTTON_LABELS, "0");
    SDL_SetHint(SDL_HINT_APP_NAME, "iWW");
#if HOST_IOS
    SDL_SetHint(SDL_HINT_ORIENTATIONS, "Portrait PortraitUpsideDown");
    SDL_SetHint(SDL_HINT_IOS_HIDE_HOME_INDICATOR, "1");
    SDL_SetHint(SDL_HINT_IDLE_TIMER_DISABLED, "1");
    SDL_SetHint(SDL_HINT_ACCELEROMETER_AS_JOYSTICK, "0");
    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI, "0");
    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
    SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "0");
#endif
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        fprintf(stderr, "frontend: no window (%s): running headless\n", SDL_GetError());
        return 0;
    }
    sShm = calloc(1, sizeof *sShm);
#if HOST_IOS
    void *stack = sShm;
    SDL_SetEventFilter(app_events, NULL);
    tc_reset(&sTouch);
#else
    void *stack = host_plat_stack_alloc(FE_STACK, 0);
    host_state_untrack(stack);
#endif
    if (!sShm || !stack) { fprintf(stderr, "frontend: no memory\n"); SDL_Quit(); free(sShm); return sShm = 0; }
    sShm->magic = ACWW_SHM_MAGIC;
#if !HOST_IOS
    sFeSp = host_coro_prepare(stack, FE_STACK, fe_main, 0);
#endif
    sWin = SDL_CreateWindow("iWW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            256 * sScale, 384 * sScale, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
#if HOST_IOS
                            | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS
#elif defined(__APPLE__)
                            | (render_on_gpu() ? SDL_WINDOW_METAL : 0)
#endif
                            );
    int vsync = getenv("ACWW_VSYNC") && atoi(getenv("ACWW_VSYNC"));
    if (sWin && render_on_gpu()) {
#if defined(__APPLE__)
        if ((sMetalView = SDL_Metal_CreateView(sWin)))
            sGpu = wdisp_attach(WDISP_METAL, SDL_Metal_GetLayer(sMetalView), 0, vsync);
#endif
        SDL_SysWMinfo wm;
        SDL_VERSION(&wm.version);
        if (!sGpu && SDL_GetWindowWMInfo(sWin, &wm)) {
#if defined(SDL_VIDEO_DRIVER_X11)
            if (wm.subsystem == SDL_SYSWM_X11)
                sGpu = wdisp_attach(WDISP_X11, wm.info.x11.display, wm.info.x11.window, vsync);
#endif
#if defined(SDL_VIDEO_DRIVER_WAYLAND)
            if (wm.subsystem == SDL_SYSWM_WAYLAND)
                sGpu = wdisp_attach(WDISP_WAYLAND, wm.info.wl.display, (uintptr_t)wm.info.wl.surface, vsync);
#endif
        }
        if (!sGpu) fprintf(stderr, "frontend: the GPU can't draw into the window: the screens are read back\n");
    }
    if (sWin && !sGpu) {
        sRen = SDL_CreateRenderer(sWin, -1, vsync ? SDL_RENDERER_PRESENTVSYNC : 0);
        if (!sRen) sRen = SDL_CreateRenderer(sWin, -1, SDL_RENDERER_SOFTWARE);
    }
    if (sRen) {
#if HOST_IOS
        sTex = SDL_CreateTexture(sRen, SDL_PIXELFORMAT_XRGB8888, SDL_TEXTUREACCESS_STREAMING, 256, 384);
        if (sTex) SDL_SetTextureScaleMode(sTex, SDL_ScaleModeNearest);
#else
        SDL_RenderSetLogicalSize(sRen, 256, 384);
        sTex = SDL_CreateTexture(sRen, SDL_PIXELFORMAT_XRGB8888, SDL_TEXTUREACCESS_STREAMING, 256, 384);
#endif
    }
    if (!sTex && !sGpu) {
        fprintf(stderr, "frontend: no window (%s): running headless\n", SDL_GetError());
        SDL_Quit();
        free(sShm);
        return sShm = 0;
    }
    ui_init();
    {
#if HOST_IOS
        features_init("acww-settings.txt");
#else
        char *dir = SDL_GetPrefPath("", "acww");
        char path[1024];
        snprintf(path, sizeof path, "%ssettings.txt", dir ? dir : "");
        SDL_free(dir);
        features_init(path);
#endif
    }
    open_audio();
    atexit(sdl_quit);
    if (getenv("ACWW_BUILD_LABEL")) ui_toast(getenv("ACWW_BUILD_LABEL"));
    return sShm;
}

void frontend_backend_frame(AcwwShm *shm) {
    (void)shm;
#if HOST_IOS
    host_coro_switch(&sGameSp, gHostMainSp);
#else
    host_coro_switch(&sGameSp, sFeSp);
#endif
}

void frontend_backend_close(void) {}

static uint32_t keyboard_keys(void) {
    static Uint8 st[SDL_NUM_SCANCODES];
    int n;
    const Uint8 *now = SDL_GetKeyboardState(&n);
    memcpy(st, now, (size_t)(n < SDL_NUM_SCANCODES ? n : SDL_NUM_SCANCODES));
    if (SDL_GetModState() & KMOD_ALT) st[SDL_SCANCODE_RETURN] = 0;
    return ui_keyboard_keys(st);
}

static uint32_t pad_keys(void) {
    enum { DEAD = 16000 };
    uint32_t k = 0;
    for (int p = 0; p < 4; p++) {
        SDL_GameController *c = sPads[p];
        if (!c) continue;
        k |= ui_pad_keys(c);
        int x = SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTX), y = SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTY);
        if (x > DEAD) k |= 1u << 4;
        if (x < -DEAD) k |= 1u << 5;
        if (y < -DEAD) k |= 1u << 6;
        if (y > DEAD) k |= 1u << 7;
        if (SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > DEAD) k |= 1u << 8;
        if (SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_TRIGGERLEFT) > DEAD) k |= 1u << 9;
    }
    return k;
}

static uint32_t stick_word(void) {
    if (!feature_on(FEAT_CIRCLE_PAD)) return 0;
    float x = 0, y = 0;
    int got = 0;
#if HOST_IOS
    got = tc_stick(&sTouch, &x, &y);
#endif
    for (int p = 0; p < 4 && !got; p++) {
        SDL_GameController *c = sPads[p];
        if (!c) continue;
        float ax = SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f;
        float ay = -SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTY) / 32767.0f;
        float m = sqrtf(ax * ax + ay * ay);
        const float dead = 0.15f;
        if (m <= dead) continue;
        float k = (m > 1 ? 1 : m);
        k = (k - dead) / (1 - dead) / m;
        x = ax * k, y = ay * k, got = 1;
    }
    int ix = (int)lrintf(x * 105), iy = (int)lrintf(y * 105);
    ix = ix < -127 ? -127 : ix > 127 ? 127 : ix;
    iy = iy < -127 ? -127 : iy > 127 ? 127 : iy;
    return (uint32_t)(ix & 0xff) | (uint32_t)(iy & 0xff) << 8 | 1u << 16;
}

static void pad_added(int index) {
    for (int p = 0; p < 4; p++) {
        if (sPads[p]) continue;
        sPads[p] = SDL_GameControllerOpen(index);
        if (sPads[p])
            fprintf(stderr, "frontend: controller %s\n", SDL_GameControllerName(sPads[p]));
#if HOST_IOS
        if (sPads[p]) sShowControls = 0;
#endif
        return;
    }
}

static void pad_removed(SDL_JoystickID id) {
    for (int p = 0; p < 4; p++) {
        if (sPads[p] && SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(sPads[p])) == id) {
            SDL_GameControllerClose(sPads[p]);
            sPads[p] = 0;
        }
    }
#if HOST_IOS
    int any = 0;
    for (int p = 0; p < 4; p++) any |= sPads[p] != 0;
    if (!any) sShowControls = 1;
#endif
}

static struct { int held, x, y; } sMouse, sFinger;
static SDL_FingerID sFingerId;
static void window_to_logical(int wx, int wy, int *x, int *y) {
    if (!sGpu) { *x = wx, *y = wy; return; }
    int w, h;
    float r[4];
    SDL_GetWindowSize(sWin, &w, &h);
    wdisp_letterbox(w, h, r);
    *x = (int)SDL_floorf(((float)wx - r[0]) * 256.0f / r[2]);
    *y = (int)SDL_floorf(((float)wy - r[1]) * 384.0f / r[3]);
}
static void finger_to_logical(float fx, float fy, int *x, int *y) {
    int w, h;
    SDL_GetWindowSize(sWin, &w, &h);
    if (sGpu) { window_to_logical((int)(fx * w), (int)(fy * h), x, y); return; }
    float lx, ly;
    SDL_RenderWindowToLogical(sRen, (int)(fx * w), (int)(fy * h), &lx, &ly);
    *x = (int)lx;
    *y = (int)ly;
}
static struct { int x, y; } sTapQ[32];
static int sTapHead, sTapCount;
static int sRawDown, sRawX, sRawY;
static unsigned sRawPresses;
static unsigned sPressId, sCurId;
static int sCurDown, sCurX, sCurY;
static unsigned long long sCurUntil, sUpAt;
static unsigned long long sVblank, sCurVb, sUpVb;
enum { TOUCH_VB_LIMIT = 6 };
static int sSawDown, sSawUp = 1;
void frontend_backend_touch_read(int held) {
    if (held && sCurDown) sSawDown = 1;
    if (!held && !sCurDown) sSawUp = 1;
}
static int raw_touch(int *x, int *y, unsigned *presses) {
#if HOST_IOS
    *presses = tc_stylus_presses(&sTouch);
    return tc_stylus(&sTouch, x, y);
#else
    *presses = sRawPresses;
    int held = sFinger.held || sMouse.held;
    *x = sFinger.held ? sFinger.x : sMouse.x, *y = (sFinger.held ? sFinger.y : sMouse.y) - 192;
    if (held && *y < 0 && sRawDown) *x = sRawX, *y = sRawY;
    else if (held && *y < 0) return 0;
    return held && *x >= 0 && *x < 256 && *y < 192;
#endif
}
static void touch_sample(void) {
    unsigned presses;
    int x, y, down = raw_touch(&x, &y, &presses);
    if (down && (!sRawDown || presses != sRawPresses)) {
        sPressId++;
        if (sTapCount < 32) {
            sTapQ[(sTapHead + sTapCount) % 32].x = x, sTapQ[(sTapHead + sTapCount) % 32].y = y;
            sTapCount++;
        }
    }
    if (down) sRawX = x, sRawY = y;
    sRawDown = down;
    sRawPresses = presses;
}
static void touch_show_next(int atTurnEnd) {
    unsigned long long now = gHostGameFrames;
    (void)now;
    if (sCurDown || !sTapCount || (!sSawUp && sVblank - sUpVb < TOUCH_VB_LIMIT)) return;
    sCurX = sTapQ[sTapHead].x, sCurY = sTapQ[sTapHead].y;
    sTapHead = (sTapHead + 1) % 32, sTapCount--;
    sCurId = sPressId - (unsigned)sTapCount;
    sCurDown = 1, sCurUntil = atTurnEnd ? now : now + 1, sCurVb = sVblank;
    sSawDown = 0;
}
static int touch_live(void) {
    return sCurDown && sCurId == sPressId && sRawDown && !sTapCount;
}
static void touch_publish(void) {
    sVblank++;
    if (sCurDown && !touch_live() && sVblank - sCurVb >= TOUCH_VB_LIMIT)
        sCurDown = 0, sUpAt = gHostGameFrames, sUpVb = sVblank, sSawUp = 0;
    touch_show_next(0);
    if (touch_live()) sCurX = sRawX, sCurY = sRawY;
    if (sCurDown) sShm->touch_x = sCurX, sShm->touch_y = sCurY;
    sShm->touch_down = sCurDown;
}
void frontend_backend_turn(void) {
    if (!sShm) return;
    unsigned long long now = gHostGameFrames;
    (void)sCurUntil;
    if (sCurDown && !touch_live() && sSawDown) sCurDown = 0, sUpAt = now, sUpVb = sVblank, sSawUp = 0;
    touch_show_next(1);
    if (sCurDown) sShm->touch_x = sCurX, sShm->touch_y = sCurY;
    sShm->touch_down = sCurDown;
}
static void update_touch(void) {
    touch_sample();
#if HOST_IOS
    int tx = sCurX, ty = sCurY, was = sShm->touch_down != 0;
    touch_publish();
    tx = sShm->touch_x, ty = sShm->touch_y;
    static int logged, logOn = -1;
    if (logOn < 0) logOn = !getenv("ACWW_TOUCH_LOG") || atoi(getenv("ACWW_TOUCH_LOG")) != 0;
    if (logOn && was != (sShm->touch_down != 0) && logged < 200) {
        logged++;
        if (sShm->touch_down) fprintf(stderr, "touch: down at %d,%d (frame %llu)\n", tx, ty, (unsigned long long)host_frame());
        else fprintf(stderr, "touch: up (frame %llu)\n", (unsigned long long)host_frame());
    }
    return;
#endif
    touch_publish();
}

static void handle_event(const SDL_Event *e);
static void handle(const SDL_Event *e) {
    handle_event(e);
    touch_sample();
}
static void handle_event(const SDL_Event *e) {
    if (e->type == SDL_QUIT) { sShm->quit = 1; return; }
    if (e->type == SDL_CONTROLLERDEVICEADDED) { pad_added(e->cdevice.which); return; }
    if (e->type == SDL_CONTROLLERDEVICEREMOVED) { pad_removed(e->cdevice.which); return; }
#if HOST_IOS
    if (ui_is_open() && (e->type == SDL_FINGERDOWN || (e->type == SDL_MOUSEBUTTONDOWN && e->button.which != SDL_TOUCH_MOUSEID))) {
        float px = e->type == SDL_FINGERDOWN ? e->tfinger.x * (float)sLayout.w : (float)e->button.x * sPt;
        float py = e->type == SDL_FINGERDOWN ? e->tfinger.y * (float)sLayout.h : (float)e->button.y * sPt;
        TcRect sc = sLayout.screens;
        if (sc.w > 0 && sc.h > 0) ui_tap((int)((px - sc.x) * 256 / sc.w), (int)((py - sc.y) * 384 / sc.h));
        tc_reset(&sTouch);
        return;
    }
#endif
    if (ui_event(e)) {
        sMouse.held = sFinger.held = 0;
#if HOST_IOS
        tc_reset(&sTouch);
#endif
        return;
    }
#if HOST_IOS
    switch (e->type) {
    case SDL_FINGERDOWN:
    case SDL_FINGERMOTION:
    case SDL_FINGERUP: {
        int ev = e->type == SDL_FINGERDOWN ? TC_DOWN : e->type == SDL_FINGERUP ? TC_UP : TC_MOVE;
        if (tc_pointer(&sTouch, &sLayout, (int64_t)e->tfinger.fingerId, ev, e->tfinger.x * (float)sLayout.w,
                       e->tfinger.y * (float)sLayout.h))
            sShowControls = 1;
        touch_sample();
        return;
    }
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        if (e->button.which == SDL_TOUCH_MOUSEID || e->button.button != SDL_BUTTON_LEFT) return;
        if (tc_pointer(&sTouch, &sLayout, -1000, e->type == SDL_MOUSEBUTTONDOWN ? TC_DOWN : TC_UP,
                       (float)e->button.x * sPt, (float)e->button.y * sPt))
            sShowControls = 1;
        touch_sample();
        return;
    case SDL_MOUSEMOTION:
        if (e->motion.which == SDL_TOUCH_MOUSEID) return;
        tc_pointer(&sTouch, &sLayout, -1000, TC_MOVE, (float)e->motion.x * sPt, (float)e->motion.y * sPt);
        return;
    default: break;
    }
#endif
    switch (e->type) {
    case SDL_KEYDOWN:
        if (e->key.repeat) break;
        if (e->key.keysym.scancode == SDL_SCANCODE_F11) {
            sScale = sScale % 3 + 1;
            SDL_SetWindowFullscreen(sWin, 0);
            SDL_SetWindowSize(sWin, 256 * sScale, 384 * sScale);
        } else if (e->key.keysym.scancode == SDL_SCANCODE_RETURN && (e->key.keysym.mod & KMOD_ALT)) {
            int full = (SDL_GetWindowFlags(sWin) & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
            SDL_SetWindowFullscreen(sWin, full ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
        } else if (e->key.keysym.scancode == SDL_SCANCODE_M && !ui_key_bound(SDL_SCANCODE_M)) {
            __atomic_store_n(&sMute, !sMute, __ATOMIC_RELAXED);
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        if (e->button.which == SDL_TOUCH_MOUSEID || e->button.button != SDL_BUTTON_LEFT) break;
        sMouse.held = e->type == SDL_MOUSEBUTTONDOWN;
        window_to_logical(e->button.x, e->button.y, &sMouse.x, &sMouse.y);
        break;
    case SDL_MOUSEMOTION:
        if (e->motion.which == SDL_TOUCH_MOUSEID) break;
        sMouse.held = (e->motion.state & SDL_BUTTON_LMASK) != 0;
        window_to_logical(e->motion.x, e->motion.y, &sMouse.x, &sMouse.y);
        break;
    case SDL_FINGERDOWN:
        if (sFinger.held) break;
        sFingerId = e->tfinger.fingerId;
        sFinger.held = 1;
        finger_to_logical(e->tfinger.x, e->tfinger.y, &sFinger.x, &sFinger.y);
        break;
    case SDL_FINGERMOTION:
        if (sFinger.held && e->tfinger.fingerId == sFingerId)
            finger_to_logical(e->tfinger.x, e->tfinger.y, &sFinger.x, &sFinger.y);
        break;
    case SDL_FINGERUP:
        if (sFinger.held && e->tfinger.fingerId == sFingerId) sFinger.held = 0;
        break;
    default: break;
    }
}

static void write_ppm(const char *path, const uint32_t *px, int w, int h) {
    FILE *o = fopen(path, "wb");
    if (!o) return;
    fprintf(o, "P6\n%d %d\n255\n", w, h);
    for (int i = 0; i < w * h; i++) {
        unsigned char rgb[3] = {(unsigned char)(px[i] >> 16), (unsigned char)(px[i] >> 8), (unsigned char)px[i]};
        fwrite(rgb, 1, 3, o);
    }
    fclose(o);
}
static void shot(const char *path) {
    int w, h;
    if (sGpu) {
        SDL_GetWindowSizeInPixels(sWin, &w, &h);
        uint32_t *px = malloc((size_t)w * h * 4);
        if (px && wdisp_read_window(w, h, px)) write_ppm(path, px, w, h);
        free(px);
        return;
    }
    SDL_GetRendererOutputSize(sRen, &w, &h);
    uint32_t *px = malloc((size_t)w * h * 4);
    SDL_RenderSetLogicalSize(sRen, 0, 0);
    SDL_RenderSetViewport(sRen, 0);
    if (px && SDL_RenderReadPixels(sRen, 0, SDL_PIXELFORMAT_XRGB8888, px, w * 4) == 0) write_ppm(path, px, w, h);
    else fprintf(stderr, "frontend: ACWW_WINSHOT: %s\n", SDL_GetError());
#if !HOST_IOS
    SDL_RenderSetLogicalSize(sRen, 256, 384);
#endif
    free(px);
}
static void window_shot(void) {
    static const char *spec;
    if (!spec) spec = getenv("ACWW_WINSHOT") ? getenv("ACWW_WINSHOT") : "";
    unsigned f = (unsigned)host_frame();
    for (const char *p = spec; *p;) {
        unsigned fr;
        char path[512];
        if (sscanf(p, "%u:%511[^;]", &fr, path) == 2 && fr == f) shot(path);
        p = strchr(p, ';');
        if (!p) break;
        p++;
    }
}

static char sPendingShot[512];
static void script_step(void) {
    static const char *spec, *next;
    if (!spec) spec = getenv("ACWW_UI_SCRIPT") ? getenv("ACWW_UI_SCRIPT") : "";
    if (!next) {
        unsigned f = (unsigned)host_frame();
        for (const char *p = spec; *p;) {
            unsigned fr;
            int n = 0;
            if (sscanf(p, "%u:%n", &fr, &n) == 1 && n && fr == f) next = p + n;
            p = strchr(p, ';');
            if (!p) break;
            p++;
        }
        if (!next) return;
    }
    char item[512];
    size_t len = strcspn(next, ",;");
    snprintf(item, sizeof item, "%.*s", (int)(len < sizeof item ? len : sizeof item - 1), next);
    next = next[len] == ',' ? next + len + 1 : NULL;
    SDL_Event e;
    memset(&e, 0, sizeof e);
    if (!strncmp(item, "wait:", 5)) {
        SDL_Delay((Uint32)atoi(item + 5));
    } else if (!strcmp(item, "quit")) {
        e.type = SDL_QUIT;
        handle(&e);
    } else if (!strncmp(item, "shot:", 5)) {
        snprintf(sPendingShot, sizeof sPendingShot, "%s", item + 5);
    } else if (!strncmp(item, "pad:", 4)) {
        e.type = SDL_CONTROLLERBUTTONDOWN;
        e.cbutton.which = -1;
        e.cbutton.button = (Uint8)SDL_GameControllerGetButtonFromString(item + 4);
        handle(&e);
        e.type = SDL_CONTROLLERBUTTONUP;
        handle(&e);
    } else {
        e.type = SDL_KEYDOWN;
        e.key.keysym.scancode = SDL_GetScancodeFromName(item);
        handle(&e);
        e.type = SDL_KEYUP;
        handle(&e);
    }
}

#if HOST_IOS
static void ios_layout(void) {
    int ow = 0, oh = 0, ww = 0, wh = 0;
    if (SDL_GetRendererOutputSize(sRen, &ow, &oh) != 0 || ow <= 0 || oh <= 0) return;
    SDL_GetWindowSize(sWin, &ww, &wh);
    sPt = ww > 0 ? (float)ow / (float)ww : 1;
    float in[4];
    ios_safe_area(sWin, in);
    for (int i = 0; i < 4; i++) in[i] *= sPt;
    int changed = ow != sLayout.w || oh != sLayout.h || sShowControls != sLayout.controls;
    if (changed) tc_reset(&sTouch);
    tc_layout(&sLayout, ow, oh, sPt, in, sShowControls);
    sLayout.stick = 1;
    {
        extern int gHostCanvasRows;
        gHostCanvasRows = tc_canvas_rows(&sLayout);
    }
    if (changed)
        fprintf(stderr, "frontend: window %dx%d px (%.0fx scale), safe area %.0f,%.0f,%.0f,%.0f px, screens %.0f,%.0f %.0fx%.0f, "
                "buttons %s\n", ow, oh, sPt, in[0], in[1], in[2], in[3], sLayout.screens.x, sLayout.screens.y,
                sLayout.screens.w, sLayout.screens.h, sLayout.controls ? "on" : "off");
}

static void ios_stats(void) {
    static int on = -1;
    static uint64_t t0;
    static unsigned frames, dry0, skips0, calls0;
    static double level0;
    if (on < 0) on = !getenv("ACWW_STATS") || atoi(getenv("ACWW_STATS")) != 0;
    if (!on) return;
    uint64_t now = host_plat_time_ns();
    if (!t0) { t0 = now; dry0 = sDry, skips0 = sSkips, calls0 = sCalls, level0 = sLevelSum; return; }
    if (++frames < 600) return;
    double secs = (double)(now - t0) / 1e9;
    unsigned calls = sCalls - calls0;
    int pads = 0;
    for (int p = 0; p < 4; p++) pads += sPads[p] != 0;
    fprintf(stderr, "stats: frame %llu: %.1f frames/s, sound %u dry, %u skips, queue %.0f frames; %s, %d controller(s)\n",
            (unsigned long long)host_frame(), frames / secs, sDry - dry0, sSkips - skips0,
            calls ? (sLevelSum - level0) / calls : 0.0, sLayout.controls ? "buttons" : "no buttons", pads);
    t0 = now, frames = 0, dry0 = sDry, skips0 = sSkips, calls0 = sCalls, level0 = sLevelSum;
}

static SDL_Texture *control_texture(int w, int h, uint32_t *px) {
    SDL_Texture *t = SDL_CreateTexture(sRen, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);
    if (t) {
        SDL_UpdateTexture(t, 0, px, w * 4);
        SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
        SDL_SetTextureScaleMode(t, SDL_ScaleModeNearest);
    }
    return t;
}
static int sCtlAlpha = 255;
static void ios_draw_stick(void) {
    float ccx, ccy;
    if (!tc_stick_center(&sTouch, &ccx, &ccy)) return;
    float size = sLayout.stick_size;
    int w = (int)(size + 0.5f), kw = (int)(size * TC_KNOB + 0.5f);
    if (w <= 0 || kw <= 0) return;
    if (w != sStickW) {
        if (sStickBase) SDL_DestroyTexture(sStickBase);
        for (int i = 0; i < 2; i++)
            if (sStickKnob[i]) SDL_DestroyTexture(sStickKnob[i]);
        sStickBase = sStickKnob[0] = sStickKnob[1] = 0;
        sStickW = w;
        uint32_t *px = malloc((size_t)w * (size_t)w * 4);
        if (!px) return;
        tc_draw_stick_base(px, w, w);
        sStickBase = control_texture(w, w, px);
        for (int i = 0; i < 2; i++) {
            tc_draw_stick_knob(px, kw, kw, i);
            sStickKnob[i] = control_texture(kw, kw, px);
        }
        free(px);
    }
    float sx, sy;
    int held = tc_stick(&sTouch, &sx, &sy);
    SDL_Rect dst = {(int)(ccx - w / 2.0f + 0.5f), (int)(ccy - w / 2.0f + 0.5f), w, w};
    if (sStickBase) SDL_SetTextureAlphaMod(sStickBase, (Uint8)sCtlAlpha), SDL_RenderCopy(sRen, sStickBase, 0, &dst);
    float cx = ccx + sx * size * TC_KNOB_TRAVEL, cy = ccy - sy * size * TC_KNOB_TRAVEL;
    SDL_Rect k = {(int)(cx - kw / 2.0f + 0.5f), (int)(cy - kw / 2.0f + 0.5f), kw, kw};
    if (sStickKnob[held]) SDL_SetTextureAlphaMod(sStickKnob[held], (Uint8)sCtlAlpha), SDL_RenderCopy(sRen, sStickKnob[held], 0, &k);
}

static void ios_draw_controls(void) {
    uint32_t held = tc_held(&sTouch), dirs = tc_dpad_dirs(&sTouch);
    for (int b = 0; b < TC_COUNT; b++) {
        TcRect r = sLayout.button[b];
        int w = (int)(r.w + 0.5f), h = (int)(r.h + 0.5f);
        if (w <= 0 || h <= 0) continue;
        if (b == TC_DPAD) {
            ios_draw_stick();
            continue;
        }
        if (w != sButtonW[b] || h != sButtonH[b]) {
            for (int v = 0; v < 16; v++) {
                if (sButtonTex[b][v]) SDL_DestroyTexture(sButtonTex[b][v]);
                sButtonTex[b][v] = 0;
            }
            sButtonW[b] = w, sButtonH[b] = h;
        }
        int v = b == TC_DPAD ? (int)(dirs >> 4 & 15) : (int)(held >> b & 1);
        SDL_Texture **t = &sButtonTex[b][v];
        if (!*t) {
            uint32_t *px = malloc((size_t)w * (size_t)h * 4);
            if (!px) continue;
            tc_draw(px, w, h, b, b == TC_DPAD ? 0 : v, b == TC_DPAD ? (uint32_t)v << 4 : 0);
            *t = SDL_CreateTexture(sRen, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);
            if (*t) {
                SDL_UpdateTexture(*t, 0, px, w * 4);
                SDL_SetTextureBlendMode(*t, SDL_BLENDMODE_BLEND);
                SDL_SetTextureScaleMode(*t, SDL_ScaleModeNearest);
            }
            free(px);
            if (!*t) continue;
        }
        SDL_Rect dst = {(int)(r.x + 0.5f), (int)(r.y + 0.5f), w, h};
        SDL_SetTextureAlphaMod(*t, (Uint8)sCtlAlpha);
        SDL_RenderCopy(sRen, *t, 0, &dst);
    }
}

static void ios_states(void) {
    static uint32_t was;
    uint32_t held = tc_held(&sTouch), pressed = held & ~was;
    was = held;
    if (pressed & 1u << TC_MENU) ui_open_settings();
}

static void ios_show(const uint32_t *overlay, int changed) {
    static SDL_Texture *canvasTex, *canvasSharp;
    static int canvasRows, canvasK;
    int rows = (int)sShm->rows;
    if (rows < 192 || rows > 640) rows = 0;
    if (overlay) {
        if (!sOverlayTex) {
            sOverlayTex = SDL_CreateTexture(sRen, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 256, 384);
            if (sOverlayTex) SDL_SetTextureBlendMode(sOverlayTex, SDL_BLENDMODE_BLEND);
            changed = 1;
        }
        if (sOverlayTex && changed) SDL_UpdateTexture(sOverlayTex, 0, overlay, 256 * 4);
    }
    SDL_SetRenderTarget(sRen, 0);
    SDL_SetRenderDrawColor(sRen, 0, 0, 0, 255);
    SDL_RenderClear(sRen);
    TcRect sc = rows ? sLayout.fill : sLayout.screens;
    int h = rows ? rows : 384;
    SDL_Texture *src = sTex;
    if (rows) {
        if (!canvasTex || canvasRows != rows) {
            if (canvasTex) SDL_DestroyTexture(canvasTex);
            canvasTex = SDL_CreateTexture(sRen, SDL_PIXELFORMAT_XRGB8888, SDL_TEXTUREACCESS_STREAMING, 256, rows);
            if (canvasTex) SDL_SetTextureScaleMode(canvasTex, SDL_ScaleModeNearest);
            canvasRows = rows;
            canvasK = 0;
        }
        src = canvasTex;
    }
    if (!src) return;
    SDL_UpdateTexture(src, 0, sShm->pixels, 256 * 4);
    SDL_FRect dst = {sc.x, sc.y, sc.w, sc.h};
    int k = (int)SDL_floorf(sc.w / 256.0f + 0.01f);
    k = k < 1 ? 1 : k > 8 ? 8 : k;
    SDL_Texture **sharp = rows ? &canvasSharp : &sSharp;
    int *sharpK = rows ? &canvasK : &sSharpK;
    if (k != *sharpK || !*sharp) {
        if (*sharp) SDL_DestroyTexture(*sharp);
        *sharp = SDL_CreateTexture(sRen, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 256 * k, h * k);
        if (*sharp) SDL_SetTextureScaleMode(*sharp, SDL_ScaleModeLinear);
        *sharpK = k;
    }
    if (*sharp && SDL_SetRenderTarget(sRen, *sharp) == 0) {
        SDL_RenderCopy(sRen, src, 0, 0);
        if (!rows && overlay && sOverlayTex) SDL_RenderCopy(sRen, sOverlayTex, 0, 0);
        SDL_SetRenderTarget(sRen, 0);
        SDL_RenderCopyF(sRen, *sharp, 0, &dst);
    } else {
        SDL_SetRenderTarget(sRen, 0);
        SDL_RenderCopyF(sRen, src, 0, &dst);
        if (!rows && overlay && sOverlayTex) SDL_RenderCopyF(sRen, sOverlayTex, 0, &dst);
    }
    if (rows && overlay && sOverlayTex) {
        TcRect s2 = sLayout.screens;
        SDL_FRect d2 = {s2.x, s2.y, s2.w, s2.h};
        SDL_RenderCopyF(sRen, sOverlayTex, 0, &d2);
    }
    {
        int target = sLayout.controls && !sTouch.buttons_off ? 255 : 0;
        sCtlAlpha += target > sCtlAlpha ? 24 : -24;
        if ((target - sCtlAlpha) * (target ? 1 : -1) < 0) sCtlAlpha = target;
        if (sCtlAlpha > 255) sCtlAlpha = 255;
        if (sCtlAlpha < 0) sCtlAlpha = 0;
    }
    if (sLayout.controls && sCtlAlpha > 0) ios_draw_controls();
}

static void ios_background(void) {
    host_set_paused(1);
    if (sDev) SDL_PauseAudioDevice(sDev, 1);
    tc_reset(&sTouch);
    SDL_Event e;
    while (sInBackground && !sShm->quit) {
        if (SDL_WaitEventTimeout(&e, 250)) handle(&e);
    }
    tc_reset(&sTouch);
    if (sDev) SDL_PauseAudioDevice(sDev, 0);
    host_set_paused(0);
}
#endif

static void show(void) {
    int changed;
    const uint32_t *overlay = ui_overlay(&changed);
#if HOST_IOS
    ios_show(overlay, changed);
    window_shot();
    if (sPendingShot[0]) shot(sPendingShot), sPendingShot[0] = 0;
    SDL_RenderPresent(sRen);
    return;
#endif
    if (sGpu) {
        int w, h;
        SDL_GetWindowSizeInPixels(sWin, &w, &h);
        wdisp_overlay(overlay, changed);
        window_shot();
        if (sPendingShot[0]) shot(sPendingShot), sPendingShot[0] = 0;
        wdisp_present(w, h);
        return;
    }
    SDL_UpdateTexture(sTex, 0, sShm->pixels, 256 * 4);
    SDL_SetRenderDrawColor(sRen, 0, 0, 0, 255);
    SDL_RenderClear(sRen);
    SDL_RenderCopy(sRen, sTex, 0, 0);
    if (overlay) {
        if (!sOverlayTex) {
            sOverlayTex = SDL_CreateTexture(sRen, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 256, 384);
            SDL_SetTextureBlendMode(sOverlayTex, SDL_BLENDMODE_BLEND);
            changed = 1;
        }
        if (changed) SDL_UpdateTexture(sOverlayTex, 0, overlay, 256 * 4);
        SDL_RenderCopy(sRen, sOverlayTex, 0, 0);
    }
    window_shot();
    if (sPendingShot[0]) shot(sPendingShot), sPendingShot[0] = 0;
    SDL_RenderPresent(sRen);
}

static void frame_body(void) {
    SDL_Event e;
#if HOST_IOS
    if (sInBackground) ios_background();
    ios_layout();
#endif
    while (SDL_PollEvent(&e)) handle(&e);
    script_step();
    if (ui_is_open()) host_set_paused(1);
    while (ui_is_open() && !sShm->quit) {
#if HOST_IOS
        if (sInBackground) ios_background();
        ios_layout();
#endif
        show();
        if (SDL_WaitEventTimeout(&e, 50)) {
            handle(&e);
            while (SDL_PollEvent(&e)) handle(&e);
        }
        script_step();
    }
    host_set_paused(0);
#if HOST_IOS
    if (sInBackground) return;
    ios_layout();
    ios_stats();
    ios_states();
    sTouch.canvas_rows = sShm->rows >= 192 && sShm->rows <= 640 ? (int)sShm->rows : 0;
    {
        extern int Scene_InTown(void), MenuCtrl_IsIdle(void), TalkRequest_IsActive(void);
        sTouch.buttons_off = !Scene_InTown() || !MenuCtrl_IsIdle() || TalkRequest_IsActive();
    }
    sShm->keys = keyboard_keys() | pad_keys() | tc_keys(&sTouch);
    sShm->stick = stick_word();
    {
        float sx = 0, sy = 0;
        extern int gHostStickRun;
        gHostStickRun = tc_stick(&sTouch, &sx, &sy) && sx * sx + sy * sy >= 0.92f * 0.92f;
    }
#else
    sShm->keys = keyboard_keys() | pad_keys();
    sShm->stick = stick_word();
#endif
    update_touch();
    show();
}

#endif
