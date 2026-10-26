#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15187EC0 */
s32 light_fx_add(s32 arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7)
{
  u8 *e;
  if (g_light_fx_count < 5)
  {
    e = (u8 *) (&g_light_fx[g_light_fx_count]);
    *((f32 *) (((u8 *) (&g_light_fx[g_light_fx_count])) + 0x14)) = arg1;
    *((s32 *) (((u8 *) (&g_light_fx[g_light_fx_count])) + 0x10)) = arg0;
    ((u8 *) (&g_light_fx[g_light_fx_count]))[0] = (((u8 *) (&g_light_fx[g_light_fx_count]))[6] = arg2);
    ((u8 *) (&g_light_fx[g_light_fx_count]))[1] = (((u8 *) (&g_light_fx[g_light_fx_count]))[7] = arg3);
    ((u8 *) (&g_light_fx[g_light_fx_count]))[2] = (((u8 *) (&g_light_fx[g_light_fx_count]))[8] = arg4);
    ((u8 *) (&g_light_fx[g_light_fx_count]))[3] = arg5;
    ((u8 *) (&g_light_fx[g_light_fx_count]))[4] = arg6;
    ((u8 *) (&g_light_fx[g_light_fx_count]))[5] = arg7;
    bzero(e + 0x18, 0xC);
    g_light_fx_count++;
    return g_light_fx_count - 1;
  }
  return -1;
}

/* was func_15188500 */
void light_fx_clear_all(void) {
    bzero(g_light_fx, 0xB4);
    g_light_fx_count = 0;
}

/* was func_15188530 */
void light_fx_get_colour(s32 arg0, s32 *arg1) {
    if ((arg0 < g_light_fx_count) && (arg0 >= 0)) {
        struct_eu_800DFB30 *temp_v0 = &g_light_fx[arg0];
        arg1[0] = temp_v0->unk6;
        arg1[1] = temp_v0->unk7;
        arg1[2] = temp_v0->unk8;
    }
}

/* was func_15188580 */
void light_fx_get_blend(s32 arg0, f32 *arg1) {
    if ((arg0 < g_light_fx_count) && (arg0 >= 0)) {
        *arg1 = g_light_fx[arg0].unkC;
    }
}

extern f32 g_light_fx_blend[][9]; /* was D_800DFB3C */
/* was func_151885BC */
void light_fx_set_blend(s32 arg0, f32 arg1) {
    if (arg0 < g_light_fx_count && arg0 >= 0) {
        if (arg1 > 1.0f) {
            arg1 = 1.0f;
        } else if (arg1 < 0.0f) {
            arg1 = 0.0f;
        }
        g_light_fx_blend[arg0][0] = arg1;
    }
}

/* P129: the light effects g_light_fx[g_light_fx_count] (set up by light_fx_add), seen with their fields. */
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
extern f32 g_light_fx_two_pi_7778;          /* 2 pi; was D_800A7778 */
extern u8 g_light_fx_blink_off_times[8];        /* blink pattern: off times; was D_800A7770 */
f32 sinf(f32);
s32 game_gu_random(void);

// light_fx_update: advances every light effect (pulse, blink pattern, random flicker) and blends its output
// colour between its two colours. The asm returns nothing; s32 for the caller's declaration (game_eu_1A2720.c).
/* was func_15188630 */
s32 light_fx_update(void) {
    LightFx *e;
    s32 v;
    s32 i;
    f32 f;
    u32 c;

    if (g_light_fx_count <= 0) {
        return 0;
    }
    /* do-while with an unsigned end test, as the asm (matters only for absurd counts whose end pointer wraps) */
    e = (LightFx *)g_light_fx;
    do {
        switch (e->mode) {
        case 1:
            e->t = (sinf(e->a.phase) + 1.0f) * 0.5f;
            e->a.phase += e->speed * g_frame_step_f;
            if (g_light_fx_two_pi_7778 <= e->a.phase) {
                e->a.phase -= g_light_fx_two_pi_7778;
            }
            break;
        case 2:
            v = e->b.timer;
            if (v == 0) {
                e->b.timer = -8;
                e->t = 1.0f;
            } else if (v < 0) {
                /* lit for 8 frames, then off for the pattern's next time */
                e->b.timer = v + g_frame_ticks;
                if (e->b.timer >= 0) {
                    e->t = 0.0f;
                    e->a.step++;
                    if ((u32)e->a.step >= 8) {
                        e->a.step = 0;
                    }
                    e->b.timer = g_light_fx_blink_off_times[e->a.step];
                }
            } else {
                e->b.timer = v - g_frame_ticks;
                if (e->b.timer < 0) {
                    e->b.timer = 0;
                }
            }
            break;
        case 3:
            switch (e->a.state) {
            case 0: /* fade up to the target, then hold (1.0) or fade down */
                e->t += e->speed * g_frame_ticks;
                if (e->b.target <= e->t) {
                    e->t = e->b.target;
                    if (e->b.target == 1.0f) {
                        e->b.target = (game_gu_random() & 1) ? 0.5f : 0.0f;
                        e->a.state = 2;
                    } else {
                        e->a.state = 1;
                        e->b.timer = game_gu_random() % 30 + 30;
                    }
                }
                break;
            case 1: /* hold */
                e->b.timer -= g_frame_ticks;
                if (e->b.timer <= 0) {
                    e->a.state = (game_gu_random() % 2) * 2;
                    e->b.target = (e->a.state != 0) ? 0.0f : 1.0f;
                }
                break;
            case 2: /* fade down to the target, then hold */
                e->t -= e->speed * g_frame_ticks;
                if (e->t <= e->b.target) {
                    e->t = e->b.target;
                    e->a.state = (e->b.target == 0.0f) ? 3 : 1;
                    e->b.timer = game_gu_random() % 30 + 30;
                }
                break;
            case 3: /* off */
                e->b.timer -= g_frame_ticks;
                if (e->b.timer <= 0) {
                    e->a.state = 0;
                    e->b.target = (game_gu_random() & 1) ? 1.0f : 0.5f;
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
    } while ((u32)++e < (u32)&g_light_fx[g_light_fx_count]);
    return 0;
}
