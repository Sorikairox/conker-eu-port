extern u32 D_800AAEE0[];
extern u8 D_800AAEE8[];
void func_15143134(void *, void *, void *);

// object_bone_point: transforms point `kind` (0 or 1) of the D_800AAEE8 offset table (3 floats each) by the bone
// matrix at byte offset D_800AAEE0[kind] in the object's matrix block (obj+0x1D4) and writes it to out.
void func_151C6F7C(u8 *obj, f32 *out, u8 kind) {
    func_15143134(D_800AAEE8 + kind * 12, out, *(u8 **)(obj + 0x1D4) + D_800AAEE0[kind]);
}
