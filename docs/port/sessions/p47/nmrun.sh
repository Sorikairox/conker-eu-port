#!/bin/bash
# P47: difftest the inserted NON_MATCHING block of each function listed (col 1, col 2 = file) in $1.
# The candidate = the whole NM block text (keeps its extern declarations). Output: port_work/p47/nmrun.tsv
cd "$(dirname "$0")/../.." && eval "$(tools/eu_port/wt.sh env portb)"
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
O=${OUT:-port_work/p47/nmrun.tsv}; : > $O; mkdir -p port_work/p47/cand
while IFS=$'\t' read f p rest; do
  python3 - "$f" "conker/$p" > port_work/p47/cand/$f.c <<'PY'
import re, sys
f, p = sys.argv[1:]; s = open(p).read()
for m in re.finditer(r'#ifdef NON_MATCHING\n((?:(?!#ifdef NON_MATCHING).)*?)#else\n#pragma GLOBAL_ASM\("[^"]*/(\w+)\.s"\)\n#endif', s, re.S):
    if m.group(2) == f: print(m.group(1)); break
PY
  r=$(DIFFTEST_TIMEOUT=300 tools/port/difftest.sh $f port_work/p47/cand/$f.c 2>&1 | tail -1)
  printf '%s\t%s\n' "$f" "$r" >> $O
done < "$1"
echo DONE >> $O
