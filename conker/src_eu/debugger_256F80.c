#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#include "controller.h"

// debugger copies of __osContPifRam and __osMaxControllers
extern OSPifRam D_80042DA0;
extern u8 D_80042DE0; // __osContLastCmd
extern u8 D_80042DE1;


void func_160018BC(void);
s32 func_160019A8(s32 direction, void *dramAddr);

// reads the controllers (osContStartReadData + wait)
s32 func_16001700(void) {
    s32 ret;
    s32 i;
    u32 end;

    if (D_80042DE0 != CONT_CMD_READ_BUTTON) {
        func_160018BC();
        func_160019A8(OS_WRITE, &D_80042DA0);
        i = 0;
        end = osGetCount() + 200000;
        while (osGetCount() < end) {
            i = func_160016F4(i);
        }
        func_160016F4(i);
    }
    for (i = 0; i < 16; i++) {
        D_80042DA0.ramarray[i] = CONT_CMD_NOP;
    }
    D_80042DA0.pifstatus = 0;
    ret = func_160019A8(OS_READ, &D_80042DA0);
    D_80042DE0 = CONT_CMD_READ_BUTTON;
    i = 0;
    end = osGetCount() + 800000;
    while (osGetCount() < end) {
        i = func_160016F4(i);
    }
    func_160016F4(i);
    return ret;
}
// osContGetReadData
void func_16001830(OSContPad *data) {
    u8 *ptr;
    __OSContReadFormat readformat;
    s32 i;

    ptr = (u8 *)D_80042DA0.ramarray;
    for (i = 0; i < D_80042DE1; i++, ptr += sizeof(__OSContReadFormat), data++) {
        readformat = *(__OSContReadFormat *)ptr;
        data->errno = CHNL_ERR(readformat);
        if (data->errno == 0) {
            data->button = readformat.button;
            data->stick_x = readformat.stick_x;
            data->stick_y = readformat.stick_y;
        }
    }
}
// __osPackReadData
void func_160018BC(void) {
    u8 *ptr;
    __OSContReadFormat readformat;
    s32 i;

    ptr = (u8 *)D_80042DA0.ramarray;
    for (i = 0; i < 16; i++) {
        D_80042DA0.ramarray[i] = 0;
    }
    D_80042DA0.pifstatus = CONT_CMD_EXE;
    readformat.dummy = CONT_CMD_NOP;
    readformat.txsize = CONT_CMD_READ_BUTTON_TX;
    readformat.rxsize = CONT_CMD_READ_BUTTON_RX;
    readformat.cmd = CONT_CMD_READ_BUTTON;
    readformat.button = 0xFFFF;
    readformat.stick_x = -1;
    readformat.stick_y = -1;
    for (i = 0; i < D_80042DE1; i++) {
        *(__OSContReadFormat *)ptr = readformat;
        ptr += sizeof(__OSContReadFormat);
    }
    *ptr = CONT_CMD_END;
}

// another __osSiDeviceBusy function
s32 func_16001984()
{
    register u32 stat = IO_READ(SI_STATUS_REG);
    if (stat & (SI_STATUS_DMA_BUSY | SI_STATUS_RD_BUSY))
        return 1;
    return 0;
}

// very similar to __osSiRawStartDma
s32 func_160019A8(s32 direction, void *dramAddr) {
    if ((s32)dramAddr & 3) { // what is this checking?
        return -1;
    }
    if (func_16001984()) {
        return -1;
    }

    if (direction == OS_WRITE) {
        osWritebackDCache(dramAddr, 64);
    }

    IO_WRITE(SI_DRAM_ADDR_REG, osVirtualToPhysical(dramAddr));

    if (direction == OS_READ) {
        IO_WRITE(SI_PIF_ADDR_RD64B_REG, 0x1FC007C0);
    } else {
        IO_WRITE(SI_PIF_ADDR_WR64B_REG, 0x1FC007C0);
    }
    if (direction == OS_READ) {
        osInvalDCache(dramAddr, 64);
    }

    return 0;
}

void func_16001A64(void) {
}

s32 func_16001A6C(f32 arg0) {
    s32 tmp = *(s32*) &arg0;

    if ((tmp * 2) == 0) {
        return 0;
    }
    tmp = (tmp & 0x7F800000) >> 0x17;
    if ((tmp <= 0) || (tmp >= 255)) {
        return 1;
    }
    return 0;
}
