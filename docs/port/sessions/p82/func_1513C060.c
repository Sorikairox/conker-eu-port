extern s32 (*D_8008A010[])(u8 *);
extern s32 (*D_8008A048[])(u8 *);
/* Per-frame update of a sprite effect (struct210): +0x10 bit 0 active; +0x18 flags; +0x1C life (s16, counts down
 * by D_800BE9E4 when flags & 1); +0x80 / +0x81 update / end handler index (D_8008A010 / D_8008A048, 0 = none);
 * +0x3A fade start, +0x3C fade rate: alpha +0x28 (flags & 0x8000) or +0x2D (flags & 0x10000) follows life * rate;
 * +0x20 frame position (16.16) advanced by speed +0x24, wrapped at the frame count of texture +0x1E
 * (D_80090F10 entry byte 4): flags 2 / 8 end at the top / bottom, 0x40 / 0x80 clamp, 4 ping-pong, else wrap.
 * When the effect ends, the end handler may veto the removal (func_1516972C). */
void func_1513C060(u8 *p) {
    s8 done;
    s32 flags;
    s32 life;
    s32 a;
    s32 speed;
    s32 pos;
    s32 top;

    if (!(*(s32 *)(p + 0x10) & 1)) {
        return;
    }
    done = 0;
    if (*(s32 *)(p + 0x18) & 1) {
        *(s16 *)(p + 0x1C) -= D_800BE9E4;
        if (*(s16 *)(p + 0x1C) < 0) {
            done = 1;
        }
    }
    if ((p[0x80] != 0) && (D_8008A010[p[0x80]](p) == 0)) {
        done = 1;
    }
    flags = *(s32 *)(p + 0x18);
    if ((flags & 0x8000) && !done) {
        life = *(s16 *)(p + 0x1C);
        if (life < *(s16 *)(p + 0x3A)) {
            a = life * *(s16 *)(p + 0x3C);
            if (a < p[0x28]) {
                p[0x28] = a;
            }
        }
    }
    flags = *(s32 *)(p + 0x18);
    if ((flags & 0x10000) && !done) {
        life = *(s16 *)(p + 0x1C);
        if (life < *(s16 *)(p + 0x3A)) {
            a = life * *(s16 *)(p + 0x3C);
            if (a < p[0x28]) {
                p[0x2D] = a;
            }
        }
    }
    if (!done && ((speed = *(s32 *)(p + 0x24)) != 0)) {
        pos = *(s32 *)(p + 0x20) + speed * D_800BE9E4;
        *(s32 *)(p + 0x20) = pos;
        top = (D_80090F14[p[0x1E]][0] << 16) - 1;
        if (top < pos) {
            flags = *(s32 *)(p + 0x18);
            if (flags & 2) {
                done = 1;
            } else if (flags & 0x40) {
                *(s32 *)(p + 0x24) = 0;
                *(s32 *)(p + 0x20) = top;
            } else if (flags & 4) {
                *(s32 *)(p + 0x20) = top - pos % top;
                *(s32 *)(p + 0x24) = -speed;
            } else {
                do {
                    pos -= top;
                    *(s32 *)(p + 0x20) = pos;
                } while (top < pos);
            }
        } else if (pos < 0) {
            flags = *(s32 *)(p + 0x18);
            if (flags & 8) {
                done = 1;
            } else if (flags & 0x80) {
                *(s32 *)(p + 0x24) = 0;
                *(s32 *)(p + 0x20) = 0;
            } else if (flags & 4) {
                *(s32 *)(p + 0x20) = -pos % top;
                *(s32 *)(p + 0x24) = -speed;
            } else {
                do {
                    pos += top;
                    *(s32 *)(p + 0x20) = pos;
                } while (pos < 0);
            }
        }
    }
    if (done) {
        if ((p[0x81] == 0) || (D_8008A048[p[0x81]](p) != 0)) {
            func_1516972C((struct102 *)p);
        }
    }
}
