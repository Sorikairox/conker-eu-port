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
