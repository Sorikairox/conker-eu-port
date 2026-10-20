//HOIST s32 func_15096E78(s32 arg0);
//DROP s32 func_15096E78(s32);
s32 func_1512DAD0();
extern s32 D_800C3A20;
extern f32 D_800D31D8;
extern s32 D_800D3250;
extern s32 D_800DC450;

s32 func_15096E78(s32 arg0) {
    s32 var_v0;
    u8 temp_t0;
    u8 *temp_v0_2;
    u8 *temp_v1;

    temp_v1 = (arg0 * 0x24) + D_800D31E0;
    switch (temp_v1[0]) {
    case 1: {
        struct108 *temp_a0;
        temp_t0 = (*(u8 *)((u8 *)temp_v1 + 1));
        temp_a0 = &D_800DBFF0[temp_t0];
        D_800D31D8 = temp_a0->unk2C0;
        D_800D2DB4 = 1;
        D_800DBFF4[temp_t0] = 3;
        (*(s32 *)((u8 *)(&D_800C3A20) + 0)) = 1;
        (*(s32 *)((u8 *)(&D_800C3A20) + 4)) = 0;
        temp_v0_2 = ((*(u8 *)((u8 *)temp_v1 + 2)) * 0x18) + D_800DC450;
        (*(f32 *)((u8 *)(&D_800C3A20) + 0x14)) = (f32) (*(s16 *)((u8 *)temp_v0_2 + 0));
        (*(f32 *)((u8 *)(&D_800C3A20) + 0x18)) = (f32) (*(s16 *)((u8 *)temp_v0_2 + 2));
        (*(f32 *)((u8 *)(&D_800C3A20) + 0x1C)) = (f32) (*(s16 *)((u8 *)temp_v0_2 + 4));
        (*(f32 *)((u8 *)(&D_800C3A20) + 0x20)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x14));
        (*(f32 *)((u8 *)(&D_800C3A20) + 0x24)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0xC));
        (*(f32 *)((u8 *)(&D_800C3A20) + 8)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800C3A20) + 0x28)) = (f32) (*(f32 *)((u8 *)temp_v0_2 + 0x10));
        func_1512DAD0(temp_a0, 5, 0, &D_800C3A20);
        func_1512DAD0(temp_a0, 7, &D_800C3A20);
        if (!((*(s32 *)((u8 *)temp_v1 + 0xC)) & 1)) {
            temp_a0->unk3D0->unk7 = 0;
            temp_a0->unk3D0->unk25C |= 0x200;
        }
        *(s32 *)((u8 *)&D_800D3250 + (arg0 * 4)) = (s32) (*(f32 *)((u8 *)temp_v1 + 0x10));
        (*(u8 *)((u8 *)temp_v1 + 0)) = 2U;
    }
block_14:
    default:
        return 1;
    case 2: {
        struct108 *temp_a0_2;
        (*(s16 *)((u8 *)temp_v1 + 4)) = (s16) ((*(s16 *)((u8 *)temp_v1 + 4)) - D_800BE9A0);
        temp_a0_2 = &D_800DBFF0[(*(u8 *)((u8 *)temp_v1 + 1))];
        if (temp_a0_2->unk3D0->health == 0) {
            (*(s16 *)((u8 *)temp_v1 + 4)) = 0;
        }
        if ((*(s16 *)((u8 *)temp_v1 + 4)) <= 0) {
            temp_a0_2->pad3A4 = (*(f32 *)((u8 *)temp_v1 + 0x20));
            var_v0 = (*(s32 *)((u8 *)temp_v1 + 0xC));
            if (!(var_v0 & 2)) {
                func_1512DAD0(temp_a0_2, 6, 0, &D_800C3A20);
                var_v0 = (*(s32 *)((u8 *)temp_v1 + 0xC));
            }
            D_800D2DB4 = 0;
            if (!(var_v0 & 1)) {
                temp_a0_2->unk3D0->unk25C &= ~0x200;
                temp_a0_2->unk3D0->unk7 = 0xFF;
            }
            (*(s16 *)((u8 *)temp_v1 + 4)) = 0;
            (*(u8 *)((u8 *)temp_v1 + 0)) = 0U;
            temp_a0_2->unk2C0 = D_800D31D8;
            return 0;
        }
        goto block_14;
    }
    }
}
