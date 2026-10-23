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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151DE100.s")

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
} MenuState;

typedef struct MenuPad {
    u16 button;
    s8 stickX;
    s8 stickY;
    u8 errno_;
    u8 pad5;
} MenuPad;

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E0BBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1174.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E1308.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E19AC.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2B9C.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E2FCC.s")

void func_151E86A4(void);
extern s8 D_800E0FE1;
extern s8 D_800BEA38;
extern s8 D_80090134;
extern u8 D_800E0FC9;
extern s16 D_8009015C;
extern s8 D_800D27C8;
s32 func_1509D1EC(s32);
s32 func_1509D338(s8, s32 *);
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E3AE4.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_20B730/func_151E73C8.s")

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
