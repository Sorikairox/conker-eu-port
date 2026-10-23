void func_1510FDA0(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, s32 arg4, f32 *arg5, f32 *arg6);
void func_1505A250(f32, f32, f32, f32 *, f32 *);
f32 func_1505210C(u8 *, f32, f32, f32 *, f32);

// swim_push_update: P179: per-frame floor / current push of a record standing or swimming (height +0x28 <= 0;
/* airborne: no push, strength 0.1). The push (fx, fz) comes from func_1510FDA0 (floor +0x188, contact +0x18C).
 * With +0xF8 bit 20 it is sampled again and the record turns towards it: the heading +0xB8 and +0xC4 blend
 * (rate 0.3, or 0.2 for kinds 0x28 / 0x77) to func_1505210C's angle / result x 0.7 (0.9). With bit 19 the push
 * becomes the record's drift: below 0.09 on both axes it stops (strength 0.2); otherwise each axis is clamped to
 * +-1 (a clamp on a kind-0x77 record also slows its speed +0x3C above 15 by 0.8 and sets +0x89 to 6 when below 8),
 * scaled by the speed (+0x226, else 35 or 7) with strength |push| x 0.7 (0.6) + 0.05; then func_1505A250
 * (-fx, -fz, strength, +0x164, +0x168). */
void func_150511E8(u8 *obj) {
    f32 sp40;
    f32 slide;
    f32 speed;
    f32 fx;
    f32 fz;
    f32 dummy64;
    f32 dummy60;
    f32 mul;
    f32 rate;
    f32 speedScale;
    f32 strength;
    f32 ang;
    f32 len;
    s32 clamped;

    if (*(f32 *)(obj + 0x28) <= 0.0f) {
        mul = 0.7f;
        rate = 0.3f;
        speed = 35.0f;
        speedScale = 0.7f;
        if (obj[4] == 0x28 || obj[4] == 0x77) {
            mul = 0.9f;
            rate = 0.2f;
            speed = 7.0f;
            speedScale = 0.6f;
        }
        func_1510FDA0(*(s32 *)(obj + 0x188), (s32) (obj + 0x18C), &dummy64, &dummy60, (s32) &slide, &fx, &fz);
        if (*(u32 *)(obj + 0xF8) & 0x100000) {
            func_1510FDA0(*(s32 *)(obj + 0x188), (s32) (obj + 0x18C), &dummy64, &dummy60, (s32) &slide, &fx, &fz);
            ang = func_1505210C(obj, fx, fz, &sp40, 50.0f);
            sp40 *= mul;
            *(f32 *)(obj + 0xB8) += (sp40 - *(f32 *)(obj + 0xB8)) * rate;
            *(f32 *)(obj + 0xC4) += (ang * mul - *(f32 *)(obj + 0xC4)) * rate;
        }
        if (!(*(u32 *)(obj + 0xF8) & 0x80000)) {
            return;
        }
        if (obj[0x226] != 0) {
            speed = obj[0x226];
        }
        if (fabsf(fx) < 0.09f && fabsf(fz) < 0.09f) {
            fx = 0.0f;
            fz = 0.0f;
            strength = 0.2f;
        } else {
            clamped = FALSE;
            if (1.0f < fabsf(fx)) {
                clamped = TRUE;
                fx = (fx < 0.0f) ? -1.0f : 1.0f;
            }
            if (1.0f < fabsf(fz)) {
                clamped = TRUE;
                fz = (fz < 0.0f) ? -1.0f : 1.0f;
            }
            if (clamped && obj[4] == 0x77) {
                if (15.0f < *(f32 *)(obj + 0x3C)) {
                    *(f32 *)(obj + 0x3C) *= 0.8f;
                }
                if (obj[0x89] < 8) {
                    obj[0x89] = 6;
                }
            }
            len = sqrtf(fx * fx + fz * fz);
            fx *= speed;
            fz *= speed;
            strength = len * speedScale + 0.05f;
        }
    } else {
        fx = 0.0f;
        fz = 0.0f;
        strength = 0.1f;
    }
    func_1505A250(-fx, -fz, strength, (f32 *) (obj + 0x164), (f32 *) (obj + 0x168));
}
