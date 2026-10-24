#!/bin/bash
# P221: re-run a converted function's verification with its exact recorded command (tools/port/verify_registry.tsv).
# usage: tools/port/reverify.sh FUNC...   (after eval "$(tools/eu_port/wt.sh env <name>)")
# Env: TR (trials per setup, default 4), NR (random trials, default 100; 0 = skip), MUT=1 also runs the mutants,
#      NOSETUP=1 random only. Candidate = the function's current NM block (tools/port/nmblock.py).
# Registry columns: func, file, setup_file (comma list), knobs (space-separated K=V env, e.g. DIFFTEST_ROMDATA=1; TR=N sets
# the setup trials), mutant_file (comma list, `sed-expr % setup names` lines), session.
# Output: one line per phase: `FUNC random: EQUIV|DIFFER...`, `FUNC setups FILE: n EQUIV / m (bad: name=RESULT ...)`,
# `FUNC muts FILE: k killed / n (survived: ...; not applied: N; invalid: N)`.
. "$(dirname "${BASH_SOURCE[0]}")/portguard.sh"
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
R=${CONKER_ROOT:-$HOME/conker}; cd "$R" || exit 2
REG=tools/port/verify_registry.tsv; W=port_work/reverify; mkdir -p $W
for F in "$@"; do
  row=$(awk -F'\t' -v f="$F" '$1==f {OFS="\037"; $1=$1; print}' $REG | tail -1)  # US-separated: read collapses empty tab fields
  [ -z "$row" ] && { echo "$F: not in registry"; continue; }
  IFS=$'\037' read -r fn file st kn mu ses <<< "$row"
  # P235: the candidate is the whole NM block (as the session drafts: mutant line numbers match; a matching-C function
  # such as func_151D52B4 keeps its matching body in the #else arm). NMBLOCK_BODY=1 = old behaviour (body only).
  wh=(NMBLOCK_WHOLE=1); [ -n "$NMBLOCK_BODY" ] && wh=(-u NMBLOCK_WHOLE)
  C=$W/$F.c; env "${wh[@]}" python3 tools/port/nmblock.py $F $C > /dev/null || { echo "$F: no C definition"; continue; }
  envs=(); tr=${TR:-4}
  for k in $kn; do case $k in TR=*) [ -z "$TR" ] && tr=${k#TR=};; *) envs+=("$k");; esac; done
  T=build/difftest_rv_${F}_$$
  dt() { local u=(); [ -n "$NOARGMEM" ] && u=(-u DIFFTEST_ARGMEM)  # mut.sh P73: the random phase runs without ARGMEM
    env "${envs[@]}" "${u[@]}" DIFFTEST_TMP=$T "$@" 2>&1 | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)" | head -1 | cut -c1-${CUT:-160}; }
  echo "$F ($ses, $file) knobs: ${kn:-none}"
  randok=""; if [ "${NR:-100}" != 0 ]; then r=$(dt tools/port/difftest.sh $F $C --trials ${NR:-100} --seed 1); echo "  random: $r"
    # mut.sh P77: random kills only count when the unmutated draft is EQUIV on random (without ARGMEM)
    [ -n "$MUT" ] && [ "$(NOARGMEM=1 CUT=5 dt tools/port/difftest.sh $F $C --trials ${NR:-100} --seed 1)" = EQUIV ] && randok=1; fi
  # setup runner: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB (the p218 knobs.sh format)
  runset() { # cand setupfile [names] -> prints "name RESULT" lines
    local c=$1 s=$2; shift 2
    grep -vE '^\s*(#|$)' "$s" | while IFS='!' read -r n a p r rf ow ww wb; do
      n=$(echo $n); [ $# -gt 0 ] && ! [[ " $* " == *" $n "* ]] && continue
      o=$(DIFFTEST_EXACT='*' DIFFTEST_ARG="$(echo $a)" DIFFTEST_POKE="$(echo $p)" DIFFTEST_RET="$(echo $r)" DIFFTEST_RETF="$(echo $rf)" \
          DIFFTEST_OUTA="$(echo $ow)" DIFFTEST_OUTW="$(echo $ww)" DIFFTEST_OUTB="$(echo $wb)" dt tools/port/difftest.sh $F $c --trials $tr --seed 1)
      echo "$n ${o:-NOOUTPUT}"; [ -n "$STOP" ] && [ "${o%% *}" != EQUIV ] && break
    done; }
  if [ -z "$NOSETUP" ]; then for s in ${st//,/ }; do
    res=$(runset $C $s); n=$(echo "$res" | grep -c .); e=$(echo "$res" | grep -c ' EQUIV')
    bad=$(echo "$res" | grep -v ' EQUIV' | awk '{print $1"="$2}' | tr '\n' ' ')
    echo "  setups $(basename $s): $e EQUIV / $n${bad:+ (bad: $bad)}"
  done; fi
  [ -n "$MUT" ] && for m in ${mu//,/ }; do
    M=$W/${F}_mut_$$.c; k=0; sv=""; na=0; inv=""; tot=0
    while IFS='%' read -r e names; do
      e=$(echo "$e" | sed 's/ *$//'); tot=$((tot+1))
      sed "$e" $C > $M 2>/dev/null || { inv="$inv sed:[$e]"; continue; }; cmp -s $C $M && { na=$((na+1)); continue; }
      if [ "${NR:-100}" != 0 ] && [ -n "$randok" ] && [ "$(NOARGMEM=1 CUT=6 dt tools/port/difftest.sh $F $M --trials ${NR:-100} --seed 1)" = DIFFER ]; then k=$((k+1)); continue; fi
      hit=""; first=${st%%,*}
      # synchronous (STOP ends the runner at the first non-EQUIV setup): a `< <(runset)` loop left the runner going
      # after `break`, racing the next mutant in the same temp dir (P221 first draft: ERROR "expected 4, found 0")
      [ -n "$first" ] && while read -r nm r; do case "$r" in DIFFER*) hit=1; break;; EQUIV*) ;; *) hit="inv"; why="$nm=$(echo $r | cut -c1-120)"; break;; esac
      done <<< "$(STOP=1 runset $M $first $names)"
      case "$hit" in 1) k=$((k+1));; inv) inv="$inv [$e]($why)";; *) sv="$sv [$e]";; esac
    done < <(grep -vE '^\s*(#|$)' "$m"); rm -f $M
    echo "  muts $(basename $m): $k killed / $tot${sv:+ (survived:$sv)}; not applied: $na${inv:+; invalid:$inv}" | cut -c1-600
  done
  docker exec ${CONKERDEV:-conkerdev} rm -rf /conker/conker/$T 2>/dev/null
done
