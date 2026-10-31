#include "types.h"
#include "gfx/VecFx32.h"
#include "snd/PlayCtx.h"



struct Ramp;
extern "C" void SndVolumeCurve_Clear(Ramp *r);
struct Ramp {
    s32 w0, w4, w8, wc, w10, w14, w18;
    Ramp() { SndVolumeCurve_Clear(this); }
};

extern "C" {
extern Ramp gSndVolumeCurve;
extern s32 data_021f5c00;
extern s32 data_021f5c04;
extern s32 data_021f5c08;
extern u8 data_021f5bfc;

s32 FX_Div(s32 a, s32 b);
s32 FX_Sqrt(s32 x);
s32 Snd_ListenerDistanceCallback(PlayCtx *p);
s32 Snd_ListenerVolumeCallback(PlayCtx *p);
s32 Snd_ListenerPanCallback(PlayCtx *p);
s32 Snd_DistanceToVolume(s32 x);
s32 Snd_CalcPan(VecFx32 *p, s32 m);
s32 Snd_CalcListenerDistance(VecFx32 *p, s32 m);
s32 SndVolumeCurve_Eval(Ramp *r, s32 x);
}


static inline s32 FX_Mul(s32 a, s32 b) {
    return (s32)(((s64)a * b + 0x800) >> 12);
}

extern "C" s32 Snd_ListenerDistanceCallback(PlayCtx *p) {
    return Snd_CalcListenerDistance((VecFx32 *)p->source, 0);
}

extern "C" s32 Snd_DistanceToVolume(s32 x) {
    return SndVolumeCurve_Eval(&gSndVolumeCurve, x);
}

extern "C" s32 Snd_ListenerVolumeCallback(PlayCtx *p) {
    return Snd_DistanceToVolume(p->distance);
}

extern "C" void Snd_CalcDepthVolumes(s32 z, s32 *a, s32 *b) {
    s32 l;
    s32 r;
    if (z <= 0) {
        l = 0;
    } else if (z <= 0x99a) {
        l = FX_Mul(data_021f5c00, z) >> 12;
    } else if (z > 0x1000) {
        l = 0;
    } else {
        l = (0x7f000 - FX_Mul(data_021f5c08, z - 0x99a)) >> 12;
    }
    if (z <= 0x99a) {
        r = 0;
    } else if (z >= 0xccd) {
        r = 127;
    } else {
        r = FX_Mul(data_021f5c04, z - 0x99a) >> 12;
    }
    if (l > 127) {
        l = 127;
    } else if (l < 0) {
        l = 0;
    }
    *a = l;
    if (r > 127) {
        r = 127;
    } else if (r < 0) {
        r = 0;
    }
    *b = r;
}

extern "C" s32 Snd_CalcPan(VecFx32 *p, s32 m) {
    s32 r;
    s32 x;
    if (p == 0) return 0;
    x = p->x >> 12;
    switch (m) {
    case 0:
        r = (x + 42) * 221 / 83 - 111;
        break;
    case 1:
        if (x > 0) {
            r = 1;
        } else {
            r = -(x < 0);
        }
        break;
    case 2:
        r = x - 128;
        break;
    }
    if (r < -128) {
        r = -128;
    } else if (r > 127) {
        r = 127;
    }
    return r;
}

extern "C" s32 Snd_ListenerPanCallback(PlayCtx *p) {
    return Snd_CalcPan((VecFx32 *)p->source, 0);
}

extern "C" void SndVolumeCurve_Clear(Ramp *r) {
    r->w4 = r->w8 = r->wc = r->w10 = 0;
    r->w14 = r->w18 = 0;
}

extern "C" void SndVolumeCurve_Set(Ramp *r, s32 v) {
    s32 t;
    if (r->w0 == v) return;
    r->w0 = v;
    t = r->w0 - 0xb000;
    r->w4 = 0x7f000 - FX_Mul(t, 0x3000);
    r->w8 = 0x68000 - FX_Mul(t, 0x4000);
    r->wc = FX_Mul(FX_Div(0x2000, 0x3000), t) + 0x4000;
    r->w10 = FX_Mul(FX_Div(0x4000, 0x3000), t) + 0x11000;
    r->w14 = FX_Div(r->w4 - r->w8, r->wc - r->w0);
    r->w18 = FX_Div(r->w8, r->w0 - r->w10);
}

extern "C" s32 SndVolumeCurve_Eval(Ramp *r, s32 x) {
    s32 v;
    if (x >= (r->w10 >> 12)) {
        v = 0;
    } else if (x <= (r->wc >> 12)) {
        v = r->w4 >> 12;
    } else if (x <= (r->w0 >> 12)) {
        v = (r->w4 + FX_Mul((x << 12) - r->wc, r->w14)) >> 12;
    } else {
        v = (r->w8 + FX_Mul((x << 12) - r->w0, r->w18)) >> 12;
    }
    if (v > 127) return 127;
    if (v < 0) return 0;
    return v;
}

extern "C" s32 Snd_CalcListenerDistance(VecFx32 *p, s32 m) {
    s32 dx, dy, dz;
    if (p == 0) return 0;
    switch (m) {
    case 0:
        dz = p->z + 0xc000;
        return FX_Sqrt(FX_Mul(p->x, p->x) + FX_Mul(p->y, p->y) + FX_Mul(dz, dz)) >> 12;
    case 1:
        dz = p->z + 0xc000;
        return FX_Sqrt(FX_Mul(p->y, p->y) + FX_Mul(dz, dz)) >> 12;
    case 2:
        dx = (p->x - 0x80000) >> 3;
        dy = (p->y - 0x50000) >> 2;
        return FX_Sqrt(FX_Mul(dx, dx) + FX_Mul(dy, dy)) >> 12;
    default:
        return 0;
    }
}

extern "C" Ramp *Snd_GetVolumeCurve(void) {
    return &gSndVolumeCurve;
}

extern "C" void Snd_SetUnusedFlag(u8 v) {
    data_021f5bfc = v;
}

Ramp gSndVolumeCurve;
u8 data_021f5bfc;
s32 data_021f5c00 = FX_Div(0x7f000, 0x99a);
s32 data_021f5c08 = FX_Div(0x7f000, 0x666);
s32 data_021f5c04 = FX_Div(0x7f000, 0x333);
