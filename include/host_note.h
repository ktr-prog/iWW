#ifndef HOST_NOTE_H
#define HOST_NOTE_H

#ifdef __cplusplus
extern "C" {
#endif
#ifdef HOST
void host_note(const char *what, int a, int b, int c);
#else
#define host_note(what, a, b, c) ((void)0)
#endif
#ifdef __cplusplus
}
#endif

#endif
