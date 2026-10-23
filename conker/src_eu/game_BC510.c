#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1508F7BC(void);
void func_1508F0D4(void);
void func_1508F9F4(void); /* P129 */
void func_1509093C(void); /* P129 */
s32 func_1518C900(s32);
void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern s16 D_8009E060[];
#endif


// need to figure out D_800D2460
extern u8 D_800D2880[];
extern s8 D_800D288D;
extern s8 D_800D289D;
extern s32 D_800D28E0;
void func_1508F060(void)
{
  int *new_var2;
  int new_var;
  u8 *p;
  D_800D288D = 0;
  D_800D289D = 0;
  new_var = 2; // fakematch: constant 2 must stay in a register
  new_var2 = &new_var; // fakematch: pins new_var in a register
  p = D_800D2880 + ((*new_var2) * 16);
  (D_800D2880 + ((*new_var2) * 16))[0x1D] = 0;
  p[0x2D] = 0;
  p[0x3D] = 0;
  p[0xD] = 0;
  D_800D28E0 = 0;
}

void func_1508F0A4(void) {
    func_1508F0D4();
    func_1508F9F4();
    func_1509093C();
}

#ifdef NON_MATCHING
extern s16 D_8009E084;
extern s16 D_8009E08A;
extern u8 D_800CC8BA;
extern f32 D_800D2834;
extern f32 D_800D2848;
extern s32 D_800D2858;
extern s32 D_800D2864;

void func_1508F0D4(void) {
    s32 sp40;
    s32 sp34;
    s32 *sp30;
    s32 *sp2C;
    f32 *temp_v0_2;
    f32 *temp_v0_3;
    f32 *temp_v1;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    f32 temp_f12_6;
    f32 temp_f12_7;
    f32 temp_f12_8;
    f32 var_f0;
    f32 var_f10;
    s32 temp_a2;
    s32 temp_v0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a3;
    s32 var_v0_2;
    s32 var_v0_3;
    struct256 **var_v1;
    struct256 *var_a0;
    u8 var_v0;

    var_a0 = D_800D245C;
    var_v1 = &D_800D245C;
    if (var_a0 != NULL) {
        do {
            var_a0->unk94 -= 5.0f;
            var_a0->unk84 += var_a0->unk90;
            var_a0->unk88 += var_a0->unk94;
            var_a0->unk8C += var_a0->unk98;
            var_a0->unk9C += var_a0->unkA8;
            var_a0->unkA0 += var_a0->unkAC;
            var_a0->unkA4 += var_a0->unkB0;
            temp_v0 = var_a0->unkB4 - D_800BE9E4;
            if (temp_v0 <= 0) {
                *var_v1 = var_a0->unk80;
                sp30 = (s32 *) var_a0;
                sp2C = (s32 *) var_v1;
                func_100043B4((s32 *) var_a0, 3U);
            } else {
                var_a0->unkB4 = (u8) temp_v0;
                var_v1 = &var_a0->unk80;
            }
            var_a0 = var_a0->unk80;
        } while (var_a0 != NULL);
    }
    var_v0 = D_800D2457;
    if ((s32) D_800CC8BA < (s32) var_v0) {
        D_800D2864 = 0xF0;
        if (var_v0 != D_800CC8BA) {
            do {
                D_800D2457 = var_v0 - 1;
                if (D_800D2848 == (f32) D_8009E08A) {
                    func_1508F7BC();
                }
                var_v0 = D_800D2457;
            } while (var_v0 != D_800CC8BA);
        }
        func_10010F30(0x1A6, 0x7FFFU, 0x40U, 0, 0U);
    } else if ((s32) var_v0 < (s32) D_800CC8BA) {
        D_800D2864 = 0xF0;
        if (var_v0 != D_800CC8BA) {
            do {
                D_800D2457 = var_v0 + 1;
                if (D_800D2848 == (f32) D_8009E08A) {
                    func_1508F9C4();
                }
                var_v0 = D_800D2457;
            } while (var_v0 != D_800CC8BA);
        }
    }
    if (D_800D2864 != 0) {
        var_a3 = 0;
        temp_f0 = (f32) D_8009E08A;
        if (D_800D2848 == temp_f0) {
            D_800D2864 -= D_800BE9E4;
            if (D_800D2864 <= 0) {
                D_800D2864 = 0;
            }
            do {
                if (D_800BE9E4 > 0) {
                    temp_a2 = var_a3 * 4;
                    temp_v0_2 = temp_a2 + &D_800D2890;
                    temp_v1 = temp_a2 + &D_800D2858;
                    temp_f12 = (f32) D_800BE9E4;
                    var_a0_2 = 1;
                    var_f10 = *temp_v1 * -0.1f;
                    if (D_800BE9E4 > 1) {
                        do {
                            var_a0_2 += 1;
                            *temp_v0_2 += var_f10;
                            *temp_v0_2 *= 0.85f;
                            *temp_v1 += *temp_v0_2 * temp_f12;
                            var_f10 = *temp_v1 * -0.1f;
                        } while (var_a0_2 < D_800BE9E4);
                    }
                    *temp_v0_2 += var_f10;
                    *temp_v0_2 *= 0.85f;
                    *temp_v1 += *temp_v0_2 * temp_f12;
                }
                var_a3 += 2;
            } while (var_a3 != 4);
        } else if ((s32) D_800D2457 < (s32) D_800D2456) {
            var_v0_2 = D_800D2456 - D_800D2457;
            var_a0_3 = 0;
            D_800D2848 += 50.0f * (f32) D_800BE9E4;
            if (temp_f0 <= D_800D2848) {
                D_800D2848 = temp_f0;
                if (var_v0_2 > 0) {
                    do {
                        sp34 = var_v0_2;
                        sp40 = var_a0_3;
                        func_1508F7BC();
                        var_a0_3 += 1;
                    } while (var_a0_3 != var_v0_2);
                }
                func_10010F30(0x1A6, 0x7FFFU, 0x40U, 0, 0U);
            }
        } else {
            var_v0_3 = D_800D2457 - D_800D2456;
            var_a0_4 = 0;
            D_800D2848 += 50.0f * (f32) D_800BE9E4;
            if (temp_f0 <= D_800D2848) {
                D_800D2848 = temp_f0;
                if (var_v0_3 > 0) {
                    do {
                        sp34 = var_v0_3;
                        sp40 = var_a0_4;
                        func_1508F9C4();
                        var_a0_4 += 1;
                    } while (var_a0_4 != var_v0_3);
                }
            }
        }
    } else {
        temp_f12_2 = (f32) D_8009E084;
        if (D_800D2848 != temp_f12_2) {
            var_f0 = ((f32) D_8009E08A - D_800D2848) * 0.1f;
            if (var_f0 < 0.01f) {
                var_f0 = 0.01f;
            }
            D_800D2848 -= var_f0 * (f32) D_800BE9E4;
            if (D_800D2848 < temp_f12_2) {
                D_800D2848 = temp_f12_2;
            }
        }
    }
    temp_v0_3 = &D_800D2410[2];
    if (*D_800D2410 != 1.0f) {
        temp_f12_3 = *D_800D2410 + ((f32) D_800BE9E4 * 0.03f);
        *D_800D2410 = temp_f12_3;
        if (temp_f12_3 > 1.0f) {
            *D_800D2410 = 1.0f;
        }
    }
    if (D_800D2834 != 1.0f) {
        temp_f12_4 = D_800D2834 + ((f32) D_800BE9E4 * 0.03f);
        D_800D2834 = temp_f12_4;
        if (temp_f12_4 > 1.0f) {
            D_800D2834 = 1.0f;
        }
    }
    temp_f12_5 = (*(f32 *)((u8 *)temp_v0_3 + 0));
    if (temp_f12_5 != 1.0f) {
        (*(f32 *)((u8 *)temp_v0_3 + 0)) = temp_f12_5 + ((f32) D_800BE9E4 * 0.03f);
        if ((*(f32 *)((u8 *)temp_v0_3 + 0)) > 1.0f) {
            (*(f32 *)((u8 *)temp_v0_3 + 0)) = 1.0f;
        }
    }
    temp_f12_6 = (*(f32 *)((u8 *)temp_v0_3 + 4));
    if (temp_f12_6 != 1.0f) {
        (*(f32 *)((u8 *)temp_v0_3 + 4)) = (f32) (temp_f12_6 + ((f32) D_800BE9E4 * 0.03f));
        if ((*(f32 *)((u8 *)temp_v0_3 + 4)) > 1.0f) {
            (*(f32 *)((u8 *)temp_v0_3 + 4)) = 1.0f;
        }
    }
    temp_f12_7 = (*(f32 *)((u8 *)temp_v0_3 + 8));
    if (temp_f12_7 != 1.0f) {
        (*(f32 *)((u8 *)temp_v0_3 + 8)) = (f32) (temp_f12_7 + ((f32) D_800BE9E4 * 0.03f));
        if ((*(f32 *)((u8 *)temp_v0_3 + 8)) > 1.0f) {
            (*(f32 *)((u8 *)temp_v0_3 + 8)) = 1.0f;
        }
    }
    temp_f12_8 = (*(f32 *)((u8 *)temp_v0_3 + 0xC));
    if (temp_f12_8 != 1.0f) {
        (*(f32 *)((u8 *)temp_v0_3 + 0xC)) = (f32) (temp_f12_8 + ((f32) D_800BE9E4 * 0.03f));
        if ((*(f32 *)((u8 *)temp_v0_3 + 0xC)) > 1.0f) {
            (*(f32 *)((u8 *)temp_v0_3 + 0xC)) = 1.0f;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F0D4.s")
#endif
void func_1508F7BC(void) {
    f32 sp48[4][4];
    f32 sp44;
    struct256 *temp_v0;

    D_800D2456 -= 1;
    D_800D2890.unk0 = (u32) (func_150ADA20() % 5U);
    D_800D2890.unk8 = sqrtf(25.0f - (D_800D2890.unk0 * D_800D2890.unk0));
    temp_v0 = allocate_memory(sizeof(*temp_v0), 1, 1, 0);
    temp_v0->unk80 = D_800D245C;
    D_800D245C = temp_v0;
    guMtxL2F(&sp48, (D_800D2456 << 7) + ((D_800BE9C0 ^ 1) << 6) + &D_800D2590);
    func_1503E5F8(&sp48, &temp_v0->unk84, &temp_v0->unk88, &temp_v0->unk8C, &temp_v0->unk9C, &temp_v0->unkA0, &temp_v0->unkA4, &sp44, &sp44, &sp44);

    temp_v0->unk90 = (u32)((func_150ADA20() & 0xF) + 10);
    temp_v0->unk94 = (u32)((func_150ADA20() & 0x1F) + 20);
    temp_v0->unk98 = 0.0f;
    temp_v0->unkA8 = (u32)(func_150ADA20() & 0xF);
    temp_v0->unkAC = (u32)(func_150ADA20() & 0xF);
    temp_v0->unkB0 = (u32)(func_150ADA20() & 0xF);
    temp_v0->unkB4 = 120;
}

void func_1508F9C4(void) {
    D_800D2410[D_800D2456++] = 0.0f;
}

#ifdef NON_MATCHING
/* P129: the six 16-byte bubble records D_800D2880 .. D_800D28E0 (drawn by func_15090630):
 *   +0 s16 x, +2 s16 y, +4 s16 x centre, +6 s16 size, +8 s16 sway amplitude, +A s16 timer,
 *   +C u8 rise speed, +D u8 state (0 free, 1 growing, 2 rising, 3 popped), +E u8 sway phase, +F u8 wobble phase.
 * D_800D28E0 = frames until the next bubble may spawn. */
#define BUB_S16(r, o) (*(s16 *)((r) + (o)))

// underwater_bubbles_update: spawns, grows, floats and pops the HUD air bubbles; a new bubble needs the player
// (object 0) under water for unkB2 >= 0x5B and a free spawn timer; its pop delay is (6 - min(unkB2 / 240, 6)) * 9.
void func_1508F9F4(void) {
    u8 *r;
    s32 value;
    s32 spawn;
    s32 delay;
    s32 frames;
    s32 v;
    s32 i;
    f32 sway;

    if (D_800D28E0 != 0) {
        D_800D28E0 -= D_800BE9E4;
        if (D_800D28E0 < 0) {
            D_800D28E0 = 0;
        }
    }
    value = D_800CC2D0[0].in_water ? D_800CC2D0[0].unkB2 : 0;
    /* The asm never sets the spawn flag (sp+0x44) to non-zero: it only clears it (value < 0x5B, or delay 0) and
     * otherwise reads whatever the stack slot holds. On the N64 that slot is always the s1 that func_1517ABB0
     * saved there just before (func_15019414 -> func_1517ABB0, then -> func_1508F0A4 -> func_1508F0D4, which
     * never writes it): func_1501878C's s1 = the address of its display list pointer (EU 0x800BEDF0), never 0. So the
     * flag is effectively "spawn allowed". The asm's delay (s7) is stack garbage only when value < 0x5B, where
     * it is never used (no spawn); 0 here. */
    delay = 0;
    spawn = 0;
    if (value >= 0x5B) {
        delay = value / 240;
        if (delay >= 7) {
            delay = 6;
        }
        delay = (6 - delay) * 9;
        spawn = (delay != 0);
    }
    for (r = D_800D2880; r != (u8 *)&D_800D28E0; r += 0x10) {
        if (r[0xD] == 2) {
            v = BUB_S16(r, 0xA) - D_800BE9E4;
            if (v > 0) {
                BUB_S16(r, 0xA) = v;
            } else {
                r[0xD] = 3;
                BUB_S16(r, 0xA) = 6;
            }
        }
        switch (r[0xD]) {
        case 0:
            if (spawn && D_800D28E0 == 0) {
                D_800D28E0 = 10;
                r[0xD] = 1;
                BUB_S16(r, 0) = 0xFC;
                BUB_S16(r, 2) = 0x60;
                BUB_S16(r, 6) = 0;
                r[0xC] = 0;
                r[0xE] = func_150ADA20();
                BUB_S16(r, 8) = 0x500;
                sway = func_15048A40(r[0xE]);
                r[0xF] = 0;
                BUB_S16(r, 0xA) = delay;
                BUB_S16(r, 4) = 0xFC - ((s32)(sway * BUB_S16(r, 8)) >> 8);
            }
            break;
        case 1:
            v = BUB_S16(r, 6) + D_800BE9E4 * 200;
            if (v >= 0x666) {
                r[0xD] = 2;
                v = 0x666;
            }
            BUB_S16(r, 6) = v;
            break;
        case 2:
            frames = D_800BE9E4;
            if (r[0xC] < 0x20) {
                v = r[0xC] + frames;
                if (v > 0x20) {
                    v = 0x20;
                }
                r[0xC] = v;
            }
            BUB_S16(r, 2) -= (s32)(frames * r[0xC]) >> 4;
            v = BUB_S16(r, 6);
            for (i = 0; i < frames; i++) {
                v = (v * 0x104) >> 8;
            }
            BUB_S16(r, 6) = v;
            r[0xE] += frames * 5;
            BUB_S16(r, 8) += frames * 30;
            sway = func_15048A40(r[0xE]);
            r[0xF] += D_800BE9E4 * 10;
            BUB_S16(r, 0) = ((s32)(sway * BUB_S16(r, 8)) >> 8) + BUB_S16(r, 4);
            break;
        case 3:
            if (BUB_S16(r, 0xA) == 0) {
                r[0xD] = 0;
            }
            break;
        }
    }
}
#undef BUB_S16
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508F9F4.s")
#endif
#ifdef NON_MATCHING
s32 *func_150938BC(s32 *arg0);
Gfx *func_15095350(Gfx *arg0);
Gfx *func_15096D44(Gfx *arg0);
void func_1518CF74(s32 arg0);
Gfx *func_150900F0(Gfx *, s32);
Gfx *func_150911F4(Gfx *);
Gfx *func_150918EC(Gfx *);
Gfx *func_15090630(Gfx *);
Gfx *func_15093B58(Gfx *, s32, s16 *, s32, s32);
extern u16 D_800D2874;
extern u8 D_800D27F0[];
extern s32 D_800BEFC4;          /* display list capacity, in Gfx commands */
extern f32 D_800901BC;          /* fog/table scale */
extern s16 D_8009E084;
extern f32 D_800D2848;
extern s32 D_800D29A8;

/* Overlay pass after the world: returns `gdl` unchanged when the list would overflow. */
u8 *func_1508FD38(u8 *arg0) {
    Gfx *start = (Gfx *)arg0;
    Gfx *gdl = start;
    s16 table[33];
    s32 scale;
    s32 i;
    f32 f;

    if (D_800BE9F0 == 0x1D) {
        return (u8 *)gdl;
    }
    gdl->words.w0 = 0xDB0E0000;
    gdl->words.w1 = D_800D2874;
    gdl++;
    gdl->words.w0 = 0xDA380007;
    gdl->words.w1 = (u32)D_800D27F0;
    gdl++;

    if (D_800BE616 != 0) {
        gdl = func_150918EC(gdl);
        if (D_800BEFC4 < gdl - D_800BEDE8[D_800BE9C0]) {
            return (u8 *)start;
        }
        return (u8 *)gdl;
    }
    if (D_800D2458 != 0) {
        gdl = (Gfx *)func_150938BC((s32 *)gdl);
    }
    if (D_800C35EA == 1) {
        return (u8 *)gdl;
    }
    if (D_8008D0A0 != 0) {
        f = D_800901BC;
        scale = 0x400;
        if (f == 1.0f) {
            table[0] = 0;
            for (i = 1; i < 33; i++) {
                table[i] = i;
            }
        } else {
            scale = 1024.0f / f;
            for (i = 0; i < 33; i++) {
                table[i] = (f32)i * f;
            }
        }
        gdl = func_15093B58(gdl, scale, table, 0x2C30, 1);
    }
    if (D_800D2848 != (f32)D_8009E084) {
        gdl = func_150900F0(gdl, 0);
    } else if (D_800D29A8 != 0) {
        func_1518CF74(0xB8);
        D_800D29A8 = 0;
    }
    gdl = func_150911F4(gdl);
    gdl = func_15095350(gdl);
    gdl = func_15090630(gdl);
    gdl = func_15096D44(gdl);
    if (D_800BEFC4 < gdl - D_800BEDE8[D_800BE9C0]) {
        return (u8 *)start;
    }
    return (u8 *)gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1508FD38.s")
#endif
#ifdef NON_MATCHING
/* Draws the D_800D29A8 display list once per world piece (D_8009E060 positions, D_800D2410 scales; matrices in
 * D_800D2590) and, in the level variant (arg1 == 0), once per D_800D245C object. arg1 != 0: front-end variant. */
Gfx *func_150900F0(Gfx *gdlArg, s32 arg1) {
    u8 *arg0 = (u8 *)gdlArg;
    f32 rot[4][4];   /* spB8 */
    f32 mf[4][4];    /* spF8; row 3 = sp128 */
    s32 count;       /* sp148 */
    f32 px, py, pz;  /* sp144 / sp140 / sp13C */
    u8 *dl;          /* spB0 */
    f32 scale;
    s16 *pos;
    s32 i;
    u8 *mtx;
    struct256 *obj;
    u8 *var_v0;
    s32 op;
    u8 *temp_s1, *temp_s1_2, *temp_s1_3, *temp_s1_4, *temp_s1_5, *temp_s1_6, *temp_s1_7, *temp_s1_8, *temp_s1_9, *temp_s1_10, *temp_s1_11;
    u8 *var_s1;

    if (D_800D29A8 == 0) {
        D_800D29A8 = func_1518C900(0xB8);
    }
    (*(s32 *)((u8 *)arg0 + 0)) = 0xD9F1FDFE;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    temp_s1 = arg0 + 8;
    (*(s32 *)((u8 *)temp_s1 + 4)) = -1;
    (*(s32 *)((u8 *)temp_s1 + 0)) = 0xD7000002;
    temp_s1_2 = temp_s1 + 8;
    (*(s32 *)((u8 *)temp_s1_2 + 4)) = 0x400;
    (*(s32 *)((u8 *)temp_s1_2 + 0)) = 0xD9FFFFFF;
    temp_s1_3 = temp_s1_2 + 8;
    (*(s32 *)((u8 *)temp_s1_3 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)temp_s1_3 + 4)) = 0;
    temp_s1_4 = temp_s1_3 + 8;
    (*(s32 *)((u8 *)temp_s1_4 + 4)) = 0xFF;
    (*(s32 *)((u8 *)temp_s1_4 + 0)) = 0xFA000000;
    temp_s1_5 = temp_s1_4 + 8;
    if (arg1 == 0) {
        (*(s32 *)((u8 *)temp_s1_5 + 0)) = 0xEF08AC0F;
        (*(s32 *)((u8 *)temp_s1_5 + 4)) = 0x55204C;
        temp_s1_6 = temp_s1_5 + 8;
        (*(s32 *)((u8 *)temp_s1_6 + 4)) = -0x604;
        (*(s32 *)((u8 *)temp_s1_6 + 0)) = 0xFC127E24;
        temp_s1_7 = temp_s1_6 + 8;
        (*(s32 *)((u8 *)temp_s1_7 + 0)) = 0xFB000000;
        (*(s32 *)((u8 *)temp_s1_7 + 4)) = 0;
        var_s1 = temp_s1_7 + 8;
    } else {
        (*(s32 *)((u8 *)temp_s1_5 + 0)) = 0xDB0E0000;
        temp_s1_8 = temp_s1_5 + 8;
        (*(s32 *)((u8 *)temp_s1_5 + 4)) = (s32) D_800D2874;
        (*(s32 *)((u8 *)temp_s1_8 + 0)) = 0xDA380007;
        (*(s32 *)((u8 *)temp_s1_8 + 4)) = (s32)D_800D27F0;
        temp_s1_9 = temp_s1_8 + 8;
        (*(s32 *)((u8 *)temp_s1_9 + 0)) = 0xEF08AC0F;
        (*(s32 *)((u8 *)temp_s1_9 + 4)) = 0x5041CC;
        temp_s1_10 = temp_s1_9 + 8;
        (*(s32 *)((u8 *)temp_s1_10 + 0)) = 0xFC12D225;
        (*(s32 *)((u8 *)temp_s1_10 + 4)) = 0xFFA7FFFF;
        temp_s1_11 = temp_s1_10 + 8;
        (*(s32 *)((u8 *)temp_s1_11 + 0)) = 0xFB000000;
        var_s1 = temp_s1_11 + 8;
        (*(s32 *)((u8 *)temp_s1_11 + 4)) = (s32) ((D_8009016C & 0xFF) | ~0xFF);
    }
    count = D_800D2456;
    dl = (u8 *)D_800D29A8;
    if (arg1 != 0) {
        px = (f32)((s16 *)&D_8009E084)[3] - 54.0f;
        count = D_800CC8BA;
        py = (f32)((s16 *)&D_8009E084)[4] - 52.0f;
        pz = (f32)((s16 *)&D_8009E084)[5] - 344.7f;
        func_150A8050(rot, 50.0f, -20.0f, -20.0f);
        scale = 1.0f;
        var_v0 = dl;
        do {
            op = (*(u32 *)var_v0 >> 24) & 0xFF;
            if (op == 0xEF) {
                *(s32 *)(var_v0 + 4) = 0x5041C8;
            } else if (op == 0xFC) {
                *(u32 *)var_v0 = 0;
            }
            var_v0 += 8;
        } while (op != 0xDF);
    } else {
        px = (&D_800D2848)[0];
        py = (&D_800D2848)[1];
        pz = (&D_800D2848)[2];
        func_150A8050(rot, ((f32 *)&D_800D2858)[0] + 50.0f, -20.0f, ((f32 *)&D_800D2858)[2] + -20.0f);
        scale = 0.0f; /* asm: uninitialised sp138, always replaced by D_800D2410[i] below */
    }
    func_15043EC8(rot, 1.0f, 1.0f, 1.0f, px, py, pz);
    pos = D_8009E060;
    mtx = &D_800D2590;
    for (i = 0; i < count; i++) {
        if (arg1 == 0) {
            scale = D_800D2410[i];
        }
        func_150A7CB0(mf, *(s32 *)&scale, *(s32 *)&scale, *(s32 *)&scale);
        mf[3][0] = (f32)pos[0];
        mf[3][1] = (f32)pos[1];
        mf[3][2] = (f32)pos[2];
        func_150A7A48(mf, rot, mf);
        guMtxF2L(mf, (Mtx *)(mtx + (D_800BE9C0 << 6)));
        ((s32 *)var_s1)[0] = 0xDA380003;
        ((s32 *)var_s1)[1] = (s32)(mtx + (D_800BE9C0 << 6));
        var_s1 += 8;
        ((s32 *)var_s1)[0] = 0xDE000000;
        ((s32 *)var_s1)[1] = (s32)dl;
        var_s1 += 8;
        pos += 3;
        mtx += 0x80;
    }
    if (arg1 == 0) {
        for (obj = D_800D245C; obj != NULL; obj = obj->unk80) {
            func_15043E68((Mtx *)((u8 *)obj + (D_800BE9C0 << 6)), obj->unk9C, obj->unkA0, obj->unkA4, obj->unk84, obj->unk88, obj->unk8C);
            ((s32 *)var_s1)[0] = 0xDA380003;
            ((s32 *)var_s1)[1] = (s32)((u8 *)obj + (D_800BE9C0 << 6));
            var_s1 += 8;
            ((s32 *)var_s1)[0] = 0xDE000000;
            ((s32 *)var_s1)[1] = (s32)dl;
            var_s1 += 8;
        }
    }
    return (Gfx *)var_s1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150900F0.s")
#endif
#ifdef NON_MATCHING
s32 func_1510D66C(s32, s32 *, s32, s32);
u8 *func_15095380(u8 *, s32 *, s32, s32 *, s32, s32, s32, s32, s32);
u8 *func_15095E58(u8 *, s32 *, f32, f32);
extern s32 D_80090784;
extern s32 D_80091BF0;

Gfx *func_15090630(Gfx *gdlArg) {
    u8 *arg0 = (u8 *)gdlArg;
    s32 sprBuf[4]; /* sprite state for func_15095380 / func_15095E58: +6 w, +8 h (s16), +0xA alpha, +0xD flip flags */
    u8 *spr = (u8 *)sprBuf;
    s32 sp84;
    f32 temp_f0;
    f32 temp_f2;
    s16 temp_s3;
    s16 temp_s4;
    s16 temp_v0_2;
    s32 var_v1;
    s32 var_s5;
    s32 var_s5_2;
    s8 var_s1;
    u8 *var_s0;
    u8 *var_s0_2;
    u8 temp_v0;
    u8 *temp_s2;
    u8 *temp_s2_2;
    u8 *var_s2;

    *(s8 *)(spr + 0xA) = 0xFF;
    *(s8 *)(spr + 0xD) = 0;
    (*(s32 *)((u8 *)arg0 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)arg0 + 4)) = 0;
    temp_s2 = arg0 + 8;
    (*(s32 *)((u8 *)temp_s2 + 0)) = 0xFCFFB5FF;
    (*(s32 *)((u8 *)temp_s2 + 4)) = 0xFFFCFE38;
    temp_s2_2 = temp_s2 + 8;
    (*(s32 *)((u8 *)temp_s2_2 + 0)) = 0xEF102C0F;
    (*(s32 *)((u8 *)temp_s2_2 + 4)) = 0x0C184244;
    var_s2 = temp_s2_2 + 8;
    var_s5 = 1;
    var_s0 = D_800D2880;
    do {
        temp_v0 = (*(u8 *)((u8 *)var_s0 + 0xD));
        if ((temp_v0 == 1) || (temp_v0 == 2)) {
            if (var_s5 != 0) {
                var_s5 = 0;
                func_1510D66C(D_80091BF0, &sp84, 3, 0);
                var_s2 = func_15095380(var_s2, &D_80090784, 0, (s32 *)spr, 0, 0, 0, 2, 3);
            }
            temp_f0 = func_15048A40((*(u8 *)((u8 *)var_s0 + 0xF)));
            temp_f2 = (f32) (*(s16 *)((u8 *)var_s0 + 6));
            *(s16 *)(spr + 6) = (s16) (s32) (temp_f2 * ((0.2f * temp_f0) + 1.0f));
            *(s16 *)(spr + 8) = (s16) (s32) (temp_f2 * ((-0.2f * temp_f0) + 1.0f));
            var_s2 = func_15095E58(var_s2, (s32 *)spr, (f32) (*(s16 *)((u8 *)var_s0 + 0)), (f32) (*(s16 *)((u8 *)var_s0 + 2)));
        }
        var_s0 += 0x10;
    } while ((u32) var_s0 < (u32) &D_800D28E0);
    var_s5_2 = 1;
    var_s0_2 = D_800D2880;
    do {
        var_s1 = 0;
        if ((*(u8 *)((u8 *)var_s0_2 + 0xD)) == 3) {
            temp_v0_2 = (*(s16 *)((u8 *)var_s0_2 + 6));
            temp_s3 = (*(s16 *)((u8 *)var_s0_2 + 0));
            temp_s4 = (*(s16 *)((u8 *)var_s0_2 + 2));
            *(s16 *)(spr + 6) = temp_v0_2;
            *(s16 *)(spr + 8) = temp_v0_2;
            if ((u32) (func_150ADA20() & 0xFF) < 0x80U) {
                var_s1 = 1;
            }
            if ((u32) (func_150ADA20() & 0xFF) < 0x80U) {
                var_s1 |= 2;
            }
            *(s8 *)(spr + 0xD) = var_s1;
            if (var_s5_2 != 0) {
                var_s5_2 = 0;
                var_s2 = func_15095380(var_s2, &D_80091BF0, 0, (s32 *)spr, 0, 0, 0, 2, 3);
            }
            var_s2 = func_15095E58(var_s2, (s32 *)spr, (f32) temp_s3, (f32) temp_s4);
            var_v1 = (*(s16 *)((u8 *)var_s0_2 + 0xA)) - D_800BE9E4;
            if (var_v1 < 0) {
                var_v1 = 0;
            }
            (*(s16 *)((u8 *)var_s0_2 + 0xA)) = var_v1;
        }
        var_s0_2 += 0x10;
    } while (var_s0_2 != (u8 *)&D_800D28E0);
    return (Gfx *)(var_s2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15090630.s")
#endif
#ifdef NON_MATCHING
/* P129: the air meter state at D_800D28E8 + 0x80 (drawn by func_15090AE8 with D_800D28E8's two 0x40 matrices). */
typedef struct {
    /* 0x80 */ s32 dl;          /* first display list of model 0xB9 */
    /* 0x84 */ u8 *vtx[2];      /* the model's 16-byte vertices (buffer 0 = the asset's own, 1 = a copy), per frame */
    /* 0x8C */ u8 *base;        /* 10-byte copies: s16 x, y, z, u8 colour[4] */
    /* 0x90 */ u8 *target;      /* the blend target (asset 2/0x18, same 10-byte layout) */
    /* 0x94 */ f32 blend;       /* 0..1 between base and target positions */
    /* 0x98 */ f32 blend_vel;
    /* 0x9C */ f32 level;       /* air used / 720, at most 1 */
    /* 0xA0 */ f32 drop_y;      /* falls once the air is gone */
    /* 0xA4 */ f32 drop_vel;
    /* 0xA8 */ f32 wobble;      /* -2..2 */
    /* 0xAC */ f32 wobble_vel;
    /* 0xB0 */ u16 img[4];      /* sprite ids by air level */
    /* 0xB8 */ s16 wobble_timer;
    /* 0xBA */ u8 active;
    /* 0xBB */ u8 count;        /* vertex count */
} AirMeter;
extern s32 D_800D28E8;
extern f32 D_8009E0F8;  /* initial blend speed */
extern f32 D_8009E0FC;  /* initial drop speed */
extern f32 D_8009E100;  /* blend range below the level */
extern f32 D_8009E104;  /* blend range above the level */
extern f32 D_8009E108;  /* minimum wobble speed */
extern f32 D_8009E10C;  /* wobble kick */
extern u16 D_8009060A;
extern u16 D_80090612;
extern u16 D_80090616;
extern u16 D_8009061E;
extern u16 D_80090622;
s32 func_15030100(s32 idx, s32 **dls, u8 *count, s32 *data, s32 *out10, s32 *out8, s32 *outC);

// underwater_air_meter_update: animates the HUD air meter while the player is under water (object 0's in_water,
// unkB2 = time under water): loads model 0xB9 once, blends its vertices towards the target shape around the air
// level, tints them, wobbles the meter when air runs low and drops it once the air is gone (unkB2 >= 1440).
void func_1509093C(void) {
    AirMeter *am = (AirMeter *)((u8 *)&D_800D28E8 + 0x80);
    s32 used;
    s32 *dls;
    u8 count;
    s32 data;
    s32 out10, out8, outC;
    f32 frames;
    f32 lo, hi;
    f32 step;
    u8 *vtx;
    u8 *dst;
    u8 *base;
    u8 *target;
    s32 i;
    s32 dark;
    s32 tint_r, tint_g;

    used = D_800CC2D0[0].in_water ? D_800CC2D0[0].unkB2 : 0;
    if (used < 0x5B) {
        am->active = 0;
        return;
    }
    if (am->active == 0) {
        am->active = 0xFF;
        am->blend = 0.0f;
        am->drop_y = 0.0f;
        am->blend_vel = D_8009E0F8;
        am->wobble = 0.0f;
        am->wobble_vel = 0.0f;
        am->drop_vel = D_8009E0FC;
        am->wobble_timer = (func_150ADA20() & 0x3F) + 0x3C;
    }
    am->level = (f32)D_800CC2D0[0].unkB2 / 720.0f;
    if (am->level > 1.0f) {
        am->level = 1.0f;
    }
    if (used < 1441) {
        /* the blend bounces between level - D_8009E100 and level + D_8009E104, clamped to 0..1 */
        am->blend += am->blend_vel * (f32)D_800BE9E4;
        lo = am->level - D_8009E100;
        if (lo < 0.0f) {
            lo = 0.0f;
        }
        if (am->blend <= lo) {
            am->blend_vel = -am->blend_vel;
            am->blend = (lo + lo) - am->blend;
        } else {
            hi = am->level + D_8009E104;
            if (hi > 1.0f) {
                hi = 1.0f;
            }
            if (hi <= am->blend) {
                am->blend_vel = -am->blend_vel;
                am->blend = (hi + hi) - am->blend;
            }
        }
    }
    if (am->dl == 0) {
        func_15030100(0xB9, &dls, &count, &data, &out10, &out8, &outC);
        am->dl = *dls;
        am->count = ((u32)dls - (u32)data) >> 4;
        am->vtx[0] = (u8 *)data;
        am->vtx[1] = (u8 *)allocate_memory(am->count * 16, 1, 2, 0);
        bcopy((void *)data, am->vtx[1], am->count * 16);
        am->base = (u8 *)allocate_memory(am->count * 10, 1, 0, 0);
        for (i = 0; i < am->count; i++) {
            *(s16 *)(am->base + i * 10 + 0) = *(s16 *)(data + i * 16 + 0);
            *(s16 *)(am->base + i * 10 + 2) = *(s16 *)(data + i * 16 + 2);
            *(s16 *)(am->base + i * 10 + 4) = *(s16 *)(data + i * 16 + 4);
            am->base[i * 10 + 6] = *(u8 *)(data + i * 16 + 0xC);
            am->base[i * 10 + 7] = *(u8 *)(data + i * 16 + 0xD);
            am->base[i * 10 + 8] = *(u8 *)(data + i * 16 + 0xE);
            am->base[i * 10 + 9] = *(u8 *)(data + i * 16 + 0xF);
        }
        /* (the asm runs this as a one-pass loop) */
        func_1502B7F0((s32 *)&am->target, 2, 0x18, 0);
    }
    vtx = am->vtx[D_800BE9C0];
    base = am->base;
    target = am->target;
    for (i = 0; i < am->count; i++) {
        dst = vtx + i * 16;
        *(s16 *)(dst + 0) = (s32)(((f32)*(s16 *)(target + i * 10 + 0) - (f32)*(s16 *)(base + i * 10 + 0)) * am->blend +
                                           (f32)*(s16 *)(base + i * 10 + 0));
        *(s16 *)(dst + 2) = (s32)(((f32)*(s16 *)(target + i * 10 + 2) - (f32)*(s16 *)(base + i * 10 + 2)) * am->blend +
                                           (f32)*(s16 *)(base + i * 10 + 2));
        *(s16 *)(dst + 4) = (s32)(((f32)*(s16 *)(target + i * 10 + 4) - (f32)*(s16 *)(base + i * 10 + 4)) * am->blend +
                                           (f32)*(s16 *)(base + i * 10 + 4));
    }
    if (used < 480) {
        am->img[3] = am->img[2] = D_8009061E;
        am->img[1] = am->img[0] = D_8009060A;
    } else if (used < 960) {
        am->img[3] = am->img[2] = D_80090622;
        am->img[1] = am->img[0] = D_8009060A;
    } else if (used < 1200) {
        am->img[3] = am->img[2] = D_80090622;
        am->img[1] = am->img[0] = D_80090616;
    } else {
        am->img[3] = am->img[2] = D_80090622;
        am->img[1] = am->img[0] = D_80090612;
    }
    /* darkening 0..255 over the last 480 units of air (used 720 .. 1200) */
    dark = ((used - 720) * 255) / 480;
    if (dark < 0) {
        dark = 0;
    } else if (dark > 0xFF) {
        dark = 0xFF;
    }
    tint_r = ((dark * -151) >> 8) + 0xFF;
    tint_g = ((dark * -164) >> 8) + 0xFF;
    for (i = 0; i < am->count; i++) {
        dst = vtx + i * 16;
        if (i < 0xD0) {
            dst[0xC] = (s32)(base[i * 10 + 6] * tint_r) >> 8;
            dst[0xD] = (s32)(base[i * 10 + 7] * tint_g) >> 8;
            dst[0xE] = (s32)(base[i * 10 + 8] * 0xFF) >> 8;
        } else if (i < 0xDC) {
            dst[0xC] = ((dark * -97) >> 8) + 0xFF;
            dst[0xD] = ((dark * -94) >> 8) + 0xFF;
            dst[0xE] = ((dark * -91) >> 8) + 0xFF;
        } else {
            dst[0xC] = tint_r;
            dst[0xD] = tint_g;
            dst[0xE] = 0xFF;
        }
    }
    frames = D_800BE9E4;
    if (used >= 1441) {
        am->wobble_vel = 0.0f;
    } else if (used >= 1201) {
        if (fabsf(am->wobble_vel) < D_8009E108) {
            am->wobble_vel = D_8009E108;
        }
    } else if (am->wobble_timer != 0) {
        i = am->wobble_timer - D_800BE9E4;
        if (i <= 0) {
            i = 0;
            am->wobble_vel = D_8009E10C;
            am->wobble = frames * am->wobble_vel;
        }
        am->wobble_timer = i;
    }
    step = am->wobble_vel * frames;
    am->wobble += step;
    if (am->wobble > 2.0f) {
        am->wobble_vel = -am->wobble_vel;
        am->wobble = 4.0f - am->wobble;
    } else if (am->wobble < -2.0f) {
        am->wobble_vel = -am->wobble_vel;
        am->wobble = -4.0f - am->wobble;
    } else if (am->wobble_timer == 0 && used < 1200 && am->wobble >= 0.0f && am->wobble < step) {
        /* a swing passed through 0 with no kick pending: rest until the next random kick */
        am->wobble_timer = (func_150ADA20() & 0x3F) + 0x3C;
        am->wobble = 0.0f;
        am->wobble_vel = 0.0f;
    }
    if (used >= 1440 && am->drop_y > -22.0f) {
        am->drop_vel -= 0.25f * D_800BE9E4;
        am->drop_y += am->drop_vel;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_1509093C.s")
#endif

#ifdef NON_MATCHING
s32 func_1510D66C(s32, s32 *, s32, s32);
extern s32 D_800837D0;
extern s32 D_80083950;
extern s32 D_800844F0;
extern s32 D_80084520;
extern s32 D_800D28E8;

Gfx *func_150911F4(Gfx *gdlArg) {
    u8 *arg0 = (u8 *)gdlArg;
    s32 sp90;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    u8 *temp_s0;
    u8 *temp_s0_10;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *temp_s0_7;
    u8 *temp_s0_8;
    u8 *temp_s0_9;
    u8 *var_s0;
    u8 *var_s0_2;
    u8 *var_s0_3;

    var_s0 = arg0;
    if ((*(u8 *)((u8 *)(&D_800D28E8) + 0xBA)) == 0) {

    } else {
        (*(s32 **)((u8 *)var_s0 + 4)) = &D_800844F0;
        temp_s0 = var_s0 + 8;
        (*(s32 *)((u8 *)var_s0 + 0)) = 0xDE000000;
        (*(s32 *)((u8 *)temp_s0 + 4)) = 0x400;
        (*(s32 *)((u8 *)temp_s0 + 0)) = 0xD9FFFFFF;
        temp_s0_2 = temp_s0 + 8;
        (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0xD9F1FDFE;
        (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0;
        temp_s0_3 = temp_s0_2 + 8;
        (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0xD9BDFFFF;
        (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0;
        temp_s0_4 = temp_s0_3 + 8;
        if ((s32) (*(u8 *)((u8 *)(&D_800D28E8) + 0xBA)) < 0xFF) {
            (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xDB060020;
            (*(s32 **)((u8 *)temp_s0_4 + 4)) = &D_800837D0;
            var_s0_2 = temp_s0_4 + 8;
        } else {
            (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xDB060020;
            (*(s32 **)((u8 *)temp_s0_4 + 4)) = &D_80083950;
            var_s0_2 = temp_s0_4 + 8;
        }
        func_15043D90((u8 *)&D_800D28E8 + (D_800BE9C0 << 6), -1.0f - (*(f32 *)((u8 *)(&D_800D28E8) + 0xA0)), -11.0f + (*(f32 *)((u8 *)(&D_800D28E8) + 0xA8)), 0.0f, 4.05f, 4.05f, 4.05f, 667.0f, 152.0f, -1668.0f);
        (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xDA380003;
        temp_s0_5 = var_s0_2 + 8;
        (*(u8 **)((u8 *)var_s0_2 + 4)) = (u8 *) ((u8 *)&D_800D28E8 + (D_800BE9C0 << 6));
        (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0xFF;
        (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xF8000000;
        temp_s0_6 = temp_s0_5 + 8;
        (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xFA00F200;
        (*(s32 *)((u8 *)temp_s0_6 + 4)) = 0;
        temp_s0_7 = temp_s0_6 + 8;
        (*(s32 *)((u8 *)temp_s0_7 + 0)) = 0xFB000000;
        temp_s0_8 = temp_s0_7 + 8;
        (*(s32 *)((u8 *)temp_s0_7 + 4)) = (s32) (*(u8 *)((u8 *)(&D_800D28E8) + 0xBA));
        (*(s32 *)((u8 *)temp_s0_8 + 0)) = 0xDB06000C;
        temp_s0_9 = temp_s0_8 + 8;
        (*(u8 **)((u8 *)temp_s0_8 + 4)) = (u8 *) ((u8 *)&D_800D28E8 + (D_800BE9C0 << 6));
        (*(s32 *)((u8 *)temp_s0_9 + 0)) = 0xDB060004;
        var_s0_3 = temp_s0_9 + 8;
        (*(s32 *)((u8 *)temp_s0_9 + 4)) = (s32) (*(s32 *)((u8 *)(((u8 *)&D_800D28E8 + (D_800BE9C0 * 4))) + 0x84));
        if ((*(u16 *)((u8 *)(&D_800D28E8) + 0xB0)) != 0) {
            temp_v0 = func_1510D66C((*(u16 *)((u8 *)(&D_800D28E8) + 0xB0)), &sp90, 3, 0);
            (*(s32 *)((u8 *)var_s0_3 + 0)) = 0xDB060018;
            (*(s32 *)((u8 *)var_s0_3 + 4)) = temp_v0;
            var_s0_3 += 8;
        }
        if ((*(u16 *)((u8 *)(&D_800D28E8) + 0xB2)) != 0) {
            temp_v0_2 = func_1510D66C((*(u16 *)((u8 *)(&D_800D28E8) + 0xB2)), &sp90, 3, 0);
            (*(s32 *)((u8 *)var_s0_3 + 0)) = 0xDB06001C;
            (*(s32 *)((u8 *)var_s0_3 + 4)) = temp_v0_2;
            var_s0_3 += 8;
        }
        if ((*(u16 *)((u8 *)(&D_800D28E8) + 0xB4)) != 0) {
            temp_v0_3 = func_1510D66C((*(u16 *)((u8 *)(&D_800D28E8) + 0xB4)), &sp90, 3, 0);
            (*(s32 *)((u8 *)var_s0_3 + 0)) = 0xDB060028;
            (*(s32 *)((u8 *)var_s0_3 + 4)) = temp_v0_3;
            var_s0_3 += 8;
        }
        if ((*(u16 *)((u8 *)(&D_800D28E8) + 0xB6)) != 0) {
            temp_v0_4 = func_1510D66C((*(u16 *)((u8 *)(&D_800D28E8) + 0xB6)), &sp90, 3, 0);
            (*(s32 *)((u8 *)var_s0_3 + 0)) = 0xDB06002C;
            (*(s32 *)((u8 *)var_s0_3 + 4)) = temp_v0_4;
            var_s0_3 += 8;
        }
        (*(s32 *)((u8 *)var_s0_3 + 0)) = 0xDE000000;
        temp_s0_10 = var_s0_3 + 8;
        (*(s32 *)((u8 *)var_s0_3 + 4)) = (s32) (*(s32 *)((u8 *)(&D_800D28E8) + 0x80));
        (*(s32 **)((u8 *)temp_s0_10 + 4)) = &D_80084520;
        var_s0 = temp_s0_10 + 8;
        (*(s32 *)((u8 *)temp_s0_10 + 0)) = 0xDE000000;
    }
    return (Gfx *)(var_s0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150911F4.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15091534.s")
// NON-MATCHING: needs some love
// Gfx* func_15091534(Gfx* arg0, struct257 *arg1, u8 *arg2) {
//     u32 temp_v0;
//
//     *arg2 = 0;
//     // get address for texture?
//     temp_v0 = func_1510D0EC(&arg1->unkD16, 0, 3, 0);;
//     // tmp = arg0;
//     if (temp_v0 != 0x80000000) {
//       // FD50000012345678
//       gDPSetTextureImage(arg0++, G_IM_FMT_CI, G_IM_SIZ_16b, 1, temp_v0);
//       // F550000007098260
//       gDPSetTile(arg0++, G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD);
//       // E600000000000000
//       gDPLoadSync(arg0++);
//       // F3000000073FF000
//       gDPLoadBlock(arg0++, G_TX_LOADTILE, 0, 0, 1023, 0);
//       // E700000000000000
//       gDPPipeSync(arg0++);
//       // F540080000098260
//       gDPSetTile(arg0++, G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD);
//       // F2000000000FC0FC
//       // FIXME: what are these macros
//       // gDPSetTileSize(arg0++, G_TX_RENDERTILE, 0, 0, qu102(63), qu102(63));
//       gDPSetTileSize(arg0++, G_TX_RENDERTILE, 0, 0, 63, 63);
//       // FD10000012345678
//       gDPSetTextureImage(arg0++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, temp_v0 + 2048);
//       // E600000000000000
//       gDPLoadSync(arg0++);
//       // F00000000603C000
//       gDPLoadTLUTCmd(arg0++, 6, 15);
//       // EF00AC3F00504244
//       gDPSetOtherMode(arg0++, G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE | 0x0000000F, G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2);
//
//       *arg2 = (u8)1;
//     }
//     return arg0;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150916B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150918EC.s")

void func_15093818(s32 arg0) {
    if ((arg0 != 0) && (D_800D2458 == 0)) {
        D_800D2458 = 1;
        func_15093878();
        return;
    }
    if ((arg0 == 0) && (D_800D2458 != 0)) {
        D_800D2458 = 0;
    }
}

void func_15093878(void) {
    D_800D2448 = func_1518C900(0xBA);
    D_800D244C = allocate_memory(0x80, 1, 1, 0);
}

#ifdef NON_MATCHING
void func_150A7D00(s32, f32, f32, f32);
s32 func_1510D66C(s32, s32 *, s32, s32);
extern s32 D_11AF;
extern s32 D_800D2870;

s32 *func_150938BC(s32 *arg0) {
    s32 *temp_v1;
    s32 *var_s2;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    u8 *temp_s2;

    var_s2 = arg0;
    var_s0 = 4;
    var_s1 = (s32) ((s32) D_800D2870 / 25) % 60;
loop_1:
    temp_v0 = func_1510D66C((s32)((u8 *)&D_11AF + (var_s1 % 10)), NULL, 3, 0);
    temp_v1 = var_s2;
    if (temp_v0 == 0x80000000) {
        return var_s2;
    }
    (*(s32 *)((u8 *)temp_v1 + 0)) = ((var_s0 * 4) & 0xFFFF) | 0xDB060000;
    var_s2 = (s32 *)((u8 *)var_s2 + (8));
    (*(s32 *)((u8 *)temp_v1 + 4)) = temp_v0;
    if (var_s0 == 3) {
        var_s1 = (s32) ((s32) D_800D2870 / 25) / 60;
    } else {
        var_s1 = var_s1 / 10;
    }
    var_s0 -= 1;
    if (var_s0 == 0) {
        func_150A7D00((D_800BE9C0 << 6) + D_800D244C, (f32) 0x78, (f32) 0x81, (f32) -0x12F);
        (*(s32 *)((u8 *)var_s2 + 0)) = 0xDA380003;
        temp_s2 = ((s32 *)((u8 *)var_s2 + 8));
        (*(s32 *)((u8 *)var_s2 + 4)) = (s32) ((D_800BE9C0 << 6) + D_800D244C);
        (*(s32 *)((u8 *)temp_s2 + 0)) = 0xDE000000;
        (*(s32 *)((u8 *)temp_s2 + 4)) = (s32) D_800D2448;
        return temp_s2 + 8;
    }
    goto loop_1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_150938BC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/func_15093B58.s")
