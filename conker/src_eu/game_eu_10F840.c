#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 beam_effect_spawn(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, struct127 *, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32);


float sqrtf(float);
f32 math_atan2f(f32, f32);
extern u8 *g_sprite_tex_descs[]; /* was D_8008CDEC */

// beam_effect_spawn: allocates a line / beam effect object (node_alloc(0xB, 0, 0x100, 1, 0xFF, 1)) from
// (x0, y0, z0) to (x1, y1, z1): start +0x94, end +0xB0, yaw +0xA4 / pitch +0xA0 of the direction (math_atan2f),
// widths +0xA8 / +0xAC / +0xBC / +0xC0, texture g_sprite_tex_descs[tex] (+0xD8) with two 4-vertex quads at +0x10 whose
// s / t span the texture size. mode (+0xD0) 0 = plain (+0xD6 = 1, +0xE0 = -1); otherwise it follows `target`
// (+0xDC, freed again with node_delete when NULL) with the extra parameters +0xD2 .. +0xF8. Returns the asm's
// leftover v0: 0 when the allocation fails, else obj + 0x80 (the quad loop pointer; no caller uses it); 0 on the
// node_delete path (the asm passes on that void call's v0).
/* was func_150E2030 */
s32 beam_effect_spawn(s32 arg0, f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, f32 w0, f32 w1, f32 w2, f32 w3,
                  s32 kind, s32 tex, s32 mode, s32 d2, s32 d4, struct127 *target, s32 da, s32 e2, s32 e0, s32 fc,
                  s32 fe, f32 e4, f32 e8, f32 ec, f32 f0, f32 f4, f32 f8) {
    u8 *obj;
    s16 *vt;
    f32 dx, dz;
    s32 i, s, t;
    u8 *img;

    obj = node_alloc(0xB, 0, 0x100, 1, 0xFF, 1);
    if (obj == NULL) {
        return 0;
    }
    *(s16 *) (obj + 0x90) = kind;
    *(f32 *) (obj + 0x94) = x0;
    *(f32 *) (obj + 0x98) = y0;
    *(f32 *) (obj + 0x9C) = z0;
    dx = x1 - x0;
    dz = z1 - z0;
    *(f32 *) (obj + 0xA4) = math_atan2f(-dx, -dz);
    *(f32 *) (obj + 0xA0) = math_atan2f(y1 - y0, sqrtf(dx * dx + dz * dz));
    *(f32 *) (obj + 0xC4) = 0.0f;
    *(f32 *) (obj + 0xC8) = 0.0f;
    *(f32 *) (obj + 0xCC) = 0.0f;
    *(f32 *) (obj + 0xB0) = x1;
    *(f32 *) (obj + 0xB4) = y1;
    *(f32 *) (obj + 0xB8) = z1;
    *(f32 *) (obj + 0xAC) = w1;
    *(f32 *) (obj + 0xA8) = w0;
    *(f32 *) (obj + 0xBC) = w2;
    *(f32 *) (obj + 0xC0) = w3;
    obj[0xE3] = 0;
    obj[0xFD] = 0;
    obj[0xFC] = fc;
    *(struct127 **) (obj + 0xDC) = target;
    obj[0xFE] = fe;
    *(u16 *) (obj + 0xD8) = tex;
    *(s8 *) (obj + 0xD0) = mode;
    if (*(s8 *) (obj + 0xD0) == 0) {
        *(s16 *) (obj + 0xD6) = 1;
        *(s16 *) (obj + 0xE0) = -1;
    } else if (target == NULL) {
        node_delete((struct102 *) obj);
        return 0;
    } else {
        *(s16 *) (obj + 0xD2) = d2;
        *(s16 *) (obj + 0xD6) = -(s16) d4;
        *(s16 *) (obj + 0xD4) = d4;
        obj[0xDA] = da;
        obj[0xE2] = e2;
        *(s16 *) (obj + 0xE0) = e0;
        *(f32 *) (obj + 0xE4) = e4;
        *(f32 *) (obj + 0xE8) = e8;
        *(f32 *) (obj + 0xEC) = ec;
        *(f32 *) (obj + 0xF0) = f0;
        *(f32 *) (obj + 0xF4) = f4;
        *(f32 *) (obj + 0xF8) = f8;
    }
    /* vertices 1..8 (16 bytes each from obj): flag 0, s / t = 0x2000 or 0x2000 + (size - 1) * 32 */
    vt = (s16 *) obj;
    for (i = 0; i < 2; i++) {
        img = g_sprite_tex_descs[*(s16 *) (obj + 0xD8)];
        s = (*(u16 *) (img + 6) - 1) * 32 + 0x2000;
        t = (*(u16 *) (img + 8) - 1) * 32 + 0x2000;
        vt += 32; /* 4 vertices */
        vt[-4] = 0x2000;
        vt[-3] = 0x2000;
        vt[-5] = 0;
        vt[-20] = s;
        vt[-19] = 0x2000;
        vt[-21] = 0;
        vt[4] = 0x2000;
        vt[5] = t;
        vt[3] = 0;
        vt[-12] = s;
        vt[-11] = t;
        vt[-13] = 0;
    }
    obj[0xDB] = 0;
    return (s32) (obj + 0x80);
}

float sqrtf(float);
f32 math_atan2f(f32, f32);
extern s32 D_800DC26C;
extern u8 g_aim_records[]; /* was D_800D9D80 */
int game_gu_random(void);
f32 vec3f_dot(u8 *, u8 *);
s32 floor_flags_surface_type(s32);
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, void *, void *, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
s32 object_ray_hit_nearest(struct127 *, f32, f32, f32, f32, f32, f32, s32, s32);
s32 impact_effect_spawn(f32, f32, f32, s32, s32, s32, s32);

// beam_effect_update: P310: update handler of the beam objects of beam_effect_spawn (object type 0xB descriptor at
// ROM 0x230D00, same layout as zap_bolt_update's; void (u8 *obj)). The life +0x90 counts down by g_frame_ticks frames;
// the beam is freed when it runs out or its followed object +0xDC changed (+0xE0 vs the object's +0x84 serial).
// Mode beams (+0xD0 != 0) re-attach both ends to the followed character's matrix +0xE2 (offsets +0xE4 / +0xF0,
// every 4th frame by the +0xE3 delay) and, each time the +0xD6 timer passes -(+0xD4), restart it (+0xD2) and pick a
// new target end: the character's aim record g_aim_records[+0x127] when it still matches (with a chance +3 of a spark
// beam + sound when D_800BE616 is off), else a point 2000 ahead along its facing; with no aim record (0xFF) every
// 3rd frame (+0xFD) a ray (collision_ray_cast) 75 * width ahead decides the end. Then (+0xD6 > 0) the head +0x94 moves
// toward the end along the yaw / pitch +0xA4 / +0xA0 at speed +0xA8 (clamped to the distance when +0xAC != 0);
// +0xFE == 1 leaves a trail (object_ray_hit_nearest). With +0xAC != 0 the beam is freed (after a impact_effect_spawn impact when
// +0xFC != 0) once the head is within +0xAC of the end or past the start distance, otherwise +0xC0 shrinks to it.
/* was func_150E2294 */
void beam_effect_update(u8 *obj) {
    u8 *target;
    u8 *mtx;
    u8 *aimrec;
    f32 *dir;
    f32 vec[3];
    f32 out[3];
    f32 hit[3];
    f32 len;
    f32 width;
    f32 alpha;
    f32 dist0;
    f32 limit;
    f32 c;
    f32 s;
    volatile f32 n[3];
    f32 vx;
    f32 vy;
    f32 vz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    f32 step;
    f32 endX;
    s32 tex;
    s32 aim;
    s32 rayhit;
    s32 ray;
    s32 hitobj;
    s32 idx;
    s32 heading;

    tex = 0x23;
    dist0 = 0.0f;
    *(s16 *) (obj + 0x90) -= g_frame_ticks;
    target = *(u8 **) (obj + 0xDC);
    if (*(s16 *) (obj + 0x90) < 0 || (target != NULL && *(s16 *) (obj + 0xE0) != -1 &&
                                      *(s16 *) (obj + 0xE0) != *(u16 *) (target + 0x84))) {
        node_destroy((struct102 *) obj);
        return;
    }
    if (*(s8 *) (obj + 0xD0) != 0) {
        if (obj[0xE3] != 0) {
            obj[0xE3]--;
        } else {
            target = *(u8 **) (obj + 0xDC);
            if (target != NULL && *(u8 **) (target + 0x1D4) != NULL && obj[0xDA] == target[0x3B] &&
                target[0x127] != 0xFF) {
                mtx = *(u8 **) (target + 0x1D4) + obj[0xE2] * 0x40;
                mtxf_transform_point((f32 (*)[4]) mtx, *(f32 *) (obj + 0xE4), *(f32 *) (obj + 0xE8), *(f32 *) (obj + 0xEC),
                              (f32 *) (obj + 0x94), (f32 *) (obj + 0x98), (f32 *) (obj + 0x9C));
                mtxf_transform_point((f32 (*)[4]) mtx, *(f32 *) (obj + 0xF0), *(f32 *) (obj + 0xF4), *(f32 *) (obj + 0xF8),
                              (f32 *) (obj + 0xB0), (f32 *) (obj + 0xB4), (f32 *) (obj + 0xB8));
                obj[0xE3] = 3;
            }
        }
        *(s16 *) (obj + 0xD6) -= g_frame_ticks;
        if (*(s16 *) (obj + 0xD6) < -*(s16 *) (obj + 0xD4)) {
            target = *(u8 **) (obj + 0xDC);
            *(s16 *) (obj + 0xD6) = *(s16 *) (obj + 0xD2);
            if (target == NULL || *(u8 **) (target + 0x1D4) == NULL || obj[0xDA] != target[0x3B]) {
                node_destroy((struct102 *) obj);
                return;
            }
            mtx = *(u8 **) (target + 0x1D4) + obj[0xE2] * 0x40;
            mtxf_transform_point((f32 (*)[4]) mtx, *(f32 *) (obj + 0xE4), *(f32 *) (obj + 0xE8), *(f32 *) (obj + 0xEC),
                          (f32 *) (obj + 0x94), (f32 *) (obj + 0x98), (f32 *) (obj + 0x9C));
            aim = (*(u8 **) (obj + 0xDC))[0x127];
            mtxf_transform_point((f32 (*)[4]) mtx, *(f32 *) (obj + 0xF0), *(f32 *) (obj + 0xF4), *(f32 *) (obj + 0xF8),
                          (f32 *) (obj + 0xB0), (f32 *) (obj + 0xB4), (f32 *) (obj + 0xB8));
            alpha = 0.0f;
            if (obj[0xFD]-- == 0) {
                obj[0xFD] = 2;
                ray = TRUE;
            } else {
                ray = FALSE;
            }
            if (*(f32 *) (obj + 0xA8) == 0.0f) {
                width = (f32) (game_gu_random() % 70) + 40.0f;
            } else {
                width = *(f32 *) (obj + 0xA8);
            }
            hitobj = 0;
            if (aim != 0xFF) {
                target = *(u8 **) (obj + 0xDC);
                aimrec = g_aim_records + aim * 0x1C;
                heading = *(u16 *) (target + 0x76) - *(s16 *) (*(u8 **) (target + 0x31C) + 0x12);
                if (heading == *(s16 *) aimrec && *(s8 *) (target + 0x1D1) == *(s8 *) (aimrec + 2)) {
                    *(f32 *) (obj + 0xB0) = *(f32 *) (aimrec + 4);
                    *(f32 *) (obj + 0xB4) = *(f32 *) (aimrec + 8);
                    *(f32 *) (obj + 0xB8) = *(f32 *) (aimrec + 0xC);
                    if (D_800BE616 == 0 && game_gu_random() % 100 < aimrec[3]) {
                        vec[0] = *(f32 *) (obj + 0xB0) - *(f32 *) (obj + 0x94);
                        vec[1] = *(f32 *) (obj + 0xB4) - *(f32 *) (obj + 0x98);
                        vec[2] = *(f32 *) (obj + 0xB8) - *(f32 *) (obj + 0x9C);
                        dir = (f32 *) (aimrec + 0x10);
                        d = vec3f_dot((u8 *) dir, (u8 *) vec);
                        vec3_scale((struct17 *) dir, d + d, (struct17 *) out);
                        vec3_sub((struct17 *) vec, (struct17 *) out, (struct17 *) out);
                        out[0] += *(f32 *) (obj + 0xB0);
                        out[1] += *(f32 *) (obj + 0xB4);
                        out[2] += *(f32 *) (obj + 0xB8);
                        beam_effect_spawn(0, *(f32 *) (obj + 0xB0), *(f32 *) (obj + 0xB4), *(f32 *) (obj + 0xB8), out[0],
                                      out[1], out[2], (f32) (game_gu_random() % 35) + 20.0f, 0.0f, 8.0f, 320.0f, 0x1E,
                                      0x23, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                        sound_play_at(game_gu_random() % 6 + 0x2B, 0x2710, 0, 0, aim, (s32) * (f32 *) (obj + 0xB0),
                                      (s32) * (f32 *) (obj + 0xB4), (s32) * (f32 *) (obj + 0xB8), 0x1F4, 0x7D0);
                    }
                    alpha = 1.0f;
                } else {
                    vec_from_yaw_pitch(heading, 2000.0f, (f32) (s16) (*(s8 *) (target + 0x1D1) * 200) * 0.0054931640625f,
                                  (f32 *) (obj + 0xB0), (f32 *) (obj + 0xB8), (f32 *) (obj + 0xB4));
                    *(f32 *) (obj + 0xB0) += *(f32 *) (obj + 0x94);
                    *(f32 *) (obj + 0xB4) += *(f32 *) (obj + 0x98);
                    *(f32 *) (obj + 0xB8) += *(f32 *) (obj + 0x9C);
                }
                *(f32 *) (obj + 0xC0) = (f32) (game_gu_random() % 3) * 80.0f + 80.0f;
            } else {
                if (ray) {
                    hit[0] = *(f32 *) (obj + 0xB0) - *(f32 *) (obj + 0x94);
                    hit[1] = *(f32 *) (obj + 0xB4) - *(f32 *) (obj + 0x98);
                    hit[2] = *(f32 *) (obj + 0xB8) - *(f32 *) (obj + 0x9C);
                    step = (75.0f * width) / sqrtf(hit[0] * hit[0] + hit[1] * hit[1] + hit[2] * hit[2]);
                    if (collision_ray_cast(*(f32 *) (obj + 0x94), *(f32 *) (obj + 0x98), *(f32 *) (obj + 0x9C), hit[0] * step,
                                      hit[1] * step, hit[2] * step, &rayhit, NULL, &hit[0], &hit[1], &hit[2], NULL, 0, 0,
                                      0.0f) != 0) {
                        *(f32 *) (obj + 0xB0) = hit[0];
                        *(f32 *) (obj + 0xB4) = hit[1];
                        *(f32 *) (obj + 0xB8) = hit[2];
                        alpha = 1.0f;
                        idx = (u32) (rayhit - D_800DC26C) / 12;
                        if (idx >= 0 && idx < D_800DBE4C && D_800DBE5C != 0) {
                            hitobj = floor_flags_surface_type(((s32 *) D_800DBE5C)[idx]);
                        }
                    }
                }
                tex = 0x43;
            }
            *(f32 *) (obj + 0xA4) = math_atan2f(-(*(f32 *) (obj + 0xB0) - *(f32 *) (obj + 0x94)),
                                                  -(*(f32 *) (obj + 0xB8) - *(f32 *) (obj + 0x9C)));
            dx = *(f32 *) (obj + 0xB0) - *(f32 *) (obj + 0x94);
            dz = *(f32 *) (obj + 0xB8) - *(f32 *) (obj + 0x9C);
            *(f32 *) (obj + 0xA0) = math_atan2f(*(f32 *) (obj + 0xB4) - *(f32 *) (obj + 0x98), sqrtf(dx * dx + dz * dz));
            *(f32 *) (obj + 0xC4) = 0.0f;
            *(f32 *) (obj + 0xC8) = 0.0f;
            *(f32 *) (obj + 0xCC) = 0.0f;
            if (ray) {
                beam_effect_spawn(0, *(f32 *) (obj + 0x94), *(f32 *) (obj + 0x98), *(f32 *) (obj + 0x9C),
                              *(f32 *) (obj + 0xB0), *(f32 *) (obj + 0xB4), *(f32 *) (obj + 0xB8), width, alpha, 15.0f,
                              820.0f, 0x4B, tex, 0, 0, 0, *(struct127 **) (obj + 0xDC), 0, 0, 0, hitobj, obj[0xFE],
                              0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            }
        }
    }
    if (*(s16 *) (obj + 0xD6) <= 0) {
        return;
    }
    c = fast_sinf(*(f32 *) (obj + 0xA0));
    s = fast_cosf(*(f32 *) (obj + 0xA0));
    // the direction: a vector turned by the pitch, then by the yaw. The asm really adds / multiplies its 0.0 terms
    // (0.0 + -0.0 = +0.0, s * 0.0 = -0.0 for s < 0); IDO folds `0.0f + x` to x, so the zero is read from the
    // volatile n[2] (setup mv_vz0: velocity -0.0 vs +0.0)
    n[2] = 0.0f;
    n[1] = n[2] - c * -1.0f;
    n[0] = n[2] + s * -1.0f;
    c = fast_sinf(*(f32 *) (obj + 0xA4));
    s = fast_cosf(*(f32 *) (obj + 0xA4));
    vx = s * n[2] + c * n[0];
    vy = n[1];
    vz = -c * n[2] + s * n[0];
    if (*(f32 *) (obj + 0xAC) != 0.0f) {
        dx = *(f32 *) (obj + 0xB0) - *(f32 *) (obj + 0x94);
        dy = *(f32 *) (obj + 0xB4) - *(f32 *) (obj + 0x98);
        dz = *(f32 *) (obj + 0xB8) - *(f32 *) (obj + 0x9C);
        dist0 = sqrtf(dx * dx + dy * dy + dz * dz);
    }
    if (obj[0xDB] == 0) {
        vx *= 0.5f;
        vy = n[1] * 0.5f;
        vz *= 0.5f;
    }
    *(f32 *) (obj + 0xC4) = vx;
    *(f32 *) (obj + 0xCC) = vz;
    *(f32 *) (obj + 0xC8) = vy;
    step = *(f32 *) (obj + 0xA8) * (f32) g_frame_ticks;
    if (dist0 < step && *(f32 *) (obj + 0xAC) != 0.0f) {
        vx *= dist0;
        *(f32 *) (obj + 0xC0) = dist0;
        vy *= dist0;
        vz *= dist0;
    } else {
        vx *= step;
        vy *= step;
        vz *= step;
    }
    if (obj[0xFE] == 1) {
        target = *(u8 **) (obj + 0xDC);
        object_ray_hit_nearest((struct127 *) target, *(f32 *) (obj + 0x94), *(f32 *) (obj + 0x98), *(f32 *) (obj + 0x9C),
                      *(f32 *) (obj + 0x94) + vx, *(f32 *) (obj + 0x98) + vy, *(f32 *) (obj + 0x9C) + vz,
                      target != NULL ? (target - (u8 *) g_objects) / 0x32C : 0, 0);
    }
    *(f32 *) (obj + 0x94) += vx;
    *(f32 *) (obj + 0x98) += vy;
    *(f32 *) (obj + 0x9C) += vz;
    limit = *(f32 *) (obj + 0xAC);
    if (limit == 0.0f) {
        return;
    }
    endX = *(f32 *) (obj + 0xB0);
    dx = endX - *(f32 *) (obj + 0x94);
    dy = *(f32 *) (obj + 0xB4) - *(f32 *) (obj + 0x98);
    dz = *(f32 *) (obj + 0xB8) - *(f32 *) (obj + 0x9C);
    d = sqrtf(dx * dx + dy * dy + dz * dz);
    if (d < limit || dist0 < d) {
        if (obj[0xFC] != 0) {
            impact_effect_spawn(endX, *(f32 *) (obj + 0xB4), *(f32 *) (obj + 0xB8), 1, obj[0xFC], 0, 0xFF);
        }
        node_destroy((struct102 *) obj);
        return;
    }
    if (d < *(f32 *) (obj + 0xC0)) {
        *(f32 *) (obj + 0xC0) = d;
    }
}

extern s32 g_gfx_tlut_mode; /* was D_800D30BC */
Gfx *sprite_load_texture(Gfx *gfx, u8 *header, s32 tmem, void *spr, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8);
Gfx *gfx_other_mode_cached(Gfx *, s32, s32, u8 *);

// beam_effect_draw: draw handler of the beam objects of beam_effect_spawn (Gfx *(Gfx *, u8 *obj, s16 viewer)). With a
// texture (+0xD6 > 0) the beam from +0x94 along the direction +0xC4 times the length +0xC0 is drawn as one quad
// facing character `viewer` (g_player_views entry, position +0x2F8): at each end the offset cross(end - eye, dir) scaled
// to the half width +0xBC gives the two corners end +- offset (far end first). The corners go to this frame's 4
// vertices (obj + 0x10 + g_dl_buf_index * 0x40, s16 x / y / z), then texture g_sprite_tex_descs[+0xD8] is loaded
// (sprite_load_texture; its sprite-parameter pointer is an unset local, as in the asm), the render mode is set
// (gfx_other_mode_cached) and gSPVertex + 2 triangles are emitted; +0xDB = 1. Returns gfx unchanged without setting +0xDB
// when an end lies on the eye line (zero offset). The asm also computes the squared eye distances of both ends and
// an unused first offset; neither is read.
/* was func_150E2E5C */
Gfx *beam_effect_draw(Gfx *gfx, u8 *obj, s16 viewer) {
    f32 ends[2][3];
    f32 verts[4][3];
    u8 spr[0x10];
    u8 flag;
    f32 *eye;
    f32 *dir;
    f32 *p;
    f32 e[3];
    f32 n[3];
    f32 len;
    f32 s;
    s32 i;
    s32 j;
    u32 *cmd;

    if (*(s16 *) (obj + 0xD6) <= 0) {
        obj[0xDB] = 1;
        return gfx;
    }
    dir = (f32 *) (obj + 0xC4);
    /* far end first */
    ends[0][0] = *(f32 *) (obj + 0x94) + *(f32 *) (obj + 0xC0) * dir[0];
    ends[0][1] = *(f32 *) (obj + 0x98) + *(f32 *) (obj + 0xC0) * dir[1];
    ends[0][2] = *(f32 *) (obj + 0x9C) + *(f32 *) (obj + 0xC0) * dir[2];
    ends[1][0] = *(f32 *) (obj + 0x94);
    ends[1][1] = *(f32 *) (obj + 0x98);
    ends[1][2] = *(f32 *) (obj + 0x9C);
    eye = (f32 *) ((u8 *) g_player_views + viewer * 0x9A0 + 0x2F8);
    for (i = 0; i < 2; i++) {
        p = ends[i];
        e[0] = p[0] - eye[0];
        e[1] = p[1] - eye[1];
        e[2] = p[2] - eye[2];
        n[0] = e[1] * dir[2] - e[2] * dir[1];
        n[1] = e[2] * dir[0] - e[0] * dir[2];
        n[2] = e[0] * dir[1] - e[1] * dir[0];
        len = sqrtf(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
        if (len == 0.0f) {
            return gfx;
        }
        s = *(f32 *) (obj + 0xBC) / len;
        n[0] *= s;
        n[1] *= s;
        n[2] *= s;
        verts[i * 2][0] = n[0] + p[0];
        verts[i * 2][1] = n[1] + p[1];
        verts[i * 2][2] = n[2] + p[2];
        verts[i * 2 + 1][0] = p[0] - n[0];
        verts[i * 2 + 1][1] = p[1] - n[1];
        verts[i * 2 + 1][2] = p[2] - n[2];
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            *(s16 *) (obj + g_dl_buf_index * 0x40 + i * 0x10 + 0x10 + j * 2) = (s32) verts[i][j];
        }
    }
    gfx = sprite_load_texture(gfx, g_sprite_tex_descs[*(s16 *) (obj + 0xD8)], 0, spr, 0, 0, 0, 2, 3);
    flag = 0;
    gfx = gfx_other_mode_cached(gfx, g_gfx_tlut_mode | 0x82CA0, 0x504A50, &flag);
    cmd = (u32 *) gfx;
    cmd[0] = 0x01004008; /* gSPVertex(this frame's 4 vertices) */
    cmd[1] = (u32) (obj + g_dl_buf_index * 0x40 + 0x10);
    cmd[2] = 0x05000206; /* triangle 0 1 3 */
    cmd[3] = 0;
    cmd[4] = 0x05000604; /* triangle 0 3 2 */
    cmd[5] = 0;
    obj[0xDB] = 1;
    return gfx + 3;
}

/* was func_150E3324 */
s32 beam_effect_stub(s32 arg0, s32 arg1) {
    return arg0;
}

/* was func_150E3334 */
void beam_effect_spawn_attached(s32 arg0, u8 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, s16 argA, s16 argB, u16 argC, u8 argD) {
    beam_effect_spawn(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 400.0f, (s32) argC, 0x27, 1, (s32) argA, (s32) argB, (struct127 *)arg0, (s32) arg1, (s32) arg2, arg3, 0, (s32) argD, arg4, arg5, arg6, arg7, arg8, arg9);
}

/* was func_150E2EA4 */
void beam_effect_spawn_attached_ex(struct127 *arg0, u8 arg1, s16 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, s16 argA, s16 argB, u16 argC, f32 argD, f32 argE, u8 argF, f32 arg10) {
    beam_effect_spawn(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, arg10, 0.0f, argD, argE, (s32) argC, 0x27, 1, (s32) argA, (s32) argB, arg0, (s32) arg1, (s32) arg2, arg3, 0, (s32) argF, arg4, arg5, arg6, arg7, arg8, arg9);
}

/* was func_150E3510 */
void beam_effect_handler_stub(s32 arg0, s32 arg1, s16 arg2) {
    beam_effect_stub(arg0, arg2);
}

/* was func_150E3540 */
void beam_effect_on_target_swap(u8 *arg0, s32 *arg1, u8 arg2) {
    if (arg2 == 0x2D) {
        if (arg1[0] == *(s32 *)(arg0 + 0xDC)) {
            *(s32 *)(arg0 + 0xDC) = arg1[1];
            arg0[0xDA] = ((u8 *)arg1)[9];
            return;
        }
        if (arg1[1] == *(s32 *)(arg0 + 0xDC)) {
            *(s32 *)(arg0 + 0xDC) = arg1[0];
            arg0[0xDA] = ((u8 *)arg1)[8];
        }
    }
}
