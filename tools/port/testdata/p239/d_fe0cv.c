#ifdef NON_MATCHING
// P239 TEST VARIANT (void, one argument: the shipped s32 (u8 *, void *) is one word longer and its jal to the
// adjacent bone_sparks_emit lands inside the candidate range, which difftest cannot stub).
// bone_sparks_burst: effect-child handler (D_8008FFE0 [4] / D_8008FFE8 [2]): sets the spark counter (self +0x30) to
// base +0x3C + random f32 * spread +0x40 and emits them at once (bone_sparks_emit). The second argument is unused (table
// signature s32 (node, pos)); returns 0 (the asm leaves bone_sparks_emit's v0; the dispatchers that reach it ignore it).
void bone_sparks_burst(u8 *self) {
    f32 *count = (f32 *)(self + 0x30);

    count[0] = count[3] + count[4] * random_float();
    bone_sparks_emit((s32)self);
}
#else
void bone_sparks_burst(s32 arg0)
{
  u8 *new_var;
  u8 *temp_v0;
  f32 *new_var2;
  temp_v0 = ((((((arg0 + 0x30) & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF;
  new_var2 = (f32 *) (((u8 *) temp_v0) + 0);
  new_var = temp_v0;
  *new_var2 = (f32) ((*((f32 *) (((u8 *) new_var) + 0xC))) + ((*((f32 *) (((u8 *) temp_v0) + 0x10))) * random_float()));
  bone_sparks_emit(arg0);
}
#endif
