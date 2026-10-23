extern s32 D_800C39D0;
extern u8 D_800844A0[];  /* screen fade colours, 3 bytes (r, g, b) per entry */
extern s8 D_800C40AA;
extern u16 D_800C40AE;
s32 func_15023C60(u32 arg0, s32 arg1, s32 arg2, u8 **arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
void func_15023EC4(u8 **, u8 **, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_15023988(u8 *, s32 *, u32 *, s32 *, s32 *, s32 *, u16 *);
s32 func_1000E134(s32);
void func_1000D96C(s32, s32, s32);
void func_1000DE1C(s32, s32);
void func_1517946C(s32);
void func_151D6CA0(s32, s32);
void func_15188EBC(s32, s32, s32);
void func_15188D80(struct127 *, s32, s32);
void func_15189040(s32);
void func_15155D6C(s32, s32, f32);
void func_15156500(void);
void func_1503DE70(struct127 *, s32, s32);
void func_150F59A0(s32, s32, s32, s32);
void func_1517F3B0(s32, s32, s32, s32, s8, s32);
void *allocate_memory(s32, s32, s32, s32);

/* the span (frames from now) to the next event of this track matching the type / id (and b4 / b5 when given) */
#define NEXT(out, useB4, b4v, useB5, b5v) \
    (func_15023C60((u32) ev, (s8) ev[0], track, (out), 1, *(s16 *) (ev + 2), (useB4), (b4v), (useB5), (b5v), player) - now)

// scene_event_run_c: third scene event handler (after func_15024910 / func_150268BC): sounds and music, object
// animations and the screen fade. ev = the 8-byte event (s8 type, u8 delta, s16 id, s8 b4, s8 b5, s16 w6), now the
// track time, obj / wrec the track's object / world record, data its position (f32 x, y, z); replay = 1 while the
// scene is fast-forwarded (then most cases only restore end states). Returns 1 when the event was handled.
//   6 / 0xA: positional sound id (volume w6, 0 = 0xFF) on func_1000FA64 with the update callback func_15023988;
//            0xA stops at its b4 1 event and fades in / out to its b4 2 / 3 events, 6 plays to the end (flags
//            0x400, 0x800 for b4 2). 8: music id (b4 0 start, 1 / 4 volume, 2 / 6 fade, 8 / 9 other controls).
//   2: object animation id with blend w6 - 1 frames, speed so that it lasts to the next type-2 event.
//   5 / 1: screen fade to colour D_800844A0[b5] over the span to the b4 1 event (w6 0 = fade in); in replay the
//          b4 != 0 event re-applies the last one. 5 / 4, 0x5C, 0x56, 0x76, 0x2D, 0x57: see the cases.
s32 func_15029EA8(s32 arg0, u8 track, u16 value, s32 now, s32 player, struct127 *obj, u8 *wrec, u8 *data, s32 flag,
                  s32 replay) {
    u8 *ev = (u8 *) arg0;
    s32 type = (s8) ev[0];
    u8 *next;
    u8 *prev;
    s32 prevTime;
    s32 span;
    s32 t;

    if (type == 6 || type == 0xA) {
        s32 vol;
        s32 fadeIn;
        s32 fadeOut;
        s32 flags;
        u8 *r;

        next = NULL;
        flags = 0;
        if ((s8) ev[4] != 0 && (s8) ev[0] != 6) {
            return 1;
        }
        if (*(s16 *) (ev + 6) == 0) {
            vol = 0xFF;
        } else {
            vol = *(s16 *) (ev + 6) & 0xFF;
        }
        span = NEXT(&next, 1, 1, 0, 0);
        if ((s8) ev[0] == 6 || next == NULL) {
            span = 0xFFFF;
        }
        if (replay != 0 && ((s8) ev[0] != 0xA || next != NULL)) {
            return 1;
        }
        fadeOut = 0;
        fadeIn = 0;
        if ((s8) ev[0] == 0xA) {
            t = NEXT(&next, 1, 2, 0, 0) + now;
            if (next != NULL && t - now < span) {
                fadeIn = t - now;
            }
            t = NEXT(&next, 1, 3, 0, 0) + now;
            if (next != NULL && t - now < span) {
                fadeOut = span - (t - now);
            }
        } else if ((s8) ev[4] == 2) {
            flags = 0x800;
        } else {
            flags = 0x400;
        }
        r = allocate_memory(0x10, 1, 0, 0);
        if (r != NULL) {
            r[0] = player;
            r[0xE] = (&D_800C3A08)[player];
            *(u16 *) (r + 4) = span;
            *(u16 *) (r + 6) = span;
            r[1] = track;
            *(u16 *) (r + 8) = fadeIn;
            *(u16 *) (r + 0xC) = (vol * 0x7FFF) >> 8;
            *(u16 *) (r + 0xA) = fadeOut;
            r[2] = (s8) ev[0] == 0xA;
            func_1000FA64(*(u16 *) (ev + 2), *(f32 *) (data + 0), *(f32 *) (data + 4), *(f32 *) (data + 8),
                          *(u16 *) (r + 0xC), 0x7D00, 0x7918, (s32) func_15023988, r, 0, flags, (s8) ev[5] * 50);
        }
        return 1;
    }
    if (type == 8) {
        s32 id = *(s16 *) (ev + 2);
        s32 w6 = *(s16 *) (ev + 6);
        s32 bit = 1 << (((s8) ev[5] + 31) & 0x1F); /* 1 << (b5 - 1), b5 0 -> bit 31 (MIPS sllv) */

        switch ((s8) ev[4]) {
            case 0:
                if (replay != 0 && func_1000E134(id) != 0) {
                    return 1;
                }
                func_1000D96C(id, 0, 0);
                return 1;
            case 1:
                func_1000E588(id, w6 * 100, bit);
                return 1;
            case 2:
                func_1000DF68(id, w6 * 328, 1);
                return 1;
            case 3:
                return 1;
            case 4:
                t = func_15023C60((u32) ev, type, track, &next, 1, id, 1, 5, 1, (s8) ev[5], player) - now;
                if (replay != 0) {
                    func_1000E588(id, w6, bit);
                } else {
                    func_1000E46C(id, w6, bit, t);
                }
                return 1;
            case 6:
                t = func_15023C60((u32) ev, type, track, &next, 1, id, 1, 7, 0, 0, player) - now;
                if (t < 2) {
                    t = 1;
                }
                func_1000DF68(id, w6 * 328, t);
                return 1;
            case 8:
                func_1000E654(id, w6 + 1, 0, -1);
                return 1;
            case 9:
                func_1000DE1C(id, 0);
                return 1;
        }
        return 1;
    }
    if (type == 2) {
        f32 frames;
        f32 blend;
        f32 speed;
        s32 mode;
        s16 anim;

        if (obj == NULL) {
            return 1;
        }
        frames = func_15023C60((u32) ev, type, track, &next, 0, 0, 0, 0, 0, 0, player) - now;
        if ((s8) ev[4] != 0) {
            return 1;
        }
        if (*(u8 **) ((u8 *) obj + 0x2D0) == NULL) {
            return 1;
        }
        blend = 5.0f;
        anim = *(s16 *) (ev + 2);
        if (*(s16 *) (ev + 6) > 0) {
            blend = *(s16 *) (ev + 6) - 1;
        }
        mode = 1;
        if (D_800C40AE >= now) {
            blend = 0.0f;
        }
        if (replay != 0) {
            blend = 0.0f;
        }
        if (next != NULL) {
            mode = (s8) next[4] == 0;
            if ((s8) next[4] == 1 && (s8) next[5] == 1) {
                mode = 1;
            }
        }
        if (anim != *(u16 *) ((u8 *) obj + 0x84)) {
            func_1505E650(obj, anim, 1.0f, blend, 0.0f, 0.0f, mode);
        }
        if (frames > 0.0f) {
            speed = 2.0f * (*(f32 *) (*(u8 **) ((u8 *) obj + 0x2D0) + 0x18) / frames);
        } else {
            speed = 0.0f;
        }
        if ((s8) ev[5] != 0) {
            speed = 0.0f;
        }
        func_1505E650(obj, anim, speed, blend, 0.0f, 0.0f, mode);
        return 1;
    }
    if (type != 5) {
        return 0;
    }
    switch (*(s16 *) (ev + 2)) {
        case 1: {
            u8 *c;

            if ((s8) ev[4] == 0) {
                t = func_15023C60((u32) ev, type, track, &next, 1, 1, 0, 0, 0, 0, player) - now;
                if (replay != 0) {
                    t = 0;
                }
                c = &D_800844A0[(s8) ev[5] * 3];
                func_1517F3B0(c[0], c[1], c[2], t, *(s16 *) (ev + 6) == 0, 0);
                D_800C40AA = *(s16 *) (ev + 6) == 0;
            } else if (replay != 0) {
                func_15023EC4(&prev, &next, NULL, &prevTime, track, type, 1, 1, 1, 0, (&D_800C39D0)[player], player);
                if (prev != NULL) {
                    c = &D_800844A0[(s8) prev[5] * 3];
                    func_1517F3B0(c[0], c[1], c[2], 0, *(s16 *) (prev + 6) == 0, 0);
                    D_800C40AA = *(s16 *) (prev + 6) == 0;
                }
            }
            return 1;
        }
        case 4: {
            s32 set;

            if (obj == NULL) {
                return 1;
            }
            if (replay == 0) {
                set = -1;
                if (((u8 *) obj)[4] == 0x4B) {
                    set = 2;
                }
                if (set == -1) {
                    return 1;
                }
                func_1503DE70(obj, set, (s8) ev[4] != 0 ? (s8) ev[4] - 1 : -1);
            } else {
                func_15060F28(obj, 1);
            }
            return 1;
        }
        case 0x5C: {
            s32 end;
            s32 in;
            s32 out;

            if ((s8) ev[4] != 0 || replay != 0) {
                return 1;
            }
            end = func_15023C60((u32) ev, type, track, &next, 1, 0x5C, 1, 1, 1, (s8) ev[5], player);
            in = NEXT(&next, 1, 2, 1, (s8) ev[5]);
            if (next == NULL) {
                in = 0;
            }
            out = end - (NEXT(&next, 1, 3, 1, (s8) ev[5]) + now);
            if (next == NULL) {
                out = 0;
            }
            func_150F59A0(in, end - now - out - in, out, (s8) ev[5]);
            return 1;
        }
        case 0x56:
            if ((s8) ev[4] == 0) {
                if (replay == 0) {
                    func_1517946C(3);
                }
            } else if (replay != 0) {
                func_1517946C(2);
            } else if ((s8) ev[5] == 0) {
                func_1517946C(0);
            } else {
                func_1517946C(1);
            }
            return 1;
        case 0x76:
            func_151D6CA0(*(s16 *) (ev + 6), (s8) ev[4] == 1 ? 0 : ((s8) ev[5] == 1 ? 2 : 1));
            return 1;
        case 0x2D:
            t = func_15023C60((u32) ev, type, track, &next, 1, 0x2D, 0, 0, 0, 0, player) - now;
            if (wrec != NULL) {
                if ((s8) ev[4] == 0) {
                    func_15188EBC((s32) wrec, t, (s8) ev[5]);
                }
            } else if (obj != NULL) {
                if ((s8) ev[4] == 0) {
                    func_15188D80(obj, t, (s8) ev[5]);
                } else if (replay != 0) {
                    func_15189040((s32) obj);
                }
            }
            return 1;
        case 0x57:
            if ((s8) ev[4] == 0) {
                func_15155D6C(0, func_15023C60((u32) ev, type, track, &next, 1, 0x57, 0, 0, 0, 0, player) - now, 0.0f);
            } else if (replay != 0) {
                D_800C3E78 = 0;
                func_15156500();
            }
            return 1;
    }
    return 1;
}
#undef NEXT
