//HOIST void func_15059C84(struct127 *);
extern f32 D_800CC630;
extern f32 D_800CC634;
extern f32 D_800CC638;
extern s32 D_800D1968;

void func_15059C84(struct127 *rec) {
    u8 *arg0 = (u8 *) rec;
    f32 tri[9];
    s32 i;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    u16 sp76;
    s32 sp74;
    s32 sp50;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f6;
    f32 temp_f8;
    f32 var_f12;
    s16 var_t5;
    u16 temp_t5;
    u8 temp_v0;
    u8 temp_v0_3;
    u8 temp_v0_5;
    u8 *temp_v0_2;
    u8 *temp_v0_4;
    u8 *temp_v1;
    u8 *var_v0;
    u8 *var_v1;

    var_f12 = (*(f32 *)((u8 *)arg0 + 0x3C));
    sp76 = (*(u16 *)((u8 *)arg0 + 0x76));
    if (D_800D1968 != 1) {
        temp_v0 = (*(u8 *)((u8 *)arg0 + 0x1FC));
        if (temp_v0 & 8) {
            (*(u8 *)((u8 *)arg0 + 0x1FC)) = (u8) (temp_v0 & 0xFFF7);
            return;
        }
        if ((*(u8 *)((u8 *)arg0 + 0x127)) != 0xFF) {
            temp_v0_2 = (*(u8 **)((u8 *)arg0 + 0x31C));
            if ((*(s16 *)((u8 *)temp_v0_2 + 0x46)) > 0) {
                temp_t5 = sp76 + (*(u16 *)((u8 *)temp_v0_2 + 0x10));
                sp76 = temp_t5;
                (*(u16 *)((u8 *)arg0 + 0x7A)) = temp_t5;
            }
        }
        if (((*(f32 *)((u8 *)arg0 + 0x3C)) < 1.0f) && ((*(f32 *)((u8 *)arg0 + 0x3C)) >= 0.0f) && !((*(u8 *)((u8 *)arg0 + 0x1FC)) & 1)) {
            temp_v0_3 = (*(u8 *)((u8 *)arg0 + 0x7E));
            if ((s32) temp_v0_3 < 0xFA) {
                (*(u8 *)((u8 *)arg0 + 0x7E)) = (u8) (temp_v0_3 + 1);
            }
            if (((*(f32 *)((u8 *)arg0 + 0x164)) == 0.0f) && ((*(f32 *)((u8 *)arg0 + 0x168)) == 0.0f) && ((*(f32 *)((u8 *)arg0 + 0x16C)) == 0.0f) && ((*(f32 *)((u8 *)arg0 + 0x170)) == 0.0f)) {
                (*(f32 *)((u8 *)arg0 + 0x1F4)) = 0.0f;
                return;
            }
            goto block_17;
        }
        (*(u8 *)((u8 *)arg0 + 0x7E)) = 0U;
block_17:
        if ((((*(u8 *)((u8 *)arg0 + 0xAD)) != 0) && ((temp_v0_4 = (*(u8 **)((u8 *)arg0 + 0x31C)), (temp_v0_4 == NULL)) || ((*(u8 *)((u8 *)temp_v0_4 + 0x21)) == 0))) || ((*(u16 *)((u8 *)arg0 + 0x22C)) & 8)) {
            sp84 = (*(f32 *)((u8 *)arg0 + 0xB8));
            if (sp84 > 90.0f) {
                sp84 = 90.0f;
            } else if (sp84 < -90.0f) {
                sp84 = -90.0f;
            }
        } else {
            sp84 = 0.0f;
        }
        temp_v0_5 = (*(u8 *)((u8 *)arg0 + 0x1FC));
        if (temp_v0_5 & 1) {
            (*(u8 *)((u8 *)arg0 + 0x1FC)) = (u8) (temp_v0_5 & 0xFFFE);
            if (*D_800D1550 != 0.0f) {
                var_f12 = 2.0f * (((*(f32 *)((u8 *)arg0 + 0x1F4)) * (*(f32 *)((u8 *)arg0 + 0x14C))) / *D_800D1550);
            }
            (*(f32 *)((u8 *)arg0 + 0x1F4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x3C));
            sp76 = (*(u16 *)((u8 *)arg0 + 0x7A));
        }
        (*(f32 *)((u8 *)arg0 + 0x1F4)) = var_f12;
        func_1505A184(sp76, var_f12, sp84, &sp84, &sp80, &sp7C);
        sp84 += (*(f32 *)((u8 *)arg0 + 0x164)) + (*(f32 *)((u8 *)arg0 + 0x16C));
        sp80 += (*(f32 *)((u8 *)arg0 + 0x168)) + (*(f32 *)((u8 *)arg0 + 0x170));
        if ((*(u8 *)((u8 *)arg0 + 0xAD)) == 0xA) {
            sp7C = 0.0f;
        }
        if ((((*(s32 *)((u8 *)arg0 + 0)) != 1) || ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x4F)) == 0)) && ((*(f32 *)((u8 *)arg0 + 0x28)) <= 0.0f) && ((*(u8 *)((u8 *)arg0 + 0xAD)) == 0)) {
            if (!((*(u16 *)((u8 *)arg0 + 0x22C)) & 8)) {
                for (i = 0; i < 9; i++) {
                    tri[i] = (f32) (*(s16 *)((u8 *)arg0 + 0x18C + i * 2));
                }
                func_15049350(*(struct_eu_bytes24 *)tri);
                if ((D_800CC634 != 0.0f) && ((temp_f12 = ((-D_800CC630 * sp84) - (D_800CC638 * sp80)) / D_800CC634, (temp_f12 > 4.0f)) || ((*(s32 *)((u8 *)arg0 + 0)) != 1) || ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x31C))) + 0x4E)) != 2))) {
                    temp_f14 = (sp84 * sp84) + (sp80 * sp80);
                    temp_f2 = sqrtf(temp_f14 + (temp_f12 * temp_f12));
                    if (temp_f2 != 0.0f) {
                        temp_f0 = sqrtf(temp_f14);
                        sp84 = (sp84 * temp_f0) / temp_f2;
                        sp7C = (temp_f12 * temp_f0) / temp_f2;
                        sp80 = (sp80 * temp_f0) / temp_f2;
                    }
                }
            }
        }
        temp_f8 = sp84 * *D_800D1550;
        temp_f6 = sp80 * *D_800D1550;
        temp_f10 = sp7C * *D_800D1550;
        sp84 = temp_f8;
        sp80 = temp_f6;
        sp7C = temp_f10;
        (*(f32 *)((u8 *)arg0 + 0x14)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) + temp_f8);
        (*(f32 *)((u8 *)arg0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x1C)) + temp_f6);
        (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x18)) + temp_f10);
    }
}
