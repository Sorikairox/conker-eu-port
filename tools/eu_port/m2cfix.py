#!/usr/bin/env python3
"""m2cfix.py <listfile> [outdir=conker/build/dfx]  run declfix.fix on the m2c drafts (tools/decomp-permuter/repair/fresh/<f>.c from gensome.sh)
of the functions in listfile (own file used as 'sibling'), write them to outdir, then screen (8 jobs) and print result counts.
Ranked results -> outdir/ranked.txt ("score result func")."""
import sys,os,subprocess,re,shutil
sys.path.insert(0,os.path.dirname(__file__)); import declfix
R=os.path.expanduser('~/conker'); fresh=R+'/tools/decomp-permuter/repair/fresh/'
out=sys.argv[2] if len(sys.argv)>2 else R+'/conker/build/dfx'
shutil.rmtree(out,ignore_errors=True); os.makedirs(out)
stem={}
for l in open(R+'/tools/eu_port/m2c/all.txt').read().split('\n')[1:]:
    t=l.split()
    if len(t)>=4: stem[t[2]]=os.path.basename(t[1])[:-2]
n=0
for f in open(sys.argv[1]).read().split():
    p=fresh+f+'.c'
    if not os.path.exists(p) or f not in stem: continue
    body=open(p).read()
    try: body,notes=declfix.fix(body,f,stem[f],stem[f])
    except Exception as e: notes=['ERR '+str(e)[:40]]
    open(out+'/'+f+'.c','w').write(body); n+=1
print('fixed',n)
rel=os.path.relpath(out,R+'/conker')
shutil.copy(R+'/tools/eu_port/m2c/screen.py',R+'/conker/build/screen.py')
env=dict(os.environ,PATH='/Applications/Docker.app/Contents/Resources/bin:'+os.environ['PATH'])
subprocess.run(['docker','exec','-w','/conker/conker','conkerdev','python3','build/screen.py',rel,'8'],env=env,capture_output=True)
rows=[]
for l in open(out+'/screen.txt'):
    t=l.split()
    if len(t)<2: continue
    r=t[0]; s=0 if r=='OK' else int(r[4:]) if r.startswith('DIFF') and r[4:].isdigit() else 3.5 if r in('SIZE+1','SIZE-1') else 1000
    rows.append((s,r,t[1]))
rows.sort(); open(out+'/ranked.txt','w').write('\n'.join('%s %s %s'%x for x in rows)+'\n')
import collections; print(collections.Counter(re.sub(r'\d+$','',r[1]) if not r[1].startswith('DIFF') else ('DIFF<=4' if r[0]<=4 else 'DIFF5-12' if r[0]<=12 else 'DIFF>12') for r in rows))
