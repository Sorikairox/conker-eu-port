#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15006010 */
void camera_level_hook24_update(struct108 *arg0) {

    if (arg0->unk3D0->unk102) {
        if (camera_push_mode(arg0, 8, 0, 0, 0)) {
            arg0->unk84 |= 0x100000;
            arg0->unk84 &= -5;
            arg0->unk1B4 = 1;
            arg0->unk1E0 = 3;
            camera_apply_zoom_level(arg0);
        }
        arg0->unk348 = 143.0f;
        arg0->unk34C = 143.0f;
        arg0->unk374 = 150.0f;
        arg0->unk190 = -38.0f;
        return;
    }
    if (arg0->unk23E == 0x3B) {
        if (camera_push_mode(arg0, 8, 0, 0, 0)) {
            arg0->unk84 |= 0x100000;
            arg0->unk84 &= -5;
            arg0->unk348 = 155.0f;
            arg0->unk34C = 155.0f;
            arg0->unk190 = 30.0f;
            arg0->unk18C = 30.0f;
            arg0->unk374 = 178.0f;
            return;
        }
    } else {
        camera_pop_mode(arg0, 0);
    }
}

/* was func_15006140 */
void camera_level_hook25_setup(struct108 *arg0) {
    arg0->unk1E0 = 5;
    arg0->unk1B4 = 2;
    camera_apply_zoom_level(arg0);
}
