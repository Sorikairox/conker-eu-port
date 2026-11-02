#!/bin/bash
# Deploy the browser build to the public site (Netlify project conker-web-port, user rule 2026-10-26: always deploy
# the latest version). Run it after a change passed its checks and browser test; it ships port/build/web as built.
#   tools/eu_port/deploy_web.sh
set -euo pipefail
cd ~/conker-wt/web
WEB_BUILD=port/build/web   # was B
[ -f $WEB_BUILD/conker.wasm ] || { echo "no build at $WEB_BUILD"; exit 1; }
# P375: the offline-play files (sw.js is stamped from port/web/sw.js, so it is checked through the stamp below)
PAGE_FILES="index.html main.js net.js gmenu.js manifest.webmanifest icon.svg icon-192.png icon-512.png"
for f in $PAGE_FILES; do cmp -s $WEB_BUILD/$f port/web/$f || { echo "build/web $f differs from port/web: rebuild first"; exit 1; }; done
SITE=~/conker-site; mkdir -p $SITE   # was S
cp $WEB_BUILD/conker.js $WEB_BUILD/conker.wasm $WEB_BUILD/conker_netx.txt $WEB_BUILD/conker_netsyms.txt $SITE/
for f in $PAGE_FILES; do cp $WEB_BUILD/$f $SITE/; done
# P375 offline play: the service worker's build id = a hash of the precached files as deployed (cache name)
python3 port/tools/sw_stamp.py port/web/sw.js $SITE
cmp -s $SITE/sw.js $WEB_BUILD/sw.js || { echo "build/web sw.js is not stamped for this build: rebuild first"; exit 1; }
git log -1 --format='%h %ad %s' --date=format:'%Y-%m-%d %H:%M' > $SITE/BUILD.txt
# P345: the room-code server (Netlify Function /api/room on Netlify Blobs). Its source is port/web/netlify; it is
# bundled from ~/conker-netlify-fn (outside the published dir, so node_modules is never published as static files),
# where npm installs @netlify/blobs from port/web/netlify/package.json.
F=~/conker-netlify-fn; mkdir -p $F/functions
rm -rf $F/functions/room; cp -R port/web/netlify/functions/room $F/functions/
if ! cmp -s port/web/netlify/package.json $F/package.json || [ ! -d $F/node_modules/@netlify/blobs ]; then
  cp port/web/netlify/package.json $F/ && (cd $F && npm install --no-audit --no-fund --silent)
fi
# the deploy runs from $F (linked to the same Netlify project): the function bundler only takes packages from under the
# directory it runs in (from ~/conker-site it shipped room.mjs without @netlify/blobs)
mkdir -p $F/.netlify && cp $SITE/.netlify/state.json $F/.netlify/
cd $F && npx -y netlify-cli@latest deploy --prod --dir $SITE --functions functions --no-build 2>&1 | grep -E "Deploy is live|Error|error|function" || true
curl -s https://conker-web-port.netlify.app/BUILD.txt
# the room server answers (a bad request gives a JSON error, nothing is stored)
curl -s -X POST -H 'content-type: application/json' -d '{"op":"host","code":"QQQQQ","secret":"x"}' https://conker-web-port.netlify.app/api/room; echo
