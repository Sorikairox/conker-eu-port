void func_150A00F0(void)
{
    s32 i;

    for (i = 0; i < 10; i++) {
        D_800D3430[i].active = 0;
        D_800D3430[i].count = 0;
        D_800D3430[i].timer = 0;
    }
}
