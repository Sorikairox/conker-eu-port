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
extern __OSViContext *g_os_vi_next; /* was D_8002C134 */ // __osViNext

void osViBlack(u8 active) {
    register u32 saveMask = __osDisableInt();

    if (active) {
        g_os_vi_next->state |= 0x20;
    } else {
        g_os_vi_next->state &= ~0x20;
    }
    __osRestoreInt(saveMask);
}

void osViSetEvent(OSMesgQueue *mq, OSMesg m, u32 retraceCount) {
    register u32 saveMask = __osDisableInt();

    g_os_vi_next->msgq = mq;
    g_os_vi_next->msg = m;
    g_os_vi_next->retraceCount = retraceCount;
    __osRestoreInt(saveMask);
}
