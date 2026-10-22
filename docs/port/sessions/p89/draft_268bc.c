/* P89 PARTIAL DRAFT of func_150268BC (game_eu_51190.c) -- not compiled, not tested, NOT in src_eu.
 * Map: func_150268BC_map.md (same directory). Written by hand from the asm (m2c only as a reading aid).
 * Done: event layout, top level (types 0x0B / 0x11 / 0x05), the type-0x05 if-chain with most sub-types,
 *       sub 0x65 / 0x5F switches.
 * TODO (marked TODO below): sub 0x11 (func_1516DF0C, 49 args), 0x1B case 2 (two func_1516FAB8), 0x48, 0x4D / 0x4E / 0x4F
 *       particle structs, 0x33 (func_1514948C), 0x5F/15; every callee prototype in the "conflicts" list of the map;
 *       check each `(u8) flag` against the callee prototype; then knob setups + mutants. */

typedef struct {
    s8  type;    /* 0x0B sound, 0x11 table byte, 0x05 effect */
    u8  delta;
    s16 id;      /* sound id / table index / effect sub-type */
    s8  b4;      /* 0 = start, else stop / variant */
    s8  b5;
    s16 w6;
} ScriptEvent;   /* size 8 */

extern u8  *D_800C3D80[4][30];      /* per player and track: byte table written by type 0x11 */
extern s16 *D_eu_800C3C88[4][30];   /* per player and track: s16 x, y, z */
extern s32 *D_800C3A00[4];          /* per player: word table indexed by w6 */
extern u8   D_800844D8[3][6];       /* sub 0x11 colour sets */
extern f32  D_80096DF8[3][3], D_80096E1C[4][3], D_80096E4C[6][3], D_80096EB0[2][3];   /* .game_data offsets */
extern u8   D_80096F28[8];          /* sub 0x5F/19 bones {7, 8, 9, 10, 13, 14, 15, 16} */
extern struct108 *D_800DBFF0;
extern u8 *D_800D34B8;
extern s32 D_8008CDF0;

/* time (frames) until the next event of this type and id on the track: the effect's duration */
#define SPAN(ev, out) (func_15023C60((u32) (ev), (ev)->type, track, (out), 1, (ev)->id, 0, 0, 0, 0, player) - now)
#define REC(player, track) (&(&D_800C3958)[player][track])
#define OBJ_INDEX(obj) ((s32) ((u8 *) (obj) - (u8 *) D_800CC2D0) / 812)

s32 func_150268BC(s32 arg0, u8 track, u16 value, s32 now, s32 player, struct127 *obj, u8 *rec, u8 *data, s32 flag) {
    ScriptEvent *ev = (ScriptEvent *) arg0;
    f32 *pos = (f32 *) data;
    struct233 *r;
    u8 *next;   /* out slot of func_15023C60 (never read) */
    s32 span;
    s32 vol;

    if (ev->type == 0x0B) {   /* sound */
        if (ev->b4 == 0) {
            func_1001263C(ev->id, ev->w6 == 0 ? 0x10000 : (ev->w6 << 16) / 255, 0x40);
        } else if (ev->b4 == 1) {
            span = func_15023C60((u32) ev, ev->type, track, &next, 1, ev->id, 1, 2, 0, 0, player) - now;
            vol = ev->w6 == 0 ? 0x10000 : (ev->w6 << 16) / 255;
            func_151F2D6C(vol, (span * 0x5604) / 50);
        } else if (ev->b4 == 3) {
            func_151F2BA8();
        } else if (ev->b4 == 4) {
            func_151F2BE8();
        } else if (ev->b4 == 5) {
            func_151F2C4C();
        }
        return 1;
    }
    if (ev->type == 0x11) {
        D_800C3D80[player][track][ev->id] = ev->b4 != 0 ? (u8) value : 0xFF;
        return 1;
    }
    if (ev->type != 5) {
        return 0;
    }

    switch (ev->id) {
    case 0x11:
        /* TODO: colours D_800844D8[b5 < 3 ? b5 : 0], size w6 (0 -> 0x1000, else max(w6, 200)),
         * func_1516DF0C((s16) ((s32) data >> 16), (s16) (s32) data, 0, 0x1B, 0, c[0..5], 0, 1, 6, 0, 0, 0, 0, 0,
         * (size >> 3) >> 8, (size >> 3) & 0xFF, 0, 0, 10, 0 x7, span, (size * 40 / 4096) & 0xFF x2, 0xFF, 14, 8, 8, 0x25,
         * 0, 0xFF, 8, 0, 0, player, 0, 0, flag, 0) -- check the 0x80 / 0x84 / 0xA4 stack slots (size >> 12 test) in the asm */
        break;
    case 0x0A:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            func_151BA1A0(3, 3, 0, 0, 0, 800, 1200, 400, 200, 0x66, 0x1C7, 2, span, (s32) data, flag, 0);
        }
        break;
    case 0x0B:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            func_151BA1A0(0x2F, 1, 0, 0, 0, 2000, 1000, 400, 200, 0x400, 0x400, 6, span, (s32) data, flag, 0);
        }
        break;
    case 0x0C: {
        struct {
            s32 unk0; s16 unk4, unk6, x, y, z, unkE, unk10, unk12; s8 unk14, unk15;
        } s;   /* TODO: check field order against the sp6D4..sp6E8 stores */
        s.unk4 = 0;
        s.unk6 = 0x100;
        s.unk0 = D_8008CDF0;
        s.x = pos[0];
        s.y = pos[1] + ev->b4;
        s.z = pos[2];
        s.unkE = 1500;
        s.unk10 = 1500;
        s.unk12 = -10;   /* TODO: sp6E6 is s8 per m2c */
        s.unk14 = 0;
        func_15167AD8(&s, (u8) flag, 1);
        break;
    }
    case 0x19:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            func_15177F90(ev->b5 != 0 ? (u8) ev->b5 : 12, data, 0xFF, (s32) pos[0], (s32) pos[1], (s32) pos[2], 0, span, flag,
                          0, ev->w6);
        }
        break;
    case 0x1A: {
        s16 *p = D_eu_800C3C88[player][track];
        f32 from[3], to[3];
        r = REC(player, track);
        from[0] = p[0];
        from[1] = p[1];
        from[2] = p[2];
        if (ev->b4 == 1) {
            to[0] = r->unk0;
            to[1] = *(f32 *) ((u8 *) r + 0x38) + r->unk4;
            to[2] = r->unk8;
            func_150B0574(from, to, (u8) flag, 1);
        } else {
            func_150E2030(0, from[0], from[1], from[2], r->unk0, *(f32 *) ((u8 *) r + 0x38) + r->unk4, r->unk8, 40.0f, 0.0f,
                          8.0f, 60.0f, 600, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);   /* TODO proto */
        }
        break;
    }
    case 0x1C:
        if (obj != NULL && (ev->b4 == 0 || ev->b4 == 1)) {
            func_150E3334(obj, ((u8 *) obj)[0x3B], ev->b4 == 0 ? 3 : 2, -1, 0.0f, 0.0f, 156.0f, 0.0f, 0.0f, 636.0f, 3, 10, 0xF0,
                          0);
        }
        break;
    case 0x1B:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            switch ((u16) ev->w6) {
            case 0: func_1516ECE8((u32) data, span, ev->b5, (u8) flag, 0); break;
            case 1: func_150BF47C(span); break;
            case 2: /* TODO: two func_1516FAB8 calls, see map */ break;
            case 3: func_151DCE6C(data, (s16) span, 1, 1, flag, 0); break;
            case 4: func_151DCE6C(data, (s16) span, 0, 0, flag, 0); break;
            }
        }
        break;
    case 0x1F:
        if (obj != NULL) {
            func_150BA4C0(obj, (u8) flag, 1);
        }
        break;
    case 0x00:
        if (obj != NULL) {
            func_151A3940(obj, (u8) flag);
        }
        break;
    case 0x20:
        func_151664F0(-1, (s32) pos[0], (s32) pos[1], (s32) pos[2], 20, 20, 1, flag, 1);
        break;
    case 0x06:
    case 0x3E:
    case 0x3F:
    case 0x2A:
        break;
    case 0x07:
        func_150B2974(obj, 9, -1);
        break;
    case 0x21:
        if (ev->b4 == 0) {
            func_15136A50((s32) data, (s32) (data + 4), (s32) (data + 8), SPAN(ev, &next), flag, 0);
        }
        break;
    case 0x60:
        if (ev->b4 == 0) {
            func_150CE660(obj, SPAN(ev, &next), (u8) flag, 0);   /* 4th argument 0 (P80) */
        }
        break;
    case 0x65:
        /* TODO: b4 == 2 part (func_151494E0 / func_150D0148), b4 == 0 switch on b5: see map "sub 0x65" */
        break;
    case 0x5B:
        if (ev->b4 == 0) {
            func_151B57F0(SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x5D:
        if (ev->b4 == 0) {
            func_151932B8(obj, SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x5E:
        if (ev->b5 == 1) {
            func_151B09BC(obj, 0, 1000, (u8) flag, 0);
        } else if (ev->b4 == 0) {
            func_151B09BC(obj, 0, SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x4C:
        if (ev->b4 == 0) {
            u8 kind = ((u8 *) obj)[4];
            span = SPAN(ev, &next);
            if (kind == 0x49 || kind == 0x58) {
                s32 n;
                u8 *list = (u8 *) func_151905AC(obj, &n);
                if (list != NULL && ev->w6 < n) {
                    func_1518FA8C(obj, list[ev->w6], span, -1, -1, -1, 0, 0, flag, 1);
                }
            } else {
                func_1518D1C0(obj, ev->b5, span, 0, flag, 1, "Cutscene 2");
            }
        }
        break;
    case 0x50:
        if (ev->b4 == 0) {
            func_150EA560(obj, SPAN(ev, &next), (u8) flag, 0);   /* TODO proto: callee declares f32 arg2 */
        }
        break;
    case 0x51:
        if (ev->b4 == 0) {
            func_150EAA80(obj, SPAN(ev, &next), (u8) flag, 0);   /* TODO proto: callee declares f32 arg2 */
        }
        break;
    case 0x48:
        /* TODO: see map */
        break;
    case 0x0F:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            func_150C7520(obj, span, (u8) flag, 1);
        }
        break;
    case 0x32:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            r = REC(player, track);
            func_150DBA98(data, (u8 *) r + 0x10, (u8 *) r + 0x18, (u8 *) r + 0x1C, (u8 *) r + 0x20, span, flag, 0);
        }
        break;
    case 0x34:
        span = SPAN(ev, &next);
        if (ev->b4 == 0) {
            u8 idx = 0;   /* N64: an uninitialised stack byte when b5 < 0 */
            u8 *node;
            if (ev->b5 >= 0) {
                idx = 13;
            }
            for (node = *(u8 **) ((u8 *) obj + 0x2F4); node != NULL; node = *(u8 **) (node + 0x14)) {
                if (idx == *(s16 *) (node + 0x1C) || func_1514DA28(*(s16 *) (D_8008AF88[idx] + 4), *(s16 *) (node + 0x1C)) != 0) {
                    u8 *target = *(u8 **) (node + 0x10);
                    r = REC(player, track);
                    *(s32 *) (target + 0x30) = (s32) func_1519EEE0(span, (s32) target, 0, (s32) ((u8 *) r + 0x30),
                                                                   (s32) ((u8 *) r + 0x20), flag, 0);
                }
            }
        }
        break;
    case 0x23:
        if (obj != NULL) {
            span = SPAN(ev, &next);
            if (ev->b4 == 0) {
                func_1516F868(OBJ_INDEX(obj), span, span, 0, flag, 0);
            }
        }
        break;
    case 0x22:
        if (obj != NULL) {
            span = SPAN(ev, &next);
            if (ev->b4 == 0) {
                func_1516F730(OBJ_INDEX(obj), span, (u8) flag, 0);
            }
        }
        break;
    case 0x52:
        if (obj != NULL) {
            func_15136404(obj, 90.0f, (u8) flag, 1);
        }
        break;
    case 0x5F:
        /* TODO: switch (u8) b4 < 23, see map "sub 0x5F" */
        break;
    case 0x40:
        func_151A0A10(obj, 0x28, (u8) flag, 1);
        break;
    case 0x4D:
    case 0x4E:
    case 0x4F:
        /* TODO: particle structs, see m2c lines 1286-1373 */
        break;
    case 0x24: {
        f32 p[3];
        u8 kind = ev->b5;
        p[0] = pos[0];
        p[1] = pos[1];
        p[2] = pos[2];
        if (kind >= 13) {
            kind = 0;
        }
        func_151DBAA8((struct17 *) p, ev->b4 != 0 ? ev->b4 : 10, kind, (u8) flag, 0);
        break;
    }
    case 0x10: {
        u8 kind = ev->b4;
        if (kind >= 27) {
            kind = 0;
        }
        func_151AFA80(obj, kind, (u8) flag, 0);
        break;
    }
    case 0x47:
        func_151925C4(obj, 0x32, (u8) flag, 0);
        break;
    case 0x2E:
        func_150C1F60((u8) flag);
        func_150C2290((u8) flag);
        func_150C2424((u8) flag);
        break;
    case 0x31:
        func_150DB3F0(obj, 0, (u8) flag, 0);
        break;
    case 0x33:
        /* TODO: func_1514948C, see map */
        break;
    case 0x35:
        func_150DBF60(obj, ev->b4 >= 2 ? 1 : ev->b4, (u8) flag);
        break;
    case 0x26:
        if (obj != NULL) {
            span = SPAN(ev, &next);
            if (ev->b4 == 0) {
                ((u8 *) obj)[0x276] = 1;
                *(s16 *) ((u8 *) obj + 0x282) = span;
            }
        }
        break;
    case 0x27:
    case 0x02: {
        f32 len = ev->w6 >= 0 ? (f32) ev->w6 : 30.0f;
        f32 speed = ev->b5 != 0 ? ev->b5 * 0.1f : 1.0f;
        s32 n = ev->b4 != 0 ? ev->b4 : 1;
        if (ev->id == 0x27) {
            func_1518B7D4((s32) data, len, speed, n, flag);
        } else {
            func_1518B818((s32) data, len, speed, n, 30, 100, (u8) flag);
        }
        break;
    }
    case 0x28:
        if (rec != NULL) {
            func_15171B70(rec, (u8) flag, 0);
        } else if (obj != NULL) {
            func_15172164(obj, (u8) flag);
        }
        break;
    case 0x29:
        if (rec != NULL) {
            func_15171434((s32) rec, (u8) flag, 0);
        } else if (obj != NULL) {
            func_15171734((u8 *) obj);
        }
        break;
    case 0x2B:
        func_1518BC20(pos[0], pos[1], pos[2], (u8) flag, 0);
        break;
    case 0x2C:
        SPAN(ev, &next);
        break;
    case 0x2F:
        if (obj != NULL && ev->b4 == 0) {
            func_1516F2D8(OBJ_INDEX(obj), SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x39:
        if (ev->b4 == 0) {
            func_150C2804((s32) data, (s32) (data + 4), (s32) (data + 8), SPAN(ev, &next), (u8) flag, 0);
        }
        break;
    case 0x3A: {
        f32 p[3];
        p[0] = pos[0];
        p[1] = pos[1];
        p[2] = pos[2];
        func_151DBAA8((struct17 *) p, ev->b4 != 0 ? ev->b4 : 10, 6, (u8) flag, 0);
        break;
    }
    default:
        return 0;
    }
    return 1;
}
