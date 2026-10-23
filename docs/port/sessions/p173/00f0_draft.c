// slots_reset: clears the 10 slots of D_800D3430 (inactive, count and timer 0); level start (func_150177F8).
void func_150A00F0(void) {
    SlotEnt *v;

    for (v = D_800D3430; v != D_800D3430 + 10; v++) {
        v->active = 0;
        v->count = 0;
        v->timer = 0;
    }
}
