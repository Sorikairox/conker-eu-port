//DROP s32 func_15051558(struct127 *, f32, f32, u16);
//HOIST void func_15051558(struct127 *, f32, f32, u16);
s32 func_15088360(s32, struct127 *);
void func_1510FDA0(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, s32 arg4, f32 *arg5, f32 *arg6);
extern f32 D_80099490[];
void func_1505A250(f32, f32, f32, f32 *, f32 *);
f32 func_1505210C(u8 *, f32, f32, f32 *, f32);

/* P60: per-frame ground push / slide of a walking record (x / z = the position it moved to this frame, angle = the
 * stick direction). On land: the floor's push (func_1510FDA0: conveyor / slope force fx / fz, its speed and the
 * slide dx / dz) when standing (height +0x28 <= 0) or sliding (+0x110), or always on ice (ctl +0x4E == 2). A slide
 * starts (D_800CC69C = 1) on a strong push or floor kind 4 (not kind 3, not while carried by record ids 8 / 0x49):
 * the record then turns to the slope (+0x112), sets the slide mode +0x110 (3 = jump-off slide 0x28E, 1 = slide
 * forward 0x101, 2 = backwards 0xD0) and its animation; the speed +0x3C and heading are rebuilt when the slide
 * flag +0x162 changes. The push goes through func_1505A250 into +0x164 / +0x168, the slide decays (+0x16C / +0x170,
 * x 0.85); a backwards slide that stops turns the record around (animation 0xA5). The landing tilt (+0xC4 / +0xB8)
 * follows the push (func_1505210C) and, on ice, a wobble with a sound at > 70. In water: the float bob only. */
/* ctl (struct126) fields not in the header: +0 f32 / +4 s32 (pad0), +0x24 s16 wobble sound latch (pad17[0xD]),
 * +0x3E u16 slide heading (pad3C[2]), +0x4F (pad4F[0]). */
void func_15051558(struct127 *rec, f32 x, f32 z, u16 angle) {
    struct126 *ctl;
    f32 dx = 0.0f;
    f32 dz = 0.0f;
    f32 rate = 0.2f;
    f32 h = rec->unk28;
    f32 fx, fz, push;
    f32 ddx, ddy, ddz, moved, m, bob, wob, anim_speed;
    s32 slide_start = 0;
    s32 was_sliding;
    s32 carrier;
    s32 kind;
    s32 anim;
    u16 heading, ref, turn;

    if (rec->in_water == 0) {
        fx = 0.0f;
        fz = 0.0f;
        was_sliding = rec->unk162;
        push = 3.0f;
        ctl = rec->unk31C;
        kind = ctl->unk4E;
        if (kind == 2) {
            func_1510FDA0(rec->unk188, (s32) &rec->unk18C, &fx, &fz, (s32) &push, &dx, &dz);
            m = dx * dx + dz * dz;
            if (1.4f < m && m < 1000.0f) {
                rec->disable_jump = 6;
                if (h < 80.0f && rec->disable_run == 0) {
                    func_15088360(D_800C3E78, rec);
                }
            }
            if (0.0f <= h) {
                fx = 0.0f;
                fz = 0.0f;
                dx = 0.0f;
                dz = 0.0f;
                push = 3.0f;
            }
            ctl = rec->unk31C;
            kind = ctl->unk4E;
        } else if ((h <= 0.0f || rec->unk110 != 0) && ctl->pad4F[0] == 0) {
            func_1510FDA0(0, (s32) &rec->unk18C, &fx, &fz, (s32) &push, &dx, &dz);
            ctl = rec->unk31C;
            kind = ctl->unk4E;
        }
        if (kind == 0 && ctl->unk84 == 0) {
            if (D_800CC69C == 0 ? (dx * dx + dz * dz > 1.0f || ((rec->unk184 >> 12) & 0xF) == 4)
                                : ctl->pad17[0] != 0) {
                if (((rec->unk184 >> 12) & 0xF) != 3) {
                    D_800CC69C = 1;
                    slide_start = 1;
                }
            }
        }
        /* unk274 = carrying record + 1 */
        carrier = (rec->unk274 != 0) ? D_800CC2D0[rec->unk274 - 1].id : -1;
        if (D_800CC69C == 0) {
            fx = 0.0f;
            fz = 0.0f;
            push = 3.0f;
        }
        if (carrier == 8 || carrier == 0x49) {
            slide_start = 0;
        }
        if (D_800CC69C != 0 && rec->unk28 < 5.0f && rec->unk110 != 0) {
            rec->unk162 = 1;
            if (rec->disable_run != 0xFE) {
                rec->disable_run = D_800BE9A0 + 1;
            }
        } else {
            rec->unk162 = 0;
        }

        ddx = x - rec->old_x_position;
        ddy = rec->y_position - rec->old_y_position;
        ddz = z - rec->old_z_position;
        moved = (sqrtf(ddx * ddx + ddy * ddy + ddz * ddz) * 2.0f) * D_800BEDC8;
        if (rec->unk162 != was_sliding) {
            if (rec->unk162 != 0) {
                rec->unk164 = ddx * D_800BEDC8;
                rec->xz_velocity = 0.0f;
                rec->unk168 = ddz * D_800BEDC8;
            } else {
                rec->xz_velocity = moved;
                if (moved < 22.0f) {
                    rec->xz_velocity = 22.0f;
                }
                if (rec->unk110 == 3) {
                    rec->unk110 = 0;
                    if (rec->disable_run != 0xFE) {
                        rec->disable_run = 0;
                    }
                    rec->xz_velocity = 17.9f;
                }
                rec->unk76 = func_1505A630(x - rec->old_x_position, rec->old_z_position - z, 0);
                rec->unk164 = 0.0f;
                rec->unk168 = 0.0f;
                rec->unk16C = 0.0f;
                rec->unk170 = 0.0f;
            }
        }

        if (D_800CC69C != 0 && rec->unk28 < 5.0f) {
            anim_speed = 1.0f;
            rec->disable_jump = D_800BE9A0 + 8;
            rec->unk112 = func_1505A630(-fx, fz, 0);
            heading = func_1505A630(rec->x_position - rec->old_x_position, rec->old_z_position - rec->z_position, 0);
            D_800CC69C = 1;
            if (rec->unk110 == 0) {
                push = (&D_80099470)[1];
                turn = rec->unk112;
                if (((((s32) (turn - heading) >> 8) + 0x30) & 0xFF) < 0x60) {
                    anim = 0x28E;
                    ref = (rec->unk44 > 8.0f) ? angle : rec->unk7A;
                    if (slide_start) {
                        rec->unk110 = 3;
                        anim_speed = 2.0f;
                    } else {
                        anim = 0xD0;
                        if (((((s32) (turn - ref) >> 8) + 0x58) & 0xFF) < 0xB0) {
                            rec->unk110 = 1;
                            anim = 0x101;
                        } else {
                            rec->unk110 = 2;
                        }
                    }
                    if (rec->stunned == 0 && rec->unk13C == 0 && rec->disable_run != 0xFF && rec->unk83 < 0xFA) {
                        ctl = rec->unk31C;
                        if (ctl->unk11A != 1 && ctl->unk11A != 3 && ctl->unk120 == 0 && ctl->unk19B == 0) {
                            func_1505E650(rec, anim, anim_speed, 6.0f, 0.0f, 0.0f, 0);
                        }
                    }
                }
            } else {
                push = D_80099490[D_800CC69C];
            }
        }

        func_1505A250(-fx, -fz, push, &rec->unk164, &rec->unk168);
        rec->unk16C = rec->unk16C + (0.0f - rec->unk16C) * 0.15f;
        rec->unk170 = rec->unk170 + (0.0f - rec->unk170) * 0.15f;
        if (rec->unk110 != 0) {
            *(u16 *) &rec->unk31C->pad3C[2] = func_1505A630(rec->x_position - rec->old_x_position,
                                               rec->old_z_position - rec->z_position, 0);
            anim = rec->unk84.uh;
            if (anim == 0x28E || anim == 0x101 || anim == 0xD0) {
                if (rec->unk31C->unk11A != 1 && rec->unk31C->unk11A != 3) {
                    rec->unk83 = D_800BE9A0 + 1;
                }
            }
            if (D_800CC69C == 0) {
                if (rec->unk110 == 2) {
                    rec->unk76 = rec->unk112;
                    *(u16 *) &rec->unk31C->pad3C[2] = rec->unk112;
                    if (rec->xz_velocity < 2.0f && 0.0f == rec->unk28) {
                        if (rec->stunned == 0) {
                            func_1505E650(rec, 0xA5, 1.4f, 5.0f, 0.0f, 0.0f, 0);
                            turn = rec->unk76 ^ 0x8000;
                            rec->unk83 = 0x3C;
                            rec->disable_run = 0x3C;
                            rec->disable_jump = 0x1E;
                            rec->unk76 = turn;
                            rec->unk7A = turn;
                            rec->unk100 |= 0x20;
                        }
                        rec->unk110 = 0;
                    }
                } else if (rec->xz_velocity < 12.0f) {
                    rec->unk110 = 0;
                }
            }
        }

        if (h <= 0.0f) {
            dx = func_1505210C((u8 *) rec, dx, dz, &dz, 50.0f);
            ctl = rec->unk31C;
            kind = ctl->unk4E;
            if (kind != 2) {
                if (*(s32 *) &ctl->pad0[4] == 0 && rec->unk110 == 0 && (kind & 0xF) != 1) {
                    dx = dx * (*(f32 *) &ctl->pad0[0] * 0.009f + 0.2f);
                    dz = dz * (*(f32 *) &rec->unk31C->pad0[0] * 0.014f + 0.2f);
                } else {
                    dx = dx * 0.8f;
                    dz = dz * 0.8f;
                    if ((rec->unk31C->unk4E & 0xF) == 1) {
                        dz = 0.0f;
                        dx = dx * 0.5f;
                    }
                }
            }
        }
        if (rec->unk31C->unk4E == 2) {
            bob = rec->unk54 * 6.0f;
            if (rec->y_velocity < -30.0f) {
                dz = dz - -30.0f;
            } else {
                dz = dz - rec->y_velocity;
            }
            rate = 0.4f;
            ctl = rec->unk31C;
            if (ctl->unk44 > 0) {
                rate = 0.25f;
                bob += (s16) ((s16) ((D_800CC670 & 4) - 2) * (ctl->unk44 * 2));
            }
            wob = fabsf(rec->unkC4);
            if (70.0f < wob && D_800BE616 == 0 && rec->health != 0 && *(s16 *) &ctl->pad17[0xD] == 0) {
                D_800D1580 = 0xFF020146;
                func_1506E8D8();
                *(s16 *) &rec->unk31C->pad17[0xD] = 1;
                wob = fabsf(rec->unkC4);
            }
            if (wob < 20.0f) {
                *(s16 *) &rec->unk31C->pad17[0xD] = 0;
            }
            dx = dx + bob;
        }
        rec->unkB8 = rec->unkB8 + (dz - rec->unkB8) * rate;
    } else {
        m = ((rec->unk118 - 30.0f) - rec->y_position) + rec->xz_velocity * 6.0f;
        m = (250.0f < m) ? 2.5f : m * 0.01f;
        if (fabsf(rec->unkB8) < 35.0f && 0.0f < m) {
            dx = 0.0f + rec->unk54 * m;
        }
        func_1505A250(0.0f, 0.0f, 0.3f, &rec->unk164, &rec->unk168);
    }
    rec->unkC4 = rec->unkC4 + (dx - rec->unkC4) * rate;
}
