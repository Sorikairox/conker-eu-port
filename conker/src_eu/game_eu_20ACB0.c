#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u64 g_os_clock_rate; /* was D_8002C060 */
extern OSTimer g_eep_timer; /* was D_80042DE8 */
extern OSMesgQueue g_eep_timer_queue; /* was D_80042E08 */
extern s32 g_eep_timer_msg; /* was D_80042E20 */
extern OSMesgQueue *g_eep_async_mq; /* was D_800E0E50 */
extern u8 g_eep_async_block; /* was D_800E0E54 */
extern void *g_eep_async_buf; /* was D_800E0E58 */
extern s32 g_eep_async_bytes_left; /* was D_800E0E5C */
/* was func_151DD4A0 */
s32 eeprom_async_write_start(OSMesgQueue *mq, u8 address, void *buffer, s32 nbytes) {
    s32 temp_v0;
    temp_v0 = eeprom_async_write_step(1);
    if (temp_v0 != 0) {
        do {
        } while (eeprom_async_write_step(1) != 0);
    }
    g_eep_async_mq = mq;
    g_eep_async_block = address;
    g_eep_async_buf = buffer;
    g_eep_async_bytes_left = nbytes;
    return osSetTimer(&g_eep_timer, (12000ULL * g_os_clock_rate) / 1000000ULL, 0, &g_eep_timer_queue, &g_eep_timer_msg);
}

/* was func_151DD588 */
int eeprom_async_write_step(s32 flag) {
    if (g_eep_async_mq == NULL) {
        return 0;
    }
    if (osRecvMesg(&g_eep_timer_queue, NULL, flag) != -1) {
        if (g_eep_async_bytes_left <= 0) {
            g_eep_async_mq = NULL;
            g_eep_async_bytes_left = 0;
            return 0;
        }
        if (game_eeprom_write(g_eep_async_mq, g_eep_async_block, g_eep_async_buf) != 0) {
            g_eep_async_mq = NULL;
            g_eep_async_bytes_left = 0;
            return 0;
        }
        g_eep_async_bytes_left -= 8;
        g_eep_async_block += 1;
        g_eep_async_buf = (u8 *)g_eep_async_buf + 8;
        osSetTimer(&g_eep_timer, (12000ULL * g_os_clock_rate) / 1000000ULL, 0, &g_eep_timer_queue, &g_eep_timer_msg);
        return 1;
    }
    return 0;
}
