#!/usr/bin/env python3
# remove //BEGIN //END markers from all src_eu files
import glob,re,os
os.chdir(os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+'/conker'))
for p in glob.glob('src_eu/**/*.c',recursive=True):
    s=open(p).read()
    t=re.sub(r'^//(BEGIN|END) \w+\n','',s,flags=re.M)
    if t!=s: open(p,'w').write(t); print(p)
