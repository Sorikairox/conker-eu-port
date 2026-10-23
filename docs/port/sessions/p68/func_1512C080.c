/* Camera eye collision. Unless collision is off (+0x84 flags 0x40000 / 0x80 / 0x200, the followed object
 * +0x3D4 has +0x95 set, or mode +0x2C == 0x40: then +0x3E8 = 1), the eye's collision ellipsoid size
 * (+0x94C width, +0x950 height) is picked from the situation and eased into +0x95C / +0x960 (func_150498A0,
 * speeds +0x954 / +0x958; set at once while +0x23C is set). A probe object (struct127, type 0x2D, camera
 * = this one) at the eye (+0x2F8; y raised by +0x18C with flag 0x800 of +0x5F0) is moved by func_15044670
 * from the previous eye (+0x304) with the collision globals D_800CC1F2..F4 and D_800894C0[1..2] set for the
 * call and restored after it. The probe's final position is the new eye (y not in mode 0x100);
 * +0x3E8 = no collision, +0x26C eases to 1.0 (0.1 per frame) or drops to 0.005 on a hit. After a hit the
 * eye is kept 40 above the floor below it (func_1510EE3C), except in level 0x1B and mode 0x100.
 * Always ends with func_151236D0 (state flags). The asm leaves v0 undefined: void under NM. */
extern u8 D_800894C0[];
extern u8 D_800CC1F2;
extern u8 D_800CC1F3;
extern u8 D_800CC1F4;
s32 func_15044670(f32 fromX, f32 fromY, s32 fromZBits, struct127 *probe, s32 arg4, s32 arg5);
#define C080_F(o) (*(f32 *)(p + (o)))
#define C080_W(o) (*(s32 *)(p + (o)))
void func_1512C080(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    struct127 probe;      /* sp74 */
    f32 floorY;           /* sp60 */
    u8 *target = *(u8 **)(p + 0x3D4);
    u8 *followed;
    s32 small = FALSE;    /* t3: the size used is the small "close" one */
    s32 savedSlide;       /* D_800894C0[2] */
    s32 savedStep;        /* D_800894C0[1] */
    s32 saved1F3;
    s32 saved1F4;
    s32 hit;
    s16 view;

    if ((C080_W(0x84) & 0x40000) || target[0x95] != 0 || C080_W(0x2C) == 0x40 || (C080_W(0x84) & 0x80) ||
        (C080_W(0x84) & 0x200)) {
        p[0x3E8] = 1;
        func_151236D0(arg0);
        return;
    }
    savedSlide = D_800894C0[2];
    savedStep = D_800894C0[1];

    /* collision size */
    if (C080_W(0x5F0) & 0x800) {
        C080_F(0x94C) = 20.0f;
        C080_F(0x950) = 40.0f;
    } else if (C080_W(0x5F0) & 0x10) {
        C080_F(0x94C) = 20.0f;
        C080_F(0x950) = 72.0f;
    } else if (580.0f < C080_F(0x374)) {
        C080_F(0x94C) = 70.0f;
        C080_F(0x950) = 140.0f;
    } else if (D_800BE9F0 == 0x31 && p[0x23E] == 3) {
        C080_F(0x94C) = 20.0f;
        C080_F(0x950) = 50.0f;
        small = TRUE;
    } else {
        view = *(s16 *)(p + 0x73C);
        followed = *(u8 **)(p + 0x3D0);
        if ((view == 0 || view == 1 || view == 3) &&
            (followed[0x102] == 0 || (C080_F(0x2B0) == *(f32 *)(followed + 0x14) &&
                                      C080_F(0x2B8) == *(f32 *)(followed + 0x1C))) &&
            target[0x1B3] == 0) {
            if (followed[0x102] != 0) {
                C080_F(0x94C) = 25.0f;
                C080_F(0x950) = 30.0f;
                small = TRUE;
            } else {
                C080_F(0x94C) = 30.0f;
                C080_F(0x950) = 60.0f;
            }
        } else {
            C080_F(0x94C) = 20.0f;
            C080_F(0x950) = 20.0f;
        }
    }
    if (p[0x23C] != 0) {
        C080_F(0x954) = 0.0f;
        C080_F(0x95C) = C080_F(0x94C);
        C080_F(0x958) = 0.0f;
        C080_F(0x960) = C080_F(0x950);
    } else {
        func_150498A0((f32 *)(p + 0x95C), C080_F(0x94C), (f32 *)(p + 0x954), 4.0f, 6.0f, C080_F(0x7B4));
        func_150498A0((f32 *)(p + 0x960), C080_F(0x950), (f32 *)(p + 0x958), 4.0f, 6.0f, C080_F(0x7B4));
    }

    /* the probe */
    probe.interaction_state = 0x2D;
    probe.camera = arg0;
    probe.x_position = C080_F(0x2F8);
    if (C080_W(0x5F0) & 0x800) {
        probe.y_position = C080_F(0x2FC) + C080_F(0x18C);
    } else {
        probe.y_position = C080_F(0x2FC);
    }
    probe.z_position = C080_F(0x300);
    probe.unk188 = C080_W(0x644);
    probe.unk28 = probe.y_position - C080_F(0x354);
    probe.y_velocity = 0.0f;
    probe.unk180 = C080_F(0x354);
    probe.unk40 = C080_F(0x37C);

    if ((C080_W(0x84) & 0x80000000) || D_800BE9F0 == 0x37) {
        D_800894C0[2] = 0;
    }
    if (C080_W(0x84) & 0x10000) {
        D_800894C0[1] = 0;
    }
    D_800CC1F2 = 1;
    saved1F3 = D_800CC1F3;
    D_800CC1F3 = (((u8 *)*(u8 **)(p + 0x3D0))[0x102] != 0) ? 1 : 0;
    saved1F4 = D_800CC1F4;
    D_800CC1F4 = (p[0x23C] != 0 || (C080_W(0x2C) == 0x100 && !small)) ? 1 : 0;
    hit = func_15044670(C080_F(0x304), C080_F(0x308), C080_W(0x30C), &probe, 0, 0);
    D_800CC1F4 = saved1F4;
    D_800CC1F2 = 0;
    D_800CC1F3 = saved1F3;
    D_800894C0[2] = savedSlide;
    D_800894C0[1] = savedStep;

    if (hit != 0) {
        p[0x3E8] = 0;
        C080_F(0x26C) = 0.005f; /* D_800A3A68 */
    } else {
        p[0x3E8] = 1;
        C080_F(0x26C) = C080_F(0x26C) + (1.0f - C080_F(0x26C)) * 0.1f; /* D_800A3A6C */
    }
    C080_F(0x2F8) = probe.x_position;
    if (C080_W(0x2C) != 0x100) {
        if (C080_W(0x5F0) & 0x800) {
            C080_F(0x2FC) = probe.y_position - C080_F(0x18C);
        } else {
            C080_F(0x2FC) = probe.y_position;
        }
    }
    C080_F(0x300) = probe.z_position;
    if (D_800BE9F0 != 0x1B && hit != 0 && C080_W(0x2C) != 0x100) {
        func_1510EE3C(0, 0, (s32)&floorY, 0, 0, 0, C080_F(0x2F8), C080_F(0x2FC), C080_F(0x300), C080_F(0x308), 0, 0,
                      0xC61C4000 /* -10000.0f, D_800A3A70 */, *(s32 *)(p + 0x2FC), 1);
        if (C080_F(0x2FC) < floorY + 40.0f) {
            C080_F(0x2FC) = floorY + 40.0f;
        }
    }
    func_151236D0(arg0);
}
