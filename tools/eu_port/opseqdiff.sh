#!/bin/bash
# opseqdiff.sh file func [ctx] (s125): difflib of mnemonic+operand lines (built .o vs splat .s), sp offsets kept; shows only changed hunks
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
cd ~/conker/conker
docker exec -w /conker/conker conkerdev make VERSION=eu build/src_eu/$1.c.o 2>&1 | grep -i 'error' | head -5
docker exec -w /conker/conker conkerdev mips-linux-gnu-objdump -d -M no-aliases build/src_eu/$1.c.o | awk -v f="<$2>:" '$2==f{p=1;next} p&&/^$/{exit} p&&/^ +[0-9a-f]+:/{$1="";$2="";print}' > /tmp/osa_$$.txt
grep -o '\*/ .*' asm/nonmatchings/$1/$2.s | sed 's/^\*\/ *//' > /tmp/osb_$$.txt
python3 - /tmp/osa_$$.txt /tmp/osb_$$.txt ${3:-2} <<'PY'
import sys,difflib,re,os
SPN=os.environ.get("SPN")
def norm(l):
    l=l.strip().replace('$','')
    l=re.sub(r'\s+',' ',l).replace(', ',',')
    op=l.split(' ')[0]
    al={'beqz':'beq','bnez':'bne','b':'beq'}
    if l.startswith('sll zero,zero,0') or op=='nop': return 'nop'
    if op.startswith('b') or op.startswith('j'): return al.get(op,op)
    if op in ('lui','ori'): return op+' '+l.split(' ')[1].split(',')[0]+',REL'
    l=re.sub(r'%\w+\([^)]*\)','REL',l)
    l=re.sub(r'0x[0-9A-Fa-f]+',lambda m:str(int(m.group(0),16)),l)
    if SPN: l=re.sub(r'-?\d+\(sp\)','N(sp)',l)
    return l
a=[norm(x) for x in open(sys.argv[1]) if x.strip()]
b=[norm(x) for x in open(sys.argv[2]) if x.strip()]
print('mine %d target %d'%(len(a),len(b)))
sm=difflib.SequenceMatcher(None,a,b,autojunk=False)
print('ratio %.3f'%sm.ratio())
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag=='equal': continue
    print('--- %s mine[%d:%d] tgt[%d:%d]'%(tag,i1,i2,j1,j2))
    for x in a[i1:i2][:12]: print('  - '+x)
    for x in b[j1:j2][:12]: print('  + '+x)
PY
rm -f /tmp/os[ab]_$$.txt
