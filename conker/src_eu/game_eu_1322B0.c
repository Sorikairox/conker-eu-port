#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15104AA0 */
void camera_update_close_snap(struct108 *arg0) {
    f32 temp_f0;
    struct127 *temp_a1;

    if ((arg0->unk6FC != 0) || (arg0->unk6C8 == 0)) {
        arg0->unk348 = 117.0f;
        arg0->unk34C = 117.0f;
        arg0->unk374 = 370.0f;
        arg0->unk190 = 77.0f;
    }
    temp_a1 = arg0->unk3D0;
    if ((temp_a1->xz_velocity < 50.0f) && (arg0->unk3E8 == 0)) {
        temp_f0 = arg0->unk374;
        if ((0.5f * temp_f0) < ((*(f32 *)((u8 *)arg0 + 0x370)) - temp_f0)) {
            camera_snap_to_object(arg0, temp_a1);
        }
    }
}
