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
