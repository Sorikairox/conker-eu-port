typedef struct { s32 x, y, z; } V3i_6700;
s32 func_15156700(s32 arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    u8 *sp44;
    V3i_6700 sp30;
    s32 var_a0;
    u8 *temp_v0;

    switch (arg1) {
    case 0:
        var_a0 = 0x2C;
        break;
    case 1:
        var_a0 = 0x53;
        break;
    default:
        var_a0 = 0x2C;
        break;
    }
    temp_v0 = func_15167A68(var_a0, arg4, arg2 + 0x98, 1, (u8) (s32) arg3, 1U);
    if (temp_v0 == NULL) {
        return 0;
    }
    (*(s16 *)((u8 *)temp_v0 + 0x5E)) = 0;
    (*(u8 *)((u8 *)temp_v0 + 0x64)) = (u8) (*(u8 *)((u8 *)arg0 + 0x24));
    (*(u8 *)((u8 *)temp_v0 + 0x65)) = (u8) (*(u8 *)((u8 *)arg0 + 0x25));
    (*(u8 *)((u8 *)temp_v0 + 0x66)) = (u8) (*(u8 *)((u8 *)arg0 + 0x26));
    (*(s16 *)((u8 *)temp_v0 + 0x60)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x62)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x6E)) = 0;
    (*(u8 *)((u8 *)temp_v0 + 0x67)) = (u8) (*(u8 *)((u8 *)arg0 + 0x27));
    (*(u8 *)((u8 *)temp_v0 + 0x74)) = (u8) (*(u8 *)((u8 *)arg0 + 0x20));
    (*(u8 *)((u8 *)temp_v0 + 0x75)) = (u8) (*(u8 *)((u8 *)arg0 + 0x21));
    (*(u8 *)((u8 *)temp_v0 + 0x76)) = (u8) (*(u8 *)((u8 *)arg0 + 0x22));
    (*(s16 *)((u8 *)temp_v0 + 0x7E)) = 0;
    (*(u8 *)((u8 *)temp_v0 + 0x77)) = (u8) (*(u8 *)((u8 *)arg0 + 0x23));
    (*(u8 *)((u8 *)temp_v0 + 0x84)) = (u8) (*(u8 *)((u8 *)arg0 + 0x20));
    (*(u8 *)((u8 *)temp_v0 + 0x85)) = (u8) (*(u8 *)((u8 *)arg0 + 0x21));
    (*(u8 *)((u8 *)temp_v0 + 0x86)) = (u8) (*(u8 *)((u8 *)arg0 + 0x22));
    (*(u8 *)((u8 *)temp_v0 + 0x87)) = (u8) (*(u8 *)((u8 *)arg0 + 0x23));
    sp30 = *(V3i_6700 *)arg0;
    *(V3i_6700 *)(temp_v0 + 0x28) = sp30;
    *(V3i_6700 *)(temp_v0 + 0x10) = sp30;
    (*(f32 *)((u8 *)temp_v0 + 0x1C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0xC)) * (*(f32 *)((u8 *)arg0 + 0x18)));
    (*(f32 *)((u8 *)temp_v0 + 0x20)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10)) * (*(f32 *)((u8 *)arg0 + 0x18)));
    (*(f32 *)((u8 *)temp_v0 + 0x24)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) * (*(f32 *)((u8 *)arg0 + 0x18)));
    (*(f32 *)((u8 *)temp_v0 + 0x34)) = (f32) ((*(f32 *)((u8 *)arg0 + 0xC)) * (*(f32 *)((u8 *)arg0 + 0x1C)));
    (*(f32 *)((u8 *)temp_v0 + 0x38)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x10)) * (*(f32 *)((u8 *)arg0 + 0x1C)));
    (*(f32 *)((u8 *)temp_v0 + 0x3C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x14)) * (*(f32 *)((u8 *)arg0 + 0x1C)));
    (*(u8 *)((u8 *)temp_v0 + 0x40)) = (u8) (*(u8 *)((u8 *)arg0 + 0x28));
    (*(s16 *)((u8 *)temp_v0 + 0x42)) = (s16) (*(s16 *)((u8 *)arg0 + 0x2A));
    (*(u16 *)((u8 *)temp_v0 + 0x44)) = (u16) (*(u16 *)((u8 *)arg0 + 0x2C));
    (*(f32 *)((u8 *)temp_v0 + 0x48)) = (f32) (*(f32 *)((u8 *)arg0 + 0x30));
    (*(u8 *)((u8 *)temp_v0 + 0x4C)) = (u8) (*(u8 *)((u8 *)arg0 + 0x34));
    (*(s16 *)((u8 *)temp_v0 + 0x4E)) = (s16) (*(s16 *)((u8 *)arg0 + 0x36));
    (*(s16 *)((u8 *)temp_v0 + 0x50)) = (s16) (*(s16 *)((u8 *)arg0 + 0x38));
    sp44 = temp_v0;
    bzero(temp_v0 + 0x88, 0x10);
    return (s32) sp44;
}
