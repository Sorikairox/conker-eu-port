void func_1506045C(struct127 *, s32, s32, s32, s32);
s32 func_1506E46C(struct127 *, s32 *, s32);
void func_151AE814(u8 *);
void func_151C7450(u8 *, u8, s32);
void func_15060A30(s32, struct127 *);
void func_15052408(struct127 *);
void func_1506160C(struct127 *, u8, u8, u8, u8);
void func_1506AF74(void);
void func_100109D0(struct127 *);
extern s32 D_800CC3C8;
extern u8 D_800CC69C;
extern char D_800997E8[];
s32 func_1000EFB4(struct_eu_sfx *, s32, s32 *, struct11 *, s32, s32 *, u16 *);

/* P64: f32 bits of an argument that a prototype declares s32 (func_1506045C's height) */
#define F298_BITS(f) (*(s32 *)&(f))

/* P64: the jump / swim / glide handler of a walking record, once per walk-handler call (func_1505A9AC family).
 * `pad` = the controller: +0 buttons (0x8000 = A / jump, 0x4000 = B, 0x2000 = Z, 0x10), +3 stick y (s8).
 * D_800CC288 = the buttons pressed this frame. ctl = rec->unk31C. Sections:
 *   1. guards: stunned / dead stop the record (target speed 0); nothing while ctl +0x46 > 0, ctl +0x36 >= 100 or
 *      ctl +0x6B. `height` = rec +0x28 (ground clearance), -150 with ctl +0x4E == 2 (carried state), 0 with
 *      ctl +0x4F == 2, +50 while rising.
 *   2. in water (rec +0xAD, not ctl +0x95, anim != 0x262): surface jump-out (A near the surface), B / swim
 *      strokes, treading water; animation and func_1506045C (in-water move); returns.
 *   3. rec +0x137 == 1 (hanging): stick up climbs (0xEA), stick down drops (0x38), A / ctl +0x84 lets go (0x40);
 *      returns when an animation was started.
 *   4. jump start: riding a record of id 0x28 (not level 0x23) / 0x8A / 0x23 (rec +0x65), or on the ground / ctl
 *      +0x55: A starts a jump (0x32, the run jump 0x37 / 0x19E, the high jump 0x279 with ctl +0x17, the item jump
 *      0x43 with ctl +8, the super jump with ctl +0x1A, the Z long jump 0xEB) with floor-kind and D_800CC69C
 *      (low gravity) adjustments; a ride is left (func_15052F58) with a push-off speed.
 *   5. func_1506045C (air move), then the double jump (ctl +0x98 / +0x95: 0x37 again), the high-fall 0x3B, and
 *      the helicopter glide (ctl +0x31: start 0xE9 with the sound 0x61E, then the spin-down counter); the
 *      animation; the sound of section 4 (func_15060A30); releasing A cuts a rising jump (gravity 6.2). */
void func_1505F298(struct127 *rec, u8 *pad) {
    struct126 *ctl;
    s32 sound = 0;         /* sp88: sound id resolved by func_1506E46C */
    f32 speed = 1.0f;      /* sp84: animation speed */
    f32 jump_v;            /* sp80 */
    u8 glide = rec->unk31C->unk31;
    f32 blend = 0.0f;      /* f12 */
    f32 height;            /* f14 */
    s32 buttons;           /* sp68 */
    s32 anim;
    s32 ride;              /* id + 1 of the ridden record */
    s32 ride_jump;
    s32 jumped;
    u16 a;

    /* 1. guards */
    if (rec->stunned != 0 || rec->health == 0) {
        rec->target_speed = 0.0f;
        return;
    }
    ctl = rec->unk31C;
    if (*(s16 *)((u8 *)ctl + 0x46) > 0 || ctl->unk36 >= 100 || ctl->unk6B != 0) {
        return;
    }
    height = rec->unk28;
    if (ctl->unk4E == 2) {
        height = height - 150.0f;
    } else if (ctl->pad4F[0] == 2) {
        height = 0.0f;
    } else if (rec->y_velocity > 0.0f) {
        height += 50.0f;
    }
    if (rec->unk110 != 0) {
        buttons = *(u16 *)pad & ~0x2000;
    } else {
        buttons = *(u16 *)pad;
    }

    /* 2. in water */
    if (rec->in_water != 0 && ctl->unk95 == 0 && rec->unk84.uh != 0x262) {
        anim = 0; /* the asm reads a stack slot here when in_water != 1 (never written on that path): UNVERIFIED */
        if (rec->in_water == 1) {
            blend = 2.0f;
            anim = 0;
            if ((D_800CC288 & 0x8000) && (D_800BE9F0 != 0x29 || (s16)ctl->unk8 <= 0)
                && rec->unk118 - 60.0f - 30.0f < rec->y_position) {
                /* jump out of the water */
                func_15052408(rec);
                rec->unk31C->unk31 = 0;
                ctl = rec->unk31C;
                anim = 0x32;
                blend = 0.0f;
                if (ctl->pad79[2] != 7 && ctl->pad79[2] != 8) {
                    ctl->unk31 = 1;
                }
                ctl = rec->unk31C;
                a = ctl->unk4C;
                rec->unk78 = a;
                rec->unk7A = a;
                rec->unk76 = a;
                if (*(u16 *)((u8 *)ctl + 0x68) != 0 && (((a - *(u16 *)((u8 *)ctl + 0x68)) + 0x4000) & 0x8000)) {
                    rec->xz_velocity = 0.0f;
                    rec->disable_run = 0xFF;
                }
                rec->unkAE = 0xC;
                rec->y_velocity = 46.0f;
                rec->unk81 = 2;
                rec->unk83 = 0;
                rec->gravity = 3.3f;
            }
            rec->target_speed = 0.0f;
            if ((D_800CC288 & 0x4000) && !(*(u16 *)pad & 0x10)) {
                ctl = rec->unk31C;
                if ((s8)ctl->pad17[0xB] < 0x69) {
                    ctl->pad17[0xB] = 0xF;
                }
            }
            ctl = rec->unk31C;
            if ((rec->xz_velocity > 2.0f && ctl->pad17[0xA] != 0)
                || (ctl->pad17[0xA] == 0
                    && ((s8)ctl->pad17[0xB] > 0 || (!(*(u16 *)pad & 0x10) && (*(u16 *)pad & 0x4000))))) {
                if (anim != 0x32) {
                    /* swim stroke */
                    blend = 9.0f;
                    rec->unk83 = 0;
                    if (rec->unk118 - 60.0f < rec->y_position) {
                        speed = 1.2f;
                        anim = 0x22;
                        rec->target_speed = 15.0f;
                    } else {
                        speed = 1.2f;
                        anim = 0xCE;
                        rec->target_speed = 23.0f;
                    }
                }
            }
        }
        if (anim == 0) {
            /* treading water */
            blend = 10.0f;
            speed = 1.2f;
            anim = 0xD1;
            if (rec->unk118 - rec->y_position < 70.0f) {
                anim = 0xCC;
                speed = 0.9f;
            }
            rec->target_speed -= 0.2f;
            if (rec->target_speed < 0.0f) {
                rec->target_speed = 0.0f;
            }
        }
        ctl = rec->unk31C;
        if (rec->in_water != 0 && rec->unk13C != 0) {
            blend = 7.0f;
            anim = 0xCB;
        }
        if (ctl->unk11A != 0 || (ctl->unk78 != 0 && ctl->unk78 != 0x27)) {
            func_1506045C(rec, 0, 0, F298_BITS(height), 1);
        }
        if (anim != 0) {
            func_1505E650(rec, anim, speed, blend, 0.0f, 0.0f, 0);
        }
        return;
    }

    /* 3. hanging */
    if (rec->unk137 == 1) {
        anim = 0;
        if (ctl->pad53 == 0) {
            if ((s8)pad[3] > 0x32) {
                speed = 2.2f;
                ctl->unk54 = 0xC;
                anim = 0xEA;
                rec->unk137 = 0;
                rec->disable_run = 0x10;
                rec->unk81 = 1;
                rec->gravity = 5.0f;
                rec->y_velocity = 48.0f;
            } else if ((s8)pad[3] < -0x32) {
                anim = 0x38;
                rec->unk137 = 0;
                rec->gravity = 3.5f;
            }
        }
        if ((D_800CC288 & 0x8000) || rec->unk31C->unk84 != 0) {
            rec->unk137 = 2;
            anim = 0x40;
            speed = 3.0f;
        }
        if (anim != 0) {
            func_1505E650(rec, anim, speed, 4.0f, 0.0f, 0.0f, 0);
            return;
        }
    }

    /* 4. jump start */
    ride = 0;
    ride_jump = 0;
    anim = 0;
    if (rec->unk65 != 0) {
        u8 id = ((u8 *)&D_800CC3C8)[rec->unk65 * 0x32C]; /* = D_800CC2D0[rec->unk65 - 1].id */
        if ((id == 0x28 && D_800BE9F0 != 0x23) || id == 0x8A || id == 0x23) {
            ride = id + 1;
            ride_jump = 1;
        }
    }
    if (ride != 0 || height <= 0.0f || rec->unk31C->unk55 != 0) {
        rec->unk137 = 0;
        jumped = 0;
        jump_v = 0.0f;
        if ((D_800CC288 & 0x8000) && rec->unk31C->unk11A != 1 && rec->unk31C->unk11A != 3
            && (ride != 0 || (rec->unk13C < 100 && rec->disable_jump == 0 && rec->disable_run != 0xFF))) {
            jumped = 1;
            jump_v = 15.0f;
            rec->unk100 &= 0xFE;
            if (ride_jump != 0) {
                func_1506160C(rec, 1, 0xFF, 0, 0);
            }
            ctl = rec->unk31C;
            if (ctl->pad17[0] != 0) {
                /* high jump */
                jump_v = 0.0f;
                anim = 0x279;
                speed = 1.25f;
                rec->unk84.uh = 0;
                rec->disable_jump = 0xA;
                rec->disable_run = 0xFF;
                rec->unk83 = 0xFF;
            } else if ((s16)ctl->unk8 != 0) {
                /* item jump */
                rec->unk83 = 0xFF;
                rec->disable_run = 0xFF;
                func_1505E650(rec, 0x43, 1.3f, 2.0f, 0.0f, 0.0f, 0);
                anim = 0;
                jumped = 0;
            } else {
                anim = 0x32;
                if (ctl->pad17[3] != 0) {
                    /* super jump */
                    jump_v = 0.0f;
                    rec->disable_run = 0xFF;
                    rec->unk81 = 1;
                    rec->y_velocity = 47.0f;
                    rec->gravity = 6.0f;
                } else if (!(buttons & 0x2000) || ctl->pad79[2] == 7 || ctl->pad79[2] == 8) {
                    /* normal / run jump */
                    if (rec->disable_run != 0) {
                        rec->disable_run = 0;
                        a = ctl->unk4C;
                        rec->unk76 = a;
                        rec->unk7A = a;
                    }
                    anim = 0x32;
                    if (rec->xz_velocity < 9.0f) {
                        jump_v = 0.0f;
                        ctl->unk31 = 1;
                    } else {
                        speed = 0.8f;
                        ctl->unk31 = 2;
                        anim = 0x37;
                        if (rec->unk31C->unk78 == 0x21) {
                            anim = 0x19E;
                            speed = 1.4f;
                        }
                    }
                    if (rec->unk31C->pad79[2] == 7 || rec->unk31C->pad79[2] == 8) {
                        rec->unk31C->unk31 = 0;
                    }
                    if (rec->unk31C->unk4E == 1) {
                        rec->y_velocity = 40.0f;
                    } else {
                        rec->y_velocity = 59.0f;
                    }
                    if (rec->unk31C->unk4E == 2) {
                        rec->y_velocity = 80.0f;
                        sound = 0x7E2;
                    }
                    rec->gravity = 4.0f;
                    if ((rec->unk184 & 0x1F) == 0xC) {
                        rec->y_velocity *= 0.7f;
                    }
                    if ((rec->unk184 & 0x1F) == 0x13) {
                        anim = 0x32;
                        rec->y_velocity *= 0.55f;
                    }
                    if (D_800CC69C != 0) {
                        rec->unk81 = 0x82;
                    } else {
                        rec->unk81 = 2;
                    }
                } else {
                    /* Z long jump */
                    if (D_800CC69C == 0) {
                        rec->unk81 = 1;
                    } else {
                        rec->unk81 = 0x81;
                    }
                    jump_v = 0.0f;
                    speed = 1.08f;
                    rec->disable_run = 0x17;
                    rec->unk83 = 0x64;
                    anim = 0xEB;
                    if (D_800CC69C != 0) {
                        rec->xz_velocity = rec->xz_velocity;
                        rec->y_velocity *= 1.4f;
                        rec->gravity = 3.8f;
                    }
                }
            }
        }
        if (jumped != 0) {
            if (sound != 0 && func_1506E46C(rec, &sound, 1) != 0) {
                func_15060A30(sound, rec);
            }
            glide = 0;
            if (ride != 0) {
                /* push off the ridden record */
                rec->xz_velocity = 20.0f;
                if (ride == 0x29) {
                    func_15052F58(rec->unk65 - 1, 0xE);
                } else if (ride == 0x8B) {
                    func_15052F58(rec->unk65 - 1, 5);
                    rec->xz_velocity = 30.0f;
                    if (D_800BE616 != 0) {
                        rec->unk7A = 0x3000;
                        if (rec->z_position > 0.0f) {
                            rec->unk7A = 0xB000;
                        }
                    }
                } else if (ride == 0x24) {
                    func_15052F58(rec->unk65 - 1, 0xE);
                    rec->xz_velocity = 27.0f;
                }
                rec->unk31C->unk30 = 0;
                rec->immune = 0x14;
                rec->unk76 = rec->unk7A + 0x1200;
                rec->unk65 = 0;
                rec->disable_run = 0xFF;
                rec->y_velocity = 30.0f;
                rec->unk31C->unk31 = 0;
            }
            sound = 0;
            rec->unk31C->unk55 = 0;
            if (rec->unk31C->unk4E != 0) {
                rec->unkA9 = 5;
            }
            if (anim != 0xEB && anim != 0x279) {
                rec->unk83 = 0;
                rec->unk28 = 80.0f;
            }
            if (rec->unk31C->unk4E != 2) {
                func_1505E650(rec, anim, speed, 2.0f, jump_v, 0.0f, 0);
            }
            height = 25.0f;
            rec->unkB8 = 0.0f;
            rec->unk110 = 0;
            rec->unk100 &= 0x53;
        }
    }

    /* 5. in the air */
    func_1506045C(rec, buttons, D_800CC288, F298_BITS(height), 0);
    anim = 0;
    ctl = rec->unk31C;
    blend = 2.0f;
    if ((ctl->pad98[0] != 0 || ctl->unk95 != 0) && rec->disable_jump == 0 && (D_800CC288 & 0x8000)) {
        /* double jump */
        a = ctl->unk4C;
        rec->unk7A = a;
        rec->unk76 = a;
        ctl->unk31 = 1;
        rec->unk80 = 0xA;
        rec->unk83 = 0;
        rec->unk100 |= 8;
        rec->disable_run = 0;
        rec->unk100 &= 0xDE;
        anim = 0x37;
        speed = 1.3f;
        if (rec->in_water == 0) {
            rec->y_velocity = 40.0f;
            rec->gravity = 3.2f;
        }
        rec->xz_velocity = rec->unk44 * 0.6f + 15.0f;
        if (rec->unk44 < 4.0f) {
            rec->unk7A = rec->unk76 = rec->unk76 + 0x8000;
        }
        rec->unk31C->unk95 = 0;
        rec->unk31C->unk97 = 0;
        if (rec->unk31C->pad98[0] != 0) {
            func_151AE814((u8 *)rec);
            anim = 0x37;
            blend = 2.0f;
        }
        rec->unk31C->unk54 = 0;
    } else if ((D_800CC288 & 0x8000) && ctl->unk4E == 0) {
        /* high fall */
        if (rec->unk84.uh != 0x3B && rec->unk84.uh != 0x3C && rec->unk137 == 0 && rec->unk13C == 0
            && ctl->unk95 == 0 && ctl->unk31 == 0 && height > 55.0f) {
            if (rec->unk118 != -10000.0f && rec->unk118 - rec->unk180 > 100.0f) {
                rec->unk81 = 1;
                rec->disable_run = 0x78;
                rec->unk137 = 0;
                anim = 0x3B;
                rec->gravity = 6.0f;
                rec->unk1CC = rec->y_position;
            }
        }
    }
    if (D_800BE616 == 0 && glide != 0 && rec->in_water == 0 && rec->unk13C <= 100 && rec->id != 0x96) {
        ctl = rec->unk31C;
        if (ctl->unk31 != 0 && ctl->unk4E == 0) {
            if (ctl->unk31 < 3) {
                /* helicopter glide start */
                if ((D_800CC288 & 0x8000) && rec->unk28 > 1.0f) {
                    blend = 6.0f;
                    anim = 0xE9;
                    rec->xz_velocity *= 0.3f;
                    ctl->unk31 = 3;
                    rec->y_velocity = 0.0f;
                    rec->unk81 = 1;
                    rec->gravity = 1.0f;
                    rec->unk1CC = rec->y_position;
                    if (rec->unk84.uh != 0xE9) {
                        func_100109D0(rec);
                        func_1000FA64(0x61E, rec->x_position, rec->y_position, rec->z_position, 0x7FFF, 0x1F4, 0xC8,
                                      (s32)func_1000EFB4, rec, (s32)D_800997E8, 0, 0);
                        func_151C7450((u8 *)rec, 0xFF, 1);
                        anim = 0xE9;
                        blend = 6.0f;
                    }
                }
            } else {
                /* gliding: count up; A held keeps it to 0x3E frames, else 0x13 */
                ctl->unk31 += D_800BE9A0;
                if (rec->unk31C->unk31 < 0xD) {
                    rec->y_velocity = 8.0f;
                }
                if (rec->unk31C->unk31 < 0x11) {
                    rec->animation_speed += 0.25f;
                } else {
                    rec->animation_speed += (0.6f - rec->animation_speed) * 0.1f;
                }
                anim = 0xE9;
                speed = rec->animation_speed;
                rec->unk31C->pad3C[0] = 6;
                if ((!(*(u16 *)pad & 0x8000) && rec->unk31C->unk31 >= 0x13) || rec->unk31C->unk31 >= 0x3E) {
                    rec->disable_run = 0xFF;
                    rec->unk100 = 0x55;
                    rec->unk31C->unk31 = 0;
                    rec->gravity = 4.5f;
                    func_1506AF74();
                    blend = 2.0f;
                    anim = 0;
                } else {
                    rec->unk80 = 1;
                    rec->unkAA = 0x4B;
                    rec->unk83 = 1;
                    if (rec->y_velocity < -8.0f) {
                        rec->y_velocity = -8.0f;
                    }
                }
            }
        }
    }
    if (anim != 0) {
        func_1505E650(rec, anim, speed, blend, 0.0f, 0.0f, 0);
    }
    if (sound != 0) {
        func_15060A30(sound, rec);
    }
    if ((rec->unk81 & 7) == 2 && !(*(u16 *)pad & 0x8000)) {
        rec->unk81 = rec->unk81 - 1;
        rec->gravity = 6.2f;
    }
}
