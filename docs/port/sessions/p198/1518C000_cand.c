typedef struct {
    f32 f[4];        // 0x00
    s16 u10;         // 0x10
    s16 u12;         // 0x12
    struct127 *obj;  // 0x14
    u8 id;           // 0x18 obj[0x3B]
    u8 u19;          // 0x19
    u8 u1A;          // 0x1A
} ObjEffect1FSpec;   // 0x1C bytes, copied by func_1518C240
u8 *func_1518C240(s32, u8, s32);

// obj_effect1F_attach: the type-0x1F effect node (lists D_800DD280[0..1][0x1F]) that belongs to `obj` (+0x24) or has
// its id (+0x28 == obj[0x3B]); if there is none, spawns one with func_1518C240 (`arg1`, `arg2` passed on) whose
// parameters depend on the object's kind obj[4]: 0..4 -> 10.0 x4 / 5 / 0, 7 -> (2.76, 5.96, 3.21, 5.0) / 4 / 0x37.
// Nothing for a NULL object or another kind. void: the asm returns the node, but the only caller (game_eu_C5530,
// a void prototype) ignores it.
void func_1518C000(struct127 *obj, s32 arg1, s32 arg2) {
    ObjEffect1FSpec spec;
    struct_eu_node *node;
    s32 i;

    if (obj == NULL) {
        return;
    }
    for (i = 0; i < 2; i++) {
        for (node = D_800DD280[i][0x1F]; node != NULL; node = node->next) {
            if (*(struct127 **) ((u8 *) node + 0x24) == obj || ((u8 *) obj)[0x3B] == *((u8 *) node + 0x28)) {
                return;
            }
        }
    }
    switch (((u8 *) obj)[4]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            spec.u12 = 0;
            spec.u10 = 5;
            spec.u19 = 5;
            spec.u1A = 0x13;
            spec.f[0] = 10.0f;
            spec.f[1] = 10.0f;
            spec.f[2] = 10.0f;
            spec.f[3] = 10.0f;
            break;
        case 7:
            spec.u12 = 0x37;
            spec.u10 = 4;
            spec.u19 = 5;
            spec.u1A = 0x13;
            spec.f[0] = 2.76f;
            spec.f[1] = 5.96f;
            spec.f[2] = 3.21f;
            spec.f[3] = 5.0f;
            break;
        default:
            return;
    }
    spec.obj = obj;
    spec.id = ((u8 *) obj)[0x3B];
    func_1518C240((s32) &spec, arg1, arg2);
}
