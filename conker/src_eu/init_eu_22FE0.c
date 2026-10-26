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

void osViSetMode(OSViMode *modep) {
    register u32 saveMask = __osDisableInt();

    g_os_vi_next->modep = modep;
    g_os_vi_next->state = 1;
    g_os_vi_next->control = g_os_vi_next->modep->comRegs.ctrl;
    __osRestoreInt(saveMask);
}
