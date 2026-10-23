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
s32 func_1501D348(s32, s32, s32, s32, s32);
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
