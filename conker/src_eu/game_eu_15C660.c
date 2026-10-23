#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_15086268(f32, f32, f32, s32, s32);
f32 func_150ADDE0(f32 *, f32 *);
void func_150498A0(f32 *, f32, f32 *, f32, f32, f32);
void func_151254F4(struct108 *, s32);
void func_15124C38(struct108 *, f32 *);
void func_15128D50(struct108 *, f32 *, f32 *);
void func_1512DD50(u8 *);
void func_1512E6B0(u8 *);
struct127 *func_1505EEF4(s32);
void func_15130370(struct108 *, s32);
f32 sinf(f32);
f32 cosf(f32);
f32 sqrtf(f32);
extern u8 *D_800DC450;   /* camera position records, 0x18 bytes each (s16 x, y, z first) */
extern u8 *D_800DC454;   /* the record of the current fixed position */

#define EF(o) (*(f32 *)(p + (o)))
#define ES32(o) (*(s32 *)(p + (o)))
#define ES16(o) (*(s16 *)(p + (o)))
#define EU16(o) (*(u16 *)(p + (o)))
/* the camera request at +0x6FC (written by the level scripts / triggers) */
#define RQ_MODE (*(s32 *)(req + 0x00))
#define RQ_ID (*(s16 *)(req + 0x04))
#define RQ_ARG (*(s32 *)(req + 0x08))
#define RQ_X (*(s16 *)(req + 0x10))
#define RQ_Y (*(s16 *)(req + 0x12))
#define RQ_Z (*(s16 *)(req + 0x14))
#define RQ_A (*(u32 *)(req + 0x1C))
#define RQ_B (*(u32 *)(req + 0x20))
#define RQ_SAVED (*(s16 *)(req + 0x34))
/* the request state at +0x6CC */
#define ST_ID (*(s16 *)(st + 0x02))
#define ST_MODE (*(s16 *)(st + 0x04))
#define ST_PENDING (*(s16 *)(st + 0x06))
#define ST_EASING (*(s16 *)(st + 0x08))
#define ST_BLEND (*(f32 *)(st + 0x10))
#define ST_PUSH (*(f32 *)(st + 0x14))
#define ST_X (*(f32 *)(st + 0x18))
#define ST_Z (*(f32 *)(st + 0x20))

/* camera_apply_request: per-frame handler of camera `arg0`'s request record (+0x6FC: mode, id +4, argument +8,
 * point +0x10/12/14, values A +0x1C / B +0x20, both unsigned) with its state at +0x6CC. Skipped while +0x2C bit
 * 0x100 or 0x40000 or +0x73C. A new id restarts it (state +6 = 0, flag +0x92C = 0, channels C/D/2/7 cleared);
 * when +0x6CC is set and nothing is pending or easing, the mode is applied:
 *  4: hold (+0x272 = -1, +0x6C8 = 1, copy +0x1B4 / +0x1E0);
 *  7: follow the camera node graph (D_800D2778, 16-byte nodes, links at +9..+13): the eye (+0x2F8/2FC/300) is
 *     moved toward the closest point of the node's links (eased with func_150498A0 at rates +0x908 / +0x90C unless
 *     +0x23C snaps); flags from the argument (+0x920): 0x10 keeps x/z, 8 keeps the height (cam +0x2FC);
 *  5: fixed position record D_800DC450[A] (argument 5 / 0x11: jump there once, func_15128774);
 *  0xB: store A / B / argument as floats in state +0x24..+0x2C;
 *  0xA / 0xE: look at object func_1505EEF4(func_15083E0C(A low byte)) (target +0x618, 0xE via func_151254F4);
 *  0xF: func_1512DD50; 3: look at the request point; 2 / 1 / 0: keep distance A from the target, pushing the eye
 *     out along the heading +0x39C; 0xD: func_15123934 only.
 * Any other mode (or an inactive / pending request) settles: the state point (+0x18 / +0x20) blends into the
 * target +0x2A4 / +0x2AC (+0x10 += 0.015 up to 1), and a finished request (+0x6C8 == 1) is reset to mode 0xD. */
void func_1512EE50(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *req;
    u8 *st;
    u8 *node;
    u8 *link;
    u8 *obj;
    u8 *rec;
    s32 mode;
    s32 i;
    u8 l;
    f32 nodePos[3];
    f32 linkPos[3];
    f32 toEye[3];
    f32 axis[3];
    f32 along[3];
    f32 cand[3];
    f32 best[3];
    f32 bestD;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    f32 dist;
    f32 push;
    f32 k;

    if (ES32(0x2C) & 0x100) {
        return;
    }
    if (ES16(0x73C) != 0) {
        return;
    }
    func_151239CC(arg0, 0xD);
    req = p + 0x6FC;
    st = p + 0x6CC;
    if (ES32(0x2C) & 0x40000) {
        return;
    }
    if (RQ_ID != ST_ID) {
        p[0x92C] = 0;
        ST_PENDING = 0;
        ST_ID = RQ_ID;
        func_151239CC(arg0, 0xC);
        func_151239CC(arg0, 0xD);
        func_151239CC(arg0, 2);
        func_151239CC(arg0, 7);
    }
    if (RQ_MODE != 4 && (*(u8 **)(p + 0x3D4))[0x120] != 0 && p[0x92C] == 0) {
        ST_PENDING = 1;
    }
    if (ST_PENDING != 0) {
        func_151239CC(arg0, 0xC);
    }
    if (ES16(0x6CC) != 0 && ST_PENDING == 0 && ST_EASING == 0) {
        ST_MODE = RQ_MODE;
        if (RQ_MODE != 0xA) {
            func_15130370(arg0, RQ_ARG);
        }
        mode = RQ_MODE;
        if (mode == 4) {
            ES16(0x272) = -1;
            ES32(0x6C8) = 1;
            ES16(0x1C4) = ES16(0x1B4);
            ES16(0x1F0) = ES16(0x1E0);
            return;
        }
        if (mode == 7) {
            node = (u8 *)D_800D2778 + func_15086268(EF(0x2F8), EF(0x2FC), EF(0x300), 7, 0) * 16;
            bestD = 1e14f;
            if (ES32(0x2C) & 0x100) {
                return;
            }
            nodePos[0] = *(s16 *)(node + 0);
            nodePos[1] = *(s16 *)(node + 2);
            nodePos[2] = *(s16 *)(node + 4);
            func_15048F90((struct17 *)nodePos, (struct17 *)(p + 0x2F8), (struct17 *)toEye);
            for (i = 0; i != 5; i++) {
                l = node[9 + i];
                if (l != 0xFF) {
                    link = (u8 *)D_800D2778 + l * 16;
                    linkPos[0] = *(s16 *)(link + 0);
                    linkPos[1] = *(s16 *)(link + 2);
                    linkPos[2] = *(s16 *)(link + 4);
                    func_150491EC((struct17 *)nodePos, (struct17 *)linkPos, (struct17 *)axis);
                    func_15049148((struct17 *)axis, func_150ADDE0(axis, toEye), (struct17 *)along);
                    func_15048F20((struct17 *)nodePos, (struct17 *)along, (struct17 *)cand);
                    dx = EF(0x2F8) - cand[0];
                    dy = EF(0x2FC) - cand[1];
                    dz = EF(0x300) - cand[2];
                    d = dx * dx + dy * dy + dz * dz;
                    if (d < bestD) {
                        bestD = d;
                        best[0] = cand[0];
                        best[1] = cand[1];
                        best[2] = cand[2];
                    }
                }
            }
            if (func_15123934(arg0, ES32(0x2C), 0, ES32(0x134), 0xC) != 0) {
                ES32(0x6C8) = 1;
                ES32(0x84) &= 0x7FFFFFF9;
                EU16(0x920) = RQ_ARG;
                EF(0x924) = RQ_A;
                EF(0x928) = RQ_B;
                if (EU16(0x920) & 1) {
                    ES32(0x84) |= 4;
                }
                if (EU16(0x920) & 2) {
                    ES32(0x84) |= 2;
                }
                if (EU16(0x920) & 7) {
                    ES32(0x84) |= 0x20000;
                }
                p[0x92C] = 1;
            }
            if (EU16(0x920) & 0x20) {
                ES32(0x84) |= 8;
            } else {
                ES32(0x84) &= ~8;
            }
            EF(0x910) = 1.5f;
            EF(0x914) = 2.5f;
            if ((EU16(0x920) & 2) && (**(u16 **)(p + 0x36C) & 7)) {
                ES32(0x84) |= 8;
                EF(0x910) *= 0.25f;
                EF(0x914) *= 0.25f;
            } else if (EU16(0x920) & 0x40) {
                k = (30.0f < *(f32 *)(*(u8 **)(p + 0x3D0) + 0x3C)) ? 7.0f : 4.0f;
                EF(0x910) *= k;
                EF(0x914) *= k;
                ES32(0x84) |= 0x20000;
            }
            if (p[0x23C] != 0) {
                EF(0x918) = 0.0f;
                EF(0x908) = EF(0x910);
                EF(0x91C) = 0.0f;
                EF(0x90C) = EF(0x914);
            } else {
                func_150498A0((f32 *)(p + 0x908), EF(0x910), (f32 *)(p + 0x918), 1.5f, 2.0f, EF(0x7B4));
                func_150498A0((f32 *)(p + 0x90C), EF(0x914), (f32 *)(p + 0x91C), 1.5f, 2.0f, EF(0x7B4));
            }
            if (!(EU16(0x920) & 0x10)) {
                if (p[0x23C] != 0) {
                    EF(0x8F4) = 0.0f;
                    EF(0x904) = 0.0f;
                    EF(0x2F8) = best[0];
                    EF(0x300) = best[2];
                } else {
                    func_150498A0((f32 *)(p + 0x2F8), best[0], (f32 *)(p + 0x8F4), EF(0x908), EF(0x90C), EF(0x7B4));
                    func_150498A0((f32 *)(p + 0x300), best[2], (f32 *)(p + 0x904), EF(0x908), EF(0x90C), EF(0x7B4));
                }
            }
            if (!(EU16(0x920) & 8)) {
                if (p[0x23C] != 0) {
                    EF(0x2FC) = best[1];
                    EF(0x8FC) = 0.0f;
                } else {
                    func_150498A0((f32 *)(p + 0x2FC), best[1], (f32 *)(p + 0x8FC), EF(0x908), EF(0x90C), EF(0x7B4));
                }
            }
            func_15125594(arg0);
            EF(0x924) = RQ_A;
            EF(0x928) = RQ_B;
            EF(0x374) = EF(0x924);
            EF(0x348) = EF(0x928);
            if (EU16(0x920) & 4) {
                ES32(0x738) = 1;
                ES32(0x734) = RQ_ID | 0x4000;
            }
            return;
        }
        if (mode == 5) {
            if (func_15123934(arg0, 0x40, 0, 0, 0xC) != 0) {
                ES32(0x84) = (ES32(0x84) & ~0xE) | 0x200;
                EF(0x27C) = EF(0x2F8);
                EF(0x280) = EF(0x2FC);
                EF(0x284) = EF(0x300);
            }
            if (RQ_ARG == 5 || RQ_ARG == 0x11) {
                if ((s32)RQ_A != ES16(0x272)) {
                    ES16(0x272) = RQ_A;
                    D_800DC454 = D_800DC450 + ES16(0x272) * 0x18;
                    EF(0x278) = RQ_B;
                    EF(0x288) = *(s16 *)(D_800DC454 + 0);
                    EF(0x28C) = *(s16 *)(D_800DC454 + 2);
                    EF(0x290) = *(s16 *)(D_800DC454 + 4);
                    ES32(0x5F0) |= 4;
                    EF(0x2F8) = EF(0x27C) = EF(0x288);
                    EF(0x2FC) = EF(0x280) = EF(0x28C);
                    EF(0x300) = EF(0x284) = EF(0x290);
                    func_15128774(arg0, *(struct127 **)(p + 0x3D0));
                    p[0x23C] = 1;
                }
            } else {
                ES16(0x272) = RQ_A;
                D_800DC454 = D_800DC450 + ES16(0x272) * 0x18;
                EF(0x288) = *(s16 *)(D_800DC454 + 0);
                EF(0x28C) = *(s16 *)(D_800DC454 + 2);
                EF(0x290) = *(s16 *)(D_800DC454 + 4);
                EF(0x278) = RQ_B;
            }
            ES16(0x274) = RQ_ARG;
            ES32(0x6C8) = 1;
            return;
        }
        if (mode == 0xB) {
            *(f32 *)(st + 0x24) = RQ_A;
            *(f32 *)(st + 0x28) = RQ_B;
            *(f32 *)(st + 0x2C) = (u32)RQ_ARG;
            return;
        }
        if (mode == 0xA || mode == 0xE) {
            obj = (u8 *)func_1505EEF4(func_15083E0C(req[0x1F]));
            if (obj == NULL) {
                return;
            }
            if (func_15123934(arg0, 0x400, 0, ES32(0x134), 2) != 0) {
                if (RQ_MODE == 0xE) {
                    func_151254F4(arg0, (obj - (u8 *)D_800CC2D0) / 0x32C);
                }
                ES32(0x84) &= ~8;
                ES32(0x628) = 0;
                *(u8 **)(p + 0x614) = p + 0x618;
                ES32(0x6C8) = 1;
                EF(0x62C) = 0.0f;
                EF(0x5DC) = 0.0f;
                dx = EF(0x2F8) - *(f32 *)(obj + 0x14);
                dz = EF(0x300) - *(f32 *)(obj + 0x1C);
                dist = sqrtf(dx * dx + dz * dz);
                EF(0x618) = -sinf(EF(0x37C) * 0.017453292f) * dist + EF(0x2A4);
                EF(0x61C) = EF(0x2A8);
                EF(0x620) = -cosf(EF(0x37C) * 0.017453292f) * dist + EF(0x2AC);
                EF(0x384) = EF(0x37C);
            }
            if (RQ_MODE == 0xE) {
                rec = (u8 *)D_800CC2D0 + p[0x23D] * 0x32C;
                EF(0x618) = *(f32 *)(rec + 0x14);
                EF(0x61C) = *(f32 *)(rec + 0x18);
                EF(0x620) = *(f32 *)(rec + 0x1C);
            } else if (p[0x23C] != 0) {
                EF(0x618) = *(f32 *)(obj + 0x14);
                EF(0x61C) = *(f32 *)(obj + 0x18);
                EF(0x620) = *(f32 *)(obj + 0x1C);
            } else {
                EF(0x618) += (*(f32 *)(obj + 0x14) - EF(0x618)) * 0.04f;
                EF(0x61C) += (*(f32 *)(obj + 0x18) - EF(0x61C)) * 0.04f;
                EF(0x620) += (*(f32 *)(obj + 0x1C) - EF(0x620)) * 0.04f;
            }
            if (RQ_ARG != 0) {
                EF(0x374) = RQ_B;
                EF(0x34C) = (f32)(u32)RQ_ARG - (EF(0x2A8) - EF(0x61C));
                RQ_SAVED = RQ_ARG;
            }
            return;
        }
        if (mode == 0xF) {
            if (func_15123934(arg0, 0x800000, 0, ES32(0x134), 2) != 0) {
                ES32(0x134) = 0;
                ES32(0x84) = (ES32(0x84) | 0x200) & ~8;
                func_1512DD50(p);
            }
            return;
        }
        if (mode == 3) {
            if (func_15123934(arg0, 0x400, 0, ES32(0x134), 2) != 0) {
                ES32(0x628) = 0;
                *(u8 **)(p + 0x614) = p + 0x618;
                ES32(0x84) |= 8;
                EF(0x62C) = 0.0f;
                EF(0x5DC) = 0.0f;
                EF(0x374) = RQ_A;
                EF(0x34C) = RQ_B;
                RQ_SAVED = RQ_B;
                ES32(0x6C8) = 1;
            }
            EF(0x618) = RQ_X;
            EF(0x61C) = RQ_Y;
            EF(0x620) = RQ_Z;
            EF(0x374) = RQ_A;
            return;
        }
        if (mode == 2) {
            if (func_15123934(arg0, 0x2000, 0, ES32(0x134), 2) != 0) {
                EF(0x374) = RQ_A;
                EF(0x34C) = RQ_B;
                RQ_SAVED = RQ_B;
            }
            ES32(0x6C8) = 1;
            func_1512E6B0(p);
            dx = EF(0x2F8) - EF(0x2A4);
            dz = EF(0x300) - EF(0x2AC);
            dist = sqrtf(dx * dx + dz * dz);
            EF(0x370) = dist;
            if (dist < EF(0x374)) {
                push = EF(0x374) - EF(0x370);
                EF(0x2F8) += push * ST_PUSH * func_150AD78C(EF(0x39C));
                EF(0x300) += push * ST_PUSH * func_150AD780(EF(0x39C));
                ST_PUSH += 0.005f;
                if (ST_PUSH > 0.04f) {
                    ST_PUSH = 0.04f;
                }
            }
            func_15128D50(arg0, NULL, NULL);
            return;
        }
        if (mode == 1 || mode == 0) {
            dx = EF(0x2F8) - (f32)RQ_X;
            dz = EF(0x300) - (f32)RQ_Z;
            dist = sqrtf(dx * dx + dz * dz);
            if (ES32(0x6C8) == 0 || mode == 0) {
                if (func_15123934(arg0, ES32(0x2C), 0, ES32(0x134), 2) != 0) {
                    ES32(0x6C8) = 1;
                    EF(0x374) = RQ_A;
                    EF(0x34C) = RQ_B;
                    RQ_SAVED = RQ_B;
                    ES32(0x84) &= ~4;
                    if (RQ_MODE == 0) {
                        ES32(0x738) = 1;
                        ES32(0x734) = RQ_ID | 0x4000;
                    }
                }
            }
            EF(0x374) = RQ_A;
            EF(0x348) = EF(0x34C) = RQ_B;
            RQ_SAVED = RQ_B;
            if (dist < EF(0x374) && RQ_MODE == 1) {
                push = EF(0x374) - dist;
                EF(0x2F8) += push * ST_PUSH * func_150AD78C(EF(0x39C));
                EF(0x300) += push * ST_PUSH * func_150AD780(EF(0x39C));
                ST_PUSH += 0.0025f;
                if (ST_PUSH > 0.04f) {
                    ST_PUSH = 0.04f;
                }
            }
            if (RQ_MODE == 1) {
                ST_X += ((f32)RQ_X - ST_X) * 0.04f;
                ST_Z += ((f32)RQ_Z - ST_Z) * 0.04f;
                EF(0x2A4) += (ST_X - EF(0x2A4)) * 0.5f;
                EF(0x2AC) += (ST_Z - EF(0x2AC)) * 0.5f;
            }
            if (RQ_MODE != 0) {
                func_1512E6B0(p);
                func_15124C38(arg0, NULL);
                ST_BLEND = 0.0f;
            }
            return;
        }
        if (mode == 0xD) {
            func_15123934(arg0, ES32(0x2C), 0, ES32(0x134), 2);
            return;
        }
    }

    /* settle: no active request (or an unknown mode) */
    *(f32 *)(st + 0x24) = 0.0f;
    *(f32 *)(st + 0x28) = 0.0f;
    *(f32 *)(st + 0x2C) = 0.0f;
    if (ES16(0x6CC) == 0) {
        ST_PENDING = 0;
    }
    if (ES32(0x6C8) == 1 && ST_MODE == 1) {
        ST_X = EF(0x2A4) + (ST_X - EF(0x2A4)) * 0.5f;
        ST_PUSH = 0.0f;
        ST_Z = EF(0x2AC) + (ST_Z - EF(0x2AC)) * 0.5f;
    }
    if (ES32(0x2C) == 0x40) {
        ES16(0x272) = -1;
        func_151239CC(arg0, 0xC);
    }
    if (ES32(0x6C8) == 1) {
        if (ST_MODE == 0) {
            ST_X = EF(0x2A4);
            ST_Z = EF(0x2AC);
        }
        if (ST_MODE == 0xE) {
            EF(0x670) = 0.01f;
            func_151254F4(arg0, p[0x23D]);
        }
    }
    if (p[0x23C] != 0) {
        ST_X = EF(0x2A4);
        ST_BLEND = 1.0f;
        ST_Z = EF(0x2AC);
    } else {
        ST_X += (EF(0x2A4) - ST_X) * ST_BLEND;
        ST_Z += (EF(0x2AC) - ST_Z) * ST_BLEND;
    }
    EF(0x2A4) = ST_X;
    EF(0x2AC) = ST_Z;
    ST_BLEND += 0.015f;
    if (ST_BLEND > 1.0f) {
        ST_BLEND = 1.0f;
    }
    if (ST_BLEND != 1.0f && ST_MODE == 1) {
        ST_EASING = 1;
    } else {
        ST_EASING = 0;
    }
    if (ES32(0x6C8) == 1) {
        ES16(0x272) = -1;
        *(u8 **)(p + 0x614) = NULL;
        ES32(0x6C8) = 0;
        RQ_SAVED = 0;
        RQ_MODE = 0xD;
        EF(0x8F0) = 0.0f;
        EF(0x8F4) = 0.0f;
        EF(0x8F8) = 0.0f;
        EF(0x8FC) = 0.0f;
        EF(0x900) = 0.0f;
        EF(0x904) = 0.0f;
        EF(0x910) = 0.0f;
        EF(0x908) = 0.0f;
        EF(0x918) = 0.0f;
        EF(0x914) = 0.0f;
        EF(0x90C) = 0.0f;
        EF(0x91C) = 0.0f;
        EU16(0x920) = 0;
        p[0x92C] = 0;
        p[0x948] = 0;
        EF(0x384) = EF(0x37C);
        EF(0x924) = 0.0f;
        EF(0x928) = 0.0f;
        func_151239CC(arg0, 1);
        func_151239CC(arg0, 0xC);
        func_151239CC(arg0, 0xD);
        func_151239CC(arg0, 2);
        func_151239CC(arg0, 7);
    }
}
#undef EF
#undef ES32
#undef ES16
#undef EU16
#undef RQ_MODE
#undef RQ_ID
#undef RQ_ARG
#undef RQ_X
#undef RQ_Y
#undef RQ_Z
#undef RQ_A
#undef RQ_B
#undef RQ_SAVED
#undef ST_ID
#undef ST_MODE
#undef ST_PENDING
#undef ST_EASING
#undef ST_BLEND
#undef ST_PUSH
#undef ST_X
#undef ST_Z
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15C660/func_1512EE50.s")
#endif
#ifdef NON_MATCHING
void func_15130370(struct108 *arg0, s32 arg1) {
    s32 temp_t0;
    s32 temp_t5;
    s32 temp_t9;

    switch (arg1) {
    case 1:
        func_15123934(arg0, arg0->unk2C, 0, 0, 7);
        return;
    case 2:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 &= ~8;
        return;
    case 3:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x10000000;
        return;
    case 8:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x80;
        return;
    case 9:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        temp_t9 = arg0->unk84 & ~8;
        arg0->unk84 = temp_t9;
        arg0->unk84 = temp_t9 | 0x80;
        return;
    case 11:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x4000;
        return;
    case 12:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x8000;
        return;
    case 13:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x20000;
        return;
    case 16:
        func_15123934(arg0, 8, 0, arg0->unk134, 7);
        return;
    case 14:
        func_15123934(arg0, 2, 0, arg0->unk134, 7);
        return;
    case 18:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x100000;
        return;
    case 19:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x400000;
        return;
    case 21:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk190 = 0.0f;
        return;
    case 22:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x800;
        arg0->unk190 = -30.0f;
        return;
    case 25:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x40;
        return;
    case 23:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x01000000;
        return;
    case 24:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x80000000;
        return;
    case 26:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x10;
        return;
    case 27:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        arg0->unk84 |= 0x20;
        return;
    case 28:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        temp_t0 = arg0->unk84 | 0x10;
        arg0->unk84 = temp_t0;
        arg0->unk84 = temp_t0 & ~8;
        return;
    case 29:
        func_15123934(arg0, arg0->unk2C, 0, arg0->unk134, 7);
        temp_t5 = arg0->unk84 | 0x01000010;
        arg0->unk84 = temp_t5;
        arg0->unk84 = temp_t5 & ~8;
        return;
    case 30:
        func_15128774(arg0, arg0->unk3D0);
        /* fallthrough */
    default:
        return;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_15C660/func_15130370.s")
#endif