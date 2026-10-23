extern s32 (*D_8008A058[])(u8 *);
extern s32 (*D_8008A100[])(u8 *);
extern s32 (*D_8008A1B0[])(u8 *);
// effect3d_update: per-frame update of a 3D sprite effect (sibling of func_1513C060): +0x10 bit 0 active;
// +0x58 flags; +0x1C life (s16, counts down by D_800BE9E4 when flags & 1); +0x70 / +0x71 update handlers
// (D_8008A058 / D_8008A100, 0 = none; returning 0 ends the effect); while alive, flags 0x08000000 / 0x10000000 fade
// alpha +0x5C / +0x2B to life * rate +0x6E below life +0x6C (only ever lowering it, compared against +0x5C);
// +0x20 frame position (16.16) advanced by speed +0x24 and wrapped at the frame count of texture +0x18
// (D_80090F14): flags 0x800 / 0x1000 end at the top / bottom, 0x400 ping-pong, else wrap. When it ends, the end
// handler +0x72 (D_8008A1B0, 2 slots) may veto the removal (nonzero), else func_1516972C frees it.
void func_1513CFE4(u8 *fx) {
    s8 done;
    s32 flags;
    s32 life;
    s32 a;
    s32 speed;
    s32 pos;
    s32 top;

    if (!(*(s32 *)(fx + 0x10) & 1)) {
        return;
    }
    done = 0;
    if (*(s32 *)(fx + 0x58) & 1) {
        *(s16 *)(fx + 0x1C) -= D_800BE9E4;
        if (*(s16 *)(fx + 0x1C) < 0) {
            done = 1;
        }
    }
    if ((fx[0x70] != 0) && (D_8008A058[fx[0x70]](fx) == 0)) {
        done = 1;
    }
    if ((fx[0x71] != 0) && (D_8008A100[fx[0x71]](fx) == 0)) {
        done = 1;
    }
    flags = *(s32 *)(fx + 0x58);
    if ((flags & 0x08000000) && !done) {
        life = *(s16 *)(fx + 0x1C);
        if (life < *(s16 *)(fx + 0x6C)) {
            a = life * *(s16 *)(fx + 0x6E);
            if (a < fx[0x5C]) {
                fx[0x5C] = a;
            }
        }
    }
    flags = *(s32 *)(fx + 0x58);
    if ((flags & 0x10000000) && !done) {
        life = *(s16 *)(fx + 0x1C);
        if (life < *(s16 *)(fx + 0x6C)) {
            a = life * *(s16 *)(fx + 0x6E);
            if (a < fx[0x5C]) {
                fx[0x2B] = a;
            }
        }
    }
    if (!done && ((speed = *(s32 *)(fx + 0x24)) != 0)) {
        pos = *(s32 *)(fx + 0x20) + speed * D_800BE9E4;
        *(s32 *)(fx + 0x20) = pos;
        top = (D_80090F14[fx[0x18]][0] << 16) - 1;
        if (top < pos) {
            flags = *(s32 *)(fx + 0x58);
            if (flags & 0x800) {
                done = 1;
            } else if (flags & 0x400) {
                *(s32 *)(fx + 0x20) = top - pos % top;
                *(s32 *)(fx + 0x24) = -speed;
            } else {
                do {
                    pos -= top;
                    *(s32 *)(fx + 0x20) = pos;
                } while (top < pos);
            }
        } else if (pos < 0) {
            flags = *(s32 *)(fx + 0x58);
            if (flags & 0x1000) {
                done = 1;
            } else if (flags & 0x400) {
                *(s32 *)(fx + 0x20) = -pos % top;
                *(s32 *)(fx + 0x24) = -speed;
            } else {
                do {
                    pos += top;
                    *(s32 *)(fx + 0x20) = pos;
                } while (pos < 0);
            }
        }
    }
    if (done) {
        if ((fx[0x72] == 0) || (D_8008A1B0[fx[0x72]](fx) == 0)) {
            func_1516972C((struct102 *)fx);
        }
    }
}
