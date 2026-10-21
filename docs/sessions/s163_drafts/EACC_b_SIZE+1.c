typedef struct { f32 x, y, z; } V3EACC;
typedef struct { V3EACC a; V3EACC b; s32 u18; } EEACC;
u8 *func_151CEBE4(s32);
s32 func_1505D024();
void func_1515C710(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);

void func_151CEACC(u8 *arg0, u8 *arg1) {
    V3EACC pos;
    f32 h;
    f32 r;
    u8 *e;
    s32 i;
    s32 pad[6]; // fakematch: frame space

    e = func_151CEBE4(*(s32 *)(arg1 + 0x18));
    if (e != NULL) {
        func_1515C710(arg0, &pos.x, &h, &r);
        if (*(u16 *)(e + 0x1E) & 8) {
            if (*(s8 *)(e + 0x2C) > 0) {
                i = *(s8 *)(e + 0x2E) - 1;
                if (i < 0) {
                    i = e[0x25] - 1;
                }
                if (pos.y - r <= (*(EEACC **)(e + 0x94))[i].a.y) {
                    func_1505D024(arg0, 0x60019, 0, -1);
                }
            }
        } else if (*(s8 *)(e + 0x2C) > 0 && (*(EEACC **)(e + 0x94))[*(s8 *)(e + 0x2D)].a.y <= pos.y + r) {
            func_1505D024(arg0, 0x60019, 0, -1);
        }
    }
}
