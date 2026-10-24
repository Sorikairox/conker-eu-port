#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
Gfx *func_15096D44(Gfx *arg0);
Gfx *func_151EDBE8(Gfx *, void *, s32, s32, s32, s32, f32, s32);
extern Gfx D_800903D8[];
u8 *func_1501A6CC(u8 *, s32, s32, s32, s32);
extern s32 D_80090410;
extern s32 D_80091BA8;
Gfx *func_151EDA54(Gfx *, u8 *, s32 *);
extern u8 D_8009E28C[];
extern u8 D_8009E280[];
extern u8 D_8009E284[];
extern u8 D_8009E288[];
#endif


Gfx *func_151ED998(Gfx *gdl);
#ifdef NON_MATCHING
/* P120: the definition (game_70200) is varargs; a fixed-arg prototype gives a different wasm signature. */
void func_15042D94(s32, s32, s32, void *, ...);
#else
void func_15042D94(s32, s32, s32, void *);
#endif
extern Gfx *(*D_800903A4[])(Gfx *);
extern u8 D_800BEB60;

Gfx *func_151E8C60(Gfx *gdl) {
    s32 msg;
    Gfx *(*fn)(Gfx *);

    D_8003C8E0 = 0x09000001;
    msg = 0;
    gdl = func_151ED998(gdl);
    fn = D_800903A4[D_800E0B94];
    if (fn != NULL) {
        gdl = fn(gdl);
    }
    if (D_80000300 == 0) {
        if (D_800BE616 != 0 && D_80090130 >= 2) {
            if ((D_800BEB60 & 0xF) == 0) {
                if (D_800E1003 == 1) {
                    msg = 0x33;
                } else if (D_800E1003 == 2) {
                    msg = 0x16;
                }
            }
        } else if ((D_800BEB60 & 1) == 0) {
            if (D_800E1003 == 1) {
                msg = 0x32;
            } else if (D_800E1003 == 2) {
                msg = 0x15;
            }
        }
    }
    if (msg != 0) {
        func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
        func_15042D94(0x94, 0xC8, 0x81, ((void **)D_800E1008)[msg]);
    }
    D_8003C8E0 = 0;
    return gdl;
}

extern Gfx *(*D_80090370[])(Gfx *);
extern s32 D_80090408;
extern s32 D_800BEFC4;
extern s16 D_800E10A8;
Gfx *func_151E8620(Gfx *arg0) {
    Gfx *(*temp_a1)(Gfx *);
    Gfx *temp_a2;
    s32 var_v0;
    u8 temp_v1;
    temp_v1 = D_800E0B94;
    temp_a2 = arg0;
    D_8003C8E0 = 0x09000000;
    temp_a1 = D_80090370[temp_v1];
    if (temp_a1 != NULL) {
        arg0 = temp_a1(arg0);
    }
    if (D_800E0B94 != 0) {
        D_80090408 = 0;
        D_800E10A8 = 0;
    }
    D_8003C8E0 = 0;
    if (D_800BEFC4 < (arg0 - D_800BEDE8[D_800BE9C0])) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    if (var_v0 != 0) {
        return temp_a2;
    }
    return arg0;
}

#ifdef NON_MATCHING
extern f32 D_800901BC;
extern f32 D_800901C0;

u8 *func_151E8E94(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s16 var_t0;
    s16 var_t0_2;
    s16 var_t1;
    s16 var_t1_2;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t7;
    s32 var_a2;
    s32 var_t1_3;
    s32 var_t2;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_a0;
    u8 *temp_a0_2;

    var_a2 = arg2;
    if (D_800901BC != 1.0f) {
        arg1 = (s32) ((f32) arg1 * D_800901BC);
        arg3 = (s32) ((f32) arg3 * D_800901BC);
        var_a2 = (s32) ((f32) var_a2 * D_800901C0);
        arg4 = (s32) ((f32) arg4 * D_800901C0);
        arg8 = (s32) ((f32) arg8 / D_800901BC);
        arg9 = (s32) ((f32) arg9 / D_800901C0);
    }
    temp_a0_2 = arg0 + 8;
    if ((s16) arg3 > 0) {
        var_t0 = (s16) arg3;
    } else {
        var_t0 = 0;
    }
    if ((s16) arg4 > 0) {
        var_t1 = (s16) arg4;
    } else {
        var_t1 = 0;
    }
    (*(s32 *)((u8 *)arg0 + 0)) = (s32) ((var_t1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
    if ((s16) arg1 > 0) {
        var_t0_2 = (s16) arg1;
    } else {
        var_t0_2 = 0;
    }
    if ((s16) var_a2 > 0) {
        var_t1_2 = (s16) var_a2;
    } else {
        var_t1_2 = 0;
    }
    (*(s32 *)((u8 *)arg0 + 4)) = (s32) ((var_t1_2 & 0xFFF) | ((arg5 & 7) << 0x18) | ((var_t0_2 & 0xFFF) << 0xC));
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xE1000000;
    temp_a0 = temp_a0_2 + 8;
    if ((s16) arg1 < 0) {
        if ((s16) arg8 < 0) {
            temp_t5 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t5 > 0) {
                var_t2 = temp_t5;
            } else {
                var_t2 = 0;
            }
        } else {
            var_v0 = 0;
            temp_t4 = (s32) ((s16) arg1 * (s16) arg8) >> 7;
            if (temp_t4 < 0) {
                var_v0 = temp_t4;
            }
            var_t2 = var_v0;
        }
    } else {
        var_t2 = 0;
    }
    if (var_a2 < 0) {
        if ((s16) arg9 < 0) {
            temp_t7 = (s32) ((s16) var_a2 * (s16) arg9) >> 7;
            if (temp_t7 > 0) {
                var_t1_3 = temp_t7;
            } else {
                var_t1_3 = 0;
            }
        } else {
            var_v0_2 = 0;
            temp_t6 = (s32) ((s16) var_a2 * (s16) arg9) >> 7;
            if (temp_t6 < 0) {
                var_v0_2 = temp_t6;
            }
            var_t1_3 = var_v0_2;
        }
    } else {
        var_t1_3 = 0;
    }
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = (s32) (((arg7 - var_t1_3) & 0xFFFF) | ((arg6 - var_t2) << 0x10));
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xF1000000;
    (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) ((arg8 << 0x10) | (arg9 & 0xFFFF));
    return temp_a0 + 8;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E8E94.s")
#endif
#ifdef NON_MATCHING
extern u16 D_8009015C;           /* HUD state: 0x10 = a player is near the target point */
extern u16 D_80090160;           /* HUD elements: 1 / 8 team scores, 0x4000 / 0x8000 carried item, 0x6340 timer */
extern s8 D_800E0FE0;            /* team count */
extern u16 D_800E0FFC;           /* players marked on the HUD (bit per player) */
extern u8 D_800ABEA0[][4];       /* team colours (r, g, b) */
extern u8 D_8009041C[4];         /* digit -> sheet column */
extern u8 D_80090420[];          /* digit -> sheet row */
extern s32 D_800BEDCC;           /* frame counter */
s32 func_1508712C(s32, f32 *, f32 *, f32 *);
s32 func_150871B8(s32);
s32 func_1510D66C(s32, s32, s32, s32);
u8 *func_151E9E1C(u8 *, s32, s32, s32, s32);
u8 *func_151EA4C8(u8 *, s32, s32);
#define HUD_W(g, a, b) ((g)->words.w0 = (a), (g)->words.w1 = (b), (g)++)
/* mp_hud_draw: the multiplayer HUD overlay; returns the new DL end. `alpha` is the overlay alpha (low byte), the
 * second argument is unused. Marks the players to show in D_800E0FFC (active or flagged players, players of kind
 * 0x25 near rail point 0x49: within 2500 units also sets D_8009015C 0x10 and the "near" icon), remembers the last
 * flagged player's team (+0x128) as the carrier (with D_80090160 0x8000 it becomes the left / right arrow flag
 * instead), and the bonus flag 4 for team 1 with +0x2E4. Every 32 frames the first 11 clear all of that (blink).
 * Then: the team score row (D_80090160 8; texture 0xD16, per team its colour bar and the score in digits from the
 * D_8009041C / D_80090420 sheet), the team panel func_151E9E1C (1), the carried-item / near icons (texture 0xD18,
 * 0xD19 with 0x4000), the side arrows / bonus icon (texture 0xD12, 0xD13 with flag 4) and the timer func_151EA4C8
 * (0x6340). */
u8 *func_151E9150(u8 *buf, s32 unused, s32 alpha) {
    Gfx *gdl = (Gfx *) buf;
    struct127 *p;
    s32 y, pitch, x, team, score, q, div, dx, started, done, tex, id, size, w, off, row, i, sel;
    u8 near, flags;
    f32 px, py, pz, ddx, ddz;

    flags = 0;
    D_8009015C &= ~0x10;
    gSPDisplayList(gdl++, D_800903D8);
    gDPSetCombine(gdl++, 0x12FE25, 0xFFFFF3F9);
    y = (D_80082FA0 == 0) ? 0x320 : 0x198;
    pitch = 0x124;
    if (D_800E0FE0 > 0) {
        pitch = 0x124 / D_800E0FE0;
    }
    D_800E0FFC = 0;
    near = 0;
    sel = -1;
    for (i = 0; i < D_8008FD8C; i++) {
        p = &D_800CC2D0[i];
        if (p->unk13C != 0 || (*(u8 *) ((u8 *) p->unk31C + 0x128) & 0x20)) {
            D_800E0FFC |= 1 << i;
            sel = p->unk128;
        }
        if (sel != -1 && (D_80090160 & 0x8000)) {
            if (sel == 0) {
                flags |= 2;
            } else {
                flags |= 1;
            }
            sel = -1;
        }
        if (p->unk128 == 1 && p->unk2E4 != 0 && (D_80090160 & 0x4000)) {
            flags |= 4;
        }
        if ((*(u8 *) ((u8 *) p->unk31C + 0x75) & 0x7F) == 0x25) {
            func_1508712C(func_150871B8(0x49), &px, &py, &pz);
            ddx = px - p->x_position;
            ddz = pz - p->z_position;
            if (ddx * ddx + ddz * ddz < 6250000.0f) {
                near = 1;
                D_8009015C |= 0x10;
            }
            D_800E0FFC |= 1 << i;
        }
    }
    if ((D_800BEDCC & 0x1F) < 11) {
        D_800E0FFC = 0;
        near = 0;
        sel = -1;
        flags = 0;
    }
    tex = 0;
    if (D_80090160 & 9) {
        tex = func_1510D66C(0xD16, 0, 3, 0);
        if (tex != (s32) 0x80000000) {
            HUD_W(gdl, 0xFD180000, tex);        /* SetTImg RGBA32 */
            HUD_W(gdl, 0xF5180000, 0x07094250); /* SetTile (load) */
            gDPLoadSync(gdl++);
            HUD_W(gdl, 0xF3000000, 0x073FF000); /* LoadBlock */
            gDPPipeSync(gdl++);
            HUD_W(gdl, 0xF5181000, 0x00094250); /* SetTile (render) */
            HUD_W(gdl, 0xF2000000, 0x0007C07C); /* SetTileSize 32x32 */
            gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        } else {
            tex = 0;
        }
    }
    if ((D_80090160 & 8) && tex != 0) {
        x = pitch >> 1;
        for (team = 0; team < D_800E0FE0; team++) {
            started = 0;
            done = 0;
            score = func_150859AC((s16) team, 6);
            gDPPipeSync(gdl++);
            gDPSetEnvColor(gdl++, D_800ABEA0[team][0], D_800ABEA0[team][1], D_800ABEA0[team][2], alpha & 0xFF);
            dx = (x + 10) * 4;
            gdl = (Gfx *) func_151E8E94((u8 *) gdl, (x + 3) * 4, y, dx, y + 0x1C, 0, 0x1C0, 0x200, 0x400, 0x400);
            div = 10000;
            do {
                q = score / div;
                if (q != 0 || started || div == 1) {
                    started = 1;
                    gdl = (Gfx *) func_151E8E94((u8 *) gdl, dx, y, dx + 0x14, y + 0x1C, 0, D_8009041C[q & 3] << 5,
                                                D_80090420[q >> 2] << 5, 0x400, 0x400);
                    dx += 0x18;
                }
                score -= q * div;
                if (div == 1) {
                    done = 1;
                }
                div /= 10;
            } while (!done);
            x += pitch;
        }
    }
    if (D_80090160 & 1) {
        gdl = (Gfx *) func_151E9E1C((u8 *) gdl, y, sel, 0, 1);
    }
    if (near || sel != -1) {
        id = (D_80090160 & 0x4000) ? 0xD19 : 0xD18;
        tex = func_1510D66C(id, 0, 3, 0);
        if (tex != (s32) 0x80000000) {
            HUD_W(gdl, 0xFD500000, tex);        /* SetTImg CI 8-bit */
            HUD_W(gdl, 0xF5500000, 0x07098260); /* SetTile (load) */
            gDPLoadSync(gdl++);
            HUD_W(gdl, 0xF3000000, 0x073FF000); /* LoadBlock */
            gDPPipeSync(gdl++);
            HUD_W(gdl, 0xF5400800, 0x00098260); /* SetTile (render) */
            HUD_W(gdl, 0xF2000000, 0x000FC0FC); /* SetTileSize 64x64 */
            HUD_W(gdl, 0xFD100000, tex + 0x800); /* SetTImg: the palette after the texels */
            gDPLoadSync(gdl++);
            HUD_W(gdl, 0xF0000000, 0x0603C000); /* LoadTLUT */
            gDPSetOtherMode(gdl++, 0x00AC3F, 0x504244);
            gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, alpha & 0xFF);
            if (near) {
                gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x238, 0xC, 0x268, 0x48, 0, 0x640, 0x660, 0x400, 0x400);
            }
            if (sel != -1) {
                if (D_80090160 & 0x4000) {
                    gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x220, 0xC, 0x250, 0x48, 0, 0x600, 0x540, 0x400, 0x400);
                } else {
                    if (D_80090160 & 1) {
                        row = 0x1A;
                        off = 0;
                    } else {
                        row = 0x26;
                        off = 0xB;
                    }
                    gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x238, (off + 3) * 4, 0x268, (off + 0xE) * 4, 0, 0x640,
                                                row << 5, 0x400, 0x400);
                }
            }
        }
    }
    size = 0x20;
    if (flags != 0) {
        id = 0xD12;
        if (flags & 4) {
            id = 0xD13;
            size = 0x10;
        }
        tex = func_1510D66C(id, 0, 3, 0);
        if (tex != (s32) 0x80000000) {
            gDPPipeSync(gdl++);
            HUD_W(gdl, 0xFD180000, tex);        /* SetTImg RGBA32 */
            HUD_W(gdl, 0xF5180000, 0x07094250); /* SetTile (load) */
            gDPLoadSync(gdl++);
            w = size * 32 - 1;
            if (w >= 0x7FF) {
                w = 0x7FF;
            }
            HUD_W(gdl, 0xF3000000, 0x07000000 | ((w & 0xFFF) << 12)); /* LoadBlock */
            gDPPipeSync(gdl++);
            HUD_W(gdl, 0xF5180000 | ((((size * 2 + 7) >> 3) & 0x1FF) << 9), 0x00094250); /* SetTile (render) */
            HUD_W(gdl, 0xF2000000, ((((size - 1) * 4) & 0xFFF) << 12) | 0x7C);       /* SetTileSize */
            gDPSetOtherMode(gdl++, 0x000C3F, 0x504244);
            gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0xFF);
            if (flags & 1) {
                gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0xA0, y - 0x10, 0xE0, y + 0x30, 0, 0, 0x200, 0x400, 0x400);
            }
            if (flags & 2) {
                gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x3B0, y - 0x10, 0x3F0, y + 0x30, 0, 0x200, 0x200, 0x400, 0x400);
            }
            if (flags & 4) {
                gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x250, 0xC, 0x280, 0x48, 0, 0, 0x200, 0x400, 0x400);
            }
        }
    }
    if (D_80090160 & 0x6340) {
        gdl = (Gfx *) func_151EA4C8((u8 *) gdl, y, 1);
    }
    return (u8 *) gdl;
}
#undef HUD_W
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E9150.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151E9E1C.s")

#ifdef NON_MATCHING
extern s16 D_800E0ED0[];         /* team score */
extern char D_800ABEB0[], D_800ABEB4[];
s32 func_1510D66C(s32, s32, s32, s32);
u8 *func_151E8E94(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
#define TW_W(g, a, b) ((g)->words.w0 = (a), (g)->words.w1 = (b), (g)++)
/* mp_team_score_draw: P237. The two-team score panel (Total War and the other team modes; func_151E9150 /
 * func_151EA90C call it with D_80090160 0x6340) at screen row `y` - 16; returns the new DL end (`buf` unchanged
 * when the texture is not loaded). Texture: 0xD12 (32 x 32) normally, 16 x 16 0xD13 with D_80090160 0x4000 or 0xD14
 * in barrel mode 8 (D_80090174 + 0x42); loaded as RGBA32 with an env colour of white. With `update` the scores are
 * recomputed and stored in D_800E0ED0[0] / [1]: with 0x6040 the team totals func_150859AC(team, 6); with 0x100 the
 * sum of func_150859AC(player, 3) (negative = 0) per team (+0x128 of D_800CC2D0[player]); else the barrel rows'
 * s16 +0x46 (negative = 0) by D_800E1030 team, and the icons use the lower half of the sheet (t + 0x200). Without
 * `update` the stored scores are drawn. Two icons (x 0x108 and 0x318, 0x40 high; 32 x 32: the right half of the sheet
 * then the left; 16 x 16: the upper then the lower), then the scores in grey (D_800ABEB0 team 1 at x 0x4F,
 * D_800ABEB4 team 0 at x 0xD3, text row y / 4 - 3). */
u8 *func_151EA4C8(u8 *buf, s32 y, s32 update) {
    Gfx *gdl = (Gfx *) buf;
    s32 top, size, tex, ls, lt, score0, score1, i, n, v, lrs, row;

    top = y - 0x10;
    if (!(D_80090160 & 0x4000) && *(s8 *) (D_80090174 + 0x42) != 8) {
        tex = 0xD12;
        size = 0x20;
        ls = 0x200;
        lt = 0;
    } else {
        tex = 0xD13;
        size = 0x10;
        if (*(s8 *) (D_80090174 + 0x42) == 8) {
            tex = 0xD14;
        }
        ls = 0;
        lt = 0x200;
    }
    tex = func_1510D66C(tex, 0, 3, 0);
    if (tex == (s32) 0x80000000) {
        return buf;
    }
    gDPPipeSync(gdl++);
    TW_W(gdl, 0xFD180000, tex);                                     /* SetTImg RGBA32 */
    TW_W(gdl, 0xF5180000, 0x07094250);                              /* SetTile (load) */
    gDPLoadSync(gdl++);
    lrs = size * 32 - 1;
    if (lrs >= 0x7FF) {
        lrs = 0x7FF;
    }
    TW_W(gdl, 0xF3000000, 0x07000000 | ((lrs & 0xFFF) << 12));      /* LoadBlock */
    gDPPipeSync(gdl++);
    TW_W(gdl, 0xF5180000 | ((((size * 2 + 7) >> 3) & 0x1FF) << 9), 0x00094250); /* SetTile (render) */
    TW_W(gdl, 0xF2000000, ((((size - 1) * 4) & 0xFFF) << 12) | 0x7C);  /* SetTileSize */
    TW_W(gdl, 0xEF000C3F, 0x00504244);                              /* SetOtherMode */
    TW_W(gdl, 0xFB000000, 0xFFFFFFFF);                              /* SetEnvColor white */

    row = 0;
    score0 = 0;
    score1 = 0;
    if (update) {
        if (D_80090160 & 0x6040) {
            score0 = func_150859AC(0, 6);
            score1 = func_150859AC(1, 6);
        } else if (D_80090160 & 0x100) {
            for (i = 0; i < D_8008FD8C; i++) {
                v = func_150859AC((s16) i, 3);
                if (v < 0) {
                    v = 0;
                }
                if (D_800CC2D0[i].unk128 != 0) {
                    score1 += v;
                } else {
                    score0 += v;
                }
            }
        } else {
            row = 0x200;
            n = D_8008FD8C;
            for (i = 0; i < n; i++) {
                v = *(s16 *) (D_80090174 + 0x46 + i * 2);
                if (v < 0) {
                    v = 0;
                }
                if (D_800E1030[i] != 0) {
                    score1 += v;
                } else {
                    score0 += v;
                }
            }
        }
        D_800E0ED0[0] = score0;
        D_800E0ED0[1] = score1;
    } else {
        score0 = D_800E0ED0[0];
        score1 = D_800E0ED0[1];
    }
    gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x108, top, 0x148, top + 0x40, 0, ls, row, 0x400, 0x400);
    gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x318, top, 0x358, top + 0x40, 0, 0, row + lt, 0x400, 0x400);
    func_1504332C(0xC0, 0xC0, 0xC0, 0xFF);
    func_15042D94(0x4F, (top >> 2) + 1, 0x80, D_800ABEB0, score1);
    func_15042D94(0xD3, (top >> 2) + 1, 0x80, D_800ABEB4, score0);
    return (u8 *) gdl;
}
#undef TW_W
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EA4C8.s")
#endif

#ifdef NON_MATCHING
extern s8 D_800901E4[4];         /* player queue (controller numbers, -1 empty) */
extern s8 D_800E0EF0[];          /* placing per team / player (1 = first) */
extern s16 D_800E0ED0[];         /* team score */
extern s16 D_800E0F00[];         /* per player value (last column) */
extern s8 D_8009011C;
extern char D_800ABEB8[], D_800ABEBC[], D_800ABEC0[], D_800ABEC8[], D_800ABECC[], D_800ABED0[], D_800ABED4[];
s32 func_1510D66C(s32, s32, s32, s32);
u8 *func_151E9E1C(u8 *, s32, s32, s32, s32);
u8 *func_151EA4C8(u8 *, s32, s32);
#define BAR_W(g, a, b) ((g)->words.w0 = (a), (g)->words.w1 = (b), (g)++)
#define BAR_MODE() (*(s8 *) (D_80090174 + 0x42))
#define BAR_ROW(i, off) (*(s16 *) (D_80090174 + (i) * 12 + (off)))
/* mp_scoreboard_draw: the multiplayer score table (barrel menu mode 3 bar of func_151ECE00, and the in-match HUD
 * with `hud` set); returns the new DL end. Menu modes 11 / 12: only the controller icons of the player queue
 * D_800901E4 (texture 0x843; nothing in the HUD). Otherwise one row per queued player that is not a spectator
 * (D_80087270 != 10) and has a team (D_800E1030; team 0 too in mode 8): the header (textures 0x887 / 0x888:
 * columns, team column with D_80090160 1, no kills column in mode 1) before the first row, then the controller icon
 * in the team colour D_800ABEA0, the placing name (D_800E1008 strings from D_800E0EF0, the second table with
 * D_800E1003 == 2), the team score D_800E0ED0, the hit percentage (+0x66 * 100 / shots, shots from the player's
 * +0x1AA in the HUD, else +0x6C; at most 9999), the score +0x46, the lives +0x6A (or the D_800ABECC mark for
 * player state 9) unless mode 1, and D_800E0F00. Rows start at `y` (40 higher with D_800E0B94 and D_80090168) and
 * are 15 apart. Ends with the timer func_151EA4C8 (D_80090160 0x6340) and, in the HUD, the team panel. */
u8 *func_151EA90C(Gfx *gdl, s32 y, s16 alpha, s32 hud) {
    s8 *q;
    s32 tex, yy, k, i, team, base, fmt, x, hy, v, pct, r;
    s8 wide, hdr, all;

    if (BAR_MODE() == 11 || BAR_MODE() == 12) {
        if (hud) {
            return (u8 *) gdl;
        }
        gDPPipeSync(gdl++);
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, alpha & 0xFF);
        gDPSetCombine(gdl++, 0x12D225, 0xFFA7FFFF);
        tex = func_1510D66C(0x843, 0, 3, 0);
        if (tex == (s32) 0x80000000) {
            return (u8 *) gdl;
        }
        BAR_W(gdl, 0xFD180000, tex);        /* SetTImg RGBA32 */
        BAR_W(gdl, 0xF5180000, 0x07094250); /* SetTile (load) */
        gDPLoadSync(gdl++);
        BAR_W(gdl, 0xF3000000, 0x073FF000); /* LoadBlock */
        gDPPipeSync(gdl++);
        BAR_W(gdl, 0xF5181000, 0x00094250); /* SetTile (render) */
        BAR_W(gdl, 0xF2000000, 0x0007C07C); /* SetTileSize 32x32 */
        gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        yy = 0x48;
        for (q = D_800901E4; q != D_800901E4 + 4; q++) {
            if (*q >= 0) {
                k = *q & 3;
                gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x120, (yy - 2) * 4, 0x160, (yy + 0xE) * 4, 0, (k & 1) << 9,
                                            (k >> 1) << 9, 0x400, 0x400);
                yy += 0x12;
            }
        }
        return (u8 *) gdl;
    }
    base = (D_80090160 & 1) ? 0x1A : 0x34;
    if (D_800E0B94 != 0 && D_80090168 != 0) {
        y -= 0x28;
    }
    func_1504332C(0xFF, 0xFF, 0xFF, alpha & 0xFF);
    if (D_800E1003 == 2) {
        fmt = 9;
        wide = 1;
    } else {
        fmt = 0x5E;
        wide = 0;
    }
    all = (BAR_MODE() == 8) ? 0 : 1;
    gDPPipeSync(gdl++);
    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, alpha & 0xFF);
    gDPSetCombine(gdl++, 0x12D225, 0xFFA7FFFF);
    hdr = 0;
    for (i = 0; i < 4; i++) {
        if (D_800901E4[i] < 0 || D_80087270[i] == 10) {
            continue;
        }
        team = D_800E1030[i];
        if (team == 0 && !all) {
            continue;
        }
        if (!hdr) {
            tex = func_1510D66C(0x887, 0, 3, 0);
            if (tex == (s32) 0x80000000) {
                return (u8 *) gdl;
            }
            BAR_W(gdl, 0xFD180000, tex);
            BAR_W(gdl, 0xF5180000, 0x07094250);
            gDPLoadSync(gdl++);
            BAR_W(gdl, 0xF3000000, 0x073FF000);
            gDPPipeSync(gdl++);
            BAR_W(gdl, 0xF5181000, 0x00094250);
            BAR_W(gdl, 0xF2000000, 0x0007C07C);
            gDPSetOtherMode(gdl++, 0x000C3F, 0x504244);
            x = (base - 0x28) * 4;
            hy = (y - 0x11) * 4;
            if (D_80090160 & 1) {
                gdl = (Gfx *) func_151E8E94((u8 *) gdl, x + 0x1D4, hy, x + 0x214, hy + 0x40, 0, 0x200, 0, 0x400, 0x400);
                x += 0x78;
            }
            x += 0x1D4;
            if (BAR_MODE() == 1) {
                x -= 0x78;
            }
            gdl = (Gfx *) func_151E8E94((u8 *) gdl, x + 0x164, hy, x + 0x1A4, hy + 0x3C, 0, 0, 0x200, 0x400, 0x400);
            if (BAR_MODE() == 1) {
                x += 0x78;
            }
            gDPPipeSync(gdl++);
            tex = func_1510D66C(0x888, 0, 3, 0);
            if (tex == (s32) 0x80000000) {
                return (u8 *) gdl;
            }
            BAR_W(gdl, 0xFD180000, tex);
            BAR_W(gdl, 0xF5180000, 0x07094250);
            gDPLoadSync(gdl++);
            BAR_W(gdl, 0xF3000000, 0x073FF000);
            gDPPipeSync(gdl++);
            BAR_W(gdl, 0xF5181000, 0x00094250);
            BAR_W(gdl, 0xF2000000, 0x0007C07C);
            gdl = (Gfx *) func_151E8E94((u8 *) gdl, x, hy, x + 0x40, hy + 0x40, 0, 0x200, 0, 0x400, 0x400);
            x += 0x74;
            gdl = (Gfx *) func_151E8E94((u8 *) gdl, x, hy, x + 0x40, hy + 0x40, 0, 0, 0, 0x400, 0x400);
            if (BAR_MODE() != 1) {
                gdl = (Gfx *) func_151E8E94((u8 *) gdl, x + 0x4C, hy, x + 0xCC, hy + 0x40, 0, 0, 0x200, 0x400, 0x400);
            }
            gDPPipeSync(gdl++);
            tex = func_1510D66C(0x843, 0, 3, 0);
            if (tex == (s32) 0x80000000) {
                return (u8 *) gdl;
            }
            BAR_W(gdl, 0xFD180000, tex);
            BAR_W(gdl, 0xF5180000, 0x07094250);
            gDPLoadSync(gdl++);
            BAR_W(gdl, 0xF3000000, 0x073FF000);
            gDPPipeSync(gdl++);
            hdr = 1;
            BAR_W(gdl, 0xF5181000, 0x00094250);
            BAR_W(gdl, 0xF2000000, 0x0007C07C);
            gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        }
        func_1504332C(D_800ABEA0[team][0], D_800ABEA0[team][1], D_800ABEA0[team][2], alpha & 0xFF);
        k = D_800901E4[i] & 3;
        gdl = (Gfx *) func_151E8E94((u8 *) gdl, (base + 8) * 4, (y - 2) * 4, (base + 0x18) * 4, (y + 0xE) * 4, 0,
                                    (k & 1) << 9, (k >> 1) << 9, 0x400, 0x400);
        pct = 0;
        if (hud) {
            v = D_800CC2D0[i].unk31C->unk1AA;
        } else {
            v = BAR_ROW(i, 0x6C);
        }
        if (v > 0) {
            pct = (BAR_ROW(i, 0x66) * 100) / v;
        }
        if (pct >= 10000) {
            pct = 9999;
        }
        if (D_80090168 != 0) {
            team = i;
        }
        r = (s8) (D_800E0EF0[team] - 1);
        if (r < 0) {
            r = 0;
        }
        func_15042D94(base + 0x3C, y, 0x81, D_800ABEB8, ((s32 *) D_800E1008)[r + fmt]);
        x = base;
        if (D_80090160 & 1) {
            func_15042D94(base + 0x54, y, 0x81, D_800ABEBC, D_800E0ED0[team]);
            x = base + 0x1E;
        }
        x += 0x58;
        func_15042D94(x, y, 0x81, D_800ABEC0, pct);
        x += 0x1A;
        func_15042D94(x, y, 0x81, D_800ABEC8, *(s16 *) (D_80090174 + i * 2 + 0x46));
        x += 0x1E;
        if (BAR_MODE() != 1) {
            if (D_80087270[i] == 9 || (i == 0 && D_8009011C == 9)) {
                func_15042D94(x, y, 0x81, D_800ABECC);
            } else {
                func_15042D94(x, y, 0x81, D_800ABED0, BAR_ROW(i, 0x6A));
            }
            x += 0x1E;
        }
        func_15042D94(x, y, 0x81, D_800ABED4, D_800E0F00[i]);
        y += 0xF;
    }
    if (D_80090160 & 0x6340) {
        gSPDisplayList(gdl++, D_800903D8);
        gDPSetCombine(gdl++, 0x12FE25, 0xFFFFF3F9);
        gdl = (Gfx *) func_151EA4C8((u8 *) gdl, 0x320, wide);
    }
    if (hud && (D_80090160 & 1)) {
        gdl = (Gfx *) func_151E9E1C((u8 *) gdl, 0x320, -1, 1, wide);
    }
    return (u8 *) gdl;
}
#undef BAR_W
#undef BAR_MODE
#undef BAR_ROW
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EA90C.s")
#endif

#ifdef NON_MATCHING
s32 func_1510D66C(s32, s32, s32, s32);
u8 *func_151E8E94(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80090424;
extern s32 D_8009044C;

u8 *func_151EB5AC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct {
        s32 u7C;
        u8 pad80[0x14];
        s32 u94;
    } sp;
    s32 *var_s1;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *var_s0;

    var_s0 = arg0;
    var_s3 = arg3;
    (*(s32 *)((u8 *)(&sp.u7C) + 0)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0));
    (*(s32 *)((u8 *)(&sp.u7C) + 4)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 4));
    (*(s32 *)((u8 *)(&sp.u7C) + 8)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 8));
    (*(s32 *)((u8 *)(&sp.u7C) + 0xC)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0xC));
    (*(s32 *)((u8 *)(&sp.u7C) + 0x10)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0x10));
    temp_t4 = arg2 * 4;
    (*(s32 *)((u8 *)(&sp.u7C) + 0x18)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0x18));
    var_s2 = arg1 * 4;
    (*(s32 *)((u8 *)(&sp.u7C) + 0x14)) = (s32) (*(s32 *)((u8 *)(&D_8009044C) + 0x14));
    if (var_s3 >= 0x989680) {
        var_s3 = 0x98967F;
    }
    var_s4 = 0;
    if (var_s3 < 0) {
        var_s3 = 0;
    }
    var_s1 = &sp.u94;
    do {
        temp_v0 = *var_s1;
        temp_v1 = var_s3 / temp_v0;
        var_s3 = var_s3 % temp_v0;
        if ((temp_v1 > 0) || (var_s4 != 0) || (var_s1 == &sp.u7C)) {
            var_s4 = 1;
            temp_v0_2 = func_1510D66C(*(s32 *)((u8 *)&D_80090424 + (temp_v1 * 4)), 0, 3, 0);
            if (temp_v0_2 != 0x80000000) {
                (*(s32 *)((u8 *)var_s0 + 0)) = 0xFD180000;
                (*(s32 *)((u8 *)var_s0 + 4)) = temp_v0_2;
                temp_s0 = var_s0 + 8;
                (*(s32 *)((u8 *)temp_s0 + 0)) = 0xF5180000;
                (*(s32 *)((u8 *)temp_s0 + 4)) = 0x07094250;
                temp_s0_2 = temp_s0 + 8;
                (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0xE6000000;
                (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0;
                temp_s0_3 = temp_s0_2 + 8;
                (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0x073FF000;
                (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0xF3000000;
                temp_s0_4 = temp_s0_3 + 8;
                (*(s32 *)((u8 *)temp_s0_4 + 0)) = 0xE7000000;
                (*(s32 *)((u8 *)temp_s0_4 + 4)) = 0;
                temp_s0_5 = temp_s0_4 + 8;
                (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xF5181000;
                (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0x94250;
                temp_s0_6 = temp_s0_5 + 8;
                (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xF2000000;
                (*(s32 *)((u8 *)temp_s0_6 + 4)) = 0x7C07C;
                var_s0 = func_151E8E94(temp_s0_6 + 8, var_s2, temp_t4, var_s2 + 0x80, temp_t4 + 0x80, 0, 0, 0, 0x400, 0x400);
            }
            var_s2 += 0x60;
        }
        var_s1 = (s32 *)((u8 *)var_s1 - (4));
    } while ((u32) var_s1 >= (u32) &sp.u7C);
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EB5AC.s")
#endif
#ifdef NON_MATCHING
/* Table D_80090370 slot 0 (the in-game HUD pass): pause/fade overlay, and with D_800BEAC0 set the
 * money/lives counter screen (texture ids 0x7D3.. loaded through func_1510D66C, counters drawn by
 * func_151EB5AC). */
u8 * func_150900F0(Gfx *, s32);
void func_151EE310(u8 *arg0);
void func_151F0114(void *, float, float, float, float, float, float, float);
s8 func_151E5DF8(void);
void func_1510DC14(s32);
u8 *func_1509B570(s32);
u8 *func_151EB5AC(u8 *, s32, s32, s32);
s32 func_1509BE40(s32, s32, ...);
u8 * func_151E9150(u8 *, s32, s32);
u8 * func_151EA90C(Gfx *, s32, s16, s32);
s32 func_151EE0C4(s32, s32, s32, f32);
u8 * func_151EE394(u8 *, s32, f32, f32, f32);
extern s32 D_8008955C;
extern s8 D_8009029C;
extern s32 D_8009040C;
extern s8 D_80090468;
extern s16 D_800C40BE;
extern s16 D_800E1060;
extern s32 D_800E1068;

u8 *func_151EB81C(u8 *arg0) {
    struct {
        s32 u70;
        u8 pad74[0x8];
        s32 u7C;
        u8 pad80[0x4];
        s32 u84;
        s32 u88;
        s32 u8C;
        s32 u90;
    } sp;
    u8 *var_s0_2;
    u8 *var_s0;
    u8 *temp_v0_2;
    u8 *temp_s0_6;
    u8 *temp_s0_5;
    u8 *temp_s0;
    u8 temp_v1;
    s32 var_v1_4;
    s32 var_v1_3;
    s32 var_v1;
    s32 var_v0_3;
    s32 var_v0_2;
    s32 var_v0;
    s32 var_t0;
    s32 var_a3;
    s32 var_a0;
    s32 temp_v1_2;
    s32 temp_v0_3;
    s32 temp_v0;
    s32 temp_t9;
    f32 temp_f2;
    f32 temp_f0;
    Gfx *temp_s0_4;
    Gfx *temp_s0_3;
    Gfx *temp_s0_2;
    Gfx *sp34;
    s32 sp3C;

    var_s0 = arg0;
    temp_t9 = (D_800D2E4C->unk19 & 4) != 0;
    sp3C = temp_t9;
    if (temp_t9 == 0) {
        sp3C = D_8008FDA8 < 0;
    }
    if ((D_800BE616 != 0) && (D_800BEAC0 == 0) && (D_800BEAC1 == 0)) {
        if ((func_151E5DF8() == 0) || ((*(s8 *)((u8 *)D_80090174 + 0x42)) == 1)) {
            var_s0 = func_151E9150(var_s0, 0, 0xFF);
        }
    } else {
        D_800E10A8 = 0;
    }
    if ((D_800BEAC0 == 0) || (D_8009029C != 0)) {
        if (D_80090408 != 0) {
            func_151EE310((u8 *) D_80090408);
            func_151EE310((u8 *) D_8009040C);
            D_80090408 = 0;
        }
        D_8009016C = 0;
        D_80090468 = 0;
    } else {
        if ((D_800B0DF0->unk8 == 4) && (D_80090468 == 0)) {
            var_v1 = 0;
            if (D_800BE9F0 == 0x13) {
                var_a0 = (*(s32 *)((u8 *)(*(s32 *)((u8 *)&D_8008955C + (D_800B0DF0->unk9 * 4))) + 8));
                /* texture ids 0x1649-0x164B and 0x1655-0x1657 stay loaded */
                for (var_v0 = 0; var_v0 != 0x48; var_v0++, var_a0++) {
                    if (var_a0 != 0x1649 && var_a0 != 0x164A && var_a0 != 0x164B && var_a0 != 0x1655 &&
                        var_a0 != 0x1656 && var_a0 != 0x1657) {
                        func_1510DC14(var_a0);
                    }
                }
                var_v1 = 0x4E;
            }
            var_v0_2 = var_v1;
            if (var_v1 < 0x168) {
                do {
                    sp.u84 = var_v0_2;
                    func_1510DC14((*(s32 *)((u8 *)(*(s32 *)((u8 *)&D_8008955C + (D_800B0DF0->unk9 * 4))) + 8)) + var_v0_2);
                    var_v0_2 = sp.u84 + 1;
                } while (var_v0_2 != 0x168);
            }
        }
        if (D_80090468 < 5) {
            D_80090468 += 1;
        } else {
            temp_s0 = var_s0 + 8;
            D_8009016C += 0x20;
            if (D_8009016C >= 0x100) {
                D_8009016C = 0xFF;
            }
            (*(s32 *)((u8 *)var_s0 + 0)) = 0xDE000000;
            (*(Gfx **)((u8 *)var_s0 + 4)) = D_800903D8;
            (*(s32 *)((u8 *)temp_s0 + 0)) = 0xFB000000;
            temp_s0_2 = temp_s0 + 8;
            (*(s32 *)((u8 *)temp_s0 + 4)) = (s32) ((D_8009016C & 0xFF) | ~0xFF);
            D_80090410 = 0x891;
            sp34 = D_800903D8;
            func_1510D66C(0x7D3, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x7D4, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x7FC, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x7FD, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x7F1, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x7F2, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x82F, (s32) &sp.u70, 3, 0);
            func_1510D66C(0x830, (s32) &sp.u70, 3, 0);
            temp_v1 = D_800BE616;
            if (temp_v1 != 0) {
                func_1510D66C(0x80E, (s32) &sp.u70, 3, 0);
                func_1510D66C(0x80F, (s32) &sp.u70, 3, 0);
            }
            if (temp_v1 == 0) {
                temp_v0 = func_150859AC(0, 6);
                var_v1_3 = temp_v0;
                if (temp_v0 == 0x7D00) {
                    var_v1_3 = 0xF4240;
                }
                sp.u90 = var_v1_3;
                if ((func_1509BE40(0, 0x5082, 0x1A) != 0) && (func_1509BE40(0, 0x5083, 0x1A) == 0)) {
                    temp_v0_2 = func_1509B570(0x83);
                    if (temp_v0_2 != NULL) {
                        temp_v1_2 = (*(s32 *)((u8 *)temp_v0_2 + 0x64));
                        if (temp_v1_2 == 0) {
                            sp.u90 = 0;
                        } else if (temp_v1_2 < 3) {
                            sp.u90 = (s32) (sp.u90 * temp_v1_2) / 3;
                        }
                    } else {
                        sp.u90 = 0;
                    }
                }
                var_v1_4 = sp.u90;
                if ((D_800C35EA == 1) && (D_800C40BE != -1)) {
                    if (D_800C40BE == 0) {
                        var_v1_4 = 0;
                    } else {
                        var_v1_4 -= D_800C40BE;
                        if (D_800C40BE == 0x7D00) {
                            var_v1_4 = 0xF4240;
                        }
                    }
                }
                if (var_v1_4 > 0) {
                    sp.u88 = 1;
                } else {
                    sp.u88 = 0;
                }
                sp.u90 = var_v1_4;
                temp_s0_3 = func_151EDBE8(temp_s0_2, &D_80090410, 0x94, 0x3C, 3, 1, 1.0f, 0);
                if (D_80090408 == 0) {
                    D_80090408 = func_151EE0C4(0xA4, 0x17, 0, 1.0f);
                    D_8009040C = func_151EE0C4(0xA2, 8, 0, 1.0f);
                }
                temp_s0_3->words.w0 = 0xD9FFFFFF;
                temp_s0_3->words.w1 = 0x220404;
                temp_s0_4 = temp_s0_3 + 1;
                temp_s0_4->words.w1 = -1U;
                temp_s0_4->words.w0 = 0xFB000000;
                temp_f0 = (*(f32 *)((u8 *)D_800BE628 + 4)) * 0.5f;
                temp_f2 = (*(f32 *)((u8 *)D_800BE628 + 8)) * 0.5f;
                var_s0_2 = func_150900F0(temp_s0_4 + 1, 1);
                func_151F0114(&D_800E1068, -temp_f0, temp_f0, -temp_f2, temp_f2, 1.0f, 20000.0f, 1.0f);
                D_800E1060 = D_8009016C;
                if (D_80090408 != 0) {
                    var_v0_3 = 0xA;
                    if (sp.u88 != 0) {
                        var_t0 = -0x10;
                        if (sp.u90 >= 0xB) {
                            do {
                                var_t0 -= 0x10;
                                var_v0_3 *= 0xA;
                            } while (var_v0_3 < sp.u90);
                        }
                        sp.u8C = var_t0;
                        var_s0_2 = func_151EE394(var_s0_2, D_80090408, (f32) var_t0 + -10.0f, -83.0f, 0.26999998f);
                    }
                }
                if ((D_8009040C != 0) && (sp3C != 0)) {
                    var_s0_2 = func_151EE394(var_s0_2, D_8009040C, 70.0f, 80.0f, 0.3f);
                }
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xDE000000;
                temp_s0_5 = var_s0_2 + 8;
                (*(Gfx **)((u8 *)var_s0_2 + 4)) = sp34;
                (*(s32 *)((u8 *)temp_s0_5 + 0)) = 0xEF002C3F;
                (*(s32 *)((u8 *)temp_s0_5 + 4)) = 0x504244;
                var_s0 = temp_s0_5 + 8;
                if (sp3C != 0) {
                    temp_v0_3 = func_150859AC(0, 3);
                    var_a3 = temp_v0_3;
                    if (temp_v0_3 != 0) {
                        var_a3 = temp_v0_3 - 1;
                    }
                    if (var_a3 >= 0x64) {
                        var_a3 = 0x63;
                    }
                    (*(s32 *)((u8 *)var_s0 + 0)) = 0xFB000000;
                    (*(s32 *)((u8 *)var_s0 + 4)) = (s32) ((D_8009016C & 0xFF) | ~0xFF);
                    var_s0 = func_151EB5AC(var_s0 + 8, 0xEC, 0x1E, var_a3);
                }
                if (sp.u88 != 0) {
                    (*(s32 *)((u8 *)var_s0 + 0)) = 0xE7000000;
                    temp_s0_6 = var_s0 + 8;
                    (*(s32 *)((u8 *)var_s0 + 4)) = 0;
                    (*(s32 *)((u8 *)temp_s0_6 + 0)) = 0xFB000000;
                    (*(s32 *)((u8 *)temp_s0_6 + 4)) = (s32) ((D_8009016C & 0xFF) | ~0xFF);
                    D_80090410 = 0x7F6;
                    var_s0 = func_151EB5AC(func_151EDBE8(temp_s0_6 + 8, &D_80090410, sp.u8C + 0xA5, 0xAA, 1, 1, 1.0f, 0), sp.u8C + 0xAD, 0x9B, sp.u90);
                }
            } else {
                var_s0 = func_151EA90C(func_151EDBE8(temp_s0_2, &D_80090410, 0x94, 0x12, 3, 1, 1.0f, 0), 0x85, D_8009016C, 1);
            }
        }
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EB81C.s")
#endif
s32 func_151EC0E0(s32 arg0) {
    if (D_8009016C != 0) {
        arg0 = func_151EA90C(arg0, 0x6A, D_8009016C, 0);
    }
    return arg0;
}

#ifdef NON_MATCHING
extern s16 D_800E0EB0;

/* Table D_80090370 slot 21: centred text screen. Lines D_800E1008[D_800E0EB0...] up to a "*" line;
 * the first line is red, an extra 12 px gap follows it. Fades in over D_800E0EC0 0..63, out at 287..350. */
Gfx *func_151EC11C(Gfx *gdl) {
    s32 pad[2];
    s16 a;
    s16 i;
    s32 n;
    s32 step;
    s32 y;
    s32 y0;
    u8 *s;

    if (D_800E0EB0 < 0) {
        return gdl;
    }
    if (D_800E0EC0 < 300) {
        a = D_800E0EC0 << 2;
        if (a >= 0x100) {
            a = 0xFF;
        }
    } else {
        a = (350 - D_800E0EC0) << 2;
        if (a < 0) {
            a = 0;
        }
        if (a >= 0x100) {
            a = 0xFF;
        }
    }
    n = 0;
    for (i = D_800E0EB0; ((u8 **)D_800E1008)[i][0] != '*'; i++) {
        n++;
    }
    if (n < 14) {
        step = 0x11;
    } else {
        step = 0xB;
    }
    func_1504332C(0xFF, 0, 0, a);
    i = D_800E0EB0;
    y0 = y = (0xD0 - n * step) >> 1;
    while ((s = ((u8 **)D_800E1008)[i])[0] != '*') {
        func_15042D94(0x94, y, 1, s);
        func_1504332C(0xFF, 0xFF, 0xFF, a);
        if (y == y0) {
            y += 0xC;
        }
        i++;
        y += step;
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC11C.s")
#endif
#ifdef NON_MATCHING
extern s32 D_80091B9C;
extern f32 D_800ABEF8;
extern u8 D_85D[];
extern u8 D_89C[];


/* Table D_80090370 slot 11: three-phase intro/credits screen on a black background, driven by the timer
 * D_800E0EC0. t < 200: one red text line (D_800E1008 + 0x238), zooming from scale 0.75 to 1.5.
 * 200 <= t < 450: two sprites (D_80091BA8 at 1/4 alpha, D_80091B9C), 14 text lines, the 16x16 D_89C icon.
 * t >= 450: the 64x64 D_85D image. D_80090410 is a shared sprite descriptor (texture, size, format)
 * that is reset to its 32x32 default afterwards. Skipped (after the clear) when D_80000300 != 0. */
Gfx *func_151EC300(Gfx *gdl) {
    s32 t;
    s32 a;
    s32 i;
    f32 scale;
    s32 envcol;
    u8 *desc = (u8 *) &D_80090410;

    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x082C3F, 0x504340);
    gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFEFB7D);
    gDPSetEnvColor(gdl++, 0, 0, 0, 0xFF);
    gdl = (Gfx *) func_1501A6CC((u8 *) gdl, 0, 0, D_800BE620, D_800BE624);
    if (D_80000300 != 0) {
        return gdl;
    }
    gSPDisplayList(gdl++, D_800903D8);
    t = D_800E0EC0;
    if (t < 200) {
        a = 0xFF - (t - 150) * 8;
        if (a < 0) {
            a = 0;
        }
        if (a >= 0x100) {
            a = 0xFF;
        }
        scale = (f32) t / 180.0f + 0.75f;
        if (scale > 1.5f) {
            scale = 1.5f;
        }
        func_150432BC(scale);
        func_1504332C(0xFF, 0, 0, a & 0xFF);
        func_15042D94(0x94, 0x69, 1, *(u8 **) ((u8 *) D_800E1008 + 0x238));
        func_150432BC(1.0f);
    } else if (t < 450) {
        if (t < 250) {
            a = (t - 200) * 8;
            if (a >= 0x100) {
                a = 0xFF;
            }
        } else {
            a = 0xFF - (t - 400) * 8;
            if (a < 0) {
                a = 0;
            }
            if (a >= 0x100) {
                a = 0xFF;
            }
        }
        gDPPipeSync(gdl++);
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, (a >> 2) & 0xFF);
        gdl = func_151EDBE8(gdl, &D_80091BA8, 0x92, 0x67, 5, 6, 1.0f, 0);
        envcol = (a & 0xFF) | ~0xFF;
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = envcol;
        gdl++;
        gdl = func_151EDBE8(gdl, &D_80091B9C, 0x92, 0x1C, 2, 1, 1.0f, 0);
        func_1504332C(0xFF, 0xFF, 0xFF, a & 0xFF);
        func_15042D94(0x94, 0x9D, 1, *(u8 **) ((u8 *) D_800E1008 + 0x204));
        func_15042D94(0x94, 0xAA, 1, *(u8 **) ((u8 *) D_800E1008 + 0x208));
        func_15042D94(0x94, 0xBC, 1, *(u8 **) ((u8 *) D_800E1008 + 0x20C));
        func_150432BC(D_800ABEF8);
        for (i = 0; i < 10; i++) {
            func_15042D94(0x94, 0x2D + i * 10, 1, *(u8 **) ((u8 *) D_800E1008 + 0x210 + i * 4));
        }
        func_150432BC(1.0f);
        gDPPipeSync(gdl++);
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = envcol;
        gdl++;
        *(u8 **) (desc + 0) = D_89C;
        *(s16 *) (desc + 6) = 0x10;
        *(s16 *) (desc + 8) = 0x10;
        gdl = func_151EDBE8(gdl, desc, 0xC7, 0xB0, 1, 1, 1.0f, 0);
        *(s16 *) (desc + 6) = 0x20;
        *(s16 *) (desc + 8) = 0x20;
    } else {
        if (t < 500) {
            a = (t - 450) * 8;
            if (a >= 0x100) {
                a = 0xFF;
            }
        } else {
            a = 0xFF - (t - 650) * 8;
            if (a < 0) {
                a = 0;
            }
            if (a >= 0x100) {
                a = 0xFF;
            }
        }
        gdl->words.w0 = 0xFB000000;
        gdl->words.w1 = (a & 0xFF) | 0xFF000000;
        gdl++;
        desc[0xA] = 4;
        desc[0xB] = 1;
        *(u8 **) (desc + 0) = D_85D;
        *(s16 *) (desc + 6) = 0x40;
        *(s16 *) (desc + 8) = 0x40;
        gdl = func_151EDBE8(gdl, desc, 0x94, 0x69, 3, 1, 1.0f, 0);
        *(s16 *) (desc + 6) = 0x20;
        *(s16 *) (desc + 8) = 0x20;
        desc[0xA] = 0;
        desc[0xB] = 3;
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC300.s")
#endif
#ifdef NON_MATCHING
s32 func_151EC928(s32 arg0) {
    s32 temp_t6;
    s32 var_v0;

    if (D_800E0EC0 >= 0x5DD) {
        temp_t6 = (D_800E0EC0 - 0x5DC) * 8;
        var_v0 = temp_t6;
        if (temp_t6 >= 0x100) {
            var_v0 = 0xFF;
        }
        func_1504332C(0xFFU, 0xFFU, 0xFFU, var_v0 & 0xFF);
        func_15042D94(0xDC, 0x130, 1, (*(u8 **)((u8 *)D_800E1008 + 0x1D0)));
    }
    return arg0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC928.s")
#endif
#ifdef NON_MATCHING
extern s32 D_80091BA8;
extern s32 D_80091BB4;
extern s32 D_80091BC0;
extern s32 D_800E0EA4;
#define MW(g, a, b) { Gfx *_g = (g); _g->words.w0 = (a); _g->words.w1 = (b); }

Gfx *func_151EC9A0(Gfx *gdl) {
    s32 temp_v1;
    s32 var_v1;
    s32 var_v1_2;
    s32 temp_t0;
    s32 temp_a;

    if (D_800BE9F0 == 0x21) {
        return gdl;
    }
    gSPDisplayList(gdl++, D_800903D8);
    if (D_800E0EC0 >= 0x12D) {
        temp_v1 = 0x1AC - D_800E0EC0;
        temp_a = temp_v1 * 2;
        var_v1 = temp_a;
        if (temp_a < 0) {
            var_v1 = 0;
        }
    } else {
        var_v1 = D_800E0EC0 * 8;
        if (var_v1 >= 0x100) {
            var_v1 = 0xFF;
        }
    }
    if (var_v1 != 0) {
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, var_v1);
        gdl = func_151EDBE8(gdl, &D_80091BA8, 0x92, 0x63, 5, 6, 1.0f, 0);
    }
    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, 0xFF);
    gdl = func_151EDBE8(gdl, &D_80091BB4, 0x92, 0xCB, 5, 2, 1.0f, 0);
    MW(gdl++, 0xFCFFD3FF, 0xFFA6FF7F);
    MW(gdl++, 0xFB000000, (u8) D_800E0FC7 | 0x20FF2000);
    gdl = func_151EDBE8(gdl, &D_80091BC0, 0x92, 0xCB, 5, 2, 1.0f, 0);
    gdl = func_15096D44(gdl);
    temp_v1 = 0x1EA - D_800E0EA4;
    if (temp_v1 < 0) {
        var_v1_2 = 0;
    } else {
        temp_t0 = temp_v1 * 0x10;
        var_v1_2 = temp_t0;
        if (temp_t0 >= 0x100) {
            var_v1_2 = 0xFF;
        }
    }
    D_800E0FC6 = 0xFF - var_v1_2;
        return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EC9A0.s")
#endif
#ifdef NON_MATCHING
Gfx *func_151EDBE8(Gfx *, void *, s32, s32, s32, s32, f32, s32);
Gfx *func_151ECE00(Gfx *);
Gfx *func_151EE93C(Gfx *);
Gfx *func_151EF3A0(Gfx *, s32);
extern Gfx D_800903D8[];
extern u8 D_80090484;
extern s8 D_800902A4;
extern s8 D_800902A8;
extern u8 D_800E0EC5;
extern s32 D_80090410;
extern s32 D_8009046C[];

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    u8 padC[0x20];
    s8 x2C;
    u8 pad2D[0x11];
    s8 x3E;
} Ent174;

Gfx *func_151ECB98(Gfx *gdl) {
    Ent174 *p;
    s32 a;
    s32 v;
    s32 k;
    s32 t;
    struct_eu_BE818 *e;

    if (D_800C35EA == 1) {
        D_80090484 = 0;
        return gdl;
    }
    a = D_80090484 + D_800BE9E4 * 4;
    if (a >= 0x100) {
        a = 0xFF;
    }
    D_80090484 = a;
    gSPDisplayList(gdl++, D_800903D8);
    p = (Ent174 *)D_80090174;
    k = p->x3E;
    if (k == 1) {
        return func_151ECE00(gdl);
    }
    if (k != 0) {
        return gdl;
    }
    t = p->x2C;
    if (t == 1 && D_800902A4 != 0) {
        gdl = func_151EE93C(gdl);
    } else if (t != 1 || D_800902A8 == 0) {
        v = (p->x0 - 0.5f) * 512.0f;
        if (v < 0) {
            v = -v;
        }
        if (v >= 0x100) {
            v = 0xFF;
        }
        if (D_80090484 < v) {
            v = D_80090484;
        }
        if (t == 1) {
            v = (D_800E0EC5 * v) >> 8;
            if (v >= 0xFE) {
                v = 0xFF;
            }
        }
        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, v);
        gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        D_80090410 = D_8009046C[((Ent174 *)D_80090174)->x2C];
        gdl = func_151EDBE8(gdl, &D_80090410, 0x94, 0x1E, 3, 1, 1.0f, 0);
    }
    p = (Ent174 *)D_80090174;
    if (0.5f <= p->x8) {
        if (p->x2C >= 3) {
            e = &D_800BE818[p->x2C - 3];
            if (e->unk8 != -1) {
                gdl = func_151EF3A0(gdl, e->padC[0]);
            }
        }
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151ECB98.s")
#endif
#ifdef NON_MATCHING
typedef struct {
    /* 0x00 */ f32 slide;        /* menu slide position (0.5 = centre) */
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 fade;         /* 0 = fully shown */
    /* 0x0C */ f32 vel;          /* slide velocity */
    /* 0x10 */ u8 pad10[0x1C];
    /* 0x2C */ s8 page;
    /* 0x2D */ u8 pad2D[0x13];
    /* 0x40 */ s8 mode;          /* 0 barrel, 3 single bar, 4 player slots */
    /* 0x41 */ s8 sel;           /* selected barrel */
} BarrelMenu174;
extern s8 D_800904A8;            /* page whose banner is shown */
extern s32 D_80090488[];         /* banner sprite per page */
extern s32 D_800904AC[];         /* barrel sprite per item (5) */
extern u8 D_800E10B8[4];         /* player slot fill (0..255) */
extern u8 D_800E0EC4;
extern f32 D_80090188;           /* barrel rotation phase */
extern s8 D_800901CC;
extern s32 D_800BEDCC;           /* frame counter */
extern s8 D_800901E0;            /* joined players */
extern s8 D_800901E4[];          /* player queue (controller numbers) */
extern s8 D_800E0FC0[];          /* character per joined player */
extern struct127 *D_800E0FD0[4]; /* character object per controller */
extern u8 D_87B[];
extern u8 D_88C[];
extern char D_800ABED8[];         /* "#" */
extern char D_800ABEDC[];         /* "#" */
extern char D_800ABEE0[];         /* "%d" */
s8 func_151E2C88(s32);
void func_151E870C(s32 slot, s32 character);
/* barrel_menu_draw: draws the multiplayer barrel menu (D_80090174 mode 1 of func_151ECB98) into gdl and returns
 * the new end. A pipe sync, then (unless mode 3) the page banner D_80090488[D_800904A8] faded by the slide offset
 * and the title D_88C faded by +0x08. Mode 0: once faded in on page 4, the ring of five item barrels (D_800904AC,
 * cos ring from the selection +0x41 and the rotation D_80090188), the front one pulsing when at rest; mode 3: the
 * single bar func_151EA90C; mode 4: two or four player slots (page 7: two) that fill while the controller is
 * joined (spawning its character with func_151E870C) and empty otherwise (removing the object), each with its
 * frame D_89C, a pulsing highlight, the fill bar D_87B, the slot number and the player's score from
 * func_151E2C88. */
Gfx *func_151ECE00(Gfx *gdl) {
    BarrelMenu174 *m;
    s32 scores[8];
    s32 alpha, a, x, k, mul, prev, cur, mid, v, i, j, slot, dir, nslots, nscores, si, pulse, step, y;
    f32 ang, sc, sizef;
    u8 *fill;

    alpha = (s32) ((((BarrelMenu174 *) D_80090174)->slide - 0.5f) * 512.0f);
    if (alpha < 0) {
        alpha = -alpha;
    }
    if (alpha >= 0x100) {
        alpha = 0xFF;
    }
    gDPPipeSync(gdl++);
    m = (BarrelMenu174 *) D_80090174;
    if (m->fade == 0.0f && m->vel == 0.0f) {
        D_800904A8 = m->page;
    } else if (m->page == 0 && m->vel < 0.0f) {
        D_800904A8 = 4;
    }
    if (m->page == 0) {
        y = 0x6A;
        a = 0xFF - (s32) (m->fade * 300.0f);
    } else {
        a = alpha;
        y = 0x6A - (s32) (m->fade * (D_800904A8 == 4 ? 68.0f : 76.0f));
    }
    if (m->mode != 3) {
        if (a > 0 && D_80090488[D_800904A8] != 0) {
            gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, a);
            if (D_800904A8 == 4) {
                sc = 0.8f;
                k = 2;
                mul = 2;
            } else {
                sc = 1.0f;
                k = 2;
                mul = 1;
                if (D_800904A8 != 0) {
                    k = 3;
                }
            }
            D_80090410 = D_80090488[D_800904A8];
            gdl = func_151EDBE8(gdl, &D_80090410, 0x94, y, k, mul, sc, 0);
            m = (BarrelMenu174 *) D_80090174;
        }
        a = 0xFF - (s32) (m->fade * 300.0f);
        if (a > 0) {
            gDPPipeSync(gdl++);
            gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, a);
            D_80090410 = (s32) D_88C;
            gdl = func_151EDBE8(gdl, &D_80090410, 0x94, 0x1E, 3, 1, 1.0f, 0);
            m = (BarrelMenu174 *) D_80090174;
        }
    }
    switch (m->mode) {
        case 0:
            D_800E10B8[0] = 0;
            D_800E10B8[1] = 0xFF;
            D_800E10B8[2] = 0xFF;
            D_800E10B8[3] = 0xFF;
            if (!(m->fade >= 0.5f) || m->page != 4) {
                break;
            }
            alpha = (D_800E0EC4 * D_800E0EC5) >> 8;
            if (alpha >= 0xFE) {
                alpha = 0xFF;
            }
            ang = 0.62831855f + (0.62831855f + 0.62831855f * D_80090188);
            prev = 0x7E - (s32) (cosf(ang) * 52.0f);
            i = ((BarrelMenu174 *) D_80090174)->sel - 4;
            if (i < 0) {
                i += 5;
            }
            for (j = 1; j != 8; j++) {
                ang -= 0.62831855f;
                cur = 0x7E - (s32) (cosf(ang) * 52.0f);
                if (prev < cur) {
                    gDPPipeSync(gdl++);
                    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, alpha);
                    mid = ((cur - prev) >> 1) + prev;
                    sizef = (f32) (cur - prev) * 0.03125f;
                    D_80090410 = D_800904AC[i];
                    gdl = func_151EDBE8(gdl, &D_80090410, 0x53, mid, 2, 1, sizef, -1);
                    if (D_80090188 == 0.0f && j == 5 && D_800901CC == 0) {
                        v = (D_800BEDCC * 2) & 0x7F;
                        if (v >= 0x40) {
                            v = 0x7F - v;
                        }
                        v = (alpha * (v * 3 + 0x3F)) >> 8;
                        if (v >= 0x100) {
                            v = 0xFF;
                        }
                        gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, v);
                        D_80090410 = D_800904AC[i] + 2;
                        gdl = func_151EDBE8(gdl, &D_80090410, 0x53, mid, 2, 1, sizef, -1);
                    }
                }
                i++;
                if (i >= 5) {
                    i -= 5;
                }
                prev = cur;
            }
            break;
        case 4:
            x = 0x28;
            pulse = (s32) (D_800E0EC5 * (s32) ((sinf((f32) (D_800BEDCC & 0x3F) * 0.09817469f + 0.7853975f) + 1.0f) * 127.0f)) >> 8;
            if (((BarrelMenu174 *) D_80090174)->page == 7) {
                x = 0x70;
                nslots = 2;
            } else {
                nslots = 4;
            }
            nscores = func_151E2C88((s32) scores);
            if (nscores != 0) {
                si = 0;
            }
            fill = D_800E10B8;
            for (slot = 0; slot != nslots; slot++, fill++, x += 0x48) {
                j = -1;
                dir = 1;
                for (i = 0; i < D_800901E0; i++) {
                    if (slot == D_800901E4[i]) {
                        j = i;
                        dir = -1;
                        break;
                    }
                }
                if (slot != 0 && D_800E0FD0[0] != NULL) {
                    if (*fill != 0xFF) {
                        if (D_800E0FD0[slot] == NULL && j != -1) {
                            func_151E870C(slot, D_800E0FC0[j]);
                        }
                    } else if (D_800E0FD0[slot] != NULL) {
                        func_15060F28(D_800E0FD0[slot], 1);
                        D_800E0FD0[slot] = NULL;
                    }
                }
                v = *fill + dir * (D_800BE9E4 * 8);
                if (v >= 0x100) {
                    v = 0xFF;
                } else if (v < 0) {
                    v = 0;
                }
                *fill = v;
                gDPPipeSync(gdl++);
                gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, D_800E0EC5);
                D_80090410 = (s32) (D_89C + 2);
                y = 0x8C - (s32) ((f32) v * 0.14285715f);
                gdl = func_151EDBE8(gdl, &D_80090410, x, y, 1, 1, 1.0f, 0);
                if (v > 0) {
                    gDPPipeSync(gdl++);
                    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, pulse);
                    gdl = func_151EDBE8(gdl, &D_80090410, x, y, 1, 1, 1.0f, 1);
                    gDPPipeSync(gdl++);
                    step = (D_800E0EC5 * v) >> 8;
                    if (step >= 0xFE) {
                        step = 0xFF;
                    }
                    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, step);
                    D_80090410 = (s32) D_87B;
                    gdl = func_151EDBE8(gdl, &D_80090410, x, 0x82, 1, 1, 1.0f, 0);
                }
                func_1504332C(0xFF, 0xFF, 0xFF, D_800E0EC5);
                func_15042D94(x, 0x41, 0x80, D_800ABED8, slot + 1);
                if (nscores != 0 && j >= 0 && D_800901E4[j] >= 0) {
                    nscores--;
                    func_15042D94(x, 0xA8, 0, D_800ABEDC, 0x38);
                    func_15042D94(x, 0xA2, 0x81, D_800ABEE0, scores[si] + 1);
                    si++;
                }
            }
            break;
        case 3:
            gdl = (Gfx *) func_151EA90C(gdl, 0x6A, 0xFF, 0);
            break;
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151ECE00.s")
#endif

#ifndef NON_MATCHING
void func_15096D44(Gfx *);
#endif
Gfx *func_151EDBE8(Gfx *, void *, s32, s32, s32, s32, f32, s32);
extern Gfx D_800903D8[];
extern u8 D_80091BCC[];
extern u8 D_80091BD8[];

/* Table D_80090370 slot 17. The original is void in C but its v0 is func_15096D44's return value, which
 * func_151E8620 uses as the new display-list pointer: under NON_MATCHING it returns it explicitly. */
#ifdef NON_MATCHING
Gfx *func_151ED854(Gfx *gdl) {
#else
void func_151ED854(Gfx *gdl) {
#endif
    s32 a;

    gSPDisplayList(gdl++, D_800903D8);
    a = D_800E0EC0 * 4;
    if (a >= 0x100) {
        a = 0xFF;
    }
    gDPSetEnvColor(gdl++, 0xFF, 0xFF, 0xFF, a);
    gdl = func_151EDBE8(gdl, D_80091BCC, 0x92, 0x6C, 8, 3, 1.0f, 0);
    gDPPipeSync(gdl++);
    gDPSetCombine(gdl++, 0xFFD3FF, 0xFFA6FF7F);
    gDPSetEnvColor(gdl++, 0xFF, 0x80, 0x20, ((u8)D_800E0FC7 * (a + 1)) >> 8);
#ifdef NON_MATCHING
    return func_15096D44(func_151EDBE8(gdl, D_80091BD8, 0x92, 0x6C, 8, 3, 1.0f, 0));
#else
    func_15096D44(func_151EDBE8(gdl, D_80091BD8, 0x92, 0x6C, 8, 3, 1.0f, 0));
#endif
}

u8 *func_1501A6CC(u8 *, s32, s32, s32, s32);
Gfx *func_151ED998(Gfx *gdl) {
    if ((u8)D_800E0FC6 == 0) {
        return gdl;
    }
    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x082C3F, 0x504340);
    gDPSetCombine(gdl++, 0xFFFFFF, 0xFFFEFB7D);
    gDPSetEnvColor(gdl++, 0, 0, 0, (u8)D_800E0FC6);
    return (Gfx *)func_1501A6CC((u8 *)gdl, 0, 0, D_800BE620, D_800BE624);
}

#ifdef NON_MATCHING
/* Tile setup for func_151EDBE8: LoadBlock word count (*outBlock, from the D_8009E280/84 size tables), then
 * SetTile (load tile 7) / SetTile (render tile 0, line = w * D_8009E288[siz] bytes / 8, masks = ceil(log2(w/h)), wrap)
 * and SetTileSize. desc: +6 width, +8 height, +0xA format, +0xB size. */
Gfx *func_151EDA54(Gfx *gdl, u8 *desc, s32 *outBlock) {
    s32 w = *(u16 *)(desc + 6);
    s32 h;
    s32 maskS = 1, maskT = 1;
    s32 p;
    u32 fmt;
    u32 *g = (u32 *)gdl;

    *outBlock = (s32)(D_8009E280[desc[0xB]] + w * *(u16 *)(desc + 8)) >> D_8009E284[desc[0xB]];
    w = *(u16 *)(desc + 6);
    if (w >= 3) {
        p = 2;
        do {
            p <<= 1;
            maskS++;
        } while (p < w);
    }
    h = *(u16 *)(desc + 8);
    if (h >= 3) {
        p = 2;
        do {
            p <<= 1;
            maskT++;
        } while (p < h);
    }
    g[0] = 0xE7000000;
    g[1] = 0;
    fmt = ((desc[0xA] & 7) << 21) | 0xF5000000;
    g[2] = ((D_8009E28C[desc[0xB]] & 3) << 19) | fmt;
    g[3] = 0x07000000;
    g[4] = ((((D_8009E288[desc[0xB]] * *(u16 *)(desc + 6) + 7) >> 3) & 0x1FF) << 9) | fmt | ((desc[0xB] & 3) << 19);
    g[5] = ((maskT & 0xF) << 14) | 0x80200 | ((maskS & 0xF) << 4);
    g[6] = 0xF2000000;
    g[7] = ((((*(u16 *)(desc + 6) - 1) * 4) & 0xFFF) << 12) | (((*(u16 *)(desc + 8) - 1) * 4) & 0xFFF);
    return (Gfx *)(g + 8);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EDA54.s")
#endif
#ifdef NON_MATCHING
/* HUD image drawn as cols x rows tiles: each tile's texture comes from the texture cache (func_1510D66C, id
 * desc+0 + idOffset, consecutive ids unless a block is larger than 0x1000 bytes and is split in halves), then
 * SetTImg / LoadBlock / scissored TextureRectangle (gSPScisTextureRectangle) at the scaled screen position.
 * desc: +0 base texture id, +6 tile width, +8 tile height (u16), +0xA format, +0xB size. idOffset < 0: x scale 1. */
Gfx *func_151EDBE8(Gfx *gdl, void *descArg, s32 x, s32 y, s32 cols, s32 rows, f32 scale, s32 idOffset) {
    u8 *desc = descArg;
    s32 blockSize; /* spB0, from func_151EDA54 */
    s32 texSize;   /* sp98 */
    s32 haveTex;
    s32 tex;
    f32 xscale;
    s32 tileW, tileH, dsdx, dtdy;
    s32 texId;
    s32 tx, ty, tyStart;
    s32 c, r;

    haveTex = 0;
    tex = 0;
    texSize = 0;
    gdl = func_151EDA54(gdl, desc, &blockSize);
    if (idOffset < 0) {
        xscale = 1.0f;
        idOffset = 0;
    } else {
        xscale = scale;
    }
    texId = *(s32 *)(desc + 0) + idOffset;
    tileW = (s32)((f32)*(u16 *)(desc + 6) * xscale * D_800901BC);
    tileH = (s32)((f32)*(u16 *)(desc + 8) * scale * D_800901C0);
    dtdy = (s32)(1024.0f / (scale * D_800901C0));
    dsdx = (s32)(1024.0f / (xscale * D_800901BC));
    tx = (s32)((f32)x * D_800901BC) - ((tileW * cols) >> 1);
    tyStart = (s32)((f32)y * D_800901C0) - ((tileH * rows) >> 1);
    for (c = 0; c < cols; c++) {
        ty = tyStart;
        for (r = 0; r < rows; r++) {
            if (haveTex == 0) {
                tex = func_1510D66C(texId, &texSize, 3, 0);
            }
            if (tex != (s32)0x80000000) {
                s32 xl4 = (s16)(tx * 4), xh4 = (s16)((tx + tileW) * 4);
                s32 yl4 = (s16)(ty * 4), yh4 = (s16)((ty + tileH) * 4);
                s32 lrs = blockSize - 1;
                s32 s, t;

                gdl->words.w0 = 0xE7000000;
                gdl->words.w1 = 0;
                gdl++;
                gdl->words.w0 = 0xFD000000 | ((D_8009E28C[desc[0xB]] & 3) << 19) | ((desc[0xA] & 7) << 21);
                gdl->words.w1 = tex;
                gdl++;
                gdl->words.w0 = 0xF3000000;
                if (lrs >= 0x7FF) {
                    lrs = 0x7FF;
                }
                gdl->words.w1 = 0x07000000 | ((lrs & 0xFFF) << 12);
                gdl++;
                gdl->words.w0 = 0xE4000000 | (((xh4 > 0 ? xh4 : 0) & 0xFFF) << 12) | ((yh4 > 0 ? yh4 : 0) & 0xFFF);
                gdl->words.w1 = (((xl4 > 0 ? xl4 : 0) & 0xFFF) << 12) | ((yl4 > 0 ? yl4 : 0) & 0xFFF);
                gdl++;
                gdl->words.w0 = 0xE1000000;
                s = 0;
                if (xl4 < 0) {
                    s32 v = (xl4 * (s16)dsdx) >> 7;
                    if ((s16)dsdx < 0) {
                        s = v > 0 ? v : 0;
                    } else {
                        s = v < 0 ? v : 0;
                    }
                }
                t = 0;
                if ((ty * 4) < 0) {
                    s32 v = (yl4 * (s16)dtdy) >> 7;
                    if ((s16)dtdy < 0) {
                        t = v > 0 ? v : 0;
                    } else {
                        t = v < 0 ? v : 0;
                    }
                }
                gdl->words.w1 = ((-s) << 16) | (-t & 0xFFFF);
                gdl++;
                gdl->words.w0 = 0xF1000000;
                gdl->words.w1 = (dsdx << 16) | (dtdy & 0xFFFF);
                gdl++;
            }
            ty += tileH;
            haveTex = 0;
            if (texSize > 0x1000) {
                haveTex = 1;
                if (tex != 0) {
                    tex += (blockSize << desc[0xB]) >> 1;
                }
                texSize -= (blockSize << desc[0xB]) >> 1;
            } else {
                texId++;
            }
        }
        tx += tileW;
    }
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl++;
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EDBE8.s")
#endif
#ifdef NON_MATCHING
/* HUD model (0xA8 bytes; func_151EE0C4 builds it, func_151EE394 draws it, func_151EE310 frees it). The pause /
 * counter screen keeps two: D_80090408 (file 0xA4, the blinking head) and D_8009040C (file 0xA2). */
typedef struct {
    Gfx **dls;          /* 0x00 the model's display lists (func_1503F91C) */
    Gfx *copies[4];     /* 0x04 HUD copies of the display lists (count entries) */
    u8 count;           /* 0x14 display list count */
    u8 blink;           /* 0x15 frames until the next blink (D_80090408 only) */
    u8 pad16[6];
    s32 seg6;           /* 0x1C segment 6 base of the model data */
    s32 u20;
    u8 *inst;           /* 0x24 animated model instance (0x3F8 bytes) */
    f32 mtx[2][4][4];   /* 0x28 model matrix, one per frame buffer (D_800BE9C0) */
} HudModel;

s32 func_1503F91C(s32, s32, void *, void *, void *, void *, void *);
void func_1503F8A8(u8 *, s32, s32, f32, f32, s32);
void func_1503F7A0(u8 *);
void func_10004074(void *);
u8 *allocate_memory(s32, s32, s32, s32);

/* hud_model_load: allocates a HudModel, loads model `file` with animation table entry `entry` (func_1503F91C),
 * starts animation `anim` at `speed`, and makes a HUD copy of each of its display lists: every
 * G_RDPSETOTHERMODE (0xEF) gets bit 16 of w0 cleared and render mode 0x5041C8, every G_SETCOMBINE (0xFC) becomes a
 * no-op, so the caller's combiner applies. Returns the HudModel, or 0 when an allocation or the load fails. */
s32 func_151EE0C4(s32 file, s32 entry, s32 anim, f32 speed) {
    HudModel *m;
    Gfx *src;
    Gfx *dst;
    u32 w0;
    u32 op;
    s32 size;
    s32 i;
    s32 j;

    m = (HudModel *) allocate_memory(sizeof(HudModel), 1, 0, 1);
    if (m == NULL) {
        return 0;
    }
    m->blink = 1;
    if (func_1503F91C(file, entry, &m->dls, &m->count, &m->seg6, &m->u20, &m->inst) != 0) {
        func_10004074(m);
        return 0;
    }
    guMtxIdentF(m->mtx[0]);
    guMtxIdentF(m->mtx[1]);
    *(f32 **) (m->inst + 0x3E0) = (f32 *) m->mtx[0];
    *(f32 **) (m->inst + 0x3E4) = (f32 *) m->mtx[1];
    func_1503F8A8(m->inst, 1, anim, speed, 0.0f, 0);

    /* size of each display list, up to and including its G_ENDDL (0xDF) */
    for (i = 0; i < m->count; i++) {
        src = m->dls[i];
        size = 0;
        do {
            size += sizeof(Gfx);
        } while (((src++)->words.w0 >> 24) != 0xDF);
        m->copies[i] = (Gfx *) allocate_memory(size, 1, 1, 1);
        if (m->copies[i] == NULL) {
            for (j = 0; j < i; j++) {
                func_10004074(m->copies[j]);
            }
            func_10004074(m);
            return 0;
        }
    }

    for (i = 0; i < m->count; i++) {
        src = m->dls[i];
        dst = m->copies[i];
        do {
            w0 = src->words.w0;
            dst->words.w0 = w0;
            dst->words.w1 = src->words.w1;
            op = w0 >> 24;
            if (op == 0xEF) {
                dst->words.w0 = w0 & ~0x10000;
                dst->words.w1 = 0x5041C8;
            }
            if (op == 0xFC) {
                dst->words.w0 = 0;
            }
            src++;
            dst++;
        } while (op != 0xDF);
    }
    return (s32) m;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE0C4.s")
#endif

void func_151EE310(u8 *arg0) {
    s32 i;

    if (arg0 != NULL) {
        func_1503FAA8(*(s32 *)(arg0 + 0x24));
        func_100043B4(arg0, 4);
        for (i = 0; i < arg0[0x14]; i++) {
            func_100043B4(((s32 **)(arg0 + 4))[i], 4);
        }
    }
}

#ifdef NON_MATCHING
extern Gfx D_800904C0[];
extern Gfx D_800904D8[];

/* hud_model_draw: draws a HudModel (func_151EE0C4) at screen position (x, y), z -100, with uniform `scale` (x and
 * scale times D_800901BC, y times D_800901C0): sets this frame buffer's model matrix, advances the animation
 * (func_1503F7A0), loads the HUD matrices and render state (D_800904C0, env alpha D_800E1060), segment 3 = the
 * instance's matrices for this frame buffer, segment 1 = the model data, then calls the HUD display list copies and
 * D_800904D8. D_80090408 (the head) blinks: a random 15..142 frame timer, texture 0x507 for its last 6 frames, else
 * 0x508, bound to segments 6 / 7; when that texture is not loaded yet (func_1510D66C returns 0x80000000) nothing
 * is drawn and gdl is returned unchanged. */
u8 *func_151EE394(u8 *gdl, s32 model, f32 x, f32 y, f32 scale) {
    HudModel *m = (HudModel *) model;
    Gfx *g = (Gfx *) gdl;
    s32 tex;
    s32 i;

    if (D_800901BC != 1.0f) {
        x *= D_800901BC;
        y *= D_800901C0;
        scale *= D_800901BC;
    }
    guMtxIdentF(m->mtx[D_800BE9C0]);
    m->mtx[D_800BE9C0][3][0] = x;
    m->mtx[D_800BE9C0][3][1] = y;
    m->mtx[D_800BE9C0][3][2] = -100.0f;
    m->mtx[D_800BE9C0][0][0] = scale;
    m->mtx[D_800BE9C0][1][1] = scale;
    m->mtx[D_800BE9C0][2][2] = scale;
    func_1503F7A0(m->inst);

    g->words.w0 = 0xDA380003; /* gSPMatrix: load modelview */
    g->words.w1 = (u32) D_80089810;
    g++;
    g->words.w0 = 0xDA380007; /* gSPMatrix: load projection */
    g->words.w1 = (u32) &D_800E1068;
    g++;
    g->words.w0 = 0xDE000000;
    g->words.w1 = (u32) D_800904C0;
    g++;
    g->words.w0 = 0xFC12FE25; /* combiner */
    g->words.w1 = 0xFFFFFBFD;
    g++;
    g->words.w0 = 0xD9000000; /* geometry mode: clear all ... */
    g->words.w1 = 0;
    g++;
    g->words.w0 = 0xD9FFFFFF; /* ... then set 0x200404 */
    g->words.w1 = 0x200404;
    g++;
    g->words.w0 = 0xFA000000; /* prim color white */
    g->words.w1 = 0xFFFFFFFF;
    g++;
    g->words.w0 = 0xFB000000; /* env color white, alpha D_800E1060 */
    g->words.w1 = (D_800E1060 & 0xFF) | ~0xFF;
    g++;
    g->words.w0 = 0xF8000000; /* fog color */
    g->words.w1 = 0xFF;
    g++;
    g->words.w0 = 0xDB06000C; /* segment 3 */
    g->words.w1 = *(u32 *) (m->inst + 0x3E8 + D_800BE9C0 * 4);
    g++;
    g->words.w0 = 0xDB060004; /* segment 1 */
    g->words.w1 = m->seg6;
    g++;
    if (m == (HudModel *) D_80090408) {
        m->blink--;
        if (m->blink == 0) {
            m->blink = (func_150ADA20() & 0x7F) + 15;
        }
        tex = func_1510D66C(m->blink < 7 ? 0x507 : 0x508, 0, 3, 0);
        if (tex == (s32) 0x80000000) {
            return gdl;
        }
        g->words.w0 = 0xDB060018; /* segment 6 */
        g->words.w1 = tex;
        g++;
        g->words.w0 = 0xDB06001C; /* segment 7 */
        g->words.w1 = tex;
        g++;
    }
    for (i = 0; i < m->count; i++) {
        g->words.w0 = 0xDE000000;
        g->words.w1 = (u32) m->copies[i];
        g++;
    }
    g->words.w0 = 0xDE000000;
    g->words.w1 = (u32) D_800904D8;
    g++;
    return (u8 *) g;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE394.s")
#endif

#ifdef NON_MATCHING
extern u8 *D_800904E8;   /* menu sprite entries (12 bytes each) */
extern u8 *D_800E10AC;   /* menu sprite block (0x1A8 bytes) */
extern s8 D_800E10B0;
extern s8 D_800E10B1;
extern s8 D_800E10B2;
extern s8 D_800E10B3;
extern s8 D_800E10B4;
u8 *allocate_memory(s32, s32, s32, s32);
s32 func_1502B6BC(s32 *, s32, s32 *, s32, ...);  /* varargs, as its definition (game_57FA0) */
s32 func_1510D3E0(s32, s32, s32, s32, s32 *);
// menu_sprites_load: mode 3's first frame. Allocates the 0x1A8-byte menu sprite block D_800E10AC (0x40 header bytes,
// then 30 entries of 12 bytes at D_800904E8: display list, asset, +8 filled by func_1510D3E0), loads the menu
// sprite assets 0x1C5..0x1E2 (func_1502B6BC(0, 1, 0, 2, 9, id)) and patches each display list up to its
// G_ENDDL (0xDF): G_VTX (1) addresses are relocated into the asset and the first two vertices get colour 0,0,0,0xFF,
// G_SETCOMBINE (0xFC) becomes 0xFC127E05 / 0xFFFFF3F8, G_SETOTHERMODE_H (0xEF) gets bit 0x100000 and w1 0x0F0A4000.
// Then clears D_800E10B0..B4 and the block's bytes 0 and 0x20. On allocation failure D_800904E8 stays NULL.
void func_151EE704(void) {
    u8 *block;
    s32 *asset;
    u32 *dl;
    u8 *vtx;
    s32 id;
    s32 off;
    u32 cmd;

    D_800904E8 = NULL;
    block = allocate_memory(0x1A8, 1, 0, 0);
    D_800E10AC = block;
    if (block == NULL) {
        return;
    }
    D_800904E8 = block + 0x40;
    for (id = 0x1C5, off = 0; id != 0x1E3; id++, off += 0xC) {
        asset = (s32 *) func_1502B6BC(NULL, 1, NULL, 2, 9, id);
        *(s32 **) (D_800904E8 + off + 4) = asset;
        *(s32 *) (D_800904E8 + off) = *asset;
        func_1510D3E0(*(s32 *) (D_800904E8 + off), 0, 1, 0x3E, (s32 *) (D_800904E8 + off + 8));
        dl = *(u32 **) (D_800904E8 + off);
        do {
            cmd = (dl[0] >> 24) & 0xFF;
            if (cmd == 1) {
                dl[1] += (u32) asset;
                vtx = (u8 *) dl[1];   /* P121/P120: the asm ORs 0x80000000, a no-op for the KSEG0 asset address (w1 += asset); kept out: it breaks wasm addresses */
                vtx[0xC] = 0;
                vtx[0xD] = 0;
                vtx[0xE] = 0;
                vtx[0xF] = 0xFF;
                vtx += 0x10;
                vtx[0xC] = 0;
                vtx[0xD] = 0;
                vtx[0xE] = 0;
                vtx[0xF] = 0xFF;
            }
            if (cmd == 0xFC) {
                dl[0] = 0xFC127E05;
                dl[1] = 0xFFFFF3F8;
            }
            if (cmd == 0xEF) {
                dl[1] = 0x0F0A4000;
                dl[0] |= 0x100000;
            }
            dl += 2;
        } while (cmd != 0xDF);
    }
    D_800E10B0 = 0;
    D_800E10B1 = 0;
    D_800E10B2 = 0;
    D_800E10B3 = 0;
    D_800E10AC[0] = 0;
    D_800E10AC[0x20] = 0;
    D_800E10B4 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE704.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EE93C.s")

#ifdef NON_MATCHING
/* save_screen_frame_draw: draws the save / load screen frame (D_80090174 mode of func_151ECB98, padC[0] = selected
 * entry): environment alpha D_800E0EC4, two halves of texture 0x7FB (RGBA16, second half mirrored in S), two pieces of
 * texture 0x887 (RGBA32), then the caption string. The caption id comes from asset table 0x1D (u16 per entry), reloaded
 * only when the entry changes (D_800E10B5 = entry + 1) and cached in D_800904EC (0 = no caption). Returns the DL end. */
extern u8 D_800E0EC4;
extern u8 D_800E10B5;
extern s32 D_800904EC;
s32 func_1502B7F0(s32 *, s32, ...);
void func_10004074(void *);
s32 func_1510D66C(s32, s32, s32, s32);
u8 *func_151E8E94(u8 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
Gfx *func_151EDBE8(Gfx *, void *, s32, s32, s32, s32, f32, s32);
#define SAVE_W(g, a, b) ((g)->words.w0 = (a), (g)->words.w1 = (b), (g)++)

Gfx *func_151EF3A0(Gfx *gdl, s32 entry) {
    s32 tex;
    u16 *table;
    u32 size;

    gDPPipeSync(gdl++);
    SAVE_W(gdl, 0xFB000000, D_800E0EC4 | 0xFFFFFF00); /* SetEnvColor 255, 255, 255, alpha */
    tex = func_1510D66C(0x7FB, 0, 3, 0);
    if (tex != (s32) 0x80000000) {
        SAVE_W(gdl, 0xFD100000, tex);        /* SetTImg RGBA16 */
        SAVE_W(gdl, 0xF5100000, 0x07054260); /* SetTile (load) */
        gDPLoadSync(gdl++);
        SAVE_W(gdl, 0xF3000000, 0x075FF000); /* LoadBlock */
        gDPPipeSync(gdl++);
        SAVE_W(gdl, 0xF5101800, 0x00054260); /* SetTile (render) */
        SAVE_W(gdl, 0xF2000000, 0x000BC07C); /* SetTileSize 48x32 */
        gDPSetOtherMode(gdl++, 0x002C3F, 0x504244);
        gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x190, 0x100, 0x250, 0x200, 0, 0, 0, 0x400, 0x400);
        gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x250, 0x100, 0x310, 0x200, 0, 0x5E0, 0, -0x400, 0x400);
    }
    gDPPipeSync(gdl++);
    tex = func_1510D66C(0x887, 0, 3, 0);
    if (tex != (s32) 0x80000000) {
        SAVE_W(gdl, 0xFD180000, tex);        /* SetTImg RGBA32 */
        SAVE_W(gdl, 0xF5180000, 0x07094250); /* SetTile (load) */
        gDPLoadSync(gdl++);
        SAVE_W(gdl, 0xF3000000, 0x073FF000); /* LoadBlock */
        gDPPipeSync(gdl++);
        SAVE_W(gdl, 0xF5181000, 0x00094250); /* SetTile (render) */
        SAVE_W(gdl, 0xF2000000, 0x0007C07C); /* SetTileSize 32x32 */
        gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x250, 0xBC, 0x290, 0xFC, 0, 0, 0, 0x400, 0x400);
        gdl = (Gfx *) func_151E8E94((u8 *) gdl, 0x180, 0xBC, 0x1D0, 0xFC, 0, 0x200, 0x200, 0x400, 0x400);
    }
    if (entry + 1 != D_800E10B5) {
        table = NULL;
        size = func_1502B7F0((s32 *) &table, 1, 0x1D);
        if ((u32) entry < (size >> 1)) {
            D_800904EC = table[entry];
        } else {
            D_800904EC = 0;
        }
        func_10004074(table);
        D_800E10B5 = entry + 1;
    }
    if (D_800904EC != 0) {
        gDPPipeSync(gdl++);
        gdl = func_151EDBE8(gdl, &D_800904EC, 0x94, 0x60, 1, 2, 1.0f, 0);
    }
    return gdl;
}
#undef SAVE_W
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_216470/func_151EF3A0.s")
#endif
