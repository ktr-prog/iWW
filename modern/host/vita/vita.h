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

#ifdef __cplusplus
}
#endif

#endif
