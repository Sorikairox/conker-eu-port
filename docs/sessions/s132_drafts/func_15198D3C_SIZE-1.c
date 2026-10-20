typedef struct { f32 x, y, z; } Vec8D3C;
typedef struct {
    Vec8D3C pos;
    u8 pad0C[0x18];
} Seg8D3C;

s32 func_15198D3C(u8 *arg0) {
    u8 *def = *(u8 **)(arg0 + 0x98);
    Seg8D3C *segs = *(Seg8D3C **)(arg0 + 0x94);
    struct127 *obj;
    s32 n;
    s32 i;
    Vec8D3C pos;
    f32 r;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 ry;
    f32 scale;
    f32 dist;
    f32 lim;
    f32 pad1;
    f32 pad2;

    obj = D_800CC2D0;
    do {
        if ((obj->interaction_state != 0) && (obj->unk65 == 0) && (obj->unique_id != (*(struct127 **)def)->unique_id)) {
            i = *(s8 *)(arg0 + 0x2E);
            while (i != *(s8 *)(arg0 + 0x2D)) {
                i--;
                if (i < 0) {
                    i = arg0[0x25] - 1;
                }
                r = obj->unkE4;
                pos = segs[i].pos;
                dx = pos.x - obj->x_position;
                dz = pos.z - obj->z_position;
                dy = (pos.y - (obj->y_position + (s16)obj->unkE8)) * ((1.0f + r / obj->unkE6) * 0.5f);
                if ((dx * dx + dy * dy + dz * dz) < (r * r + 2500.0f)) {
                    while (i != *(s8 *)(arg0 + 0x2D)) {
                        (*(s8 *)(arg0 + 0x2D))++;
                        if (arg0[0x25] == *(s8 *)(arg0 + 0x2D)) {
                            *(s8 *)(arg0 + 0x2D) = 0;
                        }
                        (*(s8 *)(arg0 + 0x2C))--;
                    }
                }
            }
        }
        obj++;
    } while (obj != (struct127 *)&D_800D121C);
    return 1;
}
