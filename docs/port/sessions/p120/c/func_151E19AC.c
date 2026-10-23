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
