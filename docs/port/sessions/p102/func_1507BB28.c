/* P102 draft (game_A28B0.c is not a port-b file): producer of the script pointer that func_15097E9C (cases 0x14,
 * 0x35, 0x60) and func_1507B... (game_A28B0.c line ~423) store in object +0x218. */
extern u8 D_8009A4E0[];          /* empty script */
extern u8 D_80086E28[];          /* default script list, 8-byte entries {script, kind} */

/* (int: game_A28B0.c calls it before any prototype, i.e. as implicit int.) The script of kind `kind` for the current object D_800D154C: its type's list (pointer 0x10 bytes before the
 * type's D_800D1588 entry) is searched first; a list without that kind (a NULL script ends it) falls back to the
 * default list D_80086E28, which must contain it (the asm spins forever otherwise). No type entry / list: the
 * empty script D_8009A4E0. */
int func_1507BB28(s32 unused, s32 kind) {
    u8 *type;
    u8 *list;
    s32 i;

    type = ((u8 **)D_800D1588)[*((u8 *)D_800D154C + 4)];
    if (type == NULL) {
        return (s32)D_8009A4E0;
    }
    list = *(u8 **)(type - 0x10);
    if (list == NULL) {
        return (s32)D_8009A4E0;
    }
    for (i = 0; list[i * 8 + 4] != kind; i++) {
        if (*(u8 **)(list + i * 8) == NULL) {
            for (i = 0; D_80086E28[i * 8 + 4] != kind; i++) {
                if (*(u8 **)(D_80086E28 + i * 8) == NULL) {
                    for (;;) {
                    }
                }
            }
            return *(s32 *)(D_80086E28 + i * 8);
        }
    }
    return *(s32 *)(list + i * 8);
}
