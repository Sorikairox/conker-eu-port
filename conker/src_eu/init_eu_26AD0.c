#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// g_os_rom_base: osRomBase (variables.h)

s32 osPiRawReadIo(u32 devAddr, u32 *data) {
    register u32 stat;

    stat = IO_READ(PI_STATUS_REG);
    while (stat & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY)) {
        stat = IO_READ(PI_STATUS_REG);
    }
    *data = IO_READ((u32)g_os_rom_base | devAddr);
    return 0;
}
