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

void osViSetMode(OSViMode *modep) {
    register u32 saveMask = __osDisableInt();

    D_8002C134->modep = modep;
    D_8002C134->state = 1;
    D_8002C134->control = D_8002C134->modep->comRegs.ctrl;
    __osRestoreInt(saveMask);
}
