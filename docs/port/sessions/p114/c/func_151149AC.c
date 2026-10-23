// world_record_find: returns the world-object record (0xA0 bytes, D_800DBEF4[0 .. D_800DC320 - 1]) whose id byte
// +0x72 equals id, or NULL; id 0 never matches. Scene tracks with ref kind 3 and scene event 5 / 3 look records up here.
u8 *func_151149AC(u8 id) {
    u8 *rec;
    s32 i;

    if (id == 0) {
        return NULL;
    }
    rec = (u8 *) D_800DBEF4;
    for (i = 0; i < D_800DC320; i++, rec += 0xA0) {
        if (rec[0x72] == id) {
            return rec;
        }
    }
    return NULL;
}
