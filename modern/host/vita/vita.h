#ifndef HOST_VITA_VITA_H
#define HOST_VITA_VITA_H

#ifdef __cplusplus
extern "C" {
#endif

// the game's real entry (modern/host/main.c, renamed there for --os vita); the glue's own main() finds the
// game on the device and calls it
int host_main(int argc, char **argv);

// a simple on-screen error (used when there is no game to run); best-effort, needs SDL's video up
void vita_fatal_message(const char *text);

// GPU render path (modern/host/vita/vita_gl.c), via vitaGL. Default on the Vita; ACWW_GL=0 forces the SDL/GXM
// software-blit renderer. Stage 1: vitaGL owns the display and presents the composited DS canvas as a textured,
// letterboxed quad. Stage 2 moves the DS 3D geometry onto the GPU.
int vita_gl_enabled(void);
int vita_gl_init(void);
void vita_gl_present_canvas(const void *pixels, int canvas_w, int canvas_h, int sx, int sy, int sw, int sh);
void vita_gl_shutdown(void);

// start the file-I/O worker thread (modern/host/vita/vita_io.c). Must be called once, early, before the game
// starts: the game runs on a custom coroutine stack, and the Vita's filesystem syscalls fault unless they run
// on a kernel-registered thread stack, so all file I/O is marshaled to this worker.
void vita_io_init(void);

#ifdef __cplusplus
}
#endif

#endif
