#include "types.h"
#include "game/Random.h"


extern "C" {
u32 Clock_GetTimeSeed();
}


extern "C" s32 gVBlanksPerFrame;
s32 gVBlanksPerFrame = 1;

#ifdef HOST
extern "C" u32 gHostTick;
u32 gHostTick;
extern "C" char *getenv(const char *);
extern "C" BOOL HostTick_Native(void) {
    static s32 on = -1;
    if (on < 0) on = !(getenv("ACWW_TICK20") && getenv("ACWW_TICK20")[0] == '1');
    return on;
}
extern "C" s32 HostTick_Steps(void) {
    if (!HostTick_Native()) return 1;
    s32 n = gVBlanksPerFrame;
    return n < 1 ? 1 : n > 4 ? 4 : n;
}
static s64 HostTick_FloorDiv(s64 a, s64 b) {
    s64 q = a / b;
    return (a % b != 0 && (a < 0) != (b < 0)) ? q - 1 : q;
}
extern "C" s32 HostTick_Part(s32 x) {
    s32 n = HostTick_Steps();
    if (n == 1) return x;
    s32 p = (s32)(gHostTick % (u32)n);
    return (s32)(HostTick_FloorDiv((s64)x * (p + 1), n) - HostTick_FloorDiv((s64)x * p, n));
}
extern "C" double pow(double, double);
extern "C" s32 HostTick_Rate(s32 r) {
    s32 n = HostTick_Steps();
    if (n == 1 || r <= 0 || r >= 0x1000) return r;
    double k = 1.0 - pow(1.0 - r / 4096.0, 1.0 / n);
    s32 v = (s32)(k * 4096.0 + 0.5);
    return v < 1 ? 1 : v;
}
extern "C" s32 HostTick_Div(s32 x) {
    s32 n = HostTick_Steps();
    if (n == 1 || x == 0) return x;
    s32 v = x / n;
    return v ? v : (x > 0 ? 1 : -1);
}
extern "C" BOOL HostTick_StepEnds(void) {
    s32 n = HostTick_Steps();
    return gHostTick % (u32)n == (u32)(n - 1);
}
#endif

Random gRandom;

Random::~Random() {}

extern "C" void Random_SeedGlobal() {
    u32 r = Clock_GetTimeSeed();
    Random_SetSeed(&gRandom.seed, r);
}
