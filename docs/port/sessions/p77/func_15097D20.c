s32 func_15083E0C(u8);
struct127 *func_15083E90(u8);
s32 func_15082E44(u8 *e, s32 idx, s32 arg2, s32 arg3, s32 reuse);

/* Object id (0x2000 | n) of script entity `entity` (u8): -1 when it has no record (func_15083E0C), the live object's
 * +0x13F when it exists (func_15083E90), else the record's flag +2 is cleared and the entity is spawned
 * (func_15082E44; -1 when that fails) and looked up again. 0 stays 0. */
s32 func_15097D20(s32 entity, s32 unused) {
    s32 idx;
    struct127 *obj;

    idx = func_15083E0C(entity);
    if (idx != -1) {
        obj = func_15083E90(entity);
        if (obj != NULL) {
            idx = ((u8 *)obj)[0x13F];
        } else {
            ((u8 *)D_800D20FC + idx * 0x30)[2] = 0;
            if (func_15082E44((u8 *)D_800D20FC + idx * 0x30, idx, 0, 0, 0) == 0) {
                return -1;
            }
            idx = func_15083E0C(entity);
        }
    }
    if (idx != 0) {
        idx |= 0x2000;
    }
    return idx;
}
