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
extern __OSViContext *g_os_vi_curr; /* was D_8002C130 */ // __osViCurr


void *osViGetCurrentFramebuffer(void) {
    register u32 saveMask = __osDisableInt();
    void *framep = g_os_vi_curr->framep;

    __osRestoreInt(saveMask);
    return framep;
}

// osViGetNextFramebuffer
/* was func_10025210 */
void *os_vi_get_next_framebuffer(void) {
    register u32 saveMask = __osDisableInt();
    void *framep = g_os_vi_next->framep;

    __osRestoreInt(saveMask);
    return framep;
}

void osViSwapBuffer(void *frameBufPtr) {
    u32 saveMask = __osDisableInt();

    g_os_vi_next->framep = frameBufPtr;
    g_os_vi_next->state |= 0x10;
    __osRestoreInt(saveMask);
}

