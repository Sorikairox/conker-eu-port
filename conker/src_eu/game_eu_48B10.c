#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* Smoothed view direction of camera `player` (D_800DBFF0 cameras, 0x9A0 bytes each), skipped while
 * D_800BEAC0 is set. The pitch (+0x388, folded into -180..180) and the heading (+0x380) are followed by
 * D_800BEAE0[player] / D_800BEAF0[player] at rate 0.1 (camera +0x698 set), 1.0 (D_800DBFF4 set) or 0.03;
 * the smoothed heading stays within 90 degrees of the real one. The direction vector, scaled to 127, is
 * stored as three s8 in D_800DCD30[player * 3]. */
extern f32 D_800BEAE0[];
extern f32 D_800BEAF0[];
#define DEG_TO_RAD 0.017453292f

void func_1501B300(s32 player) {
    u8 *cam;
    f32 rate;
    f32 pitch;
    f32 heading;
    f32 *smoothPitch;
    f32 *smoothHeading;
    f32 delta;
    f32 a;
    f32 negSinPitch;
    f32 cosPitch;
    f32 x;
    f32 z;
    s8 *out;

    if (D_800BEAC0 != 0) {
        return;
    }
    cam = (u8 *)D_800DBFF0 + player * 0x9A0;
    if (*(s32 *)(cam + 0x698) != 0) {
        rate = 0.1f;
    } else if (*(s32 *)D_800DBFF4 != 0) {
        rate = 1.0f;
    } else {
        rate = 0.03f;
    }
    pitch = *(f32 *)(cam + 0x388);
    heading = *(f32 *)(cam + 0x380);
    if (pitch < 0.0f) {
        pitch += 360.0f;
    } else if (360.0f <= pitch) {
        pitch -= 360.0f;
    }
    if (pitch > 180.0f) {
        pitch -= 360.0f;
    }

    smoothPitch = &D_800BEAE0[player];
    smoothHeading = &D_800BEAF0[player];
    *smoothPitch = *smoothPitch + (pitch - *smoothPitch) * rate;
    *smoothHeading = *smoothHeading + rate * math_angle_diff_deg(*smoothHeading, heading);
    if (*smoothHeading < 0.0f) {
        *smoothHeading += 360.0f;
    } else if (360.0f <= *smoothHeading) {
        *smoothHeading -= 360.0f;
    }

    delta = math_angle_diff_deg(*smoothHeading, heading);
    if (fabsf(delta) > 90.0f) {
        *smoothHeading = heading - (f32)((delta < 0.0f) ? -1 : 1) * 90.0f;
    }
    if (*smoothHeading < 0.0f) {
        *smoothHeading += 360.0f;
    } else if (360.0f <= *smoothHeading) {
        *smoothHeading -= 360.0f;
    }

    a = *smoothPitch * DEG_TO_RAD;
    negSinPitch = -sinf(a);
    cosPitch = cosf(a);
    a = *smoothHeading * DEG_TO_RAD;
    x = sinf(a) * cosPitch;
    z = cosf(a) * cosPitch;
    out = (s8 *)&D_800DCD30 + player * 3;
    out[0] = x * 127.0f;
    out[1] = negSinPitch * 127.0f;
    out[2] = z * 127.0f;
}

/* the asm only forwards a0 (the player index) */
void func_1501B640(s32 player) {
    func_1501B300(player);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_48B10/func_1501B300.s")

void func_1501B640(void) {
    func_1501B300();
}
#endif
