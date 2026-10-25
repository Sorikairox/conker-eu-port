#ifdef NON_MATCHING
s32 func_15146078(f32 *, f32 *, f32 *);
f32 func_15106A34(f32);
f32 func_15106A5C(f32);
f32 func_15106A90(f32);
f32 func_15106AC0(f32);
f32 func_15106AD8(f32);
f32 func_15106B04(f32);
f32 func_15106B3C(f32);
f32 func_15106B6C(f32);
// bolt_arc_sample_curve: samples the arc's cubic Bezier curve (control points +0x14, +0x20, +0x2C, +0x38) at the
// +0x48 points t = step, 2 * step, ... (step +0x64 = 1 / (n + 1)) into the 0x34-byte records at +0x88: t, the
// position (Bernstein weights func_15106A34 / A5C / A90 / AC0), the tangent (derivatives func_15106AD8 / B04 / B3C /
// B6C) and two side vectors at +0x1C / +0x28 from func_15146078 (zero when it fails, e.g. a zero tangent).
// The asm leaves a stale v0; the only caller (func_15106260) ignores it, so the C is void.
void func_15106794(struct102 *arg0) {
    u8 *obj = (u8 *) arg0;
    f32 *rec;
    f32 *p0 = (f32 *) (obj + 0x14);
    f32 *p1 = (f32 *) (obj + 0x20);
    f32 *p2 = (f32 *) (obj + 0x2C);
    f32 *p3 = (f32 *) (obj + 0x38);
    f32 step;
    f32 t;
    f32 b0, b1, b2, b3;
    f32 d0, d1, d2, d3;
    s32 i;
    s32 k;

    rec = (f32 *) func_15106760((s32) arg0);
    step = *(f32 *) (obj + 0x64);
    t = step;
    for (i = 0; i < *(s32 *) (obj + 0x48); i++) {
        rec[0] = t;
        b0 = func_15106A34(t);
        b1 = func_15106A5C(t);
        b2 = func_15106A90(t);
        b3 = func_15106AC0(t);
        d0 = func_15106AD8(t);
        d1 = func_15106B04(t);
        d2 = func_15106B3C(t);
        d3 = func_15106B6C(t);
        for (k = 0; k < 3; k++) {
            rec[1 + k] = p0[k] * b0 + p1[k] * b1 + p2[k] * b2 + p3[k] * b3;
        }
        for (k = 0; k < 3; k++) {
            rec[4 + k] = p0[k] * d0 + p1[k] * d1 + p2[k] * d2 + p3[k] * d3;
        }
        if (func_15146078(rec + 4, rec + 7, rec + 10) == 0) {
            rec[7] = 0.0f;
            rec[8] = 0.0f;
            rec[9] = 0.0f;
            rec[10] = 0.0f;
            rec[11] = 0.0f;
            rec[12] = 0.0f;
        }
        rec += 13;
        t += step;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_133A70/func_15106794.s")
#endif
