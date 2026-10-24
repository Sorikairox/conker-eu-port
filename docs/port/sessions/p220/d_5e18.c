/* P216 / P219: readable C for func_15065E18 (game_eu_90F50, 4838 words, 0x42-case switch on `kind` via jtbl_80099C40).
 * P216 wrote the prologue, the tail and most cases; P219 fixed cases 3 / 9 / 0x15 / 0x37 / 0x38 / 0x39 / 0x3C (missing
 * calls) and wrote 0x24 0x3B 0x12 0x23 0x17 0x1A 0x2A 0x1B 0x26 0x3A 0x3E. Case numbers come from the jump table
 * (`port_work/p216/jtbl.txt`, read from conker/conker.eu.bin); the rodata floats D_80099Dxx are written as literals
 * (exact values checked against the ROM). Cases 0xD 0x1C..0x20 0x29 0x2B 0x2C 0x2F..0x33 0x3D go straight to the tail. */
s32 func_15064240(struct127 *obj, s32 anim, s32 arg2, s8 kind, s32 held);   /* returns the anim (999 = none) */
s32 func_150836CC(struct127 *, s32);
s32 func_15083568(struct127 *, s32, f32, s32);
void func_1505E650(struct127 *, u16, f32, f32, f32, f32, s32);
void func_15060A30(s32, struct127 *);
void func_150D9098(struct127 *);
void func_150DC2F0(s32);
s32 func_1507BB28(s32, s32);
void func_151D4668(struct127 *);
void func_151D5308(struct127 *);
extern u16 D_80099A60[][4];  /* per weapon row (kind 2 / 0x13 / 0xA / other): {start, idle, fire, stop} anims */
extern u8 D_eu_800C3E78;
extern s16 D_800CC264;
extern u8 D_800CC2B0;
extern u8 D_800BE9A0;
extern s32 D_800BE9F0;       /* level */
extern u8 D_800BE616;
extern u8 *D_800CCA0C;
extern u8 D_800D2E68;
extern u8 *D_800D34B8;
extern s32 D_800D1580;

extern s32 D_800CC6A0;
extern s32 D_800CC6B0;
extern u16 D_800BEB30[];
void func_15080C28(s32);
void func_15080FE8(void);
s32 func_150810F4(void);
s32 func_151F2CDC(void);
extern s32 D_800864A0[2];
extern u16 D_80099A90[];
void func_1507EE9C(struct127 *);
void func_1507E7E4(struct127 *, u8, u8, u16, s32);
void func_150FC438(struct127 *, struct127 *, s32, u8);
s32 func_1000EC24();
void func_15073FA0(void);
struct127 *func_1506401C(struct127 *, s32);
void func_1514FAD8(s32);
extern s32 D_800BE9E4;
extern u8 D_800BE9B4;
extern u16 D_80099A80[];
extern u16 D_80099A88[];
struct127 *func_15083E90(u8);
s32 func_151D469C(struct127 *, s32, s32, s32, s32);
u16 func_1000FA64(u16, s16, s16, s16, s32, u16, s16, s32, void *, s32, s32, s32);
s32 func_1000F568(s32, s32);
void func_1000FD38(s32, s32, s32);
void func_10010558(u16, struct127 *, s32, s32, s32, s32);
void func_1512D854(s32, s32);
s32 func_150ADA20(void);
s32 func_15103D5C(s32, s32, s32, s32);
s32 func_1000EFB4(s32, s32, s32, s32, s32, s32, s32);

#define B(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define SH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define CTL ((u8 *)obj->unk31C)
#define POSARGS(o) (s16)(*(f32 *)((u8 *)(o) + 0x14)), (s16)(*(f32 *)((u8 *)(o) + 0x18)), (s16)(*(f32 *)((u8 *)(o) + 0x1C))


// player_item_action: per-frame action of the held item / pad mode `kind` (1..0x42) for the player obj.
// held = pressed-button word (0x4000 use, 0x2000 fire, 0x8000 ...), height = ground height (f32; +50 when obj +0x20 > 0).
// Picks an animation (returned; 999 = keep, 1000 = item finished) and plays it through func_1505E650 unless noAnim.
s32 func_15065E18(struct127 *obj, s32 buttons, s32 held, f32 height, s32 recurse, s32 kind, s32 stunned,
                  s32 timeout, s32 noAnim) {
    u8 done = 0;          /* sp13F: return 1000 */
    s32 setFlag58 = 0;    /* sp140 */
    s32 sound = 0;        /* sp138 */
    s32 clearItem = 1;    /* sp144 */
    f32 speed = 1.0f;     /* sp150 */
    f32 blend = 4.0f;     /* sp14C */
    f32 f148 = 0.0f;      /* sp148 */
    s32 anim = 0;         /* s3 */
    s32 row;
    u16 *r;

    if (B(CTL, 0x11A) == 3 || B(obj, 0x104) != 0 || recurse != 0) {
        held &= ~0x4000;
        D_800CC6AC &= ~0x4000;
        if (recurse != 0) {
            if (B(obj, 0x104) == 0) {
                W(obj, 0x1C4) = 0;
            }
            held &= ~0x2000;
            D_800CC6AC &= ~0x2000;
        }
    }
    if (0.0f < F(obj, 0x20)) {
        height += 50.0f;
    }
    switch (kind) {
    case 2: case 0xA: case 0x13: case 0x34: /* 15065F40: weapons, rows D_80099A60 */
        done = 1;
        row = (kind == 2) ? 0 : (kind == 0x13) ? 1 : (kind == 0xA) ? 2 : 3;
        if (stunned != 0) {
            if (kind == 0xA) {
                func_150836CC(obj, 0x28);
                func_150836CC(obj, 0x29);
                B(CTL, 0x11A) = 0;
            } else if (kind == 0x34) {
                func_150836CC(obj, 0x3D);
                B(CTL, 0x11A) = 0;
            }
        }
        if (kind == B(CTL, 0x78)) {
            F(obj, 0x3C) = 0.0f;
        }
        if (B(obj, 0xAD) != 0 && (kind == B(CTL, 0x78) || B(CTL, 0x11A) != 0)) {
            B(CTL, 0x78) = 0;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 0;
            if (kind == 0xA) {
                func_150836CC(obj, 0x28);
                func_150836CC(obj, 0x29);
                B(CTL, 0x11A) = 0;
            }
        } else if ((height <= 0.0f && (held & 0x4000)) || recurse != 0) {
            if (B(CTL, 0x78) != 0 || recurse != 0) {
                if (H(CTL, 0x72) == 0 || recurse != 0) {
                    B(obj, 0x89) = 0xFF;
                    B(obj, 0x8A) = 0xFF;
                    B(obj, 0x83) = 0xFF;
                    anim = D_80099A60[row][3];
                    B(CTL, 0x11A) = 3;
                    H(CTL, 0x72) = 0x5A;
                    setFlag58 = 1;
                }
            } else if (H(CTL, 0x72) == 0 && SH(W(obj, 0x318), 0x73C) != 1 && SH(W(obj, 0x318), 0x73C) != 3) {
                B(CTL, 0x1B) = 0;
                B(CTL, 0x11A) = 1;
                anim = D_80099A60[row][0];
                B(obj, 0x83) = 0xFF;
                B(obj, 0x89) = 0xFF;
                H(CTL, 0x72) = 0x5A;
            }
            held &= ~0x4000;
        }
        r = D_80099A60[row];
        if (B(CTL, 0x78) != 0 && (held & 0x2000) && anim == 0 && H(obj, 0x84) == r[1]) {
            anim = r[2];
            B(CTL, 0x1B)++;
        }
        if ((H(obj, 0x84) == r[1] || H(obj, 0x84) == r[0] || H(obj, 0x84) == r[2] || anim != 0) && anim != r[3]) {
            B(CTL, 0x78) = kind;
            *(u16 *)D_800CC6A4 &= ~0x2000;
            setFlag58 = 1;
        } else {
            B(CTL, 0x78) = 0;
        }
        if (D_eu_800C3E78 == 0) {
            break;
        }
        if (B(CTL, 0x11A) == 1 || B(CTL, 0x11A) == 2) {
            anim = r[1];
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x78) = kind;
            B(CTL, 0x11A) = 2;
            if (kind == 2 || kind == 0x13) {
                func_15083568(obj, 8, 1.0f, 0);
            } else if (kind == 0xA) {
                func_15083568(obj, 0x28, 1.0f, 0);
                func_15083568(obj, 0x29, 1.0f, 0);
            }
        } else {
            B(CTL, 0x11A) = 0;
            B(CTL, 0x78) = 0;
            if (kind == 2 || kind == 0x13) {
                func_150836CC(obj, 8);
            } else if (kind == 0xA) {
                func_150836CC(obj, 0x28);
                func_150836CC(obj, 0x29);
            } else if (kind == 0x34) {
                func_150836CC(obj, 0x3D);
            }
        }
        break;

    case 0x14: case 0x3F: { /* 15066378 */
        s32 animOn, animOff, sub, animSwim, animA, animB;
        if (kind == 0x14) {
            animOn = 0x102; animOff = 0x103; sub = 0x28; animSwim = 0x12B; animA = 0xF7; animB = 0xC3;
        } else {
            animOn = 0x2CA; animOff = 0x2CB; sub = 0x2F; animSwim = 0x2CE; animA = 0x2CC; animB = 0x2CD;
        }
        anim = 999;
        if (timeout != 0 && B(CTL, 0x78) != 0) {
            func_15083568(obj, sub, 1.0f, 0);
        }
        if ((held & 0x4000) && height <= 0.0f) {
            if (B(CTL, 0x78) != 0) {
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                B(obj, 0x8A) = 0xFF;
                B(CTL, 0x11A) = 3;
                speed = 2.0f;
                anim = animOff;
                B(CTL, 0x78) = 0;
            } else {
                B(obj, 0x89) = 0x10;
                B(obj, 0x83) = 0x10;
                B(obj, 0x8A) = 0x10;
                speed = 2.0f;
                B(CTL, 0x11A) = 1;
                anim = animOn;
                B(CTL, 0x78) = kind;
            }
        }
        if (anim != 999) {
            speed = 2.0f;
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            func_150836CC(obj, sub);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (kind != B(CTL, 0x78)) {
            break;
        }
        B(obj, 0xAA) = 0x4B;
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (B(CTL, 0x197) != 0) {
            B(obj, 0x8A) = 10;
            B(obj, 0x89) = 0;
            if ((held & 0x2000) && H(CTL, 0x72) == 0) {
                B(obj, 0x83) = 0xF;
                B(CTL, 0x1B4) |= 3;
                D_800CC2B0 = 1;
                f148 = 6.0f;
                anim = animSwim;
                H(CTL, 0x72) = 0x28;
            }
            break;
        }
        if ((held & 0x2000) && height <= 0.0f && B(obj, 0x89) == 0 && H(CTL, 0x72) == 0) {
            H(CTL, 0x72) = 0x28;
            anim = (2.0f < F(obj, 0x3C)) ? animB : animA;
            B(obj, 0x89) = 0xF;
            B(obj, 0x83) = 0xF;
            B(obj, 0x8A) = 0xF;
        }
        break;
    }

    case 3: /* 1506660C */
        done = 1;
        if (recurse != 0 || stunned != 0) {
            if (D_800BE9F0 != 0xA) {
                B(CTL, 0x78) = 0;
                B(CTL, 0xD) = 0;
                B(obj, 0x83) = 0;
            }
            if (stunned != 0) {
                clearItem = 0;
            }
            break;
        }
        if (B(CTL, 0x16) != 0) {
            break;
        }
        if (SH(CTL, 0x8) != 0) {
            SH(CTL, 0x8) -= D_800BE9A0;
            if (SH(CTL, 0x8) < 100) {
                SH(CTL, 0xE) = 0xAD;
                B(CTL, 0x16) = 0xC8;
                func_1507EB4C(obj, 0x2A);
                speed = 1.3f /* D_80099D48 */;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                B(CTL, 0x78) = 0;
                anim = 0x2D;
            }
        }
        if (B(CTL, 0x16) != 0) {
            break;
        }
        if (height <= 0.0f && (held & 0x4000)) {
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            if (B(CTL, 0x78) != 0) {
                speed = 1.3f /* D_80099D4C */;
                anim = 0x2D;
                B(CTL, 0x78) = 0;
            } else {
                B(CTL, 0x78) = 3;
                B(CTL, 0xD) = 0;
                anim = 0x2E;
                speed = 1.6f /* D_80099D50 */;
            }
            break;
        }
        if (B(CTL, 0x78) != 3 || B(obj, 0x89) == 0xFF) {
            break;
        }
        B(CTL, 0x78) = 3;
        anim = 0x2C;
        if (D_800BE616 != 0) {
            B(obj, 0x8A) = 10;
        }
        D_800CC6D2 = ((s8 *)D_800CC6A4)[2] * 150;
        if (B(CTL, 0x84) != 0) {
            SH(CTL, 0x12) = 0;
        } else if (D_800CC6D2 < -8000 && SH(CTL, 0x12) < -7000) {
            H(obj, 0x7A) = H(obj, 0x76) = H(obj, 0x76) + D_800CC264 * 7;
            anim = 0xE0;
            speed = 3.0f;
        } else if (D_800CC6D2 > 8000 && SH(CTL, 0x12) > 7000) {
            H(obj, 0x7A) = H(obj, 0x76) = H(obj, 0x76) - D_800CC264 * 7;
            anim = 0xE0;
            speed = 3.0f;
        }
        D_800CC6D4 = 10.0f;
        blend = 8.0f;
        B(obj, 0x89) = 0x10;
        B(obj, 0x83) = 0x10;
        if (B(CTL, 0xD) == 0) {
            B(CTL, 0xD) = 1;
            func_150D9098(obj);
        }
        break;

    case 1: case 0x35: /* 150668EC */
        if (!(held & 0x4000) || (!(height <= 0.0f) && kind != 0x35) || D_800CCA0C[0x4E] == 1 ||
            B(obj, 0x13C) >= 100 || B(obj, 0xA9) != 0) {
            break;
        }
        B(obj, 0x81) = 1;
        B(obj, 0xA9) = 2;
        B(obj, 0x89) = 0x78;
        F(obj, 0x24) = 6.0f;
        F(obj, 0x1CC) = -100000.0f /* D_80099D54 */;
        F(obj, 0x3C) = F(obj, 0x3C) * 0.5f;
        anim = 0x4A;
        speed = 1.8f /* D_80099D58 */;
        F(obj, 0x20) = 80.0f;
        B(CTL, 0x31) = 0;
        break;

    case 4: /* 150669B4 */
        B(CTL, 0x78) = (held & 0x4000) ? kind : 0;
        return 0;

    case 0x42: /* 150669D8 */
        if (!(D_800D2E68 & 4)) {
            if (held & 0x4000) {
                B(CTL, 0x78) = kind;
                return 0;
            }
            B(CTL, 0x78) = 0;
        }
        return 0;

    case 5: /* 15066A10 */
        if (!(held & 0x4000) || !(height <= 0.0f)) {
            break;
        }
        if (H(obj, 0x84) == 0x2F) {
            anim = 999;
            break;
        }
        B(CTL, 0x30) = 0x12;
        anim = 0x2F;
        if (D_800BE9F0 == 0x31) {
            F(CTL, 0x28) = SH(D_800D34B8, 0x270);
            F(CTL, 0x2C) = SH(D_800D34B8, 0x274);
            func_150DC2F0(5);
        } else {
            F(CTL, 0x28) = SH(D_800D34B8, 0x68);
            F(CTL, 0x2C) = SH(D_800D34B8, 0x6C);
            func_150DC2F0(0);
        }
        H(obj, 0x76) = 0xC000;
        speed = 1.05f /* D_80099D5C */;
        blend = 6.0f;
        B(obj, 0x89) = 0xFF;
        B(obj, 0x83) = 0xFF;
        sound = 0x143;
        break;

    case 6: /* 15066B3C */
    case 7: /* 15066C24: same with anim 0x45, mode 7 */
        if (B(CTL, 0x78) == 0) {
            if ((held & 0x4000) && height <= 0.0f && H(CTL, 0x72) == 0) {
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                anim = (kind == 6) ? 0x44 : 0x45;
                B(CTL, 0x78) = (kind == 6) ? 6 : 7;
            }
        } else if (H(obj, 0x84) == ((kind == 6) ? 0x44 : 0x45)) {
            anim = 999;
        } else {
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 0;
            B(CTL, 0x78) = 0;
        }
        break;

    case 0x36: /* 15066BC0 */
        if ((held & 0x4000) && height <= 0.0f) {
            u8 *t = (u8 *)func_15031C4C(obj, 0x3C, 0);
            if (t != NULL && W(t, 0x38) < 250) {
                anim = 0x240;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x8A) = 0xFF;
                B(obj, 0x83) = 0xFF;
            }
        }
        break;

    case 8: { /* 15066CA8: the other player obj +0x65 */
        u8 *other = (u8 *)D_800CC2D0 + (B(obj, 0x65) - 1) * 0x32C;
        B(obj, 0x8A) = 0x14;
        if (!(held & 0xC000)) {
            break;
        }
        if (H(other, 0x84) == 0 || H(other, 0x22E) != 0 || H(other, 0x84) == 0xC || H(other, 0x84) == 0xD) {
            s32 code = 0x10;
            D_800D154C = (struct127 *)other;
            if (held & 0x4000) {
                code = 0xE;
            } else {
                H(other, 0x84) = 0;
            }
            W(other, 0x218) = func_1507BB28(1, code);
            H(other, 0x21C) = 0;
            D_800D154C = obj;
            H(other, 0x22E) = 0;
        }
        anim = 999;
        break;
    }

    case 0x27: /* 15066D6C */
        if (kind != B(CTL, 0x78)) {
            B(CTL, 0x78) = 0x27;
            B(obj, 0x1C9) = 6;
            B(CTL, 0x17) = 1;
        }
        break;

    case 9: { /* 15066D9C: steerable item (anim 0x7B), matrix-physics mode spins ctl +0x7E */
        u8 fire = 0; /* sp10C */
        if (D_eu_800C3E78 != 0) {
            if (B(CTL, 0x11A) == 1 || B(CTL, 0x11A) == 2) {
                func_150637B4(obj);
            } else {
                func_15063894(obj);
            }
        }
        if (kind != B(CTL, 0x78)) {
            speed = 1.4f; /* D_80099D74 */
            anim = func_15064240(obj, 0x7B, 1, kind, held);
            if (anim != 999) {
                SH(CTL, 0x24) = 0x3C;
            }
            break;
        }
        {
            s16 d;
            d = -((s8 *)D_800CC6A4)[2] * 100 - SH(CTL, 0x80);
            if (d > 600) d = 600;
            if (d < -600) d = -600;
            SH(CTL, 0x80) += d;
            d = ((s8 *)D_800CC6A4)[3] * 32 - SH(CTL, 0x82) + 0x240;
            if (d > 300) d = 300;
            if (d < -300) d = -300;
            SH(CTL, 0x82) += d;
        }
        if ((recurse != 0 && (B(obj, 0x65) != 0 || B(obj, 0x104) != 0 || F(obj, 0x28) != 0.0f)) || B(obj, 0xAD) != 0) {
            func_15063894(obj);
            break;
        }
        if (recurse != 0) {
            speed = 1.4f; /* D_80099D60 */
            anim = func_15064240(obj, 0x7D, 1, 0, held | 0x4000);
            if (anim == 999) {
                func_15063894(obj);
            }
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 10;
        if (B(CTL, 0x7D) != 0) {
            if ((buttons & 0x2000) && F(obj, 0x48) < 0.6f /* D_80099D64 */) {
                u16 old = H(CTL, 0x7E);
                H(CTL, 0x7E) = old + D_800CC264 * 4 / 3;
                if ((old ^ H(CTL, 0x7E)) & 0x100) {
                    D_800D1580 = 0x13;
                    if (H(CTL, 0x7E) & 0x200) {
                        D_800D1580 = 0x14;
                    }
                    func_15071D38();
                    D_800D1580 = 0xFF0306E0;
                    func_1506E5FC();
                    func_10010630((func_150ADA20() & 1) + 0x2F5, obj, 0x7D00, 0x1F4, 1000);
                    if ((func_150ADA20() & 7) == 0) {
                        func_10010720(0x5CD, obj, 0x5DC0, 0x1F4, 1000, 0x32);
                    }
                }
            } else {
                u16 v = H(CTL, 0x7E);
                H(CTL, 0x7E) = (v & 0xFF00) | ((v * 2 + 1) & 0xFF);
            }
            break;
        }
        func_15063DE8((u8 *)obj, buttons, 0x2010);
        if (H(obj, 0x84) == 0x11A || H(obj, 0x84) == 0x7B) {
            break;
        }
        if (!(buttons & 0x2000) && (H(CTL, 0x88) & 0x2000)) {
            fire = 1;
        }
        if (SH(CTL, 0x24) == 0 || (held & 0x8000)) {
            anim = 0x11A;
            if (!(held & 0x8000)) {
                fire = 1;
            }
            SH(CTL, 0x24) = 0x3C;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
        } else if ((buttons & 0x2000) && B(obj, 0x89) == 0) {
            anim = 0x7C;
            if (F(obj, 0x3C) != 0.0f) {
                anim = 0x20D;
                if (20.0f <= F(obj, 0x44)) {
                    anim = 0x238;
                    speed = F(obj, 0x3C) / 22.0f + 0.4f; /* D_80099D68 */
                }
                if (!(buttons & 0x10)) {
                    SH(CTL, 0x12) = 0;
                    B(CTL, 0x3C) = 3;
                } else {
                    B(CTL, 0x3C) = 0;
                }
                if (D_800BE616 == 0) {
                    B(obj, 0xAA) = 0x37;
                }
            }
            B(obj, 0x83) = 8;
            if (H(obj, 0x84) != 0x7C && H(obj, 0x84) != 0x20D && H(obj, 0x84) != 0x238) {
                /* fire sounds (inlined in the asm): sound 0x2CF at the obj, then for obj kinds 0x3B / 0x80 one time in
                 * four a voice line; D_80099A80 is passed through to func_1000FA64 */
                func_151D4668(obj);
                func_1000FA64(0x2CF, POSARGS(obj), 0x7FFF, 1000, 0x1F4, (s32)func_1000EFB4, obj, (s32)D_80099A80, 0, 0);
                if ((B(obj, 4) == 0x3B || B(obj, 4) == 0x80) && (func_150ADA20() & 3) == 0) {
                    u16 v = (B(obj, 4) == 0x3B) ? func_1000F568(0x543, 4) : func_1000F568(0x57C, 6);
                    func_1000FA64(v, POSARGS(obj), 0x7FFF, 1000, 0x1F4, (s32)func_1000EFB4, obj, (s32)D_80099A80, 0, 0);
                }
            }
        } else if (W(obj, 0x2EC) != 0 && D_800BE9F0 == 0x36) {
            if ((held & 0x4000) && W(obj, 0x2EC) == 1 && F(obj, 0x28) == 0.0f) {
                blend = 16.0f;
                speed = 0.7f; /* D_80099D6C */
                anim = 0x20F;
                H(obj, 0x76) = 0;
                if (0.0f < F(obj, 0x14)) {
                    H(obj, 0x76) = 0x8000;
                    anim = 0x20E;
                }
                F(obj, 0x3C) = 0.0f;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                B(obj, 0x81) = 1;
            }
        } else {
            speed = 1.4f; /* D_80099D70 */
            anim = func_15064240(obj, 0x7D, 1, 0, held);
        }
        if (fire) {
            func_151D5308(obj);
        }
        break;
    }

    case 0x38: { /* 1506749C: anims 0x1DD..0x254, charge ctl +0x1A2 / +0x1A4 */
        u8 fire = 0; /* sp107 */
        s32 a0;
        if (kind != B(CTL, 0x78)) {
            speed = 1.4f; /* D_80099D80 */
            anim = func_15064240(obj, 0x1DD, 1, kind, held);
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            func_150836CC(obj, 0x7B);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 10;
        func_15063DE8((u8 *)obj, buttons, 0x2010);
        a0 = H(obj, 0x84);
        if (a0 == 0x1DD) {
            break;
        }
        if (!(buttons & 0x2000) && (H(CTL, 0x88) & 0x2000)) {
            fire = 1;
        }
        if (buttons & 0x2000) {
            anim = 0x1E0;
            if (F(obj, 0x3C) != 0.0f) {
                anim = 0x253;
                if (20.0f <= F(obj, 0x44)) {
                    anim = 0x254;
                    speed = F(obj, 0x3C) / 22.0f + 0.4f; /* D_80099D78 */
                }
                if (!(buttons & 0x10)) {
                    B(CTL, 0x3C) = 3;
                    SH(CTL, 0x12) = 0;
                }
            }
            blend = 0.0f;
            B(obj, 0x83) = 8;
            if (a0 != 0x1E0 && a0 != 0x253 && a0 != 0x254) {
                /* fire sounds (inlined in the asm): sound 0x2CF at the obj, then for obj kinds 0x3B / 0x80 one time in
                 * four a voice line; D_80099A88 is passed through to func_1000FA64 */
                func_151D4668(obj);
                func_1000FA64(0x2CF, POSARGS(obj), 0x7FFF, 1000, 0x1F4, (s32)func_1000EFB4, obj, (s32)D_80099A88, 0, 0);
                if ((B(obj, 4) == 0x3B || B(obj, 4) == 0x80) && (func_150ADA20() & 3) == 0) {
                    u16 v = (B(obj, 4) == 0x3B) ? func_1000F568(0x543, 4) : func_1000F568(0x57C, 6);
                    func_1000FA64(v, POSARGS(obj), 0x7FFF, 1000, 0x1F4, (s32)func_1000EFB4, obj, (s32)D_80099A88, 0, 0);
                }
            }
            H(CTL, 0x1A4) += D_800BE9E4 * 10;
            if (H(CTL, 0x1A2) >= 0xB0) {
                H(CTL, 0x1A2) = 0xAF;
            }
            H(CTL, 0x1A2) += H(CTL, 0x1A4) * D_800BE9E4;
            if (H(CTL, 0x1A2) > 0x1E00) {
                H(CTL, 0x1A2) = 0x1E00;
            }
        } else {
            speed = 1.4f; /* D_80099D7C */
            anim = func_15064240(obj, 0x1DE, 1, 0, held);
            H(CTL, 0x1A2) = 0;
            H(CTL, 0x1A4) = 0;
        }
        if (fire) {
            func_151D469C(obj, 5, 0x78, 0xFF, 1);
        }
        break;
    }

    case 0x39: /* 15067854: anims 0x1EE / 0x21E / 0x1EB, shot sound */
        if (kind != B(CTL, 0x78)) {
            speed = 1.4f; /* D_80099D88 */
            anim = func_15064240(obj, 0x1EE, 1, kind, held);
            if (anim != 999) {
                SH(CTL, 0x24) = 0x1E;
            }
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            func_150836CC(obj, 0x82);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 10;
        func_15063DE8((u8 *)obj, buttons, 0x2010);
        if (H(obj, 0x84) == 0x1EE) {
            break;
        }
        if (H(obj, 0x84) == 0x21E) {
            B(obj, 0x89) = 0xFF;
        }
        if (SH(CTL, 0x24) == 0 || ((held & 0x8000) && H(obj, 0x84) != 0x21E)) {
            if (F(obj, 0x28) == 0.0f) {
                SH(CTL, 0x24) = 0x1E;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                anim = 0x21E;
            }
            break;
        }
        if ((held & 0x2000) && H(obj, 0x84) != 0x1EE && H(obj, 0x84) != 0x21E) {
            anim = 999;
            if (F(obj, 0x3C) == 0.0f) {
                anim = 0x1EB;
            } else {
                D_800D1580 = 0x53;
                func_15071D38();
            }
            func_1000FD38((s32)func_15103D5C, (s32)obj, B(obj, 0x3B));
            func_1000FA64((func_150ADA20() & 1) + 0x2F3, (s16)F(obj, 0x14), (s16)F(obj, 0x18), (s16)F(obj, 0x1C), 0x7D00,
                          0x5DC, 0x1F4, (s32)func_15103D5C, obj, B(obj, 0x3B), 0, 0);
            if (W(obj, 0x318) != 0) {
                func_10010558((u32)func_150ADA20() % 3 + 0x2EB, obj, 0x7D00, 0x64, 0x78, 0x19);
            }
        } else {
            speed = 1.4f; /* D_80099D84 */
            anim = func_15064240(obj, 0x1EF, 1, 0, held);
        }
        break;

    case 0x37: /* 15067AE4: anims 0x1F7 / 0x1F4 / 0x235 / 0x1F8 */
        if (kind != B(CTL, 0x78)) {
            speed = 1.4f; /* D_80099D90 */
            anim = func_15064240(obj, 0x1F7, 1, kind, held);
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            func_150836CC(obj, 0x85);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 10;
        func_15063DE8((u8 *)obj, buttons, 0x2010);
        if ((held & 0x2000) && H(obj, 0x84) != 0x1F7 && H(CTL, 0x19E) == 0) {
            anim = (func_150ADA20() & 3) ? 0x1F4 : 0x235;
            blend = 0.0f;
            H(CTL, 0x19E) = 100;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
        } else if (held & 0x4000) {
            speed = 1.4f; /* D_80099D8C */
            anim = func_15064240(obj, 0x1F8, 1, 0, held);
        }
        break;

    case 0xB: /* 15067C14: anim 0x68 */
        if (H(obj, 0x84) == 0x68) {
            if (F(W(obj, 0x2D0), 8) < 68.0f && B(obj, 0x222) != 0) {
                D_800CC6D2 = H(obj, 0x7A) - func_15063740((u8 *)obj) - 0x2000;
            }
            D_800CC6D4 = 4.0f;
            anim = 999;
            break;
        }
        if ((held & 0x4000) && height <= 0.0f) {
            speed = 1.2f; /* D_80099D94 */
            anim = 0x68;
            blend = 6.0f;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
        }
        break;

    case 0xC: case 0x16: /* 15067CD4: anims 0x76 / 0x78 / 0x77 / 0x207 / 0x2C7 */
        anim = 999;
        if (recurse != 0 && kind == 0x16) {
            if (kind == B(CTL, 0x78)) {
                s32 end = 1;
                if ((s32)F(obj, 0x28) == 0) {
                    anim = func_15064240(obj, 0x78, 1, 0, held | 0x4000);
                    if (anim != 999) {
                        end = 0;
                    }
                }
                if (end) {
                    func_150836CC(obj, 0x24);
                    B(CTL, 0x11A) = 0;
                    B(obj, 0x83) = 0;
                    B(obj, 0x89) = 0;
                }
            }
        } else if (kind != B(CTL, 0x78)) {
            anim = func_15064240(obj, 0x76, 1, kind, held);
        } else {
            B(obj, 0x8A) = 10;
            if (recurse != 0 && (B(obj, 0x65) != 0 || (s32)F(obj, 0x28) != 0)) {
                func_150836CC(obj, 0x24);
                B(CTL, 0x11A) = 0;
            } else if (stunned != 0) {
                if (kind == 0x16 || (kind == 0xC && F(obj, 0x28) == 0.0f && B(obj, 0x1CA) != 0)) {
                    clearItem = 0;
                } else {
                    func_150836CC(obj, 0x24);
                    B(CTL, 0x11A) = 0;
                }
            } else if ((held & 0x4000) || recurse != 0) {
                anim = func_15064240(obj, 0x78, 1, 0, held | 0x4000);
                if (anim == 999 && recurse != 0) {
                    func_150836CC(obj, 0x24);
                    B(CTL, 0x11A) = 0;
                    B(obj, 0x83) = 0;
                }
            } else if ((held & 0x2000) && H(obj, 0x84) != 0x76 && H(CTL, 0x19E) == 0) {
                if (B(CTL, 0x1B2) != 0) {
                    anim = 0x2C7;
                } else if (kind == 0xC || D_800BE9F0 == 0x2B) {
                    anim = 0x207;
                } else {
                    anim = D_800BE616 ? 0x77 : 0x207;
                }
                blend = 0.0f;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                if (B(CTL, 0x197) != 0 && W(obj, 0x318) != 0) {
                    func_1512D854(W(obj, 0x318), 0);
                }
                H(CTL, 0x19E) = 100;
            } else if (B(CTL, 0x197) != 0 && W(obj, 0x318) != 0 && B(obj, 4) == 0x80 && func_10010894(obj) == 0 &&
                       (func_150ADA20() & 0x7F) == 0) {
                func_15060A30(func_1000F568(0x568, 4), obj);
            }
        }
        if (kind == 0xC && (kind == B(CTL, 0x78) || B(CTL, 0x11A) != 0)) {
            F(obj, 0x3C) = 0.0f;
            if ((s32)F(obj, 0x28) != 0) {
                func_150836CC(obj, 0x24);
                B(CTL, 0x11A) = 0;
                B(CTL, 0x78) = 0;
            }
        }
        break;

    case 0x19: case 0x40: /* 15068034 */
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (kind != B(CTL, 0x78)) {
            anim = func_15064240(obj, (kind == 0x19) ? 0x10E : 0x2C2, 1, kind, held);
            break;
        }
        if (B(CTL, 0x11A) != 2) {
            break;
        }
        if (held & 0x2000) {
            anim = func_15064594((u8 *)obj, 0x113, 0x113, 0x119);
            B(obj, 0x89) = 0xFF;
        } else {
            anim = func_15064240(obj, (kind == 0x19) ? 0x110 : 0x2C3, 1, 0, held);
        }
        break;

    case 0xE: /* 150680F4 */
        B(obj, 0x8A) = 0x14;
        anim = 999;
        break;

    case 0xF: /* 15068104: anims 0xB4 / 0xB6 */
        anim = 999;
        if (kind == B(CTL, 0x78) && (stunned != 0 || B(obj, 0x65) != 0 || recurse != 0)) {
            func_150836CC(obj, 0x3A);
            B(CTL, 0x11A) = 0;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 0;
        } else if ((held & 0x4000) && height <= 0.0f) {
            anim = (kind == B(CTL, 0x78)) ? 0xB6 : 0xB4;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x78) = kind;
        }
        if (kind == B(CTL, 0x78)) {
            B(obj, 0x8A) = 10;
            F(obj, 0x3C) = 0.0f;
        }
        break;

    case 0x10: /* 150681BC: anims 0xBE / 0xC1 / 0xC0, stick x -> D_800CC6D2 */
        speed = 1.4f; /* D_80099D98 */
        if (kind != B(CTL, 0x78)) {
            anim = func_15064240(obj, 0xBE, 1, kind, held);
            break;
        }
        D_800CC6D2 = ((s8 *)D_800CC6A4)[2] * 200;
        B(obj, 0x8A) = 10;
        if ((buttons & 0x2000) && H(obj, 0x84) != 0xBE) {
            anim = 0xC1;
            speed = 1.0f;
        } else {
            anim = func_15064240(obj, 0xC0, 1, 0, held);
        }
        break;

    case 0x15: /* 15068274: anims 0x168 / 0xE7 / 0x22B / 0xE4 */
        if (kind != B(CTL, 0x78)) {
            anim = func_15064240(obj, 0x168, 1, kind, held);
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            func_150836CC(obj, 0x4B);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 10;
        func_15063DE8((u8 *)obj, buttons, 0x2010);
        if ((buttons & 0x2000) && H(obj, 0x84) != 0x168) {
            anim = 0xE7;
            if (F(obj, 0x3C) != 0.0f) {
                B(obj, 0xAA) = 0x50;
                B(CTL, 0x3C) = 3;
                SH(CTL, 0x12) = 0;
                speed = F(obj, 0x3C) * 0.0625f + 0.6f; /* D_80099D9C */
                anim = 0x22B;
                if (20.0f <= F(obj, 0x44)) {
                    speed = F(obj, 0x3C) / 22.0f + 0.4f; /* D_eu_80099DA0 */
                }
            }
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 8;
            if (H(obj, 0x84) != 0xE7 && H(obj, 0x84) != 0x22B) {
                s32 list[2];
                list[0] = 0xE7;
                list[1] = 0x22B;
                SH(CTL, 0x1AA)++;
                func_1506B04C(obj, 9, list);
            }
        } else {
            anim = func_15064240(obj, 0xE4, 1, 0, held);
        }
        break;

    case 0x18: case 0x41: { /* 15068420 */
        s32 a = (kind == 0x18) ? 0xFB : 0x2C8;
        s32 b = (kind == 0x18) ? 0xFC : 0x2C9;
        if (kind != B(CTL, 0x78)) {
            anim = func_15064240(obj, a, 1, kind, held);
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (B(CTL, 0x197) != 0 && B(CTL, 0x11A) == 2) {
            B(obj, 0x8A) = 10;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 10;
            if ((*(u16 *)D_800CC6A4 & 0x2000) || (H(CTL, 0x88) & 0x2000)) {
                B(CTL, 0x1B4) |= 1;
                D_800CC2B0 = 1;
            }
            if (a == H(obj, 0x84)) {
                break;
            }
            if (!(*(u16 *)D_800CC6A4 & 0x2000) && (H(CTL, 0x88) & 0x2000) && H(CTL, 0x19E) == 0) {
                B(CTL, 0x1B4) |= 2;
                D_800CC2B0 = 1;
                blend = 0.0f;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                anim = 0x10C;
                H(CTL, 0x19E) = 0x32;
                break;
            }
            if (H(obj, 0x84) != 0x10C) {
                anim = 0x10A;
            }
            break;
        }
        B(obj, 0x8A) = 0x14;
        if ((held & 0x2000) && H(obj, 0x84) != a && H(CTL, 0x19E) == 0) {
            anim = b;
            blend = 0.0f;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            H(CTL, 0x19E) = 0x32;
        } else {
            anim = func_15064240(obj, 0xC6, 1, 0, held);
        }
        break;
    }

    case 0x11: /* 150685F4 */
        if (held & 0x4000) {
            W((u8 *)func_15083E90(7), 0x2E4) = 1;
        }
        break;

    case 0x25: case 0x2D: case 0x2E: /* 15068618 */
        B(CTL, 0x78) = kind;
        B(obj, 0x8A) = 0x14;
        break;

    case 0x28: /* 1506862C */
        if (recurse != 0) {
            B(CTL, 0x78) = 0;
        } else if (height <= 0.0f && (held & 0x4000) && kind != B(CTL, 0x78)) {
            B(CTL, 0x78) = kind;
        }
        break;

    case 0x3C: { /* 1506867C: special pad (func_1506045C: ctl +0x17 set), spin ctl +0x18 */
        u16 diff = D_800CC6A0 - H(obj, 0x7A);
        anim = 999;
        B(obj, 0x239) = 0x2F;
        if (B(obj, 0x13C) != 0) {
            s16 old = SH(CTL, 0x18);
            f32 mag;
            B(obj, 0x83) = 0xFF;
            B(obj, 0x89) = 0xFF;
            SH(CTL, 0x18) = (SH(CTL, 0x18) < 0) ? SH(CTL, 0x18) + 20 : SH(CTL, 0x18) - 20;
            if ((old ^ SH(CTL, 0x18)) & 0x8000) {
                SH(CTL, 0x18) = 0;
            }
            if (10.0f < F(obj, 0x44)) {
                s16 d = H(CTL, 0x4C) - H(CTL, 0x7E);
                if (d < 0x2000 && d >= -0x1FFF && (d > 0x100 || d < -0x100)) {
                    SH(CTL, 0x18) = (d & 0x8000) ? SH(CTL, 0x18) - 0x28 : SH(CTL, 0x18) + 0x28;
                    if (SH(CTL, 0x18) > 0x1000) SH(CTL, 0x18) = 0x1000;
                    if (SH(CTL, 0x18) < -0x1000) SH(CTL, 0x18) = -0x1000;
                }
            }
            {
                u16 yaw = H(obj, 0x7A) + SH(CTL, 0x18) * D_800CC264 / 100;
                H(obj, 0x7A) = yaw;
                H(obj, 0x76) = yaw;
            }
            if (SH(CTL, 0x18) > 0x200 || SH(CTL, 0x18) < -0x200) {
                u16 now = D_800CC6A0 - H(obj, 0x7A);
                s16 s = SH(CTL, 0x18);
                if (((diff < 0x1000 || diff > 0xF000) && now >= 0x1000 && now < 0x7000 && s < 0) ||
                    (diff > 0x7000 && now <= 0x7000 && s > 0)) {
                    D_800D1580 = 0xFF0105B6;
                    func_1506E5FC();
                }
            }
            H(CTL, 0x7E) = H(CTL, 0x4C);
            mag = fabsf((f32)SH(CTL, 0x18));
            anim = 0x288;
            if (200.0f < mag) anim = 0x286;
            if (2000.0f < mag) anim = 0x27E;
            blend = 16.0f;
            if (D_800BE9B4 != 0) {
                blend = 0.0f;
            }
            if (held & 0x4000) {
                u8 *o = (u8 *)func_15083E90(6);
                F(o, 0x3C) = 80.0f;
                F(o, 0x3C) = (2000.0f < mag) ? (mag + 1000.0f) / 36.0f : (mag + 2000.0f) / 80.0f;
                B(o, 0x104) = 0;
                B(o, 0x13D) = 0;
                W(o, 0x218) = 0;
                B(o, 0x232) = 2;
                B(obj, 0x13C) = 0;
                B(obj, 0x83) = 0;
                B(obj, 0x89) = 10;
            }
        } else if ((held & 0x4000) && height <= 0.0f && B(obj, 0x8A) == 0 && H(obj, 0x84) != 0x27D) {
            s32 a0 = H(obj, 0x84);
            if (B(obj, 0x89) == 0 || a0 < 0x27A || a0 >= 0x27E) {
                anim = 0x27A;
            } else if (B(obj, 0x103) != 0 || B(obj, 0x107) != 0) {
                anim = a0 + 1;
            }
            if (anim != 999) {
                B(obj, 0x107) = 0;
                B(obj, 0x83) = 0xFF;
                B(obj, 0x89) = 0xFF;
            }
        }
        break;
    }

    case 0x21: /* 15068A34: anims 0x120 / 0x129.. / 0x121 */
        if (recurse != 0 && B(obj, 0x65) != 0) {
            func_150836CC(obj, 0x58);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (!(height <= 0.0f)) {
            break;
        }
        if (kind != B(CTL, 0x78)) {
            anim = func_15064240(obj, 0x120, 1, kind, held);
            speed = 1.4f; /* D_80099DAC */
            break;
        }
        if (B(CTL, 0x11A) != 2) {
            break;
        }
        if (held & 0x2000) {
            anim = func_15064594((u8 *)obj, 0x129, 0x12A, 0x128);
            speed = 1.3f; /* D_eu_80099DA4 */
            B(obj, 0x89) = 0xFF;
        } else {
            anim = func_15064240(obj, 0x121, 1, 0, held);
            speed = 1.4f; /* D_eu_80099DA8 */
        }
        break;

    case 0x22: /* 15068B40: anims 0x15D / 0x15F / 0x15E */
        speed = 1.4f; /* D_80099DB0 */
        if (recurse != 0 && B(obj, 0x65) != 0) {
            func_150836CC(obj, 0x56);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (kind == B(CTL, 0x78) && height <= 0.0f) {
            if (B(CTL, 0x11A) != 2) {
                break;
            }
            if (held & 0x2000) {
                anim = func_15064594((u8 *)obj, 0x15F, 0x15F, 0x15F);
                speed = 1.3f; /* D_80099DB4 */
                B(obj, 0x89) = 0xFF;
            } else {
                anim = func_15064240(obj, 0x15E, 1, 0, held);
            }
            break;
        }
        anim = func_15064240(obj, 0x15D, 1, kind, held);
        break;

    case 0x24: /* 15068C3C: anims 0x152 / 0x155 / 0x154 / 0x156 / 0x157 */
        if (recurse != 0) {
            if (kind == B(CTL, 0x78)) {
                s32 end = 1;
                if ((s32)F(obj, 0x28) == 0 && B(CTL, 0x11A) == 2) {
                    anim = func_15064240(obj, 0x155, 1, 0, held | 0x4000);
                    if (anim != 999) {
                        end = 0;
                    }
                }
                if (end) {
                    func_150836CC(obj, 0x63);
                    B(CTL, 0x11A) = 0;
                    B(obj, 0x83) = 0;
                    B(obj, 0x89) = 0;
                }
            }
            break;
        }
        if (kind != B(CTL, 0x78)) {
            anim = func_15064240(obj, 0x152, 1, kind, held);
            break;
        }
        /* (the asm re-tests recurse here: always 0 on this path) */
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (B(CTL, 0x197) != 0 && B(CTL, 0x11A) == 2) {
            B(obj, 0x8A) = 10;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 10;
            if (H(CTL, 0x19E) == 0 && ((*(u16 *)D_800CC6A4 & 0x2000) || (H(CTL, 0x88) & 0x2000))) {
                B(CTL, 0x1B4) |= 1;
                D_800CC2B0 = 1;
            }
            if (H(obj, 0x84) == 0x152) {
                break;
            }
            if (!(*(u16 *)D_800CC6A4 & 0x2000) && (H(CTL, 0x88) & 0x2000) && H(obj, 0x84) == 0x157 &&
                H(CTL, 0x19E) == 0) {
                B(CTL, 0x1B4) |= 2;
                D_800CC2B0 = 1;
                blend = 0.0f;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                H(CTL, 0x19E) = 100;
                anim = 0x156;
                if (W(obj, 0x318) != 0) {
                    s32 m = W(obj, 0x184) & 0x1F;
                    if (m == 5 || m == 3 || m == 6 || m == 9) {
                        func_10010558((u32)func_150ADA20() % 3 + 0x2EB, obj, 0x7D00, 0x64, 0x78, 0x5A);
                    }
                }
                break;
            }
            if (H(obj, 0x84) != 0x156) {
                anim = 0x157;
            }
            break;
        }
        B(obj, 0x8A) = 0x14;
        if ((held & 0x2000) && H(obj, 0x84) != 0x152 && H(CTL, 0x19E) == 0) {
            blend = 0.0f;
            anim = 0x154;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            H(CTL, 0x19E) = 100;
        } else {
            anim = func_15064240(obj, 0x155, 1, 0, held);
        }
        break;

    case 0x3B: /* 15068FA8: anims 0x225 / 0x226 / 0x222 / 0x236 / 0x227 / 0x237 / 0x221 / 0x223 / 0x31B, item 0x89 */
        if (D_eu_800C3E78 != 0) {
            if (kind == B(CTL, 0x78)) {
                func_15083568(obj, 0x89, 1.0f, 0);
                B(CTL, 0x11A) = 2;
            } else {
                func_150836CC(obj, 0x89);
                B(CTL, 0x11A) = 0;
            }
        }
        if ((kind == B(CTL, 0x78) || B(CTL, 0x11A) != 0) && B(obj, 0xAD) != 0) {
            B(CTL, 0x78) = 0;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 0;
            func_150836CC(obj, 0x89);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (kind != B(CTL, 0x78)) {
            anim = func_15064240(obj, 0x225, 1, kind, held);
            break;
        }
        if (recurse != 0 && (B(obj, 0x65) != 0 || B(obj, 0x104) != 0 || B(obj, 0x13C) != 0)) {
            func_150836CC(obj, 0x89);
            B(CTL, 0x11A) = 0;
            B(CTL, 0x78) = 0;
            break;
        }
        if (recurse != 0) {
            anim = func_15064240(obj, 0x226, 1, 0, held | 0x4000);
            if (anim == 999) {
                func_150836CC(obj, 0x89);
                B(CTL, 0x11A) = 0;
                B(CTL, 0x78) = 0;
                B(obj, 0x83) = 0;
            }
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        B(obj, 0x8A) = 0x14;
        func_15063DE8((u8 *)obj, buttons, 0x2010);
        if (H(CTL, 0x19E) == 0 && ((D_800CC6B0 & 0x2000) || (H(CTL, 0x88) & 0x2000))) {
            if (B(CTL, 0x198) == 2) {
                B(CTL, 0x1B4) |= 4;
            } else {
                B(CTL, 0x1B4) |= 1;
            }
            D_800CC2B0 = 1;
        }
        /* (the asm re-tests recurse here: always 0 on this path) */
        if ((((D_800CC6B0 & 0x10) && !(D_800CC6B0 & 0x2000) && (H(CTL, 0x88) & 0x2000)) ||
             (!(D_800CC6B0 & 0x10) && (D_800CC6AC & 0x2000))) &&
            H(obj, 0x84) != 0x225 && H(obj, 0x84) != 0x222 && H(obj, 0x84) != 0x236 && H(obj, 0x84) != 0x227 &&
            H(obj, 0x84) != 0x237 && H(CTL, 0x19E) == 0) {
            if (*(u16 *)D_800CC6A4 & 0x10) {
                anim = (func_150ADA20() & 3) ? 0x227 : 0x237;
                B(CTL, 0x1B4) |= 2;
                D_800CC2B0 = 1;
            } else {
                anim = (func_150ADA20() & 3) ? 0x222 : 0x236;
            }
            blend = 0.0f;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            H(CTL, 0x19E) = 0x32;
            break;
        }
        if ((D_800CC6B0 & 0x10) && (D_800CC6B0 & 0x2000) && H(obj, 0x84) != 0x225) {
            B(obj, 0x89) = 0;
            B(obj, 0x8A) = 8;
            B(obj, 0x83) = 8;
            if (H(obj, 0x84) == 0x222 || H(obj, 0x84) == 0x236 || H(obj, 0x84) == 0x227 || H(obj, 0x84) == 0x237) {
                break;
            }
            if (1.0f <= F(obj, 0x44) || ((s8 *)CTL)[0x23] > 0) {
                anim = 0x223;
                if (20.0f <= F(obj, 0x44)) {
                    anim = 0x31B;
                    speed = F(obj, 0x3C) / 22.0f + 0.4f; /* D_80099DB8 */
                }
            } else {
                anim = 0x221;
            }
            break;
        }
        anim = func_15064240(obj, 0x226, 1, 0, held);
        break;

    case 0x12: /* 15069408: anims 0xC4 / 0xC6 / 0xC7 / 0x10A */
        if ((kind == B(CTL, 0x78) || B(CTL, 0x11A) != 0) && B(obj, 0xAD) != 0) {
            B(CTL, 0x78) = 0;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 0;
            B(CTL, 0x11A) = 0;
            break;
        }
        if (kind != B(CTL, 0x78)) {
            anim = func_15064240(obj, 0xC4, 1, kind, held);
            if (anim != 999) {
                F(obj, 0x3C) = 0.0f;
            }
            break;
        }
        F(obj, 0x3C) = 0.0f;
        if (recurse != 0 && B(obj, 0x65) != 0) {
            B(CTL, 0x11A) = 0;
            break;
        }
        B(obj, 0x8A) = 0x14;
        if ((*(u16 *)D_800CC6A4 & 0x2000) || (H(CTL, 0x88) & 0x2000)) {
            if (B(CTL, 0x198) == 2) {
                B(CTL, 0x1B4) |= 8;
            } else {
                B(CTL, 0x1B4) |= 1;
            }
            D_800CC2B0 = 1;
        }
        if (recurse != 0) {
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            anim = 0xC6;
            if ((s32)F(obj, 0x28) != 0) {
                B(CTL, 0x11A) = 0;
            }
            break;
        }
        if (!(*(u16 *)D_800CC6A4 & 0x2000) && (H(CTL, 0x88) & 0x2000) && H(obj, 0x84) != 0xC4 && H(CTL, 0x19E) == 0) {
            blend = 0.0f;
            anim = 0xC7;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            H(CTL, 0x19E) = 0x32;
            break;
        }
        if ((*(u16 *)D_800CC6A4 & 0x2000) && H(obj, 0x84) != 0xC4) {
            B(obj, 0x89) = 0;
            B(obj, 0x8A) = 8;
            B(obj, 0x83) = 8;
            if (H(obj, 0x84) != 0xC7) {
                anim = 0x10A;
            }
            break;
        }
        anim = func_15064240(obj, 0xC6, 1, 0, held);
        break;

    case 0x23: /* 15069620: anims 0x163 / 0x164 / 0x165 / 0x166 / 0x167 / 0x26E, shot count ctl +0x199 */
        if (kind != B(CTL, 0x78)) {
            anim = func_15064240(obj, 0x163, 1, kind, held);
            break;
        }
        if (recurse != 0 && B(obj, 0x65) != 0) {
            func_150836CC(obj, 0x16);
            B(CTL, 0x11A) = 0;
            break;
        }
        if (stunned != 0) {
            clearItem = 0;
            break;
        }
        if (B(CTL, 0x197) != 0 && B(CTL, 0x11A) == 2) {
            B(obj, 0x8A) = 10;
            B(obj, 0x89) = 0;
            B(obj, 0x83) = 10;
            if (H(CTL, 0x19E) == 0 && ((*(u16 *)D_800CC6A4 & 0x2000) || (H(CTL, 0x88) & 0x2000))) {
                B(CTL, 0x1B4) |= 1;
                D_800CC2B0 = 1;
            }
            if (H(obj, 0x84) == 0x163) {
                break;
            }
            if (B(CTL, 0x199) >= 6 || ((held & 0x8000) && H(obj, 0x84) != 0x26E)) {
                if (F(obj, 0x28) == 0.0f) {
                    B(obj, 0x89) = 0xFF;
                    B(obj, 0x83) = 0xFF;
                    H(CTL, 0x19E) = 0x96;
                    anim = 0x26E;
                    B(CTL, 0x199) = 0;
                }
                break;
            }
            if (!(*(u16 *)D_800CC6A4 & 0x2000) && (H(CTL, 0x88) & 0x2000) && H(obj, 0x84) == 0x165 &&
                H(CTL, 0x19E) == 0) {
                B(CTL, 0x1B4) |= 2;
                D_800CC2B0 = 1;
                blend = 0.0f;
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                B(CTL, 0x199)++;
                anim = 0x167;
                H(CTL, 0x19E) = 0x19;
                break;
            }
            if (H(obj, 0x84) != 0x167) {
                anim = 0x165;
            }
            break;
        }
        B(obj, 0x8A) = 0x14;
        if (H(obj, 0x84) != 0x163 &&
            (B(CTL, 0x199) >= 6 || ((held & 0x8000) && H(obj, 0x84) != 0x26E))) {
            if (F(obj, 0x28) == 0.0f) {
                B(obj, 0x89) = 0xFF;
                B(obj, 0x83) = 0xFF;
                H(CTL, 0x19E) = 0x96;
                anim = 0x26E;
                B(CTL, 0x199) = 0;
            }
            break;
        }
        if ((held & 0x2000) && H(obj, 0x84) != 0x163 && H(obj, 0x84) != 0x166 && H(CTL, 0x19E) == 0) {
            blend = 0.0f;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x199)++;
            anim = 0x166;
            H(CTL, 0x19E) = 0x19;
            break;
        }
        anim = func_15064240(obj, 0x164, 1, 0, held);
        if (anim == 0x163) {
            B(CTL, 0x199) = 0;
        }
        break;

    case 0x17: { /* 15069924: anim 0x8E, turn to the level point D_800D34B8[ctl +0x7A] (0x34 bytes) */
        s32 ok = 1;
        anim = 999;
        if (!(held & 0x4000) || !(height <= 0.0f)) {
            break;
        }
        if (B(CTL, 0x7A) != 0) {
            f32 d = func_15048A70(F(D_800D34B8 + B(CTL, 0x7A) * 0x34, 0x10), F(obj, 0x40));
            if (W(D_800D34B8 + B(CTL, 0x7A) * 0x34, 0x18) != 0 && (d < -90.0f || 90.0f < d)) {
                ok = 0;
            }
        }
        if (!ok) {
            break;
        }
        B(obj, 0x89) = 0xFF;
        B(obj, 0x83) = 0xFF;
        B(CTL, 0x78) = 0x17;
        anim = 0x8E;
        {
            /* IDO f32 -> u32: values <= -1 give 0xFFFFFFFF (kept explicit: the plain cast traps on wasm) */
            f32 a = F(D_800D34B8 + B(CTL, 0x7A) * 0x34, 0x10) * 182.04445f; /* D_80099DBC */
            u32 u = (a <= -1.0f) ? 0xFFFFFFFF : (u32)a;
            H(obj, 0x76) = u - 0x4000;
        }
        break;
    }

    case 0x1A: /* 15069ADC: anims 0x12C / 0x12E / 0x358 / 0x142 */
        done = 1;
        anim = 999;
        if (kind != B(CTL, 0x78)) {
            if (!(held & 0x4000) || !(height <= 0.0f)) {
                break;
            }
            B(obj, 0x89) = 0xFF;
            B(obj, 0x8A) = 0xFF;
            B(obj, 0x83) = 0xFF;
            F(obj, 0x3C) = 0.0f;
            anim = 0x12C;
            B(CTL, 0x78) = kind;
            func_15080C28(0);
            break;
        }
        if (stunned != 0) {
            func_15080FE8();
            B(CTL, 0x78) = 0;
            break;
        }
        if (func_150810F4() != 0) {
            if (D_800D1940 == 0x42) {
                B(CTL, 0x78) = 0;
                anim = 0x358;
                D_800D2E60[D_800D1940 >> 3] |= 1 << (D_800D1940 & 7);
            } else {
                anim = 0x12E;
            }
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            break;
        }
        if (H(obj, 0x84) == 0x12C || !(D_800BEB30[D_800C3E78] & 0x8000)) {
            break;
        }
        if ((D_800D1958[0] & 0x20) && func_151F2CDC() != 0) {
            break;
        }
        anim = 0x142;
        break;

    case 0x2A: /* 15069C3C: anim 0x26F, random shout through func_1507E7E4 */
        done = 1;
        anim = 999;
        if (kind != B(CTL, 0x78)) {
            if (!(height <= 0.0f) || B(obj, 0x110) != 0 || B(obj, 0x8A) != 0) {
                break;
            }
            B(obj, 0x89) = 0xFF;
            B(obj, 0x8A) = 0xFF;
            B(obj, 0x83) = 0xFF;
            F(obj, 0x3C) = 0.0f;
            B(CTL, 0x78) = kind;
            anim = 0x26F;
            B(obj, 0x276) = 6;
            H(obj, 0x282) = 100;
            H(obj, 0x278) = 0;
            B(obj, 0x284) = 0;
            func_15080C28(1);
            break;
        }
        if (stunned != 0) {
            func_15080FE8();
            B(CTL, 0x78) = 0;
            break;
        }
        if (func_150810F4() != 0) {
            B(CTL, 0x78) = 0;
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0;
            func_1507EE9C(obj);
            break;
        }
        {
            s32 shouts[2]; /* sp+0xB0: copy of D_800864A0 */
            shouts[0] = D_800864A0[0];
            shouts[1] = D_800864A0[1];
            H(obj, 0x282) = 100;
            if (((s8 *)obj)[0x284] == 0) {
                H(obj, 0x278) += D_800BE9E4;
                if ((u32)func_150ADA20() % 100 + 150 < H(obj, 0x278)) {
                    s32 r = func_150ADA20();
                    func_1507E7E4(obj, shouts[r & 1], 1, (u32)func_150ADA20() % 150 + 0x15E, 0);
                    H(obj, 0x278) = 0;
                    B(obj, 0x284) = 1;
                }
            } else if (B(obj, 0x70) == B(obj, 0x6F)) {
                B(obj, 0x284) = 0;
            }
        }
        B(obj, 0x89) = 10;
        B(obj, 0x8A) = 10;
        B(obj, 0x83) = 10;
        break;

    case 0x1B: { /* 15069E18: carry the other player (obj +0x65) */
        u8 *other = (u8 *)D_800CC2D0 + (B(obj, 0x65) - 1) * 0x32C; /* spAC */
        s32 grab = 0;  /* sp94 */
        s32 hold;      /* spA4 */
        s32 mode;      /* a1 */
        s32 grabAnim;  /* s3 */
        s32 carryAnim; /* s1 */
        s32 mode2;     /* a2 */
        B(CTL, 0x78) = 0x1B;
        B(obj, 0x8A) = 0x14;
        if (D_800BE616 == 0 || B(obj, 0x65) != 0) {
            clearItem = 0;
        }
        anim = 999;
        if (H(CTL, 0x19E) != 0) {
            break;
        }
        if (B(other, 4) == 0x23) {
            hold = 0x10; mode = 0xD; grabAnim = 0x15; carryAnim = 0xA; mode2 = 0xC;
        } else {
            hold = 0xB; mode = 4; grabAnim = 0xC; carryAnim = 1; mode2 = 0;
        }
        if (*(u16 *)D_800CC6A4 & 0x2000) {
            if (mode != B(other, 0x232)) {
                func_10010A3C((struct127 *)other);
                func_100109D0((struct127 *)other);
            }
            B(other, 0x232) = mode;
            W(other, 0x218) = 0;
            B(CTL, 0x199) = 1;
            if (carryAnim != H(other, 0x84) || (D_eu_800C3E78 != 0 && mode2 != 0)) {
                func_150FC438((struct127 *)other, obj, 0, carryAnim);
                func_10010A3C((struct127 *)other);
                if (B(obj, 4) == 0x80 && (func_150ADA20() & 3) == 0) {
                    u16 v = func_1000F568(0x57C, 6); /* voice id: the asm masks it to u16 */
                    func_1000FA64(v, POSARGS(obj), 0x7FFF, 1000, 0x1F4, (s32)func_1000EFB4, obj,
                                  (s32)D_80099A90, 0, 0);
                }
            }
            if (D_800BE9E4 < SH(CTL, 0x24)) {
                SH(CTL, 0x24) -= D_800BE9E4;
            } else {
                grab = grabAnim;
                func_100109D0((struct127 *)other);
            }
        } else if (D_eu_800C3E78 != 0 && mode2 != B(other, 0x232) && mode2 != 0) {
            B(other, 0x232) = mode2;
            W(other, 0x218) = 0;
        } else if (B(CTL, 0x199) == 1) {
            B(CTL, 0x199) = 0;
            if (func_1000FF90((s32)func_1000EC24, -1, -1) == -1) {
                func_1000FA64((u32)func_150ADA20() % 3 + 0x618, POSARGS(obj), 0x7D00, 0x1F4, 0xC8, (s32)func_1000EC24,
                              (void *)0x19, 0, 0x300, 0);
            }
        }
        if (held & 0x4000) {
            grab = hold;
            func_10010A3C((struct127 *)other);
            func_100109D0((struct127 *)other);
        }
        if (grab != 0) {
            SH(CTL, 0x24) = 0x1F4;
            H(CTL, 0x19E) = 0x7D;
            func_1000FA64((u32)func_150ADA20() % 3 + 0x618, POSARGS(obj), 0x7D00, 0x1F4, 0xC8, (s32)func_1000EC24,
                          (void *)0x19, 0, 0x300, 0);
            B(other, 0x232) = grab;
            W(other, 0x218) = 0;
        }
        break;
    }

    case 0x26: { /* 1506A27C: anims 0x175/0x176 (start) 0x16B/0x16C (end), item 0x2C / 0x64, state ctl +0x19B */
        s32 animStart, animEnd, sub, snd;
        if (B(obj, 4) == 0x75 || B(obj, 4) == 0xB1) {
            animStart = 0x176; animEnd = 0x16B; sub = 0x64; snd = 0x11;
        } else {
            animStart = 0x175; animEnd = 0x16C; sub = 0x2C; snd = 0x12;
        }
        if (stunned != 0) {
            if (kind != B(CTL, 0x78) && B(CTL, 0x19B) != 4) {
                break;
            }
            if (func_15031C4C(obj, sub, 0) != 0 || B(CTL, 0x19B) == 4) {
                func_150836CC(obj, sub);
                D_800D1580 = (snd & 0xFFFF) | 0x10000;
                func_15073FA0();
                if (B(CTL, 0x19A) != 0) {
                    B(CTL, 0x19A)--;
                }
            }
            B(CTL, 0x19B) = 0;
            B(CTL, 0x11A) = 0;
            break;
        }
        func_15063DE8((u8 *)obj, buttons, 0x10);
        if (B(CTL, 0x19B) == 1) {
            if (kind == B(CTL, 0x78)) {
                break;
            }
            B(CTL, 0x78) = kind;
            B(CTL, 0x11A) = 1;
            B(obj, 0x89) = 0x1E;
            B(obj, 0x8A) = 0x1E;
            B(obj, 0x83) = 0x1E;
            B(CTL, 0x19B) = 2;
            H(CTL, 0x19C) = 0xC8;
            anim = animStart;
            SH(CTL, 0x1AA)++;
        } else if (B(CTL, 0x19B) == 2) {
            if (!(D_800CC6B0 & 4) && !(H(obj, 0x2F8) & 0x10)) {
                B(CTL, 0x19B) = 3;
            }
            if (D_800BE9E4 < H(CTL, 0x19C)) {
                H(CTL, 0x19C) -= D_800BE9E4;
                break;
            }
            B(CTL, 0x19B) = 0;
            B(CTL, 0x78) = 0;
            B(obj, 0x125) = 0;
            func_15063F14(obj, 1);
        } else if (B(CTL, 0x19B) == 3) {
            if (!(height <= 0.0f) || H(obj, 0x84) == animStart) {
                break;
            }
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x19B) = 4;
            B(CTL, 0x78) = 0;
            B(CTL, 0x11A) = 3;
            anim = animEnd;
            if (B(CTL, 0x19A) != 0) {
                B(CTL, 0x19A)--;
            }
        }
        break;
    }

    case 0x3A: { /* 1506A4E4: throwable item 0x89 (0xBA in level 0x3F), anims 0x1F9 / 0x1FC, state ctl +0x19B */
        s32 item = (D_800BE9F0 == 0x3F) ? 0xBA : 0x89; /* sp7C */
        u8 *o;                                          /* sp80 */
        if (stunned != 0) {
            if (kind != B(CTL, 0x78)) {
                break;
            }
            o = (u8 *)func_1506401C(obj, item);
            if (o != NULL) {
                B(o, 0x65) = 0;
                F(o, 0x24) = 4.0f;
                F(o, 0x20) = 0.0f;
                F(o, 0x3C) = 0.0f;
            }
            B(CTL, 0x19B) = 0;
            B(CTL, 0x78) = 0;
            B(CTL, 0x11A) = 0;
            break;
        }
        func_15063DE8((u8 *)obj, buttons, 0x10);
        if (B(CTL, 0x19B) == 5) {
            if (kind == B(CTL, 0x78)) {
                break;
            }
            o = (u8 *)func_15083568(obj, (item == 0x89) ? 0x86 : 0x9F, 1.0f, 0);
            if (o == NULL) {
                B(CTL, 0x19B) = 0;
                break;
            }
            B(CTL, 0x78) = kind;
            B(CTL, 0x11A) = 1;
            anim = 0x1F9;
            B(obj, 0x89) = 0x1E;
            B(obj, 0x8A) = 0xFF;
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x19B) = 6;
            B(o, 0x125) = 0xFF;
            func_15062BDC((struct127 *)o, 1.0f, 1.0f);
            W(o, 0x2E4) = 200;
            W(o, 0x2E8) = 200;
            B(o, 0x124) = D_800C3E78 + 1;
            W(o, 0xF8) = 0x401807;
            func_1505E650((struct127 *)o, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0);
            func_1514FAD8((s32)o);
        } else if (B(CTL, 0x19B) == 6) {
            if (!(D_800CC6B0 & 4)) {
                B(CTL, 0x19B) = 7;
            }
        } else if (B(CTL, 0x19B) == 7) {
            if (!(height <= 0.0f) || H(obj, 0x84) == 0x1F9) {
                break;
            }
            B(obj, 0x89) = 0xFF;
            B(obj, 0x83) = 0xFF;
            B(CTL, 0x19B) = 0;
            B(CTL, 0x78) = 0;
            B(CTL, 0x11A) = 0;
            anim = 0x1FC;
            if (B(CTL, 0x19A) != 0) {
                B(CTL, 0x19A)--;
            }
            SH(CTL, 0x1AA)++;
            o = (u8 *)func_1506401C(obj, item);
            if (o != NULL) {
                f32 x, y, z; /* sp74, sp70, sp6C */
                f32 fwd = (f32)(200 - W(o, 0x2E4)) * 210.0f / 200.0f + 40.0f;
                s16 ang = 0x1555;
                B(o, 0x65) = 0;
                if (B(CTL, 0x198) != 0) {
                    ang = (30.0f - F(CTL, 0x170)) * 182.04445f; /* D_80099DC0 */
                }
                func_1505A184(ang, fwd, 0.0f, &x, &y, &z);
                F(o, 0x20) = -y;
                F(o, 0x24) = 4.0f;
                F(o, 0x3C) = x;
                {
                    u16 yaw = H(obj, 0x7A) - SH(CTL, 0x12);
                    H(o, 0x7A) = yaw;
                    H(o, 0x76) = yaw;
                }
            }
        }
        break;
    }

    case 0x3E: /* 1506A840: timer ctl +0x12C -> obj +0xAA */
        if (B(obj, 0x128) != 0) {
            break;
        }
        if (B(obj, 0x83) == 0) {
            B(obj, 0x83) = 1;
        }
        if (H(CTL, 0x12C) < D_800BE9E4) {
            B(obj, 0xAA) = 0x4B;
            H(CTL, 0x12C) = 0;
        } else {
            H(CTL, 0x12C) -= D_800BE9E4;
            B(obj, 0xAA) = 0x96;
        }
        break;

    default:
        break;
    }
    /* common tail (1506A89C) */
    if (recurse != 0 || stunned != 0) {
        H(CTL, 0x72) = 0;
        if (stunned != 0) {
            done = 1;
            anim = 0;
            if (clearItem != 0) {
                B(CTL, 0x78) = 0;
            }
        } else {
            B(CTL, 0x75) = 0;
            B(CTL, 0x78) = 0;
            if (B(CTL, 0x11A) != 3) {
                B(CTL, 0x11A) = 0;
            }
        }
    }
    if (anim != 0 && anim != 999 && noAnim == 0) {
        func_1505E650(obj, anim, speed, blend, f148, 0.0f, 0);
    }
    if (setFlag58 != 0) {
        B(CTL, 0x58) = 1;
    }
    if (sound != 0) {
        func_15060A30(sound, obj);
    }
    return done ? 1000 : anim;
}
