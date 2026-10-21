void func_15145740(struct127 *arg0, s32 arg1_, s32 arg2_, s32 arg3_, f32 arg4) {
    struct17 *arg1 = (struct17 *)arg1_;
    struct17 *arg2 = (struct17 *)arg2_;
    struct17 *arg3 = (struct17 *)arg3_;
    struct { f32 unk0; f32 unk4; f32 unk8; f32 unkC; f32 unk10; s32 unk14; } tmp;
    f32 temp_f6;
    s16 phi_v1;
    s16 phi_t0;

    if ((arg0->id == 0x96) && ((*(u8 *)((u8 *)arg0->unk31C + 0x7D) != 0))) {
        phi_t0 = arg0->unk7A + *(s16 *)((u8 *)arg0->unk31C + 0x80);
    } else {
        if (arg0->unk31C != 0) {
            phi_t0 = arg0->unk7A - *(s16 *)((u8 *)arg0->unk31C + 0x12);
        } else {
            phi_t0 = arg0->unk7A;
        }
    }
    if ((arg0->id == 0x96) && (*(u8 *)((u8 *)arg0->unk31C + 0x7D) != 0)) {
        phi_v1 = *(s16 *)((u8 *)arg0->unk31C + 0x82) + 1024;
    } else {
        phi_v1 = arg0->unk1D1 * 200;
    }
    tmp.unk14 = phi_t0;
    tmp.unk10 = phi_v1 * 0.005493164f;
    tmp.unk0 = tmp.unk10 * D_800A56B4;
    func_1505A184(phi_t0, 2000.0f, tmp.unk10, &arg1->unk0, &arg1->unk8, &arg1->unk4);
    if (arg2 != 0) {
        arg2->unk4 = cosf(tmp.unk0) * 1000.0f;
        temp_f6 = sinf(tmp.unk0) * 1000.0f;
        tmp.unk8 = temp_f6;
        tmp.unk4 = phi_t0 * D_800A56B8;
        arg2->unk0 = cosf(tmp.unk4) * tmp.unk8;
        arg2->unk8 = sinf(tmp.unk4) * -temp_f6;
        if (arg3 != 0) {
            tmp.unkC = tmp.unk0 + arg4;
            arg3->unk4 = cosf(tmp.unkC) * 1000.0f;
            tmp.unk8 = sinf(tmp.unkC) * 1000.0f;
            arg3->unk0 = cosf(tmp.unk4) * tmp.unk8;
            arg3->unk8 = sinf(tmp.unk4) * -tmp.unk8;
        }
    }
}
