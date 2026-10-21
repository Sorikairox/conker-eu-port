extern u16 D_800888B0[];
extern u16 D_800888BC[];
extern SlotEnt D_800D34A8[];

void func_150A067C(void)
{
    SlotEnt *v;
    s32 k;

    v = D_800D3430;
    do {
        if (v->active && v->flag == 1) {
            k = v->kind;
            v->timer += D_800BE9E4;
            if (v->timer >= D_800888B0[k]) {
                v->timer -= D_800888B0[k];
                v->count++;
                if (D_800888BC[k] != 0) {
                    v->count %= D_800888BC[k];
                }
            }
        }
        v++;
    } while (v != &D_800D3430[10]);
}
