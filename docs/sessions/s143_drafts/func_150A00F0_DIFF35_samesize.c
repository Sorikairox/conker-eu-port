void func_150A00F0(void)
{
    s32 i;
    SlotEnt *p = D_800D3430;
    for (i = 0; i < 10; i++, p++) {
        p->active = 0;
        p->count = 0;
        p->timer = 0;
    }
}
