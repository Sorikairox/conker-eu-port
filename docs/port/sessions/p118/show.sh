#!/bin/bash
# show.sh FUNC PATTERN-src [PATTERN-asm]: NM source lines matching, asm lines matching
cd /Users/sorikairo/conker-wt/web
f=$1; ps=$2; pa=${3:-$2}
file=$(grep -l "^[a-zA-Z].*\b$f(" conker/src_eu -r | head -1)
echo "== $file"
awk -v f="$f" '$0 ~ "^[A-Za-z].*[ *]"f"\\(" && $0 ~ /\{/ {p=1} p{print NR": "$0} p && /^}/ {exit}' $file | grep -E "$ps" | head -${N:-12}
echo "== asm"
awk -v f="<$f>:" '$2==f{p=1;next} p && /^$/{exit} p && /^[0-9a-f]+ </{exit} p' port/build/arity/eu_elf.dis | grep -E "$pa" | head -${M:-14}
