#ifdef NON_MATCHING
// prop_owner_effects_clear: P256: for the prop `obj` (a 0xA0-byte record of D_800DBEF4), finds its owner, the first
// live object (interaction_state != 0) of D_800CC2D0[0..24] whose bit is set in the prop's mask D_800DC3C4[index],
// or NULL, then clears effects keyed on it (effect_nodes_broadcast): kinds 0xF9 / 0xF8 / 0xF7 (obj +0x72) clear the type
// 0x35 effects of {9, part list, owner} with the 9-entry part lists g_prop_owner_parts_a / g_prop_owner_parts_b / g_prop_owner_parts_c (copied to
// the stack), kind 0xF6 the type 0x38 effects of {owner}; other kinds do nothing.
typedef struct {
    u8 b[9];
} PartList9;
extern PartList9 g_prop_owner_parts_a; /* was D_800A2750 */
extern PartList9 g_prop_owner_parts_b; /* was D_800A275C */
extern PartList9 g_prop_owner_parts_c; /* was D_800A2768 */
extern s32 *D_800DC3C4;
void prop_owner_effects_clear(u8 *obj) {
    struct {
        s32 count;
        u8 *parts;
        struct127 *owner;
    } key;
    struct {
        struct127 *owner;
    } key38;
    PartList9 parts;
    struct127 *owner;
    struct127 *p;
    s32 mask;
    s32 i;

    owner = NULL;
    mask = D_800DC3C4[(struct131 *) obj - D_800DBEF4];
    if (mask != 0) {
        p = D_800CC2D0;
        for (i = 0; i < 25 && owner == NULL; i++, p++) {
            if (p->interaction_state != 0 && (mask & (1 << i))) {
                owner = p;
            }
        }
    }
    switch (obj[0x72]) {
    case 0xF9:
    case 0xF8:
    case 0xF7:
        key.owner = owner;
        if (obj[0x72] == 0xF9) {
            parts = g_prop_owner_parts_a;
        } else if (obj[0x72] == 0xF8) {
            parts = g_prop_owner_parts_b;
        } else if (obj[0x72] == 0xF7) {
            parts = g_prop_owner_parts_c;
        }
        key.count = 9;
        key.parts = parts.b;
        effect_nodes_broadcast((s32) &key, 0x35);
        break;
    case 0xF6:
        key38.owner = owner;
        effect_nodes_broadcast((s32) &key38, 0x38);
        break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/prop_owner_effects_clear.s")
#endif
