#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C1F60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2290.s")
// TODO: figure out this struct!
// void func_150C2290(s32 arg0) {
//     s16 sp9A;
//     s16 sp98;
//     s8 sp95;
//     s8 sp94;
//     ?32 sp90;
//     ?32 sp8C;
//     ?32 sp88;
//     ?32 sp84;
//     ?32 sp80;
//     ?32 sp7C;
//     ?32 sp78;
//     ?32 sp74;
//     ?32 sp70;
//     s8 sp6E;
//     s8 sp6D;
//     s8 sp6C;
//     ?32 sp68;
//     ?32 sp64;
//     ?32 sp60;
//     ?32 sp5C;
//     ?32 sp58;
//     ?32 sp54;
//     s8 sp52;
//     s8 sp51;
//     s8 sp50;
//     s16 sp4E;
//     s16 sp4C;
//     s16 sp4A;
//     s16 sp48;
//     s16 sp46;
//     s16 sp44;
//     s16 sp42;
//     s16 sp40;
//     s16 sp3E;
//     s16 sp3C;
//     f32 sp38;
//     f32 sp34;
//     f32 sp30;
//     f32 sp2C;
//     f32 sp28;
//     f32 sp24;
//     f32 sp20;
//     f32 sp1C;
//     f32 sp18;
//
//     sp18 = *(void *)0x800A0258;
//     sp1C = 40.0f;
//     sp3E = 3;
//     sp40 = -0x29;
//     sp44 = -0x16;
//     sp42 = 0x15;
//     sp46 = 0x16;
//     sp48 = 7;
//     sp4E = 0x15;
//     sp50 = 0xB;
//     sp20 = *(void *)0x800A025C;
//     sp3C = 2;
//     sp4C = 0x30;
//     sp52 = 0x28;
//     sp54 = 1;
//     sp58 = 4;
//     sp6C = 0xFF;
//     sp6D = 0xFF;
//     sp70 = 3;
//     sp4A = 0;
//     sp51 = 1;
//     sp5C = 0;
//     sp60 = 0;
//     sp64 = 0;
//     sp68 = 0;
//     sp6E = 0;
//     sp74 = 0xFF;
//     sp78 = 0;
//     sp7C = 0x220005;
//     sp80 = 0x1D0600;
//     sp84 = (?32) (u8)1;
//     sp88 = 0x3B;
//     sp8C = 0x80;
//     sp90 = 0x20;
//     sp94 = 0;
//     sp95 = 7;
//     sp98 = 0xC;
//     sp9A = 0x15;
//     sp34 = 100.0f;
//     sp38 = 57.5f;
//     sp24 = *(void *)0x800A0260;
//     sp28 = 39.0f;
//     sp2C = *(void *)0x800A0264;
//     sp30 = 1.0f;
//     func_15151A38(&sp18, arg0 & 0xFF, 1);
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2424.s")
// NON-MATCHING: D_800A0638 is loaded after the -490.0f constant
// void func_150C2424(u8 arg0) {
//     f32 r;
//
//     r = func_150ADA68() * 8.0f + 8.0f;
//     func_1514C9E0(D_800A0638, -490.0f, -328.0f, D_800A0638, -490.0f, 328.0f, r, 1, 0, 0.0f, 0, arg0);
//     r = func_150ADA68() * 3.0f + 4.0f;
//     func_1514C9E0(D_800A063C, -560.0f, -580.0f, 8117.0f, -560.0f, -580.0f, r, 3, 0, 0.0f, 0, arg0);
// }
s32 func_150C251C(struct_eu_sprite *arg0) {
    struct_eu_sprite_sub *sub = arg0->unk98;
    s32 v = arg0->unk1C * 8;

    if (v >= 0x100) {
        v = 0xFF;
    }
    sub->unk1B = v;
    if (sub->unk1B < 0) {
        return 0;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2558.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2700.s")
void func_150C2804(s32 arg0, s32 arg1, s32 arg2, s16 arg3, u8 arg4, s32 arg5) {
    struct_eu_EF410 sp1C;

    sp1C.unkC = D_800A0650;
    sp1C.unk0 = arg0;
    sp1C.unk4 = arg1;
    sp1C.unk8 = arg2;
    sp1C.unk10 = D_800A0654;
    sp1C.unk14 = arg3;
    sp1C.unk16 = 5;
    sp1C.unk17 = 6;
    sp1C.unk18 = 3;
    sp1C.unk19 = -1;
    func_15134908(&sp1C, 0, arg4, arg5);
}
void func_150C2898(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, struct_eu_2062D0_c *arg6) {
    f32 sp6C[3];
    f32 sp60[3];
    f32 temp_f2;
    s32 pad;
    u32 sp54;
    u32 sp50;
    f32 sp4C;

    sp6C[0] = arg0;
    sp6C[1] = arg1;
    sp6C[2] = arg2;
    temp_f2 = ((func_150ADA68() * 112.0f) + 247.0f) * D_800A0658;
    sp60[0] = -arg3 * temp_f2;
    sp60[1] = -arg4 * temp_f2;
    sp60[2] = -arg5 * temp_f2;
    sp4C = func_150ADA68();
    sp50 = func_150ADA20();
    sp54 = func_150ADA20();
    func_151D9014(sp6C, sp60, 6, (sp4C * D_800A065C) + D_800A0660, (sp50 & 0xF) + 0x19, (sp54 % 101) + 0x9B, (func_150ADA68() * 119.0f) + 129.0f, 0, 1.0f, 1.0f, 1, 0, 1, 0, arg6->unkC, arg6->unk1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C29F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2C00.s")
s32 func_150C2FCC(struct_eu_EF410_b *arg0) {
    arg0->unk2C -= arg0->unk2C * arg0->unk150;
    arg0->unk30 -= arg0->unk30 * arg0->unk150;
    arg0->unk38 += arg0->unk50 * D_800BE9A4 + 0.5f * arg0->unk4C * D_800BE9A4 * D_800BE9A4;
    arg0->unk50 += arg0->unk4C * D_800BE9A4;
    if (arg0->unk2C < 10.0f || arg0->unk30 < 10.0f) {
        return 0;
    }
    return 1;
}
s32 func_150C308C(struct_eu_EF410_d *arg0) {
    u8 flag = FALSE;
    struct17 *v;
    f32 d;

    if (arg0->unk1C >= 6) {
        v = (struct17 *)func_15144B34(D_80082FA4);
        d = v->unk0 * v->unk0 + v->unk8 * v->unk8;
        if (d < D_800A06E0) {
            flag = TRUE;
        } else if (D_800A06E4 < func_15144C8C(func_150484A0(v->unk0, v->unk8), arg0->unk160)) {
            flag = TRUE;
        }
    }
    if (flag) {
        arg0->unk1C = 5;
    }
    return 1;
}
// ? func_150C308C(void *arg0) {
//     u8 sp1F;
//     f32 temp_f0;
//     f32 temp_f2;
//     u8 temp_a1;
//     void *temp_v0;
//     u8 phi_a1;
//
//     phi_a1 = (u8)0U;
//     if ((s32) arg0->unk1C >= 6) {
//         sp1F = 0;
//         temp_v0 = func_15144B34(D_80082FA4, (u8)0U);
//         temp_f0 = temp_v0->unk0;
//         temp_f2 = temp_v0->unk8;
//         temp_a1 = sp1F;
//         if (((temp_f0 * temp_f0) + (temp_f2 * temp_f2)) < D_800A0310) {
// block_4:
//             phi_a1 = (u8)1U;
//         } else {
//             sp1F = temp_a1;
//             phi_a1 = temp_a1;
//             if (D_800A0314 < func_15144C8C(func_150484A0(temp_v0->unk0, temp_v0->unk8, temp_a1), arg0->unk160)) {
//                 goto block_4;
//             }
//         }
//     }
//     if (phi_a1 != 0) {
//         arg0->unk1C = (u16)5;
//     }
//     return 1;
// }

Gfx *func_150C3160(Gfx *gfx, struct_eu_EF410_c *arg1) {
    f32 r;
    s32 v;
    s32 t;

    if (arg1->unk2E8 != 0) {
        r = (f32)arg1->unk2E4 / (f32)arg1->unk2E8;
    } else {
        r = 1.0f;
    }
    r = 1.0f - r;
    v = 500.0f * r + 2.0f;
    t = 2 - arg1->unk2EC;
    arg1->unk2EC = v / 3;
    while (t < 0) {
        t += 0x40;
    }
    gDPSetTileSize(gfx++, 4, v, t, 0x1FE, 0x3E);
    return gfx;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3230.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3574.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3994.s")

s32 func_150C3D48(s32 arg0) {
    return arg0 + 0xEDCBA988;
}

s32 func_1516DF0C(s16, s16, s16, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15170F24(s32, s32, s32, s32, f32, s32, s32);
s32 func_15171770(s32, s32, f32, f32, f32, f32, f32, f32, f32, s32, s32, f32, s32, s32);
s32 func_151BA1A0(s32, s32, s16, s16, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_150C3D48(s32 arg0);
extern f32 D_800A0708;
s32 func_151EF800(u32, u32 *);
s32 func_10004074(s32);

void func_150C3D5C(struct127 *arg0) {
    s32 sum;
    s32 pad[2]; // fakematch: unused 8-byte slot above the Header locals
    Header header;
    Header2 header2;

    func_151BA1A0(0x2F, 1, arg0->x_position, arg0->y_position, arg0->z_position, 0x578, 0x500, 0x320, 0x4B0, 0x200, 0x200, 0x1E, 1, 0, 0xFF, 0);
    ((s32 (*)(u32, u32 *))func_151EF800)(func_150C3D48(sum = 0xC23459B8), (u32 *)&sum);
    if (sum != 0x0330C820) {
        ((u32 *)&func_10004074)[0] = 0x03E00008;
        ((u32 *)&func_10004074)[1] = 0;
    }
    func_15171770(3, 0xCB, arg0->x_position, arg0->y_position, arg0->z_position, 10.0f, 1.0f, 2.0f, 60.0f, 3, 0x3C, D_800A0708, 0xFF, 0);
    func_15170F24(arg0->x_position, arg0->y_position + 20.0f, arg0->z_position, 0xA, 2000.0f, 0xFF, 0);
    func_1516DF0C(arg0->x_position, arg0->y_position, arg0->z_position, 0xD, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0xFF, 0, 0, 0, 0x14, 0x14, 2, 0, 0, 0, 0, 0x51, 0x51, 0x51, 0x51, 0xA, 1, 0, 0xFF, 0xA, 0x578, 0x190, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0xFF, 0);
    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 11U) + 0xA;
    header.unk4 = 0;
    header2.unk0 = arg0->x_position;
    header2.unk4 = arg0->y_position;
    header2.unk8 = arg0->z_position;
    func_151602C0(&header, &header2, (func_150ADA20() % 52U) + 0x28, 0xFF, 0xFF, 0x5A, 0xFF, 0, 0, 0xFF, 1);
}
