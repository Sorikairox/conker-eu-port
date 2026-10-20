extern u8 D_8002D810[];
extern u8 D_8002DC10[];

void func_1600078C(void) {
    s32 base;
    u32 addr;
    u32 lo;
    s32 x;
    u32 i;
    u32 val;
    u8 prefix;

    base = *(s32 *)((u8 *)D_1600389C + 0xF4);
    func_16001338(0, 255, 0);
    func_160012B0(11, D_160047B0);
    addr = D_16003B4C * 4 + base;
    if ((addr & 3) == 0 && addr >= 0x80000000U && addr < 0x80800001U) {
        if (D_16003B4C == 0) {
            func_16001338(255, 0, 0);
            lo = (u32)D_8002D810;
        } else {
            lo = (u32)D_8002D810;
            if (addr >= lo && addr < lo + 0x400) {
                func_16001338(128, 128, 255);
            } else if (addr >= (u32)D_8002DC10 && addr < (u32)D_8002DC10 + 0x4000) {
                func_16001338(255, 128, 128);
            } else {
                func_16001338(255, 255, 255);
            }
        }
        x = 0x61;
        for (i = 0; i < 22; i++) {
            func_16001044(x, 0, addr);
            func_160012B0(x + 8, D_160047BC);
            val = *(u32 *)addr;
            prefix = val >> 24;
            if (prefix == 0x80) {
                func_16001338(128, 128, 255);
            } else if (prefix == 0x15) {
                func_16001338(255, 0, 0);
            } else if (prefix == 0x16) {
                func_16001338(128, 255, 128);
            } else if (prefix == 0x10) {
                func_16001338(255, 0, 0);
            } else {
                func_16001338(255, 255, 255);
            }
            func_16001044(x + 0xC, 0, val);
            func_160012B0(x + 0x16, D_160047C0);
            func_16001338(255, 255, 255);
            func_16001044(x + 0x16, 1, val);
            if (addr >= lo && addr < lo + 0x400) {
                func_16001338(128, 128, 255);
            } else if (addr >= (u32)D_8002DC10 && addr < (u32)D_8002DC10 + 0x4000) {
                func_16001338(255, 128, 128);
            } else {
                func_16001338(255, 255, 255);
            }
            x += 0x20;
            addr += 4;
        }
    }
}
