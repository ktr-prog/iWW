#ifndef TOWN_TOWNMAPMARKERS_H
#define TOWN_TOWNMAPMARKERS_H

#include "types.h"

struct TownMapMarker {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ u8 z;
};

class TownMapMarkers {
public:
    /* 0x00 */ TownMapMarker e[17];
    TownMapMarkers();
    ~TownMapMarkers();
};

class TownMapAcreImage {
public:
    u8 b[0x200];
    TownMapAcreImage();
    ~TownMapAcreImage();
};

class TownMapImage {
public:
    /* 0x0000 */ TownMapAcreImage tile[16];
    /* 0x2000 */ TownMapMarkers icons;
    TownMapImage();
};

#endif
