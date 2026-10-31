#!/bin/bash
# P357 end-to-end regression test: replay input recordings made with the page's input recorder (Options > Input recorder,
# docs/port/E2E.md) headless, muted, as fast as the page runs, and report the first point where the game behaves
# differently from the recording.
#   tools/port/scripts/e2e_replay.sh [RECORDING.ckrec | DIR]      (default: every *.ckrec in tests/e2e/recordings)
#   env: WEB=DIR        the build to test (default port/build/web)
#        REF_WEB=DIR    a reference build for the "expected" picture at a difference (default port_work/e2e/ref_web, if
#                       there; SAVE_REF=1 copies WEB there after a run in which every recording passed)
#        KEEP=1         go on after the first difference (counts all differing fingerprints, reports how far it got)
#        SPEED=real     replay at 50 Hz instead of as fast as possible
#        STOP=F         stop after retrace F (and save the picture there)
#        OUT=DIR        output folder (default port_work/e2e); per recording OUT/<name>/{chrome.log,result.json,actual.png,expected.png}
#        TIMEOUT=S      per recording (default 3600)
#        EXTRA_Q=...    more page query, e.g. '&opt=widescreen:1,hfr:1' (render-only options must not change the result)
#        REBASE=1       P373: replay to the end (KEEP) and, if the recorded pad input still plays the same route (every
#                       checkpoint's retrace, kind, level, mode and Conker position as recorded), write this build's G
#                       digests and checkpoints into the .ckrec (tools/port/scripts/e2e_rebase.py; REBASE_WHY='reason'
#                       is stored in the file). For a deliberate gameplay fix that changes RNG / memory but not the route.
# No test flags in the page URL: the online hash H covers the static state of the port's test aids too (?p103boot's
# mode / level cache, for example), and a player's recording is made without any.
# Pictures are ROM-derived: they stay in port_work (never commit them). The recordings and their hashes may be committed.
# Exit status: 0 = every recording replayed identically, 1 = a difference / error.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
[ -n "${PROBE_NOWAIT:-}" ] || while [ "$(ps -axo command | grep -v grep | grep -c 'headless=new')" -gt 0 ]; do sleep 10; done
SRC=${1:-tests/e2e/recordings}
if [ -d "$SRC" ]; then RECDIR=$(cd "$SRC" && pwd); FILES=$(cd "$SRC" && ls *.ckrec 2>/dev/null)
else RECDIR=$(cd "$(dirname "$SRC")" && pwd); FILES=$(basename "$SRC"); fi
[ -n "$FILES" ] || { echo "e2e_replay: no .ckrec recordings in $SRC"; exit 1; }
WEB=$(cd "${WEB:-port/build/web}" && pwd); OUTD=${OUT:-port_work/e2e}; mkdir -p "$OUTD"
REF=${REF_WEB:-port_work/e2e/ref_web}; [ -f "$REF/conker.wasm" ] && REF=$(cd "$REF" && pwd) || REF=
NAME=conker-e2e-$$; PORT=${PROBE_PORT:-$((8100 + $$ % 800))}
docker run -d --rm --name "$NAME" -p 127.0.0.1:$PORT:8000 -v "$WEB":/www/app:ro -v "$PWD/baserom.eu.z64":/www/dev/rom.z64:ro \
  -v "$RECDIR":/www/rec:ro ${REF:+-v "$REF":/www/ref:ro} -w /www conker-emsdk python3 -m http.server 8000 >/dev/null || exit 1
trap 'docker rm -f "$NAME" >/dev/null 2>&1 || true' EXIT
sleep 1.5
[ -n "${REBASE:-}" ] && KEEP=1
Q="romurl=../dev/rom.z64&mute=1${KEEP:+&replaykeep=1}${SPEED:+&replayspeed=$SPEED}${STOP:+&replaystop=$STOP}${EXTRA_Q:-}"
FAILS=0
for F in $FILES; do
  N=${F%.ckrec}; D=$OUTD/$N; rm -rf "$D"; mkdir -p "$D"
  E2E_REBASE=${REBASE:-} node tools/port/scripts/e2e_replay.js "http://localhost:$PORT/app/index.html?$Q&replay=../rec/$F" "$D" "${TIMEOUT:-3600}" > "$D/driver.out" 2>&1
  RC=$?
  FIRST=$(python3 -c "import json,sys; r=json.load(open('$D/result.json')); print((r.get('first') or {}).get('f') or '')" 2>/dev/null)
  if [ "$RC" -ne 0 ] && [ -n "$FIRST" ] && [ -n "$REF" ]; then   # the reference build's picture at the first difference
    node tools/port/scripts/e2e_replay.js "http://localhost:$PORT/ref/index.html?romurl=../dev/rom.z64&mute=1&replaykeep=1&replay=../rec/$F&replaystop=$FIRST" "$D/ref" "${TIMEOUT:-3600}" > "$D/ref.out" 2>&1
    [ -f "$D/ref/actual.png" ] && cp "$D/ref/actual.png" "$D/expected.png"
    [ -f "$D/expected.png" ] && [ -f "$D/actual.png" ] && python3 tools/port/scripts/pngtool.py diff "$D/actual.png" "$D/expected.png" > "$D/pixdiff.txt" 2>&1
  fi
  python3 tools/port/scripts/e2e_report.py "$D" "$F" || FAILS=$((FAILS + 1))
  if [ -n "${REBASE:-}" ]; then python3 tools/port/scripts/e2e_rebase.py "$D/rebase.json" "$RECDIR/$F" "${REBASE_WHY:-}" || FAILS=$((FAILS + 1)); fi
  # P373: a void function called through a value-returning pointer that port/tools/icall_void_audit.tsv does not list
  if grep -q '^\[icall\] UNAUDITED' "$D/chrome.log" 2>/dev/null; then
    echo "FAIL $F: unaudited void indirect-call targets (port/tools/icall_void_audit.tsv):"; grep '^\[icall\] UNAUDITED' "$D/chrome.log" | head -5
    FAILS=$((FAILS + 1))
  fi
done
if [ "$FAILS" -eq 0 ] && [ -n "${SAVE_REF:-}" ]; then rm -rf port_work/e2e/ref_web; mkdir -p port_work/e2e; cp -R "$WEB" port_work/e2e/ref_web; echo "reference build saved: port_work/e2e/ref_web"; fi
echo "e2e: $(echo $FILES | wc -w | tr -d ' ') recording(s), $FAILS with a difference"
[ "$FAILS" -eq 0 ]
