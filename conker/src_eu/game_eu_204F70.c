#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_151D8CC8(f32 *arg0, f32 *arg1, f32 arg2);
extern u8 D_800A4EA8[];
#endif

void func_151D7D78(u8 *);


struct260 *func_151D7760(s16 arg0, u8 arg1, u8 arg2, f32 arg3, u8 *arg4, u8 arg5, s32 arg6) {
    struct260 *temp_v0;
    struct {
        s32 unk0;
        u8 unk4;
        u8 unk5;
        u8 pad6[2];
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
    } tmp;

    tmp.unk0 = 0;
    tmp.unk4 = arg2;
    tmp.unk5 = 0;
    tmp.unk8 = 0.0f;
    tmp.unkC = 0.0f;
    tmp.unk10 = 0.0f;
    tmp.unk14 = arg3;
    temp_v0 = func_15149130(arg0, -1, 0x42, -1, arg1, 0x36, (struct37 *)(arg4 + 0x18), arg5, arg6);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x18);
    }
    return temp_v0;
}

#ifdef NON_MATCHING
/* P204 (from the s163 draft 7814_b.c) */
extern s32 (*D_80090040[])(u8 *);
f32 func_15143E64(struct17 *);
void func_151D7DE0(u8 *);
// effect_follow_update: per-frame handler (D_8008A980 table, void (u8 *)) of an effect-carrier object: remembers its
// position (+0x30) and flag +0x2D bit 0, then runs the kind's update D_80090040[+0x2C]; when that returns 0 the object
// is retired (+0xE = -1, +0xD bit 0). Otherwise, when bit 0 of +0x2D was set before and is still set and the object
// moved less than +0x3C this frame, an effect is attached by func_151D7DE0 if there is none yet (+0x28 == NULL);
// in every other case func_151D7D78 releases the attached effect.
void func_151D7814(u8 *obj) {
    f32 pos[3];
    u8 active;
    f32 d[3];

    pos[0] = *(f32 *) (obj + 0x30);
    pos[1] = *(f32 *) (obj + 0x34);
    pos[2] = *(f32 *) (obj + 0x38);
    active = obj[0x2D] & 1;
    if (D_80090040[obj[0x2C]](obj) == 0) {
        *(s16 *) (obj + 0xE) = -1;
        obj[0xD] |= 1;
        return;
    }
    if ((obj[0x2D] & 1) && active) {
        d[0] = *(f32 *) (obj + 0x30) - pos[0];
        d[1] = *(f32 *) (obj + 0x34) - pos[1];
        d[2] = *(f32 *) (obj + 0x38) - pos[2];
        if (func_15143E64((struct17 *) d) < *(f32 *) (obj + 0x3C)) {
            if (*(u8 **) (obj + 0x28) == NULL) {
                func_151D7DE0(obj);
            }
            return;
        }
    }
    func_151D7D78(obj);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7814.s")
#endif

extern void (*D_80090044[])(u8 *, s32, u8);
void func_151D7958(u8 *arg0, s32 arg1, u8 arg2)
{
  u8 *new_var;
  if (D_80090044[arg0[0x2C]] != 0)
  {
    new_var = &arg0[0x2C]; // fakematch: second index read must not be CSEd
    if (arg1)
    {
    }
    D_80090044[*new_var](arg0, arg1, arg2);
  }
}

void func_151D79B4(void *arg0) {
    func_151D7D78(arg0);
}

void func_151D79D4(void *arg0) {
    func_151D79B4(arg0);
    func_1514933C(arg0);
}

void func_151D7A00(void *arg0) {
    func_151D79B4(arg0);
    func_15149368(arg0);
}

void func_151D7A2C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
    } tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    func_151494E0(&tmp, 0x3D);
}

void func_151D7A60(u8 *arg0, u8 arg1, s8 arg2, u8 arg3, s32 arg4) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
        s8 unk6;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = *(u8 *)(arg0 + 0x3B);
    tmp.unk5 = arg1;
    tmp.unk6 = arg2;
    temp_v0 = func_151D7760(0x12C, 0, 0, 12.0f, (u8 *)8, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x40, &tmp, 8);
    }
}

#ifdef NON_MATCHING
// linked_obj_event_3d: event handler of an object whose link record sits at +0x40 ({ s32 id, u8 key }): event 0x3D removes the
// object (func_1516972C) when the event's record matches by id or by key; any other event goes to the common
// handler func_15149514.
void func_151D7AE8(struct102 *obj, u8 *ev, u8 type) {
    u8 *link = (u8 *) obj + 0x40;

    if (type == 0x3D) {
        if (*(s32 *) link == *(s32 *) ev || link[4] == ev[4]) {
            func_1516972C(obj);
        }
    } else {
        func_15149514((s32) ev, type, (s32) link, (s32) (link + 4), (s32) obj);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7AE8.s")
#endif

extern u8 D_800AB660[];
extern u8 D_800AB6B4[];
extern s32 (*D_80090048[])(u8 *);

s32 func_151D7B74(u8 *arg0) {
    u8 *obj;
    u8 *s;
    u8 *f;

    f = arg0 + 0x28;
    obj = *(u8 **)(arg0 + 0x40);
    s = arg0 + 0x40;
    if (*(s32 *)obj == 0 || s[4] != obj[0x3B]) {
        return 0;
    }
    if (*(u8 **)(obj + 0x1D4) == NULL) {
        f[5] &= ~1;
        return 1;
    }
    if (*(u8 **)(obj + 0x31C) != NULL && (*(u8 **)(obj + 0x31C))[0x197] != 0 && *(s32 *)(obj + 0x318) != 0) {
        f[5] &= ~1;
        return 1;
    }
    if (obj[7] != 0xFF) {
        f[5] &= ~1;
        return 1;
    }
    func_15143134(&D_800AB660[s[5] * 12], f + 8, *(u8 **)(obj + 0x1D4) + (D_800AB6B4[s[5]] << 6));
    f[5] |= 1;
    if ((s8)s[6] != -1) {
        return D_80090048[(s8)s[6]](arg0);
    }
    return 1;
}

s32 func_151D7CD4(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x40);
    u8 *temp_v0_2 = arg0 + 0x28;

    if ((*(s32 *)(temp_v0 + 0x94) & 2) || (*(u16 *)(temp_v0 + 0x84) == 4) ||
        (*(u16 *)(temp_v0 + 0x84) == 0xA) || (*(u16 *)(temp_v0 + 0x84) == 0xC)) {
        temp_v0_2[5] &= ~1;
    }
    return 1;
}

s32 func_151D7D20(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x40);
    u8 *temp_v1;
    temp_v1 = arg0 + 0x28;
    if (*(u16 *)(temp_v0 + 0x84) == 0) {
        temp_v1[5] &= ~1;
    }
    return 1;
}

s32 func_151D7D4C(u8 *arg0) {
    u8 *temp_v0 = *(u8 **)(arg0 + 0x40);
    u8 *temp_v1;
    temp_v1 = arg0 + 0x28;
    if (temp_v0[0xAD] != 0) {
        temp_v1[5] &= ~1;
    }
    return 1;
}

void func_151D7D78(u8 *arg0) {
    u8 **v;
    s32 *q;
    v = (u8 **)(arg0 + 0x28);
    if (*(s32 *)(arg0 + 0x28) != 0) {
        q = *(s32 **)(*v + 0x98);
        *(s8 *)(*v + 0x30) = 0;
        *(u16 *)(*v + 0x1E) &= 0xFFFD;
        *(u16 *)(*v + 0x1E) |= 8;
        *(u16 *)(*v + 0x1E) |= 1;
        *(s16 *)(*v + 0x1C) = 0x14;
        *q = 0;
        *v = NULL;
    }
}

typedef struct { f32 x, y, z; } V37DE0;
typedef struct { V37DE0 pos; s16 u58; s16 u5A; s32 u5C; s8 u60; s8 u61; u8 pad62[2]; s32 u64; } SA7DE0;
typedef struct { u8 *u68; V37DE0 pos; f32 u78, u7C, u80; } SB7DE0;

void func_151D7DE0(u8 *arg0) {
    u8 *r;
    SB7DE0 b;
    SA7DE0 a;
    s32 pad[2]; // fakematch: frame padding below the param block

    b.u68 = arg0;
    b.pos = *(V37DE0 *)(arg0 + 0x30);
    b.u78 = 0.0f;
    b.u7C = 0.0f;
    b.u80 = 0.0f;
    a.u61 = 0x19;
    a.pos = *(V37DE0 *)(arg0 + 0x30);
    a.u58 = 0x12C;
    a.u5A = 0x76;
    a.u5C = 0x12;
    a.u60 = 4;
    a.u64 = 0;
    r = (u8 *)func_15147FF0(&a, 0x20, 0x1C, 0xD, 0x10, 0x10, 0, 0, 0, arg0[0xC], arg0[1]);
    if (r != NULL) {
        memcpy(*(void **)(r + 0x98), &b, 0x1C);
        *(u8 **)(arg0 + 0x28) = r;
    }
}

#ifdef NON_MATCHING
// trail_points_update: P232. Particle-object callback (s32 handler, returns 1 = keep / 0 = done) for a ring of
// points: the ring holds +0x25 entries of 0x1C bytes at +0x94 (position at +0, velocity at +0xC), +0x2E is the
// write cursor and +0x2D the oldest entry. Each frame every entry from the one before the cursor back to the oldest
// (wrapping) is advanced by func_151D8CC8 with the frame step D_800BE9A4. While there are points (+0x2C > 0) the
// head position +0x54 is the oldest entry's position, else it is zeroed. With fewer than 2 points and flag 8 of
// +0x1E the object ends (returns 0).
s32 func_151D7EDC(u8 *arg0) {
    u8 *ring = *(u8 **) (arg0 + 0x94);
    s32 i;
    u8 *e;

    if ((s8) arg0[0x2C] < 2 && (*(u16 *) (arg0 + 0x1E) & 8)) {
        return 0;
    }
    i = (s8) arg0[0x2E];
    while (i != (s8) arg0[0x2D]) {
        i--;
        if (i < 0) {
            i = arg0[0x25] - 1;
        }
        e = ring + i * 0x1C;
        func_151D8CC8((f32 *) e, (f32 *) (e + 0xC), D_800BE9A4);
    }
    if ((s8) arg0[0x2C] > 0) {
        e = ring + (s8) arg0[0x2D] * 0x1C;
        *(s32 *) (arg0 + 0x54) = *(s32 *) (e + 0);
        *(s32 *) (arg0 + 0x58) = *(s32 *) (e + 4);
        *(s32 *) (arg0 + 0x5C) = *(s32 *) (e + 8);
    } else {
        *(f32 *) (arg0 + 0x54) = 0.0f;
        *(f32 *) (arg0 + 0x58) = 0.0f;
        *(f32 *) (arg0 + 0x5C) = 0.0f;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7EDC.s")
#endif

#ifdef NON_MATCHING
s32 func_151D7FE8(u8 *arg0) {
    struct {
        f32 u88;
        f32 u8C;
        f32 u90;
        u8 pad94[0x20];
        f32 uB4;
        f32 uB8;
        f32 uBC;
    } sp;
    u8 *sp70;
    f32 sp64;
    f32 *temp_a0;
    f32 temp_f0;
    f32 temp_f18;
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f30;
    f32 var_f22;
    f32 var_f2;
    s32 temp_s3;
    s8 temp_v1;
    u8 *temp_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_s1 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_s3 = (*(s32 *)((u8 *)arg0 + 0x94));
    temp_v0 = (*(u8 **)((u8 *)temp_s1 + 0));
    if (!((*(u8 *)((u8 *)temp_v0 + 0x2D)) & 1)) {
        return 0;
    }
    (*(f32 *)((u8 *)(&sp.uB4) + 0)) = (*(f32 *)((u8 *)temp_v0 + 0x30));
    (*(s32 *)((u8 *)(&sp.uB4) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0x34));
    (*(s32 *)((u8 *)(&sp.uB4) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0 + 0x38));
    (*(f32 *)((u8 *)arg0 + 0x10)) = (f32) (*(f32 *)((u8 *)(&sp.uB4) + 0));
    (*(s32 *)((u8 *)arg0 + 0x14)) = (s32) (*(s32 *)((u8 *)(&sp.uB4) + 4));
    (*(s32 *)((u8 *)arg0 + 0x18)) = (s32) (*(s32 *)((u8 *)(&sp.uB4) + 8));
    (*(f32 *)((u8 *)temp_s1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x14)) + (0.25f * D_800BE9A4));
    temp_f18 = (*(f32 *)((u8 *)temp_s1 + 0x14));
    if (temp_f18 > 1.0f) {
        temp_f0 = 1.0f / temp_f18;
        temp_v0_2 = temp_s1 + 4;
        (*(f32 *)((u8 *)(&sp.u88) + 0)) = (*(f32 *)((u8 *)temp_v0_2 + 0));
        var_f22 = (*(f32 *)((u8 *)temp_s1 + 0x10)) + D_800BE9A4;
        (*(s32 *)((u8 *)(&sp.u88) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0_2 + 4));
        (*(s32 *)((u8 *)(&sp.u88) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0_2 + 8));
        temp_f26 = var_f22 * temp_f0;
        temp_f28 = (sp.uB4 - (*(f32 *)((u8 *)temp_s1 + 4))) * temp_f0;
        sp70 = temp_v0_2;
        temp_f30 = (sp.uB8 - (*(f32 *)((u8 *)temp_s1 + 8))) * temp_f0;
        var_f2 = (sp.uBC - (*(f32 *)((u8 *)temp_s1 + 0xC))) * temp_f0;
        do {
            temp_a0 = ((*(s8 *)((u8 *)arg0 + 0x2E)) * 0x1C) + temp_s3;
            (*(f32 *)((u8 *)temp_a0 + 0)) = (*(f32 *)((u8 *)(&sp.u88) + 0));
            (*(s32 *)((u8 *)temp_a0 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u88) + 4));
            (*(f32 *)((u8 *)temp_a0 + 0xC)) = 0.0f;
            (*(f32 *)((u8 *)temp_a0 + 0x10)) = 0.0f;
            (*(s8 *)((u8 *)temp_a0 + 0x14)) = 0;
            (*(f32 *)((u8 *)temp_a0 + 0x18)) = 0.0f;
            (*(s32 *)((u8 *)temp_a0 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u88) + 8));
            sp64 = var_f2;
            func_151D8CC8(temp_a0, (f32 *) ((u8 *) temp_a0 + 0xC), var_f22); /* P270: was temp_a0 + 0xC (f32 stride = +0x30 bytes; asm addiu a1,a0,0xC) */
            (*(s8 *)((u8 *)arg0 + 0x2E)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2E)) + 1);
            var_f22 -= temp_f26;
            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2E)) = 0;
            }
            temp_v1 = (*(s8 *)((u8 *)arg0 + 0x2D));
            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) + 1);
            if (temp_v1 == (*(s8 *)((u8 *)arg0 + 0x2E))) {
                (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) (temp_v1 + 1);
                if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                }
                (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
            }
            sp.u88 += temp_f28;
            sp.u8C += temp_f30;
            sp.u90 += var_f2;
            (*(f32 *)((u8 *)temp_s1 + 0x14)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0x14)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0x14)) > 1.0f);
        (*(f32 *)((u8 *)sp70 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u88) + 0));
        (*(s32 *)((u8 *)sp70 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u88) + 4));
        (*(s32 *)((u8 *)sp70 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u88) + 8));
        (*(f32 *)((u8 *)temp_s1 + 0x10)) = var_f22;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D7FE8.s")
#endif
#ifdef NON_MATCHING
f32 func_15144528(f32, f32, f32);

/* trail_ring_constrain: P238: handler of the trail object of func_151D7EDC (ring of +0x25 entries of 0x1C bytes at
 * +0x94, write cursor s8 +0x2E, oldest s8 +0x2D, count s8 +0x2C). With 2 or more points:
 * 1. walk from the newest entry (the one before the cursor; flag 2 of u16 +0x1E: start at the object's own point
 *    +0x10 instead and skip one more) back to the oldest, store each segment length at entry +0x10 and sum them;
 *    once the sum passes 80 the entry is pulled back along its segment so the trail is exactly 80 long (+0x10
 *    shortened to match) and every older entry is dropped (oldest moves up to it, count decreases).
 * 2. state (+0x98) f32 +0x18 += -41 * frame step D_800BE9A4, wrapped by func_15144528(x, 16383, -16384); each
 *    entry's +0x18 = func_15144528(that + sum of lengths so far * 46.88, 16383, -16384).
 * 3. entry byte +0x14 (alpha): 60 while the running length is <= 0.299 * total, then fading linearly to 0 at the
 *    end ((u32) conversion as in the asm).
 * Returns 1. Float constants from the ELF: D_800AB6BC / C4 = 16383, D_800AB6C0 = 46.88 (0x423B851E),
 * D_800AB6C8 = 0.299 (0x3E991688). */
s32 func_151D8280(u8 *obj) {
    u8 *ring = *(u8 **) (obj + 0x94);
    u8 *state = *(u8 **) (obj + 0x98);
    f32 *prev;
    f32 *cur;
    f32 d[3];
    f32 total;
    f32 len;
    f32 k;
    f32 acc;
    f32 fadeStart;
    f32 fadeLen;
    f32 inv;
    f32 t;
    s32 i;

    if ((s8) obj[0x2C] >= 2) {
        total = 0.0f;
        i = (s8) obj[0x2E];
        if (*(u16 *) (obj + 0x1E) & 2) {
            prev = (f32 *) (obj + 0x10);
        } else {
            i--;
            if (i < 0) {
                i = obj[0x25] - 1;
            }
            prev = (f32 *) (ring + i * 0x1C);
        }
        i--;
        while (1) {
            if (i < 0) {
                i = obj[0x25] - 1;
            }
            cur = (f32 *) (ring + i * 0x1C);
            d[0] = cur[0] - prev[0];
            d[1] = cur[1] - prev[1];
            d[2] = cur[2] - prev[2];
            len = func_15143E64((struct17 *) d);
            total += len;
            cur[4] = len;
            if (80.0f < total) {
                if (cur[4] != 0.0f) {
                    len = cur[4];
                    k = (total - 80.0f) * (1.0f / len);
                    cur[0] -= d[0] * k;
                    cur[1] -= d[1] * k;
                    cur[2] -= d[2] * k;
                    cur[4] = len * (1.0f - k);
                }
                total = 80.0f;
                while (i != (s8) obj[0x2D]) {
                    obj[0x2D] = (s8) obj[0x2D] + 1;
                    if (obj[0x25] == (s8) obj[0x2D]) {
                        obj[0x2D] = 0;
                    }
                    obj[0x2C] = (s8) obj[0x2C] - 1;
                }
            }
            prev = cur;
            if (i == (s8) obj[0x2D]) {
                break;
            }
            i--;
        }

        if ((s8) obj[0x2C] >= 2) {
            *(f32 *) (state + 0x18) += -41.0f * D_800BE9A4;
            *(f32 *) (state + 0x18) = func_15144528(*(f32 *) (state + 0x18), 16383.0f, -16384.0f);
            acc = 0.0f;
            i = (s8) obj[0x2E] - 1;
            while (1) {
                if (i < 0) {
                    i = obj[0x25] - 1;
                }
                cur = (f32 *) (ring + i * 0x1C);
                acc += cur[4];
                cur[6] = func_15144528(*(f32 *) (state + 0x18) + acc * 46.87999725341797f, 16383.0f, -16384.0f);
                if (i == (s8) obj[0x2D]) {
                    break;
                }
                i--;
            }
        }

        if ((s8) obj[0x2C] >= 2) {
            fadeStart = total * 0.2990000247955322f;
            fadeLen = total - fadeStart;
            inv = 1.0f / fadeLen;
            acc = 0.0f;
            i = (s8) obj[0x2E] - 1;
            while (1) {
                if (i < 0) {
                    i = obj[0x25] - 1;
                }
                cur = (f32 *) (ring + i * 0x1C);
                if (fadeStart < acc) {
                    t = acc - fadeStart;
                    if (fadeLen < t) {
                        t = fadeLen;
                    }
                    ((u8 *) cur)[0x14] = (u32) ((fadeLen - t) * inv * 60.0f);
                } else {
                    ((u8 *) cur)[0x14] = 60;
                }
                acc += cur[4];
                if (i == (s8) obj[0x2D]) {
                    break;
                }
                i--;
            }
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D8280.s")
#endif

#ifdef NON_MATCHING
s32 func_1513F4E4(s32, s32, s8 *);
s32 func_15142B7C(s32, s32, s32);
s32 func_15142E24(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
u8 *func_15142FBC(s32, s32, s32, s8 *);
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
extern s32 D_80091084;
extern s32 D_800D30BC;
extern s32 D_800DD608;
extern s32 D_800DD618;

u8 *func_151D8674(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        u8 * u8C;
        u8 pad90[0x17];
        s8 uA7;
        s32 uA8;
        u8 padAC[0x8];
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
    } sp;
    s32 *temp_v1;
    f32 temp_f20;
    f32 temp_f22;
    f32 var_f0;
    f32 var_f2;
    s32 temp_f10;
    s32 temp_f16;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_s3;
    s32 var_t0;
    s32 var_v1;
    s32 var_v1_2;
    u8 var_a0;
    u8 var_v0;
    u8 *temp_s1;
    u8 *temp_s2;
    u8 *temp_s2_2;
    u8 *temp_t3;
    u8 *temp_t6;
    u8 *temp_t6_2;
    u8 *temp_v0;
    u8 *var_s1;
    u8 *var_s2;

    var_s2 = arg1;
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) {

    } else {
        temp_s1 = (*(u8 **)((u8 *)arg0 + 0x98));
        sp.uA8 = (*(s32 *)((u8 *)arg0 + 0x94));
        func_151D6310(arg0 + 0x84, arg2, ((*(u8 *)((u8 *)arg0 + 0x25)) << 5) + 0xA0, &sp.u8C, 0);
        if (sp.u8C == NULL) {

        } else {
            sp.uA7 = 1;
            temp_v1 = ((u8 *)&D_800A4EA8);
            var_t0 = sp.uA8;
            var_s2 = func_15142FBC(func_1513F4E4(func_15142B7C(func_15142E24(var_s2, &D_80091084, 0, 0, 0, 0, 0x1F, 0, 0, &sp.uA7, 0x3E), 0x200005, 0x1F0600), 0x4C, &sp.uA7), D_800D30BC | 0x80000 | 0x2CA0, (*(s32 *)((u8 *)temp_v1 + 0xC)) | (*(s32 *)((u8 *)temp_v1 + 8)), &sp.uA7);
            if ((*(u16 *)((u8 *)arg0 + 0x1E)) & 2) {
                var_s3 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
                if (var_s3 < 0) {
                    var_s3 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                var_a0 = 0;
                (*(f32 *)((u8 *)(&sp.uB4) + 0)) = (*(f32 *)((u8 *)arg0 + 0x10));
                (*(s32 *)((u8 *)(&sp.uB4) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 0x14));
                (*(s32 *)((u8 *)(&sp.uB4) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 0x18));
                var_f2 = (*(f32 *)((u8 *)temp_s1 + 0x18));
            } else {
                var_v1 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
                if (var_v1 < 0) {
                    var_v1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                var_s3 = var_v1 - 1;
                if (var_s3 < 0) {
                    var_s3 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                temp_v0 = var_t0 + (var_v1 * 0x1C);
                (*(f32 *)((u8 *)(&sp.uB4) + 0)) = (*(f32 *)((u8 *)temp_v0 + 0));
                (*(s32 *)((u8 *)(&sp.uB4) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0 + 4));
                (*(s32 *)((u8 *)(&sp.uB4) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0 + 8));
                var_a0 = (*(u8 *)((u8 *)temp_v0 + 0x14));
                var_f2 = (*(f32 *)((u8 *)temp_v0 + 0x18));
            }
            var_s1 = var_t0 + (var_s3 * 0x1C);
            temp_v1_2 = arg2 * 4;
            (*(f32 *)((u8 *)(&sp.uC0) + 0)) = (*(f32 *)((u8 *)var_s1 + 0));
            (*(s32 *)((u8 *)(&sp.uC0) + 4)) = (s32) (*(s32 *)((u8 *)var_s1 + 4));
            (*(s32 *)((u8 *)(&sp.uC0) + 8)) = (s32) (*(s32 *)((u8 *)var_s1 + 8));
            temp_f20 = *(&D_800DD618 + temp_v1_2) * 5.5f;
            var_v0 = (*(u8 *)((u8 *)var_s1 + 0x14));
            temp_f22 = *(&D_800DD608 + temp_v1_2) * 5.5f;
            var_f0 = (*(f32 *)((u8 *)var_s1 + 0x18));
            if ((*(u16 *)((u8 *)arg0 + 0x1E)) & 8) {
                var_v1_2 = ((*(s16 *)((u8 *)arg0 + 0x1C)) * 0xC) & 0xFF;
            } else {
                var_v1_2 = 0xFF;
            }
            temp_f16 = (s32) var_f2;
            (*(s16 *)((u8 *)sp.u8C + 0)) = (s16) (s32) (sp.uB4 + temp_f20);
            temp_t2 = (s32) (var_a0 * var_v1_2) >> 8;
            (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) sp.uB8;
            (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) (sp.uBC - temp_f22);
            (*(s16 *)((u8 *)sp.u8C + 8)) = (s16) temp_f16;
            (*(s16 *)((u8 *)sp.u8C + 0xA)) = 0x800;
            (*(s8 *)((u8 *)sp.u8C + 0xC)) = 0xFF;
            (*(s8 *)((u8 *)sp.u8C + 0xD)) = 0xFF;
            (*(s8 *)((u8 *)sp.u8C + 0xE)) = 0xFF;
            (*(s8 *)((u8 *)sp.u8C + 0xF)) = (s8) temp_t2;
            (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
            temp_t6 = sp.u8C + 0x10;
            sp.u8C = temp_t6;
            (*(s16 *)((u8 *)temp_t6 + 0)) = (s16) (s32) (sp.uB4 - temp_f20);
            (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) sp.uB8;
            (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) (sp.uBC + temp_f22);
            (*(s16 *)((u8 *)sp.u8C + 8)) = (s16) temp_f16;
            (*(s16 *)((u8 *)sp.u8C + 0xA)) = 0;
            (*(s8 *)((u8 *)temp_t6 + 0xC)) = 0xFF;
            (*(s8 *)((u8 *)sp.u8C + 0xD)) = 0xFF;
            (*(s8 *)((u8 *)sp.u8C + 0xE)) = 0xFF;
            (*(s8 *)((u8 *)sp.u8C + 0xF)) = (s8) temp_t2;
            (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
            sp.u8C += 0x10;
            do {
                temp_t4 = (s32) (var_v0 * var_v1_2) >> 8;
                (*(s16 *)((u8 *)sp.u8C + 0)) = (s16) (s32) (sp.uC0 + temp_f20);
                temp_f10 = (s32) var_f0;
                (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) sp.uC4;
                (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) (sp.uC8 - temp_f22);
                (*(s16 *)((u8 *)sp.u8C + 8)) = (s16) temp_f10;
                (*(s16 *)((u8 *)sp.u8C + 0xA)) = 0x800;
                (*(s8 *)((u8 *)sp.u8C + 0xC)) = 0xFF;
                (*(s8 *)((u8 *)sp.u8C + 0xD)) = 0xFF;
                (*(s8 *)((u8 *)sp.u8C + 0xE)) = 0xFF;
                (*(s8 *)((u8 *)sp.u8C + 0xF)) = (s8) temp_t4;
                (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
                temp_t6_2 = sp.u8C + 0x10;
                sp.u8C = temp_t6_2;
                (*(s16 *)((u8 *)temp_t6_2 + 0)) = (s16) (s32) (sp.uC0 - temp_f20);
                (*(s16 *)((u8 *)sp.u8C + 2)) = (s16) (s32) sp.uC4;
                (*(s16 *)((u8 *)sp.u8C + 4)) = (s16) (s32) (sp.uC8 + temp_f22);
                (*(s16 *)((u8 *)sp.u8C + 8)) = (s16) temp_f10;
                (*(s16 *)((u8 *)sp.u8C + 0xA)) = 0;
                (*(s8 *)((u8 *)temp_t6_2 + 0xC)) = 0xFF;
                (*(s8 *)((u8 *)sp.u8C + 0xD)) = 0xFF;
                (*(s8 *)((u8 *)sp.u8C + 0xE)) = 0xFF;
                (*(s8 *)((u8 *)sp.u8C + 0xF)) = (s8) temp_t4;
                (*(s16 *)((u8 *)sp.u8C + 6)) = 0;
                sp.u8C += 0x10;
                (*(s32 *)((u8 *)var_s2 + 0)) = 0x01004008;
                temp_s2 = var_s2 + 8;
                (*(u8 **)((u8 *)var_s2 + 4)) = (u8 *) (sp.u8C - 0x40);
                temp_s2_2 = temp_s2 + 8;
                (*(s32 *)((u8 *)temp_s2 + 0)) = 0x05000204;
                (*(s32 *)((u8 *)temp_s2 + 4)) = 0;
                (*(s32 *)((u8 *)temp_s2_2 + 0)) = 0x05020604;
                (*(s32 *)((u8 *)temp_s2_2 + 4)) = 0;
                var_s2 = temp_s2_2 + 8;
                if (var_f0 < var_f2) {
                    sp.uA8 = var_t0;
                    memcpy(sp.u8C, sp.u8C - 0x20, 0x20);
                    (*(s16 *)((u8 *)sp.u8C + -0x18)) = (s16) ((*(s16 *)((u8 *)sp.u8C + -0x18)) - 0x8000);
                    temp_t3 = sp.u8C + 0x10;
                    sp.u8C = temp_t3;
                    (*(s16 *)((u8 *)temp_t3 + -0x18)) = (s16) ((*(s16 *)((u8 *)temp_t3 + -0x18)) - 0x8000);
                    sp.u8C += 0x10;
                }
                temp_v1_3 = var_s3;
                var_s3 -= 1;
                var_s1 -= 0x1C;
                if (var_s3 < 0) {
                    var_s3 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                    var_s1 = var_t0 + (var_s3 * 0x1C);
                }
                (*(f32 *)((u8 *)(&sp.uC0) + 0)) = (*(f32 *)((u8 *)var_s1 + 0));
                (*(s32 *)((u8 *)(&sp.uC0) + 4)) = (s32) (*(s32 *)((u8 *)var_s1 + 4));
                (*(s32 *)((u8 *)(&sp.uC0) + 8)) = (s32) (*(s32 *)((u8 *)var_s1 + 8));
                var_v0 = (*(u8 *)((u8 *)var_s1 + 0x14));
                var_f2 = (*(f32 *)((u8 *)((var_t0 + (temp_v1_3 * 0x1C))) + 0x18));
                var_f0 = (*(f32 *)((u8 *)var_s1 + 0x18));
            } while (temp_v1_3 != (*(s8 *)((u8 *)arg0 + 0x2D)));
        }
    }
    return var_s2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_204F70/func_151D8674.s")
#endif
void func_151D8CC8(f32 *arg0, f32 *arg1, f32 arg2) {
    f32 temp_f2 = *arg1;

    *arg1 += D_800AB6CC * arg2;
    arg0[1] += (temp_f2 * arg2) + (D_800AB6D0 * (arg2 * arg2));
}

void func_151D8D14(u8 *arg0) {
    s32 **temp_v0 = *(s32 ***)(arg0 + 0x98);
    s32 *temp_v1 = *temp_v0;
    if (temp_v1 != NULL) {
        temp_v1[0x28 / 4] = 0;
    }
}

void func_151D8D30(void *arg0) {
    func_151D8D14(arg0);
    func_15147E64(arg0);
}

void func_151D8D5C(void *arg0) {
    func_151D8D14(arg0);
    func_15147E98(arg0);
}
