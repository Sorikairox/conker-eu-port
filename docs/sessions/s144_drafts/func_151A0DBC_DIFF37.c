typedef struct { u8 *unk0; u8 unk4; } S0DBC;
s32 func_1519F738(s32, s32);
void func_151A0E98(u8 *);
void func_151A0DBC(u8 *arg0) {
    s32 *out;
    u8 flag;
    S0DBC *ent;
    u8 *obj;
    u8 *sub;
    s32 res;

    obj = *(u8 **)(arg0 + 0x28);
    flag = 0;
    ent = (S0DBC *)(arg0 + 0x28);
    sub = *(u8 **)(obj + 0x18);
    out = (s32 *)(obj + 0x58);

    if (*(s32 *)sub == 0) {
        flag = 1;
    }
    if (ent->unk0[0x1C] != sub[0x3B]) {
        flag = 1;
    }
    if (!flag && *(s32 *)(sub + 0x1D4) != 0) {
        res = func_1519F738((s32)ent->unk0, ent->unk4);
        flag = 1;
        if (ent->unk4 == 6) {
            out[0] = res;
        } else {
            out[2] = res;
        }
    }
    if (flag) {
        func_151A0E98(arg0);
        *(s16 *)(arg0 + 0xE) = -1;
        arg0[0xD] |= 1;
    }
}
