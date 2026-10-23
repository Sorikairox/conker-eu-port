/* Actor pass of cutscene slot `slot`: for each of its D_800C3A5A[slot] actors that has a camera and actor track
 * (D_800C39F0 / D_800C39E8 words != 0) and a record of kind 2 (D_800C3A10[slot] + 8 i), finds the object
 * (func_15083E90(record[2])) and gives it its actor frame (func_15021834(obj, slot, i)). */
void func_150225D0(s32 slot) {
    struct127 *obj;
    u8 *rec;
    s32 i;

    for (i = 0; i < D_800C3A5A[slot]; i++) {
        if (D_800C39F0[slot][i] == 0 || D_800C39E8[slot][i] == 0) {
            continue;
        }
        rec = D_800C3A10[slot] + i * 8;
        if (*(u16 *)rec == 2) {
            obj = func_15083E90(rec[2]);
            if (obj != NULL) {
                func_15021834(obj, slot, i);
            }
        }
    }
}
