#ifndef HOST_FEATURES_H
#define HOST_FEATURES_H

#ifdef __cplusplus
extern "C" {
#endif

enum {
    FEAT_CIRCLE_PAD,
    FEAT_FPS,
    FEAT_NO_RESETTI,
    FEAT_COUNT
};

extern volatile unsigned long long gHostGameFrames;

void features_init(const char *path);
int feature_on(int f);
void feature_set(int f, int on);
const char *feature_name(int f);
int host_local_play_on(void);
int host_wiimmfi_on(void);

#ifdef __cplusplus
}
#endif

#endif
