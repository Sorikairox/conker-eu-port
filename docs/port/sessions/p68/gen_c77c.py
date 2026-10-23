# setups for func_1512C77C
# P68: knob addresses are EU addresses (func_15048FC8 = 0x150492B8, func_15048A70 = 0x15048D60; mips nm build/conker.eu.elf)
import struct, itertools
def h(f): return struct.unpack('>I', struct.pack('>f', f))[0]
B=0x80420000
def line(n, flag, cam, ctr, rad, fc8, a70):
    pk={B+0x948:flag<<24, B+0x2F8:h(cam[0]), B+0x2FC:h(cam[1]), B+0x300:h(cam[2]), B+0x93C:h(ctr[0]), B+0x940:h(7.0),
        B+0x944:h(ctr[1]), B+0x938:h(rad), B+0x2A4:h(100.0), B+0x2A8:h(20.0), B+0x2AC:h(-50.0), B+0x37C:h(123.0), B+0x930:h(9.0)}
    rf=f"150492B8={h(fc8[0]):X};{h(fc8[1]):X},15048D60={h(a70):X}"
    return f"{n} ! 0={B:X} ! "+",".join(f"{a:X}={v:08X}" for a,v in pk.items())+f" ! ! {rf} ! ! !"
i=0
for flag in [0,1,0x80]:
    for cam,ctr,rad in [((1,5,2),(0,0),10.0),((10,5,0),(0,0),10.0),((3,5,4),(0,0),5.0),((30,1,1),(2,2),3.0),((-1,2,-1),(0,0),2.0)]:
        for fc8 in [(10.0,350.0),(190.0,-20.0)]:
            for a70 in [0.0,-0.0,34.9,35.0,-34.9,-35.0,-1.0,1.0,100.0]:
                print(line(f"c{i}",flag,cam,ctr,rad,fc8,a70)); i+=1
