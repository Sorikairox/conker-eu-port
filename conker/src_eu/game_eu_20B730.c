#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_151E5D28(void);

extern u8 D_800D3260;

extern s8 D_80090144;

void func_1501C710(s32, s32, s32, s32, s32);


void func_151DDF20(void) {
    s32 i;
    for (i = 0; i < 0x1C; i++) {
        D_800E1010[i] = D_800901F4[i];
    }
}

#ifdef NON_MATCHING
extern s8 D_80090210[];        /* settings minimum (0x1C bytes) */
extern s8 D_8009022C[];        /* settings maximum */

/*
 * P85: clamp the 0x1C settings bytes D_800E1010 (signed): a value outside [D_80090210[i], D_8009022C[i]] is reset to
 * its default D_800901F4[i] (as func_151DDF20 resets all of them). After a failed save checksum the settings are 0xFF
 * (-1) and this puts e.g. the language D_800E101A back in range. Callers pass arguments it ignores.
 */
void func_151DDF6C(void) {
    s32 i;

    for (i = 0; i < 0x1C; i++) {
        if (D_800E1010[i] < D_80090210[i] || D_8009022C[i] < D_800E1010[i]) {
            D_800E1010[i] = D_800901F4[i];
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DDF6C.s")
#endif

s32 func_151DE074(s32 arg0) {
    return ~arg0;
}

s32 func_1000E934();
s32 func_1000F1A8();

void func_151DE080(void) {
    D_800D3260 = 0;
    func_1501C710(6, 0x1D, 0, 0, 1);
    D_800E0B94 = 3;
    D_80090144 = 0;
    D_800BEAC1 = 0;
    func_151E5D28();
    func_1000F1A8();
    func_1000E934();
    D_8008FD8C = 1;
    D_80090130 = 1;
}

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
s32 func_1517F54C();
void func_15042E3C(s32, ...);   /* varargs, as its definition (game_70200) */
void func_15042D94(s32, s32, u8, s32, ...);
void func_1504332C(u8 arg0, u8 arg1, u8 arg2, u8 arg3);
void func_151E2FCC(void);
void func_10024190(void *, s32); /* osWritebackDCache (hand-written cache loop) */

// game_pause_update: P127: menu handler of mode 0 (story game, D_8009018C[0]): counts the play time (D_800BE3E8
// seconds), shows the time limit (multiplayer, settings byte 3 >= 3), and runs the pause menu: START (0x1000) on a
// controller that is not disabled (D_800D18A0) opens it (D_800BEAC1) unless blocked (func_1517F54C, scene states);
// the stick moves the cursor D_800901CC over the 2 (story) / 3 (multiplayer) items with sfx 0x62D; past the last item
// is the quit confirmation (D_80090138 no / yes). A on "yes" quits to the menu (D_800E0EB8 = func_151DE080, in
// multiplayer func_151E2FCC to restart when the cursor was on "restart"); A on "no" goes back after Rare's cartridge
// check (2 words at ROM 0xF80; a mismatch DMAs 0x100 bytes to a random 0x803xxxxx address); START / B closes it.
void func_151DE100(void) {
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
        if (func_1517F54C() != 0) {
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
        func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
        func_15042D94(0x87, y, 0x80, (s32) D_800ABBB8, secs / 60, secs % 60);
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
    func_1504332C(0xFF, 0xFF, 0xFF, D_8009016D);
    y = yOff + 0x73;
    if (simple) {
        D_800901CC = 0;
        func_15042D94(0x94, y, 1, (s32) D_800ABBC0, 0xD);
    } else {
        func_15042D94(0x94, y, 1, (s32) D_800ABBC4, 0x1A);
        if ((s8) D_800901CC < count) {
            func_15042D94(0xD5, y, 1, (s32) D_800ABBC8, ((s8) D_800901CC == 0) + 0xC);
        }
        func_150432FC(0x94, yOff + 0x55);
        if (count == (s8) D_800901CC) {
            func_15042E3C((s32) D_800ABBCC, 0x32);
        } else if (count < (s8) D_800901CC) {
            func_15042E3C((s32) D_800ABBD0, 0x33);
        }
    }
    func_150432FC(0x53, y);

    if ((s8) D_800901CC < count) {
        if (!simple) {
            sel = 1;
            if (count == 3) {
                func_150432FC(0x53, yOff + 0x63);
                func_15042E3C((s32) D_800ABBD4, ((s8) D_800901CC == 1) + 0x21);
                sel = 2;
                func_150432FC(0x53, yOff + 0x82);
            }
            func_15042E3C((s32) D_800ABBD8, (sel == (s8) D_800901CC) + 0xE);
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
        func_15042D94(0x6C, y, 1, (s32) D_800ABBDC, D_80090138 + 0x1F);
        func_15042D94(0xBC, y, 1, (s32) D_800ABBE0, 0x1E - D_80090138);
        if (D_800E0FCA & 0x8000) {
            if (D_80090138 != 0) {
                D_800E0B94 = 7;
                D_800E0EB8 = (s32 *) func_151DE080;
                D_80090114 = 8;
                if (D_800BE616 != 0) {
                    D_80090174[0x3F] = 4; /* MenuState mainPage */
                    if (count == (s8) D_800901CC) {
                        D_8009013C = 1;
                        D_800E0EB8 = (s32 *) func_151E2FCC;
                    }
                } else if (D_8008FDA8 >= 0) {
                    func_15007718(D_8008FDA8);
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
                i = func_151DE074(-0xF81);
                func_10024190(p, 0x10);
                osPiStartDma(&D_80038C40, 0, 0, i, p, 0x10, &gMessageQueue[0]);
                osRecvMesg(&gMessageQueue[0], NULL, 1);
                osInvalDCache(p, 0x10);
                ((u32 *) p)[0] -= 0x3E0EF0F0;
                ((u32 *) p)[1] -= 0x3E0EF0F0;
                if (((u32 *) p)[0] != 0x3050A14A || ((u32 *) p)[1] != 0xBCFCF506) {
                    i = func_150ADA20();
                    osPiStartDma(&D_80038C40, 0, 0, i & 0xFFFF, (void *) ((func_150ADA20() & 0xFFFFE) + 0x80300000), 0x100,
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
        func_10010F30(sfx, 0x5DC0, 0x40, 0, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DE100.s")
#endif

void func_151E5AB8(void);
void func_151DEBB4(void) {
    func_151E5AB8();
    *(s32 *)((u8 *)D_800CC2D0 + 0x25C) |= 0x200;
    D_800CC2D0[0].y_position = 1000.0f;
    if (D_80000300 != 0) {
        D_800E0EC0 = 0;
    }
    if (D_800E0EC0 >= 0x119 && (D_800E0FCA & 0x8000)) {
        if (D_800E0EC0 < 0x190) {
            D_800E0EC0 = 0x190;
        }
        if (D_800E0EC0 >= 0x1F5 && D_800E0EC0 < 0x258) {
            D_800E0EC0 = 0x258;
        }
    }
    if (D_800E0EC0 >= 0x2C7) {
        D_800901C8 = 2;
        D_800E0B94 = 1;
        D_800D3260 = 0;
        func_1501C710(6, 0x21, 0, 0, 1);
        *(u8 *)&D_800E0FC6 = 0xFF;
    }
}

void func_151DED3C(void);

void func_151DECB4(void) {
    D_800E0EC0 = 0;
    D_800E0FC7 = 0;
    D_800E0FC8 = 0;
    D_800E0EBC = 0;
    D_800901C8 = 2;
    func_151DED3C();
}

void func_151DECFC(void) {
    D_80090114 = 4;
    D_800E0FC6 = 0;
    if (D_800901D0 == 0) {
        func_1500764C();
    }
}


void func_151DED3C(void) {
    D_800D3260 = 0;
    func_1501C710(6, 0x1D, 0, 0, 1);
    D_800E0B94 = 3;
    D_80090120 = 1;
    D_800901C8 = 2;
    D_80090144 = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3E)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x2B)) = 5;
    (*(s8 *)((u8 *)D_80090174 + 0x2C)) = (s8) (*(s8 *)((u8 *)D_80090174 + 0x2B));
}

void func_151DEDC8(void) {
}

#ifdef NON_MATCHING
/* P117: the menu state record D_80090174 (points at D_800E0F20, set by func_151E582C). */
typedef struct MenuState {
    f32 x0;
    f32 x4;
    f32 fade;           /* 0x08: page fade-in, >= 0.5 shows the page, 1.0 = done */
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    u16 input;          /* 0x20: controller 1's menu input bits of this frame */
    u16 padInput[4];    /* 0x22: menu input bits per controller (1 up, 2 down, 4 left, 8 right, 0x10 accept, 0x20 back, 0x40 / 0x80 C buttons) */
    s8 x2A;
    s8 x2B;
    s8 titlePage;       /* 0x2C: page of the title menu (menu 0) */
    s8 x2D;
    s8 stickX[4];       /* 0x2E: last stick x per controller (0 = released, re-arms the edge) */
    s8 stickY[4];       /* 0x32 */
    s8 repeatX[4];      /* 0x36: auto-repeat counters */
    s8 repeatY[4];      /* 0x3A */
    s8 menu;            /* 0x3E: 0 = title menu, 1 = main menu */
    s8 mainPage;        /* 0x3F: page of the main menu (menu 1) */
    s8 prevMainPage;    /* 0x40 */
    s8 x41;
    s8 x42;
    s8 x43;             /* 0x43: P120: set when the main menu camera slid back to the title (carousel) */
    s8 x44;
} MenuState;

/* P127: MenuPad is defined before func_151DE100 */
extern MenuPad D_800BED38[4];   /* controller state, 6 bytes each */
extern s8 D_80090110;           /* queue entries to drop */
extern s8 D_800901E4;           /* first of a 16-byte queue */
extern u16 D_800BED50;          /* new button presses per controller (u16 each) */
extern s8 D_80090124;
extern s8 D_8009017C;           /* bit i: controller i's stick x holds (no auto-repeat) */
extern s8 D_80090184;
extern f32 D_80090188;
extern s32 D_800901C4;
extern u8 D_800901D4;
extern f32 D_800901D8;
extern f32 D_800901DC;
extern s8 D_800901E0;
extern s8 D_800902A4;
extern s8 D_800902A8;
extern s16 D_800902AC;
extern u8 D_800E0EC4;
extern u8 D_800E0EC5;
extern u8 D_800E0EC6;
extern u8 D_800901CC;
void func_151EE704(void);
void func_15007778(void);
void func_151E856C(void);
void func_151E8998(void);
void func_150076BC(s32 arg0);
void func_15007684(void);
void func_1500764C(void);
void func_151E5AB8(void);
void func_1501D348(s32, s32, s32, s32, s32);
void func_1504332C(u8 arg0, u8 arg1, u8 arg2, u8 arg3);
void func_15042D94(s32, s32, u8, s32, ...);  /* varargs, as its definition (game_70200) */
void func_1000E7A0(u32, s32);
void func_151DF6A4(void);
void func_151DFD0C(void);
void func_151E06D0(void);
void func_151E0BBC(void);
void func_151E1174(void);
void func_151E1308(void);
void func_151E19AC(void);
void func_151E1EDC(void);
void func_151E2A1C(void);

#define MENU_STICK_ON 0x32      /* stick threshold (+-50) */

// menu_mode_update: game mode 3 (title / main menu on level 0x1D), once per frame.
// Frames 0..4 after entering the mode set things up (frame 0: menu sprites, save slots, settings), then the
// pending scene start (D_80090120), the input queue shift, the controller -> menu input bits with stick auto-repeat,
// the attract-mode check (demo: any button stops it), the "press start"-like blinking prompt fade D_800902AC,
// the menu music and finally the page handler of the title menu (rec->titlePage) or of the main menu
// (rec->mainPage) once the page has faded in halfway; below that the menu input state is reset.
void func_151DEDD0(void) {
    MenuState *rec;
    s32 frame;
    s32 i;
    s32 n;
    s32 x;
    s32 a;
    f32 f;
    s32 t;

    frame = (u8) D_80090144;
    if (frame < 5) {
        if (frame == 0) {
            func_151EE704();
            func_15007778();
            func_151E856C();
            func_151E8998();
            frame = (u8) D_80090144;
        }
        if (frame < 4) {
            func_150076BC(frame);
        } else {
            func_15007684();
        }
        D_80090144 = (u8) D_80090144 + 1;
    } else if (D_800901D0 == 0) {
        func_1500764C();
    }

    if ((u8) D_80090120 != 0) {
        *(s32 *) ((u8 *) D_800DBFF0 + 0x2C) = 0x80000;
        func_1501D348(D_800BE9F0, 1, 0, 0, 0);
        D_80090120 = 0;
        return;
    }

    /* drop the first n entries of the two 16-byte queues (copies entry i + n to i for i in n .. 15 - n, as the asm) */
    n = D_80090110;
    frame = (u8) D_80090144;
    if (n != 0) {
        for (i = n; i < 0x10 - n; i++) {
            (&D_800901E4)[i] = (&D_800901E4)[i + n];
            D_800E1030[i] = D_800E1030[i + n];
        }
        D_80090110 = 0;
    }
    if (frame >= 5) {
        func_151E5AB8();
    }

    for (i = 0; i < 4; i++) {
        rec = (MenuState *) D_80090174;
        rec->padInput[i] = 0;
        if ((u8) D_800E0FC6 == 0) {
            /* edges: the stick crosses +-50 since the last frame; buttons A / Start accept, B back */
            if (rec->stickY[i] >= -(MENU_STICK_ON - 1) && D_800BED38[i].stickY < -(MENU_STICK_ON - 1)) {
                rec->padInput[i] |= 2;
            }
            if (rec->stickY[i] < MENU_STICK_ON && D_800BED38[i].stickY >= MENU_STICK_ON) {
                rec->padInput[i] |= 1;
            }
            if (rec->stickX[i] >= -(MENU_STICK_ON - 1) && D_800BED38[i].stickX < -(MENU_STICK_ON - 1)) {
                rec->padInput[i] |= 4;
            }
            if (rec->stickX[i] < MENU_STICK_ON && D_800BED38[i].stickX >= MENU_STICK_ON) {
                rec->padInput[i] |= 8;
            }
            if ((&D_800BED50)[i] & 0x1000) {
                rec->padInput[i] |= 0x10;
            }
            if ((&D_800BED50)[i] & 0x8000) {
                rec->padInput[i] |= 0x10;
            }
            if ((&D_800BED50)[i] & 0x4000) {
                rec->padInput[i] |= 0x20;
            }
            if ((&D_800BED50)[i] & 2) {
                rec->padInput[i] |= 0x40;
            }
            if ((&D_800BED50)[i] & 1) {
                rec->padInput[i] |= 0x80;
            }
            rec->stickY[i] = D_800BED38[i].stickY;
            rec->stickX[i] = D_800BED38[i].stickX;
        } else {
            rec->stickX[i] = 0;
            rec->stickY[i] = 0;
        }
        /* auto-repeat: a held stick forgets its last value after 0x33 ticks (then every 0x0B) */
        x = rec->stickX[i];
        if (x >= -(MENU_STICK_ON - 1) && x < MENU_STICK_ON) {
            rec->repeatX[i] = 0;
            D_8009017C &= ~(1 << i);
        } else if (!(D_8009017C & (1 << i))) {
            rec->repeatX[i] += D_800BE9E4;
            if (rec->repeatX[i] >= 0x33) {
                rec->repeatX[i] = 0x28;
                rec->stickX[i] = 0;
            }
        }
        x = rec->stickY[i];
        if (x >= -(MENU_STICK_ON - 1) && x < MENU_STICK_ON) {
            rec->repeatY[i] = 0;
        } else {
            rec->repeatY[i] += D_800BE9E4;
            if (rec->repeatY[i] >= 0x33) {
                rec->repeatY[i] = 0x28;
                rec->stickY[i] = 0;
            }
        }
    }
    rec = (MenuState *) D_80090174;
    rec->input = rec->padInput[0];

    if (D_800C35EA == 1) {
        /* attract mode: a button press ends the demo */
        D_800901C4 = 0;
        if (D_800E0EC0 < 0x546 && D_800BED50 != 0) {
            D_80090124 = 1;
        }
        return;
    }

    if (D_800902AC > 0) {
        t = (s16) (D_800902AC - D_800BE9E4);
        D_800902AC = t;
        if (t >= 0x33) {
            if (t >= 0x97) {
                a = 0xFF - (t - 0x96) * 8;
                if (a < 0) {
                    a = 0;
                }
            } else {
                a = (t - 0x32) * 8;
                if (a >= 0x100) {
                    a = 0xFF;
                }
                if (a == 0xFF && t >= 0x65) {
                    D_800902AC = 0x78;
                }
                if (((MenuState *) D_80090174)->input & 0x10) {
                    D_800902AC = 0x64;
                }
            }
            func_1504332C(0xFF, 0x32, 0x32, (a - (a >> 2)) & 0xFF);
            func_15042D94(0x94, 0xC0, 0x81, *(s32 *) ((u8 *) D_800E1008 + 0x23C));
        }
    }

    *(s32 *) ((u8 *) D_800DBFF0 + 0x2C) = 0x80000;
    func_1000E7A0(4, ((MenuState *) D_80090174)->menu);
    rec = (MenuState *) D_80090174;
    if (rec == NULL || (u8) D_80090144 < 5) {
        return;
    }
    rec->prevMainPage = rec->mainPage;
    rec = (MenuState *) D_80090174;
    a = (rec->fade - 0.5f) * 512.0f;
    if (a < 0) {
        a = 0;
    } else if (a >= 0x100) {
        a = 0xFF;
    }
    D_800E0EC4 = a;
    f = rec->fade;
    if (f >= 0.5f) {
        if (f < 1.0f) {
            rec->input &= ~0x10;
            rec = (MenuState *) D_80090174;
        }
        if (rec->menu == 0) {
            if (rec->titlePage != 1) {
                D_800902A4 = 0;
                D_800902A8 = 0;
            }
            switch (rec->titlePage) {
                case 1:
                    func_151DF6A4();
                    break;
                case 2:
                    func_151DFD0C();
                    break;
                case 3:
                case 4:
                case 5:
                    func_151E06D0();
                    break;
            }
        } else if (rec->menu == 1) {
            D_8008FDA8 = -1;
            switch ((u8) rec->mainPage) {
                case 0:
                    func_151E0BBC();
                    break;
                case 2:
                    func_151E1174();
                    break;
                case 3:
                    func_151E2A1C();
                    break;
                case 4:
                    func_151E1308();
                    break;
                case 1:
                    func_151E1EDC();
                    break;
                case 5:
                    func_151E19AC();
                    break;
            }
        }
    } else {
        /* page not shown yet: reset the menu input state */
        D_800E0EC6 = -1;
        D_800E0EC5 = 0xFF;
        rec->mainPage = 0;
        ((MenuState *) D_80090174)->x41 = 0;
        D_800901E0 = 1;
        D_800901E4 = 0;
        D_800901CC = 0;
        for (i = 1; i < 0x10; i++) {
            (&D_800901E4)[i] = -1;
        }
        for (i = 0; i < 0x10; i++) {
            D_800E1030[i] = 0;
        }
        D_800901D4 = 0;
        D_800901D8 = 0.0f;
        D_800901DC = 0.0f;
        D_80090188 = 0.0f;
        D_80090184 = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DEDD0.s")
#endif

#ifdef NON_MATCHING
extern u8 D_800ABBE4[]; /* "#": text id */
extern u8 D_800ABBE8[];
extern u8 D_800ABBEC[];
extern u8 D_800ABBF0[];
extern u8 D_800ABBF4[];
extern u8 D_800ABBF8[];
extern u8 D_800ABBFC[];
extern u8 D_800E0EC7;
extern s8 D_800BEE0C;
extern s8 D_800E1027;
extern s8 D_800E1028;
extern s8 D_800E102A;
extern s8 D_800E102B;
extern s8 D_800E1019;
struct216 *func_1507BB28(s32, u8);
void func_151E3AE4(s32, s32, s32, s32, s32);
void func_151E8648(void);
void func_1000DE1C(u8, s32);
s32 func_151F2CDC();

// title_press_start_page: title menu page 1 (Conker on the title screen, object 9). D_800E0EC6 != -1 runs a fade-out
// of the page alpha D_800E0EC5 (32 per tick); at 0 it toggles either the "info" screen D_800902A4 (playing Conker's
// animation 0xE / 0xF and a random voice 0xC8..0xC9 / 0xBE..0xC0) or, for 2, the screen-position screen D_800902A8;
// otherwise the alpha fades in. The plain page draws the title (func_151E3AE4) and handles accept (menu item 0x15 ->
// info, 0x19 -> screen position), left/right on item 9 (language: next voice bank), back (func_15007668). The info
// screen shows text 0x10 and reads the controller pak flags D_800E9D00 into D_800BEE0C; the screen-position screen
// moves the picture offset D_800E1010[0x17 / 0x18] with the stick and its scale [0x1A / 0x1B] with the C buttons.
void func_151DF6A4(void) {
    struct127 *obj;
    s32 v;
    s32 alpha;
    s32 voice;
    s8 x;
    s8 y;
    s8 sx;
    s8 sy;
    u16 in;

    obj = func_15083E90(9);
    if (D_800E0EC6 != (u8) -1) {
        v = D_800E0EC5 - (D_800BE9E4 << 5);
        if (v <= 0) {
            v = 0;
            if ((s8) D_800E0EC6 != 2) {
                D_800902A4 = !D_800902A4;
                if (!D_800902A4) {
                    voice = 0xE;
                    func_1001263C((func_150ADA20() & 1) + 0xC8, 0x7D00, 0x40);
                } else {
                    voice = 0xF;
                    func_1001263C((u32) func_150ADA20() % 3 + 0xBE, 0x7D00, 0x40);
                }
                if (obj != NULL) {
                    obj->unk232 = voice;
                    D_800D154C = obj;
                    D_800C3E78 = (s32) ((u8 *) obj - (u8 *) D_800CC2D0) / (s32) sizeof(struct127);
                    obj->unk218 = func_1507BB28(0, obj->unk232);
                    obj->unk21C = 0;
                    obj->unk201 = 0x14;
                }
            } else {
                D_800902A8 = !D_800902A8;
            }
            D_800E0EC6 = -1;
        }
        ((MenuState *) D_80090174)->input &= ~0x30;
    } else {
        v = D_800E0EC5 + (D_800BE9E4 << 5);
        if (v >= 0x100) {
            v = 0xFF;
        }
    }
    D_800E0EC5 = v;
    alpha = (D_800E0EC4 * v) >> 8;
    if (alpha >= 0xFE) {
        alpha = 0xFF;
    }

    if (!D_800902A4 && !D_800902A8) {
        func_151E3AE4(0x02200200, 0, 1, alpha & 0xFF, 1);
        if (D_800901D4 == 9 && (((MenuState *) D_80090174)->input & 0xC)) {
            func_151E8648();
            func_1000DE1C(D_800E0EC7, 0);
            D_800E0EC7 = func_1000EA94(D_800E1019);
        }
        in = ((MenuState *) D_80090174)->input;
        if ((in & 0x10) && D_80090188 == 0.0f) {
            if (D_800901D4 == 0x15) {
                D_800E0EC6 = 1;
                ((MenuState *) D_80090174)->input &= ~0x30;
                in = ((MenuState *) D_80090174)->input;
            } else if (D_800901D4 == 0x19) {
                D_800E0EC6 = 2;
                ((MenuState *) D_80090174)->input &= ~0x30;
                in = ((MenuState *) D_80090174)->input;
            }
        }
        if (in & 0x20) {
            func_15007668();
        }
    }

    if (obj != NULL) {
        if (func_151F2CDC() == 1) {
            if (obj->unk1FF == 0) {
                obj->unk1FF = 1;
            }
        } else {
            obj->unk1FF = 0;
        }
    }

    if (D_800902A4) {
        if (((MenuState *) D_80090174)->input & 0x20) {
            D_800E0EC6 = 1;
        }
        ((MenuState *) D_80090174)->input &= ~0x20;
        if (D_800902A4) {
            func_1504332C(0xFF, 0, 0, alpha & 0xFF);
            func_15042D94(0x94, 0x14, 0x81, (s32) D_800ABBE4, 0x10);
        }
        D_800BEE0C = 0;
        if (D_800E9D00 & 0x400000) {
            D_800BEE0C = 1;
        }
        if (D_800E9D00 & 0x800000) {
            D_800BEE0C = 2;
        }
    } else if (D_800902A8) {
        x = D_800E1010[0x17];
        y = D_800E1010[0x18];
        sx = D_800E1010[0x1A];
        sy = D_800E1010[0x1B];
        func_1504332C(0xFF, 0, 0, alpha & 0xFF);
        func_15042D94(0x94, 0x28, 0x81, (s32) D_800ABBE8, 0x3E);
        func_15042D94(0x94, 0x64, 0x81, (s32) D_800ABBEC, 0x1A);
        func_15042D94(0x7B, 0x64, 0x81, (s32) D_800ABBF0, 0x3B);
        func_15042D94(0xAD, 0x64, 0x81, (s32) D_800ABBF4, 0x3C);
        func_15042D94(0x94, 0x4B, 0x81, (s32) D_800ABBF8, 0x5D);
        func_15042D94(0x94, 0x7D, 0x81, (s32) D_800ABBFC, 0x5E);
        in = ((MenuState *) D_80090174)->input;
        if ((in & 4) && x > 0) {
            x--;
        }
        if ((in & 8) && x < 0x20) {
            x++;
        }
        if ((in & 1) && y > 0) {
            y--;
        }
        if ((in & 2) && y < 0x10) {
            y++;
        }
        if ((D_800BED50 & 2) && sx > 0) {
            sx--;
        }
        if ((D_800BED50 & 1) && sx < 0x10) {
            sx++;
        }
        if ((D_800BED50 & 8) && sy > 0) {
            sy--;
        }
        if ((D_800BED50 & 4) && sy < 0x10) {
            sy++;
        }
        D_800E102A = sx;
        D_800E102B = sy;
        D_800E1027 = x;
        D_800E1028 = y;
        if (((MenuState *) D_80090174)->input & 0x20) {
            D_800E0EC6 = 2;
        }
        ((MenuState *) D_80090174)->input &= ~0x20;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DF6A4.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DFD0C.s")

#ifdef NON_MATCHING
extern u8 D_800ABC10[]; /* "%d" */
extern u8 D_800ABC14[]; /* "%d:%02d:%02d" */
extern u8 D_800ABC24[]; /* "#": text id */
extern u8 D_800ABC28[];
extern u8 D_800ABC2C[];
extern u8 D_800ABC30[];
extern u8 D_800ABC34[];
extern u8 D_800ABC38[];
extern u8 D_800ABC3C[];
extern s32 D_800BE804;
extern s32 *D_800E0EB8;
void func_151E3A1C(void);
void func_15042E3C(s32, ...);

// title_slot_page: title menu pages 3..5 = save slot 0..2 (rec->titlePage - 3). Draws the slot in its colour (slot 2
// red, 1 green, 0 blue) with its score ("%d"; 0x7D00 is shown as 1000000 at 0.75 scale) and play time (h:mm:ss), then
// the options: a used slot offers continue / erase (D_800901CC 0 / 1, left-right toggles), erase asks no / yes
// (D_800901CC 2 / 3); an empty slot (+8 == -1) only offers "start" (text 0x31). Accept on 0 starts the game: mode 7
// (fade) with the callback func_151E3A1C, D_8008FDA8 = slot, func_150076BC(slot +0xE); accept on "yes" erases the slot
// (func_15007750, func_15017790, slot marked empty, D_80090144 = 0 re-runs the menu setup). Plays sound 0x62D on a
// move, 0x500 on accept.
void func_151E06D0(void) {
    MenuState *rec;
    struct_eu_BE818 *save;
    u8 alpha;
    s32 slot;
    s32 sfx;
    s32 sel;
    u32 v;
    s32 y;
    u16 in;

    alpha = D_800E0EC4;
    rec = (MenuState *) D_80090174;
    sfx = 0;
    slot = rec->titlePage - 3;
    sel = (s8) D_800901CC;
    if (sel < 2) {
        if (rec->input & 0xC) {
            D_800901CC = 1 - sel;
            sfx = 0x62D;
        }
    } else if (rec->input & 0xC) {
        D_800901CC = 5 - sel;
        sfx = 0x62D;
    }
    func_150432FC(0x94, 0x46);
    save = &D_800BE818[slot];
    if (save->unk8 == -1) {
        D_800901CC = 0;
    }
    if (slot == 2) {
        func_1504332C(0xFF, 0x37, 0x37, alpha);
    } else if (slot == 1) {
        func_1504332C(0x78, 0xFF, 0x16, alpha);
    } else {
        func_1504332C(0x20, 0x55, 0xFF, alpha);
    }
    if (save->unk8 != -1) {
        v = ((u32 *) save)[1];
        y = 0;
        if (v == 0x7D00) {
            v = 1000000;
            func_150432BC(0.75f);
            y = 2;
        }
        func_15042D94(0x70, y + 0x33, 0, (s32) D_800ABC10, v);
        func_150432BC(1.0f);
        v = ((u32 *) save)[0];
        func_15042D94(0xA4, 0x33, 0, (s32) D_800ABC14, v / 60 / 60, v / 60 % 60, v % 60);
    }
    func_1504332C(0xFF, 0xFF, 0xFF, alpha);
    if (save->unk8 >= 0) {
        func_15042D94(0x94, 0xAF, 1, (s32) D_800ABC24, 0x1A);
        func_150432FC(0x58, 0xAF);
        sel = (s8) D_800901CC;
        if (sel < 2) {
            func_15042E3C((s32) D_800ABC28, (sel == 0) + 0x16, 1);
        } else {
            func_15042D94(0x94, 0x91, 1, (s32) D_800ABC2C, 0x19);
        }
    } else {
        func_15042D94(0x94, 0x6E, 1, (s32) D_800ABC30, 0x31);
    }
    func_150432FC(0xD0, 0xAF);
    sel = (s8) D_800901CC;
    if (sel < 2) {
        if (save->unk8 >= 0) {
            func_15042E3C((s32) D_800ABC34, (sel != 0) + 0x18, 1);
            sel = (s8) D_800901CC;
        }
        if (sel == 0) {
            if (((MenuState *) D_80090174)->input & 0x10) {
                D_800E0B94 = 7;
                D_800E0EB8 = (s32 *) func_151E3A1C;
                D_80090114 = 3;
                D_8008FDA8 = slot;
                D_800BE7FC = -1;
                D_80082F50 = 0;
                func_150076BC(save->unkE);
                sfx = 0x500;
            }
        } else if (((MenuState *) D_80090174)->input & 0x10) {
            D_800901CC = 2;
            sfx = 0x500;
        }
    } else {
        func_15042D94(0x6C, 0xAF, 1, (s32) D_800ABC38, (sel == 3) + 0x1F);
        func_15042D94(0xBC, 0xAF, 1, (s32) D_800ABC3C, ((s8) D_800901CC == 2) + 0x1D);
        rec = (MenuState *) D_80090174;
        in = rec->input;
        if (in & 0x10) {
            if ((s8) D_800901CC == 3) {
                D_800901CC = 0;
                func_15007750(slot);
                D_800BE3DF = 0x29;
                D_800BE800 = 0;
                D_800BE804 = 0;
                func_15017790();
                save->padC[0] = 0x18;
                ((u32 *) save)[1] = 0;
                save->unk8 = -1;
                rec = (MenuState *) D_80090174;
                D_80090144 = 0;
            } else {
                D_800901CC = 1;
            }
            sfx = 0x500;
        } else if (in & 0x20) {
            D_800901CC = 1;
        }
        rec->input &= ~0x20;
    }
    if (sfx != 0) {
        func_10010F30(sfx, 0x4650, 0x40, 0, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E06D0.s")
#endif

#ifdef NON_MATCHING
void func_151E2A54(void);
extern s8 D_80090164;
extern s8 D_80090180;
extern s8 D_80090140;
extern u8 D_800E0FBC;
extern s8 D_800ABA70[][10];
extern s8 D_80090248[];         /* main menu: items per page group (titlePage 1..) */
extern s8 D_80090270[];         /* s8 per 4 bytes: setting for the negative mode codes */
extern s8 D_800E0FC0[];
extern u8 D_800ABC40[];         /* "#": text id */
extern u8 D_800ABC44[];
extern u8 D_800ABC48[];
// menu_mode_select_page: main menu page 0, the mode list of the page group rec->titlePage (D_80090248[group - 1]
// rows of D_800ABA70 starting after the earlier groups). The page alpha D_800E0EC5 fades in (8 per frame step) or,
// with a pending page change D_800E0EC6, out; at 0 the page switches (mainPage = D_800E0EC6, page 2 resets
// D_80090180 / D_8009017C / D_800901D4, func_151E2A54) and returns. Left / right toggles the yes / no cursor
// D_800901CC; up / down moves the row x41 (wrapping, sound 0x62D; a 5-row group slides with D_80090188 instead of
// drawing the rows). x42 = global row. Accept: on "yes" saves x41 in D_800E1010[0], D_800E0FC0 from the row's mode
// code (D_80090270 for codes < 0), D_800901E0 = 1, page change 4; on "no" page change 2.
void func_151E0BBC(void) {
    MenuState *rec;
    s32 alpha;
    s32 textAlpha;
    s32 v;
    s32 n;
    s32 row;
    s32 first;
    s32 i;
    s16 x;
    s16 id;
    s8 *tab;
    f32 step;
    s8 code;

    rec = (MenuState *) D_80090174;
    if (rec->titlePage == 0) {
        return;
    }
    alpha = D_800E0EC4;
    if ((s8) D_800E0EC6 != -1) {
        rec->input &= ~0x20;
        v = D_800E0EC5 - (D_800BE9E4 << 5);
        if (v <= 0) {
            D_800E0EC5 = 0;
            ((MenuState *) D_80090174)->mainPage = D_800E0EC6;
            if ((s8) D_800E0EC6 == 2) {
                D_80090180 = 0;
                D_8009017C = 1;
                D_800901D4 = 0;
            }
            func_151E2A54();
            D_800E0EC6 = -1;
            return;
        }
        D_800E0EC5 = v;
        if ((s8) D_800E0EC6 != 2) {
            alpha = v & 0xFF;
        }
        textAlpha = v & 0xFF;
        rec = (MenuState *) D_80090174;
    } else {
        v = D_800E0EC5 + (D_800BE9E4 << 5);
        if (v >= 0x100) {
            v = 0xFF;
        }
        D_800E0EC5 = v;
        textAlpha = (s32) (D_800E0EC4 * v) >> 8;
        if (textAlpha >= 0xFE) {
            textAlpha = 0xFF;
        }
    }
    D_80090140 = 0;
    D_80090164 = 0;
    D_800E0FBC = 0;
    n = D_80090248[rec->titlePage - 1];
    if (rec->input & 0xC) {
        D_800901CC = 1 - (s8) D_800901CC;
        func_10010F30(0x62D, 0x4650, 0x40, 0, 0);
    }
    func_1504332C(0xFF, 0xFF, 0xFF, alpha);
    func_15042D94(0x94, 0x7E, 1, (s32) D_800ABC40, 0x1A);
    func_1504332C(0xFF, 0xFF, 0xFF, textAlpha);
    func_15042D94(0xD5, 0x7E, 1, (s32) D_800ABC44, ((s8) D_800901CC == 1) + 0x1B);
    if (textAlpha == 0xFF && (s8) D_800901CC == 0 && (n != 5 || D_80090188 == 0.0f)) {
        rec = (MenuState *) D_80090174;
        if (rec->input & 1) {
            D_80090188 = 1.0f;
            rec->x41--;
            func_10010F30(0x62D, 0x4650, 0x40, 0, 0);
        } else if (rec->input & 2) {
            D_80090188 = -1.0f;
            rec->x41++;
            func_10010F30(0x62D, 0x4650, 0x40, 0, 0);
        }
    }
    rec = (MenuState *) D_80090174;
    if (rec->x41 < 0) {
        rec->x41 += n;
    }
    rec = (MenuState *) D_80090174;
    if (rec->x41 >= n) {
        rec->x41 -= n;
    }
    rec = (MenuState *) D_80090174;
    row = rec->x41;
    first = 0;
    for (i = 0; i < rec->titlePage - 1; i++) {
        first += D_80090248[i];
    }
    rec->x42 = row + first;
    if (n != 5) {
        x = 0x8C - ((n * 0x1C) >> 1);
        tab = D_800ABA70[first];
        for (i = 0; i < n; i++) {
            func_150432FC(0x53, x);
            id = *(s16 *) tab;
            if (i == row && (s8) D_800901CC == 0) {
                id++;
            }
            func_15042E3C((s32) D_800ABC48, id);
            tab += 10;
            x += 0x1C;
        }
    } else {
        step = D_800BE9E4 * 0.05f;
        if (D_80090188 < 0.0f) {
            D_80090188 += step;
            if (D_80090188 > 0.0f) {
                D_80090188 = 0.0f;
            }
        } else if (D_80090188 > 0.0f) {
            D_80090188 -= step;
            if (D_80090188 < 0.0f) {
                D_80090188 = 0.0f;
            }
        }
        if ((s8) D_800901CC == 0 && D_80090188 != 0.0f) {
            ((MenuState *) D_80090174)->input &= ~0x10;
        }
    }
    if (textAlpha != 0xFF) {
        return;
    }
    rec = (MenuState *) D_80090174;
    if (!(rec->input & 0x10)) {
        return;
    }
    rec->input &= ~0x20;
    if ((s8) D_800901CC == 0) {
        D_800E0EC6 = 4;
        rec = (MenuState *) D_80090174;
        D_800E1010[0] = rec->x41;
        code = D_800ABA70[rec->x42][5];
        if (code < 0) {
            D_800E0FC0[0] = D_80090270[(-1 - code) * 4];
        } else {
            D_800E0FC0[0] = 0;
        }
        D_800901E0 = 1;
    } else {
        D_800E0EC6 = 2;
        ((MenuState *) D_80090174)->input &= ~0x20;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E0BBC.s")
#endif

#ifdef NON_MATCHING
void func_15042D78(u8);
void func_151E2B9C(void);
void func_151E3AE4(s32, s32, s32, s32, s32);
extern s8 D_80090180;
extern s32 D_800ABA74;            /* s8 table, per save slot (rows of 10): settings set (declared s32 in the TU) */
extern s32 D_800ABB38[];        /* settings set -> item mask for func_151E3AE4 */
extern u8 D_800ABC4C[];         /* "#" */

// main_settings_page: main menu page 2, the settings list of the current slot (rec->x42): title text 0x1A, the ring
// list func_151E3AE4 with its own alpha D_800E0EC5 (fades in by 32 per tick; back (0x20) starts the fade-out,
// D_800E0EC6 = 0). At the end of the fade-out it leaves the page (mainPage 0) and saves the settings (func_151E2B9C)
// when they changed (D_80090180).
void func_151E1174(void) {
    MenuState *rec;
    s32 mask;
    s32 alpha;

    func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
    func_15042D94(0x94, 0x7E, 1, (s32) D_800ABC4C, 0x1A);
    func_15042D78(0x81);
    rec = (MenuState *) D_80090174;
    mask = D_800ABB38[((s8 *) &D_800ABA74)[rec->x42 * 10]];
    if ((s8) D_800E0EC6 == 0) {
        rec->input &= ~0x20;
        alpha = D_800E0EC5 - (D_800BE9E4 << 5);
        if (alpha <= 0) {
            ((MenuState *) D_80090174)->mainPage = 0;
            if (D_80090180 != 0) {
                func_151E2B9C();
            }
            D_80090180 = 0;
            D_800E0EC6 = -1;
            return;
        }
        D_800E0EC5 = alpha;
    } else {
        alpha = D_800E0EC5 + (D_800BE9E4 << 5);
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        D_800E0EC5 = alpha;
    }
    if (alpha != 0xFF) {
        ((MenuState *) D_80090174)->input = 0;
    }
    func_151E3AE4(mask, 1, 0, alpha & 0xFF, 0);
    rec = (MenuState *) D_80090174;
    if (rec->input & 0x20) {
        D_800E0EC6 = 0;
    }
    rec->input &= ~0x20;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1174.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1308.s")

#ifdef NON_MATCHING
void func_15042E3C(s32, ...);
void func_151E2FCC(void);
void func_151E4A78(void);
extern s8 D_80090140;           /* first queue slot shown / number of extra slots */
extern s8 D_8009028F;           /* (s8 table, indexed backwards by the slot's mode) */
extern s8 D_800ABA75;           /* s8 table, per save slot (rows of 10): byte 1 */
extern u8 D_800ABA76[][10];
extern s8 D_800ABB30;           /* rows of 4 bytes: max players per player count */
extern s32 *D_800E0EB8;         /* callback run when the menu fade-out ends */
extern u8 D_800ABC54[];         /* "#" */
extern u8 D_800ABC58[];         /* "#" */
extern u8 D_800ABC5C[];         /* "#" */

// main_players_page: main menu page 5, the player / controller queue (D_800901E4[16], D_800901E0 controllers joined).
// Fades the page alpha D_800E0EC5 in (32 per tick) or, while D_800E0EC6 != -1, out and then switches to mainPage =
// D_800E0EC6. Each joined controller's up / right (9) adds and down / left (6) removes a slot (D_80090140, with a
// click sound), limited by the slot table D_800ABB30; slots after the controllers are -2 ("open") and the rest of the
// queue -1. Accept at full alpha starts the game (mode 7 fade, D_80090114 = 8, callback func_151E2FCC or
// func_151E4A78); back fades out to page 4. Draws the title text 0x1A and one entry per slot (controller n + 1 or
// text 5).
void func_151E19AC(void) {
    MenuState *rec;
    s32 alpha;
    s32 joined;
    s32 slots;
    s32 i;
    s16 x;

    if ((s8) D_800E0EC6 != -1) {
        rec = (MenuState *) D_80090174;
        rec->input &= ~0x20;
        alpha = D_800E0EC5 - (D_800BE9E4 << 5);
        if (alpha <= 0) {
            D_800E0EC5 = 0;
            ((MenuState *) D_80090174)->mainPage = D_800E0EC6;
            D_800E0EC6 = -1;
            return;
        }
        D_800E0EC5 = alpha;
    } else {
        alpha = D_800E0EC5 + (D_800BE9E4 << 5);
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        D_800E0EC5 = alpha;
    }
    func_1504332C(0xFF, 0xFF, 0xFF, alpha & 0xFF);

    joined = D_800901E0;
    rec = (MenuState *) D_80090174;
    slots = ((s8 *) &D_800ABB30)[(&D_8009028F)[-(&D_800ABA75)[rec->x42 * 10]] * 4 + joined - 1];
    for (i = 0; i < joined; i++) {
        if ((&D_800901E4)[i] >= 0) {
            if (((MenuState *) D_80090174)->padInput[(&D_800901E4)[i]] & 9) {
                D_80090140++;
                if (slots >= joined + D_80090140) {
                    func_10010F30(0x4FF, 0x4650, 0x40, 0, 0);
                }
            }
            if (((MenuState *) D_80090174)->padInput[(&D_800901E4)[i]] & 6) {
                D_80090140--;
                if (D_80090140 >= 0) {
                    func_10010F30(0x4FF, 0x4650, 0x40, 0, 0);
                }
            }
            joined = D_800901E0;
            if (D_80090140 < 0) {
                D_80090140 = 0;
            }
        }
    }
    if (slots < joined + D_80090140) {
        D_80090140 = slots - joined;
    }
    slots = joined + D_80090140;
    if (slots < 2) {
        slots = 2;
    }
    D_80090140 = slots - joined;
    for (i = joined; i < slots; i++) {
        (&D_800901E4)[i] = -2;
        D_800E1030[i] = 0;
    }
    for (i = slots; i < 0x10; i++) {
        (&D_800901E4)[i] = -1;
    }

    if (alpha == 0xFF && (((MenuState *) D_80090174)->input & 0x10)) {
        D_800E0B94 = 7;
        D_80090114 = 8;
        func_10010F30(0x500, 0x7D00, 0x40, 0, 0);
        if ((s8) D_800ABA76[((MenuState *) D_80090174)->x42][0] == -1) {
            D_800E0EB8 = (s32 *) func_151E2FCC;
        } else {
            D_800E0EB8 = (s32 *) func_151E4A78;
        }
    }
    func_15042D94(0x94, 0x55, 1, (s32) D_800ABC54, 0x1A);
    x = 0xA1 - D_800901E0 * 13 - D_80090140 * 10;
    for (i = 0; i < slots; i++) {
        func_150432FC(x, 0x82);
        if ((&D_800901E4)[i] >= 0) {
            func_15042E3C((s32) D_800ABC58, (&D_800901E4)[i] + 1);
            x += 0x1A;
        } else {
            func_15042E3C((s32) D_800ABC5C, 5);
            x += 0x14;
        }
    }
    if (alpha == 0xFF && (((MenuState *) D_80090174)->input & 0x20)) {
        D_800E0EC6 = 4;
    }
    ((MenuState *) D_80090174)->input &= ~0x20;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E19AC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1EDC.s")

void func_151E5AB8(void);
void func_151E4B40(void);

void func_151E2A1C(void) {
    D_80090120 = 3;
    func_151E5AB8();
    func_151E4B40();
    D_80090120 = 0;
}

#ifdef NON_MATCHING
void func_151DDF6C(void); /* P85: takes no arguments (the asm reads none) */
extern s32 D_80082F4C;
extern s32 D_800ABA74;

void func_151E2A54(void) {
    s8 temp_a1;
    u8 var_v1;
    u8 *temp_v0;

    temp_a1 = *(s8 *)((u8 *)&D_800ABA74 + *(s8 *)((u8 *)D_80090174 + 0x42) * 0xA);
    temp_v0 = (temp_a1 * 0xA) + D_80082F4C;
    var_v1 = (*(u8 *)((u8 *)temp_v0 + 3));
    if ((s32) var_v1 >= 5) {
        (*(u8 *)((u8 *)temp_v0 + 3)) = 4U;
        var_v1 = 4 & 0xFF;
    }
    if ((s32) var_v1 < 0) {
        (*(u8 *)((u8 *)temp_v0 + 3)) = 0U;
    }
    if ((*(s8 *)((u8 *)temp_v0 + 1)) <= 0) {
        (*(s8 *)((u8 *)temp_v0 + 1)) = 1;
    }
    (*(s8 *)((u8 *)D_800E1010 + 2)) = (*(s8 *)((u8 *)temp_v0 + 1));
    (*(s8 *)((u8 *)D_800E1010 + 0xB)) = 0;
    (*(s8 *)((u8 *)D_800E1010 + 3)) = (s8) (*(s8 *)((u8 *)temp_v0 + 2));
    (*(u8 *)((u8 *)D_800E1010 + 0x10)) = (u8) (*(u8 *)((u8 *)temp_v0 + 3));
    (*(u8 *)((u8 *)D_800E1010 + 0x11)) = (u8) (*(u8 *)((u8 *)temp_v0 + 4));
    if (temp_a1 == 0) {
        (*(u8 *)((u8 *)D_800E1010 + 4)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
    } else if (temp_a1 == 1 || temp_a1 == 2) {
        (*(u8 *)((u8 *)D_800E1010 + 0xD)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
        (*(u8 *)((u8 *)D_800E1010 + 0xE)) = (u8) (*(u8 *)((u8 *)temp_v0 + 6));
    } else if (temp_a1 == 7) {
        (*(u8 *)((u8 *)D_800E1010 + 0x12)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
    } else if (temp_a1 == 5) {
        (*(u8 *)((u8 *)D_800E1010 + 0x11)) = 0U;
        (*(u8 *)((u8 *)D_800E1010 + 0x12)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
    } else if (temp_a1 == 8 || temp_a1 == 9) {
        (*(u8 *)((u8 *)D_800E1010 + 7)) = (u8) (*(u8 *)((u8 *)temp_v0 + 5));
        (*(u8 *)((u8 *)D_800E1010 + 0x11)) = 1U;
        (*(s8 *)((u8 *)D_800E1010 + 3)) = 2;
        (*(u8 *)((u8 *)D_800E1010 + 0x13)) = (u8) (*(u8 *)((u8 *)temp_v0 + 6));
    }
    (*(u8 *)((u8 *)D_800E1010 + 0x16)) = (u8) (*(u8 *)((u8 *)temp_v0 + 8));
    (*(u8 *)((u8 *)D_800E1010 + 6)) = (u8) (*(u8 *)((u8 *)temp_v0 + 9));
    func_151DDF6C();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2A54.s")
#endif
#ifdef NON_MATCHING
// settings_save: P127: the inverse of func_151E2A54: copies the settings bytes D_800E1010 into the 10-byte save
// record of the menu's settings set (D_800ABA74 row of the save slot x42; record D_80082F4C + set * 10): byte 0
// cleared, 1..4 = settings 2, 3, 0x10, 0x11, the set-specific bytes 5 / 6 (set 0: 4; sets 1, 2: 0xD, 0xE; sets 5, 7:
// 0x12; sets 8, 9: 7, 0x13; others none), 8 = 0x16, 9 = 6, then writes the save (func_150076A0).
void func_151E2B9C(void) {
    s32 set;
    s8 *rec;

    set = ((s8 *) &D_800ABA74)[((MenuState *) D_80090174)->x42 * 10];
    rec = (s8 *) D_80082F4C + set * 10;
    rec[0] = 0;
    rec[1] = D_800E1010[2];
    rec[2] = D_800E1010[3];
    rec[3] = D_800E1010[0x10];
    rec[4] = D_800E1010[0x11];
    switch (set) {
        case 0:
            rec[5] = D_800E1010[4];
            break;
        case 1:
        case 2:
            rec[5] = D_800E1010[0xD];
            rec[6] = D_800E1010[0xE];
            break;
        case 5:
        case 7:
            rec[5] = D_800E1010[0x12];
            break;
        case 8:
        case 9:
            rec[5] = D_800E1010[7];
            rec[6] = D_800E1010[0x13];
            break;
    }
    rec[8] = D_800E1010[0x16];
    rec[9] = D_800E1010[6];
    func_150076A0();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2B9C.s")
#endif

#ifdef NON_MATCHING
extern s8 D_800901E4;
extern s32 D_800901E8;
extern s32 D_800ABA78;
extern u8 D_800BEB60;
extern s32 D_800E0FFE;
extern s8 D_800E101E;

s8 func_151E2C88(s32 arg0) {
    struct {
        s8 u28;
        u8 pad29[0x3];
        s8 u2C;
        u8 pad2D[0x3];
        s32 u30;
        u8 pad34[0xC];
    } sp;
    s32 temp_a1;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t5;
    s32 var_a2;
    s32 var_a2_3;
    s32 var_a2_4;
    s32 var_a3;
    s32 var_a3_5;
    s8 *var_a2_2;
    s8 *var_a3_2;
    s8 *var_a3_3;
    s8 *var_t0;
    s8 *var_t0_2;
    s8 *var_t0_3;
    s8 *var_t0_4;
    s8 *var_t0_5;
    s8 *var_t0_6;
    s8 *var_t2;
    s8 *var_t2_2;
    s8 *var_t3;
    s8 *var_t3_2;
    s8 temp_a3;
    s8 temp_t6;
    s8 temp_t6_2;
    s8 temp_t9;
    s8 temp_t9_2;
    s8 var_a2_5;
    s8 var_a3_4;
    s8 var_v1;

    if (arg0 == 0) {
        (*(s8 *)((u8 *)(&D_800E0FFE) + 0)) = 0;
        (*(s8 *)((u8 *)(&D_800E0FFE) + 1)) = 0;
    }
    if (*(&D_800ABA78 + ((*(s8 *)((u8 *)D_80090174 + 0x42)) * 0xA)) == 8) {
        var_a2 = 0;
        var_v1 = 0;
        var_t0 = &sp.u2C;
        if (D_800E101E != 0) {
            do {
                var_t0 += 1;
                (*(s8 *)((u8 *)var_t0 + -1)) = 0;
            } while ((u32) var_t0 < (u32) &sp.u30);
            var_t0_2 = &D_800901E4;
            do {
                temp_a3 = *var_t0_2;
                var_t0_2 += 1;
                if (temp_a3 >= 0) {
                    var_v1 += 1;
                    (&sp.u2C)[temp_a3] = 1;
                    var_a2 = (var_a2 | (1 << temp_a3)) & 0xFF;
                }
            } while ((u32) var_t0_2 < (u32) &D_800901E8);
            if (var_v1 < 3) {
                var_a3 = 0;
                if (D_800BEB60 & ~var_a2 & 0xFF) {
                    var_a2_2 = &sp.u28;
                    do {
                        *var_a2_2 = 1;
                        if ((var_v1 == 1) && !(D_800BEB60 & (1 << var_a3))) {
                            *var_a2_2 = 0;
                        }
                        var_a3 += 1;
                        var_a2_2 += 1;
                    } while (var_a3 < 4);
                    var_a2_3 = 0;
                    if (arg0 == 0) {
                        temp_a1 = var_v1 * 2;
                        var_a2_4 = 0x10;
                        if (temp_a1 < 0x11) {
                            temp_t5 = -((0x11 - temp_a1) & 3);
                            if (temp_t5 != 0) {
                                temp_t1 = 0x10 - var_v1;
                                var_t2 = D_800E1030 + 0x10;
                                var_t3 = &D_800E1030[temp_t1];
                                var_t0_3 = &(&D_800901E4)[temp_t1];
                                var_a3_2 = &D_800901E4 + 0x10;
                                do {
                                    temp_t9 = *var_t0_3;
                                    temp_t6 = *var_t3;
                                    var_a2_4 -= 1;
                                    var_a3_2 -= 1;
                                    var_t0_3 -= 1;
                                    var_t2 -= 1;
                                    var_t3 -= 1;
                                    (*(s8 *)((u8 *)var_a3_2 + 1)) = temp_t9;
                                    (*(s8 *)((u8 *)var_t2 + 1)) = temp_t6;
                                } while ((temp_t5 + 0x10) != var_a2_4);
                                if ((var_a2_4 + 1) != temp_a1) {
                                    goto block_23;
                                }
                            } else {
block_23:
                                temp_t1_2 = var_a2_4 - var_v1;
                                var_t0_4 = &(&D_800901E4)[temp_t1_2];
                                var_t3_2 = &D_800E1030[temp_t1_2];
                                var_a3_3 = &(&D_800901E4)[var_a2_4];
                                var_t2_2 = &D_800E1030[var_a2_4];
                                do {
                                    var_t2_2 -= 4;
                                    *var_a3_3 = (*(s8 *)((u8 *)var_t0_4 + 0));
                                    (*(s8 *)((u8 *)var_t2_2 + 4)) = (s8) (*(s8 *)((u8 *)var_t3_2 + 0));
                                    var_a3_3 -= 4;
                                    (*(s8 *)((u8 *)var_t2_2 + 3)) = (s8) (*(s8 *)((u8 *)var_t3_2 + -1));
                                    (*(s8 *)((u8 *)var_a3_3 + 3)) = (s8) (*(s8 *)((u8 *)var_t0_4 + -1));
                                    temp_t6_2 = (*(s8 *)((u8 *)var_t0_4 + -2));
                                    var_t0_4 -= 4;
                                    (*(s8 *)((u8 *)var_a3_3 + 2)) = temp_t6_2;
                                    (*(s8 *)((u8 *)var_t2_2 + 2)) = (s8) (*(s8 *)((u8 *)var_t3_2 + -2));
                                    temp_t9_2 = (*(s8 *)((u8 *)var_t3_2 + -3));
                                    var_t3_2 -= 4;
                                    (*(s8 *)((u8 *)var_t2_2 + 1)) = temp_t9_2;
                                    (*(s8 *)((u8 *)var_a3_3 + 1)) = (s8) (*(s8 *)((u8 *)var_t0_4 + 1));
                                } while (var_t2_2 != (temp_a1 - 1 + D_800E1030));
                            }
                        }
                        var_a2_5 = var_v1;
                        var_a3_4 = 0;
                        if (var_v1 < temp_a1) {
                            var_t0_5 = &sp.u2C;
loop_27:
                            if (*var_t0_5 == 0) {
                                temp_t1_3 = var_a2_5 - var_v1;
                                if ((&sp.u28)[var_a3_4] != 0) {
                                    (&D_800901E4)[var_a2_5] = var_a3_4;
                                    D_800E1030[var_a2_5] = D_800E1030[temp_t1_3];
                                    *(&D_800E0FFE + temp_t1_3) = var_a2_5;
                                    D_80087270[var_a2_5] = 0xA;
                                    var_a2_5 += 1;
                                }
                            }
                            var_a3_4 += 1;
                            var_t0_5 += 1;
                            if (var_a3_4 < 4) {
                                if (var_a2_5 >= temp_a1) {
                                    return var_v1;
                                }
                                goto loop_27;
                            }
                            goto block_40;
                        }
                        goto block_40;
                    }
                    var_a3_5 = 0;
                    if (var_v1 > 0) {
                        var_t0_6 = &sp.u2C;
loop_35:
                        if ((*var_t0_6 == 0) && ((&sp.u28)[var_a3_5] != 0)) {
                            *(s32 *)(arg0 + (var_a2_3 * 4)) = var_a3_5;
                            var_a2_3 += 1;
                        }
                        var_a3_5 += 1;
                        var_t0_6 += 1;
                        if ((var_a3_5 < 4) && (var_a2_3 < var_v1)) {
                            goto loop_35;
                        }
                    }
block_40:
                    return var_v1;
                }
            }
            goto block_41;
        }
    }
block_41:
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2C88.s")
#endif
#ifdef NON_MATCHING
extern s8 D_800ABA70[][10];     /* menu modes (rows of 10, by MenuState x42) */
extern u16 D_80090160;
extern s16 D_8009015C;
extern s8 D_800D27C8;
extern s32 D_800ABB38[];
extern u8 D_800E0FC9;
extern s8 D_80090134;
extern s8 D_800BEA38;
extern u8 D_800D3260;
extern s8 D_80090110;
extern s8 D_800901E4;           /* first of the 16-byte player queue */
extern s32 D_800BE804;
s8 func_151E2C88(s32);
void func_151E86A4(void);
void func_1501C710(s32, s32, s32, s32, s32);
extern s8 D_8009013C;            /* set: drop the first D_80090110 queue entries on the next start */
extern s32 D_80090118;           /* time limit (settings byte 3 * 3000) or 0 */
extern s8 D_800E1000;
extern s8 D_800D2550;
extern s8 D_80087608;
extern s8 D_80090128;            /* player count (queue entries) */
extern u8 D_800E0FBC;
extern s8 D_800E0FC0[];
extern u8 D_800AB95C[][8];
extern u8 D_800E0ED8;
extern u8 D_800E0FE8[];
extern s8 D_800E0EDA;
extern s8 D_800E0ED9;
extern s8 D_800E0EE0[16];
extern s8 D_800E0EF0[16];
extern u8 D_800E0F00[];
extern s16 D_800E1040[2];
extern s32 D_800E1048[2];
extern s16 D_800E0ED0[2];
extern s8 D_800E1050;
extern s8 D_8009011C;
extern s8 D_800902E7[];          /* player count -> argument of func_1501C710 */
extern s16 D_800ABB60[];         /* settings set -> D_80090160 flags */
extern s16 D_800ABB74[];         /* settings set -> D_8009015C flags */

// menu_game_start: P127: start callback of the main menu: applies the settings of the chosen mode (D_800ABA70 row
// x42: +2 level, +4 settings set, +5 < 0 = fill free slots, +8 slot type): drops the first D_80090110 entries of the
// player queue (D_800901E4 / D_800E1030) when D_8009013C asks for it, clears the menu / game state, sets the game
// flags D_80090160 / D_8009015C from the set's tables and the settings bytes D_800E1010 (time limit D_80090118 =
// byte 3 * 3000, D_800D27C8, D_800E1000, D_80087260 / D_80087608), counts the players (D_80090128, slot mask), fills
// the 16 slot types D_80087270 (mode 8: func_151E2C88; else character records / per-mode rules), assigns free slot
// numbers when +5 < 0, resets D_800E0EE0 / D_800E0EF0 / D_800E1040.. and starts the game: func_1501C710(6, level, 0,
// D_800902E7[players], slot mask).
void func_151E2FCC(void) {
    s8 *rec;
    s32 flags;
    s32 level;
    s32 mask;
    s32 n;
    s32 i;
    s32 used;
    s32 next;
    s8 *slot;

    rec = D_800ABA70[((MenuState *) D_80090174)->x42];
    if (D_800E1010[3] < 3) {
        D_800E1010[3] = 0;
    }
    if (D_8009013C != 0) {
        n = D_80090110;
        if (n != 0 && n < 16 - n) {
            for (i = n; i < 16 - n; i++) {
                (&D_800901E4)[i] = (&D_800901E4)[i + n];
                D_800E1030[i] = D_800E1030[i + n];
            }
        }
    }
    D_8009013C = 0;
    D_80090110 = 0;
    func_15017790();
    D_800BE804 = 0;
    bzero(D_80090174 + 0x66, 0x30);
    bzero(D_80090174 + 0x46, 0x20);
    bzero(D_800E0F00, 0x20);
    D_800BEAC1 = 0;
    D_800BEAC0 = 0;
    D_800E0B94 = 0;
    D_8008FDA8 = -1;
    D_800843F0[1] = 0xFF;
    D_800843F0[2] = 0xFF;
    D_800843F0[3] = 0xFF;

    level = *(s16 *) (rec + 2);
    D_80090168 = rec[5] < 0;
    flags = D_800ABB38[rec[4]];
    D_80090160 = D_800ABB60[rec[4]];
    D_8009015C = D_800ABB74[rec[4]] | 1;
    if (flags & 0x80000) {
        D_800D27C8 = D_800E1010[0x13];
    } else {
        D_800D27C8 = 0;
    }
    if (flags & 8) {
        D_80090118 = D_800E1010[3] * 3000;
    } else {
        D_80090118 = 0;
    }
    if (flags & 0x10000) {
        D_800E1000 = D_800E1010[0x10];
    } else {
        D_800E1000 = 2;
    }
    if ((flags & 4) && D_80090118 == 0) {
        D_80090160 |= 2;
        D_8009015C &= 0xFFFE;
    }
    if (D_80090160 & 0x80) {
        D_80090160 |= 0x1000;
    }
    if ((flags & 0x20000) && D_800E1010[0x11] != 0) {
        D_80090160 |= 0x20;
    }
    if ((D_80090160 & 0x100) && D_80090118 != 0) {
        D_80090160 = (D_80090160 & ~0x100) | 0x200;
    }
    D_80087260 = D_800E1010[2];
    D_800D2550 = 3;
    D_80087264 = 0;
    D_800D2132 = 0;
    D_80087608 = D_800E1010[4];
    if (D_800E1010[3] >= 3) {
        D_80087260 = 99;
    }
    if (rec[8] == 8) {
        for (i = 0; i < 16; i++) {
            D_80087270[i] = 8;
        }
        D_80090110 = func_151E2C88(0);
    }

    /* players: queue entries != -1 (entry 0 always counts) */
    mask = 1;
    D_80090128 = 1;
    if ((&D_800901E4)[1] != -1) {
        mask = 3;
        D_800843F0[1] = (&D_800901E4)[1];
        D_80090128++;
    }
    if ((&D_800901E4)[2] != -1) {
        mask |= 4;
        D_80090128++;
        D_800843F0[2] = (&D_800901E4)[2];
    }
    if ((&D_800901E4)[3] != -1) {
        mask |= 8;
        D_800843F0[3] = (&D_800901E4)[3];
        D_80090128++;
    }
    for (i = 4; i < 16; i++) {
        if ((&D_800901E4)[i] != -1) {
            mask |= 1 << i;
            D_80090128++;
        }
    }

    if (rec[8] != 8) {
        i = 0;
        if (D_800E0FBC != 0 && (&D_800901E4)[0] >= 0) {
            do {
                D_80087270[i] = D_800AB95C[D_800E0FC0[i]][6];
                i++;
            } while ((&D_800901E4)[i] >= 0 && i != 4);
        }
        for (; i < 16; i++) {
            s32 mode;

            slot = &D_80087270[i];
            *slot = rec[8];
            mode = ((MenuState *) D_80090174)->x42;
            if (mode == 7) {
                if ((&D_800901E4)[i] < -1) {
                    *slot = 0xB;
                }
            } else if (mode == 2) {
                if (D_800E1030[i] == 0) {
                    *slot = 0xB;
                }
            } else if (mode == 8) {
                if (D_800E1030[i] != 0) {
                    *slot = 3;
                } else {
                    *slot = (func_150ADA20() & 0xF) + 0x11;
                }
            } else if (D_800E1030[i] != 0 && rec[8] == 4) {
                *slot = 3;
            } else if ((&D_800901E4)[i] < -1 && rec[8] == 0xB) {
                *slot = (i & 3) + 0xC;
            }
        }
    }

    D_800E0FC9 = 2;
    n = D_80090128;
    D_80090130 = 0;
    D_800E0ED8 = 0;
    D_8008FD8C = n;
    for (i = 0; i < n; i++) {
        if ((&D_800901E4)[i] >= 0) {
            D_80090130++;
            D_800E0ED8 |= 1 << D_800E1030[i];
        }
    }
    D_80090134 = D_80090130;
    D_800BEA38 = D_8008FD8C;
    bzero(D_800E0FE8, 0x10);
    D_800E0EDA = -1;
    D_800E0ED9 = 4;
    for (i = 0; i < 16; i++) {
        D_800E0EE0[i] = -1;
        D_800E0EF0[i] = 0;
    }
    if (D_80090168 != 0) {
        n = D_80090128;
        D_800E0ED9 = D_8008FD8C;
        used = 0;
        next = 0;
        for (i = 0; i < n; i++) {
            if ((&D_800901E4)[i] >= 0) {
                D_800E1030[i] = (&D_800901E4)[i];
                used |= 1 << D_800E1030[i];
            } else {
                while ((1 << next) & used) {
                    next++;
                }
                D_800E1030[i] = next;
                used |= 1 << next;
                next++;
            }
        }
    }
    D_800E1040[0] = -1;
    D_800E1040[1] = -1;
    D_800E1048[0] = -1;
    D_800E1048[1] = -1;
    D_800E0ED0[0] = 0;
    D_800E0ED0[1] = 0;
    func_151E86A4();
    D_800E1050 = 0;
    D_800D3260 = 0;
    D_8009011C = D_80087270[0];
    func_1501C710(6, level, 0, D_800902E7[D_80090128], mask);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2FCC.s")
#endif

void func_151E86A4(void);
extern s8 D_800E0FE1;
extern s8 D_800BEA38;
extern s8 D_80090134;
extern u8 D_800E0FC9;
extern s16 D_8009015C;
extern s8 D_800D27C8;
void func_1509D1EC(s32);
s32 func_1509D338(s32, s32 *);
s32 func_1509D49C(s8, u8, s32 *, s32 *);
extern s8 D_80090110;
extern s16 D_8009014C;
extern u8 D_80090154;
extern s8 D_800902B0;
extern u8 D_800902B4;
extern s32 D_800BE804;
extern u8 D_800E1001;

void func_151E3864(void) {

    s32 sp24[3];

    sp24[0] = 0;
    if (D_80090154 != 0) {
        sp24[1] = (s32) D_8009014C;
    } else {
        func_1509D338(D_800902B0, &sp24[2]);
        func_1509D49C(D_800902B0, D_800902B4, &sp24[1], sp24);
        func_1509D464();
    }
    func_15017790();
    func_1509D0A4(sp24[1]);
    func_1509D1EC(sp24[1]);
    D_800BE9F4 = func_1509CE40(sp24[1]);
    func_15085710(0, 9, sp24[0]);
    D_800BE804 = sp24[0];
    D_800DD2C0 = func_1509CE60(sp24[1]);
    if (D_80090154 == 2) {
        D_800DD2C0 = D_800E1001;
    }
    D_80090110 = 0;
    D_800D27C8 = 0;
    D_8009015C = 0;
    D_8008FDA8 = -1;
    D_800E0B94 = 0;
    D_800E0FC9 = 1;
    D_8008FD8C = 1;
    D_80090130 = 1;
    D_80090134 = 1;
    D_800BEA38 = 1;
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }
    *D_80087270 = 0;
    D_800D18A8 = 0;
    D_800E0FE1 = 1;
    func_151E86A4();
    D_800D3260 = 1;
    func_1501C710(6, (s32) D_800BE9F4, func_1509CE60(sp24[1]), 0, 1);
}

void func_151E86A4(void);
extern s8 D_80090134;
extern s16 D_8009015C;
extern s8 D_800BEA38;
extern s8 D_800D27C8;
extern u8 D_800E0FC9;
extern s8 D_800E0FE1;

void func_151E3A1C(void) {
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }
    *D_80087270 = 0;
    D_8008FD8C = 1;
    D_80090130 = 1;
    D_80090134 = 1;
    D_8009015C = 0;
    D_800BEA38 = 1;
    D_800D27C8 = 0;
    D_800E0B94 = 0;
    D_800D3260 = 0;
    func_1501C710(6, (s32) (s8) D_800BE3DF, (s32) D_800BE800, 0, 1);
    D_800E0FC9 = 1;
    D_800E0FE1 = 1;
    func_151E86A4();
}

#ifdef NON_MATCHING
f32 func_15049AD0(s32 points, s32 segment, f32 t);
f32 sinf(f32);
extern s8 D_800ABA2C[];         /* settings item table: per item label text, type, then (type >= 0) max + 1 choice texts */
extern s8 D_80090180;           /* settings changed */
extern s16 D_800E0EB2;          /* value fade: 0xFF = steady, -0xFF.. = fading in a changed value */
extern s8 D_800E0EB4;           /* the value before the change */
extern s8 D_800E1013;
extern u8 D_800ABC98[];         /* "#" */
extern u8 D_800ABC9C[];         /* "#" */
extern u8 D_800ABCA0[];         /* "%d" */
extern u8 D_800ABCA4[];         /* "%s" */
extern u8 D_800ABCA8[];         /* "%d" */
extern u8 D_800ABCAC[];         /* "%s" */
extern u8 D_800ABCB0[];         /* "%d" */
extern u8 D_800ABCB4[];         /* "%d" */
extern u8 D_800ABCB8[];         /* "%d %s" */
extern u8 D_800ABCC0[];         /* "#" */
extern u8 D_800ABCC4[];         /* "#" */

// settings_list_draw: draws and edits the settings list (28 items, bit i of mask = item i shown; values D_800E1010[i],
// clamped to D_80090210 / D_8009022C[i]). arg1 != 0: the items sit on a rotating ring (Catmull-Rom over 2 columns,
// x 74 / 148 / 222, scrolled by D_800901D8), up / down change the value and left / right move the selection;
// arg1 == 0: a plain column at x 0x94 from y 0x46 (0x22 apart), left / right change the value and up / down move.
// The selection D_800901D4 skips hidden items; a changed value fades in from its old value when arg4 != 0
// (D_800E0EB2 / D_800E0EB4). arg2 != 0 draws the "#" cursor arrows that slide to the selected row
// (D_80090184 / D_80090188). arg3 = alpha.
void func_151E3AE4(s32 mask, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 alpha = arg3;
    s8 fadeIn = arg4;
    MenuState *rec;
    f32 x[32];
    f32 y[32];
    s32 count;
    s32 half;
    s32 step;
    s32 pos;
    s32 i;
    s32 ring;
    f32 t;
    s32 itemAlpha;
    s32 a;
    s8 shownValue;
    s32 offset;
    s8 *item;
    s32 type;
    s32 value;
    s32 drawn;
    s32 cursorRow;
    s32 px;
    s32 py;
    s32 sel;
    s32 oldSel;
    s8 *p;
    s8 old;
    s32 changed;
    s32 forward;
    s32 arrowX;
    s32 arrowY;

    count = 0;
    for (i = 0; i < 0x1C; i++) {
        if ((1 << i) & mask) {
            count++;
        }
    }
    half = count >> 1;
    ring = half;
    if (arg2 != 0 && D_80090188 != 0.0f) {
        ((MenuState *) D_80090174)->input &= ~3;
    }
    pos = 0x46;
    if (arg1 != 0) {
        /* ring layout: column x per slot (148 top, 222 right side going down, 148 bottom, 74 left side going up) */
        a = half;
        if (count >= 4 && (count & 1)) {
            a = half + 1;
        }
        step = 0x82 / (a + 1);
        if (count >= 4) {
            step -= 5;
        }
        i = 0;
        if (count > 0) {
            if (count & 1) {
                i = 1;
                pos = step + 0x46;
                y[1] = (f32) 0x46;
                x[1] = 148.0f;
            }
            for (; i != count; i += 2) {
                y[i + 1] = (f32) pos;
                if (i == 0) {
                    pos += step;
                    x[i + 1] = 148.0f;
                } else if (i < half) {
                    x[i + 1] = 222.0f;
                    pos += step;
                    if (i + 1 != half || (count & 1)) {
                        pos += 0x10;
                    }
                } else if (i == half) {
                    if (count & 1) {
                        x[i + 1] = 222.0f;
                    } else {
                        pos -= step;
                        x[i + 1] = 148.0f;
                    }
                } else {
                    pos = pos - step - 0x10;
                    x[i + 1] = 74.0f;
                }
                y[i + 2] = (f32) pos;
                if (i < half - 1) {
                    x[i + 2] = 222.0f;
                    pos += step;
                    if (i + 2 != half || (count & 1)) {
                        pos += 0x10;
                    }
                } else if (i == half - 1) {
                    if (count & 1) {
                        x[i + 2] = 222.0f;
                    } else {
                        x[i + 2] = 148.0f;
                        pos -= step;
                    }
                } else {
                    pos = pos - step - 0x10;
                    x[i + 2] = 74.0f;
                }
            }
            pos = 0x46;
        }
        /* wrap the ring for the spline */
        x[0] = x[count];
        y[0] = y[count];
        x[count + 1] = x[1];
        y[count + 1] = y[1];
        x[count + 2] = x[2];
        y[count + 2] = y[2];
        t = sinf(D_800901D8 * 3.14159f - 1.570795f) * 0.5f + 0.5f;
        /* ring slot of the first item = number of shown items before the selection */
        ring = 0;
        for (i = 0; i < 0x1C; i++) {
            if (i < D_800901D4 && ((1 << i) & mask)) {
                ring++;
            }
        }
        if (ring >= count) {
            ring = 0;
        }
    }

    if (fadeIn != 0) {
        D_800E0EB2 += 0x5C;
        if (D_800E0EB2 >= 0x100) {
            D_800E0EB2 = 0xFF;
        }
        a = D_800E0EB2;
        if (a < 0) {
            a = -a;
        }
        a = (alpha * a) >> 8;
        if (a >= 0xFE) {
            a = 0xFF;
        }
        if (D_800E0EB2 < 0) {
            shownValue = D_800E0EB4;
        } else {
            shownValue = D_800E1010[D_800901D4];
        }
        itemAlpha = a;
    } else {
        D_800E0EB2 = 0xFF;
        itemAlpha = alpha;
    }

    cursorRow = 0;
    offset = 0;
    drawn = 0;
    for (i = 0; i < 0x1C; i++) {
        item = &D_800ABA2C[offset];
        type = item[1];
        if ((1 << i) & mask) {
            value = D_800E1010[i];
            if (i == D_800901D4) {
                cursorRow = drawn;
            }
            if (arg1 != 0) {
                px = (s32) func_15049AD0((s32) x, ring, t);
                py = (s32) func_15049AD0((s32) y, ring, t);
                ring--;
                if (ring < 0) {
                    ring += count;
                }
            } else {
                py = pos;
                px = 0x94;
                pos += 0x22;
            }
            /* label */
            func_1504332C(0xFF, 0xFF, 0xFF, (u8) itemAlpha);
            func_150432FC(px, py);
            if (item[0] >= 0) {
                func_15042E3C(((s32 *) D_800E1008)[item[0]]);
            } else if (item[0] < -1) {
                func_150432FC(px, py + 9);
                func_15042E3C((s32) D_800ABC98, -item[0]);
                func_150432FC(px, py + 0x16);
            }
            /* value */
            if (i == D_800901D4 && D_800901D8 <= 0.0f) {
                func_1504332C(0xFF, 0xFF, 0xFF, (u8) itemAlpha);
                if (fadeIn != 0) {
                    value = shownValue;
                }
            } else if (fadeIn != 0) {
                func_1504332C(0xFF, 0xFF, 0xFF, alpha);
            } else {
                func_1504332C(0xFF, 0xFF, 0xFF, (alpha >> 2) & 0xFF);
            }
            if (type < 0) {
                if (type < -1) {
                    func_15042E3C((s32) D_800ABC9C, value - type);
                }
            } else {
                switch (type) {
                    case 0x79:
                        break;
                    case 0x7A:
                        if (value == 0) {
                            func_15042E3C((s32) D_800ABCA4, ((s32 *) D_800E1008)[0x73]);
                        } else {
                            func_15042E3C((s32) D_800ABCA8, value);
                        }
                        break;
                    case 0x7B:
                        if (D_800E1013 >= 3) {
                            func_15042E3C((s32) D_800ABCAC, ((s32 *) D_800E1008)[0x2D]);
                        } else {
                            func_15042E3C((s32) D_800ABCB0, value);
                        }
                        break;
                    case 0x7C:
                        func_15042E3C((s32) D_800ABCB4, value * 1000);
                        break;
                    case 0x7D:
                        if (value >= 3) {
                            func_15042E3C((s32) D_800ABCB8, value, ((s32 *) D_800E1008)[0x72]);
                        } else {
                            func_15042E3C(((s32 *) D_800E1008)[0x73]);
                        }
                        break;
                    case 0x7E:
                        func_15042E3C((s32) D_800ABCA0, value);
                        break;
                    case 0x7F:
                        func_15042E3C(((s32 *) D_800E1008)[value != 0]);
                        break;
                    default:
                        func_15042E3C(((s32 *) D_800E1008)[item[1 + value]]);
                        break;
                }
            }
            drawn++;
        }
        /* next item: label + type, plus the choice texts of a list item */
        if (type >= 0x79 && type <= 0x7F) {
            offset += 2;
        } else if (type >= 0) {
            offset += D_8009022C[i] + 2;
        } else {
            offset += 2;
        }
        if (D_800E1010[i] < D_80090210[i]) {
            D_800E1010[i] = D_80090210[i];
            D_80090180 = 1;
        }
        if (D_8009022C[i] < D_800E1010[i]) {
            D_800E1010[i] = D_8009022C[i];
            D_80090180 = 1;
        }
    }

    /* input */
    sel = D_800901D4;
    forward = 1;
    rec = (MenuState *) D_80090174;
    if (D_800E0EB2 != 0xFF) {
        rec->input = 0;
    }
    p = &D_800E1010[sel];
    old = *p;
    oldSel = sel;
    if (D_800901D8 <= 0.0f) {
        changed = 0;
        rec = (MenuState *) D_80090174;
        if (arg1 != 0) {
            if (rec->input & 1) {
                *p = old + 1;
                D_80090180 = 1;
                changed = 1;
            } else if (rec->input & 2) {
                *p = old - 1;
                D_80090180 = 1;
                changed = 1;
            } else if (rec->input & 8) {
                D_800901DC = 0.075f;
            } else if (rec->input & 4) {
                sel--;
                p--;
                if (sel < 0) {
                    sel += 0x1C;
                    p += 0x1C;
                }
                forward = 0;
                D_800901DC = -0.075f;
                D_800901D8 = 1.0f;
            }
        } else {
            if (rec->input & 4) {
                *p = old - 1;
                D_80090180 = 1;
                changed = 1;
            } else if (rec->input & 8) {
                *p = old + 1;
                D_80090180 = 1;
                changed = 1;
            } else if (rec->input & 2) {
                D_800901DC = 1.0f;
            } else if (rec->input & 1) {
                sel--;
                p--;
                if (sel < 0) {
                    sel += 0x1C;
                    p += 0x1C;
                }
                forward = 0;
                D_800901D8 = 0.0f;
            }
        }
        if (changed != 0 && sel == 2) {
            D_800E1010[3] = 2;
        }
        if (rec->input & 0xF) {
            func_10010F30(0x4FF, 0x4650, 0x40, 0, 0);
        }
        /* values wrap around */
        if (*p < D_80090210[sel]) {
            *p = D_8009022C[sel];
            D_80090180 = 1;
        }
        if (D_8009022C[sel] < *p) {
            *p = D_80090210[sel];
            D_80090180 = 1;
        }
    }
    D_800901D8 += D_800901DC * (f32) D_800BE9E4;
    if (D_800901D8 >= 1.0f) {
        sel++;
        p++;
        if (sel >= 0x1C) {
            sel -= 0x1C;
            p -= 0x1C;
        }
        D_800901DC = 0.0f;
        D_800901D8 = 0.0f;
    } else if (D_800901D8 <= 0.0f) {
        D_800901DC = 0.0f;
        D_800901D8 = 0.0f;
    }
    /* skip hidden items */
    while (forward != 0 && !((1 << sel) & mask)) {
        sel++;
        p++;
        if (sel >= 0x1C) {
            sel -= 0x1C;
            p -= 0x1C;
        }
    }
    while (forward == 0 && !((1 << sel) & mask)) {
        sel--;
        p--;
        if (sel < 0) {
            sel += 0x1C;
            p += 0x1C;
        }
    }
    if (sel == oldSel && old != *p) {
        D_800E0EB2 = -0xFF;
        D_800E0EB4 = old;
    }
    D_800901D4 = sel;

    if (arg2 != 0) {
        /* cursor arrows left and right of the selected row */
        arrowX = (s32) ((100.0f + D_80090188 * (f32) 0) * 0.5f);
        arrowY = (s32) ((f32) (D_80090184 * 0x22 + 0x46) + D_80090188 * (f32) ((cursorRow - D_80090184) * 0x22));
        arrowX = (s32) ((f32) arrowX + 20.0f * sinf(D_80090188 * 3.1415f));
        func_1504332C(0xFF, 0xFF, 0xFF, alpha);
        func_15042D94(arrowX + 0x94, arrowY, 1, (s32) D_800ABCC0, 0x1A);
        func_15042D94(0x94 - arrowX, arrowY, 1, (s32) D_800ABCC4, 0x1A);
        if (cursorRow != D_80090184) {
            D_80090188 += 0.1f * (f32) D_800BE9E4;
            if (D_80090188 >= 1.0f) {
                D_80090184 = cursorRow;
                D_80090188 = 0.0f;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E3AE4.s")
#endif
s32 func_151F2CDC();
void func_151F2D6C(s32, s32);
extern s32 *D_800E0EB8;
void func_151E2FCC(void);

void func_151E49C8(void) {
    if ((u8) D_80090120 != 0) {
        D_80090120 = 0;
        return;
    }
    func_151E5AB8();
    if ((D_800E0FCA != 0) || (D_800C35EA != 1)) {
        if ((D_800C35EA == 1) && (func_151F2CDC() == 1)) {
            func_151F2D6C(0, 0x370C);
        }
        D_800E0B94 = 7;
        D_800E0EB8 = &func_151E2FCC;
        D_80090114 = 8;
    }
}

void func_1501D348(s32, s32, s32, s32, s32);
extern u8 D_800ABA76[][10];
extern s16 D_800ABB88[][2];
void func_151E4A78(void) {
    s8 *p;
    s8 temp_v1;
    s8 var_a1;
    temp_v1 = D_800ABA76[((s8 *)D_80090174)[0x42]][0];
    if (temp_v1 >= 0) {
        if (D_800E1030[0] != 0) {
            p = (s8 *)&D_800ABB88[temp_v1];
            var_a1 = p[3];
        } else {
            p = (s8 *)&D_800ABB88[temp_v1];
            var_a1 = p[2];
        }
        func_1501D348(*(s16 *)p, var_a1, 0, 0, 0);
        *(u8 *)&D_80090120 = 1; // fakematch: u8 store keeps the constant out of the CSE
        D_800E0B94 = 5;
        D_8008FD8C = 1;
        D_80090130 = 1;
        return;
    }
    func_151E2FCC();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E4B40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E533C.s")

void func_151E5528(void) {
    D_800E0B94 = 10;
}

void func_151E553C(void) {
    if (D_800E0FCA & 0x8020) {
        D_800E0B94 = 4;
    }
}

void func_151E5564(void) {
    D_8009016C = 0;
    func_151E5D28();
    D_800E0B94 = 3;
    D_80090144 = 0;
    D_80090120 = 0;
    D_800D3260 = 0;
    func_1501C710(6, 0x1D, 0, 0, 1);
}

s32 func_151E5D54();
extern s32 *D_800E0EB8;
void func_151E5564(void);

void func_151E55C8(void) {
    func_151E5AB8();
    func_151E5D54();
    if (D_800E0EC0 >= 0x3E9) {
        D_800E0FCA |= 0x8000;
    }
    if (D_800E0FCA != 0) {
        D_800E0B94 = 7;
        D_800E0EB8 = &func_151E5564;
        D_80090114 = 8;
    }
}

extern f32 D_80090170;
extern f32 D_800ABE30;
extern f32 D_800ABE34;
extern f32 D_800ABE38;

void func_151E564C(void)
{
  unsigned int n; // fakematch: permuter temp
  int ff; // fakematch: constant in a register gives beq a2,v0 operand order
  s32 v;
  f32 f;
  v = *((u8 *) (&D_800E0FC6));
  ff = 0xFF; // fakematch
  D_80090170 = 1.0f - (((u32) v) / 255.0f);
  if (((u8) D_80090114) == 0xFF)
  {
    f = D_800DDDC8;
    if (D_800ABE30 < f)
    {
      v = (u8) (D_800E0FC6 = v + D_800BE9E4);
      if (v < 0x55)
      {
        D_800DDDD8 = D_800ABE34;
      }
      else
      {
        D_800DDDD8 = D_800ABE38;
      }
    }
    if (f < ((float) 1.0f))
    {
      return;
    }
    if (v < 0x6E)
    {
      return;
    }
  }
  else
  {
    n = (u8) D_80090114;
    if (v != ff)
    {
      v += D_800BE9E4 * n;
      if (v >= 0x100)
      {
        v = 0xFF;
      }
      D_800E0FC6 = v;
      return;
    }
  }
  *((u8 *) (&D_800E0FC6)) = 0xFF;
  D_80090114 = 8;
  D_80090170 = 1.0f;
  if (1) // fakematch: empty ifs on separate lines
  {
  }
  if (1)
  {
  }
  ((void (*)(void)) D_800E0EB8)();
}

void func_151E5798(void) {
    (*(f32 *)D_80090174) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 4)) = 0.0f;
    (*(s8 *)((u8 *)D_80090174 + 0x2B)) = 0;
    (*(s16 *)((u8 *)D_80090174 + 0x20)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3E)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x3F)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x41)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x43)) = 0;
    (*(s8 *)((u8 *)D_80090174 + 0x44)) = 0;
    (*(f32 *)((u8 *)D_80090174 + 0x10)) = 0.0f;
    (*(s8 *)((u8 *)D_80090174 + 0x2A)) = 0;
    (*(f32 *)((u8 *)D_80090174 + 0x14)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0x18)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0x1C)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 0xC)) = 0.0f;
    (*(f32 *)((u8 *)D_80090174 + 8)) = 0.0f;
}

void func_151E73A8(void);
extern u8 D_800E0F20[];
extern u8 D_800AB950[];
extern u8 D_800E0FC5;

void func_151E582C(void) {
    s32 i;

    i = 0;
    do {
        D_800E1010[i] = D_800901F4[i];
        i++;
    } while (i < 0x1C);
    D_800E0EC0 = 0;
    func_151E73A8();
    if (D_80090174 == NULL) {
        D_80090174 = D_800E0F20;
        func_151E5798();
        if (*(s8 *)(D_80090174 + 0x3E) == 1) {
            *(s8 *)(D_80090174 + 0x2C) = D_800AB950[*(s8 *)(D_80090174 + 0x2C)];
        }
    }
    func_15017790();
    D_800E0B94 = 11;
    D_800D3260 = 0;
    func_1501C710(6, 0x25, 0, 0, 1);
    D_800E0FC5 = D_800E0B94;
}

#ifdef NON_MATCHING
// Per-frame game-mode step: screen offset/scale from the D_800E1010 settings, input snapshot,
// the mode's handler from the table D_8009018C[D_800E0B94], and the time-in-mode counter
// D_800E0EC0 (reset and the previous mode kept in D_800E0FC5 when the mode changed; mode 7 keeps it).
extern f32 D_800ABE3C;
extern s8 D_800E100C;
extern u16 D_800BED50;
extern u8 D_800E0FC5;
extern void (*D_8009018C[])(void);
void func_10003C10(s32 x, s32 y, f32 scaleY, f32 scaleX);
void func_151E7110(s32 arg0);

void func_151E5928(void) {
    u8 prevMode = D_800E0B94;

    func_10003C10((D_800E1010[0x17] - 16) * 2, (D_800E1010[0x18] - 8) * 2, D_800E1010[0x1A] * D_800ABE3C + 1.0f,
                  D_800E1010[0x1B] * D_800ABE3C + 1.0f);
    D_8003C8E0 = 0x08000000;
    D_800E100C = 0xFF;
    func_15042D78(0x81);
    D_800E0FCA = D_800BED50;
    if (D_800901C8 != 0) {
        D_800901C8--;
        D_800E0FCA = 0;
    }
    if (D_800E0B94 == 0) {
        func_151E7110(2);
    } else if (D_800E0B94 == 8) {
        func_151E7110(4);
    } else {
        func_151E7110(1);
    }
    D_8009018C[D_800E0B94]();
    if (D_800E0B94 != 7) {
        D_800E0EC0 += D_800BE9E4;
        if (prevMode != D_800E0B94) {
            D_800E0FC5 = prevMode;
            D_800E0EC0 = 0;
        }
    }
    D_8003C8E0 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5928.s")
#endif
void func_151E5AB8(void)
{
  f32 temp_f0;
  s32 var_v1_2;
  if (D_800E0B94 != 2)
  {
    if (((u8) D_800E0FC6) != 0)
    {
      var_v1_2 = ((u8) D_800E0FC6) - (D_800BE9E4 * ((u8) D_80090114));
      if (var_v1_2 < 0)
      {
        var_v1_2 = 0;
      }
      D_800E0FC6 = var_v1_2;
    }
    if (((D_80090174 != 0) && ((*((s8 *) (((u8 *) D_80090174) + 0x2B))) == 0)) && ((*((f32 *) (((u8 *) D_80090174) + 0xC))) > 0.0f))
    {
      temp_f0 = *((f32 *) (((u8 *) D_80090174) + 8));
      if (temp_f0 > 0.5f)
      {
        var_v1_2 = (s32) ((temp_f0 - 0.5f) * 524.0f);
        if (var_v1_2 >= 0x100)
        {
          var_v1_2 = 0xFF;
        }
        D_800E0FC6 = (s8) var_v1_2;
      }
    }
  }
}

void func_151E533C(void);
extern u8 D_800901CC;
extern u16 D_80090160;
extern u8 D_800E0EB6;
extern s8 D_800ABA70[][10];

void func_151E5B94(s32 arg0) {
    s32 i;

    D_800E0EC0 = 0;
    D_800901CC = 0;
    D_80087270[0] = 0;
    if (D_800BE616 != 0) {
        D_800E0B94 = 7;
        D_80090114 = 8;
        if (D_800ABA70[(s8)D_80090174[0x42]][7] != -1) {
            D_80090174[0x3F] = 4;
            D_800E0EB8 = (s32 *)&func_151E533C;
        } else {
            D_80090174[0x3F] = 3;
            D_800E0EB8 = (s32 *)&func_151DE080;
        }
        for (i = 0; i < D_80090130; i++) {
            *(s16 *)(D_80090174 + i * 12 + 0x6C) = *(s16 *)(*(u8 **)((u8 *)&D_800CC2D0[i] + 0x31C) + 0x1AA);
        }
        D_80090160 &= 0xE35F;
        D_800E0EB6 = arg0;
        if (D_800ABA70[(s8)D_80090174[0x42]][7] == -2) {
            if (arg0 == 0) {
                func_151E533C();
            } else {
                D_800E0EB8 = (s32 *)&func_151DE080;
                D_80090174[0x3F] = 3;
            }
        }
    } else {
        D_800E0B94 = 4;
    }
}

void func_151E5D28(void) {
    D_800843F0[0] = 0;
    D_800843F0[1] = 1;
    D_800843F0[2] = 2;
    D_800843F0[3] = 3;
}

s32 func_151E5D54(void) {
    s32 d;
    s32 v;

    if ((u8)D_800E0FC8 == 0) {
        d = D_800BE9E4 * 8;
    } else {
        d = -D_800BE9E4 * 8;
    }
    v = (u8)D_800E0FC7;
    v += d;
    if (v >= 0x100) {
        v = 0x1FE - v;
        D_800E0FC8 = (u8)D_800E0FC8 ^ 1;
    } else if (v < 0) {
        v = -v;
        D_800E0FC8 = (u8)D_800E0FC8 ^ 1;
    }
    D_800E0FC7 = v;
}

void func_151E5DD8(void) {
    if (D_800E0EBC != 0) {
        D_800E0EBC = 0;
    }
}

s8 func_151E5DF8(void) {
    return D_80090168;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E5E08.s")

s32 func_151E6710(s32 arg0) {
    s8 var_v1;
    if ((D_800BE616 != 0) || (D_800E0B94 != 0)) {
        var_v1 = D_800E1030[arg0];
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        return var_v1;
    }
    return arg0;
}

s8 func_151E6758(void) {
    if (D_800E101B != 0) {
        if (D_8008FD8C >= 5) {
            return D_80090130;
        }
        return D_8008FD8C;
    }
    return D_80090130;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E67A0.s")

#ifdef NON_MATCHING
/* Load the text bank `bank` (1, 2, 4: picked per game mode by func_151E5928) for the current language.
 * D_800E101A = language, D_800BEECB = language of the loaded banks, D_800E1003 = loaded bank (0 = none).
 * A bank is a block of NUL-terminated strings (runs of NULs between them), loaded with func_1502B5C8
 * (asset group 3, type 0x1C, language, entry bank - 1) into D_800E1004; D_800E1008 = its string pointer table.
 * Bank 1 also loads entry 2 into D_80090178 with an 80-entry table D_800E0FB8. The old banks are freed
 * with func_10004074 first (the bank-1 extras only when they exist). */
extern u8 D_800BEECB;
extern s8 D_800E101A;
extern u8 **D_800E0FB8;
u8 *func_1502B5C8(s32 *size, s32 group, s32 type, s32 lang, s32 entry);
void *allocate_memory(s32, s32, s32, s32);
void func_10004074(s32);

void func_151E7110(s32 bank) {
    s32 size;
    s32 entry;
    s32 count;
    s32 i;
    u8 *p;
    u8 *end;

    if (D_800BEECB != D_800E101A) {
        D_800BEECB = D_800E101A;
        D_800E1003 = 0;
    }
    if (bank == D_800E1003) {
        return;
    }
    if (D_800E1004 != 0) {
        func_10004074(D_800E1004);
        D_800E1004 = 0;
        if (D_80090178 != 0) {
            func_10004074(D_80090178);
            func_10004074((s32)D_800E0FB8);
            func_10004074((s32)D_800E1008);
            D_80090178 = 0;
        }
    }
    D_800E1003 = bank;
    if (D_800E1003 == 0) {
        return;
    }

    entry = bank - 1;
    p = func_1502B5C8(&size, 3, 0x1C, D_800BEECB, entry);
    D_800E1004 = (s32)p;
    end = p + size;
    count = 0;
    do {
        while (*p != 0) p++;
        while (*p == 0) p++;
        count++;
    } while (p < end);

    D_800E1008 = allocate_memory((count + 1) * 4, 1, 0, 0);
    p = (u8 *)D_800E1004;
    end = p + size;
    i = 0;
    do {
        ((u8 **)D_800E1008)[i++] = p;
        while (*p != 0) p++;
        while (*p == 0) p++;
    } while (p < end);

    if (entry != 0) {
        return;
    }
    D_80090178 = (s32)func_1502B5C8(&size, 3, 0x1C, D_800BEECB, 2);
    D_800E0FB8 = allocate_memory(80 * sizeof(u8 *), 1, 0, 0);
    p = (u8 *)D_80090178;
    for (i = 0; i != 80; i++) {
        D_800E0FB8[i] = p;
        while (*p != 0) p++;
        while (*p == 0) p++;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E7110.s")
#endif

void func_151E73A8(void) {
    D_800E1003 = 0;
    D_800E1004 = 0;
    D_80090178 = 0;
}

#ifdef NON_MATCHING
s32 func_150871B8(s32 id);
s32 func_1508712C(s32 point, f32 *x, f32 *y, f32 *z);
f32 func_15049AD0(s32 points, s32 segment, f32 t);
void func_1000D96C(s32 sound, s32 prevSound, s32 arg2);
u8 *func_151149AC(u8 id);
f32 sinf(f32);
extern u8 D_800902F0[];         /* menu 0: carousel stop -> path point id (6 stops) */
extern f32 D_800902F8[];        /* menu 0: zoom speed per stop */
extern u8 D_80090338[];         /* menu 1: carousel stop -> path point id (8 stops) */
extern f32 D_80090340[];        /* menu 1: zoom speed per stop */
extern u16 D_800ABD04[][2];     /* menu 0: sound per stop: [0] accept, [1] back */
extern u16 D_800ABD1C[][2];     /* menu 1 */
extern f32 D_eu_80090310[];     /* menu 0: per-page zoom damping (scaled by D_80090170) */
extern f32 D_80090170;
extern s8 D_80090328[];         /* menu 0: per-page zoom percent that shows the page objects */
extern s8 D_80090330[];         /* menu 0: per-page zoom percent that hides them again */
extern u8 D_80090360[][6];      /* menu 0: 2 world objects (ids) per title page, 0xFF = none */
extern u8 D_800AB950[];         /* menu 1: carousel stop -> main menu page */
extern u8 D_800E0EC7;           /* last menu sound */

// menu_camera_update: the title / main menu camera (object behaviour of the menu camera, arg0 = camera index into
// D_800DBFF0). It is the carousel: left / right (input 4 / 8) slide the camera to the previous / next stop
// (rec->x0 runs 1 -> 0 or 0 -> 1 at rec->x4 per tick, rec->x2B is the target stop), accept (0x10) zooms in towards the
// stop (rec->fade 0 -> 1 at rec->xC, the zoom speed of the stop; the handler shows the page from fade 0.5), back
// (0x20) zooms out. A full zoom into stop 0 toggles title <-> main menu (rec->menu) and restarts at fade 0.99 going
// back out. The eye moves along a path of world points: from the base point (0 / 0x10) to the stop's point and
// on through the point graph D_800D2778 (5 links per 16-byte node, never back to the previous node), with a
// Catmull-Rom spline (func_15049AD0) when the path has 4+ points, linear otherwise; when not zoomed the look-at
// point follows the carousel between the previous, current and next stops. rec->x10 * (x14, x18, x1C) is a decaying
// offset used when the main menu camera jumps to the "back" stop 4 (rec->x2A modes 1 / 2 / 3). Writes
// rec->titlePage (the page shown: the stop, +1 past the slide midpoint; main menu through D_800AB950) and x2D,
// and the visibility (+0x80) of the page's world objects and of objects 0xF6 / 0xF7 / 0xF8 (+0x6E).
void func_151E73C8(s32 arg0) {
    MenuState *rec;
    struct108 *cam;
    s32 base;
    s32 stops;
    u8 *stopPoints;
    f32 *zoomSpeed;
    u16 (*sounds)[2];
    f32 slide;
    f32 zoom;
    f32 rawZoom;
    s8 ids[16];
    f32 x[16];
    f32 y[16];
    f32 z[16];
    u8 *node;
    u8 *cur;
    u8 next;
    s32 count;
    s32 i;
    s32 k;
    s32 segment;
    f32 t;
    f32 bx, by, bz;
    f32 px, py, pz;
    f32 qx, qy, qz;
    s32 jump;
    u8 *obj;
    u8 *objB;

    cam = &D_800DBFF0[arg0];
    if (((MenuState *) D_80090174)->menu == 0) {
        base = 0;
        stops = 6;
        stopPoints = D_800902F0;
        zoomSpeed = D_800902F8;
        sounds = D_800ABD04;
    } else {
        base = 0x10;
        stops = 8;
        stopPoints = D_80090338;
        zoomSpeed = D_80090340;
        sounds = D_800ABD1C;
    }
    func_1508712C(func_150871B8(base), &cam->unk2F8, &cam->unk2FC, &cam->unk300);

    rec = (MenuState *) D_80090174;
    if (rec->x4 != 0.0f) {
        /* sliding to the neighbouring stop */
        rec->x0 += rec->x4 * (f32) D_800BE9E4;
        if (rec->x0 <= 0.0f) {
            rec->x0 = 0.0f;
            rec->x4 = 0.0f;
        }
        if (rec->x0 >= 1.0f) {
            rec->x0 = 0.0f;
            rec->x4 = 0.0f;
            rec->x2B++;
            if (rec->x2B >= stops) {
                rec->x2B -= stops;
            }
        }
    } else if (rec->xC != 0.0f || rec->fade != 0.0f) {
        /* zoomed in or zooming: back zooms out, accept zooms in */
        if ((rec->input & 0x20) && (rec->menu == 0 || rec->x2B != 0)) {
            rec->xC = -zoomSpeed[rec->x2B];
            func_1000D96C(sounds[rec->x2B][1], D_800E0EC7, 0);
            D_800E0EC7 = sounds[rec->x2B][1];
        }
        if (rec->x2A != 0 && rec->menu == 1 && rec->x2B == 0) {
            if (rec->input & 0x20) {
                rec->xC = zoomSpeed[rec->x2B];
            }
        } else if (rec->input & 0x10) {
            rec->xC = zoomSpeed[rec->x2B];
        }
        rec->fade += rec->xC * (f32) D_800BE9E4;
        if (rec->fade >= 1.0f) {
            rec->fade = 1.0f;
            rec->xC = 0.0f;
        } else if (rec->fade < 0.0f) {
            rec->fade = 0.0f;
            rec->xC = 0.0f;
            if (rec->titlePage == 0 && rec->menu == 1 && rec->x44 != 0) {
                rec->x43 = 1;
                rec->x44 = 0;
            }
        }
    } else if (rec->input & 0x10) {
        /* at rest: accept starts the zoom */
        rec->xC = zoomSpeed[rec->x2B];
        func_1000D96C(sounds[rec->x2B][0], D_800E0EC7, 0);
        D_800E0EC7 = sounds[rec->x2B][0];
    } else {
        /* at rest: left goes back one stop (sliding 1 -> 0), right / x43 starts the slide to the next */
        if (rec->input & 4) {
            rec->x2B--;
            rec->x0 = 1.0f;
            rec->x4 = -0.05f;
            if (rec->x2B < 0) {
                rec->x2B += stops;
            }
        }
        if ((rec->input & 8) || rec->x43 != 0) {
            rec->x4 = 0.05f;
        }
        rec->x43 = 0;
        if (rec->x2B < 0) {
            rec->x2B += stops;
        }
        if (rec->x2B >= stops) {
            rec->x2B -= stops;
        }
    }

    rawZoom = rec->fade;
    if (rec->menu == 0) {
        rawZoom *= 1.0f - D_eu_80090310[rec->titlePage] * D_80090170;
    } else if (rec->titlePage != 0) {
        rawZoom *= 0.6f;
    }
    slide = sinf(rec->x0 * 3.14159f - 1.570795f) * 0.5f + 0.5f;
    zoom = sinf(rawZoom * 3.14159f - 1.570795f) * 0.5f + 0.5f;

    if (((MenuState *) D_80090174)->menu == 0) {
        /* the title page's world objects appear / disappear at the page's zoom percentages */
        for (i = 0; i < 2; i++) {
            if (D_80090360[i][rec->titlePage] != 0xFF) {
                obj = func_151149AC(D_80090360[i][rec->titlePage]);
                if (obj != NULL) {
                    rec = (MenuState *) D_80090174;
                    if (rec->xC > 0.0f || D_80090170 < 1.0f) {
                        if (D_80090328[rec->titlePage] < (s32) (rawZoom * 100.0f)) {
                            *(s32 *) (obj + 0x80) = 1;
                        }
                    } else if (rec->xC < 0.0f) {
                        if (D_80090330[rec->titlePage] >= (s32) (rawZoom * 100.0f)) {
                            *(s32 *) (obj + 0x80) = 0;
                        }
                    }
                }
            }
        }
    }

    cam->unk3D0->unk25C |= 0x200;
    cam->unk3D0->y_position = 1000.0f;

    if (rawZoom > 0.0f) {
        /* zooming: path from the base point through the stop's point along the point graph */
        ids[0] = func_150871B8(base);
        ids[1] = func_150871B8(stopPoints[((MenuState *) D_80090174)->x2B]);
        count = 1;
        node = (u8 *) D_800D2778 + ids[1] * 16;
        while (node != NULL) {
            cur = node;
            node = NULL;
            for (k = 0; k < 5; k++) {
                next = cur[9 + k];
                if (next != 0xFF && next != ids[count - 1]) {
                    ids[count + 1] = next;
                    count++;
                    k = 5;
                    node = (u8 *) D_800D2778 + next * 16;
                }
            }
        }
        count++;
        if (count >= 4) {
            t = zoom * ((f32) count - 2.0f);
            segment = (s32) t;
            t -= (f32) segment;
            if (segment >= count - 2) {
                segment--;
                t = 1.0f;
            }
            for (i = 0; i < count; i++) {
                func_1508712C(ids[i], &x[i + 1], &y[i + 1], &z[i + 1]);
            }
            /* end points mirrored for the spline */
            x[0] = x[1] - (x[2] - x[1]);
            y[0] = y[1] - (y[2] - y[1]);
            z[0] = z[1] - (z[2] - z[1]);
            x[count + 1] = (x[count - 1] - x[count]) + x[count];
            y[count + 1] = (y[count - 1] - y[count]) + y[count];
            z[count + 1] = (z[count - 1] - z[count]) + z[count];
            cam->unk2F8 = func_15049AD0((s32) x, segment, t);
            cam->unk2FC = func_15049AD0((s32) y, segment, t);
            cam->unk300 = func_15049AD0((s32) z, segment, t);
            cam->unk2A4 = func_15049AD0((s32) x, segment + 1, t);
            cam->unk2A8 = func_15049AD0((s32) y, segment + 1, t);
            *(f32 *) &cam->unk2AC = func_15049AD0((s32) z, segment + 1, t);
        } else {
            func_1508712C(ids[0], &x[0], &y[0], &z[0]);
            func_1508712C(ids[1], &x[1], &y[1], &z[1]);
            if (count == 3) {
                func_1508712C(ids[2], &x[2], &y[2], &z[2]);
            } else {
                x[2] = (x[1] - x[0]) + x[1];
                y[2] = (y[1] - y[0]) + y[1];
                z[2] = (z[1] - z[0]) + z[1];
            }
            cam->unk2F8 = (x[1] - x[0]) * zoom + x[0];
            cam->unk2FC = (y[1] - y[0]) * zoom + y[0];
            cam->unk300 = (z[1] - z[0]) * zoom + z[0];
            cam->unk2A4 = (x[2] - x[1]) * zoom + x[1];
            cam->unk2A8 = (y[2] - y[1]) * zoom + y[1];
            *(f32 *) &cam->unk2AC = (z[2] - z[1]) * zoom + z[1];
        }
    } else {
        /* not zoomed: look at the carousel (previous, current, next, next + 1 stops) */
        k = ((MenuState *) D_80090174)->x2B - 1;
        if (k < 0) {
            k += stops;
        }
        for (i = 0; i < 4; i++) {
            func_1508712C(func_150871B8(stopPoints[k]), &x[i], &y[i], &z[i]);
            k++;
            if (k >= stops) {
                k -= stops;
            }
        }
        cam->unk2A4 = func_15049AD0((s32) x, 0, slide);
        cam->unk2A8 = func_15049AD0((s32) y, 0, slide);
        *(f32 *) &cam->unk2AC = func_15049AD0((s32) z, 0, slide);
    }

    rec = (MenuState *) D_80090174;
    if (rec->x2A != 0) {
        /* look away from the eye: mirror the look-at point through it */
        cam->unk2A4 = cam->unk2F8 + (cam->unk2F8 - cam->unk2A4);
        cam->unk2A8 = cam->unk2FC + (cam->unk2FC - cam->unk2A8);
        *(f32 *) &cam->unk2AC = cam->unk300 + (cam->unk300 - *(f32 *) &cam->unk2AC);
    }
    cam->unk2A4 += rec->x10 * rec->x14;
    cam->unk2A8 += rec->x10 * rec->x18;
    *(f32 *) &cam->unk2AC += rec->x10 * rec->x1C;
    if (rec->x2A != 3) {
        rec->x10 *= 0.85f;
    } else {
        rec->x10 = -((0.25f - rec->fade) * 4.0f);
    }

    jump = 0;
    if (rec->menu == 1) {
        /* main menu: back at stop 0 jumps to stop 4 (x2A 1 -> 2 -> 3), with a decaying look-at offset */
        func_1508712C(func_150871B8(base), &bx, &by, &bz);
        k = rec->x2B;
        if (k >= stops) {
            k = 0;
        }
        func_1508712C(func_150871B8(stopPoints[k]), &px, &py, &pz);
        px -= bx;
        py -= by;
        pz -= bz;
        if (rec->x2A != 0) {
            px = -px;
            py = -py;
            pz = -pz;
        }
        if (rec->fade == 0.0f && (rec->input & 0x20) && rec->x10 < 0.01f && rec->x4 == 0.0f) {
            rec->x2B = 0;
            if (rec->x2D >= 2 && rec->x2D < 7) {
                rec->x2A = 2;
            }
            jump = 1;
            rec->xC = zoomSpeed[rec->x2B];
            func_1000D96C(sounds[rec->x2B][0], D_800E0EC7, 0);
            D_800E0EC7 = sounds[rec->x2B][0];
        }
        if (rec->fade < 0.25f && rec->x2A == 1) {
            rec->x2B = 4;
            jump = 2;
            rec->x2A = 0;
        }
        if (rec->fade == 0.0f && rec->x2A == 3) {
            rec->x2B = 4;
            rec->x2A = 0;
            rec->x10 = 0.0f;
        }
        if (jump != 0) {
            func_1508712C(func_150871B8(stopPoints[rec->x2B]), &qx, &qy, &qz);
            qx -= bx;
            qy -= by;
            qz -= bz;
            if (rec->x2A != 0) {
                qx = -qx;
                qy = -qy;
                qz = -qz;
            }
            rec->x10 = 1.0f;
            rec->x14 = px - qx;
            rec->x18 = py - qy;
            rec->x1C = pz - qz;
        }
        if (jump == 2) {
            rec->x10 = 0.0f;
            rec->x2B = 0;
            rec->x2A = 3;
        }
    }

    if (rec->fade >= 1.0f && rec->x2B == 0) {
        /* fully zoomed into stop 0: switch title <-> main menu and zoom back out */
        rec->menu = 1 - rec->menu;
        rec->fade = 0.99f;
        if (rec->menu != 0) {
            rec->xC = -D_80090340[0];
        } else {
            rec->xC = -D_800902F8[0];
        }
        if (rec->menu != 0) {
            rec->x2A = 1;
        } else {
            rec->x2A = 0;
        }
    }
    rec->titlePage = rec->x2B;
    if (rec->x0 > 0.5f) {
        rec->titlePage++;
    }
    if (rec->titlePage < 0) {
        rec->titlePage += stops;
    }
    if (rec->titlePage >= stops) {
        rec->titlePage -= stops;
    }
    rec->x2D = rec->titlePage;
    if (rec->menu == 1) {
        rec->titlePage = D_800AB950[rec->titlePage];
    }

    cam->unk2BC = cam->unk2A4;
    cam->unk2C0 = cam->unk2A8;
    cam->unk2C4 = *(f32 *) &cam->unk2AC;
    cam->unk390 = 0.0f;
    cam->unk1A4 = 20.0f;
    cam->unk19C = 20.0f;
    cam->unk1A8 = 15.0f;
    cam->unk1A0 = 15.0f;

    obj = func_151149AC(0xF8);
    if (obj != NULL) {
        obj[0x6E] = 1;
    }
    obj = func_151149AC(0xF6);
    objB = func_151149AC(0xF7);
    if (obj != NULL && objB != NULL) {
        if (((MenuState *) D_80090174)->menu == 0) {
            obj[0x6E] = 0;
            objB[0x6E] = 1;
        } else {
            obj[0x6E] = 1;
            objB[0x6E] = 0;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E73C8.s")
#endif
extern f32 D_800ABE94;
u8 *func_151149AC(u8);
extern u8 D_80090360[][6];

void func_151E856C(void)
{
  s32 var_s0;
  u8 var_a0;
  u8 *temp_v0;
 var_s0 = 0; if ((!((*((f32 *) (((u8 *) D_80090174) + 8))) < D_800ABE94)) || ((*((s8 *) (((u8 *) D_80090174) + 0x3E))) != 0)) { do { if ((*((s8 *) (((u8 *) D_80090174) + 0x3E))) == 0) { var_a0 = D_80090360[var_s0][*((s8 *) (((u8 *) D_80090174) + 0x2C))];
      }
      else
      {
        var_a0 = D_80090360[var_s0][0];
      }
      temp_v0 = func_151149AC(var_a0);
      var_s0 += 1;
      if (temp_v0 != 0)
      {
        *((s32 *) (((u8 *) temp_v0) + 0x80)) = 2;
      }
    }
    while (var_s0 != 2);
  }
}

extern s8 D_800E1019;

void func_151E8648(void) {
    if (D_800E1019 == 2) {
        func_10017870(1U);
        return;
    }
    if (D_800E1019 == 0) {
        func_10017870(2U);
        return;
    }
    func_10017870(4U);
}

#ifdef NON_MATCHING
// menu_settings_apply_checked: P127 (port): applies the sound mode (func_151E8648). The N64 build then sums the code
// words of func_151DE100..func_151DECB4 and, on a mismatch (anti-tamper), writes 0 over osSpTaskLoad; the port has
// no MIPS code words there (the sum is 0) and the write lands in the null zone, so the NON_MATCHING build skips it.
void func_151E86A4(void) {
    func_151E8648();
}
#else
extern s32 func_151DE100;
void func_151E86A4(void) {
    void (*new_var)(OSTask *tp); // fakematch: permuter temp pinning osSpTaskLoad address
    s32 var_v1;
    s32 *var_v0;
    func_151E8648();
    new_var = osSpTaskLoad; // fakematch
    var_v1 = 0;
    for (var_v0 = &func_151DE100; (u32) var_v0 < (u32) func_151DECB4; var_v0++) {
        var_v1 += *var_v0;
        if (!new_var) { } // fakematch
    }
    if (var_v1 != 0xBB9FE01C) {
        *((s32 *) new_var) = 0;
        if (func_151DECB4) { } // fakematch
    }
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E870C.s")

#ifdef NON_MATCHING
extern s32 D_800E0FD0;
extern s32 D_800E0FD4;
extern s32 D_800E0FD8;
extern s32 D_800E0FDC;
extern s8 D_80090124;

void func_151E8998(void) {
    D_800E0FD4 = 0;
    D_800E0FD0 = 0;
    D_800E0FD8 = 0;
    D_800E0FDC = 0;
    D_80090124 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E8998.s")
#endif
s32 func_1517F54C();
extern s16 D_800E0EB0;

void func_151E89C0(void) {
    if (D_800E0B94 != 8) {
        if (func_1517F54C() == 0) {
            D_800E0EC0 = 0;
        }
        if (D_800E0EC0 >= 0xA1) {
            D_8009016C = 0;
            D_800E0B94 = 8;
            D_8008FD8C = 1;
            D_80090130 = 1;
            D_80090144 = 0;
            D_800E0EB0 = -2;
            D_800E0EC0 = 0;
            D_800D2E43 = 1;
        }
    }
}

void func_151E5AB8(void);

void func_151E8A64(void) {
    func_151E5AB8();
    if (D_800E0EB0 == -1 && D_800E0EC0 >= 0x79) {
        D_800E0B94 = 9;
        D_800E0EC0 = 0;
        D_8009016C = 0xFF;
        D_800E0EB0 = 0;
        func_1501C710(6, 0x1D, 0, 0, 1);
        return;
    }
    if (D_800E0EB0 == -2) {
        D_800E0EB0 = 0;
    }
    if (D_800E0EC0 >= 0x173 && D_800E0EB0 >= 0) {
        while (((u8 **)D_800E1008)[D_800E0EB0][0] != 0x2A) {
            D_800E0EB0++;
        }
        D_800E0EB0++;
        if (((u8 **)D_800E1008)[D_800E0EB0][0] == 0x3D) {
            D_800E0EB0 = -1;
        }
        D_800E0EC0 = 0;
    }
}

void func_1501D348(s32, s32, s32, s32, s32);

void func_151E8B94(void) {
    if (D_800E0EB0 == 0) {
        D_800E0EB0 = -1;
        func_1501D348(0x1D, 6, 0, 0, 0);
    }
    func_151E5AB8();
    if (func_1517F54C() == 0) {
        D_800E0EC0 = 0;
    }
    if (D_800E0EC0 >= 0x65) {
        func_151E5798();
        D_80090144 = 0;
        D_800E0B94 = 1;
        D_800E0EC0 = 0;
        D_800D3260 = 0;
        func_1501C710(6, 0x21, 0, 0, 1);
    }
}
