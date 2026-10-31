#include "types.h"
#include "net/gpiOperation.h"
#include "net/gpi.h"
#include "net/gpiPeer.h"
#include "net/gp.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/autoload_2/unk_0212b770.h"
#include "proto/ov065/unk_ov065_02277974.h"
#include "proto/ov065/unk_ov065_0227df0c.h"
#include "proto/ov065/unk_ov065_02283720.h"















extern "C" {
s32 strncmp(const char *, const char *, s32);
s32 OS_SPrintf(char *, const char *, ...);
s32 gpiValueForKey(const char *, const char *, char *, s32);
void gpiSetErrorString(void *, const char *);
void gpiSetError(void *, s32, const char *);
s32 recv(s32, void *, s32, s32);
s32 send(s32, void *, s32, s32);
s32 GOAGetLastError(s32);
s32 ArrayLength(s32);
s32 shutdown(s32, s32);
s32 closesocket(s32);
s32 gpiRemoveOperation(void *, void *);
s32 gpiDestroyPeer(void *, void *);
s32 gpiProfileMap(void *, s32, s32);
s32 gpiDisconnectCleanupProfile(void);

s32 gpiSendData(void *, s32, char *, s32, s32 *, s32 *, const char *);
s32 gpiAppendIntToBuffer(GPConnection *, GPIBuffer *, s32);
s32 gpiAppendStringToBuffer(GPConnection *, GPIBuffer *, const char *);
s32 gpiAppendStringToBufferLen(GPConnection *, GPIBuffer *, const char *, s32);
s32 gpiAppendCharToBuffer(GPConnection *, GPIBuffer *, char);
s32 gpiSendOrBufferStringLen(GPConnection *, GPIPeer *, const char *, s32);
s32 gpiSendFromBuffer(GPConnection *, s32, GPIBuffer *, s32 *, s32, const char *);
s32 gpiCallCallback(GPConnection *, GPICallbackData *);
s32 gpiAddCallback(GPConnection *, GPICallbackCopy, void *, GPIOperation *, s32);
void gpiCallErrorCallback(GPConnection *, s32, s32);
}

extern "C" {
s32 gpiAddCallback(GPConnection *h, GPICallbackCopy p, void *m, GPIOperation *g, s32 k) {
    GPIConnection *ctx = *h;
    GPICallbackData *node = (GPICallbackData *)GsUtil_Alloc(sizeof(GPICallbackData));
    if (node == NULL) {
        gpiSetErrorString(h, "Out of memory.");
        return 1;
    }
    *(GPICallbackCopy *)node = p;
    node->arg = m;
    if (g != NULL) {
        node->operationID = g->id;
    } else {
        node->operationID = 0;
    }
    node->type = k;
    node->pnext = NULL;
    if (ctx->callbackList == NULL) {
        ctx->callbackList = node;
    }
    if (ctx->lastCallback != NULL) {
        ctx->lastCallback->pnext = node;
    }
    ctx->lastCallback = node;
    return 0;
}
}

extern "C" {
s32 gpiCallCallback(GPConnection *h, GPICallbackData *n) {
    s32 i;
    s32 k;
    n->callback(h, n->arg, n->param);
    k = n->type;
    if (k == 2) {
        GsUtil_Free(((GPRecvBuddyMessageArg *)n->arg)->message);
        ((GPRecvBuddyMessageArg *)n->arg)->message = 0;
    } else if (k == 3) {
        GPGetUserNicksResponseArg *d = (GPGetUserNicksResponseArg *)n->arg;
        for (i = 0; i < d->numNicks; i++) {
            GsUtil_Free((void *)d->nicks[i]);
            d->nicks[i] = 0;
            GsUtil_Free((void *)d->uniquenicks[i]);
            d->uniquenicks[i] = 0;
        }
        GsUtil_Free(d->nicks);
        d->nicks = NULL;
        GsUtil_Free(d->uniquenicks);
        d->uniquenicks = NULL;
    } else if (k == 4) {
        GPFindPlayersResponseArg *d = (GPFindPlayersResponseArg *)n->arg;
        GsUtil_Free(d->matches);
        d->matches = 0;
    } else if (k == 7) {
        GPTransferCallbackArg *d = (GPTransferCallbackArg *)n->arg;
        if (d->message != 0) {
            GsUtil_Free(d->message);
            d->message = 0;
        }
    } else if (k == 8) {
        GPGetReverseBuddiesResponseArg *d = (GPGetReverseBuddiesResponseArg *)n->arg;
        if (d->profiles != 0) {
            GsUtil_Free(d->profiles);
            d->profiles = 0;
        }
    } else if (k == 9) {
        GPSuggestUniqueNickResponseArg *d = (GPSuggestUniqueNickResponseArg *)n->arg;
        for (i = 0; i < d->numSuggestedNicks; i++) {
            GsUtil_Free((void *)d->suggestedNicks[i]);
            d->suggestedNicks[i] = 0;
        }
        GsUtil_Free(d->suggestedNicks);
        d->suggestedNicks = NULL;
    }
    GsUtil_Free(n->arg);
    n->arg = NULL;
    GsUtil_Free(n);
    return 0;
}
}

extern "C" {
s32 gpiProcessCallbacks(GPConnection *h, s32 key) {
    GPIConnection *ctx = *h;
    GPICallbackData *head;
    GPICallbackData *tail;
    GPICallbackData *prev;
    GPICallbackData *node;
    GPICallbackData *next;
    if (key != 0) {
        head = ctx->callbackList;
        tail = ctx->lastCallback;
        prev = NULL;
        ctx->callbackList = NULL;
        ctx->lastCallback = NULL;
        node = head;
        if (node != NULL) {
            do {
                next = node->pnext;
                if (node->operationID == key || node->type == 1) {
                    if (prev != NULL) {
                        prev->pnext = next;
                    } else {
                        head = next;
                    }
                    if (tail == node) {
                        tail = prev;
                    }
                    gpiCallCallback(h, node);
                } else {
                    prev = node;
                }
                node = next;
            } while (node != NULL);
        }
        if (ctx->callbackList != NULL) {
            ctx->lastCallback->pnext = head;
            ctx->lastCallback = tail;
        } else {
            ctx->callbackList = head;
            ctx->lastCallback = tail;
        }
        return 0;
    }
    node = ctx->callbackList;
    if (node != NULL) {
        do {
            ctx->callbackList = NULL;
            ctx->lastCallback = NULL;
            if (node != NULL) {
                do {
                    next = node->pnext;
                    gpiCallCallback(h, node);
                    node = next;
                } while (node != NULL);
            }
            node = ctx->callbackList;
        } while (node != NULL);
    }
    return 0;
}
}
