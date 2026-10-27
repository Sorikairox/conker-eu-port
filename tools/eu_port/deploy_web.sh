#!/bin/bash
# Deploy the browser build to the public site (Netlify project conker-web-port, user rule 2026-10-26: always deploy
# the latest version). Run it after a change passed its checks and browser test; it ships port/build/web as built.
#   tools/eu_port/deploy_web.sh
set -euo pipefail
cd ~/conker-wt/web
B=port/build/web
[ -f $B/conker.wasm ] || { echo "no build at $B"; exit 1; }
cmp -s $B/main.js port/web/main.js && cmp -s $B/net.js port/web/net.js && cmp -s $B/index.html port/web/index.html || { echo "build/web page files differ from port/web: rebuild first"; exit 1; }
S=~/conker-site; mkdir -p $S
cp $B/conker.js $B/conker.wasm $B/conker_netx.txt $B/conker_netsyms.txt $B/index.html $B/main.js $B/net.js $S/
git log -1 --format='%h %ad %s' --date=format:'%Y-%m-%d %H:%M' > $S/BUILD.txt
# P345: the room-code server (Netlify Function /api/room on Netlify Blobs). Its source is port/web/netlify; it is
# bundled from ~/conker-netlify-fn (outside the published dir, so node_modules is never published as static files),
# where npm installs @netlify/blobs from port/web/netlify/package.json.
F=~/conker-netlify-fn; mkdir -p $F/functions
rm -rf $F/functions/room; cp -R port/web/netlify/functions/room $F/functions/
if ! cmp -s port/web/netlify/package.json $F/package.json || [ ! -d $F/node_modules/@netlify/blobs ]; then
  cp port/web/netlify/package.json $F/ && (cd $F && npm install --no-audit --no-fund --silent)
fi
cd $S && npx -y netlify-cli@latest deploy --prod --dir . --functions $F/functions --no-build 2>&1 | grep -E "Deploy is live|Error|error|function" || true
curl -s https://conker-web-port.netlify.app/BUILD.txt
# the room server answers (a bad request gives a JSON error, nothing is stored)
curl -s -X POST -H 'content-type: application/json' -d '{"op":"host","code":"QQQQQ","secret":"x"}' https://conker-web-port.netlify.app/api/room; echo
