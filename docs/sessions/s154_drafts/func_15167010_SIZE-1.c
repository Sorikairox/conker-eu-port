void func_15167010(void) {
    struct115 *p;
    struct115 *end;
    p = D_8008B4A8;
    end = p + 101;
    for (; p < end; p++) {
        if (p->unk18 != NULL) {
            ((void (*)(void))p->unk18)();
        }
    }
}
