#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A04D0[];
#endif


void func_150BF470(s32 arg0) {
}

#ifdef NON_MATCHING
void func_1516DF0C(s16, s16, s16, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, u8, s16, s16, s16, s16, u16, u8, u8, u8, u8, s16, u16, u16, u8, u8, u8, u8, u8, s32, u8, u8, u8, s32);

void func_150BF47C(s32 arg0) {
    s16 var_s0;
    s32 var_s1;

    var_s0 = 0x17C;
    var_s1 = 0;
    do {
        func_1516DF0C(0x1FDB, 0x25, var_s0, 0xD, 0, 0x50, 0x8F, 0, 0, 0, 0, 0, 8, 0xC8, 0xA, 0, 0, 0, 0, 0, 0x28, 0x28, 4, 0, 0, 0, 0, 0x555, 0x555, 0x555, 0x555, arg0 & 0xFFFF, 0x32, 0, 0xFF, 0x14, 0xFA0, 0x7D0, 1, 6, 0, 1, 0, 0, 0, 0, 3, 0xFF, 0);
        var_s1 += 1;
        var_s0 = -var_s0;
    } while (var_s1 != 2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150BF47C.s")
#endif
#ifdef NON_MATCHING
/* fade_slide_update: per-frame update of a fading, sliding element (no direct caller; reached through a table, returns
 * a done flag). The level +0x1F rises by +0x27 per tick (D_800BE9E4) up to +0x26 while +0x24 is set, else falls by
 * +0x2F per tick down to 0; when it is 0 and +0x24 clear the element is done (1). Otherwise the s16 position +0x14 /
 * +0x16 moves by the s8 speeds +0x2D / +0x2E per tick: once +0x14 is <= 0 both are zeroed and it is done (1), else
 * the counter +0x2C advances by the ticks (capped at 0x7F) and it goes on (0). */
s32 func_150BF5F4(u8 *e) {
    s32 on = e[0x24];
    s32 level = e[0x1F];
    s32 max = e[0x26];

    if (on != 0) {
        if (level != max) {
            level += D_800BE9E4 * e[0x27];
            if (max < level) {
                level = max;
            }
            e[0x1F] = level;
        }
        on = e[0x24];
    } else if (level != 0) {
        level -= D_800BE9E4 * e[0x2F];
        if (level < 0) {
            level = 0;
        }
        e[0x1F] = level;
        on = e[0x24];
    }
    if (on == 0 && level == 0) {
        return 1;
    }
    *(s16 *) (e + 0x14) += (s8) e[0x2D] * D_800BE9E4;
    *(s16 *) (e + 0x16) += (s8) e[0x2E] * D_800BE9E4;
    if (*(s16 *) (e + 0x14) <= 0) {
        *(s16 *) (e + 0x16) = 0;
        *(s16 *) (e + 0x14) = *(s16 *) (e + 0x16);
        return 1;
    }
    level = e[0x2C] + D_800BE9E4;
    if (level >= 0x80) {
        level = 0x7F;
    }
    e[0x2C] = level;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150BF5F4.s")
#endif

#ifdef NON_MATCHING
s32 func_151152A4(u8 *obj, s32 sound, s32 vol, s16 r0, s16 r1, s32 flags);
void func_15115484(s32 arg0, s32 arg1, s32 arg2);
void func_150A7DA0(u8 *mtx, s32 x, s32 y, s32 z);
void func_15043F6C(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);
void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);

// lift_platform_update: world-object callback (D_80089030[9][0], obj +0x38) of a lift that moves its model up to the
// target height +0x3C (s32). The current height is +0x7C, the speed +0x84; while D_800C35EA is set and D_800C3A08 is
// not 1 nothing moves (height 0 in the matrix, the bob is left alone). D_800BE9B4 snaps the height to the target.
// At the target: the bob phase +0x80 advances by 0.05, the bob amplitude is (height / 1500 + 1) * D_800BE9A4 (not
// below 0) and the move sound stops (func_151152A4 -1). Moving: the phase is reset, the speed accelerates by -5
// (down to -60) or +0.5 (up to 6, with the move sound 0xB9 looping); while the step is shorter than the remaining
// distance the height moves by speed * D_800BE9A4, +0x124 = speed * 0.4 (-10 below -25), +0xDC = 0x7D00, mode
// (+0x73 & 3) 2, the start sound when +0x74 is 0, and func_15115484 with the speed * 500; else it lands on the
// target (+0xDC = 0x80 when going down, +0x124 = 0, mode 3, sound stop). The offsets +0/+4/+8 ease (0.05, 0.2 while
// moving) toward the bob (amp * 3 sin(ph), amp * 4 sin(1.1 ph), amp * 3 cos(ph)); then the vertex list +0x28
// (+0x16 entries of 16 bytes) is transformed by translate(0, height, 0) * model(pos, scale +0x2C, angles +0x10)
// into the current buffer +0x20[D_800BE9C0].
void func_150BF71C(u8 *p) {
    f32 ease = 0.05f;
    f32 amp = 0.0f;
    f32 height = *(f32 *) (p + 0x7C);
    f32 dist;
    f32 speed;
    f32 amp3;
    f32 trans[4][4];
    f32 model[4][4];
    f32 x, y, z;
    s16 *src;
    s16 *dst;
    s32 i;
    s32 frozen;

    if (D_800C35EA == 0) {
        frozen = 0;
    } else if (D_800C3A08 != 1) {
        frozen = 1;
    } else {
        frozen = 0;
    }
    if (D_800BE9B4 != 0) {
        height = *(s32 *) (p + 0x3C);
        *(f32 *) (p + 0x7C) = height;
    }
    if (frozen) {
        height = 0.0f;
    } else {
        dist = (f32) *(s32 *) (p + 0x3C) - height;
        if (dist == 0.0f) {
            *(f32 *) (p + 0x84) = 0.0f;
            *(f32 *) (p + 0x80) += 0.05f;
            amp = (height / 1500.0f + 1.0f) * D_800BE9A4;
            if (amp < 0.0f) {
                amp = 0.0f;
            }
            func_151152A4(p, -1, 0x7D00, 0x1F4, 0x7D0, 0);
        } else {
            ease = 0.2f;
            *(f32 *) (p + 0x80) = 0.0f;
            speed = *(f32 *) (p + 0x84);
            if (dist < 0.0f) {
                if (-60.0f < speed) {
                    speed -= 5.0f;
                }
            } else {
                if (speed < 6.0f) {
                    speed += 0.5f;
                }
                func_151152A4(p, 0xB9, 0x7D00, 0x1F4, 0x7D0, 1);
            }
            *(f32 *) (p + 0x84) = speed;
            if (fabsf(speed) < fabsf(dist)) {
                height += speed * D_800BE9A4;
                if (speed < -25.0f) {
                    *(f32 *) (p + 0x124) = -10.0f;
                } else {
                    *(f32 *) (p + 0x124) = speed * 0.4f;
                }
                *(s32 *) (p + 0xDC) = 0x7D00;
                p[0x73] &= 0xFC;
                p[0x73] |= 2;
                if (*(u16 *) (p + 0x74) == 0) {
                    func_151152A4(p, 0xB9, 0x3E80, 0x3E8, 0xFA0, 0);
                }
                func_15115484((s32) p, 0x3E80, (s32) (speed * 500.0f));
            } else {
                height = *(s32 *) (p + 0x3C);
                if (speed < 0.0f) {
                    *(s32 *) (p + 0xDC) = 0x80;
                }
                *(f32 *) (p + 0x124) = 0.0f;
                p[0x73] &= 0xFC;
                p[0x73] |= 3;
                func_151152A4(p, -1, 0, 0, 0, 0);
            }
            *(f32 *) (p + 0x84) = speed;
            *(f32 *) (p + 0x7C) = height;
        }
        amp3 = amp * 3.0f;
        *(f32 *) (p + 0x0) += (amp3 * sinf(*(f32 *) (p + 0x80)) - *(f32 *) (p + 0x0)) * ease;
        *(f32 *) (p + 0x4) += (amp * 4.0f * sinf(*(f32 *) (p + 0x80) * 1.1f) - *(f32 *) (p + 0x4)) * ease;
        *(f32 *) (p + 0x8) += (amp3 * cosf(*(f32 *) (p + 0x80)) - *(f32 *) (p + 0x8)) * ease;
    }
    func_150A7DA0((u8 *) trans, 0, *(s32 *) &height, 0);
    func_15043F6C(model, *(f32 *) (p + 0x0), *(f32 *) (p + 0x4), *(f32 *) (p + 0x8), *(f32 *) (p + 0x2C),
                  *(f32 *) (p + 0x30), *(f32 *) (p + 0x34), *(s16 *) (p + 0x10), *(s16 *) (p + 0x12),
                  *(s16 *) (p + 0x14));
    func_150A7A48(trans, model, trans);
    dst = *(s16 **) (p + 0x20 + D_800BE9C0 * 4);
    src = *(s16 **) (p + 0x28);
    for (i = 0; i < *(u16 *) (p + 0x16); i++) {
        func_150A7E40(trans, src[i * 8 + 0], src[i * 8 + 1], src[i * 8 + 2], &x, &y, &z);
        dst[i * 8 + 0] = x;
        dst[i * 8 + 1] = y;
        dst[i * 8 + 2] = z;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150BF71C.s")
#endif

#ifdef NON_MATCHING
void func_1511BAA4(u8 *);
s32 func_15195FB0(u8 *, s32, s32, s32, s32, s32, s32);
s32 func_150829C0(s32, s32);

// door_lift_update: per-frame update of the object driven by object 0x14's animation (skipped while D_800C35EA is 1
// and D_800C3A08 is not). Runs func_1511BAA4, starts its looping sound D_800902B8 once (handle at +0x124), and takes
// the animation progress `ratio` = frame (+8) / (length (+0x18) - 2) of object 0x14's +0x2D0 (0 without the object).
// +0xA8 (a sway offset) is cleared, then by mode (+0x73 & 3): 2: sway -10 sin(ratio * pi * 4/3) up to ratio 0.75,
// spawning object 0x14 when missing, and its state +0x232 set to 2 (+0x218 = 0); 3: func_15060F28(obj, 0) once the
// animation ends (ratio >= 1); 0: sway 10 sin((ratio - 1) * 4pi/3) from ratio 0.25 and the same end call; 1: the same
// sway, spawning object 0x14 when missing. Mode 1's state-3 store is only reached when the spawn fails and then
// writes through NULL, as in the asm.
void func_150BFC60(u8 *p) {
    f32 ratio = 0.0f;
    u8 *obj;
    u8 *anim;
    s32 mode;
    s32 idx;

    if (D_800C35EA == 1 && D_800C3A08 != 1) {
        return;
    }
    func_1511BAA4(p);
    if (*(s32 *) (p + 0x124) == 0) {
        *(s32 *) (p + 0x124) = func_15195FB0(p, D_800902B8, 1, -1, 0, 0, -8);
    }
    obj = (u8 *) func_15083E90(0x14);
    mode = p[0x73] & 3;
    if (obj != NULL) {
        anim = *(u8 **) (obj + 0x2D0);
        ratio = *(f32 *) (anim + 8) / (*(f32 *) (anim + 0x18) - 2.0f);
    }
    *(f32 *) (p + 0xA8) = 0.0f;
    if (mode == 2) {
        if (ratio <= 0.75f) {
            *(f32 *) (p + 0xA8) = -sinf(ratio * 3.14159274f * 1.33333325f) * 10.0f;
        }
        if (obj == NULL) {
            idx = func_15083E0C(0x14);
            ((u8 *) D_800D20FC + idx * 48)[2] = 0;
            func_150829C0(idx, 0);
            obj = (u8 *) func_15083E90(0x14);
        }
        if (obj[0x232] != 2) {
            obj[0x232] = 2;
            *(s32 *) (obj + 0x218) = 0;
        }
    } else if (mode == 3) {
        if (obj != NULL && 1.0f <= ratio) {
            func_15060F28((struct127 *) obj, 0);
        }
    } else if (mode == 0) {
        if (0.25f <= ratio) {
            *(f32 *) (p + 0xA8) = sinf(ratio * 4.18878937f - 4.18878937f) * 10.0f;
        }
        if (obj != NULL && 1.0f <= ratio) {
            func_15060F28((struct127 *) obj, 0);
        }
    } else if (mode == 1) {
        if (0.25f <= ratio) {
            *(f32 *) (p + 0xA8) = sinf(ratio * 4.18878937f - 4.18878937f) * 10.0f;
        }
        if (obj == NULL) {
            idx = func_15083E0C(0x14);
            ((u8 *) D_800D20FC + idx * 48)[2] = 0;
            func_150829C0(idx, 0);
            obj = (u8 *) func_15083E90(0x14);
        }
        if (obj == NULL && obj[0x232] != 3) {
            obj[0x232] = 3;
            *(s32 *) (obj + 0x218) = 0;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150BFC60.s")
#endif

#ifdef NON_MATCHING
void func_1518BC20(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4);
u8 *func_1516547C(u8 kind, u8 view, u8 *data, u8 arg3, s32 arg4);
void func_1518D290(u8 *obj, s32 arg1, s32 arg2);
void func_1508F26C(s32 arg0, s32 arg1);
s32 func_151EFDD0(void);
extern u8 D_800BEE0B;

// sinking_platform_update: world-object callback (D_80089030[1] / [2], obj +0x38) of a platform that drops when stood
// on. kind = +0x3C >> 16: 0 drops 0x82 below its rest height at a speed falling from 16 near the bottom, with a
// start sound; 1 just follows the rest height + the offset +0x80; 2 drops 0x622 at 48 and, landed, marks itself and
// the next 0xA0-byte placement (+0x6E / +0x10E = 1, func_1508F26C(2, index)); 4 plays a sound when landed. The rest
// height (s16 +0x12 the first time) is kept in +0x7C with bit 31 set; the platform rests 0x50 below it. Mode
// (+0x73 & 3): 0 at rest (height = rest), stepping on it (+0x4F bit 4 with player D_800CC2D0's +0x31C->0x57 == 1)
// shakes the camera and rumbles (only in mode 0); 2 shakes (+0 / +8 random offsets) for the -(+0x80) ticks of
// D_800BE9E4, then sinks (offsets random / 12 for 40 ticks) to the bottom, where the rest height and +0x11C move
// down by the drop, mode 3; 3 sits at the low height until it is no longer stood on (+0x4F / +0x73 bit 4), then
// mode 1 rises by 3 per tick back to the rest height and mode 0.
void func_150BFF7C(u8 *p) {
    s32 kind = (*(s32 *) (p + 0x3C) >> 16) & 0xFFFF;
    s32 mode = p[0x73] & 3;
    s32 depth = 0;
    s32 step = 0x10;
    s32 top;
    s16 low;
    s16 bottom;
    s32 t;
    s32 h;
    structEU_151D8E18 rumble;

    if (kind == 0) {
        depth = 0x82;
    } else if (kind == 2) {
        depth = 0x622;
        step = 0x30;
    }
    if (*(s32 *) (p + 0x7C) == 0) {
        *(s32 *) (p + 0x7C) = *(s16 *) (p + 0x12) | 0x80000000;
    }
    top = (s16) *(s32 *) (p + 0x7C);
    low = top - 0x50;
    bottom = low - depth;
    if (kind == 1) {
        if (top - *(s16 *) (p + 0x12) != *(s32 *) (p + 0x80)) {
            *(s16 *) (p + 0x12) = top + *(s32 *) (p + 0x80);
        }
        return;
    }
    if ((p[0x4F] & 4) && (*(u8 **) ((u8 *) D_800CC2D0 + 0x31C))[0x57] == 1) {
        func_1518BC20(*(f32 *) ((u8 *) D_800CC2D0 + 0x14), *(f32 *) ((u8 *) D_800CC2D0 + 0x18),
                      *(f32 *) ((u8 *) D_800CC2D0 + 0x1C), 0xFF, 0);
        if (mode == 0) {
            func_1516547C(3, D_800BEE0B, NULL, 0xFF, 0);
            rumble.unk0 = 1;
            rumble.unk2 = 0x3C;
            rumble.unk5 = 1;
            rumble.unk4 = 8;
            rumble.unk6 = -1;
            func_151D8E18(&rumble, 0, 0xFF, 0);
        }
    }
    if (mode == 3) {
        if (low != *(s16 *) (p + 0x12)) {
            *(s16 *) (p + 0x12) = low;
        }
        if (!(p[0x4F] & 4) && !(p[0x73] & 4)) {
            mode = 1;
        }
    } else if (mode == 0) {
        if (top != *(s16 *) (p + 0x12)) {
            *(s16 *) (p + 0x12) = top;
        }
    } else if (mode == 2) {
        t = *(s32 *) (p + 0x80) + D_800BE9E4;
        *(s32 *) (p + 0x80) = t;
        if (t < 0) {
            *(f32 *) (p + 0x0) = ((f32) (func_151EFDD0() % 5) - 2.0f) * 0.125f;
            *(f32 *) (p + 0x8) = ((f32) (func_151EFDD0() % 5) - 2.0f) * 0.125f;
        } else {
            if (t < 0x28) {
                *(f32 *) (p + 0x0) = ((f32) (func_151EFDD0() % 5) - 2.0f) / 12.0f;
                *(f32 *) (p + 0x8) = ((f32) (func_151EFDD0() % 5) - 2.0f) / 12.0f;
            } else {
                *(f32 *) (p + 0x8) = 0.0f;
                *(f32 *) (p + 0x0) = 0.0f;
            }
            h = *(s16 *) (p + 0x12);
            if (h < low) {
                if (kind == 0) {
                    step = (h - bottom + 0x10) * step / depth;
                    if (*(s32 *) (p + 0x84) == 0) {
                        func_1518D290(p, 0xFF, 0);
                        *(s32 *) (p + 0x84) = 1;
                    }
                }
                *(s16 *) (p + 0x12) -= step;
                *(s32 *) (p + 0x120) = *(s16 *) (p + 0x12) - low;
            } else {
                *(s16 *) (p + 0x12) = h - step;
                *(s32 *) (p + 0x84) = 0;
            }
            if (bottom >= *(s16 *) (p + 0x12) || step == 0) {
                *(s16 *) (p + 0x12) = bottom;
                *(s32 *) (p + 0x7C) = (*(s32 *) (p + 0x7C) + (bottom - low)) | 0x80000000;
                *(s32 *) (p + 0x11C) = (*(s32 *) (p + 0x11C) + (bottom - low)) | 0x80000000;
                *(s32 *) (p + 0x80) = 0;
                *(s32 *) (p + 0x120) = 0;
                if (kind == 4) {
                    func_1518D290(p, 0xFF, 0);
                }
                *(f32 *) (p + 0x8) = 0.0f;
                *(f32 *) (p + 0x0) = 0.0f;
                mode = 3;
                if (kind == 2) {
                    p[0x6E] = 1;
                    p[0x10E] = 1;
                    func_1508F26C(2, (u16) ((p - (u8 *) D_800DBEF4) / 0xA0));
                    func_1508F26C(2, (u16) ((p - (u8 *) D_800DBEF4 + 0xA0) / 0xA0));
                }
            }
        }
    } else if (mode == 1) {
        *(s16 *) (p + 0x12) += 3;
        if (*(s16 *) (p + 0x12) >= top) {
            *(s16 *) (p + 0x12) = top;
            mode = 0;
        }
    }
    p[0x73] &= 0xFC;
    p[0x73] |= mode;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150BFF7C.s")
#endif

#ifdef NON_MATCHING
s32 func_15136C3C(u8 *, s32, s32, s32, s32, s32, s32, s32);
void func_15153BA4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

/* func_15153BA4 effect request (0x6C bytes; fields named by offset) */
typedef struct {
    /* 0x00 */ s16 u00;
    /* 0x02 */ s16 u02;
    /* 0x04 */ u8  u04;
    /* 0x06 */ s16 u06;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ s16 u10;
    /* 0x12 */ s16 u12;
    /* 0x14 */ s32 u14;
    /* 0x18 */ s32 u18;
    /* 0x1C */ u8  rgba0[4];
    /* 0x20 */ u8  rgba1[4];
    /* 0x24 */ u8  rgba2[2];
    /* 0x26 */ s16 u26;
    /* 0x28 */ s16 u28;
    /* 0x2A */ s16 u2A;
    /* 0x2C */ f32 u2C;
    /* 0x30 */ f32 u30;
    /* 0x34 */ f32 u34;
    /* 0x38 */ f32 pos[3];
    /* 0x44 */ s16 u44;
    /* 0x46 */ s16 u46;
    /* 0x48 */ s16 u48;
    /* 0x4A */ s16 u4A;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ f32 u50;
    /* 0x54 */ f32 u54;
    /* 0x58 */ f32 u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8  u60;
    /* 0x61 */ s8  u61;
    /* 0x62 */ u8  u62;
    /* 0x63 */ u8  u63;
    /* 0x64 */ u8  u64;
    /* 0x68 */ f32 u68;
} PuffRequest;

/* object_land_puff: func_1507D754 callee: func_15136C3C(obj, 0, 0, 1, 0, 0, 0xFF, 1), then one func_15153BA4
 * effect (constant request: model 0x11 / 7, colours 4E 54 7B FF / A4 A1 C8 9B / 64 FF, flags 0x40040E07) 35 above
 * the point 70 over the object's floor height (+0x180) at its x / z. */
void func_150C04E0(u8 *obj) {
    PuffRequest req;
    f32 pos[3];

    pos[0] = *(f32 *) (obj + 0x14);
    pos[1] = *(f32 *) (obj + 0x180) + 70.0f;
    pos[2] = *(f32 *) (obj + 0x1C);
    func_15136C3C(obj, 0, 0, 1, 0, 0, 0xFF, 1);
    req.u00 = 0x11;
    req.u02 = 7;
    req.u04 = 0x6C;
    req.u06 = 0x5103;
    req.u08 = 0x200005;
    req.u0C = 0;
    req.u10 = 0x28;
    req.u12 = 0x14;
    req.u14 = 0;
    req.u18 = 0;
    req.rgba0[0] = 0x4E;
    req.rgba0[1] = 0x54;
    req.rgba0[2] = 0x7B;
    req.rgba0[3] = 0xFF;
    req.rgba1[0] = 0xA4;
    req.rgba1[1] = 0xA1;
    req.rgba1[2] = 0xC8;
    req.rgba1[3] = 0x9B;
    req.rgba2[0] = 0x64;
    req.rgba2[1] = 0xFF;
    req.u26 = 0x1E;
    req.u28 = 8;
    req.u2A = 0x1E;
    req.u2C = 1.02f;
    req.u30 = 451.0f;
    req.u34 = 501.0f;
    req.pos[0] = pos[0];
    req.pos[1] = pos[1] + 35.0f;
    req.pos[2] = pos[2];
    req.u44 = 0;
    req.u46 = -0x14;
    req.u48 = 0xFF;
    req.u4A = 0x1E;
    req.u4C = 15.0f;
    req.u50 = 39.0f;
    req.u54 = 0.354f;
    req.u58 = 0.62600005f;
    req.u5C = 0x40040E07;
    req.u60 = 0x10;
    req.u61 = -1;
    req.u62 = 8;
    req.u63 = 6;
    req.u64 = 1;
    req.u68 = 0.877551f;
    func_15153BA4((u8 *) &req, 0xFF, 0xFF, 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150C04E0.s")
#endif

#ifdef NON_MATCHING
void func_15153BA4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_800A04D4;

s32 func_150C06DC(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    struct {
        s16 u34;
        s16 u36;
        s8 u38;
        u8 pad39[0x1];
        s16 u3A;
        s32 u3C;
        s32 u40;
        s16 u44;
        s16 u46;
        s32 u48;
        s32 u4C;
        s8 u50;
        s8 u51;
        s8 u52;
        s8 u53;
        s8 u54;
        s8 u55;
        s8 u56;
        s8 u57;
        s8 u58;
        s8 u59;
        s16 u5A;
        s16 u5C;
        s16 u5E;
        f32 u60;
        f32 u64;
        f32 u68;
        s32 u6C;
        u8 pad70[0x8];
        s16 u78;
        s16 u7A;
        s16 u7C;
        s16 u7E;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        s32 u90;
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s8 u98;
        u8 pad99[0x3];
        f32 u9C;
        s32 uA0;
        s32 uA4;
        s32 uA8;
        s32 uAC;
        s32 uB0;
        u8 padB4[0x8];
        s16 uBC;
        s16 uBE;
        s16 uC0;
        s16 uC2;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        s16 uD4;
        s16 uD6;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        s32 uE4;
        f32 uE8;
        f32 uEC;
    } sp;

    sp.uE4 = (*(s32 *)((u8 *)arg0 + 0x38));
    sp.uE8 = arg4 + 20.0f;
    sp.uEC = (*(f32 *)((u8 *)arg0 + 0x40));
    sp.uA4 = *((u8 *)&D_800A04D0);
    sp.uA0 = D_800A04D4;
    sp.uA8 = 5;
    sp.uAC = 4;
    (*(s32 *)((u8 *)(&sp.uB0) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.uE4) + 0));
    (*(s32 *)((u8 *)(&sp.uB0) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uE4) + 4));
    (*(s32 *)((u8 *)(&sp.uB0) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uE4) + 8));
    sp.uC4 = 12.0f;
    sp.uC8 = 8.0f;
    sp.uBC = 0;
    sp.uBE = 0xFF;
    sp.uC0 = -0x40;
    sp.uC2 = 0x22;
    sp.uD4 = 0x1E;
    sp.uD6 = 0xF;
    sp.uCC = -1.697f;
    sp.uD0 = 0.499f;
    sp.uD8 = 0.8f;
    sp.uDC = 1.2f;
    sp.uE0 = 15.299001f;
    func_15152700(&sp.uA8, &sp.uA4, &sp.uA0, 1, 0.0f, 1U, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
    sp.u36 = 8;
    sp.u34 = 5;
    sp.u38 = 0x6C;
    sp.u3A = 0x5103;
    sp.u3C = 0x200005;
    sp.u44 = 0x1E;
    sp.u46 = 0xF;
    sp.u53 = 0xFF;
    sp.u50 = 0x4E;
    sp.u51 = 0x54;
    sp.u54 = 0xA4;
    sp.u40 = 0;
    sp.u48 = 0;
    sp.u4C = 0;
    sp.u52 = 0x7B;
    sp.u55 = 0xA1;
    sp.u56 = 0xC8;
    sp.u57 = 0x64;
    sp.u58 = 0x9B;
    sp.u59 = 0xFF;
    sp.u5A = 0xE;
    sp.u5C = 0x12;
    sp.u5E = 0xE;
    sp.u60 = 1.046154f;
    sp.u64 = 218.0f;
    sp.u68 = 305.0f;
    (*(s32 *)((u8 *)(&sp.u6C) + 0)) = (s32) (*(s32 *)((u8 *)(&sp.uE4) + 0));
    (*(s32 *)((u8 *)(&sp.u6C) + 4)) = (s32) (*(s32 *)((u8 *)(&sp.uE4) + 4));
    (*(s32 *)((u8 *)(&sp.u6C) + 8)) = (s32) (*(s32 *)((u8 *)(&sp.uE4) + 8));
    sp.u78 = 0;
    sp.u7A = -0x28;
    sp.u7C = 0xFF;
    sp.u7E = 0x28;
    sp.u88 = 0.26200002f;
    sp.u8C = 0.26200002f;
    sp.u90 = 0x840E07;
    sp.u94 = 0x10;
    sp.u95 = -1;
    sp.u96 = 8;
    sp.u97 = 6;
    sp.u98 = 1;
    sp.u80 = 19.0f;
    sp.u84 = 8.0f;
    sp.u9C = 0.897767f;
    func_15153BA4(&sp.u34, 0xFF, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150C06DC.s")
#endif
#ifdef NON_MATCHING
s32 func_15150970(s32 *, s16 *, u8, s32);
extern s32 D_800A04D8;

void func_150C04C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    struct {
        f32 u20;
        s32 u24;
        s32 u28;
        s16 u2C;
        s16 u2E;
        s16 u30;
        s16 u32;
        s32 u34;
        s32 u38;
        s32 u3C;
        u8 pad40[0x8];
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        s16 u58;
        s16 u5A;
        f32 u5C;
        f32 u60;
        f32 u64;
        s32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        s32 * u7C;
        s32 * u80;
        s32 u84;
        f32 u88;
        s8 u8C;
        s8 u8D;
        u8 pad8E[0x2];
        s32 u90;
        f32 * u94;
    } sp;
    s8 var_v0;

    sp.u24 = D_800A04D8;
    sp.u28 = arg2;
    sp.u34 = 9;
    sp.u38 = 4;
    sp.u20 = 0.65000004f;
    (*(s32 *)((u8 *)(&sp.u3C) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u3C) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u3C) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u48 = 4.0f;
    sp.u4C = 7.0f;
    sp.u50 = -1.2800001f;
    sp.u54 = 0.33600003f;
    sp.u5C = 0.6f;
    sp.u60 = 0.45000002f;
    sp.u58 = 0x50;
    sp.u5A = 0x3C;
    sp.u68 = arg1;
    sp.u7C = &sp.u28;
    sp.u80 = &sp.u24;
    sp.u84 = 1;
    sp.u64 = 17.077002f;
    sp.u6C = 0.75200003f;
    sp.u70 = 0.20400001f;
    sp.u74 = 0.164f;
    sp.u78 = 10.0f;
    sp.u88 = 78.0f;
    if (arg3 & 0xFF) {
        var_v0 = 1;
    } else {
        var_v0 = 0;
    }
    sp.u8C = var_v0;
    sp.u8D = 0xE;
    sp.u90 = 4;
    sp.u94 = &sp.u20;
    sp.u2C = 0;
    sp.u2E = 0xFF;
    sp.u30 = -0x32;
    sp.u32 = 0x23;
    func_15150970(&sp.u34, &sp.u2C, arg4, arg5);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150C04C0.s")
#endif
#ifdef NON_MATCHING
s32 func_15134108(u8 *, f32, f32, f32, f32, s32); /* P95: f32 (float bits were passed as an int) */
void func_15153BA4(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_800A04DC;

s32 func_150C0B48(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    struct {
        s16 u34;
        s16 u36;
        s8 u38;
        u8 pad39[0x1];
        s16 u3A;
        s32 u3C;
        s32 u40;
        s16 u44;
        s16 u46;
        s32 u48;
        s32 u4C;
        s8 u50;
        s8 u51;
        s8 u52;
        s8 u53;
        s8 u54;
        s8 u55;
        s8 u56;
        s8 u57;
        s8 u58;
        s8 u59;
        s16 u5A;
        s16 u5C;
        s16 u5E;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s16 u78;
        s16 u7A;
        s16 u7C;
        s16 u7E;
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        s32 u90;
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        s8 u98;
        u8 pad99[0x3];
        f32 u9C;
        s32 uA0;
        s32 uA4;
        s16 uA8;
        s16 uAA;
        s16 uAC;
        s16 uAE;
        s32 uB0;
        s32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        s16 uD4;
        s16 uD6;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        u8 * uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        s32 * uF8;
        s32 * uFC;
        s32 u100;
        f32 u104;
        s8 u108;
        s8 u109;
        u8 pad10A[0x2];
        s32 u10C;
        s32 u110;
    } sp;
    f32 sp2C;
    f32 temp_f2;
    s8 var_v0;

    if (func_150ADA68() < (*(f32 *)((u8 *)arg0 + 0x170))) {
        sp.uA0 = D_800A04DC;
        sp.uB0 = 2;
        sp.uB4 = 0;
        temp_f2 = arg4 + 20.0f;
        sp.uA4 = (s32) (*(u16 *)((u8 *)arg0 + 0x66));
        sp.uBC = temp_f2;
        sp.uB8 = (*(f32 *)((u8 *)arg0 + 0x38));
        sp.uC0 = (*(f32 *)((u8 *)arg0 + 0x40));
        sp.uD4 = 0x28;
        sp.uD6 = 0x1E;
        sp.uC4 = 5.0f;
        sp.uC8 = 4.0f;
        sp.uCC = -1.21f;
        sp.uD0 = 0.47200003f;
        sp.uD8 = (*(f32 *)((u8 *)arg0 + 0x18)) * 0.36f;
        sp.uE4 = arg0 + 0x110;
        sp.uEC = 0.0f;
        sp.uF0 = 0.0f;
        sp.uF8 = &sp.uA4;
        sp.uFC = &sp.uA0;
        sp.uDC = (*(f32 *)((u8 *)arg0 + 0x18)) * 0.41300002f;
        sp.u100 = 1;
        sp.u104 = 0.0f;
        sp.uE0 = 31.527002f;
        sp.uE8 = 1.0f;
        sp.uF4 = 10.0f;
        if ((*(s32 *)((u8 *)arg0 + 0x60)) & 0x800) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        sp.u108 = var_v0;
        sp.u109 = 0xA;
        sp.u10C = 0;
        sp.u110 = 0;
        sp.uA8 = 0;
        sp.uAA = 0xFF;
        sp.uAC = -0x2A;
        sp.uAE = 0x19;
        sp2C = temp_f2;
        func_15150970(&sp.uB0, &sp.uA8, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
        sp.u34 = 1;
        sp.u36 = 2;
        sp.u38 = 0x6C;
        sp.u3A = 0x5103;
        sp.u3C = 0x200005;
        sp.u44 = 0x1E;
        sp.u46 = 0x10;
        sp.u53 = 0xFF;
        sp.u50 = 0x4E;
        sp.u51 = 0x54;
        sp.u40 = 0;
        sp.u48 = 0;
        sp.u4C = 0;
        sp.u52 = 0x7B;
        sp.u54 = 0xA4;
        sp.u55 = 0xA1;
        sp.u56 = 0xC8;
        sp.u57 = 0xC8;
        sp.u58 = 0x37;
        sp.u59 = 0xFF;
        sp.u5A = 0x14;
        sp.u5C = 0xC;
        sp.u5E = 0x14;
        sp.u60 = 1.024462f;
        sp.u64 = 178.0f;
        sp.u68 = 91.0f;
        sp.u70 = sp2C;
        sp.u6C = (*(f32 *)((u8 *)arg0 + 0x38));
        sp.u78 = 0;
        sp.u7A = -0x12;
        sp.u7C = 0xFF;
        sp.u7E = 0xB;
        sp.u90 = 0x40040E07;
        sp.u94 = 0x10;
        sp.u95 = -1;
        sp.u96 = 8;
        sp.u97 = 6;
        sp.u98 = 1;
        sp.u74 = (*(f32 *)((u8 *)arg0 + 0x40));
        sp.u80 = 4.0f;
        sp.u84 = 6.0f;
        sp.u88 = 0.006f;
        sp.u8C = 0.0f;
        sp.u9C = 0.9536f;
        func_15153BA4(&sp.u34, 0xFF, (*(u8 *)((u8 *)arg0 + 0xC)), (*(u8 *)((u8 *)arg0 + 1)));
        return 0;
    }
    return func_15134108(arg0, *(f32 *)&arg1, *(f32 *)&arg2, *(f32 *)&arg3, arg4, arg5); /* P95: f32 (float bits were passed as an int) */
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_ECC80/func_150C0B48.s")
#endif