#ifndef HOST_INPUT_H
#define HOST_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif
#ifdef HOST
int host_circle_pad(int *x, int *y);
#else
#define host_circle_pad(x, y) 0
#endif
#ifdef __cplusplus
}
#endif

#endif
