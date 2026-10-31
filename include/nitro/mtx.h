#ifndef NITRO_MTX_H
#define NITRO_MTX_H


typedef signed int fx32;

typedef union MtxFx33 {
    struct {
        /* 0x00 */ fx32 _00, _01, _02;
        /* 0x0c */ fx32 _10, _11, _12;
        /* 0x18 */ fx32 _20, _21, _22;
    };
    fx32 m[3][3];
    fx32 a[9];
} MtxFx33;

#endif
