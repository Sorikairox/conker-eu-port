s32 func_1504715C(s32 *, struct127 *);
s32 func_1504715C(s32 *, struct127 *);
s32 func_15046F70(f32 *, s32, f32, s32 *);
f32 func_150ADA68(void);
s32 func_150ADA20(void);
void func_150E856C(f32, u8, s32 *, f32 *, s32, s32, s32, s32, s32, s32, u8, s32);
void func_151D5404(struct17 *, f32, f32, f32, s16, s16, s32, s32);
void func_151D58E4(struct17 *, f32, f32, f32, s16, s32, s32);
s32 func_151D5AC4(struct17 *, u8, s32);
void func_151D45A4(struct17 *, u8, s32);
void func_150E892C(struct17 *, s16, u8, s32);
s32 func_15154728(f32 *, f32, f32, f32, f32, s32, s32);
s32 func_15136C3C(struct127 *, s32, s32, s32, s32, s32, s32, s32);
void func_10010F88(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
void func_151CA070(struct127 *arg0, u8 arg1, s32 arg2);

// object_explode: the big explosion at an object (135 units above its position +0x14/+0x18/+0x1C). On the ground
// (+0x2D8 == 0) a scorch mark (func_150E856C) where a ray 200 units down hits a floor with flag 1, and the debris
// burst func_15136C3C; then the blast effects func_151D5404 / func_151D58E4 / func_151D5AC4 / func_151D45A4, the
// sparks func_150E892C (at the scorch point when there is one), the flash func_15154728, the sound 0x60D, and in
// the air the extra burst func_151CA070. Nothing for a NULL object.
void func_151C9740(struct127 *obj, u8 arg1, s32 arg2) {
    s32 ground[9];  /* floor query (func_1504715C / func_15046F70): f32 height at +0, flags byte +0x1C */
    struct17 probe;
    u8 inAir;
    u8 scorched;
    struct17 mark;
    struct17 pos;
    f32 r;
    u32 a;
    u32 b;

    if (obj == NULL) {
        return;
    }
    pos.unk0 = *(f32 *) ((u8 *) obj + 0x14);
    pos.unk4 = *(f32 *) ((u8 *) obj + 0x18) + 135.0f;
    pos.unk8 = *(f32 *) ((u8 *) obj + 0x1C);
    scorched = 0;
    inAir = (*(f32 *) ((u8 *) obj + 0x2D8) != 0.0f) ? 1 : 0;
    if (!inAir) {
        probe = pos;
        func_1504715C(ground, obj);
        if (func_15046F70((f32 *) &probe, 0, pos.unk4 - 200.0f, ground) != 0 && (((u8 *) ground)[0x1C] & 1)) {
            mark.unk0 = probe.unk0;
            mark.unk4 = *(f32 *) &ground[0];
            mark.unk8 = probe.unk8;
            scorched = 1;
            r = func_150ADA68();
            a = func_150ADA20();
            b = func_150ADA20();
            func_150E856C(r * 125.0f + 204.0f, a % 101 + 155, &ground[1], (f32 *) &mark, b % 302 + 500, 0, 1, 0, 0,
                          0, arg1, 0);
        }
    }
    func_151D5404(&pos, 506.0f, 1013.0f, 0.000987166888f, 15, 20, arg1, arg2);
    func_151D58E4(&pos, 506.0f, 1013.0f, 0.000987166888f, 5, arg1, arg2);
    func_151D5AC4(&pos, arg1, arg2);
    func_151D45A4(&pos, arg1, arg2);
    func_150E892C(scorched ? &mark : &pos, (u32) func_150ADA20() % 62 + 120, arg1, arg2);
    r = func_150ADA68();
    func_15154728((f32 *) &pos, r + r + 8.0f, 2.4641099f, (u32) func_150ADA20() % 56 + 200, 0.0f, arg1, arg2);
    if (!inAir) {
        func_15136C3C(obj, 0, 0, 1, 0, 0, arg1, arg2);
    }
    func_10010F88(0x60D, 0x7D00, 0, 0, 0, (s32) pos.unk0, (s32) pos.unk4, (s32) pos.unk8, 500, 1000);
    if (inAir) {
        func_151CA070(obj, arg1, arg2);
    }
}
