extern void (*D_8008CD68[])(u8 *);  /* node behaviours, by s8 node +0x2F */
/* D_8008CDC0 (variables.h: void (*[])(void)): node end handlers void (u8 *), by s8 node +0x48 */

// sprite_node_update: P210: per-node update of render layers 5 / 59 / 66 (field 0 of their D_8008B848 records):
/* counts down the lifetime s16 +0x38 by the frame time D_800BE9E4 (0x7FFF = forever) and fades the alpha +0x3F
 * by s8 +0x3A per frame; runs the behaviour D_8008CD68[+0x2F]; while alive moves the 8.8 fixed-point position
 * (s16 +0x20 / +0x22 / +0x24 with fraction bytes +0x2C / +0x2E / +0x2D) by the velocity +0x26 / +0x30 / +0x28 (+0x30
 * accelerated by +0x32), and advances the animation frame +0x1C by speed +0x1E over the texture's (+0x10) byte 4
 * frames: past the end flag 0x20 ends the node, else 0x80 is set and flag 2 bounces (speed negated) or the frame
 * wraps; below 0 flag 0x40 ends it, flag 2 bounces, else it wraps. An ended node runs D_8008CDC0[+0x48] and is
 * freed (func_1516972C). */
void func_15167E0C(u8 *n) {
    s32 done = FALSE;
    s16 t = *(s16 *)(n + 0x38);
    s32 fade;
    s32 v;
    s32 speed;
    s32 last;
    s32 frame;
    u16 flags;

    if (t != 0x7FFF) {
        *(s16 *)(n + 0x38) = t - D_800BE9E4;
        if (*(s16 *)(n + 0x38) < 0) {
            *(s16 *)(n + 0x38) = 0;
            done = TRUE;
        }
    }
    fade = (s8)n[0x3A];
    if (fade > 0) {
        if (fade < n[0x3F]) {
            n[0x3F] -= fade;
        } else {
            *(s16 *)(n + 0x38) = 0;
            done = TRUE;
        }
    }
    if ((s8)n[0x2F] != -1 && D_8008CD68[(s8)n[0x2F]] != NULL) {
        D_8008CD68[(s8)n[0x2F]](n);
    }

    if (*(s16 *)(n + 0x38) == 0) {
        done = TRUE;
    } else {
        *(s16 *)(n + 0x30) += *(s16 *)(n + 0x32);
        speed = *(s16 *)(n + 0x1E);
        v = ((*(s16 *)(n + 0x22) << 8) | n[0x2E]) + *(s16 *)(n + 0x30) * D_800BE9E4;
        *(s16 *)(n + 0x22) = v >> 8;
        n[0x2E] = v;
        v = ((*(s16 *)(n + 0x20) << 8) | n[0x2C]) + *(s16 *)(n + 0x26) * D_800BE9E4;
        *(s16 *)(n + 0x20) = v >> 8;
        n[0x2C] = v;
        v = ((*(s16 *)(n + 0x24) << 8) | n[0x2D]) + *(s16 *)(n + 0x28) * D_800BE9E4;
        *(s16 *)(n + 0x24) = v >> 8;
        n[0x2D] = v;
        if (speed != 0) {
            last = ((*(u8 **)(n + 0x10))[4] << 8) - 1;
            *(s16 *)(n + 0x1C) += speed * D_800BE9E4;
            frame = *(s16 *)(n + 0x1C);
            if (last < frame) {
                flags = *(u16 *)(n + 0x44);
                if (flags & 0x20) {
                    *(s16 *)(n + 0x38) = 0;
                    done = TRUE;
                } else {
                    *(u16 *)(n + 0x44) = flags | 0x80;
                    if (flags & 2) {
                        *(s16 *)(n + 0x1C) = last - *(s16 *)(n + 0x1C) % last;
                        *(s16 *)(n + 0x1E) = -*(s16 *)(n + 0x1E);
                    } else {
                        do {
                            *(s16 *)(n + 0x1C) -= last;
                        } while (last < *(s16 *)(n + 0x1C));
                    }
                }
            } else if (frame < 0) {
                flags = *(u16 *)(n + 0x44);
                if (flags & 0x40) {
                    *(s16 *)(n + 0x38) = 0;
                    done = TRUE;
                } else if (flags & 2) {
                    *(s16 *)(n + 0x1C) = -frame % last;
                    *(s16 *)(n + 0x1E) = -speed;
                } else {
                    do {
                        *(s16 *)(n + 0x1C) += last;
                    } while (*(s16 *)(n + 0x1C) < 0);
                }
            }
        }
    }
    if (done) {
        if ((s8)n[0x48] != -1) {
            ((void (*)(u8 *))D_8008CDC0[(s8)n[0x48]])(n);
        }
        func_1516972C((struct102 *)n);
    }
}
