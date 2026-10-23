s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32 *, u8 *, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
f32 func_15143E64(f32 *);
// laser_sight_update: update handler (D_8008A058 slot 21) of an aim beam carried by an object (+0x110, valid while
// its +0 is set and its id +0x3B equals +0x114). The beam starts at a bone point (+0x118 in bone +0x130 space) of
// the object's skeleton (+0x1D4; skipped in mode D_800C35EA 1 when the object's +0x74 low nibble is 0xF). With flag
// 2 (+0x133) the end comes from the object's aim block (+0x31C): its locked target (+0x109 = hit kind, position
// +0xB8, distance +0xB4, surface +0xF4) or, unlocked, 2000 units along the aim direction (+0xE8). Otherwise the end
// point (+0x124, bone space) is ray cast (func_150ACEA0); a hit stores the end at +0x40 and the length at +0x154.
// On a hit (+0x133 bit 0 set) the linked effects follow: the impact (+0x138, 20 units before the end, with the
// surface data), a second marker (+0x144, hit kinds 2 / 3), a sound emitter (+0x13C), the beam (+0x134, scaled by
// +0x148) and a line (+0x140); without a hit they are all hidden. Returns 0 once the object is gone.
s32 func_151018F8(u8 *fx) {
    u8 *st = fx + 0x110;
    u8 *obj = *(u8 **)st;
    u8 *bones;
    u8 *mtx;
    u8 *aim;
    u8 *p;
    u8 hit;
    u8 visible;
    f32 dir[3];
    f32 end[3];
    s32 hitInfo;
    u8 surf[0x12];
    f32 inv;
    s32 i;

    if (*(s32 *)obj == 0 || st[4] != obj[0x3B]) {
        return 0;
    }
    visible = 1;
    hit = 0;
    bones = *(u8 **)(obj + 0x1D4);
    if (bones != NULL && (D_800C35EA != 1 || (obj[0x74] & 0xF) != 0xF)) {
        mtx = bones + (st[0x20] << 6);
        func_15143134(st + 0x8, fx + 0x34, mtx);
        if (st[0x23] & 2) {
            aim = *(u8 **)(obj + 0x31C);
            hit = aim[0x109];
            if (hit != 0) {
                *(f32 *)(fx + 0x40) = *(f32 *)(aim + 0xB8);
                *(f32 *)(fx + 0x44) = *(f32 *)(aim + 0xBC);
                *(f32 *)(fx + 0x48) = *(f32 *)(aim + 0xC0);
                *(f32 *)(st + 0x44) = *(f32 *)(*(u8 **)(obj + 0x31C) + 0xB4);
                aim = *(u8 **)(obj + 0x31C);
                for (i = 0; i < 0x12; i++) {
                    surf[i] = aim[0xF4 + i];
                }
                dir[0] = *(f32 *)(fx + 0x40) - *(f32 *)(fx + 0x34);
                dir[1] = *(f32 *)(fx + 0x44) - *(f32 *)(fx + 0x38);
                dir[2] = *(f32 *)(fx + 0x48) - *(f32 *)(fx + 0x3C);
            } else {
                visible = 0;
                hit = 2;
                *(f32 *)(st + 0x44) = 2000.0f;
                dir[0] = *(f32 *)(*(u8 **)(obj + 0x31C) + 0xE8) * 2000.0f;
                dir[1] = *(f32 *)(*(u8 **)(obj + 0x31C) + 0xEC) * 2000.0f;
                dir[2] = *(f32 *)(*(u8 **)(obj + 0x31C) + 0xF0) * 2000.0f;
                *(f32 *)(fx + 0x40) = *(f32 *)(fx + 0x34) + dir[0];
                *(f32 *)(fx + 0x44) = *(f32 *)(fx + 0x38) + dir[1];
                *(f32 *)(fx + 0x48) = *(f32 *)(fx + 0x3C) + dir[2];
            }
        } else {
            func_15143134(st + 0x14, end, mtx);
            end[0] -= *(f32 *)(fx + 0x34);
            end[1] -= *(f32 *)(fx + 0x38);
            end[2] -= *(f32 *)(fx + 0x3C);
            if (func_150ACEA0(*(f32 *)(fx + 0x34), *(f32 *)(fx + 0x38), *(f32 *)(fx + 0x3C), end[0], end[1], end[2],
                              &hitInfo, surf, (f32 *)(fx + 0x40), (f32 *)(fx + 0x44), (f32 *)(fx + 0x48), NULL, 0,
                              0, 0.0f) != 0) {
                dir[0] = *(f32 *)(fx + 0x40) - *(f32 *)(fx + 0x34);
                dir[1] = *(f32 *)(fx + 0x44) - *(f32 *)(fx + 0x38);
                dir[2] = *(f32 *)(fx + 0x48) - *(f32 *)(fx + 0x3C);
                *(f32 *)(st + 0x44) = func_15143E64(dir);
                hit = 1;
            } else {
                hit = 0;
            }
        }
    }

    if (hit != 0) {
        st[0x23] |= 1;
        p = *(u8 **)(st + 0x28);
        if (p != NULL) {
            if (hit == 1 && visible) {
                if (*(f32 *)(st + 0x44) > 40.0f) {
                    inv = 1.0f / *(f32 *)(st + 0x44);
                    *(f32 *)(p + 0x34) = *(f32 *)(fx + 0x40) - dir[0] * inv * 20.0f;
                    *(f32 *)(p + 0x38) = *(f32 *)(fx + 0x44) - dir[1] * inv * 20.0f;
                    *(f32 *)(p + 0x3C) = *(f32 *)(fx + 0x48) - dir[2] * inv * 20.0f;
                } else {
                    *(f32 *)(p + 0x34) = *(f32 *)(fx + 0x40);
                    *(f32 *)(p + 0x38) = *(f32 *)(fx + 0x44);
                    *(f32 *)(p + 0x3C) = *(f32 *)(fx + 0x48);
                }
                for (i = 0; i < 0x12; i++) {
                    p[0x112 + i] = surf[i];
                }
                p[0x110] |= 1;
            } else {
                p[0x110] &= ~1;
            }
        }
        p = *(u8 **)(st + 0x34);
        if (p != NULL) {
            if ((hit == 2 || hit == 3) && visible) {
                *(f32 *)(p + 0x40) = *(f32 *)(fx + 0x40);
                *(f32 *)(p + 0x44) = *(f32 *)(fx + 0x44);
                *(f32 *)(p + 0x48) = *(f32 *)(fx + 0x48);
                p[0xAC] |= 1;
            } else {
                p[0xAC] &= ~1;
            }
        }
        p = *(u8 **)(st + 0x2C);
        if (p != NULL) {
            *(s16 *)(*(u8 **)(p + 0x14) + 0xE) = (s32) * (f32 *)(fx + 0x40);
            *(s16 *)(*(u8 **)(p + 0x14) + 0x10) = (s32) * (f32 *)(fx + 0x44);
            *(s16 *)(*(u8 **)(p + 0x14) + 0x12) = (s32) * (f32 *)(fx + 0x48);
            (*(u8 **)(p + 0x14))[9] = visible ? 0 : 1;
        }
        p = *(u8 **)(st + 0x24);
        if (p != NULL) {
            *(f32 *)(p + 0x40) = *(f32 *)(fx + 0x34);
            *(f32 *)(p + 0x44) = *(f32 *)(fx + 0x38);
            *(f32 *)(p + 0x48) = *(f32 *)(fx + 0x3C);
            *(f32 *)(p + 0x38) = *(f32 *)(p + 0xA8) * *(f32 *)(st + 0x38);
            p[0xD4] |= 1;
            *(f32 *)(p + 0x3C) = *(f32 *)(p + 0xAC) * *(f32 *)(st + 0x38);
        }
        p = *(u8 **)(st + 0x30);
        if (p != NULL) {
            *(f32 *)(p + 0x34) = *(f32 *)(fx + 0x34);
            *(f32 *)(p + 0x38) = *(f32 *)(fx + 0x38);
            *(f32 *)(p + 0x3C) = *(f32 *)(fx + 0x3C);
            *(f32 *)(p + 0x40) = *(f32 *)(fx + 0x40);
            *(f32 *)(p + 0x44) = *(f32 *)(fx + 0x44);
            *(f32 *)(p + 0x48) = *(f32 *)(fx + 0x48);
            p[0x174] |= 1;
            *(s32 *)(p + 0x58) &= ~4;
        }
    } else {
        st[0x23] &= ~1;
        p = *(u8 **)(st + 0x28);
        if (p != NULL) {
            p[0x110] &= ~1;
        }
        p = *(u8 **)(st + 0x2C);
        if (p != NULL) {
            (*(u8 **)(p + 0x14))[9] = 1;
        }
        p = *(u8 **)(st + 0x24);
        if (p != NULL) {
            p[0xD4] &= ~1;
        }
        p = *(u8 **)(st + 0x30);
        if (p != NULL) {
            p[0x174] &= ~1;
        }
        p = *(u8 **)(st + 0x34);
        if (p != NULL) {
            p[0xAC] &= ~1;
        }
    }
    return 1;
}
