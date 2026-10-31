#include "types.h"
#include "game/Random.h"


extern "C" {
u32 Clock_GetTimeSeed();
}


extern "C" s32 gVBlanksPerFrame;
s32 gVBlanksPerFrame = 1;

Random gRandom;

Random::~Random() {}

extern "C" void Random_SeedGlobal() {
    u32 r = Clock_GetTimeSeed();
    Random_SetSeed(&gRandom.seed, r);
}
