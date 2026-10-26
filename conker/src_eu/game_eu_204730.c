#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A5860[];


/* was func_151D6F20 */
void pickup_burst_in_mp_level(s32 arg0, s32 arg1) {
    if ((g_level_id == 50) || (g_level_id == 51)) {
        obj_sprite_burst_spawn(arg0, 0xFF, 1);
    }
}


typedef struct {
    s16 u0[4];
    struct17 pos;
    s16 u14;
    s16 u16;
    f32 u18;
    f32 u1C;
    s16 u20;
    s16 u22;
    f32 u24;
    f32 u28;
    u8 u2C;
    u8 u2D;
    f32 u30;
    f32 u34;
    u8 u38;
    u8 u39;
    f32 u3C;
    u8 u40;
    f32 u44;
} S06E8;

s32 emit_dust_by_angles(S06E8 *, struct17 *, f32 *, u8, s32);
void hitinfo_from_obj_floor(f32 *, struct127 *);

/* was func_151D6F64 */
void pickup_spin_sparkle_spawn(s16 *arg0, struct127 *arg1) {
    f32 v[9];
    struct_eu_15154488 s;

    hitinfo_from_obj_floor(v, arg1);
    s.unk8.unk0 = arg0[8];
    s.unk8.unk4 = arg0[9];
    s.unk8.unk8 = arg0[10];
    s.unk14 = 2.49f;
    s.unk18 = 2.03f;
    s.unk1C = 0.60800004f;
    s.unk20 = 0.257f;
    s.unk24 = 17.0f;
    s.unk28 = 3.5f;
    s.unk2C = 3;
    s.unk2E = 3;
    s.unk2 = 0xFF;
    s.unk4 = -0x2B;
    s.unk6 = 0x20;
    s.unk0 = 0;
    s.unk30 = 3;
    s.unk32 = 2;
    s.unk34 = 0x28;
    s.unk36 = 0x14;
    s.unk38 = 0x9B;
    s.unk3A = 0x64;
    s.unk44 = 0x10;
    s.unk46 = 0xF;
    s.unk40 = 0.4f;
    s.unk48 = 0;
    s.unk3C = 9;
    emit_sparks_in_angle_range(&s, &s.unk8, (s32)v, 0xFF, 1);
    {
    S06E8 t;
    t.pos.unk0 = arg0[8];
    t.pos.unk4 = arg0[9];
    t.pos.unk8 = arg0[10];
    t.u14 = 0xF;
    t.u18 = 10.0f;
    t.u1C = 6.0f;
    t.u16 = 6;
    t.u0[0] = 0;
    t.u0[1] = 0xFF;
    t.u0[2] = -0x40;
    t.u24 = -1.506f;
    t.u0[3] = 0xC;
    t.u20 = 0x3C;
    t.u22 = 0x2D;
    t.u28 = 0.814f;
    t.u2C = 0xC8;
    t.u2D = 0x37;
    t.u38 = 1;
    t.u30 = 44.0f;
    t.u39 = 9;
    t.u34 = 88.0f;
    t.u3C = 1.0f;
    t.u40 = 0;
    t.u44 = 1.0f;
    emit_dust_by_angles(&t, &t.pos, v, 0xFF, 1);
    }
}

u8 *event_get_vars(s32);
u8 *text_pager_spawn(s32, s32 *, s32, s32, s32, s32, s32, s32);
s32 anim_model_fx_spawn(s8 *, s32, f32, s32, s32, s32, s32, s32); /* P95: f32 (float bits were passed as an int) */
s32 memcpy(s32, u8 **, s32);
extern s32 D_800AB630;

/* was func_151D71AC */
void money_collect_popup_spawn(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u38;
        u8 * u3C;
        u8 u40;
        u8 pad41[0x3];
        s32 u44;
        s16 u48;
        s16 u4A;
        u8 pad4C[0x4];
        s8 u50;
        s8 u51;
        s8 u52;
        s8 u53;
        s8 u54;
        u8 pad55[0x1];
        s16 u56;
        s32 u58;
        s32 u5C;
        s32 u60;
        s32 u64;
        s32 u68;
        s32 u6C;
        s32 u70;
        s32 u74;
        s32 u78;
        s8 u7C;
        s8 u7D;
        u8 pad7E[0x2];
        s8 u80;
        s8 u81;
        s8 u82;
        s8 u83;
        s8 u84;
        s8 u85;
        s8 u86;
        s8 u87;
        s8 u88;
        u8 pad89[0x3];
        u8 * u8C;
        u8 u90;
        s8 u91;
        u8 pad92[0x2];
        s32 u94;
        u8 pad98[0xC];
        s16 uA4;
        s16 uA6;
    } sp;
    s32 temp_v1;
    u8 *temp_t4;
    u8 *temp_v0;
    u8 *temp_v0_2;

    sp.u53 = 1;
    sp.u54 = -1;
    sp.u50 = 0x27;
    sp.u51 = -1;
    sp.u52 = 3;
    sp.u74 = 0x80;
    sp.u78 = 0x20;
    sp.u56 = 0x96;
    sp.u58 = 0xA5;
    sp.u5C = 0x17;
    sp.u64 = 0x220405;
    sp.u68 = 0x40200;
    sp.u7D = 8;
    sp.u6C = 1;
    sp.u70 = 0x38;
    sp.u88 = 0;
    sp.u60 = 0;
    sp.u7C = 0;
    sp.u80 = 0xFF;
    sp.u81 = 0xFF;
    sp.u82 = 0xFF;
    sp.u83 = 0xFF;
    sp.u84 = 0xFF;
    sp.u85 = 0xFF;
    sp.u86 = 0xFF;
    sp.u87 = 0xFF;
    sp.u8C = arg0;
    temp_t4 = ((u8 *)&D_800A5860);
    sp.u91 = 1;
    sp.u90 = (*(u8 *)((u8 *)arg0 + 0x3B));
    (*(s32 *)((u8 *)(&sp.u94) + 0)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
    (*(s32 *)((u8 *)(&sp.u94) + 4)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
    (*(s32 *)((u8 *)(&sp.u94) + 8)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
    sp.uA4 = 8;
    sp.uA6 = 0x1F;
    anim_model_fx_spawn(&sp.u50, 0, 1.0f, 0, 0, 0, (s32) arg1, arg2); /* P95: f32 (float bits were passed as an int) */
    sp.u3C = arg0;
    sp.u38 = D_800AB630;
    sp.u48 = 8;
    sp.u4A = 0x1F;
    sp.u40 = (*(u8 *)((u8 *)arg0 + 0x3B));
    sp.u44 = player_stat_get(0, 6);
    temp_v0 = event_get_vars(0x83);
    if (temp_v0 != NULL) {
        temp_v1 = (*(s32 *)((u8 *)temp_v0 + 0x64)) + 1;
        if (temp_v1 == 0xFF) {
            sp.u44 += 0x64;
        } else {
            if (temp_v1 == 0) {
                goto block_7;
            }
            if (temp_v1 < 3) {
                sp.u44 = (s32) (sp.u44 * temp_v1) / 3;
            }
        }
    } else {
block_7:
        sp.u44 = 0;
    }
    temp_v0_2 = text_pager_spawn(0x63, &sp.u38, 0x96, 0x10, 3, 1, (s32) arg1, arg2);
    if (temp_v0_2 != NULL) {
        memcpy((*(s32 *)((u8 *)temp_v0_2 + 0x48)), &sp.u3C, 0x10);
    }
}
f32 camera_get_yaw_deg(s32);
#define MTX_7410(a) (((f32 (*)[16])((a) + 0x7C))[D_800BE9C0])
/* was func_151D7410 */
s32 money_popup_mtx_update(u8 *arg0) {
    mtxf_rotate_xyz_deg(&MTX_7410(arg0), 0.0f, camera_get_yaw_deg(0) + 25.0f, 0.0f);
    MTX_7410(arg0)[12] = (*(f32 **)(arg0 + 0x4C))[5];
    MTX_7410(arg0)[13] = (*(f32 **)(arg0 + 0x4C))[6] + 120.0f;
    MTX_7410(arg0)[14] = (*(f32 **)(arg0 + 0x4C))[7];
    MTX_7410(arg0)[0] *= 0.551f;
    MTX_7410(arg0)[1] *= 0.551f;
    MTX_7410(arg0)[2] *= 0.551f;
    MTX_7410(arg0)[4] *= 0.551f;
    MTX_7410(arg0)[5] *= 0.551f;
    MTX_7410(arg0)[6] *= 0.551f;
    MTX_7410(arg0)[8] *= 0.551f;
    MTX_7410(arg0)[9] *= 0.551f;
    MTX_7410(arg0)[10] *= 0.551f;
    return 1;
}
#undef MTX_7410

/* P241: readable C for money_popup_draw (game_eu_204730, 51 insns). */
// money_popup_draw: entry 3 of the record table D_80088C40 (dispatcher text_pager_update ends the record, timer +0xE = -1,
// when the result is 0). Returns 0 once the owner object (data +0) is gone or its id byte +0x3B no longer matches
// data +4; otherwise prints "$ %d" (D_800AB634, the amount at data +8) above the owner in colour (0x32, 0x7D, 0x1C)
// with alpha fading in over the first data +0xC frames (timer * step data +0xE, clamped at 0; 0xFF after) and keeps
// the record. The asm returns text_printf's leftover v0 there (the last text node, non-zero unless the text pool
// is full), like its siblings' explicit 1.
extern u8 D_800AB634[];
void text_printf(s32, ...); /* varargs, as its definition (game_70200) */
/* was func_151D75B0 */
s32 money_popup_draw(u8 *rec) {
    u8 *data = *(u8 **) (rec + 0x48);
    u8 *owner = *(u8 **) data;
    s16 timer;
    s16 alpha;

    if (*(s32 *) owner == 0 || data[4] != owner[0x3B]) {
        return 0;
    }
    timer = *(s16 *) (rec + 0xE);
    alpha = 0xFF;
    if (timer < *(s16 *) (data + 0xC)) {
        alpha = timer * *(s16 *) (data + 0xE);
        if (alpha < 0) {
            alpha = 0;
        }
    }
    text_set_box((s32) owner, 0x109);
    text_set_color(0x32, 0x7D, 0x1C, alpha);
    text_set_flags(0x81);
    text_printf((s32) D_800AB634, *(s32 *) (data + 8));
    return 1;
}

/* was func_151D767C */
void money_popup_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *temp = *(u8 **)(arg0 + 0x48);
    node_handle_link_message(arg1, arg2, temp, temp + 4, arg0);
}

extern s32 D_80083AD0;
extern s32 D_80083C50;
u8 *gfx_emit_sprite_tex_segment(u8 *, s32, s32, s32);
/* was func_151D76BC */
Gfx *banner_sprite_set_segment(Gfx *gdl, u8 *arg1, s32 arg2, s32 arg3, s8 *arg4) {
    if (arg1[0x43] < 0xFF) {
        gSPSegment(gdl++, 8, &D_80083AD0);
    } else {
        gSPSegment(gdl++, 8, &D_80083C50);
    }
    gdl = (Gfx *)gfx_emit_sprite_tex_segment((u8 *)gdl, 0xC3, 6, 3);
    gdl = (Gfx *)gfx_emit_sprite_tex_segment((u8 *)gdl, 0xC3, 7, 3);
    *arg4 = 1;
    return gdl;
}
