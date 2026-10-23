void func_1504715C(void *, u8 *);
s32 func_15134070(struct127 *);
extern f32 D_800AA500[3]; /* (0, -12, 96): offset of the effect from the model node */

// object_hit_flash_spawn: P153: spawns the hit flash (func_15154488 parameter block) on obj's model node
// (obj +0x1D4, +0x180) for the target's class: 4 without a target or for target types 0x53 / 0xA5, else
// func_15134070(target); nothing for class 0x63, a class mode (D_800A43B8[class] byte 0xE) of 2, obj without a
// model, or obj +0x74 low nibble 0xF. Angle: (u8) ((+0x7A >> 8) + 0x40) - 0x68; +0x3C set for class mode 1.
// The asm leaves v0 unset; the callers (func_15194794, game_981E0) declare an int result and ignore it: 0 here.
s32 func_151B01B8(u8 *obj, u8 *target) {
    struct_eu_15154488 p;
    s32 basis[10];
    u8 *cls;
    s32 class;
    u8 yaw;

    if (obj == NULL || *(s32 *) (obj + 0x1D4) == 0 || (obj[0x74] & 0xF) == 0xF) {
        return 0;
    }
    func_1504715C(basis, obj);
    class = 4;
    if (target != NULL) {
        if (target[4] == 0x53 || target[4] == 0xA5) {
            class = 4;
        } else {
            class = func_15134070((struct127 *) target);
        }
    }
    if (class == 0x63) {
        return 0;
    }
    cls = D_800A43B8[class];
    if (cls[0xE] == 2) {
        return 0;
    }
    yaw = (*(u16 *) (obj + 0x7A) >> 8) + 0x40;
    func_15143134(D_800AA500, &p.unk8, *(u8 **) (obj + 0x1D4) + 0x180);
    p.unk0 = yaw - 0x68;
    p.unk14 = 7.22f;
    p.unk2C = 0xA;
    p.unk2E = 0x14;
    p.unk2 = 0xD0;
    p.unk4 = -0x1B;
    p.unk6 = 0x36;
    p.unk30 = 3;
    p.unk32 = 2;
    p.unk34 = 0x1E;
    p.unk36 = 0x28;
    p.unk38 = 0x9B;
    p.unk3A = 0x64;
    p.unk18 = 3.04f;
    p.unk1C = 0.81000006f;
    p.unk20 = 0.40500003f;
    p.unk24 = 6.0f;
    p.unk28 = 13.900001f;
    p.unk40 = 0.5f;
    if (cls[0xE] == 1) {
        p.unk3C = 1;
    } else {
        p.unk3C = 0;
    }
    p.unk44 = 0x10;
    p.unk46 = 0xF;
    p.unk48 = 0;
    func_15154488(&p, &p.unk8, (s32) basis, 0xFF, 1);
    return 0;
}
