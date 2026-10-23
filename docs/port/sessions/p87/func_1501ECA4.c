/* Camera track pass of cutscene slot `slot` (P72 / P84: the scene loader reads what this writes). Every actor i
 * has a 0x44-byte camera record cam = D_800C3958[slot] + i * 17 floats (position 0..2 from its s16 actor record,
 * then per-type defaults, entry type = u16 at D_800C3A10[slot] + i * 8). Its keys D_800C3B98[slot][i] (count
 * D_800C39F0[slot][i]) are 8-byte TrackKey records on 15 channels; each channel is evaluated at the current
 * frame (script position * 60 / 50, or D_800C3A68 once the slot has ended): before the first key -> no value,
 * at / after the last key -> last value, else spline (mode 0, func_15049AD0 over the 4 surrounding keys) or
 * linear between the two keys around the frame. Channel 10 (roll) goes to func_1501FF10 when the actor has a
 * look step (D_800C3D80 byte 0 != 0xFF), else channel 7 sets cam[4]; the other channels overwrite cam[3..16]
 * where they have a value; func_1501FD34 then places cam[0..2]. D_800C3638 = 0 while running, 1 after. */
void func_1501ECA4(s32 slot) {
    TrackKey *keys;
    TrackKey *key;
    f32 *cam;
    u8 *n;
    s32 frame;
    s32 i;
    s32 ch;
    s32 k;
    s32 seen;
    s32 at;
    s32 want;
    s32 flags;
    s32 ia;
    s32 ib;
    f32 t;
    s16 *pos;
    s32 nextFrame[15];
    s32 prevFrame[15];
    s32 nextIdx[15];
    s32 mode[15];
    s32 count[15];
    f32 first[15];
    f32 last[15];
    f32 out[15];
    f32 pts[4];

    if ((&D_800C35EA)[slot] != 1) {
        return;
    }
    if ((&D_800C39D0)[slot] < (&D_eu_800C3A60)[slot]) {
        frame = (&D_800C39D0)[slot] * 60 / 50;
    } else {
        frame = D_800C3A68;
    }
    D_800C3638 = 0;
    n = &D_800C3A5A[slot];
    ib = 0;
    for (i = 0; i < *n; i++) {
        cam = (f32 *)(&D_800C3958)[slot] + i * 17;
        if (D_800C39E8[slot][i] != 0) {
            pos = (s16 *)D_eu_800C3C88[slot][i];
            cam[0] = pos[0];
            cam[1] = pos[1];
            cam[2] = pos[2];
        } else {
            cam[0] = 0.0f;
            cam[1] = 0.0f;
            cam[2] = 0.0f;
        }
        if (*(u16 *)(D_800C3A10[slot] + i * 8) == 4) {
            cam[3] = 64.0f;
            cam[4] = 0.0f;
            cam[5] = 20.0f;
            cam[6] = 255.0f;
            cam[7] = 62.5f;
            cam[8] = 50.0f;
            cam[9] = 0.0f;
            cam[10] = 0.0f;
            cam[11] = 0.0f;
            cam[13] = 0.0f;
        } else {
            cam[3] = 0.0f;
            cam[4] = D_800C39C4;
            cam[5] = 0.0f;
            cam[6] = TRACK_NONE_F;
            cam[7] = TRACK_NONE_F;
            cam[8] = TRACK_NONE_F;
            cam[9] = 0.0f;
            cam[10] = 0.0f;
            cam[11] = 0.0f;
            cam[15] = TRACK_NONE_F;
            cam[16] = TRACK_NONE_F;
            cam[12] = TRACK_NONE_F;
        }
        cam[14] = 0.0f;
        switch (*(u16 *)(D_800C3A10[slot] + i * 8)) {
            case 1:
                cam[13] = TRACK_NONE_F;
                break;
            case 2:
                cam[13] = 255.0f;
                break;
            case 5:
                cam[6] = 32.0f;
                cam[7] = 32.0f;
                cam[13] = 1.0f;
                break;
            case 3:
                cam[6] = TRACK_NONE_F;
                cam[7] = TRACK_NONE_F;
                cam[8] = TRACK_NONE_F;
                cam[13] = 255.0f;
                break;
        }

        keys = (TrackKey *)D_800C3B98[slot][i];
        if (keys == NULL) {
            continue;
        }
        for (ch = 0; ch < 15; ch++) {
            nextFrame[ch] = TRACK_NONE;
            prevFrame[ch] = TRACK_NONE;
            nextIdx[ch] = TRACK_NONE;
            mode[ch] = 1;
            count[ch] = 0;
            first[ch] = TRACK_NONE_F;
            last[ch] = TRACK_NONE_F;
        }
        /* per channel: the last key before the frame (its mode and frame), the first key at / after it */
        for (k = 0; k < D_800C39F0[slot][i]; k++) {
            key = &keys[k];
            ch = key->channel;
            if (nextIdx[ch] == TRACK_NONE) {
                if (key->frame < frame) {
                    mode[ch] = key->mode;
                    prevFrame[ch] = key->frame;
                } else {
                    nextIdx[ch] = count[ch];
                    nextFrame[ch] = key->frame;
                }
            }
            last[ch] = key->value;
            if (first[ch] == TRACK_NONE_F) {
                first[ch] = key->value;
            }
            count[ch]++;
        }
        for (ch = 0; ch < 15; ch++) {
            out[ch] = TRACK_NONE_F;
            if (prevFrame[ch] == TRACK_NONE) {
                if (nextFrame[ch] != TRACK_NONE) {
                    out[ch] = first[ch];
                }
            } else if (nextFrame[ch] == TRACK_NONE) {
                out[ch] = last[ch];
            } else {
                t = (f32)(frame - prevFrame[ch]) / (f32)(nextFrame[ch] - prevFrame[ch]);
                if (mode[ch] == 0) {
                    /* spline over keys nextIdx-2 .. nextIdx+1 of the channel, ends repeated */
                    if (nextIdx[ch] - 2 >= 0) {
                        flags = 7;
                        seen = nextIdx[ch] - 2;
                        want = 3;
                        at = 0;
                    } else {
                        flags = 6;
                        seen = nextIdx[ch] - 1;
                        want = 2;
                        at = 1;
                    }
                    if (nextIdx[ch] + 1 < count[ch]) {
                        flags |= 8;
                        want++;
                    }
                    /* ia counts the channel's keys; from index `seen` on they are collected */
                    ia = 0;
                    for (k = 0; k < D_800C39F0[slot][i] && want != 0; k++) {
                        if (keys[k].channel == ch) {
                            if (ia == seen) {
                                pts[at++] = keys[k].value;
                                want--;
                            } else {
                                ia++;
                            }
                        }
                    }
                    if (!(flags & 1)) {
                        pts[0] = pts[1];
                    }
                    if (!(flags & 8)) {
                        pts[3] = pts[2];
                    }
                    out[ch] = func_15049AD0((s32 *)pts, 0, t);
                } else {
                    /* linear between the channel's keys nextIdx-1 (ia) and nextIdx (ib) */
                    seen = 0;
                    ia = -1;
                    for (k = 0; k < D_800C39F0[slot][i]; k++) {
                        if (keys[k].channel == ch) {
                            if (ia != -1) {
                                ib = k;
                                break;
                            }
                            if (seen + 1 == nextIdx[ch]) {
                                ia = k;
                            } else {
                                seen++;
                            }
                        }
                    }
                    out[ch] = (keys[ib].value - keys[ia].value) * t + keys[ia].value;
                }
            }
        }
        if (out[10] == TRACK_NONE_F) {
            out[10] = 0.0f;
        }
        if (*(u8 *)D_800C3D80[slot][i] != 0xFF) {
            func_1501FF10(i, out[10], &cam[4], slot);
        } else if (out[7] != TRACK_NONE_F) {
            cam[4] = out[7];
        }
        if (out[8] != TRACK_NONE_F) {
            cam[3] = out[8];
        }
        if (out[6] != TRACK_NONE_F) {
            cam[5] = out[6];
        }
        if (out[5] != TRACK_NONE_F) {
            cam[6] = out[5];
        }
        if (out[4] != TRACK_NONE_F) {
            cam[7] = out[4];
        }
        if (out[3] != TRACK_NONE_F) {
            cam[8] = out[3];
        }
        if (out[1] != TRACK_NONE_F) {
            cam[9] = out[1];
        }
        if (out[2] != TRACK_NONE_F) {
            cam[10] = out[2];
        }
        if (out[0] != TRACK_NONE_F) {
            cam[11] = out[0];
        }
        if (out[14] != TRACK_NONE_F) {
            cam[12] = out[14];
        }
        if (out[9] != TRACK_NONE_F) {
            cam[13] = out[9];
        }
        if (out[11] != TRACK_NONE_F) {
            cam[14] = out[11];
        }
        if (out[13] != TRACK_NONE_F) {
            cam[15] = out[13];
        }
        if (out[12] != TRACK_NONE_F) {
            cam[16] = out[12];
        }
        func_1501FD34(i, out[10], &cam[0], &cam[1], &cam[2], slot);
    }
    D_800C3638 = 1;
}
