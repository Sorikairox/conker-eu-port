typedef struct { f32 x, y, z; } V3;
typedef struct { u8 *o; u8 u4; u8 pad5[3]; u8 *u8; u8 *uC; } Sub28;
extern f32 D_800A1EE8[];
extern f32 D_800A1EF4[];
s32 func_15145EA4(f32 **, V3 **, s32, s32);
void func_150F66F8(u8 *arg0) {
    V3 a;
    V3 b;
    f32 *tab[2];
    V3 *outs[2];
    Sub28 *p;
    u8 *o;
    u8 *r;
    u8 *q;

    o = *(u8 **)(arg0 + 0x28);
    p = (Sub28 *)(arg0 + 0x28);
    if (*(s32 *)o == 0 || p->u4 != o[0x3B]) {
        *(s16 *)(arg0 + 0xE) = -1;
        return;
    }
    if (*(s32 *)(o + 0x1D4) != 0 && !(*(s32 *)(o + 0x94) & 2)) {
        tab[0] = D_800A1EE8;
        tab[1] = D_800A1EF4;
        outs[0] = &a;
        outs[1] = &b;
        func_15145EA4(tab, outs, *(s32 *)(o + 0x1D4), 2);
        r = p->u8;
        if (r != NULL) {
            r[0x168] |= 1;
            *(V3 *)(r + 0x34) = a;
            *(V3 *)(r + 0x40) = b;
        }
        r = p->uC;
        if (r != NULL) {
            q = *(u8 **)(r + 0x14);
            q[9] = 0;
            *(s16 *)(q + 0xE) = a.x;
            *(s16 *)(q + 0x10) = a.y;
            *(s16 *)(q + 0x12) = a.z;
        }
    } else {
        r = p->u8;
        if (r != NULL) {
            q = r + 0x110;
            q[0x58] &= 0xFFFE;
        }
        r = p->uC;
        if (r != NULL) {
            q = *(u8 **)(r + 0x14);
            q[9] = 1;
        }
    }
    r = p->u8;
    if (r != NULL) {
        q = r + 0x110;
        *(f32 *)(q + 0x48) = 4.0f;
        *(f32 *)(q + 0x4C) = 8.0f;
    }
}
