#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void fx_alloc_d88750(void);
extern s32 D_800D9CF0;
extern s8 D_800D9D40;
extern s8 D_800D9D41;
extern s8 D_800D9D48;
extern s8 D_800D9D49;
extern s32 D_800D9D4A;
extern s8 D_800D9D58;
extern s8 D_800D9D59;
extern s32 D_800D9D5A;
extern s32 D_800D9D66;
extern s32 D_800D9D70;
extern s32 D_800E0D94;

/* was func_1500E5C0 */
void level_objects_reset_state(void) {
    s32 *var_v0_2;
    s32 *var_v1;
    u8 *var_v0;

    fx_alloc_d88750();
    obj_holder_refs_init();
    level_init_nop_15012770();
    var_v0 = &D_800E0950;
    do {
        var_v0 += 4;
        (*(s8 *)((u8 *)var_v0 + -3)) = 0;
        (*(s8 *)((u8 *)var_v0 + -2)) = 0;
        (*(s8 *)((u8 *)var_v0 + -1)) = 0;
        (*(s8 *)((u8 *)var_v0 + -4)) = 0;
    } while ((s32)var_v0 != (s32)&D_800E0D94);
    D_800D9D41 = 0;
    D_800D9D40 = 0;
    D_800D9D48 = 0;
    D_800D9D58 = 0;
    D_800D9D49 = 0;
    var_v0_2 = &D_800D9D5A;
    var_v1 = &D_800D9D4A;
    D_800D9D59 = 0;
    do {
        var_v0_2 = (s32 *)((u8 *)var_v0_2 + (4));
        (*(s8 *)((u8 *)var_v1 + 1)) = 0;
        (*(s8 *)((u8 *)var_v0_2 + -3)) = 0;
        (*(s8 *)((u8 *)var_v1 + 2)) = 0;
        (*(s8 *)((u8 *)var_v0_2 + -2)) = 0;
        (*(s8 *)((u8 *)var_v1 + 3)) = 0;
        (*(s8 *)((u8 *)var_v0_2 + -1)) = 0;
        var_v1 = (s32 *)((u8 *)var_v1 + (4));
        (*(s8 *)((u8 *)var_v1 + -4)) = 0;
        (*(s8 *)((u8 *)var_v0_2 + -4)) = 0;
    } while (var_v0_2 != &D_800D9D66);
    D_800D9CB0 = 0;
    D_800D9CB4 = 0;
    (*(s32 *)((u8 *)(&D_800D9CF0) + 0)) = 0;
    (*(s32 *)((u8 *)(&D_800D9CF0) + 4)) = 0;
    (*(s32 *)((u8 *)(&D_800D9CF0) + 8)) = 0;
    (*(s32 *)((u8 *)(&D_800D9CF0) + 0xC)) = 0;
    D_80088C10 = NULL;
    bzero(D_800BE500, 5);
    (*(s8 *)((u8 *)(&D_800D9D70) + 2)) = 0;
    (*(s8 *)((u8 *)(&D_800D9D70) + 1)) = 0;
    (*(s8 *)((u8 *)(&D_800D9D70) + 0)) = 0;
    D_80088D20 = 0;
    (*(struct134 **)((u8 *)D_800D9AA0 + 0)) = NULL;
    (*(s32 *)((u8 *)D_800D9AA0 + 4)) = 0;
    (*(s32 *)((u8 *)D_800D9AA0 + 8)) = 0;
    D_800BE4F0 = NULL;
    D_80088B40 = 0;
}
/* was func_1500E70C */
void level_hook_level_2b(s32 arg0) {
    if (arg0 == 0x2B) {
        level_reset_d9aa0_sfx();
    }
}

extern u8 D_800DCE50;
extern f32 D_800DCE54;
extern s8 D_800DCE58;
extern f32 D_800DCE5C;

/* was func_1500E738 */
void level_set_lod_shifts(void) {
    switch (D_80082FA0) {
    case 0:
        D_800DCE50 = 0;
        D_800DCE54 = 1.0f;
        break;
    case 1:
        D_800DCE50 = 1;
        D_800DCE54 = 0.5f;
        break;
    case 2:
    case 3:
        D_800DCE50 = 2;
        D_800DCE54 = 0.25f;
        break;
    }
    switch (D_8008FD8C) {
    case 2:
        D_800DCE58 = 1;
        D_800DCE5C = 0.5f;
        return;
    case 3:
    case 4:
        D_800DCE58 = 2;
        D_800DCE5C = 0.25f;
        return;
    case 5:
    case 6:
    case 7:
    case 8:
        D_800DCE58 = 3;
        D_800DCE5C = 0.125f;
        return;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        D_800DCE58 = 4;
        D_800DCE5C = 0.0625f;
        return;
    case 1:
    default:
        D_800DCE58 = 0;
        D_800DCE5C = 1.0f;
        return;
    }
}

/* was func_1500E890 */
void level_obj_init_area_points(void) {
    area_points_reset();
    area_points_alloc(0);
    area_points_alloc(1);
}

void area_drift_emitter_create(void *arg0, u8 arg1);
extern s32 D_800B1214;

/* was func_1500E8C0 */
void level_obj_init_drift_scene(void) {
    struct {
        s16 u40;
        s16 u42;
        s16 u44;
        s16 u46;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s16 u78;
        s16 u7A;
        f32 u7C;
        f32 u80;
        s16 u84;
        s16 u86;
        s32 u88;
        s32 u8C;
    } sp;
    s16 var_v0;

    level_dl_add_texture_scroll(*D_800B0E00, D_800902E8, 0, -1, 0, 0, 0, -6);
    level_dl_add_texture_scroll(D_800B1214, D_800902E8, 0, -1, 0, 1, 0, -6);
    sp.u68 = 0.21428572f;
    sp.u70 = 5.0f;
    sp.u74 = 6.0f;
    sp.u60 = 8.0f;
    sp.u64 = 7.0f;
    sp.u6C = 0.0f;
    sp.u88 = 3;
    sp.u8C = 2;
    sp.u40 = 0x34;
    sp.u42 = 0x12;
    sp.u44 = -0x28;
    sp.u46 = 0xF;
    sp.u78 = 0x9B;
    sp.u7A = 0x64;
    sp.u84 = 0x29;
    sp.u86 = 0x29;
    sp.u50 = 400.0f;
    sp.u54 = 0.0f;
    sp.u58 = 0.0f;
    sp.u5C = 900.0f - 400.0f;
    sp.u7C = 0.6f;
    sp.u80 = 0.39999998f;
    sp.u48 = 800.0f;
    sp.u4C = -3000.0f;
    area_drift_emitter_create(&sp.u40, 1);
    if (D_800BE9F0 == 6) {
        var_v0 = 0x34;
    } else {
        var_v0 = 7;
    }
    sfx_emitter_start(0x61FU, var_v0, 0, 0, 0x2EE0, 0x3E8U, 0x190, (s32) sfx_cb_keep_until_silent, NULL, 0, 0x48, 0);
}
// NON-MATCHING: fair bit to figure out
// void level_obj_init_drift_scene(void) {
//     struct145 tmp;
//     s32 phi_v0;
//
//     level_dl_add_texture_scroll(D_800B0E00[0], D_800902E8, 0, -1, 0, 0, 0, -6);
//     level_dl_add_texture_scroll(D_800B0E00[1], D_800902E8, 0, -1, 0, 1, 0, -6);
//     tmp.unk28 = D_80096210; // 0.2142857164144516
//     tmp.unk30 = 5.0f;
//     tmp.unk34 = 6.0f;
//     tmp.unk20 = 8.0f;
//     tmp.unk24 = 7.0f;
//     tmp.unk14 = 0.0f;
//     tmp.unk18 = 0.0f;
//     tmp.unk2C = 0.0f;
//     tmp.unk48 = 3;
//     tmp.unk4C = 2;
//     tmp.unk0 = 0x34;
//     tmp.unk2 = 0x12;
//     tmp.unk4 = -0x28;
//     tmp.unk6 = 0xF;
//     tmp.unk38 = 0x9B;
//     tmp.unk3A = 0x64;
//     tmp.unk44 = 0x29;
//     tmp.unk46 = 0x29;
//     tmp.unk10 = 400.0f;
//     tmp.unk1C = 900.0f - 400.0f;
//     tmp.unk3C = D_80096214; // 0.6000000238418579
//     tmp.unk40 = D_80096218;
//     tmp.unkC = D_8009621C;
//     tmp.unk8 = 800.0f;
//     func_15189900(&tmp, 1);
//     if (D_800BE9F0 == 6) {
//         phi_v0 = 52;
//     } else {
//         phi_v0 = 7;
//     }
//     sfx_emitter_start(1567, (s16)phi_v0, 0, 0, 12000, 1000, 400, sfx_cb_keep_until_silent, 0, 0, 72, 0);
// }

/* was func_1500EAA0 */
void level_obj_init_tex_scroll(void) {
    level_dl_add_texture_scroll(D_800B0E00[0], D_80090320, 0, -1, 0, 0, 0, -8);
    level_dl_add_texture_scroll(D_800B0E00[1], D_80090320, 0, -1, 0, 1, 0, -8);
}
