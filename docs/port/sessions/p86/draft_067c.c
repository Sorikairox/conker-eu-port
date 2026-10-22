extern u16 D_800888B0[]; /* timer period per kind */
extern u16 D_800888BC[]; /* count modulus per kind (0: none) */

/* Per frame: every active, running slot (of the 10) adds D_800BE9E4 to its timer; each time the timer reaches the
 * period of its kind it wraps and the count goes up (modulo the kind's modulus when that is set). */
void func_150A067C(void) {
    SlotEnt *v;
    u32 period;

    for (v = D_800D3430; v != D_800D3430 + 10; v++) {
        if (v->active && v->flag == 1) {
            v->timer += D_800BE9E4;
            period = D_800888B0[v->kind];
            if (v->timer >= period) {
                v->timer -= period;
                v->count++;
                if (D_800888BC[v->kind] != 0) {
                    v->count %= D_800888BC[v->kind];
                }
            }
        }
    }
}
