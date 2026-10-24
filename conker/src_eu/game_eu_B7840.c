#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15089BB0(void) {
    D_800D27D0 = NULL;
}

#ifdef NON_MATCHING
s32 func_1508C07C(s32);
s8 *func_1509B570(s32);
extern s32 D_80087650;
extern s32 D_80087690;
extern s32 D_80087698;
extern s32 D_800D3268;
extern s8 D_800E1000;

s32 func_1508A040(void) {
    s32 sp1C;
    s32 temp_a0;
    s32 var_v0;
    s8 *temp_v0;

    temp_a0 = D_800D3268;
    sp1C = temp_a0;
    temp_v0 = func_1509B570(temp_a0);
    if (temp_v0 == NULL) {
        return 0;
    }
    switch (temp_a0) {
    case 0xB9:
        D_800D27D0 = temp_v0;
block_12:
        sp1C = temp_a0;
        func_1508C07C(temp_a0);
        (*(s8 *)((u8 *)D_800D27D0 + 0x1700)) = 0;
        (*(s8 *)((u8 *)D_800D27D0 + 0x1701)) = 0;
        var_v0 = 0;
        (*(s8 *)((u8 *)D_800D27D0 + 0x1703)) = 0;
        (*(s8 *)((u8 *)D_800D27D0 + 0x1702)) = 0;
        (*(s8 *)((u8 *)D_800D27D0 + 0x1704)) = 0;
        (*(s16 *)((u8 *)D_800D27D0 + 0x16BC)) = (s16) temp_a0;
        (*(f32 *)((u8 *)D_800D27D0 + 0x16B8)) = (f32) *(s32 *)((u8 *)&D_80087650 + (D_800E1000 * 4));
        (*(s8 *)((u8 *)D_800D27D0 + 0x1745)) = 0;
        (*(s32 *)((u8 *)D_800D27D0 + 0x16C0)) = 0;
        (*(f32 *)((u8 *)D_800D27D0 + 0x1868)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
        if (0 != 0x30) {
            do {
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17A8)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17E8)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1828)) = 0.0f;
                (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16C4)) = 0;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x186C)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17AC)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17EC)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x182C)) = 0.0f;
                (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16C8)) = 0;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1870)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17B0)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17F0)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1830)) = 0.0f;
                (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16CC)) = 0;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1874)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17B4)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17F4)) = 0.0f;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1834)) = 0.0f;
                var_v0 += 0x10;
                (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16C0)) = 0;
                (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1868)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
            } while (var_v0 != 0x30);
        }
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17A8)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17E8)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1828)) = 0.0f;
        (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16C4)) = 0;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x186C)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17AC)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17EC)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x182C)) = 0.0f;
        (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16C8)) = 0;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1870)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17B0)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17F0)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1830)) = 0.0f;
        (*(s32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x16CC)) = 0;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1874)) = (f32) *(s32 *)((u8 *)&D_80087698 + (D_800E1000 * 4));
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17B4)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x17F4)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800D27D0[var_v0]) + 0x1834)) = 0.0f;
        (*(s32 *)((u8 *)D_800D27D0 + 0xC)) = (s32) *((s8 *)&D_80087690 + D_800E1000);
        return 0;
    case 0xB8:
        D_800D27D0 = temp_v0;
        goto block_12;
    case 0xBB:
        D_800D27D0 = temp_v0;
        goto block_12;
    case 0xBA:
        D_800D27D0 = temp_v0;
        goto block_12;
    case 0xB7:
        D_800D27D0 = temp_v0;
        goto block_12;
    case 0xBD:
        D_800D27D0 = temp_v0;
        goto block_12;
    case 0xBE:
        D_800D27D0 = temp_v0;
        goto block_12;
    default:
        D_800D27D0 = NULL;
        return 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508A040.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508A41C.s")

#ifdef NON_MATCHING
s32 func_150859AC(s16, s32);
// rail_rank_rivals: script command 5 (func_1509E3D4). Advances the rail cursor +0x1704 (wraps to 0 at the racer
// count +0x10) to racer `me`. If me's bit in the mask +0x14 is clear, its 16-entry rival list (+0x5DC[me * 16]) is
// cleared to -1. Otherwise every active (+0x39C > 0) racer k of another team (+0xE64) is scored by its xz distance
// to me (D_800CC2D0 objects; 0x7D00 without an object), +500 on another rail node (+0x9C), doubled when k is not
// among the first D_80090130 racers; with me's +0x16C0 bit (0x10000 << k) set, k is dropped (-1) when it is more
// than 3000 away and its object's unk65 is set, else kinds 2 / 3 (+0x15C) are dropped unless the race mode +0x16BC is
// 0xB8. In mode 0xB7 a dropped k keeps its raw distance and racers with a carrier (unk13C) are divided by
// func_150859AC(k, 6) + 2. Scores of the first D_80090130 racers are scaled by +0x16B8. Kept racers are inserted in
// ascending order into me's list (k in +0x5DC, score in +0x9DC), the rest of the list is set to -1, and the smallest
// raw distance (start 0x7D00) goes to +0x51C[me]. Returns 0 (asm too).
s32 func_1508A63C(void) {
    u8 *rail = (u8 *) D_800D27D0;
    s32 *team = (s32 *) (rail + 0xE64);
    s32 n = *(s32 *) (rail + 0x10);
    s32 mask = *(s32 *) (rail + 0x14);
    s32 *kind = (s32 *) (rail + 0x15C);
    s32 *active = (s32 *) (rail + 0x39C);
    s32 *node = (s32 *) (rail + 0x9C);
    s32 *links = (s32 *) (rail + 0x5DC);
    s32 *weights = (s32 *) (rail + 0x9DC);
    s32 me;
    s32 row;
    s32 myTeam;
    s32 flags;
    s32 best = 0x7D00;
    s32 count = 0;
    s32 mode;
    s32 dist;
    s32 d;
    s32 k;
    s32 j;
    s32 m;
    f32 dx;
    f32 dz;
    struct127 *obj;

    rail[0x1704]++;
    me = (s8) D_800D27D0[0x1704];
    if (*(s32 *) ((u8 *) D_800D27D0 + 0x10) == me) {
        D_800D27D0[0x1704] = 0;
        me = (s8) D_800D27D0[0x1704];
    }
    row = me * 16;
    if (!(mask & (1 << me))) {
        for (j = 0; j < 16; j++) {
            links[row + j] = -1;
        }
        return 0;
    }
    myTeam = team[me];
    flags = ((s32 *) ((u8 *) D_800D27D0 + 0x16C0))[me];
    for (k = 0; k < n; k++) {
        if (active[k] <= 0 || team[k] == myTeam) {
            continue;
        }
        mode = *(s16 *) ((u8 *) D_800D27D0 + 0x16BC);
        obj = &D_800CC2D0[k];
        if (obj != NULL) {
            dx = D_800CC2D0[me].x_position - obj->x_position;
            dz = D_800CC2D0[me].z_position - obj->z_position;
            d = sqrtf(dx * dx + dz * dz);
        } else {
            d = 0x7D00;
        }
        dist = d;
        if (node[me] != node[k]) {
            d += 500;
        }
        if (flags & (0x10000 << k)) {
            if (d > 3000 && obj->unk65 != 0) {
                d = -1;
            }
        } else {
            if (k >= D_80090130) {
                d *= 2;
            }
            if (mode != 0xB8 && (kind[k] == 2 || kind[k] == 3)) {
                d = -1;
            }
        }
        if (mode == 0xB7) {
            if (d == -1) {
                d = dist;
            }
            if (obj->unk13C != 0) {
                if (k >= D_80090130) {
                    d *= 2;
                }
                d /= func_150859AC(k, 6) + 2;
            }
        }
        if (k < D_80090130 && d != -1) {
            d = d * *(f32 *) ((u8 *) D_800D27D0 + 0x16B8);
        }
        if (d >= 0) {
            for (j = 0; j < count && weights[row + j] < d; j++) {
            }
            for (m = count; m != j; m--) {
                links[row + m] = links[row + m - 1];
                weights[row + m] = weights[row + m - 1];
            }
            links[row + j] = k;
            weights[row + j] = d;
            count++;
        }
        if (dist < best) {
            best = dist;
        }
    }
    for (j = count; j < 16; j++) {
        links[row + j] = -1;
    }
    if ((u8 *) D_800D27D0 + 0x51C != NULL) {
        ((s32 *) ((u8 *) D_800D27D0 + 0x51C))[me] = best;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508A63C.s")
#endif

#ifdef NON_MATCHING
extern u8 D_800E0FE8[];    /* per-racer input byte (bit 7 = trigger), consumed here */
extern s8 D_80087670[];    /* by difficulty D_800E1000: AI timer limit */
extern s8 D_80087680[];    /* by difficulty: AI timer restart value (negated) */
extern s16 D_80087664[];   /* by difficulty: boost time that forces a re-plan (-1 = never) */
extern s8 D_80087688[];    /* by difficulty: chance (percent) to keep the old steering offsets */
s32 func_15086218(f32);
s32 func_1508CF34(s32, s32, s32, s32, s32, s32);
void func_1508B854(void);
s32 func_1508DF48(s32, s32);
void func_1508F054(s32, s32);
void func_1508F0B8(s32, s32);
// rail_racers_update: script command 6 (func_1509E3D4; its result is read by the scripts). For every racer i of the rail
// state D_800D27D0 (count +0x10): racers in the mask +0x14 (or newly seen ones, which are added to the mask +0x18) run
// their timers by the frame time D_800BE9E4, take their input byte D_800E0FE8[i] (bit 7 cleared), refresh their rail
// node (+0x9C) and activity (+0x39C); a racer that is not started (+0x35C) and becomes active (or is new, or its object
// has unk2FD set) is started: its team count moves, func_1508DF48(i, 1) resets its route, and bit i goes into the
// result. Racers with a target (+0x31C) steer through func_1508CF34 with smoothed s8 offsets (+0x1725 / +0x1735) and
// pick a new random offset when their AI timer runs out; state 5 of the object's +0x232 places a boost point near it
// (and its target). Racers neither in the mask nor new are deactivated (active 0, node -1). Afterwards the frame scale
// +0x16B4 is set and, in race mode 0xB9, each player's +0x1574 counter is drawn (/50) on its viewport.
// Returns the bit mask of the racers started this call.
s32 func_1508AB7C(void) {
    u8 *rail = (u8 *) D_800D27D0;
    s32 mask = *(s32 *) (rail + 0x14);
    s32 seen = *(s32 *) (rail + 0x18);
    s32 n = *(s32 *) (rail + 0x10);
    s32 *flash = (s32 *) (rail + 0x1C);
    s32 *node = (s32 *) (rail + 0x9C);
    s32 *state = (s32 *) (rail + 0x19C);
    s32 *boost = (s32 *) (rail + 0x21C);
    s32 *cooldown = (s32 *) (rail + 0x25C);
    s32 *aiTimer = (s32 *) (rail + 0x29C);
    s32 *target = (s32 *) (rail + 0x31C);
    s32 *started = (s32 *) (rail + 0x35C);
    s32 *active = (s32 *) (rail + 0x39C);
    s32 *input = (s32 *) (rail + 0x3DC);
    s32 *timerC = (s32 *) (rail + 0x41C);
    s32 *teamCount = (s32 *) (rail + 0xDDC);
    s32 *team = (s32 *) (rail + 0xE64);
    s32 *counter = (s32 *) (rail + 0x1574);
    s32 result = 0;
    s32 i;
    s32 bit;
    s32 isNew;
    s32 myTeam;
    s32 prevAi;
    s32 replan;
    s32 wrapped;
    s32 lvl;
    s32 limit;
    s32 st;
    s32 k;
    u8 *obj;
    u8 *other;
    u8 *view;
    s32 half;
    u16 flags;

    for (i = 0; i < n; i++) {
        bit = 1 << i;
        flash[i] = 0;
        isNew = FALSE;
        if (!(mask & bit)) {
            if (!(seen & bit)) {
                isNew = TRUE;
            }
            seen |= bit;
            if (!isNew) {
                active[i] = 0;
                node[i] = -1;
                continue;
            }
        }
        obj = (u8 *) &D_800CC2D0[i];
        myTeam = team[i];
        if (myTeam != 0 && *(s16 *) ((u8 *) D_800D27D0 + 0x16BC) == 0xB9) {
            obj[0x1E4] = 1;
        }
        prevAi = aiTimer[i];
        boost[i] += D_800BE9E4;
        aiTimer[i] += D_800BE9E4;
        cooldown[i] -= D_800BE9E4;
        if (cooldown[i] <= 0) {
            cooldown[i] = 0;
        }
        timerC[i] -= D_800BE9E4;
        if (timerC[i] <= 0) {
            timerC[i] = 0;
        }
        counter[i] -= D_800BE9E4;
        if (counter[i] < 0) {
            counter[i] = 0;
        }
        if (state[i] == 3 && (cooldown[i] & 0x1F) >= 0x1D) {
            func_1508F0B8(i, 0x8000);
        }
        input[i] = D_800E0FE8[i];
        D_800E0FE8[i] &= 0x7F;
        ((s32 *) ((u8 *) D_800D27D0 + 0x4DC))[i] = (*(u8 **) (obj + 0x31C))[0x19A];
        active[i] = func_150859AC(i, 4);
        node[i] = func_15086218(*(f32 *) (obj + 0x18));

        if (active[i] != 0 && !isNew && obj[0x2FD] == 0) {
            started[i] = 0;
        } else if (started[i] == 0) {
            /* the racer starts */
            if (obj[0x20F] != 0xFF) {
                ((s32 *) ((u8 *) D_800D27D0 + 0x59C))[i] = obj[0x20F];
            } else {
                ((s32 *) ((u8 *) D_800D27D0 + 0x59C))[i] = -1;
            }
            started[i] = 1;
            cooldown[i] = 0;
            state[i] = 0;
            ((s32 *) ((u8 *) D_800D27D0 + 0x5C))[i] = 1;
            ((s32 *) ((u8 *) D_800D27D0 + 0x11C))[i] = -1;
            teamCount[myTeam]--;
            k = input[i] & 0x7F;
            if (k < n && myTeam != team[k]) {
                teamCount[team[k]]++;
            }
            if (*(s16 *) ((u8 *) D_800D27D0 + 0x16BC) != 0xB9) {
                ((s32 *) ((u8 *) D_800D27D0 + 0xFF0))[i] = 0;
                func_1508DF48(i, 1);
            }
            result |= bit;
        }

        /* steering towards the target (racer index + 2) */
        wrapped = TRUE;
        if (target[i] != 0 && *(s16 *) ((u8 *) D_800D27D0 + 0x16BC) != 0xB8) {
            replan = FALSE;
            if (state[i] != 1 && boost[i] < 0x1E) {
                st = obj[0x232];
                obj[0x222] = target[i] - 2;
                if (st != 4 && st != 5) {
                    func_1508F054(i, 4);
                }
                if (st == 4) {
                    boost[i] = 0;
                }
                if (st == 5) {
                    /* boost point: random spot within 50 of the racer, 40 above it, pulled halfway to the target */
                    boost[i] = 0x1E;
                    ((f32 *) ((u8 *) D_800D27D0 + 0x1868))[i] = ((f32 *) &D_80087698)[D_800E1000];
                    ((f32 *) ((u8 *) D_800D27D0 + 0x17A8))[i] = func_150ADA68() * 50.0f + *(f32 *) (obj + 0x14);
                    ((f32 *) ((u8 *) D_800D27D0 + 0x17E8))[i] = *(f32 *) (obj + 0x18) + 40.0f;
                    ((f32 *) ((u8 *) D_800D27D0 + 0x1828))[i] = func_150ADA68() * 50.0f + *(f32 *) (obj + 0x1C);
                    if (target[i] - 2 >= 2) {
                        other = (u8 *) &D_800CC2D0[target[i] - 2];
                        ((f32 *) ((u8 *) D_800D27D0 + 0x17A8))[i] +=
                            (*(f32 *) (other + 0x14) - *(f32 *) (obj + 0x14)) * 0.5f;
                        ((f32 *) ((u8 *) D_800D27D0 + 0x1828))[i] +=
                            (*(f32 *) (other + 0x1C) - *(f32 *) (obj + 0x1C)) * 0.5f;
                    }
                }
            }
            wrapped = FALSE;
            lvl = D_800E1000;
            limit = 0;
            if (D_80087670[lvl] < aiTimer[i]) {
                aiTimer[i] = 0;
                prevAi = -1;
            }
            /* the AI timer has just come round (negative before, not any more) */
            if (aiTimer[i] >= 0 && prevAi < 0) {
                limit = 1;
            }
            if (D_80087664[D_800E1000] != -1 && boost[i] >= D_80087664[D_800E1000]) {
                replan = TRUE;
            }
            rail = (u8 *) D_800D27D0;
            rail[0x1725 + i] += (s8) (((s8) rail[0x1705 + i] - (s8) rail[0x1725 + i]) >> 2);
            rail = (u8 *) D_800D27D0;
            rail[0x1735 + i] += (s8) (((s8) rail[0x1715 + i] - (s8) rail[0x1735 + i]) >> 2);
            rail = (u8 *) D_800D27D0;
            if (func_1508CF34(i, target[i] - 2, limit, replan, (s8) rail[0x1725 + i], (s8) rail[0x1735 + i]) != 0
                && state[i] != 1) {
                boost[i] = 0;
            }
            if (aiTimer[i] == 0) {
                /* new random steering offsets */
                ((s8 *) D_800D27D0)[0x1705 + i] = 0;
                ((s8 *) D_800D27D0)[0x1715 + i] = 0;
                if (D_80087688[D_800E1000] < (s32) (func_150ADA68() * 100.0f)) {
                    if (0.5f < func_150ADA68()) {
                        ((s8 *) D_800D27D0)[0x1705 + i] = -50;
                    } else {
                        ((s8 *) D_800D27D0)[0x1705 + i] = 50;
                    }
                    if (0.5f < func_150ADA68()) {
                        ((s8 *) D_800D27D0)[0x1715 + i] = 50;
                    } else {
                        ((s8 *) D_800D27D0)[0x1715 + i] = 0;
                    }
                }
            }
        }
        if (wrapped && *(s16 *) ((u8 *) D_800D27D0 + 0x16BC) != 0xB8) {
            aiTimer[i] = -D_80087680[D_800E1000];
        }
        flags = *(u16 *) (obj + 0x22C);
        *(u16 *) (obj + 0x22C) = flags & ~0x200;
        if ((flags & 0x200) || (input[i] & 0x80)) {
            state[i] = 0;
            flash[i] = 1;
        }
        if ((*(u8 **) (obj + 0x31C))[0x1AC] != 0) {
            cooldown[i] = 20;
        }
    }
    rail = (u8 *) D_800D27D0;
    *(s32 *) (rail + 0x18) = seen;
    if (D_800BE9E4 != 0) {
        *(f32 *) ((u8 *) D_800D27D0 + 0x16B4) = D_800BE9E4;
    } else {
        *(f32 *) ((u8 *) D_800D27D0 + 0x16B4) = 1.0f;
    }
    func_1508B854();
    if (*(s16 *) ((u8 *) D_800D27D0 + 0x16BC) == 0xB9) {
        /* each player's counter, centred on its viewport */
        view = *(u8 **) &D_800BE628;
        half = (s32) (*(f32 *) (view + 0x30) - *(f32 *) (view + 0x2C)) >> 1;
        func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
        obj = (u8 *) D_800CC2D0;
        for (i = 0; i <= D_80082FA0; i++, obj += 0x32C) {
            if (obj[0x128] == 0) {
                view = *(u8 **) &D_800BE628 + i * 0x180;
                func_15042D94((s32) (*(f32 *) (view + 0x2C) + (f32) half), (s32) (*(f32 *) (view + 0x24) + 6.0f), 1,
                              (s32) "%d", counter[i] / 50);
            }
        }
    }
    return result;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508AB7C.s")
#endif

s32 func_1508B5F0(s32 arg0) {
    if (arg0 >= D_80090130) {
        return 0;
    }
    return *(s16 *)((u8 *)D_80090174 + arg0 * 12 + 0x70);
}

void func_1508B630(s32 arg0) {
    if (arg0 < D_80090130) {
        *(s16 *)((u8 *)D_80090174 + arg0 * 12 + 0x70) = 0;
    }
}

// PERMUTER CHANGED DECL: voidfunc_1508B20C(f32,f32,f32,f32) (base: voidfunc_1508B20C(f32arg0,f32arg1,f32arg2,f32arg3))
void func_1508B20C(f32 arg0, f32 arg1, f32 arg2, f32 arg3)
{
  s32 temp_a1;
  s8 temp_v1;
  u8 *new_var;
  if (D_800D27D0 != 0)
  {
    temp_v1 = *((s8 *) (((u8 *) D_800D27D0) + 0x1745));
    if (temp_v1 < 8)
    {
      new_var = (u8 *) D_800D27D0; // fakematch: pointer copy in a named local (permuter)
      *((s8 *) (new_var + 0x1745)) = (s8) (temp_v1 + 1);
      temp_a1 = temp_v1 * 0xC;
      *((s16 *) (((u8 *) (D_800D27D0 + temp_a1)) + 0x174C)) = (s16) ((s32) arg0);
      *((s16 *) (((u8 *) (D_800D27D0 + temp_a1)) + 0x174E)) = (s16) ((s32) arg1);
      *((s16 *) (((u8 *) (D_800D27D0 + temp_a1)) + 0x1750)) = (s16) ((s32) arg2);
      *((f32 *) (((u8 *) (D_800D27D0 + temp_a1)) + 0x1748)) = (f32) (arg3 * arg3);
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508B704.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508B854.s")

#ifdef NON_MATCHING
extern f32 D_8009DE30;
extern f32 D_8009DE34;
void func_1508CA14(s32, s32);
s32 func_1508A63C(void);

// rail_pick_chase_target: script command 13 (func_1509E3D4). Refreshes the rail state (func_1508CA14 with 1 or, for
// more than 8 racers, 4; func_1508A63C), then picks the racer the current one (+0x4) should chase: among the active
// racers k (+0x39C[k] > 0, not itself) whose link list +0x5DC[k * 16..] (ended by -1) holds the current racer, the
// cost (link weight +0x9DC) * (byte +0x15B4[me * 16 + k] * D_8009DE34), times D_8009DE30 for the racer already in
// slot +0x11C[me], is lowest (start 10000000). Stores the pick in +0x49C[me] and in +0x45C[me] the distance to it
// (or the start cost when there is none). The link tables and the current racer are the ones read before the calls;
// the result slots go to the block D_800D27D0 points to afterwards. Returns 0.
s32 func_1508BE18(void) {
    u8 *rail = (u8 *) D_800D27D0;
    s32 n = *(s32 *) (rail + 0x10);
    s32 me = *(s32 *) (rail + 0x4);
    s32 *active = (s32 *) (rail + 0x39C);
    s32 *links = (s32 *) (rail + 0x5DC);
    s32 *weights = (s32 *) (rail + 0x9DC);
    s32 *current = (s32 *) (rail + 0x11C);
    u8 *bias;
    s32 best = -1;
    s32 bestCost = 10000000;
    s32 k;
    s32 j;
    s32 w;
    s32 cost;
    f32 f;
    f32 dx;
    f32 dz;

    func_1508CA14(0, (n < 9) ? 1 : 4);
    func_1508A63C();
    rail = (u8 *) D_800D27D0;
    bias = rail + me * 16 + 0x15B4;
    for (k = 0; k < n; k++) {
        if (active[k] <= 0 || k == me) {
            continue;
        }
        w = -1;
        for (j = k * 16; j < k * 16 + 16 && links[j] != -1; j++) {
            if (links[j] == me) {
                w = weights[j];
                break;
            }
        }
        if (w == -1) {
            continue;
        }
        f = bias[k] * D_8009DE34;
        if (current[me] == k) {
            f *= D_8009DE30;
        }
        cost = (s32) (w * f);
        if (cost < bestCost) {
            bestCost = cost;
            best = k;
        }
    }
    ((s32 *) (rail + 0x49C))[me] = best;
    if (best != -1) {
        dx = D_800CC2D0[me].x_position - D_800CC2D0[best].x_position;
        dz = D_800CC2D0[me].z_position - D_800CC2D0[best].z_position;
        ((s32 *) ((u8 *) D_800D27D0 + 0x45C))[me] = (s32) sqrtf(dx * dx + dz * dz);
    } else {
        ((s32 *) ((u8 *) D_800D27D0 + 0x45C))[me] = bestCost;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508BE18.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508C07C.s")

#ifdef NON_MATCHING
// rail_assign_targets: script command 7 (func_1509E3D4). For every racer i on the current racer's team (+0xE64), the
// ones of kind 2 / 3 (+0x15C) first, then the others: picks the active (+0x39C > 0) racer k of another team whose
// link list +0x5DC[k * 16..] (ended by -1) holds i, with the lowest link weight (+0x9DC) shifted left by the number
// of racers already assigned to k (start 10000000). Stores the cost in +0x45C[i] and k in +0x49C[i] (-1: none) and
// counts the assignment for k. Returns 0.
s32 func_1508C370(void) {
    u8 *rail = (u8 *) D_800D27D0;
    s32 me = *(s32 *) (rail + 0x4);
    s32 n = *(s32 *) (rail + 0x10);
    s32 *kind = (s32 *) (rail + 0x15C);
    s32 *active = (s32 *) (rail + 0x39C);
    s32 *team = (s32 *) (rail + 0xE64);
    s32 *cost = (s32 *) (rail + 0x45C);
    s32 *pick = (s32 *) (rail + 0x49C);
    s32 *links = (s32 *) (rail + 0x5DC);
    s32 *weights = (s32 *) (rail + 0x9DC);
    s32 myTeam = team[me];
    s8 assigned[40];
    s32 pass;
    s32 special;
    s32 best;
    s32 bestK;
    s32 i;
    s32 k;
    s32 j;
    s32 w;

    for (i = 0; i < n; i++) {
        assigned[i] = 0;
    }
    for (pass = 0; pass != 2; pass++) {
        for (i = 0; i < n; i++) {
            special = (kind[i] == 2 || kind[i] == 3);
            if (special ? pass != 0 : pass == 0) {
                continue;
            }
            if (team[i] != myTeam) {
                continue;
            }
            best = 10000000;
            bestK = -1;
            for (k = 0; k < n; k++) {
                if (active[k] <= 0 || team[k] == myTeam) {
                    continue;
                }
                w = -1;
                for (j = k * 16; j < k * 16 + 16 && links[j] != -1; j++) {
                    if (links[j] == i) {
                        w = weights[j];
                        break;
                    }
                }
                if (w == -1) {
                    continue;
                }
                w <<= assigned[k];
                if (w < best) {
                    best = w;
                    bestK = k;
                }
            }
            // with no pick the asm increments the unused stack byte before the array
            if (bestK != -1) {
                assigned[bestK]++;
            }
            cost[i] = best;
            pick[i] = bestK;
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508C370.s")
#endif

s32 func_1508C5F0(s32 arg0) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508C600.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508CA14.s")

#ifdef NON_MATCHING
/*
 * player_next_active: P190. Round-robin over the D_8008FD8C player records (D_800CC2D0) from the one after the
 * cursor D_800D27D0[0x1702]: returns the first record that is live (+0), has a state block (+0x31C) with +0x84 set
 * and whose bit in D_800D18A0 is clear (-1 if none); the cursor is left on the last record examined.
 */
s32 func_1508CE28(void) {
    s32 n = D_8008FD8C;
    s32 found = -1;
    s32 tries = 0;
    s32 i = D_800D27D0[0x1702] + 1;
    u8 *rec;
    u8 *state;

    for (;;) {
        i = (s8)i;
        if (i >= n) {
            i = 0;
        }
        rec = (u8 *)D_800CC2D0 + i * 0x32C;
        if (*(s32 *)rec != 0) {
            state = *(u8 **)(rec + 0x31C);
            if (state != NULL && state[0x84] != 0 && !(D_800D18A0 & (1 << i))) {
                tries = n;
                found = i;
            }
        }
        tries++;
        if (tries >= n) {
            break;
        }
        i++;
    }
    D_800D27D0[0x1702] = i;
    return found;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508CE28.s")
#endif

s32 func_1508CEE4(void) {
    D_800D27D0[0x1703]++;
    if (D_800D27D0[0x1703] >= D_80090130) {
        D_800D27D0[0x1703] = 0;
    }
    return D_800D27D0[0x1703];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508CF34.s")

#ifdef NON_MATCHING
extern s16 D_800876C0[];
extern s8 D_80087688[];
extern f32 D_8009DE5C;
extern s8 D_800E1000;
void func_1508EFEC(s32, s32, s32);
f32 func_150ADA68(void);

// rail_rival_pace: script command 14 (func_1509E3D4). Object `i` of D_800CC2D0 races towards the object in its rail
// slot +0x11C (copied to its record's +0x129). The distance band to it (0 far = beyond D_8009DE5C, 1 beyond 2000,
// 2 close) and the difficulty D_800E1000 pick a step limit from D_800876C0; once the slot's counter +0x29C passes it,
// the counter restarts (and when the target's bit 16 + target is set in the slot's mask +0x16C0, func_1508EFEC
// sends message 0x61). On a zero counter the record's boost flag +0x12A is set when 100 * random beats D_80087688.
// Returns the band while the counter runs, 0 otherwise: no event script reads command 14's result (P211 scan), the
// asm leaves the random helper's v0 there.
s32 func_1508DCAC(s32 i) {
    struct127 *obj = &D_800CC2D0[i];
    u8 *rail = (u8 *) D_800D27D0;
    s32 *target = (s32 *) (rail + 0x11C) + i;
    s32 *count = (s32 *) (rail + 0x29C) + i;
    struct127 *other;
    f32 dx;
    f32 dz;
    f32 d;
    s32 band;

    *((u8 *) obj->unk31C + 0x129) = *target;
    if (*target < 0) {
        return 0;
    }
    other = &D_800CC2D0[*target];
    dx = other->x_position - obj->x_position;
    dz = other->z_position - obj->z_position;
    d = sqrtf(dx * dx + dz * dz);
    if (D_8009DE5C < d) {
        band = 0;
    } else if (2000.0f < d) {
        band = 1;
    } else {
        band = 2;
    }
    if (D_800876C0[D_800E1000 * 3 + band] < *count) {
        *count = 0;
        if ((0x10000 << *target) & *(s32 *) ((u8 *) D_800D27D0 + i * 4 + 0x16C0)) {
            func_1508EFEC(i, 0x61, 0x2000);
        }
    }
    if (*count != 0) {
        return band;
    }
    *((u8 *) obj->unk31C + 0x12A) = 0;
    if (D_80087688[D_800E1000] < (s32) (func_150ADA68() * 100.0f)) {
        *((u8 *) obj->unk31C + 0x12A) = 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508DCAC.s")
#endif

#ifdef NON_MATCHING
// rail_state_reset: script command 10 (func_1509E3D4): marks the D_800D27D0 slots +0xEB0 free (-1, +0x10 of them)
// and resets the per-entry tables (+0xEA4 entries): +0xF70 = -1, +0xFF0 = 0, +0x10F0 = -1, +0x1070 = 1,
// +0x12F4 = 0. The counts are re-read through D_800D27D0 on every pass, the tables stay on the block it pointed to
// at entry. Returns what the asm leaves in v0 for the script runner: the end of the +0xF70 table, or the +0xEB0
// table when there are no entries (never 0).
s32 func_1508DE78(void) {
    u8 *rail = (u8 *) D_800D27D0;
    s32 *slots = (s32 *) (rail + 0xEB0);
    s32 *link = (s32 *) (rail + 0xF70);
    s32 *count = (s32 *) (rail + 0xFF0);
    s32 *one = (s32 *) (rail + 0x1070);
    s32 *prev = (s32 *) (rail + 0x10F0);
    s32 *extra = (s32 *) (rail + 0x12F4);
    s32 i;

    for (i = 0; i < *(s32 *) ((u8 *) D_800D27D0 + 0x10); i++) {
        slots[i] = -1;
    }
    for (i = 0; i < *(s32 *) ((u8 *) D_800D27D0 + 0xEA4); i++) {
        link[i] = -1;
        count[i] = 0;
        prev[i] = -1;
        one[i] = 1;
        extra[i] = 0;
    }
    if (i > 0) {
        return (s32) &link[i];
    }
    return (s32) slots;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508DE78.s")
#endif

#ifdef NON_MATCHING
s32 func_1508DF48(s32 arg0, s32 arg1) {
    s32 temp_a3;
    s32 temp_v1;
    s32 var_a1;
    struct127 *temp_v1_2;
    u8 *temp_a1;
    u8 *temp_t0;

    temp_a1 = D_800D27D0 + (arg0 * 4);
    if (D_800D27D0 == NULL) {
        return 0;
    }
    temp_v1 = (*(s32 *)((u8 *)temp_a1 + 0xEB0));
    if (temp_v1 >= 0) {
        if (arg1 < 0) {
            return 1;
        }
        (*(s32 *)((u8 *)temp_a1 + 0xEB0)) = -1;
        temp_a3 = temp_v1 * 4;
        temp_t0 = D_800D27D0 + temp_a3;
        if (!((*(s32 *)((u8 *)temp_t0 + 0x11F4)) & 2)) {
            (*(s32 *)((u8 *)temp_t0 + 0xF70)) = -1;
            (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x10F0)) = -1;
            var_a1 = (*(s32 *)((u8 *)D_800D27D0 + 0xEAC));
            if (arg1 == 1) {
                (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x12F4)) = 0xFA;
                temp_v1_2 = &D_800CC2D0[arg0];
                var_a1 = 4;
                (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x1374)) = (s32) temp_v1_2->x_position;
                (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x13F4)) = (s32) (temp_v1_2->y_position + 50.0f);
                (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x1474)) = (s32) temp_v1_2->z_position;
            }
            (*(s32 *)((u8 *)((D_800D27D0 + temp_a3)) + 0x1070)) = var_a1;
        }
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508DF48.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508E080.s")

void func_1508EB24(void) {
}

s32 func_1508EB2C(s32 arg0) {
    switch (arg0) {
    case 0x3F:
        return 0x708;
    case 0x14:
        return 0xC80;
    case 0x22:
        return 0x1F4;
    case 0x23:
        return 0x2710;
    case 0x16:
        return 0x186A0;
    case 0x15:
        return 0x1F4;
    case 0x21:
        return 0x1F4;
    case 0x24:
        return 0x186A0;
    case 0x19:
    case 0x40:
        return 0x1F4;
    case 0x9:
        return 0x1388;
    case 0x38:
        return 0x1388;
    case 0x18:
    case 0x41:
        return 0x186A0;
    case 0x3:
        return 0x2EE;
    case 0x37:
        return 0x5DC;
    default:
        return 0x186A0;
    }
}

s32 func_1508EBDC(s32 arg0) {
    if ((*(s16 *)((u8 *)D_800D27D0 + 0x16BC)) != 0xB8) {
        switch (arg0) {
        case 0x14:
            return 0x28;
        case 0x3F:
            return 0x2F;
        case 0x22:
            return 0x56;
        case 0x23:
            return 0x16;
        case 0x16:
            return 0x24;
        case 0x15:
            return 0x4B;
        case 0x21:
            return 0x58;
        case 0x24:
            return 0x63;
        case 0x19:
            return 0x57;
        case 0x40:
            return 0x21;
        case 0x9:
            return 0x1D;
        case 0x38:
            return 0x7B;
        case 0x39:
            return 0x82;
        case 0x37:
            return 0x85;
        case 0x18:
            return 0x55;
        case 0x41:
            return 0x2E;
        case 0x25:
            return 0x1060;
        default:
            return -1;
        }
    } else {
        switch (arg0) {                             /* switch 1; irregular */
        case 8:                                     /* switch 1 */
            return -1;
        case 1:                                     /* switch 1 */
            return 0x105C;
        case 16:                                    /* switch 1 */
            return 0x1019;
        case 2:                                     /* switch 1 */
            return 0x1059;
        default:                                    /* switch 1 */
            return -1;
        }
    }
}

#ifdef NON_MATCHING
extern u8 D_800D1CC4[];
extern u16 D_800D1CC2;
extern s8 D_80090134;
void func_15062800(struct127 *, struct127 *);

#define RAIL_WORDS(off) ((s32 *) ((u8 *) D_800D27D0 + (off)))

// rail_racer_take_over: script command 15 (func_1509E3D4). Racer i takes over racer j's place: only when i's
// D_800D1CC4 byte is >= 0x33 and i is not yet marked in D_800D1CC2. Marks i there, moves the D_800D18A0 bit from i to
// j, gives i j's func_150859AC(j, 3) value through func_15085710 (j gets 0), moves the rail flag word +0x18 bit i -> j,
// copies j's rail slots (+0x9C, +0x39C, +0x3DC, +0xEB0 with its back link +0xF70, +0x16C0) to i, swaps the two
// objects (func_15062800), on level 0x3F re-points the D_800D3268 record's racer entry of the object's carrier
// (unk13C >= 100) at the moved object, then resets object i (+0x125 = 0x5A, unk31C state byte 0x84, 0x1AA kept from
// before the swap, 0x1AF = 0x40), refreshes its camera (func_15128774) and counts D_80090134. Returns 0 (asm too).
s32 func_1508ECF8(s32 i, s32 j) {
    s32 mask;
    s32 jbit;
    s32 k;
    s32 saved1AA;
    struct127 *obj;
    struct127 *carrier;
    s32 slot;
    s8 *rec;
    u8 *entry;

    if (D_800D1CC4[i] < 0x33) {
        return 0;
    }
    mask = 1 << i;
    if (D_800D1CC2 & mask) {
        return 0;
    }
    jbit = 1 << j;
    D_800D18A0 &= ~mask;
    D_800D1CC2 |= mask;
    D_800D18A0 |= jbit;
    func_15085710(i, 2, func_150859AC(j, 3));
    func_15085710(j, 2, 0);

    if (RAIL_WORDS(0x18)[0] != 0) {
        RAIL_WORDS(0x18)[0] &= ~mask;
        RAIL_WORDS(0x18)[0] |= jbit;
    }
    if (RAIL_WORDS(0x9C) != NULL) {
        RAIL_WORDS(0x9C)[i] = RAIL_WORDS(0x9C)[j];
    }
    if (RAIL_WORDS(0x39C) != NULL) {
        RAIL_WORDS(0x39C)[i] = RAIL_WORDS(0x39C)[j];
    }
    if (RAIL_WORDS(0x3DC) != NULL) {
        RAIL_WORDS(0x3DC)[i] = RAIL_WORDS(0x3DC)[j];
    }
    if (RAIL_WORDS(0xEB0) != NULL) {
        RAIL_WORDS(0xEB0)[i] = RAIL_WORDS(0xEB0)[j];
        k = RAIL_WORDS(0xEB0)[i];
        if (k >= 0) {
            RAIL_WORDS(0xF70)[k] = i;
        }
    }
    RAIL_WORDS(0x16C0)[i] = RAIL_WORDS(0x16C0)[j];

    obj = &D_800CC2D0[i];
    saved1AA = obj->unk31C->unk1AA;
    func_15062800(&D_800CC2D0[j], obj);
    if (D_800BE9F0 == 0x3F && obj->unk13C >= 100) {
        carrier = &D_800CC2D0[(u8) (obj->unk13C - 100)];
        rec = func_1509B570(D_800D3268);
        if (rec != NULL) {
            slot = obj - D_800CC2D0;
            entry = (u8 *) rec + (carrier->unique_id - 0x14) * 4;
            *(s32 *) (entry + 0x24B8) = slot | 0x2000;
            *(s32 *) (entry + 0x24DC) = slot;
        }
    }
    obj->unk31C->unk84 = 0;
    obj->immune = 0x5A;
    obj->unk31C->unk1AA = saved1AA;
    *((u8 *) obj->unk31C + 0x1AF) = 0x40;
    func_15128774(obj->camera, obj);
    D_80090134++;
    return 0;
}

#undef RAIL_WORDS
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B7840/func_1508ECF8.s")
#endif

void func_1508EFEC(s32 arg0, s32 arg1, s32 arg2) {
    s32 t;
    t = *((u8 *)&D_800CC82F + arg0 * 0x32C);
    func_1509BFB0(1, t | 0x2000, arg1, arg2);
}

void func_1508F054(s32 arg0, s32 arg1) {
    s32 t;
    t = *((u8 *)&D_800CC82F + arg0 * 0x32C);
    func_1509BFB0(1, t | 0x2000, 0x14, arg1);
}

void func_1508F0B8(s32 arg0, s32 arg1) {
    s32 t;
    t = *((u8 *)&D_800CC82F + arg0 * 0x32C);
    func_1509BFB0(1, t | 0x2000, 0x61, arg1);
}
