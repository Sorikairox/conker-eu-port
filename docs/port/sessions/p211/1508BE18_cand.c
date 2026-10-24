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
