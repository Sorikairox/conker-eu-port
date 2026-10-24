// rail_link_pick: the next track node after `node` coming from `prev`, among its type-0 links (+9..+0xD of the
// D_800D2778 node, 0xFF / `prev` skipped): the last link whose band (+0xF) is not the wanted one (1 when `alt` is set,
// else 2; a band-0 link only when none was found yet), otherwise the last link in the wanted band; 0xFF when none.
s32 func_15088D24(u8 prev, u8 node, s32 alt) {
    u8 *p = (u8 *) &D_800D2778[node];
    u8 *q;
    u8 want;
    u8 match = 0xFF;
    u8 other = 0xFF;
    u8 link;
    s32 k;

    if ((s8) alt != 0) {
        want = 1;
    } else {
        want = 2;
    }
    for (k = 0; k < 5; k++) {
        link = p[9 + k];
        if (link == 0xFF || link == prev) {
            continue;
        }
        q = (u8 *) &D_800D2778[link];
        if (q[0xE] != 0) {
            continue;
        }
        if (q[0xF] == want) {
            match = link;
        } else if (other == 0xFF || q[0xF] != 0) {
            other = link;
        }
    }
    if (other == 0xFF) {
        other = match;
    }
    return other;
}
