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
extern u8 D_800E0EC4;
extern u8 D_800E0EC5;
extern u8 D_800E0EC6;
extern s8 D_800902A4;
extern s8 D_800902A8;
extern f32 D_80090188;
extern u16 D_800BED50;
void func_15042D94(s32, s32, u8, s32, ...);
void func_1504332C(u8 arg0, u8 arg1, u8 arg2, u8 arg3);
extern u8 D_800ABBE4[]; /* "#": text id */
extern u8 D_800ABBE8[];
extern u8 D_800ABBEC[];
extern u8 D_800ABBF0[];
extern u8 D_800ABBF4[];
extern u8 D_800ABBF8[];
extern u8 D_800ABBFC[];
extern u8 D_800901D4;
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
