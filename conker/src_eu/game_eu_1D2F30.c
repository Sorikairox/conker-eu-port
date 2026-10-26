#include <ultra64.h>
#include "functions.h"
#include "variables.h"

u8 *gfx_other_mode_cached(u8 *, s32, s32, s8 *);

/* was func_151A5720 */
void screen_tint_draw_fill(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        s8 uAB;
        s32 uAC;
        s32 uB0;
        u8 padB4[0xC];
        s32 uC0;
    } sp;
    f32 var_f0;
    f32 var_f12;
    f32 var_f2;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t7;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a3;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_a0_10;
    u8 *temp_a0_11;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a0_8;
    u8 *temp_a0_9;
    u8 *var_a0;
    u8 *var_a2;

    (*(s32 *)((u8 *)arg0 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    temp_a0 = arg0 + 8;
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xFC119623;
    (*(s32 *)((u8 *)temp_a0 + 4)) = 0xFF2FFFFF;
    temp_a0_2 = temp_a0 + 8;
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xFA000100;
    temp_a0_3 = temp_a0_2 + 8;
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = (s32) (((*(u8 *)((u8 *)arg1 + 0x15)) << 0x18) | ((*(u8 *)((u8 *)arg1 + 0x16)) << 0x10) | ((*(u8 *)((u8 *)arg1 + 0x17)) << 8) | 0xFF);
    arg0 = temp_a0_3;
    render_set_scissor((s32) temp_a0_3, arg2, 0, 0, 0, 3);
    sp.uAB = 0;
    var_a0 = gfx_other_mode_cached(arg0, 0xC00, 0x0F0A4004, &sp.uAB);
    var_a2 = g_player_cams + ((*(u8 *)((u8 *)arg1 + 0x1A)) * 0x180);
    var_a3 = 0;
    var_v1 = (s32) (*(f32 *)((u8 *)var_a2 + 4));
    var_t0 = (s32) (*(f32 *)((u8 *)var_a2 + 8));
loop_1:
    if (var_a3 == 0) {
        var_f12 = (f32) var_t0;
        var_a1 = (s32) (*(f32 *)((u8 *)var_a2 + 0x2C));
        var_t2 = 8;
        var_f2 = (*(f32 *)((u8 *)var_a2 + 0x24)) + var_f12;
        var_t1 = (s32) (*(f32 *)((u8 *)var_a2 + 0x24));
        if (var_v1 >= 0x101) {
            var_v0 = 0x100;
        } else {
            var_v0 = var_v1;
        }
        goto block_7;
    }
    if (var_v1 >= 0x101) {
        var_v0 = var_v1 - 0x100;
        var_f12 = (f32) var_t0;
        var_t2 = 0x36;
        var_a1 = (s32) ((*(f32 *)((u8 *)var_a2 + 0x2C)) + 256.0f);
        var_f2 = (*(f32 *)((u8 *)var_a2 + 0x24)) + var_f12;
        var_t1 = (s32) (*(f32 *)((u8 *)var_a2 + 0x24));
block_7:
        var_f0 = (f32) var_t1;
        temp_t4 = ((((s32) ((var_v0 * 2) + 7) >> 3) & 0x1FF) << 9) | 0xF5100000;
        temp_t5 = ((var_a1 * 4) & 0xFFF) << 0xC;
        if (var_f0 < var_f2) {
            sp.uB0 = var_v1;
            temp_v1 = var_a1 + var_v0;
            sp.uAC = var_t0;
            sp.uC0 = var_a3;
            do {
                var_v0_2 = var_t1 + var_t2;
                temp_a0_4 = var_a0 + 8;
                if (var_f2 < (f32) var_v0_2) {
                    var_t2 = (s32) (var_f2 - var_f0);
                    var_v0_2 = var_t1 + var_t2;
                }
                (*(s32 *)((u8 *)var_a0 + 0)) = 0xE7000000;
                (*(s32 *)((u8 *)var_a0 + 4)) = 0;
                temp_a0_5 = temp_a0_4 + 8;
                (*(s32 *)((u8 *)temp_a0_4 + 0)) = (s32) (((g_framebuffer_width - 1) & 0xFFF) | 0xFD100000);
                temp_a0_6 = temp_a0_5 + 8;
                (*(s32 *)((u8 *)temp_a0_4 + 4)) = (s32) g_framebuffers[g_dl_buf_index];
                (*(s32 *)((u8 *)temp_a0_5 + 0)) = temp_t4;
                (*(s32 *)((u8 *)temp_a0_5 + 4)) = 0x07080200;
                temp_t7 = (var_t1 * 4) & 0xFFF;
                (*(s32 *)((u8 *)temp_a0_6 + 0)) = (s32) (temp_t5 | 0xF4000000 | temp_t7);
                (*(s32 *)((u8 *)temp_a0_6 + 4)) = (s32) (((((temp_v1 - 1) * 4) & 0xFFF) << 0xC) | 0x07000000 | (((var_v0_2 - 1) * 4) & 0xFFF));
                temp_a0_7 = temp_a0_6 + 8;
                (*(s32 *)((u8 *)temp_a0_7 + 4)) = 0x80200;
                (*(s32 *)((u8 *)temp_a0_7 + 0)) = temp_t4;
                temp_a0_8 = temp_a0_7 + 8;
                (*(s32 *)((u8 *)temp_a0_8 + 0)) = 0xF2000000;
                (*(s32 *)((u8 *)temp_a0_8 + 4)) = (s32) ((((var_v0 * 4) & 0xFFF) << 0xC) | ((var_t2 * 4) & 0xFFF));
                temp_a0_9 = temp_a0_8 + 8;
                (*(s32 *)((u8 *)temp_a0_9 + 4)) = (s32) (temp_t5 | temp_t7);
                (*(s32 *)((u8 *)temp_a0_9 + 0)) = (s32) ((((temp_v1 * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((var_v0_2 * 4) & 0xFFF));
                temp_a0_10 = temp_a0_9 + 8;
                (*(s32 *)((u8 *)temp_a0_10 + 0)) = 0xE1000000;
                (*(s32 *)((u8 *)temp_a0_10 + 4)) = 0;
                temp_a0_11 = temp_a0_10 + 8;
                (*(s32 *)((u8 *)temp_a0_11 + 0)) = 0xF1000000;
                (*(s32 *)((u8 *)temp_a0_11 + 4)) = 0x04000400;
                var_a0 = temp_a0_11 + 8;
                var_t1 = var_v0_2;
                var_f0 = (f32) var_t1;
                var_a2 = g_player_cams + ((*(u8 *)((u8 *)arg1 + 0x1A)) * 0x180);
                var_f2 = (*(f32 *)((u8 *)var_a2 + 0x24)) + var_f12;
            } while (var_f0 < var_f2);
            var_t0 = sp.uAC;
            var_a3 = sp.uC0;
            var_v1 = sp.uB0;
        }
        var_a3 += 1;
        if (var_a3 < 2) {
            goto loop_1;
        }
    }
    (*(s32 *)((u8 *)var_a0 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)var_a0 + 4)) = 0;
    gfx_other_mode_cached(var_a0 + 8, 0x2C00, 0x0F0A4004, &sp.uAB);
}
/* was func_151A5B84 */
void screen_tint_handle_msg(u8 *arg0, s32 arg1, u8 arg2) {
    void (*f)(s32, void *, u8) = g_screen_tint_fx_msg_fns[arg0[0x19]];
    if (f != NULL) {
        f(arg0, arg1, arg2);
    }
}

/* was func_151A5BCC */
void screen_tint_broadcast(s32 arg0, u8 arg1) {
    const s32 sp1C[1] = {0x5A};

    node_broadcast_types(sp1C, 1, arg0, arg1);
}
