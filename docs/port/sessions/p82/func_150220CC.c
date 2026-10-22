extern f32 D_80096DC4;
/* Look limits of the actor of player `player` in sequence slot `slot` (same search as func_15021E60): both
 * pairs are cleared, then entity record i +0x3C (into b[0], b[1]) and +0x40 (into a[0], a[1]) unless they hold the
 * "unset" value D_80096DC4. Returns 1 when the actor was found. */
s32 func_150220CC(f32 *a, f32 *b, s32 player, s32 slot) {
    u16 *ids;
    u8 *e;
    f32 *q;
    s32 n;
    s32 i;

    if ((&D_800C35EA)[slot] != 1) {
        return 0;
    }
    n = D_800C3A5A[slot];
    ids = D_800C39E8[slot];
    for (i = 0; i < n; i++, ids++) {
        if (*ids == 0) {
            continue;
        }
        e = D_800C3A10[slot] + i * 8;
        if (*(u16 *)e != 2) {
            continue;
        }
        if (*((u8 *)D_800CC2D0 + player * 0x32C + 0x3B) != e[2]) {
            continue;
        }
        a[1] = 0.0f;
        b[1] = 0.0f;
        a[0] = 0.0f;
        b[0] = 0.0f;
        q = (f32 *)(((u8 **)&D_800C3958)[slot] + i * 0x44);
        if (q[15] != D_80096DC4) {
            b[0] = q[15];
            b[1] = b[0];
        }
        if (q[16] != D_80096DC4) {
            a[0] = q[16];
            a[1] = a[0];
        }
        return 1;
    }
    return 0;
}
