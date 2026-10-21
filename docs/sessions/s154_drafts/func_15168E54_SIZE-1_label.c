void func_15168E54(struct_eu_gfxcmd *arg0, s32 arg1) {
    s32 i = 0;
    struct_eu_gfxcmd *gfx = arg0;

    while (gfx->cmd != -0x21) {
        i++;
        if (gfx->cmd == 1 || (gfx->cmd == -0x24 && gfx->b3 == 0xE)) {
            func_15168E34(&gfx->w1, arg1);
        }
        gfx = &arg0[i];
        goto next; // fakematch: label at the end of the loop body
    next:;
    }
}
