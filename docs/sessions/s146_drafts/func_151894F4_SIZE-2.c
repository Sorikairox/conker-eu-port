typedef struct { u8 u0; u8 u1; u8 u2; u8 pad3[5]; u8 *u8_; u8 padC[4]; u8 *u10; } S94F4;
typedef struct { u16 id; u16 pad; } E94F4;
extern u16 D_800DC318[];
extern E94F4 **D_800895E0;
extern u8 **D_800895F0[];
void func_151894F4(S94F4 *arg0) {
    s32 i;
    s32 j;
    s32 n;
    s32 cur;
    s32 other;
    u8 *src;
    u8 *last;
    E94F4 *e;
    s32 k;

    n = arg0->u1;
    cur = D_800BE9C0 * n;
    other = (D_800BE9C0 ^ 1) * n;
    k = 0;
    i = 0;
    if (D_800DC318[k] > 0) {
        e = *D_800895E0;
        do {
            if (arg0->u10 == (u8 *)D_800DBEF4 + e->id * 0xA0) {
                break;
            }
            i++;
            e++;
        } while (i < D_800DC318[k]);
    }
    if (i == D_800DC318[0]) {
        arg0->u2 = 0;
        return;
    }
    last = ((*D_800895E0)[i].id << 6) + *D_800895F0[D_800BE9C0];
    for (j = 0; j < n; j++) {
        if (n == j + 1) {
            src = last;
        } else {
            src = arg0->u8_ + (j + other + 1) * 0x40;
        }
        bcopy(src, arg0->u8_ + (cur + j) * 0x40, 0x40);
    }
    if (arg0->u2 != arg0->u1) {
        arg0->u2++;
    }
}
