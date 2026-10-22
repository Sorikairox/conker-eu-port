# setups for func_151236D0: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB
import itertools
B=0x80420000; O=0x80430000; P=0x80440000
def line(n,f5f0,c2c,b23c,inside,obj,o9c=0,o95=0,p137=0,p28=0x3F800000,o8=0,o16=0,o4e=0):
    pk={B+0x5F0:f5f0,B+0x2C:c2c,B+0x23C:(b23c<<24)|(0x17<<16),B+0x2FC:0x41200000,B+0x360:(0x41300000 if inside==1 else 0x41200000 if inside==2 else 0x41000000),
        B+0x3D4:(O if obj else 0),B+0x3D0:P,B+0x7B0:0x12345678,
        O+0x9C:o9c,O+0x94:o95<<16,O+0x8:o8<<16,O+0x14:o16<<8,O+0x4C:o4e<<8,P+0x134:p137,P+0x28:p28}
    return f"{n} ! 0={B:X} ! "+",".join(f"{a:X}={v:08X}" for a,v in pk.items())+" ! ! ! ! !"
i=0
for old,c2c,b23c,ins in itertools.product([0,1,4,5,0x4C9,0x4C8],[0,0x100,0x40000,0x40100],[0,1],[0,1,2]):
    print(line(f"t{i}",old,c2c,b23c,ins,0)); i+=1
for o9c,o95,p137,p28,o8,o16,o4e in [(1,0,0,0,0,0,0),(0,1,0,0,1,0,2),(0,1,1,0,1,1,2),(0,0,0,0x3F800000,0x100,0,1),(0,1,0,0x3F800000,0,0,2),(0,0,1,0,0x8000,0,3),(0,1,1,0,1,0,0)]:
    for old in [0,0x4C9,0xFFFFFFFF]:
        print(line(f"o{i}",old,0,0,1,1,o9c,o95,p137,p28,o8,o16,o4e)); i+=1
