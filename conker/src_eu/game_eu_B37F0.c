#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15088CA0(u8 *);

extern s8 D_800D27B9;

extern s32 D_800D27B4;

extern s8 D_800D27B8;


u8 *func_1502B5C8(s32, s32, s32, s32);
s32 func_15086058();
extern s16 D_80087634;

void func_15085FE0(s32 arg0) {
    u8 *temp_v0;

    temp_v0 = func_1502B5C8(0, 2, 0x19, arg0);
    if (temp_v0 == NULL) {
        D_80087630 = 0;
        D_80087634 = 0;
        D_800D2778 = NULL;
    } else {
        D_80087630 = (*(s16 *)temp_v0);
        D_80087634 = (*(s16 *)((u8 *)temp_v0 + 2));
        D_800D2778 = temp_v0 + 4;
    }
    func_15086058();
}

#ifdef NON_MATCHING
extern u8 D_800D2780; /* number of used height bands in D_800D2770 */
// point_bands_build: groups the D_800D2778 points by band (byte +6, 6 bands) and keeps each band's height range
// (+2). The used bands go in D_800D2770 (count D_800D2780) and the split heights between consecutive used bands in
// D_800D2788 (midpoint of band i's top and band i+1's bottom; a last 100000 entry ends func_15086218's search).
// Returns 1 when two consecutive bands overlap. Level start (func_15085FE0).
s32 func_15086058(void) {
    f32 top[6];
    f32 bottom[6];
    s32 overlap = 0;
    s32 i;
    struct_eu_800D2778 *p;
    f32 y;
    u8 a;
    u8 b;

    for (i = 0; i < 6; i++) {
        bottom[i] = 10000.0f;
        top[i] = -10000.0f;
    }
    for (i = 0, p = D_800D2778; i < D_80087630; i++, p++) {
        y = p->unk2;
        if (y < bottom[p->pad6]) {
            bottom[p->pad6] = y;
        }
        if (top[p->pad6] < y) {
            top[p->pad6] = y;
        }
    }
    D_800D2780 = 0;
    for (i = 0; i < 6; i++) {
        if (bottom[i] <= top[i]) {
            D_800D2770[D_800D2780++] = i;
        }
    }
    for (i = 0; i < D_800D2780 - 1; i++) {
        a = D_800D2770[i];
        b = D_800D2770[i + 1];
        D_800D2788[i] = (bottom[b] + top[a]) * 0.5f;
        if (bottom[b] < top[a]) {
            overlap = 1;
        }
    }
    D_800D2788[i] = 100000.0f;
    return overlap;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086058.s")
#endif

s32 func_15086218(f32 arg0) {
    s32 i = 0;

    while (D_800D2788[i] <= arg0) {
        i++;
    }
    return D_800D2770[i];
}

#ifdef NON_MATCHING
extern u8 D_8008763C;            /* node remembered by the last caller (0xFF none), tried first */
extern s32 D_800D277C;
f32 func_15087204(f32 x, f32 y, f32 z, f32 dx, f32 dz);
/* rail_node_nearest: the track node of D_800D2778 nearest to (x, y, z) among those of band `band` (+6) and kind
 * `kind` (+0xE; -1 = any). With kind 0 a node counts only when the straight move to it is free of walls
 * (func_15087204 < 0). The remembered node D_8008763C is tried first (its distance + 10 sets the bar) and then
 * cleared. Returns the node (0xFF none, also when nothing is nearer than 10000) and leaves its distance in
 * D_800D277C. */
s32 func_15086268(f32 x, f32 y, f32 z, s32 kind, s32 band) {
    struct_eu_800D2778 *p;
    f32 best = 1e8f;
    f32 dx, dy, dz, d;
    s32 walls = 0;
    s32 res = 0xFF;
    s32 i;

    kind = (s8) kind;
    band = (s8) band;
    if (kind == 0) {
        walls = 1;
    }
    if (D_8008763C != 0xFF) {
        p = &D_800D2778[D_8008763C];
        dx = p->unk0 - x;
        dy = p->unk2 - y;
        dz = p->unk4 - z;
        if (!walls || func_15087204(x, y, z, dx, dz) < 0.0f) {
            best = dx * dx + dy * dy + dz * dz + 10.0f;
        }
        D_8008763C = 0xFF;
    }
    for (i = 0; i < D_80087630; i++) {
        p = &D_800D2778[i];
        if (band != p->pad6 && band != -1) {
            continue;
        }
        if (kind != p->pad8[6] && kind != -1) {
            continue;
        }
        dx = p->unk0 - x;
        dy = p->unk2 - y;
        dz = p->unk4 - z;
        d = dx * dx + dy * dy + dz * dz;
        if (d < best && (!walls || func_15087204(x, y, z, dx, dz) < 0.0f)) {
            best = d;
            res = i;
        }
    }
    D_800D277C = sqrtf(best);
    return res;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086268.s")
#endif

#ifdef NON_MATCHING
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15086508.s")
#endif

#ifdef NON_MATCHING
f32 func_15087040(s32, s32);
extern u8 D_80087638;
extern s32 D_800D277C;

// rail_route_next: shortest route (Dijkstra over the D_800D2778 track nodes, links +9..+0xD, straight-line
// lengths; +5000 for a link into a node of `avoid`) from node `start` to the nearest node of `targets`
// (`nTargets` > 0). D_80087638 = the target reached (0xFF none), D_800D277C = the route length summed with
// func_15087040 over the zone runs (func_150870E0). Returns the next node to head for: the first step after start,
// or, when that step starts a zone run, the node where the run ends; `start` itself when it is a target, 0xFF when
// there is no route. The work arrays keep the asm frame layout (a long route or node ids >= 200 spill into the next
// array exactly like on N64).
s32 func_150867D4(s32 start, s32 nTargets, s32 nAvoid, u8 *targets, void *avoid) {
    struct {
        u8 zone[64];    /* sp+0x7C: route node i lies in a zone (func_150870E0) */
        u8 path[64];    /* sp+0xBC: the route, target first, start last */
        u8 prev[200];   /* sp+0xFC */
        u8 open[200];   /* sp+0x1C4: open list, 0xFF = free slot */
        s32 dist[209];  /* sp+0x28C */
    } w;
    struct_eu_800D2778 *nodes;
    u8 *node;
    u8 *other;
    s32 nOpen;
    s32 found;
    s32 best;
    s32 bestSlot;
    s32 cur;
    s32 link;
    s32 extra;
    s32 len;
    s32 slot;
    s32 free;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    s32 next;
    s32 first;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 total;

    nTargets = (s8) nTargets;
    nAvoid = (s8) nAvoid;
    D_80087638 = 0xFF;
    D_800D277C = 0;
    if (nTargets <= 0) {
        return 0xFF;
    }
    if (start < 0 || start >= D_80087630) {
        return 0xFF;
    }
    found = TRUE;
    for (i = 0; i < nTargets; i++) {
        if (start == targets[i]) {
            found = FALSE;
        }
    }
    if (!found) {
        D_80087638 = start;
        return start;
    }

    nOpen = 0;
    for (i = 0; i < D_80087630; i++) {
        w.dist[i] = 1000000;
    }
    nodes = D_800D2778;
    node = (u8 *) &nodes[start];
    for (k = 0; k < 5; k++) {
        link = node[9 + k];
        if (link == 0xFF) {
            continue;
        }
        extra = 0;
        for (i = 0; i < nAvoid; i++) {
            if (link == ((u8 *) avoid)[i]) {
                extra = 5000;
            }
        }
        w.open[nOpen] = link;
        w.prev[node[9 + k]] = start;
        other = (u8 *) &nodes[link];
        dx = *(s16 *) node - *(s16 *) other;
        dy = *(s16 *) (node + 2) - *(s16 *) (other + 2);
        dz = *(s16 *) (node + 4) - *(s16 *) (other + 4);
        nOpen++;
        w.dist[node[9 + k]] = (s16) (s32) sqrtf(dx * dx + dy * dy + dz * dz) + extra;
    }

    n = 0;
    for (;;) {
        best = 1000000;
        bestSlot = 0xFF;
        for (i = 0; i < nOpen; i++) {
            cur = w.open[i];
            if (cur != 0xFF && w.dist[cur] < best) {
                best = w.dist[cur];
                bestSlot = i;
            }
        }
        if (bestSlot == 0xFF) {
            break;
        }
        found = FALSE;
        if (bestSlot + 1 == nOpen) {
            nOpen--;
        }
        cur = w.open[bestSlot];
        w.open[bestSlot] = 0xFF;
        for (i = 0; i < nTargets; i++) {
            if (cur == targets[i]) {
                found = TRUE;
            }
        }
        if (found) {
            D_80087638 = cur;
            link = cur;
            if (cur != start) {
                w.path[n] = link;
                do {
                    link = w.prev[link];
                    n++;
                    if (link == start) {
                        break;
                    }
                    w.path[n] = link;
                } while (TRUE);
            }
            w.path[n] = link;
            n++;
            break;
        }
        node = (u8 *) &nodes[cur];
        len = w.dist[cur];
        for (k = 0; k < 5; k++) {
            link = node[9 + k];
            if (link == 0xFF || link == start) {
                continue;
            }
            extra = 0;
            for (i = 0; i < nAvoid; i++) {
                if (link == ((u8 *) avoid)[i]) {
                    extra = 5000;
                }
            }
            other = (u8 *) &nodes[link];
            dx = *(s16 *) node - *(s16 *) other;
            dy = *(s16 *) (node + 2) - *(s16 *) (other + 2);
            dz = *(s16 *) (node + 4) - *(s16 *) (other + 4);
            best = (s32) sqrtf(dx * dx + dy * dy + dz * dz) + len + extra;
            if (best >= w.dist[link]) {
                continue;
            }
            /* already open: shorter way; else into the first free slot (or appended) */
            free = 0xFF;
            for (slot = 0; slot < nOpen; slot++) {
                if (free == 0xFF && w.open[slot] == 0xFF) {
                    free = slot;
                }
                if (link == w.open[slot]) {
                    w.dist[link] = best;
                    w.prev[link] = cur;
                    break;
                }
            }
            if (slot == nOpen) {
                w.prev[link] = cur;
                w.dist[link] = best;
                if (free == 0xFF) {
                    free = nOpen;
                    nOpen++;
                }
                w.open[free] = link;
            }
        }
    }

    if (n < 2) {
        return 0xFF;
    }
    n -= 2;
    next = w.path[n];
    for (i = 0; i <= n + 1; i++) {
        w.zone[i] = func_150870E0(w.path[i]) != 0;
    }
    total = 0.0f;
    first = FALSE;
    if (w.zone[n] != 0) {
        if (w.zone[n + 1] == 0) {
            first = TRUE;
        } else if (n > 0 && w.zone[n - 1] == 0) {
            first = TRUE;
        }
    }
    if (n > 0) {
        do {
            j = n - 1;
            if (w.zone[j] != 0) {
                do {
                    j--;
                } while (j >= 0 && w.zone[j] != 0);
                j++;
            }
            total += func_15087040(w.path[n], w.path[j]);
            if (!first) {
                first = TRUE;
                if (w.zone[n] != 0) {
                    next = w.path[j];
                }
            }
            n = j;
        } while (j > 0);
    }
    D_800D277C = total;
    return next;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150867D4.s")
#endif

#ifdef NON_MATCHING
// rail_node_distance: straight-line distance between track nodes `a` and `b` of D_800D2778 (0 when either is
// 0xFF, no node).
f32 func_15087040(s32 a, s32 b) {
    s16 *pa;
    s16 *pb;
    f32 dx;
    f32 dy;
    f32 dz;

    if (a == 0xFF || b == 0xFF) {
        return 0.0f;
    }
    pa = (s16 *) &D_800D2778[a];
    pb = (s16 *) &D_800D2778[b];
    dx = pa[0] - pb[0];
    dy = pa[1] - pb[1];
    dz = pa[2] - pb[2];
    return sqrtf(dx * dx + dy * dy + dz * dz);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087040.s")
#endif

s32 func_150870E0(s32 arg0) {
    s32 temp_v1 = D_800D2778[arg0].unk4;

    return func_150A3674(3, 0xB, D_800D2778[arg0].unk0, D_800D2778[arg0].unk2, temp_v1);
}

s32 func_1508712C(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    if ((arg0 < 0) || (arg0 >= D_80087630)) {
        return 0;
    }
    *arg1 = (f32) D_800D2778[arg0].unk0;
    *arg2 = (f32) D_800D2778[arg0].unk2;
    *arg3 = (f32) D_800D2778[arg0].unk4;
    return 1;
}

s32 func_150871B8(s32 arg0) {
    s32 i;

    for (i = 0; i < D_80087630; i++) {
        if (arg0 == D_800D2778[i].unk7) {
            return i;
        }
    }
    return 0xFF;
}

#ifdef NON_MATCHING
// rail_wall_hit: where the move from (x, z) by (dx, dz) first crosses a wall: the type-1 nodes of D_800D2778 in the
// height band of `y` (node +6 = func_15086218(y)) and their links (+9..+0xD) to higher-numbered type-1 nodes form
// segments; a segment counts when the move's start and end lie on different sides of its line and the crossing
// point lies within the segment. Returns -1 when none is hit, else the move length times the crossing fraction of
// the last segment whose line the move crossed (Rare uses that fraction, not the smallest one it keeps).
f32 func_15087204(f32 x, f32 y, f32 z, f32 dx, f32 dz) {
    struct_eu_800D2778 *a;
    struct_eu_800D2778 *b;
    s32 band;
    s32 i;
    s32 k;
    u8 link;
    f32 ex;
    f32 ez;
    f32 c;
    f32 d0;
    f32 d1;
    f32 a0;
    f32 a1;
    f32 s;
    f32 hit;
    f32 best;

    band = func_15086218(y);
    best = 100.0f;
    s = 0.0f; // only read after a crossing set it
    for (i = 0; i < D_80087630; i++) {
        a = &D_800D2778[i];
        if (((u8 *) a)[0xE] != 1 || ((u8 *) a)[6] != band) {
            continue;
        }
        for (k = 0; k < 5; k++) {
            link = ((u8 *) a)[9 + k];
            if (link == 0xFF || link <= i) {
                continue;
            }
            b = &D_800D2778[link];
            if (((u8 *) b)[0xE] != 1) {
                continue;
            }
            // side of the segment's line (normal (ez, -ex)) for the start and the end of the move
            ez = b->unk4 - a->unk4;
            ex = -(f32) (b->unk0 - a->unk0);
            c = -(a->unk0 * ez + ex * a->unk4);
            d0 = x * ez + z * ex + c;
            d1 = (x + dx) * ez + (z + dz) * ex + c;
            if (!((d1 < 0.0f && 0.0f <= d0) || (d0 < 0.0f && 0.0f <= d1))) {
                continue;
            }
            a1 = d1;
            if (d1 < 0.0f) {
                a1 = -d1;
            }
            a0 = d0;
            if (d0 < 0.0f) {
                a0 = -d0;
            }
            s = a0 / (a0 + a1);
            // position of the crossing point and of b along the segment (a = 0)
            ex = -ex;
            c = -(a->unk0 * ex + ez * a->unk4);
            hit = (s * dx + x) * ex + (s * dz + z) * ez + c;
            d1 = b->unk0 * ex + ez * b->unk4 + c;
            if ((0.0f < d1 && 0.0f < hit && hit <= d1) || (d1 < 0.0f && hit < 0.0f && d1 <= hit)) {
                if (s < best) {
                    best = s;
                }
            }
        }
    }
    if (best <= 1.0f) {
        return sqrtf(dx * dx + dz * dz) * s;
    }
    return -1.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087204.s")
#endif

#ifdef NON_MATCHING
extern s8 D_800D27C8;
extern s8 D_800D27B9;
extern s8 D_800D27BA;
void *allocate_memory(s32, s32, s32, s32);
s32 func_150871B8(s32);
s32 func_15088D24(u8, u8, s32);

// rail_records_init: sets up the rail (track) records. From the node tagged `tag` (func_150871B8) it takes the type-0
// link with the highest band (the lowest when D_800D27C8 mirrors the track), the nodes after it and before the start
// (func_15088D24), and counts the nodes of one lap. Then D_800D27B8 = `humans`, D_800D27B9 = `cpus`, D_800D27B4 = 0,
// and D_80087640 gets humans + cpus records (0x84 bytes, func_15088CA0) with nodes +0x2B..+0x2E = back, start, next,
// after next, +0x26 = lap length, +0x31 = player index (human records), +0x30 = 1 from D_80090130 on; D_800D27BA = 1.
// Nothing (D_80087640 stays NULL) when the start node or one of its neighbours is missing.
void func_15087540(s32 tag, s32 humans, s32 cpus) {
    struct_eu_80087640 *rec;
    u8 *p;
    u8 *q;
    u8 start;
    u8 next;
    u8 after;
    u8 back;
    u8 best;
    u8 link;
    u8 prev;
    u8 cur;
    u8 nx;
    s32 laps;
    s32 total;
    s32 i;

    D_80087640 = NULL;
    start = func_150871B8(tag);
    if (start == 0xFF) {
        return;
    }
    best = D_800D27C8 * 0xFF;
    next = 0xFF;
    p = (u8 *) &D_800D2778[start];
    for (i = 0; i < 5; i++) {
        link = p[9 + i];
        if (link == 0xFF) {
            continue;
        }
        q = (u8 *) &D_800D2778[link];
        if (q[0xE] != 0) {
            continue;
        }
        if (D_800D27C8 == 0) {
            if (q[0xF] >= best) {
                best = q[0xF];
                next = link;
            }
        } else if (q[0xF] <= best) {
            best = q[0xF];
            next = link;
        }
    }
    if (next != 0xFF) {
        after = func_15088D24(start, next, 0);
        back = func_15088D24(next, start, 0);
    }
    if (next == 0xFF || back == 0xFF || after == 0xFF) {
        return;
    }
    // walk one lap: from (next, after) until the step that leaves the start node
    laps = 0;
    prev = next;
    cur = after;
    for (;;) {
        nx = func_15088D24(prev, cur, 0);
        laps++;
        if (prev == start) {
            break;
        }
        prev = cur;
        cur = nx;
    }
    D_800D27B9 = cpus;
    D_800D27B8 = humans;
    total = humans + cpus;
    D_800D27B4 = 0;
    D_80087640 = allocate_memory(total * 0x84, 1, 0, 0);
    for (i = 0; i < total; i++) {
        rec = &D_80087640[i];
        func_15088CA0((u8 *) rec);
        rec->pad28[3] = back;
        rec->pad28[5] = next;
        rec->pad28[6] = after;
        rec->pad28[4] = start;
        if (i < D_800D27B8) {
            rec->unk31 = i;
        }
        ((u8 *) rec)[0x26] = laps;
        ((u8 *) rec)[0x30] = !(i < D_80090130);
    }
    D_800D27BA = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15087540.s")
#endif

#ifdef NON_MATCHING
extern s8 D_800D27B0;
extern f32 D_800D27BC;
extern f32 D_800D27C0;
extern f32 D_800D27C4;
extern s8 D_800D27C9;
f32 func_15049AD0(s32 *, s32, f32);
f32 func_15049B94(s32 *, s32, f32, s32 *);
s32 func_15088E84(struct_eu_80087640 *, f32);
s32 func_150893AC(struct_eu_80087640 *, s32 *, s32 *, s32 *);
s32 func_1508849C(struct_eu_80087640 *, struct127 *, s32);
void func_15042D78(u8);

// rail_track_update: moves `player`'s rail record (D_80087640 + player * 0x84) along its spline to the point nearest
// the player object (D_800CC2D0 + rec[0x31]): the step +0 (start 0.5 when +0x30 is 0, else eased toward +4 by 1/8,
// clamped to +-0.06) is used, then up to 11 times the player's distance from the plane through the spline point
// (normal = the tangent, stored at +0xC / +0x10) is turned into a parameter step for func_15088E84 (halved when it
// grows). +0x14 gets the speed along the track ((previous - current distance) * 4 / frames). With +0x30 set it
// computes the camera point D_800D27BC / C0 / C4 on a copy moved 2 * `speed` ahead (human players: or 300 units
// behind player 0's yaw when `mode` is 0, written to the player's camera D_800D2104[obj[0x13F]] +8 / +A / +C, mode
// to obj +0x44, fov +0x20 by D_800D27B0); otherwise +0 becomes the step to the next point. Sets D_800D27C9 (rail
// cameras on), counts frames off-track in +0x1C, records state 2+ via func_1508849C (0xD) and, for player 0, ranks
// all D_800D27B8 records (score = t + segment, + 30000 - 1000 * place while +0x2A != 0x7F, - 10000 for the D_800D18A0
// players) and stores each record's place in +0x29.
void func_150877C0(s32 player, s32 mode, f32 speed) {
    struct_eu_80087640 *rec;
    u8 *r;
    u8 *obj;
    f32 px;
    f32 pz;
    f32 xs[4];
    f32 ys[4];
    f32 zs[4];
    f32 dx;
    f32 dz;
    f32 len;
    f32 seg;
    f32 sx;
    f32 sz;
    f32 c;
    f32 d;
    f32 prev;
    f32 ad;
    f32 gain;
    f32 step;
    f32 inv;
    s8 ok;
    s8 tries;
    s32 again;
    u8 copy[0x84];
    f32 score[16];
    s8 order[16];
    s32 n;
    s32 i;
    s32 sorted;
    f32 tf;
    s8 tb;

    tries = 0;
    if (D_80087640 == NULL) {
        return;
    }
    rec = &D_80087640[player];
    r = (u8 *) rec;
    obj = (u8 *) &D_800CC2D0[(s8) r[0x31]];
    px = *(f32 *) (obj + 0x14);
    pz = *(f32 *) (obj + 0x1C);
    D_800D27B0 = 0;
    if ((s8) r[0x30] == 0) {
        rec->unk0 = 0.5f;
    } else {
        step = (rec->unk4 - rec->unk0) * 0.125f;
        if (0.06f < step) {
            step = 0.06f;
        }
        if (step < -0.06f) {
            step = -0.06f;
        }
        rec->unk0 = rec->unk0 + step;
    }
    gain = 0.75f;
    ok = 1;
    prev = 10000.0f;
    do {
        again = 0;
        if (ok) {
            func_150893AC(rec, (s32 *) xs, (s32 *) ys, (s32 *) zs);
            dx = xs[2] - xs[1];
            dz = zs[2] - zs[1];
            seg = sqrtf(dx * dx + dz * dz);
        }
        sx = func_15049B94((s32 *) xs, 0, rec->unk8, (s32 *) &dx);
        sz = func_15049B94((s32 *) zs, 0, rec->unk8, (s32 *) &dz);
        inv = -1.0f / sqrtf(dx * dx + dz * dz);
        dx *= inv;
        dz *= inv;
        *(f32 *) (r + 0xC) = dx;
        *(f32 *) (r + 0x10) = dz;
        c = -(sx * dx + sz * dz);
        d = dx * px + dz * pz + c;
        if (d < -50.0f || 50.0f < d) {
            ad = d;
            if (d < 0.0f) {
                ad = -d;
            }
            if (prev < ad) {
                gain *= 0.5f;
            }
            prev = ad;
            again = 1;
            step = d * gain / seg;
            if (step < -0.5f) {
                step = -0.5f;
            }
            if (0.5f < step) {
                step = 0.5f;
            }
            ok = func_15088E84(rec, -step);
        }
        tries++;
        if (tries >= 11) {
            again = 0;
        }
    } while (again);

    func_15042D78(0x80);
    r[0x32] = r[0x33];
    r[0x33] = D_800BE9E4;
    rec->unk14 = ((*(f32 *) (obj + 0x2C) * dx + *(f32 *) (obj + 0x34) * dz + c) - d) * 4.0f / (s8) r[0x32];
    if ((s8) r[0x30] != 0) {
        bcopy(rec, copy, 0x84);
        func_15088E84((struct_eu_80087640 *) copy, speed + speed);
        func_150893AC((struct_eu_80087640 *) copy, (s32 *) xs, (s32 *) ys, (s32 *) zs);
        D_800D27BC = func_15049AD0((s32 *) xs, 0, ((struct_eu_80087640 *) copy)->unk8);
        D_800D27C0 = func_15049AD0((s32 *) ys, 0, ((struct_eu_80087640 *) copy)->unk8);
        D_800D27C4 = func_15049AD0((s32 *) zs, 0, ((struct_eu_80087640 *) copy)->unk8);
        if (player < D_800D27B8) {
            if (mode == 0) {
                // player 0's yaw (D_800CC2D0[0] +0x40) in degrees (Rare's 0.01745 for pi / 180)
                f32 ang = *(f32 *) ((u8 *) D_800CC2D0 + 0x40) * 0.01745;

                D_800D27BC = sinf(ang) * 300.0f + *(f32 *) (obj + 0x14);
                D_800D27C0 = *(f32 *) (obj + 0x18);
                D_800D27C4 = cosf(ang) * 300.0f + *(f32 *) (obj + 0x1C);
            }
            *(s16 *) ((u8 *) D_800D2104[obj[0x13F]] + 8) = D_800D27BC;
            *(s16 *) ((u8 *) D_800D2104[obj[0x13F]] + 0xA) = D_800D27C0;
            *(s16 *) ((u8 *) D_800D2104[obj[0x13F]] + 0xC) = D_800D27C4;
            *(f32 *) (obj + 0x44) = mode;
            if (D_800D27B0 == 1) {
                *(f32 *) (obj + 0x20) = 75.0f;
            } else if (D_800D27B0 == 2) {
                *(f32 *) (obj + 0x20) = 55.0f;
            } else if (D_800D27B0 == 3) {
                *(f32 *) (obj + 0x20) = 65.0f;
            }
            obj[0x21E] = 0;
        }
    } else {
        rec->unk0 = 0.0f;
        func_150893AC(rec, (s32 *) xs, (s32 *) ys, (s32 *) zs);
        sx = func_15049AD0((s32 *) xs, 0, rec->unk8);
        sz = func_15049AD0((s32 *) zs, 0, rec->unk8);
        rec->unk0 = 1.0f;
        func_150893AC(rec, (s32 *) xs, (s32 *) ys, (s32 *) zs);
        dx = func_15049AD0((s32 *) xs, 0, rec->unk8) - sx;
        dz = func_15049AD0((s32 *) zs, 0, rec->unk8) - sz;
        len = sqrtf(dx * dx + dz * dz);
        if (1.0f < len) {
            inv = 1.0f / len;
            dx *= inv;
            dz *= inv;
            rec->unk0 = ((dx * px + dz * pz) - (dx * sx + dz * sz)) * inv;
        } else {
            rec->unk0 = 0.0f;
        }
    }
    r[0x48] = mode;
    D_800D27C9 = 1;
    if ((s8) r[0x30] == 0 && r[0x48] != 0 && !(D_800D18A0 & (1 << (s8) r[0x31]))) {
        *(s32 *) (r + 0x1C) += D_800BE9E4;
    }
    if ((s8) r[0x30] >= 2 && (*(u8 **) (obj + 0x31C))[0x84] == 0) {
        func_1508849C(rec, (struct127 *) obj, 0xD);
    }
    if (player != 0) {
        return;
    }

    n = D_800D27B8;
    for (i = 0; i < n; i++) {
        order[i] = i;
        score[i] = D_80087640[i].unk8 + D_80087640[i].unk24;
        if ((s8) D_80087640[i].pad28[2] != 0x7F) {
            score[i] += 30000.0f - (s8) D_80087640[i].pad28[2] * 1000.0f;
        }
        if (D_800D18A0 & (1 << (s8) D_80087640[i].unk31)) {
            score[i] -= 10000.0f;
        }
    }
    do {
        sorted = 1;
        for (i = 0; i < n - 1; i++) {
            if (score[i] < score[i + 1]) {
                tb = order[i];
                order[i] = order[i + 1];
                order[i + 1] = tb;
                tf = score[i];
                score[i] = score[i + 1];
                score[i + 1] = tf;
                sorted = 0;
            }
        }
    } while (!sorted);
    if (n > 0) {
        for (i = 0; i < D_800D27B8; i++) {
            D_80087640[order[i]].pad28[1] = i + 1;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150877C0.s")
#endif

#ifdef NON_MATCHING
extern s8 D_800D27C9;
void func_15089664(u8 *rec, u8 *player);
void func_15089B68(u8 *rec, u8 *player, s32 release);

// rail_cameras_update: clears D_800D27C9 and runs the rail camera of each of the D_800D27B8 player records
// (D_80087640, 0x84 bytes) whose player (D_800CC2D0 + rec[0x31]) has a camera (+0x318): records in state 2 or more
// (rec[0x30]) follow the rail (func_15089664), the others with rec[0x48] == 0 run the spline camera
// (func_15089B68), and the rest release the spline camera once while rec[0x49] is set.
void func_15088130(void) {
    u8 *rec;
    u8 *player;
    s32 i;

    D_800D27C9 = 0;
    if (D_80087640 == NULL) {
        return;
    }
    for (i = 0; i < D_800D27B8; i++) {
        rec = (u8 *) D_80087640 + i * 0x84;
        player = (u8 *) &D_800CC2D0[(s8) rec[0x31]];
        if (*(s32 *) (player + 0x318) == 0) {
            continue;
        }
        if ((s8) rec[0x30] >= 2) {
            func_15089664(rec, player);
        } else if (rec[0x48] == 0) {
            func_15089B68(rec, player, 0);
        } else if ((s8) rec[0x49] != 0) {
            func_15089B68(rec, player, 1);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088130.s")
#endif

s32 func_15088D24(u8, u8, s32);
void func_1508823C(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_v1;
    s32 temp_v0;
    if (D_80087640 != NULL) {
        temp_v1 = &D_80087640[arg0];
        if (arg1 != (s8) temp_v1->pad28[7]) {
            if (arg1 != 0) {
                temp_v0 = func_15088D24(temp_v1->pad28[3], temp_v1->pad28[4], 1);
                temp_v1->pad28[5] = temp_v0;
                temp_v1->pad28[6] = func_15088D24(temp_v1->pad28[4], temp_v0, 1);
            }
            temp_v1->pad28[7] = (u8) arg1;
        }
    }
}

#ifdef NON_MATCHING
// obj_yaw_clamp_to_track: keeps the object's yaw (+0x76) within 0x2400 of a quarter turn (+0x4000) past player
// `player`'s track direction (record D_80087640 + player * 0x84, vector +0x10 / +0xC, func_1505A630). Nothing without
// player records. Returns func_1505A630's raw result (the asm leaves v0 unset without records; the one caller
// ignores it).
s32 func_150882C4(u8 player, struct127 *obj) {
    struct_eu_80087640 *rec;
    s32 r;
    u16 dir;
    u16 diff;

    if (D_80087640 == NULL) {
        return 0;
    }
    rec = &D_80087640[player];
    r = func_1505A630(*(f32 *) ((u8 *) rec + 0x10), *(f32 *) ((u8 *) rec + 0xC), 0);
    dir = r + 0x4000;
    diff = dir - *(u16 *) ((u8 *) obj + 0x76);
    if (diff & 0x8000) {
        if (diff < 0xDBFF) {
            *(u16 *) ((u8 *) obj + 0x76) = dir + 0x2400;
        }
    } else if (diff > 0x2400) {
        *(u16 *) ((u8 *) obj + 0x76) = dir - 0x2400;
    }
    return r;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150882C4.s")
#endif

#ifdef NON_MATCHING
extern s8 D_800D27C8;

// player_face_track_side: turns the object (+0x76 yaw) a quarter turn (+0x3600 / +0x4A00) from the direction of
// player `player`'s track vector (+0x10 / +0xC, func_1505A630), the side picked by the track position +0 against 0.5
// (mirrored when D_800D27C8 is set). Returns that direction (0 without player records); the one caller ignores it.
s32 func_15088360(s32 player, struct127 *obj) {
    struct_eu_80087640 *rec;
    u16 dir;

    if (D_80087640 == NULL) {
        return 0;
    }
    rec = &D_80087640[player];
    dir = func_1505A630(*(f32 *)((u8 *)rec + 0x10), *(f32 *)((u8 *)rec + 0xC), 0);
    if (D_800D27C8 == 0) {
        if (rec->unk0 < 0.5f) {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x4A00;
        } else {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x3600;
        }
    } else {
        if (0.5f <= rec->unk0) {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x4A00;
        } else {
            *(u16 *)((u8 *)obj + 0x76) = dir + 0x3600;
        }
    }
    return dir;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088360.s")
#endif

void func_15088434(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_v1;

    if (D_80087640 != NULL) {
        temp_v1 = &D_80087640[arg0];
        temp_v1->unk31 = arg1;
    }
}

void func_1508845C(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_v1;

    if (D_80087640 != NULL) {
        temp_v1 = &D_80087640[arg0];
        temp_v1->unk4 = arg1 * (1.0f / 256);
    }
}

struct216 *func_1507BB28(s32, s32);

s32 func_1508849C(struct_eu_80087640 *arg0, struct127 *arg1, s32 arg2) {
    struct126 *temp_v0;

    temp_v0 = arg1->unk31C;
    if (temp_v0->unk120 != 0) {
        return 1;
    }
    if (D_800D18A0 & (1 << (arg1 - D_800CC2D0))) {
        return 1;
    }
    temp_v0->unk84 = 1;
    arg1->interaction_state = 0xC;
    arg1->unk232 = arg2;
    D_800D154C = arg1;
    D_800C3E78 = *(s8 *)&arg0->unk31;
    arg1->unk218 = func_1507BB28(0, arg2);
    arg1->unk21C = 0;
    arg1->immune = 0xFF;
    arg0->pad28[8] = 2;
    return 0;
}

s32 func_1508849C(struct_eu_80087640 *, struct127 *, s32); // 3 params: the asm never reads a3 (s87)
extern s8 D_800D27BA;

s32 func_15088568(s32 arg0, s32 arg1) {
    struct_eu_80087640 *temp_a0;
    struct127 *temp_a1;
    s8 temp_v1;
    s32 var_a2;
    struct_eu_80087640 *sp1C;

    var_a2 = 0;
    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    temp_v1 = (s8) temp_a0->pad28[8];
    temp_a1 = &D_800CC2D0[(s8) temp_a0->unk31];
    if (temp_v1 == 0) {
        sp1C = temp_a0;
        var_a2 = func_1508849C(temp_a0, temp_a1, arg1);
    } else if (temp_v1 == 1) {
        temp_a0->pad28[8] = 2;
        temp_a1->immune = 0xFF;
    }
    temp_a0->pad28[2] = (u8) D_800D27BA;
    D_800D27BA += 1;
    return var_a2;
}

s32 func_1508863C(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk0 * 256.0f;
}

s32 func_15088688(s32 arg0) {
    struct_eu_80087640 *temp_a0;
    s16 temp_a2;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    temp_a2 = temp_a0->unk24;
    return (temp_a2 * 16) + (s32)(temp_a0->unk8 * 16.0f);
}

s32 func_150886E0(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk14 * 0.8f;
}

s32 func_1508872C(s32 arg0) {
    struct_eu_80087640 *temp_a0;

    if (D_80087640 == NULL) {
        return 0;
    }
    temp_a0 = &D_80087640[arg0];
    return temp_a0->unk27;
}

#ifdef NON_MATCHING
// player_place_gap: finds the other player whose place (+0x29) is `player`'s place + `delta` and returns the absolute
// track-progress gap to it (lap +0x24 * 16 + segment +8 * 16) << 8 | its index; 16 when there is none.
s32 func_15088760(s32 player, s32 delta) {
    struct_eu_80087640 *me;
    struct_eu_80087640 *other;
    s32 place;
    s32 gap;
    s32 i;

    if (D_80087640 == NULL) {
        return 16;
    }
    me = &D_80087640[player];
    place = *(s8 *)((u8 *)me + 0x29) + delta;
    for (i = 0, other = D_80087640; i < D_800D27B8; i++, other++) {
        if (place == *(s8 *)((u8 *)other + 0x29) && i != player) {
            gap = me->unk24 * 16 + (s32)(me->unk8 * 16.0f) - other->unk24 * 16 - (s32)(other->unk8 * 16.0f);
            if (gap < 0) {
                gap = -gap;
            }
            return (gap << 8) | i;
        }
    }
    return 16;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088760.s")
#endif

#ifdef NON_MATCHING
// rail_find_ahead: the nearest other racer in front of player `player`'s object along its rail record's track
// direction (+0xC / +0x10, reversed when `dir` >= 0): among the D_800D27B8 records whose player (+0x31) is not the
// object's own (obj[0x124] - 1) and, when the record's alt +0x2F is set, with the same alt, the one with the smallest
// positive distance (< 10000) from the plane through the player's position. Stores that record's +0 in `*t` and its
// alt in `*alt` and returns its object (D_800CC2D0 + +0x31); NULL when there is none or no records.
struct127 *func_1508882C(s32 player, s32 dir, f32 *t, s32 *alt) {
    struct_eu_80087640 *rec;
    struct_eu_80087640 *other;
    struct127 *obj;
    struct127 *found;
    f32 sign;
    f32 nx;
    f32 nz;
    f32 c;
    f32 d;
    f32 best;
    s8 self;
    s8 want;
    s8 id;
    s32 i;

    if (D_80087640 == NULL) {
        return NULL;
    }
    rec = &D_80087640[player];
    if (dir >= 0) {
        sign = -1.0f;
    } else {
        sign = 1.0f;
    }
    nx = *(f32 *) ((u8 *) rec + 0xC) * sign;
    nz = *(f32 *) ((u8 *) rec + 0x10) * sign;
    obj = &D_800CC2D0[(s8) rec->unk31];
    want = ((u8 *) rec)[0x2F];
    self = ((u8 *) obj)[0x124] - 1;
    found = NULL;
    best = 10000.0f;
    c = -(nx * *(f32 *) ((u8 *) obj + 0x14) + nz * *(f32 *) ((u8 *) obj + 0x1C));
    for (i = 0; i < D_800D27B8; i++) {
        other = &D_80087640[i];
        id = other->unk31;
        if (self == id) {
            continue;
        }
        if (want != 0 && want != (s8) ((u8 *) other)[0x2F]) {
            continue;
        }
        obj = &D_800CC2D0[id];
        d = nx * *(f32 *) ((u8 *) obj + 0x14) + nz * *(f32 *) ((u8 *) obj + 0x1C) + c;
        if (0.0f < d && d < best) {
            best = d;
            *t = other->unk0;
            *alt = (s8) ((u8 *) other)[0x2F];
            found = &D_800CC2D0[(s8) other->unk31];
        }
    }
    return found;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_1508882C.s")
#endif

// K&R: func_15088BFC calls this without the argument.
s32 func_150889D8(arg0)
    struct127 *arg0;
{
    s32 idx;
    s32 i;
    s32 n;
    struct_eu_80087640 *p;

    idx = arg0 - D_800CC2D0;
    if (D_80087640 == NULL) {
        return -1;
    }
    if (idx == 0) {
        return 0;
    }
    i = 1;
    n = D_800D27B8 + D_800D27B9;
    p = D_80087640 + 1;
    if (n >= 2) {
        for (;;) {
            if (idx == (s8)p->unk31) {
                return i;
            }
            i++;
            p++;
            if (i < n) { // fakematch: continue/break form keeps the loop rolled and the bnel shape
                continue;
            }
            break;
        }
    }
    return -1;
}

void func_15088A68(s32 arg0, s32 arg1)
{
  s32 a;
  s32 b;
  if (D_80087640 != 0) {
    a = (s8)D_80087640[arg1].unk31;
    b = (s8)D_80087640[arg1].pad28[8];
    bcopy(&D_80087640[arg0], &D_80087640[arg1], 0x84);
    D_80087640[arg1].unk31 = a;
    D_80087640[arg1].pad28[8] = b;
  }
}

#ifdef NON_MATCHING
// cpu_player_slot_claim: takes the first free computer-player slot (bit i of D_800D27B4, i < D_800D27B9), resets
// its record D_80087640[D_800D27B8 + i] (func_15088CA0), marks it used (+0x30 = 1) for the object record objp
// (+0x31 = its D_800CC2D0 index) and returns the record index; -1 when none is free or there are no records.
// arg1 is unused (the caller passes the object twice).
s32 func_15088B08(s32 objp, s32 arg1) {
    s32 bit = 1;
    s32 n = D_800D27B9;
    s32 i;

    if (D_80087640 == NULL) {
        return -1;
    }
    for (i = 0; i < n; i++, bit <<= 1) {
        if (!(D_800D27B4 & bit)) {
            D_800D27B4 |= bit;
            i += D_800D27B8;
            func_15088CA0((u8 *)&D_80087640[i]);
            *((u8 *)&D_80087640[i] + 0x30) = 1;
            D_80087640[i].unk31 = ((u8 *)objp - (u8 *)D_800CC2D0) / 0x32C;
            return i;
        }
    }
    return -1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088B08.s")
#endif

s32 func_150889D8();

#ifdef NON_MATCHING
/* The asm never sets a0 before calling func_150889D8: the object pointer is this function's own a0,
 * passed through (UNVERIFIED: check the asm callers pass a struct127 *). */
void func_15088BFC(struct127 *arg0) {
#else
void func_15088BFC(void) {
#endif
    s32 temp_v0;

    if (D_80087640 != NULL) {
#ifdef NON_MATCHING
        temp_v0 = func_150889D8(arg0);
#else
        temp_v0 = func_150889D8();
#endif
        D_80087640[temp_v0].unk31 = 0;
        D_800D27B4 &= ~(1 << (temp_v0 - D_800D27B8));
    }
}

s32 func_15088C74(void) {
    if (D_80087640 == NULL) {
        return 0;
    }
    return D_80087640->unk46 == 0xFF;
}

void func_15088CA0(u8 *arg0) {
    (*(s8 *)((u8 *)arg0 + 0x2B)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2C)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x28)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x1C)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x18)) = 0;
    (*(s32 *)((u8 *)arg0 + 0x20)) = -1;
    (*(s8 *)((u8 *)arg0 + 0x2F)) = 0;
    (*(f32 *)((u8 *)arg0 + 8)) = 0.0f;
    (*(f32 *)arg0) = 0.5f;
    (*(f32 *)((u8 *)arg0 + 4)) = 0.5f;
    (*(s16 *)((u8 *)arg0 + 0x24)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x26)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x27)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x31)) = 0;
    (*(f32 *)((u8 *)arg0 + 0xC)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x14)) = 0.0f;
    (*(s8 *)((u8 *)arg0 + 0x33)) = 2;
    (*(s8 *)((u8 *)arg0 + 0x30)) = 0;
    (*(s8 *)((u8 *)arg0 + 0x2A)) = 0x7F;
    (*(s8 *)((u8 *)arg0 + 0x49)) = 0;
    (*(f32 *)((u8 *)arg0 + 0x10)) = 1.0f;
}

#ifdef NON_MATCHING
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088D24.s")
#endif

#ifdef NON_MATCHING
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15088E84.s")
#endif

f32 func_15144BC8(f32);
f32 func_15049AD0(s32 *, s32, f32);
f32 func_15049B94(s32 *, s32, f32, s32 *);
s32 func_15088E84(struct_eu_80087640 *, f32); // 2 params: the asm never reads a2 (s87)
s32 func_150893AC(struct_eu_80087640 *, s32 *, s32 *, s32 *);

void func_150891D4(u8 *arg0)
{
  u8 *new_var;
  u8 *new_var2;
  s32 sp98[2];
  s32 sp88[4];
  s32 sp78[4];
  s32 sp68[4];
  f32 temp_f0;
  s16 temp_v0_2;
  s32 temp_v0;
  s32 var_v0;
  struct_eu_80087640 *temp_s4;
  struct_eu_800D2778 *temp_a1;
  u8 *var_v1;
  u8 temp_a0;
  u8 var_s0;
  temp_v0 = func_150889D8(arg0);
  if (temp_v0 >= 0)
  {
    temp_s4 = &D_80087640[temp_v0];
    temp_s4->unk0 = 0.5f;
    temp_s4->unk4 = 0.5f;
    temp_s4->unk8 = 0.5f;
    do
    {
      var_s0 = 0;
      var_v0 = 0;
      var_v1 = (u8 *) &D_800D2778[temp_s4->pad28[4]];
      do
      {
        temp_a0 = var_v1[9];
        var_v0 += 1;
        if (temp_a0 != 0xFF)
        {
          temp_a1 = &D_800D2778[temp_a0];
          if (temp_a1->pad8[6] == 4)
          {
            var_s0 = temp_a1->pad8[7];
          }
        }
        var_v1 += 1;
      }
      while (var_v0 != 5);
      if (var_s0)
      {
        func_15088E84(temp_s4, 1.0f);
      }
    }
    while (var_s0 != 0);
    temp_s4->unk8 = 0.0f;
    func_150893AC(temp_s4, sp88, sp78, sp68);
    *((f32 *) (((u8 *) arg0) + 0x14)) = func_15049B94(sp88, 0, temp_s4->unk8, &sp98[1]);
    new_var2 = ((u8 *) arg0) + 0x18; // fakematch: permuter temp
    *((f32 *) new_var2) = func_15049AD0(sp78, 0, temp_s4->unk8);
    *((f32 *) (((u8 *) arg0) + 0x1C)) = func_15049B94(sp68, 0, temp_s4->unk8, sp98);
    temp_f0 = func_15144BC8(((f32) (func_1505A630(*((f32 *) (((u8 *) temp_s4) + 0x10)), *((f32 *) (((u8 *) temp_s4) + 0xC)), 0) + 0x8000)) * 0.005493164f);
    new_var = (u8 *) arg0; // fakematch: permuter temp
    *((f32 *) (new_var + 0x40)) = temp_f0;
    temp_v0_2 = (s32) (temp_f0 * 182.04445f);
    temp_v0_2 = temp_v0_2 - 0x4000;
    *((s16 *) (((u8 *) arg0) + 0x7A)) = temp_v0_2;
    *((s16 *) (((u8 *) arg0) + 0x78)) = temp_v0_2;
    *((s16 *) (((u8 *) arg0) + 0x76)) = temp_v0_2;
  }
}

#ifdef NON_MATCHING
// rail_spline_points: the four spline control points of a rail record (nodes rec[0x2B..0x2E] of D_800D2778) as
// separate x / y / z float arrays: each node's position moved by rec->unk0 toward its first type-4 link (x and z only;
// the node itself when it has none); a missing node (0xFF) gives (i * 64, 0, 0). Returns 4 (the point count; the
// callers ignore it).
s32 func_150893AC(struct_eu_80087640 *rec, s32 *xs, s32 *ys, s32 *zs) {
    struct_eu_800D2778 *node;
    struct_eu_800D2778 *to;
    u8 *p;
    u8 id;
    u8 link;
    s32 i;
    s32 k;

    for (i = 0; i < 4; i++) {
        id = ((u8 *) rec)[0x2B + i];
        if (id == 0xFF) {
            ((f32 *) xs)[i] = i << 6;
            ((f32 *) ys)[i] = 0.0f;
            ((f32 *) zs)[i] = 0.0f;
            continue;
        }
        node = &D_800D2778[id];
        to = node;
        p = (u8 *) node;
        for (k = 0; k < 5; k++) {
            link = p[9 + k];
            if (link != 0xFF && ((u8 *) &D_800D2778[link])[0xE] == 4) {
                to = &D_800D2778[link];
                break;
            }
        }
        ((f32 *) xs)[i] = node->unk0 + (f32) (to->unk0 - node->unk0) * rec->unk0;
        ((f32 *) ys)[i] = node->unk2;
        ((f32 *) zs)[i] = node->unk4 + (f32) (to->unk4 - node->unk4) * rec->unk0;
    }
    return i;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150893AC.s")
#endif

#ifdef NON_MATCHING
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
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_150894F8.s")
#endif

#ifdef NON_MATCHING
extern u16 D_8009015C;
void func_1512DAD0(u8 *, s32, void *);
u8 func_150894F8(u8 node, u8 type, u8 prev, u8 band);

// rail_camera_follow: rail camera of one player record (D_80087640 + i * 0x84, player = D_800CC2D0 + rec[0x31],
// camera = player + 0x318) on the rail nodes of D_800D2778 (band 1 when D_8009015C bit 6 is set, else 0). State 2
// (rec[0x30]) sets it up: the first type-5 band-2 node starts the segment rec[0x4A] -> rec[0x4B] (rec[0x4B] = its
// band-3 link, or its non-band-3 link when D_800D27C8 is set), then the whole rail loop is walked from there and the
// segment whose end node is nearest the player (x / z) is kept; camera mode 5, state 3. Every call: the segment moves
// on when the player is nearer its end node than its start; the camera (mode 7, parameters at rec + 0x4C) looks at the
// player from that node's direction, at most 1000 units back. Camera +0x19C..+0x1A8 = 30.
void func_15089664(u8 *rec, u8 *player) {
    u8 *cam = *(u8 **) (player + 0x318);
    u8 band;
    u8 *node;
    u8 *a;
    u8 *b;
    u8 link;
    u8 start;
    u8 cur;
    u8 prev;
    u8 next;
    s32 i;
    s32 k;
    f32 best;
    f32 d;
    f32 dB;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;

    if (cam == NULL) {
        return;
    }
    band = (D_8009015C & 0x40) ? 1 : 0;
    if ((s8) rec[0x30] == 2) {
        for (i = 0; i < D_80087630; i++) {
            node = (u8 *) &D_800D2778[i];
            if (node[0xE] != 5 || node[0xF] != 2) {
                continue;
            }
            rec[0x4A] = i;
            rec[0x4B] = i;
            for (k = 0; k < 5; k++) {
                link = node[9 + k];
                if (link == 0xFF) {
                    continue;
                }
                if (D_800D27C8 == 0) {
                    if (((u8 *) &D_800D2778[link])[0xF] == 3) {
                        rec[0x4B] = link;
                    }
                } else if (((u8 *) &D_800D2778[link])[0xF] != 3) {
                    rec[0x4B] = link;
                }
            }
            break;
        }
        start = rec[0x4B];
        cur = start;
        prev = rec[0x4A];
        best = 1.0e9f;
        do {
            node = (u8 *) &D_800D2778[cur];
            next = func_150894F8(cur, 0xFF, prev, band);
            dx = *(f32 *) (player + 0x14) - *(s16 *) node;
            dz = *(f32 *) (player + 0x1C) - *(s16 *) (node + 4);
            prev = cur;
            cur = next;
            d = dx * dx + dz * dz;
            if (d < best) {
                best = d;
                rec[0x4A] = prev;
                rec[0x4B] = next;
            }
        } while (cur != start);
        func_1512DAD0(*(u8 **) (player + 0x318), 5, NULL);
        rec[0x30] = 3;
    }

    b = (u8 *) &D_800D2778[rec[0x4B]];
    dx = *(f32 *) (player + 0x14) - *(s16 *) b;
    dz = *(f32 *) (player + 0x1C) - *(s16 *) (b + 4);
    dB = dx * dx + dz * dz;
    a = (u8 *) &D_800D2778[rec[0x4A]];
    node = a;
    dx = *(f32 *) (player + 0x14) - *(s16 *) a;
    dz = *(f32 *) (player + 0x1C) - *(s16 *) (a + 4);
    d = dx * dx + dz * dz;
    if (dB < d) {
        prev = rec[0x4A];
        rec[0x4A] = rec[0x4B];
        rec[0x4B] = func_150894F8(rec[0x4A], 0xFF, prev, band);
        node = b;
        dx = *(f32 *) (player + 0x14) - *(s16 *) b;
        dz = *(f32 *) (player + 0x1C) - *(s16 *) (b + 4);
        d = dB;
    }
    dy = *(f32 *) (player + 0x18) - *(s16 *) (node + 2);
    dist = sqrtf(dy * dy + d);
    dx /= dist;
    dy /= dist;
    dz /= dist;
    if (1000.0f < dist) {
        dist = 1000.0f;
    }
    *(s32 *) (rec + 0x4C) = 0;
    *(f32 *) (rec + 0x6C) = *(f32 *) (player + 0x14);
    *(f32 *) (rec + 0x70) = *(f32 *) (player + 0x18);
    *(f32 *) (rec + 0x74) = *(f32 *) (player + 0x1C);
    *(f32 *) (rec + 0x60) = *(f32 *) (player + 0x14) - dx * dist;
    *(f32 *) (rec + 0x64) = *(f32 *) (player + 0x18) - dy * dist;
    *(f32 *) (rec + 0x68) = *(f32 *) (player + 0x1C) - dz * dist;
    *(s32 *) (rec + 0x50) = 0;
    *(f32 *) (rec + 0x7C) = 30.0f;
    *(f32 *) (rec + 0x80) = 30.0f;
    *(f32 *) (rec + 0x78) = 0.0f;
    func_1512DAD0(*(u8 **) (player + 0x318), 7, rec + 0x4C);
    *(f32 *) (cam + 0x19C) = 30.0f;
    *(f32 *) (cam + 0x1A4) = 30.0f;
    *(f32 *) (cam + 0x1A0) = 30.0f;
    *(f32 *) (cam + 0x1A8) = 30.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15089664.s")
#endif

#ifdef NON_MATCHING
void func_1512DAD0(u8 *, s32, void *);
u8 func_150894F8(u8 node, u8 type, u8 prev, u8 band);

// rail_camera_spline: spline camera of one player record (D_80087640 + i * 0x84, camera = player + 0x318).
// `release` != 0: camera mode 10 (rec + 0x4C params: +0x58 = 999, +0x5C = 120), then mode 6 with the camera's +0x23D,
// rec[0x49] = 0. Else, on the first call (rec[0x49] == 0): the first type-6 node of band D_800D27C8 + 1 and the next
// three type-6 nodes after it fill rec[0x44..0x47], the player position is kept at rec + 0x38, t (rec + 0x34) = 0,
// camera mode 5, rec[0x49] = 1. Each call t += 0.017 * D_800BE9E4; past 1 the four nodes shift on by one (t stays at
// 1 at the rail end). The eye points are the nodes rec[0x44 + k] (from rec + 0x38 behind the player's yaw +0x40 for
// the first missing one, then extrapolated), the targets their type-4 links; func_15049AD0 interpolates both at t
// into rec + 0x60 / + 0x6C and camera mode 7 takes rec + 0x4C.
void func_15089B68(u8 *rec, u8 *player, s32 release) {
    u8 *cam = *(u8 **) (player + 0x318);
    f32 pt[6][4]; // eye x / y / z, target x / y / z for the four nodes
    f32 t;
    f32 ang;
    u8 want;
    u8 old;
    u8 node;
    s32 had;
    s32 i;
    s32 k;
    s32 j;

    if (cam == NULL) {
        return;
    }
    if (release) {
        *(s32 *) (rec + 0x5C) = 120;
        *(f32 *) (rec + 0x58) = 999.0f;
        func_1512DAD0(*(u8 **) (player + 0x318), 10, rec + 0x4C);
        func_1512DAD0(*(u8 **) (player + 0x318), 6, (void *) (s32) cam[0x23D]);
        rec[0x49] = 0;
        return;
    }
    if ((s8) rec[0x49] == 0) {
        want = D_800D27C8 + 1;
        for (i = 0; i < D_80087630; i++) {
            if (((u8 *) &D_800D2778[i])[0xE] == 6 && ((u8 *) &D_800D2778[i])[0xF] == want) {
                rec[0x44] = i;
                break;
            }
        }
        rec[0x45] = func_150894F8(rec[0x44], 6, 0xFF, 0);
        rec[0x46] = func_150894F8(rec[0x45], 6, rec[0x44], 0);
        rec[0x47] = func_150894F8(rec[0x46], 6, rec[0x45], 0);
        *(f32 *) (rec + 0x38) = *(f32 *) (player + 0x14);
        *(f32 *) (rec + 0x3C) = *(f32 *) (player + 0x18);
        *(f32 *) (rec + 0x34) = 0.0f;
        *(f32 *) (rec + 0x40) = *(f32 *) (player + 0x1C);
        func_1512DAD0(*(u8 **) (player + 0x318), 5, (void *) (s32) cam[0x23D]);
        rec[0x49] = 1;
    }
    *(f32 *) (rec + 0x34) += 0.017f * (f32) D_800BE9E4;
    t = *(f32 *) (rec + 0x34);
    if (1.0f <= t) {
        node = rec[0x46];
        if (node == 0xFF) {
            *(f32 *) (rec + 0x34) = 1.0f;
        } else {
            old = rec[0x45];
            rec[0x45] = node;
            *(f32 *) (rec + 0x34) = t - 1.0f;
            rec[0x46] = rec[0x47];
            rec[0x44] = old;
            rec[0x47] = func_150894F8(rec[0x46], 6, node, 0);
        }
    }

    had = 0;
    for (k = 0; k < 4; k++) {
        if (rec[0x44 + k] != 0xFF) {
            had = 1;
            func_1508712C(rec[0x44 + k], &pt[0][k], &pt[1][k], &pt[2][k]);
            func_1508712C(func_150894F8(rec[0x44 + k], 4, 0xFF, 0), &pt[3][k], &pt[4][k], &pt[5][k]);
        } else if (had == 1) {
            had = 0;
            ang = *(f32 *) (player + 0x40) * 0.01745;
            pt[0][k] = *(f32 *) (rec + 0x38) - sinf(ang) * 500.0f;
            pt[1][k] = *(f32 *) (rec + 0x3C) + 180.0f;
            pt[2][k] = *(f32 *) (rec + 0x40) - cosf(ang) * 500.0f;
            pt[3][k] = *(f32 *) (rec + 0x38);
            pt[4][k] = *(f32 *) (rec + 0x3C) + 120.0f;
            pt[5][k] = *(f32 *) (rec + 0x40);
        } else if (k >= 2) {
            // the asm also extrapolates at k = 0 / 1 (rec[0x44] == 0xFF) from stack garbage; left 0 here
            for (j = 0; j < 6; j++) {
                pt[j][k] = (pt[j][k - 1] - pt[j][k - 2]) + pt[j][k - 1];
            }
        } else {
            for (j = 0; j < 6; j++) {
                pt[j][k] = 0.0f;
            }
        }
    }
    t = *(f32 *) (rec + 0x34);
    *(f32 *) (rec + 0x60) = func_15049AD0((s32 *) pt[0], 0, t);
    *(f32 *) (rec + 0x64) = func_15049AD0((s32 *) pt[1], 0, t);
    *(f32 *) (rec + 0x68) = func_15049AD0((s32 *) pt[2], 0, t);
    *(f32 *) (rec + 0x6C) = func_15049AD0((s32 *) pt[3], 0, t);
    *(f32 *) (rec + 0x70) = func_15049AD0((s32 *) pt[4], 0, t);
    *(f32 *) (rec + 0x74) = func_15049AD0((s32 *) pt[5], 0, t);
    *(s32 *) (rec + 0x4C) = 0;
    *(s32 *) (rec + 0x50) = 0;
    *(f32 *) (rec + 0x7C) = 30.0f;
    *(f32 *) (rec + 0x80) = 30.0f;
    *(f32 *) (rec + 0x78) = 0.0f;
    func_1512DAD0(*(u8 **) (player + 0x318), 7, rec + 0x4C);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_B37F0/func_15089B68.s")
#endif
