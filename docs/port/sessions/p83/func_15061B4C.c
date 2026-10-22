/* Shared animation state of some object kinds (D_800CC298, 0x18 bytes). */
struct ObjAnimShared {
    /* 0x00 */ f32 scrollU;   /* kind 0x24: texture scroll, degrees */
    /* 0x04 */ f32 scrollV;
    /* 0x08 */ s8 jitter;     /* kind 0x24: random -2..2 */
    /* 0x09 */ s8 pulse;      /* kind 0x2C: 0..41 ping-pong */
    /* 0x0A */ s8 pulseStep;
    /* 0x0B */ u8 phase[4];   /* kind 0x3A: colour phases, stepped by the bytes of D_80086490 */
    /* 0x0F */ u8 frameTimer; /* kind 0x4B */
    /* 0x10 */ u8 glow;       /* kind 0x54: 0..255 */
};
#define OBJ_ANIM (*(struct ObjAnimShared *)&D_800CC298)

/* Per-frame texture / colour animation of the live objects (D_800CC2D0[], +0x2FA visible), by kind (+0x04).
 * Effects shared by every object of one kind (func_15062D10 texture scroll, func_15062E24, func_eu_1501B640
 * colours) run for the first such object only (done[]). */
void func_15061B4C(void) {
    u8 done[10];
    u8 *obj;
    u8 type;
    s32 i;
    s32 v;
    u8 steps[4];
    f32 colours[4];
    f32 glow;
    s32 **tex;

    bzero(done, sizeof(done));
    for (obj = (u8 *)D_800CC2D0; obj != (u8 *)&D_800D121C; obj += sizeof(struct127)) {
        if (*(s32 *)obj == 0 || obj[0x2FA] == 0) {
            continue;
        }
        type = obj[4];
        switch (type) {
            case 0x13:
                if (!done[0]) {
                    func_15062D10(type, 0x5E, 0, -1, 0, 0);
                    func_15062D10(type, 0x60, 0, -1, 0, 0);
                    func_15062D10(type, 0x62, 0, -1, 0, 0);
                    func_15062D10(type, 0x64, 0, -1, 0, 0);
                    done[0] = 1;
                }
                break;
            case 0x23:
                if (!done[1]) {
                    func_15062D10(type, 0x1E9, 0, -1, 0, 0);
                    func_15062D10(type, 0x1EB, 0, -1, 0, 0);
                    func_15062D10(type, 0x1ED, 0, -1, 0, 0);
                    func_15062D10(type, 0x1EF, 0, -1, 0, 0);
                    done[1] = 1;
                }
                break;
            case 0x24:
                if (!done[2]) {
                    if ((u32)func_150ADA20() % 1000 < 300) {
                        OBJ_ANIM.jitter = (u32)func_150ADA20() % 5 - 2;
                    }
                    func_15062D10(type, 4, -4, OBJ_ANIM.jitter, 0, 0);
                    tex = &((s32 **)&D_800C4440)[type];
                    if (*tex != NULL) {
                        func_15062E24(type, (*tex)[0], 0x37, 0, (s32)OBJ_ANIM.scrollV, 2, 1);
                        func_15062E24(type, (*tex)[1], 0x27, 0x37, (s32)OBJ_ANIM.scrollU, 1, 0);
                    }
                    OBJ_ANIM.scrollU += -4.0f * (f32)D_800BE9E4;
                    if (OBJ_ANIM.scrollU <= 0.0f) {
                        OBJ_ANIM.scrollU += 360.0f;
                    }
                    OBJ_ANIM.scrollV += -0.5f * (f32)D_800BE9E4;
                    if (OBJ_ANIM.scrollV <= 0.0f) {
                        OBJ_ANIM.scrollV += 360.0f;
                    }
                    done[2] = 1;
                }
                break;
            case 0x2C:
                if (!done[3]) {
                    v = OBJ_ANIM.pulse;
                    if (v > 40) {
                        OBJ_ANIM.pulseStep = -1;
                    } else if (v <= 0) {
                        OBJ_ANIM.pulseStep = 1;
                    }
                    OBJ_ANIM.pulse = v + OBJ_ANIM.pulseStep;
                    func_15062D10(type, 0xAA, OBJ_ANIM.pulse, 0, 0, 1);
                    done[3] = 1;
                }
                break;
            case 0x3A:
                if (!done[4]) {
                    *(s32 *)steps = D_80086490;
                    if (*(s32 *)(obj + 0x1D4) != 0) {
                        for (i = 0; i < 4; i++) {
                            colours[i] = (func_150489B0(OBJ_ANIM.phase[i]) + 1.0f) * 0.5f;
                            OBJ_ANIM.phase[i] += steps[i];
                        }
                        func_eu_1501B640((struct127 *)obj, colours, 1);
                        done[4] = 1;
                    }
                }
                break;
            case 0x3F:
                if (!done[5]) {
                    func_15062D10(type, 4, 0, -4, 0, 0);
                    done[5] = 1;
                }
                break;
            case 0x4B:
                if (!done[6]) {
                    done[6] = 1;
                    func_15062D10(type, 0x173, -4, 0, 0, 0);
                    func_15062D10(type, 0x175, -2, 0, 0, 0);
                    func_15062D10(type, 0x177, -1, 0, 0, 0);
                }
                /* frame +0x68 cycles 15, 16, 17, 18, 17, 16 (+0x69 = 0..5), one step every 4 ticks */
                if (OBJ_ANIM.frameTimer >= 4) {
                    OBJ_ANIM.frameTimer = 0;
                    if (obj[0x69] == 5) {
                        obj[0x69] = 0;
                    } else {
                        obj[0x69]++;
                    }
                    if (obj[0x69] >= 3) {
                        obj[0x68] = 5 - obj[0x69];
                    } else {
                        obj[0x68] = obj[0x69];
                    }
                    obj[0x68] += 15;
                } else {
                    OBJ_ANIM.frameTimer += D_800BE9E4;
                }
                break;
            case 0x45:
                v = obj[0x6D];
                obj[0x68] = (v >= 10) ? v - 10 : v * 2 + 6;
                break;
            case 0x5B:
                for (i = 0; i < 2; i++) {
                    v = obj[0x6C + i];
                    obj[0x68 + i] = (v >= 10) ? v - 10 : D_800997EC[v];
                }
                break;
            case 0x54:
                if (*(s32 *)(obj + 0x2EC) != 0) {
                    OBJ_ANIM.glow = (OBJ_ANIM.glow < 0xEB) ? OBJ_ANIM.glow + 20 : 0xFF;
                } else {
                    OBJ_ANIM.glow = (OBJ_ANIM.glow <= 20) ? 0 : OBJ_ANIM.glow - 20;
                }
                glow = OBJ_ANIM.glow * (1.0f / 255.0f);
                func_eu_1501B640((struct127 *)obj, &glow, 0);
                break;
            case 0x8A:
                if (D_800BE9F0 != 0x30) {
                    if (*(u16 *)(obj + 0x84) == 1) {
                        func_15062D10(type, 0x253, 0, 0x10, 0, 0);
                        func_15062D10(type, 0x255, 0, 8, 0, 0);
                        func_15062D10(type, 0x257, 0, 4, 0, 0);
                    }
                } else {
                    func_15062FC0(obj, 0, 0, 0x1000, 0x1000, 0xC, 0,
                                  (*(u16 *)(obj + 0x84) == 1) ? -D_800BE9E4 * 40 : 0);
                }
                break;
            case 0x42:
                v = *(u16 *)(obj + 0x84);
                if (v == 2 || v == 1) {
                    if (obj[0x68] == 0xD) {
                        obj[0x68] = 0xC;
                    }
                    if ((func_150ADA20() & 3) == 0) {
                        obj[0x68] = (obj[0x68] == 0x15) ? 0xC : 0x15;
                    }
                } else {
                    obj[0x68] = 0xD;
                }
                break;
            case 0x7B:
                func_eu_150F2230(obj);
                break;
            case 0x92:
                if (!done[9]) {
                    func_15062D10(type, 4, 0, -2, 0, 0);
                    func_15062D10(type, 0x13B, 0, -2, 0, 0);
                    func_15062D10(type, 0x20D, 0, -2, 0, 0);
                    done[9] = 1;
                }
                break;
            case 0x43:
                func_15062D10(type, 4, 0x14, 8, 0, 0);
                break;
        }
    }
}
