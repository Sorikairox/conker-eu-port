// rail_node_next: the rail node after `node` coming from `prev` (D_800D2778, D_80087630 nodes of 16 bytes: s16 x / y / z,
// links +9..+0xD (0xFF = none), type +0xE, band +0xF). Takes the links in order, skipping 0xFF and `prev`; a link of
// type `type` (any type when `type` is 0xFF) and band `band` is returned at once, otherwise the last link of the right
// type. 0xFF when `node` is out of range or no link fits.
u8 func_150894F8(u8 node, u8 type, u8 prev, u8 band) {
    u8 *p;
    u8 *q;
    u8 last = 0xFF;
    u8 link;
    s32 k;

    if (node >= D_80087630) {
        return 0xFF;
    }
    p = (u8 *) &D_800D2778[node];
    for (k = 0; k < 5; k++) {
        link = p[9 + k];
        if (link == 0xFF || link == prev) {
            continue;
        }
        q = (u8 *) &D_800D2778[link];
        if (q[0xE] == type || type == 0xFF) {
            last = link;
            if (q[0xF] == band) {
                return link;
            }
        }
    }
    return last;
}
