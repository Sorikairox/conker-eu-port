#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    f32 factor;
    u16 offset;
    u32 scale;
} __OSViScale;
typedef struct {
    u16 state;
    u16 retraceCount;
    void *framep;
    OSViMode *modep;
    u32 control;
    OSMesgQueue *msgq;
    OSMesg msg;
    __OSViScale x;
    __OSViScale y;
} __OSViContext;
extern __OSViContext *D_8002C134; // __osViNext

void osViBlack(u8 active) {
    register u32 saveMask = __osDisableInt();

    if (active) {
        D_8002C134->state |= 0x20;
    } else {
        D_8002C134->state &= ~0x20;
    }
    __osRestoreInt(saveMask);
}

void osViSetEvent(OSMesgQueue *mq, OSMesg m, u32 retraceCount) {
    register u32 saveMask = __osDisableInt();

    D_8002C134->msgq = mq;
    D_8002C134->msg = m;
    D_8002C134->retraceCount = retraceCount;
    __osRestoreInt(saveMask);
}
