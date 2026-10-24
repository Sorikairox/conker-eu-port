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
