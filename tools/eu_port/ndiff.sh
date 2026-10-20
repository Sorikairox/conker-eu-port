#!/bin/bash
# ndiff.sh func draft.c [n]  (s75) ref vs mine, relocations normalised (lui/%lo immediates -> K), unified diff with 1 line context
R=${CONKER_ROOT:-$HOME/conker}; T=$(mktemp -d)
python3 $R/docs/sessions/s65_drafts/refdiff.py "$1" "$2" 2>/dev/null >/dev/null
s=$(ls $R/conker/asm/nonmatchings/*/$1.s | head -1)
grep -o '^ */\* [0-9A-F]* [0-9A-F]* [0-9A-F]* \*/ *.*' $s | sed -E 's/^ *\/\*.*\*\/ *//; s/\$//g; s/  +/ /g; s/%(hi|lo)\([^)]*\)/K/g; s/\(0x[0-9A-F]+ >> 16\)/K/; s/, /,/g' | sed -E 's/^(lui [a-z0-9]+),.*/\1,K/; s/^(j[a-z]*) .*/\1 F/; s/^(b[a-z]*) (.*),\.L.*/\1 \2,L/; s/^(b) \.L.*/\1 L/' > $T/ref
$R/tools/eu_port/m2c/mine "$1" "$2" | tr ';' '\n' | tail -n +2 | sed -E 's/^ *//; s/\$//g; s/, /,/g' | python3 -c '
import sys,re
for l in sys.stdin:
    l=l.strip()
    if not l: continue
    l=re.sub(r"0x([0-9a-f]+)",lambda m:str(int(m.group(1),16)),l) if not l.startswith("lui") else l
    l=re.sub(r"^(lui [a-z0-9]+),.*",r"\1,K",l); l=re.sub(r"^(j[a-z]*) .*",r"\1 F",l); l=re.sub(r"^(b[a-z]*) (.*),\S+$",r"\1 \2,L",l); l=re.sub(r"^b \S+$","b L",l)
    l=re.sub(r",-?\d+\((at|gp)\)$",r",K(\1)",l)
    print(l)' > $T/mine
python3 - $T/ref <<'P' > $T/ref2
import sys,re
for l in open(sys.argv[1]):
    l=l.strip(); l=re.sub(r"0x([0-9A-Fa-f]+)",lambda m:str(int(m.group(1),16)),l); l=re.sub(r",K\((at|gp)\)$",r",K(\1)",l); l=re.sub(r"^(?:addiu|ori) (\w+),zero,(-?\d+)$",r"li \1,\2",l); l=re.sub(r"^(?:or|addu) (\w+),(\w+),zero$",r"move \1,\2",l); l=re.sub(r"^lw (\w+),K\((\w+)\)$",r"lw \1,0(\2)",l); print(l)
P
diff -U1 $T/ref2 $T/mine | tail -n +3 | head -${3:-40}; rm -rf $T
