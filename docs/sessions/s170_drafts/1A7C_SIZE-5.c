s32 func_15141C0C(u8 *);
s32 func_1510FE4C(s32);
s32 func_15141CC0(u32);
void func_15141A7C(u8 *arg0, s32 arg1) {
    s32 i;
    s32 r;
    struct_eu_link *sp3C;
    struct_eu_attached *a;

    if (D_800BE616 != 0) {
        return;
    }
    i = func_15141C0C(arg0);
    if (D_8008A084[i] != 0) {
        r = ((s32 (*)(s32, u8 *))D_8008A084[i])(func_15141CC0(func_1510FE4C(*(s32 *)(arg0 + 0x184))), arg0);
        if (r != -1 && D_8008A0B4[r].unk0 != 0) {
            if (D_8008A0B4[r].unk4 > 0) {
                func_15141E38((struct127 *)arg0, r);
            } else {
                (*(void (**)(u8 *, s32, s32))&D_8008A0B4[r].unk0)(arg0, arg1, 0);
            }
        }
    }
    sp3C = *(struct_eu_link **)(arg0 + 0x2F4);
    if (func_1514F250(sp3C, 0x1A, &sp3C)) {
        do {
            a = sp3C->unk10;
            if (D_8008A0B4[a->unk28].unk0 != 0) {
                (*(void (**)(u8 *, s32, s32))&D_8008A0B4[a->unk28].unk0)(arg0, arg1, a->unkE);
            }
            sp3C = sp3C->unk14;
        } while (func_1514F250(sp3C, 0x1A, &sp3C));
    }
}
