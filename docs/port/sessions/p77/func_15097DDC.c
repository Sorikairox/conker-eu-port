s32 func_15053430(struct127 *);
void func_15060F28(struct127 *arg0, s32 arg1);
extern u8 D_800D2520;
extern s32 D_800D3C60;

/* Removes object `id`: sets flag +2 of its entity record (when id < D_800D2520) and kills it with
 * func_15060F28(obj, 0), or with func_15053430 when called with two words and args[1] != 0. Returns 999999,
 * 0 for a missing object. */
s32 func_15097DDC(s32 id, s32 *args) {
    struct127 *obj;

    obj = func_1505EEF4(id);
    if (obj == NULL) {
        return 0;
    }
    if (id < D_800D2520) {
        ((u8 *)D_800D20FC + id * 0x30)[2] = 1;
    }
    if (D_800D3C60 == 2 && args[1] != 0) {
        func_15053430(obj);
    } else {
        func_15060F28(obj, 0);
    }
    return 999999;
}
