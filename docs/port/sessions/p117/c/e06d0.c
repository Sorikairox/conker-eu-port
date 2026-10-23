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
extern u8 D_800901CC;
void func_15042D94(s32, s32, u8, s32, ...);
void func_1504332C(u8 arg0, u8 arg1, u8 arg2, u8 arg3);
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
