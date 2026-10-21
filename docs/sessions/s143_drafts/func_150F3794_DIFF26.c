extern char D_800A1D20[];
extern f32 D_800BE9A4;
typedef struct {
    u8 *obj;
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
} Sub110;
s32 func_150F3794(u8 *arg0) {
    Sub110 *v = (Sub110 *)(arg0 + 0x110);
    u8 *t = v->obj;
    if ((*(s32 *)t == 0) || (v->unk4 != *(t + 0x3B)) || (*(s32 *)(t + 0x1D4) == 0)) {
        return 0;
    }
    func_15143134(D_800A1D20, arg0 + 0x34, (u8 *)*(s32 *)(t + 0x1D4) + 0x3C0);
    *(f32 *)(arg0 + 0x2C) = *(f32 *)(arg0 + 0x30) = sqrtf(v->unk8) * v->unk10;
    *(u8 *)(arg0 + 0x5C) = (u8)(v->unk14 - v->unk18 * v->unk8 * v->unk8);
    v->unk8 = v->unk8 + D_800BE9A4;
    return v->unkC < v->unk8;
}
