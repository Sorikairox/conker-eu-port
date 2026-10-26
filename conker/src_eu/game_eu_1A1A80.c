#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s16 D_80083336;

/* was func_15174270 */
u8 *occlusion_probe_readback_emit(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 arg6) {
    s32 temp_f6;
    s32 temp_f8;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_t1;
    s32 var_t1_2;
    u8 *temp_a0;
    u8 *temp_a0_10;
    u8 *temp_a0_11;
    u8 *temp_a0_12;
    u8 *temp_a0_13;
    u8 *temp_a0_14;
    u8 *temp_a0_15;
    u8 *temp_a0_16;
    u8 *temp_a0_17;
    u8 *temp_a0_18;
    u8 *temp_a0_19;
    u8 *temp_a0_20;
    u8 *temp_a0_21;
    u8 *temp_a0_22;
    u8 *temp_a0_23;
    u8 *temp_a0_24;
    u8 *temp_a0_25;
    u8 *temp_a0_26;
    u8 *temp_a0_27;
    u8 *temp_a0_28;
    u8 *temp_a0_29;
    u8 *temp_a0_2;
    u8 *temp_a0_30;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a0_8;
    u8 *temp_a0_9;
    u8 *temp_v0;

    (*(s32 *)((u8 *)arg0 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    temp_a0 = arg0 + 8;
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xE200001C;
    (*(s32 *)((u8 *)temp_a0 + 4)) = 0;
    temp_a0_2 = temp_a0 + 8;
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xE3000C00;
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = 0;
    temp_a0_3 = temp_a0_2 + 8;
    (*(s32 *)((u8 *)temp_a0_3 + 4)) = 0x200000;
    (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xE3000A01;
    temp_a0_4 = temp_a0_3 + 8;
    (*(s32 *)((u8 *)temp_a0_4 + 0)) = 0xE2001E01;
    (*(s32 *)((u8 *)temp_a0_4 + 4)) = 0;
    temp_a0_5 = temp_a0_4 + 8;
    (*(s32 *)((u8 *)temp_a0_5 + 0)) = 0xE3001001;
    (*(s32 *)((u8 *)temp_a0_5 + 4)) = 0;
    temp_a0_6 = temp_a0_5 + 8;
    (*(s32 *)((u8 *)temp_a0_6 + 4)) = 0xC0;
    (*(s32 *)((u8 *)temp_a0_6 + 0)) = 0xE3001801;
    temp_a0_7 = temp_a0_6 + 8;
    (*(s32 *)((u8 *)temp_a0_7 + 4)) = 0x30;
    (*(s32 *)((u8 *)temp_a0_7 + 0)) = 0xE3001A01;
    temp_a0_8 = temp_a0_7 + 8;
    (*(s32 *)((u8 *)temp_a0_8 + 0)) = 0xFD100000;
    temp_a0_9 = temp_a0_8 + 8;
    temp_a0_10 = temp_a0_9 + 8;
    temp_a0_11 = temp_a0_10 + 8;
    (*(s32 *)((u8 *)temp_a0_8 + 4)) = (s32) ((arg2 * D_800BE620 * 2) + D_800BEDE4);
    (*(s32 *)((u8 *)temp_a0_9 + 0)) = 0xF5100000;
    (*(s32 *)((u8 *)temp_a0_9 + 4)) = 0x07000000;
    (*(s32 *)((u8 *)temp_a0_10 + 0)) = 0xE6000000;
    (*(s32 *)((u8 *)temp_a0_10 + 4)) = 0;
    (*(s32 *)((u8 *)temp_a0_11 + 0)) = 0xF3000000;
    temp_a0_12 = temp_a0_11 + 8;
    temp_t2 = arg6 * 0x180;
    temp_f6 = (s32) (*(f32 *)((u8 *)((D_800BE628 + temp_t2)) + 4));
    temp_v1 = temp_f6 - 1;
    if (temp_v1 < 0x7FF) {
        var_t1 = temp_v1;
    } else {
        var_t1 = 0x7FF;
    }
    temp_t7 = (s32) (temp_f6 * 2) / 8;
    if (temp_t7 <= 0) {
        var_a3 = 1;
    } else {
        var_a3 = temp_t7;
    }
    if (temp_t7 <= 0) {
        var_a2 = 1;
    } else {
        var_a2 = temp_t7;
    }
    (*(s32 *)((u8 *)temp_a0_11 + 4)) = (s32) ((((s32) (var_a3 + 0x7FF) / var_a2) & 0xFFF) | 0x07000000 | ((var_t1 & 0xFFF) << 0xC));
    (*(s32 *)((u8 *)temp_a0_12 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)temp_a0_12 + 4)) = 0;
    temp_a0_13 = temp_a0_12 + 8;
    temp_a0_14 = temp_a0_13 + 8;
    (*(s32 *)((u8 *)temp_a0_13 + 4)) = 0;
    (*(s32 *)((u8 *)temp_a0_13 + 0)) = (s32) (((((s32) (((s32) (*(f32 *)((u8 *)((D_800BE628 + temp_t2)) + 4)) * 2) + 7) >> 3) & 0x1FF) << 9) | 0xF5100000);
    (*(s32 *)((u8 *)temp_a0_14 + 0)) = 0xF2000000;
    temp_a0_15 = temp_a0_14 + 8;
    (*(s32 *)((u8 *)temp_a0_14 + 4)) = (s32) (((((s32) (*(f32 *)((u8 *)((D_800BE628 + temp_t2)) + 4)) - 1) * 4) & 0xFFF) << 0xC);
    (*(s32 *)((u8 *)temp_a0_15 + 0)) = 0xFF100003;
    temp_a0_16 = temp_a0_15 + 8;
    (*(s32 *)((u8 *)temp_a0_15 + 4)) = arg4;
    (*(s32 *)((u8 *)temp_a0_16 + 0)) = 0xED000000;
    temp_a0_17 = temp_a0_16 + 8;
    temp_a0_18 = temp_a0_17 + 8;
    (*(s32 *)((u8 *)temp_a0_16 + 4)) = (s32) ((((s32) ((f32) (s32) (*(f32 *)((u8 *)((D_800BE628 + temp_t2)) + 4)) * 4.0f) & 0xFFF) << 0xC) | 4);
    (*(s32 *)((u8 *)temp_a0_17 + 0)) = 0xE400C004;
    (*(s32 *)((u8 *)temp_a0_17 + 4)) = 0;
    (*(s32 *)((u8 *)temp_a0_18 + 0)) = 0xE1000000;
    temp_a0_19 = temp_a0_18 + 8;
    temp_t4 = arg1 << 0x15;
    (*(s32 *)((u8 *)temp_a0_18 + 4)) = temp_t4;
    (*(s32 *)((u8 *)temp_a0_19 + 0)) = 0xF1000000;
    (*(s32 *)((u8 *)temp_a0_19 + 4)) = 0x10000400;
    temp_a0_20 = temp_a0_19 + 8;
    (*(s32 *)((u8 *)temp_a0_20 + 0)) = 0xFD100000;
    temp_a0_21 = temp_a0_20 + 8;
    temp_a0_22 = temp_a0_21 + 8;
    temp_a0_23 = temp_a0_22 + 8;
    (*(s32 *)((u8 *)temp_a0_20 + 4)) = (s32) (D_8002AAE8[D_800BE9C0] + (arg2 * D_800BE620 * 2));
    (*(s32 *)((u8 *)temp_a0_21 + 0)) = 0xF5100000;
    (*(s32 *)((u8 *)temp_a0_21 + 4)) = 0x07000000;
    (*(s32 *)((u8 *)temp_a0_22 + 0)) = 0xE6000000;
    (*(s32 *)((u8 *)temp_a0_22 + 4)) = 0;
    (*(s32 *)((u8 *)temp_a0_23 + 0)) = 0xF3000000;
    temp_a0_24 = temp_a0_23 + 8;
    temp_f8 = (s32) (*(f32 *)((u8 *)((D_800BE628 + temp_t2)) + 4));
    temp_v1_2 = temp_f8 - 1;
    if (temp_v1_2 < 0x7FF) {
        var_t1_2 = temp_v1_2;
    } else {
        var_t1_2 = 0x7FF;
    }
    temp_t6 = (s32) (temp_f8 * 2) / 8;
    if (temp_t6 <= 0) {
        var_a3_2 = 1;
    } else {
        var_a3_2 = temp_t6;
    }
    if (temp_t6 <= 0) {
        var_a2_2 = 1;
    } else {
        var_a2_2 = temp_t6;
    }
    (*(s32 *)((u8 *)temp_a0_23 + 4)) = (s32) ((((s32) (var_a3_2 + 0x7FF) / var_a2_2) & 0xFFF) | 0x07000000 | ((var_t1_2 & 0xFFF) << 0xC));
    (*(s32 *)((u8 *)temp_a0_24 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)temp_a0_24 + 4)) = 0;
    temp_a0_25 = temp_a0_24 + 8;
    temp_a0_26 = temp_a0_25 + 8;
    (*(s32 *)((u8 *)temp_a0_25 + 4)) = 0;
    (*(s32 *)((u8 *)temp_a0_25 + 0)) = (s32) (((((s32) (((s32) (*(f32 *)((u8 *)((D_800BE628 + temp_t2)) + 4)) * 2) + 7) >> 3) & 0x1FF) << 9) | 0xF5100000);
    (*(s32 *)((u8 *)temp_a0_26 + 0)) = 0xF2000000;
    temp_a0_27 = temp_a0_26 + 8;
    (*(s32 *)((u8 *)temp_a0_26 + 4)) = (s32) (((((s32) (*(f32 *)((u8 *)((D_800BE628 + temp_t2)) + 4)) - 1) * 4) & 0xFFF) << 0xC);
    (*(s32 *)((u8 *)temp_a0_27 + 0)) = 0xFF100003;
    temp_a0_28 = temp_a0_27 + 8;
    (*(s32 *)((u8 *)temp_a0_27 + 4)) = arg5;
    (*(s32 *)((u8 *)temp_a0_28 + 0)) = 0xE400C004;
    temp_a0_29 = temp_a0_28 + 8;
    (*(s32 *)((u8 *)temp_a0_28 + 4)) = 0;
    (*(s32 *)((u8 *)temp_a0_29 + 0)) = 0xE1000000;
    (*(s32 *)((u8 *)temp_a0_29 + 4)) = temp_t4;
    temp_a0_30 = temp_a0_29 + 8;
    (*(s32 *)((u8 *)temp_a0_30 + 0)) = 0xF1000000;
    (*(s32 *)((u8 *)temp_a0_30 + 4)) = 0x10000400;
    temp_v0 = render_set_scissor(render_set_color_image(temp_a0_30 + 8, temp_a0_30, var_a2_2, var_a3_2), D_80083336, 0, 0, 0, 0);
    (*(s32 *)((u8 *)temp_v0 + 4)) = 0x80000;
    (*(s32 *)((u8 *)temp_v0 + 0)) = 0xE3000C00;
    return temp_v0 + 8;
}
typedef struct {
    f32 x, y, z;
    u8 state;
    u8 pad[3];
    struct_eu_bytes24 info;
    s8 b34;
    s32 v38;
} Ent_DD778_nm; /* = Ent_DD778 below, size 0x3C */
extern Ent_DD778_nm D_800DD778[];
extern u16 D_800DD740[][4];       /* per entry: z-buffer word read back (0xFFFF = pending) */
extern u16 D_800DD758[][4];       /* per entry: colour-buffer word read back (RGBA5551) */
extern s32 D_800DD730[];          /* per entry: projected depth */
extern s32 D_800DD770;
extern s32 D_800899D0[][2];       /* z-buffer decode table: (shift, add) per exponent */
extern void (*D_8008A420[])(Ent_DD778_nm *, s32, s32, s32);
void camera_world_to_screen(s32 arg0, f32 x, f32 y, f32 z, f32 *sx, f32 *sy, f32 *sz);

/* Occlusion probes (3 entries, e.g. lens flares): first, for entries read back in the current DL buffer
 * (state == D_800BE9C0 + 1), decode the z-buffer word and, when within 300 of the projected depth, call the entry's
 * callback with the pixel colour; then for new requests (state 3) project the point for player 0 and, when it lands
 * inside the viewport, queue the readback (occlusion_probe_readback_emit). Only runs when player == 0. */
/* was func_1517485C */
Gfx *occlusion_probes_update(Gfx *gdl, s16 player) {
    s32 i;
    s32 z, c, d;
    s32 x, y;
    f32 sx, sy, sz;
    u8 *cam;
    Ent_DD778_nm *e;

    if (player != 0) {
        return gdl;
    }
    for (i = 0, e = D_800DD778; i < 3; i++, e++) {
        if (e->state == D_800BE9C0 + 1) {
            z = D_800DD740[i][0];
            d = (u32)(D_800899D0[z >> 13][1] + (((z >> 2) & 0x7FF) << D_800899D0[z >> 13][0])) >> 3;
            d -= D_800DD730[i];
            if (d < 0) {
                d = -d;
            }
            if (d < 300) {
                c = D_800DD758[i][0];
                D_800DD770 = c;
                if (e->b34 != -1) {
                    D_8008A420[e->b34](e, (c >> 8) & 0xF8, (c >> 3) & 0xF8, (c << 2) & 0xF8);
                }
            }
            e->state = 0;
        }
    }
    for (i = 0, e = D_800DD778; i != 3; i++, e++) {
        if (e->state != 3) {
            continue;
        }
        D_800DD740[i][0] = 0xFFFF;
        e->state = D_800BE9C0 + 1;
        camera_world_to_screen(player, e->x, e->y, e->z, &sx, &sy, &sz);
        D_800DD730[i] = (s32)sz;
        cam = (u8 *)D_800BE628 + player * 0x180;
        x = (s32)sx;
        y = (s32)sy;
        if (x < (s32)*(f32 *)(cam + 0x2C) || !(x < (s32)*(f32 *)(cam + 0x30))) {
            continue;
        }
        if (y < (s32)*(f32 *)(cam + 0x24) || !(y < (s32)*(f32 *)(cam + 0x28))) {
            continue;
        }
        gdl = (Gfx *)occlusion_probe_readback_emit((u8 *)gdl, x, y, 1, (s32)D_800DD740[i], (s32)D_800DD758[i], player);
    }
    return gdl;
}
typedef struct {
    f32 x, y, z;
    u8 state;
    u8 pad[3];
    struct_eu_bytes24 info;
    s8 b34;
    s32 v38;
} Ent_DD778; // size 0x3C

/* was func_15174B60 */
s32 occlusion_probe_request(f32 arg0, f32 arg1, f32 arg2, struct_eu_bytes24 *arg3, s8 arg4, s32 arg5) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_800DD778[i].state == 0) {
            D_800DD778[i].x = arg0;
            D_800DD778[i].y = arg1;
            D_800DD778[i].state = 3;
            D_800DD778[i].z = arg2;
            D_800DD778[i].b34 = arg4;
            D_800DD778[i].v38 = arg5;
            if (arg3 != NULL) {
                D_800DD778[i].info = *arg3;
            }
            return 0;
        }
    }
    return 1;
}
