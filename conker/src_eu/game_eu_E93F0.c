#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 event_dispatch(s32, s32, ...);

/* was func_150BBBE0 */
void player_update_flag_from_btn4047(u8 *arg0) {
    if (event_dispatch(1, 0x4047, 6, 0x2000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x1000);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x1000);
}
