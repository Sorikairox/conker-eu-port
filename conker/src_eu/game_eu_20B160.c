#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 eeprom_async_write_step(s32);
s32 game_eeprom_read(OSMesgQueue *, u8, void *);
/* was func_151DD950 */
s32 game_eeprom_long_read(OSMesgQueue *mq, u8 address, void *buffer, s32 nbytes) {
    s32 ret = 0;

    while (eeprom_async_write_step(1) != 0) {
    }
    while (nbytes > 0) {
        ret = game_eeprom_read(mq, address, buffer);
        if (ret != 0) {
            return ret;
        }
        nbytes -= 8;
        address++;
        buffer = (u8 *)buffer + 8;
    }
    return ret;
}
