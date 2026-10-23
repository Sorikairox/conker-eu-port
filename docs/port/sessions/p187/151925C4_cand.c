struct260 *func_15192150(u8 *obj, f32 *offset, u8 kind, f32 a3, f32 arg4, s16 life, f32 arg6, f32 arg7, s16 arg8, s16 arg9, u8 arg10, u8 arg11, f32 arg12, f32 arg13, f32 arg14, u8 arg15, u8 arg16, s32 arg17);
/* per-dust-type parameters for func_15192150 (rodata), indexed by func_151925C4's type */
extern f32 D_800A8410[4][3];
extern u8 D_800A8440[4];
extern f32 D_800A8444[4];
extern f32 D_800A8454[4];
extern f32 D_800A8464[4];
extern f32 D_800A8474[4];
extern s16 D_800A8484[4];
extern s16 D_800A848C[4];
extern f32 D_800A8494[4];
extern f32 D_800A84A4[4];
extern f32 D_800A84B4[4];
extern u8 D_800A84C4[4];
// obj_dust_effect: the dust / splash effect for obj's kind (obj +4): kinds 0..4 -> type 0, 0x10 -> 1, 0x58 -> 2,
// 0x79 -> 3, others none; spawns it through func_15192150 with that type's parameters (D_800A8410 ..). life -1 =
// untimed. Returns the effect object (NULL for none / NULL obj). Callers func_150268BC (game_eu_51190, twice),
// func_1506F05C (game_981E0).
struct260 *func_151925C4(u8 *obj, s16 life, u8 arg2, s32 arg3) {
    s32 type;

    if (obj == NULL) {
        return NULL;
    }
    switch (obj[4]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            type = 0;
            break;
        case 0x10:
            type = 1;
            break;
        case 0x58:
            type = 2;
            break;
        case 0x79:
            type = 3;
            break;
        default:
            type = -1;
            break;
    }
    if (type == -1) {
        return NULL;
    }
    return func_15192150(obj, D_800A8410[type], D_800A8440[type], D_800A8444[type], D_800A8454[type], life,
                         D_800A8464[type], D_800A8474[type], D_800A8484[type], D_800A848C[type], 100, 155,
                         D_800A8494[type], D_800A84A4[type], D_800A84B4[type], D_800A84C4[type], arg2, arg3);
}
