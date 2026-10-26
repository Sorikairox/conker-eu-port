#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void os_pi_get_access(void); // __osPiGetAccess
void os_pi_rel_access(void); // __osPiRelAccess

// osPiReadIo
/* was func_151EF800 */
s32 game_os_pi_read_io(u32 devAddr, u32 *data) {
    register s32 ret;

    os_pi_get_access();
    ret = osPiRawReadIo(devAddr, data);
    os_pi_rel_access();
    return ret;
}
