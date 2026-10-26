#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void texture_id_list_release(s16 *arg0);
void heap_free(s32);
#endif


#ifdef NON_MATCHING
/* P186 */
void swarm_spawn(u8 kind, u8 *pos, s32, s32 x, s32 y, s32 z, s32, s32 span, s32 flag, s32, s32 w6);
void flyer_field_spawn(s32, s32 slot, s32 x, s32 y, s32 z, s32, s32 player, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32);
void flyer_leaf_drop_spawn(s32, s32 slot, s32 x, s32 y, s32 z, s32, s32 player, s32, f32, f32);
void flyer_leaf_burst_spawn(s32, s32 slot, s32 x, s32 y, s32 z, s32 player, f32, f32, s32);
void puff_ground_chips_burst(f32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void anim_mesh_load_with_next(s32 arg0);
void anim_mesh_load_pair(s32 arg0);
void anim_mesh_load_dependent(s32 arg0, s32 arg1);
s32 ambfx_obj_record_flag57(u8 *arg0);
void anim_mesh_load(s32);
extern u8 D_800CC704[];

/* weather_effect_start: P186: starts weather / screen effect `kind` (0..11) in the first free of the 4 slots
 * D_800DDF5C (returns -1 when all are busy). Effect position (x, y, z), a = the effect parameter (colour / id),
 * player view `player` (D_800DBFF0 + player * 0x9A0, +0x3D0 = its camera record), sizes s1..s3 (* 16), last = the
 * last argument of the spawners. Kinds: 0 / 1 swarm_spawn bursts (1 with D_800CC704), 2 / 5 / 6 / 7 / 11
 * flyer_field_spawn particle fields (with their sound / setup calls anim_mesh_load_with_next / anim_mesh_load / anim_mesh_load_pair),
 * 3 flyer_leaf_burst_spawn (only when ambfx_obj_record_flag57 accepts the camera, else -1), 4 / 10 flyer_leaf_drop_spawn (width s1 * 64),
 * 8 -1, 9 puff_ground_chips_burst at the camera (+0x14..+0x1C, +0x3C) without taking the slot. Other kinds start nothing
 * but still take the slot. Returns the slot index. `unused` is not read. */
/* was func_15183800 */
s32 ambfx_effect_start(s32 x, s32 y, s32 z, s32 a, s32 kind, s32 unused, s32 player, s32 s1, s32 s2, s32 s3, s32 last) {
    s32 slot;
    u8 *cam;

    for (slot = 0; slot < 4; slot++) {
        if (D_800DDF5C[slot] == 0) {
            break;
        }
    }
    if (slot == 4) {
        return -1;
    }
    s1 <<= 4;
    s2 <<= 4;
    s3 <<= 4;
    cam = *(u8 **) ((u8 *) D_800DBFF0 + player * 0x9A0 + 0x3D0);
    switch (kind) {
        case 0:
            swarm_spawn(a, NULL, 0xFE, x, y, z, 0, 0x7FFF, 0xFF, 1, 0);
            break;
        case 1:
            swarm_spawn(a, D_800CC704, 0xFE, x, y, z, 0, 0x7FFF, 0xFF, 1, 0);
            break;
        case 2:
            anim_mesh_load_with_next(0);
            flyer_field_spawn(a, slot, x, y, z, 0x3F, player, 30, 0, 0x30003, 10, 0, 0, 1, 2, 0.8f, 0.5f, last);
            break;
        case 3:
            if (ambfx_obj_record_flag57(cam) == 0) {
                return -1;
            }
            flyer_leaf_burst_spawn(a, slot, x, y, z, player, 0.8f, 0.5f, last);
            break;
        case 4:
            anim_mesh_load_dependent(7, 10);
            flyer_leaf_drop_spawn(a, slot, x, y, z, s1 * 4, player, 0, 0.8f, 0.5f);
            break;
        case 10:
            anim_mesh_load(7);
            flyer_leaf_drop_spawn(a, slot, x, y, z, s1 * 4, player, 1, 0.8f, 0.5f);
            break;
        case 11:
            anim_mesh_load(2);
            anim_mesh_load(3);
            anim_mesh_load(4);
            anim_mesh_load(5);
            flyer_field_spawn(a, slot, x, y, z, s1, player, s2, s3, 77, 21, 3, 2, -1, 0, 0.8f, 0.5f, last);
            break;
        case 5:
            anim_mesh_load(2);
            anim_mesh_load(3);
            anim_mesh_load(4);
            anim_mesh_load(5);
            flyer_field_spawn(a, slot, x, y, z, s1, player, s2, s3, 77, 21, 3, 2, -1, 2, 0.8f, 0.5f, last);
            break;
        case 6:
            anim_mesh_load_pair(8);
            flyer_field_spawn(a, slot, x, y, z, s1, player, s2, s3, 125, 68, 2, 8, -1, 2, 0.8f, 0.5f, last);
            break;
        case 7:
            anim_mesh_load(6);
            flyer_field_spawn(a, slot, x, y, z, s1, player, s2, s3, 77, 20, 0, 6, 0, 2, 0.04f, 0.025f, last);
            break;
        case 8:
            return -1;
        case 9:
            puff_ground_chips_burst(*(f32 *) (cam + 0x3C), (s32) *(f32 *) (cam + 0x14), (s32) *(f32 *) (cam + 0x18),
                         (s32) *(f32 *) (cam + 0x1C), a);
            break;
    }
    if (kind != 9) {
        D_800DDF5C[slot] = 1;
    }
    return slot;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/ambfx_effect_start.s")
#endif

u8 *asset_load_with_subfiles(s32, s32, s32, s32, s32, s32);
void anim_mesh_load(s32);
extern u8 D_800DE399;

/* was func_15183E20 */
void anim_mesh_load_with_next(s32 arg0) {
    u8 *temp_v0;

    if (*(s32 *)((u8 *)D_800DDE80 + arg0 * 0x14) == 0) {
        anim_mesh_load(arg0);
    }
    if (*(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x14) == 0) {
        temp_v0 = asset_load_with_subfiles(0, 0, 0, 2, 9, arg0 + 0xAE);
        if (temp_v0 != NULL) {
            *(u8 **)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x14) = temp_v0;
            *(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x18) = *(s32 *)(temp_v0 + 0);
            *(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x1C) = *(s32 *)(temp_v0 + 8);
            *(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x24) = 0;
            *(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0x20) = *(s32 *)(((u8 *)D_800DDE80 + arg0 * 0x14) + 0xC);
            *(&D_800DE399 + arg0) = 1;
        }
    }
}

typedef struct { s32 a; s32 b; s32 c; s32 d; s32 e; } StructDDE80;
/* was func_15183EE4 */
void anim_mesh_load_pair(s32 arg0) {
    if (((StructDDE80 *)D_800DDE80)[arg0].a == 0) {
        anim_mesh_load(arg0);
    }
    if (((StructDDE80 *)D_800DDE80)[arg0 + 1].a == 0) {
        anim_mesh_load(arg0 + 1);
        ((StructDDE80 *)D_800DDE80)[arg0 + 1].d = ((StructDDE80 *)D_800DDE80)[arg0].d;
    }
}

/* was func_15183F60 */
void anim_mesh_load_dependent(s32 arg0, s32 arg1)
{
  u8 *temp_v0;
  if ((*((s32 *) (((u8 *) D_800DDE80) + (arg0 * 0x14)))) == 0)
  {
    anim_mesh_load(arg0);
    if (1) // fakematch: empty block (permuter)
    {
    }
  }
  if ((*((s32 *) (((u8 *) D_800DDE80) + (arg0 * 0x14)))) != 0)
  {
    if ((*((s32 *) (((u8 *) D_800DDE80) + (arg1 * 0x14)))) == 0)
    {
      temp_v0 = asset_load_with_subfiles(0, 0, 0, 2, 9, arg1 + 0xAD);
      if (temp_v0 != 0)
      {
        *((u8 **) (((u8 *) D_800DDE80) + (arg1 * 0x14))) = temp_v0;
        *((s32 *) ((((u8 *) D_800DDE80) + (arg1 * 0x14)) + 4)) = *((s32 *) (temp_v0 + 0));
        *((s32 *) ((((u8 *) D_800DDE80) + (arg1 * 0x14)) + 8)) = *((s32 *) (temp_v0 + 8));
        *((s32 *) ((((u8 *) D_800DDE80) + (arg1 * 0x14)) + 0xC)) = *((s32 *) (temp_v0 + 0x18));
        *((s32 *) ((((u8 *) D_800DDE80) + (arg1 * 0x14)) + 0x10)) = 0;
        D_800DDF68[arg1] = 1;
      }
    }
  }
}

#ifdef NON_MATCHING
/* P133 */
s32 texture_resolve_dl_ids(Gfx *, s32, s32, s32, s16 **);

/*
 * hud_model_load: loads model idx once (asset 9, id idx + 0xAD, through asset_load_with_subfiles) into the 0x14-byte slot
 * D_800DDE80[idx]: +0 the asset, +4 / +8 / +0xC its words 0 / 2 / 6, +0x10 the vertex list texture_resolve_dl_ids fills
 * while relocating the asset's display list (word 4, also kept in D_800DDF78[idx]); D_800DDF68[idx] = 1 marks it
 * loaded. Nothing when the slot is already set or the asset is missing.
 */
/* was func_1518403C */
void anim_mesh_load(s32 idx) {
    s32 *slot = (s32 *) ((u8 *) D_800DDE80 + idx * 0x14);
    s32 *asset;

    if (slot[0] != 0) {
        return;
    }
    asset = (s32 *) asset_load_with_subfiles(0, 0, 0, 2, 9, idx + 0xAD);
    if (asset == NULL) {
        return;
    }
    slot[0] = (s32) asset;
    slot[1] = asset[0];
    slot[2] = asset[2];
    slot[3] = asset[6];
    D_800DDF78[idx] = asset[4];
    texture_resolve_dl_ids((Gfx *) asset[4], 0, 1, 0x3E, (s16 **) &slot[4]);
    D_800DDF68[idx] = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/anim_mesh_load.s")
#endif

extern u8 D_800A76B0[];
extern s32 D_800DDF78[];

/* was func_15184114 */
Gfx *anim_mesh_draw_by_id(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 idx = -1;

    for (i = 0; i < 11; i++) {
        if (arg1 == D_800A76B0[i]) {
            idx = i;
            break;
        }
    }
    if (idx != -1) {
        if (D_800DDF78[idx] != 0) {
            gSPDisplayList(gdl++, D_800DDF78[idx]);
        }
    }
    return gdl;
}

#ifdef NON_MATCHING
extern s32 D_800DE350;
extern s8 D_800DE3A0;
extern s8 D_800DE3A1;
extern s32 D_800DE3C8;

/* Release slot arg0 of the D_800DDE80 table (0x14-byte entries): its texture (word 0x10) through
 * texture_id_list_release and its block (word 0) back to the allocator, clearing the slot's DL D_800DDF78[arg0].
 * Slot 8 keeps its block unless D_800DE3A1 == -2; slot 9 with D_800DE3A0 == -2 also frees D_800DE350.
 * (P15, hand C from the asm) */
/* was func_15184198 */
void anim_mesh_release(s32 arg0) {
    s32 *e = &D_800DDE80[arg0 * 5];

    if (e[4] != 0) {
        texture_id_list_release((s16 *)e[4]);
        e[4] = 0;
    }
    if (arg0 == 8) {
        if (D_800DE3A1 != -2) {
            return;
        }
    } else if (arg0 == 9 && D_800DE3A0 == -2 && D_800DE350 != 0) {
        heap_free(D_800DE350);
        D_800DE350 = 0;
        D_800DE3C8 = 0;
    }
    if (e[0] != 0) {
        heap_free(e[0]);
        e[0] = 0;
        D_800DDF78[arg0] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/anim_mesh_release.s")
#endif
#ifdef NON_MATCHING
/* P125 */
extern u8 D_8008D450[];
extern u8 *D_8008D760[];
void mesh_swing_update(f32 *angle, s16 *vtx, f32 amp, f32 *speed, f32 max, f32 min, u8 *rows, u8 n);
void flag_wave_update(u8 i);
void flyer_wing_flap_animate(u8 arg0);
void anim_mesh_release(s32 arg0);

/* anim_meshes_update: per frame, the 11 animated mesh slots (D_800DDE80: 5 words each, block +0, Vtx buffers +4 /
 * +8; display list D_800DDF78[i]; state D_800DDF68[i]: 1 = just set up, then 0, -1, -2 = gone).
 * A live slot that lost its block or display list becomes -2. The four byte timers D_800DDF60[0..3] count down by
 * the frame step. Slots 0..6 that are newly active swing buffer +8 (mesh_swing_update with D_8008D450[i]: angle +0x18,
 * speed +0x24, max +0x28, min +0x2C, amplitude +0x30, rows D_8008D760[i], 2 * pairs), slots 2..4 also swing
 * buffer +4 with entry i + 9; slot 7 runs flyer_wing_flap_animate(7) and sets slot 10's state to 1; slots 8 / 9 wave
 * (flag_wave_update); gone slots that still hold a block are released (anim_mesh_release). Then every state ages:
 * > 0 -> 0, 0 / -1 -> one lower, -2 stays. */
/* was func_15184298 */
void anim_meshes_update(void) {
    static const u8 pairs[7] = { 2, 2, 2, 2, 2, 2, 4 };
    u8 *e;
    s32 v;
    s32 i;

    for (i = 0; i < 11; i++) {
        if (D_800DDF68[i] >= -1 && (D_800DDE80[i * 5] == 0 || D_800DDF78[i] == 0)) {
            D_800DDF68[i] = -2;
        }
    }
    for (i = 0; i < 4; i++) {
        if (D_800DDF60[i] > 0) {
            v = D_800DDF60[i] - D_800BE9E4;
            if (v < 0) {
                v = 0;
            }
            D_800DDF60[i] = v;
        }
    }
    for (i = 0; i < 7; i++) {
        if (D_800DDF68[i] == 1) {
            e = D_8008D450 + i * 0x38;
            mesh_swing_update((f32 *) (e + 0x18), (s16 *) D_800DDE80[i * 5 + 2], *(f32 *) (e + 0x30), (f32 *) (e + 0x24),
                          *(f32 *) (e + 0x28), *(f32 *) (e + 0x2C), D_8008D760[i], pairs[i]);
        }
    }
    for (i = 2; i < 5; i++) {
        if (D_800DDF68[i] == 1) {
            e = D_8008D450 + (i + 9) * 0x38;
            mesh_swing_update((f32 *) (e + 0x18), (s16 *) D_800DDE80[i * 5 + 1], *(f32 *) (e + 0x30), (f32 *) (e + 0x24),
                          *(f32 *) (e + 0x28), *(f32 *) (e + 0x2C), D_8008D760[i], pairs[i]);
        }
    }
    if (D_800DDF68[7] == 1) {
        flyer_wing_flap_animate(7);
    }
    for (i = 0; i < 2; i++) {
        if (D_800DDF68[8 + i] == 1) {
            flag_wave_update(i + 8);
        }
    }
    if (D_800DDF68[7] == 1) {
        D_800DDF68[10] = 1;
    }
    for (i = 0; i < 11; i++) {
        if (D_800DDF68[i] == -2 && D_800DDE80[i * 5] != 0) {
            anim_mesh_release(i);
        }
    }
    for (i = 0; i < 11; i++) {
        if (D_800DDF68[i] > 0) {
            D_800DDF68[i] = 0;
        } else if (D_800DDF68[i] >= -1) {
            D_800DDF68[i]--;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1B1010/anim_meshes_update.s")
#endif

/* was func_15184688 */
s32 ambfx_obj_record_flag57(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x31C);
    if ((temp_v0 != NULL) && (temp_v0[0x57] != 0)) {
        return 1;
    }
    return 0;
}
