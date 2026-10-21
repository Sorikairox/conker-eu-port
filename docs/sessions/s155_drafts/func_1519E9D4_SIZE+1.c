s32 func_1514F2AC(s32, u8 *, s32);
s32 func_1519D5A0(s32, s32, s32, s32, s32, s32);

typedef struct {
    u8 *obj;
    u8 id;
    u8 pad5[3];
    s32 x8;
} Link9D4;

void func_1519E9D4(u8 *arg0) {
    Link9D4 *p = (Link9D4 *)(arg0 + 0x28);
    u8 flag = 0;
    s32 v;

    if (*(s32 *)p->obj == 0) {
        flag = 1;
    }
    if (p->id != p->obj[0x3B]) {
        flag = 1;
    }
    if (flag == 0 && *(s32 *)(p->obj + 0x1D4) != 0) {
        flag = 1;
        v = func_1519D5A0((s32)p->obj, p->x8, *(s16 *)(arg0 + 0xE), arg0[0xD] & 1, arg0[0xC], arg0[1]);
        if (v != 0) {
            if (func_1514F2AC(*(s32 *)(p->obj + 0x2F4), arg0, 0) != 0) {
                func_1514F18C((void *)v, (struct127 *)p->obj, 0x10);
            }
        }
    }
    if (flag != 0) {
        *(s16 *)(arg0 + 0xE) = -1;
        arg0[0xD] |= 1;
    }
}
