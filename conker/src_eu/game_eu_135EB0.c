#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A2800[];
#endif


#ifdef NON_MATCHING
void fx_debris_emitter_spawn(void *, s16, u8, s32);
s32 object_hit_effects(struct127 *, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_800A2804;

/* was func_151086A0 */
void obj_impact_burst(struct127 *arg0, u8 arg1, s32 arg2) {
    struct {
        s32 u34;
        s32 u38;
        s32 u3C;
        u8 pad40[0x8];
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        s16 u60;
        s16 u62;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
    } sp;

    sp.u7C = arg0->x_position;
    sp.u80 = arg0->y_position;
    sp.u84 = arg0->z_position;
    sp.u70 = arg0->x_position;
    sp.u74 = arg0->y_position + 30.0f;
    sp.u78 = arg0->z_position;
    fx_debris_emitter_spawn(&sp.u7C, (s16) ((random_int() % 201U) + 0x1F4), arg1, arg2);
    sp.u34 = 0xF;
    sp.u38 = 8;
    (*(f32 *)((u8 *)(&sp.u3C) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u70) + 0));
    (*(s32 *)((u8 *)(&sp.u3C) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u70) + 4));
    (*(s32 *)((u8 *)(&sp.u3C) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u70) + 8));
    sp.u48 = 0;
    sp.u4A = 0xFF;
    sp.u4C = -0x40;
    sp.u4E = 0x29;
    sp.u60 = 0x27;
    sp.u62 = 0x14;
    sp.u64 = 0.305f;
    sp.u68 = 0.305f;
    sp.u50 = 8.0f;
    sp.u54 = 10.0f;
    sp.u58 = -0.8f;
    sp.u5C = 0.344f;
    sp.u6C = 26.411001f;
    emit_textured_burst(&sp.u34, ((u8 *)&D_800A2800), &D_800A2804, 1, 40.0f, 0U, (u8) (s32) arg1, arg2);
    object_hit_effects(arg0, 1, 1, 1, 0, 0, (s32) arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_135EB0/obj_impact_burst.s")
#endif