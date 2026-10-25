#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
extern s16 D_80084814;

void func_1503FCE0(s16 arg0, s16 *arg1, s16 *arg2) {
    s16 temp_v1;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 var_v0;
    s16 var_v0_2;
    s8 temp_a0;
    s8 temp_v1_2;
    u8 *temp_v0;

    temp_v1 = D_80084814 - 1;
    temp_v0 = *(s32 *)(*D_800BE728 + (arg0 * 4));
    if (temp_v1 != 0) {
        D_80084814 = temp_v1;
        *arg1 = 0;
        *arg2 = 0;
        return;
    }
    temp_a0 = (*(s8 *)((u8 *)temp_v0 + 2));
    D_80084814 = 5;
    if ((temp_a0 < -0x14) || (temp_a0 >= 0x15)) {
        *arg1 = (s16) temp_a0;
    } else {
        *arg1 = 0;
    }
    temp_v1_2 = (*(s8 *)((u8 *)temp_v0 + 3));
    if ((temp_v1_2 < -0x14) || (temp_v1_2 >= 0x15)) {
        *arg2 = (s16) temp_v1_2;
    } else {
        *arg2 = 0;
    }
    (*(s8 *)((u8 *)temp_v0 + 2)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 3)) = 0;
    temp_v1_3 = *arg1;
    if (temp_v1_3 < -1) {
        *arg1 = -1;
    } else {
        var_v0 = temp_v1_3;
        if (temp_v1_3 >= 2) {
            var_v0 = 1;
        }
        *arg1 = var_v0;
    }
    temp_v1_4 = *arg2;
    if (temp_v1_4 < -1) {
        *arg2 = -1;
        return;
    }
    var_v0_2 = temp_v1_4;
    if (temp_v1_4 >= 2) {
        var_v0_2 = 1;
    }
    *arg2 = var_v0_2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6D4F0/func_1503FCE0.s")
#endif
void func_1503FB08(void) {
    D_80084818 = 0;
    D_800C6C70 = 0.0f;
    D_8008481C = 0;
    D_80084820 = 30;
    D_80084824 = 0;
}

#ifdef NON_MATCHING
s32 func_1509CF78(void);
s32 func_1509CEA8(s32);
u8 *func_1509CE20(s32);
s32 func_1509CE88(s32);
void func_15042BC4(u8 *, s32 *, s32 *, s32 *);
Gfx *func_15041A9C(Gfx *, f32, f32, u8 *, s32, s32, s32, s32, f32, f32, s32);
s32 strlen(const char *);
extern u16 D_800BEB30;     /* buttons pressed this frame */
extern u8 D_80084828;      /* selected entry */
extern u8 D_80085D30[];    /* text display list */
extern u8 D_80098CE0[];    /* text shown while the menu is locked */
extern u8 D_80098CF4[];    /* marker line drawn above some entries */
extern u8 D_80098CF8[];    /* blink text of the selected entry */
extern u8 D_8008482C[];    /* empty text */

// menu_list_update_draw: scrolling text menu of func_1509CF78() entries (19 rows shown, the selected entry
// D_80084828 in the middle). `select` buttons pick the selected entry when it is unlocked (bit func_1509CEA8(i + 1) of
// D_800D2E4C) and return its id; `cancel` or B (0x4000) return -1. Up (4) / down (8) or the stick (func_1503FCE0)
// start a scroll (D_80084818 = -1 / 1) that moves the offset D_800C6C70 by 1.25 per tick up to +-11, then steps the
// selection by 1 (3 with Z held). Pressing 0x30 together locks the menu for 60 ticks (func_15017790 /
// func_150177F8, D_8008481C) and shows D_80098CE0 on every row. Rows fade in / out at the edges (alpha 64 per
// row); the selected row is red (blinking D_80098CF8 every 30 ticks, D_80084820 / D_80084824), others white;
// entries with func_1509CE88 < 0 get the marker D_80098CF4 above them. Returns -2 while no choice is made.
s32 func_1503FE30(Gfx **gfxp, u16 cancel, u16 select) {
    u16 buttons;
    s32 count;
    u8 visible;
    u8 idx;
    u8 i;
    u8 alpha;
    s32 id;
    s32 a;
    s32 b;
    s32 step;
    s32 row;
    s32 y;
    s32 w, h, d;
    s32 w2, h2;
    s32 hSel;
    s16 stickX, stickY;
    u8 *text;
    f32 top;
    f32 x;
    f32 yy;
    f32 off;
    Gfx *g;

    buttons = D_800BEB30;
    alpha = 0;
    i = 0;
    row = 0;
    w = 0;
    h = 0;
    count = func_1509CF78();
    g = *gfxp;
    *gfxp = g + 1;
    ((s32 *) g)[0] = 0xDE000000; /* gSPDisplayList(D_80085D30) */
    ((s32 *) g)[1] = (s32) D_80085D30;
    visible = (count < 19) ? count : 19;
    y = 1;

    if (D_8008481C == 0 && (buttons & 0x20) && (buttons & 0x10)) {
        D_8008481C = 60;
        func_15017790();
        func_150177F8();
    }
    if (D_8008481C != 0) {
        buttons = 0;
        D_8008481C -= D_800BE9E4;
        if (D_8008481C <= 0) {
            D_8008481C = 0;
        }
    }

    if (buttons & select) {
        a = func_1509CEA8(D_80084828 + 1);
        b = func_1509CEA8(D_80084828 + 1);
        if (!(((u8 *) D_800D2E4C)[a >> 3] & (1 << (b & 7)))) {
            return func_1509CEA8(D_80084828 + 1);
        }
    }
    if ((buttons & cancel) || (buttons & 0x4000)) {
        return -1;
    }

    func_1503FCE0(0, &stickX, &stickY);
    if (D_80084818 != 0) {
        D_800C6C70 += 1.25f * (s32) (D_80084818 * D_800BE9E4);
        if (D_800C6C70 < -11.0f) {
            D_800C6C70 = -11.0f;
        } else {
            D_800C6C70 = (11.0f < D_800C6C70) ? 11.0f : D_800C6C70;
        }
        if (11.0f <= fabsf(D_800C6C70)) {
            step = 1;
            if (**(u16 **) D_800BE728[0] & 0x2000) {
                step = 3;
            }
            if (D_80084818 == 1) {
                D_80084828 -= step;
                if (count < D_80084828) {
                    D_80084828 += count;
                }
            } else if (D_80084818 == -1) {
                D_80084828 = (D_80084828 + step) % count;
            }
            D_80084818 = 0;
            D_800C6C70 = 0.0f;
        }
    } else if (buttons & 4) {
        D_80084818 = -1;
        D_800C6C70 = 0.0f;
    } else if (stickY == -1) {
        D_80084818 = -1;
        D_800C6C70 = 0.0f;
    } else if ((buttons & 8) || stickY == 1) {
        D_80084818 = 1;
        D_800C6C70 = 0.0f;
    }

    /* first row: the selected entry minus half the rows, wrapped */
    idx = D_80084828 - ((visible - 1) >> 1);
    if (count < idx) {
        idx += count;
    }
    *(s8 *) &D_80084820 -= D_800BE9E4;
    if (*(s8 *) &D_80084820 <= 0) {
        *(s8 *) &D_80084820 = 30;
        D_80084824 ^= 1;
    }

    do {
        id = func_1509CEA8(idx + 1);
        if (D_8008481C != 0) {
            text = D_80098CE0;
            func_15042BC4(text, &w, &h, &d);
        } else {
            func_15042BC4(func_1509CE20(id), &w, &h, &d);
            if (((u8 *) D_800D2E4C)[id >> 3] & (1 << (id & 7))) {
                if (D_80084828 == idx) {
                    text = D_80084824 ? D_80098CF8 : func_1509CE20(id);
                    func_15042BC4(text, &w, &hSel, &d);
                } else {
                    text = func_1509CE20(id);
                }
            } else {
                text = func_1509CE20(id);
            }
        }
        x = D_800BE620 * 0.5f - (w >> 1);
        top = y + 1.0f;
        yy = top + D_800C6C70;
        if (func_1509CE88(id) < 0) {
            func_15042BC4(D_80098CF4, &w2, &h2, &d);
            off = D_800C6C70;
            *gfxp = func_15041A9C(*gfxp, D_800BE620 * 0.5f - (w2 >> 1), top + off, D_80098CF4, 0xFF, 0xFF, 0xFF, alpha,
                                  4096.0f, 4096.0f, strlen((char *) D_80098CF4));
            y += h2;
            yy += h2;
        }
        if (row < 3) {
            alpha = row * 64 + 64;
        } else if (visible - 3 < row) {
            alpha = (visible - row) << 6;
        } else {
            alpha = 0xFF;
        }
        if (text == NULL) {
            text = D_8008482C;
        }
        if (D_8008481C == 0 && (D_80084828 != idx || D_80084818 != 0)) {
            *gfxp = func_15041A9C(*gfxp, x, yy, text, 0xFF, 0xFF, 0xFF, alpha, 4096.0f, 4096.0f, strlen((char *) text));
        } else {
            *gfxp = func_15041A9C(*gfxp, x, yy, text, 0xFF, 0, 0, alpha, 4096.0f, 4096.0f, strlen((char *) text));
        }
        idx++;
        y += h;
        row++;
        idx %= count;
        i++;
    } while (i < visible);
    return -2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6D4F0/func_1503FE30.s")
#endif
