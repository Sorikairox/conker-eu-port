#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A0BC0[];


s32 memcpy(s32, u8 **, s32);

/* P80: arg3 goes on to fb_fx_spawn (its 2nd node_alloc argument); the only caller, scene_event_run_b, passes 0 */
/* was func_150CE660 */
s32 fb_zoom_fx_spawn(u8 *arg0, s16 arg1, s32 arg2, s32 arg3) {
    struct {
        u8 * u20;
        u8 u24;
        u8 pad25[0x3];
        f32 u28;
        f32 u2C;
        s32 u30;
        s8 u34;
        u8 pad35[0x8DB];
        s8 u910;
        s8 u911;
        s8 u912;
        u8 pad913[0x1];
        s16 u914;
        s8 u916;
    } sp;
    s32 var_v0;

    if (arg0 == NULL) {
        return 0;
    }
    sp.u910 = 1;
    sp.u911 = 1;
    sp.u912 = 0;
    sp.u916 = 2;
    sp.u30 = 0x2710;
    sp.u34 = 0;
    sp.u28 = 30000.0f;
    sp.u2C = 30000.0f;
    sp.u914 = arg1;
    sp.u20 = arg0;
    sp.u24 = (*(u8 *)((u8 *)arg0 + 0x3B));
    var_v0 = fb_fx_spawn(&sp.u910, 0x8F0, arg2 & 0xFF, arg3);
    if (var_v0 != 0) {
        var_v0 = memcpy(var_v0 + 0x18, &sp.u20, 0x8F0);
    }
    return var_v0;
}
extern f32 D_800A0BD0;
s32 world_to_screen(s32 *, u8 *, s32 *, s32 *, f32 *, s32);

/* was func_150CE710 */
s32 fb_zoom_fx_update(u8 *arg0) {
    struct {
        f32 u34;
        s32 u38;
        s32 u3C;
        s32 u40;
    } sp;
    u8 *sp28;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 var_f0;
    s32 temp_a3;
    s32 temp_f10;
    s32 temp_f18;
    s32 temp_f4;
    s32 temp_f8;
    u8 var_t5;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v1 = arg0 + 0x18;
    if (*(*(s32 **)((u8 *)arg0 + 0x18)) == 0) {
        return 0;
    }
    temp_v0 = (*(u8 **)((u8 *)temp_v1 + 0));
    if ((*(u8 *)((u8 *)temp_v1 + 4)) != (*(u8 *)((u8 *)temp_v0 + 0x3B))) {
        return 0;
    }
    temp_a3 = (*(s32 *)((u8 *)temp_v0 + 0x1D4));
    if (temp_a3 == 0) {
        (*(u8 *)((u8 *)temp_v1 + 0x14)) = (u8) ((*(u8 *)((u8 *)temp_v1 + 0x14)) & 0xFFFE);
    } else {
        sp28 = temp_v1;
        mtx_transform_point_or_origin(((u8 *)&D_800A0BC0), &sp.u40, temp_a3 + 0xD00);
        if (world_to_screen(&sp.u40, sp28 + 0x28, &sp.u3C, &sp.u38, &sp.u34, g_cur_view_player) != 0) {
            temp_f12 = (*(f32 *)((u8 *)sp28 + 0x28));
            temp_f0 = (*(f32 *)((u8 *)sp28 + 8)) * sp.u34;
            temp_f14 = (*(f32 *)((u8 *)sp28 + 0x2C));
            temp_f2 = (*(f32 *)((u8 *)sp28 + 0xC)) * sp.u34;
            temp_f18 = (s32) (temp_f12 - temp_f0);
            temp_f8 = (s32) (temp_f14 - temp_f2);
            (*(s32 *)((u8 *)sp28 + 0x18)) = temp_f18;
            (*(s32 *)((u8 *)sp28 + 0x1C)) = temp_f8;
            temp_f10 = (s32) (temp_f12 + temp_f0);
            (*(s32 *)((u8 *)sp28 + 0x20)) = temp_f10;
            temp_f4 = (s32) (temp_f14 + temp_f2);
            (*(s32 *)((u8 *)sp28 + 0x24)) = temp_f4;
            if (((f32) temp_f18 > D_800A0BD0) || ((f32) temp_f10 < 0.0f) || (var_f0 = (f32) temp_f8, (var_f0 > 215.0f)) || ((f32) temp_f4 < 0.0f)) {
                var_t5 = (*(u8 *)((u8 *)sp28 + 0x14)) & 0xFFFE;
                goto block_22;
            }
            if ((f32) (*(s32 *)((u8 *)sp28 + 0x18)) < 0.0f) {
                (*(s32 *)((u8 *)sp28 + 0x18)) = 0;
                var_f0 = (f32) (*(s32 *)((u8 *)sp28 + 0x1C));
            }
            if (var_f0 < 0.0f) {
                (*(s32 *)((u8 *)sp28 + 0x1C)) = 0;
            }
            if ((f32) (*(s32 *)((u8 *)sp28 + 0x20)) > D_800A0BD0) {
                (*(s32 *)((u8 *)sp28 + 0x20)) = 0x123;
            }
            if ((f32) (*(s32 *)((u8 *)sp28 + 0x24)) > 215.0f) {
                (*(s32 *)((u8 *)sp28 + 0x24)) = 0xD7;
            }
            (*(u8 *)((u8 *)sp28 + 0x14)) = (u8) ((*(u8 *)((u8 *)sp28 + 0x14)) | 1);
        } else {
            var_t5 = (*(u8 *)((u8 *)sp28 + 0x14)) & 0xFFFE;
block_22:
            (*(u8 *)((u8 *)sp28 + 0x14)) = var_t5;
        }
    }
    return 1;
}
/* the zoom effect state at arg0 + 0x18 */
typedef struct {
    u8  pad0[0x10];
    u32 step;           /* 0x10: 16.16 source advance per destination pixel */
    u8  pad14[4];
    u32 x0;             /* 0x18 rectangle (inclusive) */
    u32 y0;             /* 0x1C */
    u32 x1;             /* 0x20 */
    u32 y1;             /* 0x24 */
    u8  pad28[0x30 - 0x28];
    s16 colMap[0x280];  /* 0x30: source column per destination column */
    s16 rowMap[0x200];  /* 0x530: source row per destination row */
} Zoom150CE960;

/* Nearest-neighbour zoom of the rectangle (x0, y0) .. (x1, y1) of the 16-bit frame buffer `fb` (rows of
 * g_framebuffer_width pixels) in place, when arg0[0x2C] bit 0 is set. Rows are done bottom-up and right to left so a source
 * pixel is read before it is overwritten; a row with the same source as the row below is a copy of it. */
/* was func_150CE960 */
void fb_zoom_fx_apply(u8 *arg0, u16 *fb) {
    Zoom150CE960 *z;
    u32 acc;
    u32 src;
    u32 i;
    s32 x, y;

    z = (Zoom150CE960 *) (arg0 + 0x18);
    if (!(arg0[0x2C] & 1)) {
        return;
    }
    acc = 0;
    src = z->x0;
    for (i = z->x0; i <= z->x1; i++) {
        z->colMap[i] = src;
        acc += z->step;
        if (acc >= 0x10000) {
            src = i;
            acc -= 0x10000;
        }
    }
    acc = 0;
    src = z->y0;
    for (i = z->y0; i <= z->y1; i++) {
        z->rowMap[i] = src;
        acc += z->step;
        if (acc >= 0x10000) {
            src = i;
            acc -= 0x10000;
        }
    }
    for (y = z->y1; y >= (s32) z->y0; y--) {
        if (y != (s32) z->y1 && z->rowMap[y + 1] == z->rowMap[y]) {
            memcpy((s32) &fb[y * g_framebuffer_width + z->x0], (u8 **) &fb[(y + 1) * g_framebuffer_width + z->x0],
                   (z->x1 - z->x0) * 2 + 2);
        } else {
            for (x = z->x1; x >= (s32) z->x0; x--) {
                fb[y * g_framebuffer_width + x] = fb[z->rowMap[y] * g_framebuffer_width + z->colMap[x]];
            }
        }
    }
}

/* was func_150CEBA4 */
void fb_zoom_fx_handle_event(struct102 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = (u8 *)arg0 + 0x18;
    if (arg2 == 0x2D) {
        if (*(s32 *)arg1 == *(s32 *)v) {
            *(s32 *)v = *(s32 *)(arg1 + 4);
            v[4] = arg1[9];
        } else {
            if (*(s32 *)(arg1 + 4) == *(s32 *)v) {
                *(s32 *)v = *(s32 *)arg1;
                v[4] = arg1[8];
            }
            goto end; // fakematch: permuter artifact (no-op jump)
end:        ;
        }
    } else {
        if (arg1) { // fakematch: permuter artifact (empty if)
        }
        if (arg2 == 0) {
            s32 t = *(s32 *)arg1;
            if (t == *(s32 *)v || v[4] == arg1[4]) {
                node_destroy(arg0);
            }
        }
    }
}
