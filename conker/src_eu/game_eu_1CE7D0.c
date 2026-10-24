#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_151A177C(f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);


s32 func_1510FE4C(s32);

void func_151A0A10(u8 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        u8 unkC;
        u8 padD[3];
        f32 unk10;
    } tmp;

    if (arg0 != NULL) {
        tmp.unk0 = *(f32 *)(arg0 + 0x14);
        tmp.unk8 = *(f32 *)(arg0 + 0x1C);
        if (D_800C35EA != 1) {
            tmp.unk4 = *(f32 *)(arg0 + 0x180);
            tmp.unk10 = 0.0f;
            switch (func_1510FE4C(*(s32 *)(arg0 + 0x184))) {
            case 0xA:
                tmp.unkC = 0;
                break;
            case 0xF:
            case 0x11:
                tmp.unkC = 1;
                break;
            default:
                tmp.unkC = 0;
                break;
            }
            temp_v0 = func_151491F4(arg1, -1, 1, 1, 0, 0x14, arg2, arg3);
            if (temp_v0 != NULL) {
                memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x14);
            }
        }
    }
}

#ifdef NON_MATCHING
void func_1514CBE8(f32, f32, f32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
#else
s32 func_1514CBE8(f32, f32, s32, f32, s16, s16, s16, u8, s32, f32, s32, u8);
#endif
void func_151A10A8(u8 *arg0) {
    u8 *temp_s0;

    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + (0.17500001f * D_800BE9A4));
    if ((*(f32 *)((u8 *)arg0 + 0x38)) > 1.0f) {
        temp_s0 = arg0 + 0x28;
        do {
#ifdef NON_MATCHING
            func_1514CBE8((*(f32 *)temp_s0), (*(f32 *)((u8 *)temp_s0 + 4)), (*(f32 *)((u8 *)temp_s0 + 8)), (func_150ADA68() * 25.0f) + 15.0f, 0, 0xFF, 5, 4, (s32) (*(u8 *)((u8 *)temp_s0 + 0xC)), 0.0f, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)));
#else
            func_1514CBE8((*(f32 *)temp_s0), (*(f32 *)((u8 *)temp_s0 + 4)), (*(s32 *)((u8 *)temp_s0 + 8)), (func_150ADA68() * 25.0f) + 15.0f, 0, 0xFF, 5, 4, (s32) (*(u8 *)((u8 *)temp_s0 + 0xC)), 0.0f, 0, (s32) (*(u8 *)((u8 *)arg0 + 0xC)));
#endif
            (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x10)) > 1.0f);
    }
}

#ifdef NON_MATCHING
f32 func_151423D8(u8);
s32 func_15167D84(s32 **, s32, s32, s32, s32, s32);
extern u8 D_8008FC70[];          /* grey level per colour index (arg8) */
extern u8 D_80091C2C[];          /* sprite set of colour index 1 */
extern u8 D_80091C50[];          /* sprite set of colour index 0 */

/* emit_point_blob: D_8008ADA0 spawn handler (`s32 (s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0,
 * s32 a, s32 angle0, f32 r, s32 arg8, f32 arg9, s32 argA, s32 argB)`, as the game_eu_EF6D0 emitters): queues one
 * func_15167D84 sprite particle at (x, y, z) (s16) flying out along the byte angle a with a random pitch of -63..-49
 * (rand % 15 - 63) and speed 801..1304 (503 * rand + 801): s16 velocity (v sin(p) sin(a - 0x40), -v sin(p - 0x40),
 * v sin(p) sin(a)) (func_151423D8 = byte-angle sine); -130..-90 (rand % 41 - 130), two sizes 250..700 (rand % 451 +
 * 250), 200, 6..8 (rand % 3 + 6), grey D_8008FC70[arg8] with alpha 0xFF, sprite set D_80091C50 / D_80091C2C for
 * arg8 0 / 1 (other values leave the word unset, as the asm), owner byte argB. The three bytes at +0x1C take the
 * low byte of (s32) (x * 256) as in the asm. Words the asm never writes stay unset. Always returns 1 (go on). */
s32 func_151A11BC(s32 mode, s16 i, f32 x, f32 y, f32 z, f32 x0, f32 y0, f32 z0, s32 a, s32 angle0, f32 r, s32 arg8,
                  f32 arg9, s32 argA, s32 argB) {
    struct {
        u8 *sprites;        /* sp48 */
        s32 pad04[2];       /* not set */
        s16 h0C;
        s16 h0E;
        s16 pos[3];
        s16 vx;
        s16 vz;
        s16 pad1A;          /* not set */
        u8 b1C[3];
        s8 minus1;
        s16 vy;
        s16 h22;
        s16 size0;
        s16 size1;
        s16 h28;
        u8 b2A;
        u8 pad2B;           /* not set */
        u8 grey[3];
        u8 alpha;
        u8 b30[3];
        u8 pad33;           /* not set */
        s16 h34;
    } rec;
    s16 pitch;
    f32 sp, cp, sa, ca, v, h;
    s16 size;
    u8 g, xb;

    pitch = (u32) func_150ADA20() % 15U - 0x3F;
    sp = func_151423D8(pitch & 0xFF);
    cp = func_151423D8((pitch - 0x40) & 0xFF);
    sa = func_151423D8(a & 0xFF);
    ca = func_151423D8((a - 0x40) & 0xFF);
    v = func_150ADA68() * 503.0f + 801.0f;
    h = v * sp;
    rec.vx = (s32) (h * ca);
    rec.vy = (s32) (-v * cp);
    rec.vz = (s32) (h * sa);
    rec.h22 = (u32) func_150ADA20() % 41U - 0x82;
    rec.b2A = (u32) func_150ADA20() % 3U + 6;
    size = (u32) func_150ADA20() % 451U + 0xFA;
    g = D_8008FC70[arg8];
    xb = (s32) (x * 256.0f);
    rec.size0 = size;
    rec.b30[0] = 0;
    rec.b30[1] = 0;
    rec.b30[2] = 0;
    rec.alpha = 0xFF;
    rec.minus1 = -1;
    rec.h34 = 0;
    rec.h0C = 0;
    rec.h0E = 0;
    rec.size1 = size;
    rec.pos[0] = (s32) x;
    rec.grey[0] = g;
    rec.grey[1] = g;
    rec.grey[2] = g;
    rec.pos[1] = (s32) y;
    rec.pos[2] = (s32) z;
    rec.b1C[0] = xb;
    rec.b1C[1] = xb;
    rec.b1C[2] = xb;
    if (arg8 == 0) {
        rec.sprites = D_80091C50;
    } else if (arg8 == 1) {
        rec.sprites = D_80091C2C;
    }
    rec.h28 = 0xC8;
    func_15167D84((s32 **) &rec, 0, 0, -1, argB & 0xFF, 1);
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A11BC.s")
#endif

void func_151A13F0(f32 arg0, f32 arg1, f32 arg2, u8 arg3, s32 arg4) {
    func_151A177C(arg0, arg1, arg2, 163.0f, 2.019f, 0xA0, 0x4B, 0x41F, 0x4F6, 1, 2.019f, 0x87, 0x44, 0x41F, 0x4F6, 2, 1, 2.019f, 0x46, 0x42, 0x41F, 0x4F6, 7, 0x41, 4, 1, arg3, arg4);
}

void func_151A14D8(f32 arg0, f32 arg1, f32 arg2, u8 arg3, s32 arg4) {
    func_151A177C(arg0, arg1, arg2, 163.0f, 2.019f, 0xA0, 0x4B, 0x41F, 0x4F6, 1, 2.019f, 0x87, 0x44, 0x41F, 0x4F6, 2, 1, 2.019f, 0x46, 0x42, 0x41F, 0x4F6, 7, 0x41, 4, 1, arg3, arg4);
}

#ifdef NON_MATCHING
void func_151A15C0(f32 arg0, f32 arg1, f32 arg2, s16 arg3, f32 arg4, f32 arg5, u8 arg6, s32 arg7) {
    s16 temp_v0;
    s16 var_t4;
    s32 temp_f10;
    s32 temp_f18;
    s32 temp_f4;
    s32 temp_f8;

    temp_v0 = arg3 - 0x20;
    var_t4 = temp_v0;
    if (temp_v0 <= 0) {
        var_t4 = 1;
    }
    temp_f18 = (s32) (70.0f * arg5);
    temp_f8 = (s32) (30.0f * arg5);
    temp_f4 = (s32) (1500.0f * arg4);
    temp_f10 = (s32) (100.0f * arg4);
    func_151A177C(arg0, arg1, arg2, 250.0f * arg4, 1.0f, (s32) (s16) temp_f18, (s32) (s16) temp_f8, (s32) (s16) temp_f4, (s32) (s16) temp_f10, 0x12, 1.0f, (s32) (90.0f * arg5), (s32) (20.0f * arg5), (s32) (s16) temp_f4, (s32) (s16) temp_f10, (s32) var_t4, 0x10, 1.0f, (s32) (s16) temp_f18, (s32) (s16) temp_f8, (s32) (s16) temp_f4, (s32) (s16) temp_f10, (s32) (15.0f * arg4), (s32) (10.0f * arg4), 0x12, temp_v0 + 0x10, (u8) (s32) arg6, arg7);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A15C0.s")
#endif
void func_151A177C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, f32 argA, s32 argB, s32 argC, s32 argD, s32 argE, s32 argF, s32 arg10, f32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19, u8 arg1A, s32 arg1B) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1794.s")

#ifdef NON_MATCHING
void func_151A1D0C(u8 *arg0) {
    s16 temp_lo;
    s16 temp_lo_2;
    s16 temp_v1;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v1 = (*(s16 *)((u8 *)arg0 + 0x38));
    temp_v0 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)arg0 + 0x54)) < temp_v1) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (((*(s16 *)((u8 *)temp_v0 + 2)) - temp_v1) * (*(s16 *)((u8 *)temp_v0 + 0)));
    }
    temp_v0_2 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)temp_v0_2 + 0xA)) < temp_v1) {
        temp_lo = ((*(s16 *)((u8 *)temp_v0_2 + 8)) - temp_v1) * (*(s16 *)((u8 *)temp_v0_2 + 6));
        (*(s16 *)((u8 *)arg0 + 0x36)) = temp_lo;
        (*(s16 *)((u8 *)arg0 + 0x34)) = temp_lo;
    }
    if ((*(s16 *)((u8 *)temp_v0_2 + 0xC)) < temp_v1) {
        temp_t7 = (((*(s16 *)((u8 *)arg0 + 0x20)) << 8) | (*(u8 *)((u8 *)arg0 + 0x2C))) + ((((*(s16 *)((u8 *)temp_v0_2 + 0xE)) << 8) | (*(s16 *)((u8 *)temp_v0_2 + 0x14))) * D_800BE9E4);
        (*(s16 *)((u8 *)arg0 + 0x20)) = (s16) (temp_t7 >> 8);
        (*(u8 *)((u8 *)arg0 + 0x2C)) = (u8) temp_t7;
        temp_t6 = (((*(s16 *)((u8 *)arg0 + 0x22)) << 8) | (*(u8 *)((u8 *)arg0 + 0x2E))) + ((((*(s16 *)((u8 *)temp_v0_2 + 0x10)) << 8) | (*(s16 *)((u8 *)temp_v0_2 + 0x16))) * D_800BE9E4);
        (*(s16 *)((u8 *)arg0 + 0x22)) = (s16) (temp_t6 >> 8);
        (*(u8 *)((u8 *)arg0 + 0x2E)) = (u8) temp_t6;
        temp_t5 = (((*(s16 *)((u8 *)arg0 + 0x24)) << 8) | (*(u8 *)((u8 *)arg0 + 0x2D))) + ((((*(s16 *)((u8 *)temp_v0_2 + 0x12)) << 8) | (*(s16 *)((u8 *)temp_v0_2 + 0x18))) * D_800BE9E4);
        (*(s16 *)((u8 *)arg0 + 0x24)) = (s16) (temp_t5 >> 8);
        (*(u8 *)((u8 *)arg0 + 0x2D)) = (u8) temp_t5;
    }
    if ((*(s16 *)((u8 *)arg0 + 0x38)) < (*(s16 *)((u8 *)temp_v0_2 + 0x1A))) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) ((*(s16 *)((u8 *)arg0 + 0x38)) * (*(s16 *)((u8 *)temp_v0_2 + 0x1C)));
    }
    if ((*(s16 *)((u8 *)arg0 + 0x38)) < (*(s16 *)((u8 *)temp_v0_2 + 0x1E))) {
        temp_lo_2 = (*(s16 *)((u8 *)arg0 + 0x38)) * (*(s16 *)((u8 *)temp_v0_2 + 0x20));
        (*(s16 *)((u8 *)arg0 + 0x36)) = temp_lo_2;
        (*(s16 *)((u8 *)arg0 + 0x34)) = temp_lo_2;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1D0C.s")
#endif
void func_151A1E8C(u8 *arg0) {
    typedef struct { s32 w[3]; } Blk12;
    struct260 *temp_v0;
    struct {
        Blk12 unk0;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        s16 unk18;
        s16 unk1A;
        s16 unk1C;
        s16 unk1E;
    } tmp;

    tmp.unk0 = *(Blk12 *)(arg0 + 0x28);
    tmp.unkC = *(f32 *)(arg0 + 0x34);
    tmp.unk10 = 0.0f;
    tmp.unk14 = *(f32 *)(arg0 + 0x38);
    tmp.unk18 = *(s16 *)(arg0 + 0x3E);
    tmp.unk1A = *(s16 *)(arg0 + 0x40);
    tmp.unk1C = *(s16 *)(arg0 + 0x42);
    tmp.unk1E = *(s16 *)(arg0 + 0x44);
    temp_v0 = func_151491F4(*(s16 *)(arg0 + 0x3C), -1, 3, 1, 0, 0x20, arg0[0xC], arg0[0x1]);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x20);
    }
}

#ifdef NON_MATCHING
s32 func_15167D84(s32 **, s32, s32, s32, s32, s32);
extern s32 D_800910E4;

void func_151A1F48(u8 *arg0) {
    struct {
        s16 uA0;
        s16 uA2;
        s16 uA4;
        s16 uA6;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s16 uAE;
        s16 uB0;
        s16 uB2;
        s32 * uB4;
        s32 uB8;
        u8 padBC[0x4];
        s16 uC0;
        s16 uC2;
        s16 uC4;
        s16 uC6;
        s16 uC8;
        s16 uCA;
        s16 uCC;
        u8 padCE[0x2];
        s8 uD0;
        s8 uD1;
        s8 uD2;
        s8 uD3;
        s16 uD4;
        s16 uD6;
        s16 uD8;
        s16 uDA;
        s16 uDC;
        s8 uDE;
        u8 padDF[0x1];
        s8 uE0;
        s8 uE1;
        s8 uE2;
        s8 uE3;
        s8 uE4;
        s8 uE5;
        s8 uE6;
        u8 padE7[0x1];
        u16 uE8;
    } sp;
    f32 sp80;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f30;
    s16 temp_t1;
    s16 temp_t2;
    s16 temp_t5;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_v1;
    u8 *temp_s0;

    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x3C)) * D_800BE9A4));
    temp_s0 = arg0 + 0x28;
    if ((*(f32 *)((u8 *)arg0 + 0x38)) > 1.0f) {
        sp.uE0 = 0xFF;
        sp.uE1 = 0xFF;
        sp.uE2 = 0xFF;
        sp.uE4 = 0;
        sp.uE5 = 0;
        sp.uE6 = 0;
        sp.uD3 = 0x11;
        sp.uE8 = 0x120;
        sp.uB8 = 0xC0001;
        sp.uC0 = 0;
        sp.uB4 = &D_800910E4;
        sp.uCA = 0;
        sp.uD4 = 0;
        sp.uCC = 0;
        sp.uD6 = 0;
        sp.uDE = 0;
        sp.uE3 = 0;
        sp.uD8 = 0x7D0;
        sp.uDA = 0x7D0;
        do {
            temp_s1 = func_150ADA20() & 0xFF;
            temp_s2 = func_150ADA20() & 0xFF;
            temp_f20 = func_151423D8((temp_s1 - 0x40) & 0xFF);
            temp_f22 = func_151423D8(temp_s1 & 0xFF);
            temp_f24 = func_151423D8((temp_s2 - 0x40) & 0xFF);
            temp_f26 = func_151423D8(temp_s2 & 0xFF);
            temp_f2 = func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0xC));
            temp_f12 = temp_f2 * temp_f26;
            temp_f28 = (*(f32 *)((u8 *)temp_s0 + 0)) + (temp_f12 * temp_f20);
            temp_f30 = (*(f32 *)((u8 *)temp_s0 + 4)) - (temp_f2 * temp_f24);
            sp80 = (*(f32 *)((u8 *)temp_s0 + 8)) + (temp_f12 * temp_f22);
            if (func_150ADA20() & 1) {
                sp.uE8 |= 4;
            }
            if (func_150ADA20() & 1) {
                sp.uE8 |= 8;
            }
            temp_t5 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x1A)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x18));
            sp.uC2 = temp_t5;
            temp_t1 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x1E)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x1C));
            sp.uDC = (*(u8 *)((u8 *)D_80090F10 + 0x1D8)) * (0x100 / temp_t5);
            temp_v1 = sp.uDC >> 2;
            temp_t2 = sp.uDC - temp_v1;
            temp_t0 = sp.uDC >> 1;
            sp.uAA = (s16) temp_t0;
            sp.uA4 = temp_t2;
            sp.uA0 = (s16) (0xFF / (s32) (sp.uDC - temp_t2));
            sp.uA2 = sp.uDC;
            sp.uA8 = sp.uDC;
            sp.uA6 = (s16) (temp_t1 / (s32) (sp.uDC - sp.uAA));
            sp.uAC = (s16) temp_v1;
            sp.uC6 = (s16) (s32) temp_f30;
            sp.uAE = (s16) (0xFF / (s16) temp_v1);
            sp.uB0 = (s16) temp_t0;
            sp.uB2 = (s16) (temp_t1 / (s16) temp_t0);
            sp.uC4 = (s16) (s32) temp_f28;
            sp.uC8 = (s16) (s32) sp80;
            sp.uD0 = (s8) (s32) (temp_f28 * 256.0f);
            sp.uD2 = (s8) (s32) (temp_f30 * 256.0f);
            sp.uD1 = (s8) (s32) (sp80 * 256.0f);
            temp_v0 = func_15167D84(&sp.uB4, 0, 0x14, -1, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0x50, &sp.uA0, 0x14);
            }
            (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x10)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A1F48.s")
#endif
void func_151A23E4(u8 *arg0)
{
  s16 temp_lo;
  u8 *new_var;
  s16 temp_lo_2;
  u8 *new_var2;
  s16 temp_v1;
  u8 *temp_v0;
  u8 *temp_v0_2;
  new_var = (0, arg0 + 0x50); // fakematch: (0, x) comma flips commutative operand order
  temp_v1 = *((s16 *) (((u8 *) arg0) + 0x38));
  temp_v0 = new_var;
  if ((*((s16 *) (((u8 *) arg0) + 0x54))) < temp_v1)
  {
    new_var2 = ((u8 *) temp_v0) + 2;
    *((s8 *) (((u8 *) arg0) + 0x3F)) = (s8) ((*((s16 *) (((u8 *) temp_v0) + 0))) * ((*((s16 *) new_var2)) - temp_v1));
  }
  temp_v0_2 = new_var;
  if ((*((s16 *) (((u8 *) temp_v0_2) + 0xA))) < temp_v1)
  {
    temp_lo = (*((s16 *) (((u8 *) temp_v0_2) + 6))) * ((*((s16 *) (((u8 *) temp_v0_2) + 8))) - temp_v1);
    *((s16 *) (((u8 *) arg0) + 0x36)) = temp_lo;
    *((s16 *) (((u8 *) arg0) + 0x34)) = temp_lo;
  }
  if (temp_v1 < (*((s16 *) (((u8 *) temp_v0_2) + 0xC))))
  {
    *((s8 *) (((u8 *) arg0) + 0x3F)) = (s8) ((*((s16 *) (((u8 *) temp_v0_2) + 0xE))) * (0, temp_v1)); // fakematch: (0, x) comma flips commutative operand order
  }
  if (temp_v1 < (*((s16 *) (((u8 *) temp_v0_2) - (-0x10)))))
  {
    temp_lo_2 = (*((s16 *) (((u8 *) arg0) + 0x36)) = (*((s16 *) (((u8 *) temp_v0_2) + 0x12))) * (0, temp_v1)); // fakematch: (0, x) comma flips commutative operand order
    *((s16 *) (((u8 *) arg0) + 0x34)) = temp_lo_2;
  }
}

void func_151A2498(u8 *arg0) {
    typedef struct { s32 w[3]; } Blk12;
    struct {
        Blk12 unk0;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        s16 unk18;
        s16 unk1A;
        s16 unk1C;
        s16 unk1E;
        s16 unk20;
        s16 unk22;
        u8 pad24[4];
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = *(Blk12 *)(arg0 + 0x28);
    tmp.unkC = *(f32 *)(arg0 + 0x34);
    tmp.unk10 = 0.0f;
    tmp.unk14 = *(f32 *)(arg0 + 0x38);
    tmp.unk18 = *(s16 *)(arg0 + 0x3E);
    tmp.unk1A = *(s16 *)(arg0 + 0x40);
    tmp.unk1C = *(s16 *)(arg0 + 0x42);
    tmp.unk1E = *(s16 *)(arg0 + 0x44);
    tmp.unk20 = *(s16 *)(arg0 + 0x46);
    tmp.unk22 = *(s16 *)(arg0 + 0x48);
    temp_v0 = func_151491F4(*(s16 *)(arg0 + 0x3C), -1, 4, 1, 0, 0x24, arg0[0xC], arg0[0x1]);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x24);
    }
}

#ifdef NON_MATCHING
s32 func_15167D84(s32 **, s32, s32, s32, s32, s32);
extern s32 D_800910E4;

void func_151A2564(u8 *arg0) {
    struct {
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s16 uAE;
        s16 uB0;
        s16 uB2;
        s16 uB4;
        s16 uB6;
        s16 uB8;
        s16 uBA;
        s16 uBC;
        s16 uBE;
        s16 uC0;
        s16 uC2;
        s32 * uC4;
        s32 uC8;
        u8 padCC[0x4];
        s16 uD0;
        s16 uD2;
        s16 uD4;
        s16 uD6;
        s16 uD8;
        s16 uDA;
        s16 uDC;
        u8 padDE[0x2];
        s8 uE0;
        s8 uE1;
        s8 uE2;
        s8 uE3;
        s16 uE4;
        s16 uE6;
        s16 uE8;
        s16 uEA;
        s16 uEC;
        s8 uEE;
        u8 padEF[0x1];
        s8 uF0;
        s8 uF1;
        s8 uF2;
        s8 uF3;
        s8 uF4;
        s8 uF5;
        s8 uF6;
        u8 padF7[0x1];
        u16 uF8;
    } sp;
    f32 sp88;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f30;
    s16 temp_a1;
    s16 temp_t0;
    s32 temp_a0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v1;
    u8 *temp_s0;

    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x38)) + ((*(f32 *)((u8 *)arg0 + 0x3C)) * D_800BE9A4));
    temp_s0 = arg0 + 0x28;
    if ((*(f32 *)((u8 *)arg0 + 0x38)) > 1.0f) {
        sp.uF0 = 5;
        sp.uF1 = 0;
        sp.uF2 = 0;
        sp.uF4 = 0;
        sp.uF5 = 0;
        sp.uF6 = 0;
        sp.uE3 = 0x12;
        sp.uF8 = 0x120;
        sp.uC8 = 0xC0001;
        sp.uD0 = 0;
        sp.uC4 = &D_800910E4;
        sp.uDA = 0;
        sp.uE4 = 0;
        sp.uDC = 0;
        sp.uE6 = 0;
        sp.uEE = 0;
        sp.uF3 = 0;
        sp.uEA = 0x7D0;
        sp.uE8 = 0x7D0;
        do {
            temp_s1 = func_150ADA20() & 0xFF;
            temp_s2 = func_150ADA20() & 0xFF;
            temp_f20 = func_151423D8((temp_s1 - 0x40) & 0xFF);
            temp_f22 = func_151423D8(temp_s1 & 0xFF);
            temp_f24 = func_151423D8((temp_s2 - 0x40) & 0xFF);
            temp_f26 = func_151423D8(temp_s2 & 0xFF);
            temp_f2 = func_150ADA68() * (*(f32 *)((u8 *)temp_s0 + 0xC));
            temp_f12 = temp_f2 * temp_f26;
            temp_f28 = (*(f32 *)((u8 *)temp_s0 + 0)) + (temp_f12 * temp_f20);
            temp_f30 = (*(f32 *)((u8 *)temp_s0 + 4)) - (temp_f2 * temp_f24);
            sp88 = (*(f32 *)((u8 *)temp_s0 + 8)) + (temp_f12 * temp_f22);
            if (func_150ADA20() & 1) {
                sp.uF8 |= 4;
            }
            if (func_150ADA20() & 1) {
                sp.uF8 |= 8;
            }
            sp.uD2 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x1A)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x18));
            temp_a1 = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x1E)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x1C));
            sp.uEC = (*(u8 *)((u8 *)D_80090F10 + 0x1D8)) * (0x100 / sp.uD2);
            temp_a0 = sp.uEC >> 2;
            temp_t0 = sp.uEC - temp_a0;
            temp_v1 = sp.uEC >> 1;
            sp.uAC = temp_t0;
            sp.uA8 = (s16) (0xFF / (s32) (sp.uEC - temp_t0));
            sp.uB2 = (s16) temp_v1;
            sp.uAE = (s16) (temp_a1 / (s32) (sp.uEC - (s16) temp_v1));
            sp.uB4 = (s16) temp_v1;
            sp.uB6 = (s16) (0xFF / temp_v1);
            sp.uB8 = (s16) temp_a0;
            sp.uBA = (s16) (0xFF / temp_a0);
            sp.uBC = (s16) temp_v1;
            sp.uAA = sp.uEC;
            sp.uB0 = sp.uEC;
            sp.uBE = (func_150ADA20() % (u32) ((*(s16 *)((u8 *)temp_s0 + 0x22)) + 1)) + (*(s16 *)((u8 *)temp_s0 + 0x20));
            sp.uC0 = (s16) (sp.uEC >> 1);
            sp.uC2 = (func_150ADA20() % 81U) + 0x50;
            sp.uD4 = (s16) (s32) temp_f28;
            sp.uD6 = (s16) (s32) temp_f30;
            sp.uD8 = (s16) (s32) sp88;
            sp.uE0 = (s8) (s32) (temp_f28 * 256.0f);
            sp.uE2 = (s8) (s32) (temp_f30 * 256.0f);
            sp.uE1 = (s8) (s32) (sp88 * 256.0f);
            temp_v0 = func_15167D84(&sp.uC4, 0, 0x1C, -1, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0x50, &sp.uA8, 0x1C);
            }
            (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0x10)) > 1.0f);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2564.s")
#endif
#ifdef NON_MATCHING
void func_151A2A58(u8 *arg0) {
    s16 temp_lo;
    s16 temp_v1;
    s32 temp_lo_2;
    s8 temp_lo_3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v1 = (*(s16 *)((u8 *)arg0 + 0x38));
    temp_v0 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)arg0 + 0x54)) < temp_v1) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (((*(s16 *)((u8 *)temp_v0 + 2)) - temp_v1) * (*(s16 *)((u8 *)temp_v0 + 0)));
    }
    temp_v0_2 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)temp_v0_2 + 0xA)) < temp_v1) {
        temp_lo = ((*(s16 *)((u8 *)temp_v0_2 + 8)) - temp_v1) * (*(s16 *)((u8 *)temp_v0_2 + 6));
        (*(s16 *)((u8 *)arg0 + 0x36)) = temp_lo;
        (*(s16 *)((u8 *)arg0 + 0x34)) = temp_lo;
    }
    if (temp_v1 < (*(s16 *)((u8 *)temp_v0_2 + 0x10))) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (temp_v1 * (*(s16 *)((u8 *)temp_v0_2 + 0x12)));
    }
    if (temp_v1 < (*(s16 *)((u8 *)temp_v0_2 + 0x14))) {
        temp_lo_2 = (*(s16 *)((u8 *)temp_v0_2 + 0x16)) * D_800BE9E4;
        (*(s16 *)((u8 *)arg0 + 0x34)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x34)) + temp_lo_2);
        (*(s16 *)((u8 *)arg0 + 0x36)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x36)) + temp_lo_2);
    }
    if ((*(s16 *)((u8 *)arg0 + 0x38)) < (*(s16 *)((u8 *)temp_v0_2 + 0xC))) {
        (*(s8 *)((u8 *)arg0 + 0x2F)) = 0x13;
        (*(u16 *)((u8 *)arg0 + 0x44)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x44)) | 0x101);
        temp_lo_3 = (*(s16 *)((u8 *)arg0 + 0x38)) * (*(s16 *)((u8 *)temp_v0_2 + 0xE));
        (*(s32 *)((u8 *)arg0 + 0x14)) = 0x520003;
        (*(s8 *)((u8 *)arg0 + 0x42)) = temp_lo_3;
        (*(s8 *)((u8 *)arg0 + 0x41)) = temp_lo_3;
        (*(s8 *)((u8 *)arg0 + 0x40)) = temp_lo_3;
    }
    if ((*(s16 *)((u8 *)arg0 + 0x38)) < (*(s16 *)((u8 *)temp_v0_2 + 0x18))) {
        (*(s16 *)((u8 *)arg0 + 0x32)) = (s16) (*(s16 *)((u8 *)temp_v0_2 + 0x1A));
        (*(s16 *)((u8 *)temp_v0_2 + 0x18)) = -0x270F;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2A58.s")
#endif
#ifdef NON_MATCHING
void func_151A2B90(u8 *arg0) {
    s16 temp_lo;
    s16 temp_v1;
    s32 temp_lo_2;
    s8 temp_lo_3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v1 = (*(s16 *)((u8 *)arg0 + 0x38));
    temp_v0 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)arg0 + 0x54)) < temp_v1) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (((*(s16 *)((u8 *)temp_v0 + 2)) - temp_v1) * (*(s16 *)((u8 *)temp_v0 + 0)));
    }
    temp_v0_2 = arg0 + 0x50;
    if ((*(s16 *)((u8 *)temp_v0_2 + 0xA)) < temp_v1) {
        temp_lo = ((*(s16 *)((u8 *)temp_v0_2 + 8)) - temp_v1) * (*(s16 *)((u8 *)temp_v0_2 + 6));
        (*(s16 *)((u8 *)arg0 + 0x36)) = temp_lo;
        (*(s16 *)((u8 *)arg0 + 0x34)) = temp_lo;
    }
    if (temp_v1 < (*(s16 *)((u8 *)temp_v0_2 + 0x10))) {
        (*(s8 *)((u8 *)arg0 + 0x3F)) = (s8) (temp_v1 * (*(s16 *)((u8 *)temp_v0_2 + 0x12)));
    }
    if (temp_v1 < (*(s16 *)((u8 *)temp_v0_2 + 0x14))) {
        temp_lo_2 = (*(s16 *)((u8 *)temp_v0_2 + 0x16)) * D_800BE9E4;
        (*(s16 *)((u8 *)arg0 + 0x34)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x34)) + temp_lo_2);
        (*(s16 *)((u8 *)arg0 + 0x36)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x36)) + temp_lo_2);
    }
    if ((*(s16 *)((u8 *)arg0 + 0x38)) < (*(s16 *)((u8 *)temp_v0_2 + 0x18))) {
        (*(s16 *)((u8 *)arg0 + 0x32)) = (s16) (*(s16 *)((u8 *)temp_v0_2 + 0x1A));
        (*(s16 *)((u8 *)temp_v0_2 + 0x18)) = -0x270F;
    }
    temp_lo_3 = (*(s16 *)((u8 *)arg0 + 0x38)) * (*(s16 *)((u8 *)temp_v0_2 + 0xE));
    (*(s8 *)((u8 *)arg0 + 0x42)) = temp_lo_3;
    (*(s8 *)((u8 *)arg0 + 0x41)) = temp_lo_3;
    (*(s8 *)((u8 *)arg0 + 0x40)) = temp_lo_3;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2B90.s")
#endif
#ifdef NON_MATCHING
/* P160 */
s32 func_151308E4(void *, s32, s32, u8, s32);
s32 func_150ADA20(void);

typedef struct { f32 x, y, z; } V3_151A2C9C;
typedef struct {
    s32 u00;          /* 0x00: 0x200005 */
    s32 u04;
    s16 u08;          /* 0x08: 0x5203 */
    s16 u0A;
    s32 u0C;
    s32 u10;
    u8 color[3];      /* 0x14 */
    u8 u17[4];        /* 0x17: 0xFF */
    u8 u1B;
    u8 u1C;           /* 0xFF */
    u8 u1D;           /* 0x27 */
    s16 period;       /* 0x1E */
    s16 step;         /* 0x20: 255 / period */
    s16 u22;          /* 1 */
    f32 u24;          /* 1.0f */
    f32 scale[2];     /* 0x28 */
    V3_151A2C9C pos;  /* 0x30 */
    V3_151A2C9C vel;  /* 0x3C */
    V3_151A2C9C acc;  /* 0x48 */
    f32 u54;
    s32 flags;        /* 0x58 */
    s32 pad5C;
    u8 u60[6];        /* 7, 2, 0x11, 0xFF, 0xFF, 2 */
} Blk_151A2C9C;

typedef struct {
    f32 u0;
    s16 fadePeriod;   /* 0x4 */
    s16 fadeStep;     /* 0x6: 255 / fadePeriod */
    s16 u8;
    s8 uA;
} Extra_151A2C9C;

// particle_puff_spawn: spawns one particle (func_151308E4 class 1 / 0x10) at pos with velocity vel and
// acceleration acc; the two fade periods are clamped to at least 1 and give 255 / period steps, the flags get
// random 0x40 / 0x80 bits; ex bytes 0..7 go to the particle at +0xA8 and bytes 4..11 at +0xB0 (overlapping copies; byte 11 is padding). Returns 0.
s32 func_151A2C9C(f32 *pos, f32 *vel, f32 *acc, f32 arg3, f32 arg4, f32 scale, s32 arg6, s32 arg7, s32 period,
                  s32 fadePeriod, s32 argA, s32 argB, s32 r, s32 g, s32 b, s32 argF, s32 arg10) {
    Blk_151A2C9C blk;
    Extra_151A2C9C ex;
    s32 bit40;
    s32 bit80;
    u8 *p;

    period = (s16)period;
    fadePeriod = (s16)fadePeriod;
    if (period <= 0) {
        period = 1;
    }
    if (fadePeriod <= 0) {
        fadePeriod = 1;
    }
    ex.u0 = arg3;
    ex.fadePeriod = fadePeriod;
    ex.fadeStep = 255 / fadePeriod;
    ex.u8 = argA;
    ex.uA = argB;
    blk.u00 = 0x200005;
    blk.u04 = 0;
    blk.u08 = 0x5203;
    blk.u0A = arg6;
    blk.u0C = 0;
    blk.u10 = 0;
    blk.color[0] = r;
    blk.color[1] = g;
    blk.color[2] = b;
    blk.u17[0] = 0xFF;
    blk.u17[1] = 0xFF;
    blk.u17[2] = 0xFF;
    blk.u17[3] = 0xFF;
    blk.u1B = arg7;
    blk.u1C = 0xFF;
    blk.u1D = 0x27;
    blk.period = period;
    blk.step = 255 / period;
    blk.u22 = 1;
    blk.u24 = 1.0f;
    blk.scale[0] = scale;
    blk.scale[1] = scale;
    blk.pos = *(V3_151A2C9C *)pos;
    blk.vel = *(V3_151A2C9C *)vel;
    blk.acc = *(V3_151A2C9C *)acc;
    blk.u54 = arg4;
    bit40 = (func_150ADA20() & 1) ? 0x40 : 0;
    bit80 = (func_150ADA20() & 1) ? 0x80 : 0;
    blk.flags = bit80 | 7 | bit40 | 0x80D200;
    blk.u60[0] = 7;
    blk.u60[1] = 2;
    blk.u60[2] = 0x11;
    blk.u60[3] = 0xFF;
    blk.u60[4] = 0xFF;
    blk.u60[5] = 2;
    p = (u8 *)func_151308E4(&blk, 1, 0x10, argF, arg10);
    if (p != NULL) {
        memcpy(p + 0xA8, &ex.u0, 8);
        memcpy(p + 0xB0, &ex.fadePeriod, 8);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2C9C.s")
#endif
#ifdef NON_MATCHING
/* P146 */
extern void (*D_8008FC80[])(u8 *, s32, s32, s32);
s32 func_15131C7C(u8 *, s32);
// particle_timed_event_update: particle update handler 17 (func_1513095C). While the age (+0x1A) is below +0xB0
// the alpha +0x2C ramps as age * +0xB2. While the age (+0x1A, counting down) is <= the trigger time +0xB4 (-1 = none) the event
// D_8008FC80[+0xB6] (-1 = none) is called once with (particle, trigger time, age, -1) and the trigger cleared;
// events are suppressed while D_800BE616 is set. Then the common update func_15131C7C(particle, arg) runs and its
// result is returned.
s32 func_151A2F10(u8 *part, s32 arg) {
    s16 age = *(s16 *)(part + 0x1A);
    s16 when;
    s8 event;

    if (age < *(s16 *)(part + 0xB0)) {
        part[0x2C] = age * *(s16 *)(part + 0xB2);
    }
    if (D_800BE616 == 0) {
        when = *(s16 *)(part + 0xB4);
        event = *(s8 *)(part + 0xB6);
        if (when != -1 && event != -1 && when >= age) {
            D_8008FC80[event](part, when, age, -1);
            *(s16 *)(part + 0xB4) = -1;
        }
    }
    return func_15131C7C(part, arg);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A2F10.s")
#endif

s32 func_151A31D4(s32, s32, s16, s16, f32, f32, f32, s32, f32, f32, f32, f32, s16, s16, s16, s16, s16, s16, s8, u8, s32, u8);

s32 func_151A2FC4(s32 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA, s16 argB, s16 argC, s16 argD, s16 argE, s16 argF, s16 arg10, s8 arg11, u8 arg12, s32 arg13) {
    return func_151A31D4(arg0, 0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB, argC, argD, argE, argF, arg10, arg11, arg12, arg13, 1);
}

#ifdef NON_MATCHING
void func_151A3084(s32 arg0, s32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, s16 arg9, s16 argA, s16 argB, s16 argC, s16 argD, s16 argE, s8 argF, u8 arg10, s32 arg11) {
    func_151A31D4(arg0, arg1, 0, 0, 0.0f, arg2, arg3, arg4, arg5, arg6, arg7, arg8, (s16) (s32) arg9, (s16) (s32) argA, (s16) (s32) argB, (s16) (s32) argC, (s16) (s32) argD, (s16) (s32) argE, (s8) (s32) argF, (u8) (s32) arg10, arg11, 0U);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3084.s")
#endif
#ifdef NON_MATCHING
/* P160: same signature as func_151A3180 (func_151A31D4 calls either through one pointer; arg3 is the speed it ignores) */
// accel_scaled_copy: out = base * (1 - t) (func_151A31D4's acceleration without a direction)
void func_151A3134(f32 *arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 *arg5) {
#else
void func_151A3134(f32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 *arg5) {
#endif
    f32 temp_f0 = 1.0f - arg4;

    arg5[0] = arg0[0] * temp_f0;
    arg5[1] = arg0[1] * temp_f0;
    arg5[2] = arg0[2] * temp_f0;
}

s32 func_15143794(s16, s16, f32, s32);
void func_151A3180(s32 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, s32 arg5) {
    func_15143794(arg1, arg2, (1.0f - arg4) * arg3, arg5);
}

#ifdef NON_MATCHING
/* P160 */
extern u8 D_8008FC88[]; /* 4 colours, 3 bytes each */
typedef struct { u8 b[12]; } Blk12_151A31D4;
s32 func_151A2C9C(f32 *, f32 *, f32 *, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_151A3134(f32 *arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 *arg5);
void func_151A3180(s32 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, s32 arg5);

// particle_burst_spawn: spawns `count` particles (func_151A2C9C) at pos. For particle i (t = i / count) the
// velocity is a random direction (func_15143794) of random speed up to speedMax, the acceleration comes from
// `accel` (scaled by 1 - t) through func_151A3180 (useDir) or func_151A3134, the colour is one of the 4
// D_8008FC88 colours, about 8% of the particles get 0x19 as extra value (else -1), and the lives / periods are
// random within the given ranges. Returns 0 (the N64 code leaves func_151A2C9C's 0 in v0).
s32 func_151A31D4(s32 pos, s32 accel, s16 dirA, s16 dirB, f32 accelSpeed, f32 scaleBase, f32 scaleSlope, s32 count,
                  f32 speedMax, f32 arg9, f32 lifeBase, f32 lifeRange, s16 periodBase, s16 periodRange,
                  s16 fadeBase, s16 fadeRange, s16 period2, s16 fade2, s8 arg12, u8 arg13, s32 arg14, u8 useDir) {
    void (*accelFn)(f32 *, s16, s16, f32, f32, f32 *);
    u8 colors[12];
    f32 acc[3];
    f32 vel[3];
    s16 minPeriod;
    s16 period;
    f32 t;
    f32 step;
    f32 lifeRand;
    s32 a;
    s32 b;
    s32 c;
    s32 extra;

    if (useDir != 0) {
        accelFn = (void (*)(f32 *, s16, s16, f32, f32, f32 *))func_151A3180;
    } else {
        accelFn = func_151A3134;
    }
    minPeriod = (period2 < fade2) ? period2 : fade2;
    t = 0.0f;
    step = 1.0f / count;
    for (; count != 0; count--) {
        period = (u32)func_150ADA20() % (periodRange + 1) + periodBase;
        a = func_150ADA20();
        b = func_150ADA20();
        func_15143794((u8)a, (u8)b, func_150ADA68() * speedMax, (s32)vel);
        accelFn((f32 *)accel, dirA, dirB, accelSpeed, t, acc);
        *(Blk12_151A31D4 *)colors = *(Blk12_151A31D4 *)D_8008FC88;
        c = func_150ADA20() & 3;
        lifeRand = func_150ADA68();
        b = func_150ADA20();
        extra = (func_150ADA68() < 0.0802f) ? 0x19 : -1;
        func_151A2C9C((f32 *)pos, vel, acc, arg9, lifeRand * lifeRange + lifeBase, scaleSlope * t + scaleBase,
                      period + minPeriod, (u32)b % (fadeRange + 1) + fadeBase, period2, fade2, extra, arg12,
                      colors[c * 3 + 0], colors[c * 3 + 1], colors[c * 3 + 2], arg13, arg14);
        t += step;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A31D4.s")
#endif

#ifdef NON_MATCHING
s32 func_151530A8(s32 *, u8, s32);

void func_151A34BC(u8 *arg0) {
    struct {
        s32 u1C;
        s32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s32 u50;
        s32 u54;
        s16 u58;
        s16 u5A;
        s16 u5C;
        s8 u5E;
        s8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        s8 u65;
        s8 u66;
        s8 u67;
        s8 u68;
        s8 u69;
        s8 u6A;
        s8 u6B;
        s8 u6C;
        s8 u6D;
        s8 u6E;
        s8 u6F;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
        s8 u74;
        u8 pad75[0x3];
        s32 u78;
        s32 u7C;
        s16 u80;
        s16 u82;
        s16 u84;
        s8 u86;
        u8 pad87[0x1];
        f32 u88;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
    } sp;

    sp.u1C = 8;
    sp.u20 = 6;
    (*(f32 *)((u8 *)(&sp.u24) + 0)) = (*(f32 *)((u8 *)arg0 + 0x40));
    (*(s32 *)((u8 *)(&sp.u24) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x44));
    (*(s32 *)((u8 *)(&sp.u24) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x48));
    if ((*(s32 *)((u8 *)arg0 + 0x68)) & 0x1000) {
        sp.u24 += (*(f32 *)((u8 *)arg0 + 0x4C));
        sp.u28 += (*(f32 *)((u8 *)arg0 + 0x50));
        sp.u2C += (*(f32 *)((u8 *)arg0 + 0x54));
    }
    sp.u30 = ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x3C))) * 0.5f * 0.02f;
    sp.u4A = 0xFF;
    sp.u4C = -0x40;
    sp.u54 = 1;
    sp.u58 = 0x11;
    sp.u4E = 0x56;
    sp.u50 = 3;
    sp.u5A = 0x12;
    sp.u5C = 1;
    sp.u5E = 4;
    sp.u5F = 2;
    sp.u60 = 3;
    sp.u64 = 0xFF;
    sp.u66 = 0x37;
    sp.u61 = 0xFF;
    sp.u62 = 0xC8;
    sp.u63 = 0xC8;
    sp.u67 = 0x37;
    sp.u69 = 0xFF;
    sp.u6A = 0xFF;
    sp.u6B = 0xFF;
    sp.u6C = 0xFF;
    sp.u71 = 0xFF;
    sp.u34 = ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x3C))) * 0.5f * 0.035299998f;
    sp.u48 = 0;
    sp.u65 = 0;
    sp.u68 = 0;
    sp.u6D = 0;
    sp.u6E = 0;
    sp.u6F = 0;
    sp.u70 = 0;
    sp.u72 = 0;
    sp.u73 = 1;
    sp.u74 = 0x24;
    sp.u78 = 0x200005;
    sp.u7C = 0x60600;
    sp.u80 = 7;
    sp.u82 = 0x24;
    sp.u84 = 1;
    sp.u86 = 0;
    sp.u8C = -1;
    sp.u8D = 0;
    sp.u8E = -1;
    sp.u8F = -1;
    sp.u38 = -0.268f;
    sp.u40 = 8.0f;
    sp.u44 = 10.0f;
    sp.u3C = 0.0f;
    sp.u88 = 1.0f;
    func_151530A8(&sp.u1C, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A34BC.s")
#endif
#ifdef NON_MATCHING
s32 func_151530A8(s32 *, u8, s32);

void func_151A3700(u8 *arg0) {
    struct {
        s32 u1C;
        s32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        s32 u50;
        s32 u54;
        s16 u58;
        s16 u5A;
        s16 u5C;
        s8 u5E;
        s8 u5F;
        s8 u60;
        s8 u61;
        s8 u62;
        s8 u63;
        s8 u64;
        s8 u65;
        s8 u66;
        s8 u67;
        s8 u68;
        s8 u69;
        s8 u6A;
        s8 u6B;
        s8 u6C;
        s8 u6D;
        s8 u6E;
        s8 u6F;
        s8 u70;
        s8 u71;
        s8 u72;
        s8 u73;
        s8 u74;
        u8 pad75[0x3];
        s32 u78;
        s32 u7C;
        s16 u80;
        s16 u82;
        s16 u84;
        s8 u86;
        u8 pad87[0x1];
        f32 u88;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
    } sp;

    sp.u1C = 0xA;
    sp.u20 = 0xF;
    (*(f32 *)((u8 *)(&sp.u24) + 0)) = (*(f32 *)((u8 *)arg0 + 0x40));
    (*(s32 *)((u8 *)(&sp.u24) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x44));
    (*(s32 *)((u8 *)(&sp.u24) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x48));
    if ((*(s32 *)((u8 *)arg0 + 0x68)) & 0x1000) {
        sp.u24 += (*(f32 *)((u8 *)arg0 + 0x4C));
        sp.u28 += (*(f32 *)((u8 *)arg0 + 0x50));
        sp.u2C += (*(f32 *)((u8 *)arg0 + 0x54));
    }
    sp.u30 = ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x3C))) * 0.5f * 0.0212f;
    sp.u4A = 0xFF;
    sp.u4C = -0x40;
    sp.u54 = 2;
    sp.u58 = 0xF;
    sp.u4E = 0x56;
    sp.u50 = 3;
    sp.u5A = 0x1E;
    sp.u5C = 1;
    sp.u5E = 4;
    sp.u5F = 2;
    sp.u60 = 3;
    sp.u64 = 0xFF;
    sp.u66 = 0x37;
    sp.u61 = 0xFF;
    sp.u62 = 0xC8;
    sp.u63 = 0xC8;
    sp.u67 = 0x37;
    sp.u69 = 0xFF;
    sp.u6A = 0xFF;
    sp.u6B = 0xFF;
    sp.u6C = 0xFF;
    sp.u71 = 0xFF;
    sp.u34 = ((*(f32 *)((u8 *)arg0 + 0x38)) + (*(f32 *)((u8 *)arg0 + 0x3C))) * 0.5f * 0.0532f;
    sp.u48 = 0;
    sp.u65 = 0;
    sp.u68 = 0;
    sp.u6D = 0;
    sp.u6E = 0;
    sp.u6F = 0;
    sp.u70 = 0;
    sp.u72 = 0;
    sp.u73 = 1;
    sp.u74 = 0x24;
    sp.u78 = 0x200005;
    sp.u7C = 0x60600;
    sp.u80 = 0xF;
    sp.u82 = 0x11;
    sp.u84 = 1;
    sp.u86 = 0;
    sp.u8C = -1;
    sp.u8D = 0;
    sp.u8E = -1;
    sp.u8F = -1;
    sp.u40 = 8.0f;
    sp.u44 = 8.0f;
    sp.u38 = -1.031f;
    sp.u3C = 0.0f;
    sp.u88 = 1.0f;
    func_151530A8(&sp.u1C, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CE7D0/func_151A3700.s")
#endif