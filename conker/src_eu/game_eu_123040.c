#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 event_dispatch(s32, s32, ...);

/* was func_150F5830 */
void camera_update_flag_401c(u8 *arg0) {
    if (event_dispatch(1, 0x401C, 6, 0x9000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x80000000);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0x7FFFFFFF);
}

void water_waves_update(void);

/* was func_150F5890 */
void area_points_hook(s32 arg0) {
    water_waves_update();
}
