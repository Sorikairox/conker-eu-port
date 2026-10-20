#!/bin/bash
# objcmp.sh file func [n] (s123): compare words of func in build/src_eu/<file>.c.o vs asm/nonmatchings/<file>/<func>.s (jal/hi/lo masked)
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
cd ~/conker/conker
docker exec -w /conker/conker conkerdev make VERSION=eu build/src_eu/$1.c.o 2>&1 | grep -i 'error' | head -5
docker exec -w /conker/conker conkerdev mips-linux-gnu-objdump -d --no-show-raw-insn -M no-aliases build/src_eu/$1.c.o > /tmp/od_$$.txt 2>/dev/null
docker exec -w /conker/conker conkerdev mips-linux-gnu-objdump -d build/src_eu/$1.c.o | awk -v f="<$2>:" '$2==f{p=1;next} p&&/^$/{exit} p&&/^ +[0-9a-f]+:/{print $2" "$3" "$4" "$5}' > /tmp/odb_$$.txt
grep -o '\*/ .*' asm/nonmatchings/$1/$2.s | sed 's/^\*\/ *//' > /tmp/oda_$$.txt
grep -o '/\* [0-9A-F]* [0-9A-F]* [0-9A-F]* \*/' asm/nonmatchings/$1/$2.s | awk '{print tolower($4)}' > /tmp/odw_$$.txt
python3 - /tmp/odb_$$.txt /tmp/odw_$$.txt /tmp/oda_$$.txt ${3:-15} <<'PY'
import sys
b=[l.split(None,1) for l in open(sys.argv[1]).read().split('\n') if l.strip()]
w=open(sys.argv[2]).read().split(); a=open(sys.argv[3]).read().split('\n')
def m(x):
    v=int(x,16); op=v>>26
    if op in (2,3): return v&0xfc000000
    if op==15 or op in (9,35,43,49,57,32,33,36,37,40,41) : return v&0xffff0000 if False else v
    return v
n=0; out=[]
for i in range(max(len(b),len(w))):
    bw=b[i][0] if i<len(b) else '-'; ww=w[i] if i<len(w) else '-'
    if bw=='-' or ww=='-' or m(bw)!=m(ww):
        n+=1
        if len(out)<int(sys.argv[4]): out.append('%04X %s %s | %s'%(i*4,b[i][1] if i<len(b) else '-',ww,a[i] if i<len(a) else '-'))
print('built %d insns, target %d, %d diff words'%(len(b),len(w),n)); print('\n'.join(out))
PY
rm -f /tmp/od*_$$.txt
