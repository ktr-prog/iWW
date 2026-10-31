#ifndef GAME_SCENEINFO_H
#define GAME_SCENEINFO_H

#include "types.h"
#include "town/SceneMapInfo.h"

struct SceneWarp;


struct SceneSpawnRecord {
    union {
        /* 0x00 */ u32 w[5];
        struct {
            /* 0x00 */ u16 profile;
            /* 0x02 */ s16 x;
            /* 0x04 */ s16 y;
            /* 0x06 */ s16 z;
            /* 0x08 */ u8 rot[8];
            /* 0x10 */ u32 spawnParam;
        } actor;
    };
};

class SceneSpawnGroup {
public:
    BOOL createProcs(u8 *idx, u64 start);
    BOOL spawnPlayersAndCamera(u8 *idx, u64 start);

    /* 0x00 */ u8 kind;
    /* 0x01 */ u8 count;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ void *list;
};

#define ROOM_COMMON_PROFILE_COUNT 0x11
#define FIELD_SCENE_PROFILE_COUNT 0xe

class SceneSpawnList {
public:
    BOOL run(u8 *entryIdx, u8 *subIdx, u64 start);

    /* 0x00 */ u16 count;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ SceneSpawnGroup *groups;
};

struct SceneWarpList {
    /* 0x00 */ SceneWarp *warps;
    /* 0x04 */ u8 count;
};

class SceneInfo {
public:
    BOOL runSpawnList(u8 *entryIdx, u8 *subIdx, u64 start);
    void createSceneMapModule();

    /* 0x00 */ SceneSpawnList *spawnList;
    /* 0x04 */ u8 isOutdoor;
    /* 0x08 */ SceneMapInfo *mapInfo;
    /* 0x0c */ SceneWarpList *warps;
    /* 0x10 */ s32 infoOverlayA;
    /* 0x14 */ s32 infoOverlayB;
};

#endif
