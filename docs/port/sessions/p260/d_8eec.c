#ifdef NON_MATCHING
void func_1518403C(s32);
s32 func_1510FE58(s32, s32, s32, s32 *);
extern u8 D_8008FC40[3];
// path_hit_scene_nodes: path handler 1 of D_8008FC20 (`s32 (*)(u8 *)`, result tested by the path updater). Returns 0
// when the owner's (**(arg0 + 0x98)) attachment +0x31C is missing, or (clearing bit 0x100 of the owner's u16
// +0x2F8) when that attachment's +0x58 is not 1. Otherwise, for the three scene-node lists D_800DD280[0][t] with
// t from D_8008FC40, it walks each list (safe iteration through D_800DD5C8[++D_800DD5C0]) and, from the path's head
// point +0x2E back to the current point +0x2D (ring of +0x25 points of 0x24 bytes at +0x94, radius f32 +0x18), hits
// the node when its position (+0x98 / +0x9C / +0xA0) is within radius^2 + 900 of a point: sound func_1518403C(5),
// func_15168B10(node, 0x18), state +0xED = 5, +0x94 = D_800DDE80[27], s16 +0x92 = 9, +0xB8 = +0xA8 = 40, +0xB4 = 0,
// +0xC8 = func_1510FE58 at the node's position (then +0x91 = 4). As in the asm, the walk index is set once per list,
// so only the first node of each list sees the points (later nodes start at +0x2D). Returns 1.
s32 func_15198EEC(u8 *arg0) {
    u8 *points = *(u8 **) (arg0 + 0x94);
    u8 *owner = **(u8 ***) (arg0 + 0x98);
    u8 *att = *(u8 **) (owner + 0x31C);
    u8 types[3];
    struct_eu_node *node;
    u8 *n;
    f32 pt[3];
    f32 nx, ny, nz;
    f32 dx, dy, dz;
    f32 r;
    s32 i;
    s32 k;
    s32 v;

    types[0] = D_8008FC40[0];
    types[1] = D_8008FC40[1];
    types[2] = D_8008FC40[2];
    if (att == NULL) {
        return 0;
    }
    if (att[0x58] != 1) {
        *(u16 *) (owner + 0x2F8) &= 0xFEFF;
        return 0;
    }
    for (k = 0; k < 3; k++) {
        node = D_800DD280[0][types[k]];
        if (node == NULL) {
            continue;
        }
        i = *(s8 *) (arg0 + 0x2E);
        D_800DD5C0++;
        while (node != NULL) {
            n = (u8 *) node;
            D_800DD5C8[D_800DD5C0] = node->next;
            nx = *(f32 *) (n + 0x98);
            ny = *(f32 *) (n + 0x9C);
            nz = *(f32 *) (n + 0xA0);
            while (i != *(s8 *) (arg0 + 0x2D)) {
                i--;
                if (i < 0) {
                    i = arg0[0x25] - 1;
                }
                pt[0] = ((f32 *) (points + i * 0x24))[0];
                pt[1] = ((f32 *) (points + i * 0x24))[1];
                pt[2] = ((f32 *) (points + i * 0x24))[2];
                r = ((f32 *) (points + i * 0x24))[6];
                dx = pt[0] - nx;
                dy = pt[1] - ny;
                dz = pt[2] - nz;
                if (dx * dx + dy * dy + dz * dz < r * r + 900.0f) {
                    func_1518403C(5);
                    func_15168B10((s32) node, 0x18);
                    n[0xED] = 5;
                    *(s32 *) (n + 0x94) = D_800DDE80[27];
                    *(s16 *) (n + 0x92) = 9;
                    *(f32 *) (n + 0xB8) = 40.0f;
                    *(f32 *) (n + 0xA8) = 40.0f;
                    *(f32 *) (n + 0xB4) = 0.0f;
                    v = func_1510FE58((s32) *(f32 *) (n + 0x98), (s32) *(f32 *) (n + 0x9C), (s32) *(f32 *) (n + 0xA0),
                                      NULL);
                    n[0x91] = 4;
                    *(f32 *) (n + 0xC8) = v;
                }
            }
            node = D_800DD5C8[D_800DD5C0];
        }
        D_800DD5C0--;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1C3530/func_15198EEC.s")
#endif
