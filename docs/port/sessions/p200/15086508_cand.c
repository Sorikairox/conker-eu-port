s32 func_150870E0(s32);
s32 func_15086268(f32, f32, f32, s32, s32);
s32 func_150A3794(u8 *, s32, s32, s32);
s32 func_150867D4(s32, s32, s32, u8 *, void *);

// rail_point_pick: the track node for position (x, y, z): the nearest node of y's height band (func_15086268). With
// `count` > 0 and a node found: when the node's zone (func_150870E0) contains the position, or its radius (+8) is
// above 5000, the choice is func_150867D4's (node, count, first, list, sel); otherwise the link (+9..+0xD) whose
// line from the node passes closest to the position (only links the position lies ahead on) is checked with
// func_150867D4(node, count, first, list, sel) and taken when that returns the same link. Returns the chosen node, or
// the nearest node when none was chosen (0xFF when there is none).
s32 func_15086508(f32 x, f32 y, f32 z, s32 count, s32 first, u8 *list, void *sel) {
    struct_eu_800D2778 *node;
    struct_eu_800D2778 *to;
    u8 *zone;
    s32 res;
    s32 near;
    s32 pick;
    s32 got;
    s32 k;
    u8 link;
    u32 radius;
    f32 r2;
    f32 ex;
    f32 ez;
    f32 inv;
    f32 nx;
    f32 nz;
    f32 d;
    f32 px;
    f32 pz;
    f32 dist;
    f32 best;

    res = 0xFF;
    near = func_15086268(x, y, z, 0, func_15086218(y));
    if ((s8) count > 0 && near != 0xFF) {
        zone = (u8 *) func_150870E0(near);
        if (zone != NULL && func_150A3794(zone, (s32) x, (s32) y, (s32) z) != 0) {
            res = func_150867D4(near, (s8) count, (s8) first, list, sel);
        } else {
            node = &D_800D2778[near];
            radius = ((u8 *) node)[8];
            r2 = (f32) radius + (f32) radius;
            if (1e8f < r2 * r2) {
                res = func_150867D4(near, (s8) count, (s8) first, list, sel);
            } else {
                pick = 0xFF;
                best = 1e8f;
                for (k = 0; k < 5; k++) {
                    link = ((u8 *) node)[9 + k];
                    if (link == 0xFF) {
                        continue;
                    }
                    to = &D_800D2778[link];
                    ex = to->unk0 - node->unk0;
                    ez = to->unk4 - node->unk4;
                    inv = 1.0f / sqrtf(ex * ex + ez * ez);
                    ex *= inv;
                    ez *= inv;
                    nx = node->unk0;
                    nz = node->unk4;
                    d = x * ex + z * ez + -(nx * ex + nz * ez);
                    if (0.0f < d) {
                        px = x - (nx + ex * d);
                        pz = z - (nz + ez * d);
                        dist = px * px + pz * pz;
                        if (dist < best) {
                            pick = link;
                            best = dist;
                        }
                    }
                }
                if (pick != 0xFF) {
                    got = func_150867D4(near, (s8) count, (s8) first, list, sel);
                    if (got == pick) {
                        res = got;
                    }
                }
            }
        }
    }
    if (res != 0xFF) {
        near = res;
    }
    return near;
}
