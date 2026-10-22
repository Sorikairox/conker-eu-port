#!/bin/bash
# usage: mutant.sh SRC 'sed-expr' 'harness args' -- apply a sed mutant to conker/SRC, build NON_MATCHING, run
# python3 ../tools/port/difftest/<harness args> in the container, restore SRC and rebuild. Prints the harness's last line.
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
F=conker/$1; cp "$F" /tmp/p53_mut_backup.c
sed -i '' "$2" "$F"; if cmp -s "$F" /tmp/p53_mut_backup.c; then echo "mutant did not apply: $2"; exit 1; fi
docker exec -w /conker/conker $CONKERDEV make VERSION=eu NON_MATCHING=1 -j8 >/dev/null 2>&1 || echo "build failed"
echo "mutant [$2]: $(docker exec -w /conker/conker $CONKERDEV sh -c "python3 ../tools/port/difftest/$3" 2>&1 | tail -1)"
cp /tmp/p53_mut_backup.c "$F"; touch "$F"
docker exec -w /conker/conker $CONKERDEV make VERSION=eu NON_MATCHING=1 -j8 >/dev/null 2>&1 || echo "rebuild failed"
