/* Resets cutscene slot `slot` and the shared cutscene state (func_1501D348, before a scene is loaded): no
 * script position / script wait (D_800C39D8 = -100), slot not loaded, no actors, camera actor D_800C3A18 =
 * 0xFF (func_15020F6C picks it again), cleared look / fade state, D_800C3A94 / D_800C3A98 = 999, then
 * func_15023464. */
void func_1501D044(s32 slot) {
    D_800C39D8[slot] = -100;
    (&D_800C39D0)[slot] = 0;
    D_800C39E0[slot] = 0;
    D_800C40AE = 0;
    D_800C3A5A[slot] = 0;
    (&D_800C35EA)[slot] = 0;
    D_800C4170 = NULL;
    D_800C3A18 = 0xFF;
    D_800C3A6C = 0.0f;
    D_800C3A70 = 0.0f;
    D_800C3A74 = 0.0f;
    (&D_800C3A78)[slot] = 0;
    (&D_800C3A7A)[slot] = 0;
    (&D_800C3A7C)[slot] = 1;
    (&D_800C3A7E)[slot] = 0;
    (&D_800C3A80)[slot] = 0;
    (&D_800C3A82)[slot] = 0;
    (&D_800C3A84)[slot] = 0;
    D_800C3638 = 0;
    D_800C3A86 = 0;
    D_800C40AC = 0;
    D_800C40AD = 0;
    D_800C39E2 = 0;
    D_eu_800C3E78 = 0;
    D_800C39C4 = 0.0f;
    D_800C40AA = 0xFF;
    D_800C40AB = 0;
    D_800C3A94 = 999.0f;
    D_800C3A98 = 999.0f;
    D_800C3A9C = 0;
    D_800C3AA0 = 0;
    D_800C3A92 = 0;
    D_800C40BD = 100;
    D_800C40BE = -1;
    func_15023464();
    D_80090124 = 0;
    D_800C3670 = 0;
}
