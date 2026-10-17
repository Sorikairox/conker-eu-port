#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// libultra vi.c; this file is built -O1
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
extern __OSViContext *D_8002C130; // __osViCurr
extern __OSViContext *D_8002C134; // __osViNext

void __osViSwapContext(void) {
    register OSViMode *vm;
    register __OSViContext *vc;
    u32 origin;
    u32 hStart;
    u32 nomValue;
    u32 field;

    field = 0;
    vc = D_8002C134;
    vm = vc->modep;
    field = IO_READ(VI_V_CURRENT_LINE_REG) & 1;
    origin = osVirtualToPhysical(vc->framep) + vm->fldRegs[field].origin;
    if (vc->state & 2) {
        vc->x.scale |= vm->comRegs.xScale & ~0xFFF;
    } else {
        vc->x.scale = vm->comRegs.xScale;
    }
    if (vc->state & 4) {
        nomValue = vm->fldRegs[field].yScale & 0xFFF;
        vc->y.scale = vc->y.factor * nomValue;
        vc->y.scale |= vm->fldRegs[field].yScale & ~0xFFF;
    } else {
        vc->y.scale = vm->fldRegs[field].yScale;
    }
    hStart = vm->comRegs.hStart;
    if (vc->state & 0x20) {
        hStart = 0;
    }
    if (vc->state & 0x40) {
        vc->y.scale = 0;
        origin = osVirtualToPhysical(vc->framep);
    }
    if (vc->state & 0x80) {
        vc->y.scale = (vc->y.offset << 16) & 0x3FF0000;
        origin = osVirtualToPhysical(vc->framep);
    }
    IO_WRITE(VI_ORIGIN_REG, origin);
    IO_WRITE(VI_WIDTH_REG, vm->comRegs.width);
    IO_WRITE(VI_BURST_REG, vm->comRegs.burst);
    IO_WRITE(VI_V_SYNC_REG, vm->comRegs.vSync);
    IO_WRITE(VI_H_SYNC_REG, vm->comRegs.hSync);
    IO_WRITE(VI_LEAP_REG, vm->comRegs.leap);
    IO_WRITE(VI_H_START_REG, hStart);
    IO_WRITE(VI_V_START_REG, vm->fldRegs[field].vStart);
    IO_WRITE(VI_V_BURST_REG, vm->fldRegs[field].vBurst);
    IO_WRITE(VI_INTR_REG, vm->fldRegs[field].vIntr);
    IO_WRITE(VI_X_SCALE_REG, vc->x.scale);
    IO_WRITE(VI_Y_SCALE_REG, vc->y.scale);
    IO_WRITE(VI_CONTROL_REG, vc->control);
    D_8002C134 = D_8002C130;
    D_8002C130 = vc;
    *D_8002C134 = *D_8002C130;
}
