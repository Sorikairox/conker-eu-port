# P94: disassemble an RSP text range.  rspdis.py BIN TEXTOFF END IMEMBASE
import sys, rabbitizer
b=open(sys.argv[1],'rb').read(); s=int(sys.argv[2],16); e=int(sys.argv[3],16); base=int(sys.argv[4],16)
for o in range(s,e,4):
    w=int.from_bytes(b[o:o+4],'big')
    i=rabbitizer.Instruction(w, vram=base+o-s, category=rabbitizer.InstrCategory.RSP)
    print(f"{base+o-s:04X} {w:08X} {i.disassemble()}")
