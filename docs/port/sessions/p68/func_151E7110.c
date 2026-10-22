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
