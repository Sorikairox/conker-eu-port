# wrap the address operand of every store with (call $p161cN addr (i32.const off)) that traps if it touches wasm 0x14..0x17
import sys,re
src,dst=sys.argv[1],sys.argv[2]
L=open(src).read().split('\n')
SZ={'i32.store':4,'i64.store':8,'f32.store':4,'f64.store':8,'i32.store8':1,'i32.store16':2,'i64.store8':1,'i64.store16':2,'i64.store32':4}
pat=re.compile(r'^(\s*)\((i32\.store(?:8|16)?|i64\.store(?:8|16|32)?|f32\.store|f64\.store)((?: offset=\d+)?(?: align=\d+)?)\s*$')
out=[];n=0;skip=0;i=0;first_func=True
while i<len(L):
    l=L[i]
    if first_func and l.startswith(' (func '):
        for s in (1,2,4,8):
            out.append(f' (func $p161c{s} (param $a i32) (param $o i32) (result i32)\n  (if (i32.and (i32.lt_u (i32.add (local.get $a) (local.get $o)) (i32.const 24)) (i32.gt_u (i32.add (i32.add (local.get $a) (local.get $o)) (i32.const {s})) (i32.const 20)))\n   (then (unreachable)))\n  (local.get $a)\n )')
        first_func=False
    m=pat.match(l)
    if not m:
        if re.match(r'^\s*\((i32|i64|f32|f64)\.store',l): skip+=1
        out.append(l); i+=1; continue
    off=re.search(r'offset=(\d+)',m.group(3)); off=int(off.group(1)) if off else 0
    sz=SZ[m.group(2)]
    out.append(l)
    # address operand: next balanced expression
    j=i+1; d=L[j].count('(')-L[j].count(')'); k=j
    while d>0: k+=1; d+=L[k].count('(')-L[k].count(')')
    ind=L[j][:len(L[j])-len(L[j].lstrip())]
    out.append(f'{ind}(call $p161c{sz}')
    out.extend(L[j:k+1])
    out.append(f'{ind} (i32.const {off}))')
    n+=1; i=k+1
open(dst,'w').write('\n'.join(out))
print('wrapped',n,'skipped',skip)
