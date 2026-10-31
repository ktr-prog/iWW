#include "types.h"
#include "snd/TvSound.h"
#include "sys/new.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_02003850.h"

extern "C" {
}


extern const u32 sTvSoundSizes[];
const u32 sTvSoundSizes[] = {
    sizeof(TvSoundProgram0), sizeof(TvSoundProgram1), sizeof(TvSoundProgram2), sizeof(TvSoundProgram3),
    sizeof(TvSoundProgram4), sizeof(TvSoundProgram5), sizeof(TvSoundProgram6), sizeof(TvSoundProgram7),
    sizeof(TvSoundProgram8), sizeof(TvSoundProgram9), sizeof(TvSoundProgram10), sizeof(TvSoundWeather),
};

template <class T> static TvSound *TvSound_New(Heap *heap) {
    void *p = Heap_Alloc(heap, sizeof(T));
    if (p == NULL) return NULL;
    return new (p) T;
}

extern "C" TvSound *TvSound_Create(Heap *heap, s32 type) {
    switch (type) {
    case 0: return TvSound_New<TvSoundProgram0>(heap);
    case 1: return TvSound_New<TvSoundProgram1>(heap);
    case 2: return TvSound_New<TvSoundProgram2>(heap);
    case 3: return TvSound_New<TvSoundProgram3>(heap);
    case 4: return TvSound_New<TvSoundProgram4>(heap);
    case 5: return TvSound_New<TvSoundProgram5>(heap);
    case 6: return TvSound_New<TvSoundProgram6>(heap);
    case 7: return TvSound_New<TvSoundProgram7>(heap);
    case 8: return TvSound_New<TvSoundProgram8>(heap);
    case 9: return TvSound_New<TvSoundProgram9>(heap);
    case 10: return TvSound_New<TvSoundProgram10>(heap);
    case 0xff: return TvSound_New<TvSoundWeather>(heap);
    default: return TvSound_New<TvSoundProgram0>(heap);
    }
}

extern "C" u32 TvSound_GetMaxSize() {
    u32 m = 0;
    for (const u32 *p = sTvSoundSizes; p < sTvSoundSizes + sizeof sTvSoundSizes / sizeof sTvSoundSizes[0]; p++) {
        if (*p > m) {
            m = *p;
        }
    }
    return (m + 3) & ~3;
}
