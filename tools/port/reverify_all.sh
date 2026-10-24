#!/bin/bash
# P241: walk tools/port/verify_registry.tsv and re-run rows through tools/port/reverify.sh (MUT=1 by default), one
# compact line per function. Written for the P235 nmblock fix (NMBLOCK_WHOLE): line-numbered mutants were one line
# off before it, so those rows need a re-run.
# usage: tools/port/reverify_all.sh [FUNC...]   (after eval "$(tools/eu_port/wt.sh env <name>)")
# Filters (env, all optional; a row must pass every one given):
#   LINENUM=1     only rows whose mutant file has line-number addresses (`12s/...`, `3,5d`; `1,/re/` does not count)
#   SES=REGEX     session column (e.g. 'P2(19|20|22)')     FILE=REGEX  file column      SKIPFILE=REGEX  exclude files
#   FROM=FUNC     start at this row (resume)                LIST=1      print the selected rows and exit
# JOBS=N functions in parallel (default 1, at most 2: difftest.sh also holds each container to 2 jobs).
# Other env (TR, NR, MUT, NOSETUP, ...) passes through to reverify.sh; MUT defaults to 1 here (MUT=0 = no mutants).
# Output per function: `FUNC SES FILE | random R | setups e/n[ bad] | muts k/n[ surv=N][ na=N][ inv=N]`; full
# reverify output in port_work/reverify_all/FUNC.log. A trailing `!` marks a row that is not all green.
. "$(dirname "${BASH_SOURCE[0]}")/portguard.sh"
R=${CONKER_ROOT:-$HOME/conker}; cd "$R" || exit 2
REG=tools/port/verify_registry.tsv; O=port_work/reverify_all; mkdir -p $O
J=${JOBS:-1}; [ "$J" -gt 2 ] && J=2
sel() { python3 - "$@" <<'EOF'
import os, re, sys
env = os.environ; want = set(sys.argv[1:]); rows = []
for l in list(open('tools/port/verify_registry.tsv'))[1:]:
    r = l.rstrip('\n').split('\t') + [''] * 6
    f, file, st, kn, mu, ses = r[:6]
    if want and f not in want: continue
    if env.get('SES') and not re.search(env['SES'], ses): continue
    if env.get('FILE') and not re.search(env['FILE'], file): continue
    if env.get('SKIPFILE') and re.search(env['SKIPFILE'], file): continue
    if env.get('LINENUM'):
        ln = 0
        for m in filter(None, mu.split(',')):
            if not os.path.exists(m): continue
            for x in open(m):
                x = x.strip()
                if x and not x.startswith('#') and (re.match(r'^\d+(,\d+)?\s*[sdaci!{]', x) or re.match(r'^(?!1,/)\d+,/', x)): ln += 1
        if not ln: continue
    rows.append((f, ses, file))
seen = set(); out = []
for x in rows:  # reverify.sh uses the last row of a function; list each function once
    if x[0] in seen: continue
    seen.add(x[0]); out.append(x)
if env.get('FROM'):
    i = [x[0] for x in out].index(env['FROM']) if env['FROM'] in [x[0] for x in out] else 0
    out = out[i:]
for x in out: print(*x)
EOF
}
one() { # FUNC SES FILE
  local f=$1 log=$O/$1.log
  MUT=${MUT:-1}; [ "$MUT" = 0 ] && MUT=
  MUT=$MUT tools/port/reverify.sh $f > $log 2>&1
  python3 - "$log" "$2" "$3" <<'EOF'
import re, sys
L = open(sys.argv[1]).read().split('\n'); f = L[0].split()[0] if L and L[0] else '?'
rnd = '-'; st = []; mu = []; bad = False
for l in L:
    l = l.strip()
    if l.startswith('random:') or l.startswith('harness:'):  # P255: HARNESS= rows print `harness: VERDICT ...`
        rnd = l.split()[1] if len(l.split()) > 1 else '?'; bad |= rnd != 'EQUIV'
        if l.startswith('harness:'): rnd = 'harness ' + rnd
    elif l.startswith('setups '):
        m = re.search(r': (\d+) EQUIV / (\d+)(.*)', l)
        if m:
            st.append(f'{m[1]}/{m[2]}' + (' bad' if m[3].strip() else '')); bad |= m[1] != m[2]
    elif l.startswith('muts '):
        m = re.search(r': (\d+) killed / (\d+)', l)
        sv = len(re.findall(r'\[', l.split('survived:')[1].split(';')[0])) if 'survived:' in l else 0
        na = int(re.search(r'not applied: (\d+)', l)[1]) if 'not applied:' in l else 0
        iv = len(re.findall(r'\[', l.split('invalid:')[1])) if 'invalid:' in l else 0
        s = f'{m[1]}/{m[2]}' if m else '?'
        s += (f' surv={sv}' if sv else '') + (f' na={na}' if na else '') + (f' inv={iv}' if iv else '')
        lay = re.search(r'\[layout (\w+)', l)
        if lay: s += ' ' + lay[1]
        mu.append(s); bad |= bool(sv or na or iv or not m)
    elif l and not l.startswith(f) and not l.startswith('setups') and ('not in registry' in l or 'no C definition' in l):
        rnd = l; bad = True
print(f'{f} {sys.argv[2]} {sys.argv[3]} | random {rnd} | setups {",".join(st) or "-"} | muts {",".join(mu) or "-"}' + (' !' if bad else ''))
EOF
}
export -f one; export O
if [ -n "$LIST" ]; then sel "$@"; exit 0; fi
sel "$@" | xargs -P $J -L 1 bash -c 'one "$@"' _
