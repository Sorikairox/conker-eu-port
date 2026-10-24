#ifdef NON_MATCHING
// bone_sparks_release: effect-child handler (D_8008FFE0 [6] / D_8008FFE8 [4]): runs the release handler
// D_8008DA20[self +0x89] (= D_8008DA1C[self +0x89 + 1]; none: -1). The second argument is unused (table signature
// s32 (node, pos)); returns the handler's result (0 without; the dispatchers that reach it ignore v0).
s32 func_1518FDC8(u8 *self, void *pos) {
    s8 release = (s8)self[0x89];

    if (release != -1) {
        return D_8008DA1C[release + 1](self);
    }
    return 0;
}
#else
void func_1518FDC8(u8 *arg0)
{
  u8 *new_var;
  new_var = ((u8 *) arg0) + 0x89;
  if ((*((s8 *) new_var)) != (-1))
  {
    D_8008DA20[*((s8 *) new_var)](arg0);
  }
}
#endif
