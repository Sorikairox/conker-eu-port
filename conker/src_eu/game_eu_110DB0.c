#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_150E35A0(s32, s32, s32, s32, s32, s32, s32, f32, s32, f32, f32, f32, s32, s16);


#ifdef NON_MATCHING
extern f32 D_800A1400;
s32 func_150E35A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, s32 arg8, f32 arg9, f32 argA, f32 argB, s32 argC, s16 argD) {
    f32 temp_f0;
    s32 *var_v1;
    s8 var_a1;
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x27, 0, 0x80, 1, 0xFFU, 1U);
    if (temp_v0 == NULL) {
        return 0;
    }
    (*(f32 *)((u8 *)temp_v0 + 0x4C)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x50)) = 0.0f;
    (*(s32 *)((u8 *)temp_v0 + 0x6C)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x70)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x71)) = 0;
    (*(s32 *)((u8 *)temp_v0 + 0x74)) = 0;
    (*(f32 *)((u8 *)temp_v0 + 0x54)) = D_800A1400;
    var_v1 = D_800D99D0;
    var_a1 = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x7C)) = argD;
    (*(s32 *)((u8 *)temp_v0 + 0x78)) = argC;
    (*(f32 *)((u8 *)temp_v0 + 0x10)) = (f32) arg0;
    temp_f0 = (f32) arg1;
    (*(f32 *)((u8 *)temp_v0 + 0x14)) = temp_f0;
    (*(f32 *)((u8 *)temp_v0 + 0x18)) = (f32) arg2;
    (*(f32 *)((u8 *)temp_v0 + 0x1C)) = (f32) arg3;
    (*(f32 *)((u8 *)temp_v0 + 0x20)) = (f32) arg4;
    (*(f32 *)((u8 *)temp_v0 + 0x24)) = (f32) arg5;
    (*(f32 *)((u8 *)temp_v0 + 0x28)) = arg9;
    (*(f32 *)((u8 *)temp_v0 + 0x2C)) = argA;
    (*(f32 *)((u8 *)temp_v0 + 0x30)) = argB;
    (*(f32 *)((u8 *)temp_v0 + 0x38)) = temp_f0;
    (*(f32 *)((u8 *)temp_v0 + 0x34)) = arg7;
    (*(s32 *)((u8 *)temp_v0 + 0x3C)) = arg8;
    (*(s32 *)((u8 *)temp_v0 + 0x44)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x4A)) = 0;
    (*(s32 *)((u8 *)temp_v0 + 0x40)) = arg6;
loop_3:
    if ((*(s32 *)((u8 *)var_v1 + 0)) == 0) {
        (*(s32 *)((u8 *)var_v1 + 0)) = (s32) temp_v0;
        (*(s8 *)((u8 *)temp_v0 + 0x48)) = var_a1;
    } else if (var_v1[1] == 0) {
        var_v1[1] = (s32) temp_v0;
        (*(s8 *)((u8 *)temp_v0 + 0x48)) = (s8) (var_a1 + 1);
    } else if (var_v1[2] == 0) {
        var_v1[2] = (s32) temp_v0;
        (*(s8 *)((u8 *)temp_v0 + 0x48)) = (s8) (var_a1 + 2);
    } else if (var_v1[3] == 0) {
        var_v1[3] = (s32) temp_v0;
        (*(s8 *)((u8 *)temp_v0 + 0x48)) = (s8) (var_a1 + 3);
    } else {
        var_a1 += 4;
        var_v1 = (s32 *)((u8 *)var_v1 + (0x10));
        if (var_a1 == 8) {
            (*(s8 *)((u8 *)temp_v0 + 0x48)) = 0;
        } else {
            goto loop_3;
        }
    }
    return (s32) temp_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E35A0.s")
#endif
s32 func_150AD9A0(s32, s32, s32);

s32 func_150E3788(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 temp_v0;

    temp_v0 = func_150E35A0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, (f32) func_150AD9A0(arg0 - arg3, arg1 - arg4, arg2 - arg5) / (f32) arg7, 0, 0.0f, 0.0f, 0.0f, 0, -0x63);
    if (temp_v0 != 0) {
        return (*(u8 *)((u8 *)temp_v0 + 0x48)) + 1;
    }
    return 0;
}

s32 func_150E3850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5) {
    s32 temp_v0;

    temp_v0 = func_150E35A0(arg0, arg1, arg2, 0, 0, 0, arg4, arg5, arg3, 0.0f, 0.0f, 0.0f, 0, -0x63);
    if (temp_v0 != 0) {
        return (*(u8 *)((u8 *)temp_v0 + 0x48)) + 1;
    }
    return 0;
}


void func_150E38C0(u8 *arg0, u8 *arg1, s32 arg2, s16 arg3) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;

    temp_a0 = (*(s32 *)arg1);
    temp_a1 = (*(s32 *)((u8 *)arg1 + 4));
    temp_a2 = (*(s32 *)((u8 *)arg1 + 8));
    func_150E35A0(temp_a0, temp_a1, temp_a2, temp_a0, temp_a1, temp_a2, 0x1A, 10.0f, 0, (*(f32 *)arg0), (*(f32 *)((u8 *)arg0 + 4)), (*(f32 *)((u8 *)arg0 + 8)), arg2, (s32) arg3);
}

#ifdef NON_MATCHING
void func_1000E7A0(u32, s32);
/*
 * sound_handle_release_cb: P190. Callback that func_150E3994 passes to func_1000FA64: 1 while the handle *handle is
 * 0, else releases it (func_1000E7A0(2, handle)) and returns 0.
 */
s32 func_150E394C(s32 arg0, s32 arg1, s32 *handle, s32 arg3) {
    if (*handle == 0) {
        return 1;
    }
    func_1000E7A0(2, *handle);
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E394C.s")

extern s32 func_150E394C;
#endif

s32 func_150E3994(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8) {
    s32 temp_v0;
    s32 sp44;

    temp_v0 = func_150E35A0(arg3, arg4, arg5, 0, 0, 0, arg7, arg8, arg6, (f32) arg0, (f32) arg1, (f32) arg2, 0, -0x63);
    if (temp_v0 != 0) {
        sp44 = temp_v0;
        (*(u16 *)((u8 *)sp44 + 0x4A)) = func_1000FA64(0x2D0U, (s16) arg0, (s16) arg1, (s16) arg2, 0x5DC0, 0x1770U, 0x3E8, (s32) &func_150E394C, NULL, 0, 0, 0);
        return (*(u8 *)((u8 *)sp44 + 0x48)) + 1;
    }
    return 0;
}

void func_150E3A94(struct102 *arg0) {
    s32 idx;
    s32 *p;

    idx = *(u8 *)((u8 *)arg0 + 0x48);
    if (idx >= 0) {
        p = &D_800D99D0[idx];
        if ((s32)arg0 == *p) {
            *p = 0;
        }
    }
    if (*(u16 *)((u8 *)arg0 + 0x4A) != 0) {
        func_100111C8(*(u16 *)((u8 *)arg0 + 0x4A));
        *(u16 *)((u8 *)arg0 + 0x4A) = 0;
        func_10010F88(0x2D7, 0x5DC0, 0, 0, 0, (s16)(s32)*(f32 *)((u8 *)arg0 + 0x28), (s16)(s32)*(f32 *)((u8 *)arg0 + 0x2C), (s16)(s32)*(f32 *)((u8 *)arg0 + 0x30), 0x3E8, 0x1770);
    }
    func_1516972C(arg0);
}

void func_150E3B5C(s32 arg0) {
    s32 i;
    arg0 = arg0 - 1;
    for (i = 0; i < 2; i++) {
        struct_eu_node *node = D_800DD280[i][0x27];
        D_800DD5C0++;
        while (node != NULL) {
            D_800DD5C8[D_800DD5C0] = node->next;
            if (arg0 == -1 || arg0 == ((u8 *)node)[0x48]) {
                func_150E3A94(node);
            }
            node = D_800DD5C8[D_800DD5C0];
        }
        D_800DD5C0--;
    }
}

void func_150E3C3C(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 temp_v0;
    arg0 = arg0 - 1;
    if ((arg0 >= 0) && (arg0 < 8)) {
        temp_v0 = D_800D99D0[arg0];
        if ((temp_v0 != 0) && ((*(u8 *)((u8 *)temp_v0 + 0)) == 0x27)) {
            *arg1 = (s32) (*(f32 *)((u8 *)temp_v0 + 0x10));
            *arg2 = (s32) (*(f32 *)((u8 *)temp_v0 + 0x14));
            *arg3 = (s32) (*(f32 *)((u8 *)temp_v0 + 0x18));
        }
    }
}

#ifdef NON_MATCHING
extern f32 D_800A1404;
extern f32 D_800A1408;
extern f32 D_800A140C;
extern f32 D_800A1410;
extern f32 D_800A1414;
extern f32 D_800A1418;
extern f32 D_800A141C;
void func_15143874(s16, f32, f32 *, f32 *);
s32 func_15046F70(f32 *, s32, f32, f32 *);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
s32 func_151C284C(f32 *, s32, s32, s32, u8, void *, f32, f32, f32, f32, f32, u8, s32, u8, u8, u8, u8, u8, u8, s8, s32,
                  f32, u8, s8, s32, u8, s32);
void func_151037D4(s16, u8, f32, u8 *, u8, u8, s32);

typedef struct {
    u8 b[0x12];
} ZapStyle; /* 0x12 bytes copied from the bolt object (+0x58) into the beam request */

// zap_bolt_update: per-frame update of a type-0x27 lightning bolt object `obj` (made by func_150E35A0). Counts down
// its life (+0x7C, -0x63 = forever; func_150E3A94 frees it at < 0 but the update goes on), aims at the followed object
// (+0x3C, its +0x14 position; freed when that object's first word is 0) or the path point (+0x78), and moves its head
// (+0x10) by speed (+0x34) * D_800BE9E4 frames toward the target (+0x1C). When it arrives (no path), a followed
// target makes it shoot 500 lengths further for 25 frames (+0x44); otherwise it is freed. The +0x4C accumulator then
// spawns beam segments from the anchor (+0x28) to a random point near the head (func_151C284C, ground snapped with
// func_15046F70 and shortened by a random amount), and without a path the +0x50 accumulator spawns sparks
// (func_151037D4) at the anchor.
void func_150E3CB8(u8 *obj) {
    f32 *pos = (f32 *) (obj + 0x10);
    f32 *target = (f32 *) (obj + 0x1C);
    f32 *anchor = (f32 *) (obj + 0x28);
    struct {
        s32 u00;
        f32 len;        /* +0x04 */
        f32 end[3];     /* +0x08 */
        f32 end2[3];    /* +0x14 */
        f32 end3[3];    /* +0x20 */
        f32 start[3];   /* +0x2C */
        f32 dir[3];     /* +0x38 */
        ZapStyle style; /* +0x44 */
        s16 u56;
        u8 u58;
        u8 u59;
        u8 u5A;
        s32 owner;      /* +0x5C: +0x74 for kinds 2 / 3 */
        s32 u60;        /* +0x60: +0x6C */
    } seg;
    f32 old[3];
    f32 newPos[3];
    f32 delta[3];
    f32 vel[3];
    f32 start[3];
    f32 end[3];
    f32 tip[3];
    f32 dir[3];
    f32 len;
    f32 unused;
    f32 ox;
    f32 oz;
    f32 dist;
    f32 step;
    f32 k;
    f32 t;
    f32 a;
    f32 b;
    u32 r;
    u8 *follow;
    f32 *path;
    s32 hit = 0;
    s32 mode;

    if (*(s16 *) (obj + 0x7C) != -0x63) {
        *(s16 *) (obj + 0x7C) -= D_800BE9E4;
        if (*(s16 *) (obj + 0x7C) < 0) {
            func_150E3A94((struct102 *) obj);
        }
    }
    old[0] = pos[0];
    old[1] = pos[1];
    old[2] = pos[2];

    follow = *(u8 **) (obj + 0x3C);
    if (follow != NULL) {
        if (*(s32 *) follow == 0) {
            func_150E3A94((struct102 *) obj);
            return;
        }
        target[0] = *(f32 *) (follow + 0x14);
        target[1] = *(f32 *) (follow + 0x18);
        target[2] = *(f32 *) (follow + 0x1C);
    } else {
        path = *(f32 **) (obj + 0x78);
        if (path != NULL) {
            target[0] = path[0];
            target[1] = path[1];
            target[2] = path[2];
        }
    }
    delta[0] = target[0] - pos[0];
    delta[1] = target[1] - pos[1];
    delta[2] = target[2] - pos[2];
    dist = sqrtf(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);
    step = *(f32 *) (obj + 0x34) * (f32) D_800BE9E4;

    if (*(s32 *) (obj + 0x78) == 0) {
        if (*(s32 *) (obj + 0x44) == 0) {
            if (dist <= step) {
                if (*(s32 *) (obj + 0x3C) == 0) {
                    func_150E3A94((struct102 *) obj);
                    return;
                }
                *(s32 *) (obj + 0x44) = 25;
                *(s32 *) (obj + 0x3C) = 0;
                target[0] += delta[0] * 500.0f;
                target[1] += delta[1] * 500.0f;
                target[2] += delta[2] * 500.0f;
            }
        } else {
            *(s32 *) (obj + 0x44) -= D_800BE9E4;
            if (*(s32 *) (obj + 0x44) <= 0) {
                func_150E3A94((struct102 *) obj);
                return;
            }
        }
    }

    if (dist == 0.0f) {
        newPos[0] = target[0];
        newPos[1] = target[1];
        newPos[2] = target[2];
        vel[0] = delta[0];
        vel[1] = delta[1];
        vel[2] = delta[2];
    } else {
        k = step / dist;
        vel[0] = k * delta[0];
        vel[1] = k * delta[1];
        vel[2] = k * delta[2];
        newPos[0] = old[0] + vel[0];
        newPos[1] = old[1] + vel[1];
        newPos[2] = old[2] + vel[2];
    }
    pos[0] = newPos[0];
    pos[1] = newPos[1];
    pos[2] = newPos[2];

    *(f32 *) (obj + 0x4C) += (D_800A1404 + func_150ADA68() * D_800A1408) * D_800A140C * D_800BE9A4;
    while (1.0f < *(f32 *) (obj + 0x4C)) {
        start[0] = anchor[0];
        start[1] = anchor[1];
        start[2] = anchor[2];
        t = func_150ADA68();
        r = func_150ADA20();
        func_15143874((u8) r, func_150ADA68() * 129.0f, &ox, &oz);
        tip[0] = t * vel[0] + old[0] + ox;
        tip[1] = t * vel[1] + old[1] + 200.0f;
        tip[2] = t * vel[2] + old[2] + oz;
        end[0] = tip[0];
        end[1] = tip[1];
        end[2] = tip[2];
        if (func_15046F70(tip, 0, tip[1] - 1000.0f, (f32 *) (obj + 0x54))) {
            end[1] = *(f32 *) (obj + 0x54);
        }
        dir[0] = end[0] - start[0];
        dir[1] = end[1] - start[1];
        dir[2] = end[2] - start[2];
        if (func_15145128(dir, dir, &len, &unused)) {
            k = 190.0f * (func_150ADA68() * D_800BE9A4);
            start[0] += dir[0] * k;
            start[1] += dir[1] * k;
            start[2] += dir[2] * k;
            len -= k;
        }
        seg.u00 = 0;
        seg.len = len;
        seg.end[0] = end[0];
        seg.end[1] = end[1];
        seg.end[2] = end[2];
        seg.end2[0] = end[0];
        seg.end2[1] = end[1];
        seg.end2[2] = end[2];
        seg.end3[0] = end[0];
        seg.end3[1] = end[1];
        seg.end3[2] = end[2];
        seg.start[0] = start[0];
        seg.start[1] = start[1];
        seg.start[2] = start[2];
        seg.dir[0] = dir[0];
        seg.dir[1] = dir[1];
        seg.dir[2] = dir[2];
        seg.style = *(ZapStyle *) (obj + 0x58);
        seg.u56 = 0;
        seg.u58 = 0;
        seg.u59 = 1;
        seg.u5A = 0;
        if (obj[0x71] == 2 || obj[0x71] == 3) {
            seg.owner = *(s32 *) (obj + 0x74);
        } else {
            seg.owner = 0;
        }
        seg.u60 = *(s32 *) (obj + 0x6C);
        a = func_150ADA68();
        b = func_150ADA68();
        r = func_150ADA20();
        mode = (hit != 0 || *(s32 *) (obj + 0x78) != 0) ? 2 : 1;
        if (func_151C284C(start, 0, 0, 0, 0, &seg, 190.0f, D_800A1410, a * 50.0f + 10.0f, b * 191.0f + 160.0f, 80.0f,
                          r % 176U + 80, 0, 0, 0, 0, 0, 0, 1, mode, *(s32 *) (obj + 0x40), 0.0f, 0xFF, -1, 0, obj[0xC],
                          obj[1]) != 0) {
            hit = 1;
        }
        *(f32 *) (obj + 0x4C) -= 1.0f;
    }

    if (*(s32 *) (obj + 0x78) != 0) {
        return;
    }
    *(f32 *) (obj + 0x50) += (56.0f + func_150ADA68() * 235.0f) * D_800A1414 * D_800BE9A4;
    while (1.0f < *(f32 *) (obj + 0x50)) {
        u32 count = func_150ADA20();
        u32 alpha = func_150ADA20();
        func_151037D4((count & 3) + 6, alpha % 156U + 100, func_150ADA68() * D_800A141C + D_800A1418, anchor, 0xFF,
                      obj[0xC], obj[1]);
        *(f32 *) (obj + 0x50) -= 1.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_110DB0/func_150E3CB8.s")
#endif

extern f32 D_800A1420;

void func_150E4590(u8 *arg0) {
    u8 *temp_v0;

    temp_v0 = arg0 + 0x110;
    if ((*(s32 *)((u8 *)arg0 + 0x1B4)) != 0) {
        func_1505D1C4((*(f32 *)((u8 *)temp_v0 + 0x30)), (*(f32 *)((u8 *)temp_v0 + 0x34)), (*(f32 *)((u8 *)temp_v0 + 0x38)), (*(s32 *)((u8 *)temp_v0 + 0xA4)) | 0x60000, -1, (u16) ((((u32) (func_150484A0((*(f32 *)((u8 *)temp_v0 + 0x60)), (*(f32 *)((u8 *)temp_v0 + 0x64))) * D_800A1420) & 0xFFFF) - 0x4000) | 1), 0, 0);
    }
}

extern f32 D_800A1424;

void func_150E469C(s32 arg0) {
    func_151C40BC(arg0, 0.35200003f, 0.70100003f, 0.56600004f, D_800A1424, 0xFF, 0xFF, 0xFF);
}

s32 func_150E46F4(f32 *arg0) {
    arg0[0x2C / 4] += arg0[0x4C / 4] * D_800BE9A4;
    arg0[0x30 / 4] += arg0[0x54 / 4] * D_800BE9A4;
    return 1;
}
