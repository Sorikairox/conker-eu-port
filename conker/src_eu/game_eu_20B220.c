#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 __osSiGetAccess();
s32 __osSiRelAccess();
typedef struct { u16 type; u8 status; u8 errno; } St_DDA10;
s32 game_eep_status(s32, St_DDA10 *);
/* was func_151DDA10 */
s32 game_eeprom_probe(s32 arg0)
{
    s32 ret;
    u16 type;
    St_DDA10 st;

    __osSiGetAccess();
    ret = game_eep_status(arg0, &st);
    type = st.type & 0xC000;
    if (ret != 0) {
        ret = 0;
    } else {
        switch (type) {
        case 0x8000:
            ret = 1;
            break;
        case 0xC000:
            ret = 2;
            break;
        default:
            ret = 0;
            break;
        }
    }
    __osSiRelAccess();
    return ret;
}
