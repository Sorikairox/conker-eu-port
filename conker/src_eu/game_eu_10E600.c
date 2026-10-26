#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
typedef struct {
    f32 height;     // ground height under the probe
    s16 tri[9];     // hit triangle (passed on to func_150E856C)
    s32 unk18;
    u8 flags;       // bit 0: ground found
    u8 unk1D;
    u8 pad1E[2];
    s32 unk20;
} HitInfo_150E0DF0;
void func_1504715C(HitInfo_150E0DF0 *out, u8 *obj);
s32 func_15046F70(u8 *pos, u16 arg1, f32 min_y, u8 *out);
void func_150E856C(f32 arg0, u8 arg1, s32 arg2, u8 *arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, s32 argB);
void func_151D58E4(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6);
s32 func_151D5AC4(u8 *pos, u8 arg1, s32 arg2);
void func_151D45A4(u8 *arg0, u8 arg1, s32 arg2);
void func_150E892C(f32 *arg0, s16 arg1, u8 arg2, s32 arg3);
s32 func_15154728(f32 *pos, f32 time, f32 size, f32 bright, f32 flat, u8 arg5, s32 arg6);
s32 object_hit_effects(u8 *obj, u8 smoke, u8 splats, u8 debris, u8 finish, u8 fewer, u8 arg6, s32 arg7);
s32 func_151D4684(f32 *pos, f32 *dir, struct127 *obj, struct127 *model, s32 arg4, s32 sound1, s32 sound2, s32 flags);
/* object_explode: big explosion at an object (obj NULL: nothing). Two explosion sounds (0x2BB / 0x2BA, not when
 * D_800C35EA == 1); probes the ground below (from 100 above to 200 below the blast point, 20 above the object) and,
 * when found, leaves a scorch decal there (func_150E856C); shock wave / flash / smoke / sparks effects
 * (func_151D5404, func_151D58E4, func_151D5AC4, func_151D45A4), debris at the ground point (or the blast point),
 * a light (func_15154728), the object's hit effects (object_hit_effects) and the blast damage (func_151D4684, sounds
 * 0x16 / 0x15). `owner` / `arg2` are passed through to the effects. */
void func_150E0DF0(u8 *obj, u8 owner, s32 arg2) {
    HitInfo_150E0DF0 hit;
    f32 probe[3];
    f32 ground[3];
    f32 pos[3];
    u8 landed;
    f32 r;
    u32 a, b;

    if (obj == NULL) {
        return;
    }
    if (D_800C35EA != 1) {
        func_10010630(0x2BB, (struct127 *) obj, 0x7FFF, 1000, 2000);
        func_10010630(0x2BA, (struct127 *) obj, 0x7FFF, 1000, 2000);
    }
    pos[0] = *(f32 *) (obj + 0x14);
    pos[1] = *(f32 *) (obj + 0x18) + 20.0f;
    pos[2] = *(f32 *) (obj + 0x1C);
    landed = FALSE;
    probe[0] = pos[0];
    probe[1] = pos[1] + 100.0f;
    probe[2] = pos[2];
    func_1504715C(&hit, obj);
    if (func_15046F70((u8 *) probe, 0, pos[1] - 200.0f, (u8 *) &hit) != 0 && (hit.flags & 1)) {
        ground[0] = probe[0];
        ground[1] = hit.height;
        ground[2] = probe[2];
        landed = TRUE;
        r = func_150ADA68();
        a = func_150ADA20();
        b = func_150ADA20();
        func_150E856C(r * 125.0f + 204.0f, a % 101U + 155, (s32) hit.tri, (u8 *) ground, b % 302U + 500, 0, 1, 0, 0, 0,
                      owner, 0);
    }
    func_151D5404((struct17 *) pos, 506.0f, 1013.0f, 0.0009871668880805373f, 15, 20, owner, arg2);
    func_151D58E4((u8 *) pos, 506.0f, 1013.0f, 0.0009871668880805373f, 5, owner, arg2);
    func_151D5AC4((u8 *) pos, owner, arg2);
    func_151D45A4((u8 *) pos, owner, arg2);
    func_150E892C(landed ? ground : pos, (s16) ((u32) func_150ADA20() % 62U + 120), owner, arg2);
    r = func_150ADA68();
    a = func_150ADA20();
    func_15154728(pos, r * 4.0f + 12.0f, 1.6409999132156372f, (f32) (a % 56U + 200), 0.0f, owner, arg2);
    object_hit_effects(obj, 1, 1, 1, 1, 0, owner, arg2);
    func_151D4684(pos, NULL, (struct127 *) obj, (struct127 *) obj, 0, 0x16, 0x15, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10E600/func_150E0DF0.s")
#endif

#ifdef NON_MATCHING
void func_15021834(struct127 *, s32, s32);
s32 func_150535F4(struct127 *);
void func_15056B08(struct127 *);
void func_150585F0(struct127 *); /* P209: the asm reads only a0 and returns nothing */
s32 func_150599C8(struct127 *, s32, u16);
extern u16 D_800CC766;

void func_150E1160(struct127 *arg0) {
    u8 temp_t0;
    u8 temp_v0;
    u8 var_v0;

    arg0->unkB0 = 0xF;
    arg0->unk80 = 0xA;
    if (arg0->unk87 != 0) {
        var_v0 = arg0->unk83;
        if ((s32) var_v0 < 0x64) {
            temp_t0 = var_v0 + D_800BE9A0;
            arg0->unk83 = temp_t0;
            var_v0 = temp_t0 & 0xFF;
        }
        if ((s32) var_v0 >= 5) {
            temp_v0 = arg0->unk251;
            if (temp_v0 != 3) {
                arg0->unk218 = NULL;
                arg0->unk232 = 4;
                arg0->unk78 = D_800CC766;
                if (temp_v0 == 2) {
                    arg0->unk232 = 2;
                }
            }
        }
    } else {
        if ((s32) arg0->unk83 >= 0x3D) {
            D_800D1580 = -0xFDFECD;
            D_800D154C = D_800CC2D0;
            func_1506E8D8();
            D_800D154C = arg0;
        }
        arg0->unk83 = 0;
    }
    if (arg0->unk232 == 4) {
        if (arg0->unk83 == 0) {
            arg0->unk78 = arg0->unk76;
        }
        func_150599C8(arg0, 3, arg0->unk78);
    }
    arg0->unk87 = 0;
    if (arg0->stunned == 0) {
        func_15056B08(arg0);  // P50: one argument (the asm leaves 0x3D4C0000 in a1, unused)
    } else {
        func_150585F0(arg0);
    }
    arg0->unk40 = (f32) (s16) (arg0->unk7A + 0x4000) * 0.005493164f;
    func_15059140(arg0);
    arg0->unkBC = arg0->x_position - arg0->old_x_position;
    arg0->unk148 = arg0->z_position - arg0->old_z_position;
    if (func_150535F4(arg0) == 0) {
        func_15021834(arg0, 0, -1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_10E600/func_150E1160.s")
#endif