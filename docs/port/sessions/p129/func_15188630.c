/* P129: the light effects D_800DFB30[D_800DFBE4] (set up by func_15187EC0), seen with their fields. */
typedef struct {
    /* 0x00 */ u8 from[3];      /* colour at t = 0 */
    /* 0x03 */ u8 to[3];        /* colour at t = 1 */
    /* 0x06 */ u8 cur[3];       /* output colour */
    /* 0x09 */ u8 pad9[3];
    /* 0x0C */ f32 t;           /* 0..1 */
    /* 0x10 */ s32 mode;        /* 0 fixed, 1 pulse, 2 blink pattern, 3 random flicker */
    /* 0x14 */ f32 speed;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ union { f32 phase; s32 step; s32 state; } a;
    /* 0x20 */ union { s32 timer; f32 target; } b;
} LightFx;
extern f32 D_800A7778;          /* 2 pi */
extern u8 D_800A7770[8];        /* blink pattern: off times */
f32 sinf(f32);
s32 func_151EFDD0(void);

// light_fx_update: advances every light effect (pulse, blink pattern, random flicker) and blends its output
// colour between its two colours. The asm returns nothing; s32 for the caller's declaration (game_eu_1A2720.c).
s32 func_15188630(void) {
    LightFx *e;
    s32 v;
    s32 i;
    f32 f;
    u32 c;

    if (D_800DFBE4 <= 0) {
        return 0;
    }
    /* do-while with an unsigned end test, as the asm (matters only for absurd counts whose end pointer wraps) */
    e = (LightFx *)D_800DFB30;
    do {
        switch (e->mode) {
        case 1:
            e->t = (sinf(e->a.phase) + 1.0f) * 0.5f;
            e->a.phase += e->speed * D_800BE9A4;
            if (D_800A7778 <= e->a.phase) {
                e->a.phase -= D_800A7778;
            }
            break;
        case 2:
            v = e->b.timer;
            if (v == 0) {
                e->b.timer = -8;
                e->t = 1.0f;
            } else if (v < 0) {
                /* lit for 8 frames, then off for the pattern's next time */
                e->b.timer = v + D_800BE9E4;
                if (e->b.timer >= 0) {
                    e->t = 0.0f;
                    e->a.step++;
                    if ((u32)e->a.step >= 8) {
                        e->a.step = 0;
                    }
                    e->b.timer = D_800A7770[e->a.step];
                }
            } else {
                e->b.timer = v - D_800BE9E4;
                if (e->b.timer < 0) {
                    e->b.timer = 0;
                }
            }
            break;
        case 3:
            switch (e->a.state) {
            case 0: /* fade up to the target, then hold (1.0) or fade down */
                e->t += e->speed * D_800BE9E4;
                if (e->b.target <= e->t) {
                    e->t = e->b.target;
                    if (e->b.target == 1.0f) {
                        e->b.target = (func_151EFDD0() & 1) ? 0.5f : 0.0f;
                        e->a.state = 2;
                    } else {
                        e->a.state = 1;
                        e->b.timer = func_151EFDD0() % 30 + 30;
                    }
                }
                break;
            case 1: /* hold */
                e->b.timer -= D_800BE9E4;
                if (e->b.timer <= 0) {
                    e->a.state = (func_151EFDD0() % 2) * 2;
                    e->b.target = (e->a.state != 0) ? 0.0f : 1.0f;
                }
                break;
            case 2: /* fade down to the target, then hold */
                e->t -= e->speed * D_800BE9E4;
                if (e->t <= e->b.target) {
                    e->t = e->b.target;
                    e->a.state = (e->b.target == 0.0f) ? 3 : 1;
                    e->b.timer = func_151EFDD0() % 30 + 30;
                }
                break;
            case 3: /* off */
                e->b.timer -= D_800BE9E4;
                if (e->b.timer <= 0) {
                    e->a.state = 0;
                    e->b.target = (func_151EFDD0() & 1) ? 1.0f : 0.5f;
                }
                break;
            }
            break;
        }
        for (i = 0; i < 3; i++) {
            /* IDO's truncating float -> unsigned conversion: negative values (<= -1) and NaN give 0xFFFFFFFF */
            f = e->t * (f32)(e->to[i] - e->from[i]) + (f32)e->from[i];
            if (f >= 2147483648.0f) {
                f -= 2147483648.0f;
                c = (f < 2147483648.0f) ? ((u32)(s32)f | 0x80000000) : 0xFFFFFFFF;
            } else {
                c = (f > -1.0f) ? (u32)(s32)f : 0xFFFFFFFF;
            }
            e->cur[i] = c;
        }
    } while ((u32)++e < (u32)&D_800DFB30[D_800DFBE4]);
    return 0;
}
