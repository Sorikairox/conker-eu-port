typedef struct { f32 x, y, z; } V3_133A70;
s32 func_15106794(struct102 *);
void func_15106B90(struct102 *);
extern s32 D_80088FB0;

void func_1510660C(struct102 *arg0) {
    s32 (*temp_v1)(struct102 *, u8 *);
    u8 sp2B;
    s8 temp_v0;
    u8 *temp_v0_3;

    sp2B = 0;
    temp_v0 = (*(s8 *)((u8 *)arg0 + 0x44));
    if (temp_v0 != -1) {
        temp_v1 = *(s32 *)((u8 *)&D_80088FB0 + (temp_v0 * 4));
        if ((temp_v1 != NULL) && (temp_v1(arg0, &sp2B) == 0)) {
            func_1516972C(arg0);
        }
    }
    if (arg0->unk12 & 1) {
        arg0->unk10 -= D_800BE9E4;
        if (arg0->unk10 < 0) {
            func_1516972C(arg0);
        }
    }
    if (sp2B != 0) {
        func_15106794(arg0);
    }
    (*(s16 *)((u8 *)arg0 + 0x68)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x68)) - D_800BE9E4);
    if ((*(s16 *)((u8 *)arg0 + 0x68)) < 0) {
        func_15106B90(arg0);
        (*(s16 *)((u8 *)arg0 + 0x68)) = (s16) (((*(s16 *)((u8 *)arg0 + 0x54)) + (func_150ADA20() % (u32) ((*(s16 *)((u8 *)arg0 + 0x56)) + 1))));
    }
    temp_v0_3 = (*(u8 **)((u8 *)arg0 + 0x6C));
    if (temp_v0_3 != NULL) {
        *(V3_133A70 *)(temp_v0_3 + 0x40) = *(V3_133A70 *)((u8 *)arg0 + 0x14);
    }
    temp_v0_3 = (*(u8 **)((u8 *)arg0 + 0x70));
    if (temp_v0_3 != NULL) {
        *(V3_133A70 *)(temp_v0_3 + 0x40) = *(V3_133A70 *)((u8 *)arg0 + 0x38);
    }
}
