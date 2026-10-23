#!/bin/bash
# loc.sh FUNC...: file holding the asm stub of FUNC in conker/src_eu, EU instruction count, NM-C already present?
cd /Users/sorikairo/conker-wt/port/conker/src_eu
for f in "$@"; do
  fl=$(grep -rl "$f" . | xargs grep -lE "(GLOBAL_ASM|INCLUDE_ASM|#pragma).*$f" 2>/dev/null | tr '\n' ' ')
  n=$(awk -v f="<$f>:" '$2==f{p=1;next} p&&/^[0-9a-f]+ </{exit} p&&NF{c++} END{print c+0}' /Users/sorikairo/conker-wt/port/port_work/p93/eu.dis)
  echo "$f $n [$fl]"
done
