#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_150064E0(void) {
    s32 i = 0;
    func_15017790();

    do {
        D_800C3A60[i++] = 0;
    } while (i < 69);

    D_800BE3DF = 24;
    D_800BE3E8 = 0;
    D_800D2E45 = 1;
}

#ifdef NON_MATCHING
s32 func_1502B5C8(s32 *arg0, s32 arg1, ...);
void func_10024190(void *, s32); /* osWritebackDCache */
extern u8 *D_800BE810;           /* bit widths of the 69 packed save fields (asset 1/7, +8) */
extern s32 D_800BE804;

/* save_slot_unpack: reads EEPROM save slot arg0 (block arg0 * 16 + 4, 0x80 bytes into D_800BE778) and checks the
 * checksum (0xCC + sum of bytes 2..0x7F shifted left by index & 3, 16 bits) against the first u16. Bad block:
 * func_150064E0 (defaults) and, if a slot is loaded (D_800BE7FC >= 0) while D_80082F50 is set, the 27-byte state
 * at D_800D2E4C is put back. Good block: byte 2 = slot kind (sp+0x7F), bytes 3..6 = a time stamp (big-endian),
 * 27 bytes of D_800D2E4C, 9 bytes of D_800D2E60, D_800BE3DF, D_800BE800, D_800BE804 (u16, also passed to
 * func_15085710(0, 9, .)), D_800BE3E8, then the 69 bit fields of D_800C3A60 (u64 each, widths D_800BE810, MSB
 * first). While D_80082F50 is set and the kind is < 3, the slot record D_800BE818[kind] is refreshed when the stamp
 * is newer (count of set bits in D_800D2E4C, D_800BE3E8, D_800BE3DF, stamp, slot, D_800BE804); D_800BE7FC keeps the
 * best count (D_800BE7FE = 1 when D_800D2E68 bit 5 is set), otherwise the old D_800D2E4C state is put back.
 * Block 0x34 (slot 3) clears D_80082F50 at the end. */
void func_15006590(s8 arg0) {
    u8 saved[27];   /* sp+0x5C */
    u8 kind;        /* sp+0x7F */
    s32 stamp;      /* sp+0x78 */
    s32 block;      /* sp+0x48 */
    u64 bit;        /* sp+0xA8 */
    u8 *p;
    u8 *rec;
    s32 i, j;
    s32 sum;
    s32 bits;
    u8 mask;
    u8 cur;
    u8 v;

    for (i = 0; i < 27; i++) {
        saved[i] = ((u8 *) D_800D2E4C)[i];
    }
    if (D_800BE810 == NULL) {
        D_800BE810 = (u8 *) func_1502B5C8(NULL, 1, 7) + 8;
    }
    func_10024190(D_800BE778, 0x80);
    osInvalDCache(D_800BE778, 0x80);
    block = arg0 * 16 + 4;
    func_151DD950(&D_800BE900, block, D_800BE778, 0x80);
    sum = 0xCC;
    for (i = 2; i < 0x80; i++) {
        sum = (sum + (D_800BE778[i] << (i & 3))) & 0xFFFF;
    }
    if (sum != *(u16 *) D_800BE778) {
        func_150064E0();
        if (D_800BE7FC >= 0 && D_80082F50 != 0) {
            for (i = 0; i < 27; i++) {
                ((u8 *) D_800D2E4C)[i] = saved[i];
            }
        }
        if (block == 0x34) {
            D_80082F50 = 0;
        }
        return;
    }

    p = &D_800BE778[2];
    kind = p[0];
    stamp = (p[1] << 24) | (p[2] << 16) | (p[3] << 8) | p[4];
    p += 5;
    for (i = 0; i < 27; i++) {
        ((u8 *) D_800D2E4C)[i] = *p++;
    }
    for (i = 0; i < 9; i++) {
        D_800D2E60[i] = *p++;
    }
    D_800BE3DF = p[0];
    D_800BE800 = p[1];
    D_800BE804 = p[2] << 8;
    D_800BE804 = (p[2] << 8) | p[3];
    p += 4;
    func_15085710(0, 9, D_800BE804);
    D_800BE3E8 = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
    cur = p[4];
    p += 5;
    mask = 0x80;
    for (i = 0; i < 69; i++) {
        D_800C3A60[i] = 0;
        bit = 1LL << (D_800BE810[i] - 1);
        for (j = 0; j < D_800BE810[i]; j++) {
            if (cur & mask) {
                D_800C3A60[i] |= bit;
            }
            if (mask == 1) {
                cur = *p++;
                mask = 0x80;
            } else {
                mask >>= 1;
            }
            bit >>= 1;
        }
    }

    if (D_80082F50 != 0 && kind < 3) {
        D_800BE7F8[arg0] = kind;
        rec = (u8 *) &D_800BE818[kind];
        if (*(s32 *) (rec + 8) < stamp) {
            bits = 0;
            for (i = 0; i < 27; i++) {
                v = ((u8 *) D_800D2E4C)[i];
                for (j = 0; j < 8; j++) {
                    if (v & 1) {
                        bits++;
                    }
                    v >>= 1;
                }
            }
            rec[0xD] = bits;
            *(s32 *) (rec + 0) = D_800BE3E8;
            rec[0xC] = (s8) D_800BE3DF;
            *(s32 *) (rec + 8) = stamp;
            rec[0xE] = arg0;
            *(s32 *) (rec + 4) = D_800BE804;
            if ((u8) bits >= D_800BE7FC) {
                D_800BE7FC = (u8) bits;
                if (D_800D2E68 & 0x20) {
                    D_800BE7FE = 1;
                }
            } else {
                for (i = 0; i < 27; i++) {
                    ((u8 *) D_800D2E4C)[i] = saved[i];
                }
            }
        } else {
            for (i = 0; i < 27; i++) {
                ((u8 *) D_800D2E4C)[i] = saved[i];
            }
        }
    }
    if (block == 0x34) {
        D_80082F50 = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15006590.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15006BEC.s")
#ifdef NON_MATCHING
void func_1500707C(s32 arg0) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s0_2;
    s8 *var_s2;
    u8 *temp_t6;

    var_s0 = 0;
    do {
        temp_t6 = &D_800BE778[var_s0];
        var_s0 += 1;
        *temp_t6 = 0xFF;
    } while (var_s0 < 8);
    osWritebackDCacheAll();
    var_s2 = D_800BE7F8;
    var_s0_2 = 0;
    if (D_8002AC5C == 0) {
        do {
            temp_v0 = (var_s0_2 * 0x10) + 4;
            if (arg0 == *var_s2) {
                func_151DDA90(&D_800BE900, temp_v0 & 0xFF, D_800BE778);
                func_151DDA90(&D_800BE900, (temp_v0 + 1) & 0xFF, D_800BE778);
            }
            var_s0_2 += 1;
            var_s2 += 1;
        } while (var_s0_2 != 4);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_1500707C.s")
#endif
#ifdef NON_MATCHING
extern u8 *D_80082F4C; /* -> D_800BE712: the ten 10-byte records of the save data */

// save_data_reset: clears the save data D_800BE710 (0x68 bytes) and gives its ten records their defaults: bytes
// +1 / +2 / +3 / +4 = 3 / 10 / 2 / 1, +9 = 0 and per record (asm jump table jtbl_80095DB0) +5 = 3 (records 0, 8,
// 9), 5 (1, 2) or 20 (5, 7), record 5 also +2 = 0; records 3, 4, 6 keep +5 = 0. Takes no arguments (the C caller
// func_1500727C used to pass two that the asm never reads).
void func_15007168(void) {
    u8 *p;
    u8 *rec;
    s32 i;

    for (p = (u8 *) &D_800BE710; p < (u8 *) &D_800BE710 + 0x68; p++) {
        *p = 0;
    }
    for (i = 0; i < 10; i++) {
        rec = D_80082F4C + i * 10;
        rec[1] = 3;
        rec[3] = 2;
        rec[4] = 1;
        rec[2] = 10;
        switch (i) {
            case 0:
            case 8:
            case 9:
                rec[5] = 3;
                break;
            case 1:
            case 2:
                rec[5] = 5;
                break;
            case 5:
                rec[5] = 20;
                rec[2] = 0;
                break;
            case 7:
                rec[5] = 20;
                break;
        }
        rec[9] = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007168.s")
#endif
#ifdef NON_MATCHING

void func_1500727C(void) {
    s32 temp_t9;
    s32 var_v0;
    s32 var_v1;
    u8 *var_a0;

    func_151DD950(&D_800BE900, 0x44U, &D_800BE710, 0x70);
    var_a0 = D_800BE714;
    var_v0 = ((D_800BE712 * 4) + 0xCC + (D_800BE713 * 8)) & 0xFFFF;
    var_v1 = 4;
    do {
        temp_t9 = (var_v0 + ((*(u8 *)((u8 *)var_a0 + 0)) << (var_v1 & 3)) + ((*(u8 *)((u8 *)var_a0 + 1)) << ((var_v1 + 1) & 3)) + ((*(u8 *)((u8 *)var_a0 + 2)) << ((var_v1 + 2) & 3)) + ((*(u8 *)((u8 *)var_a0 + 3)) << ((var_v1 + 3) & 3))) & 0xFFFF;
        var_v1 += 4;
        var_v0 = temp_t9;
        var_a0 += 4;
    } while (var_v1 != 0x68);
    if (temp_t9 != D_800BE710.checksum) {
        func_15007168();
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_1500727C.s")
#endif
#ifdef NON_MATCHING
void func_15007360(void) {
    s32 sp18;
    s32 var_v1;
    u16 temp_t9;
    u16 var_v0;
    u8 *var_a0;

    var_a0 = D_800BE714;
    var_v0 = ((D_800BE712 * 4) + 0xCC + (D_800BE713 * 8)) & 0xFFFF;
    var_v1 = 4;
    do {
        temp_t9 = (var_v0 + ((*(u8 *)((u8 *)var_a0 + 0)) << (var_v1 & 3)) + ((*(u8 *)((u8 *)var_a0 + 1)) << ((var_v1 + 1) & 3)) + ((*(u8 *)((u8 *)var_a0 + 2)) << ((var_v1 + 2) & 3)) + ((*(u8 *)((u8 *)var_a0 + 3)) << ((var_v1 + 3) & 3))) & 0xFFFF;
        var_v1 += 4;
        var_v0 = temp_t9;
        var_a0 += 4;
    } while (var_v1 != 0x68);
    D_800BE710.checksum = temp_t9;
    if (D_8002AC5C == 0) {
        sp18 = func_151DD4A0(&D_800BE900, 0x44U, &D_800BE710, 0x70);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007360.s")
#endif
#ifdef NON_MATCHING
void func_151DDF6C(void); /* P85: takes no arguments (the asm reads none) */
void func_151E86A4(void);
extern u8 D_800BE77A;
extern s32 D_800E102C;

void func_15007440(void) {
    s32 temp_t7;
    s32 temp_t9;
    s32 var_a0;
    s32 var_v0;
    s8 *var_v0_2;
    s8 *var_v0_3;
    s8 temp_a1;
    u8 *var_v1;
    u8 *var_v1_2;
    u8 temp_t1;
    u8 temp_t2;
    u8 temp_t3;
    u8 temp_t4;

    func_151DD950(&D_800BE900, 0U, D_800BE778, 0x20);
    var_v0 = 0xCC;
    var_v1 = &D_800BE77A;
    var_a0 = 2;
    do {
        temp_t7 = var_a0 & 3;
        var_a0 += 1;
        temp_t9 = (var_v0 + (*var_v1 << temp_t7)) & 0xFFFF;
        var_v0 = temp_t9;
        var_v1 += 1;
    } while (var_a0 < 0x1E);
    temp_a1 = (*(s8 *)((u8 *)D_800E1010 + 0x10));
    if (temp_t9 != *(u16 *)D_800BE778) {   /* P18: the asm reads a halfword (lhu) */
        var_v0_2 = D_800E1010;
        do {
            var_v0_2 += 4;
            (*(s8 *)((u8 *)var_v0_2 + -4)) = -1;
            (*(s8 *)((u8 *)var_v0_2 + -3)) = -1;
            (*(s8 *)((u8 *)var_v0_2 + -2)) = -1;
            (*(s8 *)((u8 *)var_v0_2 + -1)) = -1;
        } while ((s32)var_v0_2 != (s32)&D_800E102C);
    } else {
        var_v0_3 = D_800E1010;
        var_v1_2 = D_800BE778;
        do {
            temp_t1 = (*(u8 *)((u8 *)var_v1_2 + 2));
            temp_t2 = (*(u8 *)((u8 *)var_v1_2 + 3));
            temp_t3 = (*(u8 *)((u8 *)var_v1_2 + 4));
            temp_t4 = (*(u8 *)((u8 *)var_v1_2 + 5));
            var_v0_3 += 4;
            var_v1_2 += 4;
            (*(u8 *)((u8 *)var_v0_3 + -4)) = temp_t1;
            (*(u8 *)((u8 *)var_v0_3 + -3)) = temp_t2;
            (*(u8 *)((u8 *)var_v0_3 + -2)) = temp_t3;
            (*(u8 *)((u8 *)var_v0_3 + -1)) = temp_t4;
        } while ((s32)var_v0_3 != (s32)&D_800E102C);
    }
    (*(s8 *)((u8 *)D_800E1010 + 0x10)) = temp_a1;
    func_151DDF6C();
    func_151E86A4();
    D_800901D0 = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007440.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007558.s")

void func_15007644(void) {
}

void func_1500764C(void) {
    D_80082BB4 = (u8)6;
    D_800BE3EC = (u8)0;
}

void func_15007668(void) {
    D_80082BB4 = (u8)7;
    D_800BE3EC = (u8)0;
}

void func_15007684(void) {
    D_80082BB4 = (u8)4;
    D_800BE3EC = (u8)0;
}

void func_150076A0(void) {
    D_80082BB4 = (u8)5;
    D_800BE3EC = (u8)0;
}

void func_150076BC(s32 arg0) {
    if (arg0 < 0) {
        func_150064E0();
    }
    if ((arg0 >= 0) && (arg0 < 4) && (D_800BE616 == 0)) {
        D_80082BB4 = (u8)1;
        D_800BE3EC = arg0;
    }
}

void func_15007718(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 3) && (D_800BE616 == 0)) {
        D_80082BB4 = (u8)2;
        D_800BE3EC = arg0;
    }
}

void func_15007750(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 3)) {
        D_80082BB4 = (u8)3;
        D_800BE3EC = arg0;
    }
}

#ifdef NON_MATCHING
// save_slots_reset: marks the three save-slot summaries D_800BE818 empty (+8 = -1, +0xE = -1), clears the current slot
// D_800BE7FC / D_800BE7FE, sets D_80082F50, clears the 27 bytes at D_800D2E4C (pointer) and the 9 save bits
// D_800D2E60, and sets the four bytes D_800BE7F8[0..3] to -1. Mode 3 (menu) calls it on its first frame.
void func_15007778(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_800BE818[i].unk8 = -1;
    }
    for (i = 0; i < 3; i++) {
        D_800BE818[i].unkE = -1;
    }
    D_800BE7FC = -1;
    D_800BE7FE = 0;
    D_80082F50 = 1;
    for (i = 0; i < 0x1B; i++) {
        ((u8 *) D_800D2E4C)[i] = 0;
    }
    for (i = 0; i < 9; i++) {
        D_800D2E60[i] = 0;
    }
    D_800BE7F8[3] = -1;
    D_800BE7F8[2] = -1;
    D_800BE7F8[1] = -1;
    D_800BE7F8[0] = -1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_33990/func_15007778.s")
#endif
// NON-MATCHING: should probably start over..
// void func_15007778(void) {
//     s32 phi_v0;
//
//     D_800BE3F8->unk8 = -1;
//     D_800BE3F8->unk18 = -1;
//     D_800BE3F8->unk28 = -1;
//     D_800BE3F8->unkE = -1;
//     D_800BE3F8->unk1E = -1;
//     D_800BE3F8->unk2E = -1;
//     D_800BE3DC = -1;
//     D_80082BC0 = 1;
//     D_800BE3DE = 0;
//
//     phi_v0 = 0;
//     do {
//         ((u8*)D_800D2E4C)[phi_v0++] = 0;
//     } while (phi_v0 < 27);
//
//     for (phi_v0 = 0; phi_v0 < 9; phi_v0++) {
//         D_800D2E60[phi_v0] = 0;
//     }
//
//     D_800BE3DB = -1;
//     D_800BE3DA = -1;
//     D_800BE3D9 = -1;
//     D_800BE3D8 = -1;
// }
