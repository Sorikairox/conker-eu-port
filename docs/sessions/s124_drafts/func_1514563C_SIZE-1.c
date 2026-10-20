s32 func_1514563C(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4) {
    f32 sp10;
    f32 x;
    f32 y;
    f32 z;
    f32 len;
    f32 t;
    f32 tt[1];

    if (arg4 == NULL) {
        arg4 = &sp10;
    }
    x = arg1->unk0;
    y = arg1->unk4;
    z = arg1->unk8;
    len = x * x + y * y + z * z;
    if (len == 0.0f) {
        return 0;
    }
    t = ((x * arg2->unk0 + y * arg2->unk4 + z * arg2->unk8) - (x * arg0->unk0 + y * arg0->unk4 + z * arg0->unk8)) / len;
    tt[0] = t;
    *arg4 = t;
    arg3->unk0 = t * arg1->unk0 + arg0->unk0;
    arg3->unk4 = *arg4 * arg1->unk4 + arg0->unk4;
    arg3->unk8 = *arg4 * arg1->unk8 + arg0->unk8;
    return 1;
}
