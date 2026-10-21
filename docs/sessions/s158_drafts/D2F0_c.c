typedef struct {
    u8 pad0[0x40];
    u32 b31 : 1;
    u32 pad1 : 5;
    u32 b25 : 1;
    u32 b24 : 1;
    u32 b23 : 1;
    u32 rest : 23;
} SrcD2F0;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    u8 unk18;
    u8 pad19[0x57];
    u8 unk70;
    u8 unk71;
    u8 unk72;
    u8 unk73;
    u8 unk74;
    u8 pad75[3];
    f32 unk78;
    u8 pad7C[0x14];
    s32 unk90;
    u8 unk94;
    u8 unk95;
    u8 pad96[2];
    s32 unk98;
    s32 unk9C;
    u8 unkA0;
    u8 padA1[3];
    s32 unkA4[4];
    s32 unkB4;
    s32 unkB8;
    u8 padBC[4];
    Vtx unkC0[4];
    u8 unk100[0x10];
} ObjD2F0;

void *func_1513D2F0(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB) {
    SrcD2F0 *src = arg0;
    ObjD2F0 *temp_v0;
    u8 type;
    s32 i;

    if (src->b23) {
        type = 0x56;
    } else if (src->b25) {
        type = 0x49;
    } else {
        type = 0x1C;
    }
    temp_v0 = func_15167A68(type, argB, arg9 + 0x110, 1, argA, src->b31 ? 2 : 1);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(&temp_v0->unk18, arg0, 0x58);
    temp_v0->unk70 = arg2;
    temp_v0->unk71 = arg3;
    temp_v0->unk72 = arg4;
    temp_v0->unk73 = arg5;
    temp_v0->unk74 = 0;
    bzero(temp_v0->unk100, 0x10);
    func_1513FFF4(temp_v0->unkC0, temp_v0->unk18, arg6);
    func_151400D0(temp_v0->unkC0, (struct_eu_vtxcol *)arg1);
    temp_v0->unk10 = 1;
    temp_v0->unk14 = 0;
    temp_v0->unk98 = 0;
    temp_v0->unk95 = 0;
    temp_v0->unk94 = 0;
    temp_v0->unk90 = 0;
    temp_v0->unk9C = arg7;
    temp_v0->unk78 = -10000.0f;
    temp_v0->unkA0 = 0;
    temp_v0->unkB8 = arg8;
    for (i = 0; i < 4; i++) {
        temp_v0->unkA4[i] = 0;
    }
    temp_v0->unkB4 = 0;
    if (arg7) {
        for (i = 0; i <= D_80082FA0; i++) {
            temp_v0->unkA4[i] = func_1515D9F0(arg7);
        }
        temp_v0->unkB4 = func_1515D9B0();
    }
    return temp_v0;
}
