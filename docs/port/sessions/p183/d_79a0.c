// player_aim_look: P183: first-person aim look of the player object arg0 (its camera record PL = arg0 +0x31C,
// input record arg1: buttons u16 +0, stick s8 +2 / +3). Types 0xC / 0x1B force the aim button (0x10). Start
// (aim type 0x12 / 0x14 / 0x16 / 0x18 / 0x1B / 0x1F / 0x23 / 0x24 / 0x29 / 0x3F / 0x41 / 0xC, aim button, state
// PL +0x197 == 0): state 2, yaw = facing (+0x40) - 90, pitch / speeds 0, func_150627D4(arg0). The asm also copies
// its not yet written eye slot to PL +0x13C there (rewritten below in the same call); kept as is.
// Each frame in state 2: eye = (x, y + PL +0x114 * 0.75 + (y - +0x30), z) of arg0; without the aim button it
// leaves (state 0, func_150627D4, returns 0); else the stick turns PL yaw / pitch +0x174 / +0x178 by 0.025 per
// unit, the yaw wraps (func_15048758), the pitch is clamped to -20..80 (types 0x1F / 0x29) or -80..80, both ease
// (func_15049978, 6 / 8 / frame time x 0.02) into +0x16C / +0x170, and PL gets eye +0x13C, target eye + dir
// +0x148, dir +0x130. Returns 1; 0 when off; the type byte PL +0x78 in any other state.
s32 func_151279A0(struct127 *arg0, struct49 *arg1) {
    u8 *obj = (u8 *) arg0;
    u8 *in = (u8 *) arg1;
    u8 *pl = *(u8 **) (obj + 0x31C);
    f32 eye[3];
    f32 target[3];
    f32 dir[3];
    f32 zoom;
    f32 yaw;
    f32 v;
    f32 lo;
    f32 c;
    u16 buttons;
    s32 type;
    s32 st;

    zoom = (f32) D_800BE9E4 * 0.02f;
    type = pl[0x78];
    if (type == 0xC || type == 0x1B) {
        *(u16 *) in |= 0x10;
    }
    switch (type) {
        case 0x23: case 0x24: case 0x16: case 0x12: case 0x18: case 0x41: case 0xC: case 0x14: case 0x3F:
        case 0x1B: case 0x1F: case 0x29:
            if ((*(u16 *) in & 0x10) && pl[0x197] == 0) {
                pl[0x197] = 2;
                *(f32 *) (pl + 0x13C) = eye[0];
                *(f32 *) (pl + 0x140) = eye[1];
                *(f32 *) (pl + 0x144) = eye[2];
                *(f32 *) (pl + 0x178) = 0.0f;
                *(f32 *) (pl + 0x170) = 0.0f;
                *(f32 *) (pl + 0x17C) = 0.0f;
                *(f32 *) (pl + 0x180) = 0.0f;
                *(f32 *) (pl + 0x174) = *(f32 *) (obj + 0x40) - 90.0f;
                *(f32 *) (pl + 0x16C) = *(f32 *) (pl + 0x174);
                func_150627D4(arg0);
            }
            break;
    }
    st = pl[0x197];
    if (st == 0) {
        return 0;
    }
    if (st != 2) {
        return type;
    }

    buttons = *(u16 *) in;
    target[0] = *(f32 *) (obj + 0x14);
    yaw = (*(f32 *) (obj + 0x40) - 90.0f) * 0.017453292f;
    target[1] = *(f32 *) (obj + 0x18) + (f32) *(s16 *) (pl + 0x114) * 0.75f;
    target[2] = *(f32 *) (obj + 0x1C);
    eye[0] = target[0];
    eye[1] = target[1];
    eye[2] = target[2];
    target[0] = sinf(yaw) * 100.0f + eye[0];
    target[2] = cosf(yaw) * 100.0f + eye[2];
    eye[1] = eye[1] + (*(f32 *) (obj + 0x18) - *(f32 *) (obj + 0x30));
    if (!(buttons & 0x10) || type == 0) {
        pl[0x197] = 0;
        func_150627D4(arg0);
        return 0;
    }

    *(f32 *) (pl + 0x174) = *(f32 *) (pl + 0x174) - (f32) (s8) in[2] * 0.025f;
    *(f32 *) (pl + 0x178) = *(f32 *) (pl + 0x178) + (f32) (s8) in[3] * 0.025f;
    func_15048758((f32 *) (pl + 0x174));
    if (type == 0x1F || type == 0x29) {
        lo = -20.0f;
    } else {
        lo = -80.0f;
    }
    v = *(f32 *) (pl + 0x178);
    if (v < lo) {
        *(f32 *) (pl + 0x178) = lo;
    } else {
        *(f32 *) (pl + 0x178) = (80.0f < v) ? 80.0f : v;
    }
    func_15049978((f32 *) (pl + 0x16C), *(f32 *) (pl + 0x174), (f32 *) (pl + 0x17C), 6.0f, 8.0f, zoom);
    func_15049978((f32 *) (pl + 0x170), *(f32 *) (pl + 0x178), (f32 *) (pl + 0x180), 6.0f, 8.0f, zoom);

    c = cosf(*(f32 *) (pl + 0x170) * -0.017453292f) * 1.0f;
    dir[1] = sinf(*(f32 *) (pl + 0x170) * -0.017453292f) * 1.0f;
    dir[0] = cosf(*(f32 *) (pl + 0x16C) * -0.017453292f) * c;
    dir[2] = sinf(*(f32 *) (pl + 0x16C) * -0.017453292f) * c;
    target[0] = eye[0] + dir[0];
    target[1] = eye[1] + dir[1];
    target[2] = eye[2] + dir[2];
    *(f32 *) (pl + 0x148) = target[0];
    *(f32 *) (pl + 0x14C) = target[1];
    *(f32 *) (pl + 0x150) = target[2];
    *(f32 *) (pl + 0x13C) = eye[0];
    *(f32 *) (pl + 0x140) = eye[1];
    *(f32 *) (pl + 0x144) = eye[2];
    *(f32 *) (pl + 0x130) = dir[0];
    *(f32 *) (pl + 0x134) = dir[1];
    *(f32 *) (pl + 0x138) = dir[2];
    return 1;
}
