#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"


s32 __osSiGetAccess();
s32 __osSiRelAccess();
s32 os_si_raw_start_dma(s32, s32 *);
void game_os_pack_read_data(void);
extern s32 g_os_cont_pif_ram; /* was D_80042DA0 */
extern s32 g_os_cont_pif_status; /* was D_80042DDC */
extern u8 g_os_cont_last_cmd; /* was D_80042DE0 */

/* was func_151F0260 */
s32 game_os_cont_start_read_data(OSMesgQueue *arg0) {
    s32 sp1C;
    s32 sp18;

    sp1C = 0;
    __osSiGetAccess();
    if (g_os_cont_last_cmd != 1) {
        game_os_pack_read_data();
        sp1C = os_si_raw_start_dma(1, &g_os_cont_pif_ram);
        osRecvMesg(arg0, NULL, 1);
    }
    for (sp18 = 0; sp18 < 0x10; sp18++) {
        *(s32 *)((u8 *)&g_os_cont_pif_ram + (sp18 * 4)) = 0xFF;
    }
    g_os_cont_pif_status = 0;
    sp1C = os_si_raw_start_dma(0, &g_os_cont_pif_ram);
    g_os_cont_last_cmd = 1;
    __osSiRelAccess();
    return sp1C;
}

extern s32 g_os_cont_pif_ram; /* was D_80042DA0 */
extern u8 g_os_max_controllers; /* was D_80042DE1 */
/* was func_151F0324 */
void game_os_cont_get_read_data(OSContPad *data) {
    u8 *ptr = (u8 *)&g_os_cont_pif_ram;
    __OSContReadFormat readformat;
    int i;

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

extern s32 g_os_cont_pif_ram; /* was D_80042DA0 */
extern s32 g_os_cont_pif_status; /* was D_80042DDC */
extern u8 g_os_max_controllers; /* was D_80042DE1 */
/* was func_151F03CC */
void game_os_pack_read_data(void) {
    u8 *ptr = (u8 *)&g_os_cont_pif_ram;
    __OSContReadFormat readformat;
    int i;

    for (i = 0; i < 16; i++) {
        (&g_os_cont_pif_ram)[i] = 0;
    }
    g_os_cont_pif_status = CONT_CMD_EXE;
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
