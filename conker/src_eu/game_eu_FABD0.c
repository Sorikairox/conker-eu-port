#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CD3C0.s")

#ifdef NON_MATCHING
void func_151436B4(f32, f32, f32, void *);

s32 func_150CD68C(u8 *arg0) {
    u8 *sp20;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f18;
    f32 var_f18_2;
    f32 var_f18_3;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;

    temp_f2 = (*(f32 *)((u8 *)arg0 + 0x114));
    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x11C));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x34)) + ((*(f32 *)((u8 *)arg0 + 0x110)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((temp_f2 * D_800BE9A4) + (0.5f * temp_f12 * D_800BE9A4 * D_800BE9A4)));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x3C)) + ((*(f32 *)((u8 *)arg0 + 0x118)) * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x114)) = (f32) (temp_f2 + (temp_f12 * D_800BE9A4));
    var_v0 = D_800BE9E4;
    if (var_v0 != 0) {
        temp_a1 = -(var_v0 & 3);
        temp_a0 = temp_a1 + var_v0;
        if (temp_a1 != 0) {
            temp_v1 = arg0 + 0x110;
            temp_f0 = (*(f32 *)((u8 *)temp_v1 + 0x10));
            var_v0 -= 1;
            var_f18 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0;
            var_f16 = (*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0;
            if (temp_a0 != var_v0) {
                do {
                    (*(f32 *)((u8 *)temp_v1 + 0)) = var_f18;
                    (*(f32 *)((u8 *)temp_v1 + 8)) = var_f16;
                    var_f18 = (*(f32 *)((u8 *)temp_v1 + 0)) * temp_f0;
                    var_v0 -= 1;
                    var_f16 = (*(f32 *)((u8 *)temp_v1 + 8)) * temp_f0;
                } while (temp_a0 != var_v0);
            }
            (*(f32 *)((u8 *)temp_v1 + 0)) = var_f18;
            (*(f32 *)((u8 *)temp_v1 + 8)) = var_f16;
            if (var_v0 != 0) {
                goto block_5;
            }
        } else {
block_5:
            temp_v1_2 = arg0 + 0x110;
            temp_f0_2 = (*(f32 *)((u8 *)temp_v1_2 + 0x10));
            var_v0_2 = var_v0 - 4;
            var_f16_2 = (*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2;
            if (var_v0_2 != 0) {
                do {
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = var_f16_2;
                    var_v0_2 -= 4;
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                    (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
                    var_f16_2 = (*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2;
                    (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
                } while (var_v0_2 != 0);
            }
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = var_f16_2;
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 0)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 0)) * temp_f0_2);
            (*(f32 *)((u8 *)temp_v1_2 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v1_2 + 8)) * temp_f0_2);
        }
    }
    temp_v1_3 = arg0 + 0x110;
    if ((*(f32 *)((u8 *)temp_v1_3 + 4)) > 0.0f) {
        var_v0_3 = D_800BE9E4;
        if (var_v0_3 != 0) {
            temp_a1_2 = -(var_v0_3 & 3);
            temp_f0_3 = (*(f32 *)((u8 *)temp_v1_3 + 0x10));
            if (temp_a1_2 != 0) {
                temp_a0_2 = temp_a1_2 + var_v0_3;
                var_v0_3 -= 1;
                var_f18_2 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                if (temp_a0_2 != var_v0_3) {
                    do {
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_2;
                        var_v0_3 -= 1;
                        var_f18_2 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                    } while (temp_a0_2 != var_v0_3);
                }
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_2;
                if (var_v0_3 != 0) {
                    goto block_14;
                }
            } else {
block_14:
                var_v0_4 = var_v0_3 - 4;
                var_f18_3 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                if (var_v0_4 != 0) {
                    do {
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_3;
                        var_v0_4 -= 4;
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                        (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                        var_f18_3 = (*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3;
                    } while (var_v0_4 != 0);
                }
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = var_f18_3;
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
                (*(f32 *)((u8 *)temp_v1_3 + 4)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 4)) * temp_f0_3);
            }
        }
    }
    temp_f2_2 = (*(f32 *)((u8 *)temp_v1_3 + 0x3C));
    if ((*(f32 *)((u8 *)temp_v1_3 + 4)) < temp_f2_2) {
        (*(f32 *)((u8 *)temp_v1_3 + 4)) = temp_f2_2;
    }
    if ((*(f32 *)((u8 *)temp_v1_3 + 4)) < 0.0f) {
        sp20 = temp_v1_3;
        func_151436B4((*(f32 *)((u8 *)temp_v1_3 + 0x2C)), ((*(f32 *)((u8 *)temp_v1_3 + 0x38)) * sinf((*(f32 *)((u8 *)temp_v1_3 + 0x30)))) + 1.5707964f, (*(f32 *)((u8 *)temp_v1_3 + 0x24)), arg0 + 0x4C);
        (*(f32 *)((u8 *)temp_v1_3 + 0x24)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x24)) + ((*(f32 *)((u8 *)temp_v1_3 + 0x28)) * D_800BE9A4));
        (*(f32 *)((u8 *)temp_v1_3 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) + ((*(f32 *)((u8 *)temp_v1_3 + 0x34)) * D_800BE9A4));
        if ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) > 6.2831855f) {
            do {
                (*(f32 *)((u8 *)temp_v1_3 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) - 6.2831855f);
            } while ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) > 6.2831855f);
        }
        if ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) < 0.0f) {
            do {
                (*(f32 *)((u8 *)temp_v1_3 + 0x30)) = (f32) ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) + 6.2831855f);
            } while ((*(f32 *)((u8 *)temp_v1_3 + 0x30)) < 0.0f);
        }
    }
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x40)) + (*(f32 *)((u8 *)temp_v1_3 + 0x14)));
    (*(f32 *)((u8 *)arg0 + 0x44)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x44)) + (*(f32 *)((u8 *)temp_v1_3 + 0x18)));
    (*(f32 *)((u8 *)arg0 + 0x48)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x48)) + (*(f32 *)((u8 *)temp_v1_3 + 0x1C)));
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CD68C.s")
#endif
#ifdef NON_MATCHING
void func_151D6310(void *, s16, s32, void *, u8 *);
void *memcpy(void *, const void *, s32);

// sprite_quad_build: entry of the D_8008A1E0 draw table (`s16 *(u8 *, s16 slot)`, same family as func_15198180).
// Gets 0x40 bytes of vertices for the view slot from the record's buffers at +0x100 (func_151D6310; on a fresh
// buffer the matrix at +0xC0 is copied into both halves of it) and returns them (NULL when none). The four corners
// (+/- half width +0x2C, +/- half height +0x30, z 0) are rotated by the angles +0x40 / +0x44 / +0x48
// (func_150A8050 / func_150A7E40) and stored as s16 x, y, z with flag 0. (The asm also sums the position +0x34 and,
// when +0x114 < 0, the offset +0x4C into a stack vector it never reads; that dead code is left out.)
s16 *func_150CDAAC(u8 *arg0, s16 arg1) {
    s16 *vtx;
    s16 *ret;
    u8 fresh;
    u8 *buf;
    f32 mtx[4][4];
    f32 p[4][3];
    s32 i;

    func_151D6310(arg0 + 0x100, arg1, 0x40, &vtx, &fresh);
    ret = vtx;
    if (vtx == NULL) {
        return NULL;
    }
    if (fresh) {
        buf = *(u8 **) (arg0 + 0x100 + arg1 * 4);
        memcpy(buf, arg0 + 0xC0, 0x40);
        memcpy(*(u8 **) (arg0 + 0x100 + arg1 * 4) + 0x40, arg0 + 0xC0, 0x40);
    }
    p[0][0] = *(f32 *) (arg0 + 0x2C);
    p[0][1] = *(f32 *) (arg0 + 0x30);
    p[0][2] = 0.0f;
    p[1][0] = -*(f32 *) (arg0 + 0x2C);
    p[1][1] = *(f32 *) (arg0 + 0x30);
    p[1][2] = 0.0f;
    p[2][0] = -*(f32 *) (arg0 + 0x2C);
    p[2][1] = -*(f32 *) (arg0 + 0x30);
    p[2][2] = 0.0f;
    p[3][0] = *(f32 *) (arg0 + 0x2C);
    p[3][1] = -*(f32 *) (arg0 + 0x30);
    p[3][2] = 0.0f;
    func_150A8050(mtx, *(f32 *) (arg0 + 0x40), *(f32 *) (arg0 + 0x44), *(f32 *) (arg0 + 0x48));
    for (i = 0; i < 4; i++) {
        func_150A7E40(mtx, p[i][0], p[i][1], 0.0f, &p[i][0], &p[i][1], &p[i][2]);
        vtx[0] = (s32) p[i][0];
        vtx[1] = (s32) p[i][1];
        vtx[2] = (s32) p[i][2];
        vtx[3] = 0;
        vtx += 8;
    }
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CDAAC.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_FABD0/func_150CDD08.s")

void func_150CE07C(s32 arg0) {
    u8 *temp_v1;

    if ((arg0 >= 0) && (arg0 < 0x100) && (D_80088C10 != NULL)) {
        temp_v1 = D_80088C10 + 0x28;
        *(f32 *)(temp_v1 + 4) = arg0 * D_800A0B74;
    }
}
