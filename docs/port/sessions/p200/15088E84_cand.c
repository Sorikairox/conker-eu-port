extern s8 D_800D27B0;
extern s8 D_800D27C8;
s32 func_15088D24(u8, u8, s32);

// rail_param_step: moves rail record `rec`'s spline parameter +8 by `dt`. Below 0 it wraps (+1) and the four control
// nodes +0x2B..+0x2E shift one node back (new first node from func_15088D24, alt = +0x2F); from 1 on it wraps (-1) and
// they shift forward (new last node), and the new second node's camera type (+0xF) picks the camera mode D_800D27B0
// (5 -> 1, 6 -> 2; on the mirrored track D_800D27C8: 7 -> 1, 8 -> 2, 9 -> 3). On a shift the node counter +0x24 moves
// by the direction and gives the lap +0x27 (/ lap length +0x26; capped at the lap count D_800E1010[7] + 1 when
// D_800BE616 is set). A new highest lap +0x28 of a human player's (+0x31 < D_80090130) record that is not on the rail
// (+0x30 = 0) with time +0x1C > 0 records the lap time (+0x1C - lap start +0x18, max 0x7D00) in +0x20 and as the
// player's best lap (s16 at D_800E1010 + 0x30) when better, and on the last lap the total time (max 0x57E40) at
// D_800E1010 + 0x38; the lap start becomes the time (-time after the last lap). Returns the direction (-1, 0, 1).
s32 func_15088E84(struct_eu_80087640 *rec, f32 dt) {
    u8 *r = (u8 *) rec;
    u8 *node;
    s32 dir = 0;
    s8 laps;
    s8 player;
    s32 t;
    s16 *best;

    rec->unk8 += dt;
    if (rec->unk8 < 0.0f) {
        rec->unk8 += 1.0f;
        r[0x2E] = r[0x2D];
        r[0x2D] = r[0x2C];
        r[0x2C] = r[0x2B];
        dir = -1;
        r[0x2B] = func_15088D24(r[0x2D], r[0x2C], (s8) r[0x2F]);
    } else if (1.0f <= rec->unk8) {
        rec->unk8 -= 1.0f;
        r[0x2B] = r[0x2C];
        r[0x2C] = r[0x2D];
        r[0x2D] = r[0x2E];
        r[0x2E] = func_15088D24(r[0x2C], r[0x2D], (s8) r[0x2F]);
        dir = 1;
        if (D_800D27C8 == 0) {
            node = (u8 *) &D_800D2778[r[0x2C]];
            if (node[0xF] == 5) {
                D_800D27B0 = 1;
            }
            node = (u8 *) &D_800D2778[r[0x2C]];
            if (node[0xF] == 6) {
                D_800D27B0 = 2;
            }
        } else {
            node = (u8 *) &D_800D2778[r[0x2C]];
            if (node[0xF] == 7) {
                D_800D27B0 = 1;
            }
            node = (u8 *) &D_800D2778[r[0x2C]];
            if (node[0xF] == 8) {
                D_800D27B0 = 2;
            }
            node = (u8 *) &D_800D2778[r[0x2C]];
            if (node[0xF] == 9) {
                D_800D27B0 = 3;
            }
        }
    }
    if (dir == 0) {
        return dir;
    }

    laps = D_800E1010[7];
    rec->unk24 += dir;
    rec->unk27 = rec->unk24 / (s8) r[0x26];
    player = (s8) r[0x31];
    if (D_800BE616 != 0 && laps < rec->unk27) {
        rec->unk27 = laps + 1;
    }
    if (rec->unk27 <= (s8) r[0x28]) {
        return dir;
    }
    r[0x28] = rec->unk27;
    if (player < D_80090130 && (s8) r[0x30] == 0 && *(s32 *) (r + 0x1C) > 0) {
        if ((s8) r[0x28] <= laps) {
            best = (s16 *) ((u8 *) D_800E1010 + 0x30);
            t = *(s32 *) (r + 0x1C) - *(s32 *) (r + 0x18);
            if (t > 0x7D00) {
                t = 0x7D00;
            }
            if (best[player] <= 0 || t < best[player]) {
                best[player] = t;
            }
            *(s32 *) (r + 0x20) = t;
        }
        if (laps == (s8) r[0x28]) {
            t = *(s32 *) (r + 0x1C);
            if (t > 0x57E40) {
                t = 0x57E40;
            }
            ((s32 *) ((u8 *) D_800E1010 + 0x38))[player] = t;
        }
    }
    if (laps == (s8) r[0x28]) {
        *(s32 *) (r + 0x18) = -*(s32 *) (r + 0x1C);
    } else if ((s8) r[0x28] < laps) {
        *(s32 *) (r + 0x18) = *(s32 *) (r + 0x1C);
    }
    return dir;
}
