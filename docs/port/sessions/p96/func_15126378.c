/* Aim mode of camera `arg0` (first-person aim / turret / sniper; type +0x23E). Returns the aim state of the target
 * PL (= +0x3D4) +0x197: 0 = off, 2 = aiming (this frame handled here), else as is.
 * Start (state 0, a type of the aim list, the aim flag 0x10 of the input record +0x36C and an "aim" type (PL
 * +0x11A == 2, 0x1B, 0x1F, 0x29), holder on the floor, not climbing): the yaw starts at the holder's facing
 * (+0x40 - 90; for 0x1F / 0x29 the riding object's facing minus its turn +0x2E4 * 0.02), the camera sits at the
 * aim point (func_1512623C) looking 100 units along the yaw, the field of view (+0x184 / +0x188 of PL) is set on
 * a type change, the projection (func_1510B8AC) and the aim sounds (func_1000FA64: 0x605 for 0x23 / 0x24, 0x622
 * twice for 0x1B / 0x1F / 0x29) start, and the holder object is marked for this player (+0x2FC / +0x74).
 * Each frame (state 2): stick (+0x36C bytes 2 / 3) turns the yaw / pitch (PL +0x174 / +0x178) with a squared
 * response scaled by the zoom, the pitch is clamped per type, both are eased (func_15049978) into +0x16C / +0x170,
 * buttons 8 / 4 zoom in / out (0x1A4 / 0x1A8 by the frame step 0.02 * fov), the look vector is rebuilt
 * (func_15048F90 with the aim point and the target 1 unit along it) and the projection and draw distance scale
 * follow the zoom (func_1510B6A8). Leaving aim (no flag, no type, PL +0x1AC, holder not able to aim) calls
 * func_15127EB8 and returns 0. */
#define A_F(o) (*(f32 *)(p + (o)))
#define A_W(o) (*(s32 *)(p + (o)))
#define A_PL (*(u8 **)(p + 0x3D4))
#define A_HOLD (*(u8 **)(p + 0x3D0))
#define A_F_OF(b, o) (*(f32 *)((b) + (o)))
s32 func_15126378(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *e;
    u8 *pl;
    u8 *hold;
    u8 *holder;
    u8 *in;
    f32 fov0;
    f32 aspect;
    f32 step;
    f32 ang;
    f32 rad;
    f32 k;
    f32 zoom;
    f32 lo;
    f32 hi;
    f32 inv;
    f32 dx;
    f32 dy;
    f32 lim;
    f32 r;
    f32 v[3];
    union {
        f32 f;
        s32 w;
    } prod;
    u32 snd;
    f32 sf;
    s32 type;
    s32 ok;
    s32 is1B;
    s32 is1F;
    s32 st;
    u16 flags;

    e = (u8 *)D_800BE628 + p[0x23D] * 0x180;
    aspect = A_F_OF(e, 0x70) / A_F_OF(e, 0x6C);
    pl = A_PL;
    fov0 = -(A_F_OF(e, 0x6C) - 5.0f);
    step = A_F_OF(e, 0x6C) * 0.02f;
    type = p[0x23E];
    if ((type == 0xC && *(u16 *)(A_HOLD + 0x84) != 0x76) || type == 0x1B) {
        *(u16 *)(p + 0x36A) |= 0x10;
        **(u16 **)(p + 0x36C) |= 0x10;
    }
    st = pl[0x197];
    if (st == 0) {
        in = *(u8 **)(p + 0x36C);
        if ((s8)in[2] != 0 || (s8)in[3] != 0) {
            pl[0x194] = 1;
            st = pl[0x197];
        }
    }
    hold = A_HOLD;
    if (hold[0x65] != 0) {
        holder = (u8 *)D_800CC2D0 + (hold[0x65] - 1) * 0x32C;
    } else {
        holder = hold;
    }
    ok = pl[0x11A] == 2 || type == 0x1B || type == 0x1F || type == 0x29;
    switch (type) {
        case 0x23: case 0x24: case 0x16: case 0x18: case 0x41: case 0xC: case 0x14: case 0x3F: case 0x1B:
        case 0x1F: case 0x29:
            break;
        default:
            goto done_start;
    }
    if (!(**(u16 **)(p + 0x36C) & 0x10) || !ok) {
        goto done_start;
    }
    if ((s32)A_F_OF(hold, 0x28) != 0 && (s32)A_F_OF(holder, 0x28) != 0) {
        goto done_start;
    }
    if (hold[0x104] != 0 || st != 0) {
        goto done_start;
    }
    /* start aiming */
    A_PL[0x198] = 0;
    *(s16 *)(p + 0x73C) = 0;
    is1F = type == 0x1F;
    if ((is1F || type == 0x29) && !(A_W(0x5F0) & 4)) {
        ang = (A_F_OF(holder, 0x40) - 90.0f) - (f32)*(s16 *)(holder + 0x2E4) * 0.02f;
        pl[0x194] = 1;
    } else {
        ang = A_F_OF(A_HOLD, 0x40) - 90.0f;
    }
    func_15048758(&ang);
    rad = ang * 0.017453292f;
    func_151239CC(arg0, 1);
    pl[0x197] = 2;
    func_151CA150(p, type);
    func_1512623C(holder, A_PL, type, (f32 *)(p + 0x2F8), (f32 *)(p + 0x2FC), (f32 *)(p + 0x300), A_W(0x5F0) & 0x10);
    A_F(0x2BC) = sinf(rad) * 100.0f + A_F(0x2F8);
    A_F(0x2C0) = A_F_OF(A_HOLD, 0x18) + (f32)*(s16 *)(A_PL + 0x114) * 0.75f;
    A_F(0x2C4) = cosf(rad) * 100.0f + A_F(0x300);
    A_F_OF(pl, 0x13C) = A_F(0x2F8);
    A_F_OF(pl, 0x140) = A_F(0x2FC);
    A_F_OF(pl, 0x144) = A_F(0x300);
    A_F_OF(pl, 0x18C) = A_F(0x37C);
    A_F_OF(pl, 0x160) = A_F(0x2F8);
    A_F_OF(pl, 0x164) = A_F(0x2FC);
    A_F_OF(pl, 0x168) = A_F(0x300);
    if (type != *(s32 *)(pl + 0x190)) {
        if (type == 0x1B) {
            k = 1.0f;
        } else if (type == 0x16) {
            k = 0.75f;
        } else {
            k = 0.5f;
        }
        if (type == 0x18 || type == 0x41 || type == 0x3F || type == 0x14 || type == 0x12) {
            if (k < 0.0f) {
                k = 0.0f;
            } else if (0.6f < k) {
                k = 0.6f;
            }
        }
        pl[0x194] = 1;
        *(s32 *)(pl + 0x190) = type;
        A_F_OF(pl, 0x184) = (0.0f - fov0) * k + fov0;
    }
    if (pl[0x194] != 0) {
        A_F_OF(pl, 0x174) = ang;
        A_F_OF(pl, 0x178) = 0.0f;
        A_F_OF(pl, 0x170) = 0.0f;
        A_F_OF(pl, 0x17C) = 0.0f;
        A_F_OF(pl, 0x180) = 0.0f;
        pl[0x194] = 0;
        A_F_OF(pl, 0x16C) = A_F_OF(pl, 0x174);
    }
    A_F_OF(pl, 0x188) = A_F_OF(pl, 0x184) * aspect;
    A_F(0x19C) = A_F_OF(pl, 0x184);
    A_F(0x1A0) = A_F_OF(pl, 0x188);
    A_F(0x1A4) = A_F_OF(pl, 0x184);
    A_F(0x1A8) = A_F_OF(pl, 0x188);
    func_1510B8AC(p[0x23D], A_F(0x19C), A_F(0x1A0), 1.0f);
    A_F_OF((u8 *)D_800BE628 + p[0x23D] * 0x180, 0x84) = 1.0f;
    func_150627D4((struct127 *)A_HOLD);
    D_800DBFF4[p[0x23D]] = 2;
    if (type == 0x24 || type == 0x23 || type == 0x1B || is1F || type == 0x29) {
        /* f32 -> u32 as the asm converts it (truncation; negative / NaN give 0xFFFFFFFF) */
        sf = -A_F(0x1A4) * 10000.0f;
        if (sf >= 2147483648.0f) {
            snd = (sf - 2147483648.0f < 2147483648.0f) ? ((u32)(s32)(sf - 2147483648.0f) | 0x80000000) : 0xFFFFFFFF;
        } else if (sf > -1.0f) {
            snd = (u32)(s32)sf;
        } else {
            snd = 0xFFFFFFFF;
        }
        if (type == 0x24 || type == 0x23) {
            func_1000FA64(0x605, 0, 0, 0, 0x6590, 0x12C, 0x12B, (s32)func_15127520, arg0, snd, 0, 0);
        } else {
            prod.f = A_F_OF(pl, 0x174) * A_F_OF(pl, 0x178);
            func_1000FA64(0x622, 0, 0, 0, 0x6590, 0x12C, 0x12B, (s32)func_15127520, arg0, snd | 0x80000000, 0x100,
                          0);
            func_1000FA64(0x622, 0, 0, 0, 0x3E80, 0x12C, 0x12B, (s32)func_151277B0, arg0, prod.w, 0x100, 0);
        }
    }
    holder[0x2FC] |= 1 << p[0x23D];
    holder[0x74] |= 1 << p[0x23D];
    st = pl[0x197];
done_start:
    if (st == 0) {
        return 0;
    }
    if (st != 2) {
        return st;
    }
    /* aiming: one frame */
    flags = **(u16 **)(p + 0x36C);
    func_1512623C(holder, A_PL, type, (f32 *)(p + 0x2F8), (f32 *)(p + 0x2FC), (f32 *)(p + 0x300), A_W(0x5F0) & 0x10);
    zoom = A_F(0x19C) / fov0;
    if (zoom < 0.0f) {
        zoom = 0.0f;
    } else if (1.0f < zoom) {
        zoom = 1.0f;
    }
    if (!(flags & 0x10) || type == 0 || pl[0x1AC] != 0) {
        goto leave;
    }
    hold = A_HOLD;
    if (hold[0x1CA] == 0 && type != 0x29) {
        goto leave;
    }
    is1B = type == 0x1B;
    if (hold[0x104] != 0 && hold[0x65] == 0 && (s32)A_F_OF(hold, 0x28) != 0 && type != 0x1F && type != 0x29) {
        goto leave;
    }
    is1F = type == 0x1F;
    if (is1B) {
        lo = 19.0f;
        hi = 31.0f;
    } else {
        lo = 25.0f;
        hi = 90.0f;
    }
    in = *(u8 **)(p + 0x36C);
    inv = 1.0f / ((hi - lo) * zoom + lo);
    inv = inv * inv;
    dx = (f32)(((s8)in[2] >= 0) ? 1 : -1) * ((f32)(s8)in[2] * (f32)(s8)in[2] * inv);
    dy = (f32)(((s8)in[3] >= 0) ? 1 : -1) * ((f32)(s8)in[3] * (f32)(s8)in[3] * inv);
    if (is1B) {
        dx *= 0.25f;
        dy *= 0.5f;
        if (dx < -3.0f) {
            dx = -3.0f;
        } else if (3.0f < dx) {
            dx = 3.0f;
        }
        if (dy < -3.0f) {
            dy = -3.0f;
        } else if (3.0f < dy) {
            dy = 3.0f;
        }
    } else if (type == 0xC) {
        dx *= 1.5f;
        dy *= 1.5f;
    }
    A_F_OF(pl, 0x174) -= dx;
    A_F_OF(pl, 0x178) += dy;
    func_15048758((f32 *)(pl + 0x174));
    if (is1F || type == 0x29) {
        lo = -80.0f;
        hi = 30.0f;
    } else if (is1B) {
        lo = -60.0f;
        hi = 50.0f;
    } else {
        lo = -80.0f;
        hi = 80.0f;
    }
    if (A_F_OF(pl, 0x178) < lo) {
        A_F_OF(pl, 0x178) = lo;
    } else if (hi < A_F_OF(pl, 0x178)) {
        A_F_OF(pl, 0x178) = hi;
    }
    func_15049978((f32 *)(pl + 0x16C), A_F_OF(pl, 0x174), (f32 *)(pl + 0x17C), 6.0f, 8.0f, A_F(0x7B4));
    func_15049978((f32 *)(pl + 0x170), A_F_OF(pl, 0x178), (f32 *)(pl + 0x180), 6.0f, 8.0f, A_F(0x7B4));
    /* zoom buttons */
    if (type != 0x16 && type != 0xC && (flags & 0xC) != 0xC) {
        if ((flags & 8) && fov0 < A_F(0x1A4)) {
            A_F(0x1A4) -= step;
            A_F(0x1A8) -= step * aspect;
        } else if ((flags & 4) && A_F(0x1A4) < 0.0f) {
            A_F(0x1A4) += step;
            A_F(0x1A8) += step * aspect;
        }
    }
    if (type == 0x24) {
        lim = fov0;
    } else if (is1B) {
        lim = fov0 * 0.5f;
    } else {
        lim = fov0 * 0.75f;
    }
    if (A_F(0x1A4) < lim) {
        A_F(0x1A4) = lim;
    } else if (0.0f < A_F(0x1A4)) {
        A_F(0x1A4) = 0.0f;
    }
    lim = lim * aspect;
    if (A_F(0x1A8) < lim) {
        A_F(0x1A8) = lim;
    } else if (0.0f < A_F(0x1A8)) {
        A_F(0x1A8) = 0.0f;
    }
    A_F(0x19C) = A_F(0x1A4);
    A_F(0x1A0) = A_F(0x1A8);
    A_F_OF(pl, 0x184) = A_F(0x1A4);
    A_F_OF(pl, 0x188) = A_F(0x1A8);
    /* look vector: yaw +0x16C, pitch +0x170 (degrees, negated) */
    r = 1.0f;
    v[0] = cosf(A_F_OF(pl, 0x170) * -0.017453292f) * r;
    v[1] = sinf(A_F_OF(pl, 0x170) * -0.017453292f) * r;
    r = v[0];
    v[0] = cosf(A_F_OF(pl, 0x16C) * -0.017453292f) * r;
    v[2] = sinf(A_F_OF(pl, 0x16C) * -0.017453292f) * r;
    A_F(0x2BC) = A_F(0x2F8) + v[0];
    A_F(0x2C0) = A_F(0x2FC) + v[1];
    A_F(0x2C4) = A_F(0x300) + v[2];
    hold = A_HOLD;
    A_F(0x2A4) = A_F_OF(hold, 0x14);
    A_F(0x2A8) = A_F_OF(hold, 0x18);
    A_F(0x2AC) = A_F_OF(hold, 0x1C);
    A_F_OF(pl, 0x148) = A_F(0x2BC);
    A_F_OF(pl, 0x14C) = A_F(0x2C0);
    A_F_OF(pl, 0x150) = A_F(0x2C4);
    A_F_OF(pl, 0x13C) = A_F(0x2F8);
    A_F_OF(pl, 0x140) = A_F(0x2FC);
    A_F_OF(pl, 0x144) = A_F(0x300);
    A_F_OF(pl, 0x130) = v[0];
    A_F_OF(pl, 0x134) = v[1];
    A_F_OF(pl, 0x138) = v[2];
    func_15048F90((struct17 *)(pl + 0x13C), (struct17 *)(pl + 0x148), (struct17 *)(pl + 0x130));
    A_F_OF((u8 *)D_800BE628 + p[0x23D] * 0x180, 0x84) = -0.94f * zoom + 1.0f;
    func_1510B6A8(p[0x23D], A_F(0x19C), A_F(0x1A0), A_F_OF((u8 *)D_800BE628 + p[0x23D] * 0x180, 0x84),
                  71.0f * zoom + 54.0f);
    return 1;
leave:
    func_15127EB8(arg0);
    return 0;
}
#undef A_F
#undef A_W
#undef A_PL
#undef A_HOLD
#undef A_F_OF
