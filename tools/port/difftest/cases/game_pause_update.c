#ifdef NON_MATCHING
typedef struct MenuPad {
    u16 button;
    s8 stickX;
    s8 stickY;
    u8 errno_;
    u8 pad5;
} MenuPad;
extern MenuPad D_800BED38[4];   /* controller state, 6 bytes each */
extern u16 D_800BED50;          /* new button presses per controller (u16 each) */
extern u8 D_800901CC;           /* pause menu cursor (read signed) */
extern s8 D_800E1013;
extern s32 D_80090118;          /* time limit (frames) */
extern s32 *D_800E0EB8;         /* callback run when the menu fade ends */
extern s8 D_8009013C;
extern u8 D_80090158;
extern s8 D_80090298;           /* pause input delay */
extern s8 D_8009029C;           /* unpause countdown */
extern s8 D_800902A0;           /* last stick x */
extern s8 D_800E0EB5;           /* last stick y */
extern s8 D_80090138;           /* quit confirmation: 1 = yes */
extern u8 D_8009016D;
extern u8 D_800BEEE3;
extern u8 D_800E0EC8;           /* controller that paused */
extern s8 D_800E0EC9;           /* frame counter for the seconds of play time */
extern s32 D_800D3268;
extern OSIoMesg D_80038C40;
extern u8 D_800ABBB8[];         /* "%d:%02d" */
extern u8 D_800ABBC0[];         /* "#": text id (the next argument), likewise the following */
extern u8 D_800ABBC4[];
extern u8 D_800ABBC8[];
extern u8 D_800ABBCC[];
extern u8 D_800ABBD0[];
extern u8 D_800ABBD4[];
extern u8 D_800ABBD8[];
extern u8 D_800ABBDC[];
extern u8 D_800ABBE0[];
s32 screen_fade_all_active();
void text_printf(s32, ...);   /* varargs, as its definition (game_70200) */
void text_printf_at(s32, s32, u8, s32, ...);
void text_set_color(u8 arg0, u8 arg1, u8 arg2, u8 arg3);
void menu_game_start(void);
void os_writeback_dcache(void *, s32); /* osWritebackDCache (hand-written cache loop) */

// game_pause_update: P127: menu handler of mode 0 (story game, D_8009018C[0]): counts the play time (D_800BE3E8
// seconds), shows the time limit (multiplayer, settings byte 3 >= 3), and runs the pause menu: START (0x1000) on a
// controller that is not disabled (D_800D18A0) opens it (D_800BEAC1) unless blocked (screen_fade_all_active, scene states);
// the stick moves the cursor D_800901CC over the 2 (story) / 3 (multiplayer) items with sfx 0x62D; past the last item
// is the quit confirmation (D_80090138 no / yes). A on "yes" quits to the menu (D_800E0EB8 = pause_quit_to_menu, in
// multiplayer menu_game_start to restart when the cursor was on "restart"); A on "no" goes back after Rare's cartridge
// check (2 words at ROM 0xF80; a mismatch DMAs 0x100 bytes to a random 0x803xxxxx address); START / B closes it.
void game_pause_update(void) {
    u8 dmaBuf[0x20];
    u8 *p;
    s32 sfx;
    u8 simple;
    s32 blocked;
    s32 nPads;
    s32 i;
    s32 yOff;
    s32 count;
    s32 y;
    s32 secs;
    s32 sel;
    u8 pad;
    s8 stickX;
    s8 stickY;

    D_800E0FC6 = 0;
    sfx = 0;
    blocked = 0;
    simple = D_80090158;
    if (D_800BE9F0 == 0x22) {
        simple = 1;
    }
    if (D_800C35EA != 1 || D_800BE9F0 != 0x18 || D_800C3A08 != 1) {
        if (screen_fade_all_active() != 0) {
            blocked = 1;
        }
    }
    if (D_800C35EA == 1 && D_800C3683 != 0) {
        blocked = 1;
    }
    if (D_80090298 > 0) {
        D_80090298--;
    }

    /* START opens the pause menu */
    if (D_800BEAC0 == 0 && D_800BEAC1 == 0 && !blocked && D_80090298 == 0) {
        nPads = D_80082FA0;
        for (i = 0; i <= nPads && D_800BEAC1 == 0; i++) {
            if (((&D_800BED50)[i] & 0x1000) && !(D_800D18A0 & (1 << i))) {
                D_800BEAC1 = 1;
                D_800BEEE3 = 1;
                D_800E0EC8 = i;
                D_800901CC = 0;
                D_800902A0 = D_800BED38[i].stickY;
                D_80090298 = 10;
            }
        }
    }

    /* play time */
    if (D_800BEAC0 == 0 && D_800D3268 != 0xC7) {
        D_800E0EC9 += D_800BE9E4;
        if (D_800E0EC9 >= 50) {
            D_800E0EC9 -= 50;
            D_800BE3E8++;
        }
    }

    /* time limit */
    if (D_800BE616 != 0 && D_800BEAC1 == 0 && D_800E1013 >= 3) {
        y = 198;
        if (D_80082FA0 > 0) {
            y = 100;
        }
        if (D_80090118 > 0) {
            D_80090118 -= D_800BEA08;
        } else {
            D_80090118 = 0;
        }
        secs = D_80090118 / 50;
        text_set_color(0xFF, 0xFF, 0xFF, 0xFF);
        text_printf_at(0x87, y, 0x80, (s32) D_800ABBB8, secs / 60, secs % 60);
    }

    if (D_8009029C > 0) {
        D_8009029C--;
        if (D_8009029C < 2) {
            D_800BEAC1 = 0;
        }
        return;
    }
    if (D_800BEAC0 == 0) {
        return;
    }

    /* pause menu */
    if (D_800BE616 != 0) {
        yOff = -0x24;
        count = 3;
    } else {
        yOff = 5;
        count = 2;
    }
    pad = D_800E0EC8;
    D_800E0FCA = (&D_800BED50)[pad];
    if (D_80090298 != 0) {
        D_800E0FCA = 0;
    }
    stickX = D_800BED38[pad].stickX;
    stickY = D_800BED38[pad].stickY;
    if ((s8) D_800901CC < count) {
        if ((D_800902A0 < 31 && stickX >= 31) || (D_800902A0 >= -30 && stickX < -30)) {
            if ((s8) D_800901CC == 2) {
                D_800901CC = 0;
            } else {
                D_800901CC = 1 - (s8) D_800901CC;
            }
            sfx = 0x62D;
        }
        if ((s8) D_800901CC != 0 && count == 3
            && ((D_800E0EB5 >= -30 && stickY < -30) || (D_800E0EB5 < 31 && stickY >= 31))) {
            sfx = 0x62D;
            if ((s8) D_800901CC == 2) {
                D_800901CC = 1;
            } else {
                D_800901CC = 2;
            }
        }
    } else if ((D_800902A0 >= -30 && stickX < -30) || (D_800902A0 < 31 && stickX >= 31)) {
        D_80090138 = 1 - D_80090138;
        sfx = 0x62D;
    }
    D_800902A0 = stickX;
    D_800E0EB5 = stickY;
    text_set_color(0xFF, 0xFF, 0xFF, D_8009016D);
    y = yOff + 0x73;
    if (simple) {
        D_800901CC = 0;
        text_printf_at(0x94, y, 1, (s32) D_800ABBC0, 0xD);
    } else {
        text_printf_at(0x94, y, 1, (s32) D_800ABBC4, 0x1A);
        if ((s8) D_800901CC < count) {
            text_printf_at(0xD5, y, 1, (s32) D_800ABBC8, ((s8) D_800901CC == 0) + 0xC);
        }
        text_set_pos(0x94, yOff + 0x55);
        if (count == (s8) D_800901CC) {
            text_printf((s32) D_800ABBCC, 0x32);
        } else if (count < (s8) D_800901CC) {
            text_printf((s32) D_800ABBD0, 0x33);
        }
    }
    text_set_pos(0x53, y);

    if ((s8) D_800901CC < count) {
        if (!simple) {
            sel = 1;
            if (count == 3) {
                text_set_pos(0x53, yOff + 0x63);
                text_printf((s32) D_800ABBD4, ((s8) D_800901CC == 1) + 0x21);
                sel = 2;
                text_set_pos(0x53, yOff + 0x82);
            }
            text_printf((s32) D_800ABBD8, (sel == (s8) D_800901CC) + 0xE);
        }
        if (D_800E0FCA & 0x1000) {
            D_8009029C = 5;
            D_80090298 = 10;
        } else if ((s8) D_800901CC == 0 || (D_800E0FCA & 0x4000)) {
            if (D_800E0FCA & 0xC000) {
                D_8009029C = 5;
                D_80090298 = 10;
            }
        } else if (D_800E0FCA & 0x8000) {
            /* A on the last item: to the quit confirmation */
            D_80090138 = 0;
            D_800901CC = (s8) D_800901CC + count - 1;
            if (count == 2) {
                D_800901CC = (s8) D_800901CC + 1;
            }
            sfx = 0x500;
        }
    } else {
        text_printf_at(0x6C, y, 1, (s32) D_800ABBDC, D_80090138 + 0x1F);
        text_printf_at(0xBC, y, 1, (s32) D_800ABBE0, 0x1E - D_80090138);
        if (D_800E0FCA & 0x8000) {
            if (D_80090138 != 0) {
                D_800E0B94 = 7;
                D_800E0EB8 = (s32 *) pause_quit_to_menu;
                D_80090114 = 8;
                if (D_800BE616 != 0) {
                    D_80090174[0x3F] = 4; /* MenuState mainPage */
                    if (count == (s8) D_800901CC) {
                        D_8009013C = 1;
                        D_800E0EB8 = (s32 *) menu_game_start;
                    }
                } else if (D_8008FDA8 >= 0) {
                    save_request_slot_write(D_8008FDA8);
                }
                D_800901CC = 0;
                D_80087270[0] = 0;
            } else {
                p = dmaBuf;
                if ((u32) p & 0xF) {
                    do {
                        p += 4;
                    } while ((u32) p & 0xF);
                }
                i = pause_bit_invert(-0xF81);
                os_writeback_dcache(p, 0x10);
                osPiStartDma(&D_80038C40, 0, 0, i, p, 0x10, &gMessageQueue[0]);
                osRecvMesg(&gMessageQueue[0], NULL, 1);
                osInvalDCache(p, 0x10);
                ((u32 *) p)[0] -= 0x3E0EF0F0;
                ((u32 *) p)[1] -= 0x3E0EF0F0;
                if (((u32 *) p)[0] != 0x3050A14A || ((u32 *) p)[1] != 0xBCFCF506) {
                    i = random_int();
                    osPiStartDma(&D_80038C40, 0, 0, i & 0xFFFF, (void *) ((random_int() & 0xFFFFE) + 0x80300000), 0x100,
                                 &gMessageQueue[0]);
                    osRecvMesg(&gMessageQueue[0], NULL, 1);
                }
                D_800901CC = (s8) D_800901CC - 2;
            }
            sfx = 0x500;
        } else if (D_800E0FCA & 0x4000) {
            D_800901CC = (s8) D_800901CC - 2;
        }
    }
    if (sfx != 0) {
        sound_play_2d(sfx, 0x5DC0, 0x40, 0, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/game_pause_update.s")
#endif
