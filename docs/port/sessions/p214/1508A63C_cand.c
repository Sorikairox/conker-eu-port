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
