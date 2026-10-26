#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
/* P98: D_800E1230 callback (mp3main_decode_next_frame calls it with (0, line, length)); a1 / a2 reach ring_buffer_put_record untouched */
void func_10012560(s32 arg0, u8 *arg1, s32 arg2) {
    ring_buffer_put_record(&D_800427A0, arg1, arg2);
}
#else
void func_10012560(s32 arg0) {
    ring_buffer_put_record(&D_800427A0);
}
#endif

void func_10012588(s32 arg0) {
    audio_fx_mixer_init(arg0);
    ring_buffer_init(&D_800427A0, &D_800427B0, 64);
    func_151F3C1C(func_10012560);
}

void func_100125CC(s32 arg0) {
    s32 res = func_151F2CDC();
    if ((arg0 != 30) || (D_800BE9F8 != 27)) {
        if (res == 1) {
            func_151F2D6C(0, 11010);
            return;
        }
        if (res != 0) {
            func_151F2BA8();
        }
    }
}

void func_1001263C(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 sp18;

    sp18 = 0;
    temp_v0 = asset_lookup_rom(&sp18, 2, 22, arg0);
    D_800427F4 = (s16) arg0;
    if ((temp_v0 != 0) && (sp18 != 0)) {
        func_151F2D6C(arg1, 0);
        func_151F2DFC(arg2, 1);
        if (arg0 != 0xD2) {
            func_151F2E4C(10, 11000);
        } else {
            func_151F2E4C(0, 0);
        }
        func_151F2960(temp_v0, sp18);
    }
}

// text_queue_read: takes the next record of the text queue D_800427A0 into the buffer arg0 (at most arg1 bytes,
// ring_buffer_get_record) and returns its length (P182: the asm caller func_15080628 loops while it is non-zero; it was void).
s32 func_100126E8(s32 arg0, s32 arg1) {
    return ring_buffer_get_record(&D_800427A0, arg0, arg1);
}

s32 func_10012718(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4) {
    s32 sp3C;
    s32 sp38;
    s32 sp34;

    if (arg1->camera != 0) {
        func_1001263C(arg0, arg2, 64);
    } else {
        func_100114D0(arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, &sp3C, &sp38, &sp34);
        func_1001263C(arg0, sp38, sp3C);
    }
    return 1;
}

s32 func_100127D0(void) {
    s32 tmp = func_151F2CDC();

    if (tmp == 1 || tmp == 2 || tmp == 5) {
        return 1;
    }
    return 0;
}
