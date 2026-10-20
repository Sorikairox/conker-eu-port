#!/bin/bash
# varsub.sh (s127) file func 'old' 'new1' 'new2' ... : try each replacement of old in src_eu/<file>.c, print objcmp diff count, restore
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
cd ~/conker/conker
stem=$1; f=src_eu/$1.c; fn=$2; old="$3"; shift 3
cp $f build_port/varsub_backup.c
for n in "$@"; do
  python3 - "$f" "$old" "$n" <<'PY'
import sys
p,o,n=sys.argv[1:4]; s=open(p).read(); assert o in s, 'old not found'; open(p,'w').write(s.replace(o,n))
PY
  r=$(../tools/eu_port/objcmp.sh $stem $fn 0 | head -1)
  echo "$r :: $n"
  cp build_port/varsub_backup.c $f
done
