void func_15035220(struct127 *obj, struct_eu_size0C *e, s32 mode, s32 model, s32 mtx, s32 nmtx, f32 a, f32 b, f32 c, f32 d,
                   f32 f, f32 x, f32 y, f32 z, f32 g, f32 h, f32 alpha, s32 shadow, s32 sub);
s32 func_1502DE10(s32 id);
void func_1502D83C(s32 id, u8 *col);
s32 func_150AD9A0(s32 dx, s32 dy, s32 dz);
s32 func_15031360(u8 *att, u8 *obj, s32 *model, s32 *out);
f32 *allocate_memory(s32, s32, s32, s32);

/* P93: queue the draw (and shadow) of object `idx` for this frame. Fades out between max - 200 and max (max = 1400,
 * or 10000 when D_800C35EA == 1) of the camera distance, scaled by obj->unk7 (0xFF = opaque). Reserves the
 * object's joint matrices in the D_800C42A8 arena (func_1502DE10(id) x 0x40 bytes) unless func_15035A04 culls it,
 * then adds one entry per attachment of D_800C3EE0 that belongs to the object (func_15031360 accepts it). */
void func_15035AF8(s32 mode, s32 idx, f32 a, f32 b, f32 c, f32 d, f32 f, f32 g, f32 h, f32 alpha) {
    struct127 *obj;
    struct_eu_size0C *e;
    u8 *att;
    u8 *next;
    s32 col[3];
    s32 model;
    s32 out[4];
    s32 nmtx;
    s32 max;
    s32 dist;
    s32 fade;
    s32 a8;
    s32 mtx;
    s32 shadow;
    u8 opacity;

    if (D_800C4320 == 15) {
        return;
    }
    max = 1400;
    if (mode == 0 && D_800CC2D0[idx].interaction_state != 1) {
        return;
    }
    obj = &D_800CC2D0[idx];
    if (obj->unk1D4 == NULL || (obj->unk74 & 0xF) == 0xF) {
        return;
    }
    opacity = obj->unk7;
    if (opacity == 0) {
        return;
    }
    nmtx = func_1502DE10(obj->id);
    if ((u32) (D_800C3E7C << 6) < (u32) (D_800C42A8 + (nmtx << 6) - D_800C42AC)) {
        return;   /* the matrix arena is full */
    }
    if (D_800C35EA == 1) {
        max = 10000;
    }
    dist = func_150AD9A0((s32) (D_800DBFF0->unk2F8 - obj->x_position), (s32) (D_800DBFF0->unk2FC - obj->y_position),
                         (s32) (D_800DBFF0->unk300 - obj->z_position));
    if ((f32) max < (f32) dist) {
        return;
    }
    fade = 0x100;
    if ((f32) (max - 200) < (f32) dist) {
        fade = (s32) (((f32) max - (f32) dist) * 256.0f / (f32) (max - 200));
    }
    if (opacity != 0xFF) {
        fade = (s32) ((u32) fade * opacity) >> 8;
    }

    e = func_150359B8();
    if (e == NULL) {
        return;
    }
    *(s32 *) &e->unk0[0] = D_800C42A8;
    func_1502D83C(idx, (u8 *) col);
    e->unk0[5] = col[0];
    e->unk0[6] = col[1];
    e->unk0[7] = col[2];
    e->unk0[0xB] = 0;
    e->unk0[8] = idx;
    e->unk0[9] = obj->unique_id;
    model = (s32) obj->unk1D4;
    func_15035220(obj, e, mode, model, *(s32 *) &e->unk0[0], nmtx, a, b, c, d, f, obj->x_position, obj->y_position,
                  obj->z_position, g, h, alpha, 0, 0);
    e->unk0[4] = (s32) ((u32) e->unk0[4] * fade) >> 8;
    if (func_15035A04(mode, (u8 *) obj, (u8 *) model, b) != 0) {
        D_800C4320--;   /* culled: drop the entry again */
        return;
    }
    D_800C42A8 += nmtx << 6;
    D_800C429A += nmtx;

    for (att = (u8 *) D_800C3EE0; att != NULL; att = next) {
        next = *(u8 **) (att + 0x54);
        if (att[0] != obj->unique_id || att[3] == 0) {
            continue;
        }
        e = func_150359B8();
        if (e == NULL) {
            return;
        }
        e->unk0[5] = col[0];
        e->unk0[6] = col[1];
        e->unk0[7] = col[2];
        e->unk0[0xB] = 1;
        e->unk0[8] = idx;
        e->unk0[9] = obj->unique_id;
        e->unk0[0xA] = att[6];
        if (func_15031360(att, (u8 *) obj, &model, out) == 0) {
            continue;
        }
        a8 = (s32) alpha;
        nmtx = 1;
        if (*(u8 **) (att + 0x48) != NULL) {
            nmtx = (*(u8 **) (att + 0x48))[0x3F4];
        }
        mtx = ((s32 *) (att + 0x4C))[D_800BE9C0];
        if (mtx == 0) {
            ((s32 *) (att + 0x4C))[D_800BE9C0] = (s32) allocate_memory(nmtx << 6, 1, 2, 0);
            mtx = ((s32 *) (att + 0x4C))[D_800BE9C0];
        }
        *(s32 *) &e->unk0[0] = mtx;
        shadow = *(s32 *) (att + 0x34) != 0 || *(s32 *) (att + 0x48) != 0;
        func_15035220(NULL, e, mode, model, mtx, nmtx, a, b, c, d, f, obj->x_position, obj->y_position, obj->z_position,
                      g, h, (f32) ((s32) ((u32) a8 * att[3]) >> 8), shadow, 1);
        e->unk0[4] = (s32) ((u32) e->unk0[4] * fade) >> 8;
    }
}
