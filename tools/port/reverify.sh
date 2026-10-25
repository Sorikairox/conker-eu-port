#!/bin/bash
# P221: re-run a converted function's verification with its exact recorded command (tools/port/verify_registry.tsv).
# usage: tools/port/reverify.sh FUNC...   (after eval "$(tools/eu_port/wt.sh env <name>)")
# Env: TR (trials per setup, default 4), NR (random trials, default 100; 0 = skip; NORAND=1 = NR=0), MUT=1 also runs the mutants,
#      NOSETUP=1 random only, MUTCUT=N cuts the mutant line at N characters (default: no cut; P227). Candidate = the function's current NM block (tools/port/nmblock.py).
# Registry columns: func, file, setup_file (comma list), knobs (space-separated K=V env, e.g. DIFFTEST_ROMDATA=1; TR=N sets
# the setup trials), mutant_file (comma list, `sed-expr % setup names` lines), session.
# Output: one line per phase: `FUNC random: EQUIV|DIFFER...`, `FUNC setups FILE: n EQUIV / m (bad: name=RESULT ...)`,
# `FUNC muts FILE: k killed / n (survived: ...; not applied: N; invalid: N)`.
. "$(dirname "${BASH_SOURCE[0]}")/portguard.sh"
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
R=${CONKER_ROOT:-$HOME/conker}; cd "$R" || exit 2
REG=tools/port/verify_registry.tsv; W=port_work/reverify; mkdir -p $W
NR0=$NR  # P244: registry knob NR=N sets the random trial count for that row (env NR still wins)
# P253: NORAND=1 skips the random phase (same as NR=0; it was silently ignored before). It wins over a registry NR= knob.
[ -n "$NORAND" ] && NR0=0
for F in "$@"; do NR=$NR0
  row=$(awk -F'\t' -v f="$F" '$1==f {OFS="\037"; $1=$1; print}' $REG | tail -1)  # US-separated: read collapses empty tab fields
  [ -z "$row" ] && { echo "$F: not in registry"; continue; }
  IFS=$'\037' read -r fn file st kn mu ses <<< "$row"
  # P255 (port-b P251 request): knob HARNESS=cmd runs a whole-function harness instead of the difftest phases, knob
  # HMUT=cmd its mutant runner (MUT=1 only). Commas in cmd become spaces (the knob column is space-separated); the
  # command runs from the worktree root with this shell's env (CONKER_ROOT, CONKERDEV). HARNESS must print a verdict
  # line starting with EQUIV / DIFFER / UNSURE / ERROR (or `RESULT X`), HMUT a last line `done: killed K survived S
  # other O` (tools/port/nmharness.sh / nmharness_mut.sh do both). Output: `  harness: VERDICT ...` and
  # `  muts harness: K killed / N (survived: [..])`. Rows with HARNESS skip random / setups / difftest mutants.
  hc=""; hm=""; for k in $kn; do case $k in HARNESS=*) hc=${k#HARNESS=};; HMUT=*) hm=${k#HMUT=};; esac; done
  if [ -n "$hc" ]; then
    echo "$F ($ses, $file) knobs: $kn"
    r=$(bash -c "${hc//,/ }" 2>&1 | grep -E '^(RESULT )?(EQUIV|DIFFER|UNSURE|ERROR)' | tail -1 | cut -c1-${CUT:-160})
    [ -z "$r" ] && r="ERROR (no verdict line from: ${hc//,/ })"; echo "  harness: ${r#RESULT }"
    if [ -n "$MUT" ]; then
      if [ -z "$hm" ]; then echo "  muts harness: 0 killed / 0; not applied: 0 (no HMUT knob)"
      else ho_out=$(bash -c "${hm//,/ }" 2>&1); d=$(echo "$ho_out" | grep -E '^done: killed' | tail -1)
        if [ -z "$d" ]; then echo "  muts harness: ? (no 'done: killed' line from: ${hm//,/ })"
        else read -r hk hs ho <<< "$(echo "$d" | sed -E 's/done: killed ([0-9]+) survived ([0-9]+) other ([0-9]+).*/\1 \2 \3/')"
          # survivors / others listed as [expr] when the runner prints `SURVIVED k: expr` lines (nmharness_mut.sh does)
          sv=$(echo "$ho_out" | sed -n 's/^SURVIVED [0-9]*: \(.*\)/ [\1]/p' | tr -d '\n'); [ -z "$sv" ] && for ((q = 0; q < hs; q++)); do sv="$sv [?]"; done
          iv=$(echo "$ho_out" | sed -nE 's/^(NOAPPLY|INVALID|ERROR) [0-9]+: (.*)/ [\2]/p' | tr -d '\n'); [ -z "$iv" ] && for ((q = 0; q < ho; q++)); do iv="$iv [?]"; done
          echo "  muts harness: $hk killed / $((hk + hs + ho))${sv:+ (survived:$sv)}; not applied: 0${iv:+; invalid:$iv}"
        fi
      fi
    fi
    continue
  fi
  # P235: the candidate is the whole NM block (as the session drafts: mutant line numbers match; a matching-C function
  # such as func_151D52B4 keeps its matching body in the #else arm). NMBLOCK_BODY=1 = old behaviour (body only).
  wh=(NMBLOCK_WHOLE=1); [ -n "$NMBLOCK_BODY" ] && wh=(-u NMBLOCK_WHOLE)
  C=$W/$F.c; env "${wh[@]}" python3 tools/port/nmblock.py $F $C > /dev/null || { echo "$F: no C definition"; continue; }
  envs=(); tr=${TR:-4}
  # P239: knob DRAFT=path tests a recorded test variant instead of the NM block (e.g. func_1518FE0C: the shipped
  # s32 (u8 *, void *) table-signature body is one word longer and its jal to the adjacent func_1518FE50 falls inside
  # the candidate range, so difftest cannot stub it; the void one-argument variant has the same body)
  cs=""; for k in $kn; do case $k in TR=*) [ -z "$TR" ] && tr=${k#TR=};; DRAFT=*) C=${k#DRAFT=};; CANDSED=*) cs=${k#CANDSED=};; NR=*) [ -z "$NR0" ] && NR=${k#NR=};; *) envs+=("$k");; esac; done
  # P244: knob CANDSED=file applies `sed -f file` to the candidate (and to the body layout) before every run, for test-only
  # edits that must track the current NM block (unlike DRAFT=); the sed must keep line numbers (mutants are line-numbered).
  # func_15065E18: the C passes func_150DC2F0's unused a1 as 0, the asm leaves garbage there -> 1-argument prototype.
  if [ -n "$cs" ]; then sed -f "$cs" $C > $W/${F}_cs.c || { echo "$F: CANDSED $cs failed"; continue; }; C=$W/${F}_cs.c; fi
  T=build/difftest_rv_${F}_$$
  dt() { local u=(); [ -n "$NOARGMEM" ] && u=(-u DIFFTEST_ARGMEM)  # mut.sh P73: the random phase runs without ARGMEM
    # P243: `env -u` must come before the K=V assignments: after them env took `-u` as the command, so with any
    # registry knob the no-ARGMEM random run printed nothing, randok stayed empty and random kills never counted
    # (mutants were killed only by setups; func_150D1D20's 3 random-only mutants all "survived"). RVENV_OLD=1 = old order.
    if [ -n "$RVENV_OLD" ]; then env "${envs[@]}" "${u[@]}" DIFFTEST_TMP=$T "$@"; else env "${u[@]}" "${envs[@]}" DIFFTEST_TMP=$T "$@"; fi 2>&1 | grep -E "^(EQUIV|DIFFER|UNSURE|ERROR)" | head -1 | dtcut; }
  # P259: keep difftest's static "[knob not a jal target ...]" note (a knob keyed on a non-EU address) after the cut
  # verdict when no CUT is given (CUT=N callers compare the cut text, e.g. `= DIFFER`, and stay as before)
  dtcut() { local l; IFS= read -r l || return 0; if [ -n "$CUT" ]; then echo "$l" | cut -c1-$CUT
    else local c n; c=$(echo "$l" | cut -c1-160); c=${c%% \[knob not a jal*}
      n=$(echo "$l" | grep -o ' \[knob not a jal target[^]]*\]' | head -1); echo "$c$n"; fi; }
  echo "$F ($ses, $file) knobs: ${kn:-none}"
  randok=""; if [ "${NR:-100}" != 0 ]; then r=$(dt tools/port/difftest.sh $F $C --trials ${NR:-100} --seed 1); echo "  random: $r"
    # mut.sh P77: random kills only count when the unmutated draft is EQUIV on random (without ARGMEM)
    [ -n "$MUT" ] && [ "$(NOARGMEM=1 CUT=5 dt tools/port/difftest.sh $F $C --trials ${NR:-100} --seed 1)" = EQUIV ] && randok=1; fi
  # setup runner: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB (the p218 knobs.sh format)
  runset() { # cand setupfile [names] -> prints "name RESULT" lines
    local c=$1 s=$2; shift 2
    grep -vE '^\s*(#|$)' "$s" | while IFS='!' read -r n a p r rf ow ww wb; do
      n=$(echo $n); [ $# -gt 0 ] && ! [[ " $* " == *" $n "* ]] && continue
      # P244: a non-empty setup field wins over the same registry knob (dt's `env "${envs[@]}"` used to override it:
      # func_15170648's random-phase knob DIFFTEST_ARG=5=0|1|2 replaced every setup's arguments -> 0 / 4 UNSURE)
      local sw=() kv; for kv in "DIFFTEST_ARG=$(echo $a)" "DIFFTEST_POKE=$(echo $p)" "DIFFTEST_RET=$(echo $r)" "DIFFTEST_RETF=$(echo $rf)" \
          "DIFFTEST_OUTA=$(echo $ow)" "DIFFTEST_OUTW=$(echo $ww)" "DIFFTEST_OUTB=$(echo $wb)"; do [ -n "${kv#*=}" ] && sw+=("$kv"); done
      o=$(DIFFTEST_EXACT='*' DIFFTEST_ARG="$(echo $a)" DIFFTEST_POKE="$(echo $p)" DIFFTEST_RET="$(echo $r)" DIFFTEST_RETF="$(echo $rf)" \
          DIFFTEST_OUTA="$(echo $ow)" DIFFTEST_OUTW="$(echo $ww)" DIFFTEST_OUTB="$(echo $wb)" dt env "${sw[@]}" tools/port/difftest.sh $F $c --trials $tr --seed 1)
      echo "$n ${o:-NOOUTPUT}"; [ -n "$STOP" ] && [ "${o%% *}" != EQUIV ] && break
    done; }
  if [ -z "$NOSETUP" ]; then for s in ${st//,/ }; do
    res=$(runset $C $s); n=$(echo "$res" | grep -c .); e=$(echo "$res" | grep -c ' EQUIV')
    bad=$(echo "$res" | grep -v ' EQUIV' | awk '{print $1"="$2}' | tr '\n' ' ')
    jn=$(echo "$res" | grep -o '\[knob not a jal target[^]]*\]' | sort -u | head -1)  # P259
    echo "  setups $(basename $s): $e EQUIV / $n${bad:+ (bad: $bad)}${jn:+ $jn}"
  done; fi
  [ -n "$MUT" ] && for m in ${mu//,/ }; do
    M=$W/${F}_mut_$$.c; k=0; sv=""; na=0; inv=""; tot=0
    # P241: line-numbered mutant files were written against one of two draft layouts: the whole NM block (P235 on) or
    # the body without the `#ifdef NON_MATCHING` line (e.g. P222 drafts). Per mutant file, the layout under which more
    # mutants apply is used (ties: whole block; NMBLOCK_BODY=1 / NMBLOCK_FIXED=1 = no choice, as before).
    lay=""; if [ -z "$NMBLOCK_BODY$NMBLOCK_FIXED" ]; then CB=$W/${F}_body_$$.c
      env -u NMBLOCK_WHOLE python3 tools/port/nmblock.py $F $CB > /dev/null
      [ -n "$cs" ] && { sed -f "$cs" $CB > $CB.cs && mv $CB.cs $CB; }
      aw=0; ab=0; while IFS='%' read -r e names; do e=$(echo "$e" | sed 's/ *$//')
        sed "$e" $C 2>/dev/null | cmp -s $C - || aw=$((aw+1)); sed "$e" $CB 2>/dev/null | cmp -s $CB - || ab=$((ab+1))
      done < <(grep -vE '^\s*(#|$)' "$m")
      if [ $ab -gt $aw ]; then lay=" [layout body: $ab vs whole $aw applied]"; Cm=$CB; else Cm=$C; [ $ab != $aw ] && lay=" [layout whole: $aw vs body $ab applied]"; fi
    else Cm=$C; fi
    while IFS='%' read -r e names; do
      e=$(echo "$e" | sed 's/ *$//'); tot=$((tot+1))
      sed "$e" $Cm > $M 2>/dev/null || { inv="$inv sed:[$e]"; continue; }; cmp -s $Cm $M && { na=$((na+1)); continue; }
      if [ "${NR:-100}" != 0 ] && [ -n "$randok" ] && [ "$(NOARGMEM=1 CUT=6 dt tools/port/difftest.sh $F $M --trials ${NR:-100} --seed 1)" = DIFFER ]; then k=$((k+1)); continue; fi
      # P244: named setups are looked up in every setup file of the row (before: the first file only, so func_15177360's
      # m7360b mutants naming s7360b setups ran nothing and were "invalid"); a mutant without names runs the first file
      hit=""; first=${st%%,*}
      # synchronous (STOP ends the runner at the first non-EQUIV setup): a `< <(runset)` loop left the runner going
      # after `break`, racing the next mutant in the same temp dir (P221 first draft: ERROR "expected 4, found 0")
      [ -n "$first" ] && while read -r nm r; do case "$r" in DIFFER*) hit=1; break;; EQUIV*) ;; *) hit="inv"; why="$nm=$(echo $r | cut -c1-120)"; break;; esac
      done <<< "$(if [ -n "$(echo $names)" ]; then for s in ${st//,/ }; do STOP=1 runset $M $s $names; done; else STOP=1 runset $M $first; fi)"
      case "$hit" in 1) k=$((k+1));; inv) inv="$inv [$e]($why)";; *) sv="$sv [$e]";; esac
    done < <(grep -vE '^\s*(#|$)' "$m"); rm -f $M ${CB:-}
    echo "  muts $(basename $m): $k killed / $tot${sv:+ (survived:$sv)}; not applied: $na${inv:+; invalid:$inv}$lay" | { [ -n "$MUTCUT" ] && cut -c1-$MUTCUT || cat; }
  done
  docker exec ${CONKERDEV:-conkerdev} rm -rf /conker/conker/$T 2>/dev/null
done
