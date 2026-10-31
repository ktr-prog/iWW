#ifndef ROOM_ROOMTELEPHONEACTENTRY_H
#define ROOM_ROOMTELEPHONEACTENTRY_H

#include "types.h"

class RoomTelephone;
typedef void (RoomTelephone::*RoomTelephoneActFn)();

struct RoomTelephoneActEntry {
    RoomTelephoneActFn enter;
    RoomTelephoneActFn exec;
};

#endif
