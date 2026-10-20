
struct B73 { u8 hi : 6; u8 lo : 2; };
void func_1511E14C(u8 *arg0) {
    s32 var_v0;
    u8 *var_v1;
    u8 *temp_v0;
    f32 temp_f12;
    f32 temp_f2;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x7C));
    if (temp_v0 == NULL) {
        var_v1 = allocate_memory(0x10, 1, 0, 0);
        (*(u8 **)((u8 *)arg0 + 0x7C)) = var_v1;
        (*(f32 *)((u8 *)var_v1 + 0)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 4)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 8)) = 0.0f;
        (*(f32 *)((u8 *)var_v1 + 0xC)) = 0.025f;
    } else {
        var_v1 = temp_v0;
    }
    var_v0 = ((struct B73 *)(arg0 + 0x73))->lo;
    if (var_v0 == 0) {
        (*(f32 *)((u8 *)arg0 + 8)) = 0.0f;
    } else if (var_v0 == 3) {
        (*(f32 *)((u8 *)arg0 + 8)) = 90.0f;
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) ((*(f32 *)((u8 *)arg0 + 8)) + (cosf((*(f32 *)((u8 *)var_v1 + 0)) * 0.017453292f) * 0.5f));
        (*(f32 *)((u8 *)var_v1 + 0)) = (f32) ((*(f32 *)((u8 *)var_v1 + 0)) + (3.0f * (f32) D_800BE9E4));
    } else if (var_v0 == 2) {
        if ((*(f32 *)((u8 *)arg0 + 8)) == 0.0f) {
            (*(f32 *)((u8 *)var_v1 + 4)) = 0.0f;
            (*(f32 *)((u8 *)var_v1 + 8)) = 0.0f;
        }
        (*(f32 *)((u8 *)var_v1 + 8)) = (f32) ((*(f32 *)((u8 *)var_v1 + 8)) + (*(f32 *)((u8 *)var_v1 + 0xC)));
        (*(f32 *)((u8 *)var_v1 + 4)) = (f32) ((*(f32 *)((u8 *)var_v1 + 4)) + (*(f32 *)((u8 *)var_v1 + 8)));
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) ((*(f32 *)((u8 *)arg0 + 8)) + (*(f32 *)((u8 *)var_v1 + 4)));
        if ((*(f32 *)((u8 *)arg0 + 8)) >= 90.0f) {
            var_v0 = 3;
            (*(f32 *)((u8 *)arg0 + 8)) = 90.0f;
        }
    } else {
        temp_f2 = (*(f32 *)((u8 *)arg0 + 8));
        temp_f12 = (f32) D_800BE9E4;
        if (temp_f12 < temp_f2) {
            (*(f32 *)((u8 *)arg0 + 8)) = (f32) (temp_f2 - temp_f12);
        } else {
            (*(f32 *)((u8 *)arg0 + 8)) = 0.0f;
            var_v0 = 0;
        }
    }
    ((struct B73 *)(arg0 + 0x73))->lo = var_v0;
}
