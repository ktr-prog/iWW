#include "uptr.h"
#include "host_tick.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "game/GroundInfo.h"
#include "Unk_020d8c7c.h"
#include "game/Unk_02034250_Id.h"
#include "game/Unk_02036c60_Vec.h"
#include "game/Unk_021e5890_T.h"
#include "snd/BgmSceneFade.h"
#include "gfx/BgModelCache.h"
#include "snd/BgmVolumeMixer.h"
#include "snd/BgmManager.h"
#include "sys/ProcProfile.h"
#include "player/PlayerData.h"
#include "player/PlayerErrands.h"
#include "net/CommManager.h"
#include "proto/main/unk_020b4828.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02101048.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02034048.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02036c58.h"
#include "proto/main/unk_020407fc.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov004/unk_ov004_0222a500.h"

typedef void (BgmVolumeMixer::*Unk_02035758_Fn)(BgmVolumeChannel *);

class BgmProc : public GameProc {
public:
    BgmProc();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual ~BgmProc();
    static BgmProc *create();

    /* 0x50 */ BgmManager bgmManager;
};




extern "C" {
extern u8 gFieldSceneKind;
extern u8 sSceneCarpets[];
extern u8 sSceneWallpapers[];
extern u8 sRoomWallFloorNoItem[];
extern CommManager *gCommManager;
extern u8 gSavePlayers[];
extern Unk_02034574_Fn data_020d8dac;
void func_02004b60();
s32 Item_SetDesign(u16 *out, s32 a, s32 b);
u32 func_0209888c();
s32 Scene_GetCurrent();
void func_020728d4(void *p);
void func_020728a4(void *p, void *q, s32 n);
void func_02072824(void *p, s32 a, s32 b);
BOOL Scene_InTown();
void __cxa_vec_cleanup(void *p, u32 n, u32 sz, void (*d)());
extern BgmManager *data_021c1b3c;
s32 Weather_GetPrecipKind(void);
void Weather_GetLevels(s32 *a, s32 *b);
u8 Scene_GetPrevious(void);
s32 Scene_InTownUnk31(void);
s32 Item_IsFurniture(void *p);
s32 Item_GetFurnitureIndex(void *p);
extern ProcBase *gActorDefaultParent;
void Clock_GetDateTime(void *);
void MI_CpuCopy8(void *, void *, u32);
s32 Event_GetState(u32, void *, u32);
s32 Clock_GetYear(void);
void Clock_GetDayMonth(u16 *);
void Clock_GetMinuteHour(u16 *);
s32 Clock_GetSecond(void);
s32 NNS_FndMountArchive(void *, const void *, void *);
void NNS_FndUnmountArchive(void *);
void *NNS_G3dGetMdlSet(void *);
void *func_021065dc(void *);
void *func_021065f8(void *, s32);
void *func_02106618(void *);
void *func_02106634(void *, s32);
void *func_02106654(void *);
void *func_02106670(void *, s32);
void *func_02106690(void *);
void *func_021066ac(void *, s32);
void *NNS_G3dGetTex(void *);
void Gfx3d_LoadTexAndPltt(void *, s32);
void *Gfx3d_CopyTex(void *, void *);
void *func_0204df64(void *);
extern u8 sBgAcreArcPathFmt[], sBgArchiveName[], sBgAcreBmdPath[], sBgAcreBclPath[], sBgAcreBsdPath[];
extern u8 sBgAcreBcaPath[], sBgAcreBmaPath[], sBgAcreBtaPath[], sBgAcreMgtPath[], sBgAcreTexPathFmt[];
extern u8 sBgGroundAnimArcPath[], sBgGroundSetBmaPath[], sBgGroundSetBtaPath[], sBgRiverBtpPath[], sBgRiverItpTexPath[];
extern u8 sBgBeBBtpPath[], sBgBeBItpTexPath[], sBgGroundSetTexPathFmt[];
extern u8 gSaveTownMap[];
extern Unk_021e5890_T data_021e5890;
}

extern const u16 sSceneBgmTable[0x3a];
extern const u8 sBgmSceneFadeDelays[8];
extern const s32 sBgmMenuDuckStates[3];
extern const u16 sHourlyBgmIds[0x18];

static inline BOOL Unk_020341c0_IsOne(u8 v) { return v == 1 ? TRUE : FALSE; }

static inline BOOL Unk_02034938_IsA() { return gFieldSceneKind == 0; }

static inline BOOL Unk_02034938_IsB() { return gFieldSceneKind == 1; }

static inline BOOL IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }

BgmRequest *BgmRequest::initEmpty()
{
    clear();
    return this;
}

BgmRequest *BgmRequest::init(s32 a, u32 b, s32 c, s32 d, u8 e)
{
    clear();
    priority = a;
    bgmId = b;
    volume = c;
    stopFadeFrames = d;
    muteDucks = e;
    return this;
}

void BgmRequest::func_02036c18()
{
}

void BgmRequest::clear()
{
    priority = 0x25;
    bgmId = 0xffff;
    stopFadeFrames = 0;
    volume = 0;
    muteDucks = 0;
    transient = 0;
    playing = 0;
    removePending = 0;
    volumePending = 0;
    lifetime = 0;
}

void BgmRequest::copyFrom(BgmRequest *src)
{
    clear();
    priority = src->priority;
    bgmId = src->bgmId;
    stopFadeFrames = src->stopFadeFrames;
    volume = src->volume;
    muteDucks = src->muteDucks;
    transient = src->transient;
    playing = src->playing;
    removePending = src->removePending;
    volumePending = src->volumePending;
    lifetime = src->lifetime;
}

BOOL BgmRequest::tickLifetime()
{
    BOOL r = FALSE;
    if (lifetime > 0) {
        lifetime = lifetime - 1;
        if (lifetime <= 0) {
            r = TRUE;
        }
    }
    return r;
}

BgmClock::BgmClock()
{
}

BgmClock::~BgmClock()
{
}

extern "C" void BgmClock_Init(BgmClock *p)
{
    p->update();
    p->update();
}

extern "C" void BgmClock_Exit(void)
{
}

extern "C" void BgmClock_Update(BgmClock *p)
{
    p->update();
}

extern "C" void BgmClock_Reset(BgmClock *p)
{
    p->update();
    p->update();
}

BOOL BgmClock::isAt(u16 *a, u16 *b)
{
    if (dayMonth == *a && *(u16 *)&minute == *b) {
        return TRUE;
    }
    return FALSE;
}

BOOL BgmClock::isMinuteInRange(u32 a, u32 b, u32 c, u32 d)
{
    u32 t = second + minute * 0x3c;
    u32 lo = b + a * 0x3c;
    u32 hi = d + c * 0x3c;
    BOOL r = FALSE;
    if (lo <= hi) {
        if (t >= lo && t < hi) r = TRUE;
    } else {
        if (t >= lo || t < hi) r = TRUE;
    }
    return r;
}

BOOL BgmClock::isTimeInRange(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f)
{
    u32 t = second + (hour * 0xe10 + minute * 0x3c);
    u32 lo = c + (a * 0xe10 + b * 0x3c);
    u32 hi = f + (d * 0xe10 + e * 0x3c);
    BOOL r = FALSE;
    if (lo <= hi) {
        if (t >= lo && t < hi) r = TRUE;
    } else {
        if (t >= lo || t < hi) r = TRUE;
    }
    return r;
}

BOOL BgmClock::hasHourChanged()
{
    if ((u8)(prevMinuteHour >> 8) != hour) {
        return TRUE;
    }
    return FALSE;
}

BOOL BgmClock::hasYearChanged()
{
    if (prevYear != year) {
        return TRUE;
    }
    return FALSE;
}

void BgmClock::update()
{
    prevYear = year;
    prevDayMonth = dayMonth;
    prevMinuteHour = *(u16 *)&minute;
    prevSecond = second;
    year = Clock_GetYear();
    Clock_GetDayMonth(&dayMonth);
    Clock_GetMinuteHour((u16 *)&minute);
    second = Clock_GetSecond();
}

HourlyBgm::HourlyBgm(BgmManager *v) : manager(v), hour(0x18), currentBgm(0xffff), hourFadeActive(0), keep(0), active(0)
{
}

HourlyBgm::~HourlyBgm()
{
}

void HourlyBgm::init()
{
    currentBgm = 0xffff;
    hour = 0x18;
    hourFadeActive = 0;
    keep = 0;
    active = 0;
}

void HourlyBgm::exit()
{
    stop();
}

void HourlyBgm::update()
{
    if (active != 0) {
        updateHour();
        updateHourFade();
    }
}

void HourlyBgm::stop()
{
    stopHourBgm();
    hour = 0x18;
    stopHourFade();
    keep = 0;
    active = 0;
}

void HourlyBgm::start()
{
    active = 1;
    updateHour();
    updateHourFade();
}

void HourlyBgm::end()
{
    if (keep == 0) {
        stopHourBgm();
        hour = 0x18;
        stopHourFade();
    }
    active = 0;
}

void HourlyBgm::setKeep(u32 v)
{
    keep = v;
}

void HourlyBgm::playHourBgm()
{
    u16 t = sHourlyBgmIds[hour];
    Bgm_Request(0x24, t, 0x7f, 0);
    currentBgm = t;
}

void HourlyBgm::stopHourBgm()
{
    u16 t = currentBgm;
    if (t != 0xffff) {
        Bgm_Release(t);
        currentBgm = 0xffff;
    }
}

void HourlyBgm::updateHour()
{
    u32 v = Bgm_GetClock()->hour;
    if (v != hour) {
        stopHourBgm();
        hour = v;
        playHourBgm();
    }
}

void HourlyBgm::startHourFade(u32 x)
{
    if (hourFadeActive == 0) {
        Bgm_RequestSilence(0x1b, x, 0);
        hourFadeActive = 1;
    }
}

void HourlyBgm::stopHourFade()
{
    if (hourFadeActive != 0) {
        Bgm_ReleasePriority(0x1b);
        hourFadeActive = 0;
    }
}

void HourlyBgm::updateHourFade()
{
    BgmClock *p = Bgm_GetClock();
    BOOL r = p->isMinuteInRange(0x3b, 0x32, 0, 0x10);
    u16 a[4];
    a[0] = sNewYearEveDate[0];
    a[1] = sNewYearDayDate[0];
    a[2] = sNewYearEveTime[0];
    func_02133ef8(&a[3], 2);
    if (p->isAt(&a[0], &a[2]) || p->isAt(&a[1], &a[3])) {
        r = FALSE;
    }
    if (r) {
        startHourFade(200);
    } else {
        stopHourFade();
    }
}

FieldSpecialBgm::FieldSpecialBgm(BgmManager *v) : manager(v), currentBgm(0xffff), keep(0), active(0)
{
}

FieldSpecialBgm::~FieldSpecialBgm()
{
}

void FieldSpecialBgm::init()
{
    currentBgm = 0xffff;
    keep = 0;
    active = 0;
}

void FieldSpecialBgm::exit()
{
    stop();
}

void FieldSpecialBgm::update()
{
}

void FieldSpecialBgm::stop()
{
    stopBgm();
    keep = 0;
    active = 0;
}

void FieldSpecialBgm::start() {
    active = 1;
    if (currentBgm == 0xffff) {
        PlayerData *r5 = PlayerData_GetCurrent();
        if (Taxi_IsArriving() != 0) {
            Bgm_RequestSilence(3, 0, 5);
            play(4, 0x45, 1);
        } else if (Taxi_IsLeaving() != 0) {
            play(0xd, 0x4a, 0);
        } else if (r5 != 0 && (((PlayerData *)r5)->testFlag(0x23) != 0 || (((PlayerData *)r5)->testFlag(1) != 0 && PlayerErrands_IsJobActive(r5->getErrands()) == 0))) {
            play(0x1c, 0x46, 0);
        } else if (r5 != 0 && ((PlayerData *)r5)->testFlag(1) != 0) {
            play(0x1d, 0x48, 0);
        }
    }
}

void FieldSpecialBgm::end() {
    if (keep == 0) stopBgm();
    active = 0;
}

void FieldSpecialBgm::setKeep(u32 a) { keep = a; }

void FieldSpecialBgm::play(s32 a, u32 b, u32 c) {
    Bgm_Request(a, b, 0x7f, c);
    currentBgm = b;
}

void FieldSpecialBgm::stopBgm() {
    if (currentBgm != 0xffff) { Bgm_Release(currentBgm); currentBgm = 0xffff; }
}

EventBgm::EventBgm(BgmManager *a) {
    manager = a;
    newYearFanfareBgm = 0xffff;
    newYearNightBgm = 0xffff;
    newYearDayBgm = 0xffff;
    countdownBgm = 0xffff;
    fireworksBgm = 0xffff;
    countdownFadeActive = 0;
    yearChanged = 0;
    keep = 0;
    active = 0;
}

EventBgm::~EventBgm() {}

void EventBgm::init() {
    newYearFanfareBgm = 0xffff;
    newYearNightBgm = 0xffff;
    newYearDayBgm = 0xffff;
    countdownBgm = 0xffff;
    fireworksBgm = 0xffff;
    countdownFadeActive = 0;
    yearChanged = 0;
    keep = 0;
    active = 0;
}

void EventBgm::exit() { stop(); }

void EventBgm::update() {
    if (active != 0) {
        updateYearChanged();
        updateEvents();
    }
}

void EventBgm::stop() {
    stopNewYearFanfare();
    stopNewYearNight();
    stopNewYearDay();
    stopCountdown();
    stopFireworks();
    stopCountdownFade();
    yearChanged = 0;
    keep = 0;
    active = 0;
}

void EventBgm::start() {
    active = 1;
    updateEvents();
}

void EventBgm::end() {
    if (keep == 0) {
        stopNewYearFanfare();
        stopNewYearNight();
        stopNewYearDay();
        stopCountdown();
        stopFireworks();
        stopCountdownFade();
    }
    active = 0;
}

void EventBgm::setKeep(u32 a) { keep = a; }

void EventBgm::updateEvents() {
    s32 r5 = EventAnnounce_GetActiveEvent();
    u32 t[2];
    u32 b0[2], b1[2], b2[2];
    BOOL r6, r7;
    t[0] = 0;
    t[1] = 0;
    Clock_GetDateTime(t);
    MI_CpuCopy8(t, b0, 8);
    if (Event_GetState(0x13, b0, 0) != 0) r6 = TRUE; else r6 = FALSE;
    r7 = TRUE;
    if (r5 != 0x12) {
        MI_CpuCopy8(t, b1, 8);
        if (Event_GetState(0x12, b1, 0) != 3) r7 = FALSE;
    }
    if (((CommManager *)gCommManager)->isOnline() != 0) {
        MI_CpuCopy8(t, b2, 8);
        r5 = Event_GetState(0xf, b2, 0);
    } else if (r5 == 0xf) {
        r5 = 1;
    } else {
        r5 = 0;
    }
    updateNewYearDay(r6);
    updateCountdown(r7);
    BOOL v;
    if (r5 != 0) v = TRUE; else v = FALSE;
    updateFireworks(v);
}

void EventBgm::updateNewYearDay(BOOL a) {
    if (a != 0) {
        BgmClock *o = Bgm_GetClock();
        s32 r0 = o->isTimeInRange(0, 0, 0, 2, 0, 0);
        s32 r1 = o->isTimeInRange(2, 0, 0, 0, 0, 0);
        if (r0 != 0) {
            if (yearChanged != 0) {
                if (newYearFanfareBgm != 0x35) {
                    stopNewYearFanfare();
                    playNewYearFanfare(0x35);
                }
                yearChanged = 0;
            }
            if (newYearNightBgm != 0x36) {
                stopNewYearNight();
                playNewYearNight(0x36);
            }
        } else {
            stopNewYearFanfare();
            stopNewYearNight();
        }
        if (r1 != 0) {
            if (newYearDayBgm != 0x37) {
                stopNewYearDay();
                playNewYearDay(0x37);
            }
        } else {
            stopNewYearDay();
        }
    } else {
        stopNewYearFanfare();
        stopNewYearNight();
        stopNewYearDayAlias();
    }
}

void EventBgm::updateCountdown(BOOL a) {
    if (a != 0) {
        BgmClock *o = Bgm_GetClock();
        u32 c = 0xffff;
        s32 r0 = o->isTimeInRange(0x17, 0, 0, 0x17, 0x1e, 0);
        s32 r1 = o->isTimeInRange(0x17, 0x1e, 0, 0x17, 0x32, 0);
        s32 r2 = o->isTimeInRange(0x17, 0x32, 0, 0x17, 0x37, 0);
        s32 r3 = o->isTimeInRange(0x17, 0x37, 0, 0, 0, 0);
        if (r0 != 0) c = 0x31;
        else if (r1 != 0) c = 0x32;
        else if (r2 != 0) c = 0x33;
        else if (r3 != 0) c = 0x34;
        if (c != 0xffff) {
            if (countdownBgm != c) {
                stopCountdown();
                playCountdown(c);
            }
        } else {
            stopCountdown();
        }
        s32 q0 = o->isTimeInRange(0x17, 0x1d, 0x32, 0x17, 0x1e, 0);
        s32 q1 = o->isTimeInRange(0x17, 0x31, 0x32, 0x17, 0x32, 0);
        s32 q2 = o->isTimeInRange(0x17, 0x36, 0x32, 0x17, 0x37, 0);
        s32 q3 = o->isTimeInRange(0x17, 0x3a, 0x32, 0, 0, 0);
        if (q0 != 0 || q1 != 0 || q2 != 0 || q3 != 0) {
            startCountdownFade(200);
        } else {
            stopCountdownFade();
        }
    } else {
        stopCountdown();
        stopCountdownFade();
    }
}

void EventBgm::updateFireworks(BOOL a) {
    if (a != 0) {
        if (fireworksBgm != 0x30) {
            stopFireworks();
            playFireworks(0x30);
        }
    } else {
        stopFireworks();
    }
}

void EventBgm::playNewYearFanfare(u32 a) { Bgm_RequestTransient(0x1f, a); newYearFanfareBgm = a; }

void EventBgm::playNewYearNight(u32 a) { Bgm_Request(0x20, a, 0x7f, 0); newYearNightBgm = a; }

void EventBgm::playNewYearDay(u32 a) { Bgm_Request(0x21, a, 0x7f, 0); newYearDayBgm = a; }

void EventBgm::playCountdown(u32 a) { Bgm_Request(0x22, a, 0x7f, 0); countdownBgm = a; }

void EventBgm::playFireworks(u32 a) { Bgm_Request(0x23, a, 0x7f, 0); fireworksBgm = a; }

void EventBgm::stopNewYearFanfare() {
    if (newYearFanfareBgm != 0xffff) { Bgm_ReleaseTransient(newYearFanfareBgm); newYearFanfareBgm = 0xffff; }
}

void EventBgm::stopNewYearNight() {
    if (newYearNightBgm != 0xffff) { Bgm_Release(newYearNightBgm); newYearNightBgm = 0xffff; }
}

void EventBgm::stopNewYearDay() {
    if (newYearDayBgm != 0xffff) { Bgm_Release(newYearDayBgm); newYearDayBgm = 0xffff; }
}

void EventBgm::stopCountdown() {
    if (countdownBgm != 0xffff) { Bgm_Release(countdownBgm); countdownBgm = 0xffff; }
}

void EventBgm::stopFireworks() {
    if (fireworksBgm != 0xffff) { Bgm_Release(fireworksBgm); fireworksBgm = 0xffff; }
}

void EventBgm::startCountdownFade(u32 a) {
    if (countdownFadeActive == 0) {
        Bgm_RequestSilence(0x1e, a, 0);
        countdownFadeActive = 1;
    }
}

void EventBgm::stopCountdownFade() {
    if (countdownFadeActive != 0) {
        Bgm_ReleasePriority(0x1e);
        countdownFadeActive = 0;
    }
}

void EventBgm::updateYearChanged() {
    u8 *p = &yearChanged;
    s32 r = Bgm_GetClock()->hasYearChanged();
    if ((yearChanged | r) != 0) r = 1; else r = 0;
    *p = r;
}

FieldBgm::FieldBgm(BgmManager *a) : hourlyBgm(a), specialBgm(a), eventBgm(a) {}

FieldBgm::~FieldBgm() {}

void FieldBgm::init() {
    hourlyBgm.init();
    specialBgm.init();
    eventBgm.init();
}

void FieldBgm::exit() {
    eventBgm.exit();
    specialBgm.exit();
    hourlyBgm.exit();
}

void FieldBgm::update() {
    hourlyBgm.update();
    specialBgm.update();
    eventBgm.update();
}

void FieldBgm::stop() {
    hourlyBgm.stop();
    specialBgm.stop();
    eventBgm.stop();
}

void FieldBgm::start() {
    if (Scene_InTown() != 0 || Scene_InTownUnk31() != 0) {
        hourlyBgm.start();
        specialBgm.start();
        eventBgm.start();
    }
}

void FieldBgm::end() {
    if (Scene_InTown() != 0 || Scene_InTownUnk31() != 0) {
        eventBgm.end();
        specialBgm.end();
        hourlyBgm.end();
    }
}

void FieldBgm::setKeep(u32 a) {
    hourlyBgm.setKeep(a);
    specialBgm.setKeep(a);
    eventBgm.setKeep(a);
}

RoomBgm::RoomBgm(BgmManager *a) {
    manager = a;
    currentScene = 0x3f;
    sceneBgm = 0xffff;
    closingFadeActive = 0;
    closingMusicPlaying = 0;
    closingForced = 0;
    active = 0;
    keep = 0;
}

RoomBgm::~RoomBgm() {}

void RoomBgm::init() {
    currentScene = 0x3f;
    sceneBgm = 0xffff;
    closingFadeActive = 0;
    closingMusicPlaying = 0;
    closingForced = 0;
    active = 0;
    keep = 0;
}

void RoomBgm::exit() { stop(); }

void RoomBgm::update() {
    if (active != 0) {
        updateSceneBgm();
        updateClosingMusic();
    }
}

void RoomBgm::stop() {
    stopSceneBgm();
    currentScene = 0x3f;
    stopClosingMusic();
    keep = 0;
    active = 0;
}

void RoomBgm::forceClosingMusic() { closingForced = 1; }

void RoomBgm::start() {
    active = 1;
    updateSceneBgm();
    updateClosingMusic();
}

void RoomBgm::end() {
    if (keep == 0) {
        BOOL r;
        if (closingMusicPlaying != 0 && Bgm_GetSceneFade()->hasExitSilence() != 0) r = TRUE; else r = FALSE;
        stopSceneBgm();
        currentScene = 0x3f;
        stopClosingMusic();
        closingForced = r;
    }
    active = 0;
}

void RoomBgm::setKeep(u32 a) { keep = a; }

extern "C" s32 Bgm_GetSceneBgmId(s32 a) {
    const u16 *e = sSceneBgmTable + sizeof(sSceneBgmTable) / sizeof(sSceneBgmTable[0]);
    u32 r = 0xffff;
    const u16 *p;
    for (p = sSceneBgmTable; p < e; p += 2) {
        if (((u8 *)p)[0] == a) { r = p[1]; break; }
    }
    return r;
}

extern "C" s32 Bgm_IsSameSceneBgm(void) {
    s32 a = Scene_GetCurrent();
    s32 b = SceneWarp_GetScene(Scene_GetWarpRequest());
    s32 x = Bgm_GetSceneBgmId(a);
    s32 y = Bgm_GetSceneBgmId(b);
    if (x == y && x != 0xffff) return TRUE;
    return FALSE;
}

void RoomBgm::playSceneBgm(s32 a) {
    s32 r = Bgm_GetSceneBgmId(a);
    u32 c = 0x7f, d = 0;
    if (r == 1) c = 0x38;
    if (r == 0x14 || r == 0x5c) d = 1;
    Bgm_Request(0x11, r, c, d);
    sceneBgm = r;
}

void RoomBgm::stopSceneBgm() {
    if (sceneBgm != 0xffff) {
        Bgm_Release(sceneBgm);
        sceneBgm = 0xffff;
    }
}

void RoomBgm::updateSceneBgm() {
    s32 t = Scene_GetCurrent();
    if (currentScene != t) {
        if (sceneBgm != Bgm_GetSceneBgmId(t)) {
            stopSceneBgm();
            playSceneBgm(t);
        }
        currentScene = t;
    }
}

void RoomBgm::stopClosingMusic() {
    if (closingFadeActive != 0) {
        Bgm_ReleasePriority(0x10);
        closingFadeActive = 0;
    }
    if (closingMusicPlaying != 0) {
        Bgm_Release(0x51);
        closingMusicPlaying = 0;
    }
    closingForced = 0;
}

extern "C" BgmClock *Bgm_GetClock(void) { return &data_021c1b3c->clock; }

void RoomBgm::updateClosingMusic() {
    BOOL a;
    void *p = PlayerData_GetCurrent();
    if (p) {
        if (((PlayerData *)(p))->testFlag(0x23) != 0 || ((PlayerData *)(p))->testFlag(1) != 0) {
            a = TRUE;
        } else {
            a = FALSE;
        }
    } else {
        a = FALSE;
    }
    s32 t = Scene_GetCurrent();
    BOOL b = t == 0x1f ? TRUE : FALSE;
    BOOL c = TRUE;
    if ((u8)(t + 0xe6) > 4 && b == 0) {
        c = FALSE;
    }
    if (a == 0 && c != 0) {
        BgmClock *pl = Bgm_GetClock();
        if (closingFadeActive == 0) {
            if (pl->isTimeInRange(0x16, 0x31, 0x32, 0x16, 0x32, 0) != 0) {
                Bgm_RequestSilence(0x10, 0xc8, 0);
                closingFadeActive = 1;
            }
        }
        if (closingMusicPlaying == 0) {
            if (pl->isTimeInRange(0x16, 0x32, 0, 0, 0, 0) != 0 || closingForced != 0) {
                Bgm_Request(0xf, 0x51, 0x7f, 0);
                closingMusicPlaying = 1;
            }
        }
    }
}

BgmVolumeChannel::BgmVolumeChannel() {
    clear();
}

BgmVolumeChannel::~BgmVolumeChannel() {}

void BgmVolumeChannel::clear() {
    changed = 0;
    masked = 0;
    volume = 0;
    fadeFrames = 0;
    state = 0;
}

void BgmVolumeChannel::set(s32 a, s32 b, u8 c) {
    volume = a;
    fadeFrames = b;
    changed = c;
}

BgmVolumeMixer::BgmVolumeMixer(BgmManager *owner) : manager(owner) {}

BgmVolumeMixer::~BgmVolumeMixer() {}

void BgmVolumeMixer::init() {
    for (s32 i = 0; i < 8; i++) {
        channels[i].clear();
    }
    talkDuckHold = 0;
}

void BgmVolumeMixer::exit() {}

void BgmVolumeMixer::update() {
    updateChannels();
    maskForTopRequest();
    applyVolume();
    clearChanged();
    clearMasks();
}

void BgmVolumeMixer::reset() {
    if ((u32)(channels[2].state - 8) <= 1) {
        Snd_RestoreSubPlayers();
    }
    for (s32 i = 0; i < 8; i++) {
        channels[i].clear();
    }
    talkDuckHold = 0;
}

void BgmVolumeMixer::startTalkDuck() { channels[2].state = 7; }

void BgmVolumeMixer::endTalkDuck() { channels[2].state = 9; }

void BgmVolumeMixer::setMenuDuck(s32 i) { channels[1].state = sBgmMenuDuckStates[i]; }

void BgmVolumeMixer::endMenuDuck() { channels[1].state = 6; }

void BgmVolumeMixer::startFishDuck() { channels[3].state = 0xa; }

void BgmVolumeMixer::endFishDuck() { channels[3].state = 0xc; }

void BgmVolumeMixer::startFireworkDuck() { channels[4].state = 0xd; }

void BgmVolumeMixer::endFireworkDuck() { channels[4].state = 0xf; }
const u16 sSceneBgmTable[0x3a] = {
    0x1a, 0x4d, 0x1b, 0x4e, 0x1c, 0x4f, 0x1d, 0x50,
    0x1e, 0x50, 0xa, 0x58, 0xb, 0x53, 0xc, 0x53,
    0xd, 0x53, 0xe, 0x53, 0x2f, 0x53, 0x2d, 0x1,
    0x20, 0x62, 0x21, 0x60, 0x22, 0x62, 0x23, 0x62,
    0x24, 0x62, 0x25, 0x62, 0x26, 0x62, 0x27, 0x62,
    0x28, 0x62, 0x29, 0x62, 0xf, 0x5a, 0x10, 0x5c,
    0x1f, 0x5e, 0x6, 0x4b, 0x7, 0x4b, 0x8, 0x4b,
    0x30, 0x14,
};

u16 sNewYearEveDate[2] = {0xc1f, 0};

u16 sNewYearEveTime[2] = {0x173b, 0};

u16 sNewYearDayDate[2] = {0x101, 0};

ProcProfile sBgmProcProfile = {(void *(*)())&BgmProc::create, 0xcf, 0xcb};

void BgmVolumeMixer::updateChannels() {
    static Unk_02035758_Fn tbl[8] = {
        &BgmVolumeMixer::updateChannel0, &BgmVolumeMixer::updateMenuDuck, &BgmVolumeMixer::updateTalkDuck,
        &BgmVolumeMixer::updateFishDuck, &BgmVolumeMixer::updateFireworkDuck, &BgmVolumeMixer::updatePositionDuck,
        &BgmVolumeMixer::updateSceneDuck, &BgmVolumeMixer::updateRequestVolume,
    };
    for (s32 i = 0; i < 8; i++) {
        (this->*tbl[i])(&channels[i]);
    }
}

void BgmVolumeMixer::updateChannel0(BgmVolumeChannel *e) {}

void BgmVolumeMixer::updateMenuDuck(BgmVolumeChannel *e) {
    s32 st = e->state;
    if (st == 2) {
        e->set(0x28, 5, 1);
        e->state = 5;
    } else if (st == 3) {
        e->set(0x7f, 5, 1);
        e->state = 5;
    } else if (st == 4) {
        e->set(0, 5, 1);
        e->state = 5;
    } else if (st != 5) {
        if (st == 6) {
            e->set(0x7f, 5, 1);
            e->state = 0;
        }
    }
}

void BgmVolumeMixer::updateTalkDuck(BgmVolumeChannel *e) {
    s32 st = e->state;
    if (st == 7) {
        e->set(0x28, 5, 1);
        e->state = 8;
        talkDuckHold = 0;
        Snd_DuckSubPlayers();
    } else if (st != 8) {
        if (st == 9) {
            if (talkDuckHold > 0) {
                talkDuckHold = talkDuckHold - 1;
            }
            if (talkDuckHold <= 0) {
                e->set(0x7f, 5, 1);
                e->state = 0;
                Snd_RestoreSubPlayers();
            }
        }
    }
}

void BgmVolumeMixer::updateFishDuck(BgmVolumeChannel *e) {
    s32 st = e->state;
    if (st == 0xa) {
        e->set(0x28, 0xf, 1);
        e->state = 0xb;
    } else if (st != 0xb) {
        if (st == 0xc) {
            e->set(0x7f, 0xf, 1);
            e->state = 0;
        }
    }
}

void BgmVolumeMixer::updateFireworkDuck(BgmVolumeChannel *e) {
    s32 st = e->state;
    if (st == 0xd) {
        e->set(0x28, 0xf, 1);
        e->state = 0xe;
    } else if (st != 0xe) {
        if (st == 0xf) {
            e->set(0x7f, 0xf, 1);
            e->state = 0;
        }
    }
}

void BgmVolumeMixer::updatePositionDuck(BgmVolumeChannel *e) {
    s32 st = e->state;
    s32 flag = 0;
    VecFx32Ctor *p = (VecFx32Ctor *)PlayerActor_GetBodyPos(4);
    if (p) {
        GroundInfo b1;
        (&b1)->initAtPos((VecFx32 *)(void *)(p), 0, 0);
        s32 k = b1.attr;
        VecFx32Ctor v(p->x, p->y, p->z + 0x2000);
        GroundInfo b2;
        (&b2)->initAtPos((VecFx32 *)(void *)(&v), 0, 0);
        s32 m = b2.waterKind;
        if (k == 0x13 || k == 0x16 || m == 1) {
            flag = 1;
        }
    }
    if (st == 0) {
        if (flag != 0) {
            e->set(0x28, 0x3c, 1);
            e->state = 0x10;
        }
    } else if (st == 0x10) {
        if (flag == 0) {
            e->set(0x7f, 0x3c, 1);
            e->state = 0;
        }
    }
}

void BgmVolumeMixer::updateSceneDuck(BgmVolumeChannel *e) {
    s32 st = e->state;
    s32 t = Scene_GetCurrent();
    BOOL a = t == 0x27 ? TRUE : FALSE;
    BOOL b = t == 0x28 ? TRUE : FALSE;
    if (st == 0) {
        if (a || b) {
            e->set(0x40, 0x28, 1);
            e->state = 0x11;
        }
    } else if (st == 0x11) {
        if (!a && !b) {
            e->set(0x7f, 0x28, 1);
            e->state = 0;
        }
    }
}

BOOL BgmRequestView::clearVolumePending() {
    volumePending = 0;
    return FALSE;
}
const u8 sBgmSceneFadeDelays[8] = {0x01, 0x2f, 0x1b, 0x34, 0x2f, 0x00, 0x00, 0x00};

void BgmVolumeMixer::updateRequestVolume(BgmVolumeChannel *e) {
    BgmManager *o = manager;
    if (o->numRequests > 0) {
        if (o->requests[0].volumePending != 0 && o->requests[0].volume != 0) {
            e->set(o->requests[0].volume, 0, 1);
        }
        manager->forEachRequest(&BgmRequestView::clearVolumePending);
        e->state = 0x12;
    } else {
        e->state = 0;
    }
}

void BgmVolumeMixer::maskForTopRequest() {
    BgmManager *o = manager;
    if (o->numRequests > 0 && o->requests[0].muteDucks != 0) {
        BgmVolumeChannel *p = &channels[2];
        BgmVolumeChannel *end = &channels[7];
        for (; p < end; p++) {
            p->masked = 1;
        }
    }
}

void BgmVolumeMixer::applyVolume() {
    BgmVolumeChannel *end;
    s32 f;
    s32 a;
    BOOL ok = FALSE;
    s32 t;
    s32 b;
    BgmManager *o = manager;
    BgmVolumeChannel *p;
    if (o->numRequests > 0 && o->requests[0].playing != 0 && o->requests[0].bgmId != 0xffff) {
        ok = TRUE;
    }
    if (ok) {
        p = &channels[7];
        end = &channels[0];
        f = 0;
        a = 0;
        b = 0;
        for (; p >= end; p--) {
            if (p->masked == 0) {
                t = p->state;
                if (p->changed != 0) {
                    f = 1;
                    b = p->fadeFrames;
                }
                if (t != 0) {
                    a = p->volume;
                }
            }
        }
        if (f != 0) {
            o->commands.requestVolume(a, b);
        }
    }
}

void BgmVolumeMixer::clearChanged() {
    for (s32 i = 0; i < 8; i++) {
        channels[i].changed = 0;
    }
}

void BgmVolumeMixer::clearMasks() {
    for (s32 i = 0; i < 8; i++) {
        channels[i].masked = 0;
    }
}

BgmCommandQueue::BgmCommandQueue(BgmManager *owner) {
    init(owner);
}

BgmCommandQueue *BgmCommandQueue::init(BgmManager *owner) {
    manager = owner;
    clear();
    return this;
}

void BgmCommandQueue::func_02035740() {}

void BgmCommandQueue::requestPlay(u16 a) {
    playPending = 1;
    playBgmId = a;
}

void BgmCommandQueue::requestStop(s32 a) {
    stopPending = 1;
    stopFadeFrames = a;
}

void BgmCommandQueue::requestVolume(s32 a, s32 b) {
    volumePending = 1;
    volume = a;
    volumeFrames = b;
}

void BgmCommandQueue::clear() {
    playPending = 0;
    playBgmId = 0xffff;
    stopPending = 0;
    stopFadeFrames = 0;
    volumePending = 0;
    volume = 0;
    volumeFrames = 0;
}

void BgmCommandQueue::flush() {
    if (stopPending != 0) {
        stopPending = 0;
        Snd_StopBgm(stopFadeFrames);
    }
    if (playPending != 0) {
        playPending = 0;
        Snd_PlayBgm(playBgmId);
        BgmTracks_OnBgmStart(&data_021c1b3c->tracks, playBgmId);
    }
    if (volumePending != 0) {
        volumePending = 0;
        Snd_MoveBgmVolume(volume, volumeFrames);
    }
}

BgmSceneFade::BgmSceneFade(BgmManager *owner) {
    manager = owner;
    keepForWarp = 0;
    sameSceneBgm = 0;
    keepRequested = 0;
    exitSilenceState = 0;
    fadeDelay = 0;
    releaseTimer = 0;
}

BgmSceneFade::~BgmSceneFade() {}

void BgmSceneFade::onFadeOut() {
    if (gActorDefaultParent->profile != 5) {
        if (exitSilenceState == 1) {
            Bgm_RequestSilence(8, 0xf, 0);
            exitSilenceState = 2;
        } else if (exitSilenceState == 3) {
            Bgm_ReleasePriority(8);
            exitSilenceState = 0;
        }
        sameSceneBgm = Bgm_IsSameSceneBgm();
        Bgm_GetRoomBgm()->setKeep(sameSceneBgm);
        if (keepForWarp == 0 && sameSceneBgm == 0 && keepRequested == 0) {
            if (fadeDelay != 0 || releaseTimer != 0) {
                Bgm_ReleasePriority(7);
            }
            fadeDelay = -1;
            releaseTimer = 0;
            Bgm_RequestSilence(7, 0xf, 0);
        } else {
            Bgm_GetFieldBgm()->setKeep(1);
            if (sameSceneBgm != 0) {
                BgmTracks_FadeOutForScene();
            }
        }
    }
}

extern "C" BgmTracks *Bgm_GetTracks(void) { return &data_021c1b3c->tracks; }

extern "C" FieldBgm *Bgm_GetFieldBgm(void) { return &data_021c1b3c->fieldBgm; }

extern "C" RoomBgm *Bgm_GetRoomBgm(void) { return &data_021c1b3c->roomBgm; }

void BgmSceneFade::onFadeIn() {
    if (gActorDefaultParent->profile != 5) {
        if (fadeDelay < 0) {
            s32 r = PlayerActor_GetActionOrSpawnAction();
            if (r != 0x3c) {
                if (r == 0x8b) {
                    fadeDelay = 0x21;
                } else if (r == 0x8e) {
                    fadeDelay = 0x21;
                } else if (r == 0x43) {
                    fadeDelay = 0x21;
                } else if (r == 0x44) {
                    fadeDelay = 0x21;
                } else if (r == 2) {
                    fadeDelay = 0x19;
                } else {
                    fadeDelay = 0x14;
                }
            }
        }
        if (sameSceneBgm != 0) {
            BgmTracks_FadeInForScene();
        }
        keepForWarp = 0;
        sameSceneBgm = 0;
        keepRequested = 0;
        Bgm_GetFieldBgm()->setKeep(0);
        Bgm_GetRoomBgm()->setKeep(0);
    }
}

void BgmSceneFade::init() {}

extern "C" void BgmSceneFade_Reset(BgmSceneFade *p) { p->reset(); }

extern "C" void BgmSceneFade_Update(void *p) { ((BgmSceneFade *)(p))->update(); }

void BgmSceneFade::reset() {
    keepForWarp = 0;
    sameSceneBgm = 0;
    keepRequested = 0;
    exitSilenceState = 0;
    if (fadeDelay != 0 || releaseTimer != 0) {
        Bgm_ReleasePriority(7);
        fadeDelay = 0;
        releaseTimer = 0;
    }
}

void BgmSceneFade::prepareEventWarp(s32 a, s32 b) {
    s32 res = 0;
    s32 f = 0;
    if (Scene_InTown()) {
        s32 a0 = (a == 0) ? 1 : 0;
        s32 a1 = (a == 1) ? 1 : 0;
        s32 a2 = (a == 2) ? 1 : 0;
        s32 b9 = (b == 9) ? 1 : 0;
        s32 b6 = (b == 6) ? 1 : 0;
        BgmRequest *rec = Bgm_GetPlayingRequest();
        u32 x;
        s32 y;
        if (rec) x = rec->bgmId; else x = 0xffff;
        if (rec) y = rec->priority; else y = 0x25;
        s32 ff = (x == 0xffff) ? 1 : 0;
        s32 y24 = (y == 0x24) ? 1 : 0;
        s32 y1a = (y == 0x1a) ? 1 : 0;
        if (a1) {
            if (b6) res = 1;
            else if (b9) {
                if (y1a || ff) res = 1;
                else if (y24) {
                    if ((u16)(x + 0xffd4) <= 1) res = 1;
                }
            } else {
                if (y1a || ff) res = 1;
            }
        } else if (a2) {
            if (b6) {
                res = 1;
                f = 1;
            } else if (b9) {
            } else if (y1a || ff) res = 1;
        } else if (a0) {
            if (y1a || ff) res = 1;
        }
    } else {
        res = 1;
        f = 1;
    }
    if (!res) keepForWarp = 1;
    if (f) exitSilenceState = 1;
}

void BgmSceneFade::prepareEventReturn(s32 a, s32 b) {
    if (exitSilenceState == 2) {
        exitSilenceState = 3;
    } else {
        BOOL c = (a == 0) ? TRUE : FALSE;
        BOOL d = (a == 1) ? TRUE : FALSE;
        BOOL e = FALSE;
        if (a == 2 && b == 6) e = TRUE;
        if (c || d || !e) keepForWarp = 1;
    }
}

void BgmSceneFade::setFadeDelay(s32 i) { fadeDelay = sBgmSceneFadeDelays[i]; }

void BgmSceneFade::setKeepBgm() { keepRequested = 1; }

BOOL BgmSceneFade::isKeepingBgm() {
    if (keepForWarp || sameSceneBgm || keepRequested) return TRUE;
    return FALSE;
}

BOOL BgmSceneFade::hasExitSilence() {
    if (exitSilenceState) return TRUE;
    return FALSE;
}

void BgmSceneFade::update() {
    if (fadeDelay > 0) {
        fadeDelay -= TICK_STEP_ENDS() ? 1 : 0;
        if (fadeDelay <= 0) {
            s32 v = 1;
            if (IsZero(gFieldSceneKind) && Scene_InTown()) {
                u16 buf[2];
                BOOL ok;
                PlayerActor_GetSlotHeldItem(buf, 4);
                if (Item_IsFurniture(buf)) {
                    buf[1] = 0xfff1;
                    if (Item_GetFurnitureIndex(buf) == Item_GetFurnitureIndex(&buf[1])) ok = TRUE;
                    else ok = FALSE;
                } else {
                    if (buf[0] == 0xfff1) ok = TRUE;
                    else ok = FALSE;
                }
                if (!ok) v = 20;
            }
            releaseTimer = v;
        }
    }
    if (releaseTimer > 0) {
        releaseTimer -= TICK_STEP_ENDS() ? 1 : 0;
        if (releaseTimer <= 0) Bgm_ReleasePriority(7);
    }
}

FaintBgm::FaintBgm(BgmManager *o) {
    manager = o;
    currentBgm = 0xffff;
    silenceActive = 0;
}

FaintBgm::~FaintBgm() {}

extern "C" BgmSceneFade *Bgm_GetSceneFade(void) { return &data_021c1b3c->sceneFade; }

void FaintBgm::play() {
    currentBgm = 0x41;
    Bgm_Request(0xb, 0x41, 0x7f, 1);
    Bgm_GetSceneFade()->setKeepBgm();
}

void FaintBgm::startSilence() {
    silenceActive = 1;
    Bgm_RequestSilence(10, 15, 0);
}

void FaintBgm::fadeOut() {
    if (currentBgm != 0xffff) {
        Bgm_RequestSilence(10, 5, 5);
        Bgm_Release(currentBgm);
        currentBgm = 0xffff;
    }
    if (silenceActive) {
        Bgm_ReleasePriority(10);
        Bgm_RequestSilence(10, 5, 5);
        silenceActive = 0;
    }
}

void FaintBgm::init() {}

void FaintBgm::exit() { stop(); }

extern "C" void FaintBgm_Update(void) {}

void FaintBgm::stop() {
    if (currentBgm != 0xffff) {
        Bgm_Release(currentBgm);
        currentBgm = 0xffff;
    }
    if (silenceActive) {
        Bgm_ReleasePriority(10);
        silenceActive = 0;
    }
}

BgmTracks::BgmTracks() {}

BgmTracks::~BgmTracks() {}

extern "C" void BgmTracks_FadeOutForScene(void) {
    s32 r = Scene_GetCurrent();
    s32 s;
    s = SceneWarp_GetScene(Scene_GetWarpRequest());
    s32 a22 = (r == 0x22) ? 1 : 0;
    s32 a25 = (r == 0x25) ? 1 : 0;
    s32 a29 = (r == 0x29) ? 1 : 0;
    s32 e20 = (s == 0x20) ? 1 : 0;
    s32 b22 = (s == 0x22) ? 1 : 0;
    s32 b23 = (s == 0x23) ? 1 : 0;
    s32 b25 = (s == 0x25) ? 1 : 0;
    s32 b27 = (s == 0x27) ? 1 : 0;
    s32 b29 = (s == 0x29) ? 1 : 0;
    s32 v = 0;
    if (r == 0x20 && (b22 || b23 || b25 || b27 || b29)) v = 1;
    else if (a29 && e20) v = 2;
    else if (a25 && e20) v = 3;
    else if (a22 && e20) v = 4;
    if (v) Snd_FadeOutBgmTracks(v);
}

extern "C" void BgmTracks_FadeInForScene(void) {
    s32 t = Scene_GetPrevious();
    s32 r = Scene_GetCurrent();
    s32 e20 = (t == 0x20) ? 1 : 0;
    s32 a22 = (t == 0x22) ? 1 : 0;
    s32 a23 = (t == 0x23) ? 1 : 0;
    s32 a25 = (t == 0x25) ? 1 : 0;
    s32 a27 = (t == 0x27) ? 1 : 0;
    s32 a29 = (t == 0x29) ? 1 : 0;
    s32 b22 = (r == 0x22) ? 1 : 0;
    s32 b25 = (r == 0x25) ? 1 : 0;
    s32 b29 = (r == 0x29) ? 1 : 0;
    s32 v = 0;
    if (r == 0x20 && (a22 || a23 || a25 || a27 || a29)) v = 1;
    else if (b29 && e20) v = 2;
    else if (b25 && e20) v = 3;
    else if (b22 && e20) v = 4;
    if (v) Snd_FadeInBgmTracks(v);
}

extern "C" void BgmTracks_FadeOutScene22(void) {
    if (Scene_GetCurrent() == 0x22) Snd_FadeOutBgmTracks(5);
}

extern "C" void BgmTracks_FadeInScene22(void) {
    if (Scene_GetCurrent() == 0x22) Snd_FadeInBgmTracks(5);
}

extern "C" void BgmTracks_OnBgmStart(BgmTracks *a, s32 b) {
    if (b == 0x62) BgmTracks_ApplySceneMask();
}

extern "C" void BgmTracks_Update(BgmTracks *a) {
    if (Scene_InTown() || Scene_InTownUnk31()) BgmTracks_UpdateWeatherVariant(a);
}

extern "C" void BgmTracks_ApplySceneMask(void) {
    s32 r = Scene_GetCurrent();
    s32 a22 = (r == 0x22) ? 1 : 0;
    s32 a23 = (r == 0x23) ? 1 : 0;
    s32 a24 = (r == 0x24) ? 1 : 0;
    s32 a25 = (r == 0x25) ? 1 : 0;
    s32 a26 = (r == 0x26) ? 1 : 0;
    s32 a27 = (r == 0x27) ? 1 : 0;
    s32 a28 = (r == 0x28) ? 1 : 0;
    s32 a29 = (r == 0x29) ? 1 : 0;
    s32 v = 0;
    if (r == 0x20) v = 6;
    else if (a23 || a24 || a27 || a28) v = 0xb;
    else if (a29) v = 0xc;
    else if (a25 || a26) v = 0xd;
    else if (a22) v = 0xe;
    if (v) Snd_FadeOutBgmTracks(v);
}

extern "C" void BgmTracks_UpdateWeatherVariant(BgmTracks *x) {
    s32 r = Weather_GetPrecipKind();
    s32 a, b;
    BOOL c, d, e;
    Weather_GetLevels(&a, &b);
    if (b >= 3) c = TRUE; else c = FALSE;
    d = FALSE;
    if (c && r == 1) d = TRUE;
    e = FALSE;
    if (c && r == 2) e = TRUE;
    s32 v;
    if (d) v = 0xc;
    else if (e) v = 0xd;
    else v = 0xb;
    Snd_SetBgmTrackVariant(v);
}

extern "C" void Bgm_Request(s32 a, s32 b, s32 c, u8 d) {
    BgmRequest e(a, b, c, 0, d);
    data_021c1b3c->push(static_cast<BgmRequestView *>(&e));
}

extern "C" void Bgm_RequestSilence(s32 a, s32 b, s32 c) {
    BgmRequest e(a, 0xffff, 0, b, 0);
    if (c > 0) e.lifetime = c;
    data_021c1b3c->push(static_cast<BgmRequestView *>(&e));
}

extern "C" void Bgm_RequestTransient(s32 a, s32 b) {
    BgmRequest e(a, b, 0x7f, 0, 0);
    e.transient = 1;
    data_021c1b3c->push(static_cast<BgmRequestView *>(&e));
}

extern "C" void Bgm_Release(s32 a) { data_021c1b3c->releaseBgm(a); }

extern "C" void Bgm_ReleasePriority(s32 a) { data_021c1b3c->releasePriority(a); }

extern "C" void Bgm_ReleaseTransient(s32 a) { data_021c1b3c->releaseBgm(a); }

extern "C" u16 Bgm_GetCurrent(void) {
    s32 i = ((BgmManager *)data_021c1b3c)->findPlaying();
    u16 r = 0xffff;
    if (i >= 0) r = data_021c1b3c->requests[i].bgmId;
    return r;
}

extern "C" void Bgm_EnableHourChime(void) { data_021c1b3c->hourChimeDisabled = 0; }

extern "C" void Bgm_DisableHourChime(void) { data_021c1b3c->hourChimeDisabled = 1; }

BgmManager::BgmManager() : numRequests(0), mixer(this), fieldBgm(this), roomBgm(this), commands(this), sceneFade(this), faintBgm(this) {
    hourChimeDisabled = 0;
}

BgmManager::~BgmManager() {}

void BgmManager::init() {
    BgmRequest *p, *end;
    data_021c1b3c = this;
    end = (BgmRequest *)&numRequests;
    for (p = requests; p < end; p++) {
        p->clear();
    }
    numRequests = 0;
    mixer.init();
    BgmClock_Init(&clock);
    fieldBgm.init();
    roomBgm.init();
    commands.clear();
    sceneFade.init();
    faintBgm.init();
    hourChimeDisabled = 0;
}

void BgmManager::exit() {
    faintBgm.exit();
    BgmSceneFade_Reset(&sceneFade);
    commands.clear();
    roomBgm.exit();
    fieldBgm.exit();
    BgmClock_Exit();
    mixer.exit();
    data_021c1b3c = 0;
}

void BgmManager::update() {
    FaintBgm_Update();
    BgmSceneFade_Update(&sceneFade);
    BgmClock_Update(&clock);
    fieldBgm.update();
    roomBgm.update();
    updateRequests();
    updateHourChime();
    postUpdate();
}

extern "C" void Bgm_ResetAll() {
    BgmManager *p;
    BgmRequest *e, *end;
    data_021c1b3c->faintBgm.stop();
    data_021c1b3c->sceneFade.reset();
    data_021c1b3c->commands.clear();
    data_021c1b3c->roomBgm.stop();
    data_021c1b3c->fieldBgm.stop();
    BgmClock_Reset(&data_021c1b3c->clock);
    data_021c1b3c->mixer.reset();
    e = data_021c1b3c->requests;
    end = &data_021c1b3c->requests[16];
    for (; e < end; e++) {
        e->clear();
    }
    data_021c1b3c->numRequests = 0;
    data_021c1b3c->hourChimeDisabled = 0;
}

extern "C" void Bgm_StartSceneBgm() {
    if (Unk_02034938_IsA()) {
        data_021c1b3c->fieldBgm.start();
    } else if (Unk_02034938_IsB()) {
        data_021c1b3c->roomBgm.start();
    }
}

extern "C" void Bgm_EndSceneBgm() {
    if (Unk_02034938_IsA()) {
        data_021c1b3c->fieldBgm.end();
    } else if (Unk_02034938_IsB()) {
        data_021c1b3c->roomBgm.end();
    }
}

extern "C" BgmRequest *Bgm_GetPlayingRequest() {
    s32 i = data_021c1b3c->findPlaying();
    BgmRequest *p = NULL;
    if (i >= 0) {
        p = &data_021c1b3c->requests[i];
    }
    return p;
}

void BgmManager::push(BgmRequestView *e) {
    s32 i = findInsertPos(e);
    if (i >= 0) {
        insertAt(i);
        requests[i].copyFrom(e);
    }
}

void BgmManager::releasePriority(s32 v) {
    s32 i = findByPriority(v);
    if (i >= 0 && i < numRequests) {
        requests[i].removePending = 1;
    }
}

void BgmManager::releaseBgm(u16 id) {
    s32 i = findByBgm(id);
    if (i >= 0 && i < numRequests) {
        requests[i].removePending = 1;
    }
}

void BgmManager::updateRequests() {
    updateStop();
    removeMarked();
    startTop();
    mixer.update();
    commands.flush();
    BgmTracks_Update(&tracks);
    tickRequests();
}

void BgmManager::updateStop() {
    s32 i = findPlaying();
    BgmRequest *p;
    if (i >= 0) {
        p = &requests[i];
        if (p->bgmId != 0xffff) {
            BOOL done = FALSE;
            if (i > 0) {
                BgmRequest *q = findKeptBefore(i);
                if (q != NULL) {
                    commands.requestStop(q->stopFadeFrames);
                    done = TRUE;
                }
            }
            if (!done) {
                if (p->removePending != 0) {
                    commands.requestStop(p->stopFadeFrames);
                }
            }
        }
    }
}

void BgmManager::removeMarked() {
    s32 i, j, last;
    for (i = numRequests - 1; i >= 0; i--) {
        if (requests[i].removePending != 0) {
            last = numRequests - 1;
            for (j = i; j < last; j++) {
                requests[j].copyFrom(&requests[j + 1]);
            }
            requests[last].clear();
            numRequests = last;
        }
    }
}

void BgmManager::clearPlaying() { requests[0].playing = 0; }
const s32 sBgmMenuDuckStates[3] = {2, 3, 4};

void BgmManager::startTop() {
    if (numRequests > 0 && requests[0].playing == 0) {
        if (requests[0].bgmId != 0xffff) {
            commands.requestPlay(requests[0].bgmId);
            requests[0].volumePending = 1;
        }
        forEachRequest(&BgmRequestView::clearPlaying);
        requests[0].playing = 1;
    }
}

void BgmManager::tickRequests() {
    BgmRequest *end = &requests[numRequests];
    BgmRequest *p;
    for (p = requests; p < end; p++) {
        if (p->tickLifetime()) {
            p->removePending = 1;
        }
        if (p != requests && p->transient != 0) {
            p->removePending = 1;
        }
    }
}

s32 BgmManager::findInsertPos(BgmRequestView *key) {
    s32 r = -1;
    s32 n = numRequests;
    if (n < 16) {
        for (r = 0; r < n; r++) {
            if (requests[r].priority > key->priority) {
                break;
            }
        }
    }
    return r;
}

s32 BgmManager::findPlaying() {
    s32 r = -1;
    s32 i;
    for (i = 0; i < numRequests; i++) {
        if (requests[i].playing != 0) {
            r = i;
            break;
        }
    }
    return r;
}

s32 BgmManager::findByPriority(s32 v) {
    s32 r = -1;
    s32 i;
    for (i = 0; i < numRequests; i++) {
        s32 c = requests[i].priority;
        if (c == v) {
            r = i;
            break;
        }
    }
    return r;
}

s32 BgmManager::findByBgm(u16 id) {
    s32 r = -1;
    s32 i;
    for (i = 0; i < numRequests; i++) {
        u16 c = requests[i].bgmId;
        if (c == id) {
            r = i;
            break;
        }
    }
    return r;
}

BgmRequest *BgmManager::findKeptBefore(s32 n) {
    BgmRequest *r = NULL;
    s32 i;
    for (i = 0; i < n; i++) {
        BgmRequest *p = &requests[i];
        if (p->removePending == 0) {
            r = p;
            break;
        }
    }
    return r;
}

void BgmManager::insertAt(s32 idx) {
    s32 i;
    if (numRequests > 0) {
        for (i = numRequests - 1; i >= idx; i--) {
            requests[i + 1].copyFrom(&requests[i]);
        }
    }
    numRequests++;
}

void BgmManager::forEachRequest(Unk_02034574_Fn fn) {
    s32 i;
    for (i = 0; i < numRequests; i++) {
        (((BgmRequestView *)&requests[i])->*fn)();
    }
}

void BgmManager::updateHourChime() {
    if (clock.hasHourChanged()) {
        BOOL ok = TRUE;
        if (!Scene_GetSkyKind(1)) {
            ok = FALSE;
        }
        if (Scene_InTown()) {
            if (Taxi_IsArriving()) {
                ok = FALSE;
            }
        }
        if (hourChimeDisabled) {
            ok = FALSE;
        }
        if (ok) {
            Melody_StartTrackA(clock.hasYearChanged());
        }
    }
}

void BgmManager::postUpdate() {}

BgmProc *BgmProc::create() { return new BgmProc(); }

BgmProc::BgmProc() {}

BgmProc::~BgmProc() {}

BOOL BgmProc::onCreate() {
    bgmManager.init();
    return TRUE;
}

BOOL BgmProc::onExecute() {
    bgmManager.update();
    return TRUE;
}

BOOL BgmProc::onDelete() {
    bgmManager.exit();
    return TRUE;
}

const u16 sHourlyBgmIds[0x18] = {
    0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
    0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
    0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
};
