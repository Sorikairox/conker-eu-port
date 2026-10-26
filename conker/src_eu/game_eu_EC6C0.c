#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 hitinfo_from_obj_floor(s32, u8 *);
s32 collision_floor_probe(f32 *, s32, f32, s32);
s32 mtx_get_translation(s32, s32, f32 *);

/* was func_150BEEB0 */
s32 obj_fx_bone_point_a(f32 *arg0, u8 *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];
    s32 var_a1;

    switch (arg3) {
    case 4:
        var_a1 = 0x17;
        break;
    case 5:
        var_a1 = 0x14;
        break;
    case 6:
        var_a1 = 0xC;
        break;
    case 7:
    default:
        var_a1 = 0x10;
        break;
    }
    mtx_get_translation(*(s32 *)(arg1 + 0x1D4), var_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }
    sp2C[0] = arg0[0];
    sp2C[1] = arg0[1] + 10.0f;
    sp2C[2] = arg0[2];
    hitinfo_from_obj_floor(arg2, arg1);
    return collision_floor_probe(sp2C, 0, arg0[1] - 50.0f, arg2);
}

/* was func_150BEFA8 */
s32 impact_a_effect_id(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg0 == 1)) {
        return 0x11;
    }
    return -1;
}

void fx_spawn_impact_particle(u8, s32 *, f32, s32, f32 *, u8);
void fx_spawn_impact_burst(u8, f32 *, s32, f32, f32);
extern f32 D_800A0490;
extern f32 D_800A0494;
extern f32 D_800A0498;
extern f32 D_800A049C;
// impact_effect_a: P250. Handler (u8 *obj, kind, level) of the effect table at ELF file offset 0x24A4DC (records
// {handler, 0x55}; neighbours obj_fx_point_impact_d0 / impact_effect_b, `(u8 *, int, s32)` like obj_fx_point_impact_bc). When the
// object has a model (+0x1D4) and obj_fx_bone_point_a finds the effect point for `kind` (pos + hit record), it spawns effect
// 0xB there (fx_spawn_impact_particle: strength level * D_800A0490 * D_800A0494, size +0x40 * D_800A0498 as a byte) and, for
// level >= 0x4C, also effect 2 (fx_spawn_impact_burst) with the hit record's word 6.
/* was func_150BEFCC */
void impact_effect_a(u8 *obj, s32 kind, s32 level) {
    f32 pos[3];
    s32 hit[9]; /* filled by obj_fx_bone_point_a (a hit record: word 6 is passed on to fx_spawn_impact_burst) */

    if (*(s32 *) (obj + 0x1D4) != 0 && obj_fx_bone_point_a(pos, obj, (s32) hit, (u8) kind) != 0) {
        fx_spawn_impact_particle(0xB, hit, (f32) level * D_800A0490 * D_800A0494, (u8) (u32) (*(f32 *) (obj + 0x40) * D_800A0498), pos,
                      (u8) kind);
        if (level >= 0x4C) {
            fx_spawn_impact_burst(2, pos, hit[6], 3.232f, D_800A049C);
        }
    }
}


/* was func_150BF130 */
s32 obj_fx_bone_point_b(f32 *arg0, u8 *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];
    s32 var_a1;

    switch (arg3) {
    case 4:
        var_a1 = 0x19;
        break;
    case 5:
        var_a1 = 0x16;
        break;
    case 6:
        var_a1 = 0xC;
        break;
    case 7:
    default:
        var_a1 = 0x10;
        break;
    }
    mtx_get_translation(*(s32 *)(arg1 + 0x1D4), var_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }
    sp2C[0] = arg0[0];
    sp2C[1] = arg0[1] + 10.0f;
    sp2C[2] = arg0[2];
    hitinfo_from_obj_floor(arg2, arg1);
    return collision_floor_probe(sp2C, 0, arg0[1] - 50.0f, arg2);
}

/* was func_150BF228 */
s32 impact_b_effect_id(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg0 == 1)) {
        return 0x12;
    }
    return -1;
}

extern f32 D_800A04A0;
extern f32 D_800A04A4;
extern f32 D_800A04A8;
// impact_effect_b: P250. Same as impact_effect_a (impact_effect_a) with the obj_fx_bone_point_b effect points, strength
// level * D_800A04A0 * 2, size +0x40 * D_800A04A4 and D_800A04A8 for the second effect.
/* was func_150BF24C */
void impact_effect_b(u8 *obj, s32 kind, s32 level) {
    f32 pos[3];
    s32 hit[9]; /* filled by obj_fx_bone_point_b (a hit record: word 6 is passed on to fx_spawn_impact_burst) */

    if (*(s32 *) (obj + 0x1D4) != 0 && obj_fx_bone_point_b(pos, obj, (s32) hit, (u8) kind) != 0) {
        fx_spawn_impact_particle(0xB, hit, (f32) level * D_800A04A0 * 2.0f, (u8) (u32) (*(f32 *) (obj + 0x40) * D_800A04A4), pos,
                      (u8) kind);
        if (level >= 0x4C) {
            fx_spawn_impact_burst(2, pos, hit[6], 3.232f, D_800A04A8);
        }
    }
}

s32 event_dispatch(s32, s32, ...);

/* was func_150BF3B0 */
void player_update_btn_flags(u8 *arg0) {
    if ((event_dispatch(1, 0x4063, 6, 0x2000) != 0) || (event_dispatch(1, 0x4001, 6, 0x9000) != 0)) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x1010);
    } else {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x1010);
    }
    if (event_dispatch(1, 0x4069, 6, 0x2000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x01000000);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0xFEFFFFFF);
}
