#!/bin/bash
# sdiff.sh (s127) file func : structural diff (t-regs, sp offsets, relocs normalised), only size-changing hunks with target asm line index
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
cd ${CONKER_ROOT:-$HOME/conker}/conker
docker exec -w /conker/conker ${CONKERDEV:-conkerdev} make VERSION=eu build/src_eu/$1.c.o 2>&1 | grep -i 'error' | head -5
docker exec -w /conker/conker ${CONKERDEV:-conkerdev} mips-linux-gnu-objdump -d -z -M no-aliases build/src_eu/$1.c.o | awk -v f="<$2>:" '$2==f{p=1;next} p&&/^$/{exit} p&&/^ +[0-9a-f]+:/{$1="";$2="";print}' > /tmp/sda_$$.txt
grep -o '\*/ .*' asm/nonmatchings/$1/$2.s | sed 's/^\*\/ *//' > /tmp/sdb_$$.txt
python3 - /tmp/sda_$$.txt /tmp/sdb_$$.txt <<'PY'
import sys,difflib,re
def norm(l):
    l=l.strip().replace('$','');l=re.sub(r'\s+',' ',l).replace(', ',',')
    parts=l.split(' ',1); op=parts[0]; rest=parts[1] if len(parts)>1 else ''
    if op=='nop': op,rest='sll','zero,zero,0'
    elif op=='beqz': op='beq'; a,b=rest.split(','); rest=a+',zero,'+b
    elif op=='bnez': op='bne'; a,b=rest.split(','); rest=a+',zero,'+b
    elif op=='b': op,rest='beq','zero,zero,'+rest
    elif op=='negu': a,b=rest.split(','); op,rest='subu',a+',zero,'+b
    rest=re.sub(r'%(hi|lo)\([^)]*\)','R',rest); rest=re.sub(r'\b[0-9a-f]+ <[^>]*>|\.L\w+','L',rest)
    rest=re.sub(r'\(0x[0-9A-Fa-f]+ >> 16\)|\(0x[0-9A-Fa-f]+ & 0xFFFF\)','R',rest)
    rest=re.sub(r'-?0x[0-9a-fA-F]+|-?\b\d+\b','N',rest); rest=re.sub(r'\bt\d\b','T',rest)
    if op=='lui': rest='T,R'
    if op.startswith('j'): rest=''
    return op+' '+rest
a=[norm(x) for x in open(sys.argv[1]) if x.strip()]; b=[norm(x) for x in open(sys.argv[2]) if x.strip()]
bo=[x.strip() for x in open(sys.argv[2]) if x.strip()]
print('mine',len(a),'target',len(b))
sm=difflib.SequenceMatcher(None,a,b,autojunk=False)
for t,i1,i2,j1,j2 in sm.get_opcodes():
    if t=='equal': continue
    print('---',t,'mine[%d:%d] tgt[%d:%d] tgtaddr %X'%(i1,i2,j1,j2,j1*4))
    for x in a[i1:i2][:8]: print('  -',x)
    for x in bo[j1:j2][:8]: print('  +',x)
PY
rm -f /tmp/sd?_$$.txt
