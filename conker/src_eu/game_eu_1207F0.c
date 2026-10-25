#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A1D20[];
#endif


#ifdef NON_MATCHING
extern u8 D_800CC82C;
extern u8 D_800CC8BA;
extern s32 *D_800DC3C4;
s32 func_151149AC(u8);
s32 func_15136C3C(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_1507CD64(struct127 *, s32);
void func_15196888(u8 *, s32, s32);

// player_item_drop_check: unless the player's held object (D_800CCA0C, byte 0x120) is busy, checks items 0xFA and
// 0xF9 (func_151149AC; entry index = (item - D_800DBEF4) / 160 into the flag words at D_800DC3C4). The first one
// with bit 0 set: releases the player's current carried object (func_15060F28), clears D_800CC8BA and resets the
// player (func_15136C3C, sound 0x627 via func_10010630, func_15145A50, mode 6 via func_1507CD64). Then the four
// D_800BE4F0 nodes are offset by +-object 0xE's +0x2E4 value (func_15196888).
void func_150F2FE0(s32 arg0) {
    struct127 *o;
    s32 off;
    s32 i;
    s32 item;

    if (D_800CCA0C == NULL || D_800CCA0C[0x120] != 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        item = func_151149AC(0xFA - i);
        if (D_800DC3C4[(item - (s32) D_800DBEF4) / 160] & 1) {
            if (D_800CC82C != 0) {
                func_15060F28((struct127 *) ((u8 *) D_800CC2D0 + (D_800CC82C - 100) * 0x32C), 0);
            }
            D_800CC8BA = 0;
            func_15136C3C(D_800CC2D0, 0, 0, 1, 1, 0, 0xFF, 1);
            func_10010630(0x627, D_800CC2D0, 0x6D60, 0x1F4, 0x3E8);
            func_15145A50(D_800CC2D0);
            func_1507CD64(D_800CC2D0, 6);
            break;
        }
    }
    o = func_15083E90(0xE);
    off = (o != NULL) ? *(s32 *) ((u8 *) o + 0x2E4) : 0;
    func_15196888(((u8 **) D_800BE4F0)[0], off, 0);
    func_15196888(((u8 **) D_800BE4F0)[1], 0, -off);
    func_15196888(((u8 **) D_800BE4F0)[2], off, 0);
    func_15196888(((u8 **) D_800BE4F0)[3], -off, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F2FE0.s")
#endif

void func_150F320C(u8 *arg0) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
        f32 unk8;
        u8 unkC;
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk5 = 0;
    tmp.unk8 = 0.0f;
    tmp.unkC = 0;
    temp_v0 = func_15149130(300, -1, 0x5C, -1, 0, 0x44, 0x10, 255, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
    }
}

#ifdef NON_MATCHING
void func_1502ED88(u8 *, s32, s32, s32, s32, s32, s32);
void func_15145EA4(f32 **, f32 **, void *, s32);
s32 func_15146078(f32 *, s32 *, s32 *);
void *func_1513D2F0(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9,
                    u8 argA, s32 argB);
extern u8 D_800A1D2C[];  /* second bone-space point (after D_800A1D20) */
extern f32 D_800A1D38;   /* drops per frame unit */
extern f32 D_800A1D3C;

// drip_emitter_update: object update of a drip emitter (record at +0x28: owner, +4 owner id, +5 last owner
// state, +8 f32 accumulator, +0xC s8 drops left). Stops when the cutscene flag D_800C35EA is 1; ends the object
// (+0xE = -1) when the owner is gone or its id changed. A new non-zero owner state (+0x222) refills 3 drops; while
// the state is set, func_1502ED88 runs on object D_800CC2D0[state]. With a model, the accumulator grows by
// D_800A1D38 * frame time and every whole unit drops one: the line between the bone points D_800A1D20 / D_800A1D2C
// (bone matrix +0x3C0) is probed (func_15146078) and a drop sprite (func_1513D2F0, template D_800A4AA0, size
// 60..100, alpha 0x34-byte trail record copied to +0x110) is spawned at the first point.
void func_150F3294(u8 *obj) {
    struct {
        u8 *owner;
        u8 id;
        u8 pad5[3];
        f32 t;
        f32 size;
        f32 unk10;
        f32 speed;
        f32 accel;
        s32 hit[3];
        s32 normal[3];
    } trail;
    struct {
        u8 type;
        u8 unk1;
        s16 tex;
        s16 life;
        u8 pad6[2];
        s32 unk8;
        s32 unkC;
        u8 col[4];
        f32 unk14;
        f32 unk18;
        f32 pos[3];
        s32 unk28[3];
        f32 scale[3];
        s32 unk40;
        u8 alpha;
        u8 unk45;
        u8 unk46;
        u8 unk47;
        s32 unk48;
        u8 unk4C;
        u8 pad4D[3];
        s32 unk50;
        s16 unk54;
        s16 unk56;
    } spr;
    f32 *in[2];
    f32 *out[2];
    f32 dir[3];
    u8 *st = obj + 0x28;
    u8 *owner;
    u8 state;
    void *p;

    if (D_800C35EA == 1) {
        return;
    }
    owner = *(u8 **) st;
    if (*(s32 *) owner == 0 || st[4] != owner[0x3B]) {
        *(s16 *) (obj + 0xE) = -1;
        return;
    }
    state = owner[0x222];
    if (state != st[5] && state != 0) {
        st[0xC] = 3;
        *(f32 *) (st + 8) = 0.0f;
    }
    st[5] = owner[0x222];
    state = owner[0x222];
    if (state != 0) {
        func_1502ED88((u8 *) D_800CC2D0 + state * 0x32C, 0xFF, 0, 0, 0x50, 0, 0xF);
    }
    if (*(u8 **) (owner + 0x1D4) == NULL) {
        return;
    }
    if (*(s8 *) (st + 0xC) <= 0) {
        return;
    }
    *(f32 *) (st + 8) += D_800A1D38 * D_800BE9A4;
    if (!(1.0f < *(f32 *) (st + 8))) {
        return;
    }
    do {
        trail.owner = owner;
        trail.id = owner[0x3B];
        trail.t = 0.0f;
        trail.size = func_150ADA68() * 6.0f + 13.0f;
        trail.unk10 = D_800A1D3C;
        trail.speed = func_150ADA68() * 40.0f + 60.0f;
        trail.accel = trail.speed / (trail.size * trail.size);
        in[0] = (f32 *) D_800A1D20;
        in[1] = (f32 *) D_800A1D2C;
        out[0] = spr.pos;
        out[1] = dir;
        func_15145EA4(in, out, *(u8 **) (owner + 0x1D4) + 0x3C0, 2);
        dir[0] -= spr.pos[0];
        dir[1] -= spr.pos[1];
        dir[2] -= spr.pos[2];
        if (func_15146078(dir, trail.hit, trail.normal) == 0) {
            return;
        }
        spr.alpha = (u32) trail.speed;
        spr.type = 0x79;
        spr.unk1 = 0xC;
        spr.tex = 0x4405;
        spr.life = 300;
        spr.unk8 = 0;
        spr.unkC = 0;
        spr.col[0] = 0xD5;
        spr.col[1] = 0xDB;
        spr.col[2] = 0xFF;
        spr.col[3] = 0xFF;
        spr.unk18 = 0.0f;
        spr.unk14 = 0.0f;
        spr.unk28[0] = ((s32 *) D_800A5860)[0];
        spr.unk28[1] = ((s32 *) D_800A5860)[1];
        spr.unk28[2] = ((s32 *) D_800A5860)[2];
        spr.scale[0] = 1.0f;
        spr.scale[1] = 1.0f;
        spr.scale[2] = 1.0f;
        spr.unk40 = 0x04EC0000;
        spr.unk45 = 0xFF;
        spr.unk46 = 0;
        spr.unk47 = 6;
        spr.unk48 = 0;
        spr.unk4C = 0xFF;
        spr.unk50 = 0;
        spr.unk54 = 1;
        spr.unk56 = 0xFF;
        p = func_1513D2F0(&spr, (s32) &D_800A4AA0, 0x26, 0, 0, 0x25, 0, 0, 0, 0x34, obj[0xC], obj[1]);
        if (p != NULL) {
            memcpy((u8 *) p + 0x110, &trail, 0x34);
        }
        *(f32 *) (st + 8) -= 1.0f;
        (*(s8 *) (st + 0xC))--;
        if (!(1.0f < *(f32 *) (st + 8))) {
            return;
        }
    } while (*(s8 *) (st + 0xC) > 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3294.s")
#endif

void func_150F3714(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void func_150F3754(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}

#ifdef NON_MATCHING
s32 func_150F3794(u8 *arg0) {
    u8 *sp18;
    f32 temp_f12;
    f32 temp_f2;
    s32 temp_t0;
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x110));
    temp_v0 = arg0 + 0x110;
    if (((*(s32 *)((u8 *)temp_v1 + 0)) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_v1 + 0x3B))) || (temp_t0 = (*(s32 *)((u8 *)temp_v1 + 0x1D4)), (temp_t0 == 0))) {
        return 0;
    }
    sp18 = temp_v0;
    func_15143134(((u8 *)&D_800A1D20), arg0 + 0x34, temp_t0 + 0x3C0);
    temp_f2 = sqrtf((*(f32 *)((u8 *)temp_v0 + 8))) * (*(f32 *)((u8 *)temp_v0 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x30)) = temp_f2;
    (*(f32 *)((u8 *)arg0 + 0x2C)) = temp_f2;
    temp_f12 = (*(f32 *)((u8 *)temp_v0 + 8));
    (*(s8 *)((u8 *)arg0 + 0x5C)) = (s8) (u32) ((*(f32 *)((u8 *)temp_v0 + 0x14)) - ((*(f32 *)((u8 *)temp_v0 + 0x18)) * temp_f12 * temp_f12));
    (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_v0 + 8)) + D_800BE9A4);
    var_v0 = 1;
    if ((*(f32 *)((u8 *)temp_v0 + 0xC)) < (*(f32 *)((u8 *)temp_v0 + 8))) {
        var_v0 = 0;
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3794.s")
#endif
s32 func_15140410();

/* P224: draw table D_8008A1BC entry; the asm returns func_15140410's v0 and the dispatcher uses it. */
u8 *func_150F38FC(u8 *arg0, s16 arg1) {
    return (u8 *) func_15140410(arg0, arg0 + 0x12C, arg0 + 0x138, arg1);
}

typedef struct {
    u8 pad0[0x4F];
    u8 unk4F_7 : 7;
    u8 unk4F_0 : 1;
} struct_eu_150F3930;

void func_150F3930(struct_eu_150F3930 *arg0) {
    if (*(f32 *)((u8 *)D_800DBFF0 + 0x300) < -2000.0f) {
        arg0->unk4F_0 = 0;
        return;
    }
    arg0->unk4F_0 = 1;
}

extern f32 D_800A1D40;

void func_150F3978(s32 arg0) {
    u8 *e = (u8 *)D_800DBFF0 + arg0 * 0x9A0;

    if (*(f32 *)(e + 0x300) < D_800A1D40) {
        if (*(f32 *)(e + 0x2FC) > 840.0f) {
            **(s16 **)&D_800D9A40 = **(s16 **)&D_800D9A40 | (1 << arg0); // fakematch: D_800D9A40 is declared s32 but holds a pointer; inline casts, no local
            return;
        }
        **(s16 **)&D_800D9A40 = **(s16 **)&D_800D9A40 & ~(1 << arg0);
    }
}

extern f32 D_800A1D50;
extern f32 D_800A1D54;

f32 func_150F3A20(s32 arg0, f32 arg1) {
    f32 var_f2;

    if (arg1 < -5.0f) {
        var_f2 = (arg1 * D_800A1D50) + D_800A1D54;
    } else {
        var_f2 = 0.75f;
    }
    return var_f2;
}

#ifdef NON_MATCHING
extern u16 D_800BEB30[];
extern u8 *D_800CC6A4; /* controller: +0 buttons (u16), +2 stick x, +3 stick y (s8) */
extern s32 D_800CC6A0;
extern u8 D_800CC68D;
extern u8 D_800CC1F3;
void func_150585F0(struct127 *); /* P209: the asm reads only a0 (this caller leaves 0.25f in a1) */
u8 func_150599C8(struct127 *arg0, u8 arg1, u16 arg2);
f32 func_1505A3A8(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4);
void func_15052590(struct127 *);
void func_15073FA0(void);

// player_swim_update: player interaction state 0x15 handler (entry 21 of D_800863B4, called as `(obj)` by
// func_1504A730 / func_15022A40). Reads the controller (D_800CC6A4, cleared when the D_800DDE3C / D_800DDDC8 gate
// of player D_800C3E78 holds). Stunned: drops the carried object (unk13C = 100 + index). Entry (unk102 == 0): heading
// from the stick (func_1505A630 / func_1505A5CC), may grab object D_800CC68D, dives below unk118. Then each frame:
// stick y / buttons 0x8000 / 0x4000 / 0x10 steer pitch (unkB8), turn (unkC4 -> unk76) and speed (func_1505A3A8),
// gravity damping and clamps, the closest grabbable object (ids 0x9C / 0x9D) to D_800D154C (unk222), carry / drop
// sounds, the 0x2000 spawn (id 0x25, fewer than 5), surfacing near the floor, and the animation (func_1505E650).
void func_150F3A74(struct127 *self) {
    struct127 *pl;
    s32 i;
    s32 n;
    u16 heading;
    u16 btn;
    u16 anim;
    u8 who;
    f32 floor_h;
    f32 speed;
    f32 stick;
    f32 mag;
    f32 best;
    f32 d;
    f32 rate;
    f32 lim;
    f32 g;
    f32 vy;
    f32 c4;
    f32 anim_speed;

    floor_h = 0.0f;
    self->unkAB = 1;
    self->unk80 = 1;
    self->unk222 = 0;
    D_800CC288 = D_800BEB30[0];
    D_800CC6A4 = *(u8 **) D_800BE728[0];
    who = D_800C3E78;
    if (who <= D_80082FA0 && (&D_800DDE3C)[who] != 0 && 0.75f < (&D_800DDDC8)[who] && D_800E0B94 != 2) {
        /* input blocked */
        D_800CC6A4[2] = 0;
        D_800CC6A4[3] = 0;
        *(u16 *) D_800CC6A4 = 0;
        D_800CC288 = 0;
    }
    self->unkF8 |= 0x40;
    self->unk1CC = self->y_position;
    if (self->unk103 != 0) {
        self->unk103--;
    }
    if (self->stunned != 0) {
        func_150585F0(self);
        func_15059140(self);
        self->unk40 = (f32) ((s16) self->unk7A + 0x4000) * 0.0054931640625f; /* 360 / 65536 */
        if (self->unk13C != 0) {
            /* let go of the carried object */
            pl = &D_800CC2D0[self->unk13C - 100];
            pl->unk13D = 0;
            pl->unk232 = 0x21;
            pl->unk218 = NULL;
            pl->stunned = 0;
            pl->unkF8 &= ~0x400;
            pl->xz_velocity = self->xz_velocity;
            self->unk13C = 0;
        }
        return;
    }
    if (self->unk102 == 0) {
        /* entering: face the stick direction */
        self->in_water = 0;
        heading = func_1505A630((f32) ((s8 *) D_800CC6A4)[2], (f32) ((s8 *) D_800CC6A4)[3], 0);
        mag = func_1505A5CC((struct49 *) D_800CC6A4);
        if (*(u16 *) D_800CC6A4 & 0x10) {
            mag = 0.0f;
        }
        self->unk78 = self->unk7A;
        if (1.0f < mag) {
            self->unk78 = heading + D_800CC6A0;
        }
        self->unk232 = 7;
        self->unk44 = mag * 0.35f;
        self->unk218 = NULL;
        if ((D_800CC288 & 0xC000) || self->unk28 > 100.0f) {
            self->unk232 = 8;
            self->unk102 = 1;
        }
        func_15052590(self);
        if (D_800CC68D != 0) {
            if (self->unk28 > 30.0f) {
                /* grab object D_800CC68D - 100 */
                D_800D1580 = 0xFF010074;
                func_1506E8D8();
                func_1505959C(&D_800CC2D0[D_800CC68D - 100], D_800C3E78);
                self->unk102 = 1;
                self->unk13C = D_800CC68D;
            }
            self->y_velocity = 23.0f;
        }
        if (self->y_position < self->unk118) {
            self->unk102 = 1;
            self->unk86 = 1;
            self->y_velocity = -6.0f;
        }
        return;
    }
    speed = self->xz_velocity;
    if (60.0f < speed) {
        speed = 60.0f;
    }
    stick = ((s8 *) D_800CC6A4)[3] * 1.25f;
    btn = *(u16 *) D_800CC6A4 & 0x10;
    if (btn) {
        stick = 0.0f;
    }
    if (self->unk13C != 0) {
        if (!btn) {
            self->y_position -= 16.0f * D_800D1550[0];
        }
    } else {
        /* closest grabbable object (ids 0x9C / 0x9D) resting on the ground */
        best = 1000.0f;
        for (i = 0, pl = D_800CC2D0; i != 25; i++, pl++) {
            if (pl->interaction_state != 0 && pl->health != 0 && pl->unk28 == 0.0f && pl->unk232 != 0x21 &&
                (pl->id == 0x9C || pl->id == 0x9D)) {
                d = func_1505A6F8(D_800D154C, pl);
                if (d < best) {
                    self->unk222 = i;
                    best = d;
                }
            }
        }
    }
    if (stick < -90.0f) {
        stick = -90.0f;
    }
    if (90.0f < stick) {
        stick = 90.0f;
    }
    if (2100.0f < self->y_position) {
        if (-30.0f < self->y_velocity) {
            self->y_velocity -= 1.5f;
        }
        stick = 40.0f;
    }
    c4 = self->unkC4;
    self->unkC4 = c4 + ((f32) ((s8 *) D_800CC6A4)[2] - c4) * (0.2f * D_800D1550[0]);
    self->unk7E = 0x19;
    self->unk76 -= (s32) (self->unkC4 * D_800D1550[0] * 0.04f * ((100.0f - speed) * 0.015f) * 220.0f);
    func_150599C8(self, 8, self->unk76);
    self->target_speed = 0.0f;
    speed = 0.0f;
    if (self->y_position < self->unk118) {
        if (self->unk86 == 0) {
            self->unk86 = 1;
            self->xz_velocity = 0.0f;
            self->y_velocity = -6.0f;
        }
    } else if (self->unk86 != 0) {
        self->unk86 = 0;
        self->y_velocity = 9.0f;
    }
    rate = 1.3f;
    btn = *(u16 *) D_800CC6A4;
    if (!(btn & 0x10)) {
        if (btn & 0x8000) {
            self->target_speed = -22.0f;
            speed = 1.0f;
            rate = 1.8f;
            btn = *(u16 *) D_800CC6A4;
        }
        if (btn & 0x4000) {
            self->target_speed = 30.0f;
            if (self->y_velocity < 0.0f) {
                self->target_speed -= self->y_velocity * 0.6f;
            }
            speed = 1.5f;
            rate = 0.3f;
        }
    }
    func_1505A3A8(self->target_speed, self, speed, rate, 1);
    self->unk40 = (f32) ((s16) self->unk7A + 0x4000) * 0.0054931640625f; /* 360 / 65536 */
    self->gravity = stick * 0.000125f * (200.0f - self->xz_velocity);
    if (self->unk13C == 0) {
        if (26.0f < self->y_velocity) {
            self->y_velocity = 26.0f;
        }
        if (self->y_velocity < -34.0f) {
            self->y_velocity = -34.0f;
        }
    }
    lim = fabsf(stick * 0.5f);
    if (self->unk86 != 0) {
        lim *= 0.4f;
        self->gravity *= 0.6f;
    }
    g = self->gravity;
    vy = self->y_velocity;
    if (g == 0.0f) {
        if (fabsf(vy) < 1.5f) {
            self->y_velocity = 0.0f;
        } else if (0.0f < vy) {
            self->gravity = 1.6f;
        } else {
            self->gravity = -1.6f;
        }
    } else if (lim * 1.2f < vy && g < 0.0f) {
        self->gravity = 0.0f;
    } else if (vy < -lim * 1.5f && 0.0f < g) {
        self->gravity = 0.0f;
    }
    self->in_water = 10;
    if (*(u16 *) D_800CC6A4 & 0x10) {
        self->y_velocity = 0.0f;
        self->gravity = 0.0f;
        self->unkB8 += ((f32) ((s8 *) D_800CC6A4)[3] - self->unkB8) * 0.2f;
    } else {
        self->unkB8 = (self->y_velocity - 0.0f) * -2.0f;
        if (40.0f < self->unkB8) {
            self->unkB8 = 40.0f;
        } else if (self->unkB8 < -55.0f) {
            self->unkB8 = -55.0f;
        }
    }
    speed = self->y_velocity;
    D_800CC1F3 = 1;
    func_15059140(self);
    D_800CC1F3 = 0;
    if (self->unk13C != 0 && self->unk28 < 50.0f) {
        floor_h = 50.0f;
    }
    if (!(*(u16 *) D_800CC6A4 & 0x10)) {
        if (D_800CC68D != 0 && self->unk13C == 0 && D_800CC2D0[D_800CC68D - 100].unk28 == 0.0f) {
            /* pick up object D_800CC68D - 100 from the ground */
            self->y_velocity = 20.0f;
            self->y_position = D_800CC2D0[D_800CC68D - 100].y_position + 70.0f;
            func_1505959C(&D_800CC2D0[D_800CC68D - 100], D_800C3E78);
            self->unk13C = D_800CC68D;
            D_800D1580 = 0xFF010074;
            func_1506E8D8();
        }
        if (self->unk13C != 0) {
            if (self->unk25C & 2) {
                /* drop the carried object */
                self->unk25C &= ~2;
                pl = &D_800CC2D0[self->unk13C - 100];
                pl->unk13D = 0;
                pl->unk232 = 0x21;
                pl->unk218 = NULL;
                pl->stunned = 0;
                pl->unkF8 &= ~0x400;
                pl->xz_velocity = self->xz_velocity;
                self->unk13C = 0;
                self->y_velocity = 0.0f;
                D_800D1580 = 0x76;
                func_1506E8D8();
            }
        } else if ((D_800CC288 & 0x2000) && self->unk103 == 0 && D_800BE9F0 == 0x3C) {
            n = 0;
            for (pl = &D_800CC2D0[1]; pl != &D_800CC2D0[25]; pl++) {
                if (pl->interaction_state != 0 && pl->id == 0x25) {
                    n++;
                }
            }
            if (n < 5) {
                D_800D1580 = 6;
                self->unk103 = 4;
                func_15073FA0();
            }
        }
    }
    if (self->unk28 <= floor_h) {
        /* at the floor */
        self->xz_velocity *= 0.6f;
        if ((*(u16 *) D_800CC6A4 & 0x4000) || self->unk86 != 0 || self->unk13C != 0) {
            if (self->unk13C != 0) {
                if (self->y_velocity < -10.0f) {
                    D_800D1580 = 0xFF0100A7;
                    func_1506E5FC();
                    D_800D1580 = 0xFF060372;
                    func_1506E8D8();
                }
            } else if (self->y_position < 0.0f) {
                D_800D1580 = 0xFF010072;
                func_1506E8D8();
            }
            if (self->unk13C == 0) {
                self->y_velocity = 20.0f;
            } else if (self->unk86 == 0) {
                self->y_velocity = 38.0f;
            }
            stick = -80.0f;
        } else {
            self->unk102 = 0;
            self->y_velocity = speed * -1.0f;
            self->unkB8 = 0.0f;
            self->unk28 = 0.1f;
        }
    }
    if (!(*(u16 *) D_800CC6A4 & 0x10)) {
        self->unkB8 += 20.0f;
    } else {
        self->y_velocity = self->unkB8 * -0.35f;
    }
    if (self->unk86 != 0) {
        self->unk83 = 0;
        if (8.0f < fabsf(stick) || 7.0f < self->target_speed) {
            anim_speed = 1.0f;
        } else {
            anim_speed = 0.5f;
        }
    } else {
        anim_speed = func_150F3A20((s32) self, stick);
    }
    anim = 0xF;
    if (40.0f < self->unkB8 && 20.0f < stick) {
        anim = 0x11;
    }
    if (self->xz_velocity < 20.0f && self->target_speed <= 0.0f && stick == 0.0f) {
        anim = 0x18;
    }
    if (self->xz_velocity < 0.0f) {
        anim = 0x1F;
    }
    if (self->unk13C != 0) {
        anim = 0x17;
        anim_speed += 0.2f;
    }
    func_1505E650(self, anim, anim_speed, 9.0f, 0.0f, 0.0f, 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F3A74.s")
#endif

#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);

void func_150F4970(struct108 *arg0) {
    s32 temp_t0;

    if (arg0->unk23E == 0x3B) {
        func_1509BFB0(0, 0x405C, 1);
        if ((arg0->unk2C != 0x100) && (arg0->unk6C8 == 0)) {
            if (func_15123934(arg0, 8, 0, 0, 0) != 0) {
                temp_t0 = arg0->unk84 | 0x300000;
                arg0->unk84 = temp_t0;
                arg0->unk84 = temp_t0 & ~4;
                arg0->unk1B4 = 1;
                arg0->unk1E0 = 3;
                func_15124B18(arg0);
            }
            arg0->unk134 = 0;
            arg0->unk348 = 125.0f;
            arg0->unk34C = 125.0f;
            arg0->unk374 = 220.0f;
            arg0->unk190 = 30.0f;
        } else {
            arg0->unk190 = 0.0f;
        }
    } else if ((arg0->unk2C == 8) && (arg0->unk6C8 == 0)) {
        func_151239CC(arg0, 0);
        func_1509BFB0(0, 0x405C, 0);
    }
    if ((func_1509BE40(1, 0x4054, 6, 0x9000) != 0) && (func_1509BE40(1, 0x405E, 6, 0x9000) == 0)) {
        arg0->unk84 |= 0x80000000;
        return;
    }
    arg0->unk84 &= 0x7FFFFFFF;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1207F0/func_150F4970.s")
#endif