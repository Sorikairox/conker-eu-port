void func_1513E13C(struct210 *arg0, f32 x, f32 y, f32 z, f32 w, f32 h, u8 ang) {
    f32 pad[3]; // fakematch
    f32 s;
    f32 c;
    f32 x1, z1, x2, z2;

    s = func_151423D8(ang - 0x40);
    c = func_151423D8(ang);
    x1 = x + (w * c);
    z1 = z + (h * c);
    x2 = x - (w * c);
    z2 = z - (h * c);
    arg0->unk40 = x1 - (h * s);
    arg0->unk42 = y;
    arg0->unk44 = z1 + (w * s);
    arg0->unk50 = x2 - (h * s);
    arg0->unk52 = y;
    arg0->unk54 = z1 - (w * s);
    arg0->unk60 = x2 + (h * s);
    arg0->unk62 = y;
    arg0->unk64 = z2 - (w * s);
    arg0->unk70 = x1 + (h * s);
    arg0->unk72 = y;
    arg0->unk74 = z2 + (w * s);
}
