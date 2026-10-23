extern f32 D_80096DC0;
/* Look target of the actor of player `player` in sequence slot `slot` (D_800C35EA[slot] == 1: a cutscene runs):
 * the first live actor (D_800C39E8 id != 0) whose record (D_800C3A10, kind 2) names the player's room.
 * Its look step (D_800C3D80 +2) gives a point next to entity r[5] (D_800C3958 0x44-byte records) raised by r[6]:
 * written to pos, returns 0. Without one, look step +1: entity 0 = fixed angles (record i +0x24 / +0x28 / +0x2C
 * to outB / outA / outC, returns 1), else the camera point (D_800DBFF0 +0x2F8) raised by r[6]. No step: pos =
 * D_80096DC0 x3. */
s32 func_15021E60(f32 *outA, f32 *outB, f32 *outC, f32 *pos, s32 player, s32 slot) {
    u16 *ids;
    u8 *e;
    u8 *step;
    u8 *r;
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
        step = (u8 *)D_800C3D80[slot][i];
        if (step[2] != 0xFF) {
            r = (u8 *)D_800C3AA8[slot][i] + step[2] * 8;
            q = (f32 *)(((u8 **)&D_800C3958)[slot] + (s8)r[5] * 0x44);
            pos[0] = q[0];
            pos[1] = q[1] + (f32)*(s16 *)(r + 6);
            pos[2] = q[2];
            return 0;
        }
        if (step[1] != 0xFF) {
            r = (u8 *)D_800C3AA8[slot][i] + step[1] * 8;
            if ((s8)r[5] == 0) {
                q = (f32 *)(((u8 **)&D_800C3958)[slot] + i * 0x44);
                *outA = q[10];
                *outB = q[9];
                *outC = q[11];
                return 1;
            }
            pos[0] = *(f32 *)((u8 *)D_800DBFF0 + 0x2F8);
            pos[1] = *(f32 *)((u8 *)D_800DBFF0 + 0x2FC) + (f32)*(s16 *)(r + 6);
            pos[2] = *(f32 *)((u8 *)D_800DBFF0 + 0x300);
            return 0;
        }
        pos[0] = D_80096DC0;
        pos[1] = D_80096DC0;
        pos[2] = D_80096DC0;
        return 0;
    }
    return 0;
}
