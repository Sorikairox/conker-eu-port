/* P220: readable C for func_151C0698 (game_eu_1EDA00, 669 words; analysis P213.md section 3). */
void func_151C1D48(u8 *arg0, u8 *arg1);
f32 func_15144AA8(s32 arg0);
s32 func_151D611C(u8 *, s32 *, u8 *, s8, s32);
s32 func_151C1F1C(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
void func_15145974(f32 *, f32 *, f32 *);
s32 func_15132FBC(f32 *, s32, s32, s32, s32, s32);
void *memcpy(void *, const void *, s32);
s32 func_151B8EB8(u8 *obj);
u8 *func_151B89B0(u8 *arg0);
s32 func_151B8C18(u8 *arg0, u8 arg1, s32 arg2);
u16 func_1000FA64(u16, s16, s16, s16, s32, u16, s16, s32, void *, s32, s32, s32);
s32 func_151C16BC(u8 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6);
void func_15145EA4(f32 **, f32 **, void *, s32);
s32 func_151030B8(struct127 *, u8, u8 *, s32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
void func_151037D4(s16, u8, f32, u8 *, u8, u8, s32);
void func_151C1E10(u8 *, u8, s32);
f32 func_150ADA68(void);
s32 func_150ADA20(void);
f32 sinf(f32);
f32 cosf(f32);
extern f32 D_800AAD10[3]; /* muzzle flash points in the gun model's space: {3, 125, 35} */
extern f32 D_800AAD1C[3]; /* {6, -50, 35} */
extern f32 D_800AAD28[3]; /* {3, 200, 35} */

#define B(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define SH(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))

// projectile_fire: fires a bullet from obj (aimed at target's / obj's aim point, or along obj's facing): finds the
// muzzle position, traces the shot (func_151D611C + func_151C1F1C), spawns the bullet particle (func_15132FBC, kind 3)
// with a 0xD0-byte payload at particle +0x170 (path state, owner, the arg2 record, sound / smoke / trail handles), then
// shows the muzzle flash on obj's gun model. arg3 is stored at payload +0x92; arg4 / arg5 are the usual layer args.
// Returns 0 (the asm returns a callee's leftover v0; the callers ignore it).
s32 func_151C0698(struct127 *obj, struct127 *target, s32 *arg2, u8 arg3, u8 arg4, s32 arg5) {
    f32 pos[3];        /* sp260: muzzle */
    f32 aim[3];        /* sp248: aim point (aimer's ctl +0x13C) */
    f32 aimDir[3];     /* sp23C: aimer's ctl +0x130 */
    f32 dir[3];        /* sp254: facing direction (no aimer) */
    f32 unused[5];     /* sp218: func_15145740's second output */
    s32 head[0x19];    /* sp2A4: 0x64 bytes of path state from func_151C1F1C */
    s32 hit[9];        /* sp270 */
    f32 hitPos[3];     /* sp294 */
    f32 hitDist = 0.0f; /* sp2A0 */
    s32 payload[0x34]; /* sp148: 0xD0 bytes copied to the particle at +0x170 */
    s32 spec[0x1F];    /* spCC: 0x7C-byte spawn spec for func_15132FBC */
    u8 *ctl;
    struct127 *aimer;
    s32 aiming;
    s32 trace;
    u8 *particle;

    if (D_800BE616 != 0) {
        if (W(obj, 0x1D4) != 0) {
            func_151C1D48((u8 *)obj, (u8 *)pos);
        } else {
            pos[0] = F(obj, 0x14);
            pos[1] = F(obj, 0x18) + 65.0f;
            pos[2] = F(obj, 0x1C);
        }
    } else {
        u8 *held = (u8 *)W(obj, 0x318);
        f32 *hand;
        ctl = (u8 *)W(obj, 0x31C);
        hand = (f32 *)(ctl + 0x13C);
        if (held != NULL && B(obj, 0x65) != 0) {
            pos[0] = hand[0];
            pos[1] = hand[1] + -13.0f;
            pos[2] = hand[2];
        } else if (held != NULL && B(ctl, 0x197) != 0) {
            f32 a = func_15144AA8(B(held, 0x23D)) * 0.017453292f; /* D_800AAD7C */
            pos[0] = cosf(a) * 25.0f + hand[0];
            pos[1] = hand[1];
            pos[2] = hand[2] - sinf(a) * 25.0f;
        } else if (W(obj, 0x1D4) != 0) {
            func_151C1D48((u8 *)obj, (u8 *)pos);
        } else {
            pos[0] = F(obj, 0x14);
            pos[1] = F(obj, 0x18) + 65.0f;
            pos[2] = F(obj, 0x1C);
        }
    }

    ctl = (u8 *)W(obj, 0x31C);
    if ((ctl != NULL && B(ctl, 0x197) != 0) || target != NULL) {
        aimer = (target != NULL) ? target : obj;
        aiming = 1;
        ctl = (u8 *)W(aimer, 0x31C);
        W(aim, 0) = W(ctl, 0x13C);
        W(aim, 4) = W(ctl, 0x140);
        W(aim, 8) = W(ctl, 0x144);
        aimDir[0] = F(ctl, 0x130);
        aimDir[1] = F(ctl, 0x134);
        aimDir[2] = F(ctl, 0x138);
    } else {
        func_15145740(obj, (s32)dir, (s32)unused, 0, 0.0f);
        dir[0] *= 0.001f; /* D_800AAD80 */
        dir[1] *= 0.001f;
        dir[2] *= 0.001f;
        aiming = 0;
    }

    if (D_800BE9F0 == 0x24) {
        trace = 0;
    } else {
        trace = func_151D611C(aiming ? (u8 *)aim : (u8 *)pos, aiming ? (s32 *)aimDir : (s32 *)dir, (u8 *)obj, 3,
                              (s32)arg2);
    }
    if (func_151C1F1C((u8 *)head, (u8 *)pos, aiming ? NULL : (u8 *)dir, aiming ? (u8 *)aim : NULL,
                      aiming ? (u8 *)aimDir : NULL, (s32)obj, (s32)arg2, (s32)hitPos, (s32)&hitDist, (s32)hit,
                      trace) == 0) {
        return 0;
    }

    /* payload (sp148) */
    {
        s32 i;
        for (i = 0; i < 0x19; i++) {
            payload[i] = head[i];
        }
    }
    W(payload, 0xCC) = trace; /* the func_151D611C hit (func_151C1730 passes it to func_15081A90) */
    W(payload, 0x80) = 0; /* sound */
    W(payload, 0x84) = 0; /* smoke */
    /* spawn spec (spCC) */
    F(spec, 0x00) = 1.0f;
    F(spec, 0x04) = 1.0f;
    F(spec, 0x08) = 0.047000002f; /* D_800AAD84 (0x3D408313) */
    F(spec, 0x0C) = 0.047000002f;
    F(spec, 0x10) = 0.0f;
    F(spec, 0x14) = 0.0f;
    F(spec, 0x18) = 0.0f;
    F(spec, 0x1C) = 1.0f;
    F(spec, 0x20) = 1.0f;
    F(spec, 0x24) = 1.0f;
    W(spec, 0x28) = W(pos, 0);
    W(spec, 0x2C) = W(pos, 4);
    W(spec, 0x30) = W(pos, 8);
    F(spec, 0x4C) = 0.0f;
    W(spec, 0x50) = 0x500920;
    SH(spec, 0x54) = 0x12C;
    SH(spec, 0x56) = 0x2F;
    B(spec, 0x58) = 1;
    W(payload, 0x6C) = (s32)obj;
    W(payload, 0x70) = arg2[0];
    W(payload, 0x74) = arg2[1];
    W(payload, 0x78) = arg2[2];
    W(payload, 0x7C) = arg2[3];
    F(payload, 0x94) = hitDist * 0.005f; /* D_800AAD88 */
    W(payload, 0x98) = W(hitPos, 0);
    W(payload, 0x9C) = W(hitPos, 4);
    W(payload, 0xA0) = W(hitPos, 8);
    B(payload, 0xC8) = (hitDist == 0.0f) ? 0 : 1;
    {
        s32 i;
        for (i = 0; i < 9; i++) {
            W(payload, 0xA4 + i * 4) = hit[i];
        }
    }
    F(payload, 0x68) = 200.0f; /* speed */
    F(spec, 0x34) = F(payload, 0x38) * 200.0f;
    F(spec, 0x38) = F(payload, 0x3C) * 200.0f;
    F(spec, 0x3C) = F(payload, 0x40) * 200.0f;
    func_15145974((f32 *)((u8 *)spec + 0x34), (f32 *)((u8 *)spec + 0x14), (f32 *)((u8 *)spec + 0x10));
    F(spec, 0x18) = 0.0f;
    F(payload, 0x64) = F(payload, 0x04) * 0.005f; /* D_800AAD8C */
    W(spec, 0x5C) = 0;
    B(spec, 0x60) = 0xFF;
    B(spec, 0x61) = 0xA;
    B(spec, 0x62) = 0;
    B(spec, 0x63) = 0;
    B(spec, 0x64) = 0;
    B(spec, 0x65) = 0;
    B(spec, 0x66) = 0;
    B(spec, 0x67) = 0;
    B(spec, 0x68) = 2;
    B(spec, 0x6A) = 2;
    W(spec, 0x6C) = 0;
    B(spec, 0x70) = 0;
    SH(spec, 0x72) = 1;
    SH(spec, 0x74) = 0xFF;
    F(spec, 0x40) = 0.0f;
    F(spec, 0x44) = 0.0f;
    F(spec, 0x48) = 0.0f;
    B(payload, 0x92) = arg3;

    particle = (u8 *)func_15132FBC((f32 *)spec, 3, 0xFF, 0xD0, arg4, arg5);
    if (particle != NULL) {
        u8 *p = particle + 0x170;
        s32 hdr[2];     /* spBC: 8-byte particle header */
        s32 hpos[3];    /* spB0 */
        s32 r;
        memcpy(p, payload, 0xD0);
        hpos[0] = (s32)pos[0];
        hpos[1] = (s32)pos[1];
        hpos[2] = (s32)pos[2];
        B(hdr, 0) = 2;
        B(hdr, 1) = 0xFF;
        SH(hdr, 2) = 0x12C;
        B(hdr, 4) = 0;
        W(p, 0x80) = (s32)func_151602C0((Header *)hdr, (Header2 *)hpos, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg4, arg5);
        W(p, 0x84) = func_151B8EB8(particle);
        r = func_150ADA20();
        H(p, 0x90) = func_1000FA64((u32)r % 3 + 0x2EE, (s16)(s32)pos[0], (s16)(s32)pos[1], (s16)(s32)pos[2], 0x7530,
                                   0x3E8, 0x1F4, (s32)func_151C16BC, particle, 0, 4, 0);
        W(p, 0x88) = (s32)func_151B89B0(particle);
        if (D_80082FA0 < 2 && D_8008FD8C < 4) {
            W(p, 0x8C) = func_151B8C18(particle, arg4, arg5);
        } else {
            W(p, 0x8C) = 0;
        }
    } else {
        /* the payload's handles are still 0 here: never taken */
        if (W(payload, 0x80) != 0) {
            func_1516972C((struct102 *)W(payload, 0x80));
        }
        if (W(payload, 0x84) != 0) {
            func_1516972C((struct102 *)W(payload, 0x84));
        }
    }

    /* muzzle flash on the gun model (obj +0x1D4, matrix at +0x240) */
    if (W(obj, 0x1D4) == 0 || (B(obj, 0x74) & 0xF) == 0xF || B(obj, 4) == 0x77 || B(obj, 4) == 0x28) {
        return 0;
    }
    {
        f32 c1[3], c2[3], c3[3]; /* spA4, sp98, sp8C */
        f32 size[2];             /* sp84 */
        f32 w1[3], w2[3];        /* sp78, sp6C: c1 / c2 in world space */
        f32 *in[2];              /* sp64 */
        f32 *out[2];             /* sp5C */
        s32 r1, r2;
        f32 rf;
        c1[0] = D_800AAD10[0]; c1[1] = D_800AAD10[1]; c1[2] = D_800AAD10[2];
        c2[0] = D_800AAD1C[0]; c2[1] = D_800AAD1C[1]; c2[2] = D_800AAD1C[2];
        c3[0] = D_800AAD28[0]; c3[1] = D_800AAD28[1]; c3[2] = D_800AAD28[2];
        size[0] = func_150ADA68() * 10.0f + 25.0f;
        size[1] = func_150ADA68() * 1.0090001f + 2.013f; /* D_800AAD90 (0x3F8126EA), D_800AAD94 */
        in[0] = c1;
        in[1] = c2;
        out[0] = w1;
        out[1] = w2;
        func_15145EA4(in, out, (u8 *)W(obj, 0x1D4) + 0x240, 2);
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        rf = func_150ADA68();
        func_151030B8(obj, 9, (u8 *)c1, (s32 *)c3, size, (u32)r1 % 3 + 8, (u32)r2 % 0x38 + 0xC8,
                      rf * 204.0f + 601.0f /* D_800AAD98 */, w1, 0xFF, 0, -1, arg4, arg5);
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        rf = func_150ADA68();
        func_151037D4((u32)r1 % 3 + 8, (u32)r2 % 0x38 + 0xC8, rf * 204.0f + 601.0f /* D_800AAD9C */, (u8 *)w2, 0xFF,
                      arg4, arg5);
        func_151C1E10((u8 *)w2, arg4, arg5);
    }
    return 0;
}
