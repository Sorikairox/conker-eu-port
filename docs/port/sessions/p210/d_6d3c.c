// object_set_scale: P210: script command: sets the current object's scale from the command bytes (two s16 in
// hundredths: D_800D1890 / D_800D1891 = xz, D_800D1892 / D_800D1893 = y, low byte first; D_8009A504 = 0.01),
// copies it to unk154 / unk158 and applies it with func_15062BDC.
void func_15076D3C(void) {
    s16 xz = D_800D1890 | (D_800D1891 << 8);
    s16 y = D_800D1892 | (D_800D1893 << 8);

    D_800D154C->xz_scale = xz * D_8009A504;
    D_800D154C->y_scale = y * D_8009A504;
    D_800D154C->unk154 = D_800D154C->xz_scale;
    D_800D154C->unk158 = D_800D154C->y_scale;
    func_15062BDC(D_800D154C, D_800D154C->xz_scale, D_800D154C->y_scale);
}
