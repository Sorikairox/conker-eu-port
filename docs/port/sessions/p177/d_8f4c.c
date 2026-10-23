void func_150E856C(f32, u8, s32 *, f32 *, s32, s32, s32, s32, s32, s32, u8, s32);
void func_1515016C(u8 *arg0, u8 arg1, s32 arg2);
u8 *func_1516547C(u8 kind, u8 view, u8 *data, u8 arg3, s32 arg4);
s32 func_1505D024(struct127 *obj, s32 flags, u16 val, s32 arg3);
s32 func_1000EC24();
extern s32 D_800AB010[]; /* hit-sound flags by beam piece kind: 0x17, 0x18 */

// beam_hit_effects: the effects when the beam `rec` is broken (by obj, from the 0x20 / 0x3A messages of
/* func_151C8C5C; obj NULL for the scripted break). At each end (+0x34 with the surface record +0x16A and the
 * direction +0x4C; +0x40 with +0x17C and the reversed direction): a spark spray (func_1515016C, the block below),
 * a flash (func_151602C0 kind 3) and a scorch mark (func_150E856C). With obj: the screen effect preset 2 for obj's
 * view (func_1516547C), a rumble (func_151D8E18) and obj's hit reaction (func_1505D024, flags D_800AB010 by the
 * piece kind at +0x1A4). Then the two sounds (0x2F5 at end A, 0x2F6 at end B) and func_1516972C(rec).
 * (The mark positions are the end points: the asm saves v0 = rec + 0x34 / + 0x40 in the delay slot of the
 * func_1515016C calls, before the call.) */
void func_151C8F4C(u8 *obj, u8 *rec) {
    struct {
        f32 dir[3];      /* 0x00 */
        u8 hit[0x12];    /* 0x0C surface record */
        u8 pad1E[2];
        f32 range;       /* 0x20 */
        s32 countBase;   /* 0x24 spray parameters (func_1514FE68) */
        s32 countExtra;  /* 0x28 */
        f32 pos[3];      /* 0x2C */
        f32 speedBase;   /* 0x38 */
        f32 speedRange;  /* 0x3C */
        f32 sizeBase;    /* 0x40 */
        f32 sizeRange;   /* 0x44 */
        f32 size2Base;   /* 0x48 */
        f32 size2Range;  /* 0x4C */
        s32 lifeBase;    /* 0x50 */
        s32 lifeExtra;   /* 0x54 */
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s16 u6A;
        s16 u6C;
        s16 u6E;
        s16 u70;
        s16 u72;
        s8 u74;
    } spray;
    struct {
        u8 kind;
        s8 u1;
        s16 size;
        u8 u4;
    } flash;
    s32 at[3];
    structEU_151D8E18 rumble;
    u8 *beam;
    s32 i;
    f32 r;

    spray.range = 491.0f;
    spray.countBase = 5;
    spray.countExtra = 3;
    spray.speedBase = 0.0605f;
    spray.speedRange = 0.0523f;
    spray.sizeBase = 30.0f;
    spray.sizeRange = 83.0f;
    spray.size2Base = 211.0f;
    spray.size2Range = 150.0f;
    spray.lifeBase = 5;
    spray.lifeExtra = 4;
    spray.u58 = 21.0f;
    spray.u5C = 0.698f;
    spray.u60 = -0.44500002f;
    spray.u64 = 0.441f;
    spray.u68 = 0x12;
    spray.u6A = 9;
    spray.u6C = 100;
    spray.u6E = 100;
    spray.u70 = 12;
    spray.u72 = 15;
    spray.u74 = 0;

    spray.pos[0] = *(f32 *)(rec + 0x34);
    spray.pos[1] = *(f32 *)(rec + 0x38);
    spray.pos[2] = *(f32 *)(rec + 0x3C);
    spray.dir[0] = *(f32 *)(rec + 0x4C);
    spray.dir[1] = *(f32 *)(rec + 0x50);
    spray.dir[2] = *(f32 *)(rec + 0x54);
    for (i = 0; i < 0x12; i++) {
        spray.hit[i] = rec[0x16A + i];
    }
    func_1515016C((u8 *)&spray, rec[0xC], rec[1]);

    beam = rec + 0x110;
    spray.pos[0] = *(f32 *)(rec + 0x40);
    spray.pos[1] = *(f32 *)(rec + 0x44);
    spray.pos[2] = *(f32 *)(rec + 0x48);
    spray.dir[0] = -*(f32 *)(rec + 0x4C);
    spray.dir[1] = -*(f32 *)(rec + 0x50);
    spray.dir[2] = -*(f32 *)(rec + 0x54);
    for (i = 0; i < 0x12; i++) {
        spray.hit[i] = beam[0x6C + i];
    }
    func_1515016C((u8 *)&spray, rec[0xC], rec[1]);

    at[0] = *(f32 *)(rec + 0x34);
    at[1] = *(f32 *)(rec + 0x38);
    at[2] = *(f32 *)(rec + 0x3C);
    flash.kind = 3;
    flash.u1 = -1;
    flash.size = (func_150ADA20() % 9U) + 0x11;
    flash.u4 = 0;
    func_151602C0((Header *)&flash, (Header2 *)at, (func_150ADA20() % 9U) + 5, 0xFF, 0x59, 0, 0xFF, 0, 0, rec[0xC],
                  rec[1]);
    at[0] = *(f32 *)(rec + 0x40);
    at[1] = *(f32 *)(rec + 0x44);
    at[2] = *(f32 *)(rec + 0x48);
    func_151602C0((Header *)&flash, (Header2 *)at, (func_150ADA20() % 9U) + 5, 0xFF, 0x59, 0, 0xFF, 0, 0, rec[0xC],
                  rec[1]);

    r = func_150ADA68();
    func_150E856C(r * 101.0f + 55.0f, (func_150ADA20() % 66U) + 0xBE, (s32 *)(beam + 0x5A), (f32 *)(rec + 0x34), -1,
                  1, 1, 0, 0, 0, rec[0xC], 0);
    r = func_150ADA68();
    func_150E856C(r * 101.0f + 55.0f, (func_150ADA20() % 66U) + 0xBE, (s32 *)(beam + 0x6C), (f32 *)(rec + 0x40), -1,
                  1, 1, 0, 0, 0, rec[0xC], 0);

    if (obj != NULL) {
        func_1516547C(2, (*(u8 **)(obj + 0x318))[0x23D], NULL, rec[0xC], rec[1]);
        rumble.unk0 = 1;
        rumble.unk2 = 0x28;
        rumble.unk5 = 1;
        rumble.unk4 = 8;
        rumble.unk6 = -1;
        func_151D8E18(&rumble, 0, 0xFF, 0);
    }
    if (obj != NULL) {
        func_1505D024((struct127 *)obj, D_800AB010[beam[0x94]], 0, -1);
    }
    func_10010F88(0x2F5, 0x7FFF, func_150ADA20() % 500U, 0, 0, *(f32 *)(rec + 0x34), *(f32 *)(rec + 0x38),
                  *(f32 *)(rec + 0x3C), 0x7D0, 0x898);
    func_1000FA64(0x2F6, *(f32 *)(rec + 0x40), *(f32 *)(rec + 0x44), *(f32 *)(rec + 0x48), 0x7FFF, 0x898, 0x7D0,
                  (s32)func_1000EC24, (void *)5, 0, 0, func_150ADA20() % 500U);
    func_1516972C((struct102 *)rec);
}
