#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15005C80 */
void camera_level_hook10_setup(struct108 *arg0) {
    arg0->unk2C = 8;
    arg0->unk84 |= 0x1300000;
    arg0->unk1B4 = 1;
    arg0->unk1E0 = 2;
    arg0->unk348 = 117.0f;
    arg0->unk34C = 117.0f;
    arg0->unk190 = 0.0f;
    arg0->unk18C = 0.0f;
    arg0->unk134 = 0;
    arg0->unk5F0 |= 0x10;
    arg0->unk23C = 1;
    arg0->unk374 = 370.0f;
}

/* was func_15005CF0 */
void camera_level_hook11_noop(s32 arg0) {
}
