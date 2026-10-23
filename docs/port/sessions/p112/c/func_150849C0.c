void func_150847B4(u8 *arg0);
void func_100043B4(s32 *arg0, u32 arg1);
void func_10004074(void *);

// object_release_models: release the shared model resources of an object that goes away (called by the object
// removal func_15060F28 for kinds other than 2 / 3). For each part id of the object (+0x2C4 list, +0x2C9 count):
// the D_800D1588 and D_800D1C90 blocks of the part are freed unless another live object (of the first 25, kind byte
// +4 != 0xFF, +5 != 2) has a part that uses the same block; then every D_800D1588 slot holding that block is
// cleared. When no other object has the same part id, the per-kind buffers D_800C5C08 / D_800C6070 / D_800C6360
// (indexed by the object's kind +4, as the asm does) are freed.
void func_150849C0(struct127 *obj) {
    u8 *o = (u8 *) obj;
    u8 *parts;
    u8 *other;
    u8 *list;
    s32 kind = o[4];
    s32 nparts;
    s32 self;
    s32 freeModel;
    s32 freeRecord;
    s32 lastUser;
    s32 j;
    s32 k;
    s32 q;
    s32 id;
    s32 model;
    struct124 *record;

    if (kind == 0xFF || (&D_800D19A0)[kind] == 0) {
        return;
    }
    nparts = o[0x2C9];
    parts = *(u8 **) (o + 0x2C4);
    func_150847B4(o);
    self = obj - D_800CC2D0;
    lastUser = 1;
    for (j = 0; j < nparts; j++) {
        freeModel = 1;
        freeRecord = 1;
        for (k = 0; k < 25; k++) {
            if (k == self) {
                continue;
            }
            other = (u8 *) &D_800CC2D0[k];
            if (*(s32 *) other == 0 || other[4] == 0xFF || other[5] == 2) {
                continue;
            }
            list = *(u8 **) (other + 0x2C4);
            id = parts[j];
            model = D_800D1588[id];
            record = D_800D1C90[id];
            for (q = 0; q < other[0x2C9]; q++) {
                if (list[q] == id) {
                    lastUser = 0;
                }
                if (D_800D1588[list[q]] == model && model != 0) {
                    freeModel = 0;
                }
                if (D_800D1C90[list[q]] == record && record != NULL) {
                    freeRecord = 0;
                }
            }
        }
        if (freeModel && (model = D_800D1588[parts[j]]) != 0) {
            func_100043B4((s32 *) (model - 0x10), 3);
            for (k = 0; k < 187; k++) {
                if (D_800D1588[k] == model) {
                    D_800D1588[k] = 0;
                }
            }
        }
        if (freeRecord && D_800D1C90[parts[j]] != NULL) {
            func_100043B4((s32 *) ((u8 *) D_800D1C90[parts[j]] - 0x10), 3);
            D_800D1C90[parts[j]] = NULL;
        }
        if (lastUser && (&D_800D19A0)[parts[j]] != 0) {
            if (D_800C5C08[kind] != 0) {
                func_10004074((void *) D_800C5C08[kind]);
                D_800C5C08[kind] = 0;
                func_10004074((void *) D_800C6070[kind]);
                D_800C6070[kind] = 0;
            }
            if (D_800C6360[kind] != 0) {
                func_10004074((void *) D_800C6360[kind]);
                D_800C6360[kind] = 0;
            }
        }
        lastUser = 1;
    }
}
