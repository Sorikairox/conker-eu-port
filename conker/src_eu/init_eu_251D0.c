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
extern __OSViContext *D_8002C130; // __osViCurr


void *osViGetCurrentFramebuffer(void) {
    register u32 saveMask = __osDisableInt();
    void *framep = D_8002C130->framep;

    __osRestoreInt(saveMask);
    return framep;
}

// osViGetNextFramebuffer
void *func_10025210(void) {
    register u32 saveMask = __osDisableInt();
    void *framep = D_8002C134->framep;

    __osRestoreInt(saveMask);
    return framep;
}

void osViSwapBuffer(void *frameBufPtr) {
    u32 saveMask = __osDisableInt();

    D_8002C134->framep = frameBufPtr;
    D_8002C134->state |= 0x10;
    __osRestoreInt(saveMask);
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_eu_251D0/osWritebackDCacheAll.s")
