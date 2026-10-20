import sys,os,re,subprocess,collections
from multiprocessing.pool import ThreadPool as Pool
M=os.path.expanduser('~/conker/tools/eu_port/m2c'); sys.path.insert(0,M)
sys.argv=['gen2.py','/tmp/x',  '1','400']
import gen2
need=set(open(os.path.expanduser('~/conker/conker/build_port/s73/undrafted.txt')).read().split())
reasons={}
orig=subprocess.run
def m2c(sp,cx,extra):
    r=orig([gen2.S+'/venv/bin/python','tools/mips_to_c/m2c.py','--valid-syntax','--context',cx]+extra+gen2.m2c_inputs(sp),capture_output=True,text=True)
    f=os.path.basename(sp)[:-2]
    if r.returncode or not r.stdout.strip(): why=['rc%d:%s'%(r.returncode,(r.stderr.strip().split('\n') or [''])[-1][:80])]
    else:
        why=[b for b in gen2.BAD if b in r.stdout]
        if not why and 'M2C' in gen2.post(r.stdout): why=sorted(set(re.findall(r'M2C_\w+',gen2.post(r.stdout))))
    open(os.path.expanduser('~/conker/conker/build_port/s73/diag/'+f+'.txt'),'a').write(' '.join(why)+'\n')
    return None
gen2.m2c=m2c
os.makedirs(os.path.expanduser('~/conker/conker/build_port/s73/diag'),exist_ok=True)
items=[]
for l in open(gen2.S+'/all.txt').read().split('\n')[1:]:
    if not l: continue
    ins,p,f,jt,fl=l.split()
    if f in need:
        m=re.search(r'#pragma GLOBAL_ASM\("([^"]*/%s\.s)"\)'%f,open(p).read())
        if m: items.append((f,p,m.group(1)))
def one(a):
    f,p,sp=a; cx=gen2.ctx(p)
    if gen2.TYPED: cx=gen2.typed_ctx(f,cx,sp)
    m2c(sp,cx,[])
with Pool(8) as pool: pool.map(one,items,chunksize=2)
