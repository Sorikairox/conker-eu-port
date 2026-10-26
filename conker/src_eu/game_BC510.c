#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void hud_health_drop_piece(void);
void hud_health_update(void);
void underwater_bubbles_update(void); /* P129 */
void underwater_air_meter_update(void); /* P129 */
s32 shared_dl_acquire(s32);
void mtxf_mul(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern s16 D_8009E060[];
#endif


// need to figure out D_800D2460
extern u8 D_800D2880[];
extern s8 D_800D288D;
extern s8 D_800D289D;
extern s32 D_800D28E0;
/* was func_1508F060 */
void hud_bubbles_reset(void)
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

/* was func_1508F0A4 */
void hud_health_air_update(void) {
    hud_health_update();
    underwater_bubbles_update();
    underwater_air_meter_update();
}

#ifdef NON_MATCHING
extern s16 D_8009E084;
extern s16 D_8009E08A;
extern u8 D_800CC8BA;
extern f32 D_800D2834;
extern f32 D_800D2848;
extern s32 D_800D2858;
extern s32 D_800D2864;

/* was func_1508F0D4 */
void hud_health_update(void) {
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
                heap_set_block_tag((s32 *) var_a0, 3U);
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
                    hud_health_drop_piece();
                }
                var_v0 = D_800D2457;
            } while (var_v0 != D_800CC8BA);
        }
        sound_play_2d(0x1A6, 0x7FFFU, 0x40U, 0, 0U);
    } else if ((s32) var_v0 < (s32) D_800CC8BA) {
        D_800D2864 = 0xF0;
        if (var_v0 != D_800CC8BA) {
            do {
                D_800D2457 = var_v0 + 1;
                if (D_800D2848 == (f32) D_8009E08A) {
                    hud_health_add_piece();
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
                        hud_health_drop_piece();
                        var_a0_3 += 1;
                    } while (var_a0_3 != var_v0_2);
                }
                sound_play_2d(0x1A6, 0x7FFFU, 0x40U, 0, 0U);
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
                        hud_health_add_piece();
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/hud_health_update.s")
#endif
/* was func_1508F7BC */
void hud_health_drop_piece(void) {
    f32 sp48[4][4];
    f32 sp44;
    struct256 *temp_v0;

    D_800D2456 -= 1;
    D_800D2890.unk0 = (u32) (random_int() % 5U);
    D_800D2890.unk8 = sqrtf(25.0f - (D_800D2890.unk0 * D_800D2890.unk0));
    temp_v0 = allocate_memory(sizeof(*temp_v0), 1, 1, 0);
    temp_v0->unk80 = D_800D245C;
    D_800D245C = temp_v0;
    guMtxL2F(&sp48, (D_800D2456 << 7) + ((D_800BE9C0 ^ 1) << 6) + &D_800D2590);
    mtxf_decompose(&sp48, &temp_v0->unk84, &temp_v0->unk88, &temp_v0->unk8C, &temp_v0->unk9C, &temp_v0->unkA0, &temp_v0->unkA4, &sp44, &sp44, &sp44);

    temp_v0->unk90 = (u32)((random_int() & 0xF) + 10);
    temp_v0->unk94 = (u32)((random_int() & 0x1F) + 20);
    temp_v0->unk98 = 0.0f;
    temp_v0->unkA8 = (u32)(random_int() & 0xF);
    temp_v0->unkAC = (u32)(random_int() & 0xF);
    temp_v0->unkB0 = (u32)(random_int() & 0xF);
    temp_v0->unkB4 = 120;
}

/* was func_1508F9C4 */
void hud_health_add_piece(void) {
    D_800D2410[D_800D2456++] = 0.0f;
}

#ifdef NON_MATCHING
/* P129: the six 16-byte bubble records D_800D2880 .. D_800D28E0 (drawn by hud_bubbles_draw):
 *   +0 s16 x, +2 s16 y, +4 s16 x centre, +6 s16 size, +8 s16 sway amplitude, +A s16 timer,
 *   +C u8 rise speed, +D u8 state (0 free, 1 growing, 2 rising, 3 popped), +E u8 sway phase, +F u8 wobble phase.
 * D_800D28E0 = frames until the next bubble may spawn. */
#define BUB_S16(r, o) (*(s16 *)((r) + (o)))

// underwater_bubbles_update: spawns, grows, floats and pops the HUD air bubbles; a new bubble needs the player
// (object 0) under water for unkB2 >= 0x5B and a free spawn timer; its pop delay is (6 - min(unkB2 / 240, 6)) * 9.
/* was func_1508F9F4 */
void underwater_bubbles_update(void) {
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
     * otherwise reads whatever the stack slot holds. On the N64 that slot is always the s1 that player_morph_cache_age
     * saved there just before (game_frame_end_update -> player_morph_cache_age, then -> hud_health_air_update -> hud_health_update, which
     * never writes it): game_frame_step's s1 = the address of its display list pointer (EU 0x800BEDF0), never 0. So the
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
                r[0xE] = random_int();
                BUB_S16(r, 8) = 0x500;
                sway = math_sin_u8(r[0xE]);
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
            sway = math_sin_u8(r[0xE]);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/underwater_bubbles_update.s")
#endif
#ifdef NON_MATCHING
s32 *hud_clock_draw(s32 *arg0);
Gfx *sprite_gfx_begin(Gfx *arg0);
Gfx *sprite_gfx_begin_alt(Gfx *arg0);
void shared_dl_release(s32 arg0);
Gfx *hud_health_draw(Gfx *, s32);
Gfx *hud_air_meter_draw(Gfx *);
Gfx *mp_hud_draw_views(Gfx *);
Gfx *hud_bubbles_draw(Gfx *);
Gfx *radar_draw(Gfx *, s32, s16 *, s32, s32);
extern u16 D_800D2874;
extern u8 D_800D27F0[];
extern s32 D_800BEFC4;          /* display list capacity, in Gfx commands */
extern f32 D_800901BC;          /* fog/table scale */
extern s16 D_8009E084;
extern f32 D_800D2848;
extern s32 D_800D29A8;

/* Overlay pass after the world: returns `gdl` unchanged when the list would overflow. */
/* was func_1508FD38 */
u8 *hud_draw(u8 *arg0) {
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
        gdl = mp_hud_draw_views(gdl);
        if (D_800BEFC4 < gdl - D_800BEDE8[D_800BE9C0]) {
            return (u8 *)start;
        }
        return (u8 *)gdl;
    }
    if (D_800D2458 != 0) {
        gdl = (Gfx *)hud_clock_draw((s32 *)gdl);
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
        gdl = radar_draw(gdl, scale, table, 0x2C30, 1);
    }
    if (D_800D2848 != (f32)D_8009E084) {
        gdl = hud_health_draw(gdl, 0);
    } else if (D_800D29A8 != 0) {
        shared_dl_release(0xB8);
        D_800D29A8 = 0;
    }
    gdl = hud_air_meter_draw(gdl);
    gdl = sprite_gfx_begin(gdl);
    gdl = hud_bubbles_draw(gdl);
    gdl = sprite_gfx_begin_alt(gdl);
    if (D_800BEFC4 < gdl - D_800BEDE8[D_800BE9C0]) {
        return (u8 *)start;
    }
    return (u8 *)gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/hud_draw.s")
#endif
#ifdef NON_MATCHING
/* Draws the D_800D29A8 display list once per world piece (D_8009E060 positions, D_800D2410 scales; matrices in
 * D_800D2590) and, in the level variant (arg1 == 0), once per D_800D245C object. arg1 != 0: front-end variant. */
/* was func_150900F0 */
Gfx *hud_health_draw(Gfx *gdlArg, s32 arg1) {
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
        D_800D29A8 = shared_dl_acquire(0xB8);
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
        mtxf_rotate_xyz_deg(rot, 50.0f, -20.0f, -20.0f);
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
        mtxf_rotate_xyz_deg(rot, ((f32 *)&D_800D2858)[0] + 50.0f, -20.0f, ((f32 *)&D_800D2858)[2] + -20.0f);
        scale = 0.0f; /* asm: uninitialised sp138, always replaced by D_800D2410[i] below */
    }
    mtxf_scale_set_trans(rot, 1.0f, 1.0f, 1.0f, px, py, pz);
    pos = D_8009E060;
    mtx = &D_800D2590;
    for (i = 0; i < count; i++) {
        if (arg1 == 0) {
            scale = D_800D2410[i];
        }
        mtxf_scale(mf, *(s32 *)&scale, *(s32 *)&scale, *(s32 *)&scale);
        mf[3][0] = (f32)pos[0];
        mf[3][1] = (f32)pos[1];
        mf[3][2] = (f32)pos[2];
        mtxf_mul(mf, rot, mf);
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
            mtx_build_rot_trans((Mtx *)((u8 *)obj + (D_800BE9C0 << 6)), obj->unk9C, obj->unkA0, obj->unkA4, obj->unk84, obj->unk88, obj->unk8C);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/hud_health_draw.s")
#endif
#ifdef NON_MATCHING
s32 texture_cache_lookup(s32, s32 *, s32, s32);
u8 *sprite_load_texture(u8 *, s32 *, s32, s32 *, s32, s32, s32, s32, s32);
u8 *sprite_draw_at_screen(u8 *, s32 *, f32, f32);
extern s32 D_80090784;
extern s32 D_80091BF0;

/* was func_15090630 */
Gfx *hud_bubbles_draw(Gfx *gdlArg) {
    u8 *arg0 = (u8 *)gdlArg;
    s32 sprBuf[4]; /* sprite state for sprite_load_texture / sprite_draw_at_screen: +6 w, +8 h (s16), +0xA alpha, +0xD flip flags */
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
                texture_cache_lookup(D_80091BF0, &sp84, 3, 0);
                var_s2 = sprite_load_texture(var_s2, &D_80090784, 0, (s32 *)spr, 0, 0, 0, 2, 3);
            }
            temp_f0 = math_sin_u8((*(u8 *)((u8 *)var_s0 + 0xF)));
            temp_f2 = (f32) (*(s16 *)((u8 *)var_s0 + 6));
            *(s16 *)(spr + 6) = (s16) (s32) (temp_f2 * ((0.2f * temp_f0) + 1.0f));
            *(s16 *)(spr + 8) = (s16) (s32) (temp_f2 * ((-0.2f * temp_f0) + 1.0f));
            var_s2 = sprite_draw_at_screen(var_s2, (s32 *)spr, (f32) (*(s16 *)((u8 *)var_s0 + 0)), (f32) (*(s16 *)((u8 *)var_s0 + 2)));
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
            if ((u32) (random_int() & 0xFF) < 0x80U) {
                var_s1 = 1;
            }
            if ((u32) (random_int() & 0xFF) < 0x80U) {
                var_s1 |= 2;
            }
            *(s8 *)(spr + 0xD) = var_s1;
            if (var_s5_2 != 0) {
                var_s5_2 = 0;
                var_s2 = sprite_load_texture(var_s2, &D_80091BF0, 0, (s32 *)spr, 0, 0, 0, 2, 3);
            }
            var_s2 = sprite_draw_at_screen(var_s2, (s32 *)spr, (f32) temp_s3, (f32) temp_s4);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/hud_bubbles_draw.s")
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
s32 model_asset9_load_refcounted(s32 idx, s32 **dls, u8 *count, s32 *data, s32 *out10, s32 *out8, s32 *outC);

// underwater_air_meter_update: animates the HUD air meter while the player is under water (object 0's in_water,
// unkB2 = time under water): loads model 0xB9 once, blends its vertices towards the target shape around the air
// level, tints them, wobbles the meter when air runs low and drops it once the air is gone (unkB2 >= 1440).
/* was func_1509093C */
void underwater_air_meter_update(void) {
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
        am->wobble_timer = (random_int() & 0x3F) + 0x3C;
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
        model_asset9_load_refcounted(0xB9, &dls, &count, &data, &out10, &out8, &outC);
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
        asset_load_ptr((s32 *)&am->target, 2, 0x18, 0);
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
        am->wobble_timer = (random_int() & 0x3F) + 0x3C;
        am->wobble = 0.0f;
        am->wobble_vel = 0.0f;
    }
    if (used >= 1440 && am->drop_y > -22.0f) {
        am->drop_vel -= 0.25f * D_800BE9E4;
        am->drop_y += am->drop_vel;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/underwater_air_meter_update.s")
#endif

#ifdef NON_MATCHING
s32 texture_cache_lookup(s32, s32 *, s32, s32);
extern s32 D_800837D0;
extern s32 D_80083950;
extern s32 D_800844F0;
extern s32 D_80084520;
extern s32 D_800D28E8;

/* was func_150911F4 */
Gfx *hud_air_meter_draw(Gfx *gdlArg) {
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
        mtx_build_rot_scale_trans((u8 *)&D_800D28E8 + (D_800BE9C0 << 6), -1.0f - (*(f32 *)((u8 *)(&D_800D28E8) + 0xA0)), -11.0f + (*(f32 *)((u8 *)(&D_800D28E8) + 0xA8)), 0.0f, 4.05f, 4.05f, 4.05f, 667.0f, 152.0f, -1668.0f);
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
            temp_v0 = texture_cache_lookup((*(u16 *)((u8 *)(&D_800D28E8) + 0xB0)), &sp90, 3, 0);
            (*(s32 *)((u8 *)var_s0_3 + 0)) = 0xDB060018;
            (*(s32 *)((u8 *)var_s0_3 + 4)) = temp_v0;
            var_s0_3 += 8;
        }
        if ((*(u16 *)((u8 *)(&D_800D28E8) + 0xB2)) != 0) {
            temp_v0_2 = texture_cache_lookup((*(u16 *)((u8 *)(&D_800D28E8) + 0xB2)), &sp90, 3, 0);
            (*(s32 *)((u8 *)var_s0_3 + 0)) = 0xDB06001C;
            (*(s32 *)((u8 *)var_s0_3 + 4)) = temp_v0_2;
            var_s0_3 += 8;
        }
        if ((*(u16 *)((u8 *)(&D_800D28E8) + 0xB4)) != 0) {
            temp_v0_3 = texture_cache_lookup((*(u16 *)((u8 *)(&D_800D28E8) + 0xB4)), &sp90, 3, 0);
            (*(s32 *)((u8 *)var_s0_3 + 0)) = 0xDB060028;
            (*(s32 *)((u8 *)var_s0_3 + 4)) = temp_v0_3;
            var_s0_3 += 8;
        }
        if ((*(u16 *)((u8 *)(&D_800D28E8) + 0xB6)) != 0) {
            temp_v0_4 = texture_cache_lookup((*(u16 *)((u8 *)(&D_800D28E8) + 0xB6)), &sp90, 3, 0);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/hud_air_meter_draw.s")
#endif
#ifdef NON_MATCHING
s32 texture_cache_lookup(s32, s32 *, s32, s32);

// hud_icon_sheet_load: P208: loads HUD icon sheet `sheet` (texture 0xD18 + sheet: CI4 64x64, its 16-colour RGBA16
// palette 0x800 bytes in) for the status icons of mp_hud_draw_views. *ready is 1 when the sheet is resident and the
// load commands were added; otherwise it is 0 and `gdl` is returned unchanged.
/* was func_15091534 */
Gfx *hud_icon_sheet_load(Gfx *gdl, s32 sheet, u8 *ready) {
    s32 tex;

    *ready = 0;
    tex = texture_cache_lookup(0xD18 + sheet, NULL, 3, 0);
    if (tex == 0x80000000) {
        return gdl;
    }
    gdl->words.w0 = 0xFD500000; /* texture image CI16 */
    gdl->words.w1 = tex;
    gdl++;
    gdl->words.w0 = 0xF5500000;
    gdl->words.w1 = 0x07098260;
    gdl++;
    gDPLoadSync(gdl++);
    gdl->words.w0 = 0xF3000000;
    gdl->words.w1 = 0x073FF000;
    gdl++;
    gDPPipeSync(gdl++);
    gdl->words.w0 = 0xF5400800; /* render tile CI4, palette 0 */
    gdl->words.w1 = 0x00098260;
    gdl++;
    gdl->words.w0 = 0xF2000000;
    gdl->words.w1 = 0x000FC0FC;
    gdl++;
    gdl->words.w0 = 0xFD100000; /* palette image */
    gdl->words.w1 = tex + 0x800;
    gdl++;
    gDPLoadSync(gdl++);
    gdl->words.w0 = 0xF0000000; /* load TLUT, 16 colours */
    gdl->words.w1 = 0x0603C000;
    gdl++;
    gdl->words.w0 = 0xEF00AC3F; /* other modes: TLUT RGBA16 */
    gdl->words.w1 = 0x00504244;
    gdl++;
    *ready = 1;
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/hud_icon_sheet_load.s")
#endif
// NON-MATCHING: needs some love
// Gfx* hud_icon_sheet_load(Gfx* arg0, struct257 *arg1, u8 *arg2) {
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

#ifdef NON_MATCHING
/* P153 */
void text_printf_at(s32, s32, u8, s32, ...);
extern char D_8009E090[]; /* "%d" */
extern char D_8009E094[]; /* ":%02d" */
extern char D_8009E09C[]; /* ":%02d" */
extern char D_8009E0A4[]; /* "--" */
extern char D_8009E0A8[]; /* ": --" */
extern char D_8009E0B0[]; /* ": --" */

// hud_time_draw: P153: draws a time of `ticks` (50 per second, at most 99:00.00) as minutes ":" seconds ":"
// hundredths at (x, y) with alpha (text_printf_at); the minutes field moves 5 left from 10 minutes on. A negative
// time draws "--: --: --".
/* was func_150916B4 */
void hud_time_draw(s32 x, s32 y, s32 ticks, u8 alpha) {
    s32 hundredths;
    s32 seconds;
    s32 minutes;
    s32 shift;

    if (ticks >= 297000) {
        ticks = 297000;
    }
    hundredths = (ticks % 50) * 100 / 50;
    if (hundredths >= 100) {
        hundredths = 99;
    }
    x -= 8;
    if (ticks >= 0) {
        seconds = ticks / 50;
        minutes = seconds / 60;
        if (minutes >= 10) {
            shift = 5;
        } else {
            shift = 0;
        }
        text_printf_at(x - shift - 8, y, alpha, (s32) D_8009E090, minutes);
        text_printf_at(x, y, alpha, (s32) D_8009E094, seconds % 60);
        text_printf_at(x + 0x10, y, alpha, (s32) D_8009E09C, hundredths);
        return;
    }
    text_printf_at(x - 8, y, alpha, (s32) D_8009E0A4);
    text_printf_at(x, y, alpha, (s32) D_8009E0A8);
    text_printf_at(x + 0x10, y, alpha, (s32) D_8009E0B0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/hud_time_draw.s")
#endif
#ifdef NON_MATCHING
s32 texture_cache_lookup(s32, s32 *, s32, s32);
Gfx *hud_icon_sheet_load(Gfx *gdl, s32 sheet, u8 *ready);
Gfx *radar_draw(Gfx *, s32, s16 *, s32, s32);
extern Gfx D_80087730[];   /* 2D HUD setup display list */
extern u8 D_80087750[4];   /* initial bar lengths (all 0) */
extern u8 D_80087754[];    /* icon sheet: t of each icon row, in 32nds */
extern u8 D_8008775C[];    /* icon sheet: layout table index of each icon row's height */
extern u8 D_80087764[];    /* placing digits: s column (k & 3), in 32nds */
extern u8 D_80087768[];    /* placing digits: t row (k >> 2), in 32nds */
extern u16 D_80090160;     /* multiplayer HUD element bits */
extern u16 D_8009015C;
extern s8 D_800E0EF0[];    /* team of each view */
extern s8 D_800E1017;      /* number of laps */
extern char D_8009E0B8[];  /* "%d" */
extern char D_8009E0BC[];  /* "(%s)" */
extern char D_8009E0C4[];  /* "%s" */
extern char D_8009E0C8[];  /* "lap %d/%d" */
extern f32 D_8009E23C;     /* map world -> screen scale (0.013) */
extern f32 D_8009E240;     /* map scale factor in hi-res (1.56) */
extern f32 D_8009E244;     /* map centre y offset (3.4) */
extern f32 D_8009E248;     /* map centre x offset (3.6) */

// mp_hud_draw: P208: the multiplayer HUD overlay (hud_draw when D_800BE616 is set). The layout table
// (33 entries, scaled by the hi-res factor D_800901BC, texture step `scale`) is the same as hud_draw's.
// D_80090160 selects the parts, each drawn per view (D_80082FA0 + 1 views, skipped when D_80087270[p] == 10;
// view rectangle D_800BE628: y top 0x24, y bottom 0x28, x left 0x2C, x right 0x30):
//   0x002: placing digit (sheet 0xD16, cell from player_stat_get(p, 3)) at the top left;
//   0x400 / 0x800: score (D_80090174 s16 table at 0x46) / "(team name)" text at the top centre;
//   0x010: two lives bars (sheet 0xD18 cell 0x620 / 0xA0, lengths from player_stat_get(p, 4));
//   0x004: status icons at the top right: icon by the player's state (sheet 0xD18 via hud_icon_sheet_load), and in
//          interaction state 0x1E the vehicle / weapon icons (sheet 0xD19) with a red ammo / fuel bar;
//   the "on fire" counter (sheet 0xD15) for players in state 0x26 / 0x3A, one icon per unit of 0x19A;
//   0x080 (race, D_80087640 records): best / current lap times and "lap n/m";
//   0x1000: the overview map (texture 0xCF3 / 0xCF4) with a dot per player (green = self, red = players,
//          white = other objects with a team);
//   0x020: the radar (radar_draw, not big).
// Returns the advanced display list.
/* was func_150918EC */
Gfx *mp_hud_draw_views(Gfx *gdl) {
    struct_eu_BE628 *view;
    struct127 *obj;
    struct_eu_80087640 *race;
    u8 *st;
    u8 bars[4];
    u8 bar_mode, fire, loaded, ready;
    s16 table[33];
    s32 scale, width, p, i, k, tex, x, y, right, row, icon, count, toff, trow, shift, s, t, ix, iy, h, dy, len;
    s32 wi, hi, size, dot, mx, my, r, cx, cy;
    s8 lap, laps;
    f32 f, zoom, fx, fy;

    for (i = 0; i < 4; i++) {
        bars[i] = D_80087750[i];
    }
    bar_mode = 0;
    fire = 0;
    width = ((struct_eu_BE628 *)D_800BE628)->unk30 - ((struct_eu_BE628 *)D_800BE628)->unk2C;
    gSPDisplayList(gdl++, D_80087730);
    text_set_color(0xFF, 0xFF, 0xFF, 0xFF);

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

    /* placing digit, score and team name */
    if (D_80090160 & 0xC02) {
        loaded = 0;
        ready = 0;
        for (p = 0; p <= D_80082FA0; p++) {
            if (D_80087270[p] == 10) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            y = (f32)table[6] + view->unk24;
            x = view->unk2C;
            if (D_80090160 & 2) {
                if (!loaded) {
                    loaded = 1;
                    tex = texture_cache_lookup(0xD16, NULL, 3, 0);
                    if (tex != 0x80000000) {
                        gdl->words.w0 = 0xFD180000; /* texture image CI8 */
                        gdl->words.w1 = tex;
                        gdl++;
                        gdl->words.w0 = 0xF5180000;
                        gdl->words.w1 = 0x07094250;
                        gdl++;
                        gDPLoadSync(gdl++);
                        gdl->words.w0 = 0xF3000000;
                        gdl->words.w1 = 0x073FF000;
                        gdl++;
                        gDPPipeSync(gdl++);
                        gdl->words.w0 = 0xF5181000;
                        gdl->words.w1 = 0x00094250;
                        gdl++;
                        gdl->words.w0 = 0xF2000000;
                        gdl->words.w1 = 0x0007C07C;
                        gdl++;
                        ready = 1;
                    }
                    gdl->words.w0 = 0xEF002C3F; /* other modes */
                    gdl->words.w1 = 0x00504244;
                    gdl++;
                    gDPPipeSync(gdl++);
                    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0x80);
                }
                ix = table[5] + x;
                k = player_stat_get((s16)p, 3);
                s = D_80087764[k & 3] << 5;
                t = D_80087768[k >> 2] << 5;
                if (ready) {
                    gSPScisTextureRectangle(gdl++, ix * 4, y * 4, (table[5] + ix) * 4, (table[7] + y) * 4,
                                            G_TX_RENDERTILE, s, t, scale, scale);
                }
            }
            if (D_80090160 & 0x400) {
                ix = (width >> 1) + x - 8;
                if (D_800901BC != 1.0f) {
                    ix -= 8;
                }
                text_printf_at(ix, y, 0x41, (s32)D_8009E0B8, *(s16 *)(D_80090174 + 0x46 + p * 2));
            }
            if (D_80090160 & 0x800) {
                ix = (width >> 1) + x + 16;
                if (D_800901BC != 1.0f) {
                    ix += 16;
                }
                text_printf_at(ix, y, 0x41, (s32)D_8009E0BC, ((u8 **)D_800E1008)[8 + D_800E0EF0[p]]);
            }
        }
    }

    /* state icons and lives bars */
    if (D_80090160 & 0x14) {
        loaded = 0;
        ready = 0;
        for (p = 0; p <= D_80082FA0; p++) {
            if (D_80087270[p] == 10) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            f = table[5];
            x = f + view->unk2C;
            right = view->unk30 - f;
            y = f + view->unk24;
            if (D_80090160 & 4) {
                obj = &D_800CC2D0[p];
                st = (u8 *)obj->unk31C;
                count = 1;
                k = st[0x75] & 0x7F;
                if (obj->interaction_state == 0x1F) {
                    k = 0;
                }
                switch (k) {
                case 0x09: icon = 0; break;
                case 0x16: icon = 1; break;
                case 0x14: case 0x3F: icon = 3; break;
                case 0x20: icon = 5; break;
                case 0x18: case 0x41: icon = 6; break;
                case 0x15: icon = 7; break;
                case 0x22: icon = 9; break;
                case 0x23: icon = 10; break;
                case 0x32: case 0x33: count = (s8)st[0x1AE]; icon = 11; break;
                case 0x21: icon = 12; break;
                case 0x24: icon = 13; break;
                case 0x25: icon = 14; break;
                case 0x40: icon = 4; toff = -3; break;
                case 0x26: case 0x3A: /* on fire: counter drawn below */
                    icon = -1;
                    if (obj->health != 0) {
                        fire = 1;
                    }
                    break;
                case 0x38: icon = -1; break;
                default:
                    icon = -1;
                    if (D_800BE9F0 == 0x1A) {
                        icon = 4;
                        toff = 4;
                    }
                    break;
                }
                if (obj->unk13C) {
                    icon = -1;
                }
                if (icon >= 0) {
                    if (!loaded) {
                        loaded = 1;
                        gdl = hud_icon_sheet_load(gdl, 0, &ready);
                    }
                    row = icon / 3;
                    ix = (right - table[25]) * 4;
                    h = table[D_8008775C[row]] * 4;
                    t = D_80087754[row] << 5;
                    dy = 0;
                    if (icon == 4) {
                        dy = 4;
                        h -= 8;
                        t += toff << 5;
                    }
                    if (icon == 1) {
                        h -= 4;
                    }
                    do {
                        if (ready) {
                            gSPTextureRectangle(gdl++, ix, y * 4 + dy, table[22] * 4 + ix, y * 4 + h + dy,
                                                G_TX_RENDERTILE, (icon % 3) * 800, t, scale, scale);
                        }
                        ix -= 18 * 4;
                    } while (--count > 0);
                }
            }
            if (D_80090160 & 0x10) {
                if (!loaded) {
                    gdl = hud_icon_sheet_load(gdl, 0, &ready);
                }
                k = player_stat_get((s16)p, 4);
                ix = table[22] + x;
                len = ((k + 1) >> 1) * 5;
                if (len != 0 && ready) {
                    gSPTextureRectangle(gdl++, (ix - table[len]) * 4, y * 4, ix * 4, (table[4] + y) * 4,
                                        G_TX_RENDERTILE, 0x620, 0xA0, scale, scale);
                }
                len = (k >> 1) * 5;
                if (len != 0 && ready) {
                    gSPTextureRectangle(gdl++, (ix - table[len]) * 4, (table[5] + y) * 4, ix * 4, (table[9] + y) * 4,
                                        G_TX_RENDERTILE, 0x620, 0xA0, scale, scale);
                }
            }
        }
    }

    /* vehicle / weapon icons (state 0x1E) and the second-sheet state icons */
    if (D_80090160 & 4) {
        loaded = 0;
        ready = 0;
        for (p = 0; p <= D_80082FA0; p++) {
            if (D_80087270[p] == 10) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            right = view->unk30 - 5.0f;
            y = view->unk24 + 5.0f;
            obj = &D_800CC2D0[p];
            count = 1;
            icon = -1;
            trow = 0;
            if (obj->interaction_state == 0x1E) {
                st = (u8 *)obj->unk31C;
                k = st[0x128];
                if (k & 1) {
                    icon = 6;
                    shift = 4;
                } else if (k & 2) {
                    icon = 3;
                } else if (k & 0x80) {
                    icon = 0;
                    shift = 6;
                } else if (k & 0x10) {
                    icon = 9;
                    shift = -3;
                }
                if (icon >= 0 && icon != 3) { /* bar from the ammo / fuel count */
                    bar_mode = 1;
                    if (shift > 0) {
                        bars[p] = *(u16 *)(st + 0x12C) >> shift;
                    } else {
                        bars[p] = *(u16 *)(st + 0x12C) << -shift;
                    }
                }
            } else {
                st = (u8 *)obj->unk31C;
                trow = 3;
                switch (st[0x75] & 0x7F) {
                case 0x30: case 0x31: count = (s8)st[0x1AE]; icon = 6; break;
                case 0x37: icon = 7; break;
                case 0x38: icon = 4; break;
                case 0x39: icon = 10; break;
                case 0x3E:
                    bars[p] = *(u16 *)(st + 0x12C) >> 4;
                    bar_mode = 2;
                    break;
                }
            }
            if (icon < 0) {
                continue;
            }
            if (!loaded) {
                loaded = 1;
                gdl = hud_icon_sheet_load(gdl, 1, &ready);
            }
            s = (icon % 3) * 800;
            ix = right - table[25];
            row = icon / 3;
            t = (D_80087754[row] + trow) << 5;
            do {
                if (ready) {
                    gSPTextureRectangle(gdl++, ix * 4, y * 4, (ix + table[22]) * 4, (table[D_8008775C[row]] + y) * 4,
                                        G_TX_RENDERTILE, s, t, scale, scale);
                }
                ix -= 18;
            } while (--count > 0);
        }
    }

    /* red bars */
    if (bar_mode) {
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xEF002C3F; /* other modes: fill */
        gdl->words.w1 = 0x0F0A4004;
        gdl++;
        gdl->words.w0 = 0xFCFFFFFF; /* combine: primitive */
        gdl->words.w1 = 0xFFFDF6FB;
        gdl++;
        gDPSetPrimColor(gdl++, 0, 0, 0xFF, 0x00, 0x00, 0xFF);
        x = (bar_mode == 2) ? 15 : 30;
        for (p = 0; p <= D_80082FA0; p++) {
            if (bars[p] == 0) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            ix = (s32)view->unk30 - x;
            iy = (s32)view->unk24 + 10;
            gDPFillRectangle(gdl++, ix - bars[p], iy, ix, iy + 4);
        }
    }

    /* on-fire counter */
    if (fire) {
        tex = texture_cache_lookup(0xD15, NULL, 3, 0);
        gdl->words.w0 = 0xFD100000; /* texture image RGBA16 */
        gdl->words.w1 = tex;
        gdl++;
        gdl->words.w0 = 0xF5100000;
        gdl->words.w1 = 0x07094250;
        gdl++;
        gDPLoadSync(gdl++);
        gdl->words.w0 = 0xF3000000;
        gdl->words.w1 = 0x073FF000;
        gdl++;
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xF5101000;
        gdl->words.w1 = 0x00094250;
        gdl++;
        gdl->words.w0 = 0xF2000000;
        gdl->words.w1 = 0x0007C07C;
        gdl++;
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xEF002C3F;
        gdl->words.w1 = 0x00504244;
        gdl++;
        for (p = 0; p <= D_80082FA0; p++) {
            obj = &D_800CC2D0[p];
            k = ((u8 *)obj->unk31C)[0x75] & 0x7F;
            if (k != 0x26 && k != 0x3A) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            ix = ((s32)view->unk30 - 15) * 4;
            iy = ((s32)view->unk24 + 5) * 4;
            if (D_800BE9F0 == 0x1A || D_800BE9F0 == 0x3F) {
                wi = 11, hi = 14, s = 0x200, t = 0x1E0;
            } else if (obj->id == 0x75 || obj->id == 0xB1) {
                wi = 5, hi = 20, s = 0xC0, t = 0x100;
            } else if (obj->id == 0x3B) {
                wi = 11, hi = 14, s = 0x200, t = 0x1E0;
            } else {
                wi = 8, hi = 9, s = 0x240, t = 0x60;
            }
            for (i = 0; i < ((u8 *)obj->unk31C)[0x19A]; i++) {
                gSPScisTextureRectangle(gdl++, ix, iy, table[wi] * 4 + ix, table[hi] * 4 + iy, G_TX_RENDERTILE, s, t,
                                        0x400, scale);
                ix -= 11 * 4;
            }
        }
    }

    /* race: lap times and lap counter */
    if ((D_80090160 & 0x80) && D_80087640 != NULL) {
        laps = D_800E1017;
        for (p = 0; p <= D_80082FA0; p++) {
            view = (struct_eu_BE628 *)D_800BE628 + p;
            iy = (s32)view->unk24 + 5;
            text_set_color(0xFF, 0xFF, 0xFF, 0xFF);
            race = &D_80087640[p];
            if (*(s32 *)((u8 *)race + 0x20) > 0) { /* best lap */
                hud_time_draw((s32)view->unk2C + 0x17, iy + 0x19, *(s32 *)((u8 *)race + 0x20), 0xC0);
                race = &D_80087640[p];
            }
            lap = race->unk27 + 1;
            ix = (s32)view->unk2C + (width >> 1);
            if (lap <= laps) {
                text_printf_at(ix, iy, 0xC1, (s32)D_8009E0C4, ((u8 **)D_800E1008)[8 + D_800E0EF0[p]]);
                text_printf_at((s32)view->unk2C + 0x1D, iy + 0xE, 0xC1, (s32)D_8009E0C8, lap, laps);
                hud_time_draw(ix, (s32)view->unk28 - 0xC, *(s32 *)((u8 *)&D_80087640[p] + 0x1C), 0xC0);
            }
        }
    }

    /* overview map */
    if (D_800BEAC1 == 0 && (D_80090160 & 0x1000)) {
        zoom = D_8009E23C;
        mx = ((s32)((struct_eu_BE628 *)D_800BE628)->unk30 - table[32]) * 4;
        if (D_800901BC != 1.0f) {
            zoom = D_8009E23C * D_8009E240;
            size = 0x63;
            dot = 6;
        } else {
            size = 0x40;
            dot = 4;
        }
        tex = texture_cache_lookup((D_8009015C & 0x40) ? 0xCF4 : 0xCF3, NULL, 3, 0);
        gdl->words.w0 = 0xFD700000; /* texture image IA16 */
        gdl->words.w1 = tex;
        gdl++;
        gdl->words.w0 = 0xF5700000;
        gdl->words.w1 = 0x07098260;
        gdl++;
        gDPLoadSync(gdl++);
        gdl->words.w0 = 0xF3000000;
        gdl->words.w1 = 0x077FF000;
        gdl++;
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xF5681000;
        gdl->words.w1 = 0x00098260;
        gdl++;
        gdl->words.w0 = 0xF2000000;
        gdl->words.w1 = 0x000FC0FC;
        gdl++;
        gdl->words.w0 = 0xEF002C3F;
        gdl->words.w1 = 0x00504244;
        gdl++;
        for (p = 0; p < D_80090130; p++) {
            if (player_stat_get((s16)p, 3) <= 0) {
                continue;
            }
            view = (struct_eu_BE628 *)D_800BE628 + p;
            my = (table[24] + (s32)view->unk24 + table[21]) * 4;
            gDPPipeSync(gdl++);
            gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0x80);
            gdl->words.w0 = 0xFC129A25; /* combine */
            gdl->words.w1 = 0xFF37FFFF;
            gdl++;
            r = table[32] * 4;
            gSPScisTextureRectangle(gdl++, mx - r, my - r, size * 4 + (mx - r), size * 4 + (my - r), G_TX_RENDERTILE,
                                    0, 0, scale, scale);
            gDPPipeSync(gdl++);
            gdl->words.w0 = 0xFC62FEC5;
            gdl->words.w1 = 0xFFFFFBFD;
            gdl++;
            for (i = 0; i < 25; i++) {
                obj = &D_800CC2D0[i];
                if (i != p && !(i < D_8008FD8C && player_stat_get((s16)i, 3) > 0) && obj->unk328 == 0) {
                    continue;
                }
                gDPPipeSync(gdl++);
                fy = (f32)my + D_8009E244;
                fx = (f32)mx + D_8009E248;
                if (i == p) {
                    gDPSetEnvColor(gdl++, 0x00, 0xFF, 0x00, 0xFF);
                } else if (i < D_8008FD8C) {
                    gDPSetEnvColor(gdl++, 0xFF, 0x00, 0x00, 0xFF);
                } else {
                    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0xFF);
                }
                cx = fx + (f32)(s32)(obj->x_position * zoom);
                cy = fy + (f32)(s32)(obj->z_position * zoom);
                gSPScisTextureRectangle(gdl++, cx - dot, cy - dot, cx + dot, cy + dot, G_TX_RENDERTILE, 0, 0, 0x400,
                                        0x400);
            }
        }
    }

    if (D_800BEAC1 == 0 && (D_80090160 & 0x20)) {
        gdl = radar_draw(gdl, scale, table, 0x2C30, 0);
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/mp_hud_draw_views.s")
#endif

/* was func_15093818 */
void hud_clock_set_enabled(s32 arg0) {
    if ((arg0 != 0) && (D_800D2458 == 0)) {
        D_800D2458 = 1;
        hud_clock_load();
        return;
    }
    if ((arg0 == 0) && (D_800D2458 != 0)) {
        D_800D2458 = 0;
    }
}

/* was func_15093878 */
void hud_clock_load(void) {
    D_800D2448 = shared_dl_acquire(0xBA);
    D_800D244C = allocate_memory(0x80, 1, 1, 0);
}

#ifdef NON_MATCHING
void mtx_translate_fixed(s32, f32, f32, f32);
s32 texture_cache_lookup(s32, s32 *, s32, s32);
extern s32 D_11AF;
extern s32 D_800D2870;

/* was func_150938BC */
s32 *hud_clock_draw(s32 *arg0) {
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
    temp_v0 = texture_cache_lookup((s32)((u8 *)&D_11AF + (var_s1 % 10)), NULL, 3, 0);
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
        mtx_translate_fixed((D_800BE9C0 << 6) + D_800D244C, (f32) 0x78, (f32) 0x81, (f32) -0x12F);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/hud_clock_draw.s")
#endif
#ifdef NON_MATCHING
s32 rail_band_for_height(f32 y);
extern f32 D_8009E24C; /* radar world -> screen scale, 2-4 players (0.0135) */
extern f32 D_8009E250; /* radar zoom of the big radar (1.329) */
extern f32 D_8009E254; /* radar world -> screen scale, 1 player (0.02025) */
extern f32 D_8009E258; /* big radar disc size factor (0.858) */
extern f32 D_8009E25C; /* big radar texture step factor (1.1655) */
extern f32 D_8009E260; /* degrees -> radians */
extern u8 D_800ABA0C[]; /* radar dot colours: r, g, b per team (unk328 - 1) */
extern u16 D_800E0FFC;  /* bit per player object: hidden from the radar */

// radar_draw: P206: draws the multiplayer radar of every active view (hud_draw / mp_hud_draw_views). The radar
// disc (texture 0xCF5, IA16 32x32) sits at the view's corner from the view rectangle (D_800BE628) and the layout
// table (table[7] / table[21] the corner offsets, table[16] the radius, table[24] in one-player mode, where the
// texture step is size * 2 / 3); `big` moves it by (-0x1C6, -0x46) quarter pixels and scales it. Every other
// object slot 0..24 with a team (unk328) inside the range is drawn as a coloured dot, rotated by the view's yaw
// (D_800DBFF0[p].unk37C, degrees); for the player slots below D_8008FD8C the dot is hidden when the player is
// out of the game (player_stat_get modes 3 / 4), flagged in D_800E0FFC, dead, or in state 0x21. A black mark above
// or below the dot shows a different height level (rail_band_for_height). When the view's object is in state 0x25 the
// radar centres on player 0 (or 1 when its camera mode is 3), which is skipped as well. Returns the advanced DL,
// or `gdl` unchanged when the texture is not loaded.
/* was func_15093B58 */
Gfx *radar_draw(Gfx *gdl, s32 size, s16 *table, s32 mode, s32 big) {
    struct_eu_BE628 *view;
    struct127 *me, *ref, *obj;
    u8 *col;
    s32 p, i, self, team, half, dot, x0, y0, r, dsdx, tex, cx, cy;
    s8 my_level, level;
    f32 scale, range, zoom, rx, rz, s, c, dx, dz, angle;

    scale = D_8009E24C;
    range = 3136.0f;
    half = table[16];
    if ((u8)big) {
        zoom = D_8009E250;
    } else {
        zoom = 1.0f;
    }
    if (D_80090130 == 1) {
        scale = D_8009E254;
        range = 7744.0f;
        size = (size * 2) / 3;
        half = table[24];
    }
    scale *= D_800901BC;
    range *= D_800901BC;
    dot = 6;
    if (D_800901BC == 1.0f) {
        dot = 4;
    }
    tex = texture_cache_lookup(0xCF5, NULL, 3, 0);
    if (tex == 0x80000000) {
        return gdl;
    }
    gdl->words.w0 = 0xFD700000; /* texture image IA16 */
    gdl->words.w1 = tex;
    gdl++;
    gdl->words.w0 = 0xF5700000;
    gdl->words.w1 = 0x07094250;
    gdl++;
    gdl->words.w0 = 0xE6000000;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xF3000000;
    gdl->words.w1 = 0x071FF000;
    gdl++;
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    gdl->words.w0 = 0xF5680800;
    gdl->words.w1 = 0x00094250;
    gdl++;
    gdl->words.w0 = 0xF2000000;
    gdl->words.w1 = 0x0007C07C;
    gdl++;
    gdl->words.w0 = 0xEF000000 | ((mode | 0xF) & 0xFFFFFF); /* other modes */
    gdl->words.w1 = 0x00504244;
    gdl++;

    for (p = 0; p < D_80090130; p++) {
        if (player_stat_get((s16)p, 3) <= 0) {
            continue;
        }
        view = (struct_eu_BE628 *)D_800BE628 + p;
        x0 = ((s32)view->unk30 - table[7] - half) * 4;
        y0 = (table[21] + (s32)view->unk24 + half) * 4;
        me = &D_800CC2D0[p];
        if ((u8)big) {
            x0 -= 0x1C6;
            y0 -= 0x46;
        }
        gdl->words.w0 = 0xE7000000;
        gdl->words.w1 = 0;
        gdl++;
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = 0xFFFFFF80;
        gdl++;
        gdl->words.w0 = 0xFC129A25;
        gdl->words.w1 = 0xFF37FFFF;
        gdl++;
        if ((u8)big) {
            r = (f32)(half * 4) * D_8009E258;
            dsdx = (f32)(s32)(f32)size * D_8009E25C;
        } else {
            r = half * 4;
            dsdx = size;
        }
        /* the radar disc */
        gSPScisTextureRectangle(gdl++, x0 - r, y0 - r, x0 + r, y0 + r, G_TX_RENDERTILE, 0, 0, dsdx, dsdx);
        gdl->words.w0 = 0xE7000000;
        gdl->words.w1 = 0;
        gdl++;
        gdl->words.w0 = 0xFC62FEC5;
        gdl->words.w1 = 0xFFFFFBFD;
        gdl++;
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = 0xFF0000FF;
        gdl++;

        angle = D_800DBFF0[p].unk37C * D_8009E260;
        s = sinf(angle);
        c = cosf(angle);
        if (me->interaction_state != 0x25) {
            self = -1;
            ref = me;
        } else {
            self = 0;
            if (me->camera != NULL && me->camera->unk23D == 3) {
                self = 1;
            }
            ref = &D_800CC2D0[self];
        }
        rx = ref->x_position;
        rz = ref->z_position;
        my_level = rail_band_for_height(ref->y_position);

        for (i = 0; i < 25; i++) {
            if (i == p || i == self) {
                continue;
            }
            obj = &D_800CC2D0[i];
            if (obj->interaction_state == 0 || obj->unk328 == 0) {
                continue;
            }
            team = obj->unk328 - 1;
            if (i < D_8008FD8C) {
                if (player_stat_get((s16)i, 3) <= 0 || player_stat_get((s16)i, 4) <= 0 || (D_800E0FFC & (1 << i)) ||
                    obj->health == 0 || (((u8 *)obj->unk31C)[0x75] & 0x7F) == 0x21) {
                    team = -1;
                }
            }
            if (team == -1) {
                continue;
            }
            dx = (obj->x_position - rx) * scale;
            dz = (obj->z_position - rz) * scale;
            if (!(dx * dx + dz * dz < range)) {
                continue;
            }
            col = &D_800ABA0C[team * 3];
            gdl->words.w0 = 0xE7000000;
            gdl->words.w1 = 0;
            gdl++;
            gdl->words.w0 = 0xFB000000;
            gdl->words.w1 = (col[0] << 24) | (col[1] << 16) | (col[2] << 8) | 0xFF;
            gdl++;
            cx = (s32)((dx * c - dz * s) * zoom) + x0;
            cy = (s32)((dx * s + dz * c) * zoom) + y0;
            gSPScisTextureRectangle(gdl++, cx - dot, cy - dot, cx + dot, cy + dot, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);

            level = rail_band_for_height(obj->y_position);
            if (level == my_level) {
                continue;
            }
            gdl->words.w0 = 0xE7000000;
            gdl->words.w1 = 0;
            gdl++;
            gdl->words.w0 = 0xFB000000;
            gdl->words.w1 = 0x000000FF;
            gdl++;
            if (my_level < level) { /* higher: mark above the dot */
                gSPScisTextureRectangle(gdl++, cx - dot, cy - dot * 2, cx + dot, cy - dot, G_TX_RENDERTILE, 0, 0,
                                        0x400, 0x400);
            } else if (level < my_level) { /* lower: mark below */
                gSPScisTextureRectangle(gdl++, cx - dot, cy + dot, cx + dot, cy + dot * 2, G_TX_RENDERTILE, 0, 0,
                                        0x400, 0x400);
            }
        }
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_BC510/radar_draw.s")
#endif
