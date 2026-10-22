/* Places the scene of cutscene slot `slot` in the level: the first actor whose entry (D_800C3A10[slot] + i * 8)
 * is an anchor moves every actor's path keys (s16 x, y, z at D_eu_800C3C88[slot][j] + k * 8):
 *   type 6: by the offset from the anchor's first key to object func_15083E90(b) (a == 0) or entity
 *     func_151149AC(b) (a == 1); other a: nothing.
 *   type 7: rotated about the anchor's first key by D_800C39B4 - its channel-7 key angle (stored in
 *     D_800C39C4) and moved onto D_800C39AC; the channel-7 keys of the other camera tracks turn by the same
 *     angle unless their sound record +0x20 is 7.
 * func_15022238 gets the anchor (unless D_800C3663). */
void func_15022C4C(s32 slot) {
    TrackKey *keys;
    u8 *ent;
    u8 *o;
    s16 *p;
    s16 *q;
    s32 i;
    s32 j;
    s32 k;
    s32 cnt;
    s32 keep;
    f32 ang;
    f32 rot;
    f32 r;
    f32 tx;
    f32 ty;
    f32 tz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 px;
    f32 py;
    f32 pz;
    f32 c;
    f32 s;
    f32 ox;
    f32 oz;
    f32 nx;
    f32 nz;

    for (i = 0; i < D_800C3A5A[slot]; i++) {
        if (D_800C39E8[slot][i] == 0) {
            continue;
        }
        ent = D_800C3A10[slot] + i * 8;
        if (*(u16 *)ent == 6) {
            if (D_800C3663 == 0) {
                p = (s16 *)D_eu_800C3C88[slot][i];
                func_15022238(p[0], p[1], p[2], 0.0f);
                ent = D_800C3A10[slot] + i * 8;
            }
            if (ent[2] == 0) {
                o = (u8 *)func_15083E90(ent[3]);
                if (o == NULL) {
                    return;
                }
                tx = *(f32 *)(o + 0x14);
                ty = *(f32 *)(o + 0x18);
                tz = *(f32 *)(o + 0x1C);
            } else if (ent[2] == 1) {
                o = func_151149AC(ent[3]);
                if (o == NULL) {
                    return;
                }
                tx = *(s16 *)(o + 0x10);
                ty = *(s16 *)(o + 0x12);
                tz = *(s16 *)(o + 0x14);
            } else {
                return;
            }
            p = (s16 *)D_eu_800C3C88[slot][i];
            dx = tx - (f32)p[0];
            dy = ty - (f32)p[1];
            dz = tz - (f32)p[2];
            for (j = 0; j < D_800C3A5A[slot]; j++) {
                for (k = 0; k < D_800C39E8[slot][j]; k++) {
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[0] = (s32)((f32)q[0] + dx);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[1] = (s32)((f32)q[1] + dy);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[2] = (s32)((f32)q[2] + dz);
                }
            }
            return;
        }
        if (*(u16 *)ent == 7) {
            cnt = D_800C39F0[slot][i];
            ang = 0.0f;
            keys = (TrackKey *)D_800C3B98[slot][i];
            for (k = 0; k < cnt; k++) {
                if (keys[k].channel == 7) {
                    ang = keys[k].value;
                    break;
                }
            }
            if (D_800C3663 == 0) {
                p = (s16 *)D_eu_800C3C88[slot][i];
                func_15022238(p[0], p[1], p[2], ang);
            }
            rot = D_800C39B4 - ang;
            D_800C39C4 = rot;
            p = (s16 *)D_eu_800C3C88[slot][i];
            r = rot * 0.017453292f;
            px = p[0];
            py = p[1];
            pz = p[2];
            c = cosf(r);
            s = sinf(r);
            dy = (f32)D_800C39AC[1] - py;
            for (j = 0; j < D_800C3A5A[slot]; j++) {
                keep = FALSE;
                for (k = 0; k < D_800C39E8[slot][j]; k++) {
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    ox = (f32)q[0] - px;
                    oz = (f32)q[2] - pz;
                    nx = ox * c + oz * s;
                    nz = -ox * s + oz * c;
                    q[0] = (s32)((f32)D_800C39AC[0] + nx);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[1] = (s32)((f32)q[1] + dy);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[2] = (s32)((f32)D_800C39AC[2] + nz);
                }
                if (D_800C39F8[slot][j] != 0 && *(s8 *)((u8 *)D_800C3AA8[slot][j] + 0x20) == 7) {
                    keep = TRUE;
                }
                if (!keep) {
                    for (k = 0; k < D_800C39F0[slot][j]; k++) {
                        keys = (TrackKey *)D_800C3B98[slot][j];
                        if (keys[k].channel == 7) {
                            keys[k].value += rot;
                        }
                    }
                }
            }
            return;
        }
    }
}
