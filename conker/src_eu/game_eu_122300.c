#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 mdl_particle_spawn_ex(f32 *, s32, s32, s32, s32, s32, s32);
s32 vec3_normalize_len(f32 *, f32 *, f32 *, s32 *);
s32 memcpy(s32, f32 *, s32);

/* was func_150F4AF0 */
void lightning_bolt_spawn(u8 *arg0, u8 *arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    struct {
        f32 u3C;
        s32 u40;
        u8 pad44[0x8];
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        s8 u60;
        u8 pad61[0x3];
        s32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        f32 u94;
        f32 u98;
        f32 u9C;
        f32 uA0;
        f32 uA4;
        f32 uA8;
        s32 uAC;
        u8 padB0[0x8];
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        s32 uD4;
        s16 uD8;
        s16 uDA;
        s8 uDC;
        u8 padDD[0x3];
        s32 uE0;
        s8 uE4;
        s8 uE5;
        s8 uE6;
        s8 uE7;
        s8 uE8;
        s8 uE9;
        s8 uEA;
        s8 uEB;
        s8 uEC;
        s8 uED;
        s8 uEE;
        u8 padEF[0x1];
        s32 uF0;
        s8 uF4;
        u8 padF5[0x1];
        s16 uF6;
        s16 uF8;
        u8 padFA[0x2];
        s32 uFC;
    } sp;
    f32 sp34;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f8;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    sp.u6C = (*(f32 *)((u8 *)arg1 + 0)) - (*(f32 *)((u8 *)arg0 + 0));
    sp.u70 = (*(f32 *)((u8 *)arg1 + 4)) - (*(f32 *)((u8 *)arg0 + 4));
    sp.u74 = (*(f32 *)((u8 *)arg1 + 8)) - (*(f32 *)((u8 *)arg0 + 8));
    if (vec3_normalize_len(&sp.u6C, &sp.u78, &sp.u68, &sp.u64) != 0) {
        if (arg6 != 0) {
            var_v1 = 1;
        } else {
            var_v1 = 0;
        }
        if (arg7 != 0) {
            var_v0 = 2;
        } else {
            var_v0 = 0;
        }
        sp.u60 = var_v0 | var_v1;
        sp.u3C = sp.u68 * arg4;
        (*(f32 *)((u8 *)(&sp.u40) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0));
        (*(f32 *)((u8 *)(&sp.u40) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
        (*(f32 *)((u8 *)(&sp.u40) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
        sp.u4C = random_float() * 6.2831855f;
        sp.u50 = (random_float() * 0.2f) + 0.080000006f;
        if (random_int() & 1) {
            sp.u50 = -sp.u50;
        }
        sp.u5C = (random_float() * 21.0f) + 13.0f;
        temp_f12 = random_float() * 6.2831855f;
        sp34 = temp_f12;
        sp.u54 = cosf(temp_f12);
        sp.u58 = sinf(temp_f12);
        sp.u84 = 1.0f;
        sp.u88 = 1.0f;
        sp.u90 = arg5;
        sp.u8C = arg5;
        sp.u94 = random_float() * 360.0f;
        sp.u98 = random_float() * 360.0f;
        temp_f0 = random_float();
        sp.uA0 = 1.0f;
        sp.uA4 = 1.0f;
        sp.uA8 = 1.0f;
        sp.u9C = temp_f0 * 360.0f;
        (*(f32 *)((u8 *)(&sp.uAC) + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0));
        (*(f32 *)((u8 *)(&sp.uAC) + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 4));
        (*(f32 *)((u8 *)(&sp.uAC) + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 8));
        sp.uB8 = sp.u78 * arg3;
        sp.uBC = sp.u7C * arg3;
        sp.uC0 = sp.u80 * arg3;
        temp_f8 = random_float() * 21.903002f;
        sp.uC8 = 0.0f;
        sp.uC4 = temp_f8 + -10.951501f;
        temp_f10 = (random_float() * 21.903002f) + -10.951501f;
        sp.uE4 = 0xFF;
        sp.uE5 = 0x16;
        sp.uDA = (s16) arg2;
        sp.uD4 = 0x14900;
        sp.uD8 = 0x12C;
        sp.uDC = 8;
        sp.uCC = temp_f10;
        sp.uE0 = 0;
        sp.uE6 = 7;
        sp.uE7 = 0;
        sp.uE8 = 0;
        sp.uE9 = 0;
        sp.uEA = 0;
        sp.uEB = 0;
        sp.uEC = 2;
        sp.uED = -1;
        sp.uEE = 2;
        sp.uF0 = 0;
        sp.uF4 = 0;
        sp.uF6 = 1;
        sp.uF8 = 0xFF;
        sp.uD0 = 0.0f;
        sp.uFC = arg7;
        temp_v0 = mdl_particle_spawn_ex(&sp.u84, 3, 0xFF, 0, 0x28, (s32) arg8, arg9);
        if (temp_v0 != 0) {
            memcpy(temp_v0 + 0x170, &sp.u3C, 0x28);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/lightning_bolt_spawn.s")
#endif
#ifdef NON_MATCHING
void vec2_from_angle_rad(f32, f32, f32 *, f32 *);

/* was func_150F4E50 */
u8 *lightning_bolt_update(u8 *arg0) {
    struct {
        f32 u1C;
        f32 u20;
    } sp;
    u8 *sp18;
    u8 *temp_v0;

    temp_v0 = arg0 + 0x170;
    (*(f32 *)((u8 *)arg0 + 0x170)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x170)) - D_800BE9A4);
    if ((*(f32 *)((u8 *)arg0 + 0x170)) <= 0.0f) {
        return NULL;
    }
    sp18 = temp_v0;
    vec2_from_angle_rad((*(f32 *)((u8 *)temp_v0 + 0x10)), (*(f32 *)((u8 *)temp_v0 + 0x20)), &sp.u1C, &sp.u20);
    (*(f32 *)((u8 *)sp18 + 0x10)) = (f32) ((*(f32 *)((u8 *)sp18 + 0x10)) + ((*(f32 *)((u8 *)sp18 + 0x14)) * D_800BE9A4));
    (*(f32 *)((u8 *)sp18 + 4)) = (f32) ((*(f32 *)((u8 *)sp18 + 4)) + ((*(f32 *)((u8 *)arg0 + 0x44)) * D_800BE9A4));
    (*(f32 *)((u8 *)sp18 + 8)) = (f32) ((*(f32 *)((u8 *)sp18 + 8)) + ((*(f32 *)((u8 *)arg0 + 0x48)) * D_800BE9A4));
    (*(f32 *)((u8 *)sp18 + 0xC)) = (f32) ((*(f32 *)((u8 *)sp18 + 0xC)) + ((*(f32 *)((u8 *)arg0 + 0x4C)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)sp18 + 4)) + (sp.u1C * (*(f32 *)((u8 *)sp18 + 0x18))));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)sp18 + 8)) + sp.u20);
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)sp18 + 0xC)) - (sp.u1C * (*(f32 *)((u8 *)sp18 + 0x1C))));
    (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x20)) + ((*(f32 *)((u8 *)arg0 + 0x50)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x24)) + ((*(f32 *)((u8 *)arg0 + 0x54)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x28)) + ((*(f32 *)((u8 *)arg0 + 0x58)) * D_800BE9A4));
    return sp18;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/lightning_bolt_update.s")
#endif
#ifdef NON_MATCHING
f32 vec3_length(f32 *);

// ambient_emitter_update: per-frame update of an ambient object with flags +0x194: the distance to the camera
// (camera_get_pos(0)) from the position +0x38..; flag 1 fades the alpha +0x70 (0 below 500, 255 from 1200, linear in
// between); flag 2 (unless flag 4) keeps a looping sound: when a handle is in the high half of +0x88 it is moved to
// the position (sound_voice_update_pan), otherwise within 200 units sound id (+0x88 low half) starts at a random pitch
// 0x4000..0x7FFF (sound_play_at) and its handle goes to the high half. Returns 1.
/* was func_150F4FB8 */
s32 ambient_obj_update(u8 *obj) {
    f32 delta[3];
    f32 *cam;
    f32 dist;
    u32 sound;
    u16 handle;

    if ((obj[0x194] & 1) || (obj[0x194] & 2)) {
        cam = camera_get_pos(0);
        delta[0] = *(f32 *) (obj + 0x38) - cam[0];
        delta[1] = *(f32 *) (obj + 0x3C) - cam[1];
        delta[2] = *(f32 *) (obj + 0x40) - cam[2];
        dist = vec3_length(delta);
    }
    if (obj[0x194] & 1) {
        if (dist < 500.0f) {
            obj[0x70] = 0;
        } else if (dist < 1200.0f) {
            obj[0x70] = (u32) ((dist - 500.0f) * 0.0014285714285714286 * 255.0);
        } else {
            obj[0x70] = 0xFF;
        }
    }
    if ((obj[0x194] & 2) && !(obj[0x194] & 4)) {
        sound = *(u32 *) (obj + 0x88);
        if ((sound >> 16) != 0) {
            sound_voice_update_pan(sound >> 16, (s32) * (f32 *) (obj + 0x38), (s32) * (f32 *) (obj + 0x3C),
                          (s32) * (f32 *) (obj + 0x40));
        } else if (dist < 200.0f) {
            handle = sound_play_at(*(u32 *) (obj + 0x88) & 0xFFFF, (random_int() & 0x3FFF) + 0x4000, 0, 0, -1,
                                   (s32) * (f32 *) (obj + 0x38), (s32) * (f32 *) (obj + 0x3C),
                                   (s32) * (f32 *) (obj + 0x40), 10000, 20000);
            *(u32 *) (obj + 0x88) |= handle << 16;
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/ambient_obj_update.s")
#endif

/* was func_150F527C */
void ambient_obj_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *v = arg0 + 0x170;

    if (arg2 == 0x4E) {
        arg0[0x71] = 0;
        v[0x24] |= 5;
    } else if (arg2 == 0x4F) {
        node_destroy(arg0);
    }
}

/* was func_150F4D5C */
void lightning_emitter_spawn(u8 *arg0, s8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct {
        u8 *unk0;
        f32 unk4;
        s8 unk8;
        u8 unk9;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = 0.0f;
    tmp.unk8 = arg1;
    tmp.unk9 = arg2;
    temp_v0 = func_15149130(300, -1, 0x56, -1, 0, 0, 0xC, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

#ifdef NON_MATCHING
typedef struct {
    f32 v[3];
} Vec3F536C;
typedef struct {
    u8 count;
    u8 *pairs;  // 2 bytes per choice, byte 1 = the bolt's texture / style
    f32 *scales;
} BoltSet536C;
extern s32 (*D_80088ED8[])(u8 *);
extern BoltSet536C D_80088EC0[];
void vec2_from_angle_byte(s16, f32, f32 *, f32 *);

// lightning_emitter_update: per-frame update of an emitter (record at +0x28: owner, accumulator, condition +0x30,
// bolt set +0x31). If a condition function (D_80088ED8[+0x30], -1 = none) says no, nothing happens. Otherwise the
// accumulator grows by (~0.051 + rand x ~0.153) x frame time and every whole unit spawns one bolt (lightning_bolt_spawn)
// between two points around the owner's camera (camera_get_pos(owner[0x23D])): both at a random distance 254..635
// along the camera heading (owner +0x380 degrees, to 256-unit angle) +-21, at height -133..79 relative to it, in
// random order; style / scale picked at random from the D_80088EC0 set, width 5..15.
/* was func_150F536C */
void lightning_emitter_update(u8 *obj) {
    struct {
        u8 *owner;
        f32 acc;
        s8 cond;
        u8 set;
    } *em = (void *) (obj + 0x28);
    Vec3F536C a;
    Vec3F536C b;
    Vec3F536C tmp;
    f32 *cam;
    s32 angle;
    s16 left;
    s16 right;
    BoltSet536C *set;
    u8 k;
    f32 width;
    f32 r;

    if ((s8) obj[0x30] != -1) {
        if (D_80088ED8[(s8) obj[0x30]](obj) == 0) {
            return;
        }
    }
    em->acc += (0.0510000028f + random_float() * 0.153000012f) * D_800BE9A4;
    if (!(1.0f < em->acc)) {
        return;
    }
    cam = camera_get_pos(em->owner[0x23D]);
    angle = (s32) ((*(f32 *) (em->owner + 0x380) + 180.0f) * 0.7111111283f);
    left = angle - 21;
    right = angle + 21;
    do {
        vec2_from_angle_byte(right, random_float() * 381.0f + 254.0f, &a.v[0], &a.v[2]);
        a.v[1] = random_float() * 212.0f + -133.0f;
        a.v[0] += cam[0];
        a.v[1] += cam[1];
        a.v[2] += cam[2];
        vec2_from_angle_byte(left, random_float() * 381.0f + 254.0f, &b.v[0], &b.v[2]);
        b.v[1] = random_float() * 212.0f + -133.0f;
        b.v[0] += cam[0];
        b.v[1] += cam[1];
        b.v[2] += cam[2];
        if (random_int() & 1) {
            tmp = a;
            a = b;
            b = tmp;
        }
        set = &D_80088EC0[em->set];
        k = (u32) random_int() % set->count;
        width = random_float() * 10.0f + 5.0f;
        r = random_float();
        lightning_bolt_spawn((u8 *) &a, (u8 *) &b, set->pairs[k * 2 + 1], width, 1.0f / width,
                      (r * 0.075f + 0.075f) * set->scales[k], 0, 0, obj[0xC], obj[1]);
        em->acc -= 1.0f;
    } while (1.0f < em->acc);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_122300/lightning_emitter_update.s")
#endif
