s32 func_1516284C(void *, s32 *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
typedef struct {
    f32 f0;    /* spawn record +0x08 */
    f32 f4;    /* spawn record +0x0C */
    u8 b8;     /* sound / emitter parameters for func_1516284C */
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 padD[3];
    void *extra; /* 0x2C bytes copied behind the record (+0x80) */
} Kind9940;
extern Kind9940 D_8008FD4C[];
// kind_effect_spawn: spawns effect kind `kind` (< 9, table D_8008FD4C, 0x14 bytes each) through func_151A8B20 (life
// `life`, -1 = untimed 300) at `pos` (f32[3]) or, without pos, attached to `owner` (s16 position at +0); the
// 0x2C-byte kind data goes behind the record (+0x80), with flag bits 0x08 / 0x10 of `flags` as its +0x28 bits 1 / 2.
// flags bit 1 marks the record (bit 4), bit 2 (bit 8); bit 4 also starts the kind's sound / emitter
// (func_1516284C) at pos or the owner position.
void func_151A9940(u8 flags, u8 kind, void *owner, s32 pos, f32 arg4, f32 arg5, s16 life, u8 arg7, s32 arg8) {
    struct {
        u8 flags;
        u8 pad1[3];
        void *owner;
        f32 f8;
        f32 fC;
        f32 pos[3];
        f32 f1C;
        f32 f20;
        s8 b24;
        s8 b25;
        s8 b26;
        u8 pad27;
    } spawn;
    struct {
        u8 flags;
        u8 b1;
        s16 life;
        u8 b4;
        u8 pad5[3];
    } snd;
    s32 at[3];
    Kind9940 *k;
    u8 *rec;
    f32 *p = (f32 *)pos;

    if (kind >= 9) {
        return;
    }
    k = &D_8008FD4C[kind];
    spawn.flags = ((flags & 2) ? 8 : 0) | 1 | ((owner != NULL) ? 2 : 0) | ((flags & 1) ? 4 : 0);
    spawn.owner = owner;
    spawn.f8 = k->f0;
    spawn.fC = k->f4;
    if (p != NULL) {
        spawn.pos[0] = p[0];
        spawn.pos[1] = p[1];
        spawn.pos[2] = p[2];
    } else {
        spawn.pos[0] = 0.0f;
        spawn.pos[1] = 0.0f;
        spawn.pos[2] = 0.0f;
    }
    spawn.b24 = 2;
    spawn.b25 = -1;
    spawn.b26 = 1;
    spawn.f1C = arg4;
    spawn.f20 = arg5;
    rec = (u8 *)func_151A8B20(&spawn, life, 0x2C, arg7, arg8);
    if (rec != NULL) {
        memcpy(rec + 0x80, k->extra, 0x2C);
        if (flags & 8) {
            rec[0x80 + 0x28] |= 1;
        }
        if (flags & 0x10) {
            rec[0x80 + 0x28] |= 2;
        }
    }
    if (flags & 4) {
        snd.flags = ((life == -1) ? 0 : 1) | 2;
        snd.b1 = 2;
        snd.life = (life == -1) ? 300 : life;
        snd.b4 = k->bB;
        if (p != NULL) {
            at[0] = p[0];
            at[1] = p[1];
            at[2] = p[2];
        } else {
            at[0] = ((s16 *)owner)[0];
            at[1] = ((s16 *)owner)[1];
            at[2] = ((s16 *)owner)[2];
        }
        func_1516284C(&snd, at, k->b8, k->b9, k->bA, 0xFF, 0, 0, k->bC, 0xFF, 1);
    }
}
