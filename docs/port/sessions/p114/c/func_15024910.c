/* --- P114: scene event handler A (func_15024910); hand-written from the asm (map: docs/port/sessions/p114/scene_vm_map.md) --- */
s16 *func_1502354C(s32 track, s32 start);
void func_150234E8(s16 *arg0, s32 arg1);
void func_1516D850(u8 *arg0);
u8 *func_1516D8E8(u8 *arg0);
u8 *func_1516D934(u8 *arg0);
s32 func_1516AD20(s32, s32, s32, void (*)(s32, s32, s32), s32 *, s32);
s32 func_15023C60(u32 arg0, s32 arg1, s32 arg2, u8 **arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
void func_1507EB4C(struct127 *arg0, s32 arg1);
void func_1507E7E4(struct127 *obj, u8 anim, u8 prio, u16 time, s32 arg4);
s32 func_15083568(struct127 *arg0, s32 arg1, f32 arg2, s32 arg3);
s32 func_150836CC(struct127 *obj, s32 n);
u8 *func_15031C4C(u8 *arg0, s32 arg1, s32 arg2);
s32 func_15053430(struct127 *obj);
void func_15060F28(struct127 *arg0, s32 arg1);
void func_1501C710(s32 arg0, u16 *arg1, s32 arg2, s32 arg3, s32 arg4);
u8 *func_151149AC(u8 id);
void func_151494E0(s32, u8);
void func_1515F170(s32 arg0, u8 arg1);
void func_151645C4(u8 arg0);
void func_151616D0(u8 arg0, u8 arg1, s32 arg2);
void func_151CD90C(s32 arg0);
void func_150B696C(u8 arg0);
void func_151C9CBC(s32 arg0, s32 arg1);
void func_151CA398(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_151CA484(u8 *arg0);
void func_150E0880(void);
void func_150FB2A8(void);
void func_150F58C0(s32 arg0);
void func_150FAFC0(u8 arg0, s32 arg1);
void func_15169040(s32 arg0, u8 arg1);
void func_151CD944(s32 arg0);
void func_15190A88(u8 *arg0);
void func_1518F9CC(s32 arg0, u8 arg1);
void func_151937F4(u8 *arg0, s32 arg1, s32 arg2);
void func_151920FC(s32 arg0, u8 arg1);
s32 *func_151905AC(u8 *arg0, s32 *arg1);
s32 func_1518FA8C(s32 arg0, u8 arg1, s16 arg2, s8 arg3, s8 arg4, s8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9);
u8 *func_1518D1C0(u8 *obj, s16 kind, s16 span, s32, s32 flag, s32, char *name);
s32 func_1519D5A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_151482D4(s32 arg0, u8 arg1);
void func_150C6174(s32 arg0);
void func_150C619C(s32 arg0);
void func_1510B9D8(s32 player, f32 width, f32 height);
s32 func_15083FB0(u8 arg0);
void func_150B7700(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void *func_151A5580(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7);
void func_10011FB0(s32 arg0);
void func_150C851C(s32 arg0);
f32 func_15052F9C(struct127 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void func_1517F9F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_1517FC90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_150F59A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_1510AEB0(s32 arg0, s32 arg1, s32 arg2);
void func_151DECB4(void);
void func_151E5B94(s32 arg0);
void func_1505959C(struct127 *arg0, s32 arg1);
void func_15073F1C(void);
void func_15093818(s32 arg0);

extern s8 D_800E1024;              /* cutscene colour-light events (7 / 0xE / 0xF / 0x10 / 0x12) enabled */
extern u8 D_800BEECB;              /* which of them is active: 0 / 4 / 2 / 3 / 1 */
extern u8 D_800844A8[3][3];        /* light colours (.data) */
extern u8 D_800844B4[2][3];        /* sub 0x41 colours (.data) */
extern s16 D_800844BC[4][2];       /* sub 0x05 kinds (.data; [i][1] is used) */
extern u8 D_800844CC[3][3];        /* sub 0x37 colours (.data) */
extern s32 *D_800C3A00[4];
extern u8 D_800C3A18;
extern s32 D_800905C4[];
extern u8 D_800C3A78[], D_800C3A7A[], D_800C3A7C[], D_800C3A7E[], D_800C3A80[], D_800C3A82[], D_800C3A84[];
extern u8 D_800C3A86;
extern f32 D_800C3A70, D_800C3A74, D_800C3A94, D_800C3A98;
extern s32 D_800C3A9C;
extern f32 D_800D9F3C, D_800D9F40;
extern s32 D_800BEE08;
extern u8 D_800C40AB, D_800C40AD, D_800C3AA0, D_800DC2DC, D_800C40BD, D_800BEE2C;
extern u8 D_800C39E2, D_800C39E3, D_800C3682, D_800C3683;
extern s16 D_800C40BE;
extern s32 D_800D2870;
extern u8 *D_800DE274, *D_800DE278, *D_800DE27C;
extern char D_80096DE0[];          /* "Cutscene 1" */

typedef struct { u8 b[9]; } SceneBytes9;
typedef struct { u8 b[6]; } SceneBytes6;
typedef struct { s16 h[8]; } SceneHalves8;
/* one 8-byte scene event (as in func_150268BC) */
typedef struct {
    s8  type;
    u8  delta;
    s16 id;
    s8  b4;
    s8  b5;
    s16 w6;
} SceneEventA;

#define SA_REC(p, t) ((u8 *) (&D_800C3958)[p] + (t) * 0x44)   /* the track's struct233 record (0x44 bytes) */
#define SA_U8(p, o) (*(u8 *) ((u8 *) (p) + (o)))
#define SA_S8(p, o) (*(s8 *) ((u8 *) (p) + (o)))
#define SA_S16(p, o) (*(s16 *) ((u8 *) (p) + (o)))
#define SA_S32(p, o) (*(s32 *) ((u8 *) (p) + (o)))
#define SA_F32(p, o) (*(f32 *) ((u8 *) (p) + (o)))
#define SA_PTR(p, o) (*(u8 **) ((u8 *) (p) + (o)))
#define SA_OBJ_INDEX(o) (((u8 *) (o) - (u8 *) D_800CC2D0) / 0x32C)

// scene_event_run_a: first handler of a scene event (func_1502AB94 tries this one, then func_150268BC, then
// func_15029EA8). ev is the 8-byte event, track / player its track, now the track time, obj / wrec the track's object
// or world record (ref kind 2 / 3), flag the player's D_800C3A08 byte. Handles the cutscene light types (7, 0xE, 0xF,
// 0x10, 0x12 while D_800E1024), object types 0xC (animation), 0xD (setup lists), 4, 9, 1, track switch 3, and the
// type 5 sub-types below (0x67: leave the logo scene for the title menu via func_151DECB4). Returns 1 when handled.
s32 func_15024910(s32 arg0, u8 track, u16 value, s32 now, s32 player, struct127 *obj, u8 *wrec, u8 *data, s32 flag) {
    SceneEventA *ev = (SceneEventA *) arg0;
    u8 *o = (u8 *) obj;
    u8 *rec;
    u8 *next;
    s32 span;
    s32 type = ev->type;

    if (D_800E1024 != 0 && (type == 7 || type == 0xE || type == 0xF || type == 0x10 || type == 0x12)) {
        u8 colours[3][3];
        s16 *light;
        u8 *text;
        s32 k;

        *(SceneBytes9 *) colours = *(SceneBytes9 *) D_800844A8;
        if ((type == 7 && D_800BEECB != 0) || (type == 0xE && D_800BEECB != 4) || (type == 0xF && D_800BEECB != 2) ||
            (type == 0x10 && D_800BEECB != 3) || (type == 0x12 && D_800BEECB != 1)) {
            return 1;
        }
        light = func_1502354C(track, ev->b4 == 0);
        if (light == NULL) {
            return 1;
        }
        if (ev->b4 == 0) {
            if (SA_U8(light, 0xC) != 0) {
                func_1516D850(SA_PTR(light, 0x34));
            }
            text = (u8 *) D_800C3A00[player][ev->id];
            if (*text == 0xBE) {
                SA_S32(light, 4) = 0x8013;
                text++;
            } else if (*text == 0xBF) {
                SA_S32(light, 4) = 0x8019;
                text++;
            } else {
                SA_S32(light, 4) = 0x8011;
            }
            SA_PTR(light, 8) = text;
            SA_S16(light, 0x2A) = 100;
            SA_U8(light, 0xC) = 1;
            SA_S16(light, 0x28) = 0;
            rec = SA_REC(player, track);
            SA_PTR(light, 0x1C) = rec + 0xC;
            SA_U8(light, 0x2F) = 1;
            SA_PTR(light, 0x20) = rec + 0x10;
            SA_PTR(light, 0x24) = rec + 0x14;
            SA_U8(light, 0x2C) = colours[ev->b5][0];
            SA_U8(light, 0x2D) = colours[ev->b5][1];
            SA_U8(light, 0x2E) = colours[ev->b5][2];
            if (ev->b5 == 2) {
                SA_S32(light, 4) |= 0x40000;
            }
            SA_S32(light, 0x34) = func_1516AD20(0, 0, 0, NULL, (s32 *) ((u8 *) light + 4), flag);
        } else if (ev->b4 == 1) {
            func_150234E8(light, ev->b5);
        } else {
            if (ev->b5 == 0) {
                SA_PTR(light, 0x34) = func_1516D8E8(SA_PTR(light, 0x34));
            } else {
                SA_PTR(light, 0x34) = func_1516D934(SA_PTR(light, 0x34));
            }
            if (ev->w6 != 0) {
                k = ev->w6 - 1;
                SA_U8(light, 0x2C) = colours[k][0];
                SA_U8(light, 0x2D) = colours[k][1];
                SA_U8(light, 0x2E) = colours[k][2];
                if (k == 2) {
                    SA_S32(light, 4) |= 0x40000;
                } else {
                    SA_S32(light, 4) &= ~0x40000;
                }
            }
        }
        return 1;
    }

    switch (type) {
    case 0xC: /* object animation */
        if (ev->id != 0) {
            if (ev->w6 != 0) {
                func_1507EB4C(obj, ev->id);
            } else {
                if (ev->b5 != 0) {
                    span = 0xFFFF;
                } else {
                    span = func_15023C60(arg0, type, track, &next, 0, 0, 0, 0, 0, 0, player) - now;
                }
                func_1507E7E4(obj, ev->id, 3, span, ev->b4);
            }
        }
        return 1;
    case 0xD: /* object setup list id + 1: run / undo / set a parameter */
        if (obj != NULL) {
            if (ev->b4 == 0) {
                func_15083568(obj, ev->id + 1, 1.0f, 0);
            } else if (ev->b4 == 1) {
                func_150836CC(obj, ev->id + 1);
            } else {
                u8 *att = func_15031C4C(o, ev->id + 1, 0);

                if (att != NULL) {
                    if (ev->b4 == 2) {
                        SA_S16(att, 0x18) = D_800905C4[ev->b5];
                    } else if (ev->b4 == 3) {
                        SA_S16(att, 0x1A) = D_800905C4[ev->b5];
                    }
                }
            }
        }
        return 1;
    case 4: /* object +0x134 / +0x135: id and half the span (1 .. 255) */
        if (obj != NULL) {
            span = (func_15023C60(arg0, type, track, &next, 0, 0, 0, 0, 0, 0, player) - now) / 2;
            if (span >= 0x100) {
                span = 0xFF;
            } else if (span == 0) {
                span = 1;
            }
            if (ev->b4 == 0) {
                SA_U8(o, 0x135) = span;
                SA_U8(o, 0x134) = ev->id;
            }
        }
        return 1;
    case 3: /* switch the camera track: only to a track of ref kind 1 */
        if (ev->id < D_800C3A5A[player] && D_800C3A10[player][ev->id].kind == 1 && ev->id != D_800C3A18) {
            D_800C3A18 = ev->id;
            D_800DBFF4[0] = 4;
            SA_S32(D_800DBFF0, 0x5F0) |= 4;
        }
        return 1;
    case 9:
        if (obj != NULL) {
            SA_U8(o + ev->b4, 0x6C) = ev->id + 10;
        }
        return 1;
    case 1:
        if (obj != NULL) {
            SA_U8(o, 0x1C9) = ev->id != 0 ? ev->id : 0xFF;
        }
        return 1;
    case 5:
        break;
    default:
        return 0;
    }

    switch (ev->id) {
    case 0x3B:
        D_800DDE18 = ev->b4 == 0 ? (s32) (SA_REC(player, track) + 0x28) : 0;
        break;
    case 0x08:
        D_800C3A7A[player] = ev->b4 == 0;
        break;
    case 0x09:
        D_800C3A7C[player] = ev->b4 == 0;
        break;
    case 0x0D:
        D_800C3A78[player] = ev->b4 == 0;
        break;
    case 0x12:
        D_800C3A7E[player] = ev->b4 == 0;
        break;
    case 0x13:
        D_800C3A80[player] = ev->b4;
        break;
    case 0x15:
        D_800C3A82[player] = ev->b4 == 0;
        break;
    case 0x14:
        if (obj != NULL) {
            if (ev->b4 == 0) {
                func_15053430(obj);
            } else {
                func_15060F28(obj, 0);
            }
        }
        break;
    case 0x41: {
        u8 colours[2][3];

        *(SceneBytes6 *) colours = *(SceneBytes6 *) D_800844B4;
        if (obj != NULL) {
            if (ev->b4 == 0) {
                SA_U8(o, 0xA5) = colours[ev->b5][0];
                SA_U8(o, 0xA6) = colours[ev->b5][1];
                SA_U8(o, 0xA4) = 1;
                SA_U8(o, 0xA7) = colours[ev->b5][2];
                SA_PTR(o, 0xA0) = SA_REC(player, track) + 0x30;
            } else {
                SA_U8(o, 0xA4) = 0;
                SA_PTR(o, 0xA0) = NULL;
            }
        }
        break;
    }
    case 0x44: /* level change */
        if (ev->b5 != 0) {
            func_1501C710(2, (u16 *) (s32) ev->b4, ev->w6, 0, 0);
        } else {
            func_1501C710(1, (u16 *) (s32) ev->b4, 0, 0, 0);
        }
        break;
    case 0x17:
        if (obj != NULL) {
            SA_U8(o, 0x1FF) = ev->b4 == 0;
            if (SA_U8(o, 0x1FF) != 0) {
                SA_U8(o, 0x1FF) += ev->b5;
            }
            if (ev->b4 == 0) {
                SA_U8(o, 0x201) = ev->w6;
            }
        }
        break;
    case 0x16:
        if (obj != NULL) {
            SA_U8(o, 0x206) = ev->b4 == 0;
            if (SA_U8(o, 0x206) != 0) {
                SA_U8(o, 0x206) += ev->b5;
            }
            if (ev->b4 == 0) {
                SA_U8(o, 0x208) = ev->w6;
            }
        }
        break;
    case 0x18:
    case 0x66:
    case 0x6B:
        break;
    case 0x1D:
        if (D_800C3A10[player][track].kind == 3 && wrec != NULL) {
            SA_U8(wrec, 0x6E) = ev->b4 == 0 ? 1 : 0;
        }
        break;
    case 0x1E:
        D_800C39E2 = ev->b4 + 1;
        D_800C39E3 = D_800BE9F0;
        break;
    case 0x03: {
        u8 *r = func_151149AC(ev->w6);

        if (r != NULL) {
            SA_U8(r, 0x73) &= ~3;
            if (ev->b5 == 0) {
                SA_U8(r, 0x73) |= 2;
            } else {
                SA_U8(r, 0x73) |= 1;
            }
        }
        break;
    }
    case 0x6C:
        switch ((u8) ev->b4) {
        case 0: {
            f32 pos[3];

            rec = SA_REC(player, track);
            pos[0] = SA_F32(rec, 0);
            pos[1] = SA_F32(rec, 4);
            pos[2] = SA_F32(rec, 8);
            func_151BEE00(pos, SA_F32(rec, 0x10), 1, 0, 2, 0xFF, 1);
            break;
        }
        case 1: {
            f32 pos[3];

            rec = SA_REC(player, track);
            pos[0] = SA_F32(rec, 0);
            pos[1] = SA_F32(rec, 4);
            pos[2] = SA_F32(rec, 8);
            func_151A9940(5, 1, NULL, (s32) pos, -10000.0f, 100.0f, -1, flag, 1);
            break;
        }
        case 2:
            func_151494E0(0, ev->b5 != 0 ? 0x2B : 0x2C);
            break;
        case 3:
            if (ev->b5 != 0) {
                func_1515F170(1, 0);
                func_1515F170(2, 1);
            } else {
                func_1515F170(1, 1);
                func_1515F170(2, 0);
            }
            break;
        case 4:
            func_151645C4(ev->b5);
            break;
        case 5:
            func_151616D0(0x28, 0x17, 0);
            break;
        case 6:
            func_151CD90C(ev->b5);
            break;
        case 7:
            func_1515F170(3, ev->b5 != 0 ? 0 : 1);
            break;
        case 8:
            func_150B696C(ev->b5);
            break;
        case 9: {
            static const s32 sLights[4] = { 0x12, 0x13, 0x14, 0x15 };   /* D_80096DD0 */
            u8 i;

            for (i = 0; i < 4; i++) {
                func_151C9CBC(2, (s32) (D_800D34B8 + sLights[i] * 0x34));
            }
            break;
        }
        case 10:
            func_151CA398((u8 *) D_800DBFF0, 0, (s8) track, (u8) flag, 1);
            break;
        case 11:
            func_151CA484((u8 *) D_800DBFF0);
            break;
        case 12:
            func_150E0880();
            break;
        case 13:
            func_150FB2A8();
            break;
        case 14:
            func_150F58C0(9);
            break;
        case 15:
            func_150FAFC0(0xFF, 1);
            break;
        case 16:
            func_15169040(0, 0x4E);
            break;
        case 17:
            func_15169040(0, 0x4F);
            break;
        case 18:
            func_151CD944(ev->b5);
            break;
        case 19:
            func_1515F170(0xB, 0);
            break;
        case 20:
            if (obj != NULL) {
                func_15190A88(o);
                func_1518F9CC(0, 0x49);
            }
            break;
        case 21:
            func_151494E0(0, ev->b5 != 0 ? 0x55 : 0x56);
            break;
        case 22:
            if (obj != NULL) {
                func_151937F4(o, 0xFF, 1);
            }
            break;
        case 23:
            if (obj != NULL) {
                struct { u8 *obj; u8 kind; } ref;

                ref.obj = o;
                ref.kind = SA_U8(o, 0x3B);
                func_151920FC((s32) &ref, 0x50);
            }
            break;
        }
        break;
    case 0x6E: {
        s32 n;
        u8 *list = (u8 *) func_151905AC(o, &n);

        if (list != NULL && ev->w6 < n) {
            func_1518FA8C((s32) obj, list[ev->w6], -1, -1, -1, -1, 0, 0, 0xFF, 1);
        }
        break;
    }
    case 0x05: {
        s16 kinds[4][2];
        s32 k;
        s32 f;

        *(SceneHalves8 *) kinds = *(SceneHalves8 *) D_800844BC;
        if (ev->b4 == 0) {
            k = ev->b5 >= 4 ? 3 : ev->b5;
            span = func_15023C60(arg0, ev->type, track, &next, 1, ev->id, 0, 0, 1, ev->b5, player) - now;
            if (ev->w6 != 0) {
                span = 999;
                f = 0xFF;
            } else {
                f = (u8) flag;
            }
            func_1518D1C0(o, kinds[k][1], span, 0, f, 0, D_80096DE0);
        }
        break;
    }
    case 0x36:
        if (ev->b4 == 0) {
            func_1519D5A0((s32) obj, 0, 300, 0, flag, 0);
        } else if (ev->b4 == 1) {
            struct { u8 *obj; u8 kind; } ref;

            ref.obj = o;
            ref.kind = SA_U8(o, 0x3B);
            func_151482D4((s32) &ref, 7);
        }
        break;
    case 0x30:
        if (obj != NULL) {
            s32 anim;

            switch (ev->b4) {
            case 1:
                anim = 4;
                break;
            case 2:
                anim = 7;
                break;
            case 3:
                anim = 10;
                break;
            default:
                anim = 12;
                break;
            }
            func_1514D3B0((s32) obj, 0xD, anim, 0);
        }
        break;
    case 0x46:
        if (ev->b4 != 0) {
            func_150C6174((s32) obj);
        } else {
            func_150C619C((s32) obj);
        }
        break;
    case 0x25:
        D_800C3A70 = ev->b4 != 0 ? (f32) ev->b4 : D_800D9F40;
        func_1510B9D8(0, D_800C3A70, D_800C3A74);
        break;
    case 0x58:
        D_800C3A74 = ev->w6 != 0 ? (f32) (ev->w6 * 10) : D_800D9F3C;
        func_1510B9D8(0, D_800C3A70, D_800C3A74);
        break;
    case 0x3C:
        if (obj != NULL) {
            s32 bits = (ev->b4 << 16) | ev->w6;   /* w6 sign-extended, as the asm (lh) */

            if (ev->b5 == 0) {
                SA_S32(o, 0x94) = bits;
            } else if (ev->b5 == 1) {
                SA_S32(o, 0x94) |= bits;
            } else {
                SA_S32(o, 0x94) &= ~(bits | 1);
            }
        }
        break;
    case 0x3D: /* target: the object with setup id w6 & 0xFF */
        if (obj != NULL) {
            if (ev->b4 == 0) {
                s32 target = func_15083FB0(ev->w6);

                if (target != -1) {
                    SA_U8(o, 0x65) = target + 1;
                    SA_U8(o, 0x101) |= 4;
                    SA_S32(o, 0x5C) = ev->b5;
                }
            } else {
                SA_U8(o, 0x65) = 0;
            }
        }
        break;
    case 0x42:
        switch (ev->b4) {
        case 0:
            D_800D9CB0 = 1;
            break;
        case 1:
            D_800D9CB0 = 4;
            break;
        case 3:
            D_800D9CB0 = 2;
            break;
        case 4:
            D_800D9CB0 = 5;
            break;
        case 5:
            D_800D9CB0 = 6;
            break;
        case 6:
            D_800D9CB0 = 7;
            break;
        case 7:
            D_800D9CB0 = 8;
            break;
        case 8:
            D_800D9CB0 = 9;
            break;
        case 9:
            D_800D9CB0 = 10;
            break;
        }
        break;
    case 0x43:
        if (ev->b4 == 0) {
            rec = SA_REC(player, track);
            func_150B7700((s32) SA_F32(rec, 0x24), (s32) SA_F32(rec, 0x28),
                          func_15023C60(arg0, type, track, &next, 1, ev->id, 0, 0, 0, 0, player) - now, flag);
        }
        break;
    case 0x45:
        if (ev->b4 == 0) {
            func_151A5580(0, func_15023C60(arg0, type, track, &next, 1, ev->id, 0, 0, 0, 0, player) - now, 0xFF, 0, 0,
                          D_800BEE08, 0, 0);
        }
        break;
    case 0x49:
        if (obj != NULL && ev->b4 < 3) {
            SA_S32(o + ev->b4 * 4, 0x2E4) = ev->w6;
        }
        break;
    case 0x4B:
        if (obj != NULL) {
            SA_S32(o, 0x9C) = (u16) ev->w6 | ((u8) ev->b5 << 16) | (ev->b4 << 24);
        }
        break;
    case 0x4A:
        func_10011FB0(ev->b4 == 0 ? ev->b5 : 0);
        break;
    case 0x54:
        D_800C3A84[player] = ~ev->b4;
        break;
    case 0x55:
        func_150C851C(ev->b4);
        break;
    case 0x59:
        D_800C40AB = 1;
        break;
    case 0x5A:
        D_800C3E78 = SA_OBJ_INDEX(obj);
        switch (SA_U8(o, 4)) {
        case 0x53:
            SA_U8(o, 0x124) = 0;
            func_15052F9C(obj, 156.0f, 1, 4, 0, 10, 0xFF, 0, 1, 0);
            break;
        case 0x28:
            SA_U8(o, 0x124) = 0;
            func_15052F9C(obj, 180.0f, 5, 0x44, 1, 1, 0xFF, 0, 1, 0);
            break;
        case 0x21:
            SA_U8(o, 0x124) = 0;
            func_15052F9C(obj, 156.0f, 0x19, 4, 0, 15, 0xFF, 0, 1, 0);
            break;
        }
        break;
    case 0x71: /* release the player object (slot 0) */
        SA_S16(D_800CC2D0, 0xCC) = 0;
        SA_U8(SA_PTR(D_800CC2D0, 0x31C), 0x4E) = 0;
        SA_U8(D_800CC2D0, 0x65) = 0;
        SA_U8(SA_PTR(D_800CC2D0, 0x31C), 0x27) = 0;
        SA_S32(D_800CC2D0, 0xF8) &= ~0x01000000;
        if (obj != NULL) {
            SA_U8(o, 0x13C) = 0;
        }
        break;
    case 0x37: {
        u8 colours[3][3];
        s32 v;

        *(SceneBytes9 *) colours = *(SceneBytes9 *) D_800844CC;
        span = func_15023C60(arg0, ev->type, track, &next, 1, ev->id, 0, 0, 0, 0, player) - now;
        if (ev->b4 == 0) {
            v = ev->w6 != 0 ? ev->w6 : 0x7F;
            func_1517F9F8(colours[ev->b5][0], colours[ev->b5][1], colours[ev->b5][2], (s16) v, span, 0);
        } else {
            D_800DE240[0] = 0;
        }
        break;
    }
    case 0x38:
        span = func_15023C60(arg0, type, track, &next, 1, ev->id, 0, 0, 0, 0, player) - now;
        if (ev->b4 == 0) {
            func_1517FC90(ev->b5, span, ev->w6 != 0 ? ev->w6 : 4, 0x7F, 1);
        } else {
            D_800DDE08 = 0;
        }
        break;
    case 0x5C: /* camera fade in / hold / out: span to the event's b4 = 1 / 2 / 3 companions */
        if (ev->b4 == 0) {
            s32 end = func_15023C60(arg0, type, track, &next, 1, ev->id, 1, 1, 1, ev->b5, player);
            s32 in = func_15023C60(arg0, ev->type, track, &next, 1, ev->id, 1, 2, 1, ev->b5, player) - now;
            s32 out;

            if (next == NULL) {
                in = 0;
            }
            out = end - func_15023C60(arg0, ev->type, track, &next, 1, ev->id, 1, 3, 1, ev->b5, player);
            if (next == NULL) {
                out = 0;
            }
            if (D_800BE9F0 == 0x18) {
                func_150F59A0(in, end - now - out - in, out, ev->b5);
            } else if (D_800BE9F0 == 0x21) {
                func_1510AEB0(in, end - now - out - in, out);
            }
        }
        break;
    case 0x62:
        SA_U8(D_800B0DF0, 8) = 0;
        break;
    case 0x7C:
        D_800C3681 = ev->b4 == 0;
        break;
    case 0x84:
        D_800C3682 = ev->b4 == 0;
        break;
    case 0x85:
        D_800C3683 = ev->b4 == 0;
        break;
    case 0x63:
        D_80041FDC = ev->w6;
        break;
    case 0x64:
        if (ev->b4 == 0) {
            D_800DDE40 = 1;
            rec = SA_REC(player, track);
            D_800DE274 = rec + 0x28;
            D_800DE278 = rec + 0x24;
            D_800DE27C = rec + 0x2C;
        } else {
            D_800DDE40 = 0;
        }
        break;
    case 0x67: /* end of the logo scene: go to the title menu */
        func_151DECB4();
        break;
    case 0x73:
        func_151E5B94(0);
        break;
    case 0x69:
        if (obj != NULL) {
            switch (ev->b4) {
            case 0:
                SA_F32(o, 0x24) = 4.0f;
                SA_F32(o, 0x20) = 20.0f;
                break;
            case 1:
                SA_F32(o, 0x24) = 0.0f;
                SA_F32(o, 0x20) = 0.0f;
                break;
            case 2:
                func_150836CC(obj, 0x11);
                SA_U8(o, 0xA9) = 0;
                break;
            case 3:
                D_800C3E78 = SA_OBJ_INDEX(obj);
                SA_U8(D_800CC2D0, 0x13C) = D_800C3E78 + 100;
                SA_F32(D_800CC2D0, 0x3C) = 0.0f;
                SA_S16(SA_PTR(D_800CC2D0, 0x31C), 0x18) = 0;
                func_1505959C(obj, 0);
                SA_S32(o, 0x5C) = 9;
                SA_U8(o, 0x65) = 1;
                SA_U8(o, 0x101) |= 4;
                break;
            case 4:
                SA_U8(SA_PTR(D_800CC2D0, 0x31C), 0x17) = 1;
                break;
            case 5:
                D_800D154C = obj;
                func_15073F1C();
                break;
            case 6:
                SA_U8(SA_PTR(o, 0x31C), 0x4E) = 0;
                break;
            }
        }
        break;
    case 0x6A:
        D_800C3A94 = ev->w6;
        break;
    case 0x7A:
        D_800C3A9C = ev->b5 * 50;
        D_800C3A98 = ev->w6;
        break;
    case 0x6D:
        D_800C3A86 = ev->b4 == 0;
        break;
    case 0x74:
        D_800BEE2C = ev->b5;
        break;
    case 0x6F:
        if (obj != NULL) {
            SA_U8(o + ev->b4, 0x68) = ev->b5;
        }
        break;
    case 0x70:
        D_800C40AC = 1;
        break;
    case 0x72:
        if (obj != NULL) {
            SA_F32(o, 0xC8) = SA_S16(D_800D1C90[SA_U8(o, 4)], 6);
        }
        break;
    case 0x78:
        D_800C40AD = 1;
        break;
    case 0x79:
        if (wrec != NULL) {
            SA_S32(wrec, 0x84) = 0;
            SA_S32(wrec, 0x80) = 0;
            SA_S32(wrec, 0x7C) = 0;
        }
        break;
    case 0x7B:
        if (D_800BE9F0 == 0x1D) {
            D_800C3AA0 = 1;
        }
        break;
    case 0x7D:
        if (obj != NULL && ev->b4 == 0) {
            SA_U8(o, 5) = 1;
        }
        break;
    case 0x7E:
        if (obj != NULL) {
            D_800D18D0 = SA_OBJ_INDEX(obj);
        }
        break;
    case 0x7F:
        D_800DC2DC = 1;
        break;
    case 0x80:
        D_800BE9ED = ev->b4;
        break;
    case 0x81:
        func_15093818(ev->b4 ^ 1);
        D_800D2870 = ev->w6 * 25;
        break;
    case 0x82:
        D_800C40BD = (u8) ev->b4 >= 101 ? 100 : ev->b4;
        break;
    case 0x83:
        D_800C40BE = ev->w6;
        break;
    default:
        return 0;
    }
    return 1;
}
#undef SA_REC
#undef SA_U8
#undef SA_S8
#undef SA_S16
#undef SA_S32
#undef SA_F32
#undef SA_PTR
#undef SA_OBJ_INDEX
