#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* P124: the 0x3C-byte effect template image_fx_spawn_template / image_fx_spawn copy into a new effect record (+0x10);
 * same layout as S59A0 in game_eu_1231B0.c. */
typedef struct {
    void *u0;
    s32 u4;
    s32 u8;
    s32 uC;
    s32 u10;
    s16 u14;
    s16 u16;
    s16 u18;
    s16 pad1A;
    f32 u1C;
    f32 u20;
    s16 u24;
    s16 u26;
    s16 u28;
    s16 u2A;
    s16 u2C;
    s16 u2E;
    u8 u30; /* effect type: index into g_node_end_handlers (record +0x40) */
    u8 u31;
    u8 u32;
    u8 u33;
    u8 u34;
    u8 u35;
    u8 u36;
    u8 u37;
    u8 u38;
    u8 u39;
    u8 pad3A[2];
} EffectTemplateE48B0;
u8 *image_fx_spawn_template(void *);

void cs_overlay_counter_box_open(s32, s32);


void cs_overlay_open_boxes_4_8(void);
void cs_overlay_open_counter_right(void);
void cs_overlay_open_counter_left(void);
void cs_overlay_open_box3(void);
void cs_overlay_open_box0(void);
void cs_overlay_reset(void);   /* P182: no result (asm v0 = a stale address) */
s32 cs_overlay_mark_boxes_closing(void);
s32 cs_overlay_destroy_all(void);
s32 cs_overlay_create_bars(void);

/* was func_150B70A0 */
void cs_overlay_update(s32 arg0) {
    switch (g_cs_overlay_cmd) {
    case 1:
        cs_overlay_reset();
        return;
    case 2:
        cs_overlay_mark_boxes_closing();
        return;
    case 4:
        cs_overlay_destroy_all();
        return;
    case 5:
        cs_overlay_open_box0();
        return;
    case 6:
        cs_overlay_open_box3();
        return;
    case 7:
        cs_overlay_open_counter_left();
        return;
    case 8:
        cs_overlay_open_boxes_4_8();
        return;
    case 9:
        cs_overlay_open_counter_right();
        return;
    case 10:
        cs_overlay_create_bars();
        /* fallthrough */
    default:
        return;
    }
}

extern s32 g_view_count_minus1; /* was D_800BEE08 */
void *screen_tint_create(s32, s32, s32, s32, s32, s32, u8, s32);

// hud_box_reset: removes the old box object g_cs_overlay_tint (node_destroy), creates a new one (screen_tint_create(0, 0, 0xFF,
// 0, 0, g_view_count_minus1, 0, 0)), sets state g_cs_overlay_cmd = 3 and clears the 10 words g_cs_overlay_fx.
/* was func_150B7170 */
void cs_overlay_reset(void) {
    s32 i;

    if (g_cs_overlay_tint != 0) {
        node_destroy((struct102 *) g_cs_overlay_tint);
    }
    g_cs_overlay_tint = (s32) screen_tint_create(0, 0, 0xFF, 0, 0, g_view_count_minus1, 0, 0);
    g_cs_overlay_cmd = 3;
    for (i = 0; i < 10; i++) {
        g_cs_overlay_fx[i] = 0;
    }
}

extern s32 g_cs_overlay_fx_3; /* was D_800D9CC4 */

/* was func_150B7214 */
s32 cs_overlay_mark_boxes_closing(void) {
    s32 *var_v1;
    s32 temp_v0;

    var_v1 = g_cs_overlay_fx;
    do {
        temp_v0 = var_v1[5];
        var_v1 = (s32 *)((u8 *)var_v1 + (4));
        if (temp_v0 != 0) {
            (*(s32 *)((u8 *)temp_v0 + 0x20)) = 1;
        }
    } while (var_v1 != &g_cs_overlay_fx_3);
    g_cs_overlay_cmd = 3;
    return temp_v0;
}
/* was func_150B7258 */
s32 cs_overlay_destroy_all(void) {
    struct102 **p;

    if (*(struct102 **)&g_cs_overlay_tint != NULL) {
        node_destroy(*(struct102 **)&g_cs_overlay_tint);
        *(struct102 **)&g_cs_overlay_tint = NULL;
    }
    p = (struct102 **)g_cs_overlay_fx; do { // fakematch: same-line `do` sets the s0/s1 addiu order
        if (*p != NULL) {
            node_destroy(*p);
            *p = NULL;
        }
        p++;
    } while (p != (struct102 **)g_cs_overlay_fx_end);
    g_cs_overlay_cmd = 3;
}

/* was func_150B72DC */
void overlay_fx_scroll_update(u8 *arg0) {
    *(s16 *)(arg0 + 0x34) += g_frame_ticks * 0x30;
    if (*(s16 *)(arg0 + 0x34) > 0x800) {
        *(s16 *)(arg0 + 0x34) = -0xC00;
    }
}

extern s32 g_cs_overlay_img_pulse; /* was D_80091CC8 */

/* was func_150B731C */
void overlay_fx_pulse_update(u8 *arg0) {
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f0;
    s32 temp_t6;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    if (((*(s32 *)((u8 *)arg0 + 0x20)) != 0) && ((*(s32 *)((u8 *)arg0 + 0x18)) == (*(s16 *)((u8 *)arg0 + 0x26)))) {
        temp_v0 = (*(s32 *)((u8 *)arg0 + 0x1C));
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x30));
        temp_f12 = (f32) temp_v0;
        if (temp_f2 < temp_f12) {
            var_f0 = -(temp_f2 - temp_f12);
        } else {
            var_f0 = temp_f2 - temp_f12;
        }
        if ((f32) (g_frame_ticks * 3) < var_f0) {
            goto block_6;
        }
        (*(f32 *)((u8 *)arg0 + 0x30)) = temp_f12;
        if (temp_v0 == 0xAA) {
            var_v1 = (*(u8 *)((u8 *)arg0 + 0x45)) + (g_frame_ticks * 8);
            if (var_v1 >= 0x100) {
                var_v1 = 0;
                temp_t6 = (*(s32 *)((u8 *)arg0 + 0x20)) + 1;
                (*(s32 *)((u8 *)arg0 + 0x20)) = temp_t6;
                if (temp_t6 == 3) {
                    (*(s32 **)((u8 *)arg0 + 0x10)) = &g_cs_overlay_img_pulse;
                    (*(s8 *)((u8 *)arg0 + 0x40)) = 8;
                    (*(u8 *)((u8 *)arg0 + 0x45)) = 0xFFU;
                    (*(s16 *)((u8 *)arg0 + 0x3C)) = 0x80;
                    (*(s16 *)((u8 *)arg0 + 0x3E)) = 0x10;
                    (*(s16 *)((u8 *)arg0 + 0x26)) = 0;
                    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
                    return;
                }
            }
            (*(u8 *)((u8 *)arg0 + 0x45)) = (u8) var_v1;
            return;
        }
        temp_f2_2 = (*(f32 *)((u8 *)arg0 + 0x30));
        if (temp_f2_2 < 170.0f) {
            var_v0 = (s32) -(temp_f2_2 - 170.0f);
        } else {
            var_v0 = (s32) (temp_f2_2 - 170.0f);
        }
        var_v1_2 = 0xFF - (var_v0 * 9);
        if (var_v1_2 < 0) {
            var_v1_2 = 0;
        }
        (*(u8 *)((u8 *)arg0 + 0x45)) = (u8) var_v1_2;
        return;
    }
block_6:
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x30)) - (f32) (g_frame_ticks * 3));
    if ((*(f32 *)((u8 *)arg0 + 0x30)) <= 140.0f) {
        (*(s16 *)((u8 *)arg0 + 0x26)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x26)) + 0x100);
        if ((*(s16 *)((u8 *)arg0 + 0x26)) >= ((*(u8 *)((u8 *)arg0 + 0x41)) << 8)) {
            (*(s16 *)((u8 *)arg0 + 0x26)) = 0;
        }
        (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (200.0f - (140.0f - (*(f32 *)((u8 *)arg0 + 0x30))));
    }
    if ((*(f32 *)((u8 *)arg0 + 0x30)) < 170.0f) {
        var_v0_2 = (s32) -((*(f32 *)((u8 *)arg0 + 0x30)) - 170.0f);
    } else {
        var_v0_2 = (s32) ((*(f32 *)((u8 *)arg0 + 0x30)) - 170.0f);
    }
    var_v1_3 = 0xFF - (var_v0_2 * 8);
    if (var_v1_3 < 0) {
        var_v1_3 = 0;
    }
    (*(u8 *)((u8 *)arg0 + 0x45)) = (u8) var_v1_3;
}
/* was func_150B757C */
void overlay_fx_slide_in_update(u8 *arg0) {
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x18));
    if (temp_v0 == 0x1E) {
        var_v1 = (*(u8 *)((u8 *)arg0 + 0x45)) + (g_frame_ticks * 8);
        if (var_v1 >= 0x100) {
            var_v1 = 0;
        }
        (*(u8 *)((u8 *)arg0 + 0x45)) = (u8) var_v1;
    }
    var_v0 = temp_v0 + (g_frame_ticks * 2);
    if (var_v0 >= 0x1F) {
        var_v0 = 0x1E;
    }
    (*(s32 *)((u8 *)arg0 + 0x18)) = var_v0;
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (((s32) (var_v0 * -0x54) / 30) + 0xE6);
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (((s32) (var_v0 * -0x32) / 30) + 0xAA);
}
/* was func_150B7688 */
void overlay_fx_scale_grow_update(u8 *arg0) {
    if (*(s16 *)(arg0 + 0x38) != 0x1000) {
        *(s16 *)(arg0 + 0x38) += g_frame_ticks << 8;
        if (*(s16 *)(arg0 + 0x38) > 0x1000) {
            *(s16 *)(arg0 + 0x38) = 0x1000;
        }
    } else if (*(s16 *)(arg0 + 0x3A) != 0x1000) {
        *(s16 *)(arg0 + 0x3A) += g_frame_ticks << 8;
        if (*(s16 *)(arg0 + 0x3A) > 0x1000) {
            *(s16 *)(arg0 + 0x3A) = 0x1000;
        }
    }
}

u8 *image_fx_spawn(void *, s32);
extern s32 g_cs_overlay_img_cross; /* was D_80091CD4 */
extern s32 g_screen_width; /* was D_800BEA58 */

// effect_spawn_cross: spawns four type-7 effects (template g_cs_overlay_img_cross, priority arg3) around (arg0, arg1): above and
// below (arg1 -/+ d, flag byte 0 / 8) and left and right (arg0 -/+ d, flag 4 / 0, u16 0x100), where d is the
// distance of arg0 to the nearer screen edge (g_screen_width = screen width). arg2 goes to words 0xC and +0x14.
/* was func_150B7700 */
void cs_overlay_spawn_cross(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    EffectTemplateE48B0 t;
    s32 d;
    s32 v;

    t.u2A = 0x1000;
    t.u0 = &g_cs_overlay_img_cross;
    t.u8 = (arg0 << 16) | (arg1 & 0xFFFF);
    t.u28 = 0x1000;
    t.uC = arg2;
    t.u14 = arg2;
    t.u18 = 0;
    t.u24 = 0;
    t.u26 = 0;
    t.u2C = 0x10;
    t.u2E = 0x10;
    t.u30 = 7;
    t.u31 = 2;
    t.u32 = 0xFF;
    t.u33 = 0;
    t.u34 = 0;
    t.u35 = 0xFF;
    t.u36 = 7;
    t.u37 = 0x11;
    if (arg0 < (g_screen_width >> 1)) {
        d = g_screen_width - arg0;
    } else {
        d = arg0;
    }
    v = arg1 - d;
    t.u10 = (arg0 << 16) | (v & 0xFFFF);
    t.u39 = 0;
    t.u16 = 0;
    t.u1C = arg0;
    t.u20 = v;
    image_fx_spawn(&t, arg3);
    v = arg1 + d;
    t.u10 = (arg0 << 16) | (v & 0xFFFF);
    t.u39 = 8;
    t.u20 = v;
    image_fx_spawn(&t, arg3);
    v = arg0 - d;
    t.u1C = v;
    t.u10 = (v << 16) | (arg1 & 0xFFFF);
    t.u39 = 4;
    t.u16 = 0x100;
    t.u20 = arg1;
    image_fx_spawn(&t, arg3);
    v = arg0 + d;
    t.u10 = (v << 16) | (arg1 & 0xFFFF);
    t.u39 = 0;
    t.u1C = v;
    image_fx_spawn(&t, arg3);
}
/* was func_150B78D0 */
void overlay_fx_lerp_pos_update(u8 *arg0) {
    s16 temp_v0;
    s16 temp_v1;
    s32 temp_lo;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x18));
    temp_lo = (s32) ((*(s16 *)((u8 *)arg0 + 0x24)) << 0x10) / (s32) (*(s32 *)((u8 *)arg0 + 0x1C));
    temp_v1 = (*(s16 *)((u8 *)arg0 + 0x1A));
    (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (((s32) (((*(s16 *)((u8 *)arg0 + 0x20)) - temp_v0) * temp_lo) >> 0x10) + temp_v0);
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) (((s32) (((*(s16 *)((u8 *)arg0 + 0x22)) - temp_v1) * temp_lo) >> 0x10) + temp_v1);
}
extern s32 g_cs_overlay_img_box; /* was D_80091C8C */

/* was func_150B7964 */
void cs_overlay_open_box0(void) {
    struct {
        s32 *unk0;
        u8 pad4[0x14 - 4];
        s16 unk14;
        s16 unk16;
        s16 unk18;
        u8 pad1A[2];
        f32 unk1C;
        f32 unk20;
        s16 unk24;
        s16 unk26;
        s16 unk28;
        s16 unk2A;
        s16 unk2C;
        s16 unk2E;
        s8 unk30;
        s8 unk31;
        u8 unk32;
        s8 unk33;
        s8 unk34;
        u8 unk35;
        s8 unk36;
        s8 unk37;
        s8 unk38;
        s8 unk39;
    } sp;

    sp.unk31 = 1;
    sp.unk2C = 0x58;
    sp.unk1C = 60.0f;
    sp.unk20 = 60.0f;
    sp.unk14 = 0;
    sp.unk16 = 0;
    sp.unk18 = 0;
    sp.unk2E = 0x58;
    sp.unk30 = 6;
    sp.unk0 = &g_cs_overlay_img_box;
    sp.unk32 = 0xFF;
    sp.unk33 = 0;
    sp.unk34 = 0;
    sp.unk35 = 0xFF;
    sp.unk24 = 0;
    sp.unk26 = 0;
    sp.unk39 = 0;
    sp.unk36 = 7;
    sp.unk37 = 0x15;
    sp.unk38 = 1;
    sp.unk28 = 0x51;
    sp.unk2A = 0x51;
    if (*(struct102 **)g_cs_overlay_fx != NULL) {
        node_destroy(*(struct102 **)g_cs_overlay_fx);
    }
    *g_cs_overlay_fx = (s32)image_fx_spawn_template(&sp);
    g_cs_overlay_cmd = 3;
}

extern s32 g_cs_overlay_img_box; /* was D_80091C8C */

/* was func_150B7A40 */
void cs_overlay_open_box3(void) {
    struct {
        s32 *unk0;
        u8 pad4[0x14 - 4];
        s16 unk14;
        s16 unk16;
        s16 unk18;
        u8 pad1A[2];
        f32 unk1C;
        f32 unk20;
        s16 unk24;
        s16 unk26;
        s16 unk28;
        s16 unk2A;
        s16 unk2C;
        s16 unk2E;
        s8 unk30;
        s8 unk31;
        u8 unk32;
        s8 unk33;
        s8 unk34;
        u8 unk35;
        s8 unk36;
        s8 unk37;
        s8 unk38;
        s8 unk39;
    } sp;

    if (*(struct102 **)g_cs_overlay_fx != NULL) {
        node_destroy(*(struct102 **)g_cs_overlay_fx);
        *g_cs_overlay_fx = 0;
    }
    sp.unk18 = 0x4D;
    sp.unk31 = 0xF;
    sp.unk14 = 0;
    sp.unk16 = 0;
    sp.unk2C = 0x58;
    sp.unk2E = 0x58;
    sp.unk30 = 0;
    sp.unk0 = &g_cs_overlay_img_box;
    sp.unk24 = 0;
    sp.unk26 = 0;
    sp.unk32 = 0xFF;
    sp.unk33 = 0;
    sp.unk34 = 0;
    sp.unk35 = 0xFF;
    sp.unk36 = 7;
    sp.unk37 = 0x11;
    sp.unk38 = 1;
    sp.unk39 = 0;
    sp.unk28 = 0x1000;
    sp.unk2A = 0x1000;
    sp.unk1C = 60.0f;
    sp.unk20 = 60.0f;
    if (((struct102 **)g_cs_overlay_fx)[3] != NULL) {
        node_destroy(((struct102 **)g_cs_overlay_fx)[3]);
    }
    g_cs_overlay_fx[3] = (s32)image_fx_spawn_template(&sp);
    g_cs_overlay_cmd = 3;
}

/* was func_150B7B3C */
void cs_overlay_open_counter_left(void) {
    cs_overlay_counter_box_open(0x3C, 1);
    g_cs_overlay_cmd = 3;
}

/* was func_150B7B6C */
void cs_overlay_open_counter_right(void) {
    cs_overlay_counter_box_open(0xE6, 2);
    g_cs_overlay_cmd = 3;
}

extern s32 g_cs_overlay_img_counter; /* was D_80091C98 */

// hud_counter_box_open: replaces HUD box slot `slot` of g_cs_overlay_fx (the old one is removed with node_destroy) by a
// new type-6 box effect (image_fx_spawn_template) using the g_cs_overlay_img_counter graphics, `width` wide and 170 high (0x51 / 0x51
// offsets, 0x58 / 0x40 size, colour 0xFF / 0 / 0 / 0xFF, flags 7 / 0x15 / 1).
/* was func_150B7B9C */
void cs_overlay_counter_box_open(s32 width, s32 slot) {
    EffectTemplateE48B0 sp;
    s32 *box;

    sp.u30 = 6;
    sp.u2E = 0x40;
    box = &g_cs_overlay_fx[slot];
    sp.u31 = 1;
    sp.u2C = 0x58;
    sp.u1C = width;
    sp.u14 = 0;
    sp.u16 = 0;
    sp.u18 = 0;
    sp.u0 = &g_cs_overlay_img_counter;
    sp.u32 = 0xFF;
    sp.u33 = 0;
    sp.u34 = 0;
    sp.u35 = 0xFF;
    sp.u24 = 0;
    sp.u26 = 0;
    sp.u39 = 0;
    sp.u36 = 7;
    sp.u37 = 0x15;
    sp.u38 = 1;
    sp.u28 = 0x51;
    sp.u2A = 0x51;
    sp.u20 = 170.0f;
    if (*box != 0) {
        node_destroy((struct102 *)*box);
    }
    *box = (s32)image_fx_spawn_template(&sp);
}

extern s32 g_cs_overlay_img_counter; /* was D_80091C98 */
extern s32 g_cs_overlay_img_a4; /* was D_80091CA4 */
extern s32 g_cs_overlay_img_b0; /* was D_80091CB0 */

/* was func_150B7C88 */
void cs_overlay_open_boxes_4_8(void) {
    struct {
        s32 *unk0;
        s32 *unk4;
        u8 pad8[0x14 - 8];
        s16 unk14;
        s16 unk16;
        s16 unk18;
        u8 pad1A[2];
        f32 unk1C;
        f32 unk20;
        s16 unk24;
        s16 unk26;
        s16 unk28;
        s16 unk2A;
        s16 unk2C;
        s16 unk2E;
        s8 unk30;
        s8 unk31;
        u8 unk32;
        s8 unk33;
        s8 unk34;
        u8 unk35;
        s8 unk36;
        s8 unk37;
        s8 unk38;
        s8 unk39;
    } sp;

    if (((struct102 **)g_cs_overlay_fx)[1] != NULL) {
        node_destroy(((struct102 **)g_cs_overlay_fx)[1]);
        g_cs_overlay_fx[1] = 0;
    }
    sp.unk1C = 60.0f;
    sp.unk20 = 170.0f;
    sp.unk2C = 0x40;
    sp.unk2E = 0x40;
    sp.unk30 = 4;
    sp.unk0 = &g_cs_overlay_img_a4;
    sp.unk4 = &g_cs_overlay_img_b0;
    sp.unk14 = 0;
    sp.unk16 = 0;
    sp.unk18 = 0;
    sp.unk31 = 0;
    sp.unk24 = -0x800;
    sp.unk26 = 9;
    sp.unk32 = 0xFF;
    sp.unk33 = 0;
    sp.unk34 = 0;
    sp.unk35 = 0xFF;
    sp.unk36 = 0xD;
    sp.unk37 = 0x12;
    sp.unk38 = 2;
    sp.unk39 = 3;
    sp.unk28 = 0x1000;
    sp.unk2A = 0x1000;
    if (((struct102 **)g_cs_overlay_fx)[4] != NULL) {
        node_destroy(((struct102 **)g_cs_overlay_fx)[4]);
    }
    g_cs_overlay_fx[4] = (s32)image_fx_spawn_template(&sp);
    sp.unk24 = 0;
    sp.unk26 = 0;
    sp.unk2C = 0x58;
    sp.unk2E = 0x40;
    sp.unk30 = 0;
    sp.unk36 = 7;
    sp.unk37 = 0x11;
    sp.unk0 = &g_cs_overlay_img_counter;
    sp.unk38 = 1;
    if (((struct102 **)g_cs_overlay_fx)[8] != NULL) {
        node_destroy(((struct102 **)g_cs_overlay_fx)[8]);
    }
    g_cs_overlay_fx[8] = (s32)image_fx_spawn_template(&sp);
    g_cs_overlay_cmd = 3;
}

u8 *image_fx_spawn_template(void *);
extern s32 g_cs_overlay_img_bar; /* was D_80091CBC */
extern s32 g_cs_overlay_img_counter; /* was D_80091C98 */

// hud_bars_create: (re)creates the effect records g_cs_overlay_fx[5..7] (three type-5 bars from template g_cs_overlay_img_bar at
// y 150 / 170 / 190, alpha 0x80 / 0xFF / 0x80) and [9] (a type-0 effect from g_cs_overlay_img_counter at 230, 170); frees [2]
// first. Returns the last record; sets g_cs_overlay_cmd = 3. The free before [6] / [7] passes g_cs_overlay_fx[5] (as the asm:
// the original source frees the wrong slot there).
/* was func_150B7DFC */
s32 cs_overlay_create_bars(void) {
    EffectTemplateE48B0 t;

    if (g_cs_overlay_fx[2] != 0) {
        node_destroy((struct102 *) g_cs_overlay_fx[2]);
        g_cs_overlay_fx[2] = 0;
    }
    t.u31 = 3;
    t.u2C = 0x40;
    t.u2E = 0x10;
    t.u30 = 5;
    t.u24 = 0;
    t.u26 = 0;
    t.u14 = 0;
    t.u16 = 0;
    t.u18 = 0;
    t.u0 = &g_cs_overlay_img_bar;
    t.u4 = 0;
    t.u8 = 0;
    t.u10 = 0;
    t.u32 = 0xFF;
    t.u33 = 0;
    t.u34 = 0;
    t.u35 = 0x80;
    t.u36 = 7;
    t.u37 = 0x11;
    t.u38 = 1;
    t.u39 = 0;
    t.u28 = 0x1000;
    t.u2A = 0x1000;
    t.u20 = 150.0f;
    t.u1C = 230.0f;
    t.uC = (s32) t.u20;
    if (g_cs_overlay_fx[5] != 0) {
        node_destroy((struct102 *) g_cs_overlay_fx[5]);
    }
    g_cs_overlay_fx[5] = (s32) image_fx_spawn_template(&t);
    t.u16 = 0x100;
    t.u8 = 0x100;
    t.u35 = 0xFF;
    t.u20 = 170.0f;
    t.uC = (s32) t.u20;
    if (g_cs_overlay_fx[6] != 0) {
        node_destroy((struct102 *) g_cs_overlay_fx[5]);
    }
    g_cs_overlay_fx[6] = (s32) image_fx_spawn_template(&t);
    t.u16 = 0x200;
    t.u8 = 0x200;
    t.u35 = 0x80;
    t.u20 = 190.0f;
    t.uC = (s32) t.u20;
    if (g_cs_overlay_fx[7] != 0) {
        node_destroy((struct102 *) g_cs_overlay_fx[5]);
    }
    g_cs_overlay_fx[7] = (s32) image_fx_spawn_template(&t);
    t.u14 = 0;
    t.u16 = 0;
    t.u18 = 0;
    t.u31 = 0;
    t.u2C = 0x58;
    t.u2E = 0x40;
    t.u35 = 0xFF;
    t.u30 = 0;
    t.u0 = &g_cs_overlay_img_counter;
    t.u1C = 230.0f;
    t.u20 = 170.0f;
    if (g_cs_overlay_fx[9] != 0) {
        node_destroy((struct102 *) g_cs_overlay_fx[9]);
    }
    g_cs_overlay_fx[9] = (s32) image_fx_spawn_template(&t);
    g_cs_overlay_cmd = 3;
    return g_cs_overlay_fx[9];
}