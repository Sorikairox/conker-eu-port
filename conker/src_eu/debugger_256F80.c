#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#include "controller.h"

// debugger copies of __osContPifRam and __osMaxControllers
extern OSPifRam g_os_cont_pif_ram; /* was D_80042DA0 */
extern u8 g_os_cont_last_cmd; /* was D_80042DE0 */ // __osContLastCmd
extern u8 g_os_max_controllers; /* was D_80042DE1 */


void debug_cont_pack_read_data(void);
s32 debug_si_raw_start_dma(s32 direction, void *dramAddr);

// reads the controllers (osContStartReadData + wait)
/* was func_16001700 */
s32 debug_cont_read(void) {
    s32 ret;
    s32 i;
    u32 end;

    if (g_os_cont_last_cmd != CONT_CMD_READ_BUTTON) {
        debug_cont_pack_read_data();
        debug_si_raw_start_dma(OS_WRITE, &g_os_cont_pif_ram);
        i = 0;
        end = osGetCount() + 200000;
        while (osGetCount() < end) {
            i = debugger_identity(i);
        }
        debugger_identity(i);
    }
    for (i = 0; i < 16; i++) {
        g_os_cont_pif_ram.ramarray[i] = CONT_CMD_NOP;
    }
    g_os_cont_pif_ram.pifstatus = 0;
    ret = debug_si_raw_start_dma(OS_READ, &g_os_cont_pif_ram);
    g_os_cont_last_cmd = CONT_CMD_READ_BUTTON;
    i = 0;
    end = osGetCount() + 800000;
    while (osGetCount() < end) {
        i = debugger_identity(i);
    }
    debugger_identity(i);
    return ret;
}
// osContGetReadData
/* was func_16001830 */
void debug_cont_get_read_data(OSContPad *data) {
    u8 *ptr;
    __OSContReadFormat readformat;
    s32 i;

    ptr = (u8 *)g_os_cont_pif_ram.ramarray;
    for (i = 0; i < g_os_max_controllers; i++, ptr += sizeof(__OSContReadFormat), data++) {
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
/* was func_160018BC */
void debug_cont_pack_read_data(void) {
    u8 *ptr;
    __OSContReadFormat readformat;
    s32 i;

    ptr = (u8 *)g_os_cont_pif_ram.ramarray;
    for (i = 0; i < 16; i++) {
        g_os_cont_pif_ram.ramarray[i] = 0;
    }
    g_os_cont_pif_ram.pifstatus = CONT_CMD_EXE;
    readformat.dummy = CONT_CMD_NOP;
    readformat.txsize = CONT_CMD_READ_BUTTON_TX;
    readformat.rxsize = CONT_CMD_READ_BUTTON_RX;
    readformat.cmd = CONT_CMD_READ_BUTTON;
    readformat.button = 0xFFFF;
    readformat.stick_x = -1;
    readformat.stick_y = -1;
    for (i = 0; i < g_os_max_controllers; i++) {
        *(__OSContReadFormat *)ptr = readformat;
        ptr += sizeof(__OSContReadFormat);
    }
    *ptr = CONT_CMD_END;
}

// another __osSiDeviceBusy function
/* was func_16001984 */
s32 debug_si_device_busy()
{
    register u32 stat = IO_READ(SI_STATUS_REG);
    if (stat & (SI_STATUS_DMA_BUSY | SI_STATUS_RD_BUSY))
        return 1;
    return 0;
}

// very similar to __osSiRawStartDma
/* was func_160019A8 */
s32 debug_si_raw_start_dma(s32 direction, void *dramAddr) {
    if ((s32)dramAddr & 3) { // what is this checking?
        return -1;
    }
    if (debug_si_device_busy()) {
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

/* was func_16001A64 */
void debug_stub(void) {
}

/* was func_16001A6C */
s32 debug_float_is_denorm_or_nan(f32 arg0) {
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
