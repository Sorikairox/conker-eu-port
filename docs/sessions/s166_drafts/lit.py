#!/usr/bin/env python3
# lit.py in.c out.c : replace `extern f32 D_800xxxxx;` with float literals read from the built ELF
import re,sys,struct,subprocess,os
src=open(sys.argv[1]).read()
syms=re.findall(r'^extern f32 (D_800[0-9A-F]{5});\s*$',src,re.M)
dev=os.environ.get('CONKERDEV','conkerdev-a')
def val(s):
    a=int(s[2:],16)
    o=subprocess.run(['docker','exec',dev,'mips-linux-gnu-objdump','-s','--start-address=0x%x'%a,'--stop-address=0x%x'%(a+4),'/conker/conker/build/conker.eu.elf'],capture_output=True,text=True).stdout
    for l in o.splitlines():
        m=re.match(r'\s*([0-9a-f]{8})\s+([0-9a-f]{8})',l)
        if m and int(m.group(1),16)==a: return struct.unpack('>f',bytes.fromhex(m.group(2)))[0]
def lit(v):
    for p in range(1,10):
        s='%.*g'%(p,v)
        if struct.pack('>f',float(s))==struct.pack('>f',v): break
    if 'e' not in s and '.' not in s: s+='.0'
    return s+'f'
for s in syms:
    v=val(s)
    if v is None: print('noval',s); continue
    L=lit(v); print(s,L)
    src=re.sub(r'^extern f32 %s;\s*\n'%s,'',src,flags=re.M)
    src=re.sub(r'\b%s\b'%s,L,src)
open(sys.argv[2],'w').write(src)
