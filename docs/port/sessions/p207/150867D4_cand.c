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
