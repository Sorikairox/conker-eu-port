#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 retraceCount;
    /* 0x04 */ void *framep;
    /* 0x08 */ OSViMode *modep;
    /* 0x0C */ u32 control;
    /* 0x10 */ OSMesgQueue *msgq;
    /* 0x14 */ OSMesg msg;
} OSViContext_s86;

extern OSViContext_s86 *g_os_vi_next; /* __osViNext; was D_8002C134 */
u32 __osDisableInt(void);
void __osRestoreInt(u32);

/* was func_151EFE00 */
void game_os_pi_set_control(u32 func) {
    register u32 saveMask;

    saveMask = __osDisableInt();
    if ((func & 0x1) != 0) {
        g_os_vi_next->control |= 0x8;
    }
    if ((func & 0x2) != 0) {
        g_os_vi_next->control &= ~0x8;
    }
    if ((func & 0x4) != 0) {
        g_os_vi_next->control |= 0x4;
    }
    if ((func & 0x8) != 0) {
        g_os_vi_next->control &= ~0x4;
    }
    if ((func & 0x10) != 0) {
        g_os_vi_next->control |= 0x10;
    }
    if ((func & 0x20) != 0) {
        g_os_vi_next->control &= ~0x10;
    }
    if ((func & 0x40) != 0) {
        g_os_vi_next->control |= 0x10000;
        g_os_vi_next->control &= ~0x300;
    }
    if ((func & 0x80) != 0) {
        g_os_vi_next->control &= ~0x10000;
        g_os_vi_next->control |= g_os_vi_next->modep->comRegs.ctrl & 0x300;
    }
    g_os_vi_next->state |= 0x8;
    __osRestoreInt(saveMask);
}
