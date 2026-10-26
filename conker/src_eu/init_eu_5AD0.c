#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#include "controller.h"
s32 __osContRamRead(OSMesgQueue *mq, int channel, u16 address, u8 *buffer);
s32 __osContRamWrite(OSMesgQueue *mq, int channel, u16 address, u8 *buffer, int force);
void os_make_motor_data(int channel, u16 address, u8 *buffer, OSPifRam *mdata);
extern u8 g_os_motor_stop_bytes[0x20]; /* was D_8003C1D0 */
extern u8 g_os_motor_start_bytes[0x20]; /* was D_8003C1F0 */
extern u8 g_os_motor_start_data[]; /* was D_8003C0D0 */
extern u8 g_os_motor_stop_data[]; /* was D_8003BFD0 */

/* was func_10005AD0 */
s32 os_motor_init(OSMesgQueue *mq, OSPfs *pfs, int channel) {
    s32 ret;
    int i;
    u8 temp[BLOCKSIZE];

    pfs->queue = mq;
    pfs->channel = channel;
    pfs->status = 0;
    pfs->activebank = 0x80;
    for (i = 0; i < BLOCKSIZE; i++) {
        temp[i] = 0x80;
    }
    ret = __osContRamWrite(mq, channel, 0x400, temp, 0);
    if (ret == 2) {
        ret = __osContRamWrite(mq, channel, 0x400, temp, 0);
    }
    if (ret != 0) {
        return ret;
    }
    ret = __osContRamRead(mq, channel, 0x400, temp);
    if (ret != 0) {
        return ret;
    }
    if (temp[BLOCKSIZE - 1] != 0x80) {
        return 11;
    }
    for (i = 0; i < 0x20; i++) {
        g_os_motor_start_bytes[i] = 1;
        g_os_motor_stop_bytes[i] = 0;
    }
    os_make_motor_data(channel, 0x600, g_os_motor_start_bytes, (OSPifRam *)(g_os_motor_start_data + (channel << 6)));
    os_make_motor_data(channel, 0x600, g_os_motor_stop_bytes, (OSPifRam *)(g_os_motor_stop_data + (channel << 6)));
    return 0;
}

// libultra io/motor.c _MakeMotorData (old version)
/* was func_10005C38 */
void os_make_motor_data(int channel, u16 address, u8 *buffer, OSPifRam *mdata) {
    u8 *ptr = (u8 *)mdata->ramarray;
    __OSContRamReadFormat ramreadformat;
    int i;

    for (i = 0; i < ARRLEN(mdata->ramarray); i++) {
        mdata->ramarray[i] = 0;
    }

    mdata->pifstatus = CONT_CMD_EXE;
    ramreadformat.dummy = CONT_CMD_NOP;
    ramreadformat.txsize = CONT_CMD_WRITE_MEMPACK_TX;
    ramreadformat.rxsize = CONT_CMD_WRITE_MEMPACK_RX;
    ramreadformat.cmd = CONT_CMD_WRITE_MEMPACK;

    ramreadformat.address = (address << 0x5) | __osContAddressCrc(address);
    ramreadformat.datacrc = CONT_CMD_NOP;

    for (i = 0; i < ARRLEN(ramreadformat.data); i++) {
        ramreadformat.data[i] = *buffer++;
    }

    if (channel != 0) {
        for (i = 0; i < channel; i++) {
            *ptr++ = 0;
        }
    }

    *(__OSContRamReadFormat *)ptr = ramreadformat;
    ptr += sizeof(__OSContRamReadFormat);
    ptr[0] = CONT_CMD_END;
}
