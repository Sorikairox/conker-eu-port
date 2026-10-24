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
