
#include "snd7.h"

static int sMasterPan = -1;
static u8 sOrgVolume[SND_CHANNEL_COUNT];
static u8 sOrgPan[SND_CHANNEL_COUNT];
static int sSurroundDecay;

static void write_cnt(int ch, u32 v) {
    u32 old = spu_ch[ch].cnt;
    spu_ch[ch].cnt = v;
    spu_cnt_written(ch, old);
}
static void write_cnt_vol(int ch, u8 vol) { spu_ch[ch].cnt = (spu_ch[ch].cnt & ~0xffu) | vol; }
static void write_cnt_vols(int ch, u16 v) { spu_ch[ch].cnt = (spu_ch[ch].cnt & ~0xffffu) | v; }
static void write_cnt_pan(int ch, u8 pan) { spu_ch[ch].cnt = (spu_ch[ch].cnt & ~0xff0000u) | (u32)pan << 16; }

static int calc_surround_decay(int vol, int pan) {
    if (pan < 24) return vol * (sSurroundDecay * (pan + 40) + ((0x7fff - sSurroundDecay) << 6)) >> 21;
    if (pan <= 104) return vol;
    return vol * (-sSurroundDecay * (pan - 40) + ((sSurroundDecay + 0x7fff) << 6)) >> 21;
}

#define SURROUND_CHANNELS 0xfff5

void snd7_setup_channel_pcm(int ch, const void *data, int format, int loop, int loopStart, int loopLength,
                            int volume, int volumeDiv, int timer, int pan) {
    sOrgPan[ch] = (u8)pan;
    if (sMasterPan >= 0) pan = sMasterPan;
    sOrgVolume[ch] = (u8)volume;
    if (sSurroundDecay > 0 && (1 << ch) & SURROUND_CHANNELS) volume = calc_surround_decay(volume, pan);
    write_cnt(ch, (u32)(format << 29 | loop << 27 | pan << 16 | volumeDiv << 8 | volume));
    spu_ch[ch].tmr = (u16)(0x10000 - timer);
    spu_ch[ch].pnt = (u16)loopStart;
    spu_ch[ch].len = (u32)loopLength & 0x3fffff;
    spu_ch[ch].sad = (uintptr_t)data & ~(uintptr_t)3;
}

void snd7_setup_channel_psg(int ch, int duty, int volume, int volumeDiv, int timer, int pan) {
    sOrgPan[ch] = (u8)pan;
    if (sMasterPan >= 0) pan = sMasterPan;
    sOrgVolume[ch] = (u8)volume;
    if (sSurroundDecay > 0 && (1 << ch) & SURROUND_CHANNELS) volume = calc_surround_decay(volume, pan);
    write_cnt(ch, (u32)(0x60000000 | duty << 24 | pan << 16 | volumeDiv << 8 | volume));
    spu_ch[ch].tmr = (u16)(0x10000 - timer);
}

void snd7_setup_channel_noise(int ch, int volume, int volumeDiv, int timer, int pan) {
    sOrgPan[ch] = (u8)pan;
    if (sMasterPan >= 0) pan = sMasterPan;
    sOrgVolume[ch] = (u8)volume;
    if (sSurroundDecay > 0 && (1 << ch) & SURROUND_CHANNELS) volume = calc_surround_decay(volume, pan);
    write_cnt(ch, (u32)(0x60000000 | pan << 16 | volumeDiv << 8 | volume));
    spu_ch[ch].tmr = (u16)(0x10000 - timer);
}

void snd7_stop_channel(int ch, int hold) {
    u32 v = spu_ch[ch].cnt & ~0x80000000u;
    if (hold & 1) v |= 0x8000;
    write_cnt(ch, v);
}

void snd7_set_channel_volume(int ch, int vol, int volDiv) {
    sOrgVolume[ch] = (u8)vol;
    if (sSurroundDecay > 0 && (1 << ch) & SURROUND_CHANNELS) vol = calc_surround_decay(vol, spu_ch[ch].cnt >> 16 & 0xff);
    write_cnt_vols(ch, (u16)(volDiv << 8 | vol));
}

void snd7_set_channel_timer(int ch, int timer) { spu_ch[ch].tmr = (u16)(0x10000 - timer); }

void snd7_set_channel_pan(int ch, int pan) {
    sOrgPan[ch] = (u8)pan;
    if (sMasterPan >= 0) pan = sMasterPan;
    write_cnt_pan(ch, (u8)pan);
    if (sSurroundDecay > 0 && (1 << ch) & SURROUND_CHANNELS) write_cnt_vol(ch, (u8)calc_surround_decay(sOrgVolume[ch], pan));
}

BOOL snd7_is_channel_active(int ch) { return (spu_ch[ch].cnt & 0x80000000u) != 0; }

void snd7_set_master_pan(int pan) {
    sMasterPan = pan;
    for (int i = 0; i < SND_CHANNEL_COUNT; i++) write_cnt_pan(i, pan >= 0 ? (u8)pan : sOrgPan[i]);
}

u32 snd7_get_channel_control(int ch) { return spu_ch[ch].cnt; }

void snd7_set_surround_decay(int decay) {
    sSurroundDecay = decay;
    for (int i = 0; i < SND_CHANNEL_COUNT; i++)
        if ((1 << i) & SURROUND_CHANNELS) write_cnt_vol(i, (u8)calc_surround_decay(sOrgVolume[i], spu_ch[i].cnt >> 16 & 0xff));
}

void snd7_setup_capture(int idx, int format, void *data, int size, BOOL loop, int capCtrlSrc, int capCtrlDst) {
    u8 old = spu_capcnt[idx];
    spu_capcnt[idx] = (u8)(format << 3 | (loop ? 0 : 1) << 2 | capCtrlSrc << 1 | capCtrlDst);
    spu_capcnt_written(idx, old);
    spu_capdad[idx] = (uintptr_t)data & ~(uintptr_t)3;
    spu_caplen[idx] = (u16)size;
}

BOOL snd7_is_capture_active(int idx) { return (spu_capcnt[idx] & 0x80) != 0; }
