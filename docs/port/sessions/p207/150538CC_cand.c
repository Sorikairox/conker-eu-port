s32 func_150889D8();
struct127 *func_1508882C(s32 player, s32 dir, f32 *t, s32 *alt);
void func_150877C0(s32 player, s32 mode, f32 speed);
void func_15088BFC(struct127 *arg0);
s32 func_15104BB4(f32, f32, f32, f32 *);
u16 func_1505A630(f32 arg0, f32 arg1, s32 arg2);
f32 func_1505A72C(struct127 *arg0, struct127 *arg1);
s32 func_15059B54(struct127 *arg0, u16 arg1);
void func_15059C84(struct127 *rec);
void func_1505A770(struct127 *rec);
void func_15058898(struct127 *arg0, f32 arg1);
void func_1505B5F8(struct127 *arg0, f32 arg1);
f32 func_150484A0(f32 arg0, f32 arg1);
s32 func_1505DDA8(struct127 *rec, s32 unused, u16 cone, f32 scale);
s32 func_15081A90(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
s32 func_15082278(u8 *obj, u8 *hit, s32 kind);
s32 func_100107F8(struct127 *arg0);
s32 func_10010894(struct127 *arg0);
u16 func_10010154(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4);
s32 func_150ADA20(void);
int func_151EFDD0(void);
void func_15060A30(s32 arg0, struct127 *arg1);
void func_15060778(s32 arg0, struct127 *arg1, u16 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_15174690(s32, s32, s32, s32, s32, s32, s32, u8, s32);
f32 func_1505A3A8(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4);
void func_1505D6F0(struct127 *, s32);
void func_1506E6FC(void);
s32 func_15145128(f32 *, f32 *, s32 *, s32 *);
void func_150D7630(u8 *arg0, u8 arg1, s32 arg2);
void func_150D779C(s32, f32 *, f32 *, u8, s32);
extern f32 D_800D27BC;
extern f32 D_800D27C0;
extern f32 D_800D27C4;
extern s8 D_800E1050;
extern f32 D_800CC674[3];
extern s32 D_800CC680;

#define P38_F32(o) (*(f32 *) (p + (o)))
#define P38_U8(o) (*(u8 *) (p + (o)))
#define P38_U16(o) (*(u16 *) (p + (o)))
#define P38_OBJ(i) ((u8 *) &D_800CC2D0[i])

// thrown_object_fly_update: per-frame update of a thrown / flying object (kind at +0x278). Kinds 13 / 14 ride a
// rail (func_150889D8 gives the rail record): func_150877C0 steps it, the object homes on its target (+0x221, or
// the rail's next object from func_1508882C, never its owner +0x124) or on the camera point D_800D27BC, the rail
// record's t (+0x0) eases to the target t and +0x2F takes the side flag; the step is clamped to 200 (kind 13) /
// 30 and the height kept 50 above the floor. Then: homing turn towards +0x126 (+0x82 window), kind sounds / spin,
// collision (func_15058898 / func_1505B5F8), hit tests (+0x284: func_15081A90 / func_15082278, else the bounce,
// landing sounds and func_1505C7D8 hits), and the object is removed (func_15060F28 mode 1) when it hit, ran out
// of time (+0x7F >= 31, +0x83 reaches 0) or health (+0x1CA); else +0x103 = 1.
// Rare reads t / side uninitialised when a +0x221 target exists but is far (> 1000) or the kind is 14: here
// they start as 0.5 / 0.
void func_150538CC(struct127 *obj) {
    u8 *p = (u8 *) obj;
    s8 done = FALSE;
    s32 kind = *(u16 *) (p + 0x278);
    s32 hitTest = *(s8 *) (p + 0x284);
    s32 flags = 0;
    s32 rail;
    s32 dir;
    s32 alt = 0;
    f32 t = 0.5f;
    f32 maxStep;
    f32 speed;
    f32 dist;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 floorY;
    f32 startY;
    f32 pitch;
    f32 range;
    f32 len;
    f32 inv;
    f32 dir3[3];
    f32 vec[3];
    s32 owner;
    s32 n;
    u16 ang;
    u8 *target;
    u8 *o;
    u8 *rec;

    if ((kind == 2 || kind == 18) && P38_U16(0x282) != 0) {
        if (D_800BE9E4 < P38_U16(0x282)) {
            P38_U16(0x282) -= D_800BE9E4;
        } else {
            P38_U16(0x282) = 0;
            P38_F32(0x24) = 1.0f;
        }
    }

    if (kind == 13 || kind == 14) {
        rail = func_150889D8(obj);
        if (rail != -1) {
            if (kind == 13) {
                speed = 0.2f;
                dir = 1;
                maxStep = 200.0f;
            } else {
                speed = 0.0f;
                dir = -1;
                maxStep = 30.0f;
            }
            func_150877C0(rail, 0, speed);
            *(s8 *) (p + 0x328) = 1;
            if (*(s8 *) (p + 0x221) == -1) {
                target = (u8 *) func_1508882C(rail, dir, &t, &alt);
                owner = P38_U8(0x124);
                if (owner != 0 && target == P38_OBJ(owner - 1)) {
                    target = NULL;
                }
            } else {
                target = P38_OBJ(*(s8 *) (p + 0x221));
            }
            if (target != NULL &&
                ((*(u8 **) (target + 0x31C))[0x120] != 0 || *(u8 *) (target + 0x125) > 0)) {
                target = NULL;
                *(s8 *) (p + 0x221) = -1;
            }
            if (target != NULL) {
                dx = *(f32 *) (target + 0x14) - P38_F32(0x14);
                dy = *(f32 *) (target + 0x18) - P38_F32(0x18);
                dz = *(f32 *) (target + 0x1C) - P38_F32(0x1C);
                dist = dx * dx + dz * dz;
            } else {
                alt = (D_8009015C & 0x40) != 0;
                t = 0.5f;
            }
            if (P38_U8(0x81) < 10) {
                target = NULL;
            }
            if (target == NULL || dist > 1000000.0f || kind == 14) {
                dx = D_800D27BC - P38_F32(0x14);
                dy = (D_800D27C0 + 100.0f) - P38_F32(0x18);
                dz = D_800D27C4 - P38_F32(0x1C);
                rec = (u8 *) D_80087640 + rail * 0x84;
                *(f32 *) rec = *(f32 *) rec + (t - *(f32 *) rec) * 0.125f;
                ((u8 *) D_80087640 + rail * 0x84)[0x2F] = alt;
            } else {
                *(s8 *) (p + 0x221) = ((u8 *) target - (u8 *) D_800CC2D0) / 0x32C;
            }
            dist = sqrtf(dx * dx + dy * dy + dz * dz);
            if (dist > 1.0f) {
                if (dist < maxStep) {
                    maxStep = dist;
                }
                dist = maxStep / dist;
                dx *= dist;
                dy *= dist;
                dz *= dist;
                P38_U16(0x76) = func_1505A630(-dx, dz, 0);
            }
            P38_F32(0x14) += dx;
            P38_F32(0x18) += dy;
            P38_F32(0x1C) += dz;
            if (func_15104BB4(P38_F32(0x14), P38_F32(0x1C), P38_F32(0x18) + 50.0f, &floorY) > 0 &&
                P38_F32(0x18) < floorY + 50.0f) {
                P38_F32(0x18) = floorY + 50.0f;
            }
            P38_U8(0x89) = 1;
            P38_U8(0x103) = 1;
            P38_F32(0x3C) = 0.0f;
        }
        P38_U16(0xB2) = (P38_U16(0xB2) + 1) & 1;
        if (P38_U16(0xB2) != 0) {
            P38_U8(0x83)++;
        }
        if (D_800E1050 != 0 || D_800E0B94 != 0) {
            P38_U8(0x83) = 1;
            done = TRUE;
        }
        if (P38_U8(0x81) < 10) {
            P38_U8(0x81)++;
        }
    }

    if (P38_U8(0x80) < 100) {
        if (P38_U8(0x102) != 0) {
            P38_U8(0x82) = 40;
        }
        o = P38_OBJ(P38_U8(0x126));
        ang = func_1505A630(*(f32 *) (o + 0x14) - P38_F32(0x14), P38_F32(0x1C) - *(f32 *) (o + 0x1C), 0);
        n = P38_U8(0x82);
        P38_U16(0x78) = ang;
        if ((u8) (((s32) (ang - P38_U16(0x76)) >> 8) + n) < n * 2) {
            o = P38_OBJ(P38_U8(0x126));
            pitch = ((*(f32 *) (o + 0x18) + (f32) *(s16 *) (p + 0x224)) - P38_F32(0x18)) * 0.18f;
            range = func_1505A72C((struct127 *) o, obj);
            func_15059B54(obj, 0x300);
            if (P38_U8(0x102) != 0 && range < P38_F32(0x3C) * 16.0f) {
                if (pitch > 90.0f) {
                    pitch = 90.0f;
                } else if (pitch < -90.0f) {
                    pitch = -90.0f;
                }
                P38_F32(0x20) = P38_F32(0x20) + (pitch - P38_F32(0x20)) * 0.18f;
            }
        }
    }
    if (P38_U8(0x82) >= 9) {
        P38_U8(0x82)--;
    }
    if (P38_U8(0x103) != 0) {
        func_15059C84(obj);
    }

    switch (kind) {
    case 2:
    case 12:
    case 18:
        if (P38_F32(0x3C) != 0.0f) {
            P38_F32(0xB8) += 15.0f * (f32) D_800BE9E4;
            if (func_100107F8(obj) == 0) {
                func_10010154(func_151EFDD0() % 2 + 0x22F, obj, 0x7530, 0x1F4, 0x3E8);
            }
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 9:
    case 10:
    case 11:
    case 13:
    case 15:
    case 17:
        P38_F32(0xB8) = -func_150484A0(P38_F32(0x20), P38_F32(0x3C)) * 57.295776f;
        switch (kind) {
        case 4:
        case 5:
        case 9:
        case 10:
        case 13:
            if (P38_U8(0xA8) < 25) {
                P38_U8(0xA8) += D_800BE9E4;
            } else if (func_100107F8(obj) == 0) {
                func_10010154((u32) func_150ADA20() % 3 + 0x2EE, obj, 0x7530, 0x1F4, 0x3E8);
            }
            break;
        case 3:
        case 6:
        case 11:
        case 17:
            if (func_1505DDA8(obj, P38_U8(0x124), 0x200, 15.0f) != -1 && P38_U8(0xA9) == 0) {
                func_10010154((func_150ADA20() & 3) + 0x43E, obj, 0x7530, 0x7D0, 0x834);
                P38_U8(0xA9) = 1;
            }
            break;
        }
        break;
    }

    P38_U8(0x104) = 1;
    if (P38_U8(0x103) != 0) {
        func_1505A770(obj);
    }
    D_800CC674[0] = P38_F32(0x14);
    D_800CC674[1] = P38_F32(0x18);
    D_800CC674[2] = P38_F32(0x1C);
    startY = P38_F32(0x18);
    func_15058898(obj, P38_F32(0x30));
    func_1505B5F8(obj, P38_F32(0x180));

    if (hitTest != 0) {
        dir3[0] = P38_F32(0x14) - P38_F32(0x2C);
        dir3[1] = P38_F32(0x18) - P38_F32(0x30);
        dir3[2] = P38_F32(0x1C) - P38_F32(0x34);
        len = sqrtf(dir3[0] * dir3[0] + dir3[1] * dir3[1] + dir3[2] * dir3[2]);
        if (len == 0.0f) {
            inv = 0.0001f;
        } else {
            inv = 1.0f / len;
        }
        dir3[0] *= inv;
        dir3[1] *= inv;
        dir3[2] *= inv;
        func_15081A90(obj, P38_F32(0x2C), P38_F32(0x30), P38_F32(0x34), dir3[0], dir3[1], dir3[2],
                      *(u8 **) (p + 0x31C) + 0xB0, len, 0, 0, 0, -1, 0, 0);
        n = func_15082278(p, *(u8 **) (p + 0x31C) + 0xB0, kind);
        if (n != 0) {
            done = TRUE;
            if (n == 1 && P38_U8(0x124) > 0) {
                o = P38_OBJ(P38_U8(0x124) - 1);
                if (*(u8 **) (o + 0x31C) != NULL && (*(u8 **) (o + 0x31C))[0xAF] != 0 &&
                    func_10010894((struct127 *) o) == 0) {
                    func_15060A30((u32) func_150ADA20() % 3 + 0x53B, (struct127 *) o);
                }
            }
        }
    } else {
        if (P38_U8(0x103) != 0 && ((*(s32 *) (p + 0xF4) & 0x18000) || startY != P38_F32(0x18)) &&
            P38_F32(0x3C) > 0.0f) {
            P38_F32(0x3C) *= 0.5f;
            flags = 1;
            if (kind == 0 && P38_F32(0x3C) > 20.0f && (*(s32 *) (p + 0xF4) & 0x10000)) {
                n = (u32) func_150ADA20() % 9;
                func_15060778((n < 2) ? n + 0x18 : n + 0x29, obj, 0x7530, 0, 0x1F4, 0x5DC, 5);
                func_15174690(D_800C3E78, 0, 0x14, 0, 0x199, 4, 0xAA, 0xFF, 0);
            }
        }
        if (P38_U8(0xD0) != 0 && (n = func_1505C7D8(obj, D_800C3E78)) != 0) {
            D_800CC680 = n;
            P38_U8(0x89) = 1;
            flags |= 8;
            P38_F32(0x3C) *= 0.3f;
            if (kind == 15) {
                o = (u8 *) func_15083E90(6);
                if (o != NULL) {
                    if (*(u8 *) (o + 0x104) != 0) {
                        P38_U8(0x83) = 6;
                        *(s32 *) (p + 0xF8) |= 0x1000000;
                    }
                    P38_U16(0x76) = func_1505A630(*(f32 *) (o + 0x14) - P38_F32(0x14),
                                                  P38_F32(0x1C) - *(f32 *) (o + 0x1C), 0);
                    P38_F32(0x20) *= 0.4f;
                }
            } else {
                n = P38_U8(0x108) & 0x7F;
                if (n < 25) {
                    o = P38_OBJ(n);
                    P38_U16(0x76) = func_1505A630(P38_F32(0x2C) - *(f32 *) (o + 0x14),
                                                  *(f32 *) (o + 0x1C) - P38_F32(0x34), 0);
                }
                P38_F32(0x20) = 35.0f;
                P38_F32(0x24) = 6.0f;
            }
        }
        if (kind == 15) {
            func_1505A3A8(0.0f, obj, 1.0f, 1.0f, 0);
            func_1505D6F0(obj, D_800C3E78);
            if ((D_800CC268 >> 1) != 0) {
                o = (u8 *) func_15083E90(6);
                if (D_800CC268 & (1 << (((u8 *) o - (u8 *) D_800CC2D0) / 0x32C))) {
                    D_800D1580 = 0xFF0100A7;
                    func_1506E6FC();
                    if (o != NULL) {
                        P38_U16(0x76) = func_1505A630(P38_F32(0x14) - *(f32 *) (o + 0x14),
                                                      *(f32 *) (o + 0x1C) - P38_F32(0x1C), 0);
                    }
                    P38_F32(0x20) = 38.0f;
                    P38_F32(0x24) = 5.0f;
                    P38_F32(0x3C) = 40.0f;
                }
            }
        }
        if (P38_U8(0x103) != 0 && P38_F32(0x28) == 0.0f) {
            flags |= 2;
        }
        if (flags != 0) {
            if (kind == 17) {
                P38_U8(0x1CA) = 0;
            }
            if (D_800BE616 != 0) {
                P38_U8(0x1CA) = 0;
            }
        }
        P38_F32(0x40) = (f32) (P38_U16(0x76) + 0x4000) * 0.0054931640625f;
        if (P38_F32(0x28) == 0.0f) {
            P38_U8(0x7F)++;
            if (P38_U8(0x232) != 0) {
                P38_F32(0x18) = P38_F32(0x30);
                done = TRUE;
            }
        }
    }

    if (P38_U8(0x7F) >= 31) {
        done = TRUE;
    }
    if (--P38_U8(0x83) == 0) {
        done = TRUE;
    }
    if (P38_U8(0x1CA) == 0) {
        done = TRUE;
    }
    if (done) {
        switch (kind) {
        case 13:
            if (flags & 8) {
                func_150D7630(p + 0x14, 0xFF, 1);
            } else {
                vec[0] = D_800CC674[0] - P38_F32(0x2C);
                vec[1] = D_800CC674[1] - P38_F32(0x30);
                vec[2] = D_800CC674[2] - P38_F32(0x34);
                if (func_15145128(vec, vec, NULL, NULL) != 0) {
                    func_150D779C(0, (f32 *) (p + 0x14), vec, 0xFF, 1);
                }
            }
            func_15088BFC(obj);
            break;
        case 14:
            func_15088BFC(obj);
            break;
        }
        func_15060F28(obj, 1);
    } else {
        P38_U8(0x103) = 1;
    }
}
#undef P38_F32
#undef P38_U8
#undef P38_U16
#undef P38_OBJ
