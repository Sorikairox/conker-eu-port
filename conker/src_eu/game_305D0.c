#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// what is this loop doing?
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003120.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_150031EC.s")

s32 func_150034B4(void) {
      s32 i;

      for (i = 0; i < 7764; i++) {
          D_800B0E58[i] = -1;
          D_800BC448[i] = 0;
      }

      D_800D9F58 = 0xFFFF; // -1 s16?
      D_800D9F5C = -1;

      if ((D_800BE9F0 != 1) && (D_800BE9F0 != 50)) {
          D_800D9F60 = 0;
      } else {
          D_800D9F60 = 1;
      }
}

#ifdef NON_MATCHING
u8 *allocate_memory(s32, s32, s32, s32);
void func_10004074(s32);
extern u8 D_1A3B40[];
extern u16 D_800920D0[];
extern s16 D_800B8BB8[];

/* build a table of 16-bit words read from ROM: for each entry, DMA 16 bytes at the (even-aligned) ROM
   position, take the big-endian halfword at offset 2 from the real (possibly odd) position, then advance
   by the entry's length */
void func_15003570(void) {
    u8 *buf = allocate_memory(0x10, 1, 2, 0);
    u32 rom = (u32)D_1A3B40;
    u16 *len = D_800920D0;
    s16 *out = D_800B8BB8;
    s32 odd;

    do {
        if (rom & 1) {
            rom--;
            odd = 1;
        } else {
            odd = 0;
        }
        func_10004514(rom, buf, 0x10, 1);
        *out++ = (buf[odd + 2] << 8) | buf[odd + 3];
        rom += *len++ + odd;
    } while (out != (s16 *)D_800BC860);
    func_10004074((s32)buf);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003570.s")
#endif
// NON-MATCHING: something along these lines
// void func_15003570(void) {
//     s32 temp_s4;
//     s32 phi_s0;
//     s32 phi_s1;
//
//     s32 i;
//     u8 *temp_v0;
//     s16 *phi_s2;
//     s16 *phi_s3;
//
//     temp_s4 = allocate_memory(16, 1, 2, 0);
//
//     phi_s0 = 0x1A37E0; // 1718240
//     phi_s2 = D_80091D20;
//     phi_s3 = D_800B87A0;
//
//     for (i = 0; i < 7764; i++) {
//         if ((phi_s0 & 1) != 0) {
//             phi_s0 = phi_s0 - 1;
//             phi_s1 = 1;
//         } else {
//             phi_s1 = 0;
//         }
//         func_10004514(phi_s0, temp_s4, 16, 1);
//         temp_v0 = temp_s4 + phi_s1;
//         phi_s2[i] = (*temp_v0 << 24) + (*(temp_v0 + 1) << 16) + (*(temp_v0 + 2) << 8) + *(temp_v0 + 3);
//         phi_s0 = phi_s3[i];
//     }
//
//     func_10004074(temp_s4);
// }

#ifdef NON_MATCHING
s32 func_15001460(s32);
void func_15002754(void);
s32 func_15002878(void);
void func_1510F800(s32);
extern s32 D_800D304C;
extern s8 D_800D3088;
extern s32 D_800D3720;
extern s32 D_800D3A8C;
extern s32 D_800DC26C;

void func_15003668(s32 arg0) {
    s32 temp_s3;
    s32 temp_t7;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    D_800DBE62 = 0;
    func_15001970();
    D_800D3088 = 0;
    func_150026C4(0);
    func_15002724((*(s32 *)((u8 *)D_800B0E00 + 0)));
    func_15002754();
    func_15001460((*(s32 *)((u8 *)D_800B0E00 + 0)));
    func_150026E8(0);
    func_150026C4(1);
    func_15002724((*(s32 *)((u8 *)D_800B0E00 + 0xC)));
    func_15002754();
    func_15001460((*(s32 *)((u8 *)D_800B0E00 + 0xC)));
    func_150026E8(1);
    func_150026C4(2);
    var_s1 = 0;
    var_s0 = 0;
    if (D_800DC320 > 0) {
        do {
            temp_v0 = &D_800DBEF4->pad[var_s0];
            if (((*(u8 *)((u8 *)temp_v0 + 0x4F)) & 0x60) != 0x20) {
                func_15002724((*(s32 *)((u8 *)temp_v0 + 0x1C)));
            }
            var_s1 += 1;
            var_s0 += 0xA0;
        } while (var_s1 < D_800DC320);
        var_s1 = 0;
    }
    func_15002754();
    D_800D3088 = 1;
    D_800D304C = 0;
    var_s0_2 = 0;
    if (D_800DC320 > 0) {
        do {
            temp_v0_2 = &D_800DBEF4->pad[var_s0_2];
            if (((*(u8 *)((u8 *)temp_v0_2 + 0x4F)) & 0x60) != 0x20) {
                temp_s3 = D_800DBE38;
                (*(s16 *)((u8 *)temp_v0_2 + 0x58)) = (s16) temp_s3;
                func_15001460((*(s32 *)((u8 *)(&D_800DBEF4->pad[var_s0_2]) + 0x1C)));
                (*(s16 *)((u8 *)(&D_800DBEF4->pad[var_s0_2]) + 0x56)) = (s16) (D_800DBE38 - temp_s3);
            } else {
                (*(s16 *)((u8 *)temp_v0_2 + 0x58)) = 0;
                (*(s16 *)((u8 *)(&D_800DBEF4->pad[var_s0_2]) + 0x56)) = 0;
            }
            var_s1 += 1;
            var_s0_2 += 0xA0;
        } while (var_s1 < D_800DC320);
    }
    func_150026E8(2);
    D_800D3088 = 0;
    (*(s32 *)((u8 *)(&D_800D3720) + 0)) = 0;
    (*(s32 *)((u8 *)(&D_800D3720) + 4)) = (s32) (D_800DC26C << 8);
    func_1510F800(0);
    temp_t7 = (func_15002878() + 7) & ~7;
    D_800D3668 = (s32) D_8003809C;
    D_800D3A8C = D_8003809C + temp_t7;
    func_1510F800(2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003668.s")
#endif
// NON-MATCHING: 40% there
// void func_15003668(s32 arg0) {
//     struct131 *temp_v0_2;
//     s32 temp_t7;
//     s32 i;
//     s32 tmp0;
//
//     D_800DBE62 = (u8)0;
//     func_15001970();
//     D_800D2C68 = (u8)0;
//     func_150026C4(0);
//     func_15002724(D_800B0E00[0]); // ->unk0
//     func_15002754();
//     func_15001460(D_800B0E00[0]); // ->unk0
//     func_150026E8(0);
//     func_150026C4(1);
//     func_15002724(D_800B0E00[3]);
//     func_15002754();
//     func_15001460(D_800B0E00[3]);
//     func_150026E8(1);
//     func_150026C4(2);
//
//     if (D_800DBEF0 > 0) {
//         for (i = 0; i < D_800DBEF0; i++) {
//             temp_v0_2 = &D_800DBEF4[i];
//             if (((u8)temp_v0_2->unk4F & 0x60) != 32) {
//                 func_15002724(temp_v0_2->unk1C);
//             }
//         }
//     }
//
//     func_15002754();
//     D_800D2C68 = (u8)1;
//     D_800D2C2C = 0;
//
//     for (i = 0; i < D_800DBEF0; i++) {
//         temp_v0_2 = &D_800DBEF4[i];
//         if (((u8)temp_v0_2->unk4F & 0x60) != 32) {
//             temp_v0_2->unk58 = D_800DBE38;
//             temp_v0_2->unk56 = 0; //D_800DBE38 - D_800DBE38;
//             func_15001460(temp_v0_2->unk1C);
//         } else {
//             temp_v0_2->unk58 = 0;
//             temp_v0_2->unk56 = 0;
//         }
//     }
//
//     func_150026E8(2);
//     D_800D2C68 = 0;
//     D_800D3300->unk0 = 0;
//     D_800D3300->unk4 = (s32) (D_800DBE3C << 8);
//     func_1510F800(0);
//     temp_t7 = (func_15002878() + 7) & ~7; // ALIGN8
//     D_800D3668 = D_8003809C;
//     D_800D366C = (s32) (D_8003809C + temp_t7);
//     func_1510F800(2);
// }

void func_150038A0(void) {
    func_15001A08();
    func_15001BC8(0, &D_800DBE2A, &D_800DBE2C);
    func_15001BC8(1, 0, 0);
    func_15001CEC(2);
    func_1510F800(0);
    func_150025FC();
    D_800DBE62 = (u8)1;
}

s32 func_1500390C(s32 arg0) {
    s32 i;

    for (i = 0; i < 7764; i++) {
        if (arg0 == D_800B0E58[i]) {
            return i;
        }
    }
    return -1;
}
