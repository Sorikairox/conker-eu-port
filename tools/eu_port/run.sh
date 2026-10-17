#!/bin/bash
# Regenerate the EU port from the committed asm-only baseline.
# Usage (repo root): tools/eu_port/run.sh
set -euo pipefail
cd "$(dirname "$0")/../.."
DOCKER=${DOCKER:-docker}
command -v "$DOCKER" >/dev/null || DOCKER=/Applications/Docker.app/Contents/Resources/bin/docker

git checkout -q HEAD -- conker/conker.eu.yaml conker/symbol_addrs.eu.txt conker/undefined_syms.eu.txt
rm -rf conker/src_eu conker/build_port/us

"$DOCKER" run --rm --platform linux/amd64 -v "$(pwd)":/conker conker bash -c '
set -euo pipefail
cd conker
mkdir -p build_port && cp symbol_addrs.eu.txt build_port/symbol_addrs.eu.base.txt
echo "== baseline split + build"
rm -rf asm build *_auto.txt
make VERSION=eu extract >/dev/null 2>&1
make VERSION=eu -j8 2>&1 | tail -1
echo "== compile US sources"
python3 ../tools/eu_port/compile_us.py | tail -1
echo "== match"
python3 ../tools/eu_port/match.py
echo "== port"
python3 ../tools/eu_port/port.py
echo "== ported split + build"
rm -rf asm build *_auto.txt
make VERSION=eu extract >/dev/null 2>&1
make VERSION=eu -j8 2>&1 | grep -E "rror|OK|FAILED" | sort -u | head -40
'
