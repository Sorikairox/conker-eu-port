#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150D7930(u8 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
        case 1:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0xFF;
            arg0[0x29] = 0;
            arg0[0x2A] = 0;
            return;
        case 2:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0xFF;
            arg0[0x29] = 0;
            arg0[0x2A] = 0;
            return;
        case 3:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0;
            arg0[0x29] = 0xFF;
            arg0[0x2A] = 0;
            return;
        default:
        case 0:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        }
    }
}

void func_150D79EC(u8 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
        case 1:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        case 2:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0xFF;
            arg0[0x29] = 0;
            arg0[0x2A] = 0;
            return;
        case 3:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0;
            arg0[0x29] = 0xFF;
            arg0[0x2A] = 0;
            return;
        default:
        case 0:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        }
    }
}

void func_150D7A9C(u8 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0x36) {
        switch (*arg1) {
        case 1:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        case 2:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        case 3:
            *(s32 *)(arg0 + 0x58) |= 2;
            arg0[0x28] = 0;
            arg0[0x29] = 0xFF;
            arg0[0x2A] = 0;
            return;
        default:
        case 0:
            *(s32 *)(arg0 + 0x58) &= ~2;
            return;
        }
    }
}

void func_150D7B40(s32 arg0) {
    if (arg0 == 0) {
        D_800D9D30 += D_800BE9E4 << 6;
    }
}

#ifdef NON_MATCHING
extern s32 *D_80088CA0[2];
s32 func_1510D66C(s32, s32 *, s32, s32);

// anim_segments_set: points segments 2..7 at textures (func_1510D66C, mode 3) taken from the two 5-entry texture id
// tables of D_80088CA0 (segments 2..5 from the first, 6 and 7 from the second): entry (D_800D9D30 >> 8) + 13 per
// segment, mod 5, so the frames cycle with the D_800D9D30 clock (func_150D7B40). Returns the advanced display list.
Gfx *func_150D7B6C(Gfx *gdl) {
    s32 *tabs[2];
    s32 size[4];
    s32 tab;
    s32 frame;
    s32 seg;
    s32 tex;

    tabs[0] = D_80088CA0[0];
    tabs[1] = D_80088CA0[1];
    tab = 0;
    frame = D_800D9D30 >> 8;
    for (seg = 2; seg < 8; seg++, frame += 13) {
        if (seg >= 6) {
            tab = 1;
        }
        tex = func_1510D66C(tabs[tab][frame % 5], size, 3, 0);
        gSPSegment(gdl++, seg, tex);
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105140/func_150D7B6C.s")
#endif

#ifdef NON_MATCHING
s32 func_150889D8(struct127 *, s32);
s32 func_15088A68(s32, s32, s32);
s32 func_15088B08(s32, s32);

void func_150D7CA0(struct127 *arg0, s32 arg1) {
    s32 sp48;
    s32 sp40;
    s32 sp38;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_t0;
    struct126 *temp_v0;
    struct126 *temp_v0_5;
    struct126 *temp_v0_6;

    var_t0 = 0;
    temp_v0 = arg0->unk31C;
    if ((temp_v0 == NULL) || ((*(s8 *)((u8 *)temp_v0 + 0x1AE)) > 0)) {
        switch (arg1) {                             /* irregular */
        default:
            var_t0 = 1;
            if (arg1 != 0x33) {
                return;
            }
        case 50:
            temp_v1 = (var_t0 * 0x1E) + 0x1E;
            sp38 = temp_v1;
            temp_v0_2 = func_1506C460(arg0->unk40, 310.0f, 0.0f, 0.0f, (u8) temp_v1, 0xD, 0.0f, 1.0f, 0, 1, var_t0 == 0);
            if (temp_v0_2 != 0) {
                (*(s8 *)((u8 *)temp_v0_2 + 0x124)) = (s8) (D_800C3E78 + 1);
            }
            if ((temp_v0_2 != 0) && (temp_v1 != 0x1E)) {
                (*(s8 *)((u8 *)temp_v0_2 + 0x221)) = -1;
                sp40 = temp_v0_2;
                temp_v0_3 = func_150889D8(arg0, temp_v0_2);
                if (temp_v0_3 != -1) {
                    sp48 = temp_v0_3;
                    temp_v0_4 = func_15088B08(temp_v0_2, temp_v0_2);
                    if (temp_v0_4 != -1) {
                        func_15088A68(sp48, temp_v0_4, sp48);
                    }
                }
            }
            temp_v0_5 = arg0->unk31C;
            if (temp_v0_5 != NULL) {
                (*(s8 *)((u8 *)temp_v0_5 + 0x1AE)) = (s8) ((*(s8 *)((u8 *)temp_v0_5 + 0x1AE)) - 1);
            }
            break;
        case 48:
        case 49:
            if (temp_v0 != NULL) {
                (*(s16 *)((u8 *)temp_v0 + 0x12C)) = 0x78;
                temp_v0_6 = arg0->unk31C;
                (*(s8 *)((u8 *)temp_v0_6 + 0x1AE)) = (s8) ((*(s8 *)((u8 *)temp_v0_6 + 0x1AE)) - 1);
                func_10010154(0x628U, arg0, 0x7FFF, 0x1F4, 0x3E8U);
                return;
            }
            break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105140/func_150D7CA0.s")
#endif
#ifdef NON_MATCHING
u8 *func_15034174(u8 *arg0);
s32 func_1505C7D8(struct127 *self, s32 skip);
f32 func_1505A3A8(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4);
f32 func_15052F9C(struct127 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
s32 func_1505327C(struct127 *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4);
void func_10010FFC(s32, s32, s32, s32, s32, u8 *);
void func_1001091C(u8 *arg0, s32 arg1);
s32 func_150535F4(struct127 *arg0);

// carried_object_update: interaction state 0x20 handler (entry 32 of D_800863B4, called as `(obj)` by
// func_1504A730) of a liftable object (id 0x48 rides on a partner object of kind 0x7A; id 0x7F is held). While a
// player holds it (unk13C, player D_800CC2D0[unk124] with unk31C +0x4E set) it copies the player's position block,
// turn and speed; otherwise it falls / spins (func_1505A3A8 / func_15059140), lets a player land on it
// (func_15052F9C when unk232 == 4) or picks a player to latch on (func_1505327C). Then the scale bounce, spin
// angle, carry height (player unkCC) and the rolling sound (0x678), and finally func_150535F4.
void func_150D7E38(struct127 *self) {
    struct127 *pl;
    s16 *dst;
    s16 *src;
    s32 id;
    s32 partner;
    s32 i;
    s32 vol;
    u8 slot;
    u16 angle;
    u16 old;
    s16 h;
    s16 h2;
    f32 speed;
    f32 turn;
    f32 vel;
    f32 dist;
    f32 top;
    f32 boost;

    slot = self->unk124;
    speed = self->xz_velocity;
    id = self->id;
    partner = -1;
    if (id == 0x48) {
        u8 *other = func_15034174((u8 *) self);
        if (other != NULL) {
            partner = other[6];
        }
    }
    self->unkB0 = 0x19;
    if (self->unkE4 != 0) {
        self->unk90 = self->unkE4;
    }
    if (self->unk13C != 0 && ((u8 *) D_800CC2D0[slot].unk31C)[0x4E] != 0) {
        /* held: follow the player */
        pl = &D_800CC2D0[slot];
        angle = pl->unk7A;
        self->unkE4 = 0;
        self->unk180 = pl->unk180;
        self->unk184 = pl->unk184;
        dst = (s16 *) ((u8 *) self + 0x18C);
        src = (s16 *) ((u8 *) pl + 0x18C);
        for (i = 0; i < 9; i++) {
            dst[i] = src[i];
        }
        self->gravity = 6.0f;
        turn = pl->unk54 * 0.45f;
        self->unk44 = pl->unkC4;
        if (id == 0x7F) {
            pl->unk184 &= ~0x1F;
            pl->immune = 0x14;
            pl->unk184 |= 4;
            self->y_position = pl->y_position;
            self->x_position += (pl->x_position - self->x_position) * 0.5f;
            self->z_position += (pl->z_position - self->z_position) * 0.5f;
            pl->disable_jump = 10;
            if (((u8 *) pl->unk31C)[0x4F] == 2) {
                boost = pl->unk44 * 1.35f;
                if (speed < boost) {
                    speed = boost;
                }
                pl->unkAA = 0x46;
            }
        } else {
            self->y_velocity = 0.0f;
        }
        old = self->unk21C;
        self->unk21C = old + (s16) (angle - old) / 3;
        self->unk7A = old;
        self->unk76 = old;
        self->xz_velocity = pl->xz_velocity;
        if (self->unkD0 != 0) {
            func_1505C7D8(self, D_800C3E78);
        }
    } else {
        self->unk21C = self->unk7A;
        if (self->unk13C != 0) {
            /* just let go: a stunned player throws it */
            if (D_800CC2D0[slot].stunned != 0) {
                self->target_speed = 15.0f;
                self->y_velocity = 80.0f;
            }
            self->unk13C = 0;
        }
        slot = D_800C3E78;
        self->unk65 = 0;
        self->unkE4 = self->unk90;
        func_1505A3A8(0.0f, self, 0.0f, 0.5f, 1);
        vel = self->xz_velocity;
        self->stunned = 0x1E;
        func_15059140(self);
        self->xz_velocity = vel;
        turn = (self->unkC4 - self->unk44) * 0.8f;
        if (self->unk232 == 4) {
            if (id == 0x48) {
                D_800CC2D0[0].unk1E4 = 1; /* EU 800CC8D4 */
            }
            func_15052F9C(self, 50.0f, 0x17, 4, 0, 5, 0, 0, 0, 0);
            /* func_15052F9C returns nothing; the asm tests its leftover v0: self->unk124 when no player landed
               (or self is not in state 0x20), self->unk7A after a landing (unk13C set) in state 0x20 */
            if ((self->unk13C != 0 && self->interaction_state == 0x20) ? self->unk7A != 0 : self->unk124 != 0) {
                return;
            }
        } else {
            for (i = 0; i < 2; i++) {
                pl = &D_800CC2D0[i];
                if (pl->interaction_state == 1 && ((u8 *) pl->unk31C)[0x78] == 0 &&
                    ((u8 *) pl->unk31C)[0x11A] == 0 && (D_800CC268 & (1 << i)) && pl->y_velocity < 0.0f) {
                    self->unk124 = i;
                    dist = 39.0f;
                    if (id == 0x48) {
                        pl->stunned = 0;
                        dist = 0.0f;
                    }
                    func_1505327C(self, dist, 3.0f, 4, -1);
                }
            }
        }
    }
    self->immune = 0xFF;
    self->unk28 = self->y_position - self->unk180;
    if (id == 0x48) {
        /* riding its partner (kind 0x7A) */
        if (partner == 0x7A) {
            self->unkF8 |= 0x10000;
            top = self->unk180 + 180.0f;
            func_15058EA4(self, top + 10.0f, 1.2f, top, -1.1f, 4.0f, -4.0f);
            if (self->unk13C != 0) {
                D_800CC2D0[self->unk124].unkCC = 0x1E;
            }
            self->unkC4 = -self->y_velocity;
            self->unk40 = (f32) self->unk7A * 0.0054931640625f; /* 360 / 65536 */
        }
    } else {
        func_1506B100(0, 2.0f, 4.0f);
        if (self->unk28 > 75.0f) {
            if (self->unk102 < 30) {
                self->unk102++;
            }
        } else if (self->unk102 < 10) {
            self->unk102 = 0;
        }
        if (self->unk102 > 10) {
            /* dropped (player on the ground / in water / grabbed elsewhere) */
            pl = &D_800CC2D0[slot];
            if (pl->unk28 == 0.0f || self->in_water != 0 ||
                (self->unk124 != 0 && ((u8 *) pl->unk31C)[0x4F] == 2)) {
                if (self->unk13C != 0) {
                    D_800CC2D0[self->unk124].unkCC = 0;
                    ((u8 *) D_800CC2D0[self->unk124].unk31C)[0x4E] = 0;
                    D_800CC2D0[self->unk124].in_water = 0;
                    D_800CC2D0[self->unk124].gravity = 4.0f;
                }
                func_100109D0(self);
                func_10010FFC(0, 0x51, 0x6D60, 0, 0, (u8 *) self);
                self->health = 0;
            }
        }
        if (self->y_scale < 1.0f) {
            self->y_scale += 0.05f;
        }
        if (self->unk28 == 0.0f) {
            self->target_speed = 0.0f;
            self->unkBC *= 0.5f;
        }
        if (self->target_speed == 0.0f) {
            self->unkC4 = self->unk44 + turn;
        } else {
            self->unkC4 += self->target_speed;
            if (self->unkC4 < 0.0f) {
                self->unkC4 += 360.0f;
            } else if (self->unkC4 > 360.0f) {
                self->unkC4 -= 360.0f;
            }
        }
        if (self->unk13C != 0) {
            h = fabsf(self->unkC4 * 0.7f) + 44.0f;
            self->unkC8 = h;
            h2 = h + 44.0f;
            D_800CC2D0[self->unk124].unkCC = h2 * self->y_scale;
        } else {
            self->unkC8 = 44.0f;
        }
        if (speed > 0.2f && self->unk28 < 10.0f && self->health != 0 && D_800C35EA != 1) {
            vol = 1000.0f * speed;
            if (vol > 0x4650) {
                vol = 0x4650;
            }
            if (func_100107F8(self) == 0) {
                func_10010154(0x678, self, vol, 0x3E8, 0x7D0);
            } else {
                func_1001091C((u8 *) self, vol);
            }
        } else {
            func_100109D0(self);
        }
        func_15052490(self, self->unk76, speed, 0.55f);
    }
    func_150535F4(self);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_105140/func_150D7E38.s")
#endif
