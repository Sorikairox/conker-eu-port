u8 * func_15031C4C(u8 *arg0, s32 arg1, s32 arg2);
void func_15145EA4(f32 **arg0, f32 **arg1, Mtx *arg2, s32 arg3);
s32 func_1514654C(u8 *, s32, s32, u8 **, u8 **, s32);

// attached_points_update: refreshes the two attachment points of arg0 (arg0 + 0x34 / + 0x40) from its owner
// (arg0 + 0x110): 0 when the owner changed or is gone, 1 when it has no model / is hidden or after the update. With
// a joint id (+0x11C != -1) the points come from that joint (func_1514654C), else from the owner's matrix list
// (func_15145EA4); sets bit 0 of +0x124 on success. P124: the point lists are 2-element arrays (m2c had 4 locals).
s32 func_15103310(u8 *arg0) {
    u8 *dst[2];
    u8 *src[2];
    s16 joint;
    s32 node;
    u8 *att;
    u8 *owner;

    owner = *(u8 **)(arg0 + 0x110);
    arg0[0x124] &= 0xFE;
    if (arg0[0x114] != owner[0x3B] || *(s32 *)(owner + 0) == 0) {
        return 0;
    }
    if (*(s32 *)(owner + 0x1D4) == 0 || (owner[0x74] & 0xF) == 0xF) {
        return 1;
    }
    att = arg0 + 0x110;
    dst[0] = arg0 + 0x34;
    dst[1] = arg0 + 0x40;
    src[0] = att + 0x18;
    src[1] = att + 0x24;
    joint = *(s16 *)(att + 0xC);
    if (joint != -1) {
        node = (s32) func_15031C4C(owner, joint, 0);
        if (node == 0) {
            return 0;
        }
        if (func_1514654C(owner, node, *(s32 *)(att + 0x10), dst, src, 2) == 0) {
            return 0;
        }
    } else {
        func_15145EA4((f32 **) dst, (f32 **) src, (Mtx *) (*(s32 *)(owner + 0x1D4) + *(s32 *)(att + 8)), 2);
    }
    att[0x14] |= 1;
    return 1;
}
