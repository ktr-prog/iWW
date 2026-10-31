#ifndef HOST_IOS_TOUCH_CONTROLS_H
#define HOST_IOS_TOUCH_CONTROLS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum { TC_A, TC_B, TC_X, TC_Y, TC_L, TC_R, TC_START, TC_SELECT, TC_SAVE, TC_LOAD, TC_MENU, TC_DPAD, TC_COUNT };

typedef struct { float x, y, w, h; } TcRect;

typedef struct {
    int w, h;
    TcRect screens;
    int controls;
    TcRect button[TC_COUNT];
    int stick;
} TcLayout;

void tc_layout(TcLayout *l, int w, int h, float pt, const float safe[4], int controls);

enum { TC_MAX_POINTERS = 12 };
typedef struct {
    struct {
        int64_t id;
        int used;
        int what;
        uint32_t keys;
    } p[TC_MAX_POINTERS];
    int stylus_x, stylus_y;
    unsigned stylus_presses;
    float stick_x, stick_y;
    int single;
} TcState;

void tc_reset(TcState *s);
enum { TC_DOWN, TC_MOVE, TC_UP };
int tc_pointer(TcState *s, const TcLayout *l, int64_t id, int event, float x, float y);
uint32_t tc_keys(const TcState *s);
int tc_stylus(const TcState *s, int *x, int *y);
unsigned tc_stylus_presses(const TcState *s);
uint32_t tc_held(const TcState *s);
uint32_t tc_dpad_dirs(const TcState *s);
int tc_stick(const TcState *s, float *x, float *y);

void tc_draw(uint32_t *px, int w, int h, int which, int pressed, uint32_t dirs);
#define TC_KNOB 0.46f
#define TC_KNOB_TRAVEL 0.27f
void tc_draw_stick_base(uint32_t *px, int w, int h);
void tc_draw_stick_knob(uint32_t *px, int w, int h, int pressed);

#ifdef __cplusplus
}
#endif

#endif
