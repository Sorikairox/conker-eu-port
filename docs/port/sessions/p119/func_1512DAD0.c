/* camera_queue_event: appends event (type, data) to camera cam's event queue D_800DC6E0[cam +0x23D]: 20 slots of
 * { s32 type; void *data; } at +0x00, write index +0xAC (wraps at 20; the read index +0xA8 is func_1512DB74's).
 * The camera event pump func_15129220 drains it. Nothing checks for a full queue (as in the asm). */
void func_1512DAD0(u8 *cam, s32 type, void *data) {
    struct_eu_15B2E0 *q = &D_800DC6E0[cam[0x23D]];
    s32 *slot = (s32 *) ((u8 *) q + q->unkAC * 8);

    slot[0] = type;
    *(void **) (slot + 1) = data;
    q->unkAC++;
    if (q->unkAC == 20) {
        q->unkAC = 0;
    }
}
