#!/bin/bash
# Deploy the browser build to the public site (Netlify project conker-web-port, user rule 2026-10-26: always deploy
# the latest version). Run it after a change passed its checks and browser test; it ships port/build/web as built.
#   tools/eu_port/deploy_web.sh
set -euo pipefail
cd ~/conker-wt/web
B=port/build/web
[ -f $B/conker.wasm ] || { echo "no build at $B"; exit 1; }
cmp -s $B/main.js port/web/main.js && cmp -s $B/index.html port/web/index.html || { echo "build/web page files differ from port/web: rebuild first"; exit 1; }
S=~/conker-site; mkdir -p $S
cp $B/conker.js $B/conker.wasm $B/index.html $B/main.js $S/
git log -1 --format='%h %ad %s' --date=format:'%Y-%m-%d %H:%M' > $S/BUILD.txt
cd $S && npx -y netlify-cli@latest deploy --prod --dir . --no-build 2>&1 | grep -E "Deploy is live|Error|error" || true
curl -s https://conker-web-port.netlify.app/BUILD.txt
