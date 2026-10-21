void func_15143134(void *arg0, void *arg1, void *arg2) {
    f32 mf[4][4];

    D_800DCE30 = 1;
    if ((arg0 != NULL) && ((((struct17 *)arg0)->unk0 != 0.0f) || (((struct17 *)arg0)->unk4 != 0.0f) || (((struct17 *)arg0)->unk8 != 0.0f))) {
        D_800DCE30 = 2;
        D_800DCE38 = ((struct17 *)arg0)->unk0;
        D_800DCE3C = ((struct17 *)arg0)->unk4;
        D_800DCE40 = ((struct17 *)arg0)->unk8;
        if (D_800C42B0 != 0) {
            D_800DCE30 = 3;
            D_800DCE34 = arg2;
            guMtxL2F(mf, arg2);
            func_150A7E40(mf, ((struct17 *)arg0)->unk0, ((struct17 *)arg0)->unk4, ((struct17 *)arg0)->unk8,
                          &((struct17 *)arg1)->unk0, &((struct17 *)arg1)->unk4, &((struct17 *)arg1)->unk8);
            D_800DCE30 = 4;
        } else {
            D_800DCE30 = 5;
            D_800DCE34 = arg2;
            func_150A7E40(arg2, ((struct17 *)arg0)->unk0, ((struct17 *)arg0)->unk4, ((struct17 *)arg0)->unk8,
                          &((struct17 *)arg1)->unk0, &((struct17 *)arg1)->unk4, &((struct17 *)arg1)->unk8);
            D_800DCE30 = 6;
        }
    } else {
        D_800DCE30 = 7;
        func_15142314(arg2, 0, arg1);
        D_800DCE30 = 8;
    }
    D_800DCE30 = 0;
}
