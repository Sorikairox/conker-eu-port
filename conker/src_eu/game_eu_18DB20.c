#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 screen_fade_alpha(s32);
s32 hud_lens_is_off(s32);
extern u8 D_800C35EA;
extern void (*D_8008B478[])(u8 *, u16 *);

/*
 * framebuffer_effects_apply: runs the framebuffer handlers (D_8008B478, index effect+0x10, -1 = none) of the
 * type-0x34 effects of both list groups on the frame about to be swapped (called by sched_swap_framebuffer).
 * Flag bits at effect+0xE: 4 = skip this frame once (cleared here), 2 = not while D_800C35EA == 1,
 * 8 = only while hud_lens_is_off(0) is set and screen_fade_alpha(0) is 0. Walks with the D_800DD5C8 safe-next
 * stack so a handler may free its effect.
 */
/* was func_15160310 */
void fb_fx_apply_all(u16 *fb) {
    u8 i;
    u8 *node;
    u8 flags;
    s32 run;

    for (i = 0; i < 2; i++) {
        node = (u8 *)D_800DD280[i][0x34];
        D_800DD5C0++;
        while (node != NULL) {
            D_800DD5C8[D_800DD5C0] = ((struct_eu_node *)node)->next;
            flags = node[0xE];
            if (flags & 4) {
                node[0xE] = flags & ~4;
            } else if (*(s8 *)(node + 0x10) != -1) {
                run = TRUE;
                if ((flags & 2) && D_800C35EA == 1) {
                    run = FALSE;
                }
                if (flags & 8) {
                    if (hud_lens_is_off(0) == 0) {
                        run = FALSE;
                    } else if (screen_fade_alpha(0) != 0) {
                        run = FALSE;
                    }
                }
                if (run) {
                    D_8008B478[*(s8 *)(node + 0x10)](node, fb);
                }
            }
            node = (u8 *)D_800DD5C8[D_800DD5C0];
        }
        D_800DD5C0--;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_18DB20/fb_fx_apply_all.s")
#endif

/* was func_151604E4 */
u8 *fb_fx_spawn(s32 arg0, s32 arg1, u8 arg2, s32 arg3) {
    u8 *temp_v0;

    temp_v0 = node_alloc(0x34, arg3, arg1 + 0x18, 1, (u8) (s32) arg2, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(temp_v0 + 0xE, arg0, 8);
    return temp_v0;
}

extern s32 (*D_8008B470[])(void);
/* was func_1516055C */
void fb_fx_update(u8 *arg0) {
    s32 pad;
    u8 ret = 0;

    if ((arg0[0xE] & 1) != 0) {
        *(s16 *)(arg0 + 0x12) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x12) < 0) {
            ret = 1;
        }
    }
    if ((ret == 0) && (*(s8 *)(arg0 + 0xF) != -1) && (D_8008B470[*(s8 *)(arg0 + 0xF)]() == 0)) {
        ret = 1;
    }
    if (ret) {
        node_destroy(arg0);
    }
}

/* was func_eu_15160600 */
void fb_fx_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(u8 *, s32, u8) = D_8008B484[arg0[0x14]];

    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg2);
    }
}

/* was func_15160648 */
s32 fb_fx_debug_tweak(u8 *arg0) {
    s32 i;
    f32 *p;

    i = 0;
    p = (f32 *)(arg0 + 0x18);
    p[0] = debug_tweak_int(i++, "pos s", -2000, 2000, 0, "../Effects/ColourFrameBuffer/colourframebuffer.c", 452) * 0.001f;
    p[1] = debug_tweak_int(i++, "pos t", -2000, 2000, 0, "../Effects/ColourFrameBuffer/colourframebuffer.c", 457) * 0.001f;
    p[2] = debug_tweak_int(i++, "size s", 0, 2000, 500, "../Effects/ColourFrameBuffer/colourframebuffer.c", 462) * 0.001f;
    p[3] = debug_tweak_int(i++, "size t", 0, 2000, 500, "../Effects/ColourFrameBuffer/colourframebuffer.c", 467) * 0.001f;
    *(s32 *)&p[4] = debug_tweak_int(i++, "pixelation", 0, 0x10000, 0x10000, "../Effects/ColourFrameBuffer/colourframebuffer.c", 473);
    return 1;
}

/* was func_151607E4 */
void fb_fx_broadcast(s32 arg0, u8 arg1) {
    const s32 sp1C[1] = {0x34};

    node_broadcast_types(sp1C, 0x1, arg0, arg1);
}
