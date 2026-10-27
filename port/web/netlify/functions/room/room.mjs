// P345: the room-code signaling server (Netlify Function v2 at /api/room) on Netlify Blobs; the logic is core.mjs.
// Deployed by tools/eu_port/deploy_web.sh (bundled from ~/conker-netlify-fn, where npm installed @netlify/blobs).
import { getStore } from '@netlify/blobs';
import { httpHandle } from './core.mjs';

function blobStore() {
  const s = getStore({ name: 'conker-rooms', consistency: 'strong' });
  return {
    async read(k) { const r = await s.getWithMetadata(k, { type: 'json', consistency: 'strong' }); return r ? { data: r.data, etag: r.etag } : null; },
    async write(k, data, o) { const r = await s.setJSON(k, data, o.isNew ? { onlyIfNew: true } : { onlyIfMatch: o.etag }); return r ? r.modified !== false : true; },
    async del(k) { await s.delete(k); },
    async keys() { return (await s.list()).blobs.map((b) => b.key); },
  };
}

export default async (req, context) => httpHandle(req, blobStore(), context && context.ip);
export const config = { path: '/api/room' };
