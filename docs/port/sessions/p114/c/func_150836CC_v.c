extern s32 D_80087064;
void func_150305E0(s32 arg0, s32 arg1);
struct127 *func_1505F0AC(s32 arg0);
void func_15054A5C(struct127 *arg0, struct127 *arg1);
void func_15060F28(struct127 *arg0, s32 arg1);

// object_setup_undo: undoes setup command list D_80087064[n - 1] on obj (the list func_15083568 runs): first
// func_150305E0(obj, n), then for every type-0 command (+3 == 0) the object it spawned (func_1505F0AC(cmd[0])) is
// removed if it is still attached to obj (+0x65 == obj's index + 1): kinds 0x1D / 0x6E / 0x2F are detached with
// func_15054A5C(o, owner), other kinds removed with func_15060F28(o, 0). No return value (callers ignore v0).
void func_150836CC(struct127 *obj, s32 n) {
    u8 *list = (u8 *) &D_80087064 + (n - 1) * 8;
    u8 *cmd;
    u8 *o;
    s32 i;

    func_150305E0((s32) obj, n);
    cmd = *(u8 **) list;
    for (i = 0; i < list[4]; i++, cmd += 0x10) {
        if (cmd[3] != 0) {
            continue;
        }
        o = (u8 *) func_1505F0AC(cmd[0]);
        if (o == NULL || o[0x65] != ((u8 *) obj - (u8 *) D_800CC2D0) / 0x32C + 1) {
            continue;
        }
        if (o[4] == 0x1D || o[4] == 0x6E || o[4] == 0x2F) {
            func_15054A5C((struct127 *) o, (struct127 *) ((u8 *) D_800CC2D0 + o[0x65] * 0x32C - 0x32C));
        } else {
            func_15060F28((struct127 *) o, 0);
        }
    }

}
