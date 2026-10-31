#include "types.h"
#include "net/SockCoreConfig.h"
#include "net/SockCoreCommand.h"
#include "net/SockCoreSocket.h"
#include "sys/OSMessageQueue.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/ov065/unk_ov065_0225f378.h"

extern "C" {
extern SockCoreConfig *sSockCoreConfig;

u32 OS_DisableInterrupts(void);
void OS_DisableScheduler(void);
s32 OS_ReceiveMessage(void *, void *, s32);
s32 OS_SendMessage(void *, void *, s32);
void OS_EnableScheduler(void);
void OS_RestoreInterrupts(u32);
void OS_InitMessageQueue(void *, void *, s32);
s32 OS_ReadMessage(void *, void *, s32);

void SockCore_CommandThreadMain(void *);
s32 SockCore_ExecCommand(SockCoreSocket *, SockCoreCommand *);
s32 SockCore_ExecOnSendSide(SockCoreSocket *, SockCoreCommand *);
s32 SockCore_ExecOnRecvSide(SockCoreSocket *, SockCoreCommand *);
s32 SockCore_PostCommandAndWait(void *, SockCoreCommand *);
s32 SockCore_PostCommandAsync(SockCoreSocket *, SockCoreCommand *);
s32 SockCore_PostCommand(void *, SockCoreCommand *);
void *SockCore_GetCommandQueue(SockCoreSocket *);
void SockCore_FreeMsg(void *);
SockCoreCommand *SockCore_AllocMsg(void *, SockCoreSocket *, s32);
SockCoreCommand *SockCore_TakeFreeMsg(s32);
s32 SockCore_DestroyMsgPool(void);
s32 SockCore_CreateMsgPool(s32);
}

extern "C" {
void *sSockMsgPool;
OSMessageQueue sSockMsgFreeQueue;

s32 SockCore_CreateMsgPool(s32 n)
{
    u32 a = (n * sizeof(OSMessage) + 3) & ~3;
    u32 b = (n * SOCK_MSG_SIZE + 3) & ~3;
    u8 *p = (u8 *)sSockCoreConfig->alloc(b + a);
    u8 *e;
    if (p == NULL) {
        return -1;
    }
    OS_InitMessageQueue(&sSockMsgFreeQueue, p, n);
    e = p + a;
    while (n > 0) {
        SockCore_FreeMsg(e);
        e += SOCK_MSG_SIZE;
        n--;
    }
    sSockMsgPool = p;
    return 0;
}

s32 SockCore_DestroyMsgPool(void)
{
    if (sSockMsgFreeQueue.usedCount < sSockMsgFreeQueue.msgCount) {
        return -1;
    }
    sSockCoreConfig->free(sSockMsgPool);
    sSockMsgPool = NULL;
    return 0;
}

SockCoreCommand *SockCore_TakeFreeMsg(s32 c)
{
    SockCoreCommand *m;
    if (OS_ReceiveMessage(&sSockMsgFreeQueue, &m, c)) {
        return m;
    }
    return NULL;
}

SockCoreCommand *SockCore_AllocMsg(void *fn, SockCoreSocket *o, s32 c)
{
    SockCoreCommand *m = SockCore_TakeFreeMsg(c);
    if (m != NULL) {
        m->handler = (s32 (*)(SockCoreCommand *))fn;
        m->sock = o;
        m->replyQueue = NULL;
        m->sockType = o->sockType;
        m->blocking = c;
    }
    return m;
}

void SockCore_FreeMsg(void *m)
{
    if (m != NULL) {
        OS_SendMessage(&sSockMsgFreeQueue, m, 0);
    }
}

void *SockCore_GetCommandQueue(SockCoreSocket *o)
{
    void *p = o->recvPipe;
    if (p == NULL) {
        p = o->sendPipe;
    }
    return p;
}

s32 SockCore_PostCommand(void *q, SockCoreCommand *m)
{
    s32 flag;
    s32 r;
    if (m != NULL) {
        flag = m->blocking;
    } else {
        flag = 1;
    }
    r = OS_SendMessage(q, m, flag);
    if (r == 0) {
        SockCore_FreeMsg(m);
    }
    if (r != 0) {
        return 0;
    }
    return -0x2a;
}

s32 SockCore_PostCommandAsync(SockCoreSocket *o, SockCoreCommand *m)
{
    return SockCore_PostCommand(SockCore_GetCommandQueue(o), m);
}

s32 SockCore_PostCommandAndWait(void *q, SockCoreCommand *m)
{
    s32 res;
    OSMessage buf;
    OSMessageQueue lq;
    if (m->blocking == 0) {
        m->replyQueue = NULL;
        res = SockCore_PostCommand(q, m);
    } else {
        OSMessage reply;
        OS_InitMessageQueue(&lq, &buf, 1);
        m->replyQueue = &lq;
        SockCore_PostCommand(q, m);
        OS_ReceiveMessage(&lq, &reply, 1);
        res = (s32)(sptr)reply;
    }
    return res;
}

s32 SockCore_ExecOnRecvSide(SockCoreSocket *o, SockCoreCommand *m)
{
    return SockCore_PostCommandAndWait(o->recvPipe, m);
}

s32 SockCore_ExecOnSendSide(SockCoreSocket *o, SockCoreCommand *m)
{
    return SockCore_PostCommandAndWait(o->sendPipe, m);
}

s32 SockCore_ExecCommand(SockCoreSocket *o, SockCoreCommand *m)
{
    return SockCore_PostCommandAndWait(SockCore_GetCommandQueue(o), m);
}

void SockCore_CommandThreadMain(void *q)
{
    SockCoreCommand *m;
    for (;;) {
        OS_ReadMessage(q, &m, 1);
        if (m == NULL) {
            break;
        }
        s32 r = m->handler(m);
        u32 irq = OS_DisableInterrupts();
        OS_DisableScheduler();
        OS_ReceiveMessage(q, 0, 0);
        if (m->sock != NULL) {
            m->sock->result = r;
        }
        if (m->replyQueue != NULL) {
            OS_SendMessage(m->replyQueue, (OSMessage)(sptr)r, 0);
        }
        SockCore_FreeMsg(m);
        OS_EnableScheduler();
        OS_RestoreInterrupts(irq);
        OSi_RescheduleThread();
    }
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov065_0225f378) {
    HOST_OVERLAY_VAR(sSockMsgPool),
    HOST_OVERLAY_VAR(sSockMsgFreeQueue),
    HOST_OVERLAY_VARS_END
};
