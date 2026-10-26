#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// some mips3/64bit stuff going on here

#ifdef NON_MATCHING
/* was func_150AD9A0 */
s32 approx_dist3_int(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;

    temp_v0 = arg0 >> 0x1F;
    var_a0 = (arg0 ^ temp_v0) - temp_v0;
    temp_v0_2 = arg1 >> 0x1F;
    var_a1 = (arg1 ^ temp_v0_2) - temp_v0_2;
    temp_v0_3 = arg2 >> 0x1F;
    var_a2 = (arg2 ^ temp_v0_3) - temp_v0_3;
    if (var_a0 < var_a1) {
        temp_a1 = var_a1 ^ var_a0;
        var_a0 ^= temp_a1;
        var_a1 = temp_a1 ^ var_a0;
    }
    temp_v0_4 = var_a2 ^ var_a0;
    if (var_a0 < var_a2) {
        var_a0 ^= temp_v0_4;
        var_a2 = temp_v0_4 ^ var_a0;
    }
    if (var_a1 < var_a2) {
        temp_a2 = var_a2 ^ var_a1;
        var_a1 ^= temp_a2;
        var_a2 = temp_a2 ^ var_a1;
    }
    return ((u32) (var_a1 * 0xB) >> 5) + (((u32) var_a2 >> 2) + var_a0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAE50/approx_dist3_int.s")
#endif
// NON-MATCHING: I am nothing without mip2c.
// s32 approx_dist3_int(s32 arg0, s32 arg1, s32 arg2) {
//     s32 v0;
//     s32 tmp0 = (s32)arg0; // = arg0;
//     s32 tmp1 = (s32)arg1;
//     s32 tmp2 = (s32)arg2;
//
//     // /* AD9A0 850AD9A0 000417C3 */  sra        $v0, $a0, 0x1f
//     // /* AD9A4 850AD9A4 00822026 */  xor        $a0, $a0, $v0
//     // /* AD9A8 850AD9A8 00822022 */  sub        $a0, $a0, $v0
//     v0 = (tmp0 >> 31);
//     tmp0 = (tmp0 ^ v0) - v0;
//     // tmp0 =   tmp0 - v0;
//     // tmp0 = tmp0 - v0;
//     // /* AD9AC 850AD9AC 000517C3 */  sra        $v0, $a1, 0x1f
//     // /* AD9B0 850AD9B0 00A22826 */  xor        $a1, $a1, $v0
//     // /* AD9B4 850AD9B4 00A22822 */  sub        $a1, $a1, $v0
//     v0 = arg1 >> 31;
//     tmp1 = tmp1 ^ v0;
//     tmp1 = tmp1 - v0;
//
//     // /* AD9B8 850AD9B8 000617C3 */  sra        $v0, $a2, 0x1f
//     // /* AD9BC 850AD9BC 00C23026 */  xor        $a2, $a2, $v0
//     // /* AD9C8 850AD9C8 00C23022 */   sub       $a2, $a2, $v0
//     v0 = tmp2 >> 31;
//     tmp2 = tmp2 ^ v0;
//     // tmp2 = tmp2 - v0;
//
//     // /* AD9C0 850AD9C0 0085082A */  slt        $at, $a0, $a1
//     // /* AD9C4 850AD9C4 10200004 */  beqz       $at, .L850AD9D8
//     if (tmp0 < tmp1)
//     {
//         // .L850AD9D8:
//         // /* AD9CC 850AD9CC 00A42826 */  xor        $a1, $a1, $a0
//         // /* AD9D0 850AD9D0 00852026 */  xor        $a0, $a0, $a1
//         // /* AD9D4 850AD9D4 00A42826 */  xor        $a1, $a1, $a0
//         v0 = tmp1 ^ tmp0;
//         tmp0 = tmp0 ^ v0;
//         tmp1 = tmp1 ^ tmp0;
//     }
//     // /* AD9E0 850AD9E0 00C41026 */   xor       $v0, $a2, $a0
//     // /* AD9E4 850AD9E4 00822026 */  xor        $a0, $a0, $v0
//     // /* AD9E8 850AD9E8 00443026 */  xor        $a2, $v0, $a0
//     v0 = tmp2 ^ tmp0;
//     tmp0 = tmp0 ^ v0;
//     tmp2 = v0 ^ tmp0;
//     // /* AD9D8 850AD9D8 0086082A */  slt        $at, $a0, $a2
//     // /* AD9DC 850AD9DC 10200003 */  beqz       $at, .L850AD9EC
//     if (tmp0 < tmp2)
//     {
//         // .L850AD9EC:
//         // /* AD9EC 850AD9EC 00A6082A */  slt        $at, $a1, $a2
//         // /* AD9F0 850AD9F0 10200004 */  beqz       $at, .L850ADA04
//         if (tmp1 - tmp2 != 0)
//         {
//             v0 = 0xb; // ??
//             tmp2 = tmp2 ^ tmp1;
//             tmp1 = tmp1 ^ tmp2;
//             tmp2 = tmp2 ^ tmp1;
//         }
//
//         // /* AD9F4 850AD9F4 2402000B */   addiu     $v0, $zero, 0xb
//         // /* AD9F8 850AD9F8 00C53026 */  xor        $a2, $a2, $a1
//         // /* AD9FC 850AD9FC 00A62826 */  xor        $a1, $a1, $a2
//         // /* ADA00 850ADA00 00C53026 */  xor        $a2, $a2, $a1
//
//     }
//     // .L850ADA04:
//     // /* ADA04 850ADA04 00A20018 */  mult       $a1, $v0
//     tmp1 = tmp1 * v0;
//     // /* ADA08 850ADA08 00063082 */  srl        $a2, $a2, 2
//     tmp2 = tmp2 >> 2;
//     // /* ADA0C 850ADA0C 00C43020 */  add        $a2, $a2, $a0
//     tmp2 = tmp2 + tmp0;
//     // /* ADA10 850ADA10 00001012 */  mflo       $v0
//     // /* ADA14 850ADA14 00021142 */  srl        $v0, $v0, 5
//     v0 = v0 << 5;
//     // /* ADA18 850ADA18 03E00008 */  jr         $ra
//     // /* ADA1C 850ADA1C 00461020 */   add       $v0, $v0, $a2
//     v0 = v0 + tmp2;
//     return v0;
// }

// well this is a bastard
#ifdef NON_MATCHING
extern s64 D_80088950;

/* random_int: (P106) one step of the 64-bit shift-register generator in D_80088950 (MIPS III ld / sd; the same step
 * as random_float), the low word of the new state returned. Model-checked (docs/port/sessions/p106/ada20). */
/* was func_150ADA20 */
s32 random_int(void) {
    u64 x = (u64) D_80088950;
    u64 t;

    t = ((x << 63) >> 31) | ((x << 31) >> 32);
    t ^= (x << 44) >> 32;
    x = ((t >> 20) & 0xFFF) ^ t;
    D_80088950 = (s64) x;
    return (s32) x;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAE50/random_int.s")
#endif
// s32 random_int() {
//     // u32 tmp1;
//     u64 tmp2;
//     u64 tmp0;
//
//     // /* ADA20 850ADA20 3C048009 */  lui        $a0, 0x8009
//     // /* ADA24 850ADA24 DC8485B0 */  ld         $a0, -0x7a50($a0)
//     tmp0 = D_800885B0;
//     // /* ADA28 850ADA28 000437FC */  dsll32     $a2, $a0, 0x1f
//     // tmp2 = tmp0 << 63;
//     // /* ADA2C 850ADA2C 000637FA */  dsrl       $a2, $a2, 0x1f
//     tmp2 = (u32) tmp0; //tmp2 >> 31;
//     // /* ADA30 850ADA30 00042FF8 */  dsll       $a1, $a0, 0x1f
//     // tmp1 = tmp0; // << 31;
//     // /* ADA34 850ADA34 0005283E */  dsrl32     $a1, $a1, 0
//     // tmp1 = tmp1 >> 0 + 32;
//     // /* ADA38 850ADA38 00C53025 */  or         $a2, $a2, $a1
//     tmp2 = tmp2 | (u32)(tmp0 >> 31) ;
//     // /* ADA3C 850ADA3C 0004233C */  dsll32     $a0, $a0, 0xc
//     tmp0 = tmp0 << 44;
//     // /* ADA40 850ADA40 0004203E */  dsrl32     $a0, $a0, 0
//     tmp0 = tmp0 >> 32;
//     // /* ADA44 850ADA44 00C43026 */  xor        $a2, $a2, $a0
//     tmp2 = tmp2 ^ tmp0;
//     // /* ADA48 850ADA48 0006253A */  dsrl       $a0, $a2, 0x14
//     tmp0 = tmp2 >> 20;
//     // /* ADA4C 850ADA4C 30840FFF */  andi       $a0, $a0, 0xfff
//     tmp0 = tmp0 & 0xfff;
//     // /* ADA50 850ADA50 00862026 */  xor        $a0, $a0, $a2
//     tmp0 = tmp0 ^ tmp2;
//     // /* ADA54 850ADA54 3C018009 */  lui        $at, 0x8009
//     // /* ADA58 850ADA58 FC2485B0 */  sd         $a0, -0x7a50($at)
//     // D_800885B0 = tmp0;
//     ///* ADA60 850ADA60 03E00008 */  jr         $ra
//     * (u64 *) 0x800885B0 = tmp0;
//     return tmp0;
//     // /* ADA5C 850ADA5C 0004103C */  dsll32     $v0, $a0, 0
//     // tmp0 = tmp0 << 0 + 32;
//     // /* ADA64 850ADA64 0002103F */   dsra32    $v0, $v0, 0
//     // tmp0 = tmp0 >> 0 + 32;
// }

#ifdef NON_MATCHING
extern s64 D_80088950;

/* P95: random float in [0, 1]: one step of the 64-bit shift-register generator in D_80088950 (as random_int),
 * low 16 bits of the new state times 1/65535 (rodata D_8009FB10 = 0x37800080). */
/* was func_150ADA68 */
f32 random_float(void) {
    u64 x = (u64) D_80088950;
    u64 t;

    t = ((x << 63) >> 31) | ((x << 31) >> 32);
    t ^= (x << 44) >> 32;
    x = ((t >> 20) & 0xFFF) ^ t;
    D_80088950 = (s64) x;
    return (f32) (s32) (x & 0xFFFF) * 1.5259022e-05f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAE50/random_float.s")
#endif

#ifdef NON_MATCHING
extern s64 D_80088950;

/* MIPS III: a 64-bit add of the (sign-extended) argument */
/* was func_150ADACC */
void random_seed(s32 arg0) {
    D_80088950 = (s64)arg0 + 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAE50/random_seed.s")
#endif
// NON-MATCHING: hand-written function
// void random_seed(s64 arg0) {
//     D_800885B0 = arg0 + 1;
// }
