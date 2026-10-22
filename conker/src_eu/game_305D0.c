#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern s32 *D_800B1240;
extern u8 *D_800B1244;
u8 *allocate_memory(s32, s32, s32, s32);
extern u8 D_800B1248;
extern s32 D_800B1214[];
extern s32 D_800B1224[];
extern s32 D_800B1254[];
extern s32 D_800B1260;
extern s32 D_800B1220[];
extern s32 D_800B1250[];
extern s32 D_800B1230[];
extern s32 *D_80082EB0[];
s32 func_1502B6BC(s32 *, s32, s32 *, s32, ...);
void func_150049A4(Gfx *, s32, s32);
s32 func_1510D3E0(Gfx *, s32, s32, s32, s16 **);
s32 func_1510D66C(s32, s32 *, s32, s32);
#endif


// what is this loop doing?
#ifdef NON_MATCHING
/* Relocates a level model's {ptr, ptr, x} table (12-byte entries, ends at ptr0 == 0) by base: the table
 * pointer goes to D_800B1240[idx] (made absolute when non-zero) and its entry count to D_800B1244[idx]. */
void func_15003120(s32 idx, s32 base, s32 table) {
    s32 n;
    s32 off;
    s32 *e;

    D_800B1240[idx] = table;
    D_800B1244[idx] = 0;
    if (table == 0) {
        return;
    }
    D_800B1240[idx] += base;
    n = 0;
    off = 0;
    e = (s32 *)D_800B1240[idx];
    if (e[0] != 0) {
        do {
            e[0] += base;
            n++;
            e = (s32 *)(D_800B1240[idx] + off);
            off += 12;
            e[1] += base;
            e = (s32 *)(D_800B1240[idx] + off);
        } while (e[0] != 0);
    }
    D_800B1244[idx] = n;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003120.s")
#endif
#ifdef NON_MATCHING
/* Level model loader: asset (2, 4, level) is a list of count {model header, size} pairs. Each header's
 * offsets +0 (display list), +8, +0x10 are made absolute, its {ptr, ptr, x} table at +0x20 is relocated by
 * func_15003120 (D_800B1240 / D_800B1244). Parts 0..3 also set D_800B0E00[i] (level DL), D_800B1220[i]
 * (vertex base = header + 0x28), D_800B1250[i] (vertex count = (DL - vertices) / 16), D_800B1230[i] (+8);
 * part 0 calls func_150039BC(+0x10). Then the level's texture preload list D_80082EB0[D_800B0DF0->0x4B]
 * (age 0x3E). Allocations: count * 4 bytes (D_800B1240) and count bytes (D_800B1244), both
 * allocate_memory(n, 1, 0, 0); both are cleared with bzero(p, count) (count bytes, also for the word array). */
void func_150031EC(s32 level) {
    s32 found;
    s32 count;
    s32 size;
    s32 *ent;
    u8 *hdr;
    u32 i;
    s32 *p;
    s32 *q;
    s32 *r;
    s32 off;
    s32 id;

    if (level >= 0x45) {
        level = 0;
    }
    ent = (s32 *)func_1502B6BC(&found, 0, &count, 2, 4, level);
    D_800B1260 = (s32)ent;
    p = D_800B1214;
    q = D_800B1224;
    r = D_800B1254;
    do {
        *p++ = 0;
        *q++ = 0;
        *r++ = 0;
    } while (r != &D_800B1260);
    func_150034B4();
    if (found != 0) {
        D_800B1240 = (s32 *)allocate_memory(count * 4, 1, 0, 0);
        D_800B1244 = (u8 *)allocate_memory(count, 1, 0, 0);
        bzero(D_800B1244, count);
        bzero(D_800B1240, count);
        D_800B1248 = count;
        for (i = 0; i < (u32)count; i++, ent += 2) {
            hdr = (u8 *)ent[0];
            if (hdr == NULL || ent[1] == 0) {
                continue;
            }
            if (*(s32 *)(hdr + 0x0) != 0) {
                *(s32 *)(hdr + 0x0) += (s32)hdr;
            }
            if (*(s32 *)(hdr + 0x8) != 0) {
                *(s32 *)(hdr + 0x8) += (s32)hdr;
            }
            if (*(s32 *)(hdr + 0x10) != 0) {
                *(s32 *)(hdr + 0x10) += (s32)hdr;
            }
            func_15003120(i, (s32)hdr, *(s32 *)(hdr + 0x20));
            if (i < 4) {
                D_800B1220[i] = (s32)(hdr + 0x28);
                D_800B0E00[i] = *(s32 *)(hdr + 0x0);
                D_800B1250[i] = (u32)(*(s32 *)(hdr + 0x0) - (s32)(hdr + 0x28)) >> 4;
                D_800B1230[i] = *(s32 *)(hdr + 0x8);
                if (i == 0) {
                    func_150039BC(*(s32 *)(hdr + 0x10));
                }
                func_150049A4((Gfx *)D_800B0E00[i], D_800B1220[i] + 0xFF000000, (s32)hdr);
                func_1510D3E0((Gfx *)D_800B0E00[i], 0, 1, 0x3F, NULL);
            } else {
                func_150049A4((Gfx *)*(s32 *)(hdr + 0x0), 0, (s32)hdr);
            }
        }
    }
    if (((u8 *)D_800B0DF0)[0x4B] != 0) {
        id = D_80082EB0[((u8 *)D_800B0DF0)[0x4B]][0];
        off = 4;
        while (id != 0) {
            func_1510D66C(id, &size, 0x3E, 0);
            id = *(s32 *)((u8 *)D_80082EB0[((u8 *)D_800B0DF0)[0x4B]] + off);
            off += 4;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_150031EC.s")
#endif
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
void func_15001460(s32);
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
