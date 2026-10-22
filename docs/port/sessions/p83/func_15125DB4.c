/* Allowed camera controls of this frame: +0x36A = mask of the camera buttons the player may use (from the
 * camera mode +0x23E or the table D_800BEB30[+0x368]), *(+0x36C) = the control flags, both cut down by the
 * player / camera state (paused or locked camera: nothing; first-person, aiming, swimming, ... : no zoom /
 * rotate bits). +0x84A counts down a short lock (flag 0x40). */
#define CAM_W(o) (*(s32 *)(p + (o)))
#define CAM_H(o) (*(s16 *)(p + (o)))
#define CAM_F(o) (*(f32 *)(p + (o)))
void func_15125DB4(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *pl = *(u8 **)(p + 0x3D4);
    u8 mode = p[0x23E];
    u16 *ctl;

#define MASK (*(u16 *)(p + 0x36A))
#define CTL (**(u16 **)(p + 0x36C))
    if (pl[0x120] != 0 || D_80084810 != 0) {
        MASK = 0;
        CTL &= 0xFFE0;
        return;
    }
    if (mode == 0) {
        if (CAM_W(0x2C) & 0x100) {
            MASK &= 0xFFF0;
            CTL &= 0xFFF0;
        }
    } else {
        if (mode == 2 || mode == 0x12 || mode == 0x13 || mode == 0xA || mode == 0x34 || mode == 0x10 ||
            mode == 0xF) {
            if (mode == 0xF) {
                func_1509BFB0(3, 0x9000, 0x18, 0x25, 0x13, 0x1E0);
            }
            CTL |= 0x10;
            MASK |= 0x10;
            CTL &= 0xFFF0;
        } else {
            MASK = D_800BEB30[CAM_H(0x368)];
        }
        if (mode == 3 || mode == 0xD || mode == 0x1A || mode == 0x2A) {
            MASK &= ~0xF;
            CTL &= ~0xF;
        }
        if (mode == 0x29) {
            CTL |= 0x10;
            MASK |= 0x10;
        }
    }
    if ((*(u8 **)(p + 0x3D0))[0xAD] == 1 && (CAM_W(0x2C) & 0x80)) {
        MASK &= 0xFFE3;
        CTL &= 0xFFF3;
    }
    if (CAM_W(0x84) & 0x200000) {
        MASK &= ~0xF;
    }
    if (D_800C3671 != 0 || (CAM_W(0x5F0) & 0x80)) {
        MASK &= 0xFFE0;
        CTL &= 0xFFE0;
    }
    pl = *(u8 **)(p + 0x3D4);
    if (pl[0x7D] != 0 || pl[0x1AC] != 0 || pl[0x27] != 0) {
        MASK &= 0xFFEF;
        CTL &= 0xFFEF;
    }
    pl = *(u8 **)(p + 0x3D4);
    if (pl[0x95] != 0 || (CAM_H(0x5FC) != 0 && pl[0x1B3] != 0)) {
        MASK &= ~0x1F;
        CTL &= ~0x1F;
    }
    if (((CAM_W(0x2C) & 0x100) && CAM_H(0x73C) == 0) || CAM_H(0x73C) == 3) {
        MASK &= ~0x10;
        CTL &= ~0x10;
    }
    if ((CAM_W(0x2C) & 0x40) && CAM_H(0x84A) != 0) {
        CAM_H(0x84A) -= D_800BE9E4;
        MASK &= ~0x10;
        CTL &= ~0x10;
        if (CAM_H(0x84A) <= 0) {
            CAM_H(0x84A) = 0;
        }
    }
#undef MASK
#undef CTL
}
#undef CAM_W
#undef CAM_H
#undef CAM_F
