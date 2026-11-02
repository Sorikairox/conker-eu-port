// P375 offline play (option "Offline play", on by default): the service worker that keeps every file the page needs in
// the Cache API, so the game runs with no network once the site was loaded once. The player's ROM and saves are not
// files of the site: they stay in IndexedDB ('conker-port', main.js), which this worker never touches.
// - OFFLINE_BUILD_ID is stamped by port/tools/sw_stamp.py (the build: `make web`; the deploy: deploy_web.sh) = the first
//   16 hex of SHA-256 over the files of OFFLINE_PRECACHE_FILES: any change to a site file gives a new worker with its
//   own cache 'conker-offline-<id>'; the previous caches are deleted when the new worker activates.
// - install: every file of OFFLINE_PRECACHE_FILES is fetched past the HTTP cache and stored (all or nothing). A new
//   worker waits (no skipWaiting at install) while an older page runs: that page may still load conker.js / net.js
//   lazily, which must come from its own build. The page (main.js offlinePlay*) shows "Update ready, reload" and sends
//   'skip-waiting'; a page that loads while a new worker waits and has not started the game sends it at once (the new
//   version takes over on that load).
// - fetch: same-origin GET of a precached file = the cache (navigations to the page's folder = index.html, whatever the
//   query); anything else (the room server /api/..., /.netlify/..., BUILD.txt, dev files) goes to the network and is
//   never stored.
'use strict';
const OFFLINE_BUILD_ID = '__OFFLINE_BUILD_ID__';
const OFFLINE_CACHE_PREFIX = 'conker-offline-';
const OFFLINE_CACHE_NAME = OFFLINE_CACHE_PREFIX + OFFLINE_BUILD_ID;
// sw_stamp.py reads this list (one quoted name per line) and hashes these files
const OFFLINE_PRECACHE_FILES = [
  'index.html',
  'main.js',
  'gmenu.js',
  'net.js',
  'conker.js',
  'conker.wasm',
  'conker_netx.txt',
  'conker_netsyms.txt',
  'manifest.webmanifest',
  'icon.svg',
  'icon-192.png',
  'icon-512.png',
];
const offlineScope = () => new URL(self.registration.scope);
const offlineNeverCache = (url) => /^\/(api|\.netlify)\//.test(url.pathname);

self.addEventListener('install', (event) => {
  event.waitUntil((async () => {
    const cache = await caches.open(OFFLINE_CACHE_NAME);
    await Promise.all(OFFLINE_PRECACHE_FILES.map(async (name) => {
      const response = await fetch(new Request(new URL(name, offlineScope()), { cache: 'reload' }));
      if (!response.ok) throw new Error(`offline precache: ${name} ${response.status}`);
      await cache.put(new URL(name, offlineScope()).href, response);
    }));
  })());
});

self.addEventListener('activate', (event) => {
  event.waitUntil((async () => {
    for (const name of await caches.keys())
      if (name.startsWith(OFFLINE_CACHE_PREFIX) && name !== OFFLINE_CACHE_NAME) await caches.delete(name);
    await self.clients.claim();
  })());
});

self.addEventListener('message', (event) => {
  if (event.data === 'skip-waiting') self.skipWaiting();
});

self.addEventListener('fetch', (event) => {
  const request = event.request;
  if (request.method !== 'GET') return;
  const url = new URL(request.url), scope = offlineScope();
  if (url.origin !== scope.origin || offlineNeverCache(url)) return;
  let key = null;
  if (request.mode === 'navigate' && (url.pathname === scope.pathname || url.pathname === scope.pathname + 'index.html'))
    key = new URL('index.html', scope).href;
  else if (url.pathname.startsWith(scope.pathname) && OFFLINE_PRECACHE_FILES.includes(url.pathname.slice(scope.pathname.length)))
    key = new URL(url.pathname, scope).href;   // the query is ignored (?v=..., the page's test aids)
  if (!key) return;
  // caches.match with cacheName never creates the cache (caches.open would recreate it after the option turned it off)
  event.respondWith((async () => (await caches.match(key, { cacheName: OFFLINE_CACHE_NAME })) || fetch(request))());
});
