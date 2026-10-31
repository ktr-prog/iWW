#ifndef HOST_OVERLAY_VARS_H
#define HOST_OVERLAY_VARS_H

typedef struct HostOverlayVar {
    void *addr;
    __SIZE_TYPE__ size;
    const char *name;
} HostOverlayVar;

#ifdef __cplusplus
#define HOST_OVERLAY_VARS_LINKAGE extern "C"
#else
#define HOST_OVERLAY_VARS_LINKAGE extern
#endif

#define HOST_OVERLAY_VARS(unit)                                                                                      \
    HOST_OVERLAY_VARS_LINKAGE const HostOverlayVar gHostOvVars_##unit[];                                             \
    HOST_OVERLAY_VARS_LINKAGE const HostOverlayVar gHostOvVars_##unit[] =
#define HOST_OVERLAY_VAR(v) {(void *)&(v), sizeof(v), #v}
#define HOST_OVERLAY_VARS_END {0, 0, 0}

#ifdef __cplusplus
#define HOST_STATIC_INIT_ARRAY(var, ...)                                                                             \
    do {                                                                                                             \
        const decltype(var) init_ = __VA_ARGS__;                                                                     \
        for (__SIZE_TYPE__ i_ = 0; i_ < sizeof(var) / sizeof((var)[0]); i_++) (var)[i_] = init_[i_];                \
    } while (0)
#define HOST_STATIC_INIT(var, ...)                                                                                   \
    do {                                                                                                             \
        const decltype(var) init_ = __VA_ARGS__;                                                                     \
        (var) = init_;                                                                                               \
    } while (0)

struct HostOverlayPlace {};
inline void *operator new(__SIZE_TYPE__, void *p, HostOverlayPlace) { return p; }
template <class T> inline void HostOverlay_Construct(T &v) { new (&v, HostOverlayPlace()) T; }
template <class T, __SIZE_TYPE__ N> inline void HostOverlay_Construct(T (&v)[N]) {
    for (__SIZE_TYPE__ i = 0; i < N; i++) HostOverlay_Construct(v[i]);
}
#define HOST_STATIC_CONSTRUCT(var) HostOverlay_Construct(var)
#endif

#endif
