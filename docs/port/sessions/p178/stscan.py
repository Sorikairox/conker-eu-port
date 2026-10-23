# P178: linear const-propagation over asm/*.s instruction words; report stores hitting [LO,HI) and jal calls whose a0..a3 const lies in [CLO,CHI)
import os,re,sys
LO,HI=0x800D2520,0x800D252C
CLO,CHI=0x800D2000,0x800D252C
root=sys.argv[1]
pat=re.compile(r'/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*)')
ST={0x28:'sb',0x29:'sh',0x2B:'sw',0x3F:'sd',0x39:'swc1',0x3D:'sdc1',0x2A:'swl',0x2E:'swr'}
def s16(x): return x-0x10000 if x&0x8000 else x
for dp,dn,fn in os.walk(root):
  for f in fn:
    if not f.endswith('.s'): continue
    p=os.path.join(dp,f); R={}
    for line in open(p,errors='replace'):
      if 'glabel' in line: R={}
      m=pat.search(line)
      if not m: continue
      va=int(m.group(1),16); w=int(m.group(2),16); op=w>>26; rs=(w>>21)&31; rt=(w>>16)&31; rd=(w>>11)&15|((w>>11)&31); imm=w&0xFFFF
      rd=(w>>11)&31
      def setr(r,v):
        if r: 
          if v is None: R.pop(r,None)
          else: R[r]=v&0xFFFFFFFF
      if op==0x0F: setr(rt,imm<<16)
      elif op==0x09: setr(rt,(R[rs]+s16(imm)) if rs in R else None)
      elif op==0x0D: setr(rt,(R[rs]|imm) if rs in R else None)
      elif op in ST:
        if rs in R:
          a=(R[rs]+s16(imm))&0xFFFFFFFF
          if LO<=a<HI: print(f'STORE {p.split("/")[-2]}/{f} {va:08X} {m.group(3)} {m.group(4)} -> {a:08X}')
      elif op==0x03:
        for r in (4,5,6,7):
          if r in R and CLO<=R[r]<CHI: print(f'CALL {p.split("/")[-2]}/{f} {va:08X} {m.group(4)} a{r-4}={R[r]:08X}')
      elif op==0 and (w&0x3F)==0x21:
        setr(rd,(R[rs]+R[rt]) if rs in R and rt in R else (R[rs] if rt==0 and rs in R else (R[rt] if rs==0 and rt in R else None)))
      elif op==0 and (w&0x3F)==0x25:
        setr(rd,(R[rs]|R[rt]) if rs in R and rt in R else (R[rs] if rt==0 and rs in R else (R[rt] if rs==0 and rt in R else None)))
      elif op==0: setr(rd,None)
      elif op in (0x20,0x21,0x23,0x24,0x25,0x27,0x37,0x0A,0x0B,0x0C,0x0E,0x08,0x18,0x19): setr(rt,None)
