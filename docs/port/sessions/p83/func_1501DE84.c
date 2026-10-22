/* Starts cutscene slot `slot`: script position D_800C39D0[slot] = start D_eu_800C3A60[slot] + D_800BEA08, runs the
 * camera / actor tracks once (func_1501ECA4, func_15020F6C, with func_1502457C around them), then gives every
 * live object that takes part (func_15022A8C, current object index in D_800C3E78) its first actor frame
 * (func_15021834(obj, slot, -1)) and ends with func_1501E888(1, slot). */
void func_1501DE84(s32 slot) {
    struct127 *obj;
    s32 i;

    (&D_800C39D0)[slot] = (&D_eu_800C3A60)[slot] + D_800BEA08;
    func_1502457C(1, 0);
    func_1501ECA4(0);
    func_1502457C(0, 0);
    func_15020F6C(0);
    for (i = 0, obj = D_800CC2D0; i < 25; i++, obj++) {
        if (*(s32 *)obj != 0) {
            D_800C3E78 = i;
            if (func_15022A8C((s32 *)obj) != 0) {
                func_15021834(obj, slot, -1);
            }
        }
    }
    func_1501E888(1, slot);
}
