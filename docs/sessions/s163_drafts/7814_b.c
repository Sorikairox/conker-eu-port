typedef struct { f32 x, y, z; } V37814;
typedef struct {
    u8 *p;
    u8 pad4;
    u8 f5;
    u8 pad6[2];
    V37814 pos;
    f32 r;
} Link7814;
extern s32 (*D_80090040[])(u8 *);
f32 func_15143E64(V37814 *);
void func_151D7D78(u8 *);
void func_151D7DE0(u8 *);

void func_151D7814(u8 *arg0) {
    s32 pad; // fakematch: frame slot above pos
    V37814 pos;
    u8 flag;
    V37814 d;
    Link7814 *s;

    pos = *(V37814 *)(arg0 + 0x30);
    flag = arg0[0x2D] & 1;
    if (D_80090040[arg0[0x2C]](arg0) == 0) {
        *(s16 *)(arg0 + 0xE) = -1;
        arg0[0xD] |= 1;
        return;
    }
    s = (Link7814 *)(arg0 + 0x28);
    if (s->f5 & 1) {
        if (flag) {
            d.x = s->pos.x - pos.x;
            d.y = s->pos.y - pos.y;
            d.z = s->pos.z - pos.z;
            if (func_15143E64(&d) < s->r) {
                if (s->p == NULL) {
                    func_151D7DE0(arg0);
                }
            } else {
                func_151D7D78(arg0);
            }
        } else {
            func_151D7D78(arg0);
        }
    } else {
        func_151D7D78(arg0);
    }
}
