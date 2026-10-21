s32 func_150A2280(struct127 *, u8 *, s32);
s32 func_150AD9A0(s16, s16, s16);
void func_15035AF8(s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_150A126C(void) {
    u32 i;
    s32 j;
    Unk34B8 *e;
    struct127 *a;
    s16 dy;
    s32 h;
    f32 g;
    f32 f;

    for (i = 0; i < D_800D3094; i++) {
        e = &((Unk34B8 *)D_800D34B8)[i];
        if (e->unk14 == 0 && (e->unk15 >> 2) == 6) {
            for (j = 0; j < 25; j++) {
                a = &D_800CC2D0[j];
                if (a->interaction_state != 0 && (a->unk5 == 0 || a->unk5 == 1) &&
                    func_150A2280(a, D_800D34B8 + i * 0x34, 1) == 0) {
                    e = &((Unk34B8 *)D_800D34B8)[i];
                    dy = a->y_position - e->y;
                    if (e->unk17 == 0) {
                        h = func_150AD9A0(a->x_position - e->x, dy, a->z_position - e->z);
                        e = &((Unk34B8 *)D_800D34B8)[i];
                        if (h < e->unk6) {
                            g = e->unk6;
                            f = g * 0.2f;
                            if (f > 100.0f) {
                                f = 100.0f;
                            }
                            func_15035AF8(2, j, e->x, e->y, e->z, 0.0f, e->unk10, g - f, g, 255.0f);
                        }
                    } else {
                        func_15035AF8(1, j, a->x_position, *(f32 *)((u8 *)a + 0x180), a->z_position, 0.0f, 0.0f, 100.0f, 150.0f, 255.0f);
                    }
                }
            }
        }
    }
}
