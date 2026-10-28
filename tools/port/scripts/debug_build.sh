#!/bin/bash
# P342: source-level DEBUG build of the browser port (DWARF, -O0) for Chrome DevTools + the "C/C++ DevTools Support
# (DWARF)" extension, and compile_commands.json for CLion. docs/port/DEBUGGING.md has the user steps.
#   tools/port/scripts/debug_build.sh            build, then serve it on http://localhost:$PORT (default 8077)
#   tools/port/scripts/debug_build.sh build      build only        ... serve | stop | cc (compile_commands.json only)
# Isolation: the release tree is never touched. The sources are rsync'ed into port/build-dbg/tree (same relative
# layout) and built there with the normal Makefile + vbe pipeline in debug mode (PORT_DBG_CFLAGS, port/Makefile and
# port/tools/vbe_build.py). The release output (port/build, port/build/web/conker.wasm, census and vbe stamps, flags)
# stays as it is. -fdebug-prefix-map turns the container path of the copy into this worktree's host path, so DWARF
# names the files you edit (file:///Users/.../conker/src_eu/x.c).
# Env: PORT (8077), DBG_OPT (-O0; -Og to speed up), JOBS (all cores), DBG_REV (build a git revision, e.g. HEAD,
# instead of the working files; DWARF still points at the worktree files, so keep them equal to that revision),
# DBG_WATCH=1 (P353: every game store checks the ?watch=ADDR[&watchlen=N] write watchpoint, port/ultra/pc_nethash.c),
# CONKER_DBG_SERVER (server container name).
set -euo pipefail
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
ROOT=$(cd "$(dirname "$0")/../../.." && pwd)
DBG=$ROOT/port/build-dbg; TREE=$DBG/tree; CT=/src/port/build-dbg/tree
IMG=${CONKER_EMSDK_IMAGE:-conker-emsdk}; SRV=${CONKER_DBG_SERVER:-conker-dbg-serve}; PORT=${PORT:-8077}
QUERY='app=game&mute=1&romurl=../dev/rom.z64'

sync_tree() {  # copy of the sources at the same relative paths; build outputs inside the copy are kept
  local from=$ROOT
  if [ -n "${DBG_REV:-}" ]; then  # a committed revision instead of the working files (someone else's WIP breaks the build)
    from=$DBG/rev; rm -rf "$from"; mkdir -p "$from"
    git -C "$ROOT" archive "$DBG_REV" conker port tools/eu_port/names.tsv | tar -x -C "$from"
  fi
  mkdir -p "$TREE/tools/eu_port"
  rsync -a --delete --exclude /build/ "$from/conker/" "$TREE/conker/"
  rsync -a --delete --exclude /build/ --exclude /build-dbg/ --exclude __pycache__ "$from/port/" "$TREE/port/"
  rsync -a "$from/tools/eu_port/names.tsv" "$TREE/tools/eu_port/names.tsv"
  ln -sfn ../../../baserom.eu.z64 "$TREE/baserom.eu.z64"   # n64mem.py reads the ROM at build time (gitignored)
}

build() {
  [ -n "${DBG_NOSYNC:-}" ] || sync_tree   # DBG_NOSYNC=1: build port/build-dbg/tree as it is
  # last matching map wins (clang): srcfix copies (port/build/srcfix/<file>.c, 5 TUs, same line numbers) -> the original
  local map="-g -fdebug-prefix-map=$CT=$ROOT -fdebug-prefix-map=port/build/srcfix=conker/src_eu"
  map="$map -fdebug-prefix-map=$CT/port/build/srcfix=$ROOT/conker/src_eu"
  local s=$(date +%s) log=$DBG/build.log
  docker run --rm -v "$ROOT":/src -w $CT -e PORT_DBG_CFLAGS="$map" -e PORT_DBG_OPT="${DBG_OPT:--O0}" -e PORT_DBG_WATCH="${DBG_WATCH:-}" "$IMG" \
    make -C port -j"${JOBS:-$(sysctl -n hw.ncpu)}" game web > "$log" 2>&1 || { tail -30 "$log"; echo "debug build FAILED ($log)"; exit 1; }
  local w=$TREE/port/build/web/conker.wasm
  echo "debug build ok in $(( $(date +%s) - s ))s: $(grep -h '^vbe_build:' "$log" | tail -1); $(grep -h 'link warnings' "$log" | tail -1)"
  echo "  $w ($(( $(stat -f %z "$w") / 1048576 )) MB, log $log)"
}

serve() {
  docker rm -f "$SRV" >/dev/null 2>&1 || true
  docker run -d --name "$SRV" -p 127.0.0.1:"$PORT":8000 -v "$TREE/port/build/web":/www/app:ro \
    -v "$ROOT/baserom.eu.z64":/www/dev/rom.z64:ro -w /www "$IMG" python3 -m http.server 8000 >/dev/null
  echo "debug page: http://localhost:$PORT/app/index.html?$QUERY&warp=29   (stop: $0 stop)"
}

case ${1:-all} in
all) build; python3 "$ROOT/tools/port/scripts/gen_compile_commands.py"; serve;;
build) build;;
serve) serve;;
stop) docker rm -f "$SRV" >/dev/null && echo "stopped $SRV";;
cc) python3 "$ROOT/tools/port/scripts/gen_compile_commands.py";;
*) sed -n '2,12p' "$0"; exit 2;;
esac
