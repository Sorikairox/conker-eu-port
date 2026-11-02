#!/usr/bin/env python3
"""P375 offline play: stamp the service worker's build id.

    python3 port/tools/sw_stamp.py SRC_SW_JS WEB_DIR     writes WEB_DIR/sw.js

Reads OFFLINE_PRECACHE_FILES from SRC_SW_JS (one quoted file name per line), hashes those files in WEB_DIR (SHA-256 over
name + bytes, in list order) and writes SRC_SW_JS with '__OFFLINE_BUILD_ID__' replaced by the first 16 hex of the hash.
Any change to a precached file gives a new id, so a new cache. Prints the id and the precache total.
Used by port/Makefile (build) and tools/eu_port/deploy_web.sh (the site copy).
"""
import hashlib, os, re, sys

src, web = sys.argv[1], sys.argv[2]
text = open(src, encoding='utf-8').read()
block = re.search(r'OFFLINE_PRECACHE_FILES = \[(.*?)\];', text, re.S).group(1)
names = re.findall(r"'([^']+)'", block)
h = hashlib.sha256(); total = 0
for n in names:
    data = open(os.path.join(web, n), 'rb').read()
    h.update(n.encode() + b'\0' + data); total += len(data)
build_id = h.hexdigest()[:16]
assert '__OFFLINE_BUILD_ID__' in text
out = text.replace('__OFFLINE_BUILD_ID__', build_id)
dst = os.path.join(web, 'sw.js')
if not os.path.exists(dst) or open(dst, encoding='utf-8').read() != out:
    open(dst, 'w', encoding='utf-8').write(out)
print(f'sw.js build {build_id}: {len(names)} files, {total} bytes ({total / 1048576:.2f} MB) precached')
