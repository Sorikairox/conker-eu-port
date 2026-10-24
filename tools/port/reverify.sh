#!/bin/bash
# P221: re-run a converted function's verification with its exact recorded command (tools/port/verify_registry.tsv).
# usage: tools/port/reverify.sh FUNC...   (after eval "$(tools/eu_port/wt.sh env <name>)")
# Env: TR (trials per setup, default 4), NR (random trials, default 100; 0 = skip), MUT=1 also runs the mutants,
#      NOSETUP=1 random only, MUTCUT=N cuts the mutant line at N characters (default: no cut; P227). Candidate = the function's current NM block (tools/port/nmblock.py).
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
  # P239: knob DRAFT=path tests a recorded test variant instead of the NM block (e.g. func_1518FE0C: the shipped
  # s32 (u8 *, void *) table-signature body is one word longer and its jal to the adjacent func_1518FE50 falls inside
  # the candidate range, so difftest cannot stub it; the void one-argument variant has the same body)
  for k in $kn; do case $k in TR=*) [ -z "$TR" ] && tr=${k#TR=};; DRAFT=*) C=${k#DRAFT=};; *) envs+=("$k");; esac; done
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
    # P241: line-numbered mutant files were written against one of two draft layouts: the whole NM block (P235 on) or
    # the body without the `#ifdef NON_MATCHING` line (e.g. P222 drafts). Per mutant file, the layout under which more
    # mutants apply is used (ties: whole block; NMBLOCK_BODY=1 / NMBLOCK_FIXED=1 = no choice, as before).
    lay=""; if [ -z "$NMBLOCK_BODY$NMBLOCK_FIXED" ]; then CB=$W/${F}_body_$$.c
      env -u NMBLOCK_WHOLE python3 tools/port/nmblock.py $F $CB > /dev/null
      aw=0; ab=0; while IFS='%' read -r e names; do e=$(echo "$e" | sed 's/ *$//')
        sed "$e" $C 2>/dev/null | cmp -s $C - || aw=$((aw+1)); sed "$e" $CB 2>/dev/null | cmp -s $CB - || ab=$((ab+1))
      done < <(grep -vE '^\s*(#|$)' "$m")
      if [ $ab -gt $aw ]; then lay=" [layout body: $ab vs whole $aw applied]"; Cm=$CB; else Cm=$C; [ $ab != $aw ] && lay=" [layout whole: $aw vs body $ab applied]"; fi
    else Cm=$C; fi
    while IFS='%' read -r e names; do
      e=$(echo "$e" | sed 's/ *$//'); tot=$((tot+1))
      sed "$e" $Cm > $M 2>/dev/null || { inv="$inv sed:[$e]"; continue; }; cmp -s $Cm $M && { na=$((na+1)); continue; }
      if [ "${NR:-100}" != 0 ] && [ -n "$randok" ] && [ "$(NOARGMEM=1 CUT=6 dt tools/port/difftest.sh $F $M --trials ${NR:-100} --seed 1)" = DIFFER ]; then k=$((k+1)); continue; fi
      hit=""; first=${st%%,*}
      # synchronous (STOP ends the runner at the first non-EQUIV setup): a `< <(runset)` loop left the runner going
      # after `break`, racing the next mutant in the same temp dir (P221 first draft: ERROR "expected 4, found 0")
      [ -n "$first" ] && while read -r nm r; do case "$r" in DIFFER*) hit=1; break;; EQUIV*) ;; *) hit="inv"; why="$nm=$(echo $r | cut -c1-120)"; break;; esac
      done <<< "$(STOP=1 runset $M $first $names)"
      case "$hit" in 1) k=$((k+1));; inv) inv="$inv [$e]($why)";; *) sv="$sv [$e]";; esac
    done < <(grep -vE '^\s*(#|$)' "$m"); rm -f $M ${CB:-}
    echo "  muts $(basename $m): $k killed / $tot${sv:+ (survived:$sv)}; not applied: $na${inv:+; invalid:$inv}$lay" | { [ -n "$MUTCUT" ] && cut -c1-$MUTCUT || cat; }
  done
  docker exec ${CONKERDEV:-conkerdev} rm -rf /conker/conker/$T 2>/dev/null
done
