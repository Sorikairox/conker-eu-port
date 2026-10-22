/* Load scene `scene` (asset group 3, type 6, found by func_1501D240) of level `level` into sequence slot `slot`.
 * Skipped while the slot is already loaded (D_800C35EA[slot] == 1) or a level change is pending (D_800C35C4).
 * For another level than the current one (D_800BE9F0) the level change is requested instead (func_1501C710;
 * D_800C35C4 = scene + 1, D_800C35C5 = "the slot was empty").
 * The asset is a header {u16 nActors, nCameras, nSounds, nWords} followed by 8-byte records {s32 value, u32 bits}
 * (record 0 is the header pointer itself): nActors actor records, one record for D_800C3A10[slot], nActors
 * more (not read here), nCameras, nSounds, then nWords plain words. The per-slot tables (u16 arrays of
 * bits >> 3, the 30-entry value tables, actor state blocks) are allocated and filled, the optional setup
 * callback D_8008448C[callback] runs, and the sequence is started (func_1501CDA0 ... func_1501DB18). */
typedef void (*SceneSetupFunc)(s32 level, s32 scene, s32 slot, s32 arg);
typedef struct {
    s32 value;
    u32 bits;
} SceneRecord;
typedef struct {
    u8 pad0[4];
    void *keys;        /* +0x04: (count of the actor's u16 entry) words */
    u8 pad8[0x30];
    void *state;       /* +0x38: 0x194 bytes */
    u8 pad3C[4];
} SceneActor;          /* 0x40 bytes, D_800C3E70[slot][actor] */

void *allocate_memory(s32, s32, s32, s32);
void func_1501C710(s32, s32, s32, s32, s32);
void func_1501D044(s32);
void func_1501CDA0(s32);
void func_1501CE34(s32);
void func_15022C4C(s32);
void func_15020430(s32, s32);
void func_15023980(void);
void func_150222DC(s32);
void func_150222F0(s32);
s32 func_1501E888(s32, s32);
void func_1502457C(s32, s32);
s32 func_1501ECA4(s32);
void func_150228F0(s32);
void func_150227FC(s32);
void func_150225D0(s32);
s32 func_15020F6C(s32);
void func_1501DB18(s32);
extern u8 D_800C39C8;
extern u8 D_800C40B8;
extern u16 *D_800C39E8[];        /* actors: bits >> 3 */
extern u16 *D_800C39F0[];        /* cameras */
extern s32 *D_800C3A00[];        /* plain words */
extern SceneActor *D_800C3E70[];
extern void *D_800C3D80[][30];   /* 16-byte block per actor */
extern s32 D_eu_800C3C88[][30];  /* actor record values */
extern s32 D_800C3B98[][30];     /* camera record values */
extern s32 D_800C3AA8[][30];     /* sound record values */
extern SceneSetupFunc D_8008448C[];
extern u16 D_800C40BA;
extern void *D_800C4170;
extern s32 D_800C39D0;
extern u8 *D_800C3A10[];        /* the record after the actors */

void func_1501D348(s32 level, s32 scene, s32 slot, s32 callback, s32 callbackArg) {
    u8 *loaded;
    u8 state;
    SceneRecord *rec;
    u16 *hdr;
    s32 size;
    s32 n;
    s32 i;
    s32 k;

    loaded = &D_800C35EA + slot;
    state = *loaded;
    if (state == 1 || D_800C35C4 != 0) {
        return;
    }
    D_800C3C90 = callback;
    D_800C3C94 = callbackArg;
    if (level != D_800BE9F0) {
        D_800C35C4 = scene + 1;
        func_1501C710(1, level, 0, 0, 0);
        if (*loaded != 0) {
            D_800C35C5 = 0;
        } else {
            D_800C35C5 = 1;
        }
        return;
    }

    (&D_800C3A08)[slot] = scene;
    if (state != 2) {
        D_800C39C8 = D_800BE9F0;
        D_800C40B8 = scene;
    }
    func_1501D044(slot);
    if (func_1501D240(level, scene, slot) == 0) {
        return;
    }
    rec = ((SceneRecord **)&D_800C3A88)[slot];
    hdr = (u16 *)rec[0].value;

    /* the per-slot tables */
    D_800C39E8[slot] = allocate_memory(hdr[0] * 2, 1, 0, 0);
    for (i = 0; i < hdr[0]; i++) {
        D_800C39E8[slot][i] = rec[1 + i].bits >> 3;
    }
    size = ((hdr[1] < hdr[0]) ? hdr[0] : hdr[1]) * 2;
    D_800C39F0[slot] = allocate_memory(size, 1, 0, 0);
    bzero(D_800C39F0[slot], size);
    size = ((hdr[2] < hdr[0]) ? hdr[0] : hdr[2]) * 2;
    D_800C39F8[slot] = allocate_memory(size, 1, 0, 0);
    bzero(D_800C39F8[slot], size);
    D_800C3A00[slot] = allocate_memory(hdr[3] * 4, 1, 0, 0);
    D_800C3E70[slot] = allocate_memory(hdr[0] * sizeof(SceneActor), 1, 0, 0);
    for (i = 0; i < hdr[0]; i++) {
        if (D_800C39E8[slot][i] != 0) {
            D_800C3E70[slot][i].keys = allocate_memory(D_800C39E8[slot][i] * 4, 1, 0, 0);
            D_800C3E70[slot][i].state = allocate_memory(0x194, 1, 0, 0);
        }
    }
    (&D_800C3958)[slot] = allocate_memory(hdr[0] * 0x44, 1, 0, 0);
    for (i = 0; i < hdr[0]; i++) {
        D_800C3D80[slot][i] = allocate_memory(0x10, 1, 0, 0);
    }
    for (i = 0; i < hdr[0]; i++) {
        D_800C39F8[slot][i] = 0;
        D_800C39F0[slot][i] = 0;
        D_800C39E8[slot][i] = 0;
    }
    D_800C3A5A[slot] = hdr[0];

    /* the records */
    k = 1;
    for (i = 0; i < hdr[0]; i++, k++) {
        D_800C39E8[slot][i] = rec[k].bits >> 3;
        D_eu_800C3C88[slot][i] = rec[k].value;
    }
    D_800C3A10[slot] = (u8 *)rec[k].value;
    k += hdr[0];
    for (i = 0; i < hdr[1]; i++, k++) {
        D_800C39F0[slot][i] = rec[k].bits >> 3;
        D_800C3B98[slot][i] = rec[k].value;
    }
    for (i = 0; i < hdr[2]; i++, k++) {
        D_800C39F8[slot][i] = rec[k].bits >> 3;
        D_800C3AA8[slot][i] = rec[k].value;
    }
    for (i = 0; i < hdr[3]; i++) {
        D_800C3A00[slot][i] = rec[k + i].value;
    }

    if (callback != 0) {
        D_8008448C[callback](level, scene, slot, callbackArg);
    }
    n = func_1501D064(slot);
    D_800C40BA = n;
    D_800C4170 = allocate_memory((u16)n * 12, 1, 0, 0);
    (&D_800C39D0)[slot] = 0;

    /* start the sequence */
    func_1501CDA0(slot);
    func_1501CE34(slot);
    func_15022C4C(slot);
    for (i = 0; i < D_800C3A5A[slot]; i++) {
        func_15020430(i, slot);
    }
    func_15023980();
    *loaded = 1;
    D_800C3638 = 1;
    func_150222DC(slot);
    func_150222F0(slot);
    if (D_800C3A5A[slot] == 0) {
        func_1501E888(0, slot);
    }
    func_1502457C(1, slot);
    func_1501ECA4(slot);
    func_150228F0(slot);
    func_150227FC(slot);
    func_150225D0(slot);
    func_15020F6C(slot);
    D_800DBFF4[0] = 4;
    func_1501DB18(slot);
}
