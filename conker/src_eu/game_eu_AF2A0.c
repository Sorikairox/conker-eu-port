#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern s32 D_8008704C;
void look_record_alloc(u8 *arg0);
struct197 *allocate_memory(s32, s32, s32, s32);
void obj_reset(struct127 *);
struct127 *obj_alloc_slot(void);
void obj_load_part_models(u8 *, s32, s32);
s32 mp_player_team(s32);
void obj_copy_type_params(u8 *, u16, u8 *);
void obj_set_type(s32, s32, s32);
s32 obj_anim_state_alloc(struct127 *, u16, s32, f32);
s32 model_make_ready(struct127 *, s32, s32, s32);
void obj_apply_setup_variant(struct127 *, s32);
s32 level_list_index_of(s32);
s32 char_fx_init(struct127 *);
void obj_randomize_anim_frame(u8 *);
extern s8 D_8008FD8C;
extern u8 *g_setup_entry_flags; /* was D_800D252C */
extern s8 D_800901E4[];
extern s8 D_800D2550;
extern u16 D_800D2132;
extern u8 D_800C67F0;
extern u8 D_80038080;
extern u8 D_800A7610[];
extern u8 D_800A7620[];
u8 obj_type_model_group(u8 *arg0);
u8 *asset_lookup_rom(s32 *arg0, s32 arg1, ...);
s32 obj_spawn_attached(struct127 *, u8, u8, s32, s32, s32, s32, s32, f32);
struct127 *attachment_create(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 *arg9, s32 argA, s32 argB, s32 argC);
extern s32 D_80087064;

typedef struct {
    /* 0x000 */ u8 pad0[0x1C9];
    /* 0x1C9 */ u8 unk1C9;
    /* 0x1CA */ u8 pad1CA[0xFA];
    /* 0x2C4 */ u8 *unk2C4;
    /* 0x2C8 */ u8 unk2C8;
} struct_eu_AF2A0;


/* P146 */
extern s32 (*D_80087030[])(u8 *, s32, s32);
s32 obj_ray_hit_model(u8 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, s32 *, s32 *, s32 *, s16 *);
s32 ray_hit_object_bounds(f32 *, f32 *, u8 *, f32 *, f32 *, f32 *, f32 *);
s32 collision_ray_cast(f32, f32, f32, f32, f32, f32, s32 *, u8 *, f32 *, f32 *, f32 *, f32 *, s32 *, u8 *, f32);
// ray_cast_world: casts the ray (x, y, z) + t * (dx, dy, dz) against the level (unless noLevel) and the 25 objects
// of g_objects (unless noObjects) and keeps the nearest hit closer than maxDist (0 = 9999999) in hit:
// +0 object, +4 distance (-1 = none), +0x8 point, +0x14 normal (model hits), +0x20 exit point, +0x2C start,
// +0x38 direction, +0x44 level surface, +0x56 / +0x58 / +0x5A model hit data, +0x59 kind (0 none, 1 level,
// 2 object bounds, 3 object model), +0x5C level material (D_800DBEF4 entry), +0x60 level hit extra. Objects are
// skipped when in skipMask, the caster's own slot (+0x124 - 1) or the caster itself, inactive, of type 3
// (+0x5), not hittable (+0xF8 bit 0x40), or rejected by filter D_80087030[filter](obj, caster, filterArg)
// (-1 = none). Without boundsOnly the object model is tested (obj_ray_hit_model) and its bounds only when that
// returns -1; an object linked (+0x65) to the previous model hit is not taken again. The original returns
// nothing (callers ignore the value); 0 here.
/* was func_15081A90 */
s32 ray_cast_world(struct127 *caster, f32 x, f32 y, f32 z, f32 dx, f32 dy, f32 dz, u8 *hit, f32 maxDist, s32 noLevel,
                  s32 noObjects, s32 boundsOnly, s32 filter, s32 filterArg, s32 skipMask) {
    f32 start[3];
    f32 dir[3];
    u8 link[0x19];
    f32 point[3];
    f32 exitPoint[3];
    f32 normal[3];
    f32 dist;
    f32 dist2;
    f32 hx;
    f32 hy;
    f32 hz;
    s32 surface;
    s32 material;
    s32 modelA;
    s32 modelB;
    s32 modelC;
    s16 modelD[4];
    s32 own;
    s32 last;
    s32 res;
    s32 i;
    u8 *obj;

    start[0] = x;
    start[1] = y;
    start[2] = z;
    dir[0] = dx;
    dir[1] = dy;
    dir[2] = dz;
    *(f32 *)(hit + 0x4) = -1.0f;
    *(u8 **)(hit + 0x0) = NULL;
    hit[0x59] = 0;
    *(f32 *)(hit + 0x2C) = start[0];
    *(f32 *)(hit + 0x30) = start[1];
    *(f32 *)(hit + 0x34) = start[2];
    *(f32 *)(hit + 0x38) = dir[0];
    *(f32 *)(hit + 0x3C) = dir[1];
    *(u8 **)(hit + 0x5C) = NULL;
    *(s32 *)(hit + 0x60) = 0;
    *(f32 *)(hit + 0x40) = dir[2];
    last = -1;
    if (maxDist == 0.0f) {
        maxDist = 9999999.0f;
    }
    if (caster != NULL) {
        own = ((u8 *)caster)[0x124] - 1;
    } else {
        own = -1;
    }
    bzero(link, sizeof(link));
    for (i = 0; i < 25; i++) {
        obj = (u8 *)&g_objects[0] + i * 0x32C;
        if (*(s32 *)obj != 0 && obj[0x65] != 0) {
            link[obj[0x65] - 1] = i + 1;
        }
    }

    if (noLevel == 0 &&
        collision_ray_cast(x, y, z, dx, dy, dz, &surface, hit + 0x44, &hx, &hy, &hz, &dist, &material, hit + 0x60, 0.0f) !=
            0 &&
        dist < maxDist) {
        *(f32 *)(hit + 0x4) = dist;
        hit[0x59] = 1;
        *(f32 *)(hit + 0x8) = hx;
        *(f32 *)(hit + 0xC) = hy;
        *(f32 *)(hit + 0x20) = *(f32 *)(hit + 0x8);
        *(f32 *)(hit + 0x10) = hz;
        *(f32 *)(hit + 0x24) = *(f32 *)(hit + 0xC);
        *(f32 *)(hit + 0x28) = *(f32 *)(hit + 0x10);
        if (material != -1) {
            *(u8 **)(hit + 0x5C) = (u8 *)D_800DBEF4 + material * 0xA0;
        } else {
            *(u8 **)(hit + 0x5C) = NULL;
        }
    }

    if (noObjects != 0) {
        return 0;
    }
    for (i = 0; i < 25; i++) {
        if ((1 << i) & skipMask) {
            continue;
        }
        if (own == i) {
            continue;
        }
        obj = (u8 *)&g_objects[0] + i * 0x32C;
        if (*(s32 *)obj == 0 || obj[0x5] == 3 || obj == (u8 *)caster || !(*(s32 *)(obj + 0xF8) & 0x40)) {
            continue;
        }
        if ((s8)filter != -1 && D_80087030[(s8)filter](obj, (s32)caster, filterArg) == 0) {
            continue;
        }
        if (boundsOnly == 0) {
            res = obj_ray_hit_model(obj, start, dir, point, exitPoint, normal, &dist, &modelA, &modelB, &modelC, modelD);
            if (res > 0 && dist < maxDist &&
                (*(f32 *)(hit + 0x4) == -1.0f || dist < *(f32 *)(hit + 0x4)) && last != link[i]) {
                *(f32 *)(hit + 0x4) = dist;
                *(u8 **)(hit + 0x0) = obj;
                last = i + 1;
                hit[0x58] = modelC;
                *(s16 *)(hit + 0x56) = modelB;
                *(f32 *)(hit + 0x8) = point[0];
                *(f32 *)(hit + 0xC) = point[1];
                *(f32 *)(hit + 0x10) = point[2];
                *(f32 *)(hit + 0x14) = normal[0];
                *(f32 *)(hit + 0x18) = normal[1];
                *(f32 *)(hit + 0x1C) = normal[2];
                hit[0x5A] = modelA;
                *(f32 *)(hit + 0x20) = exitPoint[0];
                *(f32 *)(hit + 0x24) = exitPoint[1];
                hit[0x59] = 3;
                *(f32 *)(hit + 0x28) = exitPoint[2];
            }
            if (res != -1) {
                continue;
            }
        }
        if (ray_hit_object_bounds(start, dir, obj, point, exitPoint, &dist, &dist2) != 0 && dist < maxDist &&
            (*(f32 *)(hit + 0x4) == -1.0f || dist < *(f32 *)(hit + 0x4)) && last != link[i]) {
            *(f32 *)(hit + 0x4) = dist;
            *(u8 **)(hit + 0x0) = obj;
            last = i + 1;
            *(f32 *)(hit + 0x8) = point[0];
            *(f32 *)(hit + 0xC) = point[1];
            *(f32 *)(hit + 0x10) = point[2];
            *(f32 *)(hit + 0x20) = exitPoint[0];
            *(f32 *)(hit + 0x24) = exitPoint[1];
            hit[0x59] = 2;
            *(f32 *)(hit + 0x28) = exitPoint[2];
        }
    }
    return 0;
}

/* P146 */
s32 vec3_normalize_len(f32 *, f32 *, f32 *, f32 *);
f32 vec3_length(f32 *);
// ray_hit_object_bounds: intersects the ray start + t * dir with an object's bounding sphere, squashed vertically:
// centre = the object position (+0x14) raised by +0xD6, radius +0xD2, y scaled by +0xDC into sphere space and by
// +0xE0 back. Returns 0 for a zero-length direction or a miss; on a hit stores the entry / exit points (hitIn,
// hitOut) and their distances from start (distIn, distOut) and returns 1.
/* was func_15082020 */
s32 ray_hit_object_bounds(f32 *start, f32 *dir, u8 *obj, f32 *hitIn, f32 *hitOut, f32 *distIn, f32 *distOut) {
    f32 center[3];
    f32 p[3];
    f32 d[3];
    f32 c[3];
    f32 rel[3];
    f32 ys;
    f32 yback;

    center[0] = *(f32 *)(obj + 0x14);
    center[1] = *(f32 *)(obj + 0x18) + *(s16 *)(obj + 0xD6);
    center[2] = *(f32 *)(obj + 0x1C);
    yback = *(f32 *)(obj + 0xE0);
    ys = *(f32 *)(obj + 0xDC);
    p[0] = start[0];
    p[1] = start[1] * ys;
    p[2] = start[2];
    d[0] = dir[0];
    d[1] = dir[1] * ys;
    d[2] = dir[2];
    if (vec3_normalize_len(d, d, NULL, NULL) == 0) {
        return 0;
    }
    c[0] = center[0];
    c[1] = center[1] * ys;
    c[2] = center[2];
    if (ray_sphere_intersect((struct17 *)p, (struct17 *)d, (struct17 *)c, *(s16 *)(obj + 0xD2), (s32)hitIn, (s32)hitOut, distIn,
                      distOut) == 0) {
        return 0;
    }
    hitIn[1] *= yback;
    hitOut[1] *= yback;
    rel[0] = hitIn[0] - start[0];
    rel[1] = hitIn[1] - start[1];
    rel[2] = hitIn[2] - start[2];
    *distIn = vec3_length(rel);
    rel[0] = hitOut[0] - start[0];
    rel[1] = hitOut[1] - start[1];
    rel[2] = hitOut[2] - start[2];
    *distOut = vec3_length(rel);
    return 1;
}

void obj_set_hit_flags_by_kind(u8 *, s32, u8);
/* was func_1508220C */
void obj_apply_hit_flags(u8 *arg0, u16 v, u8 arg2) {
    if (D_800BE616 == 0) {
        if (arg0[0x1CA] != 0) {
            arg0[0x1CA] = 7;
        }
        if (arg2 == 0 || v != 10) {
            obj_set_hit_flags_by_kind(arg0, v, arg2);
        }
    }
}

s32 target_volume_hit_check(u8 *arg0, f32 *arg1, s32 arg2);
void bullet_impact_effect(f32 *normal, f32 *pos, f32 *dir, s32 arg3, s32 arg4);
void stub_hit_point_noop(f32 arg0, f32 arg1, s32 arg2, s32 arg3);
void zap_burst_spawn(u8 *arg0, u8 arg1, s32 arg2);
void screen_flash_zap(u8 arg0, s32 arg1);
void impact_burst_effect(u8 *arg0, u8 arg1, s32 arg2);
extern u8 D_80099E84[];   /* per weapon kind: the hit-effect id passed to obj_send_hit */
extern f32 D_8009CFF8;    /* 65536 / 360 */
/* the hit record a ray cast fills (ray_cast_world); only the fields used here */
typedef struct {
    u8 *target;          /* 0x00: the object hit */
    f32 dist;            /* 0x04 */
    f32 pos[3];          /* 0x08 */
    f32 floorY;          /* 0x14: unused here */
    f32 f18;             /* 0x18 */
    f32 u1C;
    f32 v20[3];          /* 0x20 */
    f32 u2C[3];
    f32 dir[3];          /* 0x38 */
    f32 normal[3];       /* 0x44 */
    u8 pad50[6];
    u16 part;            /* 0x56: the body part hit */
    u8 sub;              /* 0x58: hit detail (10 = head?) */
    u8 type;             /* 0x59: 0 nothing, 1 world, 2 / 3 objects */
    u8 u5A;              /* 0x5A */
} Hit15082278;
/* the stack block attachment_spawn_at_joint gets (only the fields set here; the rest is stack garbage on N64 too) */
typedef struct {
    u8 pad0[0x14];
    f32 pos[3];          /* 0x14 */
    u8 pad20[0x40 - 0x20];
    f32 yaw;             /* 0x40: hit direction + 180 */
    u8 pad44[0xB8 - 0x44];
    f32 pitch;           /* 0xB8 */
    u8 padBC[0xC4 - 0xBC];
    f32 uC4;             /* 0xC4 */
    u8 padC8[0x14C - 0xC8];
    f32 u14C[2];         /* 0x14C: copied from the target */
    u8 pad154[0x32C - 0x154];
} Reaction15082278;

// shot_hit_apply: P194. Applies a weapon ray hit `h` (filled by ray_cast_world) of shooter obj with weapon kind `kind`;
// counts the shot in the shooter's controller (+0x31C, +0x1AA). Returns 0 when nothing was hit. World hits (type 1):
// per-kind impact effect bullet_impact_effects (kind 2: 1, 6: 0, 7: 5, 11: 3, 12: 2, 18: 4, others 5); kind 13 a decal
// bullet_impact_effect instead, kinds 5 / 9 / 10 a ricochet (stub_hit_point_noop, an empty function, and obj_effect_run_handler(obj, 2)),
// with on level 0xE kind 5 also the probe target_volume_hit_check 5 units around the point; returns 1.
// Object hits (types 2 / 3, target h->target): kinds 5 / 9 / 10 call obj_effect_run_handler(obj, 3); a target that is
// invulnerable (+0x125 / +0x104) and already reacting (+0x1CA) is skipped (return 2). Type 2: target type 0x94 gets
// zap_burst_spawn / screen_flash_zap and no blood (object_impact_effects). Type 3: with sub 10 (head shot) and no earlier head shot
// (controller +0x1AD) the target dies (obj_set_dying_flags, its sounds 0x2E3.. / object_hit_effect / sound 0xAA, effect 0x20 /
// 0x3D) or, for kinds 2 / 11 / 12 / 18, only plays sound 0x107; targets 0x9F / 0xA0 (unless D_800BE616) farther than
// 1000 call obj_apply_hit_flags instead. Kinds 2 / 18 / 12 / 11 start the reaction attachment_spawn_at_joint (0x2A / 0x22 / 0x6B / 0x6D)
// while +0x1CA < 2. Then the blood / sparks object_impact_effects, kind 13 impact_burst_effect, and when the target was already
// reacting, obj_send_hit(target, effect | 0x80000, (direction - 90) as a u16 angle, shooter player index). Returns 2.
/* was func_15082278 */
s32 shot_hit_apply(u8 *obj, u8 *hit, s32 kind) {
    Hit15082278 *h = (Hit15082278 *) hit;
    Reaction15082278 r;
    u8 *target;
    u8 *ctrl;
    f32 yaw, pitch;
    f32 a[3], b[3];
    s32 probe;
    s32 fresh;
    s32 effect;
    s32 far;
    s32 reaction;
    s32 blood = TRUE;
    f32 f;
    u32 angle;

    if (*(u8 **) (obj + 0x31C) != NULL) {
        (*(s16 *) (*(u8 **) (obj + 0x31C) + 0x1AA))++;
    }
    if (h->type == 0) {
        return 0;
    }
    if (h->type == 1) {
        switch (kind) {
            case 18: effect = 4; break;
            case 6: effect = 0; break;
            case 2: effect = 1; break;
            case 7: effect = 5; break;
            case 11: effect = 3; break;
            case 12: effect = 2; break;
            case 13:
                effect = -1;
                bullet_impact_effect(h->normal, h->pos, h->dir, 0xFF, 1);
                break;
            case 5:
                if (g_level_id == 0xE) {
                    a[0] = h->pos[0] + h->dir[0] * 5.0f;
                    a[1] = h->pos[1] + h->dir[1] * 5.0f;
                    a[2] = h->pos[2] + h->dir[2] * 5.0f;
                    b[0] = h->pos[0] - h->dir[0] * 5.0f;
                    b[1] = h->pos[1] - h->dir[1] * 5.0f;
                    b[2] = h->pos[2] - h->dir[2] * 5.0f;
                    target_volume_hit_check((u8 *) a, b, (s32) &probe);
                }
                /* fallthrough */
            case 9:
            case 10:
                effect = -1;
                stub_hit_point_noop(h->pos[0], h->pos[1], *(s32 *) &h->pos[2], obj[0x124]);
                obj_effect_run_handler((struct127 *) obj, 2, NULL);
                break;
            default:
                effect = 5;
                break;
        }
        if (effect != -1) {
            bullet_impact_effects(h->pos, h->dir, (s32) h->normal, effect & 0xFF, 0xFF, 1);
        }
        return 1;
    }

    target = h->target;
    if (kind == 5 || kind == 9 || kind == 10) {
        obj_effect_run_handler((struct127 *) obj, 3, NULL);
    }
    fresh = (target[0x1CA] == 0);
    if ((target[0x125] != 0 || target[0x104] != 0) && !fresh) {
        return 2;
    }
    effect = D_80099E84[kind];
    if (kind == 7 && g_level_id == 0x2B) {
        effect = 0x27;
    }
    vec3_to_yaw_pitch_deg(h->dir, &yaw, &pitch);
    if (h->type == 2) {
        if (target[4] == 0x94) {
            blood = FALSE;
            zap_burst_spawn(h->pos, 0xFF, 1);
            screen_flash_zap(0xFF, 1);
        }
    } else if (h->type == 3) {
        far = FALSE;
        if (D_800BE616 == 0 && (target[4] == 0x9F || target[4] == 0xA0) && 1000.0f < h->dist) {
            far = TRUE;
        }
        ctrl = *(u8 **) (target + 0x31C);
        if (h->sub == 10 && (ctrl == NULL || ctrl[0x1AD] == 0) && !far) {
            if (kind == 2 || kind == 18 || kind == 11 || kind == 12) {
                obj_sfx_play(0x107, (struct127 *) target);
            } else {
                obj_set_dying_flags((struct127 *) target);
                if (*(u8 **) (target + 0x31C) != NULL) {
                    (*(u8 **) (target + 0x31C))[0x1AD] = 1;
                }
                if (target[4] == 0x80 && h->u5A == 0 && h->f18 < h->pos[1] - 5.5f) {
                    obj_sfx_play_alt((random_int() & 7) + 0x2E3, (struct127 *) target);
                }
                object_hit_effect((struct127 *) target, 0xFF, 1);
                effect = 0x20;
                if ((target[4] == 0x9F || target[4] == 0xA0) && *(s32 *) (target + 0x2EC) != 0) {
                    effect = 0x3D;
                }
                obj_sfx_play(0xAA, (struct127 *) target);
            }
            if (kind != 11 && kind != 12 && target[0x1CA] != 0) {
                target[0x1CA] = 1;
            }
        } else if (target[4] == 0x9F || target[4] == 0xA0) {
            obj_apply_hit_flags(target, h->sub, far);
        }
        switch (kind) {
            case 2: reaction = 0x2A; break;
            case 11: reaction = 0x6D; break;
            case 12: reaction = 0x6B; break;
            case 18: reaction = 0x22; break;
            default: reaction = 0; break;
        }
        if (reaction != 0 && target[0x1CA] < 2) {
            r.pos[0] = h->pos[0];
            r.pos[1] = h->pos[1];
            r.yaw = yaw + 180.0f;
            r.pitch = pitch;
            r.pos[2] = h->pos[2];
            r.uC4 = 0.0f;
            r.u14C[0] = *(f32 *) (target + 0x14C);
            r.u14C[1] = *(f32 *) (target + 0x150);
            attachment_spawn_at_joint((u8 *) &r, target, reaction, h->part, 1, 0);
            if (h->sub == 10) {
                effect = 0x20;
            }
        }
    }
    if (blood) {
        object_impact_effects(h->target, h->pos, h->v20, h->dir, 0xFF, 1);
    }
    if (kind == 13) {
        impact_burst_effect((u8 *) h->pos, 0xFF, 1);
    }
    if (!fresh) {
        /* (u32) of the angle the IDO way: truncation, values >= 2^31 through the -2^31 retry, negatives -> -1 */
        f = (yaw - 90.0f) * D_8009CFF8;
        if (f >= 2147483648.0f) {
            f -= 2147483648.0f;
            angle = (f >= 2147483648.0f) ? 0xFFFFFFFF : ((u32) (s32) f | 0x80000000);
        } else if (f > -1.0f) {
            angle = (s32) f;
        } else {
            angle = 0xFFFFFFFF;
        }
        obj_send_hit((struct127 *) target, effect | 0x80000, angle & 0xFFFF,
                      (obj - (u8 *) g_objects) / 0x32C);
    }
    return 2;
}

s32 setup_entry_spawn(u8 *e, s32 idx, s32 arg2, s32 arg3, s32 reuse);
s32 camera_view_test_sphere(s32, s32 *, f32, f32, f32, f32, f32, f32);
extern s32 D_800DA030[];

/* P36: level-setup entry idx (0x30 bytes at D_800D20FC): spawn it with setup_entry_spawn(e, idx, 0, 0, 0) and return
 * that, or return 0 when: already spawned (g_setup_entry_flags[idx] != 0); a placeholder (e[2] == 1); no position
 * (x == 0x7FFF); its respawn timer D_800D2530[idx] is running (lowered by D_800BE9A0 this frame); idx >= 5 with a
 * range class e[1] & 6 (2: 650, 4: 1300, else 2750 units) and no player object g_objects[0 .. D_8008FD8C)
 * (+0 != 0, +0x127 != 0xFF and enabled in the u16 mask at g_session_game_mode + 0x208) within that XZ distance; or
 * e[1] & 8 and the spot (x, y + 150, z), radius 150, is in view of one of the cameras 0 .. D_80082FA0
 * (camera_view_test_sphere on D_800BE628 + i * 0x180, D_800DA030 + i * 0x10). Player slots (idx < 5) skip the range test.
 * arg1 is unused. */
/* was func_150829C0 */
s32 setup_entry_try_spawn(s32 idx, s32 arg1) {
    u8 *e;
    u16 *timer;
    u8 *obj;
    u8 *end;
    s32 x, flags, cls, n, ok, i, b;
    f32 r2, dx, dz;

    if (g_setup_entry_flags[idx] != 0) {
        return 0;
    }
    e = (u8 *) D_800D20FC + idx * 0x30;
    if (e[2] == 1) {
        return 0;
    }
    x = *(s16 *) (e + 6);
    if (x == 0x7FFF) {
        return 0;
    }
    timer = (u16 *) D_800D2530 + idx;
    if (*timer != 0) {
        if (D_800BE9A0 < *timer) {
            *timer = *timer - D_800BE9A0;
        } else {
            *timer = 0;
        }
        return 0;
    }
    flags = e[1];
    if (idx >= 5 && (cls = flags & 6) != 0) {
        if (cls == 2) {
            r2 = 422500.0f;
        } else if (cls == 4) {
            r2 = 1690000.0f;
        } else {
            r2 = 7562500.0f;
        }
        n = D_8008FD8C;
        ok = 1;
        if (n > 0) {
            obj = (u8 *) g_objects;
            end = (u8 *) g_objects + n * 0x32C;
            do {
                if (*(s32 *) obj != 0) {
                    b = obj[0x127];
                    if (b != 0xFF && ((1 << b) & *(u16 *) ((u8 *) &g_session_game_mode + 0x208))) {
                        dx = *(f32 *) (obj + 0x14) - (f32) x;
                        dz = *(f32 *) (obj + 0x1C) - (f32) *(s16 *) (e + 0xA);
                        if (dx * dx + dz * dz <= r2) {
                            ok = 0;
                            break;
                        }
                    }
                }
                obj += 0x32C;
            } while ((u32) obj < (u32) end);
        }
        if (ok) {
            return 0;
        }
    }
    if (flags & 8) {
        ok = 1;
        for (i = 0; i <= D_80082FA0; i++) {
            e = (u8 *) D_800D20FC + idx * 0x30;
            if (camera_view_test_sphere(D_800BE628 + i * 0x180, D_800DA030 + i * 0x10, (f32) *(s16 *) (e + 6),
                              (f32) (*(s16 *) (e + 8) + 150), (f32) *(s16 *) (e + 0xA), 150.0f, 150.0f, 20000.0f) != 0) {
                ok = 0;
            }
        }
        if (!ok) {
            return 0;
        }
    }
    return setup_entry_spawn((u8 *) D_800D20FC + idx * 0x30, idx, 0, 0, 0);
}

s32 setup_entry_try_spawn(s32, s32);
extern u8 D_800D2520;
extern u8 D_800D2521;
/* was func_15082D5C */
void setup_entries_spawn_range(s32 arg0, s32 arg1, s32 arg2) {
    s32 lo;
    s32 hi;
    s32 i;
    if (arg2 != 0) {
        lo = 0;
        hi = D_800D2521;
    } else {
        lo = D_800D2521;
        hi = D_800D2520;
    }
    i = lo;
    if (lo < hi) {
        do {
            setup_entry_try_spawn(i, arg1);
            i += 1;
        } while (i != hi);
    }
}

/* was func_15082DD8 */
void obj_set_spawn_flags(u8 *arg0) {
    u8 *temp_v0;

    *(s32 *)(arg0 + 0xF8) &= 0xF7FFFFFD;
    temp_v0 = *(u8 **)(arg0 + 0x31C);
    *(s32 *)(arg0 + 0xF8) |= 4;
    if ((temp_v0 != NULL) && (temp_v0[0x56] == 0)) {
        switch (g_level_id) {
        case 0x0:
        case 0xA:
        case 0xE:
        case 0x12:
        case 0x13:
        case 0x19:
        case 0x1B:
        case 0x2C:
        case 0x3C:
        case 0x3D:
        case 0x42:
        case 0x43:
        case 0x44:
            break;
        default:
            *(s32 *)(arg0 + 0xF8) |= 2;
            break;
        }
    }
}

/* Spawns the level-setup object e (0x30-byte entry of D_800D20FC) into an object slot of g_objects (0x32C each):
 * slot = reuse+reset (obj_reset) of slot reuse - 1 when reuse != 0, of slot idx when idx < D_8008FD8C (the
 * player / character slots), else a new one (obj_alloc_slot). Returns slot + 1, or 0 when g_setup_entry_flags[idx] & 0x7F
 * (already spawned) or no slot is free (25). Fills position (+0x14.., from e+6/8/A), angle (e+0xC << 8), the setup
 * flags e+0x18 (+0xF8), model / type (e+4) via obj_copy_type_params / obj_set_type / obj_anim_state_alloc, the player record
 * (+0x31C, 0x1C0 bytes) for character slots and types 0x98 / 0x28, and the other per-type defaults. */
#define O8(o) (*(u8 *)(obj + (o)))
#define O16(o) (*(s16 *)(obj + (o)))
#define O32(o) (*(s32 *)(obj + (o)))
#define OF(o) (*(f32 *)(obj + (o)))
#define REC(o) (*(u8 *)(*(u8 **)(obj + 0x31C) + (o)))
/* was func_15082E44 */
s32 setup_entry_spawn(u8 *e, s32 idx, s32 arg2, s32 arg3, s32 reuse) {
    u8 *obj;
    s32 type;
    s32 slot;
    s32 flags;
    s32 v;
    s32 n;
    s32 i;
    u8 *p;
    u8 *t;
    s32 found;
    void obj_alloc_light_bufs();
    u8 obj_current_part_model(struct_eu_AF2A0 *);

    if (g_setup_entry_flags[idx] & ~0x80) {
        return 0;
    }
    type = e[4];
    if (reuse != 0) {
        obj = (u8 *)g_objects + reuse * 0x32C - 0x32C;
        obj_reset((struct127 *)obj);
    } else if (idx != -1 && idx < D_8008FD8C) {
        obj = (u8 *)g_objects + idx * 0x32C;
        obj_reset((struct127 *)obj);
    } else {
        obj = (u8 *)obj_alloc_slot();
    }
    slot = (s32)(obj - (u8 *)g_objects) / 0x32C;
    if (slot == 0x19) {
        return 0;
    }
    if (idx != -1) {
        if (*(u16 *)e & 0x21) {
            g_setup_entry_flags[idx] = slot + 1;
        } else {
            g_setup_entry_flags[idx] = slot + 0x81;
        }
        O8(0x13F) = idx;
        if (idx < D_8008FD8C) {
            O8(0x127) = idx;
        } else {
            O8(0x127) = 0xFF;
        }
    }
    *(u8 **)(obj + 0x144) = e;
    obj_load_part_models(e, O8(0x13F), arg3);
    if (slot < D_8008FD8C || type == 0x98 || type == 0x28) {
        *(struct197 **)(obj + 0x31C) = allocate_memory(0x1C0, 1, 0, 0);
        bzero(*(void **)(obj + 0x31C), 0x1C0);
        *(f32 *)(*(u8 **)(obj + 0x31C) + 0x1B8) = 5.0f;
    }
    O8(0x1D0) = 2;
    O8(0x3B) = e[0x28];
    OF(0x14C) = *(f32 *)(e + 0x20);
    OF(0x150) = *(f32 *)(e + 0x24);
    OF(0x154) = *(f32 *)(e + 0x20);
    OF(0x158) = *(f32 *)(e + 0x24);
    O32(0x0) = e[3];
    OF(0x14) = *(s16 *)(e + 6);
    OF(0x18) = *(s16 *)(e + 8);
    O8(0x212) = 0xFF;
    O8(0x20F) = 0xFF;
    O8(0x210) = 0xFF;
    O8(0x211) = 0xFF;
    O8(0x128) = 0xFF;
    OF(0x2C) = OF(0x14);
    OF(0x30) = OF(0x18);
    OF(0x1CC) = OF(0x18);
    OF(0x1C) = *(s16 *)(e + 0xA);
    OF(0x34) = OF(0x1C);
    if (*(u16 *)e & 6) {
        obj_fade_command((struct127 *)obj, 4, 0, 0, 0);
    }
    O8(0x232) = e[0xD];
    if (idx < D_8008FD8C && D_800901E4[idx] == -2) {
        REC(0x84) = 1;
        O8(0x232) = 1;
    }
    if (O8(0x127) != 0xFF) {
        O8(0x128) = mp_player_team(O8(0x127));
        REC(0x19A) = D_800D2550;
        REC(0x1AF) = 0x40;
        REC(0x1B0) = 0xFF;
    }
    O8(0x1CA) = e[0xE] & 0xF;
    O8(0x221) = 1;
    O8(0x1E5) = e[0xF];
    O8(0x1E6) = e[0xF];
    O8(0x23C) = e[0x1C];
    O8(0x23D) = e[0x1D];
    v = e[0xC] << 8;
    O16(0x76) = v;
    O16(0x7A) = v & 0xFFFF;
    O16(0x78) = v & 0xFFFF;
    OF(0x40) = (f32)((v & 0xFFFF) + 0x4000) * 0.0054931640625f;
    OF(0x24) = 6.0f;
    O8(0x140) = arg2;
    flags = *(s32 *)(e + 0x18);
    O32(0xF8) = flags;
    if (flags & 0x200000) {
        O16(0x224) = (s32)OF(0x18);
    }
    if (flags & 0x10000000) {
        O16(0x38) = (s32)(OF(0x18) - 500.0f);
    }
    if (flags & 0x800000) {
        D_800C67F0 = 1;
    }
    O8(0x1E4) = e[0x11];
    O8(0x1DD) = 0x78;
    O8(0x1DE) = 0x78;
    O8(0x1DF) = 0x78;
    O8(0x1E0) = 0xFF;
    O8(0x1E1) = 0xFF;
    O8(0x1E2) = 0xFF;
    O8(0x23E) = 4;
    O8(0x246) = 1;
    O8(0x247) = 0x64;
    O8(0x248) = 0x64;
    O8(0x1FC) |= 2;
    O8(0x66) = e[0x10];
    obj_copy_type_params(obj, type, e);
    O16(0x92) = ((e[0x13] & 0x80) << 8) | (e[0x13] & 0x7F);
    O16(0x90) = *(s16 *)(e + 0x14);
    obj_set_type(slot, type, 1);
    if (type != 0xFF) {
        obj_anim_state_alloc((struct127 *)obj, 0, 0, 1.0f);
    } else {
        O8(5) = 3;
    }
    if (O32(0xF8) & 0x4000) {
        model_make_ready((struct127 *)obj, O8(4), 0, 0);
    }
    if (e[0x29] != 0) {
        obj_setup_run((struct127 *)obj, e[0x29], 1.0f, 0);
    }
    if (O8(0x127) != 0xFF) {
        O8(0x1CA) = player_stat_get((s16)O8(0x127), 4);
        O16(0xB2) = (s16)D_800D2132;
        obj_set_spawn_flags(obj);
        obj_apply_setup_variant((struct127 *)obj, player_stat_get((s16)slot, 1));
    }
    if ((O8(0x66) & 0xC) == 8 || (O8(0x66) & 0xC) == 0xC) {
        obj_alloc_light_bufs(obj);
    } else {
        O32(0x314) = 0;
    }
    O8(0x288) = level_list_index_of(type);
    if (D_800BE616 != 0) {
        v = mp_player_team(O8(0x127));
        if (v >= 4) {
            v = 3;
        }
        if (type == 0x3B) {
            O8(0x68) = v + 1;
        } else if (type == 0x77) {
            O8(0x68) = v + 0x10;
        }
    }
    if (D_80038080 == 0 && g_level_id != 0x1D && e[0x2E] == 0xFF) {
        n = O8(0x2C9);
        if (n == 0) {
            n = 1;
        }
        for (i = 0; i < n; i++) {
            ((u8 *)D_800D2040)[(*(u8 **)(obj + 0x2C4))[i]] = 0xFF;
        }
    }
    if (g_level_id == 0x1D) {
        O8(0x66) &= 0xDF;
    }
    char_fx_init((struct127 *)obj);
    v = obj_current_part_model((struct_eu_AF2A0 *)obj);
    found = 0;
    for (t = D_800A7610; t != D_800A7620; t += 8) {
        if (v == t[0]) {
            found = 1;
            break;
        }
    }
    if (found) {
        p = (u8 *)allocate_memory(0xC, 1, 0, 2);
        *(u8 **)(obj + 0x260) = p;
        if (p != NULL) {
            p[8] = 0;
            p[9] = 0xFF;
            *(f32 *)(p + 0) = 0.0f;
            *(f32 *)(p + 4) = 1.0f;
        }
    }
    obj_randomize_anim_frame(obj);
    return slot + 1;
}
#undef O8
#undef O16
#undef O32
#undef OF
#undef REC
typedef struct {
    u8 pad0[0x127];
    u8 unk127;
    u8 pad128[0x1C];
    u8 *unk144;
    u8 pad148[0x1B8];
    u8 unk300;
    u8 unk301;
    u8 pad302[2];
    s32 unk304[4];
    s32 unk314;
} S836AC;
s32 light_alloc_light_buf(s32);
s32 light_alloc_lookat_buf(void);
/* was func_150836AC */
void obj_alloc_light_bufs(S836AC *arg0)
{
    s32 i;
    s32 sel;
    u8 tmp;

    if (arg0->unk144 != NULL) {
        tmp = arg0->unk144[0x2F];
        if (tmp == 0) { if (arg0->unk127 == 0) sel = 5; else sel = 3; } else { sel = tmp; }
        for (i = 0; i <= D_80082FA0; i++) {
            arg0->unk304[i] = light_alloc_light_buf(sel);
        }
        if (arg0->unk304[i - 1] != 0) {
            arg0->unk301 = sel;
        }
        arg0->unk314 = light_alloc_lookat_buf();
    }
}

/* was func_15083784 */
void obj_apply_setup_variant(struct127 *arg0, s32 arg1) {
    s32 sp1C;
    s32 temp_t5;
    s32 temp_v0_2;
    s32 temp_v1;
    struct126 *temp_v0;

    sp1C = -1;
    switch (arg1) {
    case 37:
    case 38:
        temp_v0 = arg0->unk31C;
        if (temp_v0 != NULL) {
            (*(s8 *)((u8 *)temp_v0 + 0x1B2)) = 1;
        }
        break;
    case 9:
        arg0->unk94 |= 2;
        break;
    case 13:
        sp1C = 0x76;
        break;
    case 14:
        sp1C = 0x78;
        break;
    case 15:
        sp1C = 0x77;
        arg0->unk94 |= 2;
        break;
    case 29:
    case 30:
    case 31:
    case 32:
        temp_v1 = arg1 - 0x1D;
        arg0->unk94 = 0x1E;
        if (temp_v1 < 2) {
            arg0->unk94 = 0x1E & ~0x14;
        } else {
            arg0->unk94 &= ~8;
        }
        if ((temp_v1 >> 1) != 0) {
            arg0->unk94 &= ~2;
        }
        break;
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
        temp_t5 = (s32) (arg1 - 0x11) >> 2;
        arg0->unk94 = 0x3E;
        switch (temp_t5) {                          /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            arg0->unk94 &= ~4;
            break;
        case 1:                                     /* switch 1 */
            arg0->unk94 &= ~8;
            break;
        case 2:                                     /* switch 1 */
            arg0->unk94 &= ~0x10;
            break;
        }
        temp_v0_2 = (arg1 - (temp_t5 * 4)) - 0x11;
        switch (temp_v0_2) {                        /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            arg0->unk94 &= ~2;
            break;
        case 2:                                     /* switch 2 */
            arg0->unk94 &= ~0x20;
            break;
        case 3:                                     /* switch 2 */
            arg0->unk94 &= ~0x22;
            break;
        }
        break;
    }
    if (sp1C != -1) {
        obj_setup_run(arg0, sp1C, 0.0f, 0);
    }
}
/* P36: run the setup command list D_80087064[arg1 - 1] ({list, count} of 0x10-byte commands) on obj: type 0 ->
 * obj_spawn_attached, else attachment_create (attachment spawn; arg10 = cmd[6] for type 2, else -1). Returns the last result. */

/* was func_15083568 */
s32 obj_setup_run(struct127 *arg0, s32 arg1, f32 arg2, s32 arg3) {
    s32 temp_s4;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;
    u8 temp_v0;
    s32 var_v0_2;
    u8 *temp_s5;
    u8 *var_s0;

    temp_s4 = arg1 - 1;
    temp_s5 = ((s32 *)((u8 *)&D_80087064 + (temp_s4 * 8)));
    var_v1 = 0;
    var_s1 = 0;
    if ((s32) (*(u8 *)((u8 *)temp_s5 + 4)) > 0) {
        var_s0 = (*(u8 **)((u8 *)temp_s5 + 0));
        do {
            temp_v0 = (*(u8 *)((u8 *)var_s0 + 3));
            if (temp_v0 == 0) {
                var_v0 = obj_spawn_attached(arg0, (*(u8 *)((u8 *)var_s0 + 1)), (*(u8 *)((u8 *)var_s0 + 0)), 0, (s32) (*(u8 *)((u8 *)var_s0 + 2)), (s32) (*(u8 *)((u8 *)var_s0 + 4)), (s32) (*(u8 *)((u8 *)var_s0 + 5)), (s32) (*(u8 *)((u8 *)var_s0 + 6)), arg2);
            } else {
                if (temp_v0 == 2) {
                    var_v0_2 = (*(u8 *)((u8 *)var_s0 + 6));
                } else {
                    var_v0_2 = -1;
                }
                var_v0 = (s32) attachment_create((u8 *) arg0, (*(u8 *)((u8 *)var_s0 + 0)), (*(u8 *)((u8 *)var_s0 + 1)), (*(u8 *)((u8 *)var_s0 + 7)), (s32) (*(u8 *)((u8 *)var_s0 + 4)), (s32) (*(u8 *)((u8 *)var_s0 + 5)), arg3, temp_s4 + 1, (s32) (*(u8 *)((u8 *)var_s0 + 2)), var_s0 + 8, (s32) var_v0_2, (s32) (*(u8 *)((u8 *)var_s0 + 0xE)), (s32) (*(u8 *)((u8 *)var_s0 + 0xF)));
            }
            var_v1 = var_v0;
            var_s1 += 1;
            var_s0 += 0x10;
        } while (var_s1 < (s32) (*(u8 *)((u8 *)temp_s5 + 4)));
    }
    return var_v1;
}
extern s32 D_80087064;
void attachment_remove_by_slot(s32 arg0, s32 arg1);
struct127 *obj_find_by_id(s32 arg0);
void obj_release_partner_remove(struct127 *arg0, struct127 *arg1);
void obj_remove(struct127 *arg0, s32 arg1);

// object_setup_undo: undoes setup command list D_80087064[n - 1] on obj (the list obj_setup_run runs): first
// attachment_remove_by_slot(obj, n), then for every type-0 command (+3 == 0) the object it spawned (obj_find_by_id(cmd[0])) is
// removed if it is still attached to obj (+0x65 == obj's index + 1): kinds 0x1D / 0x6E / 0x2F are detached with
// obj_release_partner_remove(o, owner), other kinds removed with obj_remove(o, 0). No return value (callers ignore v0).
/* was func_150836CC */
s32 obj_setup_undo(struct127 *obj, s32 n) {
    u8 *list = (u8 *) &D_80087064 + (n - 1) * 8;
    u8 *cmd;
    u8 *o;
    s32 i;

    attachment_remove_by_slot((s32) obj, n);
    cmd = *(u8 **) list;
    for (i = 0; i < list[4]; i++, cmd += 0x10) {
        if (cmd[3] != 0) {
            continue;
        }
        o = (u8 *) obj_find_by_id(cmd[0]);
        if (o == NULL || o[0x65] != ((u8 *) obj - (u8 *) g_objects) / 0x32C + 1) {
            continue;
        }
        if (o[4] == 0x1D || o[4] == 0x6E || o[4] == 0x2F) {
            obj_release_partner_remove((struct127 *) o, (struct127 *) ((u8 *) g_objects + o[0x65] * 0x32C - 0x32C));
        } else {
            obj_remove((struct127 *) o, 0);
        }
    }
    return 0;
}
/* P36: set object slot's type (+4). 0xFF (no type): clears +0xE4/E6/E8, +0xD2 = +0xD4 = 0x46, +0xD6, +0x160, +0xC8 = 0.
 * Else +0xC8 = type record D_800D1C90[type]->+6 (s16), obj_set_scale(obj, +0x14C, +0x150), +5 = record +0x12.
 * Then +6 = obj_type_model_group(obj) (model id); +0x58 = asset_lookup_rom(0, 2, 2, id) when D_800C5A90[id] != 0. arg2 unused. */
/* was func_15083C3C */
void obj_set_type(s32 slot, s32 type, s32 arg2) {
    u8 *obj = (u8 *) g_objects + slot * 0x32C;
    u8 *rec;
    u8 id;

    obj[4] = type;
    if (type == 0xFF) {
        *(s16 *) (obj + 0xE4) = 0;
        *(s16 *) (obj + 0xE6) = 0;
        *(s16 *) (obj + 0xE8) = 0;
        *(s16 *) (obj + 0xD2) = 0x46;
        *(s16 *) (obj + 0xD4) = 0x46;
        *(s16 *) (obj + 0xD6) = 0;
        *(s16 *) (obj + 0x160) = 0;
        *(f32 *) (obj + 0xC8) = 0.0f;
    } else {
        rec = (u8 *) D_800D1C90[type];
        *(f32 *) (obj + 0xC8) = (f32) *(s16 *) (rec + 6);
        obj_set_scale((struct127 *) obj, *(f32 *) (obj + 0x14C), *(f32 *) (obj + 0x150));
        obj[5] = ((u8 *) D_800D1C90[type])[0x12];
    }
    id = obj_type_model_group(obj);
    obj[6] = id;
    if ((u16) D_800C5A90[id] != 0) {
        *(u8 **) (obj + 0x58) = asset_lookup_rom(0, 2, 2, id);
    }
}
struct197 *allocate_memory(s32, s32, s32, s32);

/* was func_15083D54 */
s32 obj_anim_state_alloc(struct127 *arg0, u16 arg1, s32 arg2, f32 arg3) {
    struct197 *temp_v0_2;
    u8 temp_v0;

    temp_v0 = arg0->id;
    if (D_800D1588[temp_v0] == 0) {
        goto block_7;
    }
    if ((u16) D_800C5A90[temp_v0] == 0) {
        goto block_7;
    }
    temp_v0_2 = allocate_memory(0x3E0, 1, 2, 0);
    arg0->unk2D0 = temp_v0_2;
    if (temp_v0_2 == NULL) {
        return 1;
    }
    bzero(arg0->unk2D0, 0x40);
    obj_start_anim(arg0, arg1, arg3, 0.0f, 0.0f, 0.0f, arg2);
block_7:
    return 0;
}
/* Copy an object's per-type parameters from its type record D_800D1C90[type] (P15, hand C). */
/* was func_15083E20 */
void obj_copy_type_params(u8 *arg0, u16 type, u8 *arg2) {
    u8 *t;

    if (type == 0xFF) {
        return;
    }
    t = (u8 *)D_800D1C90[type];
    if (arg2 != NULL) {
        u16 v = *(u16 *)(arg2 + 0x2C);

        if (v == 0) {
            *(u16 *)(arg0 + 0x10) = *(u16 *)(t + 0x2A);
        } else if (v == 1) {
            *(u16 *)(arg0 + 0x10) = 0;
        } else {
            *(u16 *)(arg0 + 0x10) = v;
        }
        if (g_level_id == 0x1D) {
            *(u16 *)(arg0 + 0x10) = 1000;
        }
    } else {
        *(u16 *)(arg0 + 0x10) = 0;
    }
    arg0[0x13B] = t[0x39];
    *(s8 *)(arg0 + 0x2CB) = *(s8 *)(t + 0x33);
    *(s32 *)(arg0 + 0x2CC) = *(s32 *)(t + 0x34);
    arg0[5] = t[0x12];
    arg0[0x68] = t[0x3B];
    arg0[0x69] = t[0x3C];
    *(s16 *)(arg0 + 0x160) = *(s16 *)(t + 2);
    if (t[4] != 0) {
        *(s32 *)(arg0 + 0x2C4) = (&D_8008704C)[t[5]];
        arg0[0x2C8] = t[4];
    }
    arg0[0x2C9] = arg0[0x2C8] + t[0x38];
    if (t[0x29] != 0) {
        look_record_alloc(arg0);
    }
}
s32 anim_bank_load(s32, s32);
s32 model_header_load(s32, s32);
struct127 *obj_alloc_slot(void);
void obj_fade_reset(struct127 *arg0);
s32 light_alloc_light_buf(s32);
s32 light_alloc_lookat_buf(void);
void obj_copy_type_params(u8 *, u16, u8 *);
void obj_set_type(s32 slot, s32 type, s32 arg2);
s32 obj_anim_state_alloc(struct127 *, u16, s32, f32);

// object_spawn_attached: setup command type 0 (obj_setup_run): makes a new object of kind `kind` in a free slot
// (obj_alloc_slot; no NULL check, as the asm) attached to owner: +0x65 = owner slot + 1, +0x3B = 0xFF - own slot,
// +0x5C = mode, +0xAB = arg3, +0 = arg4, +0xAC = flags (bit 0: +0xF8 |= 0x4000 and +0x270 = kind record +0xE * scale;
// bit 1: passed to obj_anim_state_alloc), +0x101 = keepScale (0: scales 1.0, else the owner's), copies of the owner's
// +0x66 (without bit 4) and +0x1DD..+0x1E2 (+0x1DF takes the owner's +0x1DE, as the asm does), per-camera slots
// +0x304.. from light_alloc_light_buf(1). While D_800C35EA == 1 the D_800C3638 byte is 0 during the kind setup. Returns it.
/* was func_15083F30 */
s32 obj_spawn_attached(struct127 *owner, u8 mode, u8 kind, s32 arg3, s32 arg4, s32 flags, s32 keepScale, s32 arg7,
                         f32 arg8) {
    u8 *ow = (u8 *) owner;
    u8 *o;
    s32 *slot;
    s32 i;
    s32 flag2;
    s32 single;

    model_header_load(kind, 0);
    anim_bank_load(kind, 0);
    o = (u8 *) obj_alloc_slot();
    o[0x3B] = 0xFF - (o - (u8 *) g_objects) / 0x32C;
    o[0xAB] = arg3;
    *(s32 *) o = arg4;
    obj_fade_reset((struct127 *) o);
    o[0x232] = 1;
    o[0x1CA] = 1;
    o[0x125] = 0xFF;
    o[0x65] = (ow - (u8 *) g_objects) / 0x32C + 1;
    *(s32 *) (o + 0x5C) = mode;
    o[0x123] = 1;
    o[4] = kind;
    o[0x66] = ow[0x66] & ~0x10;
    o[0x1DD] = ow[0x1DD];
    o[0x1DE] = ow[0x1DE];
    o[0x1DF] = ow[0x1DE];
    o[0x1E0] = ow[0x1E0];
    o[0x1E1] = ow[0x1E1];
    o[0x1E2] = ow[0x1E2];
    if (keepScale == 0) {
        *(f32 *) (o + 0x14C) = 1.0f;
        *(f32 *) (o + 0x150) = 1.0f;
        *(f32 *) (o + 0x154) = 1.0f;
        *(f32 *) (o + 0x158) = 1.0f;
    } else {
        *(f32 *) (o + 0x14C) = *(f32 *) (ow + 0x14C);
        *(f32 *) (o + 0x150) = *(f32 *) (ow + 0x150);
        *(f32 *) (o + 0x154) = *(f32 *) (ow + 0x154);
        *(f32 *) (o + 0x158) = *(f32 *) (ow + 0x158);
    }
    o[0x101] = keepScale;
    o[0xAC] = flags;
    model_header_load(kind, 0);
    if (flags & 1) {
        *(s32 *) (o + 0xF8) |= 0x4000;
        *(f32 *) (o + 0x270) = (f32) *(u16 *) ((u8 *) D_800D1C90[kind] + 0xE) * *(f32 *) (o + 0x14C);
    }
    flag2 = (flags & 2) ? 1 : 0;
    slot = (s32 *) (o + 0x304);
    for (i = 0; i <= D_80082FA0; i++) {
        slot[i] = light_alloc_light_buf(1);
    }
    if (slot[i - 1] != 0) {
        o[0x301] = 1;
    }
    *(s32 *) (o + 0x314) = light_alloc_lookat_buf();
    single = D_800C35EA == 1;
    if (single) {
        D_800C3638 = 0;
    }
    obj_copy_type_params(o, kind, NULL);
    obj_set_type((o - (u8 *) g_objects) / 0x32C, kind, 1);
    obj_anim_state_alloc((struct127 *) o, arg7, flag2, arg8);
    if (single) {
        D_800C3638 = 1;
    }
    return (s32) o;
}
/* was func_15084208 */
s32 setup_next_free_id(void) {
    s32 id;
    s32 i;
    id = 1;
    i = 0;
    if (D_800D2520 > 0) {
        do {
            if (id == *((u8 *)D_800D20FC + i * 0x30 + 0x28)) {
                id++;
                i = 0;
            }
            i++;
        } while (i < D_800D2520);
    }
    if (id >= 0x100) {
        id = 0xFF;
    }
    return id;
}

/* P95: index of the level-setup entry (0x30 bytes at D_800D20FC, D_800D2520 of them) whose byte +0x28 is `id`;
 * -1 when id is 0 or not found. */
/* was func_15083E0C */
s32 setup_entry_find_by_id(u8 id) {
    s32 i;

    if (id == 0) {
        return -1;
    }
    for (i = 0; i < D_800D2520; i++) {
        if (((u8 *) D_800D20FC + i * 0x30)[0x28] == id) {
            return i;
        }
    }
    return -1;
}

/* P222: readable C for obj_find_by_setup_id (game_eu_AF2A0, 72 words); replaces the m2c-style NM body (goto loop). */
// object_find_by_id: returns the live object (word +0 != 0) of g_objects whose id byte +0x3B is `id`, scanning all
// 26 slots (the asm peels slots 0 and 1 and unrolls the rest by 4); NULL for id 0 or when none matches.
/* was func_15083E90 */
struct127 *obj_find_by_setup_id(u8 id) {
    struct127 *o;
    s32 i;

    if (id == 0) {
        return NULL;
    }
    for (i = 0, o = g_objects; i < 26; i++, o++) {
        if (o->interaction_state != 0 && id == o->unique_id) {
            return o;
        }
    }
    return NULL;
}
/* was func_15083FB0 */
s32 obj_slot_by_setup_id(u8 arg0) {
    struct127 *p = obj_find_by_setup_id(arg0);

    if (p != NULL) {
        return p - g_objects;
    }
    return -1;
}

/* P80: one argument (obj_find_by_spawn reads only the id); the callers in game_CB1C0.c pass one */
/* was func_15084000 */
s32 obj_slot_by_spawn(s32 arg0) {
    struct127 *temp_v0 = obj_find_by_spawn(arg0);

    if (temp_v0 != NULL) {
        return temp_v0 - g_objects;
    }
    return -1;
}

extern u16 D_800C5BC0[]; /* vertex block size of each model slot, in 16-byte vertices */
void heap_free(void *);

/*
 * P62: vertex blocks of object o for variant var: the two frame words o +0x28C + var * 8 (+0 / +4) that
 * obj_draw_model_dl draws from. The model slot is ((u8 *)o +0x2C4)[var]; its shared block is D_800D19A0[slot] with the
 * user count D_800D1F80[slot]. The sharing mode is (rec +0x10) & 3, rec being the record +0x144 of the parent object
 * o[0x65] - 1 (or o's own when o[0x65] is 0); no record: mode 0; slot 0: mode 2.
 *   both words set, or no shared block: nothing (0);
 *   mode 0: both words share the block (count += 2);
 *   mode 1: word 0 (if 0 or the shared block): the first user shares it (count += 2), later users get a private copy;
 *           then word 1 = word 0;
 *   mode 2: each word that is 0 or the shared block (word 1 also when the two are equal): shared if the count is 0
 *           (count += 1), else a private copy; an allocation failure stops there and, on word 1, gives word 0 back
 *           (free its copy or count -= 1) and clears it;
 *   mode 3: nothing.
 * Returns 1 when an allocation failed, else 0.
 */
/* was func_150844AC */
s32 obj_model_vertex_blocks_get(struct127 *o, s32 var) {
    u8 *obj = (u8 *)o;
    u32 *words = (u32 *)(obj + 0x28C + var * 8);
    u8 *rec;
    s32 slot;
    s32 mode;
    u32 *shared;
    u8 *count;
    s32 size;
    s32 failed;
    s32 w;

    if (obj[0x65] != 0) {
        rec = *(u8 **)((u8 *)&g_objects[obj[0x65] - 1] + 0x144);
    } else {
        rec = *(u8 **)(obj + 0x144);
    }
    slot = (*(u8 **)(obj + 0x2C4))[var];
    mode = 0;
    if (rec != NULL) {
        mode = rec[0x10] & 3;
    }
    if (slot == 0) {
        mode = 2;
    }
    shared = (u32 *)&D_800D19A0 + slot;
    if (words[0] != 0 && words[1] != 0) {
        return 0;
    }
    if (*shared == 0) {
        return 0;
    }
    failed = 0;
    count = (u8 *)D_800D1F80 + slot;

    if (mode == 0) {
        words[1] = *shared;
        words[0] = *shared;
        *count += 2;
    } else if (mode == 1) {
        if (words[0] == 0 || words[0] == *shared) {
            if (*count != 0) {
                size = D_800C5BC0[slot] * 16;
                words[0] = (u32)allocate_memory(size, 1, 2, 2);
                if (words[0] == 0) {
                    failed = 1;
                } else if (words[0] != 0) {
                    bcopy((void *)*shared, (void *)words[0], size);
                } else {
                    words[0] = *shared; /* not reached (the asm has it) */
                }
            } else {
                words[1] = *shared;
                words[0] = *shared;
                *count += 2;
            }
        }
        words[1] = words[0];
    } else if (mode == 2) {
        for (w = 0; w < 2; w++) {
            if (!(words[w] == 0 || words[w] == *shared || (w == 1 && words[0] == words[1]))) {
                continue;
            }
            if (*count != 0) {
                size = D_800C5BC0[slot] * 16;
                words[w] = (u32)allocate_memory(size, 1, 2, 2);
                if (words[w] == 0) {
                    failed = 1;
                    if (w == 1) {
                        if (words[0] != *shared) {
                            heap_free((void *)words[0]);
                        } else {
                            *count -= 1;
                        }
                        words[0] = 0;
                    }
                    break;
                }
                if (words[w] != 0) {
                    bcopy((void *)*shared, (void *)words[w], size);
                } else {
                    words[w] = *shared; /* not reached (the asm has it) */
                }
            } else {
                words[w] = *shared;
                *count += 1;
            }
        }
    }
    return failed;
}

void obj_model_refs_release(struct127 *, s32);

/* was func_150847B4 */
void obj_model_refs_release_all(u8 *arg0) {
    s32 var_s0;
    u8 var_s1;

    var_s1 = (*(u8 *)((u8 *)arg0 + 0x2C9));
    if (var_s1 == 0) {
        var_s1 = 1;
    }
    var_s0 = 0;
    if ((s32) var_s1 > 0) {
        do {
            obj_model_refs_release(arg0, var_s0);
            var_s0 += 1;
        } while (var_s0 != var_s1);
    }
}

/* P150 */
// object_model_refs_release: drops entry slot's two model block references (struct127 words +0x28C + slot * 8).
// A reference to the slot's shared block D_800D19A0[model] (model = ((u8 *)+0x2C4)[slot]) only lowers its user
// count D_800D1F80[model] (bytes); any other block is freed with heap_set_block_tag(block, 3).
/* was func_15084814 */
void obj_model_refs_release(struct127 *obj, s32 slot) {
    s32 **ref;
    s32 model;
    s32 i;

    ref = (s32 **)((u8 *)obj + 0x28C + slot * 8);
    if (ref[0] == NULL && ref[1] == NULL) {
        return;
    }
    model = (*(u8 **)((u8 *)obj + 0x2C4))[slot];
    for (i = 0; i < 2; i++) {
        if (ref[i] == NULL) {
            continue;
        }
        if (ref[i] == ((s32 **)&D_800D19A0)[model]) {
            ((u8 *)D_800D1F80)[model]--;
        } else {
            heap_set_block_tag(ref[i], 3);
        }
        ref[i] = NULL;
    }
}

s32 anim_bank_load(s32, s32);
s32 model_header_load(s32, s32);
extern s32 D_8008704C;

/* was func_150848F0 */
void obj_load_part_models(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s1;
    struct124 *temp_v0;
    u8 *var_s0;
    u8 *var_v1;
    u8 temp_s0;
    s32 var_s2;

    temp_s0 = arg0[4];
    if (temp_s0 != 0xFF) {
        model_header_load(temp_s0, arg2);
        temp_v0 = D_800D1C90[temp_s0];
        var_v1 = arg0 + 4;
        var_s2 = temp_v0->unk4;
        if (var_s2 == 0) {
            var_s2 = 1;
        } else {
            var_v1 = *(u8 **)(&D_8008704C + (u8) temp_v0->unk5);
        }
        var_s1 = 0;
        var_s0 = var_v1;
        var_s2 += *(u8 *)((u8 *)temp_v0 + 0x38);
        if (var_s2 > 0) {
            do {
                model_header_load(*var_s0, arg2);
                anim_bank_load(*var_s0, arg2);
                var_s1 += 1;
                var_s0 += 1;
            } while (var_s1 != var_s2);
        }
    }
}

void obj_model_refs_release_all(u8 *arg0);
void heap_set_block_tag(s32 *arg0, u32 arg1);
void heap_free(void *);

// object_release_models: release the shared model resources of an object that goes away (called by the object
// removal obj_remove for kinds other than 2 / 3). For each part id of the object (+0x2C4 list, +0x2C9 count):
// the D_800D1588 and D_800D1C90 blocks of the part are freed unless another live object (of the first 25, kind byte
// +4 != 0xFF, +5 != 2) has a part that uses the same block; then every D_800D1588 slot holding that block is
// cleared. When no other object has the same part id, the per-kind buffers D_800C5C08 / D_800C6070 / D_800C6360
// (indexed by the object's kind +4, as the asm does) are freed.
/* was func_150849C0 */
void obj_release_models(struct127 *obj) {
    u8 *o = (u8 *) obj;
    u8 *parts;
    u8 *other;
    u8 *list;
    s32 kind = o[4];
    s32 nparts;
    s32 self;
    s32 freeModel;
    s32 freeRecord;
    s32 lastUser;
    s32 j;
    s32 k;
    s32 q;
    s32 id;
    s32 model;
    struct124 *record;

    if (kind == 0xFF || (&D_800D19A0)[kind] == 0) {
        return;
    }
    nparts = o[0x2C9];
    parts = *(u8 **) (o + 0x2C4);
    obj_model_refs_release_all(o);
    self = obj - g_objects;
    lastUser = 1;
    for (j = 0; j < nparts; j++) {
        freeModel = 1;
        freeRecord = 1;
        for (k = 0; k < 25; k++) {
            if (k == self) {
                continue;
            }
            other = (u8 *) &g_objects[k];
            if (*(s32 *) other == 0 || other[4] == 0xFF || other[5] == 2) {
                continue;
            }
            list = *(u8 **) (other + 0x2C4);
            id = parts[j];
            model = D_800D1588[id];
            record = D_800D1C90[id];
            for (q = 0; q < other[0x2C9]; q++) {
                if (list[q] == id) {
                    lastUser = 0;
                }
                if (D_800D1588[list[q]] == model && model != 0) {
                    freeModel = 0;
                }
                if (D_800D1C90[list[q]] == record && record != NULL) {
                    freeRecord = 0;
                }
            }
        }
        if (freeModel && (model = D_800D1588[parts[j]]) != 0) {
            heap_set_block_tag((s32 *) (model - 0x10), 3);
            for (k = 0; k < 187; k++) {
                if (D_800D1588[k] == model) {
                    D_800D1588[k] = 0;
                }
            }
        }
        if (freeRecord && D_800D1C90[parts[j]] != NULL) {
            heap_set_block_tag((s32 *) ((u8 *) D_800D1C90[parts[j]] - 0x10), 3);
            D_800D1C90[parts[j]] = NULL;
        }
        if (lastUser && (&D_800D19A0)[parts[j]] != 0) {
            if (D_800C5C08[kind] != 0) {
                heap_free((void *) D_800C5C08[kind]);
                D_800C5C08[kind] = 0;
                heap_free((void *) D_800C6070[kind]);
                D_800C6070[kind] = 0;
            }
            if (D_800C6360[kind] != 0) {
                heap_free((void *) D_800C6360[kind]);
                D_800C6360[kind] = 0;
            }
        }
        lastUser = 1;
    }
}

/* was func_15084E08 */
u8 obj_current_part_model(struct_eu_AF2A0 *arg0) {
    s32 temp_v1 = arg0->unk1C9;

    if (temp_v1 != 0) {
        return arg0->unk2C4[temp_v1 - 1];
    }
    return arg0->unk2C4[0];
}

/* was func_15084E34 */
u8 obj_current_part_model_idx(struct_eu_AF2A0 *arg0, s32 *arg1) {
    s32 temp_v1;

    if (arg0->unk1C9 != 0) {
        temp_v1 = arg0->unk1C9 - 1;
    } else {
        temp_v1 = (arg0->unk2C8 != 0) ? arg0->unk2C8 - 1 : 0;
    }
    if (arg1 != NULL) {
        *arg1 = temp_v1;
    }
    return arg0->unk2C4[temp_v1];
}

/* Per-frame countdown of the 187 resource slots (P15, hand C from the asm). D_800D2040 holds one
 * byte timer per slot (0 = idle, 0xFF = pinned). When a timer reaches 1 and the slot owns a block
 * (D_800D19A0[i]) that is not locked (D_800C5C08[i] == 0), the block is released: object references to
 * it (struct127 words 0x28C.., two per entry, unk2C9 entries) are cleared, objects whose entry list
 * (unk2C4) names slot i are notified through obj_model_refs_release, the slot's 12-byte records
 * (D_800C5758[i], D_800C5A48[i] of them) free their texture through texture_unref_age2, then the block
 * (minus its 0x38-byte header) goes back to the allocator. */
void texture_unref_age2(s32);
extern u16 D_800C5A48[];         /* record count per slot */
extern u8 *D_800C5758[];         /* 12-byte records per slot */
/* was func_15084E80 */
void model_slots_age_release(void) {
    u8 *timers = (u8 *)D_800D2040;
    s32 *blocks = &D_800D19A0;
    u16 *counts = D_800C5A48;
    u8 **records = D_800C5758;
    s32 i;

    for (i = 0; i != 187; i++) {
        u8 t = timers[i];

        if (t == 0xFF || t == 0) {
            continue;
        }
        if (t == 1 && blocks[i] != 0 && D_800C5C08[i] == 0) {
            struct127 *obj;
            u8 *rec;
            s32 j;

            for (obj = g_objects; (u32)obj < (u32)&g_obj_scratch_rec; obj++) {
                if (obj->interaction_state == 0) {
                    continue;
                }
                for (j = 0; j < obj->unk2C9; j++) {
                    s32 *ref = &obj->unk28C + j * 2;

                    if (ref[0] == blocks[i]) {
                        ref[0] = 0;
                    }
                    if (ref[1] == blocks[i]) {
                        ref[1] = 0;
                    }
                    if (((u8 *)obj->unk2C4)[j] == i) {
                        obj_model_refs_release(obj, j);
                    }
                }
            }
            rec = records[i];
            for (j = 0; j < counts[i]; j++, rec += 0xC) {
                if (*(u32 *)rec >= 0x10000000U) {
                    texture_unref_age2(*(s32 *)(rec + 4));
                }
            }
            heap_free(blocks[i] - 0x38);
            ((u8 *)D_800D1F80)[i] = 0;
            blocks[i] = 0;
            t = timers[i];
        }
        timers[i] = t - 1;
    }
}
/* was func_15085098 */
void obj_randomize_anim_frame(u8 *arg0) {
    u8 *p;
    f32 r;
    if (arg0[4] == 0x94) {
        p = *(u8 **)(arg0 + 0x2D0);
        r = (f32)((u32)random_int() % (u32)(s32)*(f32 *)(p + 0x18));
        *(f32 *)(p + 8) = r;
    }
}

extern u8 D_800BE9B0;
extern u16 D_800BE9B8[];
/* was func_15085118 */
s32 level_list_index_of(s32 arg0) {
    s32 ret = 0;
    s32 i;

    for (i = 0; i < D_800BE9B0; i++) {
        if (arg0 == D_800BE9B8[i]) {
            ret = i;
            break;
        }
    }
    return ret;
}
